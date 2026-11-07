/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The square root of a float, bit by bit (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one = 1.0f;
static const f32 tiny = 1.0e-30f;

f32 func_00208068(f32 x)
{
    s32 hx, ix, i, s, r, t, m;
    f32 res;

    FLOAT_TO_BITS(hx, x);
    if ((hx & 0x7F800000) == 0x7F800000)
        return x * x + x;
    if (hx <= 0) {
        if ((hx & 0x7FFFFFFF) == 0)
            return x;
        if (hx < 0)
            return (x - x) / (x - x);
    }
    ix = hx >> 23;
    if (ix == 0) {
        for (i = 0; (hx & 0x800000) == 0; i++)
            hx <<= 1;
        ix -= i - 1;
    }
    ix -= 127;
    hx = (hx & 0x7FFFFF) | 0x800000;
    hx <<= ix & 1;
    hx <<= 1;
    ix >>= 1;
    s = 0;
    r = 0;
    m = 0x1000000;
    while (m != 0) {
        t = s + m;
        if (t <= hx) {
            s = t + m;
            hx -= t;
            r += m;
        }
        hx <<= 1;
        m = (u32)m >> 1;
    }
    if (hx != 0)
        r += r & 1;
    hx = (r >> 1) + 0x3F000000;
    BITS_TO_FLOAT(res, hx + (ix << 23));
    return res;
}
