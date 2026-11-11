/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The toolchain runtime's software floating point, double precision: the whole object,
 * 0x1FC910-0x1FD5D0 (pack, add, subtract, compare, multiply, divide, and the conversions to and
 * from integers and single precision). A double travels as its 64 bits. C, built by cc1
 * (config/cflags.tsv), as the runtime was compiled (docs/TOOLCHAIN.md). Written for this project
 * from retail's code. FLUSH_TINY is the runtime's build switch that reads denormals as zero: the
 * code it disables leaves its loop's alignment in retail. */
#include "common.h"

/* A double taken apart: its kind (0 signalling NaN, 1 quiet NaN, 2 zero, 3 finite, 4 infinity),
 * sign, unbiased exponent and fraction. */
typedef struct Unpacked {
    u32 kind;
    s32 sign;
    s32 exponent;
    s32 pad;
    union {
        u64 ll;
        u32 l[2];
    } fraction;
} Unpacked;

#define IS_NAN(p) ((p)->kind < 2)
#define IS_ZERO(p) (((p)->kind ^ 2) == 0)
#define IS_INF(p) (((p)->kind ^ 4) == 0)

/* The NaN that an invalid operation returns. */
static Unpacked D_0062A770;

/* Tiny values read as zero. */
#define FLUSH_TINY 1

u64 PackDouble(Unpacked* p)
{
    union {
        u64 u;
        struct {
            u64 mant : 52;
            u64 expo : 11;
            u64 sign : 1;
        } b;
    } bits;
    u64 mant = p->fraction.ll;
    s32 expo = 0;
    u32 sign = p->sign;

    if (IS_NAN(p)) {
        expo = 0x7FF;
        mant = mant | ((u64)1 << 51);
    } else if (IS_INF(p)) {
        expo = 0x7FF;
        mant = 0;
    } else if (IS_ZERO(p)) {
        mant = 0;
    } else if (mant != 0) {
        s32 e = p->exponent;
        if (e < -0x3FE) {
            s32 sh = -0x3FE - e;
            if (sh > 0x38) {
                mant = 0;
            } else {
                mant = mant >> sh;
            }
            mant = mant >> 8;
        } else if (e >= 0x400) {
            expo = 0x7FF;
            mant = 0;
        } else {
            expo = e + 0x3FF;
            if ((mant & 0xFF) == 0x80) {
                if ((mant & 0x100) != 0) {
                    mant = mant + 0x80;
                }
            } else {
                mant = mant + 0x7F;
            }
            if (mant > 0x1FFFFFFFFFFFFFFFull) {
                mant = mant >> 1;
                expo = expo + 1;
            }
            mant = mant >> 8;
        }
    }

    bits.b.mant = mant;
    bits.b.expo = expo;
    bits.b.sign = sign;
    return bits.u;
}

void UnpackDouble(u64* in, Unpacked* out)
{
    u64 bits = *in;
    u64 fraction = bits & 0x000FFFFFFFFFFFFFull;
    s32 exponent = (s32)(bits >> 52) & 0x7FF;

    out->sign = (s32)(bits >> 63);
    if (exponent == 0) {
        if (FLUSH_TINY || fraction == 0) {
            out->kind = 2;
        } else {
            out->kind = 3;
            exponent -= 0x3FE;
            fraction <<= 8;
            while (fraction < 0x1000000000000000ull) {
                fraction <<= 1;
                exponent--;
            }
            out->exponent = exponent;
            out->fraction.ll = fraction;
        }
    } else if (exponent == 0x7FF) {
        if (fraction == 0) {
            out->kind = 4;
        } else {
            if (fraction & 0x0008000000000000ull)
                out->kind = 1;
            else
                out->kind = 0;
            out->fraction.ll = fraction;
        }
    } else {
        out->exponent = exponent - 0x3FF;
        out->kind = 3;
        out->fraction.ll = (fraction << 8) | 0x1000000000000000ull;
    }
}

