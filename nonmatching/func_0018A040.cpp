// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 292/288, checked 2026-11-08
// NEAR: every call, store and copy is retail's; the registers differ. Retail keeps &inverse in
// s0 and computes &scaling (sp+0x80) afresh for FillMemory and the first product; ours keeps
// &scaling in a saved register across FillMemory (one move more) and gives pos and rot s0/s1
// where retail has s1/s2. Tried: an array for inverse, pointer locals for pos and rot, a Vec4U
// scale, a pointer local for inverse, sizeof in FillMemory.
#include "common.h"
#include "shapes.h"

extern u8 D_00248D30[];
struct __attribute__((aligned(16))) Matrix3x4 { f32 f[3][4]; };
extern Matrix3x4 g_identityMatrix;
void* FillMemory(void* p, s32 v, s32 n);
void InvertRigidTransform(void* a, void* b, Quad16* out);
Quad16* MultiplyMatrices(Quad16* out, Quad16* m, Quad16* in);
void BuildMatrixFromRotationAndTranslation(Quad16* a, Quad16* b, Quad16* dst);

// The transform that scales by scale along the axes of the frame of rotation rot at pos (the
// origin and identity when they are null): back into the frame, scaled, out again.
void BuildScaleAboutFrame(Quad16* pos, Quad16* rot, f32* scale, Mat4A* out)
{
    Mat4A frame;
    Mat4A inverse;
    Mat4A scaling;
    Mat4A step;
    Mat4A product;

    if (pos == 0)
        pos = (Quad16*)D_00248D30;
    if (rot == 0)
        rot = (Quad16*)&g_identityMatrix;
    BuildMatrixFromRotationAndTranslation(pos, rot, (Quad16*)&frame);
    InvertRigidTransform(pos, rot, (Quad16*)&inverse);
    FillMemory(&scaling, 0, 0x40);
    scaling.m[0][0] = scale[0];
    scaling.m[1][1] = scale[1];
    scaling.m[2][2] = scale[2];
    scaling.m[3][3] = 1.0f;
    MultiplyMatrices((Quad16*)&product, (Quad16*)&scaling, (Quad16*)&inverse);
    step = product;
    MultiplyMatrices((Quad16*)&product, (Quad16*)&frame, (Quad16*)&step);
    *out = product;
}
