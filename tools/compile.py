# SPDX-License-Identifier: AGPL-3.0-or-later
"""Compile one C++ file (or C file) to an object the way the game was built.

    python3 tools/compile.py FILE.cpp OUT.o [--flags "-O2 ..."]

The pipeline is the compiler driver's, run step by step: the toolchain's
cpp.exe with the driver's predefined macros, the release's cc1plus.exe
(docs/TOOLCHAIN.md), then ee/bin/as.exe (GNU as 2.9-ee-991111b) with the
options the driver gives it (-G and -O from the file's flags). Retail's
assembler matters: it expands `move` to `daddu`, where a modern GNU as writes
`or`. A file's flags and compiler come from config/cflags.tsv: its own row
(`file<TAB>flags<TAB>compiler`, the compiler optional), or the `default` row
and the `compiler` row. The game is SN GCC 2.95.3; Sony's libraries are Sony's
own 2.9-ee-991111, as OpenRAC builds its SDK objects. Every file also gets
-ffunction-sections and -fdata-sections, so that the build can place each
function and each global it defines at its address (tools/build.py). The
functions the compiler makes for a file (a static initialiser, the constructor
that calls it) take retail's names from config/us/generated.tsv.

A `.c` file is C, built by the release's cc1 (cc1.exe, or a Linux build's cc1) with the
driver's C predefines: the toolchain's own runtime (libgcc, compiled from C) has C that only
the C front end gives, such as __builtin_eh_return, which cc1plus lacks.

A compiler that only exists as Sony's Linux build (2.9-ee-991111-01, the math
library's) runs the way OpenRAC's rac1-decomp runs it: its own 32-bit Linux
cc1plus with its own loader, from a folder of the toolchain directory, inside an
i386 Linux container where the machine is not x86 Linux. Its preprocessor and
assembler are the Windows ones of the same release.
"""

import argparse
import os
import platform
import re
import shutil
import signal
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import asm_func  # noqa: E402
import toolchain  # noqa: E402
import versions  # noqa: E402
import volatile_slots  # noqa: E402

ROOT = versions.ROOT
CFLAGS = ROOT / "config" / "cflags.tsv"
# What ee-gcc passes cpp for a C++ unit: the specs' predefines and cpp specs, and GCC's own.
CPP_DEFINES = ["-lang-c++", "-undef", "-D__GNUC__=2", "-D__GNUC_MINOR__=9", "-D__GNUG__=2", "-D__cplusplus",
               "-Dmips", "-DMIPSEL", "-DR5900", "-D_mips", "-D_MIPSEL", "-D_R5900",
               "-D__mips__", "-D__MIPSEL__", "-D__R5900__", "-D__mips=3", "-D__mips64", "-D__mips_eabi",
               "-D__mips_single_float", "-D__SIZE_TYPE__=unsigned", "-D__PTRDIFF_TYPE__=int",
               "-D__LANGUAGE_C", "-D_LANGUAGE_C", "-DLANGUAGE_C",
               "-I", "include", "-I", "src"]
# What it passes for a C unit: the same, without the C++ ones.
C_DEFINES = [d for d in CPP_DEFINES if d not in ("-lang-c++", "-D__GNUG__=2", "-D__cplusplus")]
LAYOUT_FLAGS = ["-ffunction-sections", "-fdata-sections"]
# A compile takes a second or two; a run under the Windows runner can hang for good (seen with
# wibo), so every step gives up after this many seconds and the file counts as not compiling.
TIMEOUT = int(os.environ.get("SLY1_COMPILE_TIMEOUT", "120"))
# Sony's Linux compiler builds: the folder of the toolchain directory each may be unpacked to
# (decomp.me's compilers release, as OpenRAC fetches them), and the Windows release whose
# preprocessor and assembler go with it.
LINUX_TREES = ("ee-gcc-2.9-991111-01", "ee-gcc-2.9-dtls13010")
LINUX_COMPANION = {"2.9-ee-991111-01": "2.9-ee-991111"}
LINUX_IMAGE = "i386/busybox:1.36"


