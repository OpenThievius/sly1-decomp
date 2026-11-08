// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 759/904 (84.0%), checked 2026-11-07
#include "common.h"
#include "asm_func.h"
#include "property_descriptor.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "masked_collider.h"
#include "animation.h"
#include "attachment.h"
#include "vu0.h"
#include "game_clock.h"
#include "anim_curve.h"
#include "world.h"
#include "entry_pool.h"
#include "buffered_stream.h"
#include "script_value.h"
// NEAR (2026-11-08, wave 4): ApplyPoseSourcePosition (func_001218C0): 90.7% of the instructions; the frame, the chain of cases and their operations are retail's. Left: case 1 (retail loads the owner's velocity and C before the scalars and moves dt to f12 before a3), the unit vector of case 3 (retail adds the vsub result in vf3 and goes through vf1 for the length, mine uses vf1 and vf2; building the direction through one variable made it worse), the argument order of the ramp call (floats first) and a few vector registers. The jump table is the C switch's own (the INCLUDE_RODATA line goes). The ramp's profile is read through the owner's table pointer three times as retail does; the clock through the global (a pointer local does not give retail's lui/addiu pair).
extern f32 ApproachValueWithRamp(void*, s32, f32, f32, f32);
void ComputePositionSpringAcceleration(PlacedObject* self, Vec02* a, Vec02* b, Vec02* out, f32 dt);
f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, s32 zero, Vec02* rest);
void EvaluateHermiteVectorSegment(void* a, void* b, void* c, void* d, void* e, void* f, s32 g, f32 t, f32 u, f32 v);
extern const Vec02 D_00248D00;

void ApplyPoseSourcePosition(T2195_7C0* self)
{
    PlacedObject* owner = self->owner;
    f32 dt;
    f32 now;
    Vec02 A;
    Vec02 B;
    if (owner->f294 != 0) {
        dt = g_gameClock.step;
    } else {
        dt = g_gameClock.dt;
    }
    if (owner->f294 != 0) {
        now = g_gameClock.elapsed;
    } else {
        now = g_gameClock.time;
    }
    self->vt->getPos(self, 0.0f, &A, &B);
    switch (self->mode0) {
    case 2:
    case 7:
        owner->pos = A;
        owner->v150 = B;
        break;
    case 1: {
        Vec02 C;
        ComputePositionSpringAcceleration(owner, &A, &B, &C, dt);
        Vu0::Q(C) = Vu0::Add(Vu0::Q(C), Vu0::Q(owner->v170));
        Vu0::Q(owner->pos) = Vu0::MulAddX2(Vu0::Q(owner->pos), Vu0::Q(owner->v150), Vu0::Scalar(dt), Vu0::Q(C), Vu0::Scalar(dt * (dt * 0.5f)));
        Vu0::Q(owner->v150) = Vu0::MulAddX(Vu0::Q(owner->v150), Vu0::Q(C), Vu0::Scalar(dt));
        break;
    }
    case 3:
    case 6:
    case 9: {
        Vec02 d;
        Vec02 dir;
        Vec02 rest;
        Vec02 prof;
        Vec02 k;
        Vec02 E;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(A), Vu0::Q(owner->pos));
        Vu0::Q(dir) = Vu0::Q(d);
        u128 fallback = Vu0::Q(D_00248D00);
        u128 len = Vu0::Length(Vu0::Q(d));
        f32 dist = Vu0::ToFloat(len);
        if (dist < 0.0001f) {
            Vu0::Q(dir) = fallback;
        } else {
            Vu0::Q(dir) = Vu0::DivX(Vu0::Q(d), len);
        }
        f32 r = SplitVectorAlongAxis(&B, &dir, 0, &rest);
        prof.x = ((f32*)owner->p21C)[0] + r;
        prof.y = ((f32*)owner->p21C)[1] + r;
        prof.z = ((f32*)owner->p21C)[2];
        f32 reach = ApproachValueWithRamp(&prof, (s32)&E, 0.0f, dist, dt);
        if (self->mode0 == 6) {
            f32 end = self->f18;
            f32 lim;
            if (now < end) {
                lim = dist * dt / (end - now + dt);
            } else {
                lim = dist;
            }
            if (reach < lim) {
                reach = lim;
                E.x = reach / dt;
            }
        }
        if (dist <= reach) {
            owner->pos = A;
            owner->v150 = B;
            if (self->mode0 != 9) {
                self->mode0 = 7;
            }
        } else {
            Vu0::Q(k) = Vu0::FromFloat(reach);
            Vu0::Q(owner->pos) = Vu0::MulAddX(Vu0::Q(owner->pos), Vu0::Q(dir), Vu0::Q(k));
            Vu0::Q(k) = Vu0::FromFloatAt(E.x);
            Vu0::Q(owner->v150) = Vu0::MulAddX(Vu0::Q(rest), Vu0::Q(dir), Vu0::Q(k));
        }
        break;
    }
    case 4: {
        f32 end = self->f18;
        f32 left = end - now;
        if (left < dt) {
            Vec02 k;
            Vu0::Q(k) = Vu0::FromFloat(now + dt - end);
            Vu0::Q(owner->pos) = Vu0::MulAddX(Vu0::Q(A), Vu0::Q(B), Vu0::Q(k));
            owner->v150 = B;
        } else {
            Vec02 p;
            Vec02 v;
            EvaluateHermiteVectorSegment(&owner->pos, &owner->v150, &A, &B, &p, &v, 0, left, dt, 1.0f);
            owner->pos = p;
            owner->v150 = v;
        }
        break;
    }
    }
}

