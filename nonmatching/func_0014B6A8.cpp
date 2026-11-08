// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 0/0, checked 2026-11-08
// NEAR (2026-11-08, worker night-large2): the state switch, the frame test, the sixteen
// headings, the wall, target and neighbour terms and the turn are retail's; 40 lines differ.
// The wall fraction takes f22 where retail's is f26 (allocated after the inner loop's 0.5,
// 1.0 and 0.0, which here take f24..f26 for retail's f23..f25, and the next heading f23 for
// f22); in the target and neighbour terms retail stores the 3.0 weight's slot first and puts
// the sum just before the call (its store in the delay slot), ours sums first; and retail's
// two distances sit at 0x3C4 and 0x3C8, ours at 0x3C0 and 0x3C4 (a 4-byte local before them in
// retail). Found on the way: each clamp's top as a named float (the compare and the result
// one register), the main body as the switch's 12/13 case, the hit count as a switch with
// default first, SetSinCosPair with its float first (its own code is unchanged). Tried: frac
// declared at four other places, Set for the summed point.
// In the context of its file, src/main/file_149398.cpp (with SetSinCosPair(f32, SinCosPair*)).
#include "common.h"
#include "vu0.h"
#include "switched_collider.h"
#include "world.h"
#include "collider.h"

struct SinCosPair { f32 a; f32 b; s32 value; };
void SetSinCosPair(f32 value, SinCosPair* self);
extern s32 D_00261C90;
extern s32 g_frameCount;
s32 func_001909F0(void* tree, Vec02* from, Vec02* to, s32 max, ColliderSpan* out);
void FindClosestPointsOnSegments(Vec02* a0, Vec02* a1, Vec02* b0, Vec02* b1, Vec02* onA, f32* dist, Vec02* onB);
void func_001C8418(Agent* self, Vec02* goal);
void UpdateAgentGoal(Agent* self);
f32 WrapAngle(f32 a);

typedef NumberedAgent* (*TargetOfFn)(NumberedAgent* self);

void UpdateNumberedAgentGoal(NumberedAgent* self, s32 flag)
{
    typedef Vu0::Vec Vec;
    switch (self->f724) {
    case 12:
    case 13:
        if (g_frameCount % D_00261C90 == self->fC2C % D_00261C90) {
            f32 step = 0.3926991f;
            f32 best = 3.40282347e+38f;
            f32 angle = self->f638;
            f32 frac;
            Vec02 bestPos;
            Vec02 probe;
            SinCosPair dir;
            for (s32 i = 0; i < 16; i++) {
                SetSinCosPair(angle, &dir);
                f32 score = 0.0f;
                Vu0::Set(probe, Vu0::MulAddX(Vec::Of(self->v140), Vec::Of(*(Vec02*)&dir), Vec::Scalar(3000.0f)).q);
                if (self->f928 != 0) {
                    ColliderSpan hits[8];
                    s32 r = func_001909F0(*(void**)(self->f928 + 0x54), &self->v140, &probe, 8, hits);
                    switch (r) {
                    default:
                        frac = hits[0].time[1];
                        break;
                    case 0:
                        frac = 1.0f;
                        break;
                    case 1:
                        if (hits[0].time[0] != 0.0f || hits[0].time[1] != 1.0f) {
                            frac = (hits[0].time[0] != 0.0f) ? hits[0].time[0] : hits[0].time[1];
                        }
                        break;
                    }
                    f32 v = (0.75f - frac) * 1.3333334f;
                    f32 lo = 0.0f;
                    f32 hi = 1.0f;
                    f32 c;
                    if (v < lo) {
                        c = 0.0f;
                    } else if (hi < v) {
                        c = hi;
                    } else {
                        c = v;
                    }
                    score = score + c * 4.0f;
                }
                NumberedAgent* tgt = ((TargetOfFn)((void**)self->desc)[0x198 / 4])(self);
                if (tgt != 0) {
                    Vec02 other;
                    Vu0::Q(other) = Vu0::MulAddX(Vec::Of(tgt->v140), Vec::Of(tgt->v150), Vec::Scalar(3.0f)).q;
                    Vec02 onA;
                    Vec02 onB;
                    f32 d;
                    FindClosestPointsOnSegments(&self->v140, &probe, &tgt->v140, &other, &onA, &d, &onB);
                    f32 q = d / ((tgt->radius3D0 + self->radius3D0) * 5.0f);
                    f32 hi = 1.0f;
                    if (q < 0.0f) {
                        q = 0.0f;
                    } else if (hi < q) {
                        q = hi;
                    }
                    score = score + (1.0f - q) * 3.0f;
                }
                f32 next = angle + step;
                for (NumberedAgent* o = (NumberedAgent*)self->world->list1CCC.head; o != 0;
                     o = *(NumberedAgent**)&o->fC10) {
                    if (o == self) {
                        continue;
                    }
                    Vec02 other;
                    Vu0::Q(other) = Vu0::MulAddX(Vec::Of(o->v140), Vec::Of(o->v150), Vec::Scalar(3.0f)).q;
                    Vec02 onA;
                    Vec02 onB;
                    f32 d;
                    FindClosestPointsOnSegments(&self->v140, &probe, &o->v140, &other, &onA, &d, &onB);
                    f32 q = d / ((o->radius3D0 + self->radius3D0) + (o->radius3D0 + self->radius3D0));
                    f32 hi = 1.0f;
                    if (q < 0.0f) {
                        q = 0.0f;
                    } else if (hi < q) {
                        q = hi;
                    }
                    score = score + (1.0f - q) * 0.5f;
                }
                f32 turn = WrapAngle(angle - self->f638) * 0.31830987f;
                score = score + (__builtin_fabsf(turn) + __builtin_fabsf(turn));
                if (score < best) {
                    best = score;
                    bestPos = probe;
                }
                angle = WrapAngle(next);
            }
            func_001C8418(self, &bestPos);
        }
        break;
    case 4:
        if (flag != 0) {
            func_001C8418(self, &self->v140);
        }
        break;
    default:
        UpdateAgentGoal(self);
        break;
    }
}
