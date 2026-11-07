/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arccosine of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one = 1.0f;
static const f32 pi = 3.1415925026e+00f;
static const f32 half_pi_hi = 1.5707962513e+00f;
static const f32 half_pi_lo = 7.5497894159e-08f;
static const f32 p0 = 1.6666667163e-01f;
static const f32 p1 = -3.2556581497e-01f;
static const f32 p2 = 2.0121252537e-01f;
static const f32 p3 = -4.0055535734e-02f;
static const f32 p4 = 7.9153501429e-04f;
static const f32 p5 = 3.4793309169e-05f;
static const f32 q1 = -2.4033949375e+00f;
static const f32 q2 = 2.0209457874e+00f;
static const f32 q3 = -6.8828397989e-01f;
static const f32 q4 = 7.7038154006e-02f;

f32 func_00208068(f32 x);

f32 func_00206298(f32 x)
{
    f32 t, num, den, ratio, root, head, tail;
    s32 bits, mag, hb;

    FLOAT_TO_BITS(bits, x);
    mag = bits & 0x7fffffff;

    if (mag == 0x3f800000) {
        if (bits > 0) {
            return 0.0f;
        }
        return pi + 2.0f * half_pi_lo;
    } else if (mag > 0x3f800000) {
        return (x - x) / (x - x);
    }
    if (mag < 0x3f000000) {
        if (mag <= 0x23000000) {
            return half_pi_hi + half_pi_lo;
        }
        t = x * x;
        num = t * (p0 + t * (p1 + t * (p2 + t * (p3 + t * (p4 + t * p5)))));
        den = one + t * (q1 + t * (q2 + t * (q3 + t * q4)));
        ratio = num / den;
        return half_pi_hi - (x - (half_pi_lo - x * ratio));
    } else if (bits < 0) {
        t = (one + x) * 0.5f;
        num = t * (p0 + t * (p1 + t * (p2 + t * (p3 + t * (p4 + t * p5)))));
        den = one + t * (q1 + t * (q2 + t * (q3 + t * q4)));
        root = func_00208068(t);
        ratio = num / den;
        return pi - 2.0f * (root + (ratio * root - half_pi_lo));
    } else {
        t = (one - x) * 0.5f;
        root = func_00208068(t);
        head = root;
        FLOAT_TO_BITS(hb, head);
        BITS_TO_FLOAT(head, hb & 0xfffff000);
        tail = (t - head * head) / (root + head);
        num = t * (p0 + t * (p1 + t * (p2 + t * (p3 + t * (p4 + t * p5)))));
        den = one + t * (q1 + t * (q2 + t * (q3 + t * q4)));
        ratio = num / den;
        return 2.0f * (head + (ratio * root + tail));
    }
}
