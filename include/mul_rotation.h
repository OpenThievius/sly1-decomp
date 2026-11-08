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

// The same two forms with b's rows read by index through a pointer to them (q[i]), as a's are,
// not through Vu0::Q's reference: the pointer to b is a register of its own, the first row is
// loaded at b's offset from the object and the other two at 0x10 and 0x20 from that register
// (`lqc2 0xD0(s0); addiu v0, s0, 0xD0; lqc2 0x10(v0)`), each after the stores of the row before.
// Q's reference parameter is a pseudo of its own, whose address CSE folds into the object's
// offset; an address written in the load stays as it is (func_001225D0, GetPlacedObjectRotationAt).
static inline void MulRotationRowsIndexed(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
    r.r[1] = y;
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
    *out = r;
}

// MulRotationRowsX with b's rows read so.
static inline void MulRotationRowsXIndexed(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, q[0]);
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, q[1]);
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
    *out = r;
}

// MulRotationRowsIndexed into an object's own matrix, written through the object (o->rot = r):
// the result rows are stored at the object's offset, where a Mat02* to the matrix stores them
// through a register of its own (func_00125440, MovePlacedObject; func_001B8148).
template <class O> static inline void MulRotationIntoRot(O* o, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
    r.r[1] = y;
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
    o->rot = r;
}

// The product with a's rows as values, written straight into out's rows (no matrix local), each
// result row stored to its vector local and to out's row: the first product of func_001A0DF0
// (DrawCameraSpaceEffect), whose frame has no third matrix for it.
static inline void MulRotationRowsInto(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::Q(out->r[0]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = Vu0::Q(out->r[1]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = Vu0::Q(out->r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
}

// MulRotationRowsInto with b's rows read by index (MulRotationRowsIndexed) and each row stored
// to its vector local before out's row (func_001A0DF0's second product).
static inline void MulRotationRowsIntoIndexed(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(out->r[0]) = Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
    Vu0::Q(out->r[1]) = Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
    Vu0::Q(out->r[2]) = Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, q[2]);
}

#endif
