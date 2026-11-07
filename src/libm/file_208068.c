/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The square root of a float, bit by bit (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_one = 1.0f;
static const f32 g_tenToMinus30 = 1.0e-30f;

f32 func_00208068(f32 x)
{
    s32 bits, exponent, i, twiceRoot, root, trial, bit;
    f32 result;

    FLOAT_TO_BITS(bits, x);
    if ((bits & 0x7F800000) == 0x7F800000)
        return x * x + x;
    if (bits <= 0) {
        if ((bits & 0x7FFFFFFF) == 0)
            return x;
        if (bits < 0)
            return (x - x) / (x - x);
    }
    exponent = bits >> 23;
    if (exponent == 0) {
        for (i = 0; (bits & 0x800000) == 0; i++)
            bits <<= 1;
        exponent -= i - 1;
    }
    exponent -= 127;
    bits = (bits & 0x7FFFFF) | 0x800000;
    bits <<= exponent & 1;
    bits <<= 1;
    exponent >>= 1;
    twiceRoot = 0;
    root = 0;
    bit = 0x1000000;
    while (bit != 0) {
        trial = twiceRoot + bit;
        if (trial <= bits) {
            twiceRoot = trial + bit;
            bits -= trial;
            root += bit;
        }
        bits <<= 1;
        bit = (u32)bit >> 1;
    }
    if (bits != 0)
        root += root & 1;
    bits = (root >> 1) + 0x3F000000;
    BITS_TO_FLOAT(result, bits + (exponent << 23));
    return result;
}
