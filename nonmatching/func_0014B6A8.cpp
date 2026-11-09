// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1116/1120 (99.6%), checked 2026-11-09
// NEAR (2026-11-09, w7-14B6A8): every instruction and register is retail's; only the two
// distances' slots differ (sp+0x3C0 and 0x3C4 here, retail 0x3C4 and 0x3C8). What got here:
// (1) the target and neighbour terms name their operands in source order (`Vec from`, `Vec
// weight`, `Vec vel`, then MulAddX): the integrator emits the velocity's load after the 3.0
// weight's slot store, which it may alias, so sched1 keeps it there and the sum lands by the
// call as in retail (func_00191570's lever). (2) The hit switch's one-span case falls through
// to the default's `frac = time[1]`: one store less in the loop (weighted refs 8, not 10) puts
// frac's global-alloc priority (0.131) below the neighbour loop's 0.0 (0.135), so next, 0.5,
// 1.0 and 0.0 take f22..f25 first and frac f26, as in retail; reorg copies the shared load into
// the default's branch delay slot, which is the second `lwc1 $f26,132(sp)` retail shows. The
// slots: the distances are ADDRESSOF scalars put on the stack by purge_addressof after every
// temporary, so retail has one small object (at most 4 bytes, at 0x3C0) after the hit array that
// nothing reads. An empty class with an empty destructor declared after `hits` gives EXACT
// (build/swarm/w7-14B6A8/f.cpp), the pattern of GatherCollidersInSphere (func_001DC4D0) and
// GatherCollidersInBox (func_001DC238), also around collider queries; not landed, because no
// type the original plausibly declared there is known (AGENTS.md: no invented type).
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
                    case 0:
                        frac = 1.0f;
                        break;
                    case 1:
                        if (hits[0].time[0] == 0.0f && hits[0].time[1] == 1.0f) {
                            break;
                        }
                        if (hits[0].time[0] != 0.0f) {
                            frac = hits[0].time[0];
                            break;
                        }
                    default:
                        frac = hits[0].time[1];
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
                    Vec from = Vec::Of(tgt->v140);
                    Vec weight = Vec::Scalar(3.0f);
                    Vec vel = Vec::Of(tgt->v150);
                    Vu0::Q(other) = Vu0::MulAddX(from, vel, weight).q;
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
                    Vec from = Vec::Of(o->v140);
                    Vec weight = Vec::Scalar(3.0f);
                    Vec vel = Vec::Of(o->v150);
                    Vu0::Q(other) = Vu0::MulAddX(from, vel, weight).q;
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
