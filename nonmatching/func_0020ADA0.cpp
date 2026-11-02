// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 150/156 (96.2%), checked 2026-11-02
#include "common.h"

void func_001F9D60(void);
void func_001F9DA8(void);
void func_00211BA8(void);

void func_0020ADA0(void) {
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 &= 0xFFFFFEFF;
    *(volatile u32*)0x1000B400 &= 0xFFFFFEFF;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    func_00211BA8();
}
