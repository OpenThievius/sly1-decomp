// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Quad_001891C0 { s32 a, b, c, d; } __attribute__((aligned(16)));

extern void func_001C7CB8(void);
extern void func_001C6F48(void*);
extern void func_001C7140(void*);
extern void func_00124DF8(void*, s32, void*);
extern void* func_00189438(s32, void*, void*);
extern void func_001EA480(f32, f32);
extern void func_001884C0(void*);
extern void func_00188B48(Quad_001891C0*, Quad_001891C0*, void*);
extern void func_00188668(void*, void*, void*);
extern s32 func_001B6598(s32, s32*);
extern s32 func_001C96B8(void*);
extern s32 func_001C8010(void*);
extern s32 func_00209B80(s32, s32*, s32*);
extern s32 func_0018B930(s32);
extern s32 func_0018B988(s32, s32);
extern void func_002093F0(void);
extern void func_0018B5C0(void*);
extern void func_0018BD58(void*, s32, s32);
extern void func_001F6A50(s32, s32);
extern void func_001F6B60(s32);
extern void func_001F6B40(s32);
extern s32 func_0018B770(void*);
extern u8 D_00264910[];
extern u8 D_00269990[];
extern u8 D_00264A40[];

struct Quad_001884E0 { s32 a, b, c, d; } __attribute__((aligned(16)));

void* func_001884E0(Quad_001884E0* destination, const Quad_001884E0* source)
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
	func_001884C0(destination);
	return destination;
}

struct Vec4Init_1885E0 {
    u8 pad0[0x0];
    f32 f00;
    u8 pad1[0x10];
    f32 f14;
    u8 pad2[0x10];
    f32 f28;
    u8 pad3[0x10];
    f32 f3C;
};

void* func_001F5C0C(void* p, s32 v, s32 n);

void func_001885E0(Vec4Init_1885E0* self)
{
    func_001F5C0C(self, 0, 0x40);
    self->f3C = 1.0f;
    self->f28 = 1.0f;
    self->f14 = 1.0f;
    self->f00 = 1.0f;
}
struct Quad_188770 { f32 f[4]; } __attribute__((aligned(16)));

void func_00188770(Quad_188770* src, Quad_188770* dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    f32 (*m)[4] = (f32 (*)[4])dst;
    for (s32 i = 0; i < 3; i++) {
        for (s32 j = i + 1; j < 4; j++) {
            f32 tmp = m[i][j];
            m[i][j] = *((f32*)((i * 4) + (u32)dst + j * 16));
            *((f32*)((i * 4) + (u32)dst + j * 16)) = tmp;
        }
    }
}


void func_00188810(f32* a, f32* b, f32* out)
{
	s32 count = 15;
	do {
		*out++ = *a++ + *b++;
	} while (--count >= 0);
}

struct __attribute__((aligned(16))) Quad_188B08 { s32 w[4]; };

struct Dst_188B08 {
    Quad_188B08 q0;
    Quad_188B08 q1;
    Quad_188B08 q2;
    Quad_188B08 q3;
};

void func_00188B08(Quad_188B08* a, Quad_188B08* b, Dst_188B08* dst)
{
    dst->q0 = b[0];
    dst->q1 = b[1];
    dst->q2 = b[2];
    dst->q3 = *a;
    dst->q0.w[3] = 0;
    dst->q1.w[3] = 0;
    dst->q2.w[3] = 0;
    *(f32*)&dst->q3.w[3] = 1.0f;
}

void func_00188CE0(f32* p)
{
	func_001EA480((p[0] + p[5] + p[10] - 1.0f) * 0.5f, 1.0f);
}

struct Span_188FD8 { f32 w[11]; };
struct Out_188FD8 { f32 o[3]; };

f32 func_00205678(f32 x);
f32 func_00205778(f32 y, f32 x);

void func_00188FD8(Span_188FD8* self, Out_188FD8* out)
{
    f32 k = 1.57069635f;
    f32 r = func_00205678(-self->w[2]);
    out->o[1] = r;
    if (r < k) {
        if (-k < r) {
            out->o[0] = func_00205778(self->w[6], self->w[10]);
            out->o[2] = func_00205778(self->w[1], self->w[0]);
        } else {
            out->o[0] = 0.0f;
            out->o[2] = -func_00205778(-self->w[4], self->w[8]);
        }
    } else {
        out->o[0] = 0.0f;
        out->o[2] = func_00205778(-self->w[4], self->w[8]);
    }
}

