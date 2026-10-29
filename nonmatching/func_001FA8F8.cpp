// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the body mostly matches, but loop branch/delay-slot shape and saved-register opcodes differ from retail.
#include "common.h"
extern u32 D_00277D30[];
extern u32 D_002779C0[];
void func_001FA8E8(u32, u32);
void func_001FA890(u32, u32*, u32);
void func_001F6C20(s32);
u32 func_001FA8D8();
void func_001FA8F8()
{
    u32* table = D_00277D30;
    u32 index = 3;
    func_001FA8E8(table[0], table[1]);
    func_001FA890(0x80075000, D_002779C0, 0x328);
    func_001F6C20(0);
    func_001F6C20(2);
    func_001FA8E8(table[2], table[3]);
    func_001FA8E8(table[4], table[5]);
    u32* pair = table + 6;
    do {
        u32 value = func_001FA8D8();
        func_001FA8E8(pair[0], value);
        pair += 2;
        index++;
    } while (index < 8);
}
