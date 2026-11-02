// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 564/592 (95.3%), checked 2026-11-02
// NEAR: 25 lines differ, register numbering only (sx t2 vs t1, shift temp v0 vs a0, i v1 vs v0)
#include "float_bits.h"

extern f32 D_0024FA00[];

f32 func_00206D50(f32 x, f32 y) {
    s32 hx, hy;
    FLOAT_TO_BITS(hx, x);
    FLOAT_TO_BITS(hy, y);
    s32 sx = hx & 0x80000000;
    s32 ix, iy, i;
    u32 n;
    hy &= 0x7FFFFFFF;
    hx ^= sx;
    if (hy == 0 || hx > 0x7F7FFFFF || hy > 0x7F800000) {
        f32 t = x * y;
        return t / t;
    }
    if (hx < hy) return x;
    if (hx == hy) return D_0024FA00[(u32)sx >> 31];
    if (hx < 0x00800000) {
        ix = -126;
        for (i = hx << 8; i > 0; i <<= 1) ix -= 1;
    } else {
        ix = (hx >> 23) - 127;
    }
    if (hy < 0x00800000) {
        iy = -126;
        for (i = hy << 8; i >= 0; i <<= 1) iy -= 1;
    } else {
        iy = (hy >> 23) - 127;
    }
    if (ix >= -126) hx = (hx & 0x007FFFFF) | 0x00800000;
    else hx = hx << (-126 - ix);
    if (iy >= -126) hy = (hy & 0x007FFFFF) | 0x00800000;
    else hy = hy << (-126 - iy);
    n = ix - iy;
    while (n-- > 0) {
        i = hx - hy;
        if (i < 0) hx = hx + hx;
        else {
            if (i == 0) return D_0024FA00[(u32)sx >> 31];
            hx = i + i;
        }
    }
    i = hx - hy;
    if (i >= 0) hx = i;
    if (hx == 0) return D_0024FA00[(u32)sx >> 31];
    while (hx < 0x00800000) {
        hx = hx + hx;
        iy -= 1;
    }
    if (iy >= -126) hx = (hx - 0x00800000) | ((iy + 127) << 23);
    else hx = hx >> (-126 - iy);
    hx |= sx;
    f32 r;
    BITS_TO_FLOAT(r, hx);
    return r;
}
