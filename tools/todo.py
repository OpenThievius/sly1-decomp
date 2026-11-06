# SPDX-License-Identifier: AGPL-3.0-or-later
"""The US functions still to match, with what each one needs.

    python3 tools/todo.py [--max-size N] [--min-size N] [--tags leaf,calls] [--exclude vu,jtbl] [--window 00118000]
    python3 tools/todo.py --untried --summary

One row per unfinished function: name, address, size, its source file (the
16 KiB window that holds it, in src/main/ for game code and src/lib/ for the
libraries, config/us/layout.tsv) and tags read from its disassembly:

- leaf: makes no calls;  calls: makes calls (jal)
- data: refers to data by address (%hi/%lo);  rodata: refers into .rodata (literals, tables;
  a literal links through tools/rodata.py, a jump table does not yet)
- jtbl: has a jump table;  vu: uses the vector unit (VU0 macro mode, COP2)
- float: uses the FPU;  mmi: uses 128-bit multimedia instructions
- nonc: max.s, min.s
- system: kernel or cache instructions (syscall, mfc0, cache, sync, eret)
- handwritten: spimdisasm says it was not made by the compiler
- fragment: no `jr $ra` in its listing, or a positive stack adjustment first: not a whole function.
  Most are the linker's leftovers of stripped functions (an `addiu $sp` or a store, then a nop),
  which tools/classify_asm.py counts as remnants. A listing that ends in a tail jump to another
  function (Sony's 2.9-ee writes them), a branch back into itself or a call that never returns
  is a whole function, not a fragment; so is a function behind leftovers, once
  config/us/symbol_addrs.txt names its start (code takes its address as func_X + N). On the US
  build only func_00100000 is left: the nop at the start of the code.

What stops a function from being matched, the blocker column:

- asm: original assembly, tracked in config/us/original_asm.tsv (tools/classify_asm.py): the
  function holds an instruction the compiler cannot emit, or is a run of words the linker
  left of a stripped function. It is not C waiting to be matched, and tools/progress.py
  counts it as finished, apart from the exact C matches.

- fragment: no `jr $ra` in its listing, or a positive stack adjustment first: residue the
  assembler left after a return; no C function can produce it. A listing that ends in a tail
  jump to another function (Sony's 2.9-ee writes them), a branch back into itself or a call
  that never returns is a whole function, not a fragment
- mmi: 128-bit multimedia instructions (pextlw, pcpyld, ...): not plain C. por and pref are not
  counted: the compiler emits them (COMPILER_EMITS)
- nonc: max.s, min.s: no plain C form with the files' flags. A bare sqrt.s is not one: it is
  written with include/fpu.h's Fpu::Sqrt (AGENTS.md); `break 0, 7` after a division is the
  compiler's divide-by-zero trap, plain C, not system code
- vu, system, handwritten: permanent for C: VU microcode, kernel instructions and
  hand-written library assembly (AGENTS.md: no inline asm)
- jtbl: a jump table; write the switch in C (the table stays retail's, tools/rodata.py)
- rodata: refers to named .rodata. C reads the constant through an extern
  (extern u8 D_00219718[];), so the object keeps no .rodata of its own
- compiler: saves registers with 8-byte sd in its prologue: Sony's library code, built with
  Sony's 2.9-ee-991111, which config/cflags.tsv names for every src/lib file (docs/TOOLCHAIN.md).
  Not a blocker: write it in its src/lib file as any other
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
DEFINITION = re.compile(r"^(?!\s)(?!.*;\s*$)(?!(?:struct|union|class|enum|typedef)\b(?![^\n]*\bfunc_))[A-Za-z_][\w \t\*&:<>,]*?\b(\w+)\s*\((?:[^;\n]*$|[^;\n]*\)\s*\{.*$)", re.M)


def definitions(text):
    """The DEFINITION matches of `text` that open a body: a signature that runs over several
    lines is a definition only if a `{` comes before any `;` (else it is a declaration)."""
    for m in DEFINITION.finditer(text):
        brace, semi = text.find("{", m.start()), text.find(";", m.start())
        # A class's own constructor or method (`Node::Node()`) is named by the compiler: a whole
        # file's takes retail's name from config/us/generated.tsv.
        member = text[:m.start(1)].endswith("::") and not m.group(1).startswith("func_")
        # A C file's static inline helper (src/lib/divide.c) is compiled into its callers only.
        helper = m.group(0).startswith("static inline ") and not m.group(1).startswith("func_")
        if brace >= 0 and (semi < 0 or brace < semi) and not member and not helper:
            yield m


PROLOGUE = 12  # instructions from the top of a listing that a register save may be in
SAVE64 = re.compile(r"^sd\s+\$(ra|s\d|fp)\b")
VU = re.compile(r"^(v[a-z]|lqc2|sqc2|qmtc2|qmfc2|ctc2|cfc2|vcallms)")
SYSTEM = {"syscall", "mfc0", "mtc0", "cache", "sync", "sync.l", "sync.p", "eret", "ei", "di", "break"}
DIVIDE_TRAP = "0, 7"  # `break 0, 7` after a division: the compiler's divide-by-zero trap, plain C
# No plain C form with the files' flags. (A bare sqrt.s is written with include/fpu.h's Fpu::Sqrt:
# __builtin_sqrtf adds a NaN check and a call to sqrtf that retail never has.)
NONC = {"max.s", "min.s"}
MMI = re.compile(r"^(p[a-z]|qfsrv|mfhi1|mflo1|mthi1|mtlo1|mult1|multu1|div1|divu1|madd1|maddu1|mfsa|mtsa)")
# Multimedia instructions the compiler is known to emit: six functions that contain one are
# matched in C (por is the 128-bit |, which also moves a 128-bit value between registers), so
# seeing it proves nothing. Add an instruction here only with such a function; a function in
# config/us/original_asm.tsv that src/ defines is an error (tests/test_tools.py).
COMPILER_EMITS = {"por", "pref"}


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


def whole_files():
    """{source path: {"text", "end", "rodata", "data", "bss": address or None}} of the files
    config/us/files.tsv lists: real source files, compiled and linked whole as the original's
    were (tools/c_layout.py), in place of their 16 KiB windows."""
    path = ROOT / "config" / "us" / "files.tsv"
    if not path.exists():
        return {}
    out = {}
    for line in path.read_text().splitlines()[1:]:
        if not line.strip():
            continue
        f, *cols = line.split("\t")
        out[f] = dict(zip(("text", "end", "rodata", "data", "bss"),
                          (None if c in ("-", "") else int(c, 16) for c in cols)))
    return out


def source_of(addr):
    """The source file that holds a US function: a whole file of config/us/files.tsv, or else
    its code range's folder, its 16 KiB window."""
    for f, w in whole_files().items():
        if w["text"] <= addr < w["end"]:
            return f
    return "%s/%08X.cpp" % (code_range_of(addr)[5], window_of(addr))


