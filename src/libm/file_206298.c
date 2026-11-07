/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arccosine of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_one = 1.0f;
static const f32 g_pi = 3.1415925026e+00f;
static const f32 g_halfPiHead = 1.5707962513e+00f;
static const f32 g_halfPiTail = 7.5497894159e-08f;
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

f32 func_00208068(f32 x);

f32 func_00206298(f32 x)
{
    f32 t, num, den, ratio, root, head, tail;
    s32 bits, mag, headBits;

    FLOAT_TO_BITS(bits, x);
    mag = bits & 0x7fffffff;

    if (mag == 0x3f800000) {
        if (bits > 0) {
            return 0.0f;
        }
        return g_pi + 2.0f * g_halfPiTail;
    } else if (mag > 0x3f800000) {
        return (x - x) / (x - x);
    }
    if (mag < 0x3f000000) {
        if (mag <= 0x23000000) {
            return g_halfPiHead + g_halfPiTail;
        }
        t = x * x;
        num = t * (g_numT1 + t * (g_numT2 + t * (g_numT3 + t * (g_numT4 + t * (g_numT5 + t * g_numT6)))));
        den = g_one + t * (g_denT1 + t * (g_denT2 + t * (g_denT3 + t * g_denT4)));
        ratio = num / den;
        return g_halfPiHead - (x - (g_halfPiTail - x * ratio));
    } else if (bits < 0) {
        t = (g_one + x) * 0.5f;
        num = t * (g_numT1 + t * (g_numT2 + t * (g_numT3 + t * (g_numT4 + t * (g_numT5 + t * g_numT6)))));
        den = g_one + t * (g_denT1 + t * (g_denT2 + t * (g_denT3 + t * g_denT4)));
        root = func_00208068(t);
        ratio = num / den;
        return g_pi - 2.0f * (root + (ratio * root - g_halfPiTail));
    } else {
        t = (g_one - x) * 0.5f;
        root = func_00208068(t);
        head = root;
        FLOAT_TO_BITS(headBits, head);
        BITS_TO_FLOAT(head, headBits & 0xfffff000);
        tail = (t - head * head) / (root + head);
        num = t * (g_numT1 + t * (g_numT2 + t * (g_numT3 + t * (g_numT4 + t * (g_numT5 + t * g_numT6)))));
        den = g_one + t * (g_denT1 + t * (g_denT2 + t * (g_denT3 + t * g_denT4)));
        ratio = num / den;
        return 2.0f * (head + (ratio * root + tail));
    }
}
