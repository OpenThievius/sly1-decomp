// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the loop matches, but pointer and element registers differ.
#include "common.h"

struct Obj_12AA50 { u8 pad[0x27C]; s32 count; };
s32 func_001B5388(f32 first, f32 second);

void func_0012AA50(Obj_12AA50* self, f32 first, f32 second)
{
    for (s32 i = 0; i < self->count; i++) {
        u32 items = *(u32*)((u8*)self + 0x280);
        u32 item = *(u32*)(i * 4 + items);
        if (*(s32*)(item + 8) == 6)
            func_001B5388(first, second);
    }
}
