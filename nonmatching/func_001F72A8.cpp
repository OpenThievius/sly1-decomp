// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 152/176, checked 2026-11-01
// Near match: register allocation and the newline path's tail jump differ.
#include "common.h"

extern s32 D_0027712C;
extern u8 D_00625F80[0x80];
void* func_001FA140(void* string);

void* func_001F72A8(s32 value)
{
    s32 count = D_0027712C;
    if (count >= 0x7E) {
        D_0027712C = 0;
        D_00625F80[0x7F] = 0;
        func_001FA140(D_00625F80);
        count = D_0027712C;
    }
    if (value == 10) {
        D_0027712C = 0;
        D_00625F80[count] = (u8)value;
        D_00625F80[count + 1] = 0;
        return func_001FA140(D_00625F80);
    }
    D_0027712C = count + 1;
    D_00625F80[count] = (u8)value;
    return D_00625F80 + count;
}
