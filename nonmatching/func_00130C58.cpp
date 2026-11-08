// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 744/748, checked 2026-11-08
// NEAR (src/main/placed_object.cpp, where it is INCLUDE_ASM with INCLUDE_RODATA(D_00249C90)):
// all but one register: retail keeps the switch's constant 3 in s8 (loop.c moved it out of
// the inner loop, so s8 is saved too: 16 bytes more), ours loads it in the loop (li v0,3 in
// the case-2 branch's slot, where retail has a beql with the lwc1). The loop dump (-dL) gives
// the inner loop 104 insns: the 1 and the 3 each have life 1 and are "not desirable", the 2
// (also found's test) is moved; retail moved the 3 but not the 1. Matched on the way: the final
// search as a goto loop (retail's has its test at the top and no strength reduction: loop.c
// never sees it), the window count in found's register, the va slots read as words.
// Tried for the 3: the case order, j <= 3.
#include "common.h"

f32 func_001FD578(u64 v);
s32 SolveQuadratic(f32* roots, f32 a, f32 b, f32 c);

// The earliest time from 0 on outside every window the given curves spend beyond their limits:
// for each (coefficients, scale) pair, the roots of four quadratics in the coefficients, kept
// as ordered windows; then the smallest of 0 and the windows' ends that no window covers.
void func_00130C58(s32 n, ...)
{
    f32 windows[40];
    f32* w = windows;
    char* ap = (char*)__builtin_next_arg(n) - 56;
    s32 i;
    s32 j;
    s32 found;

    for (i = 0; i < n; i++) {
        f32* c = *(f32**)((ap += 8) - 8);
        f32 t = func_001FD578(*(u64*)((ap += 8) - 8));
        for (j = 0; j < 4; j++) {
            switch (j) {
            case 0:
                found = SolveQuadratic(w, t, c[1] * 4.0f + c[3] * 2.0f, c[0] * 6.0f - c[2] * 6.0f);
                break;
            case 1:
                found = SolveQuadratic(w, -t, c[1] * 4.0f + c[3] * 2.0f, c[0] * 6.0f - c[2] * 6.0f);
                break;
            case 2:
                found = SolveQuadratic(w, t, c[1] * -2.0f - c[3] * 4.0f, c[0] * -6.0f + c[2] * 6.0f);
                break;
            case 3:
                found = SolveQuadratic(w, -t, c[1] * -2.0f - c[3] * 4.0f, c[0] * -6.0f + c[2] * 6.0f);
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
