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
#include "common.h"

f32 ConvertDoubleToFloat(u64 v);
s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots);

// The earliest time from 0 on outside every window the given curves spend beyond their limits:
// for each (coefficients, scale) pair, the roots of four quadratics in the coefficients, kept
// as ordered windows; then the smallest of 0 and the windows' ends that no window covers.
void FindEarliestCubicBoundTime(s32 n, ...)
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
