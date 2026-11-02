// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "float_bits.h"

f32 func_00209260(f32 x, s32 exp);
f32 func_00205318(f32 x);

extern const s32 D_0024FEC0[];
extern const f32 D_0024FED0[];

s32 func_002082F8(f32* x, f32* y, s32 e0, s32 nx, s32 prec, const s32* table)
{
    s32 jz, jx, jv, jk, carry, n, iq[20], i, j, k, m, q0, ih;
    f32 z, fw, f[20], fq[20], q[20];

    jv = (e0 - 3) / 8;
    if (jv < 0) {
        jv = 0;
    }
    q0 = e0 - 8 * (jv + 1);

    jk = D_0024FEC0[prec];

    jx = nx - 1;
    j = jv - jx;
    m = jx + jk;
    for (i = 0; i <= m; i++, j++) {
        f[i] = (j < 0) ? 0.0f : (f32)table[j];
    }

    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = 0.0f; j <= jx; j++) {
            fw += x[j] * f[jx + i - j];
        }
        q[i] = fw;
    }

    jz = jk;
recompute:
    for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
        fw = (f32)(s32)(0.00390625f * z);
        iq[i] = (s32)(z - 256.0f * fw);
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
            z = 1.0f - z;
            if (carry != 0) {
                z -= func_00209260(1.0f, q0);
            }
        }
    }

    if (z == 0.0f) {
        j = 0;
        for (i = jz - 1; i >= jk; i--) {
            j |= iq[i];
        }
        if (j == 0) {
            for (k = 1; iq[jk - k] == 0; k++) {
            }
            for (i = jz + 1; i <= jz + k; i++) {
                f[jx + i] = (f32)table[jv + i];
                for (j = 0, fw = 0.0f; j <= jx; j++) {
                    fw += x[j] * f[jx + i - j];
                }
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }

    if (z == 0.0f) {
        jz -= 1;
        q0 -= 8;
        while (iq[jz] == 0) {
            jz--;
            q0 -= 8;
        }
    } else {
        z = func_00209260(z, -q0);
        if (z >= 256.0f) {
            fw = (f32)(s32)(0.00390625f * z);
            iq[jz] = (s32)(z - 256.0f * fw);
            jz += 1;
            q0 += 8;
            iq[jz] = (s32)fw;
        } else {
            iq[jz] = (s32)z;
        }
    }

    fw = func_00209260(1.0f, q0);
    for (i = jz; i >= 0; i--) {
        q[i] = fw * (f32)iq[i];
        fw *= 0.00390625f;
    }

    for (i = jz; i >= 0; i--) {
        for (fw = 0.0f, k = 0; k <= jk && k <= jz - i; k++) {
            fw += D_0024FED0[k] * q[i + k];
        }
        fq[jz - i] = fw;
    }

    switch (prec) {
    case 0:
        fw = 0.0f;
        for (i = jz; i >= 0; i--) {
            fw += fq[i];
        }
        y[0] = (ih == 0) ? fw : -fw;
        break;
    case 1:
    case 2:
        fw = 0.0f;
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
        for (fw = 0.0f, i = jz; i >= 2; i--) {
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

struct Obj_00208FE8 { u8 pad[8]; s64 f8; };
typedef s64 Key_00208FE8;
s32 func_001FD308(Key_00208FE8 a, Key_00208FE8 b);

s32 func_00208FE8(Obj_00208FE8* obj)
{
    Key_00208FE8 v = obj->f8;
    (void)func_001FD308(v, v);
    return 0;
}

u32 func_00209210(f32 x)
{
    s32 bits;
    FLOAT_TO_BITS(bits, x);
    return (u32)((bits & 0x7FFFFFFF) + 0x80800000) >> 31;
}
