/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A float rounded down to an integer. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"
static const f32 ten_to_30 = 1.0e30f;

f32 func_00205318(f32 x)
{
    s32 bits = *(s32*)&x;
    s32 exponent = ((bits >> 23) & 0xff) - 0x7f;
    s32 fraction_mask;

    if (exponent < 0x17) {
        if (exponent < 0) {
            if (ten_to_30 + x > 0.0f) {
                if (bits >= 0) {
                    bits = 0;
                } else if ((bits & 0x7fffffff) != 0) {
                    bits = 0xbf800000;
                }
            }
        } else {
            fraction_mask = 0x7fffff >> exponent;
            if ((bits & fraction_mask) == 0) {
                return x;
            }
            if (ten_to_30 + x > 0.0f) {
                if (bits < 0) {
                    bits += 0x800000 >> exponent;
                }
                bits &= ~fraction_mask;
            }
        }
    } else {
        if (exponent == 0x80) {
            return x + x;
        }
        return x;
    }
    *(s32*)&x = bits;
    return x;
}
