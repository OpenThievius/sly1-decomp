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

void func_001A0338(void* self, s32 kind, s32 extra);

void func_001A0950(void* self, s32 kind, s32 extra)
{
    if (kind == 3) {
        goto three;
    }
    if (kind < 4) {
        if (kind == 2) {
            goto zero;
        }
        return;
    }
    if (kind == 10) {
        goto zero;
    }
    if (kind != 16) {
        return;
    }
zero:
    func_001A0338(self, 0, 0);
    return;
three:
    func_001A0338(self, 0, extra + 16);
}

struct Self_1A26F8 { u8 pad0[0x120]; void* f120; };

void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
s32 func_0019F620(void* self, void* a1, void* a2, void* a3);

void func_001A26F8(void* a0, void* a1)
{
    Self_1A26F8* self = (Self_1A26F8*)a0;
    u8 scratch[0x40];

    func_00128018(self->f120, 0, (u8*)self + 0x80, scratch);
    func_00128150(self->f120, 0, (u8*)self + 0x50, scratch + 0x10);
    func_0019F620(self, a1, scratch, scratch + 0x10);
}

struct Self_1A2A68 { u8 pad0[0x20]; s32 f20; };
struct Other_1A2A68 { u8 pad0[0x50]; void* f50; };

s32 func_001300E8(void* node, s32 kind);
void func_001A2380(void* self, s32 v, void* other, void* a2, void* a3, void* out);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
void func_0019EBE8(void* self);

s32 func_001A2A68(void* a0, void* a1, void* a2, void* a3)
{
    Self_1A2A68* self = (Self_1A2A68*)a0;
    Other_1A2A68* other = (Other_1A2A68*)a1;
    u8 out[0x10];
    void* p;

    if (func_001300E8(other->f50, 0x40) != 0) {
        return 0;
    }
    if (func_001300E8(other->f50, 6) != 0) {
        return 0;
    }
    func_001A2380(self, self->f20, other, a2, a3, out);
    p = *(void**)out;
    if (p != 0) {
        func_00128150(0, other, (u8*)p + 0x50, (u8*)p + 0x50);
    }
    func_0019EBE8(self);
    return 1;
}

struct Self_1A2B18 { u8 pad0[0x7C]; void* f7C; };
struct Other_1A2B18 { u8 pad0[0x538]; u64 f538; };

s32 func_001A2B18(Self_1A2B18* self, Other_1A2B18* other)
{
    u64 flag = 0x8000;

    flag <<= 28;
    if ((other->f538 & flag) != 0) {
        return 0;
    }
    return other != self->f7C;
}

struct Src_1A2D30 { u8 pad0[0x7C]; void* link; u8 pad1[0x1F0 - 0x80]; s32 f1F0; s32 f1F4; };
struct Dst_1A2D30 { u8 pad0[0xB0]; s32 f0B0; u8 pad1[0x110 - 0xB4]; s32 f0110; s32 f0114; s32 f0118; s32 f011C; s32 f0120; s32 f0124; };

void func_00128018(void* a0, void* a1, void* a2, void* a3);

void func_001A2D30(void* a0, void* a1)
{
    Dst_1A2D30* dst = (Dst_1A2D30*)a0;
    Src_1A2D30* src = (Src_1A2D30*)a1;
    func_00128018(src->link, 0, (u8*)src + 0x20, (u8*)dst + 0x80);
    dst->f0B0 = 0;
    dst->f0110 = 0;
    dst->f0120 = src->f1F4;
    dst->f0124 = src->f1F0;
}

extern u8 D_0026B5B0[];
extern u8 D_0026B5C0[];

void func_0019EB28(void* self);

struct __attribute__((aligned(16))) Quad_1A0B20 { s32 q[4]; };
struct Obj_1A0B20 {
    u8 pad000[0x1C];
    f32 f1C;
    s32 i20;
    u8 pad024[0x30 - 0x24];
    f32 f30;
    f32 f34;
    u8 pad038[0x40 - 0x38];
    Quad_1A0B20 q40;
    u8 pad050[0xB0 - 0x50];
    f32 fB0;
    u8 padB4[0xC0 - 0xB4];
    Quad_1A0B20 qC0;
};

void func_001A0B20(void* selfv)
{
    Obj_1A0B20* self = (Obj_1A0B20*)selfv;
    func_0019EB28(self);
    u8* sys = *(u8**)&D_00275710;
    self->i20 = *(s32*)(sys + 0x1D0C);
    self->f1C = 3.0f;
    self->q40 = *(Quad_1A0B20*)D_0026B5B0;
    self->f34 = self->f30 * 0.25f;
    self->qC0 = *(Quad_1A0B20*)D_0026B5C0;
    self->fB0 = -1.0f;
}


