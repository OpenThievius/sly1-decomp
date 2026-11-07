// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
u32 func_002027A0(u32);
extern u32 D_00279340[];
u32 func_002027A0(u32 index) { if (index >= 10) return 0; return D_00279340[index]; }
extern s32 D_00279454;
extern u32 D_0027A5C0[];
s32 func_00203AE8() { if (D_00279454 != 1) return 0; return *(u32*)((u32)D_0027A5C0 | 0x20000000) ; }
