// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the MMIO register writes are modeled in retail order, but GCC
// schedules the object field stores and helper argument setup differently,
// leaving a 12-byte size difference.
#include "common.h"

void func_001F9D60(void* self);
void func_001F9DA8(void);
void func_00211AD8(s32 a, s32 b);
void func_0020B870(void* self)
{
    *(s32*)((u8*)self + 0x818) = 1;
    *(s32*)((u8*)self + 0x1B0) = 0;
    func_001F9D60(self);
    volatile u32* regF520 = (volatile u32*)0x1000F520;
    volatile u32* regF590 = (volatile u32*)0x1000F590;
    volatile u32* rB000 = (volatile u32*)0x1000B000;
    volatile u32* rB400 = (volatile u32*)0x1000B400;
    volatile u32* rD400 = (volatile u32*)0x1000D400;
    *regF590 = *regF520 | 0x10000;
    *rB000 = 0;
    *rB400 = 0;
    *rD400 = 0;
    *regF590 = *regF520 & 0xFFFEFFFF;
    func_001F9DA8();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    *(volatile u32*)0x1000D420 = 0;
    *(volatile u32*)0x10002010 = 0x40000000;
    func_00211AD8(0,0);
}
