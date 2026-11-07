# SPDX-License-Identifier: AGPL-3.0-or-later
"""Say whether an attempt differs from retail only in its registers.

    python3 tools/regdiff.py FILE.cpp FUNC      # one attempt
    python3 tools/regdiff.py --all             # every US near miss in nonmatching/

Each side's instructions are compared with every register name replaced by one placeholder:

    EXACT           the bytes are retail's
    registers       the same instructions in the same order, only the registers differ
    order           the same instructions (as a multiset) in another order, registers aside
    code            different instructions: something in the C is not retail's yet

with the share of instructions that agree once the registers are set aside. A `registers` or
`order` attempt is a register-allocation problem (docs/AGENT_WORKFLOW.md): the C computes what
retail computes, and what is left is the order the compiler sees, not a missing statement.
"""

import argparse
import collections
import difflib
import re
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check  # noqa: E402
import compile as cc  # noqa: E402
import elf  # noqa: E402
import symbols  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
REGISTER = re.compile(r"\b(zero|at|v[01]|a[0-7]|t[0-9]|s[0-8]|fp|sp|ra|gp|k[01])\b|\$f\d+|\$vf\d+")


def masked(lines):
    """Each instruction with its registers replaced: the mnemonic and operands, nothing else."""
    return [REGISTER.sub("R", text) for _, text in lines]


def classify(ours, retail):
    """(verdict, agreeing instructions, retail's count) for two disassemblies."""
    if [w for w, _ in ours] == [w for w, _ in retail]:
        return "EXACT", len(retail), len(retail)
    a, b = masked(ours), masked(retail)
    agree = sum(block.size for block in difflib.SequenceMatcher(None, a, b, autojunk=False).get_matching_blocks())
    if a == b:
        return "registers", agree, len(b)
    if collections.Counter(a) == collections.Counter(b):
        return "order", agree, len(b)
    return "code", agree, len(b)


def attempt(path, func, key="us"):
    """(verdict, agree, total) for FUNC compiled from PATH as it would land, or ("ERROR", 0, 0)."""
    with tempfile.TemporaryDirectory(prefix="sly1-regdiff-") as tmp:
        obj_path = Path(tmp) / "unit.o"
        try:
            cc.compile_file(path, obj_path, source=check.source_for(path, func))
        except cc.CompileError:
            return "ERROR", 0, 0
        obj = elf.Elf(obj_path.read_bytes())
    try:
        r = check.check_function(obj, func, key, check.Resolver(key), check.retail_image(key))
    except KeyError:
        return "ERROR", 0, 0
    if "ours" not in r:
        return "ERROR", 0, 0
    _, size = check.target_of(key, func)
    ours = check.disassemble(r["ours"], r["address"])
    retail = check.disassemble(r["retail"][:size], r["address"])
    return classify(ours, retail)


def near_misses():
    """(path, function) of every US near miss in nonmatching/ whose function is not matched yet
    or classed as original assembly (config/us/original_asm.tsv)."""
    import classify_asm
    import version_check
    done = set(version_check.defined_in_src()) | set(classify_asm.read_table())
    for path in sorted((ROOT / "nonmatching").glob("func_*.c*")):
        if path.stem not in done:
            yield path, path.stem


def report(path, func):
    verdict, agree, total = attempt(path, func)
    share = "%.1f%%" % (100.0 * agree / total) if total else "-"
    print("%-14s %-9s %6s  %d/%d" % (func, verdict, share, agree, total))
    sys.stdout.flush()
    return verdict


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("src", nargs="?")
    parser.add_argument("func", nargs="?")
    parser.add_argument("--all", action="store_true", help="every US near miss in nonmatching/")
    args = parser.parse_args(argv)
    if args.func:
        args.func = symbols.canonical(args.func)    # either name (tools/symbols.py)
    if args.all:
        counts = collections.Counter(report(p, f) for p, f in near_misses())
        print("; ".join("%s %d" % kv for kv in sorted(counts.items())))
        return 0
    if not (args.src and args.func):
        parser.error("FILE.cpp FUNC, or --all")
    return 0 if report(Path(args.src), args.func) == "EXACT" else 1


if __name__ == "__main__":
    sys.exit(main())
