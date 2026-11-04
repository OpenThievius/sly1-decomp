# SPDX-License-Identifier: AGPL-3.0-or-later
"""Put the C of src/ into the US build, each function at its retail address.

tools/build.py calls this for the primary version. Every src/**/*.cpp is
compiled with its flags (tools/compile.py) into build/us/src/; each function
it defines sits in its own section (-ffunction-sections) and is placed where
retail has it. The disassembly of .text is cut into runs of the functions
between them (build/us/text/), and splat's linker script gets the runs and the
C functions in address order in place of the one .text object.

A C file may hold only code for now: an object with .data, .rodata or .bss is
refused, since that data is still placed from the disassembly. Two kinds of data
are taken out of the object instead: .rodata literals (tools/rodata.py), and the
frame tables a file built with exceptions on carries in .data, which no code
refers to and whose retail copy is in the disassembly's .data.
"""

import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check  # noqa: E402
import compile as cc  # noqa: E402
import elf  # noqa: E402
import rodata  # noqa: E402
import todo  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
WHOLE = todo.whole_files()
DATA_SECTIONS = (".data", ".rodata", ".bss", ".sdata", ".sbss", ".lit4", ".lit8")
DATA_NAME = re.compile(r"^\.(?:data|rodata)\.(D_[0-9A-F]{8})$")
ADDR_LABEL = re.compile(r"^D_[0-9A-F]{8}$")
ALIGN = re.compile(r"^\s*\.align\s+\d+\s*$")


class LayoutError(Exception):
    pass


def sources():
    return versions.sources()


def compile_sources(jobs):
    """{source: object path} for every src/ file, compiled where it changed."""
    out = {}
    image, resolver = check.retail_image("us"), check.Resolver("us")

    def one(src):
        obj = ROOT / "build" / "us" / "src" / src.relative_to(ROOT / "src").with_suffix(".o")
        obj.parent.mkdir(parents=True, exist_ok=True)
        deps = [src, ROOT / "config" / "cflags.tsv"] + sorted((ROOT / "include").rglob("*.h"))
        whole = str(src.relative_to(ROOT)) in WHOLE
        deps.append(ROOT / "config" / "us" / "files.tsv")
        if not obj.exists() or obj.stat().st_mtime < max(d.stat().st_mtime for d in deps if d.exists()):
            try:
                cc.compile_file(src, obj, whole=whole)
                if not whole:  # a whole file's .rodata is linked where retail has it
                    rodata.bake(obj, image, resolver)
                    drop_frame_tables(obj)
            except cc.CompileError as e:
                raise LayoutError("%s does not compile:\n%s" % (src.relative_to(ROOT), e))
            except rodata.RodataError as e:
                raise LayoutError("%s: %s" % (src.relative_to(ROOT), e))
        return src, obj

    # A file whose compiler is a Linux build the toolchain lacks (the math library's) stays
    # assembly: the Windows build of that release cannot give its functions, and the image
    # still matches with them taken from the disassembly.
    missing = {}
    for src in sources():
        release = cc.compiler_for(src)
        if release in cc.LINUX_COMPANION and cc.linux_cc1plus(release) is None:
            missing.setdefault(release, []).append(src)
    for release, srcs in missing.items():
        print("note: no Linux %s (docs/TOOLCHAIN.md): %s stay assembly"
              % (release, ", ".join(str(s.relative_to(ROOT)) for s in srcs)))
    skipped = {s for srcs in missing.values() for s in srcs}

    with ThreadPoolExecutor(jobs) as pool:
        for src, obj in pool.map(one, [s for s in sources() if s not in skipped]):
            out[src] = obj
    return out


FRAME_SYMBOLS = ("__FRAME_BEGIN__", "_GLOBAL_$F$")


def drop_frame_tables(path):
    """Remove an object's .data when it holds only the compiler's frame (unwind) tables, which a
    file built with exceptions on carries and no code refers to: retail's own tables are in the
    .data that comes from the disassembly. Returns True if it removed them."""
    obj = elf.Elf(Path(path).read_bytes())
    data = obj.section(".data")
    if data is None or not data["size"]:
        return False
    inside = [s for s in obj.symbols if s["shndx"] == data["index"]]
    names = [s["name"] for s in inside if s["name"]]
    if not names or not all(n.startswith(FRAME_SYMBOLS) for n in names):
        return False
    for sec in obj.sections:
        if sec["name"].startswith(".text") and sec["size"]:
            if any(sym["shndx"] == data["index"] for _, _, sym in obj.relocations(sec["name"])):
                return False
    tmp = Path(str(path) + ".frames")
    tmp.write_bytes(obj.data)
    cmd = [rodata._objcopy(), "--remove-section=.data", "--remove-section=.rel.data", str(tmp), str(path)]
    proc = subprocess.run(cmd, capture_output=True, text=True)
    tmp.unlink()
    if proc.returncode:
        raise LayoutError("objcopy: " + (proc.stderr or proc.stdout).strip())
    return True


