/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A float times 2 to the power n. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_scaleUp = 3.355443200e+07f;
static const f32 g_scaleDown = 2.9802322388e-08f;
static const f32 g_tenTo30 = 1.0e30f;
static const f32 g_tenToMinus30 = 1.0e-30f;

f32 func_002093C0(f32 x, f32 y);

f32 func_00209260(f32 x, s32 n)
{
    s32 rawBits, bits, exponent;

    FLOAT_TO_BITS(rawBits, x);
    bits = rawBits;
    exponent = (bits & 0x7F800000) >> 23;
    if (exponent == 0) {
        if ((bits & 0x7FFFFFFF) == 0) return x;
        x *= g_scaleUp;
        FLOAT_TO_BITS(rawBits, x);
        bits = rawBits;
        exponent = ((bits & 0x7F800000) >> 23) - 25;
        if (n < -50000) return g_tenToMinus30 * x;
    }
    if (exponent == 0xFF) return x + x;
    exponent = exponent + n;
    if (exponent > 0xFE) {
        return func_002093C0(g_tenTo30, x) * g_tenTo30;
    }
    if (exponent > 0) {
        BITS_TO_FLOAT(x, (bits & 0x807FFFFF) | (exponent << 23));
        return x;
    }
    if (exponent < -24) {
        if (n > 50000) return func_002093C0(g_tenTo30, x) * g_tenTo30;
        return func_002093C0(g_tenToMinus30, x) * g_tenToMinus30;
    }
    exponent += 25;
    BITS_TO_FLOAT(x, (bits & 0x807FFFFF) | (exponent << 23));
    return x * g_scaleDown;
}
