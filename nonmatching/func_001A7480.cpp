// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: state comparisons and dispatch are modeled, but the helper
// object's child offsets and likely-branch delay-slot store still differ.
#include "common.h"

struct Obj_1A7480 { void** vtbl; u8 pad0[0x550 - sizeof(void*)]; s32 state; f32 value; void* child558; u8 pad2[4]; void* child564; };
extern f32 D_0026185C;
extern u32 D_0026B860[];
void func_001A5B28(void* child, void* self);
void func_001B6628(void* child, s32 value);
void func_001B64D8(void* child, s32 value);
void func_001A7480(Obj_1A7480* self, s32 state)
{
    s32 old = self->state;
    if (state == old) return;
    if (old != 9) goto skip_1A7480;
    func_001A5B28(self->child558, self);
skip_1A7480:
    self->state = state;
    self->value = D_0026185C;
    if (self->child564 != 0) {
        s32 arg = D_0026B860[state];
        if (old == -1) func_001B6628(self->child564, arg);
        else func_001B64D8(self->child564, arg);
    }
}
