// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 100/152 (65.8%), checked 2026-11-07
// NEAR: whether the active collider's point (its position plus half its velocity) is within f684 of the cycler. With the test inside `if (active != 0)` and `if (inside) return 1;` the flag, branches and returns are retail's. Still differs: the scheduler loads and squares f684 before the vector work and loads the velocity before the position (MulAddX's a in vf2, b in vf3; retail a vf3, b vf2), and stores the point right after the sum where retail stores it after the Dot. f684 squared inline or in a local, the difference in a local, the point stored after the test, and ToFloatMoved: no closer.
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
    if (active != 0) {
        Vu0::Q(k) = Vu0::FromFloat(0.5f);
        Vu0::Q(point) = Vu0::MulAddX(Vu0::Q(active->v140), Vu0::Q(active->v150), Vu0::Q(k));
        s32 inside = LengthSquared(Vu0::Sub(Vu0::Q(point), Vu0::Q(self->v140))) < self->f684 * self->f684;
        if (inside) {
            return 1;
        }
    }
    return 0;
}
