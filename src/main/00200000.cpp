// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
s32 func_002006F0(void*);
u32 func_002014F0();
u32 func_00201BA8();
u32 func_002027A0(u32);
extern s32 D_0027696C;
extern u32 D_00279340[];
s32 func_002006F0(void* p) { return *(s32*)p; }
u32 func_002014F0() { return D_0027696C; }
extern u8 D_00279330[];
u32 func_00201BA8() { return (u32)D_00279330; }
u32 func_002027A0(u32 index) { if (index >= 10) return 0; return D_00279340[index]; }
extern s32 D_00279454;
extern u32 D_0027A5C0[];
s32 func_00203AE8() { if (D_00279454 != 1) return 0; return *(u32*)((u32)D_0027A5C0 | 0x20000000) ; }
