// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 620/624 (99.4%), checked 2026-11-07
// NEAR: one instruction: retail's min.s f1, f0, f1 (the speed, then maxSpeed, into maxSpeed's register); `maxSpeed <? speed` gives min.s f1, f1, f0 and `speed <? maxSpeed` (also with <?=, a local, the division apart) puts the division and the min in f2. Everything else is retail's: the FromFloats velocity, the Normalized struct copy at 0xC0, the turn clamp.
// In the context of its file, src/main/file_19E040.cpp.
#include "common.h"
#include "collider.h"
#include "paired_object.h"
#include "globals.h"
#include "vu0.h"

extern f32 g_gameClock[];

// The ground a paired object keeps to (its controller): a circle around center.
struct PairArea {
    u8 pad000[0x330];
    Vec02 center;           // 0x330
    f32 radius;             // 0x340
};

// v made unit length (no test for zero; func_001A6788).
static inline u128 Normalized(Vec02 v)
{
    return Vu0::DivX(Vu0::Q(v), Vu0::Length(Vu0::Q(v)));
}

s32 CollectBoundsSpans(Vec02* p, Vec02* a, Vec02* b, f32 radius, s32 count, ColliderSpan* out);
f32 ArctangentOfRatio(f32 y, f32 x);
f32 WrapAngle(f32 a);
void SetPlacedObjectLocalVelocity(PlacedObject* self, Vec02* v);
void SetPlacedObjectSpinFromFloats(PlacedObject* self, f32 x, f32 y, f32 z);

void SteerPairedObjectWithinArea(PairedObject* self, Vec02* goal, s32 backwards)
{
    Vec02 from;
    Vec02 to;
    Vec02 delta;
    from = self->v140;
    from.z = 0.0f;
    to = *goal;
    to.z = 0.0f;
    PairArea* area = (PairArea*)self->controller;
    if (0.0001f < area->radius) {
        ColliderSpan span;
        if (CollectBoundsSpans(&area->center, &from, &to, area->radius, 1, &span)) {
            Vec02 mid;
            Vec02 dir;
            Vu0::Q(mid) = Vu0::MulXSum(Vu0::Q(span.q[0]), Vu0::Scalar(0.5f), Vu0::Q(span.q[1]), Vu0::Scalar(0.5f));
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(mid), Vu0::Q(((PairArea*)self->controller)->center));
            Vu0::Q(dir) = Normalized(dir);
            Vu0::Q(to) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(((PairArea*)self->controller)->radius * 1.5f));
        }
    }
    Vu0::Q(delta) = Vu0::Sub(Vu0::Q(to), Vu0::Q(from));
    f32 bearing = ArctangentOfRatio(delta.y, delta.x);
    f32 heading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
    if (backwards) {
        heading = WrapAngle(heading + 3.1415927f);
    }
    f32 turn = WrapAngle(bearing - heading);
    if (0.05235988f < __builtin_fabsf(turn)) {
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
    } else {
        f32 speed = self->maxSpeed <? Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(delta))) / g_gameClock[2];
        if (backwards) {
            speed = -speed;
        }
        Vec02 v;
        Vu0::Q(v) = Vu0::FromFloats(speed, 0.0f, 0.0f);
        SetPlacedObjectLocalVelocity(self, &v);
    }
    f32 w = turn / g_gameClock[2];
    f32 lo = -self->maxTurn;
    if (w < lo) {
        w = lo;
    } else if (self->maxTurn < w) {
        w = self->maxTurn;
    }
    SetPlacedObjectSpinFromFloats(self, 0.0f, 0.0f, w);
}
