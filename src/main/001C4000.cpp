// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1C4180 { u8 pad[0x698]; s32 count; s32 items[1]; };

void func_001C4180(Obj_1C4180* self, s32 value)
{
    s32 n = self->count;
    self->items[n] = value;
    self->count = n + 1;
}

void func_00192B58(void* self);
void func_001C4C20(void* self);

void func_001C4ED0(void* self)
{
    func_00192B58(self);
    func_001C4C20(self);
}

typedef s32 (*VFn_C5338)(void* self);
struct Obj_C5338 { VFn_C5338* vtbl; };
struct Out_C5338 { u8 pad[0x94]; f32 f94; s32 f98; };
extern f32 D_00274B74;

void func_001C5338(Obj_C5338* self, Out_C5338* out)
{
    if (self->vtbl[0x168 / 4](self)) {
        f32 d = D_00274B74;
        out->f98 = 0;
        out->f94 = d;
    } else {
        out->f94 = 0.0f;
        out->f98 = 0;
    }
}

struct __attribute__((aligned(16))) Quad_C5D58 { s32 a, b, c, d; };
typedef void (*VFn_C5D58)(void* self, void* arg);
struct Obj_C5D58 {
    VFn_C5D58* vtbl;
    u8 pad0[0xD0 - 4];
    f32 fD0;
    f32 fD4;
    u8 pad1[0x160 - 0xD8];
    Quad_C5D58 q160;
    u8 pad2[0x638 - 0x170];
    f32 f638;
};
f32 func_00205778(f32 a, f32 b);
void func_001EA728(void* p, void* out, f32 a, f32 b, f32 c);

void func_001C5D58(Obj_C5D58* self)
{
    Quad_C5D58 q = self->q160;
    f32 r = func_00205778(self->fD4, self->fD0);
    func_001EA728((u8*)self + 0x6E0, &q.c, r, self->f638, 0.0f);
    self->vtbl[0x94 / 4](self, &q);
}

typedef s32 (*VFn_C7B60)(void* self);
struct Obj_C7B60 {
    VFn_C7B60* vtbl;
    u8 pad0[0x724 - 4];
    s32 f724;
    u8 pad1[0xB84 - 0x728];
    s32 fB84;
    s32 fB88;
};
struct Glob_C7B60 { u8 pad[0x275C]; s32 f275C; };
extern Glob_C7B60* D_00262E10;
void func_001C8F20(Obj_C7B60* self, s32 a1, s32 a2);

void func_001C7B60(Obj_C7B60* self)
{
    if (self->fB84 != 0) return;
    if (self->fB88 != 0) return;
    if (D_00262E10 != 0 && D_00262E10->f275C != 0) return;
    for (;;) {
        s32 v = self->vtbl[0x174 / 4](self);
        if (v == self->f724) break;
        func_001C8F20(self, v, 0);
    }
}

void func_001B9338(void* self);
void func_001C5148(void* self);

void func_001C5118(void* self)
{
    func_001B9338(self);
    func_001C5148(self);
}

void func_001C53A8(void);

void func_001C5388(void)
{
    func_001C53A8();
}

void func_001C53A8(void)
{
}

struct Obj_1C53E0;
typedef s32 (*VFn_1C53E0)(void* self);
struct Obj_1C53E0 { VFn_1C53E0* vtbl; };
void func_001C54D0(Obj_1C53E0* self, void* b, s32 c);

void func_001C53E0(Obj_1C53E0* self, void* b, s32 c)
{
    if (self->vtbl[90](self)) {
        func_001C54D0(self, b, c);
    }
}

void func_001C5C10(void* a, s32 b, s32 c, s32 d);

void func_001C5BF0(void* a0, s32 a1, s32 unused2, s32 unused3, s32 a4, s32 a5)
{
    func_001C5C10(a0, a1, a4, a5);
}