Unpacked* AddUnpackedDoubles(Unpacked* a, Unpacked* b, Unpacked* tmp)
{
    s32 ae, be;
    u64 af, bf;
    s64 tf;
    s32 diff;

    if (IS_NAN(a)) return a;
    if (IS_NAN(b)) return b;
    if (IS_INF(a)) {
        if (IS_INF(b) && a->sign != b->sign) return &D_0062A770;
        return a;
    }
    if (IS_INF(b)) return b;
    if (IS_ZERO(b)) {
        if (IS_ZERO(a)) {
            *tmp = *a;
            tmp->sign = a->sign & b->sign;
            return tmp;
        }
        return a;
    }
    if (IS_ZERO(a)) return b;

    ae = a->exponent;
    be = b->exponent;
    af = a->fraction.ll;
    bf = b->fraction.ll;
    diff = ae - be;
    if (diff < 0) diff = -diff;
    if (diff < 64) {
        while (ae > be) {
            be++;
            bf = (bf & 1) | (bf >> 1);
        }
        while (be > ae) {
            ae++;
            af = (af & 1) | (af >> 1);
        }
    } else {
        if (ae > be) {
            bf = 0;
        } else {
            ae = be;
            af = 0;
        }
    }
    if (a->sign != b->sign) {
        if (a->sign) tf = -af + bf;
        else tf = af - bf;
        if (tf >= 0) {
            tmp->sign = 0;
            tmp->exponent = ae;
            tmp->fraction.ll = tf;
        } else {
            tmp->sign = 1;
            tmp->exponent = ae;
            tmp->fraction.ll = -tf;
        }
        while (tmp->fraction.ll < 0x1000000000000000ULL && tmp->fraction.ll) {
            tmp->fraction.ll <<= 1;
            tmp->exponent--;
        }
    } else {
        tmp->sign = a->sign;
        tmp->exponent = ae;
        tmp->fraction.ll = af + bf;
    }
    tmp->kind = 3;
    if (tmp->fraction.ll >= 0x2000000000000000ULL) {
        tmp->fraction.ll = (tmp->fraction.ll & 1) | (tmp->fraction.ll >> 1);
        tmp->exponent++;
    }
    return tmp;
}

u64 AddDoubles(u64 pa, u64 pb)
{
    Unpacked a;
    Unpacked b;
    Unpacked c;

    UnpackDouble(&pa, &a);
    UnpackDouble(&pb, &b);
    return PackDouble(AddUnpackedDoubles(&a, &b, &c));
}

u64 SubtractDoubles(u64 pa, u64 pb)
{
    Unpacked a;
    Unpacked b;
    Unpacked c;

    UnpackDouble(&pa, &a);
    UnpackDouble(&pb, &b);
    b.sign ^= 1;
    return PackDouble(AddUnpackedDoubles(&a, &b, &c));
}

