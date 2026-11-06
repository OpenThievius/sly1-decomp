/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A signed 64-bit integer converted to a double, one of the toolchain runtime's conversion
 * files, each its own object in retail. C, built by the Linux cc1 of 2.9-ee-991111
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"

typedef long long s64_t;

double func_001FB618(s64_t x)
{
    double d = (s32)(x >> 32);

    d *= 65536.0;
    d *= 65536.0;
    d += (u32)(x & 0xFFFFFFFFLL);
    return d;
}
