// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 106/152 (69.7%), checked 2026-11-08
// Night-moved (2026-11-08): NormalizeOrMoved gives the size (152) and cuts the differing words from 23 to 13; left: the speed (lw) goes into vf2 after the maddz where retail loads it first and moves it into vf4; norm-first orders and Scalar made it worse.
// Wave 4 (night-lever1, 6 compiles): Vec::ScalarAt, Vec::Of, FromFloatAt into a Vec with and without the k store, the speed ahead of or inside the MulX call: the lw stays after the maddz (retail: lw first, qmtc2 vf4 after the maddz so the speed lives across Dot's vf2); Vec::ScalarAt puts the speed in vf1 and the sqrt in vf4; the inline MulX argument order evaluates the speed last.
// Night-low1 (2026-11-08, 5 compiles): the result named and stored after (u128 r = MulX(...); Q(self->v700) = r, or Set) gives retail's lw v0 and qmtc2 v0,vf4 but folds the destination into the store (sqc2 vf1,1792(s0), 4 bytes short, where retail forms addiu s0,s0,1792 before the branch); a pointer to v700 taken before the sum brings back this form's addiu v1 first and lw s0.
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
    Vu0::Q(self->v700) = Vu0::MulX(Vu0::NormalizeOrMoved(v, Vu0::Q(g_unitXVector)), s);
}
