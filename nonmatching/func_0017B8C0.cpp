// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 185/212 (87.3%), checked 2026-11-05
#include "common.h"
// NEAR: the switch on state gives retail branch layout; the float constants and field stores in the state-1 block are scheduled in a different order

struct Obj_17B8C0 {
    u8 pad0[0x14];
    void* f14;
    u8 pad18[0x550 - 0x18];
    s32 f550;
    f32 f554;
};

struct Table_17B8C0 {
    u8 pad0[0x260];
    s32 f260;
    s32 f264;
    s32 f268;
    s32 f26C;
    s32 f270;
    s32 f274;
    f32 f278;
    f32 f27C;
};

extern s32 D_00263E2C;
extern f32 D_0026185C;
extern u8 D_0026E248[];
extern u8 D_00264A40[];

void func_001DDC38(void* a, void* b);
void func_001603E8(s32 n);
void func_0018C7F8(void* p);

void func_0017B8C0(Obj_17B8C0* self, s32 state)
{
    Table_17B8C0* t;

    if (state == self->f550) {
        return;
    }
    D_00263E2C = -1;
    switch (state) {
    case 1:
        t = (Table_17B8C0*)D_0026E248;
        t->f27C = -1.0f;
        t->f270 = 4;
        t->f268 = 0x10;
        t->f278 = 1.0f;
        t->f260 = 4;
        t->f26C = 4;
        t->f264 = 4;
        t->f274 = 0;
        func_001DDC38(self->f14, self);
        self->f550 = state;
        break;
    case 2:
        func_001603E8(5);
        func_0018C7F8(D_00264A40);
        self->f550 = state;
        break;
    default:
        self->f550 = state;
        break;
    }
    self->f554 = D_0026185C;
}
