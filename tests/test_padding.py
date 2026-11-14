# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/padding.py's rule. They need no disc and no compiler."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import padding  # noqa: E402
import progress  # noqa: E402


def image(nonzero=()):
    """read(address, size) of an image that is zero apart from the addresses given."""
    return lambda a, s: bytes(1 if a + i in nonzero else 0 for i in range(s))


class PaddingRuleTest(unittest.TestCase):
    SECTION = [(0x1000, 0x1100)]

    def test_zeros_up_to_the_next_sections_alignment_are_padding(self):
        objects = [(0x1000, 0x1014, 16, "a.cpp .data"), (0x1020, 0x1030, 16, "b.cpp .data")]
        self.assertEqual(padding.find(objects, self.SECTION, image()), [(0x1014, 12, 16, "b.cpp .data")])

    def test_a_gap_as_long_as_the_alignment_is_not(self):
        # 0x1018 is 8-aligned already: the linker would have put b there.
        objects = [(0x1000, 0x1018, 16, "a"), (0x1020, 0x1030, 8, "b")]
        self.assertEqual(padding.find(objects, self.SECTION, image()), [])

    def test_a_nonzero_byte_is_never_padding(self):
        objects = [(0x1000, 0x1014, 16, "a"), (0x1020, 0x1030, 16, "b")]
        self.assertEqual(padding.find(objects, self.SECTION, image({0x101F})), [])

    def test_nothing_before_an_object_whose_alignment_is_not_known(self):
        # The next object is not C (original data, or the rest of a section after an included
        # label): its alignment does not explain the gap.
        objects = [(0x1000, 0x1014, 16, "a"), (0x1020, 0x1030, None, "original data")]
        self.assertEqual(padding.find(objects, self.SECTION, image()), [])

    def test_nothing_across_sections(self):
        objects = [(0x1000, 0x10F4, 4, "a"), (0x1100, 0x1110, 16, "b")]
        self.assertEqual(padding.find(objects, self.SECTION + [(0x1100, 0x1200)], image()), [])

    def test_the_table_lies_between_credited_data(self):
        # Every committed run is zeros the rule allows, outside every C global and original data.
        rows = padding.read_table()
        self.assertTrue(rows)
        credited = progress.c_data("us") + progress.original_data("us")
        for addr, size in rows:
            self.assertFalse([a for a, s in credited if a < addr + size and addr < a + s and s])
        for line in padding.TABLE.read_text().splitlines()[1:]:
            addr, size, align, _before = line.split("\t")
            self.assertLess(int(size), int(align))
            self.assertEqual((int(addr, 16) + int(size)) % int(align), 0)


if __name__ == "__main__":
    unittest.main()
