// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 970/992 (97.8%), checked 2026-11-02
#include "float_bits.h"

f32 func_002052F8(f32 x);
s32 func_002082F8(f32* x, f32* y, s32 e0, s32 nx, s32 prec, const s32* table);

extern const s32 D_0024FDF0[];
extern const s32 D_0024FAD8[];

s32 func_00207C88(f32 x, f32* y)
{
    s32 hx, ix, hy, n, i, e0, nx;
    f32 z, r, w, t, fn, tx[3];

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix <= 0x3F490FD8) {
        y[0] = x;
        y[1] = 0.0f;
        return 0;
    }
    if (ix <= 0x4016CBE3) {
        if (hx > 0) {
            z = x - 1.5707855224609375f;
            if ((ix & 0xFFFFFFF0) != 0x3FC90FD0) {
                y[0] = z - 1.0804334124259185e-05f;
                y[1] = (z - y[0]) - 1.0804334124259185e-05f;
            } else {
                z -= 1.0804273188114166e-05f;
                y[0] = z - 6.07709993438732e-11f;
                y[1] = (z - y[0]) - 6.07709993438732e-11f;
            }
            return 1;
        } else {
            z = x + 1.5707855224609375f;
            if ((ix & 0xFFFFFFF0) != 0x3FC90FD0) {
                y[0] = z + 1.0804334124259185e-05f;
                y[1] = (z - y[0]) + 1.0804334124259185e-05f;
            } else {
                z += 1.0804273188114166e-05f;
                y[0] = z + 6.07709993438732e-11f;
                y[1] = (z - y[0]) + 6.07709993438732e-11f;
            }
            return -1;
        }
    }
    if (ix <= 0x43490F80) {
        t = func_002052F8(x);
        n = (s32)(t * 0.6366198062896729f + 0.5f);
        fn = (f32)n;
        r = t - fn * 1.5707855224609375f;
        w = fn * 1.0804334124259185e-05f;
        if (n < 32 && (ix & 0xFFFFFF00) != D_0024FDF0[n - 1]) {
            y[0] = r - w;
        } else {
            FLOAT_TO_BITS(hy, r - w);
            BITS_TO_FLOAT(y[0], hy);
            i = (ix >> 23) - (((u32)hy >> 23) & 0xFF);
            if (i > 8) {
                t = r;
                w = fn * 1.0804273188114166e-05f;
                r = t - w;
                w = fn * 6.07709993438732e-11f - ((t - r) - w);
                FLOAT_TO_BITS(hy, r - w);
                BITS_TO_FLOAT(y[0], hy);
                i = (ix >> 23) - (((u32)hy >> 23) & 0xFF);
                if (i > 25) {
                    t = r;
                    w = fn * 6.077094383272197e-11f;
                    r = t - w;
                    w = fn * 6.123234262925839e-17f - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }
        y[1] = (r - y[0]) - w;
        if (hx < 0) {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        }
        return n;
    }
    if (ix > 0x7F7FFFFF) {
        y[0] = x - x;
        y[1] = y[0];
        return 0;
    }
    e0 = (ix >> 23) - 134;
    BITS_TO_FLOAT(z, ix - (e0 << 23));
    for (i = 0; i < 2; i++) {
        tx[i] = (f32)(s32)z;
        z = (z - tx[i]) * 256.0f;
    }
    tx[2] = z;
    nx = 3;
    while (tx[nx - 1] == 0.0f) {
        nx--;
    }
    n = func_002082F8(tx, y, e0, nx, 2, D_0024FAD8);
    if (hx < 0) {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }
    return n;
}
