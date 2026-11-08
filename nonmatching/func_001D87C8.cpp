// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 963/1032 (93.3%), checked 2026-11-08
// NEAR (2026-11-07, worker night-large2): the gather loop, the spans, the curve calls, the
// ramp and the closing search are retail's; 25 lines differ. The side vector's VU0 block is
// scheduled otherwise: retail loads the position (lqc2 vf3) right after the Length's dot and
// moves the far weight (qmtc2 v1, vf5, the dot's 1.0 register) in after the square root, then
// stores both weight slots after both sums; ours loads the position after the division (vf1)
// and stores the near weight between the sums. The same with u128 helpers, the position or the
// direction as values first. And the three spilled addresses (&lo, &hi, &out at 0x134, 0x138,
// 0x13C in retail) come out in another order (hi, out, lo) with this do-while; the for loop
// (the closing loop as `for (j = 0; j < k; j++)`) gives retail's slots but a plain blez with the
// field load in its slot where retail's blezl carries the store of f844.
// In the context of its file, src/main/file_1D62E0.cpp.
#include "common.h"
#include "vu0.h"
#include "switched_collider.h"
#include "path_curve_object.h"
#include "path_curve.h"
#include "value_range.h"
#include "globals.h"

struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

extern f32 g_gameClock[];
f32 ApproachValueWithRamp(void* p, s32 zero, f32 a, f32 b, f32 c);
s32 IsPathFollowerAhead(PathFollower* self, PathFollower* other);
f32 FindNearestValueOutsideSpans(s32 count, ValueRange* spans, f32 x);
s32 GatherObjectsById(void* world, s32 flags, s32 kind, void* arg, s32 max, PathFollower** out);
f32 WrapModulo(f32 x, f32 y);
s32 IsInsideRange(ValueRange* range, f32 x);
void FindPathCurveNearestTime(PathCurve* self, Vec02* lo, Vec02* hi, Vec02* out, s32 a4, f32* time,
                              f32* a6, f32 start);
extern f32 D_002754B0[4];
extern f32 D_002754C0[2];
extern f32 D_002754D0[3];
extern float D_002751D0;

void AdvancePathFollowerAlongPath(PathFollower* self, s32* nearby)
{
    typedef Vu0::Vec Vec;
    PathFollower* list[16];
    ValueRange spans[16];
    Vec02 pos;
    Vec02 tangent;
    Vec02 dir;
    Vec02 lo;
    Vec02 hi;
    Vec02 out;
    s32 n = GatherObjectsById(self->world, 5, 0x19, 0, 0x10, list);
    s32 count = 0;
    s32 k = 0;
    for (s32 i = 0; i < n; i++) {
        PathFollower* o = list[i];
        if (o == self) {
            continue;
        }
        if (o->f830 != self->f830) {
            continue;
        }
        if (IsPathFollowerAhead(self, o)) {
            continue;
        }
        count++;
        f32 d = WrapModulo(o->f83C - self->f83C, o->f834);
        f32 r = ((ValueRange*)D_002754C0)->Limit(((QuadraticCurve*)D_002754B0)->Eval(d));
        if (r <= 0.0f) {
            continue;
        }
        ValueRange* s = &spans[k++];
        s->lo = o->f840 - r;
        s->hi = o->f840 + r;
    }
    *nearby = count;
    ValueRange* s = &spans[k++];
    s->lo = -1e6f;
    s->hi = -self->f61C;
    s = &spans[k++];
    s->lo = self->f61C;
    s->hi = 1e6f;
    PathCurve* c = self->f830->curve;
    c->vt->m06(c, self->f83C + D_002751D0);
    c = self->f830->curve;
    if (c->vt->m02) {
        ((void (*)(PathCurve*, f32, Vec02*, Vec02*))c->vt->m02)(c, self->f83C + D_002751D0, &pos, &tangent);
    }
    Vu0::Vec side = Vu0::Cross(Vec::Of(g_unitZVector), Vec::Of(tangent));
    Vu0::Q(dir) = Vu0::DivX(side, Vu0::Length(side)).q;
    Vu0::Q(lo) = Vu0::MulAddX(Vec::Of(pos), Vec::Of(dir), Vec::ScalarAt(D_002754C8.lo)).q;
    Vu0::Q(hi) = Vu0::MulAddX(Vec::Of(pos), Vec::Of(dir), Vec::ScalarAt(D_002754C8.hi)).q;
    FindPathCurveNearestTime(self->f848->curve, &lo, &hi, &out, 0, &self->f84C, 0, self->f84C);
    f32 ahead = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vec::Of(out), Vec::Of(pos)), Vec::Of(dir)).q);
    f32 want = ApproachValueWithRamp(D_002754D0, 0, self->f844, ahead, g_gameClock[2]);
    f32 best = FindNearestValueOutsideSpans(k, spans, want);
    if (!IsInsideRange(&D_002754C8, best)) {
        best = want;
    } else {
        if (k > 0) {
            f32 cur = self->f840;
            ValueRange* s = spans;
            s32 j = k;
            do {
                if (cur < best && cur < s->lo && s->lo < best) {
                    best = s->lo;
                } else if (best < cur && s->hi < cur && best < s->lo) {
                    best = s->hi;
                }
                s++;
                j--;
            } while (j != 0);
        }
    }
    self->f844 = best;
}
