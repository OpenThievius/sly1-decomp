# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/tsearch.py, the search over plain C++ rewrites: each rewrite on a small
text (text in, text out), the guard against what AGENTS.md forbids, the whole library over the
near misses in nonmatching/, and the scorer. They need no compiler."""

import re
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import tsearch  # noqa: E402

HEAD = "// SPDX-License-Identifier: AGPL-3.0-or-later\n#include \"common.h\"\n\n"


def body(text):
    """The function's text with whitespace collapsed, for comparisons."""
    return re.sub(r"\s+", " ", text).strip()


def results(src, func="func_00100000", only=None):
    """{label: function text} of every rewrite that passes the guard."""
    import version_src
    # One-line definitions read as declarations to tools/todo.py: open each body on a new line.
    text = HEAD + re.sub(r"\) \{ ", ") {\n", src)
    out = {}
    for label, new in tsearch.rewrites(text, func, only=only):
        s, e = version_src.definition_span(new, func)
        out.setdefault(label, body(new[s:e]))
        out[label + " #%d" % len(out)] = body(new[s:e])
    return out


def has(rs, prefix, want):
    """Whether some rewrite labelled `prefix...` gives `want` (whitespace aside)."""
    want = body(want)
    return any(label.startswith(prefix) and text == want for label, text in rs.items())


class Tokens(unittest.TestCase):
    def test_operators_and_preprocessor(self):
        toks = tsearch.tokenize('#define X 1\nx <<= a->b ? 1.5f : y <? z; // c\n')
        self.assertEqual([t.text for t in toks], ["x", "<<=", "a", "->", "b", "?", "1.5f", ":", "y", "<?", "z", ";"])

    def test_expression_tree(self):
        u = tsearch.Unit(HEAD + "void func_00100000(s32* p) { s32 x = (s32)*p + 2 * 3; }\n", "func_00100000")
        decl = u.body.p["items"][0]
        x = u.expr(*decl.p["init"])
        self.assertEqual((x.kind, x.op), ("binary", "+"))
        self.assertEqual(x.kids[0].kind, "cast")
        self.assertEqual(x.kids[1].op, "*")