struct __attribute__((aligned(16))) Quad_1891C0 { s32 w[4]; };

void func_00188B48(void* a, void* b, Quad_1891C0* out);
void func_00188668(Quad_1891C0* out, void* b, Quad_1891C0* in);

void func_001891C0(u8* self, void* arg, Quad_1891C0* out)
{
    Quad_1891C0 tmp[4];
    Quad_1891C0 res[4];

    func_00188B48(self + 0x30, self, tmp);
    func_00188668(res, arg, tmp);
    out[0] = res[0];
    out[1] = res[1];
    out[2] = res[2];
    out[3] = res[3];
}

void* func_00189AF0(void* a0, void* a1)
{
	return func_00189438(4, a0, a1);
}

void func_0018A388(void* self)
{
	func_001C6F48(self);
	*(s32*)((char*)self + 0xE3C) = -1;
}

extern u8 D_00264910[];

void func_001C7140(void* self);
void func_00124DF8(void* self, s32 n, void* data);

void func_0018A3B8(void* self)
{
    func_001C7140(self);
    func_00124DF8(self, 2, D_00264910);
}

struct Self_18AB88 {
    u8 pad0[0x724];
    s32 f724;
    u8 pad1[0xA68 - 0x728];
    s32 fA68;
    u8 pad2[0xC04 - 0xA6C];
    s32 fC04;
};

void func_001C91C8(void* self);
void func_001603E8(s32 n);
void func_0018C7F8(void* p);
extern u8 D_00264A40[];

void func_0018AB88(Self_18AB88* self)
{
    func_001C91C8(self);
    s32 st = self->f724;
    if (st != 0xB) {
        if (st == 0x10) {
            s32 n = self->fA68;
            self->fC04 = 0;
            self->fA68 = n + 1;
        }
    } else {
        func_001603E8(2);
        func_0018C7F8(D_00264A40);
    }
}

struct Self_18ABF0 {
    u8 pad0[0x724];
    s32 f724;
    u8 pad1[0xE10 - 0x728];
    void* fE10;
};

void func_001B6598(void* a, s32* out);
s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);

s32 func_0018ABF0(Self_18ABF0* self)
{
    if (self->f724 == 4) {
        s32 kind;
        func_001B6598(self->fE10, &kind);
        if (kind == 0x438) {
            if (func_001C96B8(self) == 0)
                return 2;
        }
    }
    return func_001C8010(self);
}

void func_001C7CB8(void);

void func_0018ACD0(void)
{
    func_001C7CB8();
}

typedef void (*VFn_18ACF0)(void* self);

struct Obj_18ACF0 {
    VFn_18ACF0* vtbl;
};

struct Self_18ACF0 {
    u8 pad0[0xE10];
    void* fE10;
};

extern Obj_18ACF0 D_0026E248;

s32 func_001E9970(void);

void func_0018ACF0(Self_18ACF0* self)
{
    s32 kind;
    func_001B6598(self->fE10, &kind);
    s32 pick = 0;
    switch (kind) {
    case 0x43A:
    case 0x43C:
    case 0x43E:
        pick = func_001E9970();
        break;
    default:
        break;
    }
    if (pick)
        D_0026E248.vtbl[14](&D_0026E248);
    else
        D_0026E248.vtbl[15](&D_0026E248);
}
extern void func_001C9008(void*);
extern void func_001B64D8(s32, s32);

struct State_0018B2E8 { u8 pad0[0x724]; s32 type; u8 pad1[0xE10 - 0x728]; s32 handle; u8 pad2[0xE3C - 0xE14]; s32 token; };

void func_0018B2E8(State_0018B2E8* self)
{
    func_001C9008(self);
    if (self->type == 16) {
        s32 token = self->token;
        if (token == -1) return;
        func_001B64D8(self->handle, token);
        self->token = -1;
    }
}


