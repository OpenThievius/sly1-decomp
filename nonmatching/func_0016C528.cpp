// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 2156/2260 (95.4%), checked 2026-11-08
// NEAR (2026-11-08, worker large-16C528): ApplyLinkConstraint, a two-bone IK solver. Same size
// (565 instructions), frame 0x4A0 and every stack slot as retail's, saved registers as retail's;
// 9 lines differ in two places. (1) After the angular-rate test the VU0 registers vf2 and vf3
// are swapped: retail loads swing's second row into vf3 and dv into vf2 (so rest, the cross
// product's t and the normalisation's length follow), we load them the other way. Local
// allocation order; tried every order of the rotations, the cross product and the subtraction,
// the subtraction inline, rest as a Vec value, ToFloat/ToFloatMoved for its length. (2) In the
// last block retail loads self->f224->f94 (lw, qmtc2 for the twist rate) straight after the swing
// spin's store, before the swing scalar's slot store and the transposed rotation of b's spin;
// ours does it after that rotation. Tried every order of the five tail statements
// (tools/permute.py), a named slot for both scalars, the scalar's store after its product, and a
// FromFloatAt whose operand is a structure member (MEM_IN_STRUCT_P): no change.
//
// What this needed (docs/TOOLCHAIN.md material):
// - The chain arrays of func_00127B20 are four long and it is passed &x[1]: pos[0] is the end
//   effector (the 0x60, 0x120 and 0x160 gaps of retail's frame are rot[0], vels[0], spins[0]).
// - The by-value products of 1DDE90 do not fit here. The swing product goes through a named
//   Mat02 (`Mat02 R; MulRotationInto(&R, twist, swing); swing = R;`, four stores per row), and
//   the two products fed to MultiplyByTransposedMatrix3x3 go into named matrices declared
//   together after it, the one used second first (`Mat02 upper; Mat02 lower;`), so that lower
//   takes 0x300 and upper 0x2D0, and the call's return temporary reuses the product's freed
//   frame (0x330). An inline Mat02-returning product puts the return slot before the argument
//   (calls.c allocates the structure value first) and an assignment adds a temporary.
// - The product's x, y, z locals come before its matrix local, and are written by address
//   (`*(u128*)&x = *(u128*)&r.r[0] = ...`): through Vu0::Q the reference pseudo of the first
//   product's frame (sp+0x2D0) is CSE'd with &upper and held in s1 across the call.
// - BuildAxisAngleMatrix declared with its float first (retail computes Arccosine(c) - angle
//   before the addresses); the identity copy through a pointer (`Mat02* m = &b->rot; *m = ...`);
//   ToFloatMoved for the lengths; `w = bent = Rotate(bend, w)` chained; the final block's
//   vectors declared together at its top, with one scratch vector v holding the rate as a vector
//   and then the rotated arm; NormalizeVector(n, g_unitXVector) as an inline taking the
//   fallback by reference (its address formed before the test).
// - Rec2195_224's f80 (an s32 in attachment.h) is here the first joint object, read as a pointer.
#include "common.h"
#include "c52.h"
#include "vu0.h"
#include "placed_object.h"
#include "attachment.h"
#include "fpu.h"

void SetPlacedObjectVelocity(PlacedObject* self, Vec02* v);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void func_00127E60(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);
void func_00127B20(PlacedObject* self, PlacedObject* top, s32 count, Vec02* pos, Mat02* rot, Vec02* vel,
                   Vec02* spin);
f32 ComputeAngleBetweenVectors(Vec02* a, Vec02* b, Vec02* axis);
f32 Arccosine(f32 x);
void BuildAxisAngleMatrix(f32 angle, Vec02* axis, Mat02* out);
void BuildRotationBetweenVectors(Vec02* from, Vec02* to, Mat02* out);
Mat02 MultiplyByTransposedMatrix3x3(const Mat02& a, const Mat02& b);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 tolerance);
extern Vec02 D_00248D30;
extern Mat02 g_identityMatrix;
extern Vec02 g_unitXVector;

// v made unit length, or fallback when shorter than 0.0001.
static inline void NormalizeVector(Vec02& v, const Vec02& fallback)
{
    Vu0::Vec len = Vu0::Length(Vu0::Vec::Of(v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        v = fallback;
    } else {
        *(Vu0::Vec*)&v = Vu0::DivX(Vu0::Vec::Of(v), len);
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
    Rec2195_224* rec = self->f224;
    s32 flags = rec->f98;
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
    a->rot = MulRotationValue(*(Mat02*)((u8*)a->f224 + 0x30), *(Mat02*)a->f224);
    Rec2195_224* rb = b->f224;
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
    func_00127E60(self, top, &target, 0, &vel, 0);
    Vec02 pos[4];
    Mat02 rot[4];
    Vec02 vels[4];
    Vec02 spins[4];
    func_00127B20(b, top, 3, &pos[1], &rot[1], &vels[1], &spins[1]);
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
    BuildRotationBetweenVectors(&reachv, &t, &swing);
    Mat02 twist;
    Vec02 dir;
    dir = t;
    *(Vec*)&dir = Vu0::DivX(Vec::Of(t), Vu0::Length(Vec::Of(t)));
    BuildAxisAngleMatrix(self->f224->f90, &dir, &twist);
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
        f32 lr = Vu0::ToFloat(Vu0::Length(Vec::Of(rest)));
        *(Vec*)&n = Vu0::Cross(Vec::Of(t), Vec::Of(rest));
        NormalizeVector(n, g_unitXVector);
        *(Vec*)&swingSpin = Vu0::MulX(Vec::Of(n), Vec::Scalar(lr / lt));
        *(Vec*)&twistSpin = Vu0::MulX(Vec::Of(dir), Vec::ScalarAt(self->f224->f94));
        *(Vec*)&total = Vu0::Add(Vec::Of(twistSpin), Vec::Of(swingSpin));
        *(Vec*)&rel = Vu0::Sub(Vec::Of(total), Vec::Of(spins[3]));
        *(Vec*)&b->v160 = Vu0::RotateTransposed(rot[2], Vec::Of(spin));
        *(Vec*)&a->v160 = Vu0::RotateTransposed(rot[3], Vec::Of(rel));
    } else {
        b->v160 = D_00248D30;
        a->v160 = D_00248D30;
    }
    b->f224->p64 = 0;
    a->f224->p64 = 0;
}
