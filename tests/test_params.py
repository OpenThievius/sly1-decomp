# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/params.py: the GCC 2.95 parameter demangler and the kinds of difference."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import params  # noqa: E402


def demangle(symbol):
    return params.demangle(params.SYMBOL.match(symbol).group(2))


class DemangleTest(unittest.TestCase):
    def test_builtins_and_qualifiers(self):
        self.assertEqual(demangle("func_00100000__Fv"), [])
        self.assertEqual(demangle("func_00100000__FifUiUcScPCc"),
                         ["int", "float", "unsigned int", "unsigned char", "signed char", "const char*"])
        self.assertEqual(demangle("func_00100000__FxUxdbw"),
                         ["long long", "unsigned long long", "double", "bool", "wchar_t"])

    def test_classes_pointers_references(self):
        self.assertEqual(demangle("func_0018A388__FP10World2Boss"), ["World2Boss*"])
        self.assertEqual(demangle("func_00100000__FRC5Vec02PP6Player"), ["const Vec02&", "Player**"])
        self.assertEqual(demangle("func_00100000__FG14RandomRangeLowi"), ["RandomRangeLow", "int"])
        self.assertEqual(demangle("func_00100000__FPQ23Vu03Vec"), ["Vu0::Vec*"])

    def test_function_pointers(self):
        self.assertEqual(demangle("func_001F5CD0__FPvUiUiPFPCvPCv_i"),
                         ["void*", "unsigned int", "unsigned int", "int(*)(const void*, const void*)"])

    def test_back_references(self):
        # T<n>: the type of parameter n; N<count><n>: count more of parameter n.
        self.assertEqual(demangle("func_00104DE0__FP11ScriptValueP12NumberedItemiT0"),
                         ["ScriptValue*", "NumberedItem*", "int", "ScriptValue*"])
        self.assertEqual(demangle("func_00113B60__FP11ScriptValueN20"), ["ScriptValue*"] * 3)
        self.assertEqual(demangle("func_001782C0__FP6PlayerP15TargetArcSourcefP5Vec02N23"),
                         ["Player*", "TargetArcSource*", "float", "Vec02*", "Vec02*", "Vec02*"])
        # an index over 9 is written with a closing '_'
        self.assertEqual(demangle("func_00100000__FiiiiiiiiiifPT10_")[-1], "float*")

    def test_a_reference_inside_a_type(self):
        self.assertEqual(demangle("func_00100000__FP12PlayingSoundPT0"), ["PlayingSound*", "PlayingSound**"])

    def test_unknown_code_raises(self):
        with self.assertRaises(params.DemangleError):
            params.demangle("Z")


class KindsTest(unittest.TestCase):
    def test_kinds(self):
        k = params.kinds
        self.assertEqual(k(("void*",), ("Player*",)), {"void*"})
        self.assertEqual(k(("Player*",), ("Collider*",)), {"pointee"})
        self.assertEqual(k(("int",), ("Player*",)), {"ptr/int"})
        self.assertEqual(k(("int",), ("unsigned int",)), {"scalar"})
        self.assertEqual(k(("int",), ("int", "int")), {"count"})
        self.assertEqual(k(None, ("float",)), {"linkage"})
        self.assertEqual(k(("Player*", "float", "int*"), ("Player*", "int*", "float")), {"order"})
        self.assertEqual(k(("void*", "float", "int"), ("Player*", "int", "float")), {"order", "void*"})

    def test_top_level_const_of_a_value_is_not_part_of_the_type(self):
        self.assertEqual(params.by_value("const int"), "int")
        self.assertEqual(params.by_value("const char*"), "const char*")
        self.assertEqual(params.by_value("char* const"), "char*")


if __name__ == "__main__":
    unittest.main()
