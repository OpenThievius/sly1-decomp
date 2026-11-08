// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 119/144 (82.6%), checked 2026-11-08
// NEAR: in its file, src/lib/formatted_output.cpp (Sony's 2.9-ee-991111). Left: registers only;
//       retail keeps the bits and the mantissa in $a1 and the exponent in $a2, ours the other
//       way round. Tried: a double parameter read through a union or *(u64*)&, the exponent's
//       bias in the same statement or its own, the negated exponent in a new local or written
//       0 - e, the mantissa in its own local, the two shifts' arms swapped. Night-low1
//       (2026-11-08): the exponent declared first, the bits read with *(u64*)&a, the union's
//       word used throughout with no mantissa local, the exponent and its bias in one
//       initialiser: the same swap (or worse). Written for this
//       project from retail's code.
#include "common.h"

s32 func_001F7390(double a)
{
    union {
        double d;
        u64 u;
    } v;
    u64 m;
    s64 e;

    v.d = a;
    m = v.u;
    e = (m << 1) >> 53;
    e -= 0x433;
    if (e < -0x35) {
        return 0;
    }
    if (e >= 13) {
        return 9999;
    }
    m = ((m << 12) >> 12) | ((u64)1 << 52);
    if (e < 0) {
        e = -e;
        m >>= e - 2;
        if ((m & 3) == 3) {
            m = (m >> 2) + 1;
        } else {
            m >>= 2;
        }
    } else {
        m <<= e;
    }
    return m;
}
