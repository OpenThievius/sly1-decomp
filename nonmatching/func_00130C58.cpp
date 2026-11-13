// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 729/748 (97.5%), checked 2026-11-12
// NEAR (src/main/placed_object.cpp, where it is INCLUDE_ASM with INCLUDE_RODATA(D_00249C90)):
// retail keeps the switch's constant 3 in s8 (loop.c moved it before the outer loop, so s8 is
// saved too: 16 bytes more); ours loads it in the loop (li v0,3 in the case-2 branch's slot).
// Each tree constant is its own pseudo with life 1 and savings 1; the 2 matches found == 2
// (savings 2) and moves, the 3 needs 76 >= 104 insns (pass 1; 79 >= 90 in pass 2) and stays.
// Built with -fmove-all-movables (to explore only) the 1, 2 and 3 move in pass 1 and the code is
// retail's (the 1 rematerialised as li v0,1) except the block after the outer loop: PRE hoists
// FLT_MAX's %hi to the entry, local-alloc gives it v0 and the window count's subu v1 (retail:
// subu v0, lui v1 just before the lwc1). So retail's 1 and 3 each had a second set of the same
// constant (or a loop of at most 73 insns): not found (docs/TOOLCHAIN.md, "A switch's case
// constants in a loop with calls"). SolveQuadratic's real prototype has the roots last: with
// them first, cases 0 and 2 set a0 before $f12. Matched on the way: the final search as a goto
// loop (retail's has its test at the top and no strength reduction: loop.c never sees it), the
// window count in found's register, the va slots read as words.
// Tried for the 3: the case order, j <= 3, the counter's type, the switch in an inline, j == 3
// in case 3 (cse1 folds it), case 2: case 3: shared (a range), one call after the switch.
// w32 (2026-11-11, -dL): first differing block is the case tree's j == 2 / j == 3 tests (ours
// `beq s3,s6; li v0,3; beql s3,v0`, retail `beql s3,s6; beql s3,s8`), the rest follows from s8.
// loop.c's numbers: threshold 79 (call in the loop), less 3 per register moved; movables in
// order 1, 2, 3, floats. Pass 1 (104 insns): the 1 fails (79 < 104), the 2 moves (savings 2,
// life 2: 79*4), the 3 fails (76*1 < 104). Pass 2: 90 insns, both fail. Four calls cost 17 insns
// per case (10 to compute, 3 float moves, a0, the call, found = v0, the jump), so with retail's four
// calls the inner loop cannot fall to 76; and retail's crossjump shape (cases 0 and 1 kept apart,
// case 2's tail merged into case 3's) is the four-call one. So retail's 3 had savings * life >= 2
// in pass 1: a second SImode (or narrower) `(set (reg) (const_int 3))` inside the inner loop at
// loop time, gone by the final code (s8 is read only by the beql). Not found. Tested: one call
// after the switch (a, b, d set per case): the loop is 74 insns in pass 2, the 1 and the 3 both
// move, but the args are global pseudos (live around the loop through the no-match path) in f20+
// and 512 bytes; with `default: goto check;` around the call the frame is retail's 496 and s8 = 3,
// but cases 0 and 1 merge (crossjump) and the case bodies go through f1-f3 temporaries (147/187).
// w35 (2026-11-12, -dj -ds -dG -dL -dt -df -dS -dl; docs/toolchain/loops.md, "The 3's second
// set"): both walls are the same kind of thing, the notes of a loop that never iterates, and a
// probe with two of them is EXACT on US and PAL with the file's own flags (not plain C++ as
// AGENTS.md has it, so not landed; kept in build/swarm/w35-fable/probes/):
//   case 3:  do { } while (0); found = SolveQuadratic(j == 3 ? -t : t, ...same...);
//   after the loops:  do { found = w - windows; k = -1; } while (0); best = FLT_MAX;
// (1) The 3. cse1 stops its path at a NOTE_INSN_LOOP_END (cse_end_of_basic_block, "Don't cse
// out the end of a loop"), so the `j == 3` behind one in case 3 keeps its own `(set X 3); bne
// j,X`; loop.c matches X with the tree's 3 (savings 2, life 2: 76 * 4 >= 107, "moved"), which
// deletes X's set and makes the test `bne j,H`; cse2 (after_loop, the note ignored) follows the
// tree's `beq j,H` into the case and folds it. Flow then counts the tree's use alone (r196: 4
// refs over 186 insns), so 2, n and 3 take s6, s7 and s8. The 1 is not moved (retail's `li v0,1`
// is the loop's own). Only a test of j against the case's own value folds in cse2: the hoisted
// constants are unknown registers there. Ruled out: `if (j == 3) { two dead stores }` after the
// switch (3 moves, but its jump lives to jump2: 3 refs, 3 takes s6); an inline `switch (j)` of
// four cases returning +-t, used in every case (cse1 follows the jumps and folds all of it: 106
// insns, no second 3); a lone dead store under `j == 3` (jump.c makes it a conditional move).
// (2) The block after the loops. Retail's order and registers need `found = w - windows; k = -1`
// inside a loop's notes and `best` after its LOOP_END: flow counts the subtraction's two
// references at depth 2 (r200: "used 4 times across 3 insns"), so local-alloc ranks it over
// FLT_MAX's %hi (2 over 2) and it takes v0, the %hi v1 (their widened lives touch); the first
// insn after a LOOP_BEG or LOOP_END is a barrier in sched1 and sched2, which keeps `lwc1` behind
// `sra`. All 60 placements of one `do { } while (0)` or one dead loop over the three statements
// were compiled: only the two with both `found` and `k` inside match. final.c aligns the first
// label after a LOOP_BEG: retail's are 0x130DD0 and 0x130E68, both 8-aligned without a nop.
// Not found: the plain source with these notes. The i loop cannot own them (its exit test's
// copy jumps past its LOOP_END to 0x130E50; a break with a body is "multiple entry points").
// w38-f5 (2026-11-12): this source (no `do { } while (0)`) is 6 differing lines with -mvu0-use-vf0-vf29, vf30 or vf31 (49 at vf27, 179 at the file's vf15): the range sets loop.c's threshold (64 + N), and at 93 or more the 2 and the 3 move and the 1 is rematerialised, as retail. The 6 lines are the block after the outer loop (lui/subu order, v0 and v1). func_001D9488 and func_0013AD80 give the same threshold, 94. This is the file's last function; func_00127B20 and func_0012CD78 of the same file stop matching by N = 22 and 26, so the file's row cannot change as it stands. docs/toolchain/loops.md, "A threshold of 94".
#include "common.h"

