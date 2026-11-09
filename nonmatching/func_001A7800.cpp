// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 372/408 (91.2%), checked 2026-11-09
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call 1 (source line 50); 25 differing lines before, 24 now.
// NEAR (night-low1, 2026-11-08): the direction set through an inline taking the fallback by
// reference (retail's unit-X address formed before the difference, its lq in the fallback arm,
// the length's mtc1 at once: ToFloatMoved), the speed's length before the ramp's stores, and the
// ramp written through a pointer that is also the call's argument (retail's addiu a1, sp, 16;
// move a0, a1): 47 differing lines to 25. Still differs: the ramp's endSpeed and rampTime stores
// go through the pointer (retail: endSpeed at 20(sp), rampTime at 8(a1)), the dt load and the
// created object's load are scheduled otherwise (retail keeps the object in a2 for the slot
// call). Tried: the object read before the velocity's MulX (same).
// Before (2026-11-08, vu0w3-e1): structure and frame right (the Scalar slot at 0x30, the ramp at 0x10, the early d stored at sp+0); registers and orders differ: retail keeps the unit-X address in $v0 and the anchor's target in $v1 (here the reverse), stores the ramp's three words after the sqrt rather than before the second Length, and keeps the created object in $a2 across the Scalar for the first slot call.
#include "common.h"
#include "ramp_profile.h"
#include "vu0.h"
#include "globals.h"
#include "object_creator.h"

extern f32 g_frameDt;
void UpdateCollider(void* self);
void SetObjectCreatorState(ObjectCreator* t, s32 flag);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, RampProfile* p, f32* out);
void BuildBasisFromX(void* a, void* b);
s32 ChooseObjectCreatorState(ObjectCreator* self);

// dir = d made unit length, or fallback when d is shorter than 0.0001.
static inline void SetDirectionOr(Vec02& dir, u128 d, const Vec02& fallback)
{
    Vu0::Q(dir) = d;
    u128 len = Vu0::Length(d);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        dir = fallback;
    } else {
        Vu0::Q(dir) = Vu0::DivX(d, len);
    }
}

void UpdateObjectCreator(ObjectCreator* self)
{
    Vec02 dir;
    RampProfile ramp;
    Vec02 vel;
    UpdateCollider(self);
    s32 v;
    while ((v = ChooseObjectCreatorState(self)) != self->state) {
        SetObjectCreatorState(self, v);
    }
    if (v == 2) {
        PlacedObject* anchor = (PlacedObject*)self->createsObject;
        SetDirectionOr(dir, Vu0::Sub(Vu0::Q(((PlacedObject*)*(void**)((u8*)anchor + 0x354))->v140), Vu0::Q(((PlacedObject*)self->created)->v140)), g_unitXVector);
        f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(((PlacedObject*)self->created)->v150)));
        RampProfile* p = &ramp;
        p->maxSpeed = 3000.0f;
        p->endSpeed = 0.0f;
        p->rampTime = 0.2f;
        f32 speed = ApproachValueWithRamp(len, 3000.0f, g_frameDt, p, 0);
        Vu0::Q(vel) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(speed));
        PlacedObject* o = (PlacedObject*)self->created;
        o->desc02()->m20(o, &vel);
        Mat02 basis;
        BuildBasisFromX(&dir, &basis);
        ((PlacedObject*)self->created)->desc02()->m1E((PlacedObject*)self->created, &basis);
    }
}
