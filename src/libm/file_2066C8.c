/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arcsine of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one = 1.0f;
static const f32 huge = 1.0e30f;
static const f32 half_pi_hi = 1.5707962513e+00f;
static const f32 half_pi_lo = 7.5497894159e-08f;
static const f32 quarter_pi_hi = 7.8539818525e-01f;
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

f32 func_002052F8(f32 x);
f32 func_00208068(f32 x);

f32 func_002066C8(f32 x)
{
    s32 hx, ix, sb;
    f32 t, w, p, q, s, r, c;

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix == 0x3F800000) {
        return x * half_pi_hi + x * half_pi_lo;
    }
    if (ix > 0x3F800000) {
        return (x - x) / (x - x);
    }
    if (ix < 0x3F000000) {
        if (ix < 0x32000000) {
            if (huge + x > one) {
                return x;
            }
        } else {
            t = x * x;
        }
        p = t * (p0 + t * (p1 + t * (p2 + t * (p3 + t * (p4 + t * p5)))));
        q = one + t * (q1 + t * (q2 + t * (q3 + t * q4)));
        w = p / q;
        return x + x * w;
    }
    w = one - func_002052F8(x);
    t = w * 0.5f;
    p = t * (p0 + t * (p1 + t * (p2 + t * (p3 + t * (p4 + t * p5)))));
    q = one + t * (q1 + t * (q2 + t * (q3 + t * q4)));
    s = func_00208068(t);
    if (ix >= 0x3F79999A) {
        w = p / q;
        t = half_pi_hi - (2.0f * (s + s * w) - half_pi_lo);
    } else {
        FLOAT_TO_BITS(sb, s);
        sb &= 0xFFFFF000;
        BITS_TO_FLOAT(w, sb);
        c = (t - w * w) / (s + w);
        r = p / q;
        p = 2.0f * s * r - (half_pi_lo - 2.0f * c);
        q = quarter_pi_hi - 2.0f * w;
        t = quarter_pi_hi - (p - q);
    }
    if (hx > 0) {
        return t;
    }
    return -t;
}
