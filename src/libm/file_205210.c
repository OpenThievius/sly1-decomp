/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The cosine of a float, reduced to the kernels. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 one = 1.0f;

s32 func_00207C88(f32 x, f32* y);
f32 func_002081A0(f32 x, f32 y);
f32 func_00208C48(s32 iy, f32 x, f32 y);

f32 func_00205210(f32 x)
{
    f32 y[2];
    s32 n;
    s32 ix;

    FLOAT_TO_BITS(ix, x);
    ix = ix & 0x7fffffff;

    if (ix <= 0x3F490FD8) {
        return func_002081A0(x, 0.0f);
    }
    if (ix > 0x7F7FFFFF) {
        return x - x;
    }
    n = func_00207C88(x, y);
    switch (n & 3) {
    case 0:
        return func_002081A0(y[0], y[1]);
    case 1:
        return -func_00208C48(1, y[0], y[1]);
    case 2:
        return -func_002081A0(y[0], y[1]);
    default:
        return func_00208C48(1, y[0], y[1]);
    }
}
