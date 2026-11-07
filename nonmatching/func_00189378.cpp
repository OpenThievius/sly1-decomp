// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 158/184 (85.9%), checked 2026-11-07
// NEAR: same size class (frame 0xD0), the matrix rows are loaded once and three Rotate results are stored to out; differs in the VU0 register numbers (retail M0..M2 = vf1,vf2,vf4; ours vf2,vf1,vf5) and the order of the dead stores (retail: row pairs 96/48, 112/64, 128/80).
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

void func_00189378(Mat02* self, Mat02* scratch, Mat02* out)
{
    Mat02 local;
    Mat02 m;
    Mat02 t;
    Mat02* z = scratch ? scratch : &local;
    BuildShortestArcRotation(&self->r[2], g_unitZVector, z);
    if (out) {
        u128 x0 = Vu0::Rotate(*z, Vu0::Q(self->r[0]));
        u128 x1 = Vu0::Rotate(*z, Vu0::Q(self->r[1]));
        u128 x2 = Vu0::Rotate(*z, Vu0::Q(self->r[2]));
        Vu0::Q(m.r[0]) = x0;
        Vu0::Q(t.r[0]) = x0;
        Vu0::Q(m.r[1]) = x1;
        Vu0::Q(t.r[1]) = x1;
        Vu0::Q(m.r[2]) = x2;
        Vu0::Q(t.r[2]) = x2;
        Vu0::Q(out->r[0]) = x0;
        Vu0::Q(out->r[1]) = x1;
        Vu0::Q(out->r[2]) = x2;
    }
}

