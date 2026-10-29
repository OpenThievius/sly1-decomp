// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: This candidate is 52 bytes versus retail 48; save width and
//        branch/register selection differ.
#include "common.h"

extern void* func_001FDA10(void);
extern void* func_001FE8F0(void);

void func_001FEBE0(void)
{
    void* current = *(void**)func_001FDA10();
    if (current == 0) {
        current = func_001FE8F0();
        *(s32*)((u8*)current + 20) = 0;
    }
}
