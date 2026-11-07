/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The reduction of a float argument by pi / 2: the quadrant and the remainder in two floats. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const s32 g_digits2OverPi[] = {
    0xA2, 0xF9, 0x83, 0x6E, 0x4E, 0x44, 0x15, 0x29, 0xFC, 0x27, 0x57, 0xD1,
    0xF5, 0x34, 0xDD, 0xC0, 0xDB, 0x62, 0x95, 0x99, 0x3C, 0x43, 0x90, 0x41,
    0xFE, 0x51, 0x63, 0xAB, 0xDE, 0xBB, 0xC5, 0x61, 0xB7, 0x24, 0x6E, 0x3A,
    0x42, 0x4D, 0xD2, 0xE0, 0x06, 0x49, 0x2E, 0xEA, 0x09, 0xD1, 0x92, 0x1C,
    0xFE, 0x1D, 0xEB, 0x1C, 0xB1, 0x29, 0xA7, 0x3E, 0xE8, 0x82, 0x35, 0xF5,
    0x2E, 0xBB, 0x44, 0x84, 0xE9, 0x9C, 0x70, 0x26, 0xB4, 0x5F, 0x7E, 0x41,
    0x39, 0x91, 0xD6, 0x39, 0x83, 0x53, 0x39, 0xF4, 0x9C, 0x84, 0x5F, 0x8B,
    0xBD, 0xF9, 0x28, 0x3B, 0x1F, 0xF8, 0x97, 0xFF, 0xDE, 0x05, 0x98, 0x0F,
    0xEF, 0x2F, 0x11, 0x8B, 0x5A, 0x0A, 0x6D, 0x1F, 0x6D, 0x36, 0x7E, 0xCF,
    0x27, 0xCB, 0x09, 0xB7, 0x4F, 0x46, 0x3F, 0x66, 0x9E, 0x5F, 0xEA, 0x2D,
    0x75, 0x27, 0xBA, 0xC7, 0xEB, 0xE5, 0xF1, 0x7B, 0x3D, 0x07, 0x39, 0xF7,
    0x8A, 0x52, 0x92, 0xEA, 0x6B, 0xFB, 0x5F, 0xB1, 0x1F, 0x8D, 0x5D, 0x08,
    0x56, 0x03, 0x30, 0x46, 0xFC, 0x7B, 0x6B, 0xAB, 0xF0, 0xCF, 0xBC, 0x20,
    0x9A, 0xF4, 0x36, 0x1D, 0xA9, 0xE3, 0x91, 0x61, 0x5E, 0xE6, 0x1B, 0x08,
    0x65, 0x99, 0x85, 0x5F, 0x14, 0xA0, 0x68, 0x40, 0x8D, 0xFF, 0xD8, 0x80,
    0x4D, 0x73, 0x27, 0x31, 0x06, 0x06, 0x15, 0x56, 0xCA, 0x73, 0xA8, 0xC9,
    0x60, 0xE2, 0x7B, 0xC0, 0x8C, 0x6B,
};

static const s32 g_halfPiMultiples[] = {
    0x3FC90F00, 0x40490F00, 0x4096CB00, 0x40C90F00,
    0x40FB5300, 0x4116CB00, 0x412FED00, 0x41490F00,
    0x41623100, 0x417B5300, 0x418A3A00, 0x4196CB00,
    0x41A35C00, 0x41AFED00, 0x41BC7E00, 0x41C90F00,
    0x41D5A000, 0x41E23100, 0x41EEC200, 0x41FB5300,
    0x4203F200, 0x420A3A00, 0x42108300, 0x4216CB00,
    0x421D1400, 0x42235C00, 0x4229A500, 0x422FED00,
    0x42363600, 0x423C7E00, 0x4242C700, 0x42490F00,
};

static const f32 g_zero = 0.0f;
static const f32 g_half = 0.5f;
static const f32 g_digitBase = 2.5600000000e+02f;
static const f32 g_invHalfPi = 6.3661980629e-01f;
static const f32 g_halfPiHead1 = 1.5707855225e+00f;
static const f32 g_halfPiTail1 = 1.0804334124e-05f;
static const f32 g_halfPiHead2 = 1.0804273188e-05f;
static const f32 g_halfPiTail2 = 6.0770999344e-11f;
static const f32 g_halfPiHead3 = 6.0770943833e-11f;
static const f32 g_halfPiTail3 = 6.1232342629e-17f;

