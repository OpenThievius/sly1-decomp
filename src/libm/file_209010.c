/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A double rounded to an integer in the current rounding direction, with software double arithmetic. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const double round_bias[] = { 4.50359962737049600000e+15, -4.50359962737049600000e+15 };

double func_00209010(double x)
{
    s32 i0, i1, j0, sx;
    u32 i;
    double w, t;

    DOUBLE_TO_WORDS(i0, i1, x);
    sx = (u32)i0 >> 31;
    j0 = ((i0 >> 20) & 0x7FF) - 0x3FF;
    if (j0 < 20) {
        if (j0 < 0) {
            if (((i0 & 0x7FFFFFFF) | i1) == 0) return x;
            i1 |= i0 & 0xFFFFF;
            i0 &= 0xFFFE0000;
            i0 |= ((u32)(i1 | -i1) >> 12) & 0x80000;
            SET_DOUBLE_HIGH(x, i0);
            w = round_bias[sx] + x;
            t = w - round_bias[sx];
            DOUBLE_HIGH(i0, t);
            SET_DOUBLE_HIGH(t, (i0 & 0x7FFFFFFF) | (sx << 31));
            return t;
        }
        i = 0xFFFFF >> j0;
        if (((i0 & i) | i1) == 0) return x;
        i >>= 1;
        if (((i0 & i) | i1) != 0) {
            if (j0 == 19) i1 = 0x40000000;
            else i0 = (i0 & ~i) | (0x20000 >> j0);
        }
    } else if (j0 >= 52) {
        if (j0 == 0x400) return x + x;
        return x;
    } else {
        i = 0xFFFFFFFFu >> (j0 - 20);
        if ((i1 & i) == 0) return x;
        i >>= 1;
        if ((i1 & i) != 0) i1 = (i1 & ~i) | (0x40000000 >> (j0 - 20));
    }
    WORDS_TO_DOUBLE(x, i0, i1);
    w = round_bias[sx] + x;
    return w - round_bias[sx];
}
