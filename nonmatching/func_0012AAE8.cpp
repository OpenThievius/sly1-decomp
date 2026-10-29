// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the loop is modeled, but register allocation and branch shape differ from retail.
#include "common.h"
void func_00159A00(f32);
void func_0012AAE8(void*, f32);
void func_0012AAE8(void* object, f32 value)
{
    for (s32 i = 0; i < *(s32*)((u8*)object + 0x27C); ++i) {
        void* item = ((void**)((u8*)object + 0x280))[i];
        if (*(s32*)((u8*)item + 8) == 5) {
            func_00159A00(value);
        }
    }
    void* node = *(void**)((u8*)object + 0x34);
    if (node != 0) {
        void* item = *(void**)node;
        do {
            if ((*(u32*)((u8*)item + 8) & 1) != 0) {
                func_0012AAE8(node, value);
            }
            node = *(void**)((u8*)node + 0x1C);
            if (node != 0) item = *(void**)node;
        } while (node != 0);
    }
}