def placements(objects):
    """[(address, size, object, section, symbol)] of every C function, the aliases the link needs,
    and the same list of every global a C file defines (.data.D_XXXXXXXX, -fdata-sections)."""
    resolver = check.Resolver("us")
    functions = check.load_functions("us")
    starts = {a: n for n, (a, s, k) in functions.items()}
    placed, aliases, defined, data = [], {}, set(), []
    libcalls = check.load_libcalls("us")  # named by address in the script: no alias for them
    for src, path in objects.items():
        obj = elf.Elf(path.read_bytes())
        rel = path.relative_to(ROOT)
        w = WHOLE.get(str(src.relative_to(ROOT)))
        if w is not None:
            p, d = whole_placements(obj, w, rel, src, resolver, starts)
            for f in p:
                if f[0] in {q[0] for q in placed}:
                    raise LayoutError("two definitions of the function at 0x%X (%s)" % (f[0], f[4]))
                if starts[f[0]] != f[4]:
                    aliases[starts[f[0]]] = f[4]
                defined.add(f[4])
            placed += p
            data += d
        for sec in obj.sections if w is None else []:
            if sec["name"].startswith(DATA_SECTIONS) and sec["size"]:
                if sec["name"] == ".bss":
                    data.append(bss_placement(obj, sec, rel, src))
                    continue
                m = DATA_NAME.match(sec["name"])
                if m:
                    addr = int(m.group(1)[2:], 16)
                    if sec["align"] > 1 and addr % sec["align"]:
                        raise LayoutError("%s: %s is aligned to %d, which its address is not: retail's "
                                          "global is not that type" % (src.relative_to(ROOT), m.group(1), sec["align"]))
                    if addr in {d[0] for d in data}:
                        raise LayoutError("two definitions of the global %s" % m.group(1))
                    data.append((addr, sec["size"], rel, sec["name"], m.group(1)))
                    continue
                raise LayoutError("%s has %s data (%d bytes): a global defined in C is named "
                                  "D_XXXXXXXX, at its retail address, and lives in .data (AGENTS.md). "
                                  "A constant retail loads from .rodata is read through an extern "
                                  "(extern f32 D_00219718[];), not written as a literal"
                                  % (src.relative_to(ROOT), sec["name"], sec["size"]))
        for sym in obj.symbols if w is None else []:
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
            if sym["shndx"] == elf.SHN_UNDEF and sym["name"] and sym["name"] not in libcalls:
                base = check.base_name(sym["name"])
                if base != sym["name"]:
                    aliases.setdefault(sym["name"], base)  # C calls func_X__Fi; the disassembly defines func_X
    # A name both defined in C and aliased to its base would loop: keep the C definition.
    for name in defined:
        if aliases.get(name) and aliases[name] not in defined:
            aliases.pop(name)
    placed.sort()
    data.sort()
    for a, b in zip(data, data[1:]):
        if a[0] == b[0]:
            raise LayoutError("two definitions of the global at 0x%X (%s, %s)" % (a[0], a[4], b[4]))
    return placed, aliases, data


