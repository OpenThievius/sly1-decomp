# SPDX-License-Identifier: AGPL-3.0-or-later
"""Put the C of src/ into the US build, each function at its retail address.

tools/build.py calls this for the primary version. Every src/**/*.cpp is
compiled with its flags (tools/compile.py) into build/us/src/; each function
it defines sits in its own section (-ffunction-sections) and is placed where
retail has it. The disassembly of .text is cut into runs of the functions
between them (build/us/text/), and splat's linker script gets the runs and the
C functions in address order in place of the one .text object.

A C file may hold only code for now: an object with .data, .rodata or .bss is
refused, since that data is still placed from the disassembly.
"""

import re
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check  # noqa: E402
import compile as cc  # noqa: E402
import elf  # noqa: E402
import rodata  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
DATA_SECTIONS = (".data", ".rodata", ".bss", ".sdata", ".sbss", ".lit4", ".lit8")


class LayoutError(Exception):
    pass


def sources():
    return sorted((ROOT / "src").rglob("*.cpp")) if (ROOT / "src").exists() else []


def compile_sources(jobs):
    """{source: object path} for every src/ file, compiled where it changed."""
    out = {}
    image, resolver = check.retail_image("us"), check.Resolver("us")

    def one(src):
        obj = ROOT / "build" / "us" / "src" / src.relative_to(ROOT / "src").with_suffix(".o")
        obj.parent.mkdir(parents=True, exist_ok=True)
        deps = [src, ROOT / "config" / "cflags.tsv"] + sorted((ROOT / "include").rglob("*.h"))
        if not obj.exists() or obj.stat().st_mtime < max(d.stat().st_mtime for d in deps if d.exists()):
            try:
                cc.compile_file(src, obj)
                rodata.bake(obj, image, resolver)
            except cc.CompileError as e:
                raise LayoutError("%s does not compile:\n%s" % (src.relative_to(ROOT), e))
            except rodata.RodataError as e:
                raise LayoutError("%s: %s" % (src.relative_to(ROOT), e))
        return src, obj

    with ThreadPoolExecutor(jobs) as pool:
        for src, obj in pool.map(one, sources()):
            out[src] = obj
    return out


def placements(objects):
    """[(address, size, object, section, symbol)] of every C function, and the aliases the link needs."""
    resolver = check.Resolver("us")
    functions = check.load_functions("us")
    starts = {a: n for n, (a, s, k) in functions.items()}
    placed, aliases, defined = [], {}, set()
    for src, path in objects.items():
        obj = elf.Elf(path.read_bytes())
        rel = path.relative_to(ROOT)
        for sec in obj.sections:
            if sec["name"].startswith(DATA_SECTIONS) and sec["size"]:
                raise LayoutError("%s has %s data (%d bytes): only code can be linked from C for now. "
                                  "A constant retail loads from .rodata is read through an extern "
                                  "(extern f32 D_00219718[];), not written as a literal"
                                  % (src.relative_to(ROOT), sec["name"], sec["size"]))
        for sym in obj.symbols:
            if sym["type"] != elf.STT_FUNC or sym["shndx"] in (elf.SHN_UNDEF,) or sym["shndx"] >= len(obj.sections):
                continue
            section = obj.sections[sym["shndx"]]["name"]
            if not section.startswith(".text"):
                continue
            addr = resolver.us_address(sym["name"])
            if addr is None or addr not in starts:
                raise LayoutError("%s defines %s, which is no function of config/us/functions.tsv"
                                  % (src.relative_to(ROOT), sym["name"]))
            if addr in {p[0] for p in placed}:
                raise LayoutError("two definitions of the function at 0x%X (%s)" % (addr, sym["name"]))
            placed.append((addr, sym["size"], rel, section, sym["name"]))
            defined.add(sym["name"])
            if starts[addr] != sym["name"]:
                aliases[starts[addr]] = sym["name"]       # the disassembly calls it by its splat name
        for sym in obj.symbols:
            if sym["shndx"] == elf.SHN_UNDEF and sym["name"]:
                base = check.base_name(sym["name"])
                if base != sym["name"]:
                    aliases.setdefault(sym["name"], base)  # C calls func_X__Fi; the disassembly defines func_X
    # A name both defined in C and aliased to its base would loop: keep the C definition.
    for name in defined:
        if aliases.get(name) and aliases[name] not in defined:
            aliases.pop(name)
    placed.sort()
    return placed, aliases


LABEL = re.compile(r"\.word\s+(\.L([0-9A-Fa-f]{8}))\b")


def case_labels(placed):
    """{.LXXXXXXXX: address} of the jump-table targets that fall inside a C function.

    The disassembly's tables name the labels of its own text; with that text replaced by C, the link
    gets them as absolute symbols at the same addresses.
    """
    spans = [(a, a + size) for a, size, *_ in placed]
    out = {}
    for path in (ROOT / "asm" / "us" / "data").glob("*.s"):
        for m in LABEL.finditer(path.read_text()):
            addr = int(m.group(2), 16)
            if any(lo <= addr < hi for lo, hi in spans):
                out[m.group(1)] = addr
    return out


