// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 287/304 (94.4%), checked 2026-11-07
#include "common.h"
#include "camera.h"
#include "globals.h"
#include "placed_object.h"
#include "shapes.h"
#include "vu0.h"
void InitIdentityMatrix(void* self);
void MultiplyMatrices(void* out, void* b, void* in);
void BuildBasisFromX(void* in, void* out);
void func_001A2070(void* m, void* a, void* b);
// NEAR (2026-11-07, worker vu0-e6): every instruction is retail's; five lines differ in the order
// of three register moves: retail sets a0 (the address of the first matrix) before it saves a2
// in s3, and sets a0/a2/a1 of the multiplication in that order, here the saves come first and
// the arguments in a1/a0/a2 order. Tried: pointer locals, the temporaries in the other order,
// the copies through a pointer.

void func_001A1F40(Vec02* pos, void* a1, void* a2)
{
    Mat4 m0;
    Mat4 m1;
    Vec02 v;
    Mat02 rot;
    Quad16 t[4];
    Quad16 r[4];
    InitIdentityMatrix(&m0);
    InitIdentityMatrix(&m1);
    m0.m[3][0] = -((f32*)g_camera)[16];
    m0.m[3][1] = -((f32*)g_camera)[17];
    m0.m[3][2] = -((f32*)g_camera)[18];
    Vu0::Q(v) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(g_camera->f40));
    BuildBasisFromX(&v, &rot);
    m1.m[0][0] = -rot.r[1].x;
    m1.m[1][0] = -rot.r[1].y;
    m1.m[2][0] = -rot.r[1].z;
    m1.m[0][1] = rot.r[2].x;
    m1.m[1][1] = rot.r[2].y;
    m1.m[2][1] = rot.r[2].z;
    m1.m[0][2] = rot.r[0].x;
    m1.m[1][2] = rot.r[0].y;
    m1.m[2][2] = rot.r[0].z;
    MultiplyMatrices(r, &m1, &m0);
    t[0] = r[0];
    t[1] = r[1];
    t[2] = r[2];
    t[3] = r[3];
    func_001A2070(t, a1, a2);
}
