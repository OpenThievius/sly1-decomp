/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The sine kernel: sin(x + y) for a reduced float argument in two parts. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_half = 0.5f;
static const f32 g_sinX3 = -1.6666667163e-01f;
static const f32 g_sinX5 = 8.3333337680e-03f;
static const f32 g_sinX7 = -1.9841270114e-04f;
static const f32 g_sinX9 = 2.7557314297e-06f;
static const f32 g_sinX11 = -2.5050759689e-08f;
static const f32 g_sinX13 = 1.5896910177e-10f;

f32 func_00208C48(s32 hasTail, f32 x, f32 y)
{
    s32 bits, magnitude;
    f32 x2, x3, poly;

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude <= 0x31FFFFFF && (s32)x == 0)
        return x;
    x2 = x * x;
    x3 = x2 * x;
    poly = x2 * (x2 * (x2 * (x2 * g_sinX13 + g_sinX11) + g_sinX9) + g_sinX7) + g_sinX5;
    if (hasTail == 0)
        return x + x3 * (x2 * poly + g_sinX3);
    return x - ((x2 * (y * g_half - x3 * poly) - y) - x3 * g_sinX3);
}
