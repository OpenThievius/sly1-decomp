// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The body is close; register-save width and one zero-value instruction
//        still differ.
#include "common.h"

extern void* func_0018D740(s32);
extern void func_001FD930(void*);
extern void func_001F5C0C(void*, s32, u32);

void* func_001FD990(void)
{
    u8* object = (u8*)func_0018D740(24);
    if (object == 0) {
        func_001FD930(object);
    }
    func_001F5C0C(object, 0, 24);
    *(u8**)(object + 4) = object + 16;
    return object;
}
