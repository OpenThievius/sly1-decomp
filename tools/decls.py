# SPDX-License-Identifier: AGPL-3.0-or-later
"""Find declarations whose return type contradicts the function they declare.

    python3 tools/decls.py            # every declaration in src/ that looks wrong
    python3 tools/decls.py --names    # only the functions, one per line

A declaration's return type changes the caller's code even where the caller ignores the value: a
call to a function that returns something sets $v0 (or $f0), so the register allocator keeps its
other values out of that register around the call. A `void` declaration of a function that returns
a value looks like a register-allocation tie in the caller (docs/AGENT_WORKFLOW.md), and no
reordering of the caller fixes it. Two kinds of evidence say what a function returns:

    definition   its C definition in src/: void, float (f32, f64) or a value in $v0
    callers      retail's callers: one that reads $v0 or $f0 after the call, before writing it,
                 uses the function's result (checked over asm/us/, so US names only)

A declaration is reported when it says void and the function returns a value, when it says the
value is in one register class ($v0 or $f0) and the evidence says the other, or when it is not void
and the definition is. Callers only ever prove that a value is returned: none reading it proves
nothing, since a caller may ignore a result.
"""

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import symbols  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
NAME = r"func_(?:[a-z]+_)?[0-9A-Fa-f]{8}"
# A file-scope declaration or definition: a return type, the name (perhaps Class::), the arguments.
SIGNATURE = re.compile(r"^(?P<ret>[A-Za-z_][\w \t\*&:<>,]*?)(?P<sep>[ \t\*&]+)(?:\w+::)?(?P<name>%s)\s*\((?P<args>[^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*(?:const\s*)?(?P<end>;|\{|$)" % NAME, re.M)
QUALIFIERS = {"static", "inline", "extern", "virtual", "const", "volatile"}
# The R5900 FPU is single precision: a double (f64) comes back in $v0/$v1, like an integer.
FLOATS = {"f32", "float"}

# Instructions whose first operand is read, not written.
READS_FIRST = re.compile(r"^(s[bhwdq]|swc1|sdc1|sqc2|swl|swr|sdl|sdr|b\w*|j|jr|jalr|mult\w*|div\w*|mt\w+|teq|tne|c\.\w+|madd\w*|msub\w*)$")


def kind_of(ret):
    """'void', 'float' or 'value' for a declaration's return type text."""
    words = [w for w in re.split(r"\s+", ret.strip()) if w and w not in QUALIFIERS]
    text = " ".join(words)
    if text == "void":
        return "void"
    if text in FLOATS:
        return "float"
    return "value"


def signatures(text):
    """[(name, kind, line, is_definition)] of the file-scope declarations and definitions in a text."""
    out = []
    text = symbols.normalize(text)      # a declaration may use the readable name (tools/symbols.py)
    for m in SIGNATURE.finditer(text):
        ret = m.group("ret")
        if ret.split()[0] in ("return", "else", "case", "goto", "new", "delete", "typedef", "using", "friend"):
            continue
        if "(" in ret or "=" in ret:
            continue
        line = text.count("\n", 0, m.start()) + 1
        rest = text[m.end("args") + 1:].lstrip()
        definition = m.group("end") == "{" or rest.startswith("{")
        kind = "value" if "*" in m.group("sep") or "&" in m.group("sep") else kind_of(ret)
        out.append((m.group("name"), kind, line, definition))
    return out


def source_files():
    for sub in ("main", "lib", "libm", "versions"):
        yield from sorted((ROOT / "src" / sub).rglob("*.cpp"))


def operands(text):
    parts = text.split(None, 1)
    ops = [o.strip() for o in parts[1].split(",")] if len(parts) > 1 else []
    return parts[0], ops


def register_use(op, ops, reg):
    """'read', 'write' or None: what an instruction does with `reg` ($v0 or $f0) first."""
    def mentions(o):
        return re.search(r"(^|[^\w$])\%s\b" % reg, o) is not None or re.search(r"\(\%s\)" % reg, o) is not None
    if not any(mentions(o) for o in ops):
        return None
    if op in ("mtc1", "dmtc1", "ctc1", "qmtc2"):   # the GPR is read, the FPR written
        return "read" if mentions(ops[0]) else "write"
    if op in ("mfc1", "dmfc1", "cfc1", "qmfc2"):
        return "write" if mentions(ops[0]) else "read"
    if READS_FIRST.match(op) or len(ops) == 1:
        return "read"
    if any(mentions(o) for o in ops[1:]):
        return "read"
    return "write"


def result_uses(path=None):
    """{callee: set of registers ($v0, $f0)} that retail's callers read after a call, before writing."""
    path = path or ROOT / "asm" / "us" / "text.s"
    ins = []
    for line in Path(path).read_text().splitlines():
        if line.startswith(("glabel", "endlabel", "nonmatching", "jlabel", ".L")) or line.lstrip().startswith(".L"):
            ins.append(None)    # a label or a function's edge: control may arrive from elsewhere
            continue
        text = line.split("*/", 1)[1].strip() if "*/" in line else ""
        if text:
            ins.append(operands(text))
    out = {}
    for i, item in enumerate(ins):
        if not item or item[0] != "jal" or not item[1]:
            continue
        callee = item[1][0]
        for reg in ("$v0", "$f0"):
            for j in range(i + 2, min(i + 40, len(ins))):   # after the delay slot
                if ins[j] is None:
                    break
                op, ops = ins[j]
                use = register_use(op, ops, reg)
                if use == "read":
                    out.setdefault(callee, set()).add(reg)
                if use or op in ("jal", "jalr", "j", "jr") or op.startswith("b"):
                    break
    return out


def problems(uses=None, near_misses=False):
    """[(file, line, name, declared, evidence)] of the declarations the evidence contradicts; with
    near_misses, the declarations in nonmatching/ too (a wrong return type there moves registers)."""
    uses = result_uses() if uses is None else uses
    decls, defined = [], {}
    for path in source_files():
        for name, kind, line, definition in signatures(path.read_text()):
            if definition and "versions" not in path.parts:
                defined.setdefault(name, kind)
            decls.append((path, line, name, kind, definition))
    if near_misses:
        # A near miss's declarations of the functions it calls (its own definition is the attempt).
        for path in sorted((ROOT / "nonmatching").rglob("*.cpp")):
            for name, kind, line, definition in signatures(path.read_text()):
                if not definition:
                    decls.append((path, line, name, kind, definition))
    out = []
    for path, line, name, kind, definition in decls:
        evidence = []
        have = defined.get(name)
        if have and have != kind and not definition:
            evidence.append("defined %s" % have)
        regs = uses.get(name, set())
        if "$v0" in regs and kind != "value" and have in (None, "value"):
            evidence.append("callers read $v0")
        if "$f0" in regs and kind != "float" and have in (None, "float"):
            evidence.append("callers read $f0")
        if evidence:
            out.append((path.relative_to(ROOT), line, name, kind, "; ".join(evidence)))
    return out


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--names", action="store_true", help="only the functions, one per line")
    parser.add_argument("--near-misses", action="store_true", help="also the declarations in nonmatching/")
    args = parser.parse_args(argv)
    rows = problems(near_misses=args.near_misses)
    if args.names:
        for name in sorted({r[2] for r in rows}):
            print(name)
    else:
        for path, line, name, kind, why in rows:
            print("%s:%d: %s declared %s: %s" % (path, line, name, kind, why))
    print("%d declaration(s) of %d function(s)" % (len(rows), len({r[2] for r in rows})), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
