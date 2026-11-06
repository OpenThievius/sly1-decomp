/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The toolchain runtime's software floating point: a double taken apart, for the double routines
 * of src/lib/001FC000.cpp. C, built by cc1 (config/cflags.tsv), as the runtime was compiled
 * (docs/TOOLCHAIN.md). Written for this project from retail's code. FLUSH_TINY is the runtime's
 * build switch that reads denormals as zero: the code it disables leaves its loop's alignment in
 * retail. */
#include "common.h"

/* A double taken apart: its kind, sign, unbiased exponent and fraction. */
typedef struct Unpacked {
    s32 kind;
    s32 sign;
    s32 exponent;
    s32 pad;
    u64 fraction;
} Unpacked;

/* Tiny values read as zero. */
#define FLUSH_TINY 1

void func_001FCA40(u64* in, Unpacked* out)
{
    u64 bits = *in;
    u64 fraction = bits & 0x000FFFFFFFFFFFFFull;
    s32 exponent = (s32)(bits >> 52) & 0x7FF;

    out->sign = (s32)(bits >> 63);
    if (exponent == 0) {
        if (FLUSH_TINY || fraction == 0) {
            out->kind = 2;
        } else {
            out->kind = 3;
            exponent -= 0x3FE;
            fraction <<= 8;
            while (fraction < 0x1000000000000000ull) {
                fraction <<= 1;
                exponent--;
            }
            out->exponent = exponent;
            out->fraction = fraction;
        }
    } else if (exponent == 0x7FF) {
        if (fraction == 0) {
            out->kind = 4;
        } else {
            if (fraction & 0x0008000000000000ull)
                out->kind = 1;
            else
                out->kind = 0;
            out->fraction = fraction;
        }
    } else {
        out->exponent = exponent - 0x3FF;
        out->kind = 3;
        out->fraction = (fraction << 8) | 0x1000000000000000ull;
    }
}
