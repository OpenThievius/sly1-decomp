/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The base-10 logarithm of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_scaleUp = 3.3554432000e+07f;
static const f32 g_invLn10 = 4.3429449201e-01f;
static const f32 g_log10Of2Head = 3.0102920532e-01f;
static const f32 g_log10Of2Tail = 7.9034151668e-07f;
static const f32 g_zero = 0.0f;

f32 LogarithmKernel(f32 x);

f32 LogarithmBase10Kernel(f32 x)
{
    s32 bits, exponent, neg;
    f32 exponentF;

    FLOAT_TO_BITS(bits, x);
    exponent = 0;
    if (bits < 0x00800000) {
        if ((bits & 0x7FFFFFFF) == 0) {
            return -g_scaleUp / g_zero;
        }
        if (bits < 0) {
            return (x - x) / g_zero;
        }
        exponent -= 25;
        x *= g_scaleUp;
        FLOAT_TO_BITS(bits, x);
    }
    if (bits >= 0x7F800000) {
        return x + x;
    }
    exponent += (bits >> 23) - 127;
    neg = (u32)exponent >> 31;
    bits = (bits & 0x007FFFFF) | ((127 - neg) << 23);
    exponentF = (f32)(exponent + neg);
    BITS_TO_FLOAT(x, bits);
    return (exponentF * g_log10Of2Tail + LogarithmKernel(x) * g_invLn10) + exponentF * g_log10Of2Head;
}
