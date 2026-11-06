# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/names.py: the table's rules and the header it generates."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import names  # noqa: E402

FUNCS = {"func_0016F588", "func_0016F188"}


def row(symbol, name, evidence="registers the nine records", line=2):
    return {"symbol": symbol, "name": name, "evidence": evidence, "line": line}


class NamesTest(unittest.TestCase):
    def test_a_good_table_has_no_problems(self):
        rows = [row("func_0016F588", "RegisterButtonCodes"), row("D_00262DFC", "g_buttonCodes", line=3)]
        self.assertEqual(names.problems(rows, FUNCS), [])

    def test_the_styles_and_the_prefix_rule(self):
        bad = [row("func_0016F588", "registerButtonCodes"),          # not PascalCase
               row("func_0016F188", "Add_Button", line=3),            # underscore
               row("D_00262DFC", "buttonCodes", line=4),              # data without g_
               row("D_00262E00", "g_pButton", line=5)]                # Hungarian
        errs = names.problems(bad, FUNCS)
        self.assertEqual(len(errs), 4, errs)
        self.assertTrue(any("Hungarian" in e for e in errs))

    def test_a_name_or_symbol_given_twice_and_an_unknown_function(self):
        rows = [row("func_0016F588", "AddButtonCode"), row("func_0016F188", "AddButtonCode", line=3),
                row("func_0016F588", "RegisterButtonCodes", line=4), row("func_00100000", "Start", line=5)]
        errs = names.problems(rows, FUNCS)
        self.assertTrue(any("names two symbols" in e for e in errs))
        self.assertTrue(any("named twice" in e for e in errs))
        self.assertTrue(any("not in config/us/functions.tsv" in e for e in errs))

    def test_every_name_needs_evidence(self):
        self.assertEqual(len(names.problems([row("func_0016F588", "RegisterButtonCodes", evidence=" ")], FUNCS)), 1)

    def test_the_header_defines_each_name_as_its_symbol(self):
        text = names.header_text([row("func_0016F588", "RegisterButtonCodes")])
        self.assertIn("#define RegisterButtonCodes func_0016F588", text)
        self.assertEqual(names.problems([row("func_0016F588", "RegisterButtonCodes")], FUNCS, header=text), [])
        self.assertEqual(len(names.problems([row("func_0016F588", "RegisterButtonCodes")], FUNCS, header="")), 1)


class UseOrDefinitionTest(unittest.TestCase):
    """_is_use tells a use of the macro from a source's own identifier of the same name."""

    def check(self, text):
        path = Path(names.ROOT) / "build" / "test_names_is_use.cpp"
        path.parent.mkdir(exist_ok=True)
        path.write_text(text)
        try:
            return names._is_use(row("D_00262DFC", "g_buttonCodes"), path.relative_to(names.ROOT))
        finally:
            path.unlink()

    def test_uses_are_uses(self):
        for text in ("if (n > 0 && g_buttonCodes[0].x != 0) {}", "return g_buttonCodes;",
                     "p = (u8*)g_buttonCodes + 8;", "f(a, g_buttonCodes);",
                     "f((struct Head *)p, 1, g_buttonCodes, 8);", "s = s * (g_scale * g_buttonCodes);"):
            self.assertTrue(self.check(text), text)

    def test_declarations_are_not(self):
        for text in ("s32 g_buttonCodes;", "extern Slot* g_buttonCodes[4];", "void f(s32 a, u8* g_buttonCodes)",
                     "struct g_buttonCodes {};"):
            self.assertFalse(self.check(text), text)


class CommittedNamesTest(unittest.TestCase):
    """The committed config/names.tsv and include/names.h, which CI checks without a disc."""

    def test_the_table_is_well_formed_and_the_header_agrees(self):
        rows = names.read_table()
        header = names.HEADER.read_text() if names.HEADER.exists() else names.header_text([])
        self.assertEqual(names.problems(rows, header=header), [])


if __name__ == "__main__":
    unittest.main()
