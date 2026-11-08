// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 432/492 (87.8%), checked 2026-11-08
// NEAR: StepGaugeColliderAgent. All the calls and the control flow are retail's. Differs only in the vector registers of the first sequence: retail stores the -1 weight (vf6) after the vmulx, so the result takes the vector's register (vf3, tied through Rotate to the vmulax rows) and dt is vf7; ours stores the weight before the multiply, so the result takes the weight's register. Tried the weights as locals, as separate statements, and Vu0::Set for the stores; the order of the stores did not move.
// Tried (2026-11-08, night-close9): Scalar(-1.0f) inline, Vec values, RotateUntied (RotateRows is far worse): no change; retail loads the rows before the MulX.
#include "common.h"
#include "switched_collider.h"
#include "asm_func.h"
extern f32 g_gameTime[];
#include "vu0.h"
#include "globals.h"
#include "shapes.h"

f32 ArctangentOfRatio(f32 a, f32 b);
Vec02 D_0026A870 = { 5000.0f, 0.0f, 0.0f, 0.0f };
Vec02 D_0026A880 = { 3.0f, -2.0f, -1.0f, 0.0f };

void ApplyTurningColliderDrive(void* self);
f32 WrapAngle(f32 a);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
void AddColliderForce(void* self, Vec02* force);
void ConstrainColliderVector(void* self, void* a, void* b, void* c, s32 d);
void StepAgent(void* self, f32 dt);
extern f32 g_unitRange[];

void StepGaugeColliderAgent(GaugeColliderAgent* self, f32 dt)
{
    if (self->fC10 != 0 && *(f32*)&self->fBA4 <= g_gameTime[0]) {
        Vec02 accel;
        Vec02 moved;
        ApplyTurningColliderDrive(self);
        {
            Vec02 k;
            Vu0::Q(k) = Vu0::FromFloat(-1.0f);
            Vu0::Q(moved) = Vu0::Rotate(self->m110, Vu0::MulX(Vu0::Q(self->v640), Vu0::Q(k)));
        }
        Vu0::Q(accel) = Vu0::DivX(Vu0::Sub(Vu0::Q(moved), Vu0::Q(self->v150)), Vu0::Scalar(dt));
        f32 turn = WrapAngle(self->f638 - ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x));
        f32 a = __builtin_fabsf(turn);
        f32 v = D_0026A880.x + a * (D_0026A880.y + a * D_0026A880.z);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        f32 t;
        if (v < lo) {
            t = lo;
        } else if (hi < v) {
            t = hi;
        } else {
            t = v;
        }
        ClampVectorLength(&accel, &accel, D_0026A870.x * t);
        AddColliderForce(self, &accel);
        if (self->parent == 0 && (self->flags538 & 0x8000000000000ULL) == 0) {
            Vec02 local;
            ConstrainColliderVector(self, &self->v440, &self->gravity, &local, 0);
            AddColliderForce(self, &local);
        }
        for (Attach03* n = self->attached; n != 0; n = n->next) {
            n->owner->desc03()->m33(n->owner, n, dt);
        }
    } else {
        StepAgent(self, dt);
    }
}
