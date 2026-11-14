# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/headers.py: the parser of declarations and definitions, and the
committed headers of include/functions/."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import headers  # noqa: E402

SOURCE = '''#include "common.h"
s32 Declared(Foo* a, s32 b);
extern "C" {
void InBlock(void);
}
static s32 Hidden(s32 x) { return x; }
void OneLine(s32 v, u32 w) { if (v == 0xFFFF && w); }
Bar* Defined(Foo* self,
             s32 n)
{
    return 0;
}
'''


class ItemsTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.NamedTemporaryFile("w", suffix=".cpp", delete=False)
        self.tmp.write(SOURCE)
        self.tmp.close()
        self.items = {i[1]: i for i in headers.items(Path(self.tmp.name))}

    def tearDown(self):
        Path(self.tmp.name).unlink()

    def test_declarations_and_definitions(self):
        self.assertEqual(self.items["Declared"][0], "decl")
        self.assertEqual(self.items["Defined"][0], "def")
        self.assertEqual(self.items["Defined"][2], "Bar* Defined(Foo* self, s32 n)")
        self.assertNotIn("Hidden", self.items)

    def test_a_one_line_body_is_not_part_of_the_signature(self):
        self.assertEqual(self.items["OneLine"][2], "void OneLine(s32 v, u32 w)")

    def test_c_linkage_inside_a_block(self):
        self.assertTrue(self.items["InBlock"][5])
        self.assertFalse(self.items["Declared"][5])

    def test_types_and_returns(self):
        self.assertEqual(headers.type_names("Bar* Defined(Foo* self, s32 n)", "Defined"), ["Bar", "Foo"])
        self.assertEqual(headers.returns("Bar* Defined(Foo* self, s32 n)"), "Bar*")


class CommittedHeadersTest(unittest.TestCase):
    def test_the_headers_agree_with_the_definitions(self):
        texts, _, _ = headers.generate()
        stale = [p.name for p, t in texts.items() if not p.exists() or p.read_text() != t]
        self.assertEqual(stale, [], "run python3 tools/headers.py write")


if __name__ == "__main__":
    unittest.main()
