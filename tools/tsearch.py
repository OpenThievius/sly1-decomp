# SPDX-License-Identifier: AGPL-3.0-or-later
"""Search the plain C++ rewrites of a near miss, transform by transform, for retail's bytes.

    python3 tools/tsearch.py FUNC [--file nonmatching/FUNC.cpp] [--minutes 20] [--jobs 3]
                             [--beam 6] [--depth 4] [--only NAME,...] [--skip NAME,...]
    python3 tools/tsearch.py FUNC --list [--only NAME,...]      the rewrites of one step, no compile
    python3 tools/tsearch.py --transforms                        the library, one line each

decomp-permuter (tools/permute_night.py) mutates at random and mostly writes what nobody would;
tools/permute.py only reorders marked lines. This tool searches a defined space instead: a
library of rewrites that keep the function's meaning and that a programmer plausibly wrote, each
applied at every place it fits (`--transforms` lists them): loop forms, if/else against a
ternary or an early return, switch against an if chain, compound assignments, statement order
within the dependences, where and in what order the locals are declared, a local's integer type
and const, a parameter's or local's integer width (with a cast back where it is narrowed), a pointer local against a reference, a call's arguments named first or a temporary
written in place, an index walk against a pointer walk, a single-expression helper of the file
or its headers written in place or called, VU0 helpers of include/vu0.h against their
alternatives, commuted operands and zero tests.

The source forms that matched in November 2026 are rewrites too (docs/toolchain/*.md has the
mechanism of each): a constant named by a local of a loop body or of the function, and a named
constant written as its literal (named-constant); a local that only carries an expression removed
and the expression written at each use, and a repeated expression named once (repeat-expression);
a struct's single-expression member function called on an object written in place, a cast of a
global array read as its elements, and back (helpers); a parameter moved past parameters of the
other register file, every declaration and call in the file following (param-order); a callee's
prototype between void and s32 where its result is unused (callee-return); two locals whose lives
do not overlap merged into one, one local split at an assignment that starts a new life
(reuse-variable); a test of a variable both arms of an if/else set written in each arm, and back
(test-in-each-arm); a switch's arms and labels reordered, a variable set before a switch set in
each arm, and back (case-order); `a = v; b = v;` as `a = b = v;`, and back (chained-assignment); a
VU0 vector stored through Vu0::Q against through a structure cast (struct-store). A candidate that
changes a parameter's order or a callee's declaration names, in its header, the declarations and
calls in the other files of src/ that would have to follow.

The search is a beam: every rewrite of the start is compiled and scored, the best --beam
candidates (distinct code first) are rewritten again, to --depth steps or --minutes. Each
candidate is compiled the way the function lands (check.source_for: its src/ file's compiler and
flags) and compared as tools/check.py compares it; the score is regdiff.py's: retail's
instructions that do not line up once registers are set aside (plus any difference in size),
then the words that differ. Every improvement is written to build/tsearch/FUNC/ (best_NN.cpp,
the near miss with the function rewritten, its chain of rewrites in a comment at the top), an
EXACT one as EXACT.cpp, and log.tsv has every candidate's score and chain.

The rewrites only produce plain C++ (AGENTS.md, "Matching rules"): `forbidden()` rejects any
candidate with more inline assembly, `register`, `volatile`, `do { } while (0)`, goto, empty
statement or self-assignment than its start, or with a local that is never read, or a new array
local; the unit tests (tests/test_tsearch.py) run the whole library over the near misses and
check that none does. Dependences are judged on the text (a local by name; memory by field name,
a global by name, anything through `*` or a call as everything), which is conservative about
memory and blind to aliasing by type: an EXACT candidate is retail's bytes whatever the judgement,
and is a match only once tools/check.py and tools/build.py say so. Read each before landing it.

--beam 0 keeps every code a step reaches (through its first two texts): the closure of the
library to --depth, an exhaustive answer for a small function. Ranking a step's
candidates by the compiler's dumps (tools/globalalloc.py, tools/sched1.py) before compiling them
is not done here: a promising candidate is read with those tools by hand.
"""

import argparse
import concurrent.futures
import hashlib
import os
import re
import sys
import tempfile
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
OUT = ROOT / "build" / "tsearch"

# ---------------------------------------------------------------------------------------------
# Tokens

OPS = sorted("""<<= >>= <?= >?= ... -> ++ -- << >> <= >= == != && || += -= *= /= %= &= |= ^= :: <? >?
             + - * / % & | ^ ! ~ < > = ? : ; , . ( ) [ ] { } #""".split(), key=len, reverse=True)
TOKEN = re.compile(r"""
    (?P<ws>\s+)
  | (?P<comment>//[^\n]*|/\*.*?\*/)
  | (?P<str>"(?:\\.|[^"\\\n])*")
  | (?P<chr>'(?:\\.|[^'\\\n])+')
  | (?P<num>(?:0[xX][0-9A-Fa-f]+|\d+\.?\d*(?:[eE][-+]?\d+)?|\.\d+(?:[eE][-+]?\d+)?)[uUlLfF]*)
  | (?P<id>[A-Za-z_]\w*)
  | (?P<op>""" + "|".join(re.escape(o) for o in OPS) + r""")
""", re.S | re.X)


class Tok:
    __slots__ = ("kind", "text", "start", "end")

    def __init__(self, kind, text, start, end):
        self.kind, self.text, self.start, self.end = kind, text, start, end

    def __repr__(self):
        return "Tok(%s %r)" % (self.kind, self.text)


def tokenize(text, start=0, end=None):
    """Every token of a C++ text (from `start` to `end`) but whitespace, comments and preprocessor
    lines (a `#` at a line's start runs to the line's end, continuations included)."""
    out, i, n = [], start, len(text) if end is None else end
    while i < n:
        if text[i] == "#" and text[text.rfind("\n", 0, i) + 1:i].strip() == "":
            j = i
            while True:
                j = text.find("\n", j)
                if j < 0:
                    j = n
                    break
                if text[j - 1] != "\\":
                    break
                j += 1
            i = j
            continue
        m = TOKEN.match(text, i, n)
        if not m:
            raise ParseError("cannot tokenize at %r" % text[i:i + 20])
        kind = m.lastgroup
        if kind not in ("ws", "comment"):
            out.append(Tok(kind, m.group(), m.start(), m.end()))
        i = m.end()
    return out


class ParseError(Exception):
    pass


