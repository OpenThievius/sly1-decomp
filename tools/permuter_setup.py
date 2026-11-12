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


KEYWORDS = {"return", "else", "do", "case", "goto", "delete", "new", "sizeof", "throw", "typedef", "const",
            "static", "extern", "struct", "union", "class", "enum", "public", "private", "protected"}
SCOPED = re.compile(r"\b[A-Za-z_]\w*(?:::[A-Za-z_]\w*)+\b")
LABEL = re.compile(r"^([ \t]*)((?!(?:case|default|public|private|protected)\b)[A-Za-z_]\w*):[ \t]*$", re.M)
DIRECT_INIT = re.compile(r"^([ \t]*(?:const\s+)?)([A-Za-z_][\w:]*)(\s+[A-Za-z_]\w*)\(", re.M)
CTOR = re.compile(r"((?:\bconst\s+)?[A-Za-z_][\w:]*\s+[A-Za-z_]\w*\s*)=\s*permuter_ctor(?:_\w+)?\s*\(")


def outside_strings(text, fn):
    """fn applied to the parts of text that are not string or character literals."""
    out, i, last = [], 0, 0
    while i < len(text):
        c = text[i]
        if c in "\"'":
            j = i + 1
            while j < len(text) and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            out.append(fn(text[last:i]))
            out.append(text[i:j + 1])
            i = last = j + 1
            continue
        i += 1
    out.append(fn(text[last:]))
    return "".join(out)


def balanced(text, i):
    """The index of the `)` that closes the `(` before text[i], or -1."""
    depth = 0
    while i < len(text):
        c = text[i]
        if c in "\"'":
            j = i + 1
            while j < len(text) and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i = j
        elif c in "([":
            depth += 1
        elif c in ")]":
            if depth == 0:
                return i
            depth -= 1
        i += 1
    return -1


def direct_inits(rest, tags):
    """`T x(a, b);`, which the permuter's parser reads as a function declaration, as
    `T x = permuter_ctor(a, b);`; ctor_declarations puts it back for the compiler."""
    out, pos = [], 0
    for m in DIRECT_INIT.finditer(rest):
        if m.start() < pos or m.group(2) in KEYWORDS or not (m.group(2) in tags or "::" in m.group(2)):
            continue
        close = balanced(rest, m.end())
        if close < 0 or not rest[m.end():close].strip() or not re.match(r"\s*;", rest[close + 1:]):
            continue
        out.append(rest[pos:m.start()] + "%s%s%s = permuter_ctor%s(%s)" % (m.group(1), m.group(2), m.group(3),
                                                                        "_" + m.group(2) if m.group(2) in tags else "",
                                                                        rest[m.end():close]))
        pos = close + 1
    return "".join(out) + rest[pos:]


def ctor_declarations(text):
    """The inverse of direct_inits: `T x = permuter_ctor(a, b);` as `T x(a, b);` again, for the
    compiler and for a candidate copied back into its near miss."""
    while True:
        m = CTOR.search(text)
        if not m:
            return text
        close = balanced(text, m.end())
        if close < 0:
            return text
        text = text[:m.start()] + "%s(%s)" % (m.group(1).rstrip(), text[m.end():close]) + text[close + 1:]


REFERENCE = re.compile(r"^([ \t]*(?:const\s+)?[A-Za-z_][\w:]*(?:\s*\*+)?)[ \t]*&[ \t]*([A-Za-z_]\w*)[ \t]*=", re.M)
REF_NAME = re.compile(r"\bpermuter_ref_(\w+)")


def reference_locals(rest):
    """A local reference `T& x = e;`, which the parser cannot read, as `T permuter_ref_x = e;` with
    each later use of x renamed; reference_declarations puts it back."""
    names = []
    for m in REFERENCE.finditer(rest):
        if m.group(1).split()[-1] not in KEYWORDS:
            names.append(m.group(2))
    for name in names:
        rest = REFERENCE.sub(lambda m: "%s permuter_ref_%s =" % (m.group(1), name) if m.group(2) == name else m.group(0),
                             rest)
        rest = re.sub(r"(?<![\w.>:])%s\b" % re.escape(name), "permuter_ref_" + name, rest)
    return rest


def reference_declarations(text):
    """The inverse of reference_locals: `T permuter_ref_x = e;` as `T& x = e;`, and x again."""
    text = re.sub(r"((?:\bconst\s+)?[A-Za-z_][\w:]*(?:\s*\*+)?)\s+permuter_ref_(\w+)\s*=", r"\1& \2 =", text)
    return REF_NAME.sub(r"\1", text)


