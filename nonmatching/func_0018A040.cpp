// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 276/288 (95.8%), checked 2026-11-08
// NEAR: (2026-11-08, night-size3) the size and every register are retail's now: the clear through
// an inline function (ClearMatrix, FillMemory of its argument) forms &scaling again for FillMemory
// and the first product, as retail does, where a direct FillMemory(&scaling, ...) kept it in a
// saved register. Still differs: the copy step = product before the second product: retail loads
// rows 2, 3, 0, 1 (v1, v0, t0, a3) and stores rows 2, 3, 0 with row 1 in the call's delay slot;
// here row 2, 0, 1, 3, row 3 in the slot. Row-by-row copies in all 24 orders, the copy inside the
// call's argument and the product's return value tried; tools/permute.py --auto found nothing.
#include "common.h"
#include "shapes.h"

extern u8 D_00248D30[];
struct __attribute__((aligned(16))) Matrix3x4 { f32 f[3][4]; };
extern Matrix3x4 g_identityMatrix;
void* FillMemory(void* p, s32 v, s32 n);
void InvertRigidTransform(void* a, void* b, Quad16* out);
Quad16* MultiplyMatrices(Quad16* out, Quad16* m, Quad16* in);
void BuildMatrixFromRotationAndTranslation(Quad16* a, Quad16* b, Quad16* dst);

// A matrix of zeros.
static inline void ClearMatrix(Mat4A* m)
{
    FillMemory(m, 0, sizeof(*m));
}

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
    ClearMatrix(&scaling);
    scaling.m[0][0] = scale[0];
    scaling.m[1][1] = scale[1];
    scaling.m[2][2] = scale[2];
    scaling.m[3][3] = 1.0f;
    MultiplyMatrices((Quad16*)&product, (Quad16*)&scaling, (Quad16*)&inverse);
    step = product;
    MultiplyMatrices((Quad16*)&product, (Quad16*)&frame, (Quad16*)&step);
    *out = product;
}
