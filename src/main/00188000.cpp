// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

void func_001F5C0C(void* p, s32 v, s32 n);

void func_001885E0(Vec4Init_1885E0* self)
{
    func_001F5C0C(self, 0, 0x40);
    self->f3C = 1.0f;
    self->f28 = 1.0f;
    self->f14 = 1.0f;
    self->f00 = 1.0f;
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

extern u8 D_00264910[];

void func_001C7140(void* self);
void func_00124DF8(void* self, s32 n, void* data);

void func_0018A3B8(void* self)
{
    func_001C7140(self);
    func_00124DF8(self, 2, D_00264910);
}

void func_001C7CB8(void);

void func_0018ACD0(void)
{
    func_001C7CB8();
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

struct Pair_18BC90 { s32 a; s32 b; };

s32 func_00209B80(void* a0, s32* a1, s32* a2);
s32 func_0018B930(s32 h);
s32 func_0018B988(void* a0, s32 b);

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
