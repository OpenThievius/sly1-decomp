// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 620/624, checked 2026-11-08
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "on_off_object.h"
#include "game_clock.h"
#include "item_keeper.h"
#include "shapes.h"
#include "vu0.h"
#include "globals.h"
// NEAR (2026-11-08, night-size2): EvaluateHermiteVectorSegment declared with its three floats first (retail sets f12, f13 and f14 before the integer arguments), which gives retail's 1.0f in f20 and its reuse for the first length, the s2/s3 of outTime and the point and both calls; the weight's min is MinF(t, 0.15f) (b <? a, player_request.cpp's), retail's min.s f0, f0, f1. Still differs: 620 bytes against 624: retail reads t again from its slot for *outTime (lwc1 f0, 80(sp)) where ours keeps the f1 of the min, and in the no-solution branch the float registers (retail: vel.z f0, point.z f3, g f1, tt f0; the order of the dz and g statements changes nothing), which also gives retail its non-likely bnez.
void ComputeObjectMotionInFrame(BaseObject* from, BaseObject* to, Vec02* pt, Vec02* a, Vec02* b, Vec02* c, Vec02* d);
s32 SolveArrivalTimeAtHeight(Player* self, Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out);
void EvaluateHermiteVectorSegment(f32 t, f32 u, f32 v, void* a, void* b, void* c, void* d, void* e, void* f, void* g);

static inline f32 MinF(f32 a, f32 b) { return b <? a; }
void ScorePlayerTargetPlacement(Player* self, Vec02* point, BaseObject* obj, Vec02* start, Vec02* extra, f32* outTime, f32* outCost, Vec02* outPoint, Vec02* outVel)
{
    Vec02 vel;
    Vec02 reach;
    Vec02 seg1;
    Vec02 seg2;
    Vec02 weight;
    f32 t;
    ComputeObjectMotionInFrame(obj, 0, start, &vel, 0, 0, 0);
    if (SolveArrivalTimeAtHeight(self, (Vec02*)self->f6D4, point, start, &vel, &t) == 0) {
        f32 dz = point->z - vel.z;
        f32 g = self->gravity.z;
        f32 tt = (-dz / g) >? 0.0f;
        f32 h = ((Vec02*)self->f6D4)->z - start->z + (g * (tt * 0.5f) * tt + dz * tt);
        if (outTime != 0) {
            *outTime = tt;
        }
        if (outCost != 0) {
            *outCost = 1010000.0f - h;
        }
        return;
    }
    Vu0::Set(weight, Vu0::FromFloat(MinF(t, 0.15f)));
    Vu0::Set(reach, Vu0::MulAddX(Vu0::Q(*start), Vu0::Q(vel), Vu0::Q(weight)));
    if (extra != 0) {
        Vu0::Set(vel, Vu0::Add(Vu0::Q(vel), Vu0::Q(*extra)));
    }
    if (outTime != 0) {
        *outTime = t;
    }
    if (outCost != 0) {
        EvaluateHermiteVectorSegment(t, 0.0f, 1.0f, (void*)self->f6D4, point, &reach, &vel, 0, 0, &seg1);
        f32 a = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(seg1), Vu0::Q(seg1))));
        EvaluateHermiteVectorSegment(t, t, 1.0f, (void*)self->f6D4, point, &reach, &vel, 0, 0, &seg2);
        f32 b = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(seg2), Vu0::Q(seg2))));
        *outCost = ((a + b) * (t * 0.5f)) <? 1000000.0f;
    }
    if (outPoint != 0) {
        *outPoint = reach;
    }
    if (outVel != 0) {
        *outVel = vel;
    }
}

