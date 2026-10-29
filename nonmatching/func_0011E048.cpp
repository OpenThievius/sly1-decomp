// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: field packing and stack-store scheduling differ from retail.
#include "common.h"
extern s32 func_0011D968(s32, s32, void*);
void func_0011E048(u32 a0, u32 a1, u16 a2, u16 a3, u16 a4, u16 a5, u32 a6, u32 a7, u32 a8)
{
    u32 local[7];
    local[6] = a8;
    local[3] = ((u32)a5 << 16) | a3;
    local[2] = ((u32)a4 << 16) | a2;
    local[0] = a0;
    local[1] = a1;
    local[4] = a6;
    local[5] = a7;
    func_0011D968(0x2C, 28, local);
}
