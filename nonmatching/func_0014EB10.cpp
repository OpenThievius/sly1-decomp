// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 341/352 (96.9%), checked 2026-11-07
// NEAR: right instructions and registers; differs only in the delay slot of the branch to the join. Retail fills the delay slot of the `b` with qmfc2.ni (the first insn of the join, which it also keeps on the fall-through path) and jumps past it; ours has a nop there and the qmfc2 only at the join, because Vu0::ToFloat is an inline-asm qmfc2 and the delay-slot filler never moves an asm statement. Retail's qmfc2 is a native move.
#include "common.h"
#include "placed_object.h"
#include "path_curve.h"
#include "shapes.h"
#include "vu0.h"

void FindSplinePathNearestTime(SplinePathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12);
void ConstrainVectorByAnchor(void* self, void* a, void* b, s32 c);
extern const f32 D_00249FC8;

void FindSplinePathNearestPoint(SplinePathCurve* self, Vec02* pos, void* anchor, s32 a3, s32 a4, f32* a5, f32* a6)
{
    Vec02 d;
    s32 best = -1;
    f32 bestDist = D_00249FC8;
    s32 i = self->count;
    while (--i >= 0) {
        f32 dist;
        if (anchor != 0) {
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(((Vec02*)self->points)[i]));
            ConstrainVectorByAnchor(anchor, &d, &d, 0);
            dist = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
        } else {
            u128 e = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(((Vec02*)self->points)[i]));
            dist = Vu0::ToFloat(Vu0::Dot(e, e));
        }
        if (dist < bestDist) {
            bestDist = dist;
            best = i;
        }
    }
    FindSplinePathNearestTime(self, (s32)pos, (s32)anchor, a3, a4, a5, a6, self->times[best]);
}
