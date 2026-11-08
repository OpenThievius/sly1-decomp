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

A third kind of evidence covers the functions with no C definition (original assembly, config/us/
original_asm.tsv, and the ones not yet matched), whose callers may all ignore the result:

    body         the function's own assembly: it returns a value when, on every path to a
                 `jr $ra` (its delay slot included), $v0 (or $f0) was written after the last call
                 from an argument, a constant, memory or a computation and not read since: a
                 value nothing reads is only there to be returned (a temporary is read, or is
                 an address built with `lui`)

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
READS_FIRST = re.compile(r"^(s[bhwdq]|swc1|sdc1|sqc2|swl|swr|sdl|sdr|b\w*|j|jr|jalr|mult\w*|div\w*|mt\w+|teq|tne|c\.[\w.]+|madd\w*|msub\w*)$")


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
        yield from sorted((ROOT / "src" / sub).rglob("*.c"))


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
    if op.startswith(("qmtc2", "qmfc2")):   # qmtc2.ni, qmfc2.i: the VU0 interlock suffixes
        op = op[:5]
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


UNDEF, SCRATCH, VALUE = 0, 1, 2
BRANCH = re.compile(r"^(b\w*|j|jal|jr|jalr)$")
WRITES_NOTHING = re.compile(r"^(nop|sync\S*|break|cache)$")


def function_bodies(path=None):
    """{name: [(op, operands) or ('label', name)]} of the functions in a disassembly."""
    path = path or ROOT / "asm" / "us" / "text.s"
    bodies, cur = {}, None
    for line in Path(path).read_text().splitlines():
        if line.startswith("glabel "):
            cur = bodies.setdefault(line.split()[1], [])
        elif line.startswith("endlabel"):
            cur = None
        elif cur is None:
            continue
        elif line.lstrip().startswith(".L") and line.rstrip().endswith(":"):
            cur.append(("label", [line.strip()[:-1]]))
        elif line.startswith("jlabel"):
            cur.append(("entry", [line.split()[1]]))
        elif "*/" in line:
            text = line.split("*/", 1)[1].strip()
            if text:
                cur.append(operands(text))
    return bodies


def _write_state(op, ops, reg, state):
    """The state of `reg` after one instruction that writes it."""
    if op == "lui":
        return SCRATCH
    others = [o for o in ops[1:] if o]
    regs = [r for o in others for r in re.findall(r"\$\w+", o)]
    out = VALUE
    if reg in regs:
        out = min(out, state)
    return out


def returns_value(body, reg="$v0"):
    """True when `reg` ($v0, or $f0 for a float) holds a returned value at every `jr $ra` of a
    function's body (docs above: written after the last call, not an address kept as scratch)."""
    # Merge each branch with its delay slot into one node: (slot, branch).
    nodes, labels, i = [], {}, 0
    while i < len(body):
        op, ops = body[i]
        if op in ("label", "entry"):
            labels[ops[0]] = len(nodes)
            if op == "entry":
                nodes.append((None, "entry", []))
            i += 1
            continue
        if BRANCH.match(op):
            slot = body[i + 1] if i + 1 < len(body) and body[i + 1][0] not in ("label", "entry") else ("nop", [])
            nodes.append((slot, op, ops))
            i += 2
            continue
        nodes.append((None, op, ops))
        i += 1

    def effect(op, ops, state):
        if WRITES_NOTHING.match(op) or not ops:
            return state
        use = register_use(op, ops, reg)
        if use == "write":
            return _write_state(op, ops, reg, state)
        if use == "read":
            return min(state, SCRATCH)      # the value is used here: $v0 holds a temporary
        return state

    states = {0: UNDEF}
    states.update({k: UNDEF for k, node in enumerate(nodes) if node[1] == "entry"})   # a jump table's target
    work, returns = list(states), []
    while work:
        n = work.pop()
        if n >= len(nodes):
            continue
        slot, op, ops = nodes[n]
        state = states[n]
        likely = bool(re.match(r"^b\w*l$", op)) and op not in ("bal", "bgezal", "bltzal")
        if slot is not None and op != "entry" and register_use(op, ops, reg) == "read":
            state = min(state, SCRATCH)     # the branch reads its operands before the slot runs
        slot_state = effect(slot[0], slot[1], state) if slot is not None else state
        succ = []
        if op == "entry":
            state = UNDEF
            succ = [(n + 1, state)]
        elif BRANCH.match(op):
            if op == "jr":
                if ops == ["$ra"]:
                    returns.append(slot_state)
            elif op in ("jal", "jalr", "bal", "bgezal", "bltzal"):
                succ = [(n + 1, UNDEF)]
            else:
                if ops and ops[-1] in labels:
                    succ.append((labels[ops[-1]], slot_state))
                if op not in ("j", "b"):
                    # a branch-likely runs its delay slot only when it is taken
                    succ.append((n + 1, state if likely else slot_state))
        else:
            succ = [(n + 1, effect(op, ops, state))]
        for t, st in succ:
            new = st if t not in states else min(states[t], st)
            if states.get(t) != new:
                states[t] = new
                work.append(t)
    return bool(returns) and all(r == VALUE for r in returns)


def body_returns(path=None):
    """{function: {'$v0', '$f0'}} that return a value according to their own assembly."""
    out = {}
    for name, body in function_bodies(path).items():
        regs = {reg for reg in ("$v0", "$f0") if returns_value(body, reg)}
        if regs:
            out[name] = regs
    return out


def problems(uses=None, near_misses=False, bodies=None):
    """[(file, line, name, declared, evidence)] of the declarations the evidence contradicts; with
    near_misses, the declarations in nonmatching/ too (a wrong return type there moves registers)."""
    uses = result_uses() if uses is None else uses
    if bodies is None:
        bodies = body_returns()
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
        evidence, evidence_extra = [], {}
        have = defined.get(name)
        if have and have != kind and not definition:
            evidence.append("defined %s" % have)
        regs = set(uses.get(name, set()))
        if not have:
            for reg in bodies.get(name, set()) - regs:
                regs.add(reg)
                evidence_extra[reg] = "its assembly returns %s" % reg
        if "$v0" in regs and kind != "value" and have in (None, "value"):
            evidence.append(evidence_extra.get("$v0", "callers read $v0"))
        if "$f0" in regs and kind != "float" and have in (None, "float"):
            evidence.append(evidence_extra.get("$f0", "callers read $f0"))
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
