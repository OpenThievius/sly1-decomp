// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 508/512, checked 2026-11-08
// NEAR (2026-11-08, night-lever1): the normalisation's branch, the Set of dir and both weights (ScalarAt)
// are retail's now (NormalizeOrLength: NormalizeOr that also gives the length). Still differs: the order
// of the two weights' loads (retail: mfc1 of the ramp result, then lw of out; ours lw first) and the two
// settle loops (retail keeps v in a1 and compares a1 with the reloaded field, `move a1,v0` before the lw;
// ours compares v0 and moves in the delay slot). The loops tried: while with the assignment in the
// condition, both operand orders, a rotated while, for(;;) with a break.
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

// Vu0::NormalizeOr that also gives the length it found.
static inline u128 NormalizeOrLength(u128 v, u128 fallback, f32& length)
{
    u128 len = Vu0::Length(v);
    length = Vu0::ToFloat(len);
    if (length < 0.0001f) {
        return fallback;
    }
    return Vu0::DivX(v, len);
}

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
            f32 l;
            Vu0::Set(dir, NormalizeOrLength(d, Vu0::Q(g_unitXVector), l));
            f32 along = SplitVectorAlongAxis(&vel, &dir, 0, &split);
            f32* lim = (f32*)self->p21C;
            ramp.maxSpeed = lim[0] + along;
            ramp.endSpeed = lim[1] + along;
            ramp.rampTime = lim[2];
            f32 res = ApproachValueWithRamp(0.0f, l, g_frameDt, &ramp, &out);
            u128 w = Vu0::Scalar(res);
            Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(dir), w);
            Vu0::Q(vel) = Vu0::MulAddX(Vu0::Q(split), Vu0::Q(dir), Vu0::ScalarAt(out));
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
