// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 224/280 (80.0%), checked 2026-11-07
#include "common.h"
#include "switched_collider.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-c): the same instructions but for the order and registers of
// the loop's body and the first block. Retail loads FLT_MAX (lwc1 from 0x24DA90) before the
// first MulAddX and keeps the count in a0 copied to a1; here the count is a1 and FLT_MAX comes
// after. In the loop retail gives the position vf2, the velocity vf1 and Dot's 1.0 vf3, and
// stores the lead time (sqc2 vf4) after the vmaddx; here vf3, vf2, vf2 and the store first.
// Tried: the lead time set before or after the velocity, inside the MulAddX call; best and pick
// set first; a pointer walk counting down (worse); the difference held in a u128. The vmove
// pair before the loop is the compiler's own (the lead time and the position kept across it).
// Retail also loads D_00274CF0 with lw straight into the GPR for the qmtc2; FromFloat on a float
// gives lwc1 and mfc1. A FromFloat that passes the float's bits as an int (a union) gives the lw
// here and in func_001A31A0, but func_001BC828 (a computed float) then takes v1 for the mfc1
// where retail has v0, so the header keeps the float form.

extern float D_00274CF0;

s32 GatherObjectsByMode(World* host, s32 a1, s32 a2, s32 a3, s32 a4, PlacedObject** out);

void func_001CAB10(Agent* self)
{
    PlacedObject* found[0x20];
    Vec02 vel;
    Vec02 here;
    Vec02 there;
    Vec02 lead;
    s32 n = GatherObjectsByMode(self->world, 5, self->fB4C, 0, 0x20, found);
    PlacedObject* pick = 0;
    f32 best = 3.40282347e+38f;
    vel = self->v150;
    vel.z = 0.0f;
    Vu0::Q(lead) = Vu0::FromFloat(D_00274CF0);
    Vu0::Q(here) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(vel), Vu0::Q(lead));
    for (s32 i = 0; i < n; i++) {
        PlacedObject* obj = found[i];
        vel = obj->v150;
        vel.z = 0.0f;
        Vu0::Q(lead) = Vu0::FromFloat(D_00274CF0);
        Vu0::Q(there) = Vu0::MulAddX(Vu0::Q(obj->pos), Vu0::Q(vel), Vu0::Q(lead));
        u128 delta = Vu0::Sub(Vu0::Q(here), Vu0::Q(there));
        f32 d = Vu0::ToFloat(Vu0::Dot(delta, delta));
        if (obj == self->fB48) {
            d *= 0.5f;
        }
        if (d < best) {
            best = d;
            pick = obj;
        }
    }
    self->fB48 = pick;
    self->fB40 = 1;
}
