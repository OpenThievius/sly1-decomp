// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: helper arguments now match, but add operand ordering and values loaded into f6c4/f6c8 differ.
#include "common.h"

struct Object_13DE38 {
    u8 pad000[0x368];
    f32 scale;
    u8 pad36C[0x30C];
    s32 state;
    u8 pad67C[4];
    s32 busy;
    u8 pad684[0x40];
    s32 first;
    s32 second;
    s32 resource;
};
s32 func_0013DB28(void*, s32);
void func_001BB058(void*);
void func_001BB0C8(void*);
void func_0013DE38(Object_13DE38* self, s32* table, s32 index)
{
    if (self->busy) return;
    s32 value = *(s32*)((1 - index) * 0x40 + (u32)table);
    if (self->state) return;
    if (!func_0013DB28(self, value)) return;
    if (self->first != -1) func_001BB058(self);
    if (self->second != -1) func_001BB0C8(self);
    self->state = 1;
    self->resource = value;
    self->scale *= *(f32*)((u8*)self + 0x6C0);
}
