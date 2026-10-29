// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The broad operation is close, but register allocation, save order and
//        call setup still differ.
#include "common.h"

struct Vtable_00122488 { u8 pad0[0x20]; f32 (*get)(void*); };
struct Values_00122488 { u8 pad0[0x270]; f32* values; u8 pad274[0x20]; s32 mode; };
struct Object_00122488 {
    Vtable_00122488* vtable;
    Values_00122488* values;
    u8 pad8[0xB];
    s8 state;
};
extern f32 D_00261860;
extern f32 D_0026186C;
extern f32 D_00260E60;
extern f32 func_001EA4B8(void*, s32, f32, f32, f32);

void func_00122488(Object_00122488* self, s32 index)
{
    f32 result = self->vtable->get(self);
    if (self->state == 2) {
        self->values->values[index] = result;
    } else if (self->state == 3) {
        Values_00122488* values = self->values;
        f32 old = values->values[index];
        f32 scale = values->mode ? D_0026186C : D_00261860;
        result = func_001EA4B8(&D_00260E60, 0, old, result, scale);
        values->values[index] = result;
    }
}
