// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_0019EBE8(void* self);

void func_001A0020(u8* self, void* other)
{
    if (other != 0) {
        func_0019EBE8(self);
    }
}

void func_0019EB28(u8* self);
extern u8* D_00275710;

void func_001A1458(u8* self)
{
    func_0019EB28(self);
    s32 v = *(s32*)(D_00275710 + 0x1D28);
    *(s32*)(self + 0x120) = -1;
    *(s32*)(self + 0x20) = v;
    *(s32*)(self + 0x128) = -1;
}

void func_0019F560(u8* self);
void func_0019EBE8(u8* self);
s32 func_00182FC8(s32 handle);

void func_001A26B0(u8* self)
{
    func_0019F560(self);
    s32 h = *(s32*)(self + 0x120);
    if (h != 0) {
        if (func_00182FC8(h) == 0) {
            func_0019EBE8(self);
        }
    }
}

void func_001BAC30(u8* self);
void func_00124DF8(u8* self, s32 n, void* data);
extern u8 D_0026B778[];

void func_001A3B20(u8* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 2, D_0026B778);
}

struct __attribute__((aligned(16))) Quad_1A0040 { s32 a, b, c, d; };

struct Obj_1A0040 {
    u8 pad00[0x1C];
    f32 f1C;
    s32 i20;
    u8 pad24[0x1C];
    Quad_1A0040 q40;
    u8 pad50[0xD0];
    f32 f120;
};

void func_0019EB28(Obj_1A0040* self);
extern u8* D_00275710;
extern Quad_1A0040 D_00275C50;

void func_001A0040(Obj_1A0040* self)
{
    func_0019EB28(self);
    self->f1C = 0.25f;
    s32 v = *(s32*)(D_00275710 + 0x1CF8);
    self->i20 = v;
    self->q40 = D_00275C50;
    self->f120 = 0.05f;
}

void func_001A0338(void* self, s32 kind, s32 extra);

void func_001A0318(void* self)
{
    func_001A0338(self, 0, 0);
}

typedef void (*VFn_1A0F88)(void* self);
struct Holder_1A0F88 { u8 pad0[0x60]; VFn_1A0F88 fn60; };
struct Node_1A0F88 { u8 pad0[0x18]; f32 f18; f32 f1C; u8 pad20[0x110]; Holder_1A0F88* holder130; void* arg134; };

extern f32 D_0026185C;

void func_0019EBE8(void* self);

void func_001A0F88(Node_1A0F88* self)
{
    if (self->f1C < D_0026185C - self->f18) {
        func_0019EBE8(self);
        self->holder130->fn60(self->arg134);
    }
}

typedef Quad_1A0040 Quad_1A0FE8;
struct Node_1A0FE8 { u8 pad0[0x1C]; f32 f1C; u8 pad20[0x20]; Quad_1A0FE8 q40; };


void func_0019EB28(void* self);

void func_001A0FE8(Node_1A0FE8* self)
{
    func_0019EB28(self);
    self->q40 = D_00275C50;
    self->f1C = 2.0f;
}

struct Ctrl_1A3FE0 { u8 pad0[0x610]; s32 mode610; u8 pad1[8]; f32 level61C; u8 pad2[0x64]; s32 flag684; };

s32 func_001A3FE0(Ctrl_1A3FE0* self)
{
    s32 r = self->mode610;
    switch (r) {
    case 0:
        if (0.0f < self->level61C) {
            r = 1;
        }
        break;
    case 1:
        if (self->level61C == 0.0f) {
            r = 0;
        }
        break;
    case 2:
        if (self->flag684 == 0) {
            r = 1;
        }
        break;
    }
    return r;
}

struct Obj_1A1410 { u8 pad0[0x20]; s32 field20; u8 pad1[0xFC]; f32 f120; };
struct Ctx_1A1410 { u8 pad0[0x1D28]; s32 value1D28; };

void func_001A0040(void* self);

void func_001A1410(Obj_1A1410* self)
{
    func_001A0040(self);
    Ctx_1A1410* ctx = (Ctx_1A1410*)D_00275710;
    s32 v = ctx->value1D28;
    self->f120 = 0.15f;
    self->field20 = v;
}

void func_001A1498(void)
{
}

struct Ctrl_1A14A0 { u8 pad0[0x18]; f32 a18; f32 b1C; u8 pad1[0x100]; s32 mode120; f32 phase124; };

extern f32 D_0026185C;
extern f32 D_0026B600[];
extern f32 D_0026B610[];
void func_001A1DF0(void* self, s32 n);
void func_0019EBE8(void* self);

void func_001A14A0(Ctrl_1A14A0* c, f32 dt)
{
    f32 t = (D_0026185C - c->a18) / c->b1C;
    f32 k;
    switch (c->mode120) {
    case 0: k = D_0026B600[0] + t * (D_0026B600[1] + t * D_0026B600[2]); break;
    case 1: k = D_0026B610[0]; break;
    case 2: k = D_0026B610[0] + t * (D_0026B610[1] + t * D_0026B610[2]); break;
    }
    f32 p = c->phase124 + k * dt;
    c->phase124 = p;
    if (1.0f <= p) c->phase124 = p - 1.0f;
    if (1.0f < t) {
        switch (c->mode120) {
        case 0: func_001A1DF0(c, 1); break;
        case 1: func_001A1DF0(c, 2); break;
        case 2: func_0019EBE8(c); break;
        }
    }
}

