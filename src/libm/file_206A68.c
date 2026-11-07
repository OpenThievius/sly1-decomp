/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arctangent of y / x for floats, in the right quadrant (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 tiny = 1.0e-30f;
static const f32 zero = 0.0f;
static const f32 quarter_pi = 7.8539818525e-01f;
static const f32 half_pi = 1.5707963705e+00f;
static const f32 pi = 3.1415925026e+00f;
static const f32 pi_lo = 1.5099578832e-07f;

f32 func_00204F68(f32 x);
f32 func_002052F8(f32 x);

f32 func_00206A68(f32 y, f32 x)
{
    s32 hx, hy, ix, iy, m, k, iz;
    f32 z;

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    FLOAT_TO_BITS(hy, y);
    iy = hy & 0x7FFFFFFF;
    if (ix > 0x7F800000 || iy > 0x7F800000) {
        return x + y;
    }
    if (hx == 0x3F800000) {
        return func_00204F68(y);
    }
    m = ((u32)hy >> 31) | ((hx >> 30) & 2);
    if (iy == 0) {
        switch (m) {
        case 0:
        case 1:
            return y;
        case 2:
            return pi + tiny;
        case 3:
            return -pi - tiny;
        }
    }
    if (ix == 0) {
        return hy < 0 ? -half_pi - tiny : half_pi + tiny;
    }
    if (ix == 0x7F800000) {
        if (iy == ix) {
            switch (m) {
            case 0:
                return quarter_pi + tiny;
            case 1:
                return -quarter_pi - tiny;
            case 2:
                return 3.0f * quarter_pi + tiny;
            case 3:
                return -3.0f * quarter_pi - tiny;
            }
        } else {
            switch (m) {
            case 0:
                return zero;
            case 1:
                return -zero;
            case 2:
                return pi + tiny;
            case 3:
                return -pi - tiny;
            }
        }
    }
    if (iy == 0x7F800000) {
        return hy < 0 ? -half_pi - tiny : half_pi + tiny;
    }
    k = (iy - ix) >> 23;
    if (k > 60) {
        z = half_pi + 0.5f * pi_lo;
    } else if (hx < 0 && k < -60) {
        z = 0.0f;
    } else {
        z = func_00204F68(func_002052F8(y / x));
    }
    switch (m) {
    case 0:
        return z;
    case 1:
        FLOAT_TO_BITS(iz, z);
        BITS_TO_FLOAT(z, iz ^ 0x80000000);
        return z;
    case 2:
        return pi - (z - pi_lo);
    default:
        return (z - pi_lo) - pi;
    }
}
