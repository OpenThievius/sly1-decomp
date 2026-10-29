// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_5E08 {
    u8 pad0[0x624];
    void* f624;
};

struct Vtbl_5E08 {
    void* slots[0x148 / 4];
};

typedef void (*VFn_5E08)(void* self);

void func_001924C8(void* self);

void func_001E5E08(void* self)
{
    Obj_5E08* o = (Obj_5E08*)self;

    if (o->f624 != 0) {
        VFn_5E08 fn = *(VFn_5E08*)(*(u8**)o->f624 + 0x148);
        fn(o->f624);
    } else {
        func_001924C8(self);
    }
}

struct Obj_E7440 { u8 pad[0x260]; s32 f260; f32 f264; };
extern f32 D_00261868;

void func_001E7440(Obj_E7440* a0, s32 a1)
{
    if (a1 != a0->f260) {
        a0->f260 = a1;
        a0->f264 = D_00261868;
    }
}

struct Ptr_1E76E0 {
    s32 f0;
    union {
        s32 i4;
        f32 f4;
    };
};

struct Obj_1E76E0 {
    u8 pad0[0x218];
    Ptr_1E76E0* f218;
    u8 pad1[0x250 - 0x21C];
    s32 f250;
    u8 pad2[0x268 - 0x254];
    s32 f268;
};

extern s32 D_00270458;
void func_001AA998(void* self, s32 flag);
void func_001AAB20(void* self, f32 x, f32 y);
void func_001E7518(void* self, s32 mode);

void func_001E76E0(Obj_1E76E0* self, s32 value)
{
    s32 old = self->f250;
    func_001AA998(self, value);
    if (old == value) return;
    if (old != 0) goto done;
    if (D_00270458 == 4) {
        self->f218->i4 = 0;
        func_001AAB20(self, 640.0f, 360.0f);
    } else {
        self->f218->f4 = -20.0f;
        func_001AAB20(self, 160.0f, 125.4f);
    }
done:
    if (value != 2) return;
    if (D_00270458 == 4) return;
    self->f268 = -1;
    func_001E7518(self, 3);
}