class Rewrites(unittest.TestCase):
    def test_reorder_respects_dependences(self):
        rs = results("void func_00100000(s32* p, s32* q) { s32 a = p[0]; s32 b = a + 1; q[1] = b; }\n",
                     only={"reorder"})
        # b needs a, the store needs b: nothing may move.
        self.assertEqual(rs, {})
        rs = results("struct S { s32 a; s32 b; };\nvoid func_00100000(S* p, s32 x, s32 y) { p->a = x; p->b = y; }\n",
                     only={"reorder"})
        self.assertTrue(has(rs, "reorder", "void func_00100000(S* p, s32 x, s32 y) { p->b = y; p->a = x; }"))

    def test_address_stays_after_declaration(self):
        src = "struct S { s32 a; };\nvoid g(S*);\nvoid func_00100000() { S s; S* p = &s; g(p); }\n"
        rs = results(src, only={"reorder"})
        self.assertFalse(any(t.index("S* p") < t.index("S s;") for t in rs.values()))

    def test_calls_do_not_pass_memory(self):
        rs = results("void f(void);\nstruct S { s32 a; };\nvoid func_00100000(S* p) { p->a = 1; f(); }\n",
                     only={"reorder"})
        self.assertEqual(rs, {})

    def test_for_to_while_and_do(self):
        src = "void g(s32);\nvoid func_00100000() { for (s32 i = 0; i < 8; i++) { g(i); } }\n"
        rs = results(src, only={"loops"})
        self.assertTrue(has(rs, "for-to-while", "void func_00100000() { s32 i = 0; while (i < 8) { g(i); i++; } }"))
        # The first test is known true: a bare do-while.
        self.assertTrue(has(rs, "for-to-do", "void func_00100000() { s32 i = 0; do { g(i); i++; } while (i < 8); }"))

    def test_while_to_for(self):
        src = "void g(s32);\nvoid func_00100000(s32 n) { s32 i; i = 0; while (i < n) { g(i); i++; } }\n"
        rs = results(src, only={"loops"})
        self.assertTrue(has(rs, "while-to-for", "void func_00100000(s32 n) { s32 i; for (i = 0; i < n; i++) { g(i); } }"))
        self.assertTrue(has(rs, "while-to-do", "void func_00100000(s32 n) { s32 i; i = 0; if (i < n) { do { g(i); i++; } "
                                               "while (i < n); } }"))

    def test_loop_with_continue_stays(self):
        src = "void g(s32);\nvoid func_00100000() { for (s32 i = 0; i < 8; i++) { if (i == 2) continue; g(i); } }\n"
        rs = results(src, only={"loops"})
        self.assertFalse([l for l in rs if l.startswith(("for-to-while", "for-to-do"))])

    def test_ternary_both_ways(self):
        src = "s32 func_00100000(s32 c) { s32 x; if (c) { x = 1; } else { x = 2; } return x; }\n"
        rs = results(src, only={"conditionals"})
        self.assertTrue(has(rs, "if-to-ternary", "s32 func_00100000(s32 c) { s32 x; x = c ? 1 : 2; return x; }"))
        self.assertTrue(has(rs, "swap-branches", "s32 func_00100000(s32 c) { s32 x; if (!c) { x = 2; } else { x = 1; } return x; }"))
        src = "s32 func_00100000(s32 c) { s32 x = c ? 1 : 2; return x; }\n"
        rs = results(src, only={"conditionals"})
        self.assertTrue(has(rs, "ternary-to-if", "s32 func_00100000(s32 c) { s32 x = 2; if (c) { x = 1; } return x; }"))

    def test_default_then_conditional(self):
        src = "f32 func_00100000(s32 c) { f32 s = 0.4f; if (c) s = 0.5f; return s; }\n"
        rs = results(src, only={"conditionals"})
        self.assertTrue(has(rs, "if-to-ternary", "f32 func_00100000(s32 c) { f32 s = c ? 0.5f : 0.4f; return s; }"))

    def test_early_return(self):
        src = "void g(void);\nvoid func_00100000(s32 c) { g(); if (c != 1) { return; } g(); g(); }\n"
        rs = results(src, only={"conditionals"})
        self.assertTrue(has(rs, "wrap-rest", "void func_00100000(s32 c) { g(); if (c == 1) { g(); g(); } }"))

    def test_compound_and_increments(self):
        src = "s32 func_00100000(s32 x, s32 y) { x = x + y; y += 2; x++; return x + y; }\n"
        rs = results(src, only={"compound"})
        self.assertTrue(has(rs, "compound", "s32 func_00100000(s32 x, s32 y) { x += y; y += 2; x++; return x + y; }"))
        self.assertTrue(has(rs, "expand", "s32 func_00100000(s32 x, s32 y) { x = x + y; y = y + 2; x++; return x + y; }"))
        self.assertTrue(has(rs, "incdec", "s32 func_00100000(s32 x, s32 y) { x = x + y; y += 2; ++x; return x + y; }"))

    def test_commute_parenthesises(self):
        src = "s32 func_00100000(s32 a, s32 b, s32 c) { return a + b + c; }\n"
        rs = results(src, only={"operands"})
        self.assertTrue(has(rs, "commute", "s32 func_00100000(s32 a, s32 b, s32 c) { return c + (a + b); }"))
        self.assertTrue(has(rs, "commute", "s32 func_00100000(s32 a, s32 b, s32 c) { return b + a + c; }"))

    def test_zero_tests(self):
        src = "void g(void);\nvoid func_00100000(s32* p) { if (!p) g(); if (p[1] != 0) g(); }\n"
        rs = results(src, only={"zero-tests"})
        self.assertTrue(has(rs, "zero-test", "void func_00100000(s32* p) { if (p == 0) g(); if (p[1] != 0) g(); }"))
        self.assertTrue(has(rs, "zero-test", "void func_00100000(s32* p) { if (!p) g(); if (p[1]) g(); }"))

    def test_declarations(self):
        src = "void g(s32);\nvoid func_00100000(s32 c) { g(c); s32 x = c + 1; g(x); }\n"
        rs = results(src, only={"decls"})
        self.assertTrue(has(rs, "hoist-decl", "void func_00100000(s32 c) { s32 x; g(c); x = c + 1; g(x); }"))
        src = "void g(s32);\nvoid func_00100000(s32 c) { s32 x; g(c); x = c + 1; g(x); }\n"
        rs = results(src, only={"decls"})
        self.assertTrue(has(rs, "sink-decl", "void func_00100000(s32 c) { g(c); s32 x = c + 1; g(x); }"))

    def test_types_and_const(self):
        src = "s32 func_00100000(s32 c) { s32 x = c + 1; return x; }\n"
        rs = results(src, only={"types"})
        self.assertTrue(has(rs, "int-type", "s32 func_00100000(s32 c) { u32 x = c + 1; return x; }"))
        self.assertTrue(has(rs, "const", "s32 func_00100000(s32 c) { const s32 x = c + 1; return x; }"))
        self.assertTrue(has(rs, "const", "s32 func_00100000(const s32 c) { s32 x = c + 1; return x; }"))

    def test_widths(self):
        src = "u64 func_00100000(u32 i, u64 key) { u64 r = 0; s32 sh = 4; r = g[i] | (key << sh); return r + key; }\n"
        rs = results(src, only={"widths"})
        # Narrowed: a cast back to the old type where it is a shift's or arithmetic's operand.
        self.assertTrue(has(rs, "width", "u64 func_00100000(u32 i, s32 key) { u64 r = 0; s32 sh = 4; "
                                         "r = g[i] | ((u64)key << sh); return r + (u64)key; }"))
        # Widened: no cast.
        self.assertTrue(has(rs, "width", "u64 func_00100000(u64 i, u64 key) { u64 r = 0; s32 sh = 4; "
                                         "r = g[i] | (key << sh); return r + key; }"))
        # A local, and an assignment's target is not cast.
        src = "s32 func_00100000(s32 c) { s32 x = c; x = x + 1; return x; }\n"
        rs = results(src, only={"widths"})
        self.assertTrue(has(rs, "width", "s32 func_00100000(s32 c) { s16 x = c; x = (s32)x + 1; return x; }"))
        self.assertFalse(any("(s32)x =" in t for t in rs.values()))

    def test_width_notes_name_the_callers(self):
        cand = tsearch.Cand("", ["width@1 param key u64 -> s32"])
        self.assertIn("callers", tsearch.width_notes(cand, "func_0020A190"))
        self.assertEqual(tsearch.width_notes(tsearch.Cand("", ["width@1 local r u64 -> s32"]), "func_0020A190"), "")

    def test_pointer_and_reference(self):
        src = "struct S { s32 a; };\nextern S g_s;\ns32 func_00100000() { S* p = &g_s; return p->a; }\n"
        rs = results(src, only={"pointer-ref"})
        self.assertTrue(has(rs, "ptr-to-ref", "s32 func_00100000() { S& p = g_s; return p.a; }"))

    def test_named_argument_and_temporary(self):
        src = "void g(s32 size);\nvoid func_00100000(s32 a, s32 b) { g(a + b); }\n"
        rs = results(src, only={"arguments"})
        self.assertTrue(has(rs, "name-arg", "void func_00100000(s32 a, s32 b) { s32 size = a + b; g(size); }"))
        src = "void g(s32 size);\nvoid func_00100000(s32 a, s32 b) { s32 t = a + b; g(t); }\n"
        rs = results(src, only={"arguments"})
        self.assertTrue(has(rs, "inline-temp", "void func_00100000(s32 a, s32 b) { g((a + b)); }"))

    def test_switch_and_if_chain(self):
        src = "s32 func_00100000(s32 k) { s32 s = 0; switch (k) { case 1: s = 8; break; case 2: s = 16; break; } return s; }\n"
        rs = results(src, only={"switch"})
        self.assertTrue(has(rs, "switch-to-if", "s32 func_00100000(s32 k) { s32 s = 0; if (k == 1) { s = 8; } "
                                                "else if (k == 2) { s = 16; } return s; }"))
        src = "s32 func_00100000(s32 k) { s32 s = 0; if (k == 1) { s = 8; } else if (k == 2) { s = 16; } return s; }\n"
        rs = results(src, only={"switch"})
        self.assertTrue(has(rs, "if-to-switch", "s32 func_00100000(s32 k) { s32 s = 0; switch (k) { case 1: s = 8; break; "
                                                "case 2: s = 16; break; } return s; }"))

    def test_pointer_walk_and_element(self):
        src = "extern s32 D_00200000[8];\nvoid g(s32);\nvoid func_00100000() { for (s32 i = 0; i < 8; i++) { g(D_00200000[i]); } }\n"
        rs = results(src, only={"walks"})
        self.assertTrue(has(rs, "pointer-walk", "void func_00100000() { s32* p = D_00200000; for (s32 i = 0; i < 8; i++, p++) "
                                                "{ g(*p); } }"))
        src = ("struct P { s32 a; s32 b; };\nextern P D_00200000[8];\n"
               "s32 func_00100000(s32 i) { return D_00200000[i].a + D_00200000[i].b; }\n")
        rs = results(src, only={"element"})
        self.assertTrue(has(rs, "element-pointer", "s32 func_00100000(s32 i) { P* e = &D_00200000[i]; return e->a + e->b; }"))

    def test_result_variable(self):
        src = "s32 func_00100000(s32 i) { s32 r = 0; if (i < 10) { r = i * 2; } return r; }\n"
        rs = results(src, only={"returns"})
        self.assertTrue(has(rs, "result-to-returns", "s32 func_00100000(s32 i) { if (i < 10) { return i * 2; } return 0; }"))
        self.assertTrue(has(rs, "result-to-returns", "s32 func_00100000(s32 i) { if (i >= 10) { return 0; } return i * 2; }"))

    def test_helpers_both_ways(self):
        src = ("struct M { static s32 X(f32 x) { return (s32)((x + 1.0f) * 16.0f); } };\n"
               "s32 func_00100000(f32 a) { return M::X(a); }\n")
        rs = results(src, only={"helpers"})
        inlined = sorted({t for l, t in rs.items() if l.startswith("inline-helper")})
        self.assertEqual(len(inlined), 1)
        self.assertIn("return ((s32)((a + 1.0f) * 16.0f));", inlined[0])
        src = ("struct M { static s32 X(f32 x) { return (s32)((x + 1.0f) * 16.0f); } };\n"
               "s32 func_00100000(f32 a) { return (s32)((a + 1.0f) * 16.0f); }\n")
        rs = results(src, only={"helpers"})
        self.assertTrue(any(l.startswith("call-helper") and "return M::X(a);" in t for l, t in rs.items()))

    def test_named_constants(self):
        src = "void h(f32);\nvoid func_00100000(f32* p) { for (s32 i = 0; i < 8; i++) { h(p[i]); h(p[i] * 0.5f); } }\n"
        rs = results(src, only={"named-constant"})
        self.assertTrue(has(rs, "name-constant", "void func_00100000(f32* p) { for (s32 i = 0; i < 8; i++) { "
                                                 "f32 k = 0.5f; h(p[i]); h(p[i] * k); } }"))
        self.assertTrue(has(rs, "name-constant", "void func_00100000(f32* p) { for (s32 i = 0; i < 8; i++) { "
                                                 "h(p[i]); f32 k = 0.5f; h(p[i] * k); } }"))
        # used twice in the function: one local at the top
        src = "void h(f32);\nvoid func_00100000(f32 x) { h(x * 9.0f); h(x - 9.0f); }\n"
        rs = results(src, only={"named-constant"})
        self.assertTrue(has(rs, "name-constant", "void func_00100000(f32 x) { f32 k = 9.0f; h(x * k); h(x - k); }"))
        # the reverse, parenthesised where the place needs it
        src = "void h(f32);\nvoid func_00100000(f32 x) { f32 step = 1.0f / 15.0f; h(x + step); h(step); }\n"
        rs = results(src, only={"named-constant"})
        self.assertTrue(has(rs, "literal", "void func_00100000(f32 x) { h(x + (1.0f / 15.0f)); h(1.0f / 15.0f); }"))
        # not a shift count, a mask, an index or a template argument
        src = "void h(s32);\nvoid func_00100000(s32* p) { h(p[3] << 4); h(p[3] & 7); }\n"
        self.assertEqual(results(src, only={"named-constant"}), {})

    def test_repeat_expression(self):
        src = "void h(s32);\nvoid func_00100000(s32 n) { s32 last = n - 1; h(last); h(last * 2); }\n"
        rs = results(src, only={"repeat-expression"})
        self.assertTrue(has(rs, "write-at-uses", "void func_00100000(s32 n) { h(n - 1); h((n - 1) * 2); }"))
        src = "void h(s32);\nvoid func_00100000(s32 n) { h(n - 1); h(n - 1); }\n"
        rs = results(src, only={"repeat-expression"})
        self.assertTrue(has(rs, "name-repeat", "void func_00100000(s32 n) { s32 t = n - 1; h(t); h(t); }"))
        # not across a change of what it reads
        src = "void h(s32);\nvoid func_00100000(s32 n) { s32 last = n - 1; h(last); n++; h(last); }\n"
        self.assertFalse(any(l.startswith("write-at-uses") for l in results(src, only={"repeat-expression"})))
        src = "void h(s32);\nvoid func_00100000(s32 n) { h(n - 1); n++; h(n - 1); }\n"
        self.assertFalse(any(l.startswith("name-repeat") for l in results(src, only={"repeat-expression"})))

    def test_inline_method_in_place(self):
        src = ("extern float D_00200000[];\nstruct Q { f32 c[3]; f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); } };\n"
               "f32 func_00100000(f32 t) { return ((Q*)D_00200000)->Eval(t); }\n")
        rs = results(src, only={"helpers"})
        self.assertTrue(has(rs, "inline-method", "f32 func_00100000(f32 t) { return (D_00200000[0] + t * "
                                                 "(D_00200000[1] + t * D_00200000[2])); }"))
        src = ("struct Q { f32 c[3]; f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); } };\n"
               "f32 func_00100000(Q* q, f32 t) { return q->Eval(t); }\n")
        rs = results(src, only={"helpers"})
        self.assertTrue(has(rs, "inline-method", "f32 func_00100000(Q* q, f32 t) { return (q->c[0] + t * (q->c[1] + t * q->c[2])); }"))
        src = ("extern float D_00200000[];\nstruct Q { f32 c[3]; f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); } };\n"
               "f32 func_00100000(f32 t) { return D_00200000[0] + t * (D_00200000[1] + t * D_00200000[2]); }\n")
        rs = results(src, only={"helpers"})
        self.assertTrue(has(rs, "call-method", "f32 func_00100000(f32 t) { return ((Q*)D_00200000)->Eval(t); }"))

    def whole(self, src, only):
        """{label: the unit's text after HEAD} of every rewrite, for rewrites outside the definition."""
        text = HEAD + re.sub(r"\) \{ ", ") {\n", src)
        return {l: body(t[len(HEAD):]) for l, t in tsearch.rewrites(text, "func_00100000", only=only)}

    def test_param_order(self):
        src = ("s32 func_00100000(s32 a, s32* b, f32 r);\ns32 g2() { return func_00100000(1, 0, 2.0f); }\n"
               "s32 func_00100000(s32 a, s32* b, f32 r) { return a + (s32)r; }\n")
        rs = self.whole(src, {"param-order"})
        want = body("s32 func_00100000(s32 a, f32 r, s32* b);\ns32 g2() {\nreturn func_00100000(1, 2.0f, 0); }\n"
                    "s32 func_00100000(s32 a, f32 r, s32* b) {\nreturn a + (s32)r; }")
        self.assertIn(want, rs.values())
        # a float never passes a float, nor an integer an integer
        self.assertFalse(any("a to" in l for l in rs))
        src = "s32 func_00100000(f32 a, f32 b) { return (s32)(a + b); }\n"
        self.assertEqual(self.whole(src, {"param-order"}), {})

    def test_callee_return(self):
        src = "void g(s32);\nvoid h(void) { g(2); }\nvoid func_00100000(s32 n) { g(n); }\n"
        rs = self.whole(src, {"callee-return"})
        self.assertIn("s32 g(s32);", list(rs.values())[0])
        # s32 to void only where no call uses the result
        src = "s32 g(s32);\ns32 h(void) { return g(2); }\nvoid func_00100000(s32 n) { g(n); }\n"
        self.assertEqual(self.whole(src, {"callee-return"}), {})
        src = "s32 g(s32);\nvoid h(void) { if (1) g(2); }\nvoid func_00100000(s32 n) { g(n); }\n"
        self.assertIn("void g(s32);", list(self.whole(src, {"callee-return"}).values())[0])
        # a function the file defines is left alone
        src = "void g(s32 x) {\n}\nvoid func_00100000(s32 n) { g(n); }\n"
        self.assertEqual(self.whole(src, {"callee-return"}), {})
        cand = tsearch.Cand("", ["callee-return@3 func_00100000 void -> s32"])
        self.assertIn("other declarations", tsearch.width_notes(cand, "func_00100000"))

    def test_reuse_variable(self):
        src = "void h(s32);\nvoid func_00100000(s32 n) { for (s32 i = 0; i < n; i++) h(i); s32 j = 0; while (j < 4) { h(j); j++; } }\n"
        rs = results(src, only={"reuse-variable"})
        self.assertTrue(has(rs, "reuse-variable", "void func_00100000(s32 n) { s32 i; for (i = 0; i < n; i++) h(i); "
                                                  "i = 0; while (i < 4) { h(i); i++; } }"))
        # the later one declared first: the loop takes its name
        src = "void h(s32);\nvoid func_00100000(s32 n) { s32 i; for (s32 j = 0; j < n; j++) h(j); for (i = 0; i < 4; i++) h(i); }\n"
        rs = results(src, only={"reuse-variable"})
        self.assertTrue(has(rs, "reuse-variable", "void func_00100000(s32 n) { s32 i; for (i = 0; i < n; i++) h(i); "
                                                  "for (i = 0; i < 4; i++) h(i); }"))
        # split at an assignment that starts a new life
        src = "void h(s32);\ns32 f(void);\nvoid func_00100000(s32 n) { s32 x = f(); h(x); x = f(); h(x + 1); }\n"
        rs = results(src, only={"reuse-variable"})
        self.assertTrue(has(rs, "split-variable", "void func_00100000(s32 n) { s32 x = f(); h(x); s32 x2 = f(); h(x2 + 1); }"))
        # not where the lives overlap, nor where a loop carries one past the other
        src = "void h(s32);\nvoid func_00100000(s32 n) { s32 a = n; s32 b = n + 1; h(a); h(b); }\n"
        self.assertFalse(any(l.startswith("reuse-variable") for l in results(src, only={"reuse-variable"})))
        src = "void h(s32);\ns32 f(void);\nvoid func_00100000(s32 n) { s32 x = 0; while (n--) { h(x); x = f(); h(x); } }\n"
        self.assertFalse(any(l.startswith("split-variable") for l in results(src, only={"reuse-variable"})))
        # nor where a use after the block reads the value either arm set
        src = "void h(s32);\nvoid func_00100000(s32 n) { s32 x = n; h(x); if (n) { x = 1; h(x); } else { x = 2; } h(x); }\n"
        self.assertFalse(any(l.startswith("split-variable") for l in results(src, only={"reuse-variable"})))

    def test_in_each_arm(self):
        src = ("s32 F(void);\ns32 G(void);\nvoid h(void);\n"
               "void func_00100000(s32 a) { s32 hit; if (a) { hit = F(); } else { hit = G(); } if (hit != 0) { h(); } }\n")
        rs = results(src, only={"test-in-each-arm"})
        self.assertTrue(has(rs, "test-in-each-arm", "void func_00100000(s32 a) { if (a) { if (F() != 0) { h(); } } "
                                                    "else { if (G() != 0) { h(); } } }"))
        src = ("s32 F(void);\ns32 G(void);\nvoid h(void);\n"
               "void func_00100000(s32 a) { if (a) { if (F() != 0) { h(); } } else { if (G() != 0) { h(); } } }\n")
        rs = results(src, only={"test-in-each-arm"})
        self.assertTrue(has(rs, "test-after-arms", "void func_00100000(s32 a) { s32 hit; if (a) { hit = F(); } "
                                                   "else { hit = G(); } if (hit != 0) { h(); } }"))
        # not when the variable is read again after the test
        src = ("s32 F(void);\ns32 G(void);\nvoid h(s32);\n"
               "void func_00100000(s32 a) { s32 hit; if (a) { hit = F(); } else { hit = G(); } if (hit != 0) { h(hit); } }\n")
        self.assertEqual(results(src, only={"test-in-each-arm"}), {})

    def test_case_order(self):
        src = "s32 func_00100000(s32 k) { s32 n = 4; switch (k) { case 0: case 1: n = 2; break; case 2: n = 3; break; } return n; }\n"
        rs = results(src, only={"case-order"})
        self.assertTrue(has(rs, "case-order", "s32 func_00100000(s32 k) { s32 n = 4; switch (k) { case 2: n = 3; break; "
                                              "case 0: case 1: n = 2; break; } return n; }"))
        self.assertTrue(has(rs, "case-order", "s32 func_00100000(s32 k) { s32 n = 4; switch (k) { case 1: case 0: n = 2; break; "
                                              "case 2: n = 3; break; } return n; }"))
        self.assertTrue(has(rs, "set-in-arms", "s32 func_00100000(s32 k) { s32 n; switch (k) { case 0: case 1: n = 2; break; "
                                               "case 2: n = 3; break; default: n = 4; break; } return n; }"))
        src = "s32 func_00100000(s32 k) { s32 n; switch (k) { case 0: n = 4; k = 1; break; case 2: n = 4; break; } return n + k; }\n"
        rs = results(src, only={"case-order"})
        self.assertTrue(has(rs, "set-before-switch", "s32 func_00100000(s32 k) { s32 n = 4; switch (k) { case 0: k = 1; break; "
                                                     "case 2: break; } return n + k; }"))
        # an arm that falls through is never moved
        src = "s32 func_00100000(s32 k) { s32 n = 0; switch (k) { case 0: n = 2; case 1: n++; break; } return n; }\n"
        self.assertFalse(any(l.startswith("case-order") for l in results(src, only={"case-order"})))

    def test_chained_assignment(self):
        src = "struct S { f32 a; f32 b; };\nvoid func_00100000(S* p) { p->a = 1.0f; p->b = 1.0f; }\n"
        rs = results(src, only={"chained-assignment"})
        self.assertTrue(has(rs, "chain", "void func_00100000(S* p) { p->a = p->b = 1.0f; }"))
        self.assertTrue(has(rs, "chain", "void func_00100000(S* p) { p->b = p->a = 1.0f; }"))
        src = "struct S { f32 a; f32 b; };\nvoid func_00100000(S* p) { p->a = p->b = 1.0f; }\n"
        rs = results(src, only={"chained-assignment"})
        self.assertTrue(has(rs, "unchain", "void func_00100000(S* p) { p->b = 1.0f; p->a = 1.0f; }"))
        self.assertTrue(has(rs, "unchain", "void func_00100000(S* p) { p->b = 1.0f; p->a = p->b; }"))
        # not when the second target reads the first one
        src = "void func_00100000(s32* p, s32 x) { x = 1; p[x] = 1; }\n"
        self.assertFalse(any(l.startswith("chain@") for l in results(src, only={"chained-assignment"})))

    def test_struct_store(self):
        src = ("#include \"vu0.h\"\nstruct S { Vec02 q; };\n"
               "void func_00100000(S* p, Vu0::Vec v) { Vu0::Q(p->q) = Vu0::Add(v, v).q; }\n")
        rs = results(src, only={"struct-store"})
        self.assertTrue(has(rs, "struct-store", "void func_00100000(S* p, Vu0::Vec v) { *(Vu0::Vec*)&p->q = Vu0::Add(v, v); }"))
        src = ("#include \"vu0.h\"\nstruct S { Vec02 q; };\n"
               "void func_00100000(S* p, Vu0::Vec v) { *(Vu0::Vec*)&p->q = Vu0::Add(v, v); }\n")
        rs = results(src, only={"struct-store"})
        self.assertTrue(has(rs, "q-store", "void func_00100000(S* p, Vu0::Vec v) { Vu0::Q(p->q) = Vu0::Add(v, v).q; }"))

    def test_vu0_alternatives(self):
        src = "#include \"vu0.h\"\nf32 func_00100000(u128 v, f32 s) { return Vu0::ToFloat(Vu0::MulX(v, Vu0::Scalar(s))); }\n"
        rs = results(src, only={"vu0"})
        self.assertTrue(any("Vu0::ToFloatMoved(" in t for t in rs.values()))
        self.assertTrue(any("Vu0::ScalarAt(s)" in t for t in rs.values()))


