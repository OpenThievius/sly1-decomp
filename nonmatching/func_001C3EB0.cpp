// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 192/180, checked 2026-11-07
#include "common.h"
#include "placed_object.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-a): retail's normalisation with the unit x fallback
// (NormalizeOr), scaled by D_00274AB4 and handed to the receiver's slot 32 (SetColliderVelocity).
// Retail loads the scale (lw, qmtc2 vf4) first and keeps it in vf4 across the test; here it is
// stored to k and loaded back after the join (lqc2 vf1, 0x20(sp)), the result's pointer is
// formed before the test (addiu v0,sp,0x10; move a3), and the branch is laid out the other way
// (bc1t to the join). Kept in a u128 (as in func_0018DDD8) the scale stays in a register but is
// scheduled after the square root. a0 (the reply's value) is the sending object.

extern f32 D_00274AB4;

void func_001C3EB0(s32 c, void* receiver)
{
    PlacedObject* from = (PlacedObject*)c;
    PlacedObject* to = (PlacedObject*)receiver;
    Vec02 d;
    Vec02 v;
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloatAt(D_00274AB4);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(to->v140), Vu0::Q(from->v140));
    d.z = 0.0f;
    Vu0::Q(v) = Vu0::MulX(Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector)), Vu0::Q(k));
    to->desc02()->m20(to, &v);
}
