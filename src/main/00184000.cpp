// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Vec2_1840B8 { f32 x; f32 y; };

void func_00183F40(f32* out0, f32* out1, f32 a, f32 b, f32 c, f32 d);

void func_001840B8(Vec2_1840B8* self, f32* out0, f32* out1)
{
    func_00183F40(out0, out1, self->x, 1.0f, self->y, 0.0f);
}

struct Obj_001841B0 { u8 pad[0x304]; s32 f304; };
extern s32 D_002622CC;
extern s32 D_00264260;

void func_001841B0(Obj_001841B0* self)
{
    if (self->f304 == 0) {
        D_00264260 = D_002622CC;
    }
}

struct Obj_184768 { u8 pad0[0x2C8]; u64 bits; s32 flag; };
void func_001841D0(void* self);
void func_00184B58(void* self);

void func_00184768(Obj_184768* self, s32 flag)
{
    self->flag = flag;
    if (flag == 0) {
        self->bits = (self->bits & ~(u64)0x30000000000) | ((u64)0x8000 << 25);
    } else {
        self->bits = self->bits & ~(u64)0x30000000000;
    }
    func_001841D0(self);
    func_00184B58(self);
}

struct Obj_001847F0 { u8 pad[0x2E0]; u32 q[4]; };
struct Quad_001847F0 { u32 w[4]; } __attribute__((aligned(16)));

void func_001847F0(Obj_001847F0* self, Quad_001847F0* src)
{
    *(Quad_001847F0*)self->q = *src;
    func_001841D0(self);
}

struct Obj_00184818 { u8 pad[0x2F0]; f32 value; };

void func_00184818(Obj_00184818* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_00184838 { u8 pad[0x2F4]; f32 value; };

void func_00184838(Obj_00184838* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_00184858 { u8 pad[0x2F8]; f32 value; };

void func_00184858(Obj_00184858* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_00184878 { u8 pad[0x2FC]; f32 value; };

void func_00184878(Obj_00184878* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_00184898 { u8 pad[0x300]; f32 value; };

void func_00184898(Obj_00184898* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_184968 { u8 pad[0x304]; s32 f304; };

void func_00184968(Obj_184968* self, s32 v)
{
    if (v != self->f304) {
        self->f304 = v;
        func_001841D0(self);
    }
}

struct Obj_184D78 {
    u8 pad0[0x2C8];
    u64 bits;
    s32 f2D0;
    u8 pad1[0x304 - 0x2D4];
    s32 f304;
    s32 f308;
};

s32 func_00184D78(Obj_184D78** a, Obj_184D78** b)
{
    Obj_184D78* x = *a;
    Obj_184D78* y = *b;
    s32 d;

    d = x->f304 - y->f304;
    if (d != 0) {
        return d;
    }
    d = x->f308 - y->f308;
    if (d != 0) {
        return d;
    }
    d = ((s32)(x->bits >> 38) & 1) - ((s32)(y->bits >> 38) & 1);
    if (d != 0) {
        return d;
    }
    return x->f2D0 - y->f2D0;
}

struct __attribute__((packed)) Packed8_184990 { u64 v; };

struct Obj_184990 {
    u8 pad0[0x330];
    Packed8_184990 p330;
};

void func_00184990(Obj_184990* self, Packed8_184990* src)
{
    self->p330 = *src;
    func_001841D0(self);
    func_00184B58(self);
}

struct Obj_1849D0 {
    u8 pad0[0x338];
    f32 f338;
};

void func_00184A70(void* self);

void func_001849D0(Obj_1849D0* self, f32 v)
{
    self->f338 = v;
    func_00184A70(self);
    func_001841D0(self);
    func_00184B58(self);
}

struct Obj_184A08 {
    u8 pad0[0x33C];
    f32 f33C;
};

void func_00184A08(Obj_184A08* self, f32 v)
{
    self->f33C = v;
    func_00184A70(self);
    func_001841D0(self);
}

struct __attribute__((aligned(16))) Quad_184A38 { s32 a, b, c, d; };

struct Obj_184A38 {
    u8 pad0[0x340];
    Quad_184A38 q340;
};

void func_00184A38(Obj_184A38* self, Quad_184A38* src)
{
    self->q340 = *src;
    func_001841D0(self);
    func_00184B58(self);
}

void func_00184818(void* self, f32 v);
void func_00184838(void* self, f32 v);

void func_00184CD0(void* self, f32 v)
{
    func_00184818(self, v);
    func_00184838(self, v);
}

struct Obj_184D10 {
    u8 pad0[0x2F0];
    f32 f2F0;
};

void func_00184D10(Obj_184D10* self, f32* out)
{
    *out = self->f2F0;
}

struct __attribute__((aligned(16))) Quad_00184D20 { s32 a, b, c, d; };

void func_001B4600(void* a0, void* a1);
void func_001847F0(void* self, void* a1);

void func_00184D20(void* self, void* a1)
{
    Quad_00184D20 q;
    func_001B4600(a1, &q);
    func_001847F0(self, &q);
}

void func_001B4580(void* self);

void func_00184D58(u8* self)
{
    func_001B4580(self + 736);
}

struct __attribute__((aligned(16))) Quad_00185358 { s32 a, b, c, d; };
struct __attribute__((packed)) Pk8_00185358 { u64 v; };

struct __attribute__((aligned(16))) Obj_00185358 {
    u8 pad0[32]; s32 f20; u8 pad1[28]; f32 f40; s32 f44; s32 f48; u8 pad2[4];
    Quad_00185358 q50; Pk8_00185358 p60; u8 pad3[8]; Quad_00185358 q70; Pk8_00185358 p80;
};

extern u8 D_00264770[];
extern u8 D_00264780[];
extern u8 D_00264790[];
extern u8 D_002647A0[];

void func_00121338(void* self);

void func_00185358(Obj_00185358* self)
{
    func_00121338(self);
    self->f20 = -1;
    self->f40 = 800.0f;
    *(Quad_00185358*)&self->q50 = *(Quad_00185358*)D_00264770;
    self->p60 = *(Pk8_00185358*)D_00264780;
    self->q70 = *(Quad_00185358*)D_00264790;
    self->p80 = *(Pk8_00185358*)D_002647A0;
    self->f44 = 1;
    self->f48 = -1;
}

struct IndexPair_185C18 { s32 a; s32 b; };
struct Weight_264840 { f32 a; f32 b; };

extern Weight_264840 D_00264840[];
extern s32 D_00262C64;

f32 func_00185C18(IndexPair_185C18* p)
{
    f32 num = D_00264840[p->a].b + D_00264840[p->b].b;
    f32 den = D_00264840[p->a].a + D_00264840[p->b].a;
    f32 r = num / den;
    if (r < 0.0f) r = 0.0f;
    if (D_00262C64 & 8) r = r * 0.2f;
    return r;
}

struct IndexPair_185CA0 { s32 a; s32 b; };
struct Weight_2648A8 { f32 a; f32 b; };

extern Weight_2648A8 D_002648A8[];

f32 func_00185CA0(IndexPair_185CA0* p)
{
    f32 one = 1.0f;
    f32 num = D_002648A8[p->a].b + D_002648A8[p->b].b;
    f32 den = D_002648A8[p->a].a + D_002648A8[p->b].a;
    f32 r = num / den;
    if (r < 0.0f) return 0.0f;
    if (one < r) r = one;
    return r;
}
