# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/regalloc.py, the register-allocation explainer, and the -dp marks of
tools/compile.py. They need no compiler: the dumps and the listing are synthetic, in the form
GCC 2.95's -dl, -dg and -dp and GNU as's -alm write them."""

import collections
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import compile as cc  # noqa: E402
import regalloc  # noqa: E402

# One block: a0 is copied into r117, r118 is loaded through it, r119 = 4, then a compare and
# a store. local-alloc places r118 and r119; r117 is global-alloc's.
LREG = """
;; Function int func_00100000(int *)

130 registers.

Register 117 used 3 times across 5 insns; set 1 time; user var; 4 bytes; GR_REGS or none; pointer.

Register 118 used 2 times across 2 insns in block 0; set 1 time; 4 bytes; GR_REGS or none.

Register 119 used 2 times across 3 insns in block 0; set 1 time; 4 bytes; GR_REGS or none.

1 basic blocks, 2 edges.

Basic block 0: first insn 20, last 14.
Predecessors:  ENTRY (fallthru)
Successors:  EXIT (fallthru)
Registers live at start: 4 [$4] 29 [$sp]
Registers live at end: 2 [$2] 29 [$sp]

;; Register 118 in 2.
;; Register 119 in 3.
(note 1 0 20 ("t.cpp") 3)

(note 20 1 10 [bb 0] NOTE_INSN_BASIC_BLOCK)

(insn 10 20 21 (set (reg/v:SI 117)
        (reg:SI 4 a0)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 4 a0)
        (nil)))

(note 21 10 12 ("t.cpp") 4)

(insn 12 21 11 (set (reg:SI 119)
        (const_int 4 [0x4])) 253 {movsi_internal2} (nil)
    (nil))

(insn 11 12 13 (set (reg:SI 118)
        (mem:SI (reg/v:SI 117) 0)) 253 {movsi_internal2} (nil)
    (nil))

(note 22 11 13 ("t.cpp") 5)

(insn 13 22 14 (set (reg:SI 2 v0)
        (plus:SI (reg:SI 118)
            (reg:SI 119))) 1 {addsi3} (nil)
    (expr_list:REG_DEAD (reg:SI 118)
        (expr_list:REG_DEAD (reg:SI 119)
            (nil))))

(insn 14 13 0 (set (mem:SI (reg/v:SI 117) 0)
        (reg:SI 2 v0)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg/v:SI 117)
        (nil)))
"""

GREG = """
;; Function int func_00100000(int *)

;; 1 regs to allocate: 117
;; 117 conflicts: 117 118 119 4 29
;; 117 preferences: 4

;; Register dispositions:
117 in 5  118 in 2  119 in 3

;; Hard regs used:  2 3 4 5 29

(insn 10 20 21 (set (reg/v:SI 5 a1)
        (reg:SI 4 a0)) 253 {movsi_internal2} (nil)
    (nil))

(insn 12 10 11 (set (reg:SI 3 v1)
        (const_int 4 [0x4])) 253 {movsi_internal2} (nil)
    (nil))

(insn 11 12 13 (set (reg:SI 2 v0)
        (mem:SI (reg/v:SI 5 a1) 0)) 253 {movsi_internal2} (nil)
    (nil))

(insn 13 11 30 (set (reg:SI 2 v0)
        (plus:SI (reg:SI 2 v0)
            (reg:SI 3 v1))) 1 {addsi3} (nil)
    (nil))

(insn 30 13 14 (set (reg:SI 6 a2)
        (reg:SI 2 v0)) 253 {movsi_internal2} (nil)
    (nil))

(insn 14 30 0 (set (mem:SI (reg/v:SI 5 a1) 0)
        (reg:SI 6 a2)) 253 {movsi_internal2} (nil)
    (nil))
