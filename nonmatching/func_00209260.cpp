// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 336/352 (95.5%), checked 2026-11-02
#include "float_bits.h"

f32 func_002093C0(f32 scale, f32 value);

f32 func_00209260(f32 x, s32 n)
{
    s32 ix, hx, k;
    f32 s;

    FLOAT_TO_BITS(ix, x);
    hx = ix;
    k = (hx & 0x7F800000) >> 23;
    if (k == 0) {
        if ((hx & 0x7FFFFFFF) == 0) return x;
        x *= 33554432.0f;
        FLOAT_TO_BITS(ix, x);
        hx = ix;
        k = ((hx & 0x7F800000) >> 23) - 25;
        if (n < -50000) return 1e-30f * x;
    }
    if (k == 0xFF) return x + x;
    k = k + n;
    if (k > 0xFE) {
        s = 1e30f;
        return func_002093C0(s, x) * s;
    }
    if (k > 0) {
        BITS_TO_FLOAT(x, (hx & 0x807FFFFF) | (k << 23));
        return x;
    }
    if (k < -24) {
        s = (50000 < n) ? 1e30f : 1e-30f;
        return func_002093C0(s, x) * s;
    }
    k += 25;
    BITS_TO_FLOAT(x, (hx & 0x807FFFFF) | (k << 23));
    return x * 2.9802322387695312e-08f;
}
