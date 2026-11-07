/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arcsine of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_one = 1.0f;
static const f32 g_tenTo30 = 1.0e30f;
static const f32 g_halfPiHead = 1.5707962513e+00f;
static const f32 g_halfPiTail = 7.5497894159e-08f;
static const f32 g_quarterPiHead = 7.8539818525e-01f;
static const f32 g_numT1 = 1.6666667163e-01f;
static const f32 g_numT2 = -3.2556581497e-01f;
static const f32 g_numT3 = 2.0121252537e-01f;
static const f32 g_numT4 = -4.0055535734e-02f;
static const f32 g_numT5 = 7.9153501429e-04f;
static const f32 g_numT6 = 3.4793309169e-05f;
static const f32 g_denT1 = -2.4033949375e+00f;
static const f32 g_denT2 = 2.0209457874e+00f;
static const f32 g_denT3 = -6.8828397989e-01f;
static const f32 g_denT4 = 7.7038154006e-02f;

f32 AbsoluteValue(f32 x);
f32 SquareRootKernel(f32 x);

f32 ArcsineKernel(f32 x)
{
    s32 bits, magnitude, rootBits;
    f32 arg, scratch, num, den, root, ratio, tail;

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude == 0x3F800000) {
        return x * g_halfPiHead + x * g_halfPiTail;
    }
    if (magnitude > 0x3F800000) {
        return (x - x) / (x - x);
    }
    if (magnitude < 0x3F000000) {
        if (magnitude < 0x32000000) {
            if (g_tenTo30 + x > g_one) {
                return x;
            }
        } else {
            arg = x * x;
        }
        num = arg * (g_numT1 + arg * (g_numT2 + arg * (g_numT3 + arg * (g_numT4 + arg * (g_numT5 + arg * g_numT6)))));
        den = g_one + arg * (g_denT1 + arg * (g_denT2 + arg * (g_denT3 + arg * g_denT4)));
        scratch = num / den;
        return x + x * scratch;
    }
    scratch = g_one - AbsoluteValue(x);
    arg = scratch * 0.5f;
    num = arg * (g_numT1 + arg * (g_numT2 + arg * (g_numT3 + arg * (g_numT4 + arg * (g_numT5 + arg * g_numT6)))));
    den = g_one + arg * (g_denT1 + arg * (g_denT2 + arg * (g_denT3 + arg * g_denT4)));
    root = SquareRootKernel(arg);
    if (magnitude >= 0x3F79999A) {
        scratch = num / den;
        arg = g_halfPiHead - (2.0f * (root + root * scratch) - g_halfPiTail);
    } else {
        FLOAT_TO_BITS(rootBits, root);
        rootBits &= 0xFFFFF000;
        BITS_TO_FLOAT(scratch, rootBits);
        tail = (arg - scratch * scratch) / (root + scratch);
        ratio = num / den;
        num = 2.0f * root * ratio - (g_halfPiTail - 2.0f * tail);
        den = g_quarterPiHead - 2.0f * scratch;
        arg = g_quarterPiHead - (num - den);
    }
    if (bits > 0) {
        return arg;
    }
    return -arg;
}
