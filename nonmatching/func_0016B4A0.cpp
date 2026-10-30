// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: calls and field values match, but GCC schedules the final zero
// stores and floating constant load in a different order than retail.
#include "common.h"

extern u8 D_00262988[];
extern f32 D_00262970[];
void func_001AA268(void* self);
s32 func_0015C188(s32 index);
void* func_0015C1C0(s32 index);
void func_001AA8B8(void* self, f32 zero);

void func_0016B4A0(void* self)
{
    func_001AA268(self);
    if (func_0015C188(2)) {
        *(void**)((u8*)self + 0x210) = D_00262988;
        s32 value = (s32)func_0015C1C0(2);
        **(s32**)((u8*)self + 0x210) = value;
    }
    func_001AA8B8(self, 0.0f);
    *(u32*)((u8*)self + 0x260) = 0;
    *(u32*)((u8*)self + 0x208) = 0xDF7F7F7F;
    *(u32*)((u8*)self + 0x264) = 0;
    *(f32*)((u8*)self + 0x268) = -D_00262970[0];
}