def generated_names(source):
    """{compiler's symbol: function name} of what the compiler makes for `source`
    (config/us/generated.tsv: file, symbol, function)."""
    path = ROOT / "config" / "us" / "generated.tsv"
    if not path.exists():
        return {}
    rel = os.path.relpath(source, ROOT)
    rows = [l.split("\t") for l in path.read_text().splitlines()[1:] if l]
    return {sym: func for f, sym, func in rows if f == rel}


def rename_generated(asm, names):
    """The assembly with each compiler-made symbol under its function name. A name ending in `*`
    stands for any rest: `_GLOBAL_$I$*` is the file's constructor, which GCC names after the
    file's first public definition."""
    for sym, func in names.items():
        rest = r"[\w$.]*" if sym.endswith("*") else ""
        # Its own section (.text.SYMBOL, -ffunction-sections) takes the name too.
        pattern = re.compile(r"(?<![\w$])%s%s(?![\w$.])" % (re.escape(sym.rstrip("*")), rest))
        if not pattern.search(asm):
            raise CompileError("config/us/generated.tsv names %s, which the compiler did not make" % sym)
        asm = pattern.sub(func, asm)
    return asm


class CompileError(Exception):
    pass


def compiler_release():
    """The compiler release config/cflags.tsv names (its `compiler` row): a gcc-lib/ee/ folder."""
    for line in CFLAGS.read_text().splitlines():
        if line.startswith("compiler\t"):
            return line.split("\t", 1)[1].strip()
    raise CompileError("config/cflags.tsv has no compiler row")


def row_for(path):
    """(flags, compiler) config/cflags.tsv gives a source file: its own row, or the defaults."""
    rel = str(Path(path).resolve().relative_to(ROOT)) if Path(path).resolve().is_relative_to(ROOT) else None
    default = None
    for line in CFLAGS.read_text().splitlines():
        if not line.strip() or line.startswith(("#", "compiler\t")):
            continue
        name, rest = line.split("\t", 1)
        flags, _, compiler = rest.partition("\t")
        if name == "default":
            default = flags.split()
        elif rel and name == rel:
            return flags.split(), compiler.strip() or compiler_release()
    if default is None:
        raise CompileError("config/cflags.tsv has no default row")
    return default, compiler_release()


def flags_for(path):
    """The flags config/cflags.tsv gives a source file."""
    return row_for(path)[0]


def compiler_for(path):
    """The compiler release (a gcc-lib/ee/ folder) that builds a source file; SLY1_COMPILER overrides it."""
    return os.environ.get("SLY1_COMPILER") or row_for(path)[1]


def tools(release=None):
    root = toolchain.toolchain_dir()
    if root is None:
        raise CompileError("no toolchain: set SLY1_TOOLCHAIN or link ./toolchain (docs/TOOLCHAIN.md)")
    release = release or os.environ.get("SLY1_COMPILER") or compiler_release()
    cc1plus = root / "lib" / "gcc-lib" / "ee" / release / "cc1plus.exe"
    if not cc1plus.exists():
        raise CompileError("no lib/gcc-lib/ee/%s/cc1plus.exe in %s" % (release, root))
    run = toolchain.runner(cc1plus)
    if run is None:
        raise CompileError("no runner for the Windows tools: install wibo or wine, or set SLY1_RUNNER")
    # ee/bin/as.exe, the assembler the compiler driver runs: GNU as 2.9-ee-991111b as SN ships it.
    # Unlike bin/ee-as.exe of the same release, it puts no nop between mtc1 and the instruction
    # that uses the register, as retail has none (the R5900 interlocks there).
    ee_as = root / "ee" / "bin" / "as.exe"
    if not ee_as.exists():
        raise CompileError("no ee/bin/as.exe in %s" % root)
    return run, cc1plus.parent / "cpp.exe", cc1plus, ee_as


def linux_cc1plus(release, front="cc1plus"):
    """(command, tree) running a Linux release's cc1plus (or `front`, cc1 for C) through its own
    loader, or None.

    SLY1_LINUX_TOOLCHAIN names the folder; else the toolchain directory's LINUX_TREES."""
    env = os.environ.get("SLY1_LINUX_TOOLCHAIN")
    root = toolchain.toolchain_dir()
    trees = [Path(env).expanduser()] if env else [root / t for t in LINUX_TREES] if root else []
    for tree in trees:
        cc1plus = tree / "lib" / "gcc-lib" / "ee" / release / (front + ".bin")
        if cc1plus.exists():
            tree = tree.resolve()
            lib = tree / "lib"
            return [str(lib / "ld-2.3.6.so"), "--library-path", str(lib), str(cc1plus.resolve())], tree
    return None


