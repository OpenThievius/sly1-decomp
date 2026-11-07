// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 132/128, checked 2026-11-07
#include "common.h"
#include "switched_collider.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-b): RotateTransposed, MulX and Sub are retail's. Retail loads
// D_00275890 with lw into a GPR (Scalar's FromFloat gives lwc1 and mfc1) and stores the
// weight after it reads effect->v150, so the store sinks to the call and the weight stays live
// past the vmulx (reading v150 into a value first gives the late store). Wants the lw form of FromFloat (worker a's FromFloatAt).

extern f32 D_00275890;
void ApplyColliderPendingImpulse(void);

// Takes the impulse at +0x490 into the frame of the glow effect's parent and removes half of
// it from the effect's v150, then applies the collider's own.
void ApplyTintBlendColliderPendingImpulse(TintBlendCollider* self)
{
    Vec02 local;
    PlacedObject* effect = (PlacedObject*)self->f748;
    Vu0::Q(local) = Vu0::RotateTransposed(((PlacedObject*)effect->parent)->m110, Vu0::Q(self->v490));
    u128 v = Vu0::Q(effect->v150);
    Vu0::Q(effect->v150) = Vu0::Sub(v, Vu0::MulX(Vu0::Q(local), Vu0::Scalar(D_00275890)));
    ApplyColliderPendingImpulse();
}
