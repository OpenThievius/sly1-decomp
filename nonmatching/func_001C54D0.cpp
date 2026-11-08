// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 776/756, checked 2026-11-07
// NEAR: the whole function is written (the ground push, the two ramps, the rotated tangent and MulAddX2); it compiles 20 bytes over retail's and the registers differ throughout (retail keeps the push in f21 on both paths). It also needs MulAddX2 to give the result a's register (retail: the end's v30, here the tangent's); see func_001BBEB8.
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
    f32 push = 0.0f;
    if (self->f6DC != 0 && self->f6CC != 0.0f) {
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
        f32 cur = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d0), Vu0::Q(self->m110.r[2])));
        push = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d1), Vu0::Q(c->v80))) / w;
        ApproachValueWithRamp(cur, 0.0f, g_gameClock.dt, &A, &out1);
        ApproachValueWithRamp(cur, -self->f6CC, g_gameClock.dt, &B, &out2);
        if (push < out2) {
            push = out2;
        }
        push = push + ClampToMagnitude(out1 - push, g_gameClock.dt * (B.f[0] - B.f[1]) / B.f[2]);
    }
    Vec02 rot;
    u128 tangent;
    Vec02 k;
    Vu0::Q(rot) = Vu0::Rotate(self->m660, Vu0::Q(self->v640));
    tangent = Vu0::Sub(Vu0::Q(rot), Vu0::MulX(Vu0::Q(c->v80), Vu0::Dot(Vu0::Q(rot), Vu0::Q(c->v80))));
    Vu0::Q(c->end[e].v30) = Vu0::MulAddX2(Vu0::Q(c->end[e].v30), Vu0::Q(self->m110.r[2]), Vu0::Scalar(-push), tangent, Vu0::ScalarAt(self->f63C));
}
