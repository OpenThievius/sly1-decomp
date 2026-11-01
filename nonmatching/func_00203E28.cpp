// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 164/184, checked 2026-11-01
// NEAR: helper behavior is modeled, but control flow, register allocation, and frame size differ from retail.
// NEAR: helper calls and return value are modeled; control flow, register allocation, and frame layout differ.
#include "common.h"

extern u8 D_0027AE48[];
extern volatile s32 D_00279454;
extern s32 D_0027942C;
extern u8 D_0027A600[];
s32 func_002033D8(s32);
s32 func_001F8290(void*, s32, s32, s32, s32, void*, s32, s32, s32);
s32 func_001F6B40(s32);

s32 func_00203E28(void)
{
    if (func_002033D8(0x1E) != 0) {
        D_00279454 = 8;
        if (func_001F8290(D_0027AE48, 0x16, 0, 0, 0, D_0027A600, 4, 0, 0) >= 0) {
            D_00279454 = 0;
            func_001F6B40(D_0027942C);
            return *(s32*)((u32)D_0027A600 | 0x20000000);
        }
        func_001F6B40(D_0027942C);
        D_00279454 = 0;
    }
    return 0;
}
