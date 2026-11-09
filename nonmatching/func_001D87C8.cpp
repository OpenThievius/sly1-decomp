// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1015/1032 (98.4%), checked 2026-11-08
// NEAR (2026-11-08, worker w4-1D87C8): everything but five lines is retail's. The three spilled
// addresses (&lo, &hi, &out at 0x134, 0x138, 0x13C) now come in retail's order: they are PRE's
// reaching registers, numbered in bucket order of gcse's expression table, (13259 + C) mod T for
// a frame address at C; the Vec form had T = 123, which puts &out (C = 272) in bucket 1, first,
// and the uniform u128 form (each Vec value an extra movti copy at gcse) has T = 103, which
// keeps 240, 256, 272 in order (docs/TOOLCHAIN.md, GCSE). The closing loop stays the do-while
// under `if (k > 0)`: a for loop gives blez with the field load in its slot where retail has
// blezl with the store of f844.
// Still differs: the weights' slot stores (sqc2 vf4/vf5 to 0x120) against the curve's loads.
// Retail loads self->f848 between the two MulAddX sums, stores the lo weight after the three
// result stores, then loads ->curve (lw a0, 52(v0)) and f84C, and stores the hi weight last,
// in the call's delay slot. Ours stores the lo weight first and the hi weight before both
// loads. sched1 (-dS -fsched-verbose-6): the curve load, through a pointer loaded from memory
// (no known base), depends on every Scalar slot store before it (a `u128*` store, neither
// MEM_IN_STRUCT_P nor MEM_SCALAR_P), so both slot stores take its priority (17-18) and go
// first, and the f848 load (priority 17, weight +1) loses its cycle to them. Retail's order
// needs sched1 to put the lo store before the curve load and the hi store after it, which it
// can only do if the curve load does not depend on the hi store: the slots would have to be
// MEM_SCALAR_P (fixed_scalar_and_varying_struct_p), or the hi store emitted after the call's
// arguments. With the weights' stores removed (FromFloatAt alone) the f848 load lands exactly in
// retail's cycle, which confirms it. Ruled out: the curve read into a local at every place in
// the block (tools/permute.py over dir/curve/lo/hi: the current order is best), the f848 pointer
// read early, dir as a Vec value (it is a frame local: 0xE0), the weight as a temporary bound to
// a const u128& (in an inline or a template helper, a by-value parameter whose address is taken,
// a pointer to a local): every scalar temporary is purged back into a register, and the only
// slot that stays in memory is an aggregate's, which conflicts with the curve load.
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
    u128 side = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(tangent));
    Vu0::Q(dir) = Vu0::DivX(side, Vu0::Length(side));
    Vu0::Q(lo) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(dir), Vu0::ScalarAt(D_002754C8.lo));
    Vu0::Q(hi) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(dir), Vu0::ScalarAt(D_002754C8.hi));
    FindPathCurveNearestTime(self->f848->curve, &lo, &hi, &out, 0, &self->f84C, 0, self->f84C);
    f32 ahead = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(out), Vu0::Q(pos)), Vu0::Q(dir)));
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
