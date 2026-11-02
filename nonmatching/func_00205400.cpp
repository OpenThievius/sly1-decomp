// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 224/240 (93.3%), checked 2026-11-02
#include "common.h"
// NEAR: body and branches match; the only differences are the prologue scheduling (lui/ori before addiu sp) and the $ra saves (sq/lq here, sd/ld in retail: the lib region is 2.9-ee-991111's, config/us/layout.tsv), so it does not match with the default compiler.

s32 func_00207C88(f32 x, f32* y);
f32 func_002081A0(f32 x, f32 y);
f32 func_00208C48(s32 iy, f32 x, f32 y);

f32 func_00205400(f32 x)
{
    s32 ix = *(s32*)&x;
    ix &= 0x7fffffff;
    f32 y[2];
    s32 n;

    if (ix <= 0x3F490FD8) {
        return func_00208C48(0, x, 0.0f);
    }
    if (ix > 0x7F7FFFFF) {
        return x - x;
    }
    n = func_00207C88(x, y);
    switch (n & 3) {
    case 0:
        return func_00208C48(1, y[0], y[1]);
    case 1:
        return func_002081A0(y[0], y[1]);
    case 2:
        return -func_00208C48(1, y[0], y[1]);
    default:
        return -func_002081A0(y[0], y[1]);
    }
}