def generated():
    """{function name: source file} of the functions the compiler makes for a file, which
    config/us/generated.tsv names (tools/compile.py gives them those names)."""
    path = ROOT / "config" / "us" / "generated.tsv"
    if not path.exists():
        return {}
    rows = [l.split("\t") for l in path.read_text().splitlines()[1:] if l]
    return {func: ROOT / f for f, _sym, func in rows if (ROOT / f).exists()}


def finished():
    """Names of the US functions src/ defines (by their address name or symbol_addrs name), and
    those the compiler makes for a file of src/."""
    names = set(generated())
    for path in versions.sources():
        for m in definitions(path.read_text()):
            names.add(m.group(1))
    return names


def classified():
    """{name: kind} of the functions config/us/original_asm.tsv lists as original assembly."""
    path = ROOT / "config" / "us" / "original_asm.tsv"
    if not path.exists():
        return {}
    rows = {}
    for line in path.read_text().splitlines()[1:]:
        name, _addr, _size, kind, _why = line.split("\t")
        rows[name] = kind
    return rows


def functions(key="us"):
    rows = []
    for line in (ROOT / "config" / key / "functions.tsv").read_text().splitlines()[1:]:
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


def bodies(key="us"):
    out, current = {}, None
    for line in (ROOT / "asm" / key / "text.s").read_text().splitlines():
        if line.startswith("nonmatching "):
            current = line.split()[1].rstrip(",")
            out[current] = []
        elif current and line.lstrip().startswith(("/*", "jlabel", ".L")):
            out[current].append(decoded(line))
    return out


def ends_whole(lines):
    """True when a listing without a `jr` still ends as a whole function: its last instruction
    before the delay slot is a tail jump to another function (Sony's 2.9-ee writes them), a
    branch back into itself (it never returns) or a call to a function that never returns."""
    ins = [line.split() for line in lines if line.split() and not line.startswith(("jlabel", ".L"))]
    while ins and ins[-1][0] == "nop":
        ins.pop()  # alignment padding, or a delay slot that holds nothing
    if not ins:
        return False
    last = ins[-1] if ins[-1][0] in ("j", "b", "jal") else ins[-2] if len(ins) > 1 else ins[-1]
    op, target = last[0], last[-1]
    return (op == "j" and target.startswith("func_")) or (op in ("b", "j") and target.startswith(".L")) \
        or op == "jal"


def tags_of(lines, kind):
    tags = set()
    if kind == "handwritten":
        tags.add("handwritten")
    if lines and not any(line.split(None, 1)[:1] == ["jr"] for line in lines) and not ends_whole(lines):
        tags.add("fragment")
    first = next((line.split() for line in lines if line.split()), [])
    if len(first) >= 4 and first[:3] == ["addiu", "$sp,", "$sp,"] and not first[3].startswith("-"):
        tags.add("fragment")  # a positive stack adjustment first: the end of the function before
    if any(SAVE64.match(line) for line in lines[:PROLOGUE]):
        tags.add("compiler")
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
        if op in SYSTEM and not (op == "break" and rest.strip() == DIVIDE_TRAP):
            tags.add("system")
        if op.endswith((".s", ".w")) or op in ("lwc1", "swc1", "mtc1", "mfc1"):
            tags.add("float")
        if op in NONC:
            tags.add("nonc")
        if MMI.match(op) and op not in COMPILER_EMITS:
            tags.add("mmi")
    if "calls" not in tags:
        tags.add("leaf")
    return tags


PERMANENT = ("asm", "fragment", "vu", "system", "handwritten", "mmi", "nonc")


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
    asm = classified()
    out = []
    for name, addr, size, kind in functions():
        if name in done:
            continue
        tags = tags_of(body.get(name, []), kind)
        if name in asm:
            tags.add("asm")
        out.append((name, addr, size, source_of(addr), sorted(tags)))
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
        for key in ("none", "rodata", "jtbl", "asm", "fragment", "vu", "system", "handwritten", "mmi", "nonc"):
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
