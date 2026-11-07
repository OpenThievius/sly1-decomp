/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arctangent of a float. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 atan_anchor_head[] = { 0.4636476f, 0.7853981f, 0.9827937f, 1.5707963f };
static const f32 atan_anchor_tail[] = { 5.0121582e-09f, 3.7748947e-08f, 3.4473217e-08f, 7.5497894e-08f };
static const f32 atan_coefficients[] = { 0.33333334f, -0.2f, 0.14285715f, -0.111111104f, 0.09090887f, -0.07691876f, 0.06661073f, -0.058335703f, 0.04976878f, -0.03653157f, 0.01628582f };
static const f32 one_f = 1.0f;
static const f32 ten_to_30 = 1.0e30f;

f32 func_002052F8(f32 x);

f32 func_00204F68(f32 x)
{
    s32 bits;
    s32 magnitude;
    s32 anchor;
    f32 x2, x4, odd_sum, even_sum;

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude >= 0x50800000) {
        if (magnitude > 0x7F800000) {
            return x + x;
        }
        if (bits > 0) {
            return atan_anchor_head[3] + atan_anchor_tail[3];
        }
        return -atan_anchor_head[3] - atan_anchor_tail[3];
    }
    if (magnitude < 0x3EE00000) {
        if (magnitude < 0x31000000) {
            if (ten_to_30 + x > one_f) {
                return x;
            }
        }
        anchor = -1;
    } else {
        x = func_002052F8(x);
        if (magnitude < 0x3F980000) {
            if (magnitude < 0x3F300000) {
                anchor = 0;
                x = (2.0f * x - one_f) / (2.0f + x);
            } else {
                anchor = 1;
                x = (x - one_f) / (x + one_f);
            }
        } else {
            if (magnitude < 0x401C0000) {
                anchor = 2;
                x = (x - 1.5f) / (one_f + 1.5f * x);
            } else {
                anchor = 3;
                x = -1.0f / x;
            }
        }
    }
    x2 = x * x;
    x4 = x2 * x2;
    odd_sum = x2 * (atan_coefficients[0] + x4 * (atan_coefficients[2] + x4 * (atan_coefficients[4] + x4 * (atan_coefficients[6] + x4 * (atan_coefficients[8] + x4 * atan_coefficients[10])))));
    even_sum = x4 * (atan_coefficients[1] + x4 * (atan_coefficients[3] + x4 * (atan_coefficients[5] + x4 * (atan_coefficients[7] + x4 * atan_coefficients[9]))));
    if (anchor < 0) {
        return x - x * (odd_sum + even_sum);
    }
    x2 = atan_anchor_head[anchor] - ((x * (odd_sum + even_sum) - atan_anchor_tail[anchor]) - x);
    return bits < 0 ? -x2 : x2;
}
