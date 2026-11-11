// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 738/756 (97.6%), checked 2026-11-11
// NEAR: same size, frame and code as retail up to the tail; 10 lines differ, the order of v640's and row 1's loads and the tail's two weights (2026-11-10, w15). The frame (208 bytes: the ground push's weight at 32, the tail's weights at 64, out1 and out2 at 80 and 84) needs the vectors d0 and d1 declared at the top (the ground push reuses d0, d1 is the 16 bytes before its weight) and the ramp copies declared at function scope after the ground push, live through the tail (assign_temp slots are freed only at their block's end): the zero-push path jumps over them with a goto. The ground push reads end[e].v10 into a named u128 first and stores it at the address recomputed in place (retail's move a1, a0), the separation through Vu0::StoreX (a0), and both ramp inputs convert with ToFloatMoved, which leaves the dots below the profile loads in sched2 (priority 18 against 19). The rotation reads m660's rows as Vec values through a pointer to them, ahead of v640 (RotateRowsTied): Rotate's by-value v is always loaded before its rows (integrate.c's process_reg_param copies a memory argument at the call), so sched1 took v first on the LUID tie; read before it, row 0 wins the first cycle, and rows read as Vec values no longer wait for the weight-slot stores, which gives retail's rows vf5, vf3, vf4 and v vf2. Still differs: the f63C weight's qmtc2 (one insn with its memory operand, the block's last use of self, so weight 0) is ready at the start and wins its cycle over the -push weight's qmtc2 on its dependents (three, an anti dependence on the end->v30 store among them, against two); the lalloc2 emulator gives retail's weights only with the -push qmtc2 first and the f63C one after the dot and before the end->v30 load; reading m110.r[2] as a plain u128 after the weights' calls puts the -push qmtc2 first but then self dies at m110's load, which wins the cycle, and the f63C weight takes vf4 and s1 (docs/toolchain/stack-slots.md, "Ramp copies live through a tail: a goto over function-scope locals").
// W23 (2026-11-11, tools/sched1.py and the g11 lalloc2.py emulator on the tail block, insns 865 = Scalar(-push)'s qmtc2, 901 = ScalarAt(f63C)'s, 824 = end->v30's load): the replay matches the trace (every block). Retail's registers (f63C weight vf5 and a1, -push vf6 and a0) come out of local-alloc and reload exactly when 865 issues before 901 in sched1 (emulated order ...672,865,698,721,755,901,778,824...: f63C's quantity is then born late enough to outrank -push's and take vf5, and reload hands a0 to 865 first). At cycle 4 both are ready with priority 4 and weight 0 (865 kills the neg's result, 901 kills self); 901 wins on dependents, 3 (941, its slot store 911, and an anti dependence from end->v30's store 961) against 2. Every form that changes the tie breaks something retail shows: Vec::ScalarAtValue/ScalarAtCall/Scalar(self->f63C) (re-tried, same code or lwc1+mfc1), naming the f63C weight before the statement (its slot store then precedes -push's in the shared slot), m110.r[2] as a plain read (self dies at it). No plain form found; tools/globalalloc.py --local cannot chain a multi-block function, so the check was by lalloc2.py.
// W24 (2026-11-11, haifa-sched.c's rank_for_schedule read against the tail's table): no rank field can flip 865 and 901. Both are asms, so every link into them is LINK_COST_FREE (cost 1) and both are always class 3 against the last insn; 901 depends on nothing in the block, so it sits in the ready list from cycle 0 and 865 can only come first by outranking it (priority, weight, dependents, LUID, in that order) or by 901 gaining a predecessor. The anti dependence 961 -> 901 cannot go: self and c are both incoming arguments (base ADDRESS of VOIDmode, -fargument-noalias off, -fstrict-aliasing off), and a COMPONENT_REF read is never RTX_UNCHANGING_P. 865 can gain no third dependent without another reader of the weight, a later write of the neg's pseudo or a memory operand, each visible in retail's code. Injected into tools/sched1.py's replay and run through lalloc2.py: an edge 865 -> 901 (any kind) gives retail's VU registers (order 659,663,667,856,665,865,672,655,698,721,755,901,778,824,801,842,941,875,961,911); an edge 875 -> 901 (the f63C read held behind the -push slot store, as an address of unknown base would make it) does not (380 vf4, 369 vf4). Compiled (12): ScalarAtValue/ScalarAtCall(self->f63C) and MulAddX2WeightFirst are the near miss's code; Scalar(self->f63C) and a named f32 local (through Scalar, ScalarAt or ScalarAtValue) give retail's -push weight (mfc1 a0, vf6) but load f63C with lwc1 and mfc1 a1 into vf4; a plain "r" u32 operand splits the load into its own pseudo, so the qmtc2 holds no memory and ties 2 against 2, and 865 wins on LUID (-push a0 and vf6), but local-alloc gives the loaded pseudo v0 and the weight vf4, where retail's lw a1 is a reload; naming both weights before the statement, a helper ordered (a, s, t, b, c), and the u128 Q store form all let self die at the f63C read (lw s1, vf4).
#include "common.h"
#include "switched_collider.h"
#include "game_clock.h"
#include "fpu.h"
#include "vu0.h"
#include "globals.h"

