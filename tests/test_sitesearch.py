# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/sitesearch.py: the head-test generator's text transforms on the real
file, and the guard. They need no compiler."""

import re
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import sitesearch  # noqa: E402

FILE = Path(__file__).resolve().parent.parent / sitesearch.BB18_FILE


class HeadTest(unittest.TestCase):
    def setUp(self):
        if not FILE.exists():
            self.skipTest("%s has moved: update sitesearch.BB18_FILE" % sitesearch.BB18_FILE)
        self.text = FILE.read_text()

    def test_neutral_has_no_site_statement(self):
        n = sitesearch.bb18_neutral(self.text)
        self.assertNotIn("NOT THE ORIGINAL'S STATEMENT", n)
        self.assertNotIn("u32* p3;", n)
        self.assertIn("        return;\n" + sitesearch.STORES, n)
        self.assertEqual(sitesearch.bb18_neutral(n), n)

    def test_landed_form_is_a_candidate(self):
        # The neutral file, plane 3 named and the landed test inserted, is the landed file
        # without the comment over the test.
        landed = re.search(r"\n    if \(\(u32\)p3 & \(w & 15\)\)\n        handle->pictureWidth = 0;\n", self.text)
        if landed is None:
            self.skipTest("the stand-in is no longer in the file")
        want = re.sub(r"    // NOT THE ORIGINAL'S STATEMENT.*?\n(?=    if )", "", self.text, flags=re.S)
        n = sitesearch.bb18_neutral(self.text)
        got = sitesearch.bb18_insert(sitesearch.bb18_name(n, [3]), landed.group(0)[1:])
        self.assertEqual(got, want)

    def test_candidates_are_plain(self):
        labels = set()
        for i, (label, pred, text, stmt) in enumerate(sitesearch.bb18_candidates(self.text)):
            self.assertNotIn(label, labels)
            labels.add(label)
            self.assertIn(pred, ("use", "use?", "no", "no?"))
            if i % 500 == 0:
                self.assertTrue(sitesearch.guard(self.text, text), label)
        self.assertGreater(len(labels), 1000)

    def test_guard(self):
        self.assertTrue(sitesearch.guard("int x;", "int y;"))
        self.assertFalse(sitesearch.guard("int x;", "volatile int y;"))
        self.assertFalse(sitesearch.guard("int x;", "asm(\"nop\");"))


if __name__ == "__main__":
    unittest.main()
