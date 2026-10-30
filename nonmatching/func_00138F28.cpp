// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: owner and temporary register allocation, frame size, and callback scheduling differ from retail.
#include "common.h"
typedef s32 (*Func_00138F28_VFn)(void*, ...);
void func_001385A0(void*, void*, void*, s32, s32);
void func_00138F28(void* owner, void* object)
{
    *(s32*)((u8*)object + 0x4B8) = 0;
    for (u8* entry = *(u8**)((u8*)owner + 0x1AE8); entry != 0; entry = *(u8**)(entry + 8)) {
        if (*(void**)(entry + 4) == object) continue;
        s32 matching = 0;
        Func_00138F28_VFn f = *(Func_00138F28_VFn*)(*(u32**)object + 0xF0 / 4);
        if (f(object) != 0) {
            matching = 1;
        } else {
            void* other = *(void**)(entry + 4);
            f = *(Func_00138F28_VFn*)(*(u32**)other + 0xF0 / 4);
            if (f(other, object) != 0) matching = 1;
        }
        func_001385A0(owner, *(void**)((u8*)object + 0x480), entry,
                      matching ? 0 : 8, matching ? 8 : 0);
    }
}
