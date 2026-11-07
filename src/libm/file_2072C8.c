/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The base-10 logarithm of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 scale_up = 3.3554432000e+07f;
static const f32 inv_ln10 = 4.3429449201e-01f;
static const f32 log10_2_high = 3.0102920532e-01f;
static const f32 log10_2_low = 7.9034151668e-07f;
static const f32 zero = 0.0f;

f32 func_00206FA0(f32 x);

f32 func_002072C8(f32 x)
{
    s32 ix, k, neg;
    f32 dk;

    FLOAT_TO_BITS(ix, x);
    k = 0;
    if (ix < 0x00800000) {
        if ((ix & 0x7FFFFFFF) == 0) {
            return -scale_up / zero;
        }
        if (ix < 0) {
            return (x - x) / zero;
        }
        k -= 25;
        x *= scale_up;
        FLOAT_TO_BITS(ix, x);
    }
    if (ix >= 0x7F800000) {
        return x + x;
    }
    k += (ix >> 23) - 127;
    neg = (u32)k >> 31;
    ix = (ix & 0x007FFFFF) | ((127 - neg) << 23);
    dk = (f32)(k + neg);
    BITS_TO_FLOAT(x, ix);
    return (dk * log10_2_low + func_00206FA0(x) * inv_ln10) + dk * log10_2_high;
}
