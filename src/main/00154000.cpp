// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Actor_156108 {
    u8 pad0[0x2D4];
    s32 f2D4;
    s32 f2D8;
    u8 pad1[0x34C - 0x2DC];
    s32 f34C;
};

void func_00155F90();
void func_00155FA0(Actor_156108* self);

void func_00156108(Actor_156108* self, s32 a1)
{
    if (self->f2D4 == -1) {
        self->f2D8 = a1;
    } else if (self->f2D4 == 0) {
        if (a1 == 0) {
            func_00155F90();
        } else if (a1 == -1) {
            func_00155FA0(self);
        } else {
            self->f2D8 = a1;
        }
    }
    self->f34C = 1;
}

struct Actor_156178 {
    u8 pad0[0x308];
    s32 f308;
    u8 pad1[0x34C - 0x30C];
    s32 f34C;
};

void func_00156178(Actor_156178* a0, s32 a1)
{
    a0->f308 = a1;
    a0->f34C = 1;
}

void* func_00155778(void* a0, s32 a1);
void func_00156188(void* self, s32 a1);

void func_00156218(void* a0, s32 a1)
{
    void* r = func_00155778(a0, 1);
    func_00156188(r, a1);
}

void* func_00158DD8(void* a0, s32 a1);
void func_00156188(void* self, s32 a1);

void func_00156250(void* a0, s32 a1)
{
    void* r = func_00158DD8(a0, 1);
    func_00156188(r, a1);
}

struct __attribute__((aligned(16))) Quad_001566C8 { s32 a, b, c, d; };
struct Msg_001566C8 {
    s32 kind;
    u8 pad0[0x20 - 4];
    Quad_001566C8 q;
    s32 zero;
    f32 f;
    u8 pad1[0x50 - 0x38];
};
struct Game_001566C8 {
    u8 pad0[0x1D0C];
    void* f1D0C;
};
typedef void (*VFn_001566C8)(void* self, void* msg);

extern Game_001566C8* D_00275710;

void func_001566C8(Quad_001566C8* a0, f32 f)
{
    void* obj = D_00275710->f1D0C;
    if (obj != 0) {
        Msg_001566C8 m;
        m.kind = 12;
        m.q = *a0;
        m.f = f;
        m.zero = 0;
        VFn_001566C8* vt = *(VFn_001566C8**)obj;
        vt[31](obj, &m);
    }
}

struct Obj_1550B8;
typedef void (*VFn_1550B8)(Obj_1550B8* self, void* arg);
struct Sub_1550B8 { u8 pad[0x7C]; void* value; };
struct Obj_1550B8 { VFn_1550B8* vtbl; u8 pad[0x2D0 - 4]; Sub_1550B8* sub; };

void func_001550B8(Obj_1550B8* self)
{
    self->vtbl[25](self, self->sub->value);
}

struct Obj_1557B8 { u8 pad[0x34C]; s32 field; };

Obj_1557B8* func_001557B8(Obj_1557B8* self, s32 value)
{
    if (value == 1) {
        self->field = value;
    }
    return self;
}

extern f32 D_0026185C;

struct Obj_155FB0 { u8 pad0[0x2D4]; s32 a2d4; s32 a2d8; u8 pad1[0x340 - 0x2DC]; f32 f340; };

s32 func_00155FB0(Obj_155FB0* self)
{
    if (D_0026185C < self->f340) {
        return 1;
    }
    if (self->a2d4 < 2) {
        if (self->a2d4 >= 0) {
            if (self->a2d8 == 0) {
                return 1;
            }
        }
    }
    return 0;
}

struct Obj_157E00 {
    u8 pad0[0x120];
    s32 f120;
    u8 pad1[0x130 - 0x124];
    s32 f130;
};

struct Frame_157E00 {
    s32 out[4];
    s32 flag;
    s32 pad[3];
    s32 pair[2];
    u8 tail[0x18];
};

void func_0018D608(void);
void func_0018D6F0(void);
void func_001579B0(void* a, void* b, s32* out);
void func_00157320(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3);
void func_00157B88(void* a, void* b, s32* out, s32* pair);
void func_001575D8(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3, s32 p0, s32 p1);

void func_00157E00(void* a, Obj_157E00* b, void* c)
{
    Frame_157E00 f;
    if (a == 0) {
        return;
    }
    func_0018D608();
    f.flag = 1;
    func_001579B0(a, b, f.out);
    if (b->f120 == 1) {
        func_00157320(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3]);
    } else {
        if (b->f130 == 2) {
            func_00157B88(a, b, f.out, f.pair);
        } else {
            f.pair[0] = 0;
            f.pair[1] = 0;
        }
        func_001575D8(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3], f.pair[0], f.pair[1]);
    }
    func_0018D6F0();
}
