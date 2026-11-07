/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A double converted to an unsigned 64-bit integer, one of the toolchain runtime's conversion
 * files, each its own object in retail. C, built by the Linux cc1 of 2.9-ee-991111
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"

typedef unsigned long long u64_t;
typedef long long s64_t;

u32 func_001FD4A8(double a);
double func_001FB618(s64_t x);

u64_t func_001FB528(double a)
{
    double t;
    u64_t v;

    if (a < 0)
        return 0;
    v = ConvertDoubleToU32(a * (1.0 / 4294967296.0));
    v <<= 32;
    if ((s64_t)v >= 0) {
        t = ConvertS64ToDouble(v);
    } else {
        t = ConvertS64ToDouble((v & 1) | (v >> 1));
        t = t + t;
    }
    a -= t;
    if (a < 0)
        v -= ConvertDoubleToU32(-a);
    else
        v += ConvertDoubleToU32(a);
    return v;
}
