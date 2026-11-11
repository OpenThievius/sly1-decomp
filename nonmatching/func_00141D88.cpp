// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 428/444 (96.4%), checked 2026-11-10
// Tried w8 (2026-11-09): the loop matches as retail with the compiler's vmove (Vec d stored, then NormalizeOr(d, ...): docs/TOOLCHAIN.md, "A compiler copy's latency in sched2"); the head's dots are VU0 pseudos in retail (a dot read through ToFloatMoved is a TI_REGS pseudo and reload picks its VU0 register: the old vf3/vf4/vf5 mix). All three as ToFloat give retail's VU0 registers but not its order; all three as ToFloatViaBits give retail's order once dot3 is placed before dot2's qmfc2 in sched1 (the local-alloc emulation then gives retail's vf5 for dot3's 1.0), which no priority allows (dot2's conversion 15 against dot3's 13 at -dS).
// Tried w15 (2026-11-10): the head is a sched1 priority wall (docs/toolchain/sched1.md, "The quadratic's head"): dot3's path is 13 at most, below dot2's conversion (14-15), c's subtraction (16) and the 4.0 load (15), and twoB's add is raised to 14 by adjust_priority (set once, live at the block's end), so dot3 never issues before or directly after dot2's qmfc2, which retail's vf5 for dot3's 1.0 needs. Lengthening dot3's path (probe: `+ 0.0f`) gives every VU0 register of retail. Ruled out: the 64 conversion mixes, Vec-valued dots (448 forms), a copied twoB, an inline root solver.
// NEAR: the loop is retail's. Still differs: the head only: dot2's qmfc2 issues before the 4.0 and the sub.s (retail after), and dot3 (ToFloatMoved here, the closest of 216 conversion mixes) takes vf4/vf3 where retail has vf3/vf5.
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
    roots[0] = (-twoB - disc) / twoA;
    roots[1] = (-twoB + disc) / twoA;
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
