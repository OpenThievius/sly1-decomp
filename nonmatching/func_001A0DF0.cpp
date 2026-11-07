// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 408/404, checked 2026-11-07
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "camera.h"
#include "globals.h"
#include "mul_rotation.h"
extern f32 g_gameTime;
// NEAR (2026-11-08, worker vu0w4-e1): the vector arithmetic is retail's, instruction for instruction
// (a's rows loaded once, b's rows lazily, the second product's rows in the order retail has). Open:
// retail keeps self + 0x50 in s4 across the first three calls and reads the second product's rows 2 and
// 1 through it (0x20(s4), 0x10(s4)) but row 0 as 0x50(s1); here the compiler folds the address into
// s1 and saves no s4 (frame 480 against 496). The first product's store pattern is also not
// settled: retail stores x, y, z (0x140), the second product's out rows (0xA0) and then r1 (0x110),
// then x, y, z and r2 (0xE0) interleaved; r2 is below r1 and x, y, z above both, which is not the
// order of the header's forms (x, y, z, then r).

void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void func_0019F620(Effect* self, Camera* cam, Vec02* point, Mat02* rot);
void func_00144128(Camera* cam, void* point, void* out);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, void* axis);

void func_001A0DF0(Effect* self, Camera* cam)
{
    Vec02 point;
    Mat02 view;
    Mat02 a;
    Mat02 b;
    Mat02 out;
    Vec02 axis;
    f32 angle;
    f32 t;
    Mat02 r1;
    Mat02* c = (Mat02*)self->rot50;

    func_00144128(cam, &self->f120, &point);
    MultiplyMatrices3x3(c, (Mat02*)&cam->g80, &view);
    MatrixToAxisAngle(&view, &angle, &axis);
    t = (g_gameTime - self->start) / self->life;
    BuildAxisAngleMatrix(&axis, &a, angle * t);
    t = t + t;
    BuildAxisAngleMatrix((Vec02*)((u8*)self->params + 0x40), &b, t * 3.14159274f);
    MulRotationRows(&r1, a, b);
    MulRotationRowsX(&out, r1, *c);
    func_0019F620(self, cam, &point, &out);
}
