// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (2026-11-08, worker night-large1): the player's upright torque: the ramp profile blended
// by the ground speed and scaled by 0x634 (D_00263740 alone off the ground), the tilt and the
// heading to the goal matrix 0x660, the two speeds ApproachValueClampingVelocity gives, the
// torque that reaches them in one step, and the pull to the pivot as ApplyTurningColliderDrive
// does it. The code is retail's but for the product of the turn and the placement matrix:
// retail reads the placement's rows 1 and 2 through a pointer kept in s1, each after the store
// of the row before (a dependence this C does not give: its loads are hoisted to the top), so
// retail keeps one more saved register and its frame is 16 bytes larger; the two speeds sit at
// 0x130 where this C puts them at 0xD0, and the shared scalar slot is 0xD0 where this C has 0xE0.
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "font.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "scatter_controller.h"
#include "render_frame.h"
#include "background_job.h"
#include "vu0.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "path_curve_object.h"
#include "asm_func.h"
#include "vu0.h"
#include "ramp_profile.h"
#include "ramp_profile.h"

extern RampProfile D_00263730;
extern RampProfile D_00263740;
extern RampProfile D_00263750;
extern f32 D_00263760[4];
extern f32 D_00263770[4];
extern f32 g_gameClock[];
extern f32 g_unitRange[];
f32 ComputeAngleBetweenVectors(const Vec02* a, const Vec02* b, Vec02* axis);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
f32 SplitVectorAlongAxis(const Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
f32 ApproachValueClampingVelocity(f32 value, f32 speed, f32 target, f32 dt, RampProfile* ramp, f32* out);
void AddColliderTorque(void* self, Vec02* torque);
void AddColliderForce(void* self, Vec02* force);

static inline f32 LimitToRange(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

static inline f32 BlendRamp(f32 t, f32 a, f32 b)
{
    return (1.0f - t) * a + t * b;
}

void func_0016FD70(Player* self)
{
    Vec02 axis;
    Vec02 axis2;
    Vec02 along;
    Vec02 rest;
    Vec02 spin;
    Vec02 torque;
    Mat02 turn;
    Mat02 rot;
    RampProfile ramp;
    f32 speeds[2];

    if (self->f2220 == 1) {
        f32 v = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v150), Vu0::Q(self->v150))));
        f32 t = LimitToRange(D_00263760[0] + v * (D_00263760[1] + v * D_00263760[2]), g_unitRange[0], g_unitRange[1]);
        ramp.maxSpeed = BlendRamp(t, D_00263740.maxSpeed, D_00263750.maxSpeed);
        ramp.endSpeed = BlendRamp(t, D_00263740.endSpeed, D_00263750.endSpeed);
        ramp.rampTime = BlendRamp(t, D_00263740.rampTime, D_00263750.rampTime);
        ramp.maxAccel = BlendRamp(t, D_00263740.maxAccel, D_00263750.maxAccel);
        f32 k = self->f634;
        f32 s = LimitToRange(D_00263770[0] + k * (D_00263770[1] + k * D_00263770[2]), g_unitRange[0], g_unitRange[1]);
        ramp.maxSpeed *= s;
        ramp.endSpeed *= s;
    } else {
        ramp = D_00263740;
    }
    Mat02* cur = &self->rot;
    Mat02* goal = &self->m660;
    f32 tilt = ComputeAngleBetweenVectors(&cur->r[2], &goal->r[2], &axis);
    BuildAxisAngleMatrix(&axis, &turn, tilt);
    {
        u128 m0 = Vu0::Q(turn.r[0]);
        u128 m1 = Vu0::Q(turn.r[1]);
        u128 m2 = Vu0::Q(turn.r[2]);
        Mat02 r;
        Vec02 x;
        Vec02 y;
        Vec02 z;
        u128 p0 = Vu0::RotateRows(m0, m1, m2, Vu0::Q(cur->r[0]));
        Vu0::Set(r.r[0], p0);
        Vu0::Set(x, p0);
        u128 p1 = Vu0::RotateRows(m0, m1, m2, Vu0::Q(cur->r[1]));
        Vu0::Set(r.r[1], p1);
        Vu0::Set(y, p1);
        u128 p2 = Vu0::RotateRows(m0, m1, m2, Vu0::Q(cur->r[2]));
        Vu0::Set(r.r[2], p2);
        Vu0::Set(z, p2);
        rot = r;
    }
    f32 heading = ComputeAngleBetweenVectors(&rot.r[0], &goal->r[0], &axis2);
    u128 up = Vu0::Q(goal->r[2]);
    if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(axis2), up)) < 0.0f) {
        heading = -heading;
    }
    Vu0::Q(axis2) = up;
    f32 w = SplitVectorAlongAxis(&self->v160, &axis, &along, &rest);
    f32 w2 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(rest), Vu0::Q(axis2)));
    ApproachValueClampingVelocity(0.0f, w, tilt, g_gameClock[2], &D_00263730, &speeds[0]);
    ApproachValueClampingVelocity(0.0f, w2, heading, g_gameClock[2], &ramp, &speeds[1]);
    f32 dt = g_gameClock[2];
    Vu0::Q(spin) = Vu0::MulXSum(Vu0::Q(axis), Vu0::ScalarAt(speeds[0]), Vu0::Q(axis2), Vu0::ScalarAt(speeds[1]));
    Vu0::Q(torque) = Vu0::MulXSum(Vu0::Q(spin), Vu0::Scalar(1.0f / dt), Vu0::Q(self->v160), Vu0::Scalar(-1.0f / dt));
    AddColliderTorque(self, &torque);
    {
        Vec02* pivot;
        if (self->f690 != 0) {
            pivot = &self->v6A0;
        } else {
            pivot = (Vec02*)self->f6D4;
        }
        Vec02 arm;
        Vec02 v;
        Vec02 u;
        Vu0::Q(arm) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*pivot));
        Vu0::Q(v) = Vu0::Cross(Vu0::Q(self->v180), Vu0::Q(arm));
        AddColliderForce(self, &v);
        Vu0::Q(u) = Vu0::Cross(Vu0::Q(self->v160), Vu0::Q(arm));
        Vu0::Q(v) = Vu0::Cross(Vu0::Q(self->v160), Vu0::Q(u));
        AddColliderForce(self, &v);
    }
}
