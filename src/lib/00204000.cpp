// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

f32 func_00205318(f32 x)
{
    s32 i0 = *(s32*)&x;
    s32 j0 = ((i0 >> 23) & 0xff) - 0x7f;
    s32 i;

    if (j0 < 0x17) {
        if (j0 < 0) {
            if (1.0e30f + x > 0.0f) {
                if (i0 >= 0) {
                    i0 = 0;
                } else if ((i0 & 0x7fffffff) != 0) {
                    i0 = 0xbf800000;
                }
            }
        } else {
            i = 0x7fffff >> j0;
            if ((i0 & i) == 0) {
                return x;
            }
            if (1.0e30f + x > 0.0f) {
                if (i0 < 0) {
                    i0 += 0x800000 >> j0;
                }
                i0 &= ~i;
            }
        }
    } else {
        if (j0 == 0x80) {
            return x + x;
        }
        return x;
    }
    *(s32*)&x = i0;
    return x;
}
