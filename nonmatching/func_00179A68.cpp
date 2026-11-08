// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 3173/3176 (99.9%), checked 2026-11-08
// NEAR (2026-11-08, worker large-179A68): every instruction but three: the f700 clamp's upper
// bound is loaded into $f3 where retail has $f0. Here the scheduler's first pass puts the load of
// D_00263C90[1] before the add whose product (dt * f708) holds $f0, so global-alloc cannot give it
// $f0 (tools/regalloc.py); in retail the load comes after the add. Reading the bound inside the
// else arm (an explicit if/else-if, or a ClampToRange(v, const f32*) inline) gives $f0 but moves the
// bound's address (addiu v0,s5,%lo) from the block's start into the branch's delay slot (2 insns
// off). Found on the way (all in this attempt): ApproachValueWithRamp takes its floats first
// (value, target, dt, profile, speed out); ApproachRotationWithRamp takes dt fourth; one loop index
// at function scope (its final value 2 is the constant of the second mode test, li s2,2); the mode
// range as a switch (case 2, 3, 4) where && folds into a range test; the 3 address spill slots'
// order follows the insn count at GCSE time (the address pseudos are numbered in hash-bucket order):
// Vec rows in the product inline and the Vec axis copy give retail's order.
#include "common.h"
#include "switched_collider.h"
#include "globals.h"
#include "placed_object.h"
#include "screen_element.h"
#include "vu0.h"
#include "pad_record.h"
#include "game_progress.h"
#include "attachment.h"
#include "mul_rotation.h"

extern T217D_BF0 D_00270650;
extern f32 g_gameTime;
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

// The record ModeCollider::f618 points at in mode 3: a value tested against zero and an object
// whose 0x34 is the mode's length.
struct ModeColliderLength {
    u8 pad00[0x34];
    f32 length;             // 0x34
};
struct ModeColliderSource {
    u8 pad00[0x08];
    ModeColliderLength* f08; // 0x08
    u8 pad0C[0x18 - 0x0C];
    f32 f18;                // 0x18: 0.0 ends the mode at once
};

// The three floats of a ramp profile ApproachValueWithRamp reads, copied whole.
struct RampProfile3 {
    f32 maxSpeed;
    f32 endSpeed;
    f32 rampTime;
};

extern f32 D_00263C50[];
extern f32 D_00263C58[];
extern f32 D_00263C68[];
extern f32 D_00263C78[];
extern f32 D_00263C80[];
extern f32 D_00263C90[];
extern f32 D_00263CA0[];
extern f32 D_00263CB0[];
extern f32 D_00263CC0[];
extern f32 D_00263CD0[];
extern f32 D_00263CE0[];
extern f32 D_00263CF0[];
extern f32 D_00263D00[];
extern f32 D_00263D08[];
extern f32 D_00263D18[];

s32 HasSpareCount(void);
void ClearPadPressedBits(PadRecord* pad, s32 bits);
void GetStateWalkerCurrentKey(void* walker, s32* out);
void SetStateWalkerTarget(void* walker, s32 key);
f32 ApproachValueWithRamp(f32 value, f32 target, f32 dt, void* profile, f32* speed);
void ProjectPointToCamera(Camera* camera, Vec02* pos, f32* out);
void BuildBasisFromXAndZHint(Vec02* x, const Vec02* z, Mat02* out);
void TransformRotationBetweenFrames(void* from, void* to, Mat02* in, Mat02* out);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void ApproachRotationWithRamp(Mat02* rot, Mat02* target, void* profile, f32 dt, Mat02* out, s32 flags);
void HandleStepSequenceSkipButtons(ModeCollider* self, PadRecord* pad);
void ClearRootTries(void* self);

// v limited to lo..hi, in place.
static inline f32 ClampInPlace(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    return v;
}

// The product a b of two rotations into out: a's rows loaded once, b's rows each rotated by
// them, each result row stored to its vector local and then to out's row.
static inline void RotationProductInto(Mat02* out, const Mat02& a, const Mat02& b)
{
    Vu0::Vec a0 = Vu0::Vec::Of(a.r[0]);
    Vu0::Vec a1 = Vu0::Vec::Of(a.r[1]);
    Vu0::Vec a2 = Vu0::Vec::Of(a.r[2]);
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(out->r[0]) = Vu0::Q(x) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[0]));
    Vu0::Q(out->r[1]) = Vu0::Q(y) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[1]));
    Vu0::Q(out->r[2]) = Vu0::Q(z) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[2]));
}

