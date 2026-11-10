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

// MulRotationIntoRot with the matrix local declared first, as MulRotationIntoRotMatFirst, and
// each row's two stores as one chained assignment (MulRotationRowsX): ApplyPoseSourceRotation's
// spring and ramp products.
template <class O> static inline void MulRotationIntoRotX(O* o, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, q[0]);
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, q[1]);
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

// MulRotationIntoRot with the matrix local declared before the row locals, so its rows sit
// below them in the frame, and every row stored to its local and then to the matrix
// (ApplyPoseSourceRotation's eased product: retail copies the rows from the lower block).
template <class O> static inline void MulRotationIntoRotMatFirst(O* o, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, q[2]);
    r.r[2] = z;
    o->rot = r;
}

// A matrix's three rows set from quadword values passed as the signed quadword type. The
// product's rows are u128, so each argument is converted and g++ binds a temporary of s128 to
// the reference: a scalar's slot in the frame (MEM_SCALAR_P), stored though nothing reads it
// back, the three alive together for the call and so at three addresses above the locals.
// Loads of structure members through a pointer never wait for such stores
// (fixed_scalar_and_varying_struct_p), so they sink below later code as retail's do
// (docs/TOOLCHAIN.md, "Three row copies made by one call").
static inline void SetRows(Mat02& m, const s128& x, const s128& y, const s128& z)
{
    Vu0::Q(m.r[0]) = x;
    Vu0::Q(m.r[1]) = y;
    Vu0::Q(m.r[2]) = z;
}

// The product a b with a's rows loaded once as values and the three result rows put in the
// matrix local by SetRows, then copied to out (GetIdentityPoseRotation, func_00122B30).
static inline void MulRotationSetRows(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    const u128* p = (const u128*)&a;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    u128 x = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    u128 y = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    u128 z = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    SetRows(r, x, y, z);
    *out = r;
}

// A matrix's three rows set from quadwords that are already in memory, bound where they are:
// the arguments are u128 lvalues, so no copy is made for the call.
static inline void SetRowsFrom(Mat02& m, const u128& x, const u128& y, const u128& z)
{
    Vu0::Q(m.r[0]) = x;
    Vu0::Q(m.r[1]) = y;
    Vu0::Q(m.r[2]) = z;
}

// The product a b into out with the matrix local r the caller's: a's rows loaded once as values,
// b's read as Vec members, and each result row, in SetRowsFrom's own argument, copied through a
// cast (Vu0::Scalar's copy, a scalar's slot) and then stored to r's row, which is what the call
// reads. The three slots are temporaries of the one call statement, so they are distinct and
// alive together; each is stored before its row of r, as retail's last row shows (the slot's
// store and r's tie at the block's end, and the earlier insn goes first). b's rows as structure
// members never wait for the slots' stores (fixed_scalar_and_varying_struct_p), only for r's
// (func_00172078, OrientPlayerSpinPart's second product; docs/TOOLCHAIN.md, "A rotation
// product's last two stores").
static inline void MulRotationCopiedVia(Mat02* out, Mat02& r, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    const Vu0::Vec* q = (const Vu0::Vec*)&b;
    u128 x, y, z;
    SetRowsFrom(*out, Vu0::Q(r.r[0]) = Vu0::Q((s128)(x = Vu0::RotateRows(a0, a1, a2, q[0].q))),
                Vu0::Q(r.r[1]) = Vu0::Q((s128)(y = Vu0::RotateRows(a0, a1, a2, q[1].q))),
                Vu0::Q(r.r[2]) = Vu0::Q((s128)(z = Vu0::RotateRows(a0, a1, a2, q[2].q))));
}

// MulRotationCopiedVia with the matrix local its own (UpdateFrameCameraController,
// func_0014A8F8; func_001721B0's spin part).
static inline void MulRotationCopied(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    const u128* p = (const u128*)&a;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    const Vu0::Vec* q = (const Vu0::Vec*)&b;
    u128 x, y, z;
    SetRowsFrom(*out, Vu0::Q(r.r[0]) = Vu0::Q((s128)(x = Vu0::RotateRows(a0, a1, a2, q[0].q))),
                Vu0::Q(r.r[1]) = Vu0::Q((s128)(y = Vu0::RotateRows(a0, a1, a2, q[1].q))),
                Vu0::Q(r.r[2]) = Vu0::Q((s128)(z = Vu0::RotateRows(a0, a1, a2, q[2].q))));
}

// The product a b with the three rows computed first and then set into out by SetRowsFrom
// through their casts' copies, three slots of the one call (func_00172078's first product).
static inline void MulRotationThenCopy(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    u128 x = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    u128 y = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    u128 z = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    SetRowsFrom(*out, Vu0::Q((s128)x), Vu0::Q((s128)y), Vu0::Q((s128)z));
}

// MulRotationThenCopy through the caller's matrix local r: each row's cast copy stored to r's
// row in SetRowsFrom's own argument, so a slot's store and r's row alternate in the expand
// order, and out is set from r's rows (UpdateTargetCameraController's second product, the
// camera's matrix set through a local: retail stores r's row 0 between the first and second
// slots).
static inline void MulRotationThenCopyVia(Mat02* out, Mat02& r, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    u128 x = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    u128 y = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    u128 z = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    SetRowsFrom(*out, Vu0::Q(r.r[0]) = Vu0::Q((s128)x), Vu0::Q(r.r[1]) = Vu0::Q((s128)y),
                Vu0::Q(r.r[2]) = Vu0::Q((s128)z));
}

#endif
