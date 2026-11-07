// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 101/128 (78.9%), checked 2026-11-07
#include "common.h"
#include "switched_collider.h"
#include "vu0.h"

extern f32 D_00275890;
void ApplyColliderPendingImpulse(void);
// NEAR (2026-11-08, wave 3 retry): with FromFloatAt, the weight in a u128 that the store to k
// and the MulX share, and v150 read into a value first, every VU0 instruction and store is
// retail's. Only the general registers differ: retail loads the weight first (lui v0, lw
// v0,22672(v0)) and the effect into a2; here lui a2, the effect in a1 and the weight in a0. The
// weight read before or after the effect, and the frame vector read into a value, give the
// same.
void ApplyTintBlendColliderPendingImpulse(TintBlendCollider* self)
{
    Vec02 local;
    Vec02 k;
    u128 s = Vu0::FromFloatAt(D_00275890);
    PlacedObject* effect = (PlacedObject*)self->f748;
    Vu0::Q(local) = Vu0::RotateTransposed(((PlacedObject*)effect->parent)->m110, Vu0::Q(self->v490));
    u128 v = Vu0::Q(effect->v150);
    Vu0::Q(k) = s;
    Vu0::Q(effect->v150) = Vu0::Sub(v, Vu0::MulX(Vu0::Q(local), s));
    ApplyColliderPendingImpulse();
}
