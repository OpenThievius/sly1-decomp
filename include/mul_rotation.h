// SPDX-License-Identifier: AGPL-3.0-or-later
// The product of two rotations as retail's inline code computes it: b's rows each rotated by a's
// rows, which are loaded once as values (Vu0::RotateRows); a result row is stored to a local of
// the product and to the local it is copied from, in the order the chained assignments give.
// Written for this project from what retail's code does (docs/TOOLCHAIN.md, "The VU0 helpers").
#ifndef MUL_ROTATION_H
#define MUL_ROTATION_H

#include "common.h"
#include "placed_object.h"
#include "vu0.h"

// out = a times b, the rows of the result stored as the separate statements give.
static inline void MulRotationRows(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    *out = r;
}

// The same with each row's two stores in the other order (func_00128E88's second product).
static inline void MulRotationRowsX(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    *out = r;
}


#endif
