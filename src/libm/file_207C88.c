/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The reduction of a float argument by pi / 2: the quadrant and the remainder in two floats. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const s32 digits_2_over_pi[] = {
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

static const s32 half_pi_multiples[] = {
    0x3FC90F00, 0x40490F00, 0x4096CB00, 0x40C90F00,
    0x40FB5300, 0x4116CB00, 0x412FED00, 0x41490F00,
    0x41623100, 0x417B5300, 0x418A3A00, 0x4196CB00,
    0x41A35C00, 0x41AFED00, 0x41BC7E00, 0x41C90F00,
    0x41D5A000, 0x41E23100, 0x41EEC200, 0x41FB5300,
    0x4203F200, 0x420A3A00, 0x42108300, 0x4216CB00,
    0x421D1400, 0x42235C00, 0x4229A500, 0x422FED00,
    0x42363600, 0x423C7E00, 0x4242C700, 0x42490F00,
};

static const f32 zero = 0.0f;
static const f32 half = 0.5f;
static const f32 f256 = 2.5600000000e+02f;
static const f32 inv_half_pi = 6.3661980629e-01f;
static const f32 half_pi_1 = 1.5707855225e+00f;
static const f32 half_pi_1_tail = 1.0804334124e-05f;
static const f32 half_pi_2 = 1.0804273188e-05f;
static const f32 half_pi_2_tail = 6.0770999344e-11f;
static const f32 half_pi_3 = 6.0770943833e-11f;
static const f32 half_pi_3_tail = 6.1232342629e-17f;

f32 func_002052F8(f32 x);
s32 func_002082F8(f32* x, f32* y, s32 e0, s32 nx, s32 prec, const s32* table);

s32 func_00207C88(f32 x, f32* y)
{
    s32 hx, ix, hy, n, i, j, e0, nx;
    f32 z, r, w, t, fn, tx[3];

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix <= 0x3F490FD8) {
        y[0] = x;
        y[1] = 0.0f;
        return 0;
    }
    if (ix <= 0x4016CBE3) {
        if (hx > 0) {
            z = x - half_pi_1;
            if ((ix & 0xFFFFFFF0) != 0x3FC90FD0) {
                y[0] = z - half_pi_1_tail;
                y[1] = (z - y[0]) - half_pi_1_tail;
            } else {
                z -= half_pi_2;
                y[0] = z - half_pi_2_tail;
                y[1] = (z - y[0]) - half_pi_2_tail;
            }
            return 1;
        } else {
            z = x + half_pi_1;
            if ((ix & 0xFFFFFFF0) != 0x3FC90FD0) {
                y[0] = z + half_pi_1_tail;
                y[1] = (z - y[0]) + half_pi_1_tail;
            } else {
                z += half_pi_2;
                y[0] = z + half_pi_2_tail;
                y[1] = (z - y[0]) + half_pi_2_tail;
            }
            return -1;
        }
    }
    if (ix <= 0x43490F80) {
        t = func_002052F8(x);
        n = (s32)(t * inv_half_pi + half);
        fn = (f32)n;
        r = t - fn * half_pi_1;
        w = fn * half_pi_1_tail;
        if (n < 32 && (ix & 0xFFFFFF00) != half_pi_multiples[n - 1]) {
            y[0] = r - w;
        } else {
            y[0] = r - w;
            j = ix >> 23;
            FLOAT_TO_BITS(hy, y[0]);
            i = j - (((u32)hy >> 23) & 0xFF);
            if (i > 8) {
                t = r;
                w = fn * half_pi_2;
                r = t - w;
                w = fn * half_pi_2_tail - ((t - r) - w);
                y[0] = r - w;
                FLOAT_TO_BITS(hy, y[0]);
                i = j - (((u32)hy >> 23) & 0xFF);
                if (i > 25) {
                    t = r;
                    w = fn * half_pi_3;
                    r = t - w;
                    w = fn * half_pi_3_tail - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }
        y[1] = (r - y[0]) - w;
        if (hx < 0) {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        }
        return n;
    }
    if (ix > 0x7F7FFFFF) {
        y[0] = y[1] = x - x;
        return 0;
    }
    e0 = (ix >> 23) - 134;
    BITS_TO_FLOAT(z, ix - (e0 << 23));
    for (i = 0; i < 2; i++) {
        tx[i] = (f32)(s32)z;
        z = (z - tx[i]) * f256;
    }
    tx[2] = z;
    nx = 3;
    while (tx[nx - 1] == zero) {
        nx--;
    }
    n = func_002082F8(tx, y, e0, nx, 2, digits_2_over_pi);
    if (hx < 0) {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }
    return n;
}
