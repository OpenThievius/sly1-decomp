// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 738/756 (97.6%), checked 2026-11-10
// NEAR: same size, frame and code as retail up to the tail; 10 lines differ, the order of v640's and row 1's loads and the tail's two weights (2026-11-10, w15). The frame (208 bytes: the ground push's weight at 32, the tail's weights at 64, out1 and out2 at 80 and 84) needs the vectors d0 and d1 declared at the top (the ground push reuses d0, d1 is the 16 bytes before its weight) and the ramp copies declared at function scope after the ground push, live through the tail (assign_temp slots are freed only at their block's end): the zero-push path jumps over them with a goto. The ground push reads end[e].v10 into a named u128 first and stores it at the address recomputed in place (retail's move a1, a0), the separation through Vu0::StoreX (a0), and both ramp inputs convert with ToFloatMoved, which leaves the dots below the profile loads in sched2 (priority 18 against 19). The rotation reads m660's rows as Vec values through a pointer to them, ahead of v640 (RotateRowsTied): Rotate's by-value v is always loaded before its rows (integrate.c's process_reg_param copies a memory argument at the call), so sched1 took v first on the LUID tie; read before it, row 0 wins the first cycle, and rows read as Vec values no longer wait for the weight-slot stores, which gives retail's rows vf5, vf3, vf4 and v vf2. Still differs: the f63C weight's qmtc2 (one insn with its memory operand, the block's last use of self, so weight 0) is ready at the start and wins its cycle over the -push weight's qmtc2 on its dependents (three, an anti dependence on the end->v30 store among them, against two); the lalloc2 emulator gives retail's weights only with the -push qmtc2 first and the f63C one after the dot and before the end->v30 load; reading m110.r[2] as a plain u128 after the weights' calls puts the -push qmtc2 first but then self dies at m110's load, which wins the cycle, and the f63C weight takes vf4 and s1 (docs/toolchain/stack-slots.md, "Ramp copies live through a tail: a goto over function-scope locals").
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
