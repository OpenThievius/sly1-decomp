/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The arctangent of a float. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 high[] = { 0.4636476f, 0.7853981f, 0.9827937f, 1.5707963f };
static const f32 low[] = { 5.0121582e-09f, 3.7748947e-08f, 3.4473217e-08f, 7.5497894e-08f };
static const f32 coeff[] = { 0.33333334f, -0.2f, 0.14285715f, -0.111111104f, 0.09090887f, -0.07691876f, 0.06661073f, -0.058335703f, 0.04976878f, -0.03653157f, 0.01628582f };
static const f32 one = 1.0f;
static const f32 huge = 1.0e30f;

f32 func_002052F8(f32 x);

f32 func_00204F68(f32 x)
{
    s32 hx;
    s32 ix;
    s32 id;
    f32 z, w, s1, s2;

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix >= 0x50800000) {
        if (ix > 0x7F800000) {
            return x + x;
        }
        if (hx > 0) {
            return high[3] + low[3];
        }
        return -high[3] - low[3];
    }
    if (ix < 0x3EE00000) {
        if (ix < 0x31000000) {
            if (huge + x > one) {
                return x;
            }
        }
        id = -1;
    } else {
        x = func_002052F8(x);
        if (ix < 0x3F980000) {
            if (ix < 0x3F300000) {
                id = 0;
                x = (2.0f * x - one) / (2.0f + x);
            } else {
                id = 1;
                x = (x - one) / (x + one);
            }
        } else {
            if (ix < 0x401C0000) {
                id = 2;
                x = (x - 1.5f) / (one + 1.5f * x);
            } else {
                id = 3;
                x = -1.0f / x;
            }
        }
    }
    z = x * x;
    w = z * z;
    s1 = z * (coeff[0] + w * (coeff[2] + w * (coeff[4] + w * (coeff[6] + w * (coeff[8] + w * coeff[10])))));
    s2 = w * (coeff[1] + w * (coeff[3] + w * (coeff[5] + w * (coeff[7] + w * coeff[9]))));
    if (id < 0) {
        return x - x * (s1 + s2);
    }
    z = high[id] - ((x * (s1 + s2) - low[id]) - x);
    return hx < 0 ? -z : z;
}
