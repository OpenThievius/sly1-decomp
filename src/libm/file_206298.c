/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arccosine of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one_f = 1.0f;
static const f32 pi = 3.1415925026e+00f;
static const f32 half_pi_head = 1.5707962513e+00f;
static const f32 half_pi_tail = 7.5497894159e-08f;
static const f32 num_t1 = 1.6666667163e-01f;
static const f32 num_t2 = -3.2556581497e-01f;
static const f32 num_t3 = 2.0121252537e-01f;
static const f32 num_t4 = -4.0055535734e-02f;
static const f32 num_t5 = 7.9153501429e-04f;
static const f32 num_t6 = 3.4793309169e-05f;
static const f32 den_t1 = -2.4033949375e+00f;
static const f32 den_t2 = 2.0209457874e+00f;
static const f32 den_t3 = -6.8828397989e-01f;
static const f32 den_t4 = 7.7038154006e-02f;

f32 func_00208068(f32 x);

f32 func_00206298(f32 x)
{
    f32 t, num, den, ratio, root, head, tail;
    s32 bits, mag, head_bits;

    FLOAT_TO_BITS(bits, x);
    mag = bits & 0x7fffffff;

    if (mag == 0x3f800000) {
        if (bits > 0) {
            return 0.0f;
        }
        return pi + 2.0f * half_pi_tail;
    } else if (mag > 0x3f800000) {
        return (x - x) / (x - x);
    }
    if (mag < 0x3f000000) {
        if (mag <= 0x23000000) {
            return half_pi_head + half_pi_tail;
        }
        t = x * x;
        num = t * (num_t1 + t * (num_t2 + t * (num_t3 + t * (num_t4 + t * (num_t5 + t * num_t6)))));
        den = one_f + t * (den_t1 + t * (den_t2 + t * (den_t3 + t * den_t4)));
        ratio = num / den;
        return half_pi_head - (x - (half_pi_tail - x * ratio));
    } else if (bits < 0) {
        t = (one_f + x) * 0.5f;
        num = t * (num_t1 + t * (num_t2 + t * (num_t3 + t * (num_t4 + t * (num_t5 + t * num_t6)))));
        den = one_f + t * (den_t1 + t * (den_t2 + t * (den_t3 + t * den_t4)));
        root = func_00208068(t);
        ratio = num / den;
        return pi - 2.0f * (root + (ratio * root - half_pi_tail));
    } else {
        t = (one_f - x) * 0.5f;
        root = func_00208068(t);
        head = root;
        FLOAT_TO_BITS(head_bits, head);
        BITS_TO_FLOAT(head, head_bits & 0xfffff000);
        tail = (t - head * head) / (root + head);
        num = t * (num_t1 + t * (num_t2 + t * (num_t3 + t * (num_t4 + t * (num_t5 + t * num_t6)))));
        den = one_f + t * (den_t1 + t * (den_t2 + t * (den_t3 + t * den_t4)));
        ratio = num / den;
        return 2.0f * (head + (ratio * root + tail));
    }
}
