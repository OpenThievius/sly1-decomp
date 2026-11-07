/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The cosine kernel: cos(x + y) for a reduced float argument in two parts. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one = 1.0f;
static const f32 c1 = 4.1666667908e-02f;
static const f32 c2 = -1.3888889225e-03f;
static const f32 c3 = 2.4801587642e-05f;
static const f32 c4 = -2.7557314297e-07f;
static const f32 c5 = 2.0875723372e-09f;
static const f32 c6 = -1.1359647598e-11f;

f32 func_002081A0(f32 x, f32 y)
{
    s32 hx, ix;
    f32 z, r, v, qs;

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix <= 0x31FFFFFF && (s32)x == 0)
        return one;
    z = x * x;
    r = z * (z * (z * (z * (z * c6 + c5) + c4) + c3) + c2) + c1;
    v = z * r;
    if (ix <= 0x3E999999)
        return one - (0.5f * z - (z * v - x * y));
    if (ix > 0x3F480000)
        qs = 0.28125f;
    else
        BITS_TO_FLOAT(qs, ix - 0x01000000);
    return (one - qs) - ((0.5f * z - qs) - (z * v - x * y));
}
