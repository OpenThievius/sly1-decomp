// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 764/756, checked 2026-11-08
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call 1 (source line 54); 169 differing lines before, 167 now.
// NEAR: the whole function is written (the ground push, the two ramps, the rotated tangent and MulAddX2, whose result now takes a's register as retail's does); 8 bytes over retail. Now retail's: push = 0 as the first arm of the test, the rotation kept in a register. Still differs: retail's frame is 16 bytes larger (out1 and out2 at 80 and 84, a 16-byte slot at 64 that the tail's weights take, and in the inner block one more 16-byte slot before the weight at 32), the copy of &c->end[e] (move a1, a0) retail keeps for the store, and the VU0 registers of the tail (retail loads m660's rows into vf5, vf3, vf4).
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
    f32 push;
    if (self->f6DC == 0 || self->f6CC == 0.0f) {
        push = 0.0f;
    } else {
        f32 f90 = c->f90;
        f32 w = Vu0::ToFloat(Vu0::Dot(Vu0::Q(c->v80), Vu0::Q(self->m110.r[2]))) * D_00274AD0[e];
        if (f90 < -2.0f) {
            ContactEnd03* end = &c->end[e];
            f32 t = (f90 + 1.0f) / w;
            f32 ground = ((Vec02*)self->mesh.verts)[self->f6D0].z + 10.0f;
            f32 m = ground >? t;
            Vec02 d;
            Vu0::Q(end->v10) = Vu0::MulAddX(Vu0::Q(end->v10), Vu0::Q(self->m110.r[2]), Vu0::Scalar(-m));
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(c->end[0].v10), Vu0::Q(c->end[1].v10));
            *(u32*)&c->f90 = Vu0::ToBits(Vu0::Dot(Vu0::Q(d), Vu0::Q(c->v80)));
        }
        Vec02 d0;
        Vec02 d1;
        RampCopy A;
        RampCopy B;
        f32 out1;
        f32 out2;
        Vu0::Q(d0) = Vu0::Sub(Vu0::Q(*(Vec02*)self->f6D4), Vu0::Q(c->end[e].v10));
        Vu0::Q(d1) = Vu0::Sub(Vu0::Q(c->end[0].v30), Vu0::Q(c->end[1].v30));
        A.w = *(ThreeWords*)self->f710;
        B.w = *(ThreeWords*)self->f704;
        A.f[0] = A.f[0] * self->f700;
        B.f[0] = B.f[0] * self->f700;
        f32 cur = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d0), Vu0::Q(self->m110.r[2])));
        push = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d1), Vu0::Q(c->v80))) / w;
        ApproachValueWithRamp(cur, 0.0f, g_gameClock.dt, &A, &out1);
        ApproachValueWithRamp(cur, -self->f6CC, g_gameClock.dt, &B, &out2);
        if (push < out2) {
            push = out2;
        }
        push = push + ClampToMagnitude(out1 - push, g_gameClock.dt * (B.f[0] - B.f[1]) / B.f[2]);
    }
    u128 rot = Vu0::Rotate(self->m660, Vu0::Q(self->v640));
    u128 tangent = Vu0::Sub(rot, Vu0::MulX(Vu0::Q(c->v80), Vu0::Dot(rot, Vu0::Q(c->v80))));
    Vu0::Q(c->end[e].v30) = Vu0::MulAddX2(Vu0::Q(c->end[e].v30), Vu0::Q(self->m110.r[2]), Vu0::Scalar(-push), tangent, Vu0::ScalarAt(self->f63C));
}
