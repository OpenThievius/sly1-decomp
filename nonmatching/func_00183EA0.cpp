// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: remaining differences include a 64-byte candidate frame versus retail 80 bytes, register allocation, and unaligned-copy local placement.
#include "common.h"

struct State_183EA0 { u8 pad00[0x304]; u32 value; };
struct __attribute__((packed)) Unaligned_183EA0 { u64 value; };
s32 func_00182FC8(void*, void*);
void func_00183DC0(void*, void*);
void func_00127048(void*, void*);
void func_00183DF8(void*);

void func_00183EA0(State_183EA0* self, void* other)
{
    s32 changed = 0;
    if (func_00182FC8(self, other)) {
        u32 a = self->value;
        u32 b = *(u32*)((u8*)other + 0x304);
        changed = a != b;
    }
    if (changed) func_00183DC0(self, other);
    Unaligned_183EA0* slot = (Unaligned_183EA0*)((u8*)self + 0x410);
    u64 saved = slot->value;
    func_00127048(self, other);
    slot->value = saved;
    if (changed) func_00183DF8(self);
}
