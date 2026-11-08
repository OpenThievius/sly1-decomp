// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 403/444 (90.8%), checked 2026-11-08
// Night-moved (2026-11-08): c, hb and ha read with ToFloatMoved put the head in retail instruction order (sub.s before the second qmfc2, sqc2 after the mul.s); left: only the VU0 registers (retail a=vf4, dots vf3, ones vf5; ours a=vf3, ones vf4, dots vf5). Reordering the three dots or the two subs did not change them.
// NEAR: Vu0::Copy gives retail's vmove (the copy for the length and the first store, the division by the original; NormalizeOfCopy below is NormalizeOr with the length of the copy), and the loop is retail's. Still differs: the head's scheduling only (retail puts sub.s before the qmfc2 of the second dot and the sqc2 of the stack vector after the mul.s; reordering the three dots changes nothing).
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

static inline u128 NormalizeOfCopy(u128 v, u128 vc, u128 fallback)
{
    u128 len = Vu0::Length(vc);
    if (Vu0::ToFloat(len) < 0.0001f) {
        return fallback;
    }
    return Vu0::DivX(v, len);
}

// The spans where the segment a-b is inside the sphere of the given radius around p (the roots
// of a quadratic in the position along the segment): the points, their directions from p and
// the times, into out.
s32 func_00141D88(Vec02* p, Vec02* a, Vec02* b, f32 radius, s32 count, ColliderSpan* out)
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
    roots[0] = (-twoB - disc) / twoA;
    roots[1] = (-twoB + disc) / twoA;
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
