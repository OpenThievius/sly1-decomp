// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: This candidate is 184 bytes versus retail 168; branch direction and
//        floating-point register use differ.
#include "common.h"

struct Vtable_00126CB8 { u8 pad0[0x18]; void (*update)(void*); };
struct Timed_00126CB8 { u8 pad0[4]; f32 rate; f32 result; };
struct Object_00126CB8 { Vtable_00126CB8* vtable; u8 pad4[0x294]; Timed_00126CB8* timed; };
extern s32 func_00182FC8(void*);
extern void func_00126C58(void*);

void func_00126CB8(Object_00126CB8* self, f32 step)
{
    if (func_00182FC8(self) && self->timed) {
        return;
    }
    func_00126C58(self);
    self->vtable->update(self);
    f32 value;
    if (step == 0.0f) {
        value = 1.0f - self->timed->rate + 0.01f;
        if (value < 0.0f) value = 0.0f;
    } else {
        value = 1.0f / step;
    }
    self->timed->result = value;
}