BUILTIN_TYPES = {"void", "char", "short", "int", "long", "float", "double", "signed", "unsigned", "bool",
                 "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "s128", "u128", "f32", "f64"}
QUALIFIERS = {"const", "static", "struct", "class", "union", "enum", "volatile", "register", "inline"}
KEYWORDS = {"if", "else", "for", "while", "do", "switch", "case", "default", "return", "break", "continue",
            "goto", "sizeof", "new", "delete", "this", "operator", "asm", "__asm__", "typedef"}
INT_TYPES = ["s32", "u32", "s16", "u16", "s8", "u8", "int"]
PRIMARY_KINDS = ("id", "num", "str", "chr", "paren", "call", "index", "member", "postfix")

# ---------------------------------------------------------------------------------------------
# Expressions

BINARY = {",": 1, "||": 4, "&&": 5, "|": 6, "^": 7, "&": 8, "==": 9, "!=": 9,
          "<": 10, ">": 10, "<=": 10, ">=": 10, "<?": 10, ">?": 10, "<<": 11, ">>": 11,
          "+": 12, "-": 12, "*": 13, "/": 13, "%": 13}
ASSIGN = {"=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "<?=", ">?="}
UNARY = {"-", "+", "!", "~", "*", "&", "++", "--"}


class Expr:
    """A node: kind, op, children, and its token range [s, e) in the unit's tokens."""
    __slots__ = ("kind", "op", "kids", "s", "e", "extra")

    def __init__(self, kind, op, kids, s, e, extra=None):
        self.kind, self.op, self.kids, self.s, self.e, self.extra = kind, op, kids, s, e, extra

    def walk(self):
        yield self
        for k in self.kids:
            if k is not None:
                yield from k.walk()

    def __repr__(self):
        return "Expr(%s %s)" % (self.kind, self.op)


class ExprParser:
    def __init__(self, unit, s, e):
        self.u, self.t, self.i, self.end = unit, unit.toks, s, e

    def peek(self, k=0):
        j = self.i + k
        return self.t[j].text if j < self.end else None

    def take(self, want=None):
        if self.i >= self.end:
            raise ParseError("unexpected end of expression")
        tok = self.t[self.i]
        if want is not None and tok.text != want:
            raise ParseError("expected %r, found %r" % (want, tok.text))
        self.i += 1
        return tok

    def parse(self, min_bp=1):
        s = self.i
        lhs = self.unary()
        while True:
            op = self.peek()
            if op is None:
                break
            if op in ASSIGN:
                if 2 < min_bp:
                    break
                self.take()
                rhs = self.parse(2)
                lhs = Expr("assign", op, [lhs, rhs], s, self.i)
            elif op == "?":
                if 3 < min_bp:
                    break
                self.take()
                mid = self.parse(1)
                self.take(":")
                rhs = self.parse(2)
                lhs = Expr("ternary", "?", [lhs, mid, rhs], s, self.i)
            elif op in BINARY and self.t[self.i].kind == "op":
                bp = BINARY[op]
                if bp < min_bp:
                    break
                self.take()
                rhs = self.parse(bp + 1)
                lhs = Expr("binary", op, [lhs, rhs], s, self.i)
            else:
                break
        return lhs

    def unary(self):
        s = self.i
        op = self.peek()
        if op is None:
            raise ParseError("missing operand")
        tok = self.t[self.i]
        if tok.kind == "op" and op in UNARY:
            self.take()
            return Expr("unary", op, [self.unary()], s, self.i)
        if op == "sizeof":
            self.take()
            if self.peek() == "(" and self.type_ahead(self.i + 1):
                close = self.u.match(self.i)
                self.i = close + 1
                return Expr("sizeof", "sizeof", [], s, self.i)
            return Expr("sizeof", "sizeof", [self.unary()], s, self.i)
        if op == "(":
            close = self.u.match(self.i)
            if close >= self.end:
                raise ParseError("unbalanced (")
            if self.type_ahead(self.i + 1, close) and close + 1 < self.end and self.starts_operand(close + 1):
                self.i = close + 1
                inner = self.unary()
                return Expr("cast", "cast", [inner], s, self.i, extra=(s + 1, close))
            self.take("(")
            inner = self.parse(1)
            self.take(")")
            return self.postfix(Expr("paren", "()", [inner], s, self.i))
        return self.postfix(self.primary())

    def starts_operand(self, j):
        tok = self.t[j]
        if tok.kind in ("id", "num", "str", "chr"):
            return tok.text not in KEYWORDS or tok.text in ("sizeof", "this")
        return tok.text in ("(", "-", "+", "!", "~", "*", "&", "++", "--")

    def type_ahead(self, j, close=None):
        """Whether tokens j..close (a parenthesised group) name a type."""
        if close is None:
            close = self.u.match(j - 1)
        words = self.t[j:close]
        if not words:
            return False
        if any(w.kind not in ("id", "op") or (w.kind == "op" and w.text not in ("*", "&", "::"))
               for w in words):
            return False
        names = [w.text for w in words if w.kind == "id" and w.text not in QUALIFIERS]
        if not names:
            return False
        return names[0] in BUILTIN_TYPES or names[0] in self.u.types or (
            words[-1].text in ("*", "&") and names[0] not in self.u.locals_hint)

    def primary(self):
        s = self.i
        tok = self.take()
        if tok.kind == "id":
            if tok.text in KEYWORDS and tok.text != "this":
                raise ParseError("keyword %s in an expression" % tok.text)
            while self.peek() == "::":
                self.take()
                self.take()
            return Expr("id", self.u.text_of(s, self.i), [], s, self.i)
        if tok.kind == "op" and tok.text == "::":
            self.take()
            return Expr("id", self.u.text_of(s, self.i), [], s, self.i)
        if tok.kind == "str":
            while self.peek() is not None and self.t[self.i].kind == "str":
                self.take()
            return Expr("str", None, [], s, self.i)
        if tok.kind in ("num", "chr"):
            return Expr(tok.kind, tok.text, [], s, self.i)
        raise ParseError("unexpected %r" % tok.text)

    def postfix(self, e):
        while True:
            op = self.peek()
            s = e.s
            if op == "(":
                self.take()
                args = []
                if self.peek() != ")":
                    while True:
                        args.append(self.parse(2))
                        if self.peek() == ",":
                            self.take()
                            continue
                        break
                self.take(")")
                e = Expr("call", "()", [e] + args, s, self.i)
            elif op == "[":
                self.take()
                idx = self.parse(1)
                self.take("]")
                e = Expr("index", "[]", [e, idx], s, self.i)
            elif op in (".", "->"):
                self.take()
                name = self.take()
                if name.kind != "id":
                    raise ParseError("member name expected")
                e = Expr("member", op, [e], s, self.i, extra=name.text)
            elif op in ("++", "--"):
                self.take()
                e = Expr("postfix", op, [e], s, self.i)
            else:
                return e


# ---------------------------------------------------------------------------------------------
# Statements


class Stmt:
    """kind: block if for while do switch return break continue goto label decl expr empty.
    s, e: its token range. parts: kind-specific (spans as (s, e) and child statements)."""
    __slots__ = ("kind", "s", "e", "p")

    def __init__(self, kind, s, e, **parts):
        self.kind, self.s, self.e, self.p = kind, s, e, parts

    def children(self):
        for v in self.p.values():
            if isinstance(v, Stmt):
                yield v
            elif isinstance(v, list):
                for x in v:
                    if isinstance(x, Stmt):
                        yield x

    def walk(self):
        yield self
        for c in self.children():
            yield from c.walk()

    def __repr__(self):
        return "Stmt(%s)" % self.kind


class Unit:
    """A file's text, its tokens, and the definition of one function in it, parsed."""

    def __init__(self, text, func, base=None):
        """`base`, a Unit of the same file whose text differs only inside FUNC's definition,
        lends its file-scope facts (the type names, the definition's start)."""
        import version_src
        self.text, self.func = text, func
        if base is not None and text[:base.span[0]] == base.text[:base.span[0]] and \
                text[len(text) - (len(base.text) - base.span[1]):] == base.text[base.span[1]:]:
            cs, ce = base.span[0], base.span[1] + len(text) - len(base.text)
            self.types = base.types
        else:
            try:
                cs, ce = version_src.definition_span(text, func)
            except version_src.VersionSourceError as e:
                raise ParseError(str(e))
            self.types = set(BUILTIN_TYPES)
            for m in re.finditer(r"\b(?:struct|class|union|enum)\s+(\w+)", text):
                self.types.add(m.group(1))
            for m in re.finditer(r"\btypedef\b[^;]*?(\w+)\s*(?:\)\s*\([^;]*\))?\s*;", text):
                self.types.add(m.group(1))
            for m in re.finditer(r"\btypedef\b[^;(]*\(\s*\*\s*(\w+)\s*\)", text):
                self.types.add(m.group(1))
        self.span = (cs, ce)
        self._ids = None
        # Only the definition's own tokens: the rest of the file is read as text where needed.
        self.toks = tokenize(text, cs, ce)
        self._match = {}
        stack = []
        for i, t in enumerate(self.toks):
            if t.text in "([{" and t.kind == "op":
                stack.append(i)
            elif t.text in ")]}" and t.kind == "op":
                if stack:
                    self._match[stack.pop()] = i
        self.locals_hint = set()
        first = next(i for i, t in enumerate(self.toks) if t.start >= cs)
        self.open = next(i for i in range(first, len(self.toks)) if self.toks[i].text == "{")
        self.close = self.match(self.open)
        if self.toks[self.close].end != ce:
            raise ParseError("the definition's braces do not close where it ends")
        # The parameters: the last `(` group before the body.
        j = self.open - 1
        while j > first and self.toks[j].text != ")":
            j -= 1
        popen = next(k for k, v in self._match.items() if v == j)
        self.pspan = (popen + 1, j)
        self.params = self.split_decls(popen + 1, j)
        self.locals_hint = {p[2] for p in self.params}
        self.ret_type = self.text_of(first, popen - 1) if popen - 1 > first else ""
        self.body = self.block(self.open)
        self.decls = [st for st in self.body.walk() if st.kind == "decl"]
        for st in self.body.walk():
            if st.kind == "for" and st.p["init"] is not None:
                self.decls.append(st.p["init"])
        self.locals = {p[2] for p in self.params} | {st.p["name"] for st in self.decls if st.kind == "decl"}
        self.locals_hint = set(self.locals)
        self.addr_taken = self._addr_taken()

    # -- token helpers --------------------------------------------------------------------
    def match(self, i):
        if i not in self._match:
            raise ParseError("unbalanced %r" % self.toks[i].text)
        return self._match[i]

    def text_of(self, s, e):
        if e <= s:
            return ""
        return self.text[self.toks[s].start:self.toks[e - 1].end]

    def cstart(self, i):
        return self.toks[i].start

    def cend(self, i):
        return self.toks[i - 1].end

    def line_of(self, i):
        return self.text.count("\n", 0, self.toks[i].start) + 1

    def indent_at(self, i):
        pos = self.toks[i].start
        ls = self.text.rfind("\n", 0, pos) + 1
        m = re.match(r"[ \t]*", self.text[ls:pos])
        return m.group()

    def expr(self, s, e):
        p = ExprParser(self, s, e)
        x = p.parse(1)
        if p.i != e:
            raise ParseError("trailing tokens in %r" % self.text_of(s, e))
        return x

    # -- declarations ---------------------------------------------------------------------
    def decl_shape(self, s, e):
        """(type end, name index) when tokens s..e start a declaration, else None."""
        t = self.toks
        i = s
        while i < e and t[i].text in QUALIFIERS:
            i += 1
        if i >= e or t[i].kind != "id" or t[i].text in KEYWORDS:
            return None
        i += 1
        while i + 1 < e and t[i].text == "::" and t[i + 1].kind == "id":
            i += 2
        while i < e and t[i].text in ("*", "&", "const"):
            i += 1
        if i < e and t[i].kind == "id" and t[i].text not in KEYWORDS:
            nxt = t[i + 1].text if i + 1 < e else ";"
            if nxt in ("=", ";", "[", ",", "(", ")"):
                return i, i
        return None

    def split_decls(self, s, e):
        """Parameters: [(type text, start, name)] (unnamed ones get name None)."""
        out, i = [], s
        while i < e:
            j = i
            depth = 0
            while j < e and not (self.toks[j].text == "," and depth == 0):
                if self.toks[j].text in "([":
                    depth += 1
                elif self.toks[j].text in ")]":
                    depth -= 1
                j += 1
            shape = self.decl_shape(i, j) if j > i else None
            if shape:
                out.append((self.text_of(i, shape[1]), i, self.toks[shape[1]].text))
            elif j > i and self.text_of(i, j) not in ("void", "..."):
                out.append((self.text_of(i, j), i, None))
            i = j + 1
        return [p for p in out if p[2]]

    def decl(self, s, e, end):
        """A declaration statement s..e (e at its `;`)."""
        shape = self.decl_shape(s, e)
        ni = shape[1]
        j = ni + 1
        init = None
        ctor = None
        dims = None
        while j < e and self.toks[j].text == "[":
            k = self.match(j)
            dims = (j, k + 1) if dims is None else (dims[0], k + 1)
            j = k + 1
        if j < e and self.toks[j].text == "(":
            k = self.match(j)
            ctor = (j + 1, k)
            j = k + 1
        if j < e and self.toks[j].text == "=":
            k = j + 1
            depth = 0
            while k < e and not (self.toks[k].text == "," and depth == 0):
                if self.toks[k].text in "([{":
                    depth += 1
                elif self.toks[k].text in ")]}":
                    depth -= 1
                k += 1
            init = (j + 1, k)
            j = k
        multi = j < e
        return Stmt("decl", s, end, type=(s, ni), name=self.toks[ni].text, name_at=ni, init=init,
                    ctor=ctor, dims=dims, multi=multi)

    # -- statements ------------------------------------------------------------------------
    def block(self, i):
        close = self.match(i)
        items, j = [], i + 1
        while j < close:
            st = self.statement(j, close)
            items.append(st)
            j = st.e
        return Stmt("block", i, close + 1, items=items)

    def find_semi(self, i, limit):
        depth = 0
        while i < limit:
            tx = self.toks[i].text
            if tx in ("(", "[", "{"):
                i = self.match(i) + 1
                continue
            if tx == ";":
                return i
            i += 1
        raise ParseError("no ;")

    def statement(self, i, limit):
        t = self.toks
        tx = t[i].text
        if tx == "{":
            return self.block(i)
        if tx == ";":
            return Stmt("empty", i, i + 1)
        if tx == "if":
            c = self.match(i + 1)
            then = self.statement(c + 1, limit)
            other = None
            end = then.e
            if end < limit and t[end].text == "else":
                other = self.statement(end + 1, limit)
                end = other.e
            return Stmt("if", i, end, cond=(i + 2, c), then=then, other=other)
        if tx == "while":
            c = self.match(i + 1)
            body = self.statement(c + 1, limit)
            return Stmt("while", i, body.e, cond=(i + 2, c), body=body)
        if tx == "do":
            body = self.statement(i + 1, limit)
            if t[body.e].text != "while":
                raise ParseError("do without while")
            c = self.match(body.e + 1)
            return Stmt("do", i, c + 2, body=body, cond=(body.e + 2, c))
        if tx == "for":
            c = self.match(i + 1)
            a = self.find_semi(i + 2, c)
            b = self.find_semi(a + 1, c)
            init = None
            if a > i + 2:
                init = self.decl(i + 2, a, a) if self.decl_shape(i + 2, a) else Stmt("expr", i + 2, a, value=(i + 2, a))
            body = self.statement(c + 1, limit)
            return Stmt("for", i, body.e, init=init, init_span=(i + 2, a), cond=(a + 1, b), step=(b + 1, c), body=body)
        if tx == "switch":
            c = self.match(i + 1)
            body = self.statement(c + 1, limit)
            return Stmt("switch", i, body.e, cond=(i + 2, c), body=body)
        if tx in ("case", "default"):
            j = i + 1
            while t[j].text != ":":
                j += 1
            return Stmt("label", i, j + 1, value=(i + 1, j))
        if tx in ("break", "continue"):
            return Stmt(tx, i, i + 2)
        if tx == "return":
            semi = self.find_semi(i, limit)
            return Stmt("return", i, semi + 1, value=(i + 1, semi) if semi > i + 1 else None)
        if tx == "goto":
            semi = self.find_semi(i, limit)
            return Stmt("goto", i, semi + 1)
        if t[i].kind == "id" and i + 1 < limit and t[i + 1].text == ":" and tx not in KEYWORDS:
            return Stmt("label", i, i + 2, value=None)
        if tx in ("asm", "__asm__", "typedef") or (tx in ("struct", "class", "union", "enum") and
                                                   i + 2 < limit and t[i + 2].text in ("{", ":")):
            semi = self.find_semi(i, limit)
            return Stmt("opaque", i, semi + 1)
        semi = self.find_semi(i, limit)
        if self.decl_shape(i, semi):
            return self.decl(i, semi, semi + 1)
        return Stmt("expr", i, semi + 1, value=(i, semi))

    def _addr_taken(self):
        out = set()
        for i in range(self.open, self.close):
            t = self.toks[i]
            if t.text == "&" and i + 1 < self.close and self.toks[i + 1].text in self.locals:
                prev = self.toks[i - 1]
                if prev.kind == "op" and prev.text not in (")", "]") or prev.text in ("return",):
                    out.add(self.toks[i + 1].text)
        # A local of a class type used with `.` lives in memory (its address goes to its methods).
        for st in self.decls:
            if st.kind == "decl" and self.text_of(*st.p["type"]).split()[-1] not in BUILTIN_TYPES and \
                    not self.text_of(*st.p["type"]).endswith(("*", "&")):
                out.add(st.p["name"])
        return out


# ---------------------------------------------------------------------------------------------
# Effects: what a statement reads and writes, for the dependences.

ANY = ("*",)


class Eff:
    __slots__ = ("reads", "writes", "mr", "mw", "control")

    def __init__(self):
        self.reads, self.writes, self.mr, self.mw, self.control = set(), set(), set(), set(), False

    def add(self, o):
        self.reads |= o.reads
        self.writes |= o.writes
        self.mr |= o.mr
        self.mw |= o.mw
        self.control |= o.control


def escapes(st, in_loop=False, in_switch=False):
    """Whether control leaves a compound statement other than by its end: a return, a goto, a
    label, or a break or continue of an enclosing statement."""
    for c in st.children():
        k = c.kind
        if k in ("return", "goto", "label", "opaque") and not (k == "label" and in_switch):
            return True
        if k == "break" and not (in_loop or in_switch) or k == "continue" and not in_loop:
            return True
        if escapes(c, in_loop or k in ("for", "while", "do"), in_switch or k == "switch"):
            return True
    return False


def _mem_conflict(a, b):
    return any(x == ANY or y == ANY or x == y for x in a for y in b)


def conflict(a, b):
    return bool(a.writes & (b.reads | b.writes) or b.writes & a.reads
                or _mem_conflict(a.mw, b.mr | b.mw) or _mem_conflict(b.mw, a.mr))


class Effects:
    def __init__(self, unit, pure=()):
        self.u, self.pure = unit, set(pure)

    def name_key(self, name, eff, write=False):
        base = name.split("::")[-1]
        if name in self.u.locals and name not in self.u.addr_taken:
            (eff.writes if write else eff.reads).add(name)
        elif name in self.u.locals:
            (eff.mw if write else eff.mr).add(("g", name))
            eff.reads.add(name)
        elif base not in self.u.types and not base.isupper():
            (eff.mw if write else eff.mr).add(("g", name))

    def expr(self, x, eff=None):
        eff = eff or Eff()
        self._e(x, eff)
        return eff

    def _lvalue(self, x, eff, also_read):
        if x.kind == "paren":
            return self._lvalue(x.kids[0], eff, also_read)
        if x.kind == "id":
            self.name_key(x.op, eff, write=True)
            if also_read:
                self.name_key(x.op, eff)
            return
        if x.kind == "member":
            key = ("f", x.extra)
            eff.mw.add(key)
            if also_read:
                eff.mr.add(key)
            base = x.kids[0]
            if x.op == "." and base.kind == "id":
                self.name_key(base.op, eff, write=True)
                self.name_key(base.op, eff)
            else:
                self._e(base, eff)
            return
        if x.kind == "index":
            root = x.kids[0]
            key = ("g", root.op) if root.kind == "id" else ANY
            eff.mw.add(key)
            if also_read:
                eff.mr.add(key)
            if root.kind != "id":
                self._e(root, eff)
            elif root.op in self.u.locals:
                self.name_key(root.op, eff)
            self._e(x.kids[1], eff)
            return
        # *p, a cast lvalue, anything else
        eff.mw.add(ANY)
        if also_read:
            eff.mr.add(ANY)
        for k in x.kids:
            self._e(k.kids[0] if k.kind == "unary" and k.op == "*" else k, eff)

    def _e(self, x, eff):
        k = x.kind
        if k == "id":
            self.name_key(x.op, eff)
        elif k == "member":
            eff.mr.add(("f", x.extra))
            base = x.kids[0]
            if x.op == "." and base.kind == "id":
                self.name_key(base.op, eff)
            else:
                self._e(base, eff)
        elif k == "index":
            root = x.kids[0]
            eff.mr.add(("g", root.op) if root.kind == "id" else ANY)
            if root.kind != "id" or root.op in self.u.locals:
                self._e(root, eff)
            self._e(x.kids[1], eff)
        elif k == "unary" and x.op == "*":
            eff.mr.add(ANY)
            self._e(x.kids[0], eff)
        elif k == "unary" and x.op == "&":
            inner = x.kids[0]
            while inner.kind in ("member", "index", "paren"):
                if inner.kind == "index":
                    self._e(inner.kids[1], eff)
                inner = inner.kids[0]
            if inner.kind != "id":
                self._e(inner, eff)
            elif inner.op in self.u.locals:
                eff.reads.add(inner.op)     # not a read of its value, but it must stay in scope
        elif k in ("unary", "postfix") and x.op in ("++", "--"):
            self._lvalue(x.kids[0], eff, True)
        elif k == "assign":
            self._lvalue(x.kids[0], eff, x.op != "=")
            self._e(x.kids[1], eff)
        elif k == "call":
            callee = x.kids[0]
            name = callee.op if callee.kind == "id" else None
            if not (name and name.split("::")[-1] in self.pure):
                eff.mr.add(ANY)
                eff.mw.add(ANY)
            if callee.kind != "id":
                self._e(callee, eff)
            for a in x.kids[1:]:
                self._e(a, eff)
        else:
            for kid in x.kids:
                if kid is not None:
                    self._e(kid, eff)

    def stmt(self, st):
        """A statement's effects; one this parser cannot read is fixed in place (control)."""
        try:
            return self._stmt(st)
        except ParseError:
            eff = Eff()
            eff.control = True
            return eff

    def _stmt(self, st):
        eff = Eff()
        u = self.u
        k = st.kind
        if k == "decl":
            eff.writes.add(st.p["name"])
            for part in ("init", "ctor"):
                span = st.p[part]
                if span and span[1] > span[0]:
                    self._e(u.expr(*span), eff)
            if st.p["name"] in u.addr_taken:
                eff.mw.add(("g", st.p["name"]))
        elif k == "expr":
            self._e(u.expr(*st.p["value"]), eff)
        elif k in ("return", "break", "continue", "goto", "label", "opaque"):
            eff.control = True
            if k == "return" and st.p.get("value"):
                self._e(u.expr(*st.p["value"]), eff)
        elif k == "empty":
            pass
        else:
            for part in ("cond", "step"):
                span = st.p.get(part)
                if span and span[1] > span[0]:
                    self._e(u.expr(*span), eff)
            if k == "switch":
                eff.control = True
            for c in st.children():
                eff.add(self._stmt(c))
            eff.control = escapes(st)
        return eff


# ---------------------------------------------------------------------------------------------
# Rewrites. Each is a generator over a Unit, yielding (label, edits); an edit is (start, end,
# replacement) in characters of the unit's text.


class Ctx:
    """What the rewrites share: the unit, its effects, the file's helpers and prototypes."""

    def __init__(self, unit, path=None):
        self.u = unit
        self.headers = _header_texts(unit.text, path)
        self.helpers = find_helpers(unit.text, path)
        self.methods = find_methods(unit.text, path)
        pure = {n for n, h in self.helpers.items() if h["pure"]}
        self.eff = Effects(unit, pure)
        self.protos = find_prototypes(unit.text, path)

    def label(self, name, i, what=""):
        return "%s@%d%s" % (name, self.u.line_of(i), (" " + what) if what else "")


def short(text, n=40):
    text = " ".join(text.split())
    return text if len(text) <= n else text[:n - 3] + "..."


def apply_edits(text, edits):
    for s, e, r in sorted(edits, key=lambda x: (x[0], x[1]), reverse=True):
        text = text[:s] + r + text[e:]
    return text


def blocks(u):
    for st in u.body.walk():
        if st.kind == "block":
            yield st


def simple_rvalue(x):
    """No side effects: no call, assignment or increment."""
    return not any(n.kind in ("call", "assign") or n.op in ("++", "--") and n.kind in ("unary", "postfix")
                   for n in x.walk())


def wrap(u, x):
    t = u.text_of(x.s, x.e)
    return t if x.kind in PRIMARY_KINDS else "(" + t + ")"


def has_tok(u, st, words):
    return any(u.toks[i].text in words for i in range(st.s, st.e))


def reindent(text, old, new):
    return "\n".join((new + l[len(old):]) if l.startswith(old) else l for l in text.split("\n"))


def inner_lines(u, st, ind):
    """A statement as the lines of a block's body indented by `ind`."""
    if st.kind == "block":
        if st.e - st.s <= 2:
            return ""
        first = st.p["items"][0]
        old = u.indent_at(first.s)
        return reindent(u.text[u.toks[first.s].start:u.cend(st.e - 1)], old, ind).lstrip()
    return u.text_of(st.s, st.e)


def t_reorder(ctx):
    """Move a statement up or down its block past statements it does not depend on."""
    u = ctx.u
    for b in blocks(u):
        items = b.p["items"]
        try:
            effs = [ctx.eff.stmt(st) for st in items]
        except ParseError:
            continue
        for k, st in enumerate(items):
            if effs[k].control or st.kind in ("empty",):
                continue
            for direction in (-1, 1):
                j = k
                while True:
                    j2 = j + direction
                    if not 0 <= j2 < len(items) or abs(j2 - k) > 8:
                        break
                    if effs[j2].control or conflict(effs[k], effs[j2]):
                        break
                    j = j2
                    order = list(range(len(items)))
                    order.pop(k)
                    order.insert(j, k)
                    lo, hi = min(k, j), max(k, j)
                    edits = [(u.cstart(items[i].s), u.cend(items[i].e), u.text_of(items[order[i]].s, items[order[i]].e))
                             for i in range(lo, hi + 1)]
                    yield ctx.label("reorder", st.s, "%+d" % (j - k)), edits


def _continues(u, st):
    """Whether a loop body holds a continue of its own loop (not of a nested one)."""
    for s in st.walk():
        if s.kind == "continue":
            return True
    return False


def t_loops(ctx):
    """for into while, while into for, a loop into a guarded do-while (or a bare one when its
    first test is known true)."""
    u = ctx.u
    for b in blocks(u):
        items = b.p["items"]
        for k, st in enumerate(items):
            if st.kind not in ("for", "while"):
                continue
            ind = u.indent_at(st.s)
            body = st.p["body"]
            inner = ind + "    "
            cond = u.text_of(*st.p["cond"]) or "1"
            if st.kind == "for":
                init_s, init_e = st.p["init_span"]
                init = u.text_of(init_s, init_e)
                step = u.text_of(*st.p["step"])
                if _continues(u, body):
                    continue
                stepl = ("\n" + inner + step + ";") if step else ""
                pre = (init + ";\n" + ind) if init else ""
                text = "%swhile (%s) {\n%s%s%s\n%s}" % (pre, cond, inner, inner_lines(u, body, inner), stepl, ind)
                yield ctx.label("for-to-while", st.s), [(u.cstart(st.s), u.cend(st.e), text)]
                try:
                    cx = u.expr(*st.p["cond"]) if cond != "1" else None
                except ParseError:
                    continue
                if cx is None or not simple_rvalue(cx):
                    continue
                if _known_true(u, st.p["init"], cx):
                    loop = "do {\n%s%s%s\n%s} while (%s);" % (inner, inner_lines(u, body, inner), stepl, ind, cond)
                else:
                    deep = inner + "    "
                    loop = "if (%s) {\n%sdo {\n%s%s%s\n%s} while (%s);\n%s}" % (
                        cond, inner, deep, inner_lines(u, body, deep), stepl.replace(inner, deep), inner, cond, ind)
                yield ctx.label("for-to-do", st.s), [(u.cstart(st.s), u.cend(st.e), pre + loop)]
            else:
                yield ctx.label("while-to-for", st.s), [(u.cstart(st.s), u.cend(st.p["cond"][1] + 1), "for (; %s; )" % cond)]
                # init before and step at the end of the body: a full for
                if k > 0 and items[k - 1].kind in ("expr", "decl") and body.kind == "block" and body.p["items"] \
                        and body.p["items"][-1].kind == "expr" and not _continues(u, body):
                    prev, last = items[k - 1], body.p["items"][-1]
                    pname = prev.p.get("name") or _assigned_name(u, prev)
                    lname = _assigned_name(u, last)
                    if pname and pname == lname and re.search(r"\b%s\b" % re.escape(pname), cond):
                        rest = body.p["items"][:-1]
                        btxt = "\n".join(inner + u.text_of(x.s, x.e) if x is not rest[0] else u.text_of(x.s, x.e)
                                         for x in rest) if rest else ""
                        btxt = u.text[u.cstart(rest[0].s):u.cend(rest[-1].e)] if rest else ""
                        text = "for (%s; %s; %s) {\n%s%s\n%s}" % (
                            u.text_of(prev.s, prev.e - 1), cond, u.text_of(last.s, last.e - 1),
                            inner, btxt.lstrip(), ind)
                        yield ctx.label("while-to-for", st.s, "full"), [
                            (u.cstart(prev.s), u.cend(st.e), text)]
                try:
                    cx = u.expr(*st.p["cond"])
                except ParseError:
                    continue
                if simple_rvalue(cx) and not _continues(u, body):
                    text = "if (%s) {\n%sdo {\n%s    %s\n%s} while (%s);\n%s}" % (
                        cond, inner, inner, inner_lines(u, body, inner + "    "), inner, cond, ind)
                    yield ctx.label("while-to-do", st.s), [(u.cstart(st.s), u.cend(st.e), text)]


def _known_true(u, init, cx):
    """A loop `i = A; i < B` (or !=) with constants A < B: its first test always passes."""
    if init is None or cx.kind != "binary" or cx.op not in ("<", "!=", "<="):
        return False
    a = cx.kids[0]
    b = cx.kids[1]
    if a.kind != "id" or b.kind != "num":
        return False
    if init.kind == "decl" and init.p["name"] == a.op and init.p["init"]:
        val = u.text_of(*init.p["init"])
    elif init.kind == "expr":
        m = re.match(r"^\s*%s\s*=\s*(\S+)\s*$" % re.escape(a.op), u.text_of(*init.p["value"]))
        val = m.group(1) if m else None
    else:
        val = None
    try:
        return val is not None and int(val, 0) < int(b.op.rstrip("uUlL"), 0)
    except ValueError:
        return False


def _assigned_name(u, st):
    if st.kind != "expr":
        return None
    try:
        x = u.expr(*st.p["value"])
    except ParseError:
        return None
    if x.kind in ("assign", "postfix", "unary") and x.kids and x.kids[0].kind == "id" and \
            (x.kind == "assign" or x.op in ("++", "--")):
        return x.kids[0].op
    return None


def _single(st):
    """The one statement of a branch (a block of one, or the statement)."""
    if st is None:
        return None
    if st.kind == "block":
        return st.p["items"][0] if len(st.p["items"]) == 1 else None
    return st


def _assign_of(u, st):
    if st is None or st.kind != "expr":
        return None
    x = u.expr(*st.p["value"])
    return x if x.kind == "assign" and x.op == "=" else None


NEGATE = {"==": "!=", "!=": "=="}


INVERT = {"<": ">=", ">=": "<", ">": "<=", "<=": ">"}


def negate(u, x):
    """The negated condition: == and != swapped, a comparison with an integer literal inverted
    (not a float's: !(a < b) and a >= b differ there), else !(x)."""
    if x.kind == "binary" and x.op in INVERT and any(
            k.kind == "num" and not re.search(r"[.fFeE]", k.op) or k.kind == "num" and k.op.lower().startswith("0x")
            for k in x.kids):
        return "%s %s %s" % (u.text_of(x.kids[0].s, x.kids[0].e), INVERT[x.op], u.text_of(x.kids[1].s, x.kids[1].e))
    if x.kind == "binary" and x.op in NEGATE:
        return "%s %s %s" % (u.text_of(x.kids[0].s, x.kids[0].e), NEGATE[x.op], u.text_of(x.kids[1].s, x.kids[1].e))
    if x.kind == "unary" and x.op == "!":
        inner = x.kids[0]
        return u.text_of(inner.kids[0].s, inner.kids[0].e) if inner.kind == "paren" else u.text_of(inner.s, inner.e)
    return "!" + wrap(u, x)


def t_conditionals(ctx):
    """if/else of one assignment or return against a ternary; an assignment then a conditional
    one against a ternary; branches swapped under the negated condition; an early return against
    an else, and against wrapping the rest in the negated if."""
    u = ctx.u
    void = u.ret_type.split()[-1:] == ["void"] if u.ret_type else False
    for b in blocks(u):
        items = b.p["items"]
        for k, st in enumerate(items):
            try:
                yield from _conditional_at(ctx, u, b, items, k, st, void)
            except ParseError:
                continue


def _conditional_at(ctx, u, b, items, k, st, void):
    ind = u.indent_at(st.s)
    if st.kind == "if":
        cx = u.expr(*st.p["cond"])
        cond = u.text_of(*st.p["cond"])
        then, other = st.p["then"], st.p["other"]
        a, c = _single(then), _single(other)
        xa, xc = _assign_of(u, a), _assign_of(u, c)
        if xa is not None and xc is not None and u.text_of(xa.kids[0].s, xa.kids[0].e) == u.text_of(xc.kids[0].s, xc.kids[0].e):
            text = "%s = %s ? %s : %s;" % (u.text_of(xa.kids[0].s, xa.kids[0].e), wrap(u, cx) if cx.kind in ("ternary", "assign") else cond,
                                         u.text_of(xa.kids[1].s, xa.kids[1].e), u.text_of(xc.kids[1].s, xc.kids[1].e))
            yield ctx.label("if-to-ternary", st.s), [(u.cstart(st.s), u.cend(st.e), text)]
        if a is not None and c is not None and a.kind == "return" and c.kind == "return" and a.p["value"] and c.p["value"]:
            text = "return %s ? %s : %s;" % (cond, u.text_of(*a.p["value"]), u.text_of(*c.p["value"]))
            yield ctx.label("if-to-ternary", st.s, "return"), [(u.cstart(st.s), u.cend(st.e), text)]
        if other is not None and other.kind != "if":
            text = "if (%s) %s else %s" % (negate(u, cx), u.text_of(other.s, other.e), u.text_of(then.s, then.e))
            yield ctx.label("swap-branches", st.s), [(u.cstart(st.s), u.cend(st.e), text)]
        # x = b; if (c) x = a;  ->  x = c ? a : b;
        if other is None and xa is not None and k > 0:
            prev = items[k - 1]
            lhs = u.text_of(xa.kids[0].s, xa.kids[0].e)
            px = None
            if prev.kind == "expr":
                px = _assign_of(u, prev)
                if px is not None and u.text_of(px.kids[0].s, px.kids[0].e) == lhs and simple_rvalue(px.kids[1]) \
                        and not re.search(r"\b%s\b" % re.escape(lhs), cond):
                    text = "%s = %s ? %s : %s;" % (lhs, cond, u.text_of(xa.kids[1].s, xa.kids[1].e), u.text_of(px.kids[1].s, px.kids[1].e))
                    yield ctx.label("if-to-ternary", st.s, "default"), [(u.cstart(prev.s), u.cend(st.e), text)]
            elif prev.kind == "decl" and prev.p["name"] == lhs and prev.p["init"] and not prev.p["multi"] \
                    and not re.search(r"\b%s\b" % re.escape(lhs), cond):
                init = u.text_of(*prev.p["init"])
                text = "%s %s = %s ? %s : %s;" % (u.text_of(*prev.p["type"]), lhs, cond, u.text_of(xa.kids[1].s, xa.kids[1].e), init)
                yield ctx.label("if-to-ternary", st.s, "default"), [(u.cstart(prev.s), u.cend(st.e), text)]
        # early returns
        ends = _ends_in_return(then)
        rest = items[k + 1:]
        if ends and other is None and rest and b is not None:
            body = u.text[u.cstart(rest[0].s):u.cend(rest[-1].e)]
            text = "%s else {\n%s    %s\n%s}" % (u.text_of(st.s, st.e), ind, reindent(body, ind, ind + "    "), ind)
            yield ctx.label("else-after-return", st.s), [(u.cstart(st.s), u.cend(rest[-1].e), text)]
        if ends and other is not None and other.kind == "block":
            text = "%s\n%s%s" % (u.text_of(st.s, then.e), ind, reindent(inner_lines(u, other, ind), ind + "    ", ind))
            yield ctx.label("drop-else", st.s), [(u.cstart(st.s), u.cend(st.e), text)]
        if void and b is u.body and k == len(items) - 1 and other is None:
            # if (c) { S }  at the end  ->  if (!c) return; S
            text = "if (%s) {\n%s    return;\n%s}\n%s%s" % (negate(u, cx), ind, ind, ind, reindent(inner_lines(u, then, ind), ind + "    ", ind))
            yield ctx.label("early-return", st.s), [(u.cstart(st.s), u.cend(st.e), text)]
        if void and b is u.body and other is None and a is not None and a.kind == "return" and a.p["value"] is None and rest:
            body = u.text[u.cstart(rest[0].s):u.cend(rest[-1].e)]
            text = "if (%s) {\n%s    %s\n%s}" % (negate(u, cx), ind, reindent(body, ind, ind + "    "), ind)
            yield ctx.label("wrap-rest", st.s), [(u.cstart(st.s), u.cend(rest[-1].e), text)]
    elif st.kind in ("expr", "decl", "return"):
        span = st.p["init"] if st.kind == "decl" else st.p.get("value")
        if not span:
            return
        x = u.expr(*span)
        if st.kind == "expr" and x.kind == "assign" and x.op == "=" and x.kids[1].kind == "ternary":
            lhs, t = u.text_of(x.kids[0].s, x.kids[0].e), x.kids[1]
            c, a, e = (u.text_of(n.s, n.e) for n in t.kids)
            text = "if (%s) {\n%s    %s = %s;\n%s} else {\n%s    %s = %s;\n%s}" % (c, ind, lhs, a, ind, ind, lhs, e, ind)
            yield ctx.label("ternary-to-if", st.s), [(u.cstart(st.s), u.cend(st.e), text)]
        elif st.kind == "decl" and x.kind == "ternary" and not st.p["multi"] and "&" not in u.text_of(*st.p["type"]):
            name, ty = st.p["name"], u.text_of(*st.p["type"])
            c, a, e = (u.text_of(n.s, n.e) for n in x.kids)
            text = "%s %s;\n%sif (%s) {\n%s    %s = %s;\n%s} else {\n%s    %s = %s;\n%s}" % (
                ty, name, ind, c, ind, name, a, ind, ind, name, e, ind)
            yield ctx.label("ternary-to-if", st.s), [(u.cstart(st.s), u.cend(st.e), text)]
            if simple_rvalue(x.kids[2]):
                text = "%s %s = %s;\n%sif (%s) {\n%s    %s = %s;\n%s}" % (ty, name, e, ind, c, ind, name, a, ind)
                yield ctx.label("ternary-to-if", st.s, "default"), [(u.cstart(st.s), u.cend(st.e), text)]
        elif st.kind == "return" and x.kind == "ternary":
            c, a, e = (u.text_of(n.s, n.e) for n in x.kids)
            text = "if (%s) {\n%s    return %s;\n%s}\n%sreturn %s;" % (c, ind, a, ind, ind, e)
            yield ctx.label("ternary-to-if", st.s, "return"), [(u.cstart(st.s), u.cend(st.e), text)]


def _ends_in_return(st):
    if st is None:
        return False
    if st.kind == "return":
        return True
    if st.kind == "block" and st.p["items"]:
        return st.p["items"][-1].kind == "return"
    return False


COMMUTATIVE = {"+", "*", "&", "|", "^"}
FLIP = {"<": ">", ">": "<", "<=": ">=", ">=": "<=", "==": "==", "!=": "!="}


def _stmt_exprs(u, st):
    for part in ("value", "init", "cond", "step", "ctor"):
        span = st.p.get(part)
        if isinstance(span, tuple) and span[1] > span[0]:
            yield part, u.expr(*span)


def _all_exprs(u):
    for st in u.body.walk():
        try:
            for part, x in _stmt_exprs(u, st):
                yield st, part, x
        except ParseError:
            continue


def t_compound(ctx):
    """x = x op y against x op= y; x++ against ++x, x += 1 and x = x + 1."""
    u = ctx.u
    for st, part, x in _all_exprs(u):
        if part not in ("value", "step") or st.kind not in ("expr", "for"):
            continue
        if x.kind == "assign" and x.op == "=" and x.kids[1].kind == "binary" and x.kids[1].op in BINARY \
                and x.kids[1].op not in (",", "&&", "||", "==", "!=", "<", ">", "<=", ">=", "<?", ">?"):
            lhs = u.text_of(x.kids[0].s, x.kids[0].e)
            if not simple_rvalue(x.kids[0]):
                continue
            rhs = x.kids[1]
            l, r = rhs.kids
            if u.text_of(l.s, l.e) == lhs:
                other = r
            elif rhs.op in COMMUTATIVE and u.text_of(r.s, r.e) == lhs:
                other = l
            else:
                continue
            o = u.text_of(other.s, other.e)
            if o in ("1",) and rhs.op in ("+", "-"):
                yield ctx.label("compound", x.s, "++"), [(u.cstart(x.s), u.cend(x.e), lhs + rhs.op * 2)]
            yield ctx.label("compound", x.s, rhs.op + "="), [(u.cstart(x.s), u.cend(x.e), "%s %s= %s" % (lhs, rhs.op, o))]
        elif x.kind == "assign" and x.op in ASSIGN and x.op not in ("=", "<?=", ">?="):
            lhs = u.text_of(x.kids[0].s, x.kids[0].e)
            if not simple_rvalue(x.kids[0]):
                continue
            op = x.op[:-1]
            r = x.kids[1]
            rt = u.text_of(r.s, r.e)
            if r.kind in ("binary", "ternary", "assign") and (r.kind != "binary" or BINARY[r.op] <= BINARY[op]):
                rt = "(" + rt + ")"
            yield ctx.label("expand", x.s, x.op), [(u.cstart(x.s), u.cend(x.e), "%s = %s %s %s" % (lhs, lhs, op, rt))]
            if rt == "1" and op in ("+", "-"):
                yield ctx.label("expand", x.s, op * 2), [(u.cstart(x.s), u.cend(x.e), lhs + op * 2)]
        elif x.kind in ("postfix", "unary") and x.op in ("++", "--"):
            v = u.text_of(x.kids[0].s, x.kids[0].e)
            op = x.op[0]
            alts = [("pre" if x.kind == "postfix" else "post", (x.op + v) if x.kind == "postfix" else (v + x.op)),
                    (op + "=1", "%s %s= 1" % (v, op))]
            for what, t in alts:
                yield ctx.label("incdec", x.s, what), [(u.cstart(x.s), u.cend(x.e), t)]


def t_operands(ctx):
    """Commuted operands of + * & | ^ == != (both free of side effects; parenthesised as needed),
    a comparison written the other way round (a < b as b > a)."""
    u = ctx.u
    seen = set()
    for st, part, top in _all_exprs(u):
        for x in top.walk():
            if x.kind != "binary" or (x.s, x.e) in seen:
                continue
            seen.add((x.s, x.e))
            if x.op not in COMMUTATIVE and x.op not in FLIP:
                continue
            l, r = x.kids
            if not (simple_rvalue(l) and simple_rvalue(r)):
                continue
            bp = BINARY[x.op]
            lt, rt = u.text_of(l.s, l.e), u.text_of(r.s, r.e)
            if l.kind == "binary" and BINARY[l.op] <= bp or l.kind in ("ternary", "assign"):
                lt = "(" + lt + ")"
            op = x.op if x.op in COMMUTATIVE else FLIP[x.op]
            yield ctx.label("commute", x.s, "`%s`" % short(u.text_of(x.s, x.e))), [(u.cstart(x.s), u.cend(x.e), "%s %s %s" % (rt, op, lt))]


ZERO = re.compile(r"^(0|0\.0*f?|0x0+|0[uUlL]*)$")


def t_zero_tests(ctx):
    """!e against e == 0, and a bare condition e against e != 0."""
    u = ctx.u
    conds = []
    for st, part, x in _all_exprs(u):
        if part == "cond" and st.kind != "switch":
            conds.append(x)
        for n in x.walk():
            if n.kind == "ternary":
                conds.append(n.kids[0])
            if n.kind == "binary" and n.op in ("&&", "||"):
                conds.extend(n.kids)
            if n.kind == "unary" and n.op == "!":
                conds.append(n)
    done = set()
    for c in conds:
        while c.kind == "paren":
            c = c.kids[0]
        if (c.s, c.e) in done:
            continue
        done.add((c.s, c.e))
        if c.kind == "binary" and c.op in ("&&", "||"):
            continue
        if c.kind == "unary" and c.op == "!":
            inner = c.kids[0]
            yield ctx.label("zero-test", c.s, "==0"), [(u.cstart(c.s), u.cend(c.e), "%s == 0" % wrap(u, inner))]
        elif c.kind == "binary" and c.op in ("==", "!=") and ZERO.match(u.text_of(c.kids[1].s, c.kids[1].e)):
            e = c.kids[0]
            t = wrap(u, e)
            yield ctx.label("zero-test", c.s, c.op), [(u.cstart(c.s), u.cend(c.e), ("!" + t) if c.op == "==" else t)]
        elif c.kind in PRIMARY_KINDS and c.kind not in ("num", "str"):
            yield ctx.label("zero-test", c.s, "!=0"), [(u.cstart(c.s), u.cend(c.e), "%s != 0" % u.text_of(c.s, c.e))]


def _uses(u, name, s=None, e=None):
    """The token indices where `name` (an identifier, not a member) appears in tokens s..e."""
    if u._ids is None:
        u._ids = {}
        for i, t in enumerate(u.toks):
            if t.kind == "id" and not (i > 0 and u.toks[i - 1].text in (".", "->", "::")):
                u._ids.setdefault(t.text, []).append(i)
    s = u.open if s is None else s
    e = u.close if e is None else e
    return [i for i in u._ids.get(name, ()) if s <= i < e]


def _assigned(u, name, after):
    """Whether `name` is assigned, incremented or has its address taken after token `after`."""
    for i in _uses(u, name, after + 1):
        nxt = u.toks[i + 1].text if i + 1 < len(u.toks) else ""
        prev = u.toks[i - 1].text
        if nxt in ASSIGN or nxt in ("++", "--") or prev in ("++", "--", "&"):
            return True
    return False


def _top_insert(u):
    """Where a declaration hoisted to the function's top goes: after its leading declarations."""
    items = u.body.p["items"]
    k = 0
    while k < len(items) and items[k].kind == "decl":
        k += 1
    if k == 0:
        return u.cend(u.open + 1), u.indent_at(items[0].s) if items else "    ", True
    return u.cend(items[k - 1].e), u.indent_at(items[k - 1].s), False


def t_decls(ctx):
    """A declaration hoisted to the top of the function (its initialiser left as an assignment
    in place), or to the top of its block; a declaration without initialiser sunk into its first
    assignment; a for loop's own declaration hoisted out."""
    u = ctx.u
    names = [st.p["name"] for st in u.decls if st.kind == "decl"] + [p[2] for p in u.params]
    pos, top_ind, first = _top_insert(u)
    for b in blocks(u):
        items = b.p["items"]
        for k, st in enumerate(items):
            if st.kind != "decl" or st.p["multi"] or st.p["ctor"] is not None:
                continue
            name, ty = st.p["name"], u.text_of(*st.p["type"])
            if names.count(name) != 1 or ty.endswith("&") or re.search(r"\bconst\s*$|^\s*(static\b|const\b)", ty) or \
                    st.p["dims"] and st.p["init"]:
                continue
            init = u.text_of(*st.p["init"]) if st.p["init"] else None
            if init is not None and init.lstrip().startswith("{"):
                continue
            decl = "%s %s%s;" % (ty, name, u.text_of(*st.p["dims"]) if st.p["dims"] else "")
            repl = "%s = %s;" % (name, init) if init is not None else ""
            # to the top of the function, unless it is there already
            if b is not u.body or any(items[i].kind != "decl" for i in range(k)):
                ins = ("\n" + top_ind + decl) if not first else ("\n" + top_ind + decl)
                if not (repl == "" and b is u.body):
                    yield ctx.label("hoist-decl", st.s, name), [(pos, pos, ins), _replace_stmt(u, st, repl)]
            # to the top of its own block
            if b is not u.body and k > 0 and any(items[i].kind != "decl" for i in range(k)):
                bpos = u.cend(b.s + 1)
                yield ctx.label("hoist-decl", st.s, name + " in block"), [
                    (bpos, bpos, "\n" + u.indent_at(st.s) + decl), _replace_stmt(u, st, repl)]
            # sink: `T x;` then the first statement `x = e;` of the same block
            if init is None and not st.p["dims"]:
                for j in range(k + 1, len(items)):
                    nxt = items[j]
                    if nxt.kind == "expr":
                        x = None
                        try:
                            x = _assign_of(u, nxt)
                        except ParseError:
                            pass
                        if x is not None and x.kids[0].kind == "id" and x.kids[0].op == name and \
                                not _uses(u, name, x.kids[1].s, x.kids[1].e):
                            text = "%s %s = %s;" % (ty, name, u.text_of(x.kids[1].s, x.kids[1].e))
                            yield ctx.label("sink-decl", st.s, name), [_replace_stmt(u, st, ""),
                                                                      (u.cstart(nxt.s), u.cend(nxt.e), text)]
                    if _uses(u, name, nxt.s, nxt.e):
                        break
            # sink a declaration into the one inner block that uses it
            if init is None and not st.p["dims"]:
                users = [i for i in _uses(u, name) if i != st.p["name_at"]]
                if users:
                    inner = _innermost_common(u, b, users)
                    if inner is not None and inner is not b:
                        ipos = u.cend(inner.s + 1)
                        first_in = inner.p["items"][0] if inner.p["items"] else None
                        iind = u.indent_at(first_in.s) if first_in else u.indent_at(st.s) + "    "
                        yield ctx.label("sink-decl", st.s, name + " into block"), [
                            _replace_stmt(u, st, ""), (ipos, ipos, "\n" + iind + decl)]
    for st in u.body.walk():
        if st.kind == "for" and st.p["init"] is not None and st.p["init"].kind == "decl":
            d = st.p["init"]
            name, ty = d.p["name"], u.text_of(*d.p["type"])
            if names.count(name) != 1 or d.p["init"] is None:
                continue
            ins = "\n" + top_ind + "%s %s;" % (ty, name)
            yield ctx.label("hoist-decl", st.s, name + " of for"), [
                (pos, pos, ins), (u.cstart(d.s), u.cend(d.p["init"][1]), "%s = %s" % (name, u.text_of(*d.p["init"])))]


def _innermost_common(u, b, users):
    """The block directly inside `b` (or deeper) that holds every user token, or None."""
    for st in b.p["items"]:
        for c in st.walk():
            if c.kind == "block" and c is not b and all(c.s < i < c.e for i in users):
                deeper = _innermost_common(u, c, users)
                return deeper or c
    return None


def _replace_stmt(u, st, repl):
    """Replace a statement; an empty replacement takes its line with it."""
    s, e = u.cstart(st.s), u.cend(st.e)
    if repl == "":
        ls = u.text.rfind("\n", 0, s)
        if u.text[ls + 1:s].strip() == "" and u.text[e:u.text.find("\n", e) if u.text.find("\n", e) >= 0 else len(u.text)].strip() == "":
            return ls, e, ""
    return s, e, repl


def _local_decl_types(u):
    """(stmt, type token range) of every local declaration, the for loops' included."""
    for st in u.decls:
        if st.kind == "decl" and not st.p["multi"]:
            yield st


def t_types(ctx):
    """A local's integer type among s32/u32 (and a narrower one widened), const added to a local
    or value parameter never assigned, or removed."""
    u = ctx.u
    for st in _local_decl_types(u):
        ts, te = st.p["type"]
        toks = [u.toks[i].text for i in range(ts, te)]
        words = [w for w in toks if w not in ("const", "static")]
        if len(words) == 1 and words[0] in INT_TYPES:
            cur = words[0]
            alts = {"s32": ["u32"], "u32": ["s32"], "int": ["u32"], "s16": ["s32"], "u16": ["s32", "u32"],
                    "s8": ["s32"], "u8": ["s32", "u32"]}[cur]
            i = next(i for i in range(ts, te) if u.toks[i].text == cur)
            for a in alts:
                yield ctx.label("int-type", st.s, "%s %s" % (a, st.p["name"])), [(u.cstart(i), u.cend(i + 1), a)]
        if "const" in toks:
            for i in range(ts, te):
                if u.toks[i].text == "const":
                    yield ctx.label("const", st.s, "-" + st.p["name"]), [(u.cstart(i), u.cend(i + 1) + (1 if u.text[u.cend(i + 1)] == " " else 0), "")]
        elif st.p["init"] and not toks[-1] == "&" and not st.p["dims"] and not _assigned(u, st.p["name"], st.p["name_at"]) \
                and st.p["name"] not in u.addr_taken:
            if toks[-1] == "*":
                yield ctx.label("const", st.s, "+" + st.p["name"]), [(u.cend(te), u.cend(te), " const")]
            else:
                yield ctx.label("const", st.s, "+" + st.p["name"]), [(u.cstart(ts), u.cstart(ts), "const ")]
    for ty, s, name in u.params:
        if ty.split()[-1] in BUILTIN_TYPES and not ty.startswith("const") and not _assigned(u, name, u.open):
            yield ctx.label("const", s, "+param " + name), [(u.cstart(s), u.cstart(s), "const ")]
        elif ty.startswith("const ") and not ty.endswith(("*", "&")):
            yield ctx.label("const", s, "-param " + name), [(u.cstart(s), u.cstart(s) + 6, "")]


WIDTH_BITS = {"s8": 8, "u8": 8, "s16": 16, "u16": 16, "s32": 32, "u32": 32, "int": 32, "s64": 64, "u64": 64}
WIDTH_TYPES = ["s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64"]
ARITH_OPS = {"<<", "+", "-", "*", "|", "&", "^"}


def _widen_casts(u, name, orig, skip_at):
    """Edits that write `(orig)name` at the uses of `name` that are an operand of a shift or of
    arithmetic: a variable narrowed from `orig` keeps its old width there."""
    edits = []
    for i in _uses(u, name):
        if i == skip_at or i + 1 >= len(u.toks):
            continue
        prev, nxt = u.toks[i - 1], u.toks[i + 1].text
        before = u.toks[i - 2] if i >= 2 else None
        binary_prev = prev.text in ARITH_OPS and before is not None and (
            (before.kind in ("id", "num") and before.text not in KEYWORDS) or before.text in (")", "]"))
        if nxt in ASSIGN or nxt in ("++", "--", "(", "[", ".", "->") or prev.text in ("++", "--") \
                or (prev.text in ("&", "*") and not binary_prev) \
                or (prev.text == ")" and i >= 2 and u.toks[i - 2].text in BUILTIN_TYPES):
            continue
        if nxt in ARITH_OPS or binary_prev:
            edits.append((u.cstart(i), u.cstart(i), "(%s)" % orig))
    return edits


def t_widths(ctx):
    """A parameter's or local's integer width changed among s8/u8/s16/u16/s32/u32/s64/u64, with a
    cast back to the old type where it is a shift's or arithmetic's operand and the new type is
    narrower (func_0020A190: a u64 key as `s32 key`, `(u64)key << sh`). A parameter's new width
    changes its callers' code too."""
    u = ctx.u
    targets = []
    for st in _local_decl_types(u):
        ts, te = st.p["type"]
        words = [u.toks[i].text for i in range(ts, te) if u.toks[i].text not in ("const", "static")]
        if len(words) == 1 and words[0] in WIDTH_BITS and not st.p["dims"]:
            i = next(i for i in range(ts, te) if u.toks[i].text == words[0])
            targets.append((words[0], i, st.p["name"], st.p["name_at"], st.s, "local "))
    for ty, s, name in u.params:
        words = [w for w in ty.split() if w != "const"]
        if len(words) == 1 and words[0] in WIDTH_BITS:
            i = next((i for i in range(s, u.open) if u.toks[i].text == words[0]), None)
            if i is not None:
                targets.append((words[0], i, name, next(k for k in range(i, u.open) if u.toks[k].text == name), s, "param "))
    for cur, i, name, name_at, at, what in targets:
        for new in WIDTH_TYPES:
            if new == cur or (cur == "int" and new == "s32"):
                continue
            edits = [(u.cstart(i), u.cend(i + 1), new)]
            if WIDTH_BITS[new] < WIDTH_BITS[cur]:
                edits += _widen_casts(u, name, cur, name_at)
            yield ctx.label("width", at, "%s%s %s -> %s" % (what, name, cur, new)), edits


def t_pointer_ref(ctx):
    """A pointer local only used as p->m written as a reference (T& p = *e), and back."""
    u = ctx.u
    for st in _local_decl_types(u):
        if not st.p["init"]:
            continue
        ts, te = st.p["type"]
        last = u.toks[te - 1].text
        name = st.p["name"]
        uses = [i for i in _uses(u, name) if i != st.p["name_at"]]
        if not uses:
            continue
        try:
            init = u.expr(*st.p["init"])
        except ParseError:
            continue
        if last == "*" and all(u.toks[i + 1].text == "->" for i in uses) and not _assigned(u, name, st.p["name_at"]):
            ref_init = u.text_of(init.kids[0].s, init.kids[0].e) if init.kind == "unary" and init.op == "&" else "*" + wrap(u, init)
            edits = [(u.cstart(te - 1), u.cend(te), "&"), (u.cstart(st.p["init"][0]), u.cend(st.p["init"][1]), ref_init)]
            edits += [(u.cstart(i + 1), u.cend(i + 2), ".") for i in uses]
            yield ctx.label("ptr-to-ref", st.s, name), edits
        elif last == "&":
            ptr_init = u.text_of(init.kids[0].s, init.kids[0].e) if init.kind == "unary" and init.op == "*" else "&" + wrap(u, init)
            edits = [(u.cstart(te - 1), u.cend(te), "*"), (u.cstart(st.p["init"][0]), u.cend(st.p["init"][1]), ptr_init)]
            for i in uses:
                if u.toks[i + 1].text == ".":
                    edits.append((u.cstart(i + 1), u.cend(i + 2), "->"))
                else:
                    edits.append((u.cstart(i), u.cend(i + 1), "(*%s)" % name))
            yield ctx.label("ref-to-ptr", st.s, name), edits


def _fresh(u, base):
    taken = set(u.locals) | {t.text for t in u.toks if t.kind == "id"}
    if base not in taken and base not in KEYWORDS:
        return base
    n = 2
    while "%s%d" % (base, n) in taken:
        n += 1
    return "%s%d" % (base, n)


def find_prototypes(text, path=None):
    """{function name: [(param type, param name)]} from the declarations and definitions of the
    file (and the project headers it includes)."""
    out = {}
    for src in [text] + _header_texts(text, path):
        for m in re.finditer(r"(?:^|[;{}\n])\s*(?:static\s+|inline\s+|virtual\s+)*[\w:<>]+[\s\*&]+(\w+)\s*\(([^()]*)\)\s*(?:const\s*)?[;{]", src):
            name, params = m.group(1), m.group(2).strip()
            if name in KEYWORDS:
                continue
            plist = []
            ok = True
            for p in [p.strip() for p in params.split(",")] if params and params != "void" else []:
                pm = re.match(r"^(.*?[\s\*&])(\w+)$", p)
                if p == "...":
                    plist.append(("...", None))
                elif pm:
                    plist.append((pm.group(1).strip(), pm.group(2)))
                else:
                    plist.append((p, None))
            if ok:
                out.setdefault(name, plist)
    return out


_HEADERS = {}


def _header_texts(text, path=None):
    out = []
    for m in re.finditer(r'^\s*#\s*include\s+"([^"]+)"', text, re.M):
        h = ROOT / "include" / m.group(1)
        if m.group(1) in ("common.h", "names.h"):
            continue
        if h not in _HEADERS:
            _HEADERS[h] = h.read_text(errors="replace") if h.exists() else None
        if _HEADERS[h] is not None:
            out.append(_HEADERS[h])
    return out


_METHODS = {}


def _struct_bodies(src):
    """(name, body text) of every struct or class definition in a text."""
    for m in re.finditer(r"\b(?:struct|class)\s+(\w+)\s*(?::[^{;()]*)?\{", src):
        depth, i = 0, m.end() - 1
        while i < len(src):
            if src[i] == "{":
                depth += 1
            elif src[i] == "}":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        yield m.group(1), src[m.end():i]


def _struct_fields(body):
    """[(type, name, dims)] of a struct body's data members, in order."""
    flat, depth = [], 0
    for ch in body:
        if ch == "{":
            depth += 1
            if depth == 1:
                flat.append(";")
        elif ch == "}":
            depth -= 1
        elif depth == 0:
            flat.append(ch)
    out = []
    for piece in "".join(flat).split(";"):
        piece = re.sub(r"^\s*(?:public|private|protected)\s*:", "", _strip_comments(piece)).strip()
        if not piece or "(" in piece or re.match(r"(static|typedef|friend|enum|using|template)\b", piece):
            continue
        m = re.match(r"^((?:const\s+|unsigned\s+|signed\s+|struct\s+)*[\w:]+)\s*(.*)$", piece, re.S)
        if not m:
            continue
        for d in m.group(2).split(","):
            dm = re.match(r"^\s*(\**)\s*(\w+)\s*((?:\[[^\]]*\])*)\s*$", d)
            if dm:
                out.append(((m.group(1) + dm.group(1)).strip(), dm.group(2), dm.group(3)))
    return out


def find_methods(text, path=None):
    """{method name: [{struct, params, body, fields}]} of the single-expression member functions
    (not static) of the structs of the file and of the project headers it includes, with the
    struct's data members [(type, name, dims)] in order."""
    out = {}
    pat = re.compile(r"(?:^|(?<=[;{}:]))\s*(?:inline\s+)?((?:const\s+)?[\w:]+(?:\s*[\*&])*)\s+(\w+)\s*\(([^()]*)\)\s*"
                     r"(?:const\s*)?\{\s*return\s+([^;{}]*);\s*\}")
    for src in [text] + _header_texts(text, path):
        key = hashlib.sha1(src.encode()).hexdigest()
        if key not in _METHODS:
            found = []
            for sname, body in _struct_bodies(src):
                fields = None
                for m in pat.finditer(body):
                    mbody = m.group(4).strip()
                    if "asm" in mbody or re.search(r"\bthis\b", mbody) or m.group(2) in KEYWORDS:
                        continue
                    params = []
                    for p in [p.strip() for p in m.group(3).split(",")] if m.group(3).strip() not in ("", "void") else []:
                        pm = re.match(r"^(.*?[\s\*&])(\w+)$", p)
                        if not pm:
                            params = None
                            break
                        params.append((pm.group(1).strip(), pm.group(2)))
                    if params is None:
                        continue
                    if fields is None:
                        fields = _struct_fields(body)
                    found.append((m.group(2), {"struct": sname, "params": params, "body": mbody, "fields": fields}))
            _METHODS[key] = found
        for name, meth in _METHODS[key]:
            if not any(x["struct"] == meth["struct"] for x in out.get(name, [])):
                out.setdefault(name, []).append(meth)
    return out


def _array_alias(u, meth, g):
    """Whether the global array `g` may stand for the method's object: its first member is an
    array of g's element type."""
    if not meth["fields"] or not meth["fields"][0][2]:
        return False
    et = _element_type(u, g)
    return et is not None and _canon(et) == _canon(meth["fields"][0][0])


def _method_in_place(u, meth, base, op, args):
    """A member function's body written for the object `base` (reached by `op`) and the
    arguments; the struct's first array member read straight from a global array the object is
    a cast of."""
    b = base
    while b.kind == "paren":
        b = b.kids[0]
    arr = None
    if b.kind == "cast" and b.kids[0].kind == "id" and _array_alias(u, meth, b.kids[0].op):
        arr = (meth["fields"][0][1], b.kids[0].op)
    fields = {f[1] for f in meth["fields"]}
    params = {p: a for (_, p), a in zip(meth["params"], args)}
    body = meth["body"]
    toks = tokenize(body)
    pieces, pos = [], 0
    for n, t in enumerate(toks):
        if t.kind != "id" or n and toks[n - 1].text in (".", "->", "::"):
            continue
        nxt = toks[n + 1].text if n + 1 < len(toks) else ""
        if t.text in params:
            rep = wrap(u, params[t.text])
        elif t.text in fields:
            rep = arr[1] if arr and t.text == arr[0] and nxt == "[" else wrap(u, base) + op + t.text
        else:
            continue
        pieces += [body[pos:t.start], rep]
        pos = t.end
    pieces.append(body[pos:])
    return "".join(pieces)


def _match_method(pu, pat, u, x, binds, meth, obj):
    """_match_pattern for a member function's body: its members match the same object's members,
    or (the first array member) a global array's elements; obj[0] records the object."""
    while x.kind == "paren":
        x = x.kids[0]
    while pat.kind == "paren":
        pat = pat.kids[0]
    fields = {f[1] for f in meth["fields"]}

    def same_obj(form):
        if obj[0] is None:
            obj[0] = form
        return obj[0] == form
    if pat.kind == "id" and pat.op in binds:
        t = u.text_of(x.s, x.e)
        if binds[pat.op] is None:
            binds[pat.op] = (t, x)
            return True
        return binds[pat.op][0] == t
    if pat.kind == "index" and pat.kids[0].kind == "id" and pat.kids[0].op in fields:
        if x.kind != "index":
            return False
        root, f = x.kids[0], pat.kids[0].op
        if root.kind == "id" and f == meth["fields"][0][1] and _array_alias(u, meth, root.op):
            ok = same_obj(("arr", root.op))
        elif root.kind == "member" and root.extra == f:
            ok = same_obj(("mem", wrap(u, root.kids[0]), root.op))
        else:
            return False
        return ok and _match_method(pu, pat.kids[1], u, x.kids[1], binds, meth, obj)
    if pat.kind == "id" and pat.op in fields:
        return x.kind == "member" and x.extra == pat.op and same_obj(("mem", wrap(u, x.kids[0]), x.op))
    if pat.kind != x.kind or pat.op != x.op or len(pat.kids) != len(x.kids):
        return False
    if pat.kind == "member" and pat.extra != x.extra:
        return False
    if pat.kind == "cast" and pu.text_of(*pat.extra) != u.text_of(*x.extra):
        return False
    return all(_match_method(pu, p, u, k, binds, meth, obj) for p, k in zip(pat.kids, x.kids))


def find_helpers(text, path=None):
    """{name: {params, body (expression text), pure}} of the single-expression functions defined
    in the file or a project header it includes (`static T Name(params) { return e; }`)."""
    out = {}
    pat = re.compile(r"(?:static\s+|inline\s+)+([\w:]+[\s\*&]*)\s+(\w+)\s*\(([^()]*)\)\s*\{\s*return\s+([^;{}]*);\s*\}")
    for src in [text] + _header_texts(text, path):
        for m in pat.finditer(src):
            body = m.group(4)
            if "asm" in body:
                continue
            params = []
            for p in [p.strip() for p in m.group(3).split(",")] if m.group(3).strip() not in ("", "void") else []:
                pm = re.match(r"^(.*?[\s\*&])(\w+)$", p)
                if not pm:
                    params = None
                    break
                params.append((pm.group(1).strip(), pm.group(2)))
            if params is None:
                continue
            pure = not re.search(r"->|\[|\b[A-Za-z_]\w*\s*\(", re.sub(r"\(\s*[a-zA-Z_]\w*\s*\)", "", body)) and "*" not in \
                re.sub(r"\)\s*\*|\w\s*\*|\d\s*\*", "", body)
            out.setdefault(m.group(2), {"params": params, "body": body.strip(), "pure": pure,
                                        "type": m.group(1).strip()})
    return out


def t_arguments(ctx):
    """A call's argument named in a local before the statement (typed as the callee's parameter),
    and a local read once written in place of its use."""
    u = ctx.u
    for st in u.body.walk():
        if st.kind not in ("expr", "decl", "return"):
            continue
        try:
            xs = list(_stmt_exprs(u, st))
        except ParseError:
            continue
        for _, top in xs:
            calls = [top] if top.kind == "call" else []
            if top.kind == "assign" and top.kids[1].kind == "call":
                calls.append(top.kids[1])
            for call in calls:
                callee = call.kids[0]
                if callee.kind != "id":
                    continue
                proto = ctx.protos.get(callee.op.split("::")[-1])
                if not proto:
                    continue
                args = call.kids[1:]
                others_call = [any(n.kind == "call" for n in a.walk()) for a in args]
                for n, a in enumerate(args):
                    if n >= len(proto) or proto[n][0] == "..." or a.kind in ("id", "num", "str", "chr"):
                        continue
                    if a.kind == "unary" and a.op in ("&", "-") and a.kids[0].kind in ("id", "num"):
                        continue
                    if not simple_rvalue(a) or any(others_call[:n]):
                        continue
                    ty, pname = proto[n]
                    if "&" in ty:
                        continue
                    name = _fresh(u, pname or "arg")
                    ind = u.indent_at(st.s)
                    edits = [(u.cstart(st.s), u.cstart(st.s), "%s %s = %s;\n%s" % (ty, name, u.text_of(a.s, a.e), ind)),
                             (u.cstart(a.s), u.cend(a.e), name)]
                    yield ctx.label("name-arg", a.s, "%s of %s" % (name, callee.op)), edits
    # a temporary written in place
    for b in blocks(u):
        items = b.p["items"]
        for k, st in enumerate(items):
            if st.kind != "decl" or not st.p["init"] or st.p["multi"] or st.p["dims"] or st.p["ctor"]:
                continue
            name = st.p["name"]
            ty = u.text_of(*st.p["type"])
            if ty.endswith("&") or name in u.addr_taken or _assigned(u, name, st.p["name_at"]):
                continue
            uses = [i for i in _uses(u, name) if i != st.p["name_at"]]
            if len(uses) != 1:
                continue
            try:
                init = u.expr(*st.p["init"])
                if not simple_rvalue(init):
                    continue
                eff = ctx.eff.expr(init)
            except ParseError:
                continue
            j = next((j for j in range(k + 1, len(items)) if items[j].s <= uses[0] < items[j].e), None)
            if j is None:
                continue
            ok = True
            for m in range(k + 1, j):
                try:
                    e2 = ctx.eff.stmt(items[m])
                except ParseError:
                    ok = False
                    break
                if e2.control or conflict(eff, e2):
                    ok = False
                    break
            if not ok:
                continue
            # The use statement itself may write what the initialiser reads before the use: only
            # when it is a single expression whose own writes are disjoint, or a simple statement.
            if items[j].kind not in ("expr", "decl", "return", "if", "switch", "while", "for"):
                continue
            yield ctx.label("inline-temp", st.s, name), [_replace_stmt(u, st, ""),
                                                        (u.cstart(uses[0]), u.cend(uses[0] + 1), wrap(u, init))]


def t_switch(ctx):
    """switch against an if/else-if chain on the same operand (no fall-through)."""
    u = ctx.u
    for st in u.body.walk():
        try:
            if st.kind == "switch":
                yield from _switch_to_if(ctx, u, st)
            elif st.kind == "if":
                yield from _if_to_switch(ctx, u, st)
        except ParseError:
            continue


def _switch_to_if(ctx, u, st):
    cx = u.expr(*st.p["cond"])
    if not simple_rvalue(cx) or st.p["body"].kind != "block":
        return
    subj = wrap(u, cx) if cx.kind not in PRIMARY_KINDS else u.text_of(cx.s, cx.e)
    groups, cur = [], None
    for it in st.p["body"].p["items"]:
        if it.kind == "label" and it.p["value"] is not None or it.kind == "label" and u.toks[it.s].text == "default":
            if cur is None or cur[1]:
                cur = [[], []]
                groups.append(cur)
            cur[0].append(None if u.toks[it.s].text == "default" else u.text_of(*it.p["value"]))
        elif cur is None:
            return
        else:
            cur[1].append(it)
    ind = u.indent_at(st.s)
    parts, default = [], None
    for labels, body in groups:
        if not body or body[-1].kind not in ("break", "return"):
            return
        stmts = body[:-1] if body[-1].kind == "break" else body
        for s in stmts:
            for x in s.walk():
                if x.kind in ("break", "continue") and not any(
                        y.kind in ("for", "while", "do", "switch") and y.s < x.s < y.e for s2 in stmts for y in s2.walk()):
                    return
        text = "\n".join(ind + "    " + u.text_of(s.s, s.e) for s in stmts)
        if None in labels:
            if len(labels) > 1:
                return
            default = text
            continue
        cond = " || ".join("%s == %s" % (subj, l) for l in labels)
        parts.append((cond, text))
    if not parts:
        return
    out = ""
    for n, (cond, text) in enumerate(parts):
        out += ("if (%s) {\n%s\n%s}" if n == 0 else " else if (%s) {\n%s\n%s}") % (cond, text, ind)
    if default is not None and default.strip():
        out += " else {\n%s\n%s}" % (default, ind)
    yield ctx.label("switch-to-if", st.s), [(u.cstart(st.s), u.cend(st.e), out)]


def _if_to_switch(ctx, u, st):
    chain, node = [], st
    while node is not None and node.kind == "if":
        chain.append(node)
        node = node.p["other"]
    if len(chain) < 2:
        return
    subj, cases = None, []
    for n in chain:
        cx = u.expr(*n.p["cond"])
        alts = []
        stack = [cx]
        while stack:
            c = stack.pop()
            if c.kind == "binary" and c.op == "||":
                stack.extend(reversed(c.kids))
            elif c.kind == "binary" and c.op == "==" and c.kids[1].kind in ("num", "chr", "id"):
                s = u.text_of(c.kids[0].s, c.kids[0].e)
                if subj is None:
                    subj = s
                if s != subj:
                    return
                alts.append(u.text_of(c.kids[1].s, c.kids[1].e))
            else:
                return
        if any(x.kind in ("break", "continue") for x in n.p["then"].walk()):
            return
        cases.append((alts, n.p["then"]))
    ind = u.indent_at(st.s)
    out = "switch (%s) {\n" % subj
    for alts, body in cases:
        for a in alts:
            out += "%scase %s:\n" % (ind, a)
        out += "%s    %s\n%s    break;\n" % (ind, inner_lines(u, body, ind + "    ") if body.kind == "block" else u.text_of(body.s, body.e), ind)
    if node is not None:
        out += "%sdefault:\n%s    %s\n%s    break;\n" % (ind, ind, inner_lines(u, node, ind + "    ") if node.kind == "block" else u.text_of(node.s, node.e), ind)
    out += ind + "}"
    yield ctx.label("if-to-switch", st.s), [(u.cstart(st.s), u.cend(st.e), out)]


def _element_type(u, name):
    """The element type of an array or pointer `name` (local, parameter or file-scope), or None."""
    for st in u.decls:
        if st.kind == "decl" and st.p["name"] == name:
            ty = u.text_of(*st.p["type"])
            if st.p["dims"]:
                return ty
            return ty[:-1].strip() if ty.endswith("*") else None
    for ty, _, pname in u.params:
        if pname == name:
            return ty[:-1].strip() if ty.endswith("*") else None
    m = re.search(r"^\s*(?:extern\s+|static\s+)?([\w:]+(?:\s*\*)*)\s*(\*?)\s*\b%s\s*(\[[^\]]*\])?\s*[;=]" % re.escape(name),
                  u.text[:u.span[0]], re.M)
    if m:
        if m.group(3):
            return (m.group(1) + m.group(2)).strip()
        if m.group(2) or m.group(1).endswith("*"):
            return (m.group(1) + m.group(2)).strip()[:-1].strip()
    return None


def t_walks(ctx):
    """A counted loop over A[i] walked with a pointer instead (the counter kept for the test, or
    dropped when it serves only the walk)."""
    u = ctx.u
    for st in u.body.walk():
        if st.kind != "for" or st.p["init"] is None:
            continue
        step = u.text_of(*st.p["step"])
        m = re.match(r"^\s*(?:(\w+)\s*\+\+|\+\+\s*(\w+)|(\w+)\s*\+=\s*1)\s*$", step)
        if not m:
            continue
        i = m.group(1) or m.group(2) or m.group(3)
        body = st.p["body"]
        hits = {}
        for k in range(body.s, body.e - 3):
            t = u.toks
            if t[k].kind == "id" and t[k + 1].text == "[" and t[k + 2].text == i and t[k + 3].text == "]" and \
                    not (k > 0 and t[k - 1].text in (".", "->")):
                hits.setdefault(t[k].text, []).append(k)
        uses_i = [k for k in _uses(u, i, body.s, body.e)]
        for arr, at in hits.items():
            ety = _element_type(u, arr)
            if ety is None:
                continue
            p = _fresh(u, "p")
            edits = []
            for k in at:
                after = u.toks[k + 4].text if k + 4 < len(u.toks) else ""
                if after == ".":
                    edits.append((u.cstart(k), u.cend(k + 5), p + "->"))
                else:
                    edits.append((u.cstart(k), u.cend(k + 4), "*" + p))
            ind = u.indent_at(st.s)
            edits.append((u.cstart(st.p["step"][0]), u.cend(st.p["step"][1]), "%s, %s++" % (step.strip(), p)))
            edits.append((u.cstart(st.s), u.cstart(st.s), "%s* %s = %s;\n%s" % (ety, p, arr, ind)))
            yield ctx.label("pointer-walk", st.s, arr), edits


def t_helpers(ctx):
    """A call of a single-expression helper (of the file, or of a project header it includes)
    written in place, and an expression of a helper's shape written as its call; the same for a
    struct's single-expression member function called on an object, a cast of a global array
    read as the array's elements in place (func_001D7778, docs/toolchain/loops.md: a pointer
    passed to an inline lives longer)."""
    u = ctx.u
    yield from _methods_both_ways(ctx)
    if not ctx.helpers:
        return
    # in place
    for st, part, top in _all_exprs(u):
        for x in top.walk():
            if x.kind != "call" or x.kids[0].kind != "id":
                continue
            full = x.kids[0].op
            h = ctx.helpers.get(full.split("::")[-1])
            if not h or len(h["params"]) != len(x.kids) - 1:
                continue
            body = h["body"]
            ok = True
            for (pty, pname), a in zip(h["params"], x.kids[1:]):
                n = len(re.findall(r"\b%s\b" % re.escape(pname), body))
                if n != 1 and not simple_rvalue(a):
                    ok = False
                    break
            if not ok:
                continue
            subst = body
            for (pty, pname), a in zip(h["params"], x.kids[1:]):
                subst = re.sub(r"\b%s\b" % re.escape(pname), lambda _m, a=a: wrap(u, a).replace("\\", "\\\\"), subst)
            yield ctx.label("inline-helper", x.s, full), [(u.cstart(x.s), u.cend(x.e), "(%s)" % subst)]
    # as a call
    patterns = []
    for name, h in ctx.helpers.items():
        try:
            pu = _ExprUnit(h["body"], {p for _, p in h["params"]} | u.locals, u.types)
            pat = pu.expr(0, len(pu.toks))
        except ParseError:
            continue
        if pat.kind == "id":
            continue
        patterns.append((name, h, pu, pat))
    qual = _qualified_names(u.text)
    for st, part, top in _all_exprs(u):
        for x in top.walk():
            for name, h, pu, pat in patterns:
                binds = {p: None for _, p in h["params"]}
                if _match_pattern(pu, pat, u, x, binds) and all(binds.values()):
                    args = ", ".join(binds[p][0] for _, p in h["params"])
                    yield ctx.label("call-helper", x.s, name), [(u.cstart(x.s), u.cend(x.e), "%s(%s)" % (qual.get(name, name), args))]


def _methods_both_ways(ctx):
    u = ctx.u
    if not ctx.methods:
        return
    for st, part, top in _all_exprs(u):
        for x in top.walk():
            if x.kind != "call" or x.kids[0].kind != "member":
                continue
            callee = x.kids[0]
            cands = ctx.methods.get(callee.extra, [])
            base = callee.kids[0]
            b = base
            while b.kind == "paren":
                b = b.kids[0]
            if b.kind == "cast":
                cty = _canon(u.text_of(*b.extra)).rstrip("*").strip()
                cands = [m for m in cands if m["struct"] == cty.split("::")[-1]]
            elif len(cands) != 1:
                continue
            args = x.kids[1:]
            for meth in cands:
                if len(meth["params"]) != len(args):
                    continue
                if any(len(re.findall(r"\b%s\b" % re.escape(p), meth["body"])) != 1 and not simple_rvalue(a)
                       for (_, p), a in zip(meth["params"], args)):
                    continue
                if base.kind not in PRIMARY_KINDS and not simple_rvalue(base) and \
                        len(re.findall(r"\b(?:%s)\b" % "|".join(re.escape(f[1]) for f in meth["fields"]) or "^$",
                                       meth["body"])) > 1:
                    continue
                text = _method_in_place(u, meth, base, callee.op, args)
                yield ctx.label("inline-method", x.s, "%s::%s" % (meth["struct"], callee.extra)), [
                    (u.cstart(x.s), u.cend(x.e), "(%s)" % text)]
    # an expression of a member function's shape as its call
    patterns = []
    for name, meths in ctx.methods.items():
        for meth in meths:
            try:
                pu = _ExprUnit(meth["body"], {p for _, p in meth["params"]} | {f[1] for f in meth["fields"]} | u.locals,
                               u.types)
                pat = pu.expr(0, len(pu.toks))
            except ParseError:
                continue
            if pat.kind in ("id", "member", "index", "num"):
                continue
            patterns.append((name, meth, pu, pat))
    if not patterns:
        return
    for st, part, top in _all_exprs(u):
        for x in top.walk():
            if x.kind == "paren":
                continue
            for name, meth, pu, pat in patterns:
                binds = {p: None for _, p in meth["params"]}
                obj = [None]
                if _match_method(pu, pat, u, x, binds, meth, obj) and all(binds.values()) and obj[0] is not None:
                    args = ", ".join(binds[p][0] for _, p in meth["params"])
                    if obj[0][0] == "arr":
                        call = "((%s*)%s)->%s(%s)" % (meth["struct"], obj[0][1], name, args)
                    else:
                        call = "%s%s%s(%s)" % (obj[0][1], obj[0][2], name, args)
                    yield ctx.label("call-method", x.s, "%s::%s" % (meth["struct"], name)), [(u.cstart(x.s), u.cend(x.e), call)]


def _qualified_names(text):
    """{method: Class::method} for the static methods of the file's own structs."""
    out = {}
    for m in re.finditer(r"\b(?:struct|class)\s+(\w+)\s*\{", text):
        depth, i = 0, m.end() - 1
        while i < len(text):
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        for f in re.finditer(r"\bstatic\s+[\w\s\*&:]+?\b(\w+)\s*\(", text[m.end():i]):
            out.setdefault(f.group(1), "%s::%s" % (m.group(1), f.group(1)))
    return out


class _ExprUnit:
    """A bare expression's tokens, for the helpers' bodies."""

    def __init__(self, text, names, types):
        self.text = text
        self.toks = tokenize(text)
        self._match = {}
        stack = []
        for i, t in enumerate(self.toks):
            if t.text in "([{":
                stack.append(i)
            elif t.text in ")]}" and stack:
                self._match[stack.pop()] = i
        self.types, self.locals_hint = types, names
        self._ids = None

    match = Unit.match
    text_of = Unit.text_of

    def expr(self, s, e):
        p = ExprParser(self, s, e)
        x = p.parse(1)
        if p.i != e:
            raise ParseError("trailing tokens")
        return x


def t_element(ctx):
    """A repeated element A[i] (a simple index, read more than once) named by a pointer to it,
    T* e = &A[i], its members then read through e->."""
    u = ctx.u
    for b in blocks(u):
        items = b.p["items"]
        done = set()
        for k, st in enumerate(items):
            if st.kind in ("label", "empty"):
                continue
            # the element accesses in this statement and the ones after it in the block
            found = {}
            for i in range(st.s, items[-1].e - 3):
                t = u.toks
                if t[i].kind == "id" and t[i + 1].text == "[" and not (i > 0 and t[i - 1].text in (".", "->")):
                    close = u.match(i + 1)
                    if close + 1 < len(t) and t[close + 1].text == "." and all(
                            t[j].kind in ("id", "num") or t[j].text in ("+", "-") for j in range(i + 2, close)):
                        found.setdefault(u.text_of(i, close + 1), []).append((i, close))
            for elem, at in found.items():
                if len(at) < 2 or at[0][0] >= st.e or elem in done:
                    continue
                done.add(elem)
                arr = u.toks[at[0][0]].text
                ety = _element_type(u, arr)
                if ety is None:
                    continue
                idx_names = {u.toks[j].text for j in range(at[0][0] + 2, at[0][1]) if u.toks[j].kind == "id"}
                # the index and the array must not change after the pointer is taken
                if any(_assigned(u, n, st.s) for n in idx_names | {arr}):
                    continue
                p = _fresh(u, "e")
                edits = [(u.cstart(i), u.cend(c + 2), p + "->") for i, c in at]
                edits.append((u.cstart(st.s), u.cstart(st.s), "%s* %s = &%s;\n%s" % (ety, p, elem, u.indent_at(st.s))))
                yield ctx.label("element-pointer", st.s, elem), edits


def t_returns(ctx):
    """A result variable returned at the end, set in one if, written as returns: the if's branch
    returns its value and the default is returned after it (or first, under the negated test)."""
    u = ctx.u
    items = u.body.p["items"]
    if len(items) < 3 or items[-1].kind != "return" or not items[-1].p["value"]:
        return
    ret = u.text_of(*items[-1].p["value"])
    decl = next((st for st in items if st.kind == "decl" and st.p["name"] == ret), None)
    if decl is None or not decl.p["init"] or decl.p["multi"]:
        return
    default = u.text_of(*decl.p["init"])
    k = len(items) - 2
    st = items[k]
    if st.kind != "if" or st.p["other"] is not None or st.p["then"].kind != "block" or not st.p["then"].p["items"]:
        return
    last = st.p["then"].p["items"][-1]
    x = _assign_of(u, last)
    if x is None or x.kids[0].kind != "id" or x.kids[0].op != ret:
        return
    uses = [i for i in _uses(u, ret) if i not in (decl.p["name_at"], x.kids[0].s, items[-1].p["value"][0])]
    if uses or any(not st.s < i < st.e for i in _uses(u, ret) if i != decl.p["name_at"] and i != items[-1].p["value"][0]):
        return
    try:
        cx = u.expr(*st.p["cond"])
    except ParseError:
        return
    ind = u.indent_at(st.s)
    value = u.text_of(x.kids[1].s, x.kids[1].e)
    then_items = st.p["then"].p["items"][:-1]
    old_inner = u.indent_at(last.s)
    before = "".join(reindent(u.text_of(t.s, t.e), old_inner, ind + "    ") + "\n" + ind + "    " for t in then_items)
    a = "if (%s) {\n%s    %sreturn %s;\n%s}\n%sreturn %s;" % (u.text_of(*st.p["cond"]), ind, before, value, ind, ind, default)
    yield ctx.label("result-to-returns", st.s, ret), [_replace_stmt(u, decl, ""),
                                                      (u.cstart(st.s), u.cend(items[-1].e), a)]
    flat = "".join(reindent(u.text_of(t.s, t.e), old_inner, ind) + "\n" + ind for t in then_items)
    b = "if (%s) {\n%s    return %s;\n%s}\n%s%sreturn %s;" % (negate(u, cx), ind, default, ind, ind, flat, value)
    yield ctx.label("result-to-returns", st.s, ret + " early"), [_replace_stmt(u, decl, ""),
                                                                 (u.cstart(st.s), u.cend(items[-1].e), b)]


def _match_pattern(pu, pat, u, x, binds):
    while x.kind == "paren":
        x = x.kids[0]
    while pat.kind == "paren":
        pat = pat.kids[0]
    if pat.kind == "id" and pat.op in binds:
        t = u.text_of(x.s, x.e)
        if binds[pat.op] is None:
            binds[pat.op] = (t, x)
            return True
        return binds[pat.op][0] == t
    if pat.kind != x.kind or pat.op != x.op or len(pat.kids) != len(x.kids):
        return False
    if pat.kind == "member" and pat.extra != x.extra:
        return False
    if pat.kind == "cast" and pu.text_of(*pat.extra) != u.text_of(*x.extra):
        return False
    return all(_match_pattern(pu, p, u, k, binds) for p, k in zip(pat.kids, x.kids))


VU0_GROUPS = [["ToFloat", "ToFloatMoved", "ToFloatNow", "ToFloatViaBits"],
              ["Scalar", "ScalarAt", "ScalarAtValue", "ScalarAtCall", "ScalarInGpr"],
              ["FromFloat", "FromFloatAt", "FromFloatAtCall"],
              ["NormalizeOr", "NormalizeOrMoved"],
              ["RotateRows", "RotateRowsTied"]]
LVALUE_ONLY = {"ScalarAt", "FromFloatAt"}


def t_vu0(ctx):
    """A VU0 helper of include/vu0.h replaced by an alternative of the same signature (ToFloat,
    ToFloatMoved, ...; Scalar, ScalarAt, ScalarAtValue, ...); the ones taking a reference only
    for an lvalue argument."""
    u = ctx.u
    for st, part, top in _all_exprs(u):
        for x in top.walk():
            if x.kind != "call" or x.kids[0].kind != "id" or not x.kids[0].op.startswith("Vu0::"):
                continue
            name = x.kids[0].op.split("::")[-1]
            group = next((g for g in VU0_GROUPS if name in g), None)
            if not group:
                continue
            arg = x.kids[1] if len(x.kids) > 1 else None
            lvalue = arg is not None and arg.kind in ("id", "member", "index") or \
                arg is not None and arg.kind == "unary" and arg.op == "*"
            for alt in group:
                if alt == name or alt in LVALUE_ONLY and not lvalue:
                    continue
                f = x.kids[0]
                yield ctx.label("vu0", x.s, "%s->%s" % (name, alt)), [(u.cstart(f.s), u.cend(f.e), "Vu0::" + alt)]


# ---------------------------------------------------------------------------------------------
# The source forms that matched in November 2026 (docs/toolchain/*.md cite each one).

CANON_TYPE = {"float": "f32", "int": "s32", "double": "f64"}
SCALAR_WORDS = set(WIDTH_BITS) | {"int", "unsigned", "signed", "long", "short", "char", "bool"}
LOOSE_BEFORE = ASSIGN | {"(", ",", "return"}


def _canon(ty):
    """A type's text without qualifiers, float and int written f32 and s32, spaces normalised."""
    words = [w for w in ty.replace("*", " * ").replace("&", " & ").split()
             if w not in ("const", "static", "extern", "volatile", "register", "inline")]
    return " ".join(CANON_TYPE.get(w, w) for w in words).replace(" *", "*").replace(" &", "&")


def _placed(u, s, e, text, x):
    """`text`, the expression x, written over tokens s..e: in parentheses unless x is primary or
    the place takes a whole expression (an assignment's right side, an argument, a return)."""
    if x.kind in PRIMARY_KINDS:
        return text
    prev = u.toks[s - 1].text if s > 0 else ";"
    nxt = u.toks[e].text if e < len(u.toks) else ";"
    if not (x.kind == "binary" and x.op == ",") and x.kind != "assign" and \
            (prev in LOOSE_BEFORE and nxt in (";", ")", ",") or prev == "[" and nxt == "]"):
        return text
    return "(" + text + ")"


def _toks_key(u, s, e):
    return " ".join(t.text for t in u.toks[s:e])


def _const_expr(x):
    """Whether x is built of numbers only (a literal or a constant expression of literals)."""
    if x.kind == "num":
        return True
    if x.kind == "paren" or x.kind == "unary" and x.op in ("-", "+"):
        return _const_expr(x.kids[0])
    if x.kind == "binary" and x.op in ("+", "-", "*", "/"):
        return all(_const_expr(k) for k in x.kids)
    return False


def _is_float_num(t):
    t = t.lower()
    return not t.startswith("0x") and ("." in t or "e" in t or t.endswith("f"))


def _const_type(x):
    """f32, u32 or s32 for a constant expression (None for a 64-bit one)."""
    nums = [n.op.lower() for n in x.walk() if n.kind == "num"]
    if any(_is_float_num(n) for n in nums):
        return "f32"
    if any("ll" in n for n in nums):
        return None
    return "u32" if any(n.rstrip("l").endswith("u") for n in nums) else "s32"


def _written_through(u, i):
    """Whether the operand ending at token i is the base of a member or element that is assigned
    or incremented (x.f = ..., x[2]++, ...), or is itself assigned."""
    j = i + 1
    while j < len(u.toks):
        t = u.toks[j].text
        if t in (".", "->") and j + 1 < len(u.toks):
            j += 2
        elif t == "[" and j in u._match:
            j = u.match(j) + 1
        else:
            break
    t = u.toks[j].text if j < len(u.toks) else ""
    return t in ASSIGN or t in ("++", "--")


def _constants(u):
    """The maximal constant subexpressions of the function: the float ones, and the integer ones
    (but 0) that are an operand of arithmetic or a comparison, an assignment's or initialiser's
    value, a return's or a call's argument; not a shift count, a mask, an index, a case label, a
    template's or an upper-case macro's argument."""
    out, seen = [], set()

    def visit(x, parent):
        if _const_expr(x):
            ty = _const_type(x)
            if ty is None or (x.s, x.e) in seen:
                return
            prev = u.toks[x.s - 1].text if x.s > 0 else ""
            nxt = u.toks[x.e].text if x.e < len(u.toks) else ""
            if prev == "<" and nxt == ">":
                return
            if ty != "f32":
                if x.kind == "num" and ZERO.match(x.op):
                    return
                if parent is not None and (parent.kind in ("index", "unary", "cast") or parent.kind == "binary" and
                                           parent.op not in ("+", "-", "*", "/", "<", ">", "<=", ">=", "==", "!=")):
                    return
            if parent is not None and parent.kind == "call" and parent.kids[0].kind == "id" and \
                    (parent.kids[0].op.isupper() or len(parent.kids[0].op) == 1):
                return
            seen.add((x.s, x.e))
            out.append(x)
            return
        for k in x.kids:
            if k is not None:
                visit(k, x)
    for st, part, top in _all_exprs(u):
        if st.kind != "label":
            visit(top, None)
    return out


def _ndecls(u, name):
    """How many declarations of `name` the function has (a for loop's own counted once)."""
    return len({id(d) for d in u.decls if d.kind == "decl" and d.p["name"] == name})


def _single_decl(u, name):
    return _ndecls(u, name) == 1 and name not in {p[2] for p in u.params}


def _block_decls(u):
    """(block, index, decl) of every declaration that is an item of a block."""
    for b in blocks(u):
        for k, st in enumerate(b.p["items"]):
            if st.kind == "decl":
                yield b, k, st


def _plain_value_local(u, st):
    """A declaration `T x = e;` whose x is never assigned again nor has its address taken."""
    if not st.p["init"] or st.p["multi"] or st.p["dims"] or st.p["ctor"]:
        return False
    ty = u.text_of(*st.p["type"])
    name = st.p["name"]
    if "&" in ty or re.search(r"\bstatic\b", ty) or name in u.addr_taken or not _single_decl(u, name):
        return False
    if u.text_of(*st.p["init"]).lstrip().startswith("{"):
        return False
    return not _assigned(u, name, st.p["name_at"])


def t_named_constants(ctx):
    """A constant used in a loop body named by a local of that body (`f32 half = 0.5f;`, at the
    body's top or before its first use), a constant used more than once named by one local at the
    function's top, and the reverse: a local set to a constant and never changed written as the
    constant at each use (func_00131F60, docs/toolchain/loops.md, "Named constants that lose their
    registers")."""
    u = ctx.u
    groups = {}
    for x in _constants(u):
        groups.setdefault(_toks_key(u, x.s, x.e), []).append(x)
    pos, top_ind, _ = _top_insert(u)
    loops = [st for st in u.body.walk() if st.kind in ("for", "while", "do") and st.p["body"].kind == "block"
             and st.p["body"].p["items"]]
    for key, xs in groups.items():
        ty = _const_type(xs[0])
        text = u.text_of(xs[0].s, xs[0].e)
        name = _fresh(u, "k")
        if len(xs) >= 2:
            edits = [(u.cstart(x.s), u.cend(x.e), name) for x in xs]
            edits.append((pos, pos, "\n%s%s %s = %s;" % (top_ind, ty, name, text)))
            yield ctx.label("name-constant", xs[0].s, "%s at the top" % short(text, 24)), edits
        for loop in loops:
            b = loop.p["body"]
            inside = [x for x in xs if b.s < x.s and x.e < b.e]
            if not inside:
                continue
            items = b.p["items"]
            ind = u.indent_at(items[0].s)
            first = next(k for k, it in enumerate(items) if it.s <= inside[0].s < it.e)
            for k, what in sorted({0: "top", first: "use"}.items()):
                at = u.cstart(items[k].s)
                edits = [(u.cstart(x.s), u.cend(x.e), name) for x in inside]
                edits.append((at, at, "%s %s = %s;\n%s" % (ty, name, text, u.indent_at(items[k].s) if k else ind)))
                yield ctx.label("name-constant", inside[0].s, "%s in the loop of line %d (%s)" % (
                    short(text, 24), u.line_of(loop.s), what)), edits
    # the reverse: a named constant written as its literal
    for b, k, st in _block_decls(u):
        if not _plain_value_local(u, st):
            continue
        try:
            init = u.expr(*st.p["init"])
        except ParseError:
            continue
        if not _const_expr(init):
            continue
        uses = [i for i in _uses(u, st.p["name"]) if i != st.p["name_at"]]
        if not uses:
            continue
        itext = u.text_of(init.s, init.e)
        edits = [_replace_stmt(u, st, "")] + [(u.cstart(i), u.cend(i + 1), _placed(u, i, i + 1, itext, init)) for i in uses]
        yield ctx.label("literal", st.s, st.p["name"]), edits


def _dup_ok(ctx, x):
    """Whether x may be evaluated again where it was evaluated once: no assignment or increment,
    and calls only of VU0 helpers or of the file's pure helpers."""
    for n in x.walk():
        if n.kind == "assign" or n.kind in ("unary", "postfix") and n.op in ("++", "--"):
            return False
        if n.kind == "call":
            c = n.kids[0]
            if c.kind != "id" or not (c.op.startswith("Vu0::") or c.op.split("::")[-1] in ctx.eff.pure):
                return False
    return True


def _value_effects(ctx, x):
    """x's effects, its VU0 and helper calls read as values (they touch no memory of their own)."""
    names = {n.kids[0].op.split("::")[-1] for n in x.walk() if n.kind == "call" and n.kids[0].kind == "id"}
    return Effects(ctx.u, ctx.eff.pure | names).expr(x)


def _untouched(ctx, eff, items, k, j, start, uses):
    """Whether an expression (its effects `eff`) evaluated at token `start` has the same value at
    each of `uses` (token indices, in items k..j of a block): no local it reads is written between
    `start` and the last use, nor in a loop that holds a use and starts after `start`; no
    statement of items k..j writes memory it reads."""
    u = ctx.u
    loops = [L for L in u.body.walk() if L.kind in ("for", "while", "do") and L.s >= start and
             any(L.s <= i < L.e and not (L.kind == "for" and L.p["init_span"][0] <= i < L.p["init_span"][1])
                 for i in uses)]
    for name in eff.reads:
        if name not in u.locals:
            continue
        for w in _uses(u, name):
            nxt = u.toks[w + 1].text if w + 1 < len(u.toks) else ""
            if not (nxt in ASSIGN or nxt in ("++", "--") or u.toks[w - 1].text in ("++", "--")):
                continue
            if start < w < max(uses) or any(L.s <= w < L.e for L in loops):
                return False
    if eff.mr:
        for m in range(k, j + 1):
            if _mem_conflict(ctx.eff.stmt(items[m]).mw, eff.mr):
                return False
    return True


def _local_type(u, name):
    ds = list({id(d): d for d in u.decls if d.kind == "decl" and d.p["name"] == name}.values())
    if len(ds) == 1 and not ds[0].p["dims"]:
        return _canon(u.text_of(*ds[0].p["type"]))
    for ty, _, pname in u.params:
        if pname == name:
            return _canon(ty)
    return None


def _return_type(ctx, name):
    """The return type of a function or helper named in a call, from the file and its headers."""
    if name.startswith("Vu0::Vec::"):
        return "Vu0::Vec"
    if not hasattr(ctx, "_rtypes"):
        ctx._rtypes = {}
    base = name.split("::")[-1]
    if base not in ctx._rtypes:
        found = None
        pat = re.compile(r"(?:^|[;{}\n])\s*(?:template\s*<[^>]*>\s*)?(?:static\s+|inline\s+|extern\s+|virtual\s+)*"
                         r"((?:const\s+)?[\w:]+(?:\s*[\*&])*)\s+%s\s*\(" % re.escape(base))
        for src in [ctx.u.text] + ctx.headers:
            for m in pat.finditer(src):
                ty = m.group(1)
                if ty.split()[-1] not in KEYWORDS and ty not in ("else", "return"):
                    found = _canon(ty).rstrip("&").strip()
                    break
            if found:
                break
        ctx._rtypes[base] = found
    return ctx._rtypes[base]


def _type_of(ctx, x):
    """The type of an expression where the text tells it, else None."""
    k = x.kind
    if k == "num":
        return _const_type(x)
    if k == "paren":
        return _type_of(ctx, x.kids[0])
    if k == "id":
        return _local_type(ctx.u, x.op)
    if k == "cast":
        return _canon(ctx.u.text_of(*x.extra))
    if k == "unary":
        if x.op == "!":
            return "s32"
        t = _type_of(ctx, x.kids[0])
        if x.op == "*":
            return t[:-1].strip() if t and t.endswith("*") else None
        return t if x.op in ("-", "~", "+") else None
    if k == "binary":
        if x.op in ("==", "!=", "<", ">", "<=", ">=", "&&", "||"):
            return "s32"
        a, b = (_type_of(ctx, kk) for kk in x.kids)
        if x.op in ("<<", ">>"):
            return a
        if "f32" in (a, b):
            return "f32"
        if a and a.endswith("*"):
            return "s32" if b and b.endswith("*") else a
        t = a if a == b or b is None else (a if a is not None and WIDTH_BITS.get(a, 0) >= WIDTH_BITS.get(b, 0) else b)
        return "s32" if t in ("s8", "u8", "s16", "u16") else t
    if k == "ternary":
        return _type_of(ctx, x.kids[1])
    if k == "call" and x.kids[0].kind == "id":
        return _return_type(ctx, x.kids[0].op)
    return None


def _lvalue_place(u, x):
    """Whether x is written or has its address taken where it stands, or is a method's callee."""
    prev = u.toks[x.s - 1] if x.s > 0 else None
    nxt = u.toks[x.e].text if x.e < len(u.toks) else ""
    if prev is not None and prev.text in ("++", "--"):
        return True
    if prev is not None and prev.text == "&" and x.s >= 2 and (u.toks[x.s - 2].kind == "op" and
                                                               u.toks[x.s - 2].text not in (")", "]")):
        return True
    return _written_through(u, x.e - 1) or x.kind == "member" and nxt == "("


def _innermost_block(u, lo, hi):
    best = None
    for b in blocks(u):
        if b.s < lo and hi <= b.e - 1 and (best is None or b.e - b.s < best.e - best.s):
            best = b
    return best


def t_repeat_expression(ctx):
    """A local that only carries an expression used several times removed and the expression
    written at each use, and the reverse: an expression written several times named once by a
    local before its first use (func_001D5678, docs/toolchain/gcse.md, "One reaching register for
    every occurrence")."""
    u = ctx.u
    for b, k, st in _block_decls(u):
        if not _plain_value_local(u, st):
            continue
        try:
            init = u.expr(*st.p["init"])
        except ParseError:
            continue
        if _const_expr(init) or not _dup_ok(ctx, init):
            continue
        name = st.p["name"]
        uses = [i for i in _uses(u, name) if i != st.p["name_at"]]
        if len(uses) < 2 or any(_written_through(u, i) for i in uses):
            continue
        items = b.p["items"]
        j = next((j for j in range(k + 1, len(items)) if items[j].s <= uses[-1] < items[j].e), None)
        if j is None or not _untouched(ctx, _value_effects(ctx, init), items, k + 1, j, st.e - 1, uses):
            continue
        itext = u.text_of(init.s, init.e)
        edits = [_replace_stmt(u, st, "")] + [(u.cstart(i), u.cend(i + 1), _placed(u, i, i + 1, itext, init)) for i in uses]
        yield ctx.label("write-at-uses", st.s, name), edits
    # the reverse: name an expression written several times
    groups, seen = {}, set()
    for st, part, top in _all_exprs(u):
        if st.kind == "label":
            continue
        for x in top.walk():
            if x.kind not in ("binary", "call", "member", "index", "cast", "unary") or (x.s, x.e) in seen:
                continue
            seen.add((x.s, x.e))
            if x.kind == "unary" and x.op in ("&", "++", "--") or x.kind == "binary" and x.op in (",", "&&", "||"):
                continue
            if x.e - x.s < 3 or _const_expr(x) or not _dup_ok(ctx, x) or _lvalue_place(u, x):
                continue
            groups.setdefault(_toks_key(u, x.s, x.e), []).append(x)
    for key, every in groups.items():
        every.sort(key=lambda x: x.s)
        # every run of two or more consecutive occurrences
        for a in range(len(every)):
            for c in range(a + 2, len(every) + 1):
                yield from _name_repeat(ctx, u, key, every[a:c])


def _name_repeat(ctx, u, key, xs):
    b = _innermost_block(u, xs[0].s, xs[-1].e)
    if b is None:
        return
    items = b.p["items"]
    k = next((k for k, it in enumerate(items) if it.s <= xs[0].s < it.e), None)
    j = next((j for j, it in enumerate(items) if it.s <= xs[-1].s < it.e), None)
    if k is None or j is None:
        return
    ids = {n.op for n in xs[0].walk() if n.kind == "id" and n.op in u.locals}
    if any(not any(d.kind == "decl" and d.p["name"] == n and d.p["name_at"] < items[k].s for d in u.decls)
           and n not in {p[2] for p in u.params} for n in ids):
        return
    ty = _type_of(ctx, xs[0])
    if ty is None or ty == "void" or \
            not _untouched(ctx, _value_effects(ctx, xs[0]), items, k, j, items[k].s, [x.s for x in xs]):
        return
    name = _fresh(u, "t")
    at = u.cstart(items[k].s)
    edits = [(at, at, "%s %s = %s;\n%s" % (ty, name, u.text_of(xs[0].s, xs[0].e), u.indent_at(items[k].s)))]
    edits += [(u.cstart(x.s), u.cend(x.e), name) for x in xs]
    yield ctx.label("name-repeat", xs[0].s, "%dx %s" % (len(xs), short(key, 30))), edits


def _split_top(toks, s, e):
    """The token ranges of the comma-separated parts of tokens s..e, at depth 0."""
    out, i, start, depth = [], s, s, 0
    while i < e:
        t = toks[i].text
        if t in ("(", "[", "{"):
            depth += 1
        elif t in (")", "]", "}"):
            depth -= 1
        elif t == "," and depth == 0:
            out.append((start, i))
            start = i + 1
        i += 1
    if e > s:
        out.append((start, e))
    return out


_FILE_TOKS = {}


def _file_tokens(text):
    """Every token of a whole file and its bracket pairs (both ways), cached by text."""
    key = hashlib.sha1(text.encode()).hexdigest()
    if key not in _FILE_TOKS:
        if len(_FILE_TOKS) > 64:
            _FILE_TOKS.clear()
        toks = tokenize(text)
        match, back, stack = {}, {}, []
        for i, t in enumerate(toks):
            if t.kind == "op" and t.text in "([{":
                stack.append(i)
            elif t.kind == "op" and t.text in ")]}" and stack:
                o = stack.pop()
                match[o], back[i] = i, o
        _FILE_TOKS[key] = (toks, match, back)
    return _FILE_TOKS[key]


def _name_aliases(name):
    names = {name}
    try:
        import symbols
        c = symbols.canonical(name)
        names |= {c, symbols.readable(c)}
    except Exception:
        pass
    names.discard(None)
    return names


def t_param_order(ctx):
    """One parameter of the definition moved to another place where the calling convention does
    not change: past parameters of the other register file only (a float among integers and
    pointers, or one of those among floats), with every declaration and call in the file
    reordered to follow (func_00185150, docs/toolchain/vu0-helpers.md). The candidate's header
    names the callers in the other files."""
    u = ctx.u
    ps, pe = u.pspan
    spans = _split_top(u.toks, ps, pe)
    if len(spans) < 2 or len(spans) != len(u.params):
        return
    kinds = []
    for s, e in spans:
        words = [t.text for t in u.toks[s:e - 1]]
        if "..." in words or u.toks[e - 1].kind != "id":
            return
        if "*" in words or "&" in words:
            kinds.append("i")
        elif any(w in ("f32", "float") for w in words):
            kinds.append("f")
        elif words and all(w in SCALAR_WORDS or w == "const" for w in words):
            kinds.append("i")
        else:
            return
    if kinds.count("i") > 8 or kinds.count("f") > 8 or len(set(kinds)) < 2:
        return
    texts = [u.text_of(s, e) for s, e in spans]
    names = _name_aliases(u.toks[ps - 2].text)
    toks, match, _ = _file_tokens(u.text)
    own = u.toks[ps - 1].start
    sites = []
    for i, t in enumerate(toks):
        if t.kind == "id" and t.text in names and i + 1 < len(toks) and toks[i + 1].text == "(" and \
                toks[i + 1].start != own and not (i > 0 and toks[i - 1].text in (".", "->")) and i + 1 in match:
            parts = _split_top(toks, i + 2, match[i + 1])
            if len(parts) == len(spans) and all(a < b for a, b in parts):
                sites.append([u.text[toks[a].start:toks[b - 1].end] for a, b in parts] +
                             [(toks[i + 2].start, toks[match[i + 1] - 1].end)])
    n = len(spans)
    for k in range(n):
        for j in range(n):
            if j == k or any(kinds[m] == kinds[k] for m in range(min(k, j), max(k, j) + 1) if m != k):
                continue
            order = list(range(n))
            order.pop(k)
            order.insert(j, k)
            edits = [(u.cstart(ps), u.cend(pe), ", ".join(texts[m] for m in order))]
            for site in sites:
                edits.append((site[-1][0], site[-1][1], ", ".join(site[m] for m in order)))
            yield ctx.label("param-order", ps, "%s to %d" % (u.params[k][2], j + 1)), edits


def _prototypes_in_file(u, name):
    """[(start, end, type)] of the return types of the file's prototypes of `name` (outside the
    definition being searched), or None when the file defines it or declares it otherwise."""
    out = []
    pat = re.compile(r"(?m)^[ \t]*(?:extern\s+)?(void|s32|int)\s+%s\s*\(" % re.escape(name))
    for m in pat.finditer(u.text):
        if u.span[0] <= m.start() < u.span[1]:
            continue
        depth, i = 0, m.end() - 1
        while i < len(u.text):
            if u.text[i] == "(":
                depth += 1
            elif u.text[i] == ")":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        rest = u.text[i + 1:i + 40].lstrip()
        if not rest.startswith(";"):
            return None
        out.append((m.start(1), m.end(1), m.group(1)))
    if len({t for _, _, t in out}) != 1:
        return None
    return out


def _results_unused(text, names):
    """Whether every call in the file of a function named `names` is a statement of its own."""
    toks, match, back = _file_tokens(text)
    for i, t in enumerate(toks):
        if t.kind != "id" or t.text not in names or i + 1 >= len(toks) or toks[i + 1].text != "(":
            continue
        prev = toks[i - 1].text if i else ";"
        if prev in ("void", "s32", "int", "u32", "extern", "*", "::", ".", "->"):
            continue
        close = match.get(i + 1)
        if close is None or close + 1 >= len(toks) or toks[close + 1].text != ";":
            return False
        if prev in (";", "{", "}", "else", ":"):
            continue
        if prev == ")" and i - 1 in back and back[i - 1] > 0 and toks[back[i - 1] - 1].text in ("if", "while", "for"):
            continue
        return False
    return True


def t_callee_return(ctx):
    """A called function's prototype in the file changed between void and s32, where the call's
    result is unused (and, for void, every call of it in the file is a statement): a callee
    declared s32 leaves $v0 to the caller's next value (func_001FA6B0, docs/toolchain/
    alias-classes.md). The candidate's header names the other declarations in src/."""
    u = ctx.u
    done = set()
    for st in u.body.walk():
        if st.kind != "expr":
            continue
        try:
            x = u.expr(*st.p["value"])
        except ParseError:
            continue
        if x.kind != "call" or x.kids[0].kind != "id" or "::" in x.kids[0].op or x.kids[0].op in done:
            continue
        name = x.kids[0].op
        done.add(name)
        protos = _prototypes_in_file(u, name)
        if not protos:
            continue
        old = protos[0][2]
        new = "s32" if old == "void" else "void"
        if new == "void" and not _results_unused(u.text, {name}):
            continue
        yield ctx.label("callee-return", st.s, "%s %s -> %s" % (name, old, new)), [(s, e, new) for s, e, _ in protos]


def _decl_uses(u):
    """[(decl, its uses as token indices, its declaration's included)] of every local declared as
    an item of a block or in a for loop's head, each use given to the innermost declaration of its
    name whose scope holds it."""
    scopes = []
    for st in u.body.walk():
        if st.kind == "block":
            for it in st.p["items"]:
                if it.kind == "decl":
                    scopes.append((it, it.p["name_at"], st.e - 1))
        elif st.kind == "for" and st.p["init"] is not None and st.p["init"].kind == "decl":
            scopes.append((st.p["init"], st.p["init"].p["name_at"], st.e))
    out = []
    for d, s, e in scopes:
        same = [x for x in scopes if x[0].p["name"] == d.p["name"]]
        uses = [i for i in _uses(u, d.p["name"], s, e)
                if min((x for x in same if x[1] <= i < x[2]), key=lambda x: x[2] - x[1])[0] is d]
        out.append((d, uses, (s, e)))
    return out


def _decl_as_assignment(u, d, name):
    """The edit that turns a declaration into an assignment of its initialiser to `name` (or
    removes it when it has none); a for loop's own declaration stays in the loop's head."""
    in_for = u.toks[d.e - 1].text != ";"
    if d.p["init"]:
        text = "%s = %s" % (name, u.text_of(*d.p["init"]))
        return (u.cstart(d.s), u.cend(d.e), text + ("" if in_for else ";"))
    if in_for:
        return (u.cstart(d.s), u.cend(d.e), "")
    return _replace_stmt(u, d, "")


def t_reuse_variable(ctx):
    """Two locals of one type whose lives do not overlap merged into one (declared at the top, the
    second's declaration an assignment): one index for two loops, one int for a size, a count and
    an index; and one local with separate uses split into two at an assignment that starts a new
    life (func_001B7280, func_001FA6B0, docs/toolchain/alias-classes.md, "One int for a size, a
    count and an index")."""
    u = ctx.u
    simple = []
    for d, uses, scope in _decl_uses(u):
        ty = u.text_of(*d.p["type"])
        if d.p["multi"] or d.p["dims"] or d.p["ctor"] or d.p["name"] in u.addr_taken or \
                re.search(r"\b(const|static)\b", ty) or "&" in ty or \
                d.p["init"] and u.text_of(*d.p["init"]).lstrip().startswith("{"):
            continue
        # its life: its uses, its declaration only when that sets it
        life = [i for i in uses if i != d.p["name_at"] or d.p["init"]] or uses
        simple.append((d, life, _canon(ty), ty, scope))
    loops = [st for st in u.body.walk() if st.kind in ("for", "while", "do")]
    pnames = {p[2] for p in u.params}
    pos, top_ind, _ = _top_insert(u)
    body_items = set(id(x) for x in u.body.p["items"])
    for da, ua, ta, tya, _ in simple:
        for db, ub, tb, _, scb in simple:
            if da is db or ta != tb or max(ua) >= min(ub):
                continue
            if any(any(L.s < i < L.e for i in ua) and any(L.s < i < L.e for i in ub) for L in loops):
                continue
            na, nb = da.p["name"], db.p["name"]
            others = [d for d, _, _, _, _ in simple if d is not da and d is not db]
            if na not in pnames and not any(d.p["name"] == na for d in others) and \
                    _ndecls(u, na) <= (2 if na == nb else 1):
                edits = []
                if id(da) not in body_items:
                    edits.append((pos, pos, "\n%s%s %s;" % (top_ind, tya, na)))
                    edits.append(_decl_as_assignment(u, da, na))
                edits.append(_decl_as_assignment(u, db, na))
                if na != nb:
                    edits += [(u.cstart(i), u.cend(i + 1), na) for i in ub if i != db.p["name_at"]]
                yield ctx.label("reuse-variable", db.s, "%s for %s" % (na, nb)), edits
            # the later one declared (without a value) before the first's life, in a scope that
            # holds it: the first's uses take its name
            if na != nb and not db.p["init"] and db.p["name_at"] < min(ua) and scb[0] <= min(ua) and \
                    max(ua) < scb[1] and not any(d.p["name"] == nb for d in others) and nb not in pnames and \
                    _ndecls(u, nb) == 1:
                edits = [_decl_as_assignment(u, da, nb)]
                edits += [(u.cstart(i), u.cend(i + 1), nb) for i in ua if i != da.p["name_at"]]
                yield ctx.label("reuse-variable", da.s, "%s for %s" % (nb, na)), edits
    # split: a new life from a plain assignment on
    for d, us, _, ty, _ in simple:
        name = d.p["name"]
        if _ndecls(u, name) != 1:
            continue
        new = _fresh(u, name)
        points = []
        for b in blocks(u):
            for it in b.p["items"]:
                if it.kind == "expr" and it.s > d.p["name_at"]:
                    points.append((it, b.e - 1, True))
        for st in u.body.walk():
            if st.kind == "for" and st.p["init"] is not None and st.p["init"].kind == "expr" and st.s > d.p["name_at"]:
                points.append((st.p["init"], st.e, False))
        stores = {}
        for p, end, whole in points:
            try:
                x = _assign_of(u, p) if whole else u.expr(*p.p["value"])
            except ParseError:
                continue
            if x is not None and x.kind == "assign" and x.op == "=" and x.kids[0].kind == "id" and \
                    x.kids[0].op == name and not _uses(u, name, x.kids[1].s, x.kids[1].e):
                stores[x.kids[0].s] = (p, end, whole, x)
        for p, end, whole, x in stores.values():
            before = [i for i in us if i < p.s and i != d.p["name_at"]]
            after = [i for i in us if p.e <= i < end]
            if not after or not any(not _is_plain_store(u, i) for i in before):
                continue
            if any(L.s < p.s < L.e and any(L.s < i < p.s for i in us) for L in loops):
                continue
            # the uses after this life's block must each be reached only from a later store of
            # their own (one at the head of a block that holds every use after it)
            rest, ok = [i for i in us if i >= end], True
            while rest and ok:
                nxt = stores.get(rest[0])
                ok = nxt is not None and not any(L.s < rest[0] < L.e and any(L.s < i < rest[0] for i in us)
                                                 for L in loops)
                if ok:
                    rest = [i for i in rest if i >= nxt[1]]
            if not ok:
                continue
            edits = [(u.cstart(p.s), u.cend(p.e), "%s %s = %s%s" % (ty, new, u.text_of(x.kids[1].s, x.kids[1].e),
                                                                     ";" if whole else ""))]
            edits += [(u.cstart(i), u.cend(i + 1), new) for i in after]
            yield ctx.label("split-variable", p.s, "%s from line %d" % (name, u.line_of(p.s))), edits


def _last_stmt(st):
    if st is None:
        return None
    if st.kind == "block":
        return st.p["items"][-1] if st.p["items"] else None
    return st


def t_test_in_arms(ctx):
    """A test of a variable that each arm of the if/else before it sets (`if (a) hit = F(); else
    hit = G(); if (hit) S`) written in each arm instead (`if (a) { if (F()) S } else { if (G()) S }`),
    and the reverse (func_00187F40, docs/toolchain/gcse.md, "A test written in each arm")."""
    u = ctx.u
    for b in blocks(u):
        items = b.p["items"]
        for k, st in enumerate(items):
            if st.kind != "if" or st.p["other"] is None or st.p["other"].kind == "if":
                continue
            try:
                yield from _test_into_arms(ctx, u, items, k, st)
                yield from _test_out_of_arms(ctx, u, st)
            except ParseError:
                continue


def _test_into_arms(ctx, u, items, k, st):
    if k + 1 >= len(items) or items[k + 1].kind != "if":
        return
    test = items[k + 1]
    arms = [st.p["then"], st.p["other"]]
    lasts = [_last_stmt(a) for a in arms]
    xs = [_assign_of(u, s) for s in lasts]
    if any(x is None or x.kids[0].kind != "id" for x in xs) or xs[0].kids[0].op != xs[1].kids[0].op:
        return
    v = xs[0].kids[0].op
    if v not in u.locals or v in u.addr_taken:
        return
    cs, ce = test.p["cond"]
    mine = [(d, us, e - s) for d, us, (s, e) in _decl_uses(u) if d.p["name"] == v and s <= cs < e]
    if not mine:
        return
    decl, uses, _ = min(mine, key=lambda m: m[2])
    occ = [i for i in uses if cs <= i < ce]
    if len(occ) != 1 or decl.p["init"] or u.toks[decl.e - 1].text != ";":
        return
    if [i for i in uses if i not in (decl.p["name_at"], xs[0].kids[0].s, xs[1].kids[0].s, occ[0])]:
        return
    rest = u.text[u.cend(test.p["cond"][1] + 1):u.cend(test.e)]
    edits = [_replace_stmt(u, test, ""), _replace_stmt(u, decl, "")]
    for last, x in zip(lasts, xs):
        val = x.kids[1]
        cond = u.text[u.cstart(cs):u.cstart(occ[0])] + _placed(u, occ[0], occ[0] + 1, u.text_of(val.s, val.e), val) + \
            u.text[u.cend(occ[0] + 1):u.cend(ce)]
        text = "if (%s)%s" % (cond, reindent(rest, u.indent_at(test.s), u.indent_at(last.s)))
        edits.append((u.cstart(last.s), u.cend(last.e), text))
    yield ctx.label("test-in-each-arm", test.s, v), edits


def _diff_part(u, a, b):
    """The one pair of subexpressions where two expressions differ, or None."""
    if _toks_key(u, a.s, a.e) == _toks_key(u, b.s, b.e):
        return None
    if a.kind == b.kind and a.op == b.op and len(a.kids) == len(b.kids) and a.kind in ("binary", "unary", "paren"):
        diff = [(x, y) for x, y in zip(a.kids, b.kids) if _toks_key(u, x.s, x.e) != _toks_key(u, y.s, y.e)]
        if len(diff) == 1:
            return _diff_part(u, *diff[0]) or diff[0]
    return (a, b)


def _test_out_of_arms(ctx, u, st):
    arms = [st.p["then"], st.p["other"]]
    inner = [_last_stmt(a) for a in arms]
    if any(i is None or i.kind != "if" for i in inner):
        return
    t1, t2 = inner

    def key(s):
        return None if s is None else _toks_key(u, s.s, s.e)
    if key(t1.p["then"]) != key(t2.p["then"]) or key(t1.p["other"]) != key(t2.p["other"]):
        return
    c1, c2 = u.expr(*t1.p["cond"]), u.expr(*t2.p["cond"])
    d = _diff_part(u, c1, c2)
    if d is None or d[0].kind != "call" or d[1].kind != "call":
        return
    ty = _type_of(ctx, d[0]) or "s32"
    if ty == "void":
        return
    name = _fresh(u, "hit")
    ind = u.indent_at(st.s)
    cond = u.text[u.cstart(t1.p["cond"][0]):u.cstart(d[0].s)] + name + u.text[u.cend(d[0].e):u.cend(t1.p["cond"][1])]
    rest = u.text[u.cend(t1.p["cond"][1] + 1):u.cend(t1.e)]
    edits = [(u.cstart(st.s), u.cstart(st.s), "%s %s;\n%s" % (ty, name, ind)),
             (u.cend(st.e), u.cend(st.e), "\n%sif (%s)%s" % (ind, cond, reindent(rest, u.indent_at(t1.s), ind)))]
    for t, x in zip(inner, d):
        edits.append((u.cstart(t.s), u.cend(t.e), "%s = %s;" % (name, u.text_of(x.s, x.e))))
    yield ctx.label("test-after-arms", st.s, name), edits


def _switch_groups(u, sw):
    """A switch's arms as [(first item, end item)] of its body, or None when an arm falls through
    or the body is not a list of labelled arms."""
    if sw.p["body"].kind != "block":
        return None
    items = sw.p["body"].p["items"]
    if not items or items[0].kind != "label":
        return None
    groups, k = [], 0
    while k < len(items):
        s = k
        while k < len(items) and items[k].kind == "label":
            k += 1
        while k < len(items) and items[k].kind != "label":
            k += 1
        if k == s or items[k - 1].kind not in ("break", "return", "continue") or items[k - 1].kind == "label":
            return None
        groups.append((s, k))
    return groups


def t_cases(ctx):
    """The order of a switch's arms (none falling through) and of the labels of one arm; a
    variable set before the switch set in every arm instead (a default arm added where there is
    none), and the reverse (func_001B7280, docs/toolchain/loops.md, "A count set in each arm")."""
    u = ctx.u
    for b in blocks(u):
        for k, sw in enumerate(b.p["items"]):
            if sw.kind != "switch":
                continue
            groups = _switch_groups(u, sw)
            if not groups:
                continue
            items = sw.p["body"].p["items"]
            ind = u.indent_at(items[0].s)
            texts = [u.text[u.cstart(items[s].s):u.cend(items[e - 1].e)] for s, e in groups]
            span = (u.cstart(items[0].s), u.cend(items[-1].e))
            n = len(groups)
            for a in range(n):
                for c in range(n):
                    if a == c:
                        continue
                    order = list(range(n))
                    order.pop(a)
                    order.insert(c, a)
                    yield ctx.label("case-order", items[groups[a][0]].s, "arm %d to %d" % (a + 1, c + 1)), [
                        (span[0], span[1], ("\n" + ind).join(texts[m] for m in order))]
            for s, e in groups:
                labels = [it for it in items[s:e] if it.kind == "label"]
                if len(labels) > 1:
                    yield ctx.label("case-order", labels[0].s, "labels reversed"), [
                        (u.cstart(labels[0].s), u.cend(labels[-1].e),
                         ("\n" + ind).join(u.text_of(l.s, l.e) for l in reversed(labels)))]
            try:
                yield from _set_in_arms(ctx, u, b.p["items"], k, sw, groups)
            except ParseError:
                continue


def _arm_store(u, items, s, e, v):
    """The first statement of an arm that is `v = ...;` with nothing reading v before it."""
    for it in items[s:e]:
        if it.kind == "label":
            continue
        if it.kind == "expr":
            x = _assign_of(u, it)
            if x is not None and x.kids[0].kind == "id" and x.kids[0].op == v and not _uses(u, v, x.kids[1].s, x.kids[1].e):
                return it, x
        if _uses(u, v, it.s, it.e):
            return None
    return None


def _set_in_arms(ctx, u, outer, k, sw, groups):
    items = sw.p["body"].p["items"]
    ind = u.indent_at(items[groups[0][0] + 1].s) if groups[0][0] + 1 < len(items) else u.indent_at(items[0].s) + "    "
    lind = u.indent_at(items[0].s)
    has_default = any(it.kind == "label" and u.toks[it.s].text == "default" for it in items)
    # forward: `T v = K;` or `v = K;` just before the switch
    if k > 0:
        prev = outer[k - 1]
        v = val = None
        if prev.kind == "decl" and prev.p["init"] and not prev.p["multi"]:
            v, val = prev.p["name"], u.expr(*prev.p["init"])
        elif prev.kind == "expr":
            x = _assign_of(u, prev)
            if x is not None and x.kids[0].kind == "id":
                v, val = x.kids[0].op, x.kids[1]
        if v is not None and v in u.locals and v not in u.addr_taken and (_const_expr(val) or val.kind == "id") and \
                not _uses(u, v, sw.p["cond"][0], sw.p["cond"][1]):
            vt = u.text_of(val.s, val.e)
            edits = []
            if prev.kind == "decl":
                edits.append((u.cstart(prev.s), u.cend(prev.e), "%s %s;" % (u.text_of(*prev.p["type"]), v)))
            else:
                edits.append(_replace_stmt(u, prev, ""))
            for s, e in groups:
                if _arm_store(u, items, s, e, v) is None:
                    first = next(it for it in items[s:e] if it.kind != "label")
                    at = u.cstart(first.s)
                    edits.append((at, at, "%s = %s;\n%s" % (v, vt, u.indent_at(first.s))))
            if not has_default:
                # without a default arm v is left unset for the values no arm takes (where the
                # original never reads it), or set there by a new default arm
                yield ctx.label("set-in-arms", sw.s, v + " (no default)"), list(edits)
                at = u.cend(items[-1].e)
                edits.append((at, at, "\n%sdefault:\n%s%s = %s;\n%sbreak;" % (lind, ind, v, vt, ind)))
            yield ctx.label("set-in-arms", sw.s, v), edits
    # reverse: every arm sets v to one value first
    cands = {}
    for s, e in groups:
        names = set()
        for it in items[s:e]:
            if it.kind == "expr":
                x = _assign_of(u, it)
                if x is not None and x.kids[0].kind == "id":
                    names.add(x.kids[0].op)
        for v in names:
            cands[v] = cands.get(v, 0) + 1
    for v, count in cands.items():
        if count != len(groups) or v not in u.locals or v in u.addr_taken:
            continue
        stores = [_arm_store(u, items, s, e, v) for s, e in groups]
        if any(x is None for x in stores):
            continue
        vals = {_toks_key(u, x.kids[1].s, x.kids[1].e) for _, x in stores}
        if len(vals) != 1:
            continue
        val = stores[0][1].kids[1]
        if not (_const_expr(val) or val.kind == "id" and val.op not in u.locals):
            continue
        vt = u.text_of(val.s, val.e)
        edits = [_replace_stmt(u, it, "") for it, _ in stores]
        prev = outer[k - 1] if k > 0 else None
        if prev is not None and prev.kind == "decl" and prev.p["name"] == v and not prev.p["init"] and not prev.p["multi"]:
            edits.append((u.cstart(prev.s), u.cend(prev.e), "%s %s = %s;" % (u.text_of(*prev.p["type"]), v, vt)))
        else:
            at = u.cstart(sw.s)
            edits.append((at, at, "%s = %s;\n%s" % (v, vt, u.indent_at(sw.s))))
        yield ctx.label("set-before-switch", sw.s, v), edits


def t_chained(ctx):
    """`a = v; b = v;` with one value written `b = a = v;` or `a = b = v;` (and `a = v; b = a;`), and
    the reverse (func_00109488, docs/toolchain/long-block-constants.md, "The source form of
    func_00109488": a chain expands with one constant and stores its inner target first)."""
    u = ctx.u
    for b in blocks(u):
        items = b.p["items"]
        for k, st in enumerate(items):
            if st.kind != "expr":
                continue
            try:
                x = _assign_of(u, st)
                y = _assign_of(u, items[k + 1]) if k + 1 < len(items) and items[k + 1].kind == "expr" else None
            except ParseError:
                continue
            if x is None:
                continue
            ind = u.indent_at(st.s)
            span = (u.cstart(st.s), u.cend(st.e))
            if x.kids[1].kind == "assign" and x.kids[1].op == "=":
                a, (bb, v) = x.kids[0], x.kids[1].kids
                if v.kind == "assign" or not all(simple_rvalue(n) for n in (a, bb, v)):
                    continue
                at, bt, vt = (u.text_of(n.s, n.e) for n in (a, bb, v))
                for what, text in (("inner first", "%s = %s;\n%s%s = %s;" % (bt, vt, ind, at, vt)),
                                   ("outer first", "%s = %s;\n%s%s = %s;" % (at, vt, ind, bt, vt)),
                                   ("copied", "%s = %s;\n%s%s = %s;" % (bt, vt, ind, at, bt))):
                    yield ctx.label("unchain", st.s, what), [(span[0], span[1], text)]
                continue
            if y is None or y.kids[1].kind == "assign" or not simple_rvalue(x.kids[1]) or \
                    not simple_rvalue(x.kids[0]) or not simple_rvalue(y.kids[0]):
                continue
            at, bt = u.text_of(x.kids[0].s, x.kids[0].e), u.text_of(y.kids[0].s, y.kids[0].e)
            vt = u.text_of(x.kids[1].s, x.kids[1].e)
            if at == bt:
                continue
            both = (u.cstart(st.s), u.cend(items[k + 1].e))
            same = _toks_key(u, x.kids[1].s, x.kids[1].e) == _toks_key(u, y.kids[1].s, y.kids[1].e)
            a_key = _toks_key(u, x.kids[0].s, x.kids[0].e)
            reads_a = a_key in _toks_key(u, y.kids[1].s, y.kids[1].e) or a_key in _toks_key(u, y.kids[0].s, y.kids[0].e)
            if same and not reads_a:
                yield ctx.label("chain", st.s, "b first"), [(both[0], both[1], "%s = %s = %s;" % (at, bt, vt))]
                yield ctx.label("chain", st.s, "a first"), [(both[0], both[1], "%s = %s = %s;" % (bt, at, vt))]
            elif _toks_key(u, y.kids[1].s, y.kids[1].e) == a_key and \
                    a_key not in _toks_key(u, y.kids[0].s, y.kids[0].e):
                yield ctx.label("chain", st.s, "copy"), [(both[0], both[1], "%s = %s = %s;" % (bt, at, vt))]


def t_struct_store(ctx):
    """A VU0 vector stored through Vu0::Q (`Vu0::Q(x) = v.q;`) against through a structure cast
    of the same address (`*(Vu0::Vec*)&x = v;`): a structure store does not hold a scalar load in
    sched1 (func_0019ED58, docs/toolchain/sched1.md, "Which of two sums issues first")."""
    u = ctx.u
    for st in u.body.walk():
        if st.kind != "expr":
            continue
        try:
            x = _assign_of(u, st)
        except ParseError:
            continue
        if x is None:
            continue
        l, r = x.kids
        if l.kind == "call" and l.kids[0].kind == "id" and l.kids[0].op == "Vu0::Q" and len(l.kids) == 2 and \
                r.kind == "member" and r.op == "." and r.extra == "q":
            lv = l.kids[1]
            if lv.kind not in ("id", "member", "index"):
                continue
            yield ctx.label("struct-store", st.s, short(u.text_of(lv.s, lv.e), 24)), [
                (u.cstart(x.s), u.cend(x.e), "*(Vu0::Vec*)&%s = %s" % (u.text_of(lv.s, lv.e), u.text_of(r.kids[0].s, r.kids[0].e)))]
        elif l.kind == "unary" and l.op == "*" and l.kids[0].kind == "cast" and \
                u.text_of(*l.kids[0].extra).replace(" ", "") == "Vu0::Vec*" and \
                l.kids[0].kids[0].kind == "unary" and l.kids[0].kids[0].op == "&":
            lv = l.kids[0].kids[0].kids[0]
            yield ctx.label("q-store", st.s, short(u.text_of(lv.s, lv.e), 24)), [
                (u.cstart(x.s), u.cend(x.e), "Vu0::Q(%s) = %s.q" % (u.text_of(lv.s, lv.e), wrap(u, r)))]


TRANSFORMS = [
    ("reorder", t_reorder),
    ("loops", t_loops),
    ("conditionals", t_conditionals),
    ("compound", t_compound),
    ("operands", t_operands),
    ("zero-tests", t_zero_tests),
    ("decls", t_decls),
    ("types", t_types),
    ("widths", t_widths),
    ("pointer-ref", t_pointer_ref),
    ("arguments", t_arguments),
    ("switch", t_switch),
    ("walks", t_walks),
    ("element", t_element),
    ("returns", t_returns),
    ("helpers", t_helpers),
    ("vu0", t_vu0),
    ("named-constant", t_named_constants),
    ("repeat-expression", t_repeat_expression),
    ("param-order", t_param_order),
    ("callee-return", t_callee_return),
    ("reuse-variable", t_reuse_variable),
    ("test-in-each-arm", t_test_in_arms),
    ("case-order", t_cases),
    ("chained-assignment", t_chained),
    ("struct-store", t_struct_store),
]


# ---------------------------------------------------------------------------------------------
# What a candidate may not hold (AGENTS.md, "Matching rules").

FORBIDDEN = [
    ("inline assembly", re.compile(r"\b(?:asm|__asm__|__asm)\b")),
    ("a register variable", re.compile(r"\bregister\b")),
    ("volatile", re.compile(r"\bvolatile\b")),
    ("do { } while (0)", re.compile(r"while\s*\(\s*0\s*\)")),
    ("goto", re.compile(r"\bgoto\b")),
    ("an empty statement", re.compile(r"(?<!\()\s*;\s*;(?!\s*\))|\{\s*;|\}\s*;")),
    ("x ^ 0, x + 0, x | 0", re.compile(r"[\^|]\s*0\b(?!\.|x)")),
    ("a comma expression statement", re.compile(r"^\s*\(?\s*\w+\s*,\s*\w+\s*\)?\s*;", re.M)),
]


def forbidden(old_text, new_text, func, ou=None, nu=None):
    """The reasons `new_text`'s definition of FUNC breaks AGENTS.md's rules where `old_text`'s does
    not: more of a forbidden construct, a self-assignment, a new array local, or a local that is
    never read (a dead store or a padding local). An empty list when it is plain C++. `ou` and
    `nu` are the two texts' Units when the caller has them."""
    reasons = []
    try:
        ou = ou or Unit(old_text, func)
        nu = nu or Unit(new_text, func, base=ou)
    except (ParseError, StopIteration):
        return ["does not parse"]
    old = _strip_comments(old_text[ou.span[0]:ou.span[1]])
    new = _strip_comments(new_text[nu.span[0]:nu.span[1]])
    for what, pat in FORBIDDEN:
        if len(pat.findall(new)) > len(pat.findall(old)):
            reasons.append(what)
    for m in re.finditer(r"(?<![\w.>])(\w+(?:(?:\.|->)\w+)*)\s*=\s*(\w+(?:(?:\.|->)\w+)*)\s*;", new):
        if m.group(1) == m.group(2):
            reasons.append("a self-assignment (%s)" % m.group(1))
    old_arrays = {st.p["name"] for st in ou.decls if st.kind == "decl" and st.p["dims"]}
    old_unread = {st.p["name"] for st in ou.decls if st.kind == "decl" and not _reads(ou, st)}
    for st in nu.decls:
        if st.kind != "decl":
            continue
        name = st.p["name"]
        if st.p["dims"] and name not in old_arrays:
            reasons.append("a new array local (%s)" % name)
        if not _reads(nu, st) and name not in old_unread:
            reasons.append("a local never read (%s)" % name)
    return reasons


def _reads(u, st):
    """The uses of a declared local that read it (not its declaration, not a plain `x = ...`)."""
    return [i for i in _uses(u, st.p["name"]) if i != st.p["name_at"] and not _is_plain_store(u, i)]


def _is_plain_store(u, i):
    """Token i (a local's name) is the target of a plain `=` and nothing else."""
    nxt = u.toks[i + 1].text if i + 1 < len(u.toks) else ""
    prev = u.toks[i - 1].text if i > 0 else ""
    return nxt == "=" and prev not in (".", "->", "&", "*")


def _strip_comments(text):
    return re.sub(r"//[^\n]*|/\*.*?\*/", "", text, flags=re.S)


def rewrites(text, func, only=None, skip=(), path=None):
    """[(label, text)] of every single rewrite of FUNC's definition in `text` that parses and
    passes forbidden()."""
    u = Unit(text, func)
    ctx = Ctx(u, path)
    out, seen = [], {normalize(text)}
    for name, fn in TRANSFORMS:
        if only and name not in only or name in skip:
            continue
        try:
            for label, edits in fn(ctx):
                new = apply_edits(text, edits)
                key = normalize(new)
                if key in seen:
                    continue
                seen.add(key)
                try:
                    nu = Unit(new, func, base=u)
                except (ParseError, StopIteration):
                    continue
                if forbidden(text, new, func, u, nu):
                    continue
                out.append((label, new))
        except (ParseError, StopIteration, IndexError, KeyError):
            continue
    return out


def normalize(text):
    return re.sub(r"\s+", " ", _strip_comments(text)).strip()


# ---------------------------------------------------------------------------------------------
# Scoring


def score_of(ours, retail):
    """(instructions of retail's that do not line up registers aside, plus the difference in
    count; then the words that differ): (0, 0) is EXACT."""
    import regdiff
    verdict, agree, total = regdiff.classify(ours, retail)
    if verdict == "EXACT":
        return (0, 0)
    words = sum(1 for a, b in zip(ours, retail) if a[0] != b[0]) + abs(len(ours) - len(retail))
    return (total - agree + abs(len(ours) - len(retail)), max(words, 1))


class Scorer:
    """Compiles a candidate the way the function lands and scores it against retail."""

    def __init__(self, func, path, key="us", work=None):
        import check
        import compile as cc
        self.check, self.cc = check, cc
        self.func, self.key = func, key
        self.source = check.source_for(path, func)
        self.resolver = check.Resolver(key)
        self.image = check.retail_image(key)
        self.addr, self.size = check.target_of(key, func)
        self.work = Path(work or tempfile.mkdtemp(prefix="sly1-tsearch-"))
        self.work.mkdir(parents=True, exist_ok=True)
        self.retail = None
        self.suffix = ".c" if Path(path).suffix == ".c" else ".cpp"

    def score(self, text, tag):
        """(score, code hash) or (None, None) when it does not compile."""
        import elf
        src = self.work / ("%s%s" % (tag, self.suffix))
        obj = self.work / ("%s.o" % tag)
        src.write_text(text)
        try:
            self.cc.compile_file(src, obj, source=self.source)
            r = self.check.check_function(elf.Elf(obj.read_bytes()), self.func, self.key, self.resolver, self.image)
        except (self.cc.CompileError, KeyError, ValueError):
            return None, None
        finally:
            for p in (src, obj):
                if p.exists():
                    p.unlink()
        if "ours" not in r:
            return None, None
        if r["status"] == "EXACT":
            return (0, 0), hashlib.sha1(r["ours"]).hexdigest()
        if self.retail is None:
            self.retail = self.check.disassemble(r["retail"][:self.size], r["address"])
        ours = self.check.disassemble(r["ours"], r["address"])
        s = score_of(ours, self.retail)
        if s == (0, 0):
            s = (0, 1)      # same instructions, but check.py did not say EXACT (padding, size)
        return s, hashlib.sha1(r["ours"]).hexdigest()


# ---------------------------------------------------------------------------------------------
# The search


class Cand:
    __slots__ = ("text", "chain", "score", "code")

    def __init__(self, text, chain, score=None, code=None):
        self.text, self.chain, self.score, self.code = text, chain, score, code


def callers_of(func):
    """The files of src/ (and the lines) that mention FUNC by its address name or its readable name,
    its declarations and callers, whose code a changed parameter changes too."""
    import symbols
    names = {func, symbols.readable(func)}
    names.discard(None)
    pat = re.compile(r"\b(?:%s)\b" % "|".join(re.escape(n) for n in sorted(names)))
    found = []
    for path in sorted((ROOT / "src").rglob("*.cpp")) + sorted((ROOT / "src").rglob("*.c")):
        try:
            lines = path.read_text().splitlines()
        except OSError:
            continue
        for n, line in enumerate(lines, 1):
            if pat.search(line):
                found.append("%s:%d" % (path.relative_to(ROOT), n))
    return found


def width_notes(cand, func):
    """A header comment for a candidate that changed a parameter's width or order, or a callee's
    return type: the declarations and callers elsewhere in src/ that would have to follow."""
    out = ""
    if any(c.startswith("width@") and " param " in c for c in cand.chain):
        callers = callers_of(func)
        out += "// NOTE: a parameter's width changed: every caller's code changes too (declaration and callers):\n" + \
            "".join("//   %s\n" % c for c in callers[:12]) + ("//   (none found in src/)\n" if not callers else "")
    if any(c.startswith("param-order@") for c in cand.chain):
        callers = callers_of(func)
        out += "// NOTE: the parameters' order changed (the registers do not): every declaration and call\n" + \
            "// in the other files must follow:\n" + \
            "".join("//   %s\n" % c for c in callers[:20]) + ("//   (none found in src/)\n" if not callers else "")
    for c in cand.chain:
        m = re.match(r"callee-return@\d+ (\S+) (\w+) -> (\w+)", c)
        if m:
            decls = declarations_of(m.group(1))
            out += "// NOTE: %s declared %s here (%s before): its other declarations in src/ must agree:\n" % (
                m.group(1), m.group(3), m.group(2)) + \
                "".join("//   %s\n" % d for d in decls[:20]) + ("//   (none found in src/)\n" if not decls else "")
    return out


def declarations_of(name):
    """The lines of src/ that declare or define the function `name` (either of its names)."""
    names = _name_aliases(name)
    pat = re.compile(r"\b(?:void|s32|int|u32|u8|s8|u16|s16|f32|bool)\s*\*?\s+(?:%s)\s*\(" %
                     "|".join(re.escape(n) for n in sorted(names)))
    found = []
    for path in sorted((ROOT / "src").rglob("*.cpp")) + sorted((ROOT / "src").rglob("*.c")):
        try:
            lines = path.read_text().splitlines()
        except OSError:
            continue
        for n, line in enumerate(lines, 1):
            if pat.search(line):
                found.append("%s:%d: %s" % (path.relative_to(ROOT), n, line.strip()))
    return found


def write_result(outdir, name, cand, func, base_score):
    path = outdir / name
    header = "// tsearch %s: score %s (start %s)\n// chain: %s\n" % (
        func, cand.score, base_score, "; ".join(cand.chain) or "(start)")
    notes = width_notes(cand, func)
    if notes:
        header += notes
    text = cand.text
    if text.startswith("// SPDX"):
        first, rest = text.split("\n", 1)
        text = first + "\n" + header + rest
    else:
        text = header + text
    path.write_text(text)
    return path


def search(func, path, minutes=20.0, jobs=3, beam=6, depth=4, only=None, skip=(), key="us",
           outdir=None, log=print, max_pool=4000):
    """Beam search from the near miss at `path`. Returns the best Cand."""
    deadline = time.time() + minutes * 60
    outdir = Path(outdir or OUT / func)
    outdir.mkdir(parents=True, exist_ok=True)
    for old in list(outdir.glob("best_*.cpp")) + list(outdir.glob("EXACT*.cpp")):
        old.unlink()
    scorer = Scorer(func, path, key, work=outdir / "work")
    text = Path(path).read_text()
    start = Cand(text, [])
    start.score, start.code = scorer.score(text, "start")
    if start.score is None:
        raise SystemExit("%s does not compile as it is" % path)
    log("%s: start score %s" % (func, start.score))
    logf = (outdir / "log.tsv").open("w")
    logf.write("depth\tscore\tcode\tchain\n")
    best = start
    seen = {normalize(text)}
    beam_set = [start]
    nbest = 0
    compiled = 0
    by_code = {start.code: start.score}
    for d in range(1, depth + 1):
        pool = []
        for parent in beam_set:
            try:
                rws = rewrites(parent.text, func, only, skip, path)
            except (ParseError, StopIteration) as e:
                log("  cannot parse a candidate (%s): %s" % ("; ".join(parent.chain), e))
                continue
            for label, new in rws:
                k = normalize(new)
                if k in seen:
                    continue
                seen.add(k)
                pool.append(Cand(new, parent.chain + [label]))
        if len(pool) > max_pool:
            pool = pool[:max_pool]
        log("depth %d: %d candidates from %d in the beam" % (d, len(pool), len(beam_set)))
        if not pool:
            log("  no rewrite of the beam is new: the space it reaches is exhausted")
            break
        done = []
        stop = False
        with concurrent.futures.ThreadPoolExecutor(jobs) as ex:
            futs = {}
            it = iter(enumerate(pool))
            def submit():
                for n, c in it:
                    futs[ex.submit(scorer.score, c.text, "d%d_%d_%d" % (d, n, os.getpid()))] = c
                    return True
                return False
            for _ in range(jobs * 2):
                submit()
            while futs:
                fin, _ = concurrent.futures.wait(list(futs), return_when=concurrent.futures.FIRST_COMPLETED)
                for f in fin:
                    c = futs.pop(f)
                    c.score, c.code = f.result()
                    compiled += 1
                    if not stop and time.time() < deadline:
                        submit()
                    if c.score is None:
                        logf.write("%d\tnone\t-\t%s\n" % (d, "; ".join(c.chain)))
                        continue
                    done.append(c)
                    by_code.setdefault(c.code, c.score)
                    logf.write("%d\t%s\t%s\t%s\n" % (d, c.score, c.code[:10], "; ".join(c.chain)))
                    if c.score < best.score:
                        best = c
                        nbest += 1
                        p = write_result(outdir, "best_%02d.cpp" % nbest, c, func, start.score)
                        log("  better: %s  %s  (%s)" % (c.score, "; ".join(c.chain), p.name))
                    if c.score == (0, 0):
                        write_result(outdir, "EXACT.cpp", c, func, start.score)
                        log("  EXACT: %s" % "; ".join(c.chain))
                        stop = True
                logf.flush()
        if stop or time.time() >= deadline:
            break
        # The next beam: the best of this step (the beam's own are rewritten already), distinct
        # code first, then the best of what is left.
        ranked = sorted(done, key=lambda c: (c.score, len(c.chain)))
        if beam <= 0:
            # Exhaustive: every code this step reached is rewritten again (the closure to --depth),
            # through its first two texts: rewrites that change no byte multiply the texts, not
            # the codes (func_0020A190: 7,139 texts, 73 codes).
            per = {}
            beam_set = [c for c in sorted(done, key=lambda c: len(c.chain))
                        if per.setdefault(c.code, []).append(c) or len(per[c.code]) <= 2]
            continue
        nxt, codes = [], set()
        for c in ranked:
            if c.code not in codes:
                nxt.append(c)
                codes.add(c.code)
            if len(nxt) >= beam:
                break
        for c in ranked:
            if len(nxt) >= beam:
                break
            if c not in nxt:
                nxt.append(c)
        beam_set = nxt
    logf.close()
    log("%s: best %s after %d compiles, %d distinct codes: %s" % (
        func, best.score, compiled, len(by_code), "; ".join(best.chain) or "(start)"))
    return best, start, compiled


def main(argv=None):
    import symbols
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("func", nargs="?")
    parser.add_argument("--file", help="the near miss (default nonmatching/FUNC.cpp)")
    parser.add_argument("--minutes", type=float, default=20.0)
    parser.add_argument("--jobs", type=int, default=3)
    parser.add_argument("--beam", type=int, default=6, help="candidates kept per step (0: all, exhaustive)")
    parser.add_argument("--depth", type=int, default=4)
    parser.add_argument("--only", help="rewrites to use (names from --transforms), comma-separated")
    parser.add_argument("--skip", help="rewrites to leave out, comma-separated")
    parser.add_argument("--version", default="us", choices=["us", "eu"])
    parser.add_argument("--list", action="store_true", help="print one step's rewrites, compile nothing")
    parser.add_argument("--transforms", action="store_true", help="list the rewrites")
    args = parser.parse_args(argv)
    if args.transforms:
        for name, fn in TRANSFORMS:
            print("%-13s %s" % (name, " ".join(fn.__doc__.split())))
        return 0
    if not args.func:
        parser.error("FUNC")
    func = symbols.canonical(args.func)
    path = Path(args.file) if args.file else ROOT / "nonmatching" / (func + ".cpp")
    if not path.exists() and not args.file:
        path = ROOT / "nonmatching" / (func + ".c")
    only = set(args.only.split(",")) if args.only else None
    skip = set(args.skip.split(",")) if args.skip else set()
    if args.list:
        for label, _ in rewrites(path.read_text(), func, only, skip, path):
            print(label)
        return 0
    best, start, _ = search(func, path, args.minutes, args.jobs, args.beam, args.depth, only, skip, args.version)
    return 0 if best.score == (0, 0) else 1


if __name__ == "__main__":
    sys.exit(main())
