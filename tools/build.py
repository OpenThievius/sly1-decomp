# SPDX-License-Identifier: AGPL-3.0-or-later
"""Build a version's executable and check it against retail.

    python3 tools/build.py [--version us] [-j N]

Assembles every .s splat wrote under asm/<version>/, turns splat's binary
units into objects, and for the primary version (us) compiles src/ and puts
each C function at its retail address in place of its disassembly
(tools/c_layout.py). Then it links, lays the result out by file offset and
compares it with your retail executable. It ends with one line:

    MATCH: build/us/SCUS_971.98 sha1 57dc305db57932ad3f1122966cdb695d2e62a47a

or DIFFER, with the first differing offset. Needs tools/setup_asm.py run
first, and GNU binutils for mips (MIPS_PREFIX, default mips-linux-gnu-).
"""

import argparse
import hashlib
import os
import re
import shutil
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import asm_func  # noqa: E402
import classify_asm  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
PREFIX = os.environ.get("MIPS_PREFIX", "mips-linux-gnu-")
AS_FLAGS = ["-EL", "-march=r5900", "-mabi=eabi", "-G0", "-no-pad-sections", "-I", str(ROOT / "include")]


def tool(name):
    path = shutil.which(PREFIX + name)
    if not path:
        raise SystemExit("error: %s%s not found; install GNU binutils for mips (docs/BUILDING.md)" % (PREFIX, name))
    return path


def run(cmd):
    proc = subprocess.run(cmd, capture_output=True, text=True)
    if proc.returncode:
        raise RuntimeError("%s\n%s%s" % (" ".join(map(str, cmd)), proc.stdout, proc.stderr))
    return proc


def objects_of(ld_script):
    """The object paths splat's linker script names, relative to the root."""
    return sorted(set(re.findall(r"^\s*(build/\S+?\.o)\(", ld_script.read_text(), re.M)))


def source_of(obj, key):
    """build/<v>/asm/...s.o -> asm/...s; build/<v>/assets/x.bin.o -> assets/x.bin."""
    rel = Path(obj).relative_to(Path("build") / key)
    return ROOT / str(rel)[:-2]


def build_object(obj, key):
    src = source_of(obj, key)
    out = ROOT / obj
    out.parent.mkdir(parents=True, exist_ok=True)
    if out.exists() and out.stat().st_mtime >= src.stat().st_mtime:
        return
    if src.suffix != ".s":
        # A binary unit: wrap it in .incbin, so its object has the same ABI flags as the rest.
        wrapper = out.with_suffix(".s")
        wrapper.write_text('.section .data, "wa"\n.incbin "%s"\n' % src)
        src = wrapper
    run([tool("as")] + AS_FLAGS + [str(src), "-o", str(out)])


def build_run(src):
    out = src.with_suffix(".s.o")
    if not out.exists() or out.stat().st_mtime < src.stat().st_mtime:
        run([tool("as")] + AS_FLAGS + [str(src), "-o", str(out)])
        # GNU as aligns a MIPS .text to 16; a run starts wherever its first function does
        # (8-byte aligned, or 4 in the libraries), so its section asks for no more than that.
        start = int(src.stem.split("_")[-1], 16)
        section = "." + src.parent.name if src.parent.name in ("rodata", "data", "bss") else ".text"
        # Data runs can start at any label: 8, 4, 2 or 1, whatever its address allows.
        align = next(a for a in (8, 4, 2, 1) if start % a == 0) if section != ".text" else (8 if start % 8 == 0 else 4)
        run([tool("objcopy"), "--set-section-alignment", "%s=%d" % (section, align), str(out)])


def included_asm():
    """The functions the whole files (config/us/files.tsv) include with INCLUDE_ASM."""
    names = set()
    for line in (ROOT / "config" / "us" / "files.tsv").read_text().splitlines()[1:]:
        names |= set(asm_func.included((ROOT / line.split("\t")[0]).read_text()))
    return names


EXPECTED_MARKER = {"handwritten": "ASM_FUNC", "inline": "INCLUDE_ASM", "remnant": "LINKER_REMNANT"}


def marker_errors(files=None, table=None):
    """The inclusions of the whole files whose marker disagrees with config/us/original_asm.tsv:
    ASM_FUNC for hand-written assembly, LINKER_REMNANT for a linker's leftover, INCLUDE_ASM for a
    function still to match (include/asm_func.h)."""
    table = classify_asm.read_table() if table is None else table
    if files is None:
        files = [(line.split("\t")[0], (ROOT / line.split("\t")[0]).read_text())
                 for line in (ROOT / "config" / "us" / "files.tsv").read_text().splitlines()[1:]]
    errors = []
    for path, text in files:
        for marker, name in asm_func.markers(text):
            want = EXPECTED_MARKER.get(table.get(name), "INCLUDE_ASM")
            if marker.replace("_AFTER_INIT", "") != want:
                errors.append("%s: %s(%s) should be %s(%s) (config/us/original_asm.tsv)"
                              % (path, marker, name, want, name))
    return errors


