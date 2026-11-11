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
import version_src  # noqa: E402


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


class OwnDataTests(unittest.TestCase):
    """PAL's own definition of a global (src/versions/eu/<file>/D_XXXXXXXX.cpp)."""

    SHARED = (
        '#include "common.h"\n'
        "extern s32 D_00200010[4];\n"
        "void func_00100010(void) { D_00200010[0] = 1; }\n"
        "// a comment; with a semicolon\n"
        "s32 D_00200010[4] = { 1, 2,\n"
        "                       3, 4 };\n"
        "INCLUDE_DATA(D_00200020);\n"
        "INCLUDE_ASM(func_00100030);\n"
        "s32 D_00200030 = 5;\n"
    )

    def test_the_definition_is_found_and_the_declaration_is_not(self):
        start, end = version_src.data_span(self.SHARED, "D_00200010")
        self.assertEqual(self.SHARED[start:end], "s32 D_00200010[4] = { 1, 2,\n                       3, 4 };")
        with self.assertRaises(version_src.VersionSourceError):
            version_src.data_span("extern s32 D_00200010[4];\n", "D_00200010")

    def test_an_extern_with_an_initial_value_is_a_definition(self):
        text = 'extern s32 D_00200010[2];\nextern const char D_00200010[2] = "a;";\n'
        start, end = version_src.data_span(text, "D_00200010")
        self.assertEqual(text[start:end], 'extern const char D_00200010[2] = "a;";')

    def test_a_definition_in_a_function_body_is_not_the_globals(self):
        with self.assertRaises(version_src.VersionSourceError):
            version_src.data_span("void f(void) {\n    s32 D_00200010 = 1;\n}\n", "D_00200010")

    def test_a_global_is_replaced_in_the_unit(self):
        with tempfile.TemporaryDirectory() as tmp:
            shared, own = Path(tmp) / "shared.cpp", Path(tmp) / "D_00200010.cpp"
            shared.write_text(self.SHARED)
            own.write_text("// PAL\ns32 D_00200010[4] = { 9, 8, 7, 6 };\n")
            text = version_src.unit_text(shared, {"D_00200010": own})
        self.assertIn("{ 9, 8, 7, 6 };", text)
        self.assertNotIn("3, 4 };", text)
        self.assertIn("extern s32 D_00200010[4];", text)
        self.assertIn("s32 D_00200030 = 5;", text)

    def test_the_unit_that_checks_data_keeps_the_data_it_includes(self):
        with tempfile.TemporaryDirectory() as tmp:
            shared = Path(tmp) / "shared.cpp"
            shared.write_text(self.SHARED)
            plain = version_src.unit_text(shared, {})
            kept = version_src.unit_text(shared, {}, keep_data=True)
        self.assertNotIn("INCLUDE_DATA", plain)
        self.assertIn("INCLUDE_DATA(D_00200020);", kept)
        self.assertNotIn("INCLUDE_ASM", kept)

    def test_only_a_global_name_is_data(self):
        self.assertTrue(version_src.DATA_NAME.match("D_00200010"))
        self.assertFalse(version_src.DATA_NAME.match("D_eu_00200010"))
        self.assertFalse(version_src.DATA_NAME.match("func_00200010"))

    def test_a_definition_of_its_own_is_stale_when_the_shared_file_lacks_it(self):
        with tempfile.TemporaryDirectory() as tmp:
            shared = Path(tmp) / "shared.cpp"
            shared.write_text("extern s32 D_00200010;\n")
            own = Path(tmp) / "D_00200010.cpp"
            own.write_text("s32 D_00200010 = 1;\n")
            with mock.patch.object(version_src, "data_overrides", lambda key: {"D_00200010": own}), \
                    mock.patch.object(version_src, "version_of", lambda path: ("eu", shared)):
                problems = data_check.own_problems()
        self.assertEqual(len(problems), 1)
        self.assertIn("which its shared file does not", problems[0])


if __name__ == "__main__":
    unittest.main()


