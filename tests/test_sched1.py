# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for tools/sched1.py, the replay of GCC 2.95's first scheduling pass. They need no
compiler: the dumps are synthetic, in the form -dS -fsched-verbose-6 and -dN write them."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import sched1  # noqa: E402

# One block: a pointer in r116 (insn 10), two constants (11, 12), two stores through the pointer
# (13, 14, the second output-dependent on the first), a load (15) whose result (latency 2) a
# third store (16) needs. Only one memory access issues per cycle; two ALU insns may. In cycle 2
# the first store wins its tie on register weight (its constant dies), the second constant then
# beats the load on original order; the load's store waits out the load's latency.
SCHED = """
;; Function void func_00100200(int *)

;;   ======================================================
;;   -- basic block 0 from 9 to 16 -- before reload
;;   ======================================================

;;   --------------- forward dependences: ------------

;;   --- Region Dependences --- b 0 bb 0
;;      insn  code    bb   dep  prio  cost   blockage units
;;      ----  ----    --   ---  ----  ----   -------- -----
;;       10   253     0     0     4     1    0 -  0   alu\t: 16 15 14 13
;;       11   253     0     0     4     1    0 -  0   alu\t: 13
;;       12   253     0     0     3     1    0 -  0   alu\t: 14
;;       13   253     0     2     3     1    0 -  0   memory\t: 14
;;       14   253     0     3     2     1    0 -  0   memory\t: 16
;;       15   253     0     1     3     2    0 -  0   memory\t: 16
;;       16   253     0     3     1     1    0 -  0   memory\t:

;;\t\tReady list initially:               12  11  10
;;\tReady list (t =  1):    12  11  10
;;\t\t--> scheduling insn <<<10>>> on unit alu
;;\t\t--> scheduling insn <<<11>>> on unit alu
;;\tReady list (t =  2):    15  12  13
;;\t\t--> scheduling insn <<<13>>> on unit memory
;;\t\t--> scheduling insn <<<12>>> on unit alu
;;\tReady list (t =  3):    14  15
;;\t\t--> scheduling insn <<<15>>> on unit memory
;;\tReady list (t =  4):    14
;;\t\t--> scheduling insn <<<14>>> on unit memory
;;\tReady list (t =  5):    16
;;\t\t--> scheduling insn <<<16>>> on unit memory
;;\tReady list (final):

(insn 10 9 11 (set (reg/v:SI 116)
        (reg:SI 4 a0)) 253 {movsi_internal2} (nil)
    (nil))

(insn 11 10 12 (set (reg:SI 117)
        (const_int 1 [0x1])) 253 {movsi_internal2} (nil)
    (nil))

(insn 12 11 13 (set (reg:SI 118)
        (const_int 2 [0x2])) 253 {movsi_internal2} (nil)
    (nil))

(insn 15 12 13 (set (reg:SI 119)
        (mem:SI (reg/v:SI 116) 0)) 253 {movsi_internal2} (insn_list 10 (nil))
    (nil))

(insn 13 15 14 (set (mem:SI (reg/v:SI 116) 4)
        (reg:SI 117)) 253 {movsi_internal2} (insn_list 10 (insn_list 11 (nil)))
    (nil))

(insn 14 13 16 (set (mem:SI (reg/v:SI 116) 8)
        (reg:SI 118)) 253 {movsi_internal2} (insn_list 10 (insn_list 12 (insn_list:REG_DEP_OUTPUT 13 (nil))))
    (nil))

(insn 16 14 0 (set (mem:SI (reg/v:SI 116) 12)
        (reg:SI 119)) 253 {movsi_internal2} (insn_list 10 (insn_list 15 (insn_list:REG_DEP_OUTPUT 14 (nil))))
    (nil))
"""

# The insns as the pass before sched1 left them: their death notes give the register weights.
REGMOVE = """
;; Function void func_00100200(int *)

(insn 10 9 11 (set (reg/v:SI 116)
        (reg:SI 4 a0)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 4 a0)
        (nil)))

(insn 11 10 12 (set (reg:SI 117)
        (const_int 1 [0x1])) 253 {movsi_internal2} (nil)
    (nil))

(insn 12 11 13 (set (reg:SI 118)
        (const_int 2 [0x2])) 253 {movsi_internal2} (nil)
    (nil))

(insn 13 12 14 (set (mem:SI (reg/v:SI 116) 4)
        (reg:SI 117)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 117)
        (nil)))

(insn 14 13 15 (set (mem:SI (reg/v:SI 116) 8)
        (reg:SI 118)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg:SI 118)
        (nil)))

(insn 15 14 16 (set (reg:SI 119)
        (mem:SI (reg/v:SI 116) 0)) 253 {movsi_internal2} (nil)
    (nil))

(insn 16 15 0 (set (mem:SI (reg/v:SI 116) 12)
        (reg:SI 119)) 253 {movsi_internal2} (nil)
    (expr_list:REG_DEAD (reg/v:SI 116)
        (expr_list:REG_DEAD (reg:SI 119)
            (nil))))
"""


class Parsing(unittest.TestCase):
    def test_table_and_trace(self):
        (b,) = sched1.parse_sched(SCHED)
        self.assertEqual(b.order, [10, 11, 12, 13, 14, 15, 16])
        self.assertEqual(b.rows[15]["unit"], "memory")
        self.assertEqual(b.rows[10]["succ"], [16, 15, 14, 13])
        self.assertEqual(b.trace[:4], [(1, 10), (1, 11), (2, 13), (2, 12)])

    def test_link_kinds_and_weights(self):
        kinds = sched1.link_kinds(SCHED)
        self.assertEqual(kinds[(13, 14)], 2)
        self.assertEqual(kinds[(10, 14)], 0)
        info = sched1.insn_info(REGMOVE)
        self.assertEqual(info[10]["weight"], 0)      # a set and a death
        self.assertEqual(info[11]["weight"], 1)
        self.assertEqual(info[16]["weight"], -1)     # a store with two deaths


class Replay(unittest.TestCase):
    def replay(self, prio=None):
        ((b, r),) = sched1.replay_function(SCHED, REGMOVE, prio=prio)
        return b, r

    def test_matches_the_trace(self):
        b, r = self.replay()
        self.assertEqual(r.out, b.trace)

    def test_priorities_are_longest_paths(self):
        b, r = self.replay()
        self.assertEqual(r.computed_priorities(), {u: row["prio"] for u, row in b.rows.items()})

    def test_one_memory_access_per_cycle(self):
        b, r = self.replay()
        per_cycle = {}
        for clock, u in r.out:
            if b.rows[u]["unit"] == "memory":
                per_cycle[clock] = per_cycle.get(clock, 0) + 1
        self.assertEqual(max(per_cycle.values()), 1)

    def test_priority_override(self):
        # with the second constant first among the ready insns, it issues in cycle 1
        b, r = self.replay({12: 9})
        self.assertEqual(r.out[0], (1, 12))


if __name__ == "__main__":
    unittest.main()
