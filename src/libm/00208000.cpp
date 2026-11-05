// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "float_bits.h"

f32 func_00209260(f32 x, s32 exp);
f32 func_00205318(f32 x);

extern const s32 D_0024FEC0[4] = { 4, 7, 9, 0 };
extern const f32 D_0024FED0[26] = { 1.5703125f, 0.00045776367f, 2.5987625e-05f, 7.543713e-08f, 6.002665e-11f, 7.3896445e-13f, 5.3845817e-15f, 5.6378513e-18f, 8.300923e-20f, 3.2756352e-22f, 6.3331016e-25f, 0.0f, 1.0f, 256.0f, 0.00390625f, 0.5f, -0.16666667f, 0.008333334f, -0.0001984127f, 2.7557314e-06f, -2.505076e-08f, 1.589691e-10f, 1.0f, 0.7853981f, 3.7748947e-08f, 0.0f };

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
void func_001FD308(Key_00208FE8 a, Key_00208FE8 b);

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

f32 func_00208C48(s32 flag, f32 x, f32 y)
{
    s32 hx;
    s32 ix;
    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix <= 0x31FFFFFF && (s32)x == 0)
        return x;
    f32 z = x * x;
    f32 v = z * x;
    f32 r = z * (z * (z * (z * 1.58969102e-10f + -2.50507597e-08f) + 2.75573143e-06f) + -0.000198412701f) + 0.00833333377f;
    if (flag == 0)
        return x + v * (z * r + -0.166666672f);
    return x - ((z * (y * 0.5f - v * r) - y) - v * -0.166666672f);
}

u32 func_00209238(f32 x)
{
    s32 ix;
    FLOAT_TO_BITS(ix, x);
    ix &= 0x7FFFFFFF;
    ix = 0x7F800000 - ix;
    return (u32)ix >> 31;
}

f32 func_002093C0(f32 mag, f32 sign)
{
    s32 m, s;
    FLOAT_TO_BITS(m, mag);
    FLOAT_TO_BITS(s, sign);
    BITS_TO_FLOAT(mag, (m & 0x7FFFFFFF) | (s & 0x80000000));
    return mag;
}

f32 func_00208068(f32 x)
{
    s32 hx;
    FLOAT_TO_BITS(hx, x);
    if ((hx & 0x7F800000) == 0x7F800000)
        return x * x + x;
    if (hx <= 0) {
        if ((hx & 0x7FFFFFFF) == 0)
            return x;
        if (hx < 0)
            return (x - x) / (x - x);
    }
    s32 ix = hx >> 23;
    s32 i;
    if (ix == 0) {
        for (i = 0; (hx & 0x800000) == 0; i++)
            hx <<= 1;
        ix -= i - 1;
    }
    ix -= 127;
    hx = (hx & 0x7FFFFF) | 0x800000;
    hx <<= ix & 1;
    hx <<= 1;
    ix >>= 1;
    s32 s = 0;
    s32 r = 0;
    s32 t;
    s32 m = 0x1000000;
    while (m != 0) {
        t = s + m;
        if (t <= hx) {
            s = t + m;
            hx -= t;
            r += m;
        }
        hx <<= 1;
        m = (u32)m >> 1;
    }
    if (hx != 0)
        r += r & 1;
    hx = (r >> 1) + 0x3F000000;
    f32 res;
    BITS_TO_FLOAT(res, hx + (ix << 23));
    return res;
}

f32 func_002081A0(f32 x, f32 y)
{
    s32 hx;
    s32 ix;
    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix <= 0x31FFFFFF && (s32)x == 0)
        return 1.0f;
    f32 z = x * x;
    f32 r = z * (z * (z * (z * (z * -1.13596476e-11f + 2.08757234e-09f) + -2.75573143e-07f) + 2.48015876e-05f) + -0.00138888892f) + 0.0416666679f;
    f32 v = z * r;
    if (ix <= 0x3E999999)
        return 1.0f - (0.5f * z - (z * v - x * y));
    f32 qs;
    if (ix > 0x3F480000)
        qs = 0.28125f;
    else
        BITS_TO_FLOAT(qs, ix - 0x01000000);
    return (1.0f - qs) - ((0.5f * z - qs) - (z * v - x * y));
}

f32 func_002093C0(f32 scale, f32 value);

