/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The tangent kernel: tan(x + y), or -1 / tan when sign is -1, for a reduced float argument in two parts. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 one_f = 1.0f;
static const f32 quarter_pi_head = 7.8539812565e-01f;
static const f32 quarter_pi_tail = 3.7748947079e-08f;
static const f32 tan_coefficients[] = {
    3.3333334327e-01f, 1.3333334029e-01f, 5.3968254477e-02f, 2.1869488060e-02f,
    8.8632395491e-03f, 3.5920790397e-03f, 1.4562094584e-03f, 5.8804126456e-04f,
    2.4646313977e-04f, 7.8179444245e-05f, 7.1407252108e-05f, -1.8558637748e-05f,
    2.5907305826e-05f,
};

f32 func_002052F8(f32 x);

f32 func_00208D50(f32 x, f32 y, s32 sign)
{
    s32 bits, magnitude, chop_bits;
    f32 x2, x4, poly, poly_odd, x3, neg_recip, recip_head;

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude <= 0x317FFFFF) {
        if ((s32)x == 0) {
            if ((magnitude | (sign + 1)) == 0) {
                return one_f / func_002052F8(x);
            }
            if (sign != 1) {
                return -one_f / x;
            }
            return x;
        }
    }
    if (magnitude > 0x3F2CA13F) {
        if (bits < 0) {
            x = -x;
            y = -y;
        }
        x2 = quarter_pi_head - x;
        x4 = quarter_pi_tail - y;
        x = x2 + x4;
        y = 0.0f;
    }
    x2 = x * x;
    x4 = x2 * x2;
    poly = tan_coefficients[1] + x4 * (tan_coefficients[3] + x4 * (tan_coefficients[5] + x4 * (tan_coefficients[7] + x4 * (tan_coefficients[9] + x4 * tan_coefficients[11]))));
    poly_odd = x2 * (tan_coefficients[2] + x4 * (tan_coefficients[4] + x4 * (tan_coefficients[6] + x4 * (tan_coefficients[8] + x4 * (tan_coefficients[10] + x4 * tan_coefficients[12])))));
    x3 = x2 * x;
    poly = y + x2 * (x3 * (poly + poly_odd) + y);
    poly += tan_coefficients[0] * x3;
    x4 = x + poly;
    if (magnitude > 0x3F2CA13F) {
        poly_odd = (f32)sign;
        return (f32)(1 - ((bits >> 30) & 2)) * (poly_odd - 2.0f * (x - (x4 * x4 / (x4 + poly_odd) - poly)));
    }
    if (sign == 1) {
        return x4;
    }
    FLOAT_TO_BITS(chop_bits, x4);
    BITS_TO_FLOAT(x2, chop_bits & 0xFFFFF000);
    poly_odd = poly - (x2 - x);
    neg_recip = -one_f / x4;
    FLOAT_TO_BITS(chop_bits, neg_recip);
    BITS_TO_FLOAT(recip_head, chop_bits & 0xFFFFF000);
    x3 = one_f + recip_head * x2;
    return recip_head + neg_recip * (x3 + recip_head * poly_odd);
}
