# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/data_check.py. They need no disc and no compiler."""

import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import check  # noqa: E402
import data_check  # noqa: E402
import elf  # noqa: E402
import progress  # noqa: E402


class FakeElf:
    """The parts of tools/elf.py's Elf that data_check reads."""

    def __init__(self, data, relocs, symbols, secname=".data.D_00200010"):
        self.sections = [{"index": 0, "name": "", "type": 0, "size": 0},
                         {"index": 1, "name": secname, "type": 1, "size": len(data)},
                         {"index": 2, "name": ".text", "type": 1, "size": 0}]
        self.symbols = symbols
        self._data, self._relocs, self._name = data, relocs, secname

    def section(self, name):
        return self.sections[1] if name == self._name else None

    def contents(self, section):
        return self._data

    def relocations(self, name):
        return self._relocs


class Resolver:
    """US 0x200010 is PAL's 0x210010; US 0x200100 has no PAL address."""

    table = {0x200010: 0x210010, 0x200200: 0x210300}

    def translate(self, a):
        return self.table.get(a)

    def address(self, name):
        return self.translate(int(name[2:], 16)) if name.startswith("D_") else None


class Image:
    def __init__(self, at, data):
        self.at, self.data = at, data

    def read_vaddr(self, addr, size):
        if addr != self.at or size > len(self.data):
            raise ValueError("no section")
        return self.data[:size]


def named(name, shndx=0):
    return {"name": name, "type": 0, "shndx": shndx, "value": 0}


ROW = ("D_00200010", 0x200010, 8, ".data.D_00200010", "src/main/x.cpp")


class TranslateTests(unittest.TestCase):
    def test_pointer_is_translated_to_the_pal_address_of_its_target(self):
        data = bytes(4) + (7).to_bytes(4, "little")      # a REL word holds only the addend
        obj = FakeElf(data, [(0, elf.R_MIPS_32, named("D_00200200"))], [])
        out, note = data_check.section_bytes(obj, ".data.D_00200010", Resolver(), None)
        self.assertEqual(out, (0x210300).to_bytes(4, "little") + (7).to_bytes(4, "little"), note)

    def test_addend_is_kept(self):
        data = (4).to_bytes(4, "little") + bytes(4)
        obj = FakeElf(data, [(0, elf.R_MIPS_32, named("D_00200200"))], [])
        out, _ = data_check.section_bytes(obj, ".data.D_00200010", Resolver(), None)
        self.assertEqual(out[:4], (0x210304).to_bytes(4, "little"))

    def test_pointer_with_no_pal_address_is_refused(self):
        obj = FakeElf(bytes(8), [(0, elf.R_MIPS_32, named("D_00200100"))], [])
        out, note = data_check.section_bytes(obj, ".data.D_00200010", Resolver(), None)
        self.assertIsNone(out)
        self.assertIn("no address in PAL", note)

    def test_whole_file_section_symbol_goes_through_files_tsv(self):
        sym = {"name": "", "type": elf.STT_SECTION, "shndx": 1, "value": 0}
        obj = FakeElf((0x10).to_bytes(4, "little") + bytes(4), [(0, elf.R_MIPS_32, sym)], [], ".data")
        out, note = data_check.section_bytes(obj, ".data", Resolver(), {"data": 0x200000})
        self.assertEqual(out[:4], (0x210010).to_bytes(4, "little"), note)


class CheckGlobalTests(unittest.TestCase):
    def check(self, theirs, row=ROW):
        obj = FakeElf((1).to_bytes(4, "little") + bytes(4), [], [])
        return data_check.check_global(obj, row, Resolver(), Image(0x210010, theirs), None)

    def test_equal_bytes_match(self):
        self.assertEqual(self.check((1).to_bytes(4, "little") + bytes(4)), (0x210010, "match", ""))

    def test_one_byte_differs(self):
        eu, status, note = self.check((2).to_bytes(4, "little") + bytes(4))
        self.assertEqual((eu, status), (0x210010, "differs"))
        self.assertIn("+0x0", note)

    def test_unplaced_global_is_absent(self):
        eu, status, _ = self.check(bytes(8), ("D_00200100", 0x200100, 8, ".data.D_00200100", "x"))
        self.assertEqual((eu, status), (None, "absent"))

    def test_bss_is_absent(self):
        eu, status, note = self.check(bytes(8), ("D_00200010", 0x200010, 8, ".bss", "x"))
        self.assertEqual(status, "absent")
        self.assertIn("bss", note)


class TableTests(unittest.TestCase):
    def test_translate_inside_a_paired_datum(self):
        r = check.Resolver.__new__(check.Resolver)
        r.translation = {0x200000: 0x210000, 0x200100: 0x210200}
        r.paired = None
        self.assertEqual(r.translate(0x200010), 0x210010)
        self.assertIsNone(r.translate(0x2000FF + 0x200))    # past the next pair in PAL

    def test_check_passes_when_rows_agree_with_c_data(self):
        globals_ = [("D_00200010", 0x200010, 8, ".data", "x")]
        with tempfile.TemporaryDirectory() as tmp, \
                mock.patch.object(data_check, "STATUS", Path(tmp) / "s.tsv"), \
                mock.patch.object(data_check, "us_globals", lambda: globals_):
            data_check.write({"D_00200010": ("00210010", 8, "match", "")})
            self.assertEqual(data_check.check_current(), 0)
            data_check.write({"D_00200010": ("00210010", 8, "match", ""), "D_00200020": ("-", 4, "absent", "")})
            self.assertEqual(data_check.check_current(), 1)     # a row for a global C no longer defines
            data_check.write({})
            self.assertEqual(data_check.check_current(), 1)     # a global with no row
            data_check.write({"D_00200010": ("00210010", 4, "match", "")})
            self.assertEqual(data_check.check_current(), 1)     # a size that disagrees

    def test_progress_counts_only_match_rows_for_pal(self):
        status = {"A": ("00210010", 8, "match", ""), "B": ("00210020", 4, "differs", ""), "C": ("-", 4, "absent", "")}
        with mock.patch.object(data_check, "read_status", lambda: status):
            self.assertEqual(progress.c_data("eu"), [(0x210010, 8)])


if __name__ == "__main__":
    unittest.main()
