// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 3297/3316 (99.4%), checked 2026-11-12
// DECLS (2026-11-11, w28-nmdecls): StoreFloatAsQuadword now returns void*: neutral, order 828/829.
// NEAR (2026-11-10, w15-1D7778): same size and frame; only the first loop's three saved registers differ
//
// Still differs (9 instructions): the first loop's saved registers. Retail keeps &spin (0x70)
// in s8 and the two push curves (D_002753D0, D_002753E0) in s7, s6; ours has the curves in s8,
// s7 and &spin in s6. All three are loop.c's moves into the preheader (5 refs each, live through
// the loop); global-alloc ranks them by 100000 / live length, so the order is their birth in the
// preheader: ours D0's lo (402), E0's (400), spin's copy (398) ranks spin first (s6, lowest free),
// retail's means spin's copy was born first (spin, D0, E0). loop.c moves in loop order (the
// copy of PRE's &0x70 is at the first call, after the push's curves), and sched1 keeps that
// order (equal raised priorities, LUID decides). What made retail's copy of &spin come before
// the curves is open. Ruled out (2026-11-10, 6 compiles, still 10 lines): spin declared at the
// top (frame changes); the curves as named references before the push, or as pointers passed
// to an inline (both substituted as constants: unchanged); the curve pointers named at the loop
// body's top (635 lines); the loop's eight vectors as members of one struct (80 lines). The
// curves cannot be read after the first call that takes &spin: the push is tested before it.
//
// Measured (2026-11-10, w19, docs/toolchain/loops.md "Three invariants ranked by their place in
// loop.c's move list"): globalalloc.py --set 381:length=402 (or 404) gives retail's three
// registers, so only the copy's birth differs. sched1 ties the preheader's moved insns on
// priority 2, weight 1, class and dependents and keeps loop.c's order (LUID); loop.c moves all
// of them in pass 1 in body order. Retail's copy of &spin was moved after B0's lo_sum and before
// D0's %hi, i.e. the original computed spin's address between the slip statement and the push.
// Ruled out: a pointer or reference to spin there (697 lines: lifetime 0 copy, not moved).
// w22 (2026-11-11): re-scored (same 9 instructions). The .lreg dump confirms the ranking: pseudos
// 227 (B0), 238 (C0), 288 (D0), 316 (E0), 381 (&spin's copy) with 5, 3, 5, 5, 5 refs over 406, 404,
// 402, 400, 398 insns, global order 381, 316, 288, 227. Two ways out, both checked against the
// code: the copy born between C0's and D0's lo_sum (above), or D0 and E0 with one more use each in
// the loop (7 refs: order E0, D0, spin, B0 as retail), which retail's code rules out (c[0] is read
// through the symbol, c[1] and c[2] through the pointer, as ours). With the "*r" ToFloatMoved, the
// along and sum conversions as Moved change nothing (same 9). Wall unchanged.
// What matched (2026-11-10, docs/toolchain gcse.md, alias-classes.md, sched1.md):
// - `s` declared once at the top and assigned by both loops: set twice, it has no base value,
//   so the force's u128 store invalidates s->v20 in cse1 and the torque arm reloads it.
// - The two ScalarInGpr(dt) statements over Vu0::Vec values: 718 insns at gcse, T = 359, which
//   puts the dt value's bucket after the seven frame addresses (its slot last, the frame 528).
// - ToFloatMoved for both terms of the push and for the heading's dot product.
// - Torque before accel, and `push *= mass;` (the product in push's register, f1).
// Earlier: the frame (block locals reusing the first block's matrix slot, want declared before
// the roll matrix, delta/world/clamped after it); NormalizeInto taking the difference by value
// (retail's store of it at 0x80); `one` named for the clamps that load 1.0 before the test;
// floats first in ApproachValueWithRamp's prototype; each pseudo of the yaw chain set once.
// In the context of its file, src/main/file_1D62E0.cpp: the declarations it needs.
#include "common.h"
#include "vu0.h"
#include "switched_collider.h"
#include "globals.h"
#include "value_range.h"

extern f32 g_gameClock[];
extern float D_002751D8;
extern float D_002751E0[];
extern float D_002751F0[];
extern float D_00275200[];
extern float D_00275210[];
extern float D_00275220[];
extern float D_00275230[];
extern float D_00275390;
extern f32 D_00275394;
extern Vec02 D_002753A0;
extern float D_002753B0[];
extern float D_002753C0[];
extern float D_002753C8;
extern float D_002753CC;
extern float D_002753D0[];
extern float D_002753E0[];
extern float D_002753F0[];
extern float D_00275400[];
extern float D_00275410;
extern float D_00275414;
extern float D_00275418;
extern float D_0027541C;
extern f32 D_00275420[];
extern f32 D_00275430[];
extern f32 D_00275440[];
extern f32 D_00275448[];
extern f32 D_00275458[];
extern f32 D_00275470[];
extern f32 D_00275480[];
extern f32 D_00275488;

typedef int Quadword __attribute__((mode(TI)));

struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void AddColliderForce(void* a, void* b);
void BuildAxisAngleMatrix(const Vec02* t, void* out, f32 x);
f32 ClampToMagnitude(f32 a, f32 b);
void* StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
void* StoreQuadword(void* dst, Quadword v);
void StepCollider(Collider* self, f32 t);
void SteerColliderTowardRotation(Collider* self, Mat02* target, Vec02* pull, const Vec02* aim, Vec02* turn, f32 limit);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, s32 a, s32 b, s32 c);
void ApplyColliderInverseInertia(Collider* self, Vec02* in, Vec02* out);
void AddColliderTorque(Collider* self, Vec02* torque);
Quadword ScaleQuadword(Quadword a, Quadword b);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, void* table, f32* out);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);

// v made unit length into out; returns its length.
static inline f32 NormalizeInto(Vec02& out, Vec02 v)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    Vu0::Q(out) = Vu0::DivX(Vu0::Q(v), len);
    return Vu0::ToFloat(len);
}

void StepPathFollower(PathFollower* self, f32 dt)
{
    StepCollider(self, dt);
    if (g_gameClock[1] - self->f850 > D_00275390 && g_gameClock[1] - self->f86C > D_00275394) {
        Mat02 upright;
        RotateMatrixUpright(&self->rot, 0, &upright);
        SteerColliderTowardRotation(self, &upright, &D_002753A0, 0, 0, dt);
    }
    f32 sum = 0.0f;
    u32 i;
    Slot19* s;
    for (i = 0; i < 4; i++) {
        s = &self->f6B0[i];
        if (s->f0C != self->f6A0) {
            continue;
        }
        Vec02 a;
        Vec02 b;
        Vec02 dir;
        Vec02 motion;
        Vec02 force;
        Vec02 torque;
        Vec02 accel;
        Vec02 spin;
        s32 front = (s32)i < 2;
        a = *(Vec02*)((u8*)s->obj8 + 0x40);
        a.z -= front ? self->f610 : self->f614;
        TransformPointBetweenFrames(self, 0, &a, &a);
        b = s->obj->v190;
        b.z -= front ? self->f610 : self->f614;
        TransformPointBetweenFrames(self, 0, &b, &b);
        Vu0::Q(dir) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
        f32 len = NormalizeInto(dir, dir);
        ComputeObjectMotionInFrame(self, 0, &s->v20, &motion, 0, 0, 0);
        u128 axis = Vu0::Q(s->v30);
        u128 side = Vu0::Sub(Vu0::Q(motion), Vu0::MulX(axis, Vu0::Dot(Vu0::Q(motion), axis)));
        f32 slip = Vu0::ToFloatMoved(Vu0::Length(side));
        s->f5C += ((ValueRange*)D_002753C0)->Clamp(((QuadraticCurve*)D_002753B0)->Eval(slip)) * dt;
        f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(s->v20), Vu0::Q(b)), Vu0::Q(dir))) / len;
        f32 one = 1.0f;
        f32 t;
        if (along < 0.0f) {
            t = 0.0f;
        } else if (one < along) {
            t = one;
        } else {
            t = along;
        }
        f32 push = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(s->v40), Vu0::Q(motion)), Vu0::Q(dir))) * ((QuadraticCurve*)D_002753D0)->Eval(t) * D_002753C8
                 + Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(s->v20), Vu0::Q(b)), Vu0::Q(dir))) * ((QuadraticCurve*)D_002753E0)->Eval(t) * D_002753CC;
        if (push < 0.0f) {
            continue;
        }
        f32 mass = self->mass;
        push *= mass;
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(push));
        Vu0::Q(torque) = Vu0::Cross(Vu0::Sub(Vu0::Q(s->v20), Vu0::Q(self->v140)), Vu0::Q(force));
        *(u128*)&accel = Vu0::DivX(Vu0::Q(force), Vu0::Scalar(mass));
        ApplyColliderInverseInertia(self, &torque, &spin);
        AddColliderForce(self, &accel);
        AddColliderTorque(self, &spin);
        sum += Vu0::ToFloat(Vu0::Dot(Vu0::Q(force), Vu0::Q(self->rot.r[2])));
    }
    if (sum == 0.0f) {
        f32 t = (g_gameClock[1] - self->f86C) / D_00275394;
        f32 k = g_unitRange.Clamp(((QuadraticCurve*)D_002753F0)->Eval(t));
        u8* p = (u8*)D_00275400;
        Quadword q;
        StoreFloatAsQuadword(&q, k);
        Quadword qv = q;
        Quadword u;
        CopyQuadword(&u, p);
        Vec02 turn;
        StoreQuadword(&turn, ScaleQuadword(qv, u));
        SteerColliderTowardRotation(self, 0, 0, &D_00248D30, &turn, dt);
    }
    f32 one = 1.0f;
    f32 drive = sum / (self->mass * D_00275410);
    if (drive < 0.0f) {
        drive = 0.0f;
    } else if (one < drive) {
        drive = one;
    }
    self->fB9C = drive;
    f32 grip = self->fAFC != 0 ? self->fAFC->f18 : self->f868;
    f32 lap = (g_gameClock[1] - self->f854) / D_002751D8;
    f32 limit = D_00275414 <? grip * sum / self->mass;
    f32 w = ((ValueRange*)D_00275210)->Clamp(((QuadraticCurve*)D_00275200)->Eval(lap));
    if (1.0f < self->f85C) {
        w *= self->f85C * self->f85C;
    }
    limit *= w;
    Vec02 vel;
    Vu0::Q(vel) = Vu0::MulAddX(Vu0::Vec::Of(self->v150), Vu0::Vec::Of(self->v170), Vu0::Vec::ScalarInGpr(dt)).q;
    Vec02 local;
    Vu0::Q(local) = Vu0::RotateTransposed(self->rot, Vu0::Q(vel));
    f32 span = self->f6B0[0].obj->v190.x - self->f6B0[2].obj->v190.x;
    f32 rate = self->f698 / self->f618;
    f32 r;
    if (rate < 0.0f) {
        r = 0.0f;
    } else if (1.0f < rate) {
        r = 1.0f;
    } else {
        r = rate;
    }
    r *= g_unitRange.Clamp(((QuadraticCurve*)D_00275420)->Eval(local.x / self->f618));
    f32 yaw = (local.x <? D_0027541C) * self->f69C;
    f32 r2 = r * self->f69C;
    Vec02 spinL;
    Vu0::Q(spinL) = Vu0::RotateTransposed(self->rot, Vu0::Q(self->v160));
    f32 inertia = self->mass * __builtin_fabsf(self->f6B0[0].obj->v190.x) / self->inertia.r[2].z;
    Vec02 c;
    c.x = c.y = 0.0f;
    f32 tq = ClampToMagnitude((yaw / span + r2 * D_00275418 - spinL.z) / dt, inertia * limit);
    c.z = tq;
    inertia = tq / inertia;
    Vec02 torque2;
    Vu0::Q(torque2) = Vu0::Rotate(self->rot, Vu0::Q(c));
    limit -= __builtin_fabsf(inertia);
    AddColliderTorque(self, &torque2);
    f32 lean = ((ValueRange*)D_002751F0)->Clamp(((QuadraticCurve*)D_002751E0)->Eval(lap)) * self->f85C;
    f32 tilt = (D_002751F0[1] <? lean) / self->f85C;
    Vec02 heading;
    ComputePolarOffset(&heading, self->f694, 1.0f, 0.0f);
    f32 h = ((ValueRange*)D_00275440)->Limit(((QuadraticCurve*)D_00275430)->Eval(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(heading), Vu0::Q(self->rot.r[0])))));
    Vec02 want;
    Mat02 roll;
    BuildAxisAngleMatrix(&g_unitZVector, &roll, (spinL.z + c.z * (dt * 0.5f)) * dt);
    f32 speed;
    if (1.0f < tilt) {
        speed = tilt * self->f618;
    } else {
        speed = tilt * h * self->f698;
    }
    Vu0::Q(want) = Vu0::FromFloats(speed, 0.0f, 0.0f);
    Vu0::Q(want) = Vu0::RotateUntied(roll, Vu0::Q(want));
    f32 maxAccel = ((ValueRange*)D_00275230)->Limit(((QuadraticCurve*)D_00275220)->Eval(lap));
    Vec02 delta;
    Vec02 world;
    Vec02 clamped;
    Vu0::Q(delta) = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(want), Vu0::Vec::Of(local)), Vu0::Vec::ScalarInGpr(dt)).q;
    delta.z = 0.0f;
    ClampVectorLength(&delta, &clamped, limit >? maxAccel);
    if (self->f698 != 0.0f && self->fB30 == 0) {
        f32 out;
        if (local.x < self->f698) {
            ApproachValueWithRamp(local.x, self->f698, dt, D_00275448, &out);
            clamped.x = (out >? maxAccel) <? clamped.x;
        } else {
            ApproachValueWithRamp(local.x, self->f698, dt, D_00275458, &out);
            clamped.x = out >? clamped.x;
        }
    }
    Vu0::Q(world) = Vu0::Rotate(self->rot, Vu0::Q(clamped));
    AddColliderForce(self, &world);
    for (i = 0; i < 4; i++) {
        s = &self->f6B0[i];
        if (s->f0C == self->f6A0) {
            f32 p = ((ValueRange*)D_00275480)->Limit(((QuadraticCurve*)D_00275470)->Eval(Vu0::ToFloat(Vu0::Length(Vu0::Q(delta))) * dt));
            s->f58 += p * g_gameClock[2];
        }
    }
    Vec02 tq3;
    Vu0::Q(tq3) = Vu0::Cross(Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::ScalarAt(D_00275488)), Vu0::MulX(Vu0::Q(world), Vu0::ScalarAt(self->mass)));
    ApplyColliderInverseInertia(self, &tq3, &torque2);
    AddColliderTorque(self, &torque2);
}
