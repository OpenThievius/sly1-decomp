// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 315/372 (84.7%), checked 2026-11-06
// NEAR: code: the stores filling the first matrix are ordered differently, the 128-bit third
//       argument of func_00188628 takes two extra moves (retail: mfc1; por a2,zero,v0, sq in the
//       call's delay slot), and the second matrix's pointer is rebuilt differently.
#include "common.h"
#include "shapes.h"

extern const Mat4A D_00248400;
struct Obj_158480 {
    f32 scale;          // 0x00
    u8 pad4[0xC];
    f32 tx, ty, tz;     // 0x10
    u8 pad1C[4];
    f32 angle;          // 0x20
    u8 pad24[0xC];
    Quad16 axis;        // 0x30
    s32 mode;           // 0x40
    void* parent;       // 0x44
};
typedef int V128_158480 __attribute__((mode(TI)));
void TransformDirectionBetweenFrames(void* a, s32 b, void* c, void* d);
void BuildAxisAngleMatrix(void* axis, Mat4* mat, f32 angle);
void MultiplyMatrices(void* out, void* b, void* in);
void ScaleMatrix(void* out, void* in, V128_158480 q);
void AddMatrices(f32* a, f32* b, f32* out);

void TurnMatrixBySpin(Obj_158480* self, f32* out, f32 f)
{
    Mat4A a = D_00248400;
    Mat4A b;
    Quad16 axis;
    Mat4A e;
    Mat4A d;
    Mat4A c;
    Mat4A* p = &b;
    a.m[0][0] = self->scale;
    a.m[3][1] = self->ty;
    a.m[3][0] = self->tx;
    a.m[1][1] = self->scale;
    a.m[2][2] = self->scale;
    a.m[3][2] = self->tz;
    b = D_00248400;
    if (self->angle != 0.0f) {
        if (self->mode == 1 && self->parent != 0) {
            TransformDirectionBetweenFrames(self->parent, 0, &self->axis, &axis);
        } else {
            axis = self->axis;
        }
        BuildAxisAngleMatrix(&axis, (Mat4*)p, self->angle * f);
    }
    MultiplyMatrices(&c, p, &a);
    *(V128_158480*)&axis = (V128_158480)*(s32*)&f;
    ScaleMatrix(&d, &c, *(V128_158480*)&axis);
    e = d;
    AddMatrices((f32*)p, (f32*)&e, out);
}