f32 func_00209260(f32 x, s32 n)
{
    s32 ix, hx, k;

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
        return func_002093C0(1e30f, x) * 1e30f;
    }
    if (k > 0) {
        BITS_TO_FLOAT(x, (hx & 0x807FFFFF) | (k << 23));
        return x;
    }
    if (k < -24) {
        if (n > 50000) return func_002093C0(1e30f, x) * 1e30f;
        return func_002093C0(1e-30f, x) * 1e-30f;
    }
    k += 25;
    BITS_TO_FLOAT(x, (hx & 0x807FFFFF) | (k << 23));
    return x * 2.9802322387695312e-08f;
}

f32 func_002052F8(f32 x);

extern const f32 D_0024FF38[14] = { 0.33333334f, 0.13333334f, 0.053968254f, 0.021869488f, 0.00886324f, 0.003592079f, 0.0014562095f, 0.00058804126f, 0.00024646314f, 7.8179444e-05f, 7.140725e-05f, -1.8558638e-05f, 2.5907306e-05f, 0.0f };

f32 func_00208D50(f32 x, f32 y, s32 k)
{
    s32 hx, ix, zb;
    f32 z, w, r, v, s, t, a;

    FLOAT_TO_BITS(hx, x);
    ix = hx & 0x7FFFFFFF;
    if (ix <= 0x317FFFFF) {
        if ((s32)x == 0) {
            if ((ix | (k + 1)) == 0) {
                return 1.0f / func_002052F8(x);
            }
            if (k != 1) {
                return -1.0f / x;
            }
            return x;
        }
    }
    if (ix > 0x3F2CA13F) {
        if (hx < 0) {
            x = -x;
            y = -y;
        }
        z = 0.7853981256484985f - x;
        w = 3.774894707930798e-08f - y;
        x = z + w;
        y = 0.0f;
    }
    z = x * x;
    w = z * z;
    r = D_0024FF38[1] + w * (D_0024FF38[3] + w * (D_0024FF38[5] + w * (D_0024FF38[7] + w * (D_0024FF38[9] + w * D_0024FF38[11]))));
    v = z * (D_0024FF38[2] + w * (D_0024FF38[4] + w * (D_0024FF38[6] + w * (D_0024FF38[8] + w * (D_0024FF38[10] + w * D_0024FF38[12])))));
    s = z * x;
    r = y + z * (s * (r + v) + y);
    r += D_0024FF38[0] * s;
    w = x + r;
    if (ix > 0x3F2CA13F) {
        v = (f32)k;
        return (f32)(1 - ((hx >> 30) & 2)) * (v - 2.0f * (x - (w * w / (w + v) - r)));
    }
    if (k == 1) {
        return w;
    }
    FLOAT_TO_BITS(zb, w);
    BITS_TO_FLOAT(z, zb & 0xFFFFF000);
    v = r - (z - x);
    t = -1.0f / w;
    FLOAT_TO_BITS(zb, t);
    BITS_TO_FLOAT(a, zb & 0xFFFFF000);
    s = 1.0f + a * z;
    return a + t * (s + a * v);
}

extern const double D_0024FF80[];
double func_001FCD20(double a, double b);
double func_001FCD78(double a, double b);

double func_00209010(double x)
{
    s32 hi, lo, e, sign;
    u32 m;
    double t;

    DOUBLE_TO_WORDS(hi, lo, x);
    sign = (u32)hi >> 31;
    e = ((hi >> 20) & 0x7FF) - 0x3FF;
    if (e < 20) {
        if (e < 0) {
            if (((hi & 0x7FFFFFFF) | lo) == 0) return x;
            lo |= hi & 0xFFFFF;
            hi &= 0xFFFE0000;
            hi |= ((u32)(lo | -lo) >> 12) & 0x80000;
            SET_DOUBLE_HIGH(x, hi);
            double w = D_0024FF80[sign];
            double y = func_001FCD78(func_001FCD20(w, x), w);
            DOUBLE_HIGH(hi, y);
            SET_DOUBLE_HIGH(y, (hi & 0x7FFFFFFF) | (sign << 31));
            return y;
        }
        m = 0xFFFFF >> e;
        if (((hi & m) | lo) == 0) return x;
        m >>= 1;
        if (((hi & m) | lo) != 0) {
            if (e == 19) lo = 0x40000000;
            else hi = (hi & ~m) | (0x20000 >> e);
        }
    } else if (e >= 52) {
        if (e == 0x400) return func_001FCD20(x, x);
        return x;
    } else {
        m = 0xFFFFFFFFu >> (e - 20);
        if ((lo & m) == 0) return x;
        m >>= 1;
        if ((lo & m) != 0) lo = (lo & ~m) | (0x40000000 >> (e - 20));
    }
    WORDS_TO_DOUBLE(x, hi, lo);
    t = D_0024FF80[sign];
    return func_001FCD78(func_001FCD20(t, x), t);
}
