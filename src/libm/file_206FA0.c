/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The natural logarithm of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 ln2_high = 6.9313812256e-01f;
static const f32 ln2_low = 9.0580006145e-06f;
static const f32 scale_up = 3.355443200e+07f;
static const f32 poly1 = 6.6666668653e-01f;
static const f32 poly2 = 4.0000000596e-01f;
static const f32 poly3 = 2.8571429849e-01f;
static const f32 poly4 = 2.2222198546e-01f;
static const f32 poly5 = 1.8183572590e-01f;
static const f32 poly6 = 1.5313838422e-01f;
static const f32 poly7 = 1.4798198640e-01f;
static const f32 zero = 0.0f;

f32 func_00206FA0(f32 x)
{
    s32 ix, i, j;
    s32 k = 0;
    f32 f, hfsq, s, z, R, w, t1, t2, dk;

    FLOAT_TO_BITS(ix, x);
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
    ix &= 0x007FFFFF;
    i = (ix + (0x95F64 << 3)) & 0x800000;
    BITS_TO_FLOAT(x, ix | (i ^ 0x3F800000));
    k += (i >> 23);
    f = x - 1.0f;
    if ((0x007FFFFF & (15 + ix)) < 16) {
        if (f == zero) {
            if (k == 0) {
                return zero;
            }
            dk = (f32)k;
            return dk * ln2_high + dk * ln2_low;
        }
        R = f * f * (0.5f - 0.33333333333333333f * f);
        if (k == 0) {
            return f - R;
        }
        dk = (f32)k;
        return dk * ln2_high - ((R - dk * ln2_low) - f);
    }
    s = f / (2.0f + f);
    dk = (f32)k;
    z = s * s;
    i = ix - (0x6147A << 3);
    w = z * z;
    j = (0x6B851 << 3) - ix;
    t1 = w * (poly2 + w * (poly4 + w * poly6));
    t2 = z * (poly1 + w * (poly3 + w * (poly5 + w * poly7)));
    i |= j;
    R = t2 + t1;
    if (i > 0) {
        hfsq = 0.5f * f * f;
        if (k == 0) {
            return f - (hfsq - s * (hfsq + R));
        }
        return dk * ln2_high - ((hfsq - (s * (hfsq + R) + dk * ln2_low)) - f);
    }
    if (k == 0) {
        return f - s * (f - R);
    }
    return dk * ln2_high - ((s * (f - R) - dk * ln2_low) - f);
}
