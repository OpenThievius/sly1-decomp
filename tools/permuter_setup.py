# SPDX-License-Identifier: AGPL-3.0-or-later
"""Set up a near miss for decomp-permuter, against this project's own compiler.

    python3 tools/permuter_setup.py FILE FUNC          # writes build/permuter/FUNC/
    python3 tools/permuter_compile.py ...              # what that folder's compile.sh runs

decomp-permuter (https://github.com/simonlindholm/decomp-permuter, MIT) randomly rewrites one C
function -- statement order, temporaries, types, branch shape -- and keeps whatever compiles
closer to a target object. It is the tool for a register-allocation or scheduling tie that no
hand rewrite moves. It is never committed: fetch it into tools/ext/ (gitignored) as
docs/AGENT_WORKFLOW.md says, with its own Python environment there.

The folder this writes is what the permuter reads:

- target.o: retail's function, assembled from splat's listing (asm/us/text.s) with the build's
  assembler and flags, so its relocations look like a compiled object's;
- base.c: FILE preprocessed by the toolchain's cpp, with a `typedef struct X X;` for each struct
  it names, so that the permuter's C parser reads our C++ (wrap anything else C++ in
  PERM_IGNORE(...));
- compile.sh: compiles a candidate through tools/compile.py with the compiler and flags of the
  src/ file that holds FUNC (Sony's for the library), as tools/check.py does;
- settings.toml: the function's name and compiler type.

A score of 0 from the permuter is a lead, not a match: copy the candidate back and run
tools/check.py; it counts once that prints EXACT in a build that matches. As OpenRAC wires it up
(rac1-decomp, docs/agents/PERMUTER.md; credited in THIRD_PARTY_NOTICES.md); the code is ours.
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import symbols  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
OUT = ROOT / "build" / "permuter"
STRUCT = re.compile(r"\b(struct|union|class)\s+(?:__attribute__\s*\(\(.*?\)\)\s*)?([A-Za-z_]\w*)\s*(?:[{;]|:[^:])")


def target(func, dest):
    """Assemble retail's listing of FUNC into dest/target.o."""
    import build
    import c_layout
    header, chunks = c_layout.split_text("us")
    if func not in chunks:
        raise SystemExit("%s is not in asm/us/text.s" % func)
    src = dest / "target.s"
    src.write_text("\n".join(header + chunks[func]) + "\n")
    subprocess.run([build.tool("as")] + build.AS_FLAGS + [str(src), "-o", str(dest / "target.o")], check=True)


C_TYPEDEF = re.compile(r"^\s*typedef\b[^:<&]*;\s*$", re.S)


def items(text):
    """The top-level items of a translation unit: each declaration up to its `;`, and each function
    definition up to its closing brace."""
    out, start, depth, i, body = [], 0, 0, 0, False
    while i < len(text):
        c = text[i]
        if c in "\"'":
            j = i + 1
            while j < len(text) and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i = j + 1
            continue
        if c in "({[":
            if c == "{" and depth == 0:
                before = text[start:i].rstrip()
                body = before.endswith(")") or before.endswith("const")
            depth += 1
        elif c in ")}]":
            depth -= 1
            if c == "}" and depth == 0 and body:
                out.append(text[start:i + 1]); start, body = i + 1, False
        elif c == ";" and depth == 0:
            out.append(text[start:i + 1]); start = i + 1
        i += 1
    out.append(text[start:])
    return out


def plain_calls(body, tags):
    """FUNC's body with the C++ calls in it given plain names, and the macros that turn them back:
    `Fpu::Sqrt(x)` becomes `Fpu__Sqrt(x)` (`Vu0::Vec::Of` `Vu0__Vec__Of`), a type called like a function `T()` becomes `make_T()`."""
    aliases = {}

    def scoped(m):
        alias = m.group(1).replace("::", "__")
        aliases[alias] = m.group(1)
        return alias + "("
    body = re.sub(r"\b([A-Za-z_]\w*(?:::[A-Za-z_]\w*)+)\s*\(", scoped, body)
    head, brace, rest = body.partition("{")

    def construct(m):
        if m.group(1) not in tags:
            return m.group(0)
        aliases["make_" + m.group(1)] = m.group(1)
        return "make_%s(" % m.group(1)
    rest = re.sub(r"(?<![\w.>])([A-Za-z_]\w*)\s*\((?=\s*\))", construct, rest)
    return head + brace + rest, sorted(aliases.items())


# What ends an operand of g++'s <? and >?, which bind looser than + and - and tighter than the
# comparisons: anything of lower precedence, at the operand's own parenthesis depth.
STOP = re.compile(r"&&|\|\||<<=|>>=|<<|>>|==|!=|<=|>=|[-+*/%&|^]?=|[<>?:,;{}&|^]|\breturn\b")


def min_max_calls(text):
    """g++'s `a >? b` and `a <? b` as permuter_max(a, b) and permuter_min(a, b), which the
    permuter's C parser reads; permuter_compile.py defines them as the operators again."""
    while True:
        m = re.search(r"([<>])\?", text)
        if not m:
            return text
        name = "permuter_max" if m.group(1) == ">" else "permuter_min"
        # The left operand: back to an unmatched ( or a lower-precedence token at depth 0.
        i, depth = m.start(), 0
        while i > 0:
            c = text[i - 1]
            if c in ")]":
                depth += 1
            elif c in "([":
                if depth == 0:
                    break
                depth -= 1
            elif depth == 0:
                if re.search(r"\breturn\s$", text[max(0, i - 8):i]):
                    break
                t = STOP.search(text, i - 3 if i >= 3 else 0, i)
                if t and t.end() == i and not text[t.start():i].endswith("->") \
                        and not (c == ">" and text[i - 2:i] == "->"):
                    break
            i -= 1
        # The right operand: on to an unmatched ) or a lower-precedence token at depth 0.
        j, depth = m.end(), 0
        while j < len(text):
            c = text[j]
            if c in "([":
                depth += 1
            elif c in ")]":
                if depth == 0:
                    break
                depth -= 1
            elif depth == 0:
                if text.startswith("->", j):
                    j += 2
                    continue
                t = STOP.match(text, j)
                if t:
                    break
            j += 1
        left, right = text[i:m.start()].strip(), text[m.end():j].strip()
        lead = text[i:m.start()][:len(text[i:m.start()]) - len(text[i:m.start()].lstrip())]
        text = text[:i] + lead + "%s(%s, %s)" % (name, left, right) + text[j:]


