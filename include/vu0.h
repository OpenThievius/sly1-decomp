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
//   lqc2, one sqc2. A helper's result that is never named stays in its register. A local also
//   passed by address is written with Vu0::Set where retail forms its address afresh for the call.
// - A vector local (Vec02, Quad16) lives on the stack, so a result assigned to it is stored
//   there even when nothing reads it back: retail's stores to the stack that nothing loads. A
//   float made a vector (FromFloat) is always stored so in retail: it goes into a local.
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
    // A 16-aligned, 16-byte object read or written as one 128-bit value.
    template <class T> static u128& Q(T& v) { return *(u128*)&v; }
    template <class T> static const u128& Q(const T& v) { return *(const u128*)&v; }
    // v = x, stored where v is. Q(v) = x stores through the address Q returns, held in a
    // register; when the local is also passed by address after a call, CSE keeps that address
    // in a callee-saved register, where retail forms it again (addiu a1, sp, n) for the call.
    // Set's store is addressed from the frame and leaves nothing to keep (func_001BC828).
    template <class T> static void Set(T& v, u128 x) { *(u128*)&v = x; }

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

    // The cross product a x b, its w zero: vopmula.xyz ACC, a, b; vopmsub.xyz r, b, a;
    // vsub.w r, r, r.
    static u128 Cross(u128 a, u128 b)
    {
        u128 r;
        __asm__("vopmula.xyz ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1\n\tvsub.w %0, %0, %0"
                : "=j"(r) : "j"(a), "j"(b));
        return r;
    }

    // The smaller of a and b in each of x, y and z: vmini.xyz r, a, b. The result's w is
    // whatever its register held (retail gives the result a fresh register when a lives on).
    static u128 Min(u128 a, u128 b)
    {
        u128 r;
        __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
        return r;
    }

    // The larger of a and b in each of x, y and z: vmax.xyz r, a, b (its w as Min's).
    static u128 Max(u128 a, u128 b)
    {
        u128 r;
        __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
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

    // Rotate with its result untied: the same sequence, the result free to take any input's
    // register; retail has both forms. The result takes the register of the first input that
    // dies there, the matrix's rows before v: in a product of two rotations (placed_object.cpp's
    // MulRotation) the last row's product takes the register of the first matrix's first row,
    // and func_00125750 gives a rotated position a fresh register, where Rotate's tie to v
    // would keep v's.
    template <class M> static u128 RotateUntied(const M& m, u128 v)
    {
        const u128* r = (const u128*)&m;
        u128 out;
        __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
                : "=j"(out) : "j"(r[0]), "j"(r[1]), "j"(r[2]), "j"(v));
        return out;
    }
};

#endif
