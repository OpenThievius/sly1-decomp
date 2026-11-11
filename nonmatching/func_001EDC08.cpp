// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 420/424 (99.1%), checked 2026-11-10
// Night-moved (2026-11-08): ToFloatMoved on the length test gives the size (424).
// NEAR: w12 (2026-11-10): from 49 differing lines to 2. The operands as Vu0::Vec values named in pairs, each weight before its point (w0, p0, w1, p1, ...; MulXSum4 over Vecs), give retail's VU0 registers and, through block 8's local-alloc (the 1.0 now outranks 1 - v), retail's f3 for the second clamp and its bc1t; the fallback's address named before the test (`const Vec02* fallback`) gives retail's lui/addiu in the test block with the lq in the arm. Still differs: the epilogue restores s6 then s5, retail s5 then s6 (unique in retail). sched2 ranks the two lq equal; retail's s6 waits because the sw before it is an asm (StoreX, no function unit: it issues with lq s5 in one cycle, and s6, anti-dependent on it, a cycle later), which ToFloatNow or ToFloat with StoreX confirm. StoreX with ToFloatMoved's test gives the length two "r" operands against two "j": regclass ties and picks TI_REGS (a GPR, qmtc2 back for DivX), the wall of func_00186230 and player_path (docs/TOOLCHAIN.md); ToFloatNow + StoreX: the test's GPR is local-alloc's v0 where retail's is reload's v1 (the address then takes v1); ToFloat + StoreX: reload's mtc1 latency 2 lets a slot store in. Vec copies of the length are folded by cse2 before regclass. w15 (2026-11-10): re-scored 420/424. gcse's copy propagation, not cse2, removes the length's inline copy (cse2 then folds the test's use): regclass's counts say retail had a copy of the length at the join read only by StoreX (the length 2 "j" to 1 "r", the copy the compiler's qmfc2 into v0), but CSE folds every block-local copy (`u128 l2 = len;` tested). ToFloatNow + StoreX: only v0/v1 and the addiu differ (its unused GPR takes v0 after the fallback's %hi dies at the lo_sum, which sched1 issues before the test) (docs/toolchain/alias-classes.md). w19 (2026-11-10): re-scored 420/424. Diagnosed: the store as an asm sw of an asm qmfc2's GPR is EXACT (`u32 b = Vu0::ToBits(len);` then an asm `sw` of b; also with ToFloat's "=r" float in place of ToBits): len then has three "j" operands (Sqrt, DivX, the qmfc2) to the test's one "r", so it stays VU_REGS and the test's qmfc2 stays reload's v1, and the sw (no function unit) issues beside `lq s5`. As a form this needs StoreX to take a word already in a GPR (an overload for u32 or f32, or a value-type template parameter): a compiler-emittable sw kept as an asm, a new helper by AGENTS.md's rule, not landed for want of a second retail site (the s5-before-s6 epilogue is unique). ToFloat + StoreX (the vector) gives the epilogue too and differs by one swap in the test block (reload's mtc1, latency 2 on memory+flop, lets the slot store of vf6 in before it); ToFloatViaBits + StoreX gives the test's GPR to local-alloc (v0) because sched1 issues the fallback's lo_sum before the qmfc2 (tools/sched1.py --trace 389), so the %hi dies first. (docs/toolchain/alias-classes.md, "An asm store issues beside an epilogue restore").
#include "common.h"
#include "globals.h"
#include "vu0.h"

void FindSegmentClosestParams(const Vec02* p0, const Vec02* p1, const Vec02* q0, const Vec02* q1, f32* st, f32* dist, Vec02* dir);

// v clamped to [0, 1].
static inline f32 ClampUnit(f32 v)
{
    f32 c;
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    if (v < lo) {
        c = lo;
    } else if (hi < v) {
        c = hi;
    } else {
        c = v;
    }
    return c;
}

// The closest points of the segments p0-p1 and q0-q1, their fractions clamped to the segments:
// the direction from the first to the second into dir (the x axis when they meet) and the
// distance into dist.
void FindClosestPointsOnSegments(const Vec02* p0, const Vec02* p1, const Vec02* q0, const Vec02* q1, f32* st, f32* dist, Vec02* dir)
{
    FindSegmentClosestParams(p0, p1, q0, q1, st, dist, dir);
    st[0] = ClampUnit(st[0]);
    st[1] = ClampUnit(st[1]);
    Vu0::Vec w0 = Vu0::Vec::Scalar(st[0] - 1.0f);
    Vu0::Vec a0 = Vu0::Vec::Of(*p0);
    Vu0::Vec w1 = Vu0::Vec::Scalar(-st[0]);
    Vu0::Vec a1 = Vu0::Vec::Of(*p1);
    Vu0::Vec w2 = Vu0::Vec::Scalar(1.0f - st[1]);
    Vu0::Vec a2 = Vu0::Vec::Of(*q0);
    Vu0::Vec w3 = Vu0::Vec::Scalar(st[1]);
    Vu0::Vec a3 = Vu0::Vec::Of(*q1);
    u128 d = Vu0::MulXSum4(a0, w0, a1, w1, a2, w2, a3, w3).q;
    Vu0::Q(*dir) = d;
    const Vec02* fallback = &g_unitXVector;
    u128 len = Vu0::Length(d);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        *dir = *fallback;
    } else {
        Vu0::Q(*dir) = Vu0::DivX(d, len);
    }
    *(u32*)dist = Vu0::ToBits(len);
}
