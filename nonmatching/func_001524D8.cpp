// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: This candidate is 108 bytes versus retail 104; save order, register
//        allocation and store order differ.
#include "common.h"
struct Pair_1524D8 { u32 first, second; };
u32 func_00152460(Pair_1524D8*, u32);
void func_001524D8(Pair_1524D8* self, u32 value)
{
    u32* slot = (u32*)func_00152460(self, value);
    u32 first = self->first;
    if (first == 0) {
        self->first = value;
        self->second = value;
    } else {
        u32* oldHead = (u32*)func_00152460(self, first);
        *oldHead = first;
        slot[1] = value;
        self->first = value;
    }
}
