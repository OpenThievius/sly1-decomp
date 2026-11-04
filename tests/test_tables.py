# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/tables.py, the tables of function pointers.
They need no disc: the words are synthetic."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import tables  # noqa: E402


def words(*toks):
    return [(0x200000 + 4 * i, t) for i, t in enumerate(toks)]


class ClassifyTest(unittest.TestCase):
    def test_a_run_of_functions_and_zeros_is_a_method_table(self):
        w = words("func_00100000", "0x00000000", "func_00100010")
        self.assertEqual(tables.classify("D_00200000", w, set(), set()), "methods")

    def test_a_listed_descriptor_is_left_to_the_class_map(self):
        w = words("D_00217410", "0x00000001", "0x00000000", "0x00000010", "func_00100000")
        self.assertEqual(tables.classify("D_00200000", w, {"D_00200000"}, set()), "descriptor")

    def test_functions_at_a_fixed_stride_are_records(self):
        w = words("func_00100000", "0x00000001", "0x00000002",
                  "func_00100010", "0x00000003", "0x00000004",
                  "func_00100020", "0x00000005", "0x00000006")
        self.assertEqual(tables.classify("D_00200000", w, set(), set()), "records/3")

    def test_one_function_word_is_a_function_pointer(self):
        self.assertEqual(tables.classify("D_00200000", words("func_00100000"), set(), set()), "fnptr")


class VtableTest(unittest.TestCase):
    def test_two_vtables_in_one_label_are_cut_at_the_second_header(self):
        z = "0x00000000"
        w = words(z, z, z, "func_00100000", z, "func_00100010", z, z,   # header, two slots, close
                  z, z, z, "func_00100020", z, z)                      # second header, one slot, close
        cut = tables.split_vtables(w)
        self.assertEqual(len(cut), 2)
        self.assertEqual([t for _, t in cut[1]][3], "func_00100020")

    def test_words_that_are_not_entries_are_no_vtable(self):
        self.assertEqual(tables.split_vtables(words("func_00100000", "func_00100010", "0x5", "0x6")), [])


if __name__ == "__main__":
    unittest.main()
