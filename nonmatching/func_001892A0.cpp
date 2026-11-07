// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 137/176 (77.8%), checked 2026-11-07
// NEAR: same instructions and same frame (0xF0, four Mat02 locals), the three Rotate results stored to the out matrix and two dead locals as retail; only the VU0 registers differ (retail: matrix rows vf1/vf4/vf2, vector rows vf3/vf5/vf6; ours vf1/vf3/vf2 and vf4/vf5/vf6) and the dead stores come in row-pairs in retail (96 then 144 ...). With an untied Rotate result ("j" for the vector instead of "0") the register diff drops to the one swap, but every single-Rotate function then differs (checked in a copy of the header, not committed).
#include "common.h"
#include "shapes.h"
#include "placed_object.h"
#include "vu0.h"

extern u8 g_unitZVector[];
extern u8 g_unitYVector[];
void BuildAxisAngleMatrix(f32* axis, Mat4* mat, f32 angle);
void BuildShortestArcRotation(void* from, void* to, void* out);

// The product of two rotation matrices, as a function returning the three rows.
static inline Mat02 MulRows(const Mat02& a, const Mat02& b)
{
    Mat02 m;
    Vu0::Q(m.r[0]) = Vu0::Rotate(a, Vu0::Q(b.r[0]));
    Vu0::Q(m.r[1]) = Vu0::Rotate(a, Vu0::Q(b.r[1]));
    Vu0::Q(m.r[2]) = Vu0::Rotate(a, Vu0::Q(b.r[2]));
    return m;
}

void func_001892A0(Mat02* out, f32 yaw, f32 pitch)
{
    Mat02 a;
    Mat02 b;
    BuildAxisAngleMatrix((f32*)g_unitZVector, (Mat4*)&a, yaw);
    BuildAxisAngleMatrix((f32*)g_unitYVector, (Mat4*)&b, -pitch);
    *out = MulRows(a, b);
}

