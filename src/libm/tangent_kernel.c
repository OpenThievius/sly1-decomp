/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The tangent kernel: tan(x + y), or -1 / tan when sign is -1, for a reduced float argument in two parts. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 g_one = 1.0f;
static const f32 g_quarterPiHead = 7.8539812565e-01f;
static const f32 g_quarterPiTail = 3.7748947079e-08f;
static const f32 g_tanCoefficients[] = {
    3.3333334327e-01f, 1.3333334029e-01f, 5.3968254477e-02f, 2.1869488060e-02f,
    8.8632395491e-03f, 3.5920790397e-03f, 1.4562094584e-03f, 5.8804126456e-04f,
    2.4646313977e-04f, 7.8179444245e-05f, 7.1407252108e-05f, -1.8558637748e-05f,
    2.5907305826e-05f,
};

f32 func_002052F8(f32 x);

f32 func_00208D50(f32 x, f32 y, s32 sign)
{
    s32 bits, magnitude, chopBits;
    f32 x2, x4, poly, polyOdd, x3, negRecip, recipHead;

    FLOAT_TO_BITS(bits, x);
    magnitude = bits & 0x7FFFFFFF;
    if (magnitude <= 0x317FFFFF) {
        if ((s32)x == 0) {
            if ((magnitude | (sign + 1)) == 0) {
                return g_one / AbsoluteValue(x);
            }
            if (sign != 1) {
                return -g_one / x;
            }
            return x;
        }
    }
    if (magnitude > 0x3F2CA13F) {
        if (bits < 0) {
            x = -x;
            y = -y;
        }
        x2 = g_quarterPiHead - x;
        x4 = g_quarterPiTail - y;
        x = x2 + x4;
        y = 0.0f;
    }
    x2 = x * x;
    x4 = x2 * x2;
    poly = g_tanCoefficients[1] + x4 * (g_tanCoefficients[3] + x4 * (g_tanCoefficients[5] + x4 * (g_tanCoefficients[7] + x4 * (g_tanCoefficients[9] + x4 * g_tanCoefficients[11]))));
    polyOdd = x2 * (g_tanCoefficients[2] + x4 * (g_tanCoefficients[4] + x4 * (g_tanCoefficients[6] + x4 * (g_tanCoefficients[8] + x4 * (g_tanCoefficients[10] + x4 * g_tanCoefficients[12])))));
    x3 = x2 * x;
    poly = y + x2 * (x3 * (poly + polyOdd) + y);
    poly += g_tanCoefficients[0] * x3;
    x4 = x + poly;
    if (magnitude > 0x3F2CA13F) {
        polyOdd = (f32)sign;
        return (f32)(1 - ((bits >> 30) & 2)) * (polyOdd - 2.0f * (x - (x4 * x4 / (x4 + polyOdd) - poly)));
    }
    if (sign == 1) {
        return x4;
    }
    FLOAT_TO_BITS(chopBits, x4);
    BITS_TO_FLOAT(x2, chopBits & 0xFFFFF000);
    polyOdd = poly - (x2 - x);
    negRecip = -g_one / x4;
    FLOAT_TO_BITS(chopBits, negRecip);
    BITS_TO_FLOAT(recipHead, chopBits & 0xFFFFF000);
    x3 = g_one + recipHead * x2;
    return recipHead + negRecip * (x3 + recipHead * polyOdd);
}
