// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 576/568, checked 2026-11-07
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "globals.h"
// NEAR (2026-11-08, worker vu0w4-e1): the structure is retail's: frame size and slots (the turn matrix,
// r and x, y, z of the rotation block, the two vectors of the split sharing r's slots, the weights'
// slot at r's third row), the clamp, the split and the two weights. Differing: the rotation block,
// where retail reads the placement's rows 1 and 2 through s0 = self + 0x50 (0x10(s0), 0x20(s0))
// and row 0 as 0x50(s1) (as func_0019F390 and func_001A0DF0 do), the matrix rows and the direction
// loaded in another order, and the VU0 registers numbered by that; the clamp's float registers.
// Retail's pointer to the placement is saved in s0 (it is formed before the call that builds the
// turn matrix) and not folded into the loads of rows 1 and 2.

extern f32 D_0026B6D0[4];
extern f32 D_0026B6E0[2];
extern f32 D_0026B6E8;
extern f32 D_0026B6EC;
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void MoveEffect(Effect* self, f32 dt);
void SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* across);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void MoveEffect(Effect* self, f32 dt);

void func_001A2830(Effect* self, f32 dt)
{
    Mat02 turn;
    f32 spin = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->qA0), Vu0::Q(self->rot50[0])));
    f32 w = D_0026B6D0[0] + spin * (D_0026B6D0[1] + spin * D_0026B6D0[2]);
    if (w < D_0026B6E0[0]) {
        w = D_0026B6E0[0];
    } else if (D_0026B6E0[1] < w) {
        w = D_0026B6E0[1];
    }
    Vec02* b = self->rot50;
    BuildAxisAngleMatrix(&self->rot50[1], &turn, w * dt);
    f32 saved;
    {
        Mat02 r;
        Vec02 x;
        Vec02 y;
        Vec02 z;
        const u128* p = (const u128*)&turn;
        u128 a0 = p[0];
        u128 a1 = p[1];
        u128 a2 = p[2];
        Vu0::Q(self->qA0) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(self->qA0));
        Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b[0]));
        saved = self->fB0;
        Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b[1]));
        Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b[2]));
        b[1] = r.r[1];
        b[2] = r.r[2];
        self->iB0 = 0;
        b[0] = r.r[0];
    }
    {
        Vec02 along;
        Vec02 across;
        SplitVectorAlongAxis((Vec02*)&self->qA0, b, &along, &across);
        f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(along)));
        Vu0::Q(along) = Vu0::NormalizeOr(Vu0::Q(along), Vu0::Q(g_unitXVector));
        Vu0::Q(self->qA0) = Vu0::MulXSum(Vu0::Q(along), Vu0::Scalar(D_0026B6EC + (D_0026B6E8 * dt + 1.0f) * (len - D_0026B6EC)),
                                         Vu0::Q(across), Vu0::Scalar(saved * dt + 1.0f));
    }
    MoveEffect(self, dt);
    self->fB0 = saved;
}
