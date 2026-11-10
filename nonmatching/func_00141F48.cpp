// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 524/548 (95.6%), checked 2026-11-10
// Tried w12 (2026-11-10): func_00141D88's forms (ToFloatViaBits for the first two dots, the loop's direction a Vec stored then NormalizeOr'd) give the loop exactly. The head is func_00141D88's: retail's VU0 registers (dot3 vf3, scratch vf5) need dot3 in sched1 directly after dot2's conversion, and retail's sched2 order needs the first dot's mtc1 an asm (ToFloatViaBits) and the second's qmfc2 and mtc1 one asm (ToFloatNow, priority 14 below the 4.0's 15). With those, sched1 issues twoB's add before dot3 at t=8: both priority 13, and INSN_REG_WEIGHT is 0 for the add (hb dies there) against 1 for the dot (two sets, one unused). Doubling hb in place (`hb += hb;`, no death) puts dot3 first and gives every VU0 register of retail, but then hb and twoB are one pseudo and retail's add.s $f5,$f1,$f1 cannot come out (17 lines). Also ruled out: SelfDot for the squared dots, named dots in any order, the 4ac product's other groupings, an inline SolveQuadratic.
// NEAR: the loop is retail's. Still differs: the head only, as func_00141D88's: dot2's qmfc2 before the 4.0 and the sub.s (retail after), and dot3 vf4/vf3 where retail has vf3/vf5.
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
    f32 c = Vu0::ToFloatViaBits(Vu0::Dot(Vu0::Q(pa), Vu0::Q(pa))) - radius * radius;
    f32 hb = Vu0::ToFloatViaBits(Vu0::Dot(Vu0::Q(ab), Vu0::Q(pa)));
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
        Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(out->q[j]), Vu0::Vec::Of(*p));
        *(Vu0::Vec*)&out->q[j + 2] = d;
        *(Vu0::Vec*)&out->q[j + 2] = Vu0::NormalizeOr(d, Vu0::Vec::Of(g_unitXVector));
    }
    out->f48 = 1;
    return 1;
}
