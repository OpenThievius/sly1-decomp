# SPDX-License-Identifier: AGPL-3.0-or-later
"""The US functions still to match, with what each one needs.

    python3 tools/todo.py [--max-size N] [--min-size N] [--tags leaf,calls] [--exclude vu,jtbl] [--window 00118000]

One row per unfinished function: name, address, size, its source file (the
16 KiB window that holds it, in src/main/ for game code and src/lib/ for the
libraries, config/us/layout.tsv) and tags read from its disassembly:

- leaf: makes no calls;  calls: makes calls (jal)
- data: refers to data by address (%hi/%lo);  rodata: refers into .rodata (literals,
  tables: it cannot be linked from C until its file's .rodata is modelled)
- jtbl: has a jump table;  vu: uses the vector unit (VU0 macro mode, COP2)
- float: uses the FPU;  mmi: uses 128-bit multimedia instructions
- system: kernel or cache instructions (syscall, mfc0, cache, sync, eret)
- handwritten: spimdisasm says it was not made by the compiler

A function is finished when src/ defines it (tools/progress.py reads the same
list). Needs asm/us/ (tools/setup_asm.py).
"""

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
WINDOW = 0x4000
RODATA = (0x217380, 0x250580)          # US .rodata (docs/VERSIONS.md)
DEFINITION = re.compile(r"^(?!\s)(?!.*;\s*$)(?!(?:struct|union|class|enum|typedef)\b)[A-Za-z_][\w \t\*&:<>,]*?\b(\w+)\s*\((?:[^;\n]*$|[^;\n]*\)\s*\{.*$)", re.M)
VU = re.compile(r"^(v[a-z]|lqc2|sqc2|qmtc2|qmfc2|ctc2|cfc2|vcallms)")
SYSTEM = {"syscall", "mfc0", "mtc0", "cache", "sync", "sync.l", "sync.p", "eret", "ei", "di", "break"}
MMI = re.compile(r"^(p[a-z]|qfsrv|mfhi1|mflo1|mthi1|mtlo1|mult1|multu1|div1|divu1|madd1|maddu1|mfsa|mtsa)")


def window_of(addr):
    return addr & ~(WINDOW - 1)


def layout(key="us"):
    """config/<key>/layout.tsv: [(kind, name, start, end, category, source folder)]."""
    rows = []
    for line in (ROOT / "config" / key / "layout.tsv").read_text().splitlines():
        if not line or line.startswith(("#", "kind\t")):
            continue
        kind, name, start, end, category, source = line.split("\t")
        rows.append((kind, name, int(start, 16), int(end, 16), category, source))
    return rows


def code_range_of(addr, key="us"):
    """The layout row of the code range that holds an address (game code or libraries)."""
    for row in layout(key):
        if row[0] == "code" and row[2] <= addr < row[3]:
            return row
    raise KeyError("0x%X is in no code range of config/%s/layout.tsv" % (addr, key))


def source_of(addr):
    """The source file that holds a US function: its code range's folder, its 16 KiB window."""
    return "%s/%08X.cpp" % (code_range_of(addr)[5], window_of(addr))


def finished():
    """Names of the US functions src/ defines (by their address name or symbol_addrs name)."""
    names = set()
    for path in sorted((ROOT / "src").rglob("*.cpp")) if (ROOT / "src").exists() else []:
        for m in DEFINITION.finditer(path.read_text()):
            names.add(m.group(1))
    return names


def functions():
    rows = []
    for line in (ROOT / "config" / "us" / "functions.tsv").read_text().splitlines()[1:]:
        name, addr, size, kind, _ = line.split("\t")
        rows.append((name, int(addr, 16), int(size), kind))
    return rows


def bodies():
    out, current = {}, None
    for line in (ROOT / "asm" / "us" / "text.s").read_text().splitlines():
        if line.startswith("nonmatching "):
            current = line.split()[1].rstrip(",")
            out[current] = []
        elif current and line.lstrip().startswith(("/*", "jlabel", ".L")):
            out[current].append(line.split("*/", 1)[-1].strip())
    return out


def tags_of(lines, kind):
    tags = set()
    if kind == "handwritten":
        tags.add("handwritten")
    for line in lines:
        if line.startswith("jlabel"):
            tags.add("jtbl")
        parts = line.split(None, 1)
        if not parts:
            continue
        op, rest = parts[0], parts[1] if len(parts) > 1 else ""
        if op == "jal":
            tags.add("calls")
        if "%hi(" in rest or "%lo(" in rest:
            tags.add("data")
            for a in re.findall(r"\b(?:D|jtbl)_([0-9A-F]{8})", rest):
                if RODATA[0] <= int(a, 16) < RODATA[1]:
                    tags.add("rodata")
        if "jtbl_" in rest:
            tags.add("jtbl")
        if VU.match(op):
            tags.add("vu")
        if op in SYSTEM:
            tags.add("system")
        if op.endswith((".s", ".w")) or op in ("lwc1", "swc1", "mtc1", "mfc1"):
            tags.add("float")
        if MMI.match(op) and op != "pref":
            tags.add("mmi")
    if "calls" not in tags:
        tags.add("leaf")
    return tags


def todo():
    done = finished()
    body = bodies()
    out = []
    for name, addr, size, kind in functions():
        if name in done:
            continue
        out.append((name, addr, size, source_of(addr), sorted(tags_of(body.get(name, []), kind))))
    return out


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--min-size", type=int, default=0)
    parser.add_argument("--max-size", type=int, default=1 << 30)
    parser.add_argument("--tags", default="", help="only functions with all of these tags")
    parser.add_argument("--exclude", default="", help="leave out functions with any of these tags")
    parser.add_argument("--window", help="only the functions of one source file, e.g. 00118000")
    args = parser.parse_args(argv)
    want = {t for t in args.tags.split(",") if t}
    avoid = {t for t in args.exclude.split(",") if t}
    rows = [r for r in todo() if args.min_size <= r[2] <= args.max_size and want <= set(r[4])
            and not avoid & set(r[4]) and (not args.window or r[3].endswith(args.window + ".cpp"))]
    print("name\taddress\tsize\tsource\ttags")
    for name, addr, size, src, tags in rows:
        print("%s\t%08X\t%d\t%s\t%s" % (name, addr, size, src, ",".join(tags)))
    print("# %d functions, %d bytes" % (len(rows), sum(r[2] for r in rows)), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