void func_0018B580(void)
{
	func_002093F0();
	func_0018B5C0(D_00269990);
	func_0018BD58(D_00264A40, 0, 0);
}

struct Obj_18B720 { void* f0; void* f4; };

extern u8 D_00269990[];

s32 func_0018B770(void* p);
void func_001F6A50(void* a, s32 b);
void func_001F6B60(void* a);
void func_001F6B40(void* a);

void func_0018B720(Obj_18B720* a0)
{
    if (func_0018B770(D_00269990)) {
        func_001F6A50(a0->f4, 1);
    }
    func_001F6B60(a0->f0);
    func_001F6B40(a0->f0);
}

s32 func_0018B770(void* p)
{
	return *(s32*)((char*)p + 4) != -1;
}

struct Src_18B780 {
    u8 pad0[1];
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;
    u16 h6;
    u8 pad3[1];
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u16 hE;
    s32 f10;
    u16 f14;
    u8 pad2[0x20 - 0x16];
    u8 sub20[0x10];
};

struct Dst_18B780 {
    u8 pad0[0x44];
    s32 f44;
    u8 pad1[2];
    u8 f4A;
    u8 f4B;
    u16 f4C;
    u8 f4E;
    u8 f4F;
    u8 f50;
    u8 pad3[1];
    u8 f52;
    u8 f53;
    u16 f54;
    u8 f56;
    u8 f57;
    u8 f58;
};

void* func_001F5C0C(void* p, int c, int n);
void func_001E2138(void* dst, void* src);

void func_0018B780(Src_18B780* s, Dst_18B780* d)
{
    func_001F5C0C(d, 0, 0x5C);
    func_001E2138(d, s->sub20);
    d->f44 = s->f10;
    if (s->f14 & 0x1) {
        *(s32*)((u8*)d + 0x48) |= 0x1;
    }
    if (s->f14 & 0x2) {
        *(s32*)((u8*)d + 0x48) |= 0x2;
    }
    if (s->f14 & 0x4) {
        *(s32*)((u8*)d + 0x48) |= 0x4;
    }
    if (s->f14 & 0x8) {
        *(s32*)((u8*)d + 0x48) |= 0x8;
    }
    if (s->f14 & 0x20) {
        *(s32*)((u8*)d + 0x48) |= 0x10;
    }
    if (s->f14 & 0x80) {
        *(s32*)((u8*)d + 0x48) |= 0x20;
    }
    if (s->f14 & 0x800) {
        *(s32*)((u8*)d + 0x48) |= 0x40;
    }
    if (s->f14 & 0x1000) {
        *(s32*)((u8*)d + 0x48) |= 0x80;
    }
    d->f4A = s->b5;
    d->f4B = s->b4;
    d->f4C = s->h6;
    d->f4E = s->b3;
    d->f4F = s->b2;
    d->f50 = s->b1;
    d->f52 = s->bD;
    d->f53 = s->bC;
    d->f54 = s->hE;
    d->f56 = s->bB;
    d->f57 = s->bA;
    d->f58 = s->b9;
}

s32 func_0018B910(s32 value)
{
	if (value == 0) return 29;
	if (value > 0) return 30;
	return 31;
}

struct Pair_18BC90 { s32 a; s32 b; };

s32 func_00209B80(void* a0, s32* a1, s32* a2);
s32 func_0018B930(s32 h);
s32 func_0018B988(void* a0, s32 b);
s32 func_0018B930(s32 value)
{
    switch (value) {
    case 0: return 32;
    case 1: return 33;
    case -1: return 34;
    default: return 31;
    }
}


s32 func_0018BC90(void* a0, void* a1, s32* a2)
{
    Pair_18BC90 t;
    s32 r = func_0018B930(func_00209B80(a0, &t.a, &t.b));
    if (a2) {
        *a2 = t.b;
    }
    if (r == 0x21) {
        r = func_0018B988(a1, t.b);
    }
    return r;
}

s32 func_0018BD00(s32 value, void* first, s32 second)
{
	s32 result = func_0018B910(value);
	if (result == 29)
		result = func_0018BC90(0, first, (s32*)second);
	return result;
}

