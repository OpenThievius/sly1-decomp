// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern s32 D_00262474;
extern u8 D_002622A8[];

void func_001EE3B8(void* obj, s32 size, s32 flags);

void func_00166658(void)
{
    s32 v = 0x23C - D_00262474;
    D_00262474 = v;
    func_001EE3B8(D_002622A8, v, 0);
}

void func_001CA5E0(void);

void func_00167EF0(void)
{
    func_001CA5E0();
}
