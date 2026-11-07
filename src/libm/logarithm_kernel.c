/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The natural logarithm of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_ln2Head = 6.9313812256e-01f;
static const f32 g_ln2Tail = 9.0580006145e-06f;
static const f32 g_scaleUp = 3.355443200e+07f;
static const f32 g_logS2 = 6.6666668653e-01f;
static const f32 g_logS4 = 4.0000000596e-01f;
static const f32 g_logS6 = 2.8571429849e-01f;
static const f32 g_logS8 = 2.2222198546e-01f;
static const f32 g_logS10 = 1.8183572590e-01f;
static const f32 g_logS12 = 1.5313838422e-01f;
static const f32 g_logS14 = 1.4798198640e-01f;
static const f32 g_zero = 0.0f;

f32 LogarithmKernel(f32 x)
{
    s32 bits, flag, flagHigh;
    s32 exponent = 0;
    f32 frac, halfFrac2, ratio, ratio2, poly, ratio4, evenTerms, oddTerms, exponentF;

    FLOAT_TO_BITS(bits, x);
    if (bits < 0x00800000) {
        if ((bits & 0x7FFFFFFF) == 0) {
            return -g_scaleUp / g_zero;
        }
        if (bits < 0) {
            return (x - x) / g_zero;
        }
        exponent -= 25;
        x *= g_scaleUp;
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
        if (frac == g_zero) {
            if (exponent == 0) {
                return g_zero;
            }
            exponentF = (f32)exponent;
            return exponentF * g_ln2Head + exponentF * g_ln2Tail;
        }
        poly = frac * frac * (0.5f - 0.33333333333333333f * frac);
        if (exponent == 0) {
            return frac - poly;
        }
        exponentF = (f32)exponent;
        return exponentF * g_ln2Head - ((poly - exponentF * g_ln2Tail) - frac);
    }
    ratio = frac / (2.0f + frac);
    exponentF = (f32)exponent;
    ratio2 = ratio * ratio;
    flag = bits - (0x6147A << 3);
    ratio4 = ratio2 * ratio2;
    flagHigh = (0x6B851 << 3) - bits;
    evenTerms = ratio4 * (g_logS4 + ratio4 * (g_logS8 + ratio4 * g_logS12));
    oddTerms = ratio2 * (g_logS2 + ratio4 * (g_logS6 + ratio4 * (g_logS10 + ratio4 * g_logS14)));
    flag |= flagHigh;
    poly = oddTerms + evenTerms;
    if (flag > 0) {
        halfFrac2 = 0.5f * frac * frac;
        if (exponent == 0) {
            return frac - (halfFrac2 - ratio * (halfFrac2 + poly));
        }
        return exponentF * g_ln2Head - ((halfFrac2 - (ratio * (halfFrac2 + poly) + exponentF * g_ln2Tail)) - frac);
    }
    if (exponent == 0) {
        return frac - ratio * (frac - poly);
    }
    return exponentF * g_ln2Head - ((ratio * (frac - poly) - exponentF * g_ln2Tail) - frac);
}
