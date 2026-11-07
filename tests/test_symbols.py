# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/symbols.py (either name works in the tools) and `names.py apply`."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import names  # noqa: E402
import symbols  # noqa: E402
import todo  # noqa: E402
import version_src  # noqa: E402

PAIRS = [("func_0016F588", "RegisterButtonCodes"), ("func_0016F188", "AdvanceButtonCodes"),
         ("D_00262DFC", "g_buttonCodes")]
TO_NAME = dict(PAIRS)


def table():
    return symbols.Symbols(PAIRS)


class SymbolsTest(unittest.TestCase):
    def test_both_directions(self):
        t = table()
        self.assertEqual(t.canonical("RegisterButtonCodes"), "func_0016F588")
        self.assertEqual(t.canonical("func_0016F588"), "func_0016F588")
        self.assertEqual(t.canonical("Unknown"), "Unknown")
        self.assertEqual(t.readable("func_0016F588"), "RegisterButtonCodes")
        self.assertEqual(t.readable("func_00100000"), "func_00100000")

    def test_normalize_turns_readable_names_back_whole_words_only(self):
        t = table()
        text = "void RegisterButtonCodes(); // RegisterButtonCodes\nx = g_buttonCodes + RegisterButtonCodesX;\n"
        self.assertEqual(t.normalize(text),
                         "void func_0016F588(); // func_0016F588\nx = D_00262DFC + RegisterButtonCodesX;\n")

    def test_the_tools_find_a_definition_under_either_name(self):
        text = ("void RegisterButtonCodes();\n\nvoid RegisterButtonCodes()\n{\n    AdvanceButtonCodes();\n}\n\n"
                "void func_0016F188()\n{\n}\n")
        with mock.patch.object(symbols, "load", return_value=table()):
            self.assertEqual([m.group(1) for m in todo.definitions(text)], ["func_0016F588", "func_0016F188"])
            for name in ("RegisterButtonCodes", "func_0016F588"):
                start, end = symbols.find_definition(text, name)
                self.assertTrue(text[start:end].startswith("void RegisterButtonCodes()\n{"), name)
                self.assertTrue(text[start:end].endswith("}"))
            start, end = version_src.definition_span(text, "AdvanceButtonCodes")
            self.assertEqual(text[start:end], "void func_0016F188()\n{\n}")
            self.assertIsNone(symbols.find_definition(text, "func_00100000"))

    def test_a_struct_line_is_a_definition_only_with_an_address_name_in_it(self):
        text = "struct Obj* RegisterButtonCodes(struct Size* n)\n{\n}\n\nstruct Obj Make(int a)\n{\n}\n"
        with mock.patch.object(symbols, "load", return_value=table()):
            self.assertEqual([m.group(1) for m in todo.definitions(text)], ["func_0016F588"])


class ConvertTest(unittest.TestCase):
    def test_every_use_changes_but_markers_comments_strings_and_includes(self):
        text = ('#include "func_0016F588.h"\n'
                "// func_0016F588 is cited on purpose\n"
                "INCLUDE_ASM(func_0016F188);\n"
                "ASM_FUNC( func_0016F188 );\n"
                'const char* s = "func_0016F588";\n'
                "void func_0016F588();\n"
                "void func_0016F588() { func_0016F188(); }\n"
                "extern u32 D_00262DFC[];\n"
                "#define CALL func_0016F588\n"
                "#undef func_0016F588\n"
                "void func_0016F588__Fv();\n")
        new, done, kept = names.convert(text, TO_NAME)
        self.assertEqual(new, ('#include "func_0016F588.h"\n'
                               "// func_0016F588 is cited on purpose\n"
                               "INCLUDE_ASM(func_0016F188);\n"
                               "ASM_FUNC( func_0016F188 );\n"
                               'const char* s = "func_0016F588";\n'
                               "void RegisterButtonCodes();\n"
                               "void RegisterButtonCodes() { AdvanceButtonCodes(); }\n"
                               "extern u32 g_buttonCodes[];\n"
                               "#define CALL RegisterButtonCodes\n"
                               "#undef func_0016F588\n"
                               "void func_0016F588__Fv();\n"))
        self.assertEqual(len(done), 5)
        self.assertEqual(kept, [])
        # idempotent
        self.assertEqual(names.convert(new, TO_NAME)[0], new)

    def test_nothing_changes_before_names_h_is_in_effect(self):
        text = "void func_0016F588();\n#include \"common.h\"\nvoid func_0016F588();\n"
        start = text.index("#include")
        new, done, kept = names.convert(text, TO_NAME, start)
        self.assertEqual(new, "void func_0016F588();\n#include \"common.h\"\nvoid RegisterButtonCodes();\n")
        self.assertEqual(len(kept), 1)

    def test_collisions_are_reported(self):
        self.assertEqual(names.collisions("x = obj->RegisterButtonCodes;\n", {"RegisterButtonCodes"}),
                         {"RegisterButtonCodes": "read as a field"})
        self.assertEqual(names.collisions("void f()\n{\n    s32 AdvanceButtonCodes = 0;\n}\n", {"AdvanceButtonCodes"}),
                         {"AdvanceButtonCodes": "declared as another identifier"})
        self.assertEqual(names.collisions("struct RegisterButtonCodes { s32 a; };\n", {"RegisterButtonCodes"}),
                         {"RegisterButtonCodes": "declared as another identifier"})
        self.assertEqual(names.collisions("extern u32 g_buttonCodes[];\nvoid RegisterButtonCodes();\n"
                                          "void f() { RegisterButtonCodes(); }\n", set(dict(TO_NAME.items()).values())), {})

    def test_a_file_is_converted_from_its_include_and_a_collision_is_left_alone(self):
        rows = [{"symbol": s, "name": n} for s, n in PAIRS]
        with tempfile.TemporaryDirectory() as tmp:
            good, clash = Path(tmp) / "a.cpp", Path(tmp) / "b.cpp"
            good.write_text('#include "common.h"\nvoid func_0016F588();\n// func_0016F588\n')
            clash.write_text('#include "common.h"\nvoid func_0016F588();\nvoid f(S* o) { o->AdvanceButtonCodes = func_0016F188; }\n')
            report = names.apply_files([good, clash], rows)
            self.assertEqual(good.read_text(), '#include "common.h"\nvoid RegisterButtonCodes();\n// func_0016F588\n')
            self.assertIn("void RegisterButtonCodes();", clash.read_text())
            self.assertIn("= func_0016F188;", clash.read_text())
            self.assertEqual(report[1][3], {"AdvanceButtonCodes": "read as a field"})
            self.assertEqual(names.apply_files([good, clash], rows)[0][1], 0)         # idempotent

    def test_a_file_without_names_h_is_left_alone(self):
        rows = [{"symbol": s, "name": n} for s, n in PAIRS]
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "a.h"
            path.write_text("void func_0016F588();\n")
            report = names.apply_files([path], rows)
            self.assertEqual(path.read_text(), "void func_0016F588();\n")
            self.assertEqual(report[0][1:3], (0, 1))


if __name__ == "__main__":
    unittest.main()
