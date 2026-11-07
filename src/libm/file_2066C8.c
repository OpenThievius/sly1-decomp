/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arcsine of a float (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 one_f = 1.0f;
static const f32 ten_to_30 = 1.0e30f;
static const f32 half_pi_head = 1.5707962513e+00f;
static const f32 half_pi_tail = 7.5497894159e-08f;
static const f32 quarter_pi_head = 7.8539818525e-01f;
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

f32 func_002052F8(f32 x);
f32 func_00208068(f32 x);

f32 func_002066C8(f32 x)
{
    s32 bits, magnitude, root_bits;
    f32 arg, scratch, num, den, root, ratio, tail;

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude == 0x3F800000) {
        return x * half_pi_head + x * half_pi_tail;
    }
    if (magnitude > 0x3F800000) {
        return (x - x) / (x - x);
    }
    if (magnitude < 0x3F000000) {
        if (magnitude < 0x32000000) {
            if (ten_to_30 + x > one_f) {
                return x;
            }
        } else {
            arg = x * x;
        }
        num = arg * (num_t1 + arg * (num_t2 + arg * (num_t3 + arg * (num_t4 + arg * (num_t5 + arg * num_t6)))));
        den = one_f + arg * (den_t1 + arg * (den_t2 + arg * (den_t3 + arg * den_t4)));
        scratch = num / den;
        return x + x * scratch;
    }
    scratch = one_f - func_002052F8(x);
    arg = scratch * 0.5f;
    num = arg * (num_t1 + arg * (num_t2 + arg * (num_t3 + arg * (num_t4 + arg * (num_t5 + arg * num_t6)))));
    den = one_f + arg * (den_t1 + arg * (den_t2 + arg * (den_t3 + arg * den_t4)));
    root = func_00208068(arg);
    if (magnitude >= 0x3F79999A) {
        scratch = num / den;
        arg = half_pi_head - (2.0f * (root + root * scratch) - half_pi_tail);
    } else {
        FLOAT_TO_BITS(root_bits, root);
        root_bits &= 0xFFFFF000;
        BITS_TO_FLOAT(scratch, root_bits);
        tail = (arg - scratch * scratch) / (root + scratch);
        ratio = num / den;
        num = 2.0f * root * ratio - (half_pi_tail - 2.0f * tail);
        den = quarter_pi_head - 2.0f * scratch;
        arg = quarter_pi_head - (num - den);
    }
    if (bits > 0) {
        return arg;
    }
    return -arg;
}
