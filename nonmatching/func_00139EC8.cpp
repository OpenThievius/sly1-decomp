// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: stack traversal and helper calls are modeled, but frame size and register allocation differ from retail.
#include "common.h"
extern u32 D_0027B314;
extern u8 D_002622E0[];
void func_00139D28(void*);
void func_00152600(u32, void*);
void func_00152470(void*, void*);
void func_001243E0(void*);
void func_00139EC8(void* object)
{
    u32 frame[4];
    frame[3] = D_0027B314;
    D_0027B314 = (u32)frame;
    u8* current = *(u8**)((u8*)object + 0x624);
    u32 stride = current ? *(u32*)(current + 8) : 0;
    u8* cursor = current + stride;
    while (current != 0) {
        func_00139D28(current);
        current = *(u8**)cursor;
        cursor = current + stride;
    }
    func_00152600(*(u32*)((u8*)object + 0x14) + 0x1CB4, object);
    func_00152470(D_002622E0, object);
    func_001243E0(object);
    D_0027B314 = frame[3];
}
