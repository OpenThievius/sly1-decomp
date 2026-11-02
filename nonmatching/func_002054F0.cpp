// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 120/136 (88.2%), checked 2026-11-02
#include "common.h"
// NEAR: the whole body matches; retail schedules the frame push ahead of the abs-bits moves (the lui/ori of 0x7FFFFFFF and the move of the bits), which this compiler keeps in another order.

struct Red_2054F0 { f32 f0; f32 f4; };
s32 func_00207C88(struct Red_2054F0* p);
f32 func_00208D50(f32 x, f32 y, s32 q);

f32 func_002054F0(f32 x)
{
    struct Red_2054F0 buf;
    s32 bits;
    f32 y;
    s32 q;
    s32 n;

    bits = *(s32*)&x;
    bits &= 0x7FFFFFFF;
    if (0x3F490FDA >= bits) {
        y = 0.0f;
        q = 1;
    } else {
        if (bits > 0x7F7FFFFF) return x - x;
        n = func_00207C88(&buf);
        x = buf.f0;
        y = buf.f4;
        q = 1;
        q -= (n & 1) << 1;
    }
    return func_00208D50(x, y, q);
}
