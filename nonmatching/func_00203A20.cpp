// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 172/196, checked 2026-11-01
// NEAR: helper behavior is modeled, but control flow, register allocation, and frame size differ from retail.
// NEAR: helper calls and behavior are modeled; control flow, register allocation, and frame layout differ.
#include "common.h"

extern s32 D_0027942C;
extern s32 D_0027AA40;
extern u8 D_0027AE48[];
extern u8 D_0027A600[];
s32 func_002033D8(s32);
s32 func_001FA7D8(void*, s32);
s32 func_001F8290(void*, s32, s32, void*, s32, void*, s32, s32, s32);
s32 func_001F6B40(s32);

s32 func_00203A20(s32 self)
{
    if (func_002033D8(0x22) != 0) {
        D_0027AA40 = self;
        func_001FA7D8(&D_0027AA40, 4);
        if (func_001F8290(D_0027AE48, 0x22, 0, &D_0027AA40, 4, D_0027A600, 4, 0, 0) >= 0) {
            func_001F6B40(D_0027942C);
            return *(s32*)((u32)D_0027A600 | 0x20000000);
        }
        func_001F6B40(D_0027942C);
    }
    return 0;
}
