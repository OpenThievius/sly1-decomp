// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

u32 func_0020DEE8(u32 value)
{
    u32* setting = (u32*)0x10002010;
    u32 result = (*setting & 0xFF7FFFFFu) | (value << 23);
    *setting = result;
    return result;
}

struct Obj_20F0C0 { u8 pad[0x818]; u32 value; };
extern u32 D_0027B040[];

void func_0020F0C0(Obj_20F0C0* obj, u32 value)
{
    u32 index = value >> 28;
    volatile u32* setting = (volatile u32*)0x10002000;
    *setting = value;
    obj->value = D_0027B040[index];
}

