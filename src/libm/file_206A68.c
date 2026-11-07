/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arctangent of y / x for floats, in the right quadrant (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 g_tenToMinus30 = 1.0e-30f;
static const f32 g_zero = 0.0f;
static const f32 g_quarterPi = 7.8539818525e-01f;
static const f32 g_halfPi = 1.5707963705e+00f;
static const f32 g_pi = 3.1415925026e+00f;
static const f32 g_piTail = 1.5099578832e-07f;

f32 func_00204F68(f32 x);
f32 func_002052F8(f32 x);

f32 func_00206A68(f32 y, f32 x)
{
    s32 xBits, yBits, xMag, yMag, quadrantCase, exponentGap, angleBits;
    f32 angle;

    FLOAT_TO_BITS(xBits, x);
    xMag = xBits & 0x7FFFFFFF;
    FLOAT_TO_BITS(yBits, y);
    yMag = yBits & 0x7FFFFFFF;
    if (xMag > 0x7F800000 || yMag > 0x7F800000) {
        return x + y;
    }
    if (xBits == 0x3F800000) {
        return func_00204F68(y);
    }
    quadrantCase = ((u32)yBits >> 31) | ((xBits >> 30) & 2);
    if (yMag == 0) {
        switch (quadrantCase) {
        case 0:
        case 1:
            return y;
        case 2:
            return g_pi + g_tenToMinus30;
        case 3:
            return -g_pi - g_tenToMinus30;
        }
    }
    if (xMag == 0) {
        return yBits < 0 ? -g_halfPi - g_tenToMinus30 : g_halfPi + g_tenToMinus30;
    }
    if (xMag == 0x7F800000) {
        if (yMag == xMag) {
            switch (quadrantCase) {
            case 0:
                return g_quarterPi + g_tenToMinus30;
            case 1:
                return -g_quarterPi - g_tenToMinus30;
            case 2:
                return 3.0f * g_quarterPi + g_tenToMinus30;
            case 3:
                return -3.0f * g_quarterPi - g_tenToMinus30;
            }
        } else {
            switch (quadrantCase) {
            case 0:
                return g_zero;
            case 1:
                return -g_zero;
            case 2:
                return g_pi + g_tenToMinus30;
            case 3:
                return -g_pi - g_tenToMinus30;
            }
        }
    }
    if (yMag == 0x7F800000) {
        return yBits < 0 ? -g_halfPi - g_tenToMinus30 : g_halfPi + g_tenToMinus30;
    }
    exponentGap = (yMag - xMag) >> 23;
    if (exponentGap > 60) {
        angle = g_halfPi + 0.5f * g_piTail;
    } else if (xBits < 0 && exponentGap < -60) {
        angle = 0.0f;
    } else {
        angle = func_00204F68(func_002052F8(y / x));
    }
    switch (quadrantCase) {
    case 0:
        return angle;
    case 1:
        FLOAT_TO_BITS(angleBits, angle);
        BITS_TO_FLOAT(angle, angleBits ^ 0x80000000);
        return angle;
    case 2:
        return g_pi - (angle - g_piTail);
    default:
        return (angle - g_piTail) - g_pi;
    }
}
