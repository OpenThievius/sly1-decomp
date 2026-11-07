// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 334/340 (98.2%), checked 2026-11-07
// NEAR: one swap in the call to ApproachValueWithRamp: retail moves the limit (mov.s f14,f20) before move a0,s0; here after. The rest is retail's (MulRotationRowsX of include/mul_rotation.h, the step and angle as scalars, the spin's FromFloatAt weight stored in a slot of its own, which needs the ScalarAt form the header lacks: written here with Vu0::Slot).
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
#include "common.h"
#include "ramp_profile.h"
#include "mul_rotation.h"

f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, f32* axis);
void BuildAxisAngleMatrix(Vec02* axis, Mat02* out, f32 angle);

void func_001EA918(Mat02* from, Mat02* to, RampProfile* ramp, Mat02* outRot, Vec02* outSpin, f32 limit)
{
    Mat02 rel;
    Mat02 built;
    Vec02 axis;
    f32 angle;
    f32 step;
    MultiplyMatrices3x3(from, to, &rel);
    MatrixToAxisAngle(&rel, &angle, (f32*)&axis);
    f32 a = angle;
    f32 travel = ApproachValueWithRamp(ramp, &step, 0.0f, a, limit);
    if (outRot != 0) {
        if (travel == angle) {
            *outRot = *to;
        } else {
            BuildAxisAngleMatrix(&axis, &built, travel);
            MulRotationRowsX(outRot, built, *from);
        }
    }
    if (outSpin != 0) {
        Vu0::Slot t;
        Vu0::Q(t) = Vu0::FromFloatAt(step);
        Vu0::Q(*outSpin) = Vu0::MulX(Vu0::Q(axis), Vu0::Q(t));
    }
}
