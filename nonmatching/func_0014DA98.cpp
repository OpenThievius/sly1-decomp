// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 164/168, checked 2026-11-07
// NEAR: right instructions; retail does qmfc2 in each branch of the if/else and one shared mtc1 (the GPR holding the float's bits is merged at the join); ours puts one qmfc2 after the join (u128 r) or an mtc1 in each branch (f32 r). The anchor (self->b) is the first argument of func_001BA430.
#include "common.h"
#include "placed_object.h"
#include "path_curve.h"
#include "shapes.h"
#include "vu0.h"

struct NearestTimeQuery {
    PathCurve* curve;
    Vec02* a;
    Vec02* b;
    s32 pad;
};
typedef void (*CurveSamplePointFn)(PathCurve* self, Vec02* out, s32 flag);
void ConstrainVectorByAnchor(void* self, void* a, void* b, s32 c);

f32 MeasureSplinePathDistance(NearestTimeQuery* self)
{
    Vec02 p;
    Vec02 d;
    u128 r;
    if (self->curve->vt->m01)
        ((CurveSamplePointFn)self->curve->vt->m01)(self->curve, &p, 0);
    if (self->b == 0) {
        u128 e = Vu0::Sub(Vu0::Q(p), Vu0::Q(*self->a));
        r = Vu0::Dot(e, e);
    } else {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(p), Vu0::Q(*self->a));
        ConstrainVectorByAnchor(self->b, &d, &d, 0);
        r = Vu0::Dot(Vu0::Q(d), Vu0::Q(d));
    }
    return Vu0::ToFloat(r);
}
