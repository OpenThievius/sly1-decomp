// SPDX-License-Identifier: AGPL-3.0-or-later
// The VU0 macro-mode sequences the game's C used through inline-assembly helpers. Written for
// this project from retail's code (docs/TOOLCHAIN.md, "The VU0 helpers").
//
// The game's compiler keeps a 128-bit value in a VU0 register itself: the constraint `j` names
// the class $vf1..$vfN (-mvu0-use-vf0-vfN, config/cflags.tsv), and the compiler loads and stores
// such a value with lqc2 and sqc2, which it schedules with the rest of the function, and picks
// the registers. So a helper holds only what the compiler cannot emit: each is one __asm__
// statement for one sequence that recurs across retail's functions, on u128 values.
//
// - A helper takes and returns u128 by value (an aggregate as a `j` operand does not compile).
//   A vector in memory (any 16-aligned 16-byte object) is read and written through Vu0::Q: one
//   lqc2, one sqc2. A helper's result that is never named stays in its register.
// - A vector local (Vec02, Quad16) lives on the stack, so a result assigned to it is stored
//   there even when nothing reads it back: retail's stores to the stack that nothing loads. A
//   float made a vector (FromFloat) is always stored so in retail: it goes into a local.
// - A float weight retail stores in a slot of its own that later weights reuse goes through
//   Scalar, a helper whose 16-byte local takes the store (not a local of the caller's).
// - None is volatile: retail schedules loads, stores and other code across them.
// - A result may take an input's register ("=j"). The order of the inputs matters: the
//   allocator gives the result the register of the first input that dies there, so each
//   helper lists its inputs in the order retail's registers show (MulX the scale first), and
//   Rotate's result is tied to the vector it rotates ("0"). A register a sequence only
//   writes (Dot's 1.0) is a second output.
#ifndef VU0_H
#define VU0_H

#include "common.h"

// A 128-bit value: what a VU0 register holds.
typedef unsigned int u128 __attribute__((mode(TI)));

struct Vu0 {
    // A vector local of a helper's own (Scalar): 16-aligned, so it lives on the stack.
    struct __attribute__((aligned(16))) Slot {
        f32 v[4];
    };

    // A 16-aligned, 16-byte object read or written as one 128-bit value.
    template <class T> static u128& Q(T& v) { return *(u128*)&v; }
    template <class T> static const u128& Q(const T& v) { return *(const u128*)&v; }

    // (0, 0, 0, 0): vsub.xyzw r, vf0, vf0.
    static u128 Zero()
    {
        u128 r;
        __asm__("vsub.xyzw %0, vf0, vf0" : "=j"(r));
        return r;
    }

    // a + b: vadd.xyzw.
    static u128 Add(u128 a, u128 b)
    {
        u128 r;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
        return r;
    }

    // a - b: vsub.xyzw.
    static u128 Sub(u128 a, u128 b)
    {
        u128 r;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
        return r;
    }

    // A float into the x of a VU0 register: qmtc2 (the compiler moves it to a GPR first).
    static u128 FromFloat(f32 f)
    {
        u128 r;
        __asm__("qmtc2 %1, %0" : "=j"(r) : "r"(f));
        return r;
    }

    // A float as a vector of its own: FromFloat into a 16-byte local of the helper, stored to
    // the stack though nothing reads it back. Retail's weights show it: the two of a MulXSum
    // (or three, with a MulAddX after it) share one stack slot, as locals of calls that have
    // ended do, the first stored first, each store after the arithmetic that uses it. The
    // same float twice (Scalar(dt) in two expressions) is one qmtc2 and two stores.
    static u128 Scalar(f32 f)
    {
        Slot t;
        Q(t) = FromFloat(f);
        return Q(t);
    }

    // The x of a VU0 register as a float: qmfc2 (the compiler moves it on to an FPR).
    static f32 ToFloat(u128 a)
    {
        f32 r;
        __asm__("qmfc2 %0, %1" : "=r"(r) : "j"(a));
        return r;
    }

