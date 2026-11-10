// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1800/1796, checked 2026-11-10
// NEAR (2026-11-08, night-large3): func_0017D5D8, the player's steer and leap search (80.8% of
// the words). The steer block, both switches and both searches follow retail; what is left is
// the frame (0x160 against 0x180): retail's point-object loop has its vectors 0x10 higher (pos at
// 0x60, the MulAddX end at 0xB0, an unexplained slot at 0xA0) and the floats t, cost, a, b after
// them at 0xD0..0xE4, and the -1 vector of the steer is a Scalar retail keeps in the vf6 register
// MulX's result does not take. Tried: Vec forms of MulAddX, a function-scope position.
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"
#include "switched_collider.h"

extern f32 D_00263EB0[4];
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);
f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);
void ConvertPositionToWorld(void* obj, Vec02* out);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, s32 a, s32 b, s32 c);
void MeasurePointToSegment(const Vec02* p, Vec02* a, Vec02* b, f32* o1, f32* o2);
void InitContactPairFlags(void* world, void* obj);
void SetPlayerState(Player* self, s32 a, s32 b);
void ScorePlayerTargetPlacement(Player* p, Vec02* vel, void* target, Vec02* at, s32 zero, f32* t, f32* cost, Vec02* aim, Vec02* land);
extern f32 g_gameTime;

struct LeapPart_17D5D8 {
    u8 pad000[0x100];
    Vec02 pos;                      // 0x100
    u8 pad110[0x140 - 0x110];
    Vec02 v140;                     // 0x140
    Vec02 v150;                     // 0x150
    u8 pad160[0x558 - 0x160];
    LeapPart_17D5D8* next;          // 0x558
    u8 pad55C[0x568 - 0x55C];
    f32 height;                     // 0x568
};
struct LeapPoint_17D5D8 {
    u8 pad00[0x18];
    void* parent;                   // 0x18
    u8 pad1C[0x50 - 0x1C];
    LeapPoint_17D5D8* next;         // 0x50
    u8 pad54[0x58 - 0x54];
    f32 radius;                     // 0x58
};
struct LeapRecord_17D5D8 { u8 pad00[0x18]; f32 time; u8 pad1C[0x20 - 0x1C]; Vec02 aim; Vec02 land; };

static inline void StartPlayerLeap(Player* p, f32 t, const Vec02& aim, const Vec02& land)
{
    ((LeapRecord_17D5D8*)p->f2514)->time = g_gameTime + t;
    ((LeapRecord_17D5D8*)p->f2514)->aim = aim;
    ((LeapRecord_17D5D8*)p->f2514)->aim.z += 75.0f;
    ((LeapRecord_17D5D8*)p->f2514)->land = land;
    ((LeapRecord_17D5D8*)p->f2514)->land.z = p->v150.z + t * p->gravity.z;
}

// v made a unit vector, or the fallback when shorter than 1e-4; its length.
static inline u128 NormalizeVectorOr(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Q(v) = Vu0::DivX(Vu0::Q(v), len);
    }
    return len;
}

// The square of the distance from a to b on the ground plane.
static inline f32 GroundDistanceSquared(const Vec02& a, const Vec02& b)
{
    Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(a), Vu0::Vec::Of(b));
    return Vu0::ToFloatMoved(Vu0::DotXY(d.q, d.q));
}

