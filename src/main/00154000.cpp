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
