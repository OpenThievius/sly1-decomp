/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* Whether a float is finite. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
s32 func_00209210(f32 x)
{
    s32 ix;

    FLOAT_TO_BITS(ix, x);
    return (u32)((ix & 0x7FFFFFFF) + 0x80800000) >> 31;
}
