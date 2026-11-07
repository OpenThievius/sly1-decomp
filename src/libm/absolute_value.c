/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The absolute value of a float. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

f32 AbsoluteValue(f32 x)
{
    s32 bits;

    FLOAT_TO_BITS(bits, x);
    bits &= 0x7FFFFFFF;
    BITS_TO_FLOAT(x, bits);
    return x;
}
