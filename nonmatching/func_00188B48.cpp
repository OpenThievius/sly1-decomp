// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 192/196 (98.0%), checked 2026-11-07
// NEAR: two dead stores swapped: retail stores the transposed rows to the stack in the order 0x30, 0x40, 0x10, 0x50, 0x20; here 0x30, 0x40, 0x50, 0x10, 0x20. Everything else is retail's (Vu0::Transpose's two sequences and registers, the negated rotated position in place). Tried every order of the row assignments in Transpose, Q/Set/pointer stores, the result through a caller local (in a block or not, rows copied in every order) and through an out parameter.
// In the context of its file, src/main/matrix.cpp.
#include "common.h"
#include "shapes.h"
#include "vu0.h"

void InvertRigidTransform(void* a, void* b, Quad16* out)
{
    *(Vu0::Rows*)out = Vu0::Transpose(*(Vu0::Rows*)b);
    Vu0::Q(out[3]) = Vu0::RotateTransposed(*(Vu0::Rows*)b, Vu0::Q(*(Quad16*)a));
    Vu0::Q(out[3]) = Vu0::MulX(Vu0::Q(out[3]), Vu0::Scalar(-1.0f));
    out[0].w[3] = 0;
    out[1].w[3] = 0;
    out[2].w[3] = 0;
    *(f32*)&out[3].w[3] = 1.0f;
}
