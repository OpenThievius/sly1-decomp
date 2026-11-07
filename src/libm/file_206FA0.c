/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The natural logarithm of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 ln2_head = 6.9313812256e-01f;
static const f32 ln2_tail = 9.0580006145e-06f;
static const f32 scale_up = 3.355443200e+07f;
static const f32 log_s2 = 6.6666668653e-01f;
static const f32 log_s4 = 4.0000000596e-01f;
static const f32 log_s6 = 2.8571429849e-01f;
static const f32 log_s8 = 2.2222198546e-01f;
static const f32 log_s10 = 1.8183572590e-01f;
static const f32 log_s12 = 1.5313838422e-01f;
static const f32 log_s14 = 1.4798198640e-01f;
static const f32 zero_f = 0.0f;

f32 func_00206FA0(f32 x)
{
    s32 bits, flag, flag_high;
    s32 exponent = 0;
    f32 frac, half_frac2, ratio, ratio2, poly, ratio4, even_terms, odd_terms, exponent_f;

    FLOAT_TO_BITS(bits, x);
    if (bits < 0x00800000) {
        if ((bits & 0x7FFFFFFF) == 0) {
            return -scale_up / zero_f;
        }
        if (bits < 0) {
            return (x - x) / zero_f;
        }
        exponent -= 25;
        x *= scale_up;
        FLOAT_TO_BITS(bits, x);
    }
    if (bits >= 0x7F800000) {
        return x + x;
    }
    exponent += (bits >> 23) - 127;
    bits &= 0x007FFFFF;
    flag = (bits + (0x95F64 << 3)) & 0x800000;
    BITS_TO_FLOAT(x, bits | (flag ^ 0x3F800000));
    exponent += (flag >> 23);
    frac = x - 1.0f;
    if ((0x007FFFFF & (15 + bits)) < 16) {
        if (frac == zero_f) {
            if (exponent == 0) {
                return zero_f;
            }
            exponent_f = (f32)exponent;
            return exponent_f * ln2_head + exponent_f * ln2_tail;
        }
        poly = frac * frac * (0.5f - 0.33333333333333333f * frac);
        if (exponent == 0) {
            return frac - poly;
        }
        exponent_f = (f32)exponent;
        return exponent_f * ln2_head - ((poly - exponent_f * ln2_tail) - frac);
    }
    ratio = frac / (2.0f + frac);
    exponent_f = (f32)exponent;
    ratio2 = ratio * ratio;
    flag = bits - (0x6147A << 3);
    ratio4 = ratio2 * ratio2;
    flag_high = (0x6B851 << 3) - bits;
    even_terms = ratio4 * (log_s4 + ratio4 * (log_s8 + ratio4 * log_s12));
    odd_terms = ratio2 * (log_s2 + ratio4 * (log_s6 + ratio4 * (log_s10 + ratio4 * log_s14)));
    flag |= flag_high;
    poly = odd_terms + even_terms;
    if (flag > 0) {
        half_frac2 = 0.5f * frac * frac;
        if (exponent == 0) {
            return frac - (half_frac2 - ratio * (half_frac2 + poly));
        }
        return exponent_f * ln2_head - ((half_frac2 - (ratio * (half_frac2 + poly) + exponent_f * ln2_tail)) - frac);
    }
    if (exponent == 0) {
        return frac - ratio * (frac - poly);
    }
    return exponent_f * ln2_head - ((ratio * (frac - poly) - exponent_f * ln2_tail) - frac);
}
