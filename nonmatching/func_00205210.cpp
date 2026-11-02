// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 216/232 (93.1%), checked 2026-11-02
#include "common.h"

s32 func_00207C88(f32 x, f32* y);
f32 func_002081A0(f32 x, f32 y);
f32 func_00208C48(s32 iy, f32 x, f32 y);

f32 func_00205210(f32 x)
{
    f32 y[2];
    s32 n;
    s32 ix = *(s32*)&x;
    ix = ix & 0x7fffffff;

    if (ix <= 0x3F490FD8) {
        return func_002081A0(x, 0.0f);
    }
    if (ix > 0x7F7FFFFF) {
        return x - x;
    }
    n = func_00207C88(x, y);
    switch (n & 3) {
    case 0:
        return func_002081A0(y[0], y[1]);
    case 1:
        return -func_00208C48(1, y[0], y[1]);
    case 2:
        return -func_002081A0(y[0], y[1]);
    default:
        return func_00208C48(1, y[0], y[1]);
    }
}
