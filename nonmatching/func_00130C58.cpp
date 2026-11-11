// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 736/748, checked 2026-11-11
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
