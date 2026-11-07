/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The reduction of a large float argument by pi / 2 on a table of the digits of 2 / pi, 8 bits to a float. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const s32 terms_for_precision[] = { 4, 7, 9 };

static const f32 half_pi_parts[] = {
    1.5703125000e+00f, 4.5776367188e-04f, 2.5987625122e-05f, 7.5437128544e-08f,
    6.0026650317e-11f, 7.3896444519e-13f, 5.3845816694e-15f, 5.6378512969e-18f,
    8.3009228831e-20f, 3.2756352257e-22f, 6.3331015649e-25f,
};

static const f32 zero = 0.0f;
static const f32 one = 1.0f;
static const f32 f256 = 2.5600000000e+02f;
static const f32 f1_256 = 3.9062500000e-03f;

f32 func_00209260(f32 x, s32 n);
f32 func_00205318(f32 x);

s32 func_002082F8(f32* x, f32* y, s32 e0, s32 nx, s32 prec, const s32* table)
{
    s32 jz, jx, jv, jk, carry, n, iq[20], i, j, k, m, q0, ih;
    f32 z, fw, f[20], fq[20], q[20];

    jv = (e0 - 3) / 8;
    if (jv < 0) {
        jv = 0;
    }
    q0 = e0 - 8 * (jv + 1);

    jk = terms_for_precision[prec];

    jx = nx - 1;
    j = jv - jx;
    m = jx + jk;
    for (i = 0; i <= m; i++, j++) {
        f[i] = (j < 0) ? zero : (f32)table[j];
    }

    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = zero; j <= jx; j++) {
            fw += x[j] * f[jx + i - j];
        }
        q[i] = fw;
    }

    jz = jk;
recompute:
    for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
        fw = (f32)(s32)(f1_256 * z);
        iq[i] = (s32)(z - f256 * fw);
        z = q[j - 1] + fw;
    }

    z = func_00209260(z, q0);
    z -= 8.0f * func_00205318(z * 0.125f);
    n = (s32)z;
    z -= (f32)n;
    ih = 0;
    if (q0 > 0) {
        i = iq[jz - 1] >> (8 - q0);
        n += i;
        iq[jz - 1] -= i << (8 - q0);
        ih = iq[jz - 1] >> (7 - q0);
    } else if (q0 == 0) {
        ih = iq[jz - 1] >> 8;
    } else if (z >= 0.5f) {
        ih = 2;
    }

    if (ih > 0) {
        n += 1;
        carry = 0;
        for (i = 0; i < jz; i++) {
            j = iq[i];
            if (carry == 0) {
                if (j != 0) {
                    carry = 1;
                    iq[i] = 0x100 - j;
                }
            } else {
                iq[i] = 0xFF - j;
            }
        }
        if (q0 > 0) {
            switch (q0) {
            case 1:
                iq[jz - 1] &= 0x7F;
                break;
            case 2:
                iq[jz - 1] &= 0x3F;
                break;
            }
        }
        if (ih == 2) {
            z = one - z;
            if (carry != 0) {
                z -= func_00209260(one, q0);
            }
        }
    }

    if (z == zero) {
        j = 0;
        for (i = jz - 1; i >= jk; i--) {
            j |= iq[i];
        }
        if (j == 0) {
            for (k = 1; iq[jk - k] == 0; k++) {
            }
            for (i = jz + 1; i <= jz + k; i++) {
                f[jx + i] = (f32)table[jv + i];
                for (j = 0, fw = zero; j <= jx; j++) {
                    fw += x[j] * f[jx + i - j];
                }
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }

    if (z == zero) {
        jz -= 1;
        q0 -= 8;
        while (iq[jz] == 0) {
            jz--;
            q0 -= 8;
        }
    } else {
        z = func_00209260(z, -q0);
        if (z >= f256) {
            fw = (f32)(s32)(f1_256 * z);
            iq[jz] = (s32)(z - f256 * fw);
            jz += 1;
            q0 += 8;
            iq[jz] = (s32)fw;
        } else {
            iq[jz] = (s32)z;
        }
    }

    fw = func_00209260(one, q0);
    for (i = jz; i >= 0; i--) {
        q[i] = fw * (f32)iq[i];
        fw *= f1_256;
    }

    for (i = jz; i >= 0; i--) {
        for (fw = zero, k = 0; k <= jk && k <= jz - i; k++) {
            fw += half_pi_parts[k] * q[i + k];
        }
        fq[jz - i] = fw;
    }

    switch (prec) {
    case 0:
        fw = zero;
        for (i = jz; i >= 0; i--) {
            fw += fq[i];
        }
        y[0] = (ih == 0) ? fw : -fw;
        break;
    case 1:
    case 2:
        fw = zero;
        for (i = jz; i >= 0; i--) {
            fw += fq[i];
        }
        y[0] = (ih == 0) ? fw : -fw;
        fw = fq[0] - fw;
        for (i = 1; i <= jz; i++) {
            fw += fq[i];
        }
        y[1] = (ih == 0) ? fw : -fw;
        break;
    case 3:
        for (i = jz; i > 0; i--) {
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (i = jz; i > 1; i--) {
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (fw = zero, i = jz; i >= 2; i--) {
            fw += fq[i];
        }
        if (ih == 0) {
            y[0] = fq[0];
            y[1] = fq[1];
            y[2] = fw;
        } else {
            y[0] = -fq[0];
            y[1] = -fq[1];
            y[2] = -fw;
        }
        break;
    }
    return n & 7;
}
