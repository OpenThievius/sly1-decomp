/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The cosine of a float, reduced to the kernels. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 g_one = 1.0f;

s32 func_00207C88(f32 x, f32* parts);
f32 func_002081A0(f32 x, f32 y);
f32 func_00208C48(s32 hasTail, f32 x, f32 y);

f32 func_00205210(f32 x)
{
    f32 parts[2];
    s32 quadrant;
    s32 magnitude;

    FLOAT_TO_BITS(magnitude, x);
    magnitude = magnitude & 0x7fffffff;

    if (magnitude <= 0x3F490FD8) {
        return CosineKernel(x, 0.0f);
    }
    if (magnitude > 0x7F7FFFFF) {
        return x - x;
    }
    quadrant = ReduceByHalfPi(x, parts);
    switch (quadrant & 3) {
    case 0:
        return CosineKernel(parts[0], parts[1]);
    case 1:
        return -SineKernel(1, parts[0], parts[1]);
    case 2:
        return -CosineKernel(parts[0], parts[1]);
    default:
        return SineKernel(1, parts[0], parts[1]);
    }
}
