/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The absolute value of a float. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

f32 func_002052F8(f32 x)
{
    s32 hx;

    FLOAT_TO_BITS(hx, x);
    hx &= 0x7FFFFFFF;
    BITS_TO_FLOAT(x, hx);
    return x;
}