def split_text(key):
    """The header lines of asm/<key>/text.s and {function: its lines}, in address order."""
    lines = (ROOT / "asm" / key / "text.s").read_text().splitlines()
    starts = [i for i, l in enumerate(lines) if l.startswith("nonmatching ")]
    if not starts:
        raise LayoutError("asm/%s/text.s has no functions" % key)

    def back(i):
        # A function's own preamble: the alignment and the comment just above it.
        while i > 0 and (lines[i - 1].startswith((".align", "/* Handwritten")) or not lines[i - 1].strip()):
            i -= 1
        return i

    cuts = [back(i) for i in starts]
    header = lines[:cuts[0]]
    chunks = {}
    for n, cut in enumerate(cuts):
        name = lines[starts[n]].split()[1].rstrip(",")
        chunks[name] = lines[cut:cuts[n + 1] if n + 1 < len(cuts) else len(lines)]
    return header, chunks


def write_if_changed(path, text):
    if not path.exists() or path.read_text() != text:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)


ABSOLUTE = re.compile(r"^(D_[0-9A-Fa-f]+)\s*=\s*0x([0-9A-Fa-f]+);", re.M)


def absolute_aliases(syms_text):
    """{8-digit name: splat's name} for the data symbols splat pins to an address outside the executable.

    The disassembly knows D_FA0; C, like tools/check.py, spells it D_00000FA0.
    """
    out = {}
    for m in ABSOLUTE.finditer(syms_text):
        long = "D_%08X" % int(m.group(2), 16)
        if long != m.group(1):
            out[long] = m.group(1)
    return out


ALIGN = re.compile(r"^\s*\.align\s+(\d+)", re.M)


def run_alignment(lines):
    """The alignment, in bytes, that a run's section is given by its .align directives (4 for none)."""
    bits = [int(m.group(1)) for m in ALIGN.finditer("\n".join(lines))]
    return max([4] + [1 << b for b in bits])


def layout(ld_script, objects):
    """Write the runs of disassembly and the linker script with the C placed. Returns (script, run sources)."""
    placed, aliases = placements(objects)
    syms = ld_script.with_name("undefined_syms_auto.txt")
    if syms.exists():
        aliases.update(absolute_aliases(syms.read_text()))
    functions = check.load_functions("us")
    order = sorted(functions.items(), key=lambda kv: kv[1][0])
    text_start = order[0][1][0]
    c_at = {p[0]: p for p in placed}
    header, chunks = split_text("us")
    text_dir = ROOT / "build" / "us" / "text"
    # Every entry is pinned at its retail address (inside an output section, `.` is an offset
    # from its start); ld fills the gaps with zeros, which is retail's padding (nop).
    entries, runs, run = [], [], []

    def emit(names):
        start = functions[names[0]][0]
        body = header + [l for name in names for l in chunks[name]]
        need = run_alignment(body)
        if start % need:
            if len(names) > 1:
                # A later .align directive would round the whole section up: give the first
                # function a section of its own, which asks for no more than its address has.
                emit(names[:1])
                emit(names[1:])
                return
            raise LayoutError("a run of disassembly would start at 0x%X, which is not %d-byte aligned, "
                              "as its .align directives need" % (start, need))
        path = text_dir / ("run_%08X.s" % start)
        write_if_changed(path, "\n".join(body) + "\n")
        runs.append(path)
        entries.append("        . = 0x%X;" % (start - text_start))
        entries.append("        %s(.text);" % path.relative_to(ROOT).with_suffix(".s.o"))

    def flush():
        if not run:
            return
        emit(list(run))
        run.clear()

    for name, (addr, size, kind) in order:
        p = c_at.get(addr)
        if p:
            flush()
            if p[1] > size:
                raise LayoutError("%s is %d bytes, more than retail's %d at 0x%X" % (p[4], p[1], size, addr))
            entries.append("        . = 0x%X;" % (addr - text_start))
            entries.append("        %s(%s);" % (p[2], p[3]))
        else:
            run.append(name)
    flush()
    for stale in text_dir.glob("run_*.s"):
        if stale not in runs:
            stale.unlink()

    text = ld_script.read_text()
    marker = re.compile(r"^\s*build/us/asm/us/text\.s\.o\((\.[a-z]+)\);$", re.M)
    if not marker.search(text):
        raise LayoutError("%s has no text.s object to replace" % ld_script.relative_to(ROOT))
    text = marker.sub(lambda m: "\n".join(entries) if m.group(1) == ".text" else "", text)
    labels = case_labels(placed)
    if labels:
        text += "\n" + "\n".join("PROVIDE(%s = 0x%X);" % (n, a) for n, a in sorted(labels.items())) + "\n"
    if aliases:
        text += "\n" + "\n".join("PROVIDE(%s = %s);" % (a, b) for a, b in sorted(aliases.items())) + "\n"
    out = ld_script.with_name(ld_script.name.replace(".splat.ld", ".ld"))
    write_if_changed(out, text)
    return out, runs, placed
