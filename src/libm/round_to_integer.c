/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A double rounded to an integer in the current rounding direction, with software double arithmetic. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const double g_roundBias[] = { 4.50359962737049600000e+15, -4.50359962737049600000e+15 };

double RoundToInteger(double x)
{
    s32 high, low, exponent, sign;
    u32 mask;
    double biased, rounded;

    DOUBLE_TO_WORDS(high, low, x);
    sign = (u32)high >> 31;
    exponent = ((high >> 20) & 0x7FF) - 0x3FF;
    if (exponent < 20) {
        if (exponent < 0) {
            if (((high & 0x7FFFFFFF) | low) == 0) return x;
            low |= high & 0xFFFFF;
            high &= 0xFFFE0000;
            high |= ((u32)(low | -low) >> 12) & 0x80000;
            SET_DOUBLE_HIGH(x, high);
            biased = g_roundBias[sign] + x;
            rounded = biased - g_roundBias[sign];
            DOUBLE_HIGH(high, rounded);
            SET_DOUBLE_HIGH(rounded, (high & 0x7FFFFFFF) | (sign << 31));
            return rounded;
        }
        mask = 0xFFFFF >> exponent;
        if (((high & mask) | low) == 0) return x;
        mask >>= 1;
        if (((high & mask) | low) != 0) {
            if (exponent == 19) low = 0x40000000;
            else high = (high & ~mask) | (0x20000 >> exponent);
        }
    } else if (exponent >= 52) {
        if (exponent == 0x400) return x + x;
        return x;
    } else {
        mask = 0xFFFFFFFFu >> (exponent - 20);
        if ((low & mask) == 0) return x;
        mask >>= 1;
        if ((low & mask) != 0) low = (low & ~mask) | (0x40000000 >> (exponent - 20));
    }
    WORDS_TO_DOUBLE(x, high, low);
    biased = g_roundBias[sign] + x;
    return biased - g_roundBias[sign];
}