def linux_runner(mounts):
    """What runs a 32-bit Linux program here: nothing on x86 Linux, else a container that sees
    each of `mounts` at its own path. SLY1_LINUX_RUNNER overrides it."""
    env = os.environ.get("SLY1_LINUX_RUNNER")
    if env is not None:
        return env.split()
    if sys.platform.startswith("linux") and platform.machine() in ("x86_64", "i386", "i686"):
        return []
    cmd = ["docker", "run", "--rm", "--platform", "linux/386"]
    for path in mounts:
        cmd += ["-v", "%s:%s" % (path, path)]
    return cmd + ["-w", str(ROOT.resolve()), LINUX_IMAGE]


def exit_note(code):
    """What a step's exit code says, for its error. cc1plus.exe reserves a 1 MiB stack (its PE
    header): a very large function can overflow it, which wibo reports as SIGSEGV and Windows as
    STATUS_STACK_OVERFLOW (0xC00000FD)."""
    if not code:
        return ""
    if code in (-signal.SIGSEGV, 0xC00000FD, 0xC00000FD - (1 << 32)):
        return " (exit %d: crashed, likely cc1plus.exe's 1 MiB stack overflowing)" % code
    return " (exit %d)" % code


def run_step(cmd, **kw):
    """Run one step with the time limit; a hung step is killed and raises CompileError.

    The step writes to files, not pipes, and runs in its own process group: a Windows tool that
    hangs under its runner can leave a child stuck in the kernel, which no signal removes and
    which would hold a pipe open for good. On timeout the group is killed and nothing waits on it.
    """
    with tempfile.TemporaryFile("w+") as out, tempfile.TemporaryFile("w+") as err:
        proc = subprocess.Popen(cmd, stdout=out, stderr=err, text=True, start_new_session=True, **kw)
        try:
            proc.wait(timeout=TIMEOUT)
        except subprocess.TimeoutExpired:
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except OSError:
                pass
            raise CompileError("%s did not finish in %d seconds" % (Path(cmd[0]).name, TIMEOUT))
        out.seek(0)
        err.seek(0)
        return subprocess.CompletedProcess(cmd, proc.returncode, out.read(), err.read())


REMNANT_BLOCK = re.compile(r" #APP\n\s*# linker remnant\n.*?\n #NO_APP\n", re.S)
STATIC_INIT = re.compile(r"^\t\.ent\t__static_initialization_and_destruction_0$", re.M)
CONSTRUCTOR = re.compile(r"^\t\.align\t\d+\n\t\.globl\t_GLOBAL_\$I\$", re.M)


def place_remnants(asm):
    """Move the LINKER_REMNANT_AFTER_INIT blocks a file writes after its last function to just
    before its _GLOBAL_$I$, where retail has them (include/asm_func.h). GCC emits a file-scope asm
    where it reads it, and the static initialiser and _GLOBAL_$I$ only at the end of the unit."""
    init, ctor = STATIC_INIT.search(asm), CONSTRUCTOR.search(asm)
    if not init or not ctor or ctor.start() < init.start():
        return asm
    last_end = asm.rfind("\t.end\t", 0, init.start())
    blocks = [m for m in REMNANT_BLOCK.finditer(asm) if last_end < m.start() < init.start()]
    if not blocks:
        return asm
    moved = "".join(m.group(0) for m in blocks)
    for m in reversed(blocks):
        asm = asm[:m.start()] + asm[m.end():]
    at = CONSTRUCTOR.search(asm).start()
    return asm[:at] + moved + asm[at:]


