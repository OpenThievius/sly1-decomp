// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: field values and offsets are identified, but the compiler loads
// the floating constants into different FPU registers and schedules their
// stores in a different order than retail.
#include "common.h"

void func_001C6F48(void* self);
void func_00167D68(void* self)
{
    func_001C6F48(self);
    *(f32*)((u8*)self + 0xC20) = 1000.0f;
    *(f32*)((u8*)self + 0x74C) = 1.04719758f;
    *(f32*)((u8*)self + 0xC24) = 1500.0f;
    *(f32*)((u8*)self + 0xC28) = 0.785398185f;
    *(f32*)((u8*)self + 0xC2C) = 3.14159274f;
    *(f32*)((u8*)self + 0xC10) = 2000.0f;
    *(s32*)((u8*)self + 0xC18) = -1;
    *(f32*)((u8*)self + 0x73C) = 300.0f;
    *(s32*)((u8*)self + 0xC30) = -1;
    *(f32*)((u8*)self + 0xC14) = 300.0f;
    *(s32*)((u8*)self + 0x738) = 0;
}
