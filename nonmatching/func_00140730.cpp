// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: GCC emits addu with reversed operands; retail uses addu v0,a0,v0.
#include "common.h"
void func_00140730(void* self, void* value)
{
    s32 i = *(s32*)((u8*)self + 0x550);
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x554) = (u32)value;
    *(s32*)((u8*)self + 0x550) = i + 1;
}
