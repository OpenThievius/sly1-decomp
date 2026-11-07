/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The sine kernel: sin(x + y) for a reduced float argument in two parts. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 half = 0.5f;
static const f32 s1 = -1.6666667163e-01f;
static const f32 s2 = 8.3333337680e-03f;
static const f32 s3 = -1.9841270114e-04f;
static const f32 s4 = 2.7557314297e-06f;
static const f32 s5 = -2.5050759689e-08f;
static const f32 s6 = 1.5896910177e-10f;

f32 func_00208C48(s32 iy, f32 x, f32 y)
{
    s32 hx, ix;
    f32 z, v, r;

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix <= 0x31FFFFFF && (s32)x == 0)
        return x;
    z = x * x;
    v = z * x;
    r = z * (z * (z * (z * s6 + s5) + s4) + s3) + s2;
    if (iy == 0)
        return x + v * (z * r + s1);
    return x - ((z * (y * half - v * r) - y) - v * s1);
}