    // a * s.x: vmulx.xyzw.
    static u128 MulX(u128 a, u128 s)
    {
        u128 r;
        __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s), "j"(a));
        return r;
    }

    // a + b * s.x: vadda.xyzw ACC, a, vf0; vmaddx.xyzw.
    static u128 MulAddX(u128 a, u128 b, u128 s)
    {
        u128 r;
        __asm__("vadda.xyzw ACC, %1, vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s));
        return r;
    }

    // The three-term dot product of a and b, in x: vmul.xyz, then 1.0 into a scratch x
    // (vaddw.x) to sum the terms with vadday.x and vmaddz.x.
    static u128 Dot(u128 a, u128 b)
    {
        u128 r, one;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, vf0, vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
                : "=j"(r), "=j"(one) : "j"(a), "j"(b));
        return r;
    }

    // The xyz of a 3x3 matrix's rows m[0], m[1], m[2] weighted by v's x, y and z (the matrix
    // times v): vmulax.xyz, vmadday.xyz, vmaddz.xyz. The matrix is any 16-aligned object whose
    // first three quadwords are the rows, read where it is.
    template <class M> static u128 Rotate(const M& m, u128 v)
    {
        const u128* r = (const u128*)&m;
        u128 out;
        __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
                : "=j"(out) : "j"(r[0]), "j"(r[1]), "j"(r[2]), "0"(v));
        return out;
    }

    // Rotate with the rows as values r0, r1, r2 (the caller loads them once, as a matrix
    // product does, or builds them): vmulax.xyz, vmadday.xyz, vmaddz.xyz, the result not tied
    // to v. As with Transform4, it takes the register of the first of r0, r1, r2, v that dies
    // there: v's while the rows live on, row 0's at their last use (func_00116840's three
    // rows). Retail uses Rotate where the matrix is read where it is and the result takes v's
    // register; this one where the rows are values and the result may take row 0's.
    static u128 RotateRows(u128 r0, u128 r1, u128 r2, u128 v)
    {
        u128 out;
        __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
                : "=j"(out) : "j"(r0), "j"(r1), "j"(r2), "j"(v));
        return out;
    }

    // The point v through a 4x4 matrix whose fourth row is the translation: m[0], m[1], m[2]
    // weighted by v's x, y and z, plus m[3] weighted by w (1 for a point, 0 for a direction),
    // in xyz: vmulax.xyz, vmadday.xyz, vmaddaz.xyz, vmaddx.xyz. w goes in as a float, made a
    // vector by Scalar inside: retail gives w's register after v's and stores it after the
    // sequence. The result may take a row's or v's register, the first of m[0], m[1], m[2],
    // m[3], v that dies there.
    template <class M> static u128 Transform(const M& m, u128 v, f32 w)
    {
        const u128* r = (const u128*)&m;
        u128 s = Scalar(w);
        u128 out;
        __asm__("vmulax.xyz ACC, %1, %5x\n\tvmadday.xyz ACC, %2, %5y\n\tvmaddaz.xyz ACC, %3, %5z\n\t"
                "vmaddx.xyz %0, %4, %6x"
                : "=j"(out) : "j"(r[0]), "j"(r[1]), "j"(r[2]), "j"(r[3]), "j"(v), "j"(s));
        return out;
    }

    // The vector v through a 4x4 matrix whose rows are m0, m1, m2, m3: the rows weighted by
    // v's x, y, z and w: vmulax.xyzw, vmadday.xyzw, vmaddaz.xyzw, vmaddw.xyzw. The rows are
    // values the caller loads once: a product of matrices stores each row of the result
    // between the sequences, which would make rows read in place be read again. The result
    // may take a row's or v's register, the first of m0, m1, m2, m3, v that dies there.
    static u128 Transform4(u128 m0, u128 m1, u128 m2, u128 m3, u128 v)
    {
        u128 out;
        __asm__("vmulax.xyzw ACC, %1, %5x\n\tvmadday.xyzw ACC, %2, %5y\n\tvmaddaz.xyzw ACC, %3, %5z\n\t"
                "vmaddw.xyzw %0, %4, %5w"
                : "=j"(out) : "j"(m0), "j"(m1), "j"(m2), "j"(m3), "j"(v));
        return out;
    }

    // The product of a's transpose and b, for 3x3 matrices (any 16-aligned objects whose first
    // three quadwords are the rows, read where they are), into out: row c of the product is b's
    // rows weighted by column c of a, b[0] * a[0].c + b[1] * a[1].c + b[2] * a[2].c, with
    // vmulac.xyzw ACC, vmaddac.xyzw ACC and vmaddc.xyzw. One sequence per row (retail's
    // registers: x and z new, y in b[0]'s, which dies there; the scheduler orders them z, x,
    // y). The rows are read into values first, b's then a's, so a store of out between the
    // sequences does not make them be read again (func_00128FD0's a is not an argument).
    template <class M> static void MulTransposed(M& out, const M& a, const M& b)
    {
        const u128* p = (const u128*)&a;
        const u128* q = (const u128*)&b;
        u128 b0 = q[0], b1 = q[1], b2 = q[2];
        u128 a0 = p[0], a1 = p[1], a2 = p[2];
        u128* r = (u128*)&out;
        __asm__("vmulax.xyzw ACC, %1, %4x\n\tvmaddax.xyzw ACC, %2, %5x\n\tvmaddx.xyzw %0, %3, %6x"
                : "=j"(r[0]) : "j"(b0), "j"(b1), "j"(b2), "j"(a0), "j"(a1), "j"(a2));
        __asm__("vmulay.xyzw ACC, %1, %4y\n\tvmadday.xyzw ACC, %2, %5y\n\tvmaddy.xyzw %0, %3, %6y"
                : "=j"(r[1]) : "j"(b0), "j"(b1), "j"(b2), "j"(a0), "j"(a1), "j"(a2));
        __asm__("vmulaz.xyzw ACC, %1, %4z\n\tvmaddaz.xyzw ACC, %2, %5z\n\tvmaddz.xyzw %0, %3, %6z"
                : "=j"(r[2]) : "j"(b0), "j"(b1), "j"(b2), "j"(a0), "j"(a1), "j"(a2));
    }

    // v through the transpose of a 3x3 matrix whose rows are m[0], m[1], m[2]: the dot
    // products of v with each row, into x, y and z (w is whatever the register held):
    // vmul.xyzw of each row by v, (1, 1, 1, 1) into a scratch (vmaxw.xyzw r, vf0, vf0w), then
    // vadday.x/vmaddz.x, vaddax.y/vmaddz.y, vaddax.z/vmaddy.z to sum each product's terms.
    // For a rotation it is the inverse of Rotate. The result and the four scratch registers are
    // written while the inputs are still read ("=&j"); listed result, 1.0, then the products
    // of rows 0, 1, 2, they take retail's registers (result first, the 1.0 last).
    template <class M> static u128 RotateTransposed(const M& m, u128 v)
    {
        const u128* r = (const u128*)&m;
        u128 out, p0, p1, p2, one;
        __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, vf0, vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\t"
                "vadday.x ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\t"
                "vaddax.z ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
                : "=&j"(out), "=&j"(one), "=&j"(p0), "=&j"(p1), "=&j"(p2)
                : "j"(r[0]), "j"(r[1]), "j"(r[2]), "j"(v));
        return out;
    }

    // a * s.x + b * t.x (a linear blend when s and t are 1 - u and u, a spring's force):
    // vmulax.xyzw ACC, then vmaddx.xyzw. The weights are Scalars. The inputs are listed s, a,
    // b, t: where s and a both die there, retail's result takes s's register.
    static u128 MulXSum(u128 a, u128 s, u128 b, u128 t)
    {
        u128 r;
        __asm__("vmulax.xyzw ACC, %2, %1x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(s), "j"(a), "j"(b), "j"(t));
        return r;
    }
};

#endif
