// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x16C470 to 0x16CE00. Its name is ours, after ApplyLinkConstraint, nearly all of its code
// (0x8D4 of 0x990 bytes); the small overrides before it are described below.
#include "common.h"
#include "c52.h"
#include "vu0.h"
#include "placed_object.h"
#include "attachment.h"
#include "fpu.h"
#include "asm_func.h"
#include "c35.h"

// Small overrides of three classes (0x76's set-up and transform read, the slot 0xA4 of 0x35 and
// of 0x52) and ApplyLinkConstraint, a two-bone IK solver on VU0. Its .rodata is
// func_0016C470's FLT_MAX literal at 0x24A7DC and, after it, two -FLT_MAX words no code reads.

void InitClass75Object(void* self);

// An object of class 0x76 (0xC0 bytes, under 0x75): the fields its set-up writes.
struct C76 {
    u8 pad0[0x88];
    s32 f88;
    u8 pad8C[0xA8 - 0x8C];
    s32 fA8;
    s32 fAC;
    u8 padB0[0xB4 - 0xB0];
    f32 fB4;
};

void InitC76Object(void* a0)
{
    C76* self = (C76*)a0;
    InitClass75Object(a0);
    self->f88 = 1;
    self->fA8 = 8;
    self->fAC = 9;
    self->fB4 = 3.4028234663852886e+38f;
}

// Two words no code reads, after func_0016C470's literal: those of functions the linker stripped
// (func_0016C4D8 is what it left of one). The zeros after them are the linker's padding before
// target_follower's 16-aligned .rodata.
extern const f32 D_0024A7E0 = -3.40282347e+38f;
extern const f32 D_0024A7E4 = -3.40282347e+38f;

struct TransformObject;
void ReadTransformObject(TransformObject* self, void* stream);

void LoadC76Object(TransformObject* self, void* stream)
{
    ReadTransformObject(self, stream);
}

LINKER_REMNANT(func_0016C4D8);

void DrawCollider(Collider* self, void* arg1, void* arg2);

void DrawC35Collider(C35* self, void* arg1, void* arg2)
{
    DrawCollider(self, arg1, arg2);
}

void DrawPlacedObject(PlacedObject* self, void* arg1, void* arg2);

void DrawC52Object(C52* self, void* arg1, void* arg2)
{
    DrawPlacedObject(self, arg1, arg2);
}

void SetPlacedObjectVelocity(PlacedObject* self, Vec02* v);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void TransformStateToAncestorFrame(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);
void AccumulateFrameChain(PlacedObject* self, PlacedObject* top, s32 n, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);
f32 ComputeAngleBetweenVectors(Vec02* a, Vec02* b, Vec02* axis);
extern "C" f32 Arccosine(f32 x);
void BuildAxisAngleMatrix(f32 angle, const Vec02* v, Mat02* out);
void BuildRotationBetweenVectors(Vec02* a, Vec02* b, f32* m);
// The definition takes the angle last; the EE passes it in its own register, and retail's
// caller evaluates it first, as this order does.
Mat02 MultiplyByTransposedMatrix3x3(const Mat02& a, const Mat02& b);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 tolerance);
extern Vec02 D_00248D30;
extern Mat02 g_identityMatrix;
extern Vec02 g_unitXVector;

// v made unit length, or fallback when shorter than 0.0001.
static inline void NormalizeVector(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        v = fallback;
    } else {
        *(Vu0::Vec*)&v = Vu0::DivX(Vu0::Vec::Of(v), Vu0::Vec::Of(len));
    }
}

// The product a b of two rotations, returned: b's rows each rotated by a.
static inline Mat02 MulRotationValue(const Mat02& a, const Mat02& b) return r
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = *(u128*)&r.r[0] = Vu0::RotateRows(a0, a1, a2, q[0]);
    Vu0::Q(y) = *(u128*)&r.r[1] = Vu0::RotateRows(a0, a1, a2, q[1]);
    Vu0::Q(z) = *(u128*)&r.r[2] = Vu0::RotateRows(a0, a1, a2, q[2]);
}

// The same with b's rows read through Vu0::Q, which CSE folds into frame offsets.
static inline Mat02 MulRotationQ(const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = *(u128*)&r.r[0] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = *(u128*)&r.r[1] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = *(u128*)&r.r[2] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    return r;
}

