// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 412/444 (92.8%), checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "globals.h"
#include "mul_rotation.h"
// NEAR (2026-11-08, night-size1): now the same size (444) and frame; 19 words differ. The product
// of the turn and the placement is an inline (MulRows) with MulRotationRowsX's locals whose result
// rows go to the effect's rot50 as quadwords (Q), not as a Mat02 copy: retail stores them from the
// VU0 registers after the product, as here. Still differs: the turn's row 1 takes vf3 where retail
// has vf6, so the placement's rows take vf4, vf5, vf6 for retail's vf3, vf5, vf4; and the copies
// of v20/v30 to q80/qA0 load into v1/v0 for retail's v0/v1, stored in another order among the
// rows. Tried: RotateUntied, the turn's rows loaded in four other orders, the two copies swapped,
// the rows stored as Vec02 copies or a Mat02 copy (those keep the old 452 bytes).

extern f32 g_gameClock[];
void func_00130540(void* a, void* b, const T219C_Params* c, const f32* d, void* e, void* f, s32 g, f32 t, f32 u, f32 v);
s32 ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);

void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

static inline void MulRows(Vec02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    Vu0::Q(out[0]) = Vu0::Q(r.r[0]);
    Vu0::Q(out[1]) = Vu0::Q(r.r[1]);
    Vu0::Q(out[2]) = Vu0::Q(r.r[2]);
}

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
        MulRows(self->rot50, turn, rot);
        self->q80 = *(Quad219C*)&v20;
        self->qA0 = *(Quad219C*)&v30;
    }
}
