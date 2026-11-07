/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A signed 64-bit integer converted to a float, rounded once, one of the toolchain runtime's
 * conversion files, each its own object in retail. C, built by the Linux cc1 of 2.9-ee-991111
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"

typedef long long s64_t;
typedef unsigned long long u64_t;

f32 ConvertS64ToFloat(s64_t x)
{
    double f;

    if ((u64_t)(x + 0x1FFFFFFFFFFFFFLL) > 0x3FFFFFFFFFFFFEULL) {
        if ((s32)x & 0x7FF)
            x |= 0x800;
    }
    f = (s32)(x >> 32);
    f *= 65536.0;
    f *= 65536.0;
    f += (u32)(x & 0xFFFFFFFFLL);
    return (f32)f;
}
