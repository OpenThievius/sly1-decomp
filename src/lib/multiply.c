/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The 64-bit product (__muldi3 in config/us/libcalls.tsv), its own object in retail. C, built
 * by the Linux cc1 of 2.9-ee-991111 (config/cflags.tsv, docs/TOOLCHAIN.md): the compiler issues
 * the second cross product as mult1, to the EE's second pipeline. The low halves multiply with
 * MUL_WIDE (include/mul_wide.h), as the division files do. Written for this project from
 * retail's code. */
#include "mul_wide.h"

typedef unsigned int u32;
typedef int s32;
typedef long long s64;

typedef union {
    s64 all;
    struct {
        u32 lo;
        s32 hi;
    } h;
} Halves;

s64 func_001FE890(s64 u, s64 v)
{
    Halves uu, vv, w;

    uu.all = u;
    vv.all = v;
    MUL_WIDE(w.h.hi, w.h.lo, uu.h.lo, vv.h.lo);
    w.h.hi += (u32)uu.h.lo * (u32)vv.h.hi + (u32)uu.h.hi * (u32)vv.h.lo;
    return w.all;
}