FOR_DECL = re.compile(r"\bfor\s*\(\s*((?:const\s+)?[A-Za-z_]\w*(?:\s*\*+)?)\s+([A-Za-z_]\w*)\s*(=|;)")
FOR_HOIST = re.compile(r"\{[ \t]*\n?[ \t]*((?:const\s+)?[A-Za-z_]\w*(?:\s*\*+)?)\s+permuter_for_(\w+);\s*"
                       r"(for)\s*\(\s*permuter_for_\2\s*=")
FOR_NAME = re.compile(r"\bpermuter_for_(\w+)")


def matching(text, i, open_, close):
    """The index of the bracket that closes the one at text[i], or -1 (strings and characters skipped)."""
    depth, n = 0, len(text)
    while i < n:
        c = text[i]
        if c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i = j
        elif c == open_:
            depth += 1
        elif c == close:
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def for_end(text, start):
    """The index just past the `for` statement that starts at text[start], or -1 when its body is
    neither a braced block nor a single simple statement."""
    open_ = text.find("(", start)
    close = matching(text, open_, "(", ")")
    if close < 0:
        return -1
    i = close + 1
    while i < len(text) and text[i].isspace():
        i += 1
    if text.startswith("{", i):
        end = matching(text, i, "{", "}")
        return end + 1 if end >= 0 else -1
    j = i
    while j < len(text) and text[j] != ";":
        if text[j] in "{}":
            return -1
        j += 1
    return j + 1 if j < len(text) else -1


def for_declarations(rest):
    """A declaration in a for loop's first clause, `for (s32 j = 0; ...)`, which the permuter's
    randomizer cannot walk (it fails on the DeclList, most of its tries), as a block that declares it
    first: `{ s32 permuter_for_j; for (permuter_for_j = 0; ...) ... }`, the name made apart so
    that for_inits can put the loop back. A loop that is the body of an `if` without braces, or
    that declares two variables, stays."""
    pos = 0
    while True:
        m = FOR_DECL.search(rest, pos)
        if not m:
            return rest
        end = for_end(rest, m.start())
        prev = (rest[:m.start()].rstrip() or ";")[-1]
        first = rest[m.end():rest.index(";", m.end())]
        if end < 0 or prev not in ";{}" or "," in first:
            pos = m.end()
            continue
        name = m.group(2)
        inner = rest[m.start():end].split("(", 1)[1]
        inner = inner.lstrip()[len(m.group(1)):].lstrip()           # without its type
        inner = re.sub(r"(?<![\w.>:])%s\b" % re.escape(name), "permuter_for_" + name, inner)
        head = "{ %s permuter_for_%s; for (" % (m.group(1).strip(), name)
        rest = rest[:m.start()] + head + inner + " }" + rest[end:]
        pos = m.start() + len(head)         # the loops inside it next


def for_inits(text):
    """The inverse of for_declarations: `{ s32 permuter_for_j; for (permuter_for_j = 0; ...) ... }`
    as `for (s32 j = 0; ...) ...` where the block holds only that loop; a declaration the permuter
    moved away keeps its place and gets the plain name."""
    while True:
        m = FOR_HOIST.search(text)
        if not m:
            break
        end = for_end(text, m.start(3))
        close = matching(text, m.start(), "{", "}")
        if end < 0 or close < 0 or text[end:close].strip():
            # Something else is in the block now: only the name goes back.
            text = text[:m.start() + 1] + text[m.start() + 1:].replace("permuter_for_" + m.group(2), "permuter_keep_" + m.group(2), 1)
            continue
        loop = text[m.start(3):end]
        loop = re.sub(r"\bpermuter_for_%s\b" % re.escape(m.group(2)), m.group(2), loop)
        loop = re.sub(r"\(\s*%s\s*=" % re.escape(m.group(2)), "(%s %s =" % (m.group(1).strip(), m.group(2)), loop, count=1)
        text = text[:m.start()] + loop + text[close + 1:]
    text = text.replace("permuter_keep_", "permuter_for_")
    return FOR_NAME.sub(r"\1", text)


def cpp_declarations(text):
    """All the inverses, for a candidate that goes back to the compiler or into its near miss."""
    return for_inits(reference_declarations(ctor_declarations(text)))


