// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 139/176 (79.0%), checked 2026-11-01
// NEAR: check.py reports DIFFER; register allocation and ordering around the state compare and first virtual call differ.
#include "common.h"

typedef void (*Method0_1C8F20)(void*);
typedef void (*Method2_1C8F20)(void*, s32, void*);
struct Self_1C8F20 {
    void** vtbl;
    u8 pad04[0x720];
    s32 state;
    f32 value;
    s32 flags;
};
struct Frame_1C8F20 { void* oldSlot; void* stateSlot; u8 pad08[8]; s32 oldState; };
extern f32 D_0026185C;
void func_001837E0(void*, s32, s32, void*);

void func_001C8F20(Self_1C8F20* self, s32 state, void* context)
{
    self->flags &= -2;
    if (self->state == state) return;
    Frame_1C8F20 frame;
    frame.oldState = self->state;
    ((Method0_1C8F20)self->vtbl[95])(self);
    self->state = state;
    self->value = D_0026185C;
    ((Method2_1C8F20)self->vtbl[96])(self, frame.oldState, context);
    frame.oldSlot = &frame.oldState;
    frame.stateSlot = &self->state;
    func_001837E0(self, 15, 2, &frame);
}
