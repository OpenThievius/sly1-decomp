/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The signed remainder (__moddi3), with the sign of the dividend. One of the toolchain runtime's division files, each its
 * own object in retail with its own table (include/divide.h). C, built by the Linux cc1 of
 * 2.9-ee-991111 (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's
 * code. */
#include "divide.h"

s64 func_001FB790(s64 num, s64 den)
{
    int neg = 0;
    Halves nn, dd;
    s64 rem;

    nn.all = num;
    dd.all = den;
    if (nn.h.hi < 0) {
        neg = ~neg;
        nn.all = negate(nn.all);
    }
    if (dd.h.hi < 0)
        dd.all = negate(dd.all);
    divide(nn.all, dd.all, (u64*)&rem);
    if (neg)
        rem = negate(rem);
    return rem;
}
