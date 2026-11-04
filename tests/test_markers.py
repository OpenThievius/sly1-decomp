# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for the assembly markers of whole files (include/asm_func.h): which marker each
included function takes, and where tools/compile.py puts a remnant after the static initialiser."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import asm_func  # noqa: E402
import build  # noqa: E402
import compile  # noqa: E402

UNIT = """\t.ent\tfunc_00100000
func_00100000:
\t.end\tfunc_00100000
 #APP
\t# linker remnant
\t.section .text
\t.include "build/us/asm_func/func_00100010.s"
 #NO_APP
\t.text
\t.align\t3
\t.ent\t__static_initialization_and_destruction_0
__static_initialization_and_destruction_0:
\t.end\t__static_initialization_and_destruction_0
\t.align\t3
\t.globl\t_GLOBAL_$I$func_00100000
\t.ent\t_GLOBAL_$I$func_00100000
_GLOBAL_$I$func_00100000:
"""


class MarkerTest(unittest.TestCase):
    def test_every_marker_includes_its_function(self):
        text = "INCLUDE_ASM(func_00100000);\nASM_FUNC(func_00100010);\nLINKER_REMNANT(func_00100020);\n" \
               "LINKER_REMNANT_AFTER_INIT(func_00100030);\n"
        self.assertEqual(asm_func.included(text), ["func_00100000", "func_00100010", "func_00100020", "func_00100030"])
        self.assertEqual(asm_func.markers(text)[3], ("LINKER_REMNANT_AFTER_INIT", "func_00100030"))

    def test_a_marker_must_agree_with_the_classification(self):
        table = {"func_00100010": "handwritten", "func_00100020": "remnant", "func_00100030": "remnant"}
        good = [("a.cpp", "INCLUDE_ASM(func_00100000);\nASM_FUNC(func_00100010);\n"
                          "LINKER_REMNANT(func_00100020);\nLINKER_REMNANT_AFTER_INIT(func_00100030);\n")]
        self.assertEqual(build.marker_errors(good, table), [])
        bad = [("a.cpp", "INCLUDE_ASM(func_00100010);\nASM_FUNC(func_00100020);\nLINKER_REMNANT(func_00100000);\n")]
        self.assertEqual(len(build.marker_errors(bad, table)), 3)


class PlaceRemnantTest(unittest.TestCase):
    def test_a_remnant_after_the_last_function_goes_before_the_constructor(self):
        out = compile.place_remnants(UNIT)
        self.assertLess(out.index("__static_initialization_and_destruction_0:"), out.index("# linker remnant"))
        self.assertLess(out.index("# linker remnant"), out.index("_GLOBAL_$I$func_00100000:"))

    def test_a_unit_without_a_constructor_is_left_as_it_is(self):
        text = UNIT[:UNIT.index("\t.align\t3\n\t.globl")]
        self.assertEqual(compile.place_remnants(text), text)


if __name__ == "__main__":
    unittest.main()