def plain_calls(body, tags):
    """FUNC's body with the C++ in it given plain names, and the macros that turn them back:
    `Fpu::Sqrt(x)` becomes `Fpu__Sqrt(x)` (`Vu0::Vec::Of` `Vu0__Vec__Of`, and a type `Vu0::Vec`
    `Vu0__Vec`, which typedefs name), a type called like a function `T(a)` becomes `make_T(a)`, a
    declaration `T x(a);` becomes `T x = permuter_ctor(a);`, a local reference
    `T& x = e;` becomes `T permuter_ref_x = e;`, and a label that ends a block
    gets an empty statement for C (`done: ;`)."""
    aliases = {}

    def scoped(m):
        alias = m.group(0).replace("::", "__")
        aliases[alias] = m.group(0)
        return alias
    head, brace, rest = body.partition("{")
    rest = for_declarations(reference_locals(direct_inits(rest, tags)))
    rest = LABEL.sub(r"\1\2: ;", rest)

    def construct(m):
        if m.group(1) not in tags:
            return m.group(0)
        aliases["make_" + m.group(1)] = m.group(1)
        return "make_%s(" % m.group(1)
    rest = outside_strings(rest, lambda t: re.sub(r"(?<![\w.>:])([A-Za-z_]\w*)\s*\((?!\s*\*)", construct, t))
    body = outside_strings(head + brace + rest, lambda t: SCOPED.sub(scoped, re.sub(r"(\b[A-Za-z_]\w*(?:::[A-Za-z_]\w*)+)\s+\(", r"\1(", t)))
    return body, sorted(aliases.items())


def scoped_types(body, aliases):
    """The aliases of plain_calls that stand for a type in body (before a declared name, or before
    the `*` of a cast), for the `typedef struct A A;` lines the permuter's parser needs."""
    return sorted(a for a, real in aliases if "::" in real
                  and re.search(r"\b%s\b(?=\s+[A-Za-z_]|\s*\*+\s*(?:\)|[A-Za-z_>])|\s*&\s*[A-Za-z_])" % a, body))


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


CPP_ONLY = re.compile(r"::|\b(?:class|template|operator|virtual|static|inline|public|private|protected|friend|"
                      r"typename|namespace|using|new|delete|this|bool)\b|__attribute__|&|\bextern\s+\"")
PLAIN_STRUCT = re.compile(r"^(?:struct|union)\s+[A-Za-z_]\w*\s*\{[^{}]*\}\s*;$", re.S)
PLAIN_FIELD = re.compile(r"^\s*(?:const\s+)?[A-Za-z_]\w*(?:\s*\*+)?\s*\*?[A-Za-z_]\w*(?:\[[^\]]*\])*\s*;\s*$")
PLAIN_DECL = re.compile(r"^(?:extern\s+)?(?:const\s+)?[A-Za-z_]\w*(?:\s*\*+)?\s*\*?\s*[A-Za-z_]\w*\s*"
                        r"(?:\[[^\]]*\]|\([^()]*\))\s*;$|^(?:extern\s+)?(?:const\s+)?[A-Za-z_]\w*(?:\s*\*+)?\s+"
                        r"[A-Za-z_]\w*\s*;$")


STRUCT_HEAD = re.compile(r"^(?:struct|class)\s+(?:__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)\s*)?([A-Za-z_]\w*)\s*"
                         r"(?::\s*(?:public\s+)?([A-Za-z_]\w*)\s*)?\{")


def strip_attribute(item):
    return re.sub(r"\s*__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)", "", item)


def member_fields(body):
    """The data members of a struct's body, as one C declaration per line (an anonymous union or
    struct of plain fields kept whole), or None when it holds anything else but methods: a template,
    a nested type, a typedef, an enum, an initialiser."""
    out, depth, start, i = [], 0, 0, 0
    while i < len(body):
        c = body[i]
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == "{" and depth == 0:
            before = body[start:i].strip()
            if re.fullmatch(r"(?:union|struct)", before):
                end = matching(body, i, "{", "}")
                inner = member_fields(body[i + 1:end]) if end > 0 else None
                tail = body.find(";", end)
                if inner is None or tail < 0 or body[end + 1:tail].strip():
                    return None
                out.append("%s { %s };" % (before, " ".join(inner)))
                start, i = tail + 1, tail
            elif before.endswith((")", "const")) or re.search(r"\)\s*(?:const)?\s*(?::[^{]*)?$", before):
                end = matching(body, i, "{", "}")        # a method with its body: dropped
                if end < 0:
                    return None
                start, i = end + 1, end
            else:
                return None
        elif c == ";" and depth == 0:
            decl = " ".join(body[start:i].split())
            start = i + 1
            if not decl or re.match(r"^(?:public|private|protected)\s*:$", decl):
                pass
            elif "(" in decl and "(*" not in decl:
                pass            # a method's declaration
            elif re.search(r"\b(?:template|typedef|enum|friend|operator|typename|using|static|virtual)\b|=|::|&", decl):
                return None
            else:
                out.append(decl + ";")
        i += 1
    return out