void ControlModeCollider(ModeCollider* self, f32 dt, PadRecord* pad)
{
    Mat02 mats[2];
    s32 i;
    Mat02 aim;
    s32 key;
    f32 hiX;
    f32 loX;
    f32 hiY;
    f32 loY;

    if (self->f610 == 3 && HasSpareCount() != 0) {
        ModeColliderSource* src = (ModeColliderSource*)self->f618;
        if (src == 0 || src->f18 == 0.0f) {
            self->desc05()->m50(self);
        } else {
            if (pad->flags & 0x40) {
                ClearPadPressedBits(pad, 0x40);
                self->f6DC = g_gameTime;
            }
            if (self->f6E0 != 0 && g_gameTime - self->f6DC < D_00263C50[0]) {
                self->desc05()->m50(self);
            }
        }
    }
    if (pad->keyA8 & 0x80) {
        GetStateWalkerCurrentKey(self->f658, &key);
        if (key >= 0x44F) {
            if (key < 0x451) {
                key = 0x451;
            } else if (key < 0x453) {
                key = 0x44F;
            }
        }
        SetStateWalkerTarget(self->f658, key);
    }
    switch (self->f610) {
    case 2:
    case 3:
    case 4: {
        Vec02 at;
        Vec02 pos;
        TransformPointBetweenFrames(0, self->f660, &self->f664->v140, &at);
        f32 u = (at.y - D_00263CA0[0]) / D_00263CA0[1];
        f32 v = (at.z - D_00263CB0[0]) / D_00263CB0[1];
        ApproachValueWithRamp(self->f6EC, u + D_00263C78[1], 0.0f, D_00263C58, &hiX);
        ApproachValueWithRamp(self->f6EC, u + D_00263C78[0], 0.0f, D_00263C58, &loX);
        ApproachValueWithRamp(self->f6F0, v + D_00263C78[1], 0.0f, D_00263C58, &hiY);
        ApproachValueWithRamp(self->f6F0, v + D_00263C78[0], 0.0f, D_00263C58, &loY);
        f32 stickY = pad->f44;
        if (g_saveData->f19EC & 0x800) {
            stickY = -stickY;
        }
        f32 tx;
        f32 ty;
        if (self->f610 == 2) {
            tx = loX + (pad->f40 + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            tx = (loX + hiX) * 0.5f;
            ty = (loY + hiY) * 0.5f;
        }
        self->f6F4 = ApproachValueWithRamp(self->f6F4, tx, dt, D_00263C68, 0);
        self->f6F8 = ApproachValueWithRamp(self->f6F8, ty, dt, D_00263C68, 0);
        self->f6EC = ClampBetween(self->f6EC + dt * self->f6F4, u + D_00263C78[0], u + D_00263C78[1]);
        f32 w = ClampBetween(self->f6F0 + dt * self->f6F8, v + D_00263C78[0], v + D_00263C78[1]);
        self->f6F0 = w;
        f32 h = self->f6EC;
        Vu0::Q(pos) = Vu0::FromFloats(at.x, D_00263CA0[0] + h * (D_00263CA0[1] + h * D_00263CA0[2]),
                                      D_00263CB0[0] + w * (D_00263CB0[1] + w * D_00263CB0[2]));
        TransformPointBetweenFrames(self->f660, 0, &pos, &pos);
        TransformPointBetweenFrames(0, self->f660, &pos, (u8*)self->f650 + 0xF0);
        ProjectPointToCamera(g_camera, &pos, D_00270650.aim);
        for (i = 0; i < 2; i++) {
            Vec02 dir;
            *(Vu0::Vec*)&dir = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->f674[i]->v140));
            BuildBasisFromXAndZHint(&dir, &g_unitZVector, &mats[i]);
            TransformRotationBetweenFrames(0, self->f674[i]->parent, &mats[i], &mats[i]);
        }
        ApproachValueWithRamp(self->f6FC, D_00263C90[1], 0.0f, D_00263C58, &hiX);
        ApproachValueWithRamp(self->f6FC, D_00263C90[0], 0.0f, D_00263C58, &loX);
        ApproachValueWithRamp(self->f700, D_00263C90[1], 0.0f, D_00263C58, &hiY);
        ApproachValueWithRamp(self->f700, D_00263C90[0], 0.0f, D_00263C58, &loY);
        RampProfile3 prof = *(RampProfile3*)D_00263C80;
        if (self->f610 == 2) {
            tx = loX + (pad->f40 + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            f32 k = (g_gameTime - self->f614) / ((ModeColliderSource*)self->f618)->f08->length;
            f32 s = D_00263CC0[0] + k * (D_00263CC0[1] + k * D_00263CC0[2]);
            tx = (loX + hiX) * 0.5f;
            ty = hiY;
            f32 lo = g_unitRange.lo;
            f32 hi = g_unitRange.hi;
            if (s < lo) {
                s = lo;
            } else if (hi < s) {
                s = hi;
            }
            prof.maxSpeed *= s;
            prof.endSpeed *= s;
        }
        self->f704 = ApproachValueWithRamp(self->f704, tx, dt, &prof, 0);
        self->f708 = ApproachValueWithRamp(self->f708, ty, dt, &prof, 0);
        self->f6FC = ClampInPlace(self->f6FC + dt * self->f704, D_00263C90[0], D_00263C90[1]);
        self->f700 = ClampInPlace(self->f700 + dt * self->f708, D_00263C90[0], D_00263C90[1]);

        Mat02 pitch;
        Mat02 yaw;
        Mat02 face;
        Vec02 to;
        Vec02 rel;
        Mat02 tilt;
        Vec02 axis;
        TransformPointBetweenFrames(0, self->f668, &((PlacedObject*)self->f660)->v140, &rel);
        f32 sx = pad->f40;
        if (rel.x < 0.0f) {
            sx = -sx;
        }
        BuildAxisAngleMatrix(&g_unitXVector, &pitch, D_00263CD0[0] + sx * (D_00263CD0[1] + sx * D_00263CD0[2]));
        f32 sy = pad->f44;
        BuildAxisAngleMatrix(&g_unitYVector, &yaw, D_00263CE0[0] + sy * (D_00263CE0[1] + sy * D_00263CE0[2]));
        *(Vu0::Vec*)&to = Vu0::Sub(Vu0::Vec::Of(((PlacedObject*)self->f660)->v140), Vu0::Vec::Of(self->v140));
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &face);
        f32 speed = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v150), Vu0::Q(self->v150))));
        f32 angle = ClampInPlace(D_00263CF0[0] + speed * (D_00263CF0[1] + speed * D_00263CF0[2]), D_00263D00[0], D_00263D00[1]);
        Vu0::Vec n;
        n.q = Vu0::FromFloats(-self->v150.y, self->v150.x, 0.0f);
        *(Vu0::Vec*)&axis = n;
        *(Vu0::Vec*)&axis = Vu0::NormalizeOr(Vu0::Vec::Of(axis), Vu0::Vec::Of(g_unitXVector));
        BuildAxisAngleMatrix(&axis, &tilt, angle);
        Mat02 m3;
        Mat02 m2;
        Mat02 m1;
        RotationProductInto(&m1, tilt, face);
        RotationProductInto(&m2, m1, yaw);
        RotationProductInto(&m3, m2, pitch);
        self->m620 = m3;
        *(Vu0::Vec*)&to = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->f67C->v140));
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &aim);
        TransformRotationBetweenFrames(0, self->f67C->f224->p60, &aim, &aim);
        break;
    }
    default:
        BuildAxisAngleMatrix(&g_unitZVector, &self->m620, self->f61C);
        for (i = 0; i < 2; i++) {
            mats[i] = self->f674[i]->m1A0;
        }
        aim = g_identityMatrix;
        break;
    }
    Mat02 rot;
    for (i = 0; i < 2; i++) {
        ApproachRotationWithRamp(&self->f674[i]->rot, &mats[i], D_00263D08, dt, &rot, 0);
        self->f674[i]->desc02()->m1E(self->f674[i], &rot);
    }
    if (self->f67C->f1F0 == 0) {
        MulRotationRowsIndexed(&aim, aim, self->f67C->m1A0);
        ApproachRotationWithRamp(&self->f67C->rot, &aim, D_00263D18, dt, &rot, 0);
        self->f67C->desc02()->m1E(self->f67C, &rot);
    }
    HandleStepSequenceSkipButtons(self, pad);
    ClearRootTries(self);
}
