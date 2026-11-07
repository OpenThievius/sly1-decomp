// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 508/512, checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): structure right (frame, calls, the hit-and-ramp path); differs in the normalisation's branch (retail stores d to dir in the bc1f delay slot and moves the fallback into the VU in the delay slot of the jump over the divide; here the fallback is a struct copy), and in the two weights: retail makes both of the final MulAddX weights vectors of one shared slot at 0x60 (the first from the ramp's result, the second with an lw of the float out straight into qmtc2), which wants a Scalar built on FromFloatAt, and registers them vf4 then vf5.
#include "common.h"
#include "ramp_profile.h"
#include "vu0.h"
#include "globals.h"
#include "attachment.h"

extern f32 g_frameDt;
f32 ArctangentOfRatio(f32 a, f32 b);
s32 HasAnimationDrivenAttachment(void* ctx);
f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, s32 z, Vec02* out);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, RampProfile* p, f32* out);
void UpdateSwitchedCollider(void* self);
s32 ChooseWalkerColliderState(WalkerCollider* self);
s32 ChooseWalkerColliderSubState(WalkerCollider* self);
void SetWalkerColliderState(WalkerCollider* self, s32 n);
void SetWalkerColliderSubState(WalkerCollider* self, s32 state);
void ClearRootTries(void* self);

void UpdateWalkerCollider(WalkerCollider* self)
{
    UpdateSwitchedCollider(self);
    if (HasAnimationDrivenAttachment(self) != 0) {
        Vec02 pos;
        Vec02 vel;
        Vec02 diff;
        Vec02 dir;
        Vec02 split;
        RampProfile ramp;
        f32 out;
        self->f1EC->vt->getPos(self->f1EC, 0.0f, &pos, &vel);
        if (self->f610 == 3) {
            u128 d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos));
            Vu0::Q(diff) = d;
            Vu0::Q(dir) = d;
            u128 len = Vu0::Length(d);
            f32 l = Vu0::ToFloat(len);
            if (!(l < 0.0001f)) {
                Vu0::Q(dir) = Vu0::DivX(d, len);
            } else {
                dir = g_unitXVector;
            }
            f32 along = SplitVectorAlongAxis(&vel, &dir, 0, &split);
            f32* lim = (f32*)self->p21C;
            ramp.maxSpeed = lim[0] + along;
            ramp.endSpeed = lim[1] + along;
            ramp.rampTime = lim[2];
            f32 res = ApproachValueWithRamp(0.0f, l, g_frameDt, &ramp, &out);
            u128 w = Vu0::Scalar(res);
            Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(dir), w);
            Vu0::Q(vel) = Vu0::MulAddX(Vu0::Q(split), Vu0::Q(dir), Vu0::FromFloatAt(out));
        }
        self->desc02()->m1D(self, &pos);
        self->desc02()->m20(self, &vel);
        self->f618 = ArctangentOfRatio(vel.y, vel.x);
    }
    s32 v;
    while ((v = ChooseWalkerColliderState(self)) != self->f610) {
        SetWalkerColliderState(self, v);
    }
    while ((v = ChooseWalkerColliderSubState(self)) != self->f614) {
        SetWalkerColliderSubState(self, v);
    }
    ClearRootTries(self);
}
