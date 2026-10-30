// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the readiness polling and flag return paths are modeled. The
// compiler keeps an extra saved register for the two globals and grows the
// function to 176 bytes instead of retail's 168.
#include "common.h"

extern s32 D_0025C34C;
extern u32 D_00260DC0;
extern u32 D_0025C358;
s32 func_002032C8(s32 value);
void func_001F6C20(s32 value);
s32 func_0011CE30(void);

s32 func_0011E1F8(s32 flag)
{
    if (D_0025C34C == 0) {
        return func_002032C8(flag);
    }
    func_001F6C20(0);
    u32 ready = D_00260DC0 < 1;
    D_0025C358 = ready;
    if (ready == 1) {
        return 0;
    }
    if (flag == 1) {
        return 1;
    }
    do {
        func_0011CE30();
        func_001F6C20(0);
        ready = D_00260DC0 < 1;
        D_0025C358 = ready;
    } while (ready == 0);
    return 0;
}
