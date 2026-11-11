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
and const, a pointer local against a reference, a call's arguments named first or a temporary
written in place, an index walk against a pointer walk, a single-expression helper of the file
or its headers written in place or called, VU0 helpers of include/vu0.h against their
alternatives, commuted operands and zero tests.

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
        self.helpers = find_helpers(unit.text, path)
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


def _header_texts(text, path=None):
    out = []
    for m in re.finditer(r'^\s*#\s*include\s+"([^"]+)"', text, re.M):
        h = ROOT / "include" / m.group(1)
        if h.exists() and m.group(1) not in ("common.h", "names.h"):
            out.append(h.read_text(errors="replace"))
    return out


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
    written in place, and an expression of a helper's shape written as its call."""
    u = ctx.u
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
              ["Scalar", "ScalarAt", "ScalarAtValue", "ScalarAtCall", "ScalarInGpr", "ScalarInGprReg"],
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


TRANSFORMS = [
    ("reorder", t_reorder),
    ("loops", t_loops),
    ("conditionals", t_conditionals),
    ("compound", t_compound),
    ("operands", t_operands),
    ("zero-tests", t_zero_tests),
    ("decls", t_decls),
    ("types", t_types),
    ("pointer-ref", t_pointer_ref),
    ("arguments", t_arguments),
    ("switch", t_switch),
    ("walks", t_walks),
    ("element", t_element),
    ("returns", t_returns),
    ("helpers", t_helpers),
    ("vu0", t_vu0),
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


def write_result(outdir, name, cand, func, base_score):
    path = outdir / name
    header = "// tsearch %s: score %s (start %s)\n// chain: %s\n" % (
        func, cand.score, base_score, "; ".join(cand.chain) or "(start)")
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
