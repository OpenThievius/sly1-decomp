// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 178/188 (94.7%), checked 2026-11-02
#include "common.h"

void func_001F9D60(void);
void func_001F9DA8(void);
void func_00211AD8(s32 a, s32 b);

struct Chan_20B870 {
    u8 pad0[0x1B0];
    s32 f1B0;
    u8 pad1[0x818 - 0x1B4];
    s32 f818;
};

void func_0020B870(Chan_20B870* c) {
    c->f818 = 1;
    c->f1B0 = 0;
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 = 0;
    *(volatile u32*)0x1000B400 = 0;
    *(volatile u32*)0x1000D400 = 0;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    *(volatile u32*)0x1000D420 = 0;
    *(volatile u32*)0x10002010 = 0x40000000;
    func_00211AD8(0, 0);
}
