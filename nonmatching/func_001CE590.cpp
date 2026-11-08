// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 628/624, checked 2026-11-07
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "on_off_object.h"
#include "game_clock.h"
#include "item_keeper.h"
#include "shapes.h"
#include "vu0.h"
#include "globals.h"
// NEAR (2026-11-08, wave 4): the instructions are retail's; registers and scheduling differ. Retail keeps outTime in s2 and the point in s3 (here swapped), holds 1.0f in f20 and reuses f20 for the first length (mov.s f14 for the second call before the qmfc2), where here 1.0f takes f21 because the argument move is scheduled after the length is computed, and the arguments of the two Hermite calls are ordered differently around the delay slots. Set for the stack vectors keeps the address of reach out of a callee-saved register (it was s6 with Q); ToFloatMoved did not change the schedule.
void ComputeObjectMotionInFrame(BaseObject* from, BaseObject* to, Vec02* pt, Vec02* a, Vec02* b, Vec02* c, Vec02* d);
s32 SolveArrivalTimeAtHeight(Player* self, Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out);
void EvaluateHermiteVectorSegment(void* a, void* b, void* c, void* d, void* e, void* f, void* g, f32 t, f32 u, f32 v);

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
    Vu0::Set(weight, Vu0::FromFloat(t <? 0.15f));
    Vu0::Set(reach, Vu0::MulAddX(Vu0::Q(*start), Vu0::Q(vel), Vu0::Q(weight)));
    if (extra != 0) {
        Vu0::Set(vel, Vu0::Add(Vu0::Q(vel), Vu0::Q(*extra)));
    }
    if (outTime != 0) {
        *outTime = t;
    }
    if (outCost != 0) {
        EvaluateHermiteVectorSegment((void*)self->f6D4, point, &reach, &vel, 0, 0, &seg1, t, 0.0f, 1.0f);
        f32 a = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(seg1), Vu0::Q(seg1))));
        EvaluateHermiteVectorSegment((void*)self->f6D4, point, &reach, &vel, 0, 0, &seg2, t, t, 1.0f);
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

