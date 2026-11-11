# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/globalalloc.py, the replay of GCC 2.95's local and global register
allocators. They need no compiler: the dumps are synthetic, in the form -dl and -dg write them."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import globalalloc as ga  # noqa: E402

# One block: a0 copied into r116 (global), r117 and r118 constants local-alloc put in s0 and s1,
# r119 a constant no register is free for. With the frame pointer kept, r119 has to take a
# register from local-alloc: s1's pseudo is used 8 times in 10 insns, more than r119's 4 in 10,
# so the scan from the top passes it and takes s0, whose pseudo is used twice. That pseudo comes
# later in the order and is placed again by global-alloc, in v0.
EVICT_LREG = """
;; Function void func_00100000(int *)

130 registers.

Register 116 used 4 times across 4 insns; set 1 time; user var; 4 bytes; GR_REGS or none; pointer.

Register 117 used 2 times across 10 insns in block 0; set 1 time; 4 bytes; GR_REGS or none.

Register 118 used 8 times across 10 insns in block 0; set 1 time; 4 bytes; GR_REGS or none.

Register 119 used 4 times across 10 insns in block 0; set 1 time; 4 bytes; GR_REGS or none.

1 basic blocks, 0 edges.

Basic block 0: first insn 20, last 13.
Registers live at start: 4 [$4] 29 [$sp]
Registers live at end: 29 [$sp]

;; Register 117 in 16.
;; Register 118 in 17.
(note 20 0 10 [bb 0] NOTE_INSN_BASIC_BLOCK)

(insn 10 20 11 (set (reg/v:SI 116)
        (reg:SI 4 a0)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 4 a0)
        (nil)))

(insn 11 10 12 (set (reg:SI 119)
        (const_int 3 [0x3])) 253 {movsi_internal2} (nil)
    (nil))

(insn 12 11 13 (set (mem:SI (reg/v:SI 116) 0)
        (reg:SI 119)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 119)
        (nil)))

(insn 13 12 0 (set (mem:SI (reg/v:SI 116) 4)
        (reg:SI 2 v0)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg/v:SI 116)
        (nil)))
"""

ALL_GPRS = " ".join(str(r) for r in range(2, 26))
EVICT_GREG = """
;; Function void func_00100000(int *)

;; 2 regs to allocate: 116 119
;; 116 conflicts: 116 117 118 119 2 3 16 17 29
;; 116 preferences: 4
;; 117 conflicts: 116 117 16 29
;; 118 conflicts: 116 118 17 29
;; 119 conflicts: 116 119 %s 29

;; Register dispositions:
116 in 4  117 in 2  118 in 17  119 in 16

;; Hard regs used:  2 4 16 17 29
""" % ALL_GPRS

# One block for local-alloc and the conflict scan: r116 = a0 (a copy, so a0 is a suggestion),
# r117 = 4, r118 = r116 + r117 where r117 dies (tied to r118), then a store through r116.
LOCAL_LREG = """
;; Function void func_00100100(int *)

130 registers.

Register 116 used 3 times across 4 insns in block 0; set 1 time; user var; 4 bytes; GR_REGS or none; pointer.

Register 117 used 2 times across 2 insns in block 0; set 1 time; 4 bytes; GR_REGS or none.

Register 118 used 2 times across 2 insns in block 0; set 1 time; 4 bytes; GR_REGS or none.

1 basic blocks, 0 edges.

Basic block 0: first insn 20, last 13.
Registers live at start: 4 [$4] 29 [$sp]
Registers live at end: 29 [$sp]

;; Register 116 in 4.
;; Register 117 in 2.
;; Register 118 in 2.
(note 20 0 10 [bb 0] NOTE_INSN_BASIC_BLOCK)

(insn 10 20 11 (set (reg/v:SI 116)
        (reg:SI 4 a0)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 4 a0)
        (nil)))

(insn/i 11 10 12 (asm_input ("a
	b")) -1 (nil)
    (nil))

(insn 12 11 14 (set (reg:SI 117)
        (const_int 4 [0x4])) 253 {movsi_internal2} (nil)
    (nil))

(insn 14 12 13 (set (reg:SI 118)
        (plus:SI (reg/v:SI 116)
            (reg:SI 117))) 1 {addsi3} (nil)
    (expr_list:REG_DEAD (reg:SI 117)
        (nil)))

(insn 13 14 0 (set (mem:SI (reg/v:SI 116) 0)
        (reg:SI 118)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg/v:SI 116)
        (expr_list:REG_DEAD (reg:SI 118)
            (nil))))
"""

