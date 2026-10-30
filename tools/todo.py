# SPDX-License-Identifier: AGPL-3.0-or-later
"""The US functions still to match, with what each one needs.

    python3 tools/todo.py [--max-size N] [--min-size N] [--tags leaf,calls] [--exclude vu,jtbl] [--window 00118000]
    python3 tools/todo.py --untried --summary

One row per unfinished function: name, address, size, its source file (the
16 KiB window that holds it, in src/main/ for game code and src/lib/ for the
libraries, config/us/layout.tsv) and tags read from its disassembly:

- leaf: makes no calls;  calls: makes calls (jal)
- data: refers to data by address (%hi/%lo);  rodata: refers into .rodata (literals,
  tables: it cannot be linked from C until its file's .rodata is modelled)
- jtbl: has a jump table;  vu: uses the vector unit (VU0 macro mode, COP2)
- float: uses the FPU;  mmi: uses 128-bit multimedia instructions
- nonc: max.s, min.s, sqrt.s
- system: kernel or cache instructions (syscall, mfc0, cache, sync, eret)
- handwritten: spimdisasm says it was not made by the compiler
- fragment: no `jr $ra` in its listing, or a positive stack adjustment first: not a whole function

What stops a function from being matched, the blocker column:

- fragment: no `jr $ra` in its listing, or a positive stack adjustment first (the end of the
  function before): a piece of a function, or a tail call, not a whole function
- mmi: 128-bit multimedia instructions (pextlw, pcpyld, ...): not plain C
- nonc: max.s, min.s, sqrt.s: no plain C form in this compiler
- vu, system, handwritten: permanent for C: VU microcode, kernel instructions and
  hand-written library assembly (AGENTS.md: no inline asm)
- jtbl: a jump table; its .rodata must be placed from C first
- rodata: refers to named .rodata. C reads the constant through an extern
  (extern u8 D_00219718[];), so the object keeps no .rodata of its own
- none: nothing blocks it

A function is finished when src/ defines it (tools/progress.py reads the same
list). --untried leaves out the functions a worker already attempted
(build/swarm/*/func_*.cpp). Needs asm/us/ (tools/setup_asm.py).
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
NONC = {"max.s", "min.s", "sqrt.s"}  # no plain C form in this compiler
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


COP1_SQRT_S = 0x46000004  # sqrt.s: COP1, fmt S (0x10), funct 4; the register fields vary


def decoded(line):
    """A listing line's text, with a raw COP1 sqrt.s word (listed as c1) given its mnemonic."""
    text = line.split("*/", 1)[-1].strip()
    match = re.search(r"/\*\s*\S+\s+\S+\s+([0-9A-Fa-f]{8})\s*\*/", line)
    if match and text.split()[:1] == ["c1"]:
        word = int.from_bytes(bytes.fromhex(match.group(1))[::-1], "big")
        if word & 0xFFE0003F == COP1_SQRT_S:
            return "sqrt.s" + text[len("c1"):]
    return text


def bodies():
    out, current = {}, None
    for line in (ROOT / "asm" / "us" / "text.s").read_text().splitlines():
        if line.startswith("nonmatching "):
            current = line.split()[1].rstrip(",")
            out[current] = []
        elif current and line.lstrip().startswith(("/*", "jlabel", ".L")):
            out[current].append(decoded(line))
    return out


def tags_of(lines, kind):
    tags = set()
    if kind == "handwritten":
        tags.add("handwritten")
    if lines and not any(line.split(None, 1)[:1] == ["jr"] for line in lines):
        tags.add("fragment")
    first = next((line.split() for line in lines if line.split()), [])
    if len(first) >= 4 and first[:3] == ["addiu", "$sp,", "$sp,"] and not first[3].startswith("-"):
        tags.add("fragment")  # a positive stack adjustment first: the end of the function before
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
        if op in NONC:
            tags.add("nonc")
        if MMI.match(op) and op != "pref":
            tags.add("mmi")
    if "calls" not in tags:
        tags.add("leaf")
    return tags


PERMANENT = ("fragment", "vu", "system", "handwritten", "mmi", "nonc")


def blocker(tags):
    """The first thing that stops a function from being matched (see the module doc)."""
    for tag in PERMANENT + ("jtbl", "rodata"):
        if tag in tags:
            return tag
    return "none"


def attempted():
    """Names of the functions a worker has already tried (a file in build/swarm/<worker>/)."""
    swarm = ROOT / "build" / "swarm"
    return {p.stem for p in swarm.glob("*/func_*.cpp")} if swarm.exists() else set()


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
    parser.add_argument("--untried", action="store_true", help="leave out the functions a worker already attempted")
    parser.add_argument("--summary", action="store_true", help="count the functions by blocker, instead of listing them")
    args = parser.parse_args(argv)
    want = {t for t in args.tags.split(",") if t}
    avoid = {t for t in args.exclude.split(",") if t}
    done = attempted() if args.untried else set()
    rows = [r for r in todo() if args.min_size <= r[2] <= args.max_size and want <= set(r[4])
            and not avoid & set(r[4]) and (not args.window or r[3].endswith(args.window + ".cpp"))
            and r[0] not in done]
    if args.summary:
        counts = {}
        for name, addr, size, src, tags in rows:
            key = blocker(tags)
            n, total = counts.get(key, (0, 0))
            counts[key] = (n + 1, total + size)
        print("blocker\tfunctions\tbytes")
        for key in ("none", "rodata", "jtbl", "fragment", "vu", "system", "handwritten", "mmi", "nonc"):
            if key in counts:
                print("%s\t%d\t%d" % (key, counts[key][0], counts[key][1]))
        return 0
    print("name\taddress\tsize\tsource\ttags\tblocker")
    for name, addr, size, src, tags in rows:
        print("%s\t%08X\t%d\t%s\t%s\t%s" % (name, addr, size, src, ",".join(tags), blocker(tags)))
    print("# %d functions, %d bytes" % (len(rows), sum(r[2] for r in rows)), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
