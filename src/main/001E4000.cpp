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