def write_c_data(key, data_placed):
    """config/<key>/c_data.tsv: every global a C file defines, in a build that printed MATCH
    (tools/progress.py counts their bytes as matched data)."""
    rows = ["name\taddress\tsize\tsection\tsource"]
    listings = {}
    for addr, size, obj, section, name in sorted(data_placed):
        rel = Path(obj).relative_to(Path("build") / key)
        # A C++ file, or a C file (the toolchain's runtime, docs/TOOLCHAIN.md).
        source = next((rel.with_suffix(s) for s in (".cpp", ".c") if (ROOT / rel.with_suffix(s)).exists()),
                      rel.with_suffix(".cpp")).as_posix()
        if section in (".rodata", ".data"):
            # A whole file's section: the labels it includes from the disassembly are not C.
            text = (ROOT / source).read_text()
            included = asm_func.included_rodata(text) if section == ".rodata" else asm_func.included_data(text)
            if included:
                name_ = "rodata.rodata.s" if section == ".rodata" else "data.data.s"
                if name_ not in listings:
                    listings[name_] = (ROOT / "asm" / key / "data" / name_).read_text()
                size -= sum(asm_func.label_size(listings[name_], label) for label in included)
        rows.append("%s\t%08X\t%d\t%s\t%s" % (name, addr, size, section, source))
    path = ROOT / "config" / key / "c_data.tsv"
    text = "\n".join(rows) + "\n"
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


def first_difference(a, b):
    for i, (x, y) in enumerate(zip(a, b)):
        if x != y:
            return i
    return min(len(a), len(b)) if len(a) != len(b) else None


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--version", default=versions.primary(), choices=sorted(versions.versions()))
    parser.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    args = parser.parse_args(argv)

    key = args.version
    v = versions.get(key)
    name = v["boot"]["name"]
    out_dir = ROOT / "build" / key
    ld_script = out_dir / ("%s.splat.ld" % name)
    if not ld_script.exists():
        print("error: %s is missing; run python3 tools/setup_asm.py --version %s" % (ld_script.relative_to(ROOT), key))
        return 1

    if key == versions.primary():
        errors = marker_errors()
        if errors:
            print("\n".join("error: " + e for e in errors))
            return 1
    placed, data_placed = [], []
    try:
        if key == versions.primary():
            import c_layout
            objects = c_layout.compile_sources(args.jobs)
            ld_script, runs, placed, data_placed = c_layout.layout(ld_script, objects)
        objs = [o for o in objects_of(ld_script) if not o.startswith(("build/%s/src/" % key, "build/%s/text/" % key, "build/%s/data/" % key,
                                                                "build/%s/bss/" % key, "build/%s/rodata/" % key))]
        with ThreadPoolExecutor(args.jobs) as pool:
            list(pool.map(lambda o: build_object(o, key), objs))
            if key == versions.primary():
                list(pool.map(build_run, runs))
    except Exception as e:  # LayoutError, RuntimeError
        print("error: %s" % e)
        return 1

    elf = out_dir / ("%s.elf" % name)
    flat = out_dir / name
    scripts = [ld_script] + [p for p in (out_dir / "undefined_syms_auto.txt", out_dir / "undefined_funcs_auto.txt") if p.exists()]
    try:
        cmd = [tool("ld"), "-EL", "-o", str(elf), "-Map", str(out_dir / ("%s.map" % name)), "--no-check-sections"]
        for s in scripts:
            cmd += ["-T", str(s)]
        run(cmd)
        run([tool("objcopy"), "-O", "binary", str(elf), str(flat)])
    except RuntimeError as e:
        print("error: %s" % e)
        return 1

    built = flat.read_bytes()
    sha1 = hashlib.sha1(built).hexdigest()
    rel = flat.relative_to(ROOT)
    # A whole file also holds the assembly functions inside its range (include/asm_func.h): the
    # original assembly, and the functions not matched yet. They are placed with it, but not C.
    asm = set(classify_asm.read_table()) | included_asm()
    from_c = [p for p in placed if p[-1] not in asm]
    linked = (" with %d function%s from C" % (len(from_c), "" if len(from_c) == 1 else "s")) if from_c else ""
    if data_placed:
        linked += " and %d global%s" % (len(data_placed), "" if len(data_placed) == 1 else "s")
    if sha1 == v["boot"]["sha1"]:
        if key == versions.primary():
            write_c_data(key, data_placed)
            import padding
            padding.write(key)  # the alignment padding between that data (config/us/padding.tsv)
        print("MATCH: %s sha1 %s%s" % (rel, sha1, linked))
        return 0
    retail = versions.boot_path(key).read_bytes()
    at = first_difference(built, retail)
    print("DIFFER: %s sha1 %s, not %s (%d bytes against %d; first difference at file offset 0x%X)"
          % (rel, sha1, v["boot"]["sha1"], len(built), len(retail), at if at is not None else -1))
    return 1


if __name__ == "__main__":
    sys.exit(main())
