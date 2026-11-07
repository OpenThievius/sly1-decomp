/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The tangent of a float, reduced to its kernel. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

s32 func_00207C88(f32 x, f32* y);
f32 func_00208D50(f32 x, f32 y, s32 k);

f32 func_002054F0(f32 x)
{
    f32 y[2];
    s32 ix;
    s32 n;

    FLOAT_TO_BITS(ix, x);
    ix &= 0x7FFFFFFF;
    if (ix <= 0x3F490FDA) {
        return func_00208D50(x, 0.0f, 1);
    }
    if (ix > 0x7F7FFFFF) {
        return x - x;
    }
    n = func_00207C88(x, y);
    return func_00208D50(y[0], y[1], 1 - ((n & 1) << 1));
}