s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

struct Other_1A39C8 {
    u8 pad000[0x7C];
    void* p7C;
    u8 pad080[0x1F0 - 0x80];
    s32 i1F0;
    f32 f1F4;
};
struct Obj_1A39C8 {
    u8 pad000[0x120];
    s32 i120;
    f32 f124;
};

void func_001A39C8(void* selfv, void* otherv)
{
    Obj_1A39C8* self = (Obj_1A39C8*)selfv;
    Other_1A39C8* other = (Other_1A39C8*)otherv;
    self->i120 = func_0015A418(*(void**)&D_00275710, 0x104, other->i1F0, other->p7C);
    self->f124 = other->f1F4;
}

typedef void (*VFn_1A3B58)(void* self);
struct Obj_1A3B58 {
    VFn_1A3B58* vtbl;
    u8 pad_004[0x640 - 0x004];
    void* f640;
    void* f644;
    u8 pad_648[0x650 - 0x648];
    void* f650;
    void* f654;
    u8 pad_658[0x664 - 0x658];
    void* f664;
    s32 f668;
    u8 f66C[0x678 - 0x66C];
    s32 f678;
};

extern u8* D_00275710;
extern u8 D_0026B790[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
s32 func_001A4070(void* self, s32 n);
void func_001A42C8(void* self, s32 v);

void func_001A3B58(Obj_1A3B58* self)
{
    func_00124A48(self);
    if (self->f678 != 0) {
        func_00124DF8(self, 6, D_0026B790);
        func_001B9AE0(self, 0, 0, 3, 0);
        if (self->f640 != 0) {
            self->f644 = func_001B6290(self->f640, self, -1, 0);
        }
        if (self->f650 != 0) {
            self->f654 = func_001B6290(self->f650, self, -1, 1);
        }
        self->f668 = func_0015A4F0(D_00275710, 1, 0x50, self->f664, 3, self->f66C);
        func_001A4070(self, 2);
        func_001A42C8(self, 0);
    } else {
        self->vtbl[7](self);
    }
}

struct Dst_1A3F40 { u8 pad_000[0x618]; s32 f618; f32 f61C; f32 f620; f32 f624; };
struct Src_1A3F40 { u8 pad_000[0x48]; f32 f48; u8 pad_04C[0x7C - 0x4C]; f32 f7C; };

extern void* D_00261990;

void func_00144FF8(void* a, void* b, s32 c, void* d);

void func_001A3F40(Dst_1A3F40* out, Src_1A3F40* src)
{
    if (0.3f < src->f48) {
        func_00144FF8(D_00261990, src, 0, &out->f618);
    }
    out->f61C = src->f48;
    if (0.8f < src->f7C) {
        func_00144FF8(D_00261990, src, 1, &out->f620);
    }
    out->f624 = src->f7C;
}

extern u8 D_0026B710[];
extern u8 D_0026B720[];

void func_0019EB28(void* self);

struct __attribute__((aligned(16))) Quad_1A31F0 { s32 q[4]; };
struct Obj_1A31F0 {
    u8 pad000[0x1C];
    f32 f1C;
    s32 i20;
    u8 pad024[0x30 - 0x24];
    Quad_1A31F0 q30;
    Quad_1A31F0 q40;
};

void func_001A31F0(void* selfv)
{
    Obj_1A31F0* self = (Obj_1A31F0*)selfv;
    func_0019EB28(self);
    f32 half = 0.5f;
    u8* sys = *(u8**)&D_00275710;
    self->f1C = half;
    self->i20 = *(s32*)(sys + 0x1D30);
    self->q40 = *(Quad_1A31F0*)D_0026B710;
    self->q30 = *(Quad_1A31F0*)D_0026B720;
}



struct __attribute__((aligned(16))) Quad_1A3598 { s32 q[4]; };
struct Obj_1A3598 {
    u8 pad000[0x30];
    f32 f30;
    f32 f34;
    s32 i38;
    Quad_1A3598 q40;
};

void func_0019EB28(Obj_1A3598* self, f32 x);

void func_001A3598(Obj_1A3598* self, f32 x)
{
    func_0019EB28(self, x);
    self->q40 = *(Quad_1A3598*)&D_00275C50;
    self->f30 = x;
    self->f34 = 1.0f - x;
    self->i38 = 0;
}