def whole_placements(obj, w, rel, src, resolver, starts):
    """The functions and data of a whole file (config/us/files.tsv): its .text at its start, each
    function where retail has it (source order is retail's order), and its .rodata, .data and .bss
    each in one piece at their addresses. A function after the first has no section of its own to
    place (section "")."""
    name = src.relative_to(ROOT)
    placed, data = [], []
    for sec in obj.sections:
        kind = sec["name"][1:]
        if sec["name"] in (".text", ".rodata", ".data", ".bss") and sec["size"] and w.get(kind) is None:
            raise LayoutError("%s has %s (%d bytes), which config/us/files.tsv gives no address"
                              % (name, sec["name"], sec["size"]))
    text = obj.section(".text")
    funcs = sorted((s["value"], s["name"], s["size"]) for s in obj.symbols
                   if s["type"] == elf.STT_FUNC and text is not None and s["shndx"] == text["index"])
    for i, (off, fname, size) in enumerate(funcs):
        addr = w["text"] + off
        if resolver.us_address(fname) != addr or addr not in starts:
            raise LayoutError("%s: %s lands at 0x%X, where retail has %s: a whole file defines its "
                              "functions in retail's order" % (name, fname, addr, starts.get(addr, "no function")))
        placed.append((addr, size, rel, ".text" if i == 0 else "", fname))
    if text is not None and text["size"] and w["text"] + text["size"] > w["end"]:
        raise LayoutError("%s: its .text ends at 0x%X, past 0x%X" % (name, w["text"] + text["size"], w["end"]))
    for kind in ("rodata", "data", "bss"):
        sec = obj.section("." + kind)
        if sec is not None and sec["size"]:
            data.append((w[kind], sec["size"], rel, "." + kind, "D_%08X" % w[kind]))
    return placed, data


def bss_placement(obj, sec, rel, src):
    """A C file's .bss (its static variables, which -fdata-sections leaves in one section) as one
    placement: each variable is named D_XXXXXXXX and sits at its address's offset from the first."""
    inside = sorted((s["value"], s["name"]) for s in obj.symbols if s["shndx"] == sec["index"] and s["name"])
    if not inside or any(not ADDR_LABEL.match(n) for _, n in inside):
        raise LayoutError("%s has .bss variables not named D_XXXXXXXX (%s)"
                          % (src.relative_to(ROOT), ", ".join(n for _, n in inside) or "unnamed"))
    base = int(inside[0][1][2:], 16) - inside[0][0]
    for off, n in inside:
        if int(n[2:], 16) != base + off:
            raise LayoutError("%s: %s is at .bss+0x%X, not at its address's place from %s"
                              % (src.relative_to(ROOT), n, off, inside[0][1]))
    return (base, sec["size"], rel, ".bss", inside[0][1])


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


def split_data(key, kind="data"):
    """The header lines of asm/<key>/data/<kind>.<kind>.s and [(label, address, its lines)] in order."""
    lines = (ROOT / "asm" / key / "data" / ("%s.%s.s" % (kind, kind))).read_text().splitlines()
    starts = [i for i, l in enumerate(lines) if l.startswith("nonmatching ")]
    if not starts:
        raise LayoutError("asm/%s/data/%s.%s.s has no labels" % (key, kind, kind))
    header = lines[:starts[0]]
    chunks = []
    for n, i in enumerate(starts):
        name = lines[i].split()[1].rstrip(",")  # D_XXXXXXXX, or a jump table's jtbl_XXXXXXXX
        chunks.append([name, int(name.rsplit("_", 1)[1], 16), lines[i:starts[n + 1] if n + 1 < len(starts) else len(lines)]])
    # An .align between two labels aligns the next one: it goes with it.
    for prev, nxt in zip(chunks, chunks[1:]):
        body = prev[2]
        while body and (not body[-1].strip() or ALIGN.match(body[-1])):
            line = body.pop()
            if line.strip():
                nxt[2].insert(0, line)
    return header, [tuple(c) for c in chunks]


def aligned(lines):
    """True if a chunk starts with an .align: its run starts with it, placed at its address."""
    return bool(lines) and bool(ALIGN.match(lines[0]))


def data_plan(chunks, data_placed):
    """The order of .data: [("run", [(label, address, lines)]) or ("c", placement)], and the labels
    a C global covers. A global starts at a label and ends where a later one starts."""
    at = {d[0]: d for d in data_placed}
    missing = sorted(set(at) - {a for _, a, _ in chunks})
    if missing:
        raise LayoutError("no label of .data starts at 0x%X, where a C global is defined" % missing[0])
    plan, covered, end = [], {}, 0
    for i, (name, addr, lines) in enumerate(chunks):
        if addr < end:
            covered[name] = addr  # inside a C global: its label stays defined at its address
            continue
        d = at.get(addr)
        if d:
            covered[name] = addr  # defined by C unless the C variable is a static
            end = addr + d[1]
            later = [a for _, a, _ in chunks[i + 1:] if a >= end]
            # A section can end in the padding before the next object's (zeros): a whole file's,
            # or a global's ending on a word when the next label is 8-aligned, as GCC aligns an
            # aggregate of 8 bytes or more.
            gap = later[0] - end if later else 8
            if gap >= 8 or (gap and d[3].count(".") > 1 and (end % 4 or later[0] % 8)):
                raise LayoutError("%s (%d bytes) does not end where a label of .data starts"
                                  % (d[4], d[1]))
            end = later[0]
            plan.append(("c", d))
        elif plan and plan[-1][0] == "run" and not aligned(lines):
            plan[-1][1].append((name, addr, lines))
        else:
            plan.append(("run", [(name, addr, lines)]))
    return plan, covered


