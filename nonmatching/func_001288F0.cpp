// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 180/168, checked 2026-11-01
// NEAR: stack frame, register allocation, and control-flow scheduling still differ from retail.
#include "common.h"
extern u32 D_0027B314;
s32 func_001C1A28(void*, void**);
s32 func_001288F0(void*, void*);
s32 func_001288F0(void* object, void* context)
{
    u32 frame[8];
    frame[0] = (u32)((u8*)object + 0x34);
    frame[1] = frame[0];
    u32 old = D_0027B314;
    frame[3] = old;
    D_0027B314 = (u32)frame;
    u32 step = *(u32*)((u8*)object + 0x3C);
    void* current = *(void**)((u8*)object + 0x34);
    frame[2] = step;
    frame[1] = (u32)current + step;
    frame[4] = (u32)current;
    s32 result = 1;
    while (current != 0) {
        if (func_001C1A28(context, &current) == 0) {
            result = 0;
            break;
        }
        current = *(void**)(frame[1]);
        frame[1] = (u32)current + frame[2];
        frame[4] = (u32)current;
    }
    D_0027B314 = frame[3];
    return result;
}
