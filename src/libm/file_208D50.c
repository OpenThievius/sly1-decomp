/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The tangent kernel: tan(x + y), or -1 / tan when k is -1, for a reduced float argument in two parts. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 one = 1.0f;
static const f32 quarter_pi = 7.8539812565e-01f;
static const f32 quarter_pi_lo = 3.7748947079e-08f;
static const f32 coeffs[] = {
    3.3333334327e-01f, 1.3333334029e-01f, 5.3968254477e-02f, 2.1869488060e-02f,
    8.8632395491e-03f, 3.5920790397e-03f, 1.4562094584e-03f, 5.8804126456e-04f,
    2.4646313977e-04f, 7.8179444245e-05f, 7.1407252108e-05f, -1.8558637748e-05f,
    2.5907305826e-05f,
};

f32 func_002052F8(f32 x);

f32 func_00208D50(f32 x, f32 y, s32 k)
{
    s32 hx, ix, zb;
    f32 z, w, r, v, s, t, a;

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix <= 0x317FFFFF) {
        if ((s32)x == 0) {
            if ((ix | (k + 1)) == 0) {
                return one / func_002052F8(x);
            }
            if (k != 1) {
                return -one / x;
            }
            return x;
        }
    }
    if (ix > 0x3F2CA13F) {
        if (hx < 0) {
            x = -x;
            y = -y;
        }
        z = quarter_pi - x;
        w = quarter_pi_lo - y;
        x = z + w;
        y = 0.0f;
    }
    z = x * x;
    w = z * z;
    r = coeffs[1] + w * (coeffs[3] + w * (coeffs[5] + w * (coeffs[7] + w * (coeffs[9] + w * coeffs[11]))));
    v = z * (coeffs[2] + w * (coeffs[4] + w * (coeffs[6] + w * (coeffs[8] + w * (coeffs[10] + w * coeffs[12])))));
    s = z * x;
    r = y + z * (s * (r + v) + y);
    r += coeffs[0] * s;
    w = x + r;
    if (ix > 0x3F2CA13F) {
        v = (f32)k;
        return (f32)(1 - ((hx >> 30) & 2)) * (v - 2.0f * (x - (w * w / (w + v) - r)));
    }
    if (k == 1) {
        return w;
    }
    FLOAT_TO_BITS(zb, w);
    BITS_TO_FLOAT(z, zb & 0xFFFFF000);
    v = r - (z - x);
    t = -one / w;
    FLOAT_TO_BITS(zb, t);
    BITS_TO_FLOAT(a, zb & 0xFFFFF000);
    s = one + a * z;
    return a + t * (s + a * v);
}
