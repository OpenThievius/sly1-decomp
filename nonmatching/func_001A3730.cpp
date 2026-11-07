// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 452/444, checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "globals.h"
#include "mul_rotation.h"
// NEAR (2026-11-08, worker vu0w4-e1): everything up to func_00130540's call is retail's, instruction
// for instruction (the four weights are separate locals, the 0.25 stored before the Scalar of t, which
// retail stores last). The product of the turn and the placement (MulRotationRowsX) has retail's
// arithmetic with other VU0 register numbers (retail: the turn's rows in vf1, vf6, vf2, the
// placement's in vf3, vf5, vf4), and retail stores the three rows and the two quadwords
// func_00130540 returned into the effect together after the product, while here the first row is
// stored right after its sequence and the last goes through a stack copy and a pointer.

extern f32 g_gameClock[];
void func_00130540(void* a, void* b, const T219C_Params* c, const f32* d, void* e, void* f, s32 g, f32 t, f32 u, f32 v);
s32 ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);

void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

void func_001A3730(Effect* self, f32 f)
{
    Vec02 pos;
    Vec02 v10;
    Vec02 v20;
    Vec02 v30;
    Mat02 rot;
    Mat02 turn;
    f32 t;

    if (!(g_gameClock[1] < self->start)) {
        self->q90 = self->q80;
        t = self->start + self->life - g_gameClock[1];
        t = f >? t;
        ComputeObjectFrameAtTime(self->p20, 0, &pos, &rot, 0, 0, t);
        u128 d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->q80));
        u128 w1 = Vu0::Scalar(1.5f / t);
        u128 w2 = Vu0::Scalar(-0.5f);
        u128 w3 = Vu0::Scalar(0.25f);
        u128 c = Vu0::MulX(Vu0::Q(self->qC0), Vu0::Scalar(t));
        Vu0::Q(v10) = Vu0::MulXSum3(d, w1, Vu0::Q(self->qA0), w2, c, w3);
        func_00130540(&self->q80, &self->qA0, (const T219C_Params*)&pos, (const f32*)&v10, &v20, &v30, 0, t, f, 1.0f);
        BuildAxisAngleMatrix((Vec02*)&self->f120, &turn, self->f130 * t / self->life);
        MulRotationRowsX((Mat02*)self->rot50, turn, rot);
        self->q80 = *(Quad219C*)&v20;
        self->qA0 = *(Quad219C*)&v30;
    }
}
