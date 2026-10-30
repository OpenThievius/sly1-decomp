// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern s32 D_002779B0;

void func_001FA0A0(void)
{
    D_002779B0 = 0;
}

s32 func_001FA0D8(void)
{
    return 1;
}

s32 func_001FA1B0(s32* src, s32* dst)
{
    s32 value = src[4];
    dst[2] = value;
    return value;
}

extern s32 D_006294C0[];

s32 func_001FA1C0(s32 index)
{
    return D_006294C0[index];
}

extern s32 D_006293A4;
extern s32 D_006293AC;

void func_001FA4A0(s32 index, s32 first, s32 second)
{
    s32 scaled = index << 3;
    if (index < 0) {
        index = D_006293A4;
    } else {
        index = D_006293AC;
    }
    scaled += index;
    s32* p = (s32*)scaled;
    p[0] = first;
    p[1] = second;
}
