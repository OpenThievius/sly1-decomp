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
//   Scalar, whose slot is the copy g++ makes of a cast to s128 bound by reference (not a local
//   of the caller's): a scalar's memory, which loads of structure members do not wait for.
// - None is volatile: retail schedules loads, stores and other code across them.
// - A result may take an input's register ("=j"). The order of the inputs matters: the
//   allocator gives the result the register of the first input that dies there, so each
//   helper lists its inputs in the order retail's registers show (MulX the scale first), and
//   Rotate's result is tied to the vector it rotates ("0"). A register a sequence only
//   writes (Dot's 1.0) is a second output.
// - A float read from memory goes in with FromFloatAt: retail loads it with lw straight into
//   the GPR qmtc2 takes, which an f32 operand does not give (the compiler loads it into an FPR
//   and moves it with mfc1); a float computed in an FPR goes in with FromFloat. The word is the
//   operand itself, which reload loads for the qmtc2: into the register of an address that dies
//   there (lw s0,0(s0)), or a reload register (docs/TOOLCHAIN.md, "Reloads and stores").
// - A value retail handles in GPRs (a vector moved there with qmfc2 or lq, floats with mfc1, the
//   MMI pextlw, pextuw, pcpyld, pcpyud, prot3w, then sq or qmtc2) goes in and out as "r": the
//   compiler makes the moves and the stores, and the helper holds only the MMI instructions
//   (ToFloatY, ToFloatZ, Splat, FromFloats, Transpose). A float out of a GPR is "=r", so its
//   mtc1 is a reload in whatever GPR is free there, as retail's is.
// - Length and NormalizeOr are C over the helpers, not sequences of their own: NormalizeOr's
//   test is compiled code, and its fallback is an argument because retail loads it before the
//   test (lq, then qmtc2 on the fallback's path).
#ifndef VU0_H
#define VU0_H

#include "common.h"

// A 128-bit value: what a VU0 register holds.
typedef unsigned int u128 __attribute__((mode(TI)));
// The signed 128-bit value: Scalar's slot is a copy of a u128 cast to it.
typedef int s128 __attribute__((mode(TI)));

struct Vu0 {
    // A 16-aligned, 16-byte local of a helper's own: it lives on the stack, and a store to it
    // through Q has no alias flag (Scalar's slot is a cast's copy instead).
    struct __attribute__((aligned(16))) Slot {
        f32 v[4];
    };

    // A 16-aligned, 16-byte object read or written as one 128-bit value.
    template <class T> static u128& Q(T& v) { return *(u128*)&v; }
    template <class T> static const u128& Q(const T& v) { return *(const u128*)&v; }
    // v = x, stored where v is. Q(v) = x stores through the address Q returns, held in a
    // register; when the local is also passed by address after a call, CSE keeps that address
    // in a callee-saved register, where retail forms it again (addiu a1, sp, n) for the call.
    // Set's store is addressed from the frame and leaves nothing to keep in func_001BC828, but
    // Set takes v by reference too: after inlining, the address can sit in a pseudo CSE reuses for
    // a later &v passed to a call (a saved register, 16 more bytes of frame). Writing
    // `*(u128*)&v = x` at the use addresses the frame directly and gives retail's fresh addiu
    // (func_00126DE8, func_0015BD48, func_0015AF50, func_00189D38).
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