s32 func_0018BFA8(void* lhs, void* rhs)
{
	s32 difference = *(u16*)((char*)lhs + 0x54) - *(u16*)((char*)rhs + 0x54);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x52) - *(u8*)((char*)rhs + 0x52);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x53) - *(u8*)((char*)rhs + 0x53);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x56) - *(u8*)((char*)rhs + 0x56);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x57) - *(u8*)((char*)rhs + 0x57);
	if (difference) return difference;
	return *(u8*)((char*)lhs + 0x58) - *(u8*)((char*)rhs + 0x58);
}

typedef s32 (*VFnI_0018AAE0)(void* self);

struct Obj_0018AAE0 {
    VFnI_0018AAE0* vtbl;
    u8 pad0[0x14 - 4];
    void* owner;
    u8 pad1[0x724 - 0x18];
    s32 f724;
    u8 pad2[0xC10 - 0x728];
    s32 fC10;
    u8 pad3[0xE10 - 0xC14];
    void* fE10;
};

s32 func_001DDA80(void* p);
void func_001B6598(void* dev, s32* out);

s32 func_0018AAE0(Obj_0018AAE0* self)
{
    s32 out;
    if (func_001DDA80(self->owner) != 0) goto zero;
    if (self->fC10 != 0) goto zero;
    if (self->f724 == 0x10) goto zero;
    if (self->f724 == 0xB) goto zero;
    if (self->vtbl[0x66](self) == 0) goto zero;
    func_001B6598(self->fE10, &out);
    if (out == 0x43C) goto one;
    if (out < 0x43D) {
        if (out == 0x43A) goto one;
        goto zero;
    }
    if (out == 0x43E) goto one;
zero:
    return 0;
one:
    return 1;
}

extern s32 D_002649D8[];
extern s32 D_002649E8[];

struct Obj_0018AC58 {
    u8 pad0[0xE28];
    s32 fE28;
    u8 pad1[0xE30 - 0xE2C];
    s32 fE30[1];
    u8 pad2[0xE3C - 0xE34];
    s32 fE3C;
};

void func_001AC060(void* p);
void func_001C8F20(void* node, s32 kind, s32 flag);

void func_0018AC58(Obj_0018AC58* self)
{
    func_001AC060((u8*)&D_0026E248);
    s32 idx = self->fE28;
    func_001C8F20(self, D_002649D8[idx], self->fE30[idx]);
    s32 n = self->fE28;
    self->fE3C = D_002649E8[n];
    self->fE28 = n + 1;
}

struct Glob_18BDC8 { u8 pad0[0x25C]; s32 f25C; u8 pad260[8]; s32 f268; };
struct Self2_18BDC8 { u8 pad0[0xC]; s32 fC; f32 f10; s32 f14; s32 f18; f32 f1C; f32 f20; u8 pad24[0x4F44 - 0x24]; s32 f4F44; };

extern u8 D_00269990[];
extern f32 D_00261868[];
extern Glob_18BDC8 D_0026FF68[];

s32 func_0018B770(u8* p);
void func_0018B670(u8* p, void* fn, Self2_18BDC8* self);
void func_0018C028(Self2_18BDC8* self, s32 v);
void func_0018D0A0(Self2_18BDC8* self);
void func_00194D30(Glob_18BDC8* g, s32 a, s32 b);

void func_0018BDC8(Self2_18BDC8* self)
{
    if (func_0018B770(D_00269990) != 0) return;
    if (self->fC == self->f14) {
        if (self->f20 <= D_00261868[0])
            func_0018B670(D_00269990, (void*)func_0018D0A0, self);
    } else {
        func_0018C028(self, self->f14);
    }
    if (func_0018B770(D_00269990) != 0) return;
    if (self->f18 == 1 && D_00261868[0] - self->f10 >= 0.3f) {
        if (self->f4F44 != 0) {
            if (self->fC != 5) func_00194D30(D_0026FF68, 1, 0x15);
        } else if (D_0026FF68->f25C != 0 && D_0026FF68->f268 == 0x11) {
            if (self->fC != 5) func_00194D30(D_0026FF68, 1, 0x20);
        } else {
            switch (self->fC) {
            case 1: func_00194D30(D_0026FF68, 1, 3); break;
            case 2: func_00194D30(D_0026FF68, 1, 4); break;
            case 3: func_00194D30(D_0026FF68, 1, 7); break;
            case 4: func_00194D30(D_0026FF68, 1, 10); break;
            }
        }
    }
}