def struct_view(item, views, tags):
    """The plain struct the permuter's parser can read for the struct `item`, recorded in views by
    name, or None: its fields only, a base class's first (as C has no inheritance), each field a
    plain declaration."""
    m = STRUCT_HEAD.match(strip_attribute(item))
    item = strip_attribute(item)
    close = matching(item, m.end() - 1, "{", "}")
    if close < 0 or not item[close + 1:].strip() == ";":
        return None
    fields = member_fields(item[m.end():close])
    if not fields and not m.group(2):
        return None             # nothing for the parser to learn (and an empty struct is not written back)
    if fields is None:
        return None
    if m.group(2):
        if m.group(2) not in views:
            return None
        base = views[m.group(2)]
        fields = [f for f in base[base.index("{") + 1:base.rindex("}")].split("\n") if f.strip()] + fields
    for f in fields:
        if CPP_ONLY.search(f):
            return None
    view = "struct %s {\n%s\n};" % (m.group(1), "\n".join(fields))
    views[m.group(1)] = view
    return view


def plain_c_item(stripped, tags):
    """Whether the permuter's parser can read this declaration as it is, so that it knows the
    fields of a struct and the type of a global or a function (without them the randomizer fails on
    `p->x`, on a global's name or on a call to a function it has never seen): a struct of plain
    fields, an `extern` global or a prototype that names no C++ construct and has no initialiser."""
    if CPP_ONLY.search(stripped) or "=" in stripped or "//" in stripped:
        return False
    if PLAIN_STRUCT.match(stripped):
        fields = stripped[stripped.index("{") + 1:stripped.rindex("}")].replace("\n", " ")
        return all(not f.strip() or PLAIN_FIELD.match(f + ";") or re.match(r"^\s*\w+\s+\w+(\s*,\s*\w+)*\s*$", f)
                   for f in fields.split(";"))
    return bool(PLAIN_DECL.match(re.sub(r"\s+", " ", stripped)))


BUILTINS = {"__builtin_fabsf": "f32 __builtin_fabsf(f32 x);"}
STATIC_FN = re.compile(r"\bstatic\s+(?:inline\s+)?((?:const\s+)?[A-Za-z_]\w*)\s+([A-Za-z_]\w*)\s*\(")


def class_body(item_texts, name):
    """The text between the braces of `struct NAME {` (or class), from the unit's items, or None."""
    for item in item_texts:
        m = re.search(r"\b(?:struct|class)\s+(?:__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)\s*)?%s\s*(?::[^{;]*)?\{" % re.escape(name), item)
        if m:
            close = matching(item, m.end() - 1, "{", "}")
            if close > 0:
                return item[m.end():close]
    return None


def static_returns(body, prefix, out):
    """{prefix + name: {return types}} for the static functions at body's own level and,
    as prefix + Nested__, in a nested struct's."""
    depth, i, level = 0, 0, []
    for m in STATIC_FN.finditer(body):
        before = body[:m.start()]
        if before.count("{") - before.count("}") != 0:
            continue
        tmpl = re.search(r"template\s*<([^>]*)>\s*$", before)
        if tmpl and re.search(r"\b%s\b" % re.escape(m.group(1)), tmpl.group(1)):
            continue            # the return type is a template parameter
        out.setdefault(prefix + m.group(2), set()).add(m.group(1))
    for m in re.finditer(r"\bstruct\s+([A-Za-z_]\w*)\s*\{", body):
        before = body[:m.start()]
        if before.count("{") - before.count("}") == 0:
            close = matching(body, m.end() - 1, "{", "}")
            if close > 0:
                static_returns(body[m.end():close], prefix + m.group(1) + "__", out)
    return out