extern f32 D_00274AD0[2];
// Three words copied whole from .data to a place only 4-aligned: the first two as one
// unaligned doubleword.
struct __attribute__((packed)) UnalignedPair { u64 v; };
struct ThreeWords { UnalignedPair a; s32 b; };
union RampCopy {
    ThreeWords w;
    f32 f[3];
};

f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, void* p, f32* out);
f32 ClampToMagnitude(f32 a, f32 b);

void func_001C54D0(TurningCollider* self, Contact03* c, s32 e)
{
    Vec02 d0;
    Vec02 d1;
    f32 push;
    f32 w;
    f32 cur;
    if (self->f6DC == 0 || self->f6CC == 0.0f) {
        push = 0.0f;
        goto apply;
    }
    w = Vu0::ToFloat(Vu0::Dot(Vu0::Q(c->v80), Vu0::Q(self->m110.r[2]))) * D_00274AD0[e];
    if (c->f90 < -2.0f) {
        f32 f90 = c->f90;
        u128 v = Vu0::Q(c->end[e].v10);
        f32 t = (f90 + 1.0f) / w;
        f32 ground = ((Vec02*)self->mesh.verts)[self->f6D0].z + 10.0f;
        f32 m = ground >? t;
        Vu0::Q(c->end[e].v10) = Vu0::MulAddX(v, Vu0::Q(self->m110.r[2]), Vu0::Scalar(-m));
        Vu0::Q(d0) = Vu0::Sub(Vu0::Q(c->end[0].v10), Vu0::Q(c->end[1].v10));
        Vu0::StoreX(c->f90, Vu0::Dot(Vu0::Q(d0), Vu0::Q(c->v80)));
    }
    RampCopy A;
    RampCopy B;
    f32 out1;
    f32 out2;
    Vu0::Q(d0) = Vu0::Sub(Vu0::Q(*(Vec02*)self->f6D4), Vu0::Q(c->end[e].v10));
    Vu0::Q(d1) = Vu0::Sub(Vu0::Q(c->end[0].v30), Vu0::Q(c->end[1].v30));
    cur = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d0), Vu0::Q(self->m110.r[2])));
    push = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d1), Vu0::Q(c->v80))) / w;
    A.w = *(ThreeWords*)self->f710;
    B.w = *(ThreeWords*)self->f704;
    A.f[0] = A.f[0] * self->f700;
    B.f[0] = B.f[0] * self->f700;
    ApproachValueWithRamp(cur, 0.0f, g_gameClock.dt, &A, &out1);
    ApproachValueWithRamp(cur, -self->f6CC, g_gameClock.dt, &B, &out2);
    if (push < out2) {
        push = out2;
    }
    push = push + ClampToMagnitude(out1 - push, g_gameClock.dt * (B.f[0] - B.f[1]) / B.f[2]);
apply:
    ContactEnd03* end = &c->end[e];
    const Vu0::Vec* m = (const Vu0::Vec*)&self->m660;
    Vu0::Vec rot = Vu0::RotateRowsTied(m[0], m[1], m[2], Vu0::Vec::Of(self->v640));
    Vu0::Vec n = Vu0::Vec::Of(c->v80);
    Vu0::Vec tangent = Vu0::Sub(rot, Vu0::MulX(n, Vu0::Dot(rot, n)));
    *(Vu0::Vec*)&end->v30 = Vu0::MulAddX2(Vu0::Vec::Of(end->v30), Vu0::Vec::Of(self->m110.r[2]), Vu0::Vec::Scalar(-push), tangent, Vu0::Vec::ScalarAt(self->f63C));
}
