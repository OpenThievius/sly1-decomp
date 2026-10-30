// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the hardware-status poll and timeout callback are modeled, but loop-counter scheduling, register allocation, and frame size differ from retail.
// NEAR: the hardware-status poll and timeout callback are modeled in plain C++. The loop counter schedule, register allocation, and frame size differ from retail.
#include "common.h"

struct Object_20F0F0 { u8 pad00[0x858]; s32 wait; };
extern void func_0020B1E0(s32);

s32 func_0020F0F0(Object_20F0F0* self)
{
    volatile u32* status = (volatile u32*)0x10002010;
    u32 mask = 0x80004000;
    if ((*status & mask) != 0x80000000)
        return 0;
    s32 count = 0;
    do {
        if (count >= 5001) {
            func_0020B1E0(self->wait);
            count = 0;
        }
        count++;
    } while ((*status & mask) == 0x80000000);
    return count;
}