f32 ConvertDoubleToFloat(u64 v);
s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots);

// The earliest time from 0 on outside every window the given curves spend beyond their limits:
// for each (coefficients, scale) pair, the roots of four quadratics in the coefficients, kept
// as ordered windows; then the smallest of 0 and the windows' ends that no window covers.
void FindEarliestTimeWithinCurveLimits(s32 n, ...)
{
    f32 windows[40];
    f32* w = windows;
    char* ap = (char*)__builtin_next_arg(n) - 56;
    s32 i;
    s32 j;
    s32 found;

    for (i = 0; i < n; i++) {
        f32* c = *(f32**)((ap += 8) - 8);
        f32 t = ConvertDoubleToFloat(*(u64*)((ap += 8) - 8));
        for (j = 0; j < 4; j++) {
            switch (j) {
            case 0:
                found = SolveQuadratic(t, c[1] * 4.0f + c[3] * 2.0f, c[0] * 6.0f - c[2] * 6.0f, w);
                break;
            case 1:
                found = SolveQuadratic(-t, c[1] * 4.0f + c[3] * 2.0f, c[0] * 6.0f - c[2] * 6.0f, w);
                break;
            case 2:
                found = SolveQuadratic(t, c[1] * -2.0f - c[3] * 4.0f, c[0] * -6.0f + c[2] * 6.0f, w);
                break;
            case 3:
                found = SolveQuadratic(-t, c[1] * -2.0f - c[3] * 4.0f, c[0] * -6.0f + c[2] * 6.0f, w);
                break;
            }
            if (found == 2) {
                f32 a = w[0];
                f32 b = w[1];
                if (b < a) {
                    w[0] = b;
                    w[1] = a;
                }
                w += 2;
            }
        }
    }
    found = w - windows;
    f32 best = 3.4028234663852886e+38f;
    s32 k = -1;
next:
    if (k < found) {
        f32 x = k < 0 ? 0.0f : windows[k];
        k += 2;
        if (best < x)
            goto next;
        s32 m;
        for (m = 0; m < found; m += 2) {
            if (windows[m] + 1e-4f < x && x < windows[m + 1] - 1e-4f)
                goto next;
        }
        best = x;
        goto next;
    }
    **(f32**)((ap += 8) - 8) = best;
}
