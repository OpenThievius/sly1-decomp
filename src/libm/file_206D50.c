/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The remainder of x / y for floats, with the sign of x (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one = 1.0f;
static const f32 zero[] = { 0.0f, -0.0f };

f32 func_00206D50(f32 x, f32 y)
{
    s32 hx, hy, sx, ix, iy, i, j;
    u32 n;
    f32 t;

    FLOAT_TO_BITS(hx, x);
    FLOAT_TO_BITS(hy, y);
    sx = hx & 0x80000000;
    hy &= 0x7FFFFFFF;
    hx ^= sx;
    if (hy == 0 || hx > 0x7F7FFFFF || hy > 0x7F800000) {
        t = x * y;
        return t / t;
    }
    if (hx < hy) return x;
    if (hx == hy) return zero[(u32)sx >> 31];
    if (hx < 0x00800000) {
        ix = -126;
        for (j = hx << 8; j > 0; j <<= 1) ix -= 1;
    } else {
        ix = (hx >> 23) - 127;
    }
    if (hy < 0x00800000) {
        iy = -126;
        for (j = hy << 8; j >= 0; j <<= 1) iy -= 1;
    } else {
        iy = (hy >> 23) - 127;
    }
    if (ix >= -126) hx = (hx & 0x007FFFFF) | 0x00800000;
    else { n = -126 - ix; hx = hx << n; }
    if (iy >= -126) hy = (hy & 0x007FFFFF) | 0x00800000;
    else { n = -126 - iy; hy = hy << n; }
    n = ix - iy;
    while (n-- > 0) {
        i = hx - hy;
        if (i < 0) hx = hx + hx;
        else {
            if (i == 0) return zero[(u32)sx >> 31];
            hx = i + i;
        }
    }
    i = hx - hy;
    if (i >= 0) hx = i;
    if (hx == 0) return zero[(u32)sx >> 31];
    while (hx < 0x00800000) {
        hx = hx + hx;
        iy -= 1;
    }
    if (iy >= -126) {
        hx = (hx - 0x00800000) | ((iy + 127) << 23);
        BITS_TO_FLOAT(x, hx | sx);
    } else {
        n = -126 - iy;
        hx = hx >> n;
        BITS_TO_FLOAT(x, hx | sx);
    }
    return x;
}