"""

LISTING = """GAS LISTING unit.s \t\t\tpage 1


   1              \t\t.file\t1 "t.cpp"
   2              \t\t.section .text.func_00100000__FPi,"ax",@progbits
   3 0000 2D288000 \t\tmove\t$5,$4\t # 10\tmovsi_internal2/1\t[length = 1]
   4 0004 04000324 \t\tli\t$3,4\t\t\t# 0x4\t # 12\tmovsi_internal2/3\t[length = 1]
   5 0008 0000A28C \t\tlw\t$2,0($5)\t # 11\tmovsi_internal2/5\t[length = 1]
   6 000c 21104300 \t\taddu\t$2,$2,$3\t # 13\taddsi3\t[length = 1]
   7 0010 0000013C \t\tli.s\t$f0,1.0\t # 40\tmovsf_internal1/4\t[length = 2]
   7      00008144
   8              \t #APP
   9 0018 0118C248 \t\tctc2.i $2, $vi3
  10              \t #NO_APP
  11              \t\t.section .text.other,"ax",@progbits
  12 0000 00000000 \t\tnop\t # 99\tnop\t[length = 1]
"""


class Fake:
    """What compile_with_dumps returns, without a compiler."""

    def __init__(self, listing=LISTING):
        self.listing = regalloc.parse_listing(listing, ".text.func_00100000__FPi")
        self.lreg_text, self.greg_text = LREG, GREG
        self.start, self.source_name = 0, "t.cpp"


class Parsing(unittest.TestCase):
    def test_sexpr(self):
        x = regalloc.parse_sexpr('(insn 5 4 6 (parallel[ (set (reg:SI 2 v0) (const_int 1 [0x1])) '
                                 '(asm_operands/v ("ctc2.i %0, $vi%1") ("") 0[ ]) ]) -1 (nil) (nil))')
        self.assertEqual(regalloc.head(x), "insn")
        self.assertEqual(regalloc.regs_in(x[4]), [2])
        self.assertEqual(regalloc.asm_template(x[4]), "ctc2.i %0, $vi%1")

    def test_defs_uses(self):
        x = regalloc.parse_sexpr("(set (mem:SI (plus:SI (reg:SI 120) (const_int 4)) 0) (reg:SI 121))")
        self.assertEqual(regalloc.defs_uses(x), (set(), {120, 121}))
        x = regalloc.parse_sexpr("(set (subreg:SI (reg:DI 130) 0) (reg:SI 131))")
        self.assertEqual(regalloc.defs_uses(x), ({130}, {130, 131}))

    def test_lreg(self):
        d = regalloc.Dump(regalloc.function_part(LREG, "func_00100000"))
        self.assertEqual(d.order, [10, 12, 11, 13, 14])
        self.assertEqual(d.local, {118: 2, 119: 3})
        self.assertEqual(d.info[118]["block"], 0)
        self.assertIsNone(d.info[117]["block"])
        self.assertTrue(d.info[117]["user"])
        self.assertEqual(d.insns[11].line, ("t.cpp", 4))
        self.assertEqual(d.insns[13].line, ("t.cpp", 5))
        self.assertEqual(d.blocks[0]["end"], {2, 29})

    def test_greg(self):
        d = regalloc.Dump(GREG)
        self.assertEqual(d.to_allocate, [117])
        self.assertEqual(d.disposition, {117: 5, 118: 2, 119: 3})
        self.assertEqual(d.preferences[117], [4])
        self.assertIn(4, d.conflicts[117])

    def test_liveness(self):
        d = regalloc.Dump(LREG)
        live = regalloc.liveness(d)
        self.assertIn(117, live[13])            # live through the add, to the store
        self.assertIn(119, live[11])            # set before the load, used after it
        self.assertNotIn(118, live[10])

    def test_listing(self):
        rows = regalloc.parse_listing(LISTING, ".text.func_00100000__FPi")
        self.assertEqual([(o, u) for o, u, _ in rows],
                         [(0, 10), (4, 12), (8, 11), (12, 13), (16, 40), (20, 40), (24, None)])

    def test_templates(self):
        rx, = regalloc.template_regexes("ctc2.i %0, $vi%1")
        self.assertTrue(rx.match("ctc2.i $2, $vi3"))
        self.assertFalse(rx.match("ctc2.ni $2, $vi3"))
        self.assertEqual(len(regalloc.template_regexes("vnop\\n\\tvcallms 0x10")), 2)

    def test_registers(self):
        self.assertEqual(regalloc.reg_number("a1"), 5)
        self.assertEqual(regalloc.reg_number("$f12"), 44)
        self.assertIsNone(regalloc.reg_number("$vf3"))
        self.assertEqual(regalloc.reg_name(44), "$f12")
        self.assertEqual(regalloc.reg_name(30), "$s8")


class Mapping(unittest.TestCase):
    def setUp(self):
        self.a = regalloc.Analysis(Fake(), "func_00100000", source_root=Path("/nonexistent"))

    def test_pseudo_of(self):
        self.assertEqual(self.a.pseudo_of(11, 2)[:2], ("pseudo", 118))
        self.assertEqual(self.a.pseudo_of(11, 5)[:2], ("pseudo", 117))
        self.assertEqual(self.a.pseudo_of(13, 3)[:2], ("pseudo", 119))
        self.assertEqual(self.a.pseudo_of(10, 4)[:2], ("hard", 4))
        self.assertEqual(self.a.pseudo_of(99, 2)[0], "unknown")

    def test_reload_insn(self):
        # insn 30 is reload's: the store at 14 reads a2, which holds no pseudo of 14's.
        kind, p, _ = self.a.pseudo_of(30, 6)
        self.assertEqual(kind, "reload")

    def test_allocators(self):
        self.assertEqual(self.a.allocator(118)[0], "local-alloc")
        self.assertEqual(self.a.allocator(117)[0], "global-alloc")

    def test_local_priority(self):
        # r119 is set at the block's second insn and used at its fourth (span 2); r118 at the
        # third and fourth (span 1): local-alloc places r118 first.
        self.assertEqual(self.a.block_span(119), (1, 3))
        self.assertEqual(self.a.block_span(118), (2, 3))
        self.assertGreater(self.a.pri(118), self.a.pri(119))
        self.assertTrue(self.a.placed_before(118, 119))
        self.assertTrue(self.a.placed_before(118, 117))      # local before global

    def test_explain_swap(self):
        # Retail had r118 in v1 and r119 in v0: the two swap, and r119 must go first.
        self.a.retail_of = {118: collections.Counter({3: 2}),
                            119: collections.Counter({2: 2})}
        swaps = self.a.swaps()
        self.assertEqual(len(swaps), 1)
        self.assertIn("r118 ($v0) and r119 ($v1) swap", swaps[0])
        self.assertIn("insn 12 sets r119; insn 11 sets r118; insn 13 uses r118 r119", swaps[0])
        lines, levers = self.a.explain(119, 3, 2)
        self.assertTrue(any("$v0 is taken by r118" in s for s in lines))

    def test_template_uid(self):
        self.assertEqual(self.a.uid_at[6][0], None)     # no asm insn in the dump for ctc2.i


class Marks(unittest.TestCase):
    def test_restore(self):
        marked = "\tmove\t$5,$4\t # 10\tmovsi_internal2/1\t[length = 1]\n\tj\t$31\t # 20\treturn\t[length = 1]"
        plain = cc.INSN_MARK.sub("", marked)
        self.assertEqual(plain, "\tmove\t$5,$4\n\tj\t$31")
        moved = "\t.set\tnoreorder\n\tmove\t$5,$4\n\tj\t$31\n\t.set\treorder"
        back = cc.restore_marks(moved, marked)
        self.assertIn("# 10", back.split("\n")[1])
        self.assertIn("# 20", back.split("\n")[2])


if __name__ == "__main__":
    unittest.main()
