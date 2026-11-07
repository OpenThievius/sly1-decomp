/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The cosine kernel: cos(x + y) for a reduced float argument in two parts. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one_f = 1.0f;
static const f32 cos_x4 = 4.1666667908e-02f;
static const f32 cos_x6 = -1.3888889225e-03f;
static const f32 cos_x8 = 2.4801587642e-05f;
static const f32 cos_x10 = -2.7557314297e-07f;
static const f32 cos_x12 = 2.0875723372e-09f;
static const f32 cos_x14 = -1.1359647598e-11f;

f32 func_002081A0(f32 x, f32 y)
{
    s32 bits, magnitude;
    f32 x2, poly, x2_poly, quarter;

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude <= 0x31FFFFFF && (s32)x == 0)
        return one_f;
    x2 = x * x;
    poly = x2 * (x2 * (x2 * (x2 * (x2 * cos_x14 + cos_x12) + cos_x10) + cos_x8) + cos_x6) + cos_x4;
    x2_poly = x2 * poly;
    if (magnitude <= 0x3E999999)
        return one_f - (0.5f * x2 - (x2 * x2_poly - x * y));
    if (magnitude > 0x3F480000)
        quarter = 0.28125f;
    else
        BITS_TO_FLOAT(quarter, magnitude - 0x01000000);
    return (one_f - quarter) - ((0.5f * x2 - quarter) - (x2 * x2_poly - x * y));
}