void func_0017D5D8(Player* p)
{
    Vec02 aim;
    Vec02 bestAim;
    Vec02 land;
    Vec02 bestLand;
    Vec02 pos;
    switch (p->f2228) {
    case 4:
    case 6:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        break;
    default:
        ComputePolarOffset(&aim, p->f630, p->f634 * p->f226C, 0.0f);
        Vu0::Q(bestAim) = Vu0::FromFloat(-1.0f);
        Vu0::Q(p->v640) = Vu0::MulX(Vu0::RotateTransposed(p->m660, Vu0::Q(aim)), Vu0::Q(bestAim));
        if ((p->f2228 != 0 || p->f2270 == 3) && p->f2268 == 0) {
            bestAim = p->v150;
            bestAim.z = 0.0f;
            f32 speed = Vu0::ToFloat(NormalizeVectorOr(bestAim, g_unitXVector));
            f32 d = SplitVectorAlongAxis(&aim, &bestAim, 0, &land);
            if (d < speed && speed * -0.25f < d) {
                Vu0::Q(bestLand) = Vu0::FromFloat(speed);
                Vu0::Q(aim) = Vu0::MulAddX(Vu0::Q(land), Vu0::Q(bestAim), Vu0::Q(bestLand));
            }
        }
        p->v2290 = aim;
        break;
    }
    switch (p->f2228) {
    case 3:
        if (!(D_00263EB0[0] < g_gameTime - p->f222C)) {
            return;
        }
    case 1:
    case 2:
    case 5:
    default: {
        LeapPart_17D5D8* best = 0;
        LeapPoint_17D5D8* bestPoint = 0;
        f32 bestCost = 1500.0f;
        f32 bestT;
        for (LeapPart_17D5D8* q = (LeapPart_17D5D8*)g_partList.head; q != 0; q = q->next) {
            Vec02 rel;
            Vec02 dv;
            Vec02 end;
            f32 t;
            f32 cost;
            f32 a;
            f32 b;
            if (360000.0f < GroundDistanceSquared(q->v140, p->v140)) {
                continue;
            }
            if (q->v140.z + q->height < p->v140.z) {
                continue;
            }
            ScorePlayerTargetPlacement(p, &p->v150, q, &q->v140, 0, &t, &cost, &aim, &land);
            if (bestCost < cost) {
                continue;
            }
            Vu0::Q(rel) = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(q->pos));
            Vu0::Q(dv) = Vu0::Sub(Vu0::Q(p->v150), Vu0::Q(q->v150));
            Vu0::Q(end) = Vu0::MulAddX(Vu0::Q(rel), Vu0::Q(dv), Vu0::Scalar(0.25f <? t));
            end.z = 0.0f;
            rel.z = 0.0f;
            MeasurePointToSegment(&D_00248D30, &rel, &end, &a, &b);
            if ((100.0f < b || a == 0.0f) && (25.0f < b || 0.0f < p->v150.z)) {
                continue;
            }
            best = q;
            bestPoint = 0;
            bestAim = aim;
            bestLand = land;
            bestT = t;
            bestCost = cost;
        }
        for (LeapPoint_17D5D8* q = (LeapPoint_17D5D8*)g_pointObjects.head; q != 0; q = q->next) {
            Vec02 vel;
            Vec02 rel;
            Vec02 dv;
            Vec02 end;
            f32 t;
            f32 cost;
            f32 a;
            f32 b;
            ConvertPositionToWorld(q, &pos);
            if (360000.0f < GroundDistanceSquared(pos, p->v140)) {
                continue;
            }
            ScorePlayerTargetPlacement(p, &p->v150, q->parent, &pos, 0, &t, &cost, &aim, &land);
            if (bestCost < cost) {
                continue;
            }
            ComputeObjectMotionInFrame(q->parent, 0, &pos, &vel, 0, 0, 0);
            Vu0::Q(rel) = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(pos));
            Vu0::Q(dv) = Vu0::Sub(Vu0::Q(p->v150), Vu0::Q(vel));
            Vu0::Q(end) = Vu0::MulAddX(Vu0::Q(rel), Vu0::Q(dv), Vu0::Scalar(0.25f <? t));
            end.z = 0.0f;
            rel.z = 0.0f;
            MeasurePointToSegment(&D_00248D30, &rel, &end, &a, &b);
            if ((q->radius < b || a == 0.0f) && (q->radius * 0.25f < b || 0.0f < p->v150.z)) {
                continue;
            }
            bestPoint = q;
            best = 0;
            bestAim = aim;
            bestLand = land;
            bestT = t;
            bestCost = cost;
        }
        if (best != 0) {
            if (p->f2220 != 2 || p->f2228 != 5) {
                void* held = p->heldObject;
                if (held != best) {
                    InitContactPairFlags(p->world, best);
                    if (held != 0) {
                        InitContactPairFlags(p->world, held);
                    }
                }
                StartPlayerLeap(p, bestT, bestAim, bestLand);
                p->heldObject = best;
                SetPlayerState(p, 2, 4);
                return;
            }
        }
        if (bestPoint != 0) {
            StartPlayerLeap(p, bestT, bestAim, bestLand);
            p->f23B4 = bestPoint;
            SetPlayerState(p, 2, 9);
        }
        return;
    }
    case 0:
    case 4:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        return;
    }
}
