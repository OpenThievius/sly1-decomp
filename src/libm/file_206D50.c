/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The remainder of x / y for floats, with the sign of x (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one_f = 1.0f;
static const f32 signed_zeros[] = { 0.0f, -0.0f };

f32 func_00206D50(f32 x, f32 y)
{
    s32 x_bits, y_bits, sign, x_exp, y_exp, diff, probe;
    u32 shift;
    f32 product;

    FLOAT_TO_BITS(x_bits, x);
    FLOAT_TO_BITS(y_bits, y);
    sign = x_bits & 0x80000000;
    y_bits &= 0x7FFFFFFF;
    x_bits ^= sign;
    if (y_bits == 0 || x_bits > 0x7F7FFFFF || y_bits > 0x7F800000) {
        product = x * y;
        return product / product;
    }
    if (x_bits < y_bits) return x;
    if (x_bits == y_bits) return signed_zeros[(u32)sign >> 31];
    if (x_bits < 0x00800000) {
        x_exp = -126;
        for (probe = x_bits << 8; probe > 0; probe <<= 1) x_exp -= 1;
    } else {
        x_exp = (x_bits >> 23) - 127;
    }
    if (y_bits < 0x00800000) {
        y_exp = -126;
        for (probe = y_bits << 8; probe >= 0; probe <<= 1) y_exp -= 1;
    } else {
        y_exp = (y_bits >> 23) - 127;
    }
    if (x_exp >= -126) x_bits = (x_bits & 0x007FFFFF) | 0x00800000;
    else { shift = -126 - x_exp; x_bits = x_bits << shift; }
    if (y_exp >= -126) y_bits = (y_bits & 0x007FFFFF) | 0x00800000;
    else { shift = -126 - y_exp; y_bits = y_bits << shift; }
    shift = x_exp - y_exp;
    while (shift-- > 0) {
        diff = x_bits - y_bits;
        if (diff < 0) x_bits = x_bits + x_bits;
        else {
            if (diff == 0) return signed_zeros[(u32)sign >> 31];
            x_bits = diff + diff;
        }
    }
    diff = x_bits - y_bits;
    if (diff >= 0) x_bits = diff;
    if (x_bits == 0) return signed_zeros[(u32)sign >> 31];
    while (x_bits < 0x00800000) {
        x_bits = x_bits + x_bits;
        y_exp -= 1;
    }
    if (y_exp >= -126) {
        x_bits = (x_bits - 0x00800000) | ((y_exp + 127) << 23);
        BITS_TO_FLOAT(x, x_bits | sign);
    } else {
        shift = -126 - y_exp;
        x_bits = x_bits >> shift;
        BITS_TO_FLOAT(x, x_bits | sign);
    }
    return x;
}
