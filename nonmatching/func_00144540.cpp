// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 784/772, checked 2026-11-07
// NEAR: wave 4 e3. 772 bytes; ours 784, same frame (336). The shape is retail's: the blend factor (a quadratic of the time since f218, clamped by the unit range and
//       turned by a sine), the eye moved along the turned axis, the rotation from the direction vector, the lens numbers from a MulAddX of the corners, the product
//       of the rotations, BuildProjectionMatrix, BuildViewProjectionMatrix (or the plain one when the blend is over), the inverse, the frustum normals and the
//       transpose into the planes at 0x50. Open: (1) retail's clamp keeps the polynomial in its own register and assigns the result in each arm (ours folds it into
//       the result); (2) the product of rotations in retail has the camera's rows loaded as values (vf7, vf6 early, vf4 late) and its stores go to 0x20/0x30/0x40, 0x90,
//       0xA0, 0x70, 0x80 (a Mat4 at 0x70 partly overwritten before BuildProjectionMatrix) where MulRotation's stores differ; (3) the callee-saved registers (retail
//       self s4, view s5, the two arms' addresses s1 and s3). D_002618C8.. are INCLUDE_DATA in camera.cpp (0.5, 50, {1,-2,1,0}, {0}, {0.05,0,0,0}, {0}, {0}); this near miss declares
//       them extern. ~14 compiles.
#include "common.h"
#include "shapes.h"
#include "collider.h"
#include "world.h"
#include "camera.h"
#include "pad_record.h"
#include "fpu.h"
#include "asm_func.h"
#include "vu0.h"
#include "ramp_profile.h"
#include "placed_object.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "game_clock.h"

#include "mul_rotation.h"
#include "value_range.h"
extern f32 D_002618C8;
extern f32 D_002618CC;
extern f32 D_002618D0[4];
extern f32 D_002618E0[4];
extern f32 D_002618F0[4];
extern f32 D_00261900[4];
extern f32 D_00261910[4];
void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out);
void* InvertMatrix4x4(void* a0, void* a1);
extern f32 D_0026185C;
extern u8 D_00248D40[];
f32 Sine(f32 x);
void BuildRotationFromVector(Vec02* v, Mat4* out);
void BuildProjectionMatrix(Mat4* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void func_001443C8(Mat02* m, Vec02* out, f32 x, f32 y);
void func_00144540(Camera* self)
{
    Vec02 pos;
    Vec02 dir;
    Mat4 rotation;
    Mat02* view;
    f32 f6 = D_0026185C - self->f218;
    if (D_002618C8 < f6) {
        BuildViewProjectionMatrix((f32*)self->f40, (f32*)self->f80, (void*)((u8*)self + 0xC0), (Quad16*)((u8*)self + 0x100));
        view = (Mat02*)self->f80;
        InvertMatrix4x4((u8*)self + 0x100, (u8*)self + 0x140);
    } else {
        f32 t = f6 / D_002618C8;
        f32 poly = D_002618D0[0] + t * (D_002618D0[1] + t * D_002618D0[2]);
        f32 amount = g_unitRange.Clamp(poly);
        view = (Mat02*)self->f80;
        f32 swing = Sine(f6 * D_002618CC) * amount;
        u128 turn = Vu0::Rotate(*view, Vu0::Q(*(Vec02*)D_002618E0));
        u128 s = Vu0::Scalar(swing);
        Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(*(Vec02*)self->f40), turn, s);
        Vu0::Q(dir) = Vu0::MulX(Vu0::Q(*(Vec02*)D_002618F0), s);
        BuildRotationFromVector(&dir, &rotation);
        Vec02 corner;
        Vu0::Q(corner) = Vu0::MulAddX(Vu0::Q(*(Vec02*)D_00248D40), Vu0::Q(*(Vec02*)D_00261900), s);
        MulRotation((Mat02*)&rotation, *view, *(Mat02*)&rotation);
        Vec02 tilt;
        Vu0::Q(tilt) = Vu0::MulX(Vu0::Q(*(Vec02*)D_00261910), s);
        Mat4 proj;
        BuildProjectionMatrix(&proj, corner.x * 640.0f / (self->f1F0 * 4096.0f), corner.y * 224.0f / (self->f1F4 * 4096.0f), tilt.x, tilt.y, self->f1E4, self->f1E8);
        BuildViewProjectionMatrix((f32*)&pos, (f32*)&rotation, &proj, (Quad16*)((u8*)self + 0x100));
        InvertMatrix4x4((u8*)self + 0x100, (u8*)self + 0x140);
    }
    func_001443C8(view, (Vec02*)((u8*)self + 0x180), self->f1F0, self->f1F4);
    {
        f32* d = self->planes[0];
        f32* a = (f32*)((u8*)self + 0x180);
        f32* b = (f32*)((u8*)self + 0x190);
        f32* c = (f32*)((u8*)self + 0x1A0);
        f32* e = (f32*)((u8*)self + 0x1B0);
        s32 n = 2;
        do {
            d[0] = *a++;
            d[1] = *b++;
            d[2] = *c++;
            d[3] = *e++;
            d += 4;
        } while (--n >= 0);
    }
}
