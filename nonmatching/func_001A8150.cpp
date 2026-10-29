// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports 184 bytes vs retail's 180; index increment, slot address, and flag masking instruction order differ.
#include "common.h"
s32 func_0018D5C0(s32);
struct Item_A8150 { s32 first, second, pad[2], flags; };
struct Self_A8150 { u8 pad[0x34]; s32 index; s32 count; Item_A8150* items; };
void func_001A8150(Self_A8150* self, s32 x, s32 y, s32 flags, s32 mode)
{
    if (!self->items) self->items=(Item_A8150*)func_0018D5C0(0x50);
    s32 i=self->count++;
    Item_A8150* item=(Item_A8150*)((u8*)self->items+0x14*i);
    item->first=x; item->second=y;
    item->flags=(item->flags & -2) | (flags&1);
    item->flags=(item->flags & -3) | ((mode&1)<<1);
}