def compile_file(src, out, flags=None, keep_asm=None, source=None, whole=False):
    """Compile `src` to the object `out`. Returns the cc1plus assembly text.

    source: the file whose config/cflags.tsv row applies (a version's unit takes its shared file's).
    whole: compile it as the original was, without -ffunction-sections and -fdata-sections (a
    whole file of config/us/files.tsv, linked as one object).
    """
    src = Path(src).resolve()
    source = Path(source).resolve() if source else src
    release = compiler_for(source)
    # Without the Linux build, its Windows companion builds the file, as rac1-decomp does: the
    # build still works, but what only the Linux build gives cannot match.
    is_c = src.suffix == ".c"
    linux = linux_cc1plus(release, "cc1" if is_c else "cc1plus") if release in LINUX_COMPANION else None
    run, cpp, cc1plus, ee_as = tools(LINUX_COMPANION.get(release, release))
    if is_c:
        cc1plus = cc1plus.parent / "cc1.exe"
        if not cc1plus.exists():
            raise CompileError("no %s" % cc1plus)
    flags = flags if flags is not None else flags_for(source)
    # The original assembly functions the file includes (include/asm_func.h), written from the
    # disassembly before the assembler reads them.
    text = src.read_text()
    asm_func.write(asm_func.included(text))
    asm_func.write_rodata(asm_func.included_rodata(text))
    asm_func.write_data(asm_func.included_data(text))
    with tempfile.TemporaryDirectory(prefix="sly1-cc-") as tmp:
        ii, s = Path(tmp).resolve() / "unit.ii", Path(tmp).resolve() / "unit.s"
        if linux:
            command, tree = linux
            compiler = linux_runner([ROOT.resolve(), tree, ii.parent]) + command
        else:
            compiler = run + [str(cc1plus)]
        # The Windows tools get paths relative to the repository root, where they run.
        for cmd, name in ((run + [str(cpp)] + (C_DEFINES if is_c else CPP_DEFINES) + [os.path.relpath(src, ROOT), str(ii)], "cpp"),
                          (compiler + ["-quiet"] + flags + ([] if whole else LAYOUT_FLAGS) + [str(ii), "-o", str(s)], "cc1plus")):
            proc = run_step(cmd, cwd=ROOT)
            if proc.returncode or (proc.stderr.strip() and not s.exists() and cmd[-1] == str(s)):
                raise CompileError(((proc.stderr or proc.stdout).strip() or "%s failed" % name)
                                   + exit_note(proc.returncode))
        asm = s.read_text()
        placed = place_remnants(asm)
        if placed != asm:
            asm = placed
            s.write_text(asm)
        names = generated_names(source)
        if names:
            asm = rename_generated(asm, names)
        if release == "2.9-ee-991111":
            # The assembler that built Sony's libraries put a volatile store into the slot of
            # the call after it; ours leaves the slot empty (tools/volatile_slots.py).
            asm = volatile_slots.fill(asm)
        if names or release == "2.9-ee-991111":
            s.write_text(asm)
        if keep_asm:
            Path(keep_asm).write_text(asm)
        as_flags = [f for f in flags if f.startswith(("-G", "-O"))] + os.environ.get("SLY1_ASFLAGS", "").split()
        proc = run_step(run + [str(ee_as)] + as_flags + [str(s), "-o", str(Path(tmp) / "unit.o")], cwd=ROOT)
        if not proc.returncode:
            # ee-as (1999) leaves local symbols after the symbol table's sh_info, which modern ld
            # refuses; objcopy writes the same sections and code back with the table in order.
            objcopy = shutil.which(os.environ.get("MIPS_PREFIX", "mips-linux-gnu-") + "objcopy")
            if objcopy is None:
                raise CompileError("GNU objcopy for mips not found (MIPS_PREFIX, default mips-linux-gnu-)")
            proc = subprocess.run([objcopy, str(Path(tmp) / "unit.o"), str(out)], capture_output=True, text=True)
        if proc.returncode:
            raise CompileError(proc.stderr.strip())
    return asm


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("src")
    parser.add_argument("out")
    parser.add_argument("--flags", help="override config/cflags.tsv")
    parser.add_argument("--asm", help="also write cc1plus's assembly here")
    args = parser.parse_args(argv)
    try:
        compile_file(args.src, args.out, args.flags.split() if args.flags else None, args.asm)
    except CompileError as e:
        print("error: %s" % e, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
