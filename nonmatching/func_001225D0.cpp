// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 260/264, checked 2026-11-07
// NEAR: GetPlacedObjectRotationAt. The structure is retail's (the spring-less branch builds the rotation from the scaled spin, then the product of the two rotations); the product differs in scheduling only: retail reads the second matrix's rows (self->rot) lazily, one after the sequence before it and after the stores of the previous row's result, and orders the sequences row 0, 1, 2; ours reads them all up front and orders them 2, 0, 1. The rows of the first matrix as values (RotateRows) are right. MulRotation of func_00122CB0 (rows of a as values, b in place) was tried; a pointer or a separate inline gave the same order.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "attachment.h"
#include "anim_curve.h"
#include "globals.h"
#include "buffered_stream.h"
#include "script_value.h"

void BuildRotationFromVector(f32* in, f32* out);
void MatrixToAxisAngle(void*, void*, void*);

// The product a b of two rotations into out: b's rows each rotated by a, the rows of a read once.
static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    const u128* p = (const u128*)&a;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}

void GetPlacedObjectRotationAt(PlacedObject* self, f32 t, Mat02* rot, Vec02* vec)
{
    Vec02 d;
    Mat02 m;
    Vec02 k;
    Attachment* source = self->f1F0;
    if (t == 0.0f) {
        *rot = self->rot;
        *vec = self->v160;
    } else if (source) {
        source->vt->getRot(source, t, rot, vec);
    } else {
        u128 w = Vu0::Q(self->v160);
        Vu0::Q(k) = Vu0::FromFloat(t);
        Vu0::Q(*vec) = w;
        Vu0::Q(d) = Vu0::MulX(w, Vu0::Q(k));
        BuildRotationFromVector((f32*)&d, (f32*)&m);
        MulRotation(rot, m, self->rot);
    }
}
