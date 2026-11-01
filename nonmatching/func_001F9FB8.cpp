// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 168/172, checked 2026-11-01
// NEAR: helper call flow largely aligns, but loop pointer stride/branch and save/load sequence differ (candidate +4 versus retail +8).
#include "common.h"
struct Table_1F9FB8 { void* first; void* second; void* third; void* fourth; u8 data[0x20]; };
extern Table_1F9FB8 D_00277998;
extern u8 D_002771F0[];
s32 func_001F9F50(void);
void func_001F9EE8(void*, void*);
void func_001F9EF8(void*, void*, s32);
void func_001F6C20(s32);
void* func_001F9F40(void*);
void func_001F9FB8(void)
{
    if (!func_001F9F50()) return;
    func_001F9EE8(D_00277998.first, D_00277998.second);
    func_001F9EF8((void*)0x80074000, D_002771F0, 0x7A8);
    func_001F6C20(0);
    func_001F6C20(2);
    func_001F9EE8(D_00277998.third, D_00277998.fourth);
    void** p = (void**)&D_00277998.data[0x10];
    for (s32 i=2; i<3; ++i,++p) func_001F9EE8(*p, func_001F9F40(*p));
}
