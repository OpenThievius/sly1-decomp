// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 156/152, checked 2026-11-07
#include "common.h"
#include "child_group_object.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-a): the instructions are retail's, but for the scheduling of the
// speed. Retail loads it (lw, FromFloatAt) right after the velocity and moves it into the VU
// before the vsqrt, so it takes vf4 and the end pointer reuses s0 (addiu s0,s0,0x700 late);
// here sched1 puts the lw and qmtc2 after the square root (vf2), computes the pointer into v1
// first, and the c.lt.s needs a nop. Without sched1 (-fno-schedule-insns) the registers are
// retail's. Tried: the speed's statement before and after the velocity and the length, the
// speed read back from k (reloaded across the branch) or kept in a u128 (this), the fallback
// as a ternary or if/else around MulX (both load it with lqc2, not lq/qmtc2: NormalizeOr's
// argument gives retail's lq before the test), FromFloat's float through an FPR (lwc1+mfc1),
// a union or a volatile asm (both change other functions). ContactListGlider is
// src/main/movie_player.cpp's.

struct ContactListGlider : ContactListObject {
    f32 speed6F0;           // 0x6F0
    f32 rate6F4;            // 0x6F4
    u8 pad6F8[0x700 - 0x6F8];
    Vec02 v700;             // 0x700
};

void LaunchContactListObject(ContactListObject* self);

void LaunchContactListObjectWithoutGravity(ContactListGlider* self)
{
    Vec02 k;
    LaunchContactListObject(self);
    u128 v = Vu0::Q(self->v150);
    Vu0::Q(k) = Vu0::FromFloatAt(self->speed6F0);
    u128 s = Vu0::Q(k);
    Vu0::Q(self->v700) = Vu0::MulX(Vu0::NormalizeOr(v, Vu0::Q(g_unitXVector)), s);
}
