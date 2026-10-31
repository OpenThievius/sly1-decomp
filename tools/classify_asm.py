# SPDX-License-Identifier: AGPL-3.0-or-later
"""Which functions of game code are original assembly, not C waiting to be matched.

    python3 tools/classify_asm.py           # writes config/us/original_asm.tsv
    python3 tools/classify_asm.py --check   # fails when the table is out of date

Some retail code was written as assembly, and some words are what the linker left of a
function it stripped. Matching those bytes by compiling C would misrepresent where they
come from. This follows OpenRAC's classification (rac1-decomp, docs/ASM_CLASSIFICATION.md,
credited in THIRD_PARTY_NOTICES.md): the rules below are ours, from the evidence in the
bytes, and the table they write is committed so that CI needs no disc.

Two kinds, game code only (config/us/layout.tsv): Sony's libraries are matched in C with
Sony's own compiler instead (docs/TOOLCHAIN.md), so they are not classified here.

- handwritten: the function holds an instruction the compiler cannot emit, so it was not
  made from C. A VU0 macro-mode instruction (COP2), a 128-bit multimedia instruction
  (MMI) that no function matched in C contains (COMPILER_EMITS), or the disassembler's own
  "handwritten" mark.
- remnant: a run of words the linker left of a stripped function. It starts on an
  8-byte boundary, has no jump or branch in it, nothing refers to it (no instruction
  or data names it), and the code before it is finished: going back over earlier
  remnants, a `jr` and its delay slot, a tail `j`, or the start of the code.

What these rules do not classify (kernel and cache instructions, max.s/min.s/sqrt.s,
fragments that contain a jump) stays unmatched and is listed by tools/todo.py with its
blocker, for a person to look at.

The table needs asm/us/ (tools/setup_asm.py) only to be written or checked.
"""

import argparse
import glob
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import todo  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
TABLE = ROOT / "config" / "us" / "original_asm.tsv"
HEADER = "name\taddress\tsize\tkind\twhy"
BRANCH = re.compile(r"^(j|jal|jr|jalr|b|bal|beq|bne|beqz|bnez|bgez|bgtz|blez|bltz|bgezal|bltzal|beql|bnel|"
                    r"beqzl|bnezl|bgezl|bgtzl|blezl|bltzl|bc[0-3][tf]l?)$")
OWN_LINES = ("nonmatching", "glabel", "endlabel", "dlabel", "enddlabel")
# Multimedia instructions the compiler is known to emit: six functions that contain one are
# matched in C (por is the 128-bit |), so seeing it proves nothing. Add an instruction here only
# with such a function; a function in the table that src/ defines is an error (tests/test_tools.py).
COMPILER_EMITS = {"por", "pref"}


def ops_of(lines):
    """The mnemonics of a listing, without its labels."""
    out = []
    for line in lines:
        if line.startswith(("jlabel", ".L")):
            continue
        parts = line.split()
        if parts:
            out.append(parts[0])
    return out


def ends_finished(ops):
    """True when a listing ends in a return or a tail jump, whose delay slot may be followed by padding."""
    for i in range(len(ops) - 1, -1, -1):
        if ops[i] in ("jr", "j"):
            return all(o == "nop" for o in ops[i + 2:])
        if ops[i] != "nop":
            # a real instruction after the last jump is not a delay slot with padding behind it
            return i >= 1 and ops[i - 1] in ("jr", "j")
    return False


def handwritten(ops, kind):
    """Why a function is original assembly, or None."""
    if any(todo.VU.match(o) for o in ops):
        return "VU0 macro instruction"
    if any(todo.MMI.match(o) and o not in COMPILER_EMITS for o in ops):
        return "128-bit MMI instruction"
    if kind == "handwritten":
        return "marked handwritten by the disassembler"
    return None


def classify(funcs, bodies, references):
    """[(name, addr, size, kind, why)] for game-code functions.

    funcs: (name, addr, size, kind) in any order, game code only; bodies: {name: listing lines};
    references: {name: how many times the asm outside its own labels names it}.
    """
    out = []
    ok = True  # the code before is finished: true at the start of game code
    for name, addr, size, kind in sorted(funcs, key=lambda f: f[1]):
        lines = bodies.get(name, [])
        tags = todo.tags_of(lines, kind)
        ops = ops_of(lines)
        why = handwritten(ops, kind)
        if why:
            out.append((name, addr, size, "handwritten", why))
            ok = ends_finished(ops)
            continue
        if ("fragment" in tags and ok and addr % 8 == 0 and not any(BRANCH.match(o) for o in ops)
                and references.get(name, 0) == 0):
            out.append((name, addr, size, "remnant", "stripped-function leftover"))
            continue  # the chain stays finished across a remnant
        ok = ends_finished(ops)
    return out


def references_of(names):
    """{name: occurrences in the asm outside its own labels}."""
    counts = {n: 0 for n in names}
    pattern = re.compile(r"\b(func_[0-9A-Fa-f]{8})\b")
    for path in glob.glob(str(ROOT / "asm" / "us" / "**" / "*.s"), recursive=True):
        for line in Path(path).read_text().splitlines():
            if line.startswith(OWN_LINES):
                continue
            for m in pattern.finditer(line):
                if m.group(1) in counts:
                    counts[m.group(1)] += 1
    return counts


def derive():
    bodies = todo.bodies()
    funcs = [f for f in todo.functions() if todo.source_of(f[1]).startswith("src/main")]
    refs = references_of([f[0] for f in funcs])
    return classify(funcs, bodies, refs)


def render(rows):
    return HEADER + "\n" + "".join("%s\t%08X\t%d\t%s\t%s\n" % r for r in sorted(rows, key=lambda r: r[1]))


def read_table(path=None):
    """{name: kind} of config/us/original_asm.tsv, or empty when the table does not exist."""
    path = path or TABLE
    if not path.exists():
        return {}
    rows = {}
    for line in path.read_text().splitlines()[1:]:
        name, _addr, _size, kind, _why = line.split("\t")
        rows[name] = kind
    return rows


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)
    text = render(derive())
    if args.check:
        if not TABLE.exists() or TABLE.read_text() != text:
            print("stale: %s (run python3 tools/classify_asm.py)" % TABLE.relative_to(ROOT))
            return 1
        return 0
    TABLE.parent.mkdir(parents=True, exist_ok=True)
    TABLE.write_text(text)
    rows = read_table()
    kinds = {}
    for k in rows.values():
        kinds[k] = kinds.get(k, 0) + 1
    print("wrote %s: %s" % (TABLE.relative_to(ROOT), ", ".join("%d %s" % (v, k) for k, v in sorted(kinds.items()))))
    return 0


if __name__ == "__main__":
    sys.exit(main())