// Matches US and EU: retail's return-1 block is a shared target that every return-1 path branches to.
extern f32 D_0026185C;
extern f32 D_002649C8;

typedef void* (*FnSelf_18A9A8)(void* self);
typedef s32 (*FnSub_18A9A8)(void* self);

struct Loc_18A9A8 {
    u8 buf[0x10];
    s32 code;
};

s32 func_0018A910(void* self, void* a, void* b);
s32 func_00125750(void* a, s32 b, void* c, s32 d, s32 e, s32 f, f32 g);

s32 func_0018A9A8(void* self)
{
    u8* obj = (u8*)self;
    Loc_18A9A8 loc;
    void* sub;
    s32 code;

    if (D_0026185C < *(f32*)(obj + 0x748)) {
        return 0;
    }
    sub = ((FnSelf_18A9A8)(*(void***)obj)[0x198 / 4])(obj);
    if (sub == 0) {
        return 0;
    }
    if (*(u32*)((u8*)*(void**)sub + 8) & 8) {
        if (((FnSub_18A9A8)(*(void***)sub)[0x144 / 4])(sub)) {
            return 0;
        }
    }
    func_001B6598(*(void**)(obj + 0xE10), &loc.code);
    code = loc.code;
    if (code != 0x43C) {
        if (code < 0x43D) {
            if (code != 0x43A) {
                return 0;
            }
        } else {
            if (code == 0x43E) {
                goto one;
            }
            return 0;
        }
    }
    if (func_0018A910(obj, obj + 0x140, (u8*)sub + 0x140) != 0) {
        goto second;
    }
one:
    return 1;
second:
    func_00125750(sub, 0, loc.buf, 0, 0, 0, D_002649C8);
    if (func_0018A910(obj, obj + 0x140, loc.buf) == 0) {
        goto one;
    }
    return 0;
}

struct Slot_18B5C0 { s32 f00; s32 f04; u8 pad08[8]; s32 f10; };

s32 func_001E2268(s32 a, s32 b);

void func_0018B5C0(Slot_18B5C0* self)
{
    s32 r = func_001E2268(1, 1);
    self->f00 = r; self->f04 = -1; self->f10 = 0x22;
}

struct Obj_18BD58 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; u8 pad18[0x4F44 - 0x18]; s32 f4F44; s32 f4F48; };

void* func_001F5C0C(void* p, s32 zero, s32 size);
void func_0018C178(void* self, s32 value);

void func_0018BD58(Obj_18BD58* self, s32 a, s32 b)
{
    func_001F5C0C(self, 0, 0x4F50);
    self->fC = -1;
    self->f14 = 0;
    func_0018C178(self, 0);
    self->f4 = a;
    self->f8 = b;
    self->f4F48 = 0;
    self->f4F44 = 0;
}

// NEAR: same callees, args and frame. Retail saves s2,s1,s0 then moves a2->s2, a1->s1 before the jal and fills its delay slot with self->s0; the compiler places move s0 early and fills the delay slot with move s1.
typedef s32 (*Cb_18A910)(void* self, void* ctx);

struct Self_18A910 {
    u8 pad[0x14];
    void* f14;
};

s32 func_0018A830(void* self, void* ctx);
void func_0018D608(void* self, void* a1, void* a2);
void func_001DC238(void* a0, s32 a1, void* a2, void* a3, Cb_18A910 a4, void* a5, s32* a6, s32* a7);
s32 func_0018A6C0(s32 a0, void* a1, void* a2, s32 a3, s32 a4, void* a5, f32 f);
void func_0018D6F0(void);
extern f32 D_002649C4;

s32 func_0018A910(Self_18A910* self, void* a1, void* a2)
{
    u8 buf[0x70];
    s32 x;
    s32 y;
    func_0018D608(self, a1, a2);
    func_001DC238(self->f14, 0, a1, a2, func_0018A830, self, &x, &y);
    s32 r = func_0018A6C0(0, a1, a2, x, y, buf, D_002649C4);
    func_0018D6F0();
    return r != 0;
}