struct Vec2_1C4FA0 { f32 x; f32 y; };
typedef void (*VFn_1C4FA0)(void* self);
struct Obj_1C4FA0 { VFn_1C4FA0* vtbl; u8 pad0[0x630 - 4]; f32 f630; u8 pad1[0x638 - 0x634]; f32 f638; };

void func_001B97E0(void* self, void* src);
f32 func_00205778(f32 a, f32 b);

void func_001C4FA0(Obj_1C4FA0* self, Vec2_1C4FA0* v)
{
    func_001B97E0(self, v);
    f32 r = func_00205778(v->y, v->x);
    self->f638 = r;
    self->f630 = r;
    self->vtbl[88](self);
}

extern u8 D_00274BF0[];

struct Obj_1C6E58 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad1[0x638 - 0x18];
    f32 f638;
    u8 pad2[0x2200 - 0x63C];
    s32 f2200;
    s32 f2204;
    s32 f2208;
};

struct Tmp_1C6E58 {
    f32 pair[4];
    s32 out;
};

void func_001C6AA8(Obj_1C6E58* self, s32 n, void* table, s32* out, f32* pair, f32 lo, f32 hi);
f32 func_00205778(f32 x, f32 y);
void func_001C5D58(Obj_1C6E58* self);

void func_001C6E58(Obj_1C6E58* self)
{
    Tmp_1C6E58 t;
    func_001C6AA8(self, 8, D_00274BF0, &t.out, t.pair, 0.25f, 1.0f);
    self->f2204 = 0;
    self->f2200 = t.out;
    self->f2208 = 0;
    if (t.out != 0) {
        self->f638 = func_00205778(t.pair[1], t.pair[0]);
        func_001C5D58(self);
    }
}

extern u8 D_00274C00[];

struct Obj_1C6ED0 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad1[0x638 - 0x18];
    f32 f638;
    u8 pad2[0x2200 - 0x63C];
    s32 f2200;
    s32 f2204;
    s32 f2208;
};

struct Tmp_1C6ED0 {
    f32 pair[4];
    s32 out;
};

void func_001C6AA8(Obj_1C6ED0* self, s32 n, void* table, s32* out, f32* pair, f32 lo, f32 hi);
f32 func_00205778(f32 x, f32 y);
void func_001C5D58(Obj_1C6ED0* self);

void func_001C6ED0(Obj_1C6ED0* self)
{
    Tmp_1C6ED0 t;
    func_001C6AA8(self, 4, D_00274C00, &t.out, t.pair, 0.25f, 3.15f);
    self->f2204 = 0;
    self->f2200 = t.out;
    self->f2208 = 0;
    if (t.out != 0) {
        self->f638 = func_00205778(t.pair[1], t.pair[0]);
        func_001C5D58(self);
    }
}

struct Obj_1C71E0 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad1[0x924 - 0x18];
    s32 f924;
    s32 f928;
    u8 pad2[0xAF8 - 0x92C];
    s32 fAF8;
    s32 fAFC;
    s32 fB00;
    u8 pad3[0xB4C - 0xB04];
    s32 fB4C;
};

void func_001249A8(Obj_1C71E0* self);
s32 func_0015A448(s32 a, s32 b, Obj_1C71E0* self);
void func_001CAB10(Obj_1C71E0* self);
s32 func_0015A418(s32 a, s32 b, s32 c, Obj_1C71E0* self);
void func_00159478(s32* p, Obj_1C71E0* self);

void func_001C71E0(Obj_1C71E0* self)
{
    s32 v;
    func_001249A8(self);
    if (self->f924 != -1) {
        self->f928 = func_0015A448(self->f14, self->f924, self);
    }
    if (self->fB4C != -1) {
        func_001CAB10(self);
    }
    v = self->fAF8;
    if (v != 0) {
        if (self->fAFC != -1) {
            self->fB00 = func_0015A418(self->f14, 0x101, self->fAFC, self);
        }
    } else {
        func_00159478(&self->fB00, self);
    }
}
