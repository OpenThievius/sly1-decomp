# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/classes.py, the class map.
They need no disc: the listings are synthetic."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import classes  # noqa: E402


def word(address, value, operand=None):
    raw = value.to_bytes(4, "little").hex().upper()
    return "    /* %06X %08X %s */ .word %s" % (address - 0x100000, address, raw, operand or "0x%08X" % value)


def func(address, target):
    return word(address, target, "func_%08X" % target)


def ptr(address, target):
    return word(address, target, "D_%08X" % target)


def label(address, lines):
    name = "D_%08X" % address
    return ["nonmatching " + name, "", "dlabel " + name] + lines + ["enddlabel " + name, ""]


ROOT, BASE, CHILD, OTHER, HEAD, TABLE = 0x217410, 0x217418, 0x217440, 0x217470, 0x2174B0, 0x247448


def listing(child_id=2):
    """root; class 1 (3 slots); class 2, a child of 1 (4 slots, one overridden); class 3, a
    child of 1 whose label runs on two words past its only child, class 4 (3 slots); a head."""
    out = [".section .rodata"]
    out += label(ROOT, [word(ROOT, 0), word(ROOT + 4, 0)])
    out += label(BASE, [ptr(BASE, ROOT), word(BASE + 4, 1), word(BASE + 8, 0), word(BASE + 12, 0x34),
                        func(BASE + 16, 0x100000), func(BASE + 20, 0x100010), word(BASE + 24, 0)])
    out += label(CHILD, [ptr(CHILD, BASE), word(CHILD + 4, child_id), word(CHILD + 8, 1),
                         word(CHILD + 12, 0x40), func(CHILD + 16, 0x100020), func(CHILD + 20, 0x100010),
                         word(CHILD + 24, 0), func(CHILD + 28, 0x100030)])
    # class 3 and, right after its three slots and two words of something else, class 4
    out += label(OTHER, [ptr(OTHER, BASE), word(OTHER + 4, 3), word(OTHER + 8, 0), word(OTHER + 12, 0x34),
                         func(OTHER + 16, 0x100000), func(OTHER + 20, 0x100040), word(OTHER + 24, 0),
                         func(OTHER + 28, 0x100050), func(OTHER + 32, 0x100060)])
    four = OTHER + 36
    out += label(four, [ptr(four, OTHER), word(four + 4, 4), word(four + 8, 0), word(four + 12, 0x38),
                        func(four + 16, 0x100000), func(four + 20, 0x100040), word(four + 24, 0)])
    out += label(HEAD, [ptr(HEAD, ROOT), word(HEAD + 4, 5)])
    table = [ROOT, BASE, CHILD, OTHER, four, HEAD]
    out += label(TABLE, [ptr(TABLE + 4 * i, a) for i, a in enumerate(table)])
    return "\n".join(out) + "\n"


FUNCTIONS = {"func_%08X" % a for a in range(0x100000, 0x100070, 0x10)}


class ClassMapTest(unittest.TestCase):
    def setUp(self):
        self.entries, classes.ENTRIES = classes.ENTRIES, 6

    def tearDown(self):
        classes.ENTRIES = self.entries

    def rows(self, text=None):
        words, labels = classes.read_data([text or listing()])
        return classes.descriptors(words, labels, FUNCTIONS)

    def test_the_header_and_the_parent(self):
        rows = self.rows()
        self.assertEqual([r["kind"] for r in rows], ["root", "class", "class", "class", "class", "head"])
        self.assertEqual((rows[2]["parent"], rows[2]["flags"], rows[2]["size"], rows[2]["depth"]), (1, 1, 0x40, 2))
        self.assertEqual((rows[5]["parent"], rows[5]["depth"]), (0, 1))

    def test_own_and_inherited_slots(self):
        child = self.rows()[2]
        self.assertEqual(child["slots"], ["func_00100020", "func_00100010", "0", "func_00100030"])
        self.assertEqual(child["own"], [True, False, False, True])

    def test_a_class_ends_at_its_childrens_slots(self):
        rows = self.rows()
        self.assertEqual(rows[3]["words"], 9)
        self.assertEqual(len(rows[3]["slots"]), 3)
        self.assertEqual(rows[3]["note"], "2 words after its slots")
        self.assertEqual(rows[4]["own"], [False, False, False])

    def test_a_descriptor_ends_at_its_label(self):
        self.assertEqual(self.rows()[4]["words"], 7)

    def test_an_id_must_be_its_index(self):
        with self.assertRaises(SystemExit):
            self.rows(listing(child_id=7))

    def test_a_slot_must_be_a_function(self):
        words, labels = classes.read_data([listing()])
        with self.assertRaises(SystemExit):
            classes.descriptors(words, labels, FUNCTIONS - {"func_00100030"})

    def test_the_tables(self):
        rows = self.rows()
        _p, text = classes.write_classes(rows)
        line = text.splitlines()[3]
        self.assertTrue(line.startswith("0x02\t00217440\tclass\t0x2\t0x01\t2\t0x1\t0x40\t8\t4\t2\t-\t"))
        self.assertTrue(line.endswith("+func_00100020 func_00100010 0 +func_00100030"))
        _p, text = classes.write_methods(rows)
        self.assertIn("func_00100010\t0x01@0x14\t1", text.splitlines())


class CreatorTest(unittest.TestCase):
    def insns(self, lines):
        text = "glabel func_00100000\n" + "\n".join(
            l if l.startswith(".L") else "    /* 0 %08X 00000000 */  %s" % (0x100000 + 4 * k, l)
            for k, l in enumerate(lines)) + "\n"
        return classes.read_text(text.replace("\n.L", "\n  .L"))["func_00100000"]

    def made(self, lines):
        return classes.creators({"func_00100000": self.insns(lines)}, [None] * 0x100)

    def test_the_id_in_the_delay_slot(self):
        self.assertEqual(self.made(["jal func_0011E580", " addiu $a0, $zero, 0x6C"]), {0x6C: ["func_00100000"]})

    def test_the_id_before_the_call(self):
        self.assertEqual(self.made(["addiu $a0, $zero, 0x51", "daddu $a1, $s0, $zero",
                                    "jal func_0011E580", " nop"]), {0x51: ["func_00100000"]})

    def test_a_loop_sets_it_on_every_way_in(self):
        self.assertEqual(self.made(["addiu $a0, $zero, 0x1E", ".L00100004:", "jal func_0011E580", " nop",
                                    "bgez $s0, .L00100004", " addiu $a0, $zero, 0x1E"]),
                         {0x1E: ["func_00100000"]})
        self.assertEqual(self.made(["addiu $a0, $zero, 0x1E", ".L00100004:", "jal func_0011E580", " nop",
                                    "bgez $s0, .L00100004", " addiu $a0, $zero, 0x1F"]), {})

    def test_an_id_from_a_register_or_a_call_is_not_followed(self):
        self.assertEqual(self.made(["daddu $a0, $s1, $zero", "jal func_0011E580", " nop"]), {})
        self.assertEqual(self.made(["addiu $a0, $zero, 1", "jal func_00100100", " nop",
                                    "jal func_0011E580", " nop"]), {})


if __name__ == "__main__":
    unittest.main()