def min_max_operators(text):
    """The inverse of min_max_calls: permuter_max(a, b) and permuter_min(a, b) as g++'s
    (a >? b) and (a <? b) again, for a candidate copied back into its near miss."""
    while True:
        m = re.search(r"\bpermuter_(max|min)\s*\(", text)
        if not m:
            return text
        depth, comma, j = 0, None, m.end()
        while j < len(text):
            c = text[j]
            if c in "([":
                depth += 1
            elif c in ")]":
                if depth == 0:
                    break
                depth -= 1
            elif c == "," and depth == 0 and comma is None:
                comma = j
            j += 1
        if comma is None or j >= len(text):
            return text
        op = ">?" if m.group(1) == "max" else "<?"
        a, b = text[m.end():comma].strip(), text[comma + 1:j].strip()
        text = text[:m.start()] + "(%s %s %s)" % (a, op, b) + text[j + 1:]


def isolate(text, func):
    """The unit with everything the permuter's C parser cannot read, or need, inside PERM_IGNORE:
    all but FUNC's definition and plain C typedefs. Our C++ (classes with bases and methods,
    references, templates) then reaches the compiler untouched."""
    tags = {m.group(2) for m in STRUCT.finditer(text)}
    out = []
    for item in items(text):
        stripped = item.strip()
        if not stripped:
            out.append(item)
        elif re.search(r"\b%s\s*\(" % func, stripped) and stripped.endswith("}"):
            body, aliases = plain_calls(min_max_calls(item), tags)
            if aliases:
                # The permuter preprocesses its input, so a #define would undo the alias before
                # it parses; permuter_compile.py turns these strings back into #defines.
                out.append("\nPERM_IGNORE(%s)\n" % " ".join('static const char permuter_alias_%d[] = "%s=%s";' % (i, a, b)
                                                         for i, (a, b) in enumerate(aliases)))
            out.append(body)
        elif C_TYPEDEF.match(stripped) and "class" not in stripped:
            if "__attribute__" in stripped:
                # The permuter's parser drops attributes, so u128 (mode(TI)) would reach the
                # compiler as a 32-bit int, and every VU0 helper's "j" operand would be
                # impossible: its parser gets the plain typedef, and permuter_compile.py puts
                # the original back.
                name = re.search(r"(\w+)\s*__attribute__", stripped)
                if name:
                    plain = re.sub(r"\s*__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)", "", stripped)
                    out.append("\nPERM_IGNORE(static const char permuter_typedef_%s[] = \"%s\";)\n"
                               % (name.group(1), stripped.replace('"', '\\"')))
                    out.append("\n" + plain + "\n")
                    continue
            out.append(item)
        else:
            out.append("\nPERM_IGNORE(%s)\n" % stripped)
    return "".join(out)


def base(path, dest, func):
    """FILE preprocessed, with a typedef for each struct, as dest/base.c."""
    import compile as cc
    run, cpp, _cc1plus, _as = cc.tools()
    ii = dest / "base.ii"
    proc = subprocess.run(run + [str(cpp)] + cc.CPP_DEFINES + ["-P", str(Path(path).resolve().relative_to(ROOT)),
                                                             str(ii.relative_to(ROOT))],
                          cwd=ROOT, capture_output=True, text=True)
    if proc.returncode:
        raise SystemExit("cpp failed:\n" + proc.stderr)
    text = ii.read_text()
    tags = sorted({m.group(2) for m in STRUCT.finditer(text)})
    lines = ["typedef %s %s %s;" % ("union" if kind == "union" else "struct", tag, tag) for tag in tags
             for kind in [next(m.group(1) for m in STRUCT.finditer(text) if m.group(2) == tag)]]
    (dest / "base.c").write_text("\n".join(lines) + "\n" + isolate(text, func))
    ii.unlink()


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("file")
    parser.add_argument("func")
    args = parser.parse_args(argv)
    args.func = symbols.canonical(args.func)    # either name (tools/symbols.py)
    dest = OUT / args.func
    dest.mkdir(parents=True, exist_ok=True)
    target(args.func, dest)
    base(args.file, dest, args.func)
    compile_sh = dest / "compile.sh"
    compile_sh.write_text('#!/bin/sh\nexec "%s" "%s" %s "$@"\n' % (sys.executable, ROOT / "tools" / "permuter_compile.py",
                                                                  args.func))
    compile_sh.chmod(0o755)
    (dest / "settings.toml").write_text('func_name = "%s"\ncompiler_type = "gcc"\n' % args.func)
    print("wrote %s: target.o, base.c, compile.sh, settings.toml" % dest.relative_to(ROOT))
    print("run: tools/ext/venv/bin/python tools/ext/decomp-permuter/permuter.py -j6 %s" % dest.relative_to(ROOT))
    return 0


if __name__ == "__main__":
    sys.exit(main())
