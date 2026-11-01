// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 48/200, checked 2026-11-01
// NEAR: the high-level behavior is modeled, but GCC removes retail dimension calculations and the MMI multiply as dead code.
// NEAR: GCC reduces this to a short mode return and removes the dimension calculations and MMI multiply seen in retail.
#include "common.h"

u8* func_00201BA8(void);

s32 func_002023B0(s32 flags, s32 x, s32 y)
{
    x = (s16)x;
    y = (s16)y;
    u8* frame = func_00201BA8();
    s32 maxX = x + 126;
    if (x + 63 > -1) {
        maxX = x + 63;
    }
    s32 tilesX = maxX >> 6;
    s32 maxY;
    s32 shift;
    if ((flags & 2) != 0) {
        maxY = y + 126;
        if (y + 63 > -1) {
            maxY = y + 63;
        }
        shift = 6;
    } else {
        maxY = y + 62;
        if (y + 31 > -1) {
            maxY = y + 31;
        }
        shift = 5;
    }
    s32 tilesY = maxY >> shift;
    u32 mode = *(u32*)frame;
    if (mode == 1) {
        return mode;
    }
    return mode << 1;
}
