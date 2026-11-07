// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 266/408 (65.2%), checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): structure and frame right (the Scalar slot at 0x30, the ramp at 0x10, the early d stored at sp+0); registers and orders differ: retail keeps the unit-X address in $v0 and the anchor's target in $v1 (here the reverse), stores the ramp's three words after the sqrt rather than before the second Length, and keeps the created object in $a2 across the Scalar for the first slot call.
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
        u128 fb = *(const u128*)&g_unitXVector;
        u128 d = Vu0::Sub(Vu0::Q(((PlacedObject*)*(void**)((u8*)anchor + 0x354))->v140), Vu0::Q(((PlacedObject*)self->created)->v140));
        Vu0::Q(dir) = d;
        u128 dlen = Vu0::Length(d);
        if (Vu0::ToFloat(dlen) < 0.0001f) {
            *(u128*)&dir = fb;
        } else {
            Vu0::Q(dir) = Vu0::DivX(d, dlen);
        }
        ramp.maxSpeed = 3000.0f;
        ramp.endSpeed = 0.0f;
        ramp.rampTime = 0.2f;
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(((PlacedObject*)self->created)->v150)));
        f32 speed = ApproachValueWithRamp(len, ramp.maxSpeed, g_frameDt, &ramp, 0);
        Vu0::Q(vel) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(speed));
        PlacedObject* o = (PlacedObject*)self->created;
        o->desc02()->m20(o, &vel);
        Mat02 basis;
        BuildBasisFromX(&dir, &basis);
        ((PlacedObject*)self->created)->desc02()->m1E((PlacedObject*)self->created, &basis);
    }
}
