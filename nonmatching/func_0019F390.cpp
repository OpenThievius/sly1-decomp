// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 460/460, checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "mul_rotation.h"
// NEAR (2026-11-08, worker vu0w4-e1): the same size; everything but the product of the turn matrix
// and the effect's placement (rot50) is retail's instruction for instruction (the drag and the length
// of the spin, the turn matrix, the second half with TurnMatrixBySpin and Transform). In the
// product retail loads rows 1 and 2 of rot50 after the dead stores of the row before, through
// v0 = s0 + 0x50 (0x10(v0), 0x20(v0)), and stores the three rows to the effect together after the
// third product; here all three rows are loaded first, from s0, and the first row is stored at once.
// Tried: the product in place, through a pointer variable, written out with a Vec02* b.

s32 IsSpinNegligible(void* a);
s32 IsVelocityNegligible(void* a);
s32 IsAccelerationNegligible(void* a);
void TurnMatrixBySpin(void* spin, f32 dt, void* out);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

struct EffectFrame {
    Vec02 r[4];
};

void func_0019F390(Effect* self, f32 dt)
{
    EffectFrame frame;
    Mat02 res;

    if (IsSpinNegligible(&self->v100) == 0) {
        f32 len;
        Vu0::Q(self->v100) = Vu0::MulX(Vu0::Q(self->v100), Vu0::Scalar(self->f110 * dt + 1.0f));
        len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v100)));
        if (0.0001f < len) {
            Vu0::Q(frame.r[0]) = Vu0::MulX(Vu0::Q(self->v100), Vu0::Scalar(1.0f / len));
            BuildAxisAngleMatrix(&frame.r[0], (Mat02*)&frame.r[1], len * dt);
            MulRotationRows(&res, *(Mat02*)&frame.r[1], *(Mat02*)self->rot50);
            *(Mat02*)self->rot50 = res;
        }
    }
    self->q90 = self->q80;
    if (IsVelocityNegligible(&self->qA0) == 0 || IsAccelerationNegligible(&self->qC0) == 0) {
        TurnMatrixBySpin((u8*)self + 0xB0, dt, &frame);
        u128 nv = Vu0::Transform(frame, Vu0::Q(self->qA0), 1.0f);
        Vu0::Q(self->q80) = Vu0::MulAddX(Vu0::Q(self->q80), nv, Vu0::Scalar(dt));
        Vu0::Q(self->qA0) = nv;
    }
}
