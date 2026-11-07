/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The toolchain runtime's software floating point, single precision: the whole object,
 * 0x1FD5D0-0x1FD8A8 (pack, unpack, the conversion to an unsigned integer, and the entry that
 * packs from loose parts and the one that widens to a double). A single travels as its 32 bits.
 * C, built by cc1 (config/cflags.tsv), as the runtime was compiled (docs/TOOLCHAIN.md). Written
 * for this project from retail's code. */
#include "common.h"
#include "asm_func.h"

/* A single taken apart: its kind (0 signalling NaN, 1 quiet NaN, 2 zero, 3 finite, 4 infinity),
 * sign, unbiased exponent and fraction. */
typedef struct Packed {
    u32 kind;
    s32 sign;
    s32 exp;
    u32 mant;
} Packed;

#define IS_NAN(p) ((p)->kind < 2)
#define IS_ZERO(p) (((p)->kind ^ 2) == 0)
#define IS_INF(p) (((p)->kind ^ 4) == 0)

u64 func_001FD548(s32 a0, s32 a1, s32 a2, u64 a3);

f32 func_001FD5D0(Packed* p)
{
    union {
        f32 f;
        struct {
            u32 mant : 23;
            u32 expo : 8;
            u32 sign : 1;
        } b;
    } bits;
    u32 mant = p->mant;
    s32 expo = 0;
    u32 sign = p->sign;

    if (IS_NAN(p)) {
        expo = 0xFF;
        mant = mant | 0x100000;
    } else if (IS_INF(p)) {
        expo = 0xFF;
        mant = 0;
    } else if (IS_ZERO(p)) {
        mant = 0;
    } else if (mant != 0) {
        s32 e = p->exp;
        if (e < -0x7E) {
            s32 sh = -0x7E - e;
            if (sh > 0x19) {
                mant = 0;
            } else {
                mant = mant >> sh;
            }
            mant = mant >> 7;
        } else if (e >= 0x80) {
            expo = 0xFF;
            mant = 0;
        } else {
            expo = e + 0x7F;
            if ((mant & 0x7F) == 0x40) {
                if ((mant & 0x80) != 0) {
                    mant = mant + 0x40;
                }
            } else {
                mant = mant + 0x3F;
            }
            if ((s32)mant < 0) {
                mant = mant >> 1;
                expo = expo + 1;
            }
            mant = mant >> 7;
        }
    }

    bits.b.mant = mant;
    bits.b.expo = expo;
    bits.b.sign = sign;
    return bits.f;
}

void func_001FD6E0(u32* src, Packed* out)
{
    u32 bits = *src;
    u32 exp = bits >> 23;
    u32 mant = bits & 0x7FFFFF;

    exp &= 0xFF;

    out->sign = bits >> 31;
    if (exp == 0) {
        out->kind = 2;
        return;
    }
    if (exp == 0xFF) {
        if (mant == 0) {
            out->kind = 4;
            return;
        }
        if ((mant & 0x100000) != 0) {
            out->kind = 1;
        } else {
            out->kind = 0;
        }
        out->mant = mant;
        return;
    }
    out->exp = exp - 0x7F;
    out->kind = 3;
    out->mant = (mant << 7) | 0x40000000;
}

LINKER_REMNANT(func_001FD770);

u32 func_001FD7A0(f32 value)
{
    f32 in = value;
    Packed p;

    UnpackFloat((u32*)&in, &p);
    if ((p.kind ^ 2) == 0) {
        return 0;
    }
    if (p.kind < 2) {
        return 0;
    }
    if (p.sign != 0) {
        return 0;
    }
    if ((p.kind ^ 4) == 0) {
        return 0xFFFFFFFFu;
    }
    if (p.exp < 0) {
        return 0;
    }
    if (p.exp >= 0x20) {
        return 0xFFFFFFFFu;
    }
    if (p.exp >= 0x1F) {
        return p.mant << (p.exp - 0x1E);
    }
    return p.mant >> (0x1E - p.exp);
}

f32 func_001FD838(s32 a0, s32 a1, s32 a2, s32 a3)
{
    Packed args;

    args.kind = a0;
    args.sign = a1;
    args.exp = a2;
    args.mant = a3;
    return PackFloat(&args);
}

u64 func_001FD868(f32 x)
{
    Packed v;

    UnpackFloat((u32*)&x, &v);
    return PackDoubleFromParts(v.kind, v.sign, v.exp, (u64)v.mant << 30);
}
