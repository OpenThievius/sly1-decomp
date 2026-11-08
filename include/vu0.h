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
// - A float weight retail stores in a slot of its own that later weights reuse goes through
//   Scalar, a helper whose 16-byte local takes the store (not a local of the caller's).
// - None is volatile: retail schedules loads, stores and other code across them.
// - A result may take an input's register ("=j"). The order of the inputs matters: the
//   allocator gives the result the register of the first input that dies there, so each
//   helper lists its inputs in the order retail's registers show (MulX the scale first), and
//   Rotate's result is tied to the vector it rotates ("0"). A register a sequence only
//   writes (Dot's 1.0) is a second output.
// - A float read from memory goes in with FromFloatAt: retail loads it with lw straight into
//   the GPR qmtc2 takes, which an f32 operand does not give (the compiler loads it into an FPR
//   and moves it with mfc1); a float computed in an FPR goes in with FromFloat.
// - Length and NormalizeOr are C over the helpers, not sequences of their own: NormalizeOr's
//   test is compiled code, and its fallback is an argument because retail loads it before the
//   test (lq, then qmtc2 on the fallback's path).
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

    // (1, 1, 1, 1): vmaxw.xyzw r, vf0, vf0w (vf0's w is 1.0, the larger in every field).
    static u128 Ones()
    {
        u128 r;
        __asm__("vmaxw.xyzw %0, vf0, vf0w" : "=j"(r));
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

    // A float in memory into the x of a VU0 register: qmtc2 of its bits, which the compiler
    // loads with lw (FromFloat's operand would be loaded into an FPR and moved with mfc1).
    static u128 FromFloatAt(const f32& f)
    {
        u128 r;
        __asm__("qmtc2 %1, %0" : "=j"(r) : "r"(*(const u32*)&f));
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

    // Scalar of a float in memory: FromFloatAt into the helper's 16-byte local, so the float is
    // loaded with lw straight into qmtc2's GPR, and stored to the stack as Scalar's is.
    static u128 ScalarAt(const f32& f)
    {
        Slot t;
        Q(t) = FromFloatAt(f);
        return Q(t);
    }

    // The x of a VU0 register as a float: qmfc2 (the compiler moves it on to an FPR).
    static f32 ToFloat(u128 a)
    {
        f32 r;
        __asm__("qmfc2 %0, %1" : "=r"(r) : "j"(a));
        return r;
    }

    // The x of a VU0 register as a float, the move to a GPR the compiler's: the value goes in
    // as "r" and the sequence is only the mtc1, so the qmfc2 is the compiler's own copy, which
    // it schedules and may put in a branch's delay slot (an asm statement never goes there), and
    // which it makes in each arm of an if whose arms meet at the conversion (func_0014EB10).
    // The two allocate differently: func_00187B60 matches with ToFloat and takes other VU0
    // registers with this one, which matches every other user of ToFloat.
    static f32 ToFloatMoved(u128 a)
    {
        f32 r;
        __asm__("mtc1 %1, %0" : "=f"(r) : "r"(a));
        return r;
    }

    // The x of a VU0 register as the bits of a float: qmfc2 into a GPR, which retail stores
    // with sw straight to memory (ToFloat's f32 goes on to an FPR: mtc1, then swc1).
    static u32 ToBits(u128 a)
    {
        u32 r;
        __asm__("qmfc2 %0, %1" : "=r"(r) : "j"(a));
        return r;
    }

    // The y of a vector in a GPR as a float: prot3w r, a (the words turned to y, z, x, w).
    // The vector goes in as "r", so the qmfc2 (or lq) that brings it to a GPR is the
    // compiler's, made once and shared with the reads of the other lanes (ToFloatMoved reads
    // x). The float comes out of the GPR ("=r"): the mtc1 to an FPR is the compiler's, a
    // reload whose GPR is one the values live there leave free (func_001B9940, whose a0 an
    // f32 or u128 pseudo of the caller's would take as v0).
    static f32 ToFloatY(u128 a)
    {
        f32 r;
        __asm__("prot3w %0, %1" : "=r"(r) : "r"(a));
        return r;
    }

    // The z of a vector in a GPR as a float: pextuw r, $zero, a (z, 0, w, 0), as ToFloatY.
    static f32 ToFloatZ(u128 a)
    {
        f32 r;
        __asm__("pextuw %0, $0, %1" : "=r"(r) : "r"(a));
        return r;
    }

    // Three rows of a 3x3 matrix, as a value (Transpose returns one).
    struct __attribute__((aligned(16))) Rows {
        u128 r[3];
    };

    // The transpose of a 3x3 matrix (any 16-aligned object whose first three quadwords are
    // the rows), its rows' w zero, built in GPRs as the 4x4 transpose with a zero fourth row:
    // the rows loaded with lq (the compiler's), then pextlw/pextuw of rows 0 and 1 and of row
    // 2 with $zero, then pcpyld/pcpyud of those into the three columns. The two steps are two
    // sequences, as retail schedules other code between them (func_00188B48's -1.0); the
    // result is returned in a local of its own, stored to the stack as retail's is.
    template <class M> static Rows Transpose(const M& m)
    {
        const u128* p = (const u128*)&m;
        u128 r0 = p[0], r1 = p[1], r2 = p[2];
        u128 lo01, hi01, lo2, hi2;
        __asm__("pextlw %0, %5, %4\n\tpextuw %1, %5, %4\n\tpextlw %2, $0, %6\n\tpextuw %3, $0, %6"
                : "=&r"(lo01), "=&r"(hi01), "=&r"(lo2), "=&r"(hi2) : "r"(r0), "r"(r1), "r"(r2));
        u128 c0, c1, c2;
        __asm__("pcpyld %0, %4, %3\n\tpcpyud %1, %3, %4\n\tpcpyld %2, %6, %5"
                : "=&r"(c0), "=&r"(c1), "=&r"(c2) : "r"(lo01), "r"(lo2), "r"(hi01), "r"(hi2));
        Rows t;
        t.r[0] = c0;
        t.r[1] = c1;
        t.r[2] = c2;
        return t;
    }

    // The vector (x, y, z) of three floats in FPRs, built in a GPR: mfc1 r, x; mfc1 t, y;
    // pextlw r, t, r (x and y interleaved); mfc1 t, z; pcpyld r, t, r (z after them). Its w
    // is z's sign extension. One sequence: retail never schedules anything inside it, and the
    // three floats die together (separate mfc1s are hoisted and change the FPRs the floats
    // take, func_00144AA0). The result is "=r": the compiler stores it with sq where it goes
    // straight to memory (func_00141690, func_00174E20) and moves it to VU0 with qmtc2 where
    // it is used there (func_00144AA0, func_001BFBF8). It is held in a 16-byte local of the
    // helper's, stored to the stack though nothing reads it back, as Scalar's.
    static u128 FromFloats(f32 x, f32 y, f32 z)
    {
        Slot t;
        u128 r, w;
        __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
                : "=&r"(r), "=&r"(w) : "f"(x), "f"(y), "f"(z));
        Q(t) = r;
        return Q(t);
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

    // a + b * s.x + c * t.x: vadda.xyzw ACC, a, vf0 (a into ACC, as MulAddX); vmaddax.xyzw
    // ACC, b, s.x; vmaddx.xyzw. The weights are Scalars (or ScalarAts). Listed c first: where
    // all die there, retail's result takes c's register (func_00198BD8).
    static u128 MulAddX2(u128 a, u128 b, u128 s, u128 c, u128 t)
    {
        u128 r;
        __asm__("vadda.xyzw ACC, %2, vf0\n\tvmaddax.xyzw ACC, %3, %4x\n\tvmaddx.xyzw %0, %1, %5x"
                : "=j"(r) : "j"(c), "j"(a), "j"(b), "j"(s), "j"(t));
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

    // The two-term dot product of a and b (their x and y), in x: vmul.xy r, a, b; vaddy.x r,
    // r, r.y. With a and b the same vector it is the squared length of its xy, which retail
    // mostly takes the Sqrt of (a length on the ground plane). The result may take an input's
    // register.
    static u128 DotXY(u128 a, u128 b)
    {
        u128 r;
        __asm__("vmul.xy %0, %1, %2\n\tvaddy.x %0, %0, %0y" : "=j"(r) : "j"(a), "j"(b));
        return r;
    }

    // The square root of a's x, in x: vsqrt Q, a.x; vwaitq; vaddq.x (the disassembler prints
    // vsqrt as a .word). The result may take a's register.
    static u128 Sqrt(u128 a)
    {
        u128 r;
        __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, vf0, Q" : "=j"(r) : "j"(a));
        return r;
    }

    // a / s.x: vdiv Q, vf0w, s.x (1 / s.x into Q); vwaitq; vmulq.xyzw. The scale comes first,
    // as in MulX: the result takes its register when it dies there, a's otherwise.
    static u128 DivX(u128 a, u128 s)
    {
        u128 r;
        __asm__("vdiv Q, vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, Q" : "=j"(r) : "j"(s), "j"(a));
        return r;
    }

    // The length of v's xyz, in x: Dot of v with itself, then Sqrt (the sequences stay two:
    // retail schedules other code between them).
    static u128 Length(u128 v)
    {
        return Sqrt(Dot(v, v));
    }

    // v made unit length (DivX by its Length), or fallback when v is shorter than 0.0001.
    static u128 NormalizeOr(u128 v, u128 fallback)
    {
        u128 len = Length(v);
        if (ToFloat(len) < 0.0001f) {
            return fallback;
        }
        return DivX(v, len);
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

    // Which of four planes the sphere at v of radius s.x lies wholly behind: the planes' unit
    // normals are the columns of a 3x4 matrix whose rows are m[0], m[1], m[2] (any 16-aligned
    // object, read where it is), so m[0] * v.x + m[1] * v.y + m[2] * v.z is v's distance from
    // each plane, less ones * s.x (ones is Ones()). Only ACC is written: vmulax.xyzw,
    // vmadday.xyzw, vmaddaz.xyzw, vmsubax.xyzw, then four vnop for the flags to settle and
    // cfc2 of the MAC flags (vi17) into a GPR. Their sign bits are 0x80 (x) to 0x10 (w): a
    // result of 0xF0 is all four negative, the sphere inside every plane.
    static u32 PlaneSigns(u128 r0, u128 r1, u128 r2, u128 v, u128 ones, u128 s)
    {
        u32 flags;
        __asm__("vmulax.xyzw ACC, %1, %4x\n\tvmadday.xyzw ACC, %2, %4y\n\tvmaddaz.xyzw ACC, %3, %4z\n\t"
                "vmsubax.xyzw ACC, %5, %6x\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2 %0, $vi17"
                : "=r"(flags) : "j"(r0), "j"(r1), "j"(r2), "j"(v), "j"(ones), "j"(s));
        return flags;
    }

    // a * s.x + b * t.x + c * u.x, three vectors weighted (a direction from the three axes of a
    // heading, blend weights): vmulax.xyzw ACC, vmaddax.xyzw ACC, vmaddx.xyzw. The weights are
    // Scalars. As in MulXSum the inputs are listed s, a, then the rest: retail's result takes
    // s's register where s and a die there.
    static u128 MulXSum3(u128 a, u128 s, u128 b, u128 t, u128 c, u128 u)
    {
        u128 r;
        __asm__("vmulax.xyzw ACC, %2, %1x\n\tvmaddax.xyzw ACC, %3, %4x\n\tvmaddx.xyzw %0, %5, %6x"
                : "=j"(r) : "j"(s), "j"(a), "j"(b), "j"(t), "j"(c), "j"(u));
        return r;
    }

    // a * s.x + b * t.x + c * u.x + d * v.x, four vectors weighted (the gap between the
    // points at given fractions of two segments, a Hermite segment's point): vmulax.xyzw ACC,
    // two vmaddax.xyzw ACC, vmaddx.xyzw. The weights are Scalars, listed first as in MulXSum.
    static u128 MulXSum4(u128 a, u128 s, u128 b, u128 t, u128 c, u128 u, u128 d, u128 v)
    {
        u128 r;
        __asm__("vmulax.xyzw ACC, %2, %1x\n\tvmaddax.xyzw ACC, %3, %4x\n\tvmaddax.xyzw ACC, %5, %6x\n\t"
                "vmaddx.xyzw %0, %7, %8x"
                : "=j"(r) : "j"(s), "j"(a), "j"(b), "j"(t), "j"(c), "j"(u), "j"(d), "j"(v));
        return r;
    }

    // Rotate with its result untied, the matrix read where it is: RotateRows on its rows, the
    // result free to take any input's
    // register; retail has both forms. The result takes the register of the first input that
    // dies there, the matrix's rows before v: in a product of two rotations (placed_object.cpp's
    // MulRotation) the last row's product takes the register of the first matrix's first row,
    // and func_00125750 gives a rotated position a fresh register, where Rotate's tie to v
    // would keep v's.
    template <class M> static u128 RotateUntied(const M& m, u128 v)
    {
        const u128* r = (const u128*)&m;
        return RotateRows(r[0], r[1], r[2], v);
    }
};

#endif
