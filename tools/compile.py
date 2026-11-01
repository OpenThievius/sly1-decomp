# SPDX-License-Identifier: AGPL-3.0-or-later
"""Compile one C++ file to an object the way the game was built.

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
-ffunction-sections, so that the build can place each function at its address
(tools/build.py).
"""

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import toolchain  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
CFLAGS = ROOT / "config" / "cflags.tsv"
# What ee-gcc passes cpp for a C++ unit: the specs' predefines and cpp specs, and GCC's own.
CPP_DEFINES = ["-lang-c++", "-undef", "-D__GNUC__=2", "-D__GNUC_MINOR__=9", "-D__GNUG__=2", "-D__cplusplus",
               "-Dmips", "-DMIPSEL", "-DR5900", "-D_mips", "-D_MIPSEL", "-D_R5900",
               "-D__mips__", "-D__MIPSEL__", "-D__R5900__", "-D__mips=3", "-D__mips64", "-D__mips_eabi",
               "-D__mips_single_float", "-D__SIZE_TYPE__=unsigned", "-D__PTRDIFF_TYPE__=int",
               "-D__LANGUAGE_C", "-D_LANGUAGE_C", "-DLANGUAGE_C",
               "-I", "include", "-I", "src"]
LAYOUT_FLAGS = ["-ffunction-sections"]
# A compile takes a second or two; a run under the Windows runner can hang for good (seen with
# wibo), so every step gives up after this many seconds and the file counts as not compiling.
TIMEOUT = int(os.environ.get("SLY1_COMPILE_TIMEOUT", "120"))


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


def run_step(cmd, **kw):
    """subprocess.run with the time limit: a hung step is killed and raises CompileError."""
    try:
        return subprocess.run(cmd, capture_output=True, text=True, timeout=TIMEOUT, **kw)
    except subprocess.TimeoutExpired:
        raise CompileError("%s did not finish in %d seconds" % (Path(cmd[0]).name, TIMEOUT))


def compile_file(src, out, flags=None, keep_asm=None, source=None):
    """Compile `src` to the object `out`. Returns the cc1plus assembly text.

    source: the file whose config/cflags.tsv row applies (a version's unit takes its shared file's).
    """
    src = Path(src).resolve()
    source = Path(source).resolve() if source else src
    run, cpp, cc1plus, ee_as = tools(compiler_for(source))
    flags = flags if flags is not None else flags_for(source)
    with tempfile.TemporaryDirectory(prefix="sly1-cc-") as tmp:
        ii, s = Path(tmp) / "unit.ii", Path(tmp) / "unit.s"
        # The Windows tools get paths relative to the repository root, where they run.
        for cmd in (run + [str(cpp)] + CPP_DEFINES + [os.path.relpath(src, ROOT), str(ii)],
                    run + [str(cc1plus), "-quiet"] + flags + LAYOUT_FLAGS + [str(ii), "-o", str(s)]):
            proc = run_step(cmd, cwd=ROOT)
            if proc.returncode or (proc.stderr.strip() and not s.exists() and cmd[-1] == str(s)):
                raise CompileError((proc.stderr or proc.stdout).strip() or "%s failed" % Path(cmd[len(run)]).name)
        asm = s.read_text()
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
