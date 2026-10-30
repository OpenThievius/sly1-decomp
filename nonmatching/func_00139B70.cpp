// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the setup calls mostly match, but argument scheduling, constants, and frame size differ from retail.
#include "common.h"
void func_001611B8(void*);
void func_001528F0(void*, s32);
void func_001613C0(void*, s32, s32, s32);
void func_00161708(void*, s32, s32);
void func_001612F8(void*, s32, s32, s32, u64, s32);
void func_00152D70(void*);
void func_001529E0(void*, s32, s32);
void func_00139B70(u64 value, s32 arg)
{
    u8 local[0x30];
    func_001611B8(local);
    func_001528F0(local, 4);
    func_001613C0(local, 0, 1, 14);
    func_00161708(local, 0x47, 0x7180B);
    func_00161708(local, 0x42, (value << 2) | 0x40);
    func_001612F8(local, 0x54, 0, 10, 0x42424242412EULL, 0);
    func_00152D70(local);
    func_001529E0(local, 0, arg);
}
