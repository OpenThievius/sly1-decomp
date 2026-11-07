// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 62/152 (40.8%), checked 2026-11-07
// NEAR: whether the active collider's point (its position plus half its velocity) is within f684 of the cycler. The vector work and the compare are retail's, but the result is not: retail sets a flag to 1, clears it when the compare fails and returns flag != 0 as 1 or 0 (a flag in v1, a bnez, then li 1 / move 0); ours returns the compare directly. Retail also stores the point to the stack after the Dot and gives the Dot's scratch the register vf2; ours stores the point right after the add. The forms `return active && (...)`, an `inside` local, and the early return were tried.
#include "common.h"
#include "object_cycler.h"
#include "vu0.h"

void* GetActiveSwitchedCollider(void);

static inline f32 LengthSquared(u128 d)
{
    return Vu0::ToFloat(Vu0::Dot(d, d));
}

s32 func_0015BFC0(ObjectCycler* self)
{
    Vec02 point;
    Vec02 k;
    PlacedObject* active = (PlacedObject*)GetActiveSwitchedCollider();
    if (!active)
        return 0;
    Vu0::Q(k) = Vu0::FromFloat(0.5f);
    Vu0::Q(point) = Vu0::MulAddX(Vu0::Q(active->v140), Vu0::Q(active->v150), Vu0::Q(k));
    f32 range = self->f684 * self->f684;
    s32 inside = LengthSquared(Vu0::Sub(Vu0::Q(point), Vu0::Q(self->v140))) < range;
    return inside ? 1 : 0;
}
