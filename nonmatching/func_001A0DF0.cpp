// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 416/404, checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "camera.h"
#include "globals.h"
#include "mul_rotation.h"
extern f32 g_gameTime;
// NEAR (2026-11-08, night-size2): the second product is mul_rotation.h's MulRotationRowsXIndexed (c's rows read by index through the pointer, as retail's 0x20(s4) and 0x10(s4) after 0x50(s1)), which gives retail's s4, its frame (496) and the second product's loads. Still differs: 416 bytes against 404, the stores: retail writes the first product's x, y, z (0x140) and r1 (0x110) and no third set, the second's x, y, z at 0x140 again and r2 at 0xE0; here r1 is copied to 0xE0 and the second product stores 0x110 as well (12 bytes); and two pairs of insns around the third and fourth calls are swapped. Older note: the first product's store pattern is not one of the header's forms.

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
    MulRotationRowsX(&r1, a, b);
    MulRotationRowsXIndexed(&out, r1, *c);
    func_0019F620(self, cam, &point, &out);
}
