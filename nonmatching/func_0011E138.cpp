// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: both synchronization paths and the message payload are modeled.
// The compiler allocates the persistent registers differently and uses a
// 112-byte frame; retail uses a 96-byte frame.
#include "common.h"

extern s32 D_0025C34C;
extern s32 D_0025C354;
extern s32 D_0025C358;
extern s32 D_00260DC0;
s32 func_00203B18(void);
s32 func_0011E1F8(s32 flag);
s32 func_0011DB00(s32 id, s32 size, void* args, s32 a3, s32 a4);

s32 func_0011E138(void* a0, s32 a1, s32 a2)
{
    if (D_0025C34C == 0) {
        return func_00203B18();
    }
    if (func_0011E1F8(1) == 1) {
        return 0;
    }
    s32 args[5];
    args[0] = (s32)a0;
    args[1] = a1;
    args[2] = a2;
    args[4] = 0;
    D_00260DC0 = 1;
    func_0011DB00(0x38, 0xC, args, 0, 0);
    D_0025C354 = 1;
    D_0025C358 = 0;
    return 1;
}
