// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 493/548 (90.0%), checked 2026-11-08
// NEAR: night-size4: func_00141D88's levers (ToFloatMoved for the three dots, Vu0::Copy with NormalizeOfCopy) give retail's vmove and size, and MaxF(0.0f, roots[0]) / MinF(roots[1], 1.0f) retail's clamps (the constants' registers, both stores after). Still differs: the head's VU0 registers as in func_00141D88 (retail a=vf4, dots vf3, ones vf5), and in the loop the copy's sqc2 to out->q[j + 2] comes before the length's dot where retail has it after.
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
// The cut roots: the constant in the first register of max.s and min.s, the result in its register.
static inline f32 MaxF(f32 a, f32 b) { return a >? b; }
static inline f32 MinF(f32 a, f32 b) { return b <? a; }
static inline u128 NormalizeOfCopy(u128 v, u128 vc, u128 fallback)
{
    u128 len = Vu0::Length(vc);
    if (Vu0::ToFloat(len) < 0.0001f) {
        return fallback;
    }
    return Vu0::DivX(v, len);
}

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
    f32 c = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(pa), Vu0::Q(pa))) - radius * radius;
    f32 hb = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ab), Vu0::Q(pa)));
    f32 ha = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
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
    roots[0] = MaxF(0.0f, roots[0]);
    roots[1] = MinF(roots[1], 1.0f);
    for (s32 j = 0; j < 2; j++) {
        f32 t = roots[j];
        out->time[j] = t;
        Vu0::Q(out->q[j]) = Vu0::MulXSum(Vu0::Q(*b), Vu0::Scalar(t), Vu0::Q(*a), Vu0::Scalar(1.0f - t));
        u128 d = Vu0::Sub(Vu0::Q(out->q[j]), Vu0::Q(*p));
        u128 dc = Vu0::Copy(d);
        Vu0::Q(out->q[j + 2]) = dc;
        Vu0::Q(out->q[j + 2]) = NormalizeOfCopy(d, dc, Vu0::Q(g_unitXVector));
    }
    out->f48 = 1;
    return 1;
}