u64 MultiplySigned64(u64 a, u64 b);
static inline Unpacked* Multiply(Unpacked* a, Unpacked* b, Unpacked* tmp)
{
    u64 high;
    u64 low;
    u64 alo, ahi, blo, bhi;
    u64 p0, p1, p2, p3;
    u64 mid, hi, lo;

    if (IS_NAN(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (IS_NAN(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    if (IS_INF(a)) {
        if (IS_ZERO(b)) {
            return (Unpacked*)&D_0062A770;
        }
        a->sign = a->sign != b->sign;
        return a;
    }
    if (IS_INF(b)) {
        if (IS_ZERO(a)) {
            return (Unpacked*)&D_0062A770;
        }
        b->sign = a->sign != b->sign;
        return b;
    }
    if (IS_ZERO(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (IS_ZERO(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    alo = a->fraction.ll & 0xFFFFFFFF;
    ahi = a->fraction.ll >> 32;
    blo = b->fraction.ll & 0xFFFFFFFF;
    bhi = b->fraction.ll >> 32;
    p0 = MultiplySigned64(blo, alo);
    p1 = MultiplySigned64(bhi, alo);
    p2 = MultiplySigned64(blo, ahi);
    p3 = MultiplySigned64(bhi, ahi);
    mid = p1 + p2;
    hi = 0;
    if (mid < p1) {
        hi += (u64)1 << 32;
    }
    lo = p0 + (mid << 32);
    if (lo < p0) {
        hi++;
    }
    hi += ((mid >> 32) & 0xFFFFFFFF) + p3;
    high = hi;
    low = lo;
    tmp->exponent = a->exponent + b->exponent;
    tmp->sign = a->sign != b->sign;
    tmp->exponent += 4;
    while (high > (~(u64)0 >> 3)) {
        tmp->exponent++;
        if (high & 1) {
            low >>= 1;
            low |= 0x8000000000000000ull;
        }
        high >>= 1;
    }
    while (high <= (~(u64)0 >> 4)) {
        tmp->exponent--;
        high <<= 1;
        if (low & 0x8000000000000000ull) {
            high |= 1;
        }
        low <<= 1;
    }
    if ((high & 0xFF) == 0x80) {
        if (high & 0x100) {
            high += 0x80;
        } else if (low) {
            high += 0x80;
        }
    }
    tmp->fraction.ll = high;
    tmp->kind = 3;
    return tmp;
}

u64 MultiplyDoubles(u64 x, u64 y)
{
    Unpacked a;
    Unpacked b;
    Unpacked tmp;
    u64 xa;
    u64 xb;

    xa = x;
    xb = y;
    UnpackDouble(&xa, &a);
    UnpackDouble(&xb, &b);
    return PackDouble((Unpacked*)Multiply(&a, &b, &tmp));
}


static inline Unpacked* Divide(Unpacked* a, Unpacked* b)
{
    u64 rem;
    u64 div;
    u64 bit;
    u64 quo;

    if (IS_NAN(a)) {
        return a;
    }
    if (IS_NAN(b)) {
        return b;
    }
    a->sign ^= b->sign;
    if (IS_INF(a) || IS_ZERO(a)) {
        if (a->kind == b->kind) {
            return &D_0062A770;
        }
        return a;
    }
    if (IS_INF(b)) {
        a->fraction.ll = 0;
        a->exponent = 0;
        return a;
    }
    if (IS_ZERO(b)) {
        a->kind = 4;
        return a;
    }
    a->exponent = a->exponent - b->exponent;
    rem = a->fraction.ll;
    div = b->fraction.ll;
    if (rem < div) {
        a->exponent--;
        rem <<= 1;
    }
    bit = (u64)1 << 60;
    quo = 0;
    while (bit) {
        if (rem >= div) {
            quo |= bit;
            rem -= div;
        }
        bit >>= 1;
        rem <<= 1;
    }
    if ((quo & 0xFF) == 0x80) {
        if (quo & 0x100) {
            quo += 0x80;
        } else if (rem) {
            quo += 0x80;
        }
    }
    a->fraction.ll = quo;
    return a;
}

u64 DivideDoubles(u64 x, u64 y)
{
    Unpacked pa;
    Unpacked pb;

    UnpackDouble(&x, &pa);
    UnpackDouble(&y, &pb);
    return PackDouble((Unpacked*)Divide(&pa, &pb));
}

s32 CompareUnpackedDoubles(Unpacked* a, Unpacked* b)
{
    if (a->kind < 2) {
        return 1;
    }
    if (b->kind < 2) {
        return 1;
    }
    if ((a->kind ^ 4) == 0) {
        if ((b->kind ^ 4) == 0) {
            return b->sign - a->sign;
        }
        return a->sign != 0 ? -1 : 1;
    }
    if ((b->kind ^ 4) == 0) {
        return b->sign != 0 ? 1 : -1;
    }
    if ((a->kind ^ 2) == 0) {
        if ((b->kind ^ 2) == 0) {
            return 0;
        }
        return b->sign == 0 ? -1 : 1;
    }
    if ((b->kind ^ 2) == 0) {
        return a->sign != 0 ? -1 : 1;
    }
    if (a->sign != b->sign) {
        return a->sign != 0 ? -1 : 1;
    }
    if (a->exponent > b->exponent) {
        return a->sign != 0 ? -1 : 1;
    }
    if (a->exponent < b->exponent) {
        return a->sign != 0 ? 1 : -1;
    }
    if (a->fraction.ll > b->fraction.ll) {
        return a->sign != 0 ? -1 : 1;
    }
    if (a->fraction.ll < b->fraction.ll) {
        return a->sign != 0 ? 1 : -1;
    }
    return 0;
}

s32 CompareDoubles(u64 pa, u64 pb)
{
    Unpacked a;
    Unpacked b;

    UnpackDouble(&pa, &a);
    UnpackDouble(&pb, &b);
    return CompareUnpackedDoubles(&a, &b);
}

u64 ConvertS32ToDouble(s32 value)
{
    Unpacked parts;
    u64 m;
    s32 e;
    u64 n;

    parts.kind = 3;
    parts.sign = (u32)value >> 31;
    if (value == 0) {
        parts.kind = 2;
    } else {
        parts.exponent = 0x3C;
        if (parts.sign != 0) {
            if (value == (s32)0x80000000) {
                return 0xC1E0000000000000ULL;
            }
            parts.fraction.ll = (s32)-value;
        } else {
            parts.fraction.ll = value;
        }
        m = parts.fraction.ll;
        if (m <= 0x0FFFFFFFFFFFFFFFULL) {
            e = parts.exponent;
            do {
                n = m << 1;
                e--;
                m = n;
            } while (n <= 0x0FFFFFFFFFFFFFFFULL);
            parts.exponent = e;
            parts.fraction.ll = m;
        }
    }
    return PackDouble(&parts);
}

s32 ConvertDoubleToS32(u64 value)
{
    u64 in = value;
    Unpacked out;
    s32 v;

    UnpackDouble(&in, &out);
    if ((out.kind ^ 2) == 0) {
        return 0;
    }
    if (out.kind < 2) {
        return 0;
    }
    if ((out.kind ^ 4) == 0) {
        goto saturate;
    }
    if (out.exponent < 0) {
        return 0;
    }
    if (out.exponent < 0x1F) {
        goto compute;
    }
saturate:
    return (out.sign != 0) ? (s32)0x80000000 : 0x7FFFFFFF;
compute:
    v = (s32)(out.fraction.ll >> (0x3C - out.exponent));
    if (out.sign != 0) {
        v = -v;
    }
    return v;
}

u32 ConvertDoubleToU32(u64 value)
{
    Unpacked d;
    u64 b;
    s32 e;

    b = value;
    UnpackDouble(&b, &d);
    if ((d.kind ^ 2) == 0) {
        return 0;
    }
    if (d.kind < 2) {
        return 0;
    }
    if (d.sign != 0) {
        return 0;
    }
    if ((d.kind ^ 4) == 0) {
        return 0xFFFFFFFF;
    }
    if (d.exponent < 0) {
        return 0;
    }
    if (d.exponent >= 0x20) {
        return 0xFFFFFFFF;
    }
    e = d.exponent;
    if (e >= 0x3D) {
        return (u32)(d.fraction.ll << (e - 0x3C));
    }
    return (u32)(d.fraction.ll >> (0x3C - e));
}

u64 PackDoubleFromParts(s32 a0, s32 a1, s32 a2, u64 a3)
{
    Unpacked args;

    args.kind = a0;
    args.sign = a1;
    args.exponent = a2;
    args.fraction.ll = a3;
    return PackDouble(&args);
}

f32 PackFloatFromParts(s32 a0, s32 a1, s32 a2, s32 a3);

f32 ConvertDoubleToFloat(u64 bits)
{
    Unpacked u;
    s32 fraction;

    UnpackDouble(&bits, &u);
    fraction = (s32)(u.fraction.ll >> 30) | 1;
    if ((u.fraction.ll & 0x3FFFFFFFULL) == 0) fraction = (s32)(u.fraction.ll >> 30);
    return PackFloatFromParts(u.kind, u.sign, u.exponent, fraction);
}
