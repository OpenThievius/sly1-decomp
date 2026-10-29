// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: wrapper calls and float arguments are modeled, but saved-register allocation differs.
#include "common.h"

void* func_00155778(void*, s32);
void func_00158198(void*, void*, void*, void*, f32, f32, f32, f32);
void func_001557D0(void* owner, void* first, void* second, void* third,
                   f32 x, f32 y, f32 z, f32 w)
{
    void* record = func_00155778(owner, 1);
    func_00158198((u8*)record + 0x10, first, second, owner, x, y, z, w);
}