def alias_stubs(item_texts, aliases, body):
    """Declarations for the permuter's parser of the C++ functions that plain_calls gave plain names
    (`Vu0::Vec::Of` as Vu0__Vec__Of), with the return type their class declares: its randomizer
    fails on a call to a function it has never seen. permuter_compile.py drops them again."""
    stubs = []
    for alias, real in aliases:
        parts = real.split("::")
        if alias == "make_" + real and len(parts) == 1:
            stubs.append("%s %s();" % (real, alias))        # a constructor call, `T(a)`
            continue
        if len(parts) < 2:
            continue
        cls = class_body(item_texts, parts[0])
        if cls is None:
            continue
        found = static_returns(cls, parts[0] + "__", {})
        rets = {r.replace("const ", "") for r in found.get(alias, ())}
        if not rets:
            continue
        if len(rets) > 1:
            # Overloaded (u128 and Vec): the Vec ones where the function declares a Vec, else the
            # plain ones; only the parser's guess at the call's type, the compiler sees the real one.
            vec = parts[0] + "__Vec"
            rets = {"Vec"} if "Vec" in rets and re.search(r"\b%s\b" % vec, body) else {sorted(rets - {"Vec"} or rets)[0]}
        ret = rets.pop()
        if ret in ("Vec",) and parts[0] + "__" + ret in {a for a, _ in aliases}:
            ret = parts[0] + "__" + ret
        stubs.append("%s %s();" % (ret, alias))
    for t in sorted(set(re.findall(r"\bpermuter_ctor_(\w+)\s*\(", body))):
        stubs.append("%s permuter_ctor_%s();" % (t, t))       # `T x(a);`, which direct_inits wrote as a call
    for name, decl in BUILTINS.items():
        if name in body:
            stubs.append(decl)
    return stubs


def isolate(text, func, visible=True):
    """The unit with everything the permuter's C parser cannot read, or need, inside PERM_IGNORE:
    all but FUNC's definition and plain C typedefs. Our C++ (classes with bases and methods,
    references, templates) then reaches the compiler untouched."""
    tags = {m.group(2) for m in STRUCT.finditer(text)}
    out, views = [], {}
    for item in items(text):
        stripped = item.strip()
        if not stripped:
            out.append(item)
        elif re.search(r"\b%s\s*\(" % func, stripped) and stripped.endswith("}"):
            body, aliases = plain_calls(min_max_calls(item), tags)
            out.extend("\ntypedef struct %s %s;\n" % (t, t) for t in scoped_types(body, aliases))
            if visible:
                out.extend("\n%s\n" % stub for stub in alias_stubs(items(text), aliases, body))
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
        elif visible and plain_c_item(stripped, tags):
            out.append("\n%s\n" % stripped)
            head = STRUCT_HEAD.match(stripped)
            if head:
                views[head.group(1)] = stripped
        elif visible and STRUCT_HEAD.match(stripped) and struct_view(stripped, views, tags):
            # The permuter's parser reads a plain view of the struct (its fields: no attribute, no
            # method, the fields of a base class first), and permuter_compile.py puts the original
            # back, as for u128's typedef.
            name = STRUCT_HEAD.match(stripped).group(1)
            escaped = stripped.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n")
            out.append("\nPERM_IGNORE(static const char permuter_struct_%s[] = \"%s\";)\n" % (name, escaped))
            out.append("\n%s\n" % views[name])
        else:
            out.append("\nPERM_IGNORE(%s)\n" % stripped)
    return "".join(out)


EXT = ROOT / "tools" / "ext" / "decomp-permuter"
VALIDATE = """
import sys
sys.path.insert(0, %r)
from src.perm.parse import perm_parse
from src.perm.eval import perm_evaluate_one
from src.candidate import Candidate
source, state = perm_evaluate_one(perm_parse(open(sys.argv[1]).read()))
Candidate._cached_shared_ast(source, sys.argv[2])
"""


def readable_by_permuter(base_c, func):
    """Whether decomp-permuter's own parser reads base_c and finds FUNC (None when it is not set up:
    tools/ext/venv). The plain views of structs, and the declarations, are only worth it then."""
    py = ROOT / "tools" / "ext" / "venv" / "bin" / "python"
    if not py.exists() or not EXT.exists():
        return None
    proc = subprocess.run([str(py), "-c", VALIDATE % str(EXT), str(base_c), func], capture_output=True, text=True)
    return proc.returncode == 0 or (proc.stderr.strip().splitlines() or ["?"])[-1:]


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
    header = "\n".join(lines) + "\n"
    (dest / "base.c").write_text(header + isolate(text, func))
    if readable_by_permuter(dest / "base.c", func) not in (True, None):
        # The visible declarations are an aid, not a need: without them, the old base.c.
        print("note: the permuter cannot read the visible declarations (%s); everything ignored"
              % readable_by_permuter(dest / "base.c", func)[0][:100])
        (dest / "base.c").write_text(header + isolate(text, func, visible=False))
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
