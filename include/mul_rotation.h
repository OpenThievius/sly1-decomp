// SPDX-License-Identifier: AGPL-3.0-or-later
// The product of two rotation matrices as the game's inline code computes it: b's rows each
// rotated by a, kept in vector locals and a matrix local, then copied to the result. The groups
// of stack stores in retail's frames show the locals. Three forms are kept because retail's
// sites differ in how a's rows are read (where they are, or loaded once as values) and in the
// order of each row's two stores; the one source form the original had is not known yet, and a
// matched function uses the form whose stores retail shows (docs/TOOLCHAIN.md, "The VU0
// helpers"). Written for this project from what retail's code does.
#ifndef MUL_ROTATION_H
#define MUL_ROTATION_H

#include "common.h"
#include "vu0.h"
#include "placed_object.h"

// The product a b of two rotations into out: b's rows each rotated by a, a's rows read where
// they are (Vu0::RotateUntied), each result row stored to its vector local and then to the
// matrix local (placed_object.cpp's frame functions).
static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}

// The same with a's rows loaded once as values (Vu0::RotateRows), and the last row's two
// stores as one chained assignment (func_00128150, func_00128E88's first product).
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