def data_entries(data_placed, main_start, kind="data"):
    """The linker-script lines for .data (or .bss) with the C globals placed, the run sources, and
    the labels a C global covers (PROVIDEd at their addresses). main_start: the output section's."""
    header, chunks = split_data("us", kind)
    plan, covered = data_plan(chunks, data_placed)
    data_dir = ROOT / "build" / "us" / kind
    entries, runs = [], []
    for what, item in plan:
        if what == "c":
            entries.append("        . = 0x%X;" % (item[0] - main_start))
            entries.append("        %s(%s);" % (item[2], item[3]))
            continue
        start = item[0][1]
        path = data_dir / ("run_%08X.s" % start)
        first = list(item[0][2])
        while first and ALIGN.match(first[0]):
            first.pop(0)  # its own alignment: the run is placed at its address already
        body = first + [l for _, _, ls in item[1:] for l in ls]
        write_if_changed(path, "\n".join(header + body) + "\n")
        runs.append(path)
        entries.append("        . = 0x%X;" % (start - main_start))
        entries.append("        %s(.%s);" % (path.relative_to(ROOT).with_suffix(".s.o"), kind))
    for stale in data_dir.glob("run_*.s"):
        if stale not in runs:
            stale.unlink()
    return entries, runs, covered


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
    placed, aliases, data_placed = placements(objects)
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
            if not p[3]:
                continue  # inside a whole file's .text, placed with its first function
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
    for kind in ("rodata", "data", "bss"):
        mine = [d for d in data_placed if d[3].split(".")[1] == kind]
        if not mine:
            continue
        # .main starts with .rodata, then .data; .main_bss with the first label of .bss.
        start = (next(r[2] for r in todo.layout("us") if r[1] == "rodata") if kind != "bss"
                 else split_data("us", "bss")[1][0][1])
        data_lines, data_runs, covered = data_entries(mine, start, kind)
        dmarker = re.compile(r"^\s*build/us/asm/us/data/%s\.%s\.s\.o\(\.%s\);$" % (kind, kind, kind), re.M)
        if not dmarker.search(text):
            raise LayoutError("%s has no %s.%s.s object to replace" % (ld_script.relative_to(ROOT), kind, kind))
        text = dmarker.sub(lambda m: "\n".join(data_lines), text)
        runs += data_runs
        text += "\n" + "\n".join("PROVIDE(%s = 0x%X);" % (n, a) for n, a in sorted(covered.items())) + "\n"
    labels = case_labels(placed)
    if labels:
        text += "\n" + "\n".join("PROVIDE(%s = 0x%X);" % (n, a) for n, a in sorted(labels.items())) + "\n"
    if aliases:
        text += "\n" + "\n".join("PROVIDE(%s = %s);" % (a, b) for a, b in sorted(aliases.items())) + "\n"
    libcalls = check.load_libcalls("us")
    if libcalls:
        text += "\n" + "\n".join("PROVIDE(%s = 0x%X);" % (n, a) for n, a in sorted(libcalls.items())) + "\n"
    # A global C names by its address that the disassembly has no label for (an address inside
    # another label): defined at that address, unless something else defines it.
    named = address_names(objects)
    if named:
        text += "\n" + "\n".join("PROVIDE(%s = 0x%X);" % (n, a) for n, a in sorted(named.items())) + "\n"
    out = ld_script.with_name(ld_script.name.replace(".splat.ld", ".ld"))
    write_if_changed(out, text)
    return out, runs, placed, data_placed


def address_names(objects):
    """{D_XXXXXXXX: address} of every global the C objects refer to by its address name."""
    out = {}
    for path in objects.values():
        for sym in elf.Elf(path.read_bytes()).symbols:
            if sym["shndx"] == elf.SHN_UNDEF and ADDR_LABEL.match(sym["name"]):
                out[sym["name"]] = int(sym["name"][2:], 16)
    return out
