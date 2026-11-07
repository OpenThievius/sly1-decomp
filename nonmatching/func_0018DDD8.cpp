// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 156/152, checked 2026-11-07
#include "common.h"
#include "child_group_object.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-08, wave 3 retry): FromFloatAt (already used) leaves the scheduling: retail
// loads the speed (lw) right after the velocity, before the first vmul, and moves it into vf4
// before the vsqrt; here sched1 puts the lw and the qmtc2 after the square root (vf2), forms
// the end pointer first and the c.lt.s needs a nop. Re-tried in wave 3 with the same body:
// unchanged.
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