struct Item_1A1F18 { u8 pad0[0x20]; f32 key20; };

s32 func_001A1F18(Item_1A1F18* a, Item_1A1F18* b)
{
    if (a->key20 < b->key20) return -1;
    return 1;
}

struct Self_1A22C8 { u8 pad0[0x120]; s32 f120; s32 f124; };
struct Src_1A22C8 { u8 pad0[0x1DC]; s32 f1DC; u8 pad1[0x10]; s32 f1F0; };

void func_001A22C8(Self_1A22C8* self, Src_1A22C8* src)
{
    self->f120 = src->f1DC;
    self->f124 = src->f1F0;
}

struct Self_1A25F0 { u8 pad0[0x120]; s32 f120; };
struct Obj_1A25F0 { u8 pad0[0x50]; void* f50; };

extern void* D_0026B6C0[];

void func_001A2380(void* self, s32 v, void* other, void* a2, void* a3, s32 zero);
void func_0019EBE8(void* self);
s32 func_001300E8(void* self, s32 kind);

s32 func_001A25F0(Self_1A25F0* self, Obj_1A25F0* other, void* a2, void* a3)
{
    u32 i;
    for (i = 0; i < 4; i++) {
        if (func_001300E8(other->f50, (s32)D_0026B6C0[i]) != 0) {
            return 0;
        }
    }
    if (func_001300E8(other, 0x1F) == 0) {
        func_001A2380(self, self->f120, other, a2, a3, 0);
    }
    func_0019EBE8(self);
    return 1;
}

struct Obj_1A0A78 { u8 pad0[0x18]; f32 f18; u8 pad1[0x1C]; f32 f38; u8 pad2[0x44]; };
typedef void (*VFn_1A0A78)(void* self, void* p, f32 f, s32 z);
struct Node_1A0A78 { VFn_1A0A78* vtbl; };

void func_0019F560(Obj_1A0A78* self);
void* func_0019EA78(s32 a, s32 b);
extern f32 D_0026185C;

void func_001A0A78(Obj_1A0A78* self, f32 arg)
{
    func_0019F560(self);
    f32 d = D_0026185C - self->f18;
    d = d - 0.15f;
    if (0.0f <= d && d < arg) {
        arg = -self->f38;
        Node_1A0A78* n = (Node_1A0A78*)func_0019EA78(12, 0);
        if (n != 0) {
            n->vtbl[0](n, (u8*)self + 0x80, arg, 0);
        }
    }
}

s32 func_001300E8(void* self, s32 kind);
s32 func_0019ED58(void* a, void* b, void* c, void* d);

struct Obj_1A3128 { u8 pad0[0x50]; void* p50; };

s32 func_001A3128(void* a0, Obj_1A3128* a1, void* a2, void* a3)
{
    if (func_001300E8(a1->p50, 6) != 0) {
        return 0;
    }
    return func_0019ED58(a0, a1, a2, a3);
}

typedef u64 Quad_1A0C50 __attribute__((mode(TI)));
struct Obj_1A0C50 { u8 pad00[0x1C]; f32 f1C; s32 i20; u8 pad24[0x9C]; Quad_1A0C50 qC0; };

void func_0019EB28(void* self);
extern u8* D_00275710;

void func_001A0C50(Obj_1A0C50* self)
{
    func_0019EB28(self);
    u8* g = D_00275710;
    s32 v = *(s32*)(g + 0x1CEC);
    self->f1C = 0.5f;
    self->i20 = v;
    self->qC0 = *(Quad_1A0C50*)(g + 0x1EE0);
}

typedef void (*VFn_1A38F0)(void* self);
struct Obj_1A38F0 { VFn_1A38F0* vtbl; };
struct Node_1A38F0 {
    u8 pad_00[0x18];
    f32 f18;
    f32 f1C;
    Obj_1A38F0* f20;
    u8 pad_24[0x134 - 0x24];
    s32 f134;
};

extern f32 D_00261858[];

void func_001A35F0(void* self);
void func_0019EBE8(void* self);

void func_001A38F0(Node_1A38F0* self)
{
    if (self->f18 <= D_00261858[1]) {
        if (self->f134 != 0) {
            func_001A35F0(self);
        }
    }
    f32 span = D_00261858[1] - self->f18;
    if (self->f1C < span) {
        Obj_1A38F0* o = self->f20;
        o->vtbl[6](o);
        func_0019EBE8(self);
    }
}

struct Node_1A3990 {
    u8 pad_00[0x18];
    f32 f18;
};

extern f32 D_0026185C;

void func_0019F858(void* self);

void func_001A3990(Node_1A3990* self)
{
    if (D_0026185C < self->f18) {
        return;
    }
    func_0019F858(self);
}
