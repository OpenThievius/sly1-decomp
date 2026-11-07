// SPDX-License-Identifier: AGPL-3.0-or-later
// The product of two rotation matrices as the game's code writes it (placed_object.cpp,
// file_19E040.cpp): b's rows each rotated by a, kept in vector locals and a matrix local, then
// copied to the result. The groups of stack stores in retail's frames show it.
#ifndef MUL_ROTATION_H
#define MUL_ROTATION_H

#include "common.h"
#include "vu0.h"
#include "placed_object.h"

// The product a b of two rotations into out: b's rows each rotated by a.
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

#endif
