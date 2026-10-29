// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*VFn_125108)(void* self);

struct Vtbl_125108 {
    u8 pad0[0x5C];
    VFn_125108 f5C;
};

struct Obj_125108 {
    Vtbl_125108* vt;
};

void func_00125108(Obj_125108* self)
{
    VFn_125108 fn = self->vt->f5C;
    if (fn != 0) {
        fn(self);
    }
}

void* func_00159BB0(void);
s32 func_00182FC8(void* self);

struct Sub_126C58 {
    s32 f0;
    f32 f4;
};

struct Obj_126C58 {
    u8 pad0[0x298];
    Sub_126C58* f298;
};

void func_00126C58(Obj_126C58* self)
{
    if (self->f298 == 0) {
        self->f298 = (Sub_126C58*)func_00159BB0();
        if (func_00182FC8(self) != 0) {
            self->f298->f4 = 1.0f;
        } else {
            self->f298->f4 = 0.0f;
        }
    }
}
