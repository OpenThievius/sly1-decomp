/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A float times 2 to the power n. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 scale_up = 3.355443200e+07f;
static const f32 scale_down = 2.9802322388e-08f;
static const f32 huge = 1.0e30f;
static const f32 tiny = 1.0e-30f;

f32 func_002093C0(f32 x, f32 y);

f32 func_00209260(f32 x, s32 n)
{
    s32 ix, hx, k;

    FLOAT_TO_BITS(ix, x);
    hx = ix;
    k = (hx & 0x7F800000) >> 23;
    if (k == 0) {
        if ((hx & 0x7FFFFFFF) == 0) return x;
        x *= scale_up;
        FLOAT_TO_BITS(ix, x);
        hx = ix;
        k = ((hx & 0x7F800000) >> 23) - 25;
        if (n < -50000) return tiny * x;
    }
    if (k == 0xFF) return x + x;
    k = k + n;
    if (k > 0xFE) {
        return func_002093C0(huge, x) * huge;
    }
    if (k > 0) {
        BITS_TO_FLOAT(x, (hx & 0x807FFFFF) | (k << 23));
        return x;
    }
    if (k < -24) {
        if (n > 50000) return func_002093C0(huge, x) * huge;
        return func_002093C0(tiny, x) * tiny;
    }
    k += 25;
    BITS_TO_FLOAT(x, (hx & 0x807FFFFF) | (k << 23));
    return x * scale_down;
}
