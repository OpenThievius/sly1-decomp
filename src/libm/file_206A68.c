/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arctangent of y / x for floats, in the right quadrant (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 ten_to_minus_30 = 1.0e-30f;
static const f32 zero_f = 0.0f;
static const f32 quarter_pi = 7.8539818525e-01f;
static const f32 half_pi = 1.5707963705e+00f;
static const f32 pi = 3.1415925026e+00f;
static const f32 pi_tail = 1.5099578832e-07f;

f32 func_00204F68(f32 x);
f32 func_002052F8(f32 x);

f32 func_00206A68(f32 y, f32 x)
{
    s32 x_bits, y_bits, x_mag, y_mag, quadrant_case, exponent_gap, angle_bits;
    f32 angle;

    FLOAT_TO_BITS(x_bits, x);
    x_mag = x_bits & 0x7FFFFFFF;
    FLOAT_TO_BITS(y_bits, y);
    y_mag = y_bits & 0x7FFFFFFF;
    if (x_mag > 0x7F800000 || y_mag > 0x7F800000) {
        return x + y;
    }
    if (x_bits == 0x3F800000) {
        return func_00204F68(y);
    }
    quadrant_case = ((u32)y_bits >> 31) | ((x_bits >> 30) & 2);
    if (y_mag == 0) {
        switch (quadrant_case) {
        case 0:
        case 1:
            return y;
        case 2:
            return pi + ten_to_minus_30;
        case 3:
            return -pi - ten_to_minus_30;
        }
    }
    if (x_mag == 0) {
        return y_bits < 0 ? -half_pi - ten_to_minus_30 : half_pi + ten_to_minus_30;
    }
    if (x_mag == 0x7F800000) {
        if (y_mag == x_mag) {
            switch (quadrant_case) {
            case 0:
                return quarter_pi + ten_to_minus_30;
            case 1:
                return -quarter_pi - ten_to_minus_30;
            case 2:
                return 3.0f * quarter_pi + ten_to_minus_30;
            case 3:
                return -3.0f * quarter_pi - ten_to_minus_30;
            }
        } else {
            switch (quadrant_case) {
            case 0:
                return zero_f;
            case 1:
                return -zero_f;
            case 2:
                return pi + ten_to_minus_30;
            case 3:
                return -pi - ten_to_minus_30;
            }
        }
    }
    if (y_mag == 0x7F800000) {
        return y_bits < 0 ? -half_pi - ten_to_minus_30 : half_pi + ten_to_minus_30;
    }
    exponent_gap = (y_mag - x_mag) >> 23;
    if (exponent_gap > 60) {
        angle = half_pi + 0.5f * pi_tail;
    } else if (x_bits < 0 && exponent_gap < -60) {
        angle = 0.0f;
    } else {
        angle = func_00204F68(func_002052F8(y / x));
    }
    switch (quadrant_case) {
    case 0:
        return angle;
    case 1:
        FLOAT_TO_BITS(angle_bits, angle);
        BITS_TO_FLOAT(angle, angle_bits ^ 0x80000000);
        return angle;
    case 2:
        return pi - (angle - pi_tail);
    default:
        return (angle - pi_tail) - pi;
    }
}