class Guard(unittest.TestCase):
    OLD = HEAD + "s32 func_00100000(s32 a) { s32 x = a + 1; return x; }\n"

    def check(self, new_body):
        return tsearch.forbidden(self.OLD, HEAD + new_body, "func_00100000")

    def test_plain_is_clean(self):
        self.assertEqual(self.check("s32 func_00100000(s32 a) { return a + 1; }\n"), [])

    def test_each_forbidden_construct(self):
        cases = {
            "inline assembly": "s32 func_00100000(s32 a) { s32 x = a + 1; asm(\"nop\"); return x; }\n",
            "a register variable": "s32 func_00100000(s32 a) { register s32 x = a + 1; return x; }\n",
            "volatile": "s32 func_00100000(s32 a) { volatile s32 x = a + 1; return x; }\n",
            "do { } while (0)": "s32 func_00100000(s32 a) { s32 x; do { x = a + 1; } while (0); return x; }\n",
            "goto": "s32 func_00100000(s32 a) { s32 x = a + 1; goto out; out: return x; }\n",
            "an empty statement": "s32 func_00100000(s32 a) { s32 x = a + 1;; return x; }\n",
            "x ^ 0, x + 0, x | 0": "s32 func_00100000(s32 a) { s32 x = (a + 1) ^ 0; return x; }\n",
        }
        for what, src in cases.items():
            self.assertIn(what, self.check(src), what)

    def test_dead_and_padding_locals(self):
        reasons = self.check("s32 func_00100000(s32 a) { s32 x = a + 1; s32 y = 2; return x; }\n")
        self.assertTrue(any(r.startswith("a local never read (y)") for r in reasons), reasons)
        reasons = self.check("s32 func_00100000(s32 a) { s32 pad[4]; s32 x = a + 1; return x; }\n")
        self.assertTrue(any(r.startswith("a new array local") for r in reasons), reasons)
        reasons = self.check("s32 func_00100000(s32 a) { s32 x = a + 1; x = x; return x; }\n")
        self.assertTrue(any(r.startswith("a self-assignment") for r in reasons), reasons)

    def test_new_groups_stay_plain(self):
        """The rewrites that remove or move declarations never leave a local unread, and the guard
        still turns away a candidate that would."""
        src = HEAD + ("s32 F(void);\ns32 G(void);\nvoid h(void);\n"
                      "void func_00100000(s32 a) {\n s32 hit; if (a) { hit = F(); } else { hit = G(); } if (hit != 0) { h(); } }\n")
        for label, new in tsearch.rewrites(src, "func_00100000"):
            self.assertEqual(tsearch.forbidden(src, new, "func_00100000"), [], label)
        old = HEAD + "s32 func_00100000(s32 a) {\n s32 i; for (i = 0; i < a; i++) {} return i; }\n"
        new = HEAD + "s32 func_00100000(s32 a) {\n s32 i; s32 j; for (i = 0; i < a; i++) {} return i; }\n"
        self.assertTrue(any(r.startswith("a local never read (j)") for r in tsearch.forbidden(old, new, "func_00100000")))
        self.test_each_forbidden_construct()

    def test_library_over_the_near_misses(self):
        """Every rewrite of every near miss (but the one very long function) parses again and
        passes the guard: the library cannot write what AGENTS.md forbids."""
        root = Path(__file__).resolve().parent.parent / "nonmatching"
        files = [p for p in sorted(root.glob("func_*.cpp")) if p.stat().st_size < 40000]
        if not files:
            self.skipTest("no near misses")
        total = 0
        for path in files:
            text = path.read_text()
            u = tsearch.Unit(text, path.stem)
            ctx = tsearch.Ctx(u, path)
            for name, fn in tsearch.TRANSFORMS:
                for label, edits in fn(ctx):
                    new = tsearch.apply_edits(text, edits)
                    nu = tsearch.Unit(new, path.stem, base=u)
                    self.assertEqual(tsearch.forbidden(text, new, path.stem, u, nu), [], "%s %s" % (path.name, label))
                    total += 1
        # The corpus shrinks as near misses match (it skips itself when none is left), so the
        # floor is per file: the library offers well over twenty rewrites of any real function.
        self.assertGreater(total, 20 * len(files))


class Score(unittest.TestCase):
    def test_score(self):
        retail = [("00000000", "addiu sp,sp,-16"), ("8c820000", "lw v0,0(a0)"), ("03e00008", "jr ra")]
        self.assertEqual(tsearch.score_of(retail, retail), (0, 0))
        regs = [("00000000", "addiu sp,sp,-16"), ("8c830000", "lw v1,0(a0)"), ("03e00008", "jr ra")]
        self.assertEqual(tsearch.score_of(regs, retail), (0, 1))
        code = [("00000000", "addiu sp,sp,-16"), ("8c820004", "lw v0,4(a0)"), ("03e00008", "jr ra"), ("0", "nop")]
        self.assertEqual(tsearch.score_of(code, retail), (2, 2))
        self.assertLess(tsearch.score_of(regs, retail), tsearch.score_of(code, retail))


if __name__ == "__main__":
    unittest.main()
