/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The remainder of x / y for floats, with the sign of x (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_one = 1.0f;
static const f32 g_signedZeros[] = { 0.0f, -0.0f };

f32 FloatRemainderKernel(f32 x, f32 y)
{
    s32 xBits, yBits, sign, xExp, yExp, diff, probe;
    u32 shift;
    f32 product;

    FLOAT_TO_BITS(xBits, x);
    FLOAT_TO_BITS(yBits, y);
    sign = xBits & 0x80000000;
    yBits &= 0x7FFFFFFF;
    xBits ^= sign;
    if (yBits == 0 || xBits > 0x7F7FFFFF || yBits > 0x7F800000) {
        product = x * y;
        return product / product;
    }
    if (xBits < yBits) return x;
    if (xBits == yBits) return g_signedZeros[(u32)sign >> 31];
    if (xBits < 0x00800000) {
        xExp = -126;
        for (probe = xBits << 8; probe > 0; probe <<= 1) xExp -= 1;
    } else {
        xExp = (xBits >> 23) - 127;
    }
    if (yBits < 0x00800000) {
        yExp = -126;
        for (probe = yBits << 8; probe >= 0; probe <<= 1) yExp -= 1;
    } else {
        yExp = (yBits >> 23) - 127;
    }
    if (xExp >= -126) xBits = (xBits & 0x007FFFFF) | 0x00800000;
    else { shift = -126 - xExp; xBits = xBits << shift; }
    if (yExp >= -126) yBits = (yBits & 0x007FFFFF) | 0x00800000;
    else { shift = -126 - yExp; yBits = yBits << shift; }
    shift = xExp - yExp;
    while (shift-- > 0) {
        diff = xBits - yBits;
        if (diff < 0) xBits = xBits + xBits;
        else {
            if (diff == 0) return g_signedZeros[(u32)sign >> 31];
            xBits = diff + diff;
        }
    }
    diff = xBits - yBits;
    if (diff >= 0) xBits = diff;
    if (xBits == 0) return g_signedZeros[(u32)sign >> 31];
    while (xBits < 0x00800000) {
        xBits = xBits + xBits;
        yExp -= 1;
    }
    if (yExp >= -126) {
        xBits = (xBits - 0x00800000) | ((yExp + 127) << 23);
        BITS_TO_FLOAT(x, xBits | sign);
    } else {
        shift = -126 - yExp;
        xBits = xBits >> shift;
        BITS_TO_FLOAT(x, xBits | sign);
    }
    return x;
}
