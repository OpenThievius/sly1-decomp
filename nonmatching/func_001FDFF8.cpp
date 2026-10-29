// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: This candidate is 144 bytes versus retail 136; save width and
//        register assignment differ.
#include "common.h"

extern void* func_002014D0(void);

void* func_001FDFF8(s32 index, u8* object, s32 unused)
{
    s8* types = (s8*)(object + 668);
    while (types[index] == 2) {
        index = *(s32*)((u8*)object + 28 + index * 8);
    }
    if (types[index] == 1) {
        return object + *(s32*)object + *(s32*)((u8*)object + 24 + index * 8);
    }
    return func_002014D0();
}
