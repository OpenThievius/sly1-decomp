# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/modern_check.py: the rewriting of g++'s operators and the sorting of errors."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import modern_check  # noqa: E402


class SanitizeTest(unittest.TestCase):
    def test_minimum_and_maximum_operators_keep_their_columns(self):
        src = "x = a <? b; y = c >? d;"
        out = modern_check.sanitize(src)
        self.assertEqual(len(out), len(src))
        self.assertNotIn("<?", out)
        self.assertNotIn(">?", out)

    def test_strings_comments_and_shifts_are_left_alone(self):
        for src in ('s = "<?";', "// a <? b\n", "/* c >? d */", "x = a << 2; y = b >> 1;", "c = '?';"):
            self.assertEqual(modern_check.sanitize(src), src)

    def test_a_string_broken_over_a_line_is_closed_and_reopened(self):
        self.assertEqual(modern_check.sanitize('s = "a\nb";'), 's = "a"\n"b";')


class ClassifyTest(unittest.TestCase):
    def test_the_ps2_helpers_errors_are_not_the_ports(self):
        self.assertTrue(modern_check.PS2.search("invalid output constraint '=j' in asm"))
        self.assertTrue(modern_check.PS2.search("unknown register name 'vf26' in asm"))
        self.assertFalse(modern_check.PS2.search("unknown type name 'BaseObject'"))
        self.assertIn("include/vu0.h", modern_check.HELPERS)


if __name__ == "__main__":
    unittest.main()