f32 func_002052F8(f32 x);
s32 func_002082F8(f32* digits, f32* parts, s32 exponent, s32 digitCount, s32 precision, const s32* twoOverPi);

s32 func_00207C88(f32 x, f32* parts)
{
    s32 bits, magnitude, remBits, quadrant, i, xExp, exponent, digitCount;
    f32 scaled, rem, correction, absX, quadrantF, digits[3];

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude <= 0x3F490FD8) {
        parts[0] = x;
        parts[1] = 0.0f;
        return 0;
    }
    if (magnitude <= 0x4016CBE3) {
        if (bits > 0) {
            scaled = x - g_halfPiHead1;
            if ((magnitude & 0xFFFFFFF0) != 0x3FC90FD0) {
                parts[0] = scaled - g_halfPiTail1;
                parts[1] = (scaled - parts[0]) - g_halfPiTail1;
            } else {
                scaled -= g_halfPiHead2;
                parts[0] = scaled - g_halfPiTail2;
                parts[1] = (scaled - parts[0]) - g_halfPiTail2;
            }
            return 1;
        } else {
            scaled = x + g_halfPiHead1;
            if ((magnitude & 0xFFFFFFF0) != 0x3FC90FD0) {
                parts[0] = scaled + g_halfPiTail1;
                parts[1] = (scaled - parts[0]) + g_halfPiTail1;
            } else {
                scaled += g_halfPiHead2;
                parts[0] = scaled + g_halfPiTail2;
                parts[1] = (scaled - parts[0]) + g_halfPiTail2;
            }
            return -1;
        }
    }
    if (magnitude <= 0x43490F80) {
        absX = AbsoluteValue(x);
        quadrant = (s32)(absX * g_invHalfPi + g_half);
        quadrantF = (f32)quadrant;
        rem = absX - quadrantF * g_halfPiHead1;
        correction = quadrantF * g_halfPiTail1;
        if (quadrant < 32 && (magnitude & 0xFFFFFF00) != g_halfPiMultiples[quadrant - 1]) {
            parts[0] = rem - correction;
        } else {
            parts[0] = rem - correction;
            xExp = magnitude >> 23;
            FLOAT_TO_BITS(remBits, parts[0]);
            i = xExp - (((u32)remBits >> 23) & 0xFF);
            if (i > 8) {
                absX = rem;
                correction = quadrantF * g_halfPiHead2;
                rem = absX - correction;
                correction = quadrantF * g_halfPiTail2 - ((absX - rem) - correction);
                parts[0] = rem - correction;
                FLOAT_TO_BITS(remBits, parts[0]);
                i = xExp - (((u32)remBits >> 23) & 0xFF);
                if (i > 25) {
                    absX = rem;
                    correction = quadrantF * g_halfPiHead3;
                    rem = absX - correction;
                    correction = quadrantF * g_halfPiTail3 - ((absX - rem) - correction);
                    parts[0] = rem - correction;
                }
            }
        }
        parts[1] = (rem - parts[0]) - correction;
        if (bits < 0) {
            parts[0] = -parts[0];
            parts[1] = -parts[1];
            return -quadrant;
        }
        return quadrant;
    }
    if (magnitude > 0x7F7FFFFF) {
        parts[0] = parts[1] = x - x;
        return 0;
    }
    exponent = (magnitude >> 23) - 134;
    BITS_TO_FLOAT(scaled, magnitude - (exponent << 23));
    for (i = 0; i < 2; i++) {
        digits[i] = (f32)(s32)scaled;
        scaled = (scaled - digits[i]) * g_digitBase;
    }
    digits[2] = scaled;
    digitCount = 3;
    while (digits[digitCount - 1] == g_zero) {
        digitCount--;
    }
    quadrant = ReduceLargeByHalfPi(digits, parts, exponent, digitCount, 2, g_digits2OverPi);
    if (bits < 0) {
        parts[0] = -parts[0];
        parts[1] = -parts[1];
        return -quadrant;
    }
    return quadrant;
}
