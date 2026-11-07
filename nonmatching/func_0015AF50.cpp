// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 480/472, checked 2026-11-07
// NEAR: the object cycler's per-frame step (a switch on the state: follow the curve for states 0, 3 and 5, steer for 1, step the collider for 6). Same instructions; it differs in the frame (retail's is 16 bytes smaller) and one register: the output vector of the rotation ramp and the scale vector share the slot at sp+0x30 in retail, and the address of that slot is formed again (addiu s0) where it is used; ours forms it early in s2 and keeps it, which costs a saved register. Locals in nested blocks, a separate `out` local and one shared local were tried.
#include "common.h"
#include "object_cycler.h"
#include "globals.h"
#include "game_clock.h"
#include "vu0.h"

extern f32 D_002621F8[6];
extern f32 D_00262210[4];
extern f32 D_00262220[4];

void EvaluateHermiteVectorSegment(Vec02* p0, Vec02* v0, Vec02* p1, void* v1, Vec02* outPos, Vec02* outVel, s32 zero, f32 t, f32 dt, f32 scale);
void ClampVectorLength(Vec02* out, Vec02* in, f32 limit);
void AddColliderForce(Collider* self, Vec02* force);
void BuildBasisFromXAndZHint(Vec02* x, Vec02* zHint, Mat02* out);
void ApproachRotationWithRamp(Mat02* current, Mat02* target, const f32* ramp, f32 dt, s32 zero, Vec02* out);
void SteerColliderTowardPosition(Collider* self, void* a, void* b, const Vec02* zero, const f32* ramp, f32 dt);
void SteerColliderTowardRotation(Collider* self, void* a, void* b, const Vec02* zero, const f32* ramp, f32 dt);
void StepCollider(Collider* self, f32 dt);

void func_0015AF50(ObjectCycler* self, f32 dt)
{
    switch (self->state) {
    case 0:
    case 3:
    case 5: {
        Vec02 pos;
        Vec02 vel;
        Vec02 accel;
        Vec02 k;
        Mat02 basis;
        f32 t = self->stateEnd + dt - g_gameClock.time;
        EvaluateHermiteVectorSegment(&self->pos, &self->v150, &self->v5F0, (u8*)self + 0x600, &pos, &vel, 0, t, dt, 1.0f);
        Vu0::Q(accel) = Vu0::Sub(Vu0::Q(vel), Vu0::Q(self->v150));
        Vu0::Q(k) = Vu0::FromFloat(1.0f / dt);
        Vu0::Q(accel) = Vu0::MulX(Vu0::Q(accel), Vu0::Q(k));
        ClampVectorLength(&accel, &accel, 3000.0f);
        AddColliderForce(self, &accel);
        Vu0::Q(accel) = Vu0::Sub(Vu0::Q(accel), Vu0::Q(self->gravity));
        BuildBasisFromXAndZHint(&vel, &accel, &basis);
        ApproachRotationWithRamp(&self->rot, &basis, D_002621F8, dt, 0, &k);
        self->desc02()->m21(self, &k);
        break;
    }
    case 1:
        AddColliderForce(self, &self->gravity);
        SteerColliderTowardPosition(self, 0, 0, &D_00248D30, D_00262210, dt);
        SteerColliderTowardRotation(self, 0, 0, &D_00248D30, D_00262220, dt);
        break;
    case 6:
        StepCollider(self, dt);
        break;
    }
}