// MulRotationQ with g++'s named return value.
static inline Mat02 MulRotationQNamed(const Mat02& a, const Mat02& b) return r
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = *(u128*)&r.r[0] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = *(u128*)&r.r[1] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = *(u128*)&r.r[2] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
}

// The product a b of two rotations into out: b's rows each rotated by a's rows, loaded once,
// each result row stored to the matrix local and then to its vector local, then the matrix
// copied out (mul_rotation.h's MulRotationRowsX, the locals written by address rather than
// through Vu0::Q, whose reference pseudo CSE would share with a later use of the same frame
// address).
static inline void MulRotationInto(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    *(u128*)&x = *(u128*)&r.r[0] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    *(u128*)&y = *(u128*)&r.r[1] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    *(u128*)&z = *(u128*)&r.r[2] = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    *out = r;
}

void ApplyLinkConstraint(PlacedObject* self)
{
    typedef Vu0::Vec Vec;
    Rec2195_224* rec = self->linkRecord;
    s32 flags = rec->linkFlags;
    PlacedObject* a = (PlacedObject*)rec->f80;
    PlacedObject* b = (PlacedObject*)rec->p84;
    PlacedObject* top = (PlacedObject*)rec->p88;
    if (flags & 2) {
        f32 reach = Vu0::ToFloatMoved(Vu0::Length(Vec::Of(b->pos))) + Vu0::ToFloatMoved(Vu0::Length(Vec::Of(rec->q60[1])));
        Vec02 to;
        Vec02 diff;
        *(Vec*)&diff = Vu0::Sub(Vec::Of(self->v140), Vec::Of(a->v140));
        f32 d = Vu0::ToFloatMoved(Vu0::Length(Vec::Of(diff)));
        if (reach < d) {
            *(Vec*)&diff = Vu0::MulX(Vec::Of(diff), Vec::Scalar(reach / d));
            *(Vec*)&to = Vu0::Add(Vec::Of(((PlacedObject*)rec->f80)->v140), Vec::Of(diff));
            SetPlacedObjectVelocity(self, &D_00248D30);
            TransformPointBetweenFrames(0, (PlacedObject*)self->parent, &to, &to);
            self->desc02()->m1D(self, &to);
        }
    }
    a->rot = MulRotationValue(*(Mat02*)((u8*)a->linkRecord + 0x30), *(Mat02*)a->linkRecord);
    Rec2195_224* rb = b->linkRecord;
    if (rb != 0 && (rb->fB0 & 3)) {
        b->rot = MulRotationValue(*(Mat02*)((u8*)rb + 0x30), *(Mat02*)rb);
    } else {
        Mat02* m = &b->rot;
        *m = g_identityMatrix;
    }
    if (a->desc->m12 != 0) {
        a->desc->m12(a);
    }
    Vec02 target = *(Vec02*)&rec->q60[0];
    Vec02 vel = D_00248D30;
    TransformStateToAncestorFrame(self, top, &target, 0, &vel, 0);
    Vec02 pos[4];
    Mat02 rot[4];
    Vec02 vels[4];
    Vec02 spins[4];
    AccumulateFrameChain(b, top, 3, &pos[1], &rot[1], &vels[1], &spins[1]);
    *(Vec*)&pos[0] = Vu0::Rotate(rot[1], Vec::Of(rec->q60[1]));
    *(Vec*)&pos[0] = Vu0::Add(Vec::Of(pos[0]), Vec::Of(pos[1]));
    Vec02 u;
    Vec02 w;
    Vec02 t;
    *(Vec*)&u = Vu0::Sub(Vec::Of(pos[1]), Vec::Of(pos[2]));
    *(Vec*)&w = Vu0::Sub(Vec::Of(pos[0]), Vec::Of(pos[1]));
    *(Vec*)&t = Vu0::Sub(Vec::Of(target), Vec::Of(pos[2]));
    f32 lu = Vu0::ToFloatMoved(Vu0::Length(Vec::Of(u)));
    f32 lw = Vu0::ToFloatMoved(Vu0::Length(Vec::Of(w)));
    f32 lt = Vu0::ToFloatMoved(Vu0::Length(Vec::Of(t)));
    Vec02 axis;
    f32 angle = ComputeAngleBetweenVectors(&u, &w, &axis);
    f32 c = (lt * lt - lu * lu - lw * lw) / (2.0f * lu * lw);
    if (1.0f < c) {
        c = 1.0f;
    } else if (c < -1.0f) {
        c = -1.0f;
    }
    Mat02 bend;
    BuildAxisAngleMatrix(Arccosine(c) - angle, &axis, &bend);
    Vec02 bent;
    Vec02 reachv;
    *(Vec*)&w = *(Vec*)&bent = Vu0::Rotate(bend, Vec::Of(w));
    *(Vec*)&reachv = Vu0::Add(Vec::Of(u), Vec::Of(bent));
    Mat02 swing;
    BuildRotationBetweenVectors(&reachv, &t, (f32*)&swing);
    Mat02 twist;
    Vec02 dir;
    dir = t;
    *(Vec*)&dir = Vu0::DivX(Vec::Of(t), Vu0::Length(Vec::Of(t)));
    BuildAxisAngleMatrix(self->linkRecord->angle, &dir, &twist);
    Mat02 R;
    MulRotationInto(&R, twist, swing);
    swing = R;
    Mat02 upper;
    Mat02 lower;
    MulRotationInto(&lower, bend, rot[1]);
    b->rot = MultiplyByTransposedMatrix3x3(rot[2], lower);
    MulRotationInto(&upper, swing, rot[2]);
    a->rot = MultiplyByTransposedMatrix3x3(rot[3], upper);
    if (a->desc->m12 != 0) {
        a->desc->m12(a);
    }
    if (flags & 1) {
        Vec02 dv;
        Vec02 spin;
        Vec02 v;
        Vec02 sweep;
        Vec02 rest;
        Vec02 n;
        Vec02 swingSpin;
        Vec02 total;
        Vec02 twistSpin;
        Vec02 bendSpin;
        Vec02 rel;
        *(Vec*)&dv = Vu0::Sub(Vec::Of(vel), Vec::Of(vels[2]));
        f32 rate;
        if (AreFloatsNearlyEqual(__builtin_fabsf(c), 1.0f, 1e-4f)) {
            rate = 0.0f;
        } else {
            f32 k = lt / (lw * lu);
            f32 d = Vu0::ToFloat(Vu0::Dot(Vec::Of(dv), Vec::Of(dir)));
            rate = -1.0f / Fpu::Sqrt(1.0f - c * c) * k * d;
        }
        *(Vec*)&v = Vec::FromFloat(rate);
        *(Vec*)&spin = Vu0::MulX(Vec::Of(axis), Vec::Of(v));
        *(Vec*)&v = Vu0::Rotate(swing, Vec::Of(w));
        *(Vec*)&bendSpin = Vu0::RotateUntied(swing, Vec::Of(spin));
        *(Vec*)&sweep = Vu0::Cross(Vec::Of(bendSpin), Vec::Of(v));
        *(Vec*)&rest = Vu0::Sub(Vec::Of(dv), Vec::Of(sweep));
        f32 lr = Vu0::ToFloatMoved(Vu0::Length(Vec::Of(rest)));
        *(Vec*)&n = Vu0::Cross(Vec::Of(t), Vec::Of(rest));
        NormalizeVector(n, g_unitXVector);
        *(Vec*)&swingSpin = Vu0::MulX(Vec::Of(n), Vec::Scalar(lr / lt));
        *(Vec*)&twistSpin = Vu0::MulX(Vec::Of(dir), Vec::ScalarAtValue(self->linkRecord->angleSlope));
        *(Vec*)&total = Vu0::Add(Vec::Of(twistSpin), Vec::Of(swingSpin));
        *(Vec*)&rel = Vu0::Sub(Vec::Of(total), Vec::Of(spins[3]));
        *(Vec*)&b->v160 = Vu0::RotateTransposed(rot[2], Vec::Of(spin));
        *(Vec*)&a->v160 = Vu0::RotateTransposed(rot[3], Vec::Of(rel));
    } else {
        b->v160 = D_00248D30;
        a->v160 = D_00248D30;
    }
    b->linkRecord->p64 = 0;
    a->linkRecord->p64 = 0;
}