class PlacementTests(unittest.TestCase):
    """Where the start of a datum is in PAL (check.Resolver.place, data_check.whole_address)."""

    def resolver(self, translation):
        r = check.Resolver.__new__(check.Resolver)
        r.translation, r.paired, r.placed, r.extent = translation, None, {}, {}
        return r

    # The nearest pair below 0x200000 puts a datum at 0x210000 + 0x10; its own addresses say 0x210030.
    TABLE = {0x1FFFF0: 0x210000, 0x200040: 0x210070, 0x200080: 0x2100B0}

    def test_the_datums_own_addresses_outrank_the_nearest_below(self):
        r = self.resolver(self.TABLE)
        self.assertEqual(r.translate(0x200000), 0x210010)
        self.assertEqual(r.place(0x200000, 0x100), 0x210030)
        self.assertEqual(r.placed[0x200000], 0x210030)

    def test_one_address_of_its_own_is_not_enough(self):
        r = self.resolver({0x1FFFF0: 0x210000, 0x200040: 0x210070})
        self.assertEqual(r.place(0x200000, 0x100), 0x210010)

    def test_addresses_that_disagree_keep_the_translation(self):
        r = self.resolver({0x1FFFF0: 0x210000, 0x200040: 0x210070, 0x200080: 0x2100C0})
        self.assertEqual(r.place(0x200000, 0x100), 0x210010)

    def test_a_directly_paired_start_stays(self):
        r = self.resolver({0x200000: 0x210000, 0x200040: 0x210070, 0x200080: 0x2100B0})
        self.assertEqual(r.place(0x200000, 0x100), 0x210000)

    def test_a_datum_with_no_place_has_none(self):
        r = self.resolver({0x200100: 0x210100, 0x200200: 0x210200})
        self.assertIsNone(r.place(0x200000, 0x10))
        self.assertNotIn(0x200000, r.placed)

    def test_section_starts_pair_the_sections_both_executables_have(self):
        class Exe:
            def __init__(self, sections):
                self.sections = sections

            def section(self, name):
                return self.sections.get(name)

        us = Exe({".rodata": {"addr": 0x217380}, ".data": {"addr": 0x250580}, ".bss": {"addr": 0}})
        pal = Exe({".rodata": {"addr": 0x218880}, ".data": {"addr": 0x251880}, ".bss": {"addr": 0x284B00},
                   ".extra": {"addr": 0x300000}})
        self.assertEqual(check.section_starts(us, pal), {0x217380: 0x218880, 0x250580: 0x251880})

    def test_a_pointer_into_a_placed_whole_section_follows_its_placement(self):
        r = self.resolver(self.TABLE)
        r.place(0x200000, 0x100)
        self.assertEqual(data_check.whole_address(r, 0x200000, 0x20), 0x210050)
        self.assertEqual(data_check.whole_address(r, 0x200040, 0), 0x210070)    # not placed: translated


class PlacedPointerTests(unittest.TestCase):
    def test_a_label_inside_a_placed_datum_translates_by_its_offset(self):
        r = PlacementTests().resolver(PlacementTests.TABLE)
        r.place(0x200000, 0x100)
        self.assertEqual(data_check.inside_placed(r, 0x200028), 0x210058)
        self.assertIsNone(data_check.inside_placed(r, 0x200100))

    def test_an_undefined_symbol_in_a_placed_datum_is_resolved_through_it(self):
        class Placed(Resolver):
            placed = {0x200300: 0x210800}
            extent = {0x200300: 0x40}

            def us_address(self, name):
                return int(name[2:], 16)

        obj = FakeElf(bytes(4) + (8).to_bytes(4, "little"), [(4, elf.R_MIPS_32, named("D_00200300"))], [])
        out, note = data_check.section_bytes(obj, ".data.D_00200010", Placed(), None)
        self.assertEqual(out[4:], (0x210808).to_bytes(4, "little"), note)


class DescribeTests(unittest.TestCase):
    def test_words_are_counted_by_what_they_are(self):
        ours = b"Text" + (0x120000).to_bytes(4, "little") + (7).to_bytes(4, "little") + bytes(4)
        theirs = b"Tent" + bytes(12)
        note = data_check.describe(ours, theirs, {4})
        self.assertEqual(note, "first difference at +0x2; 1 text, 1 pointer, 1 other words differ")

    def test_check_global_names_the_cause_of_a_difference(self):
        obj = FakeElf((1).to_bytes(4, "little") + bytes(4), [], [])
        _eu, status, note = data_check.check_global(
            obj, ROW, Resolver(), Image(0x210010, (2).to_bytes(4, "little") + bytes(4)), None)
        self.assertEqual(status, "differs")
        self.assertIn("1 other words differ", note)