    // A copy of a in another VU0 register: vmove.xyzw. A plain `u128 b = a;` is a copy only
    // across basic blocks; within one CSE folds it away, and retail's vmove there (a value
    // kept whole while a copy of it is used up) is this one.
    static u128 Copy(u128 a)
    {
        u128 r;
        __asm__("vmove.xyzw %0, %1" : "=j"(r) : "j"(a));
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
    // "rV": the memory reference stays the asm's operand until reload ('V' admits memory
    // before it), and reload, finding it offsettable, loads it into a GPR for "r"; a plain "r"
    // loads it into a pseudo of its own, which local allocation never gives the dying address's
    // register.
    static u128 FromFloatAt(const f32& f)
    {
        u128 r;
        __asm__("qmtc2 %1, %0" : "=j"(r) : "rV"(*(const u32*)&f));
        return r;
    }

    // A float as a vector of its own, stored to the stack though nothing reads it back.
    // Retail's weights show it: the two of a MulXSum (or three, with a MulAddX after it) share
    // one stack slot, as temporaries of calls that have ended do, the first stored first, each
    // store after the arithmetic that uses it. The same float twice (Scalar(dt) in two
    // expressions) is one qmtc2 and two stores. The slot is the copy g++ 2.95 makes of a cast
    // bound by reference: a cast of a variable is an lvalue to it (an extension), so Q((s128)r)
    // takes the address of the cast without making r addressable, and expand_expr copies r's
    // register into a fresh temporary of the cast's type (assign_temp of a scalar type), which
    // CSE then reads back from the register. That temporary is a scalar's memory
    // (MEM_SCALAR_P) at a fixed address, which a structure member's load through a pointer
    // never waits for (alias.c, fixed_scalar_and_varying_struct_p); a 16-byte local of the
    // helper's (an aggregate) or a store through a u128 pointer (no flag) holds such loads
    // behind it, which retail's schedules never do (docs/TOOLCHAIN.md, "The weight slot is a
    // cast's copy"). The address is taken here, not through Q: Q returns a reference, which
    // leaves the slot's address in a pseudo of its own that CSE then keeps as the canonical
    // register for that frame address, and a later local given the freed slot (a block's Vec02
    // passed by address) is read through that pseudo across the calls in between, one saved
    // register more than retail (func_0017BCD0; docs/TOOLCHAIN.md, "A weight slot's address
    // must not outlive the statement").
    static u128 Scalar(f32 f)
    {
        u128 r = FromFloat(f);
        return *(u128*)&(s128)r;
    }

    // Scalar of a float in memory: FromFloatAt, so the float is loaded with lw straight into
    // qmtc2's GPR, and stored to its slot as Scalar's is.
    static u128 ScalarAt(const f32& f)
    {
        u128 r = FromFloatAt(f);
        return Q((s128)r);
    }

    // ScalarAt with the float passed by value: the operand is the float itself ("rV"), and an
    // inline call passes a const by-value argument as the caller's own memory reference, its
    // flags included (integrate.c copies only a writable parameter to a register), so a
    // structure member's load stays MEM_IN_STRUCT_P and need not wait for the stores before it
    // (ScalarAt reads the word through a cast pointer: no flag). func_0016C528's twist rate
    // (self->f224->f94) is loaded before an earlier weight's store, as retail does.
    static u128 ScalarAtValue(const f32 f)
    {
        u128 r;
        __asm__("qmtc2 %1, %0" : "=j"(r) : "rV"(f));
        return Q((s128)r);
    }

    // FromFloatAt of a float passed by value: the caller loads it where it makes the call, the
    // load just after its address's lui, and the load becomes the asm's memory operand, which
    // reload loads with lw into the register of the address that dies there (lui v1; lw v1).
    // FromFloatAt's reference copies the address into a pseudo before the inline body's block
    // notes, which loop.c counts in the address's life: in a loop it moves the lui out
    // (80 x savings x life >= the loop's insns), global-alloc spills it, and reload rebuilds it
    // in a reload register of its own. By value the life is one insn and it stays
    // (func_0017E3C8; docs/TOOLCHAIN.md, "Loops").
    static u128 FromFloatAtCall(f32 f)
    {
        u128 r;
        __asm__("qmtc2 %1, %0" : "=j"(r) : "rV"(f));
        return r;
    }

    // Scalar of FromFloatAtCall: a float passed by value, loaded with lw, held in the
    // helper's 16-byte local as Scalar's is.
    static u128 ScalarAtCall(f32 f)
    {
        Slot t;
        Q(t) = FromFloatAtCall(f);
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

    // The x of a VU0 register as a float, qmfc2 and mtc1 in one sequence through a GPR of the
    // compiler's choosing: retail's mtc1 follows the qmfc2 at once even where the scheduler
    // has a store ready for the slot between them, which ToFloat's separate mtc1 lets it take
    // (func_00187A88: the difference's sqc2 after the squared distance's mtc1).
    static f32 ToFloatNow(u128 a)
    {
        f32 r;
        u32 t;
        __asm__("qmfc2 %1, %2\n\tmtc1 %1, %0" : "=f"(r), "=r"(t) : "j"(a));
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

    // The x of a VU0 register as a float through its bits: ToBits' qmfc2 into a GPR, then an
    // mtc1 of its own. The value stays in its VU0 register up to the qmfc2, as with ToFloat
    // (ToFloatMoved's "r" input makes the vector a GPR pseudo, which renumbers the VU0
    // registers around it), and the mtc1 is an asm, issued a cycle after the qmfc2 where the
    // compiler's own (ToFloat's reload of its "=r" float) has a latency of 2: what uses the
    // float issues a cycle sooner (func_001C5C10: the neg.s of a call's float argument comes
    // before the last argument move, which reorg then puts in the call's delay slot).
    static f32 ToFloatViaBits(u128 a)
    {
        u32 t = ToBits(a);
        f32 r;
        __asm__("mtc1 %1, %0" : "=f"(r) : "r"(t));
        return r;
    }

    // The x of a VU0 register stored to a word in memory (a float, or its bits): sw of the low word of the vector in
    // a GPR. The vector goes in as "r", so the qmfc2 that brings it there is the compiler's: a
    // reload, whose GPR is taken after every pseudo has its register (func_001DAA18's length
    // loop: a1 after the loop's v0, v1 and a0), where ToBits' result is a pseudo of its own that
    // the local allocator gives the first free one (v0). The store is the helper's: the low
    // word of a 128-bit GPR as a u32 is a truncation, which the compiler sign-extends first.
    template <class T> static void StoreX(T& dst, u128 a)
    {
        __asm__("sw %1, %0" : "=m"(dst) : "r"(a));
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

    // The transpose of a 3x3 matrix, its rows' w zero, built in GPRs as the 4x4 transpose with
    // a zero fourth row: the rows loaded with lq (the compiler's), then pextlw/pextuw of rows 0
    // and 1 and of row 2 with $zero, then pcpyld/pcpyud of those into the three columns. The
    // two steps are two sequences, as retail schedules other code between them (func_00188B48's
    // -1.0). The rows are made in a local of its own and the matrix is returned by value,
    // each row going to the result as soon as it is made (g++'s named return value, as
    // matrix.cpp's MultiplyMatrices): retail stores each row to the local, then to the result.
    static Rows Transpose(const Rows& m);

    // A float in all four fields, built in a GPR: pextlw t, t, t (the float twice in the low
    // doubleword), pextlw r, t, t (four times), where t is the GPR the float came in: the mfc1
    // that brings it there is the compiler's ("r"), which retail schedules apart, and the
    // first pextlw turns that copy in place (retail's ten sites all do; the copy dies there).
    // r may be t (func_0019E220) or another GPR (func_0019F620). The result is "=r": stored
    // with sq where it goes straight to a vector local, moved to VU0 with qmtc2 where it is
    // used there. It has no local of its own: retail stores it once, where the C put it.
    // Known imperfection: the first pextlw overwrites the input's register without declaring
    // it. Declaring it (a second output tied to the input) forbids the result from taking that
    // register, which func_0019E220 needs. It is safe because the GPR copy is one the compiler
    // makes for this asm alone (an f32 lives in an FPR), and dies here; a float that reaches a
    // GPR by other means must not be passed through Splat.
    static u128 Splat(f32 f)
    {
        u128 r;
        __asm__("pextlw %1, %1, %1\n\tpextlw %0, %1, %1" : "=r"(r) : "r"(f));
        return r;
    }

    // The vector (x, y, z) of three floats in FPRs, built in a GPR: mfc1 r, x; mfc1 t, y;
    // pextlw r, t, r (x and y interleaved); mfc1 t, z; pcpyld r, t, r (z after them). Its w
    // is z's sign extension. One sequence: retail never schedules anything inside it, and the
    // three floats die together (separate mfc1s are hoisted and change the FPRs the floats
    // take, func_00144AA0). The result is "=r": the compiler stores it with sq where it goes
    // straight to memory (func_00141690, func_00174E20) and moves it to VU0 with qmtc2 where
    // it is used there (func_00144AA0, func_001BFBF8). It is stored to a slot of its own though
    // nothing reads it back, as Scalar's: a cast's copy, so a load through a pointer of no known
    // base (func_0017ABE8's method table) need not wait for the sq.
    static u128 FromFloats(f32 x, f32 y, f32 z)
    {
        u128 r, w;
        __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
                : "=&r"(r), "=&r"(w) : "f"(x), "f"(y), "f"(z));
        return Q((s128)r);
    }

    // A weight passed whole in a GPR: the float's bits put in a 128-bit value with mfc1 (the
    // float as "f", the result "=r"), stored to a slot of its own as Scalar's is.
    // Retail passes the scale of ScaleMatrix (func_00188628) so: mfc1 v0, then the compiler's
    // por a2, zero, v0 and the sq to the slot (MultiplyScriptValues, DivideScriptValues,
    // func_00158480). No C form puts a float in a 128-bit GPR value: a union goes through
    // memory, and a store to its low word masks the rest.
    static u128 ScalarInGpr(f32 f)
    {
        u128 r;
        __asm__("mfc1 %0, %1" : "=r"(r) : "f"(f));
        return Q((s128)r);
    }

    // The same mfc1 with no slot: the value stays in a register of its own (func_00191AC8
    // holds it in a saved GPR across its loop and copies it to the stack per use).
    static u128 ScalarInGprReg(f32 f)
    {
        u128 r;
        __asm__("mfc1 %0, %1" : "=r"(r) : "f"(f));
        return r;
    }

    // a * s.x: vmulx.xyzw.
    static u128 MulX(u128 a, u128 s)
    {
        u128 r;
        __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s), "j"(a));
        return r;
    }

    // a + b * s.x: vadda.xyzw ACC, a, vf0; vmaddx.xyzw. The inputs are listed a, s, b: the
    // local allocator ties the result to the first input that dies there, and retail gives it
    // the weight's register where a lives on and b is loaded for the sum (func_00187260's three,
    // docs/TOOLCHAIN.md, "MulAddX lists its weight before b"). Every matched function builds
    // the same with either order.
    static u128 MulAddX(u128 a, u128 b, u128 s)
    {
        u128 r;
        __asm__("vadda.xyzw ACC, %1, vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a), "j"(s), "j"(b));
        return r;
    }

    // a + b * s.x + c * t.x: vadda.xyzw ACC, a, vf0 (a into ACC, as MulAddX); vmaddax.xyzw
    // ACC, b, s.x; vmaddx.xyzw. The weights are Scalars (or ScalarAts). The inputs in their own
    // order: the result takes the first that is local to the block and dies there, a's where a
    // is loaded for the sum (func_001BBEB8, func_0017E3C8), c's where a and b come from earlier
    // blocks (func_00198BD8). A tie to a ("+j") doubles a's references and swaps a's and b's
    // registers; where they still differ, look at the allocation around it (docs/TOOLCHAIN.md).
    static u128 MulAddX2(u128 a, u128 b, u128 s, u128 c, u128 t)
    {
        u128 r;
        __asm__("vadda.xyzw ACC, %1, vf0\n\tvmaddax.xyzw ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
                : "=j"(r) : "j"(a), "j"(b), "j"(s), "j"(c), "j"(t));
        return r;
    }

    // MulAddX2 with its parameters as the sum reads, each weight before its vector (a + s b +
    // t c), as MulAddX3's: an inline call emits its arguments in parameter order, so with the
    // vectors read as Vec::Of each weight's slot store comes before the next vector's load,
    // and the loads of a and b need not wait behind the slot stores before them. The asm's
    // operands keep MulAddX2's order (a, b, s, c, t). ApplyPoseSourcePosition's spring step,
    // pos + dt v + (dt dt / 2) c, loads pos before dt's slot store and v after it, as retail
    // (func_001218C0; docs/TOOLCHAIN.md, "A weight listed before its vector").
    static u128 MulAddX2WeightFirst(u128 a, u128 s, u128 b, u128 t, u128 c)
    {
        u128 r;
        __asm__("vadda.xyzw ACC, %1, vf0\n\tvmaddax.xyzw ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
                : "=j"(r) : "j"(a), "j"(b), "j"(s), "j"(c), "j"(t));
        return r;
    }

    // a + s.x * b + t.x * c + u.x * d: MulAddX2 with a third weighted vector (vadda.xyzw ACC, a,
    // vf0; two vmaddax.xyzw ACC; vmaddx.xyzw), as MulXSum3 and MulXSum4 extend MulXSum; one use in
    // retail so far, func_001DDE90. Each weight is listed before its vector, as the sum reads
    // (a + s b + t c + u d): an inline call emits its arguments in parameter order, so a weight's
    // slot store comes before the next vector's load, which retail's schedule shows
    // (docs/TOOLCHAIN.md, "A weight listed before its vector"). The asm's operands keep the order
    // a, b, s, c, t, d, u, which decides which input's register the result takes.
    static u128 MulAddX3(u128 a, u128 s, u128 b, u128 t, u128 c, u128 u, u128 d)
    {
        u128 r;
        __asm__("vadda.xyzw ACC, %1, vf0\n\tvmaddax.xyzw ACC, %2, %3x\n\tvmaddax.xyzw ACC, %4, %5x\n\t"
                "vmaddx.xyzw %0, %6, %7x"
                : "=j"(r) : "j"(a), "j"(b), "j"(s), "j"(c), "j"(t), "j"(d), "j"(u));
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

    // Dot of one vector with itself, the vector a single input: vmul.xyz r, v, v. Given as one
    // operand, v takes another register than Dot(v, v) gives it, and the 1.0 the other way
    // round: retail's vf3 for v and vf2 for 1.0 in func_001EF768.
    static u128 SelfDot(u128 v)
    {
        u128 r, one;
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, vf0, vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
                : "=j"(r), "=j"(one) : "j"(v));
        return r;
    }

    // The length of v's xyz through SelfDot: v a single input to the dot (func_001EF768).
    static u128 SelfLength(u128 v)
    {
        return Sqrt(SelfDot(v));
    }

    // v made unit length (DivX by its Length), or fallback when v is shorter than 0.0001. The
    // length's test reads it through ToFloatMoved: retail's mtc1 follows the qmfc2 at once, which
    // the compiler's own qmfc2 gives and ToFloat's does not (func_00189B18, func_00189C28).
    static u128 NormalizeOr(u128 v, u128 fallback)
    {
        u128 len = Length(v);
        if (ToFloatMoved(len) < 0.0001f) {
            return fallback;
        }
        return DivX(v, len);
    }

    // NormalizeOr with the length's qmfc2 the compiler's (ToFloatMoved): sched2 then puts the
    // fallback's lq before the mtc1 of the test, where retail has it (func_001C96D8).
    static u128 NormalizeOrMoved(u128 v, u128 fallback)
    {
        u128 len = Length(v);
        if (ToFloatMoved(len) < 0.0001f) {
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

    // Transform with the rows as values the caller loads where they are: retail reads a local
    // matrix's rows from the frame where Transform's reference keeps the matrix's address in a
    // register once a call has taken it (func_001F2840's inverse and its vertex loop).
    static u128 TransformRows(u128 r0, u128 r1, u128 r2, u128 r3, u128 v, f32 w)
    {
        u128 s = Scalar(w);
        u128 out;
        __asm__("vmulax.xyz ACC, %1, %5x\n\tvmadday.xyz ACC, %2, %5y\n\tvmaddaz.xyz ACC, %3, %5z\n\t"
                "vmaddx.xyz %0, %4, %6x"
                : "=j"(out) : "j"(r0), "j"(r1), "j"(r2), "j"(r3), "j"(v), "j"(s));
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
    // Rotate with the rows read as Vec members (m's rows through a Vec pointer): each row load
    // is a structure member's, MEM_IN_STRUCT_P, which a MEM_SCALAR_P weight slot at a fixed
    // address never conflicts with (ScalarCopy), while Rotate's u128 reads, with no flag, wait
    // for every store to the frame. The address is m's own (a pointer parameter's base passes
    // frame stores; an address pseudo of no known base waits for the other frame stores):
    // func_001C75B0 loads row 0 before the weight's store and rows 1 and 2 after v's.
    template <class M> static u128 RotateMembers(const M& m, u128 v);

    template <class M> static u128 RotateUntied(const M& m, u128 v)
    {
        const u128* r = (const u128*)&m;
        return RotateRows(r[0], r[1], r[2], v);
    }
    // A vector as a value of its own type: one u128 in a struct, passed and returned by value.
    // GCC keeps the struct in a 128-bit register, as it does a u128, and the code comes out the
    // same; but each inline call that takes or returns one copies it from pseudo to pseudo (movti),
    // copies CSE does not fold and only the register allocator removes. loop.c counts them, so a
    // loop over vectors in this form is as big to it as retail's were: big enough that it leaves
    // the loop's constants and its index multiplication where they are (docs/TOOLCHAIN.md,
    // "Loops"). In a condition a Vec temporary makes the front end compute the condition as a
    // value (the temporary's cleanup point) where retail branches on it: Distance keeps its Vecs
    // in an inline function of its own.
    struct Vec {
        u128 q;

        // A 16-aligned, 16-byte object in memory, as a value (lqc2).
        template <class T> static Vec Of(const T& v)
        {
            Vec r;
            r.q = *(const u128*)&v;
            return r;
        }

        static Vec Scalar(f32 f)
        {
            Vec r;
            r.q = Vu0::Scalar(f);
            return r;
        }

        static Vec ScalarInGpr(f32 f)
        {
            Vec r;
            r.q = Vu0::ScalarInGpr(f);
            return r;
        }

        static Vec ScalarAt(const f32& f)
        {
            Vec r;
            r.q = Vu0::ScalarAt(f);
            return r;
        }

        static Vec ScalarAtCall(f32 f)
        {
            Vec r;
            r.q = Vu0::ScalarAtCall(f);
            return r;
        }

        static Vec ScalarAtValue(const f32 f)
        {
            Vec r;
            r.q = Vu0::ScalarAtValue(f);
            return r;
        }

        static Vec Zero()
        {
            Vec r;
            r.q = Vu0::Zero();
            return r;
        }

        static Vec FromFloat(f32 f)
        {
            Vec r;
            r.q = Vu0::FromFloat(f);
            return r;
        }
    };

    static Vec Sub(Vec a, Vec b)
    {
        Vec r;
        r.q = Sub(a.q, b.q);
        return r;
    }

    static Vec Add(Vec a, Vec b)
    {
        Vec r;
        r.q = Add(a.q, b.q);
        return r;
    }

    static Vec DivX(Vec a, Vec s)
    {
        Vec r;
        r.q = DivX(a.q, s.q);
        return r;
    }

    static Vec MulX(Vec a, Vec s)
    {
        Vec r;
        r.q = MulX(a.q, s.q);
        return r;
    }

    static Vec Dot(Vec a, Vec b)
    {
        Vec r;
        r.q = Dot(a.q, b.q);
        return r;
    }

    static Vec Length(Vec a)
    {
        Vec r;
        r.q = Length(a.q);
        return r;
    }

    static Vec DotXY(Vec a, Vec b)
    {
        Vec r;
        r.q = DotXY(a.q, b.q);
        return r;
    }

    static Vec Sqrt(Vec a)
    {
        Vec r;
        r.q = Sqrt(a.q);
        return r;
    }


    static Vec Min(Vec a, Vec b)
    {
        Vec r;
        r.q = Min(a.q, b.q);
        return r;
    }

    static Vec Max(Vec a, Vec b)
    {
        Vec r;
        r.q = Max(a.q, b.q);
        return r;
    }

    static Vec Cross(Vec a, Vec b)
    {
        Vec r;
        r.q = Cross(a.q, b.q);
        return r;
    }


    static Vec MulAddX(Vec a, Vec b, Vec s)
    {
        Vec r;
        r.q = MulAddX(a.q, b.q, s.q);
        return r;
    }

    static Vec NormalizeOr(Vec v, Vec fallback)
    {
        Vec r;
        r.q = NormalizeOr(v.q, fallback.q);
        return r;
    }

    static Vec MulXSum(Vec a, Vec s, Vec b, Vec t)
    {
        Vec r;
        r.q = MulXSum(a.q, s.q, b.q, t.q);
        return r;
    }

    static Vec MulXSum3(Vec a, Vec s, Vec b, Vec t, Vec c, Vec u)
    {
        Vec r;
        r.q = MulXSum3(a.q, s.q, b.q, t.q, c.q, u.q);
        return r;
    }

    static Vec MulXSum4(Vec a, Vec s, Vec b, Vec t, Vec c, Vec u, Vec d, Vec v)
    {
        Vec r;
        r.q = MulXSum4(a.q, s.q, b.q, t.q, c.q, u.q, d.q, v.q);
        return r;
    }

    template <class M> static Vec Rotate(const M& m, Vec v)
    {
        Vec r;
        r.q = Rotate(m, v.q);
        return r;
    }

    static Vec MulAddX2(Vec a, Vec b, Vec s, Vec c, Vec t)
    {
        Vec r;
        r.q = MulAddX2(a.q, b.q, s.q, c.q, t.q);
        return r;
    }

    static Vec MulAddX2WeightFirst(Vec a, Vec s, Vec b, Vec t, Vec c)
    {
        Vec r;
        r.q = MulAddX2WeightFirst(a.q, s.q, b.q, t.q, c.q);
        return r;
    }

    static Vec MulAddX3(Vec a, Vec s, Vec b, Vec t, Vec c, Vec u, Vec d)
    {
        Vec r;
        r.q = MulAddX3(a.q, s.q, b.q, t.q, c.q, u.q, d.q);
        return r;
    }

    template <class M> static Vec RotateUntied(const M& m, Vec v)
    {
        Vec r;
        r.q = RotateUntied(m, v.q);
        return r;
    }


    template <class M> static Vec RotateTransposed(const M& m, Vec v)
    {
        Vec r;
        r.q = RotateTransposed(m, v.q);
        return r;
    }

    static f32 ToFloatMoved(Vec a)
    {
        return ToFloatMoved(a.q);
    }

    static f32 ToFloatY(Vec a)
    {
        return ToFloatY(a.q);
    }

    static f32 ToFloatZ(Vec a)
    {
        return ToFloatZ(a.q);
    }





    static f32 ToFloat(Vec a)
    {
        return ToFloat(a.q);
    }

    // The distance between two points in memory: the Length of their difference, as a float.
    template <class T> static f32 Distance(const T& a, const T& b)
    {
        return ToFloat(Length(Sub(Vec::Of(a), Vec::Of(b))));
    }

    // The interface of a VU0 microprogram: the game's microprograms read and write fixed
    // registers, which the compiler (it allocates $vf1..$vf15) cannot pick. One instruction
    // each, volatile with a memory clobber so that they keep their order with each other and
    // with the loads and stores around them. Used by func_0013A498 and func_00185150.

    // A quadword from memory into $vfN (N 16..31): lqc2.
    template <int N> static void LoadVf(const void* p)
    {
        __asm__ volatile("lqc2 $vf%1, %0" : : "m"(*(const u128*)p), "i"(N) : "memory");
    }

    // $vfN (N 16..31) to memory: sqc2.
    template <int N> static void StoreVf(void* p)
    {
        __asm__ volatile("sqc2 $vf%1, %0" : "=m"(*(u128*)p) : "i"(N) : "memory");
    }

    // A GPR's word (a vector or float in a GPR, as a caller passes it) into $vfN (N 16..31):
    // qmtc2.ni (the .ni form does not wait for the microprogram).
    template <int N> static void MoveToVf(u128 bits)
    {
        __asm__ volatile("qmtc2.ni %0, $vf%1" : : "r"(bits), "i"(N) : "memory");
    }

    // Start the microprogram at address N: vcallms.
    template <int N> static void CallMs()
    {
        __asm__ volatile("vcallms %0" : : "i"(N) : "memory");
    }

    // A GPR into the integer register $viN (N 1..15): ctc2.ni, or ctc2.i (the interlocked
    // form, which first waits for the microprogram) from MoveToViWait.
    template <int N> static void MoveToVi(u32 v)
    {
        __asm__ volatile("ctc2.ni %0, $vi%1" : : "r"(v), "i"(N) : "memory");
    }
    template <int N> static void MoveToViWait(u32 v)
    {
        __asm__ volatile("ctc2.i %0, $vi%1" : : "r"(v), "i"(N) : "memory");
    }

    // $viN (N 0..15) into a GPR: cfc2.ni, or cfc2.i (interlocked: it stalls until the
    // microprogram has ended) from ReadViWait. ReadViWait<0> reads zero: the game's wait.
    template <int N> static u32 ReadVi()
    {
        u32 r;
        __asm__ volatile("cfc2.ni %0, $vi%1" : "=r"(r) : "i"(N) : "memory");
        return r;
    }
    template <int N> static u32 ReadViWait()
    {
        u32 r;
        __asm__ volatile("cfc2.i %0, $vi%1" : "=r"(r) : "i"(N) : "memory");
        return r;
    }

    // The VU0 no-operation, a vnop (upper and lower nop) the game puts between a register
    // write and the use the microprogram will make of it.
    static void VuNop()
    {
        __asm__ volatile("vnop" : : : "memory");
    }

    // RotateRows with its result tied to v ("0") as Rotate's is: the rows are values the caller
    // loaded before it computed v, and the result takes v's register. Loaded first, the rows
    // come before a Scalar's slot store in the insn order, so sched1 does not have to keep them
    // behind it (they may alias it), and the store waits to the end of the block as retail's does
    // (func_00149760's case 2; docs/TOOLCHAIN.md, "Memory dependences in sched1").
    static u128 RotateRowsTied(u128 r0, u128 r1, u128 r2, u128 v)
    {
        u128 out;
        __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
                : "=j"(out) : "j"(r0), "j"(r1), "j"(r2), "0"(v));
        return out;
    }

    static Vec RotateRowsTied(Vec r0, Vec r1, Vec r2, Vec v)
    {
        Vec r;
        r.q = RotateRowsTied(r0.q, r1.q, r2.q, v.q);
        return r;
    }
};

// Vu0::RotateMembers, out of the class: its rows are read as Vu0::Vec, complete only here.
template <class M> inline u128 Vu0::RotateMembers(const M& m, u128 v)
{
    const Vec* r = (const Vec*)&m;
    u128 out;
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(out) : "j"(r[0].q), "j"(r[1].q), "j"(r[2].q), "0"(v));
    return out;
}

// Vu0::Transpose, out of the class: g++ 2.95 takes a named return value only in a definition
// at namespace scope (in the class body it is a parse error; on a member template cc1 never
// finishes). docs/TOOLCHAIN.md, "A matrix returned by value".
inline Vu0::Rows Vu0::Transpose(const Rows& m) return y
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
    y.r[0] = t.r[0];
    t.r[1] = c1;
    y.r[1] = t.r[1];
    t.r[2] = c2;
    y.r[2] = t.r[2];
}

#endif
