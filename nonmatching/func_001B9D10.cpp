// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 501/536 (93.5%), checked 2026-11-08
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call 2 (source line 43); 16 differing lines before, 14 now.
// NEAR (2026-11-08, night-size2): the same size as retail now: the difference of the torque as a u128 kept for the length and the scale (retail's vf6 across the if, where Q(torque) read it back from the stack). Still differs: float registers (retail keeps the clamped step in f4 and the dot in f3, ours in f3 and f0, so rest is in f0 there and f2 here; the operands of along + step, the dot read inline and ToFloatMoved change nothing) and the last MulX (retail's Scalar in vf1 and the result in vf2, ours the other way) with the order of the call's argument moves.
#include "common.h"
#include "collider.h"
#include "globals.h"
#include "vu0.h"

f32 ClampToMagnitude(f32 value, f32 limit);

void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void AddColliderTorque(Collider* self, Vec02* torque);

void TurnColliderTowardRotation(Collider* self, Mat02* target, f32* gain, f32 dt)
{
    Mat02 m;
    Vec02 axis;
    Vec02 want;
    Vec02 torque;
    Vec02 have;
    f32 angle;
    f32 limit = gain[0];
    f32 rate = (limit - gain[1]) / gain[2];
    f32 zone = limit * limit / (rate + rate);
    f32 speed = Vu0::ToFloat(Vu0::Length(Vu0::Q(self->v160)));
    if (limit < speed) {
        Vu0::Q(torque) = Vu0::MulX(Vu0::Q(self->v160), Vu0::Scalar((limit - speed) * 2.5f / speed));
        AddColliderTorque(self, &torque);
    }
    MultiplyMatrices3x3(&self->rot, target, &m);
    MatrixToAxisAngle(&m, &angle, &axis);
    f32 step = ClampToMagnitude(angle / zone * limit, limit);
    f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v160), Vu0::Q(axis)));
    f32 rest = angle - (along + step) * (dt * 0.5f);
    if (rest < zone) {
        step = ClampToMagnitude(rest / zone * limit, limit);
    }
    Vu0::Q(want) = Vu0::MulX(Vu0::Q(axis), Vu0::Scalar(step));
    Vu0::Q(have) = Vu0::MulAddX(Vu0::Q(self->v160), Vu0::Q(self->v180), Vu0::Scalar(dt));
    u128 diff = Vu0::Sub(Vu0::Q(want), Vu0::Q(have));
    Vu0::Q(torque) = diff;
    f32 error = Vu0::ToFloatMoved(Vu0::Length(diff));
    f32 scale;
    if (error < rate * dt) {
        scale = 1.0f / dt;
    } else {
        scale = rate / error;
    }
    Vu0::Q(torque) = Vu0::MulX(diff, Vu0::Scalar(scale));
    AddColliderTorque(self, &torque);
}
