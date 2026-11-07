/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The tangent of a float, reduced to its kernel. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

s32 func_00207C88(f32 x, f32* parts);
f32 func_00208D50(f32 x, f32 y, s32 sign);

f32 func_002054F0(f32 x)
{
    f32 parts[2];
    s32 magnitude;
    s32 quadrant;

    FLOAT_TO_BITS(magnitude, x);
    magnitude &= 0x7FFFFFFF;
    if (magnitude <= 0x3F490FDA) {
        return func_00208D50(x, 0.0f, 1);
    }
    if (magnitude > 0x7F7FFFFF) {
        return x - x;
    }
    quadrant = func_00207C88(x, parts);
    return func_00208D50(parts[0], parts[1], 1 - ((quadrant & 1) << 1));
}
