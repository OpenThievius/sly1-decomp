// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the callback flow is modeled, but register allocation and sq/lq saves differ from retail sd/ld.
// NEAR: body and callback arguments line up; allocator and SN sq/lq saves differ from retail sd/ld.
#include "common.h"

typedef void* (*Factory_200D58)(void);
typedef s32 (*Value_200D58)(void);
typedef void (*Apply_200D58)(void*, s32, s32, s32, s32, s32);

void func_00200D58(Factory_200D58 factory, Value_200D58 firstValue, s32 arg2, s32 arg3, Value_200D58 secondValue, s32 arg5)
{
    void* object = factory();
    u8* state = *(u8**)((u8*)object + 4);
    s16 offset = *(s16*)(state + 0x10);
    state += 0x10;
    s32 first = firstValue();
    object = (u8*)object + offset;
    s32 second = secondValue();
    Apply_200D58 apply = *(Apply_200D58*)(state + 4);
    apply(object, first, arg2, arg3, second, arg5);
}
