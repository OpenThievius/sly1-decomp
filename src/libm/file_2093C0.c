/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A float with the magnitude of x and the sign of y. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
f32 func_002093C0(f32 x, f32 y)
{
    s32 x_bits, y_bits;

    FLOAT_TO_BITS(x_bits, x);
    FLOAT_TO_BITS(y_bits, y);
    BITS_TO_FLOAT(x, (x_bits & 0x7FFFFFFF) | (y_bits & 0x80000000));
    return x;
}
