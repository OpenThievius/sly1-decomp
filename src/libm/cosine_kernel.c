/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The cosine kernel: cos(x + y) for a reduced float argument in two parts. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_one = 1.0f;
static const f32 g_cosX4 = 4.1666667908e-02f;
static const f32 g_cosX6 = -1.3888889225e-03f;
static const f32 g_cosX8 = 2.4801587642e-05f;
static const f32 g_cosX10 = -2.7557314297e-07f;
static const f32 g_cosX12 = 2.0875723372e-09f;
static const f32 g_cosX14 = -1.1359647598e-11f;

f32 CosineKernel(f32 x, f32 y)
{
    s32 bits, magnitude;
    f32 x2, poly, x2Poly, quarter;

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude <= 0x31FFFFFF && (s32)x == 0)
        return g_one;
    x2 = x * x;
    poly = x2 * (x2 * (x2 * (x2 * (x2 * g_cosX14 + g_cosX12) + g_cosX10) + g_cosX8) + g_cosX6) + g_cosX4;
    x2Poly = x2 * poly;
    if (magnitude <= 0x3E999999)
        return g_one - (0.5f * x2 - (x2 * x2Poly - x * y));
    if (magnitude > 0x3F480000)
        quarter = 0.28125f;
    else
        BITS_TO_FLOAT(quarter, magnitude - 0x01000000);
    return (g_one - quarter) - ((0.5f * x2 - quarter) - (x2 * x2Poly - x * y));
}
