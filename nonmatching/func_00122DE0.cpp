// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 241/324 (74.4%), checked 2026-11-08
// NEAR: GetAimPoseRotation. The shape is retail's (the gravity scaled by -1 in both arms, the spring term added only with both weights nonzero, the basis built from the owner's velocity and the result). Differs in the registers (retail keeps the attachment in s1 and the owner in s0, ours the reverse), in the address of dir (retail forms `daddu a1,sp` in the prologue and stores through it after the join, ours forms it in each arm) and in where the weight f20 is loaded (retail lw's it into the dead self register after the loads of the vectors; ours with the first weight). The weights are ScalarAt (Vu0::Scalar for a float in memory: FromFloatAt into a slot of its own), which gives retail's one shared slot.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "attachment.h"
#include "anim_curve.h"
#include "globals.h"
#include "buffered_stream.h"
#include "script_value.h"

#include "collider.h"

void BuildBasisFromXAndZHint(void* x, void* hint, void* out);

// Vu0::Scalar for a float in memory: FromFloatAt into a slot of its own.
static inline u128 ScalarAt(const f32& f)
{
    Vu0::Slot t;
    Vu0::Q(t) = Vu0::FromFloatAt(f);
    return Vu0::Q(t);
}

void GetAimPoseRotation(T2195_600* self, Mat02* out, Vec02* vec)
{
    Vec02 dir;
    Vec02 vel;
    PlacedObject* owner = self->owner;
    Vu0::Q(dir) = (owner->desc->flags & 2) != 0
        ? Vu0::MulX(Vu0::Q(((Collider*)owner)->gravity), Vu0::Scalar(-1.0f))
        : Vu0::MulX(Vu0::Q(owner->world->gravity), Vu0::Scalar(-1.0f));
    Attachment* source = owner->f1EC;
    if (source != 0 && self->f20 != 0.0f && self->f1C != 0.0f) {
        source->vt->getPos(source, self->f20, 0, &vel);
        u128 w1 = ScalarAt(self->f1C);
        Vu0::Q(dir) = Vu0::MulAddX(Vu0::Q(dir), Vu0::DivX(Vu0::Sub(Vu0::Q(vel), Vu0::Q(owner->v150)), ScalarAt(self->f20)), w1);
    }
    BuildBasisFromXAndZHint(&owner->v150, &dir, out);
    *vec = D_00248D30;
}
