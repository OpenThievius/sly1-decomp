// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1512/3316 (45.6%), checked 2026-11-08
// NEAR (2026-11-08, large-1D7778): same size, the frame's locals and every block's code are retail's; three things differ
//
// Still differs (89.9% of instructions with registers, build/swarm notes in the worker's report):
// - The first loop's torque arm (s->v20 - self->v140): retail loads s->v20 again (lqc2 vf3,
//   0x20(s0)), ours reuses the load of the pushing term (vf6), which shifts the VU registers and
//   the scheduling of that block. It is cse1's doing (not GCSE: -fno-gcse keeps it); a pointer to
//   s->v20 taken before ComputeObjectMotionInFrame stops it but keeps the pointer in s1 (retail's
//   s1 is the i < 2 flag). What retail's C had that made the second load a new expression is open.
// - The spill slots: GCSE hoists the addresses of the locals at 0x40, 0x50, 0x70, 0x80, 0x90, 0xC0,
//   0xD0 and the ScalarInGpr(dt) value above the first loop (as retail does); retail's dt value
//   takes the last slot (0x130), ours comes between 0x80's and 0x90's, which adds 16 bytes of
//   frame and moves the later spill slots. Pre_delete makes the new pseudos in hash-bucket order,
//   so the asm's hash (its operands' register numbers) decides it.
// - The loop's saved registers: retail keeps &spin (0x70) in s8 and the two curve tables in s7, s6;
//   ours has the tables in s8, s7 and &spin in s6.
//
// What matched on the way: the frame (block locals reusing the first block's matrix slot, want
// declared before the roll matrix, delta/world/clamped after it); NormalizeInto taking the
// difference by value (retail's store of it at 0x80); `one` named for the clamps that load 1.0
// before the test; floats first in ApproachValueWithRamp's prototype; each pseudo of the yaw
// chain set once (a variable set twice goes to global allocation and loses f12).
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
void StoreFloatAsQuadword(void* out, f32 f);
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
    for (i = 0; i < 4; i++) {
        Slot19* s = &self->f6B0[i];
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
        f32 slip = Vu0::ToFloat(Vu0::Length(side));
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
        f32 push = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(s->v40), Vu0::Q(motion)), Vu0::Q(dir))) * ((QuadraticCurve*)D_002753D0)->Eval(t) * D_002753C8
                 + Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(s->v20), Vu0::Q(b)), Vu0::Q(dir))) * ((QuadraticCurve*)D_002753E0)->Eval(t) * D_002753CC;
        if (push < 0.0f) {
            continue;
        }
        f32 mass = self->mass;
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(push * mass));
        *(u128*)&accel = Vu0::DivX(Vu0::Q(force), Vu0::Scalar(mass));
        Vu0::Q(torque) = Vu0::Cross(Vu0::Sub(Vu0::Q(s->v20), Vu0::Q(self->v140)), Vu0::Q(force));
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
    Vu0::Q(vel) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(self->v170), Vu0::ScalarInGpr(dt));
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
    f32 h = ((ValueRange*)D_00275440)->Limit(((QuadraticCurve*)D_00275430)->Eval(Vu0::ToFloat(Vu0::Dot(Vu0::Q(heading), Vu0::Q(self->rot.r[0])))));
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
    Vu0::Q(delta) = Vu0::DivX(Vu0::Sub(Vu0::Q(want), Vu0::Q(local)), Vu0::ScalarInGpr(dt));
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
        Slot19* s = &self->f6B0[i];
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