LOCAL_GREG = """
;; Function void func_00100100(int *)

;; 0 regs to allocate:
;; 116 conflicts: 116 117 118 2 4 29
;; 117 conflicts: 116 117 2 4 29
;; 118 conflicts: 116 118 2 4 29

;; Register dispositions:
116 in 4  117 in 2  118 in 2
"""


class Parsing(unittest.TestCase):
    def test_lreg(self):
        pseudos, local, insns, flow = ga.parse_lreg(LOCAL_LREG)
        self.assertEqual(sorted(pseudos), [116, 117, 118])
        self.assertEqual(pseudos[116].block, 0)
        self.assertEqual(pseudos[118].mode, "SI")
        self.assertEqual(local, {116: 4, 117: 2, 118: 2})
        # the asm string spanning two lines does not swallow the insns after it
        self.assertEqual(flow["chain"], [20, 10, 11, 12, 14, 13])
        self.assertEqual(flow["blocks"], [(20, 13, {4, 29})])

    def test_greg(self):
        g = ga.parse_greg(EVICT_GREG)
        self.assertEqual(g["order"], [116, 119])
        self.assertEqual(g["preferences"], {116: [4]})
        self.assertEqual(g["disposition"], {116: 4, 117: 2, 118: 17, 119: 16})


class GlobalReplay(unittest.TestCase):
    def replay(self):
        # the conflicts are the dump's (written by hand, not from the RTL)
        return ga.replay(ga.model_from_text(EVICT_LREG, EVICT_GREG, need_fp=True))

    def test_matches_the_dump(self):
        m = self.replay()
        out = []

        class Sink:
            def write(self, s):
                out.append(s)
        self.assertEqual(ga.check(m, Sink()), 0, "".join(out))

    def test_priority_order(self):
        m = self.replay()
        # 116: 2 * 4 / 4; 119: 2 * 4 / 10; the local ones in between by their own measure
        self.assertEqual(m.priority(116), 20000)
        self.assertEqual(m.priority(119), 8000)
        self.assertEqual([r for r in m.order if r not in m.local], [116, 119])

    def test_copy_preference(self):
        m = self.replay()
        place = [e for e in m.events if e["kind"] == "place" and e["reg"] == 116][0]
        self.assertEqual(place["hard"], 4)

    def test_poorly_used_eviction(self):
        m = self.replay()
        ev = [e for e in m.events if e["kind"] == "evict"]
        self.assertEqual(len(ev), 1)
        self.assertEqual((ev[0]["reg"], ev[0]["hard"], ev[0]["gone"]), (119, 16, [117]))
        scanned = [(r, why.split(":")[0]) for r, why, _ in ev[0]["scan"]]
        self.assertEqual(scanned, [(17, "kept"), (16, "taken")])
        self.assertEqual(m.renumber[117], 2)

    def test_what_if(self):
        # s1's pseudo used twice is now the least used from the top: s1 is taken instead
        m = ga.replay(ga.model_from_text(EVICT_LREG, EVICT_GREG, sets=["118:refs=2"], need_fp=True))
        self.assertEqual(m.renumber[119], 17)
        self.assertEqual(m.renumber[117], 16)
        self.assertEqual(m.renumber[118], 2)

    def test_pass_zero_opens_no_saved_register(self):
        # Without the frame pointer, s8 is free of conflicts (they are eliminated) and taken in
        # pass 1, since pass 0 only uses registers already in use.
        m = ga.replay(ga.model_from_text(EVICT_LREG, EVICT_GREG))
        place = [e for e in m.events if e["kind"] == "place" and e["reg"] == 119][0]
        self.assertEqual((place["hard"], place["how"]), (30, "pass 1"))


class Conflicts(unittest.TestCase):
    def test_computed_like_the_dump(self):
        m = ga.replay(ga.model_from_text(LOCAL_LREG, LOCAL_GREG), verify=True)
        conf, hard = m.computed
        self.assertEqual(conf, m.dumped_conf)
        self.assertEqual(hard, m.dumped_hard)
        self.assertEqual(hard[116], {2, 4, 29})


class LocalAlloc(unittest.TestCase):
    def test_tie_and_suggestion(self):
        pseudos, local, insns, flow = ga.parse_lreg(LOCAL_LREG)
        lm = ga.LocalModel(pseudos, insns, flow)
        self.assertEqual(lm.run(), local)
        tied = [q["regs"] for q in lm.qtys if len(q["regs"]) > 1]
        self.assertEqual(tied, [[117, 118]])

    def test_priority_override(self):
        pseudos, local, insns, flow = ga.parse_lreg(LOCAL_LREG)
        got = ga.LocalModel(pseudos, insns, flow).run({117: 1})
        self.assertEqual(got[117], 2)


if __name__ == "__main__":
    unittest.main()
