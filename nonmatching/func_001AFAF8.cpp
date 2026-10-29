// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: operand/load order and the bitfield load/sign-extension sequence still differ.
#include "common.h"

struct Object_1AFAF8 {
    u8 pad00[0x50]; s32 state50;
    u8 pad54[0x278]; u32 bit2CC;
    u8 pad2D0[0x268]; u64 flags538;
    u8 pad540[0x1CE0]; s32 state2220;
    u8 pad2224[0x178]; s32 state239C;
};
struct Other_1AFAF8 { u8 pad00[0x50]; s32 state50; };
extern Object_1AFAF8* D_00262E10;
s32 func_001AEE50(void);
s32 func_00160D10(void);

s64 func_001AFAF8(Other_1AFAF8* other, Object_1AFAF8* self)
{
    if (self->flags538 & 0x0000080000000000ull) return 0;
    s32 current = self->state50;
    s32 previous = other->state50;
    if (current == previous) return 0;
    if (func_001AEE50()) return 0;
    if (self != D_00262E10) goto result;
    if (self->state2220 != 6) goto result;
    if (self->state239C != 3) goto result;
    if (func_00160D10() & 0x12000) return 0;
result:
    return (((s64)(s32)self->bit2CC) ^ 1ll) & 1ll;
}
