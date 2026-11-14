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


class TablesTest(unittest.TestCase):
    """Each function's row is in its source file's table, each global's in data.tsv."""

    FILES = [(0x16F000, 0x170000, "src/main/button.cpp"), (0x204F68, 0x205000, "src/libm/sqrt.c")]

    def test_each_row_goes_to_its_files_table(self):
        self.assertEqual(names.table_for("func_0016F588", self.FILES), "config/names/main/button.tsv")
        self.assertEqual(names.table_for("func_00204F68", self.FILES), "config/names/libm/sqrt.tsv")
        self.assertEqual(names.table_for("D_00262DFC", self.FILES), "config/names/data.tsv")
        self.assertEqual(names.table_for("func_00100000", self.FILES), "config/names/other.tsv")

    def test_tables_are_sorted_and_a_misplaced_row_is_reported(self):
        rows = [row("func_0016F588", "RegisterButtonCodes"), row("func_0016F188", "AddButtonCode", line=3)]
        texts = names.table_texts(rows, self.FILES)
        self.assertEqual(list(texts), ["config/names/main/button.tsv"])
        self.assertLess(texts["config/names/main/button.tsv"].index("AddButtonCode"),
                        texts["config/names/main/button.tsv"].index("RegisterButtonCodes"))
        placed = [dict(r, table="config/names/main/button.tsv") for r in rows]
        self.assertEqual(names.problems(placed, FUNCS, files=self.FILES), [])
        errs = names.problems([dict(rows[0], table="config/names/data.tsv")], FUNCS, files=self.FILES)
        self.assertEqual(len(errs), 1, errs)
        self.assertIn("belongs in config/names/main/button.tsv", errs[0])


class OwnFunctionsTest(unittest.TestCase):
    """A function only PAL has (func_eu_XXXXXXXX) is named like any other, in its shared file's table."""

    FILES = TablesTest.FILES
    OWN = {"func_eu_0016F600": "config/names/main/button.tsv"}

    def test_a_pal_only_function_takes_a_row_and_a_macro(self):
        rows = [row("func_eu_0016F600", "ReadWideButtonCode")]
        self.assertEqual(names.problems(rows, FUNCS | {"func_eu_0016F600"}), [])
        self.assertIn("#define ReadWideButtonCode func_eu_0016F600", names.header_text(rows))

    def test_it_must_be_a_function_only_that_version_has(self):
        errs = names.problems([row("func_eu_0016F700", "ReadWideButtonCode")], FUNCS)
        self.assertEqual(len(errs), 1, errs)
        self.assertIn("config/eu/map.tsv", errs[0])
        errs = names.problems([row("func_EU_0016F600", "ReadWideButtonCode")], FUNCS)
        self.assertTrue(any("not an address name" in e for e in errs), errs)

    def test_its_row_goes_to_its_shared_files_table(self):
        self.assertEqual(names.table_for("func_eu_0016F600", self.FILES, self.OWN), "config/names/main/button.tsv")
        self.assertEqual(names.table_for("func_eu_0016F700", self.FILES, self.OWN), "config/names/other.tsv")
        rows = [dict(row("func_eu_0016F600", "ReadWideButtonCode"), table="config/names/data.tsv")]
        errs = names.problems(rows, FUNCS | {"func_eu_0016F600"}, files=self.FILES, own=self.OWN)
        self.assertEqual(len(errs), 1, errs)
        self.assertIn("belongs in config/names/main/button.tsv", errs[0])

    def test_the_committed_pal_only_functions_have_tables(self):
        own = names.own_tables(names.proved_files())
        self.assertEqual(own.get("func_eu_0015DF58"), "config/names/main/font.tsv")
        self.assertTrue(all(t.startswith("config/names/") and t != "config/names/other.tsv" for t in own.values()))


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
                     "f((struct Head *)p, 1, g_buttonCodes, 8);", "s = s * (g_scale * g_buttonCodes);",
                     "f(at, (Head*)other, radius * g_buttonCodes);"):
            self.assertTrue(self.check(text), text)

    def test_declarations_are_not(self):
        for text in ("void f()\n{\n    s32 g_buttonCodes;\n}\n", "void f(s32 a, u8* g_buttonCodes)",
                     "struct g_buttonCodes {};", "struct S { Slot* g_buttonCodes[4]; };"):
            self.assertFalse(self.check(text), text)

    def test_the_symbols_own_declaration_in_the_first_column_is_a_use(self):
        # The converter writes the readable name in definitions and extern declarations too.
        for text in ("s32 g_buttonCodes;", "extern Slot* g_buttonCodes[4];", "EntryPool g_buttonCodes = {0};"):
            self.assertTrue(self.check(text), text)


class CommittedNamesTest(unittest.TestCase):
    """The committed tables in config/names/ and include/names.h, which CI checks without a disc."""

    def test_the_tables_are_well_formed_and_the_header_agrees(self):
        rows = names.read_tables()
        header = names.HEADER.read_text() if names.HEADER.exists() else names.header_text([])
        self.assertEqual(names.problems(rows, header=header, files=names.proved_files()), [])


if __name__ == "__main__":
    unittest.main()
