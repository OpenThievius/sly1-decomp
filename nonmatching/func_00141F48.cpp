// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 544/548, checked 2026-11-07
// NEAR: the same body as func_00141D88 with the roots cut to [0, 1] (min.s/max.s through >? and <?); the same vmove copy blocks it, and here the cut roots are reloaded from the stack where retail keeps them in registers.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "collider.h"
#include "shapes.h"
s32 CollectColliderSpans(Collider* self, void* a1, void* a2, s32 a3, s32 a4);
s32 MergeOverlappingSpans(s32 count, ColliderSpan* spans);
s32 CollectTreeNodeSpans(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 CollectBoundsSpans(void* a, void* b, void* c, f32 x, s32 d, s32 e);
s32 TestTreeSegmentHit(void* a, void* b, void* c, void* d, s32 e, s32 f, f32 x);
s32 TestBoundsSegmentHit(void* a, void* b, void* c, void* d, s32 e, f32 fa, f32 fb);
#include "fpu.h"
#include "globals.h"

// The spans where the segment a-b, cut to its ends, is inside the sphere of the given radius around p (the roots
// of a quadratic in the position along the segment): the points, their directions from p and
// the times, into out.
s32 func_00141F48(Vec02* p, Vec02* a, Vec02* b, f32 radius, s32 count, ColliderSpan* out)
{
    if (count <= 0) {
        return 0;
    }
    Vec02 ab;
    Vec02 pa;
    f32 roots[2];
    Vu0::Q(ab) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    Vu0::Q(pa) = Vu0::Sub(Vu0::Q(*a), Vu0::Q(*p));
    f32 c = Vu0::ToFloat(Vu0::Dot(Vu0::Q(pa), Vu0::Q(pa))) - radius * radius;
    f32 hb = Vu0::ToFloat(Vu0::Dot(Vu0::Q(ab), Vu0::Q(pa)));
    f32 ha = Vu0::ToFloat(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
    f32 twoB = hb + hb;
    f32 disc = twoB * twoB - ha * (c * 4.0f);
    if (disc < 0.0001f) {
        return 0;
    }
    disc = Fpu::Sqrt(disc);
    f32 twoA = ha + ha;
    f32 r0 = (-twoB - disc) / twoA;
    f32 r1 = (-twoB + disc) / twoA;
    roots[0] = r0;
    roots[1] = r1;
    if (r0 < 0.0f && r1 < 0.0f) {
        return 0;
    }
    if (1.0f < r0 && 1.0f < r1) {
        return 0;
    }
    roots[0] = 0.0f >? roots[0];
    roots[1] = 1.0f <? roots[1];
    for (s32 j = 0; j < 2; j++) {
        f32 t = roots[j];
        out->time[j] = t;
        Vu0::Q(out->q[j]) = Vu0::MulXSum(Vu0::Q(*b), Vu0::Scalar(t), Vu0::Q(*a), Vu0::Scalar(1.0f - t));
        u128 d = Vu0::Sub(Vu0::Q(out->q[j]), Vu0::Q(*p));
        Vu0::Q(out->q[j + 2]) = d;
        Vu0::Q(out->q[j + 2]) = Vu0::NormalizeOr(d, Vu0::Q(g_unitXVector));
    }
    out->f48 = 1;
    return 1;
}
