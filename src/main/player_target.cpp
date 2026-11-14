// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "on_off_object.h"
#include "game_clock.h"
#include "item_keeper.h"
#include "shapes.h"
#include "vu0.h"
#include "globals.h"
#include "game_progress.h"
#include "pad_record.h"
#include "ramp_profile.h"
#include "fpu.h"
#include "object_finder.h"
struct BaseObject;
struct Vec02;

struct BaseObject;

struct PlacedObject;
struct World;

struct BaseObject;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct TargetCurve;
struct TargetPoint;

struct __attribute__((aligned(16))) OnOffDefaultsBlock { f32 f[36]; };

// The file's .data, in retail's order.
float D_00274E00 = 150.0f;
float D_00274E04 = 50.0f;
float D_00274E08 = 250.0f;
float D_00274E0C = 1000.0f;
float D_00274E10 = 1.25f;
float D_00274E14 = 2.0f;
float D_00274E18 = 250.0f;
float D_00274E1C = 0.200000003f;
float D_00274E20 = 2500.0f;
float D_00274E24 = -250.0f;
f32 D_00274E28 = 0;
f32 D_00274E2C = 0;
float D_00274E30 = 1250.0f;
float D_00274E34 = 500.0f;
float D_00274E38 = 500.0f;
f32 D_00274E3C = 1e+03f;
float D_00274E40 = 100.0f;
float D_00274E44 = 100.0f;
float D_00274E48 = 0.300000012f;
float D_00274E4C = 25.0f;
float D_00274E50 = 1.5f;
float D_00274E54 = 0.25f;
float D_00274E58 = 0.5f;
float D_00274E5C = 0.200000003f;
OnOffDefaultsBlock g_onOffObjectDefaults = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      -225.0f, 1.0f, 0.0f, 0.0f, 20.0f, 1.0f, 0.0f, 0.0f,
      -3.40282347e+38f, 3.40282347e+38f, -3.40282347e+38f, 3.40282347e+38f, -3.40282347e+38f, 3.40282347e+38f,
      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }
};
float D_00274EF0[3] = {2500.0f, 0.0f, 1.0f};

struct TargetShape_1CDFB8;
typedef void (*TargetShapeFn_1CDFB8)(TargetShape_1CDFB8* self, Vec02* at, s32 a, Vec02* out, s32 b, s32 c, f32* t);
struct TargetShape_1CDFB8 { TargetShapeFn_1CDFB8* vtbl; };
struct TargetCurve_1CDFB8 : BaseObject {
    TargetShape_1CDFB8* shape;      // 0x34
    TargetCurve_1CDFB8* next;       // 0x38
    u8 pad3C[0x40 - 0x3C];
    s32 mode40;                     // 0x40
};
struct TargetPoint_1CDFB8 : BaseObject {
    u8 pad34[0x50 - 0x34];
    TargetPoint_1CDFB8* next;       // 0x50
    u8 pad54[0x58 - 0x54];
    s32 mode58;                     // 0x58
    f32 radius5C;                   // 0x5C
};
struct Part_1CDFB8 {
    u8 pad0[0x140];
    Vec02 pos;                      // 0x140
    u8 pad150[0x558 - 0x150];
    Part_1CDFB8* next;              // 0x558
    u8 pad55C[0x560 - 0x55C];
    f32 radius;                     // 0x560
};
struct Class75_1CDFB8 : BaseObject {
    u8 pad34[0x80 - 0x34];
    Class75_1CDFB8* next;           // 0x80
    u8 pad84[0x88 - 0x84];
    u32 flags88;                    // 0x88
};
struct C17_1CDFB8 { u8 pad0[0x618]; void* f618; u8 pad61C[0x760 - 0x61C]; s32 worldBits; };
struct World_1CDFB8 { u8 pad0[0x1CE4]; C17_1CDFB8* f1CE4; u8 pad1CE8[0x2300 - 0x1CE8]; s32 count2300; };
struct Chooser_1CDFB8 {
    u8 pad0[0x14];
    World_1CDFB8* world;            // 0x14
    u8 pad18[0x140 - 0x18];
    Vec02 pos;                      // 0x140
    u8 pad150[0x2200 - 0x150];
    void* f2200;                    // 0x2200
    void* aimObject;                // 0x2204
    void* aimVector;                // 0x2208
    f32 aimVectorPlace;             // 0x220C
    void* lastAimObject;            // 0x2210
    u8 pad2214[0x23A0 - 0x2214];
    void* targetCurve;              // 0x23A0
    f32 targetCurvePlace;           // 0x23A4
    void* targetPoint;              // 0x23A8
    u8 pad23AC[0x23B0 - 0x23AC];
    void* heldObject;               // 0x23B0
    u8 pad23B4[0x23CC - 0x23B4];
    void* f23CC;                    // 0x23CC
};
extern List01 g_class75List;
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
s32 CompletesWorldBits(s32 bits);
void SetPlayerAimMode(Player* self, s32 state);
void UpdatePlayerAimTarget(Player* s);
s32 MaskWorldBitsBySave(void);

s32 ChooseNearbyPlayerTarget(Chooser_1CDFB8* self, void* target, s32* out)
{
    Vec02 a;
    Vec02 b;
    f32 curveT;
    f32 vectorT;
    s32 kind = -1;
    f32 best = target != 0 ? -3.40282347e+38f : D_00274E00;
    Class75_1CDFB8* obj;
    TargetCurve_1CDFB8* curve;
    Part_1CDFB8* part;
    TargetPoint_1CDFB8* point;
    TargetCurve_1CDFB8* vector;
    C17_1CDFB8* c17;
    f32 curveU;
    f32 vectorU;
    f32 dist;

    for (TargetCurve_1CDFB8* c = (TargetCurve_1CDFB8*)g_targetCurveList.head; c != 0; c = c->next) {
        TransformPointBetweenFrames(0, (PlacedObject*)c->parent, &self->pos, &a);
        TargetShape_1CDFB8* s = c->shape;
        if (s->vtbl[10] != 0) {
            s->vtbl[10](s, &a, 0, &b, 0, 0, &curveT);
        }
        f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(b))));
        if (d < best || c == target) {
            curveU = curveT;
            best = best <? d;
            curve = c;
            kind = 0;
        }
    }
    for (TargetPoint_1CDFB8* p = (TargetPoint_1CDFB8*)g_targetPointList.head; p != 0; p = p->next) {
        ConvertPositionToWorld(p, &a);
        dist = Vu0::Distance(a, self->pos);
        dist = __builtin_fabsf(dist - p->radius5C);
        if (dist < best || p == target) {
            best = best <? dist;
            point = p;
            kind = 1;
        }
    }
    for (Part_1CDFB8* q = (Part_1CDFB8*)g_partList.head; q != 0; q = q->next) {
        dist = Vu0::Distance(q->pos, self->pos);
        dist = __builtin_fabsf(dist - q->radius);
        if (dist < best || q == target) {
            part = q;
            best = best <? dist;
            kind = 2;
        }
    }
    for (Class75_1CDFB8* o = (Class75_1CDFB8*)g_class75List.head; o != 0; o = o->next) {
        if (o != self->lastAimObject && (o->flags88 & 1) && (target == 0 || o == target) && IsObjectOfKind(o, 0x76) != 0) {
            GetObjectWorldPosition(o, &a);
            f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(self->pos)))) - D_00274E08;
            if (d < (best <? 0.0f) || o == target) {
                best = best <? d;
                obj = o;
                kind = 6;
            }
        }
    }
    for (TargetCurve_1CDFB8* v = (TargetCurve_1CDFB8*)g_targetVectors.list.head; v != 0; v = v->next) {
        TransformPointBetweenFrames(0, (PlacedObject*)v->parent, &self->pos, &a);
        TargetShape_1CDFB8* s = v->shape;
        if (s->vtbl[10] != 0) {
            s->vtbl[10](s, &a, 0, &b, 0, 0, &vectorT);
        }
        TransformPointBetweenFrames((PlacedObject*)v->parent, 0, &b, &b);
        f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(b), Vu0::Q(self->pos)))) - D_00274E08;
        if (d < (best <? 0.0f) || v == target) {
            d = best <? d;
            vectorU = vectorT;
            vector = v;
            best = d;
            kind = 7;
        }
    }
    World_1CDFB8* w = self->world;
    s32 n = g_currentEntry->count64;
    C17_1CDFB8* c = w->f1CE4;
    if (c != 0 && n >= w->count2300 && CompletesWorldBits(c->worldBits) == 0) {
        GetObjectWorldPosition((BaseObject*)self->world->f1CE4->f618, &a);
        dist = Vu0::Distance(a, self->pos);
        if (dist < D_00274E18 || self->world->f1CE4 == target) {
            kind = 5;
            c17 = self->world->f1CE4;
        }
    }
    s32 r;
    switch (kind) {
    case 0:
        *out = curve->mode40;
        r = 0x15;
        self->targetCurve = curve;
        self->targetCurvePlace = curveU;
        break;
    case 1:
        *out = point->mode58;
        r = 0x15;
        self->targetPoint = point;
        break;
    case 2:
        *out = 1;
        r = 0x15;
        self->heldObject = part;
        break;
    case 6:
        self->aimObject = obj;
        self->f2200 = obj;
        self->aimVector = 0;
        SetPlayerAimMode((Player*)self, 0);
        UpdatePlayerAimTarget((Player*)self);
        *out = 6;
        r = 0x10;
        break;
    case 7:
        self->aimVector = vector;
        self->aimVectorPlace = vectorU;
        self->aimObject = 0;
        self->f2200 = 0;
        SetPlayerAimMode((Player*)self, 0);
        UpdatePlayerAimTarget((Player*)self);
        *out = 6;
        r = 0x10;
        break;
    case 5:
        *out = 7;
        r = 0x10;
        self->f23CC = c17;
        break;
    default:
        if (MaskWorldBitsBySave() & 0x12000) {
            *out = 3;
            r = 0x10;
        } else {
            *out = -1;
            r = -1;
        }
        break;
    }
    return r;
}

void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
s32 SolveArrivalTimeAtHeight(Player* self, Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void EvaluateHermiteVectorSegment(f32 dur, f32 t, f32 k, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, Vec02* pos, Vec02* vel, Vec02* acc);

static inline f32 MinF(f32 a, f32 b) { return b <? a; }
void ScorePlayerTargetPlacement(Player* self, Vec02* point, BaseObject* obj, Vec02* start, Vec02* extra, f32* outTime, f32* outCost, Vec02* outPoint, Vec02* outVel)
{
    Vec02 vel;
    Vec02 reach;
    Vec02 seg1;
    Vec02 seg2;
    Vec02 weight;
    f32 t;
    ComputeObjectMotionInFrame((PlacedObject*)obj, 0, start, &vel, 0, 0, 0);
    if (SolveArrivalTimeAtHeight(self, (Vec02*)self->probeVertex, point, start, &vel, &t) == 0) {
        f32 dz = point->z - vel.z;
        f32 g = self->gravity.z;
        f32 fall = -dz / g;
        f32 tt = fall >? 0.0f;
        f32 h = ((Vec02*)self->probeVertex)->z - start->z + (g * (tt * 0.5f) * tt + dz * tt);
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
        *(Vu0::Vec*)&vel = Vu0::Add(Vu0::Vec::Of(vel), Vu0::Vec::Of(*extra));
    }
    if (outTime != 0) {
        *outTime = t;
    }
    if (outCost != 0) {
        EvaluateHermiteVectorSegment(t, 0.0f, 1.0f, (const Vec02*)self->probeVertex, point, &reach, &vel, 0, 0, &seg1);
        f32 a = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(seg1), Vu0::Q(seg1))));
        EvaluateHermiteVectorSegment(t, t, 1.0f, (const Vec02*)self->probeVertex, point, &reach, &vel, 0, 0, &seg2);
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

typedef void (*PathShapeFn)(void* self, void* out, s32 x);

struct PathShape {
    PathShapeFn* vtbl;
};

struct PathTarget {
    u8 pad0[0x18];
    s32 frame;
    u8 pad1C[0x34 - 0x1C];
    PathShape* shape;
};

typedef f32 (*ShapeScalarFn)(void* self, f32 t);
typedef f32 (*ShapeLimitFn)(void* self);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.

// A value clamped to [lo, hi]; returned from an inline, the three outcomes are one value.
static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void PlaceOnTargetObject(Player* self, PathTarget* node, Vec02* outA, Vec02* outB, f32 t)
{
    Vec02 a;
    Vec02 b;
    Vec02 c;
    Vec02 d;
    Vec02 e;
    Vec02 f;
    f32 lo;
    f32 hi;
    PathShape* shape = node->shape;
    if (shape->vtbl[1] != 0) {
        shape->vtbl[1](shape, &a, (s32)&b);
    }
    TransformPointBetweenFrames((PlacedObject*)node->frame, 0, &a, &c);
    TransformDirectionBetweenFrames((PlacedObject*)node->frame, 0, &b, &d);
    ComputePolarOffset((Vec3*)&e, self->stickHeading, Vu0::ToFloat(Vu0::Length(Vu0::Q(*(Vec02*)((u8*)self + 0xE90)))) * self->stickLevel, 0.0f);
    f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(e), Vu0::Q(d)));
    PathShape* s2 = node->shape;
    f32 value = ((ShapeScalarFn)s2->vtbl[5])(s2, t);
    f.y = -*(f32*)((u8*)self + 0xE40);
    f.x = -*(f32*)((u8*)self + 0xE90);
    f.z = D_00274E1C;
    ApproachValueWithRamp(value, D_00274E04, g_gameClock.dt, (RampProfile*)&f, &lo);
    PathShape* s3 = node->shape;
    ApproachValueWithRamp(value, ((ShapeLimitFn)s3->vtbl[8])(s3) - D_00274E04, g_gameClock.dt, (RampProfile*)&f, &hi);
    *outA = c;
    f32 clamped = ClampBetween(along, lo, hi);
    Vu0::Q(*outB) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(clamped));
}

// What a target cost search passes to its scorer: the player, the target, and the record at
// +0x10 the scorer hands on.
struct TargetCostContext { Player* p0; BaseObject* p4; u8 pad1[0x10 - 8]; };
struct ObjectPlacementScore { u8 vecA[0x10]; u8 vecB[0x10]; f32 result; };

void PlaceOnTargetObject(Player* self, PathTarget* node, Vec02* outA, Vec02* outB, f32 t);
void ScorePlayerTargetPlacement(Player* self, Vec02* point, BaseObject* obj, Vec02* start, Vec02* extra, f32* outTime, f32* outCost, Vec02* outPoint, Vec02* outVel);

f32 ScoreTargetObjectAt(TargetCostContext* self, f32 t)
{
    ObjectPlacementScore f;
    PlaceOnTargetObject(self->p0, (PathTarget*)self->p4, (Vec02*)f.vecA, (Vec02*)f.vecB, t);
    ScorePlayerTargetPlacement(self->p0, (Vec02*)((u8*)self + 0x10), self->p4->parent, (Vec02*)f.vecA, (Vec02*)f.vecB, 0, &f.result, 0, 0);
    return f.result;
}

struct PointPlacementScore { u8 vecA[0x10]; f32 result; };

struct TargetPoint;
struct TargetCurve;
void PlaceOnTargetPoint(TargetPoint* self, Vec02* out, f32* angleOut, f32 t);
void ScorePlayerTargetPlacement(Player* self, Vec02* point, BaseObject* obj, Vec02* start, Vec02* extra, f32* outTime, f32* outCost, Vec02* outPoint, Vec02* outVel);

f32 ScoreTargetPointAt(TargetCostContext* self, f32 t)
{
    PointPlacementScore f;
    PlaceOnTargetPoint((TargetPoint*)self->p4, (Vec02*)f.vecA, 0, t);
    ScorePlayerTargetPlacement(self->p0, (Vec02*)((u8*)self + 0x10), self->p4->parent, (Vec02*)f.vecA, 0, 0, &f.result, 0, 0);
    return f.result;
}

void PlaceOnTargetCurve(TargetCurve* self, Vec02* out, f32* angleOut, f32 t);
void ScorePlayerTargetPlacement(Player* self, Vec02* point, BaseObject* obj, Vec02* start, Vec02* extra, f32* outTime, f32* outCost, Vec02* outPoint, Vec02* outVel);

f32 ScoreTargetCurveAt(TargetCostContext* self, f32 t)
{
    PointPlacementScore f;
    PlaceOnTargetCurve((TargetCurve*)self->p4, (Vec02*)f.vecA, 0, t);
    ScorePlayerTargetPlacement(self->p0, (Vec02*)((u8*)self + 0x10), self->p4->parent, (Vec02*)f.vecA, 0, 0, &f.result, 0, 0);
    return f.result;
}

// Left in this order: retail's call here evaluates the time before the pointers.
void TransformPointAtTime(PlacedObject* self, PlacedObject* top, f32 t, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);
extern const Vec02 D_00248D30;

// v made unit length, or fallback when shorter than 0.0001; returns its length.
static inline f32 NormalizeVector(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Set(v, Vu0::DivX(Vu0::Q(v), len));
    }
    return Vu0::ToFloatMoved(len);
}

void ScorePlayerLeapToPoint(Player* self, BaseObject* obj, Vec02* point, f32* out1, Vec02* out2, Vec02* out3, f32 t)
{
    Vec02 pos0;
    Vec02 p;
    Vec02 d;
    Vec02 acc;
    Vec02 vel;
    Vu0::Set(pos0, Vu0::MulAddX2(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Scalar(t), Vu0::Q(self->gravity), Vu0::Scalar(t * (t * 0.5f))));
    p = *point;
    TransformPointAtTime((PlacedObject*)obj, 0, t, &p, 0, 0, 0);
    Vu0::Set(d, Vu0::Sub(Vu0::Q(p), Vu0::Q(pos0)));
    f32 r = D_00274E08;
    f32 dist2 = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
    if (dist2 < r * r) {
        if (out1 != 0) {
            *out1 = Fpu::Sqrt(dist2) - r;
        }
        if (out2 != 0) {
            *out2 = pos0;
        }
        if (out3 != 0) {
            Vu0::Q(*out3) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t));
        }
        return;
    }
    f32 az = __builtin_fabsf(d.z);
    if (r < az || t == 0.0f) {
        if (out1 != 0) {
            *out1 = az + 1010000.0f;
        }
        if (out2 != 0) {
            *out2 = pos0;
        }
        if (out3 != 0) {
            Vu0::Q(*out3) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t));
        }
        return;
    }
    d.z = 0.0f;
    f32 l = NormalizeVector(d, D_00248D30);
    f32 gap = l - Fpu::Sqrt(D_00274E08 * D_00274E08 - az * az);
    Vu0::Set(acc, Vu0::MulX(Vu0::Q(d), Vu0::Scalar((gap + gap) / (t * t))));
    Vu0::Set(vel, Vu0::MulAddX2(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t), Vu0::Q(acc), Vu0::Scalar(t)));
    if (out1 != 0) {
        *out1 = ((D_00274E14 + D_00274E14) * gap / t) <? 1000000.0f;
    }
    if (out2 != 0) {
        Vu0::Q(*out2) = Vu0::MulAddX(Vu0::Q(pos0), Vu0::Q(acc), Vu0::Scalar(t * (t * 0.5f)));
    }
    if (out3 != 0) {
        Vu0::Q(*out3) = Vu0::MulAddX2(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t), Vu0::Q(acc), Vu0::Scalar(t));
    }
}

// func_001CEB18 also takes a float in $f12 (it reads $f12 at entry); this
// function passes its own float parameter straight through.
struct PathScoreArgs { Player* self; BaseObject* obj; s32 pad[2]; s32 c[4]; };
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void ScorePlayerLeapToPoint(f32 t, Player* self, BaseObject* obj, Vec02* point, f32* out1, Vec02* out2, Vec02* out3);

f32 ScoreTargetPathAt(PathScoreArgs* o, f32 t)
{
    f32 out;
    ScorePlayerLeapToPoint(t, o->self, o->obj, (Vec02*)o->c, &out, 0, 0);
    return out;
}

struct PathScoreContext {
    s32 f0;
    PathTarget* node;
};

struct PathScoreFrame {
    Quad16 a;
    s32 b[2];
    u8 pad18[8];
    Quad16 c;
    f32 out;
};

typedef f32 (*MinimumFn)(void* ctx, f32 x);
void FindLocalMinimum(MinimumFn fn, void* ctx, f32 x, f32 step, f32 lo, f32 hi, f32* outX, f32* outY);

f32 ScoreTargetPathNearest(PathScoreContext* self)
{
    PathScoreFrame l;
    PathTarget* n = self->node;
    PathShape* o = n->shape;
    if (o->vtbl[2] != 0) {
        o->vtbl[2](o, &l.a, 0);
    }
    f32 q = 0.25f;
    l.b[0] = self->f0;
    l.b[1] = n->frame;
    l.c = l.a;
    
    FindLocalMinimum((MinimumFn)ScoreTargetPathAt, l.b, 0.5f, q, q, 3.0f, 0, &l.out);
    return l.out;
}

struct TargetSpanHit {
    Vec02 point;
    u8 pad10[0x34];
    f32 f44;
    u8 pad48[0x28];
};
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void EvaluateHermiteVectorSegment(f32 dur, f32 t, f32 k, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, Vec02* pos, Vec02* vel, Vec02* acc);
s32 FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);


s32 AddTargetObstructionCost(f32 limit, BaseObject* self, void* a1, void* a2, void* pa, void* pb, Vec02* pc, void* pd, Vec02* pe)
{
    Vec02 lo;
    Vec02 hi;
    Vec02 p;
    Vec02 q;
    TargetSpanHit hit;
    s32 n0;
    Collider** n1;
    PushBackMemoryMark();
    if (pe != 0) {
        Vu0::Q(lo) = Vu0::Min(Vu0::Q(*(Vec02*)pa), Vu0::Min(Vu0::Q(*pc), Vu0::Q(*pe)));
        Vu0::Q(hi) = Vu0::Max(Vu0::Q(*(Vec02*)pa), Vu0::Max(Vu0::Q(*pc), Vu0::Q(*pe)));
    } else {
        lo = *(Vec02*)pa;
        hi = *pc;
    }
    GatherCollidersInBox(self->world, (Collider*)self, &lo, &hi, (s32 (*)(void*, Collider*))a1, a2, &n0, &n1);
    f32 t = 0.0f;
    for (;;) {
        EvaluateHermiteVectorSegment(limit, t, 1.0f, (const Vec02*)pa, (const Vec02*)pb, pc, (const Vec02*)pd, &q, 0, 0);
        if (t != 0.0f) {
            if (FindNearestSpanObject(0, &p, &q, n0, n1, (ColliderSpan*)&hit) != 0) {
                if (100.0f < Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(hit.point), Vu0::Q(*pc))))) {
                    break;
                }
            }
        }
        p = q;
        if (t == limit) {
            break;
        }
        t = limit <? (t + 0.1f);
    }
    if (pe != 0) {
        if (FindNearestSpanObject(0, &p, pe, n0, n1, (ColliderSpan*)&hit) != 0) {
            if (hit.f44 != 1.0f) {
                if (50.0f < Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(hit.point), Vu0::Q(*pe))))) {
                    t = limit - 1.0f;
                }
            }
        }
    }
    PopBackMemoryMark();
    return t < limit;
}

f32 AddRepeatTargetPenalty(Player* self, void* target, f32 a, f32 b)
{
    f32 r = a + b;
    if (target == self->penalizedTarget) {
        r = r + D_00274E3C;
    }
    return r;
}

// ChoosePlayerTargetByCost: the six candidate searches (objects, paths, class 0x75, target
// vectors, points, curves), the cheapest kept, and the player's record and state set from it.
extern f32 D_00262E24;
extern s32 g_codeChecksumFailed;

struct TargetShape;
struct TargetShapeDesc {
    u8 pad00[8];
    void (*m2)(TargetShape* self, Vec02* out, f32 t, s32 a);           // 0x08
    u8 pad0C[0x14 - 0x0C];
    f32 (*m5)(TargetShape* self, f32 t);                               // 0x14
    f32 (*m6)(TargetShape* self, f32 t);                               // 0x18
    u8 pad1C[0x20 - 0x1C];
    f32 (*m8)(TargetShape* self);                                      // 0x20
    u8 pad24[0x28 - 0x24];
    void (*m10)(TargetShape* self, Vec02* in, s32 a, Vec02* out, s32 b, f32* t, f32* u); // 0x28
};
struct TargetShape { TargetShapeDesc* desc; };

// The candidates: their frame at 0x18, their shape at 0x34 and the heights over the player
// they are taken within.
struct TargetCand {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    TargetShape* shape;     // 0x34
    TargetCand* next38;     // 0x38
    u8 pad3C[0x40 - 0x3C];
    union {
        Vec02 v40;          // 0x40
        struct {
            u8 pad40[0xC];
            f32 f4C;        // 0x4C
        };
    };
    TargetCand* next50;     // 0x50
    u8 pad54[0x58 - 0x54];
    f32 f58;                // 0x58
    f32 f5C;                // 0x5C
    u8 pad60[0x70 - 0x60];
    f32 f70;                // 0x70
    u8 pad74[0x80 - 0x74];
    TargetCand* next80;     // 0x80
    u8 pad84[0x88 - 0x84];
    u32 flags88;            // 0x88
    u8 pad8C[0xB4 - 0x8C];
    f32 fB4;                // 0xB4
};
struct TargetWorld { u8 pad0[0x1C84]; TargetCand* objects; u8 pad1C88[0x1C90 - 0x1C88]; TargetCand* paths; };
struct TargetRecord { u8 pad0[0x18]; f32 time; u8 pad1C[4]; Vec02 a; Vec02 b; };
struct Chooser {
    u8 pad0[0x14];
    TargetWorld* world;     // 0x14
    u8 pad18[0x100 - 0x18];
    Vec02 pos;              // 0x100
    u8 pad110[0x140 - 0x110];
    Vec02 v140;             // 0x140
    Vec02 v150;             // 0x150
    u8 pad160[0x358 - 0x160];
    f32 f358;               // 0x358
    u8 pad35C[0x6D4 - 0x35C];
    void* f6D4;             // 0x6D4
    u8 pad6D8[0x2200 - 0x6D8];
    void* f2200;            // 0x2200
    void* aimObject;        // 0x2204
    void* aimVector;        // 0x2208
    f32 aimVectorPlace;     // 0x220C
    void* lastAimObject;    // 0x2210
    u8 pad2214[0x2228 - 0x2214];
    s32 subState;           // 0x2228
    u8 pad222C[0x23A0 - 0x222C];
    void* targetCurve;      // 0x23A0
    f32 targetCurvePlace;   // 0x23A4
    void* targetPoint;      // 0x23A8
    f32 targetPointPlace;   // 0x23AC
    u8 pad23B0[0x23B8 - 0x23B0];
    void* targetObject;     // 0x23B8
    void* targetPath;       // 0x23BC
    f32 targetPathPlace;    // 0x23C0
    f32 f23C4;              // 0x23C4
    u8 pad23C8[0x2514 - 0x23C8];
    TargetRecord* aimRecord; // 0x2514
};
// What a cost search hands its scorer: the player, the target, and the point at +0x10.
struct CostContext { Chooser* self; void* target; u8 pad08[8]; Vec02 v; };
// What ScoreTargetPathAt reads: the player, a frame, and a point in that frame.
struct PathArgs { Chooser* self; void* frame; u8 pad08[8]; Vec02 c; };
// What ScoreTargetPathNearest reads: the player and the vector target.
struct NearestContext { Chooser* self; void* target; };


void ComputeUpwardBoostVelocity(PlacedObject* self, Vec02* out);
void ScorePlayerTargetPlacement(Player* self, Vec02* point, BaseObject* obj, Vec02* start, Vec02* extra, f32* outTime, f32* outCost, Vec02* outPoint, Vec02* outVel);
f32 AddRepeatTargetPenalty(Player* self, void* target, f32 a, f32 b);
s32 AddTargetObstructionCost(f32 limit, BaseObject* self, void* a1, void* a2, void* pa, void* pb, Vec02* pc, void* pd, Vec02* pe);
f32 GetPathCurveSearchStep(PathCurve* self);
void FindLocalMinimum(MinimumFn fn, void* ctx, f32 x, f32 step, f32 lo, f32 hi, f32* outX, f32* outY);
void PlaceOnTargetObject(Player* self, PathTarget* node, Vec02* outA, Vec02* outB, f32 t);
void ScorePlayerLeapToPoint(Player* self, BaseObject* obj, Vec02* point, f32* out1, Vec02* out2, Vec02* out3, f32 t);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void PlaceOnTargetPoint(TargetPoint* self, Vec02* out, f32* angleOut, f32 t);
void PlaceOnTargetCurve(TargetCurve* self, Vec02* out, f32* angleOut, f32 t);
f32 RandomFloatInRange(f32 a, f32 b);
void SetPlayerAimMode(Player* self, s32 state);
void UpdatePlayerAimTarget(Player* s);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// The squared distance between two points, and the distance.
static inline f32 DistanceSquared(const Vec02& a, const Vec02& b)
{
    Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(a), Vu0::Vec::Of(b));
    return Vu0::ToFloatMoved(Vu0::Dot(d, d));
}

static inline f32 Distance(const Vec02& a, const Vec02& b)
{
    return Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(b))));
}

s32 ChoosePlayerTargetByCost(Chooser* self, TargetCand* keep)
{
    Vec02 cur0;
    Vec02 best0;
    Vec02 cur1;
    Vec02 best1;
    Vec02 from;
    Vec02 at;
    f32 t;
    f32 cost;
    f32 tPath;
    f32 tPathBest;
    f32 tVector;
    f32 tVectorBest;
    f32 tPoint;
    f32 tCurve;
    f32 tCurveBest;
    s32 kind = -1;
    TargetCand* bestObject;
    TargetCand* bestPath;
    TargetCand* bestPoint;
    TargetCand* bestCurve;
    TargetCand* bestClass75;
    TargetCand* bestVector;
    f32 bestCost;
    f32 bestT;
    f32 bestPathT;
    f32 bestPointT;
    f32 bestCurveT;
    f32 bestVectorT;
    TargetCand* o;

    if (keep != 0) {
        bestCost = -3.40282347e+38f;
    } else {
        bestCost = 3.40282347e+38f;
    }
    bestT = 0.0f;
    ComputeUpwardBoostVelocity((PlacedObject*)self, &from);
    for (o = self->world->objects; o != 0; o = o->next50) {
        ConvertPositionToWorld((BaseObject*)o, &at);
        if (o != keep && o->f58 < self->pos.z - at.z) {
            continue;
        }
        ScorePlayerTargetPlacement((Player*)self, &from, (BaseObject*)o->frame, &at, 0, &t, &cost, &cur0, &cur1);
        cur1.z = from.z + t * self->f358;
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty((Player*)self, o, cost, D_00274E24);
            if (bestCost <= cost) {
                continue;
            }
            if (AddTargetObstructionCost(t, (BaseObject*)self, 0, 0, self->f6D4, &from, &cur0, &cur1, 0)) {
                continue;
            }
        }
        best0 = cur0;
        best1 = cur1;
        bestObject = o;
        kind = 3;
        bestCost = bestCost <? cost;
        bestT = t;
    }
    for (TargetCand* path = self->world->paths; path != 0; path = path->next38) {
        Vec02 at2;
        CostContext ctx;
        Vec02 q;
        TransformPointBetweenFrames(0, (PlacedObject*)path->frame, (Vec02*)self->f6D4, &at);
        if (path->shape->desc->m10) {
            path->shape->desc->m10(path->shape, &at, 0, &at2, 0, &tPath, 0);
        }
        TransformPointBetweenFrames((PlacedObject*)path->frame, 0, &at2, &at2);
        if (path != keep && path->f4C < self->pos.z - at2.z) {
            continue;
        }
        ctx.self = self;
        ctx.target = path;
        ctx.v = from;
        CostContext* c = &ctx;
        f32 start = tPath;
        f32 step = GetPathCurveSearchStep((PathCurve*)path->shape);
        f32 lo = path->shape->desc->m6(path->shape, D_00274E04);
        FindLocalMinimum((MinimumFn)ScoreTargetObjectAt, c, start, step, lo,
                         path->shape->desc->m6(path->shape, path->shape->desc->m8(path->shape) - D_00274E04),
                         &tPathBest, &cost);
        if (path != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty((Player*)self, path, cost, D_00274E28);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetObject((Player*)self, (PathTarget*)path, &at2, &q, tPathBest);
        ScorePlayerTargetPlacement((Player*)self, &from, (BaseObject*)path->frame, &at2, &q, &t, 0, &cur0, &cur1);
        cur1.z = from.z + t * self->f358;
        if (path != keep && AddTargetObstructionCost(t, (BaseObject*)self, 0, 0, self->f6D4, &from, &cur0, &cur1, 0)) {
            continue;
        }
        best0 = cur0;
        best1 = cur1;
        bestPath = path;
        kind = 4;
        bestCost = bestCost <? cost;
        bestT = t;
        bestPathT = tPathBest;
    }
    for (o = (TargetCand*)g_class75List.head; o != 0; o = o->next80) {
        if (o != keep) {
            if (keep != 0) {
                continue;
            }
            if (o == self->lastAimObject) {
                continue;
            }
            if ((o->flags88 & 1) == 0) {
                continue;
            }
            if (!IsObjectOfKind((BaseObject*)o, 0x76)) {
                continue;
            }
        }
        GetObjectWorldPosition((BaseObject*)o, &at);
        if (o != keep) {
            if (o->fB4 < self->pos.z - at.z) {
                continue;
            }
            s32 far = D_00274E0C * D_00274E0C < DistanceSquared(at, self->v140);
            if (far) {
                continue;
            }
        }
        PathArgs args;
        Vec02 p;
        args.self = self;
        args.frame = o->frame;
        args.c = o->v40;
        FindLocalMinimum((MinimumFn)ScoreTargetPathAt, &args, 0.5f, 0.25f, 0.25f, 3.0f, &t, &cost);
        ScorePlayerLeapToPoint((Player*)self, (BaseObject*)args.frame, &args.c, 0, &cur0, &cur1, t);
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty((Player*)self, o, cost, D_00274E2C);
            if (bestCost <= cost) {
                continue;
            }
            TransformPointBetweenFrames((PlacedObject*)args.frame, 0, &args.c, &p);
            if (AddTargetObstructionCost(t, (BaseObject*)self, 0, 0, &self->v140, &self->v150, &cur0, &cur1, &p)) {
                continue;
            }
        }
        best0 = cur0;
        best1 = cur1;
        best0.z -= 75.0f;
        bestClass75 = o;
        kind = 6;
        bestCost = cost <? bestCost;
        bestT = t;
    }
    for (o = (TargetCand*)g_targetVectors.list.head; o != 0; o = o->next38) {
        Vec02 at2;
        NearestContext near;
        PathArgs args;
        Vec02 p;
        TransformPointBetweenFrames(0, (PlacedObject*)o->frame, &self->v140, &at);
        if (o->shape->desc->m10) {
            o->shape->desc->m10(o->shape, &at, 0, &at2, 0, 0, &tVector);
        }
        TransformPointBetweenFrames((PlacedObject*)o->frame, 0, &at2, &at2);
        if (o != keep) {
            if (o->f5C < self->pos.z - at2.z) {
                continue;
            }
            s32 far = D_00274E0C < Distance(at2, self->v140);
            if (far) {
                continue;
            }
        }
        NearestContext* n = &near;
        near.self = self;
        near.target = o;
        f32 start = tVector;
        FindLocalMinimum((MinimumFn)ScoreTargetPathNearest, n, start, 100.0f, 50.0f, o->shape->desc->m8(o->shape) - 50.0f,
                         &tVectorBest, &cost);
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty((Player*)self, o, cost, D_00274E30);
            if (bestCost <= cost) {
                continue;
            }
        }
        args.self = self;
        args.frame = o->frame;
        if (o->shape->desc->m2) {
            o->shape->desc->m2(o->shape, &args.c, tVectorBest, 0);
        }
        FindLocalMinimum((MinimumFn)ScoreTargetPathAt, &args, 0.5f, 0.25f, 0.25f, 3.0f, &t, 0);
        ScorePlayerLeapToPoint((Player*)self, (BaseObject*)args.frame, &args.c, 0, &cur0, &cur1, t);
        if (o != keep) {
            TransformPointBetweenFrames((PlacedObject*)o->frame, 0, &args.c, &p);
            if (AddTargetObstructionCost(t, (BaseObject*)self, 0, 0, &self->v140, &self->v150, &cur0, &cur1, &p)) {
                continue;
            }
        }
        best0 = cur0;
        kind = 7;
        best0.z -= 75.0f;
        best1 = cur1;
        bestVector = o;
        bestCost = cost <? bestCost;
        bestT = t;
        bestVectorT = tVectorBest;
    }
    for (o = (TargetCand*)g_targetPointList.head; o != 0; o = o->next50) {
        CostContext ctx;
        Vec02 d;
        // The point and curve searches weigh their cost and test it against the limit, both
        // named here (bound by reference: their %hi parts are formed at the top of the body).
        const f32& weight = D_00274E10;
        const f32& maxCost = D_00274E20;
        ConvertPositionToWorld((BaseObject*)o, &at);
        if (o->f70 < self->pos.z - at.z) {
            continue;
        }
        CostContext* c = &ctx;
        void* fn = (void*)ScoreTargetPointAt;
        Vu0::Set(d, Vu0::Sub(Vu0::Vec::Of(self->v140), Vu0::Vec::Of(at)).q);
        ctx.v = self->v150;
        ctx.self = self;
        ctx.target = o;
        f32 lo = -3.40282347e+38f;
        f32 hi = 3.40282347e+38f;
        FindLocalMinimum((MinimumFn)fn, c, ArctangentOfRatio(d.y, d.x) * o->f5C, D_00274E40, lo, hi, &tPoint, &cost);
        cost = cost * weight;
        if (o != keep) {
            if (cost >= maxCost) {
                continue;
            }
            cost = AddRepeatTargetPenalty((Player*)self, o, cost, D_00274E38);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetPoint((TargetPoint*)o, &at, 0, tPoint);
        ScorePlayerTargetPlacement((Player*)self, &self->v150, (BaseObject*)o->frame, &at, 0, &t, 0, &cur0, &cur1);
        cur1.z = self->v150.z + t * self->f358;
        if (o != keep && AddTargetObstructionCost(t, (BaseObject*)self, 0, 0, self->f6D4, &self->v150, &cur0, &cur1, 0)) {
            continue;
        }
        best0 = cur0;
        best1 = cur1;
        bestPoint = o;
        kind = 1;
        bestCost = cost <? bestCost;
        bestT = t;
        bestPointT = tPoint;
    }
    for (o = (TargetCand*)g_targetCurveList.head; o != 0; o = o->next38) {
        Vec02 at2;
        CostContext ctx;
        const f32& weight = D_00274E10;
        const f32& maxCost = D_00274E20;
        TransformPointBetweenFrames(0, (PlacedObject*)o->frame, (Vec02*)self->f6D4, &at);
        if (o->shape->desc->m10) {
            o->shape->desc->m10(o->shape, &at, 0, &at2, 0, 0, &tCurve);
        }
        TransformPointBetweenFrames((PlacedObject*)o->frame, 0, &at2, &at2);
        if (o->f58 < self->pos.z - at2.z) {
            continue;
        }
        CostContext* c = &ctx;
        ctx.self = self;
        ctx.v = self->v150;
        ctx.target = o;
        f32 start = tCurve;
        FindLocalMinimum((MinimumFn)ScoreTargetCurveAt, c, start, D_00274E44, 30.0f, o->shape->desc->m8(o->shape) - 30.0f,
                         &tCurveBest, &cost);
        cost = cost * weight;
        if (o != keep) {
            if (cost >= maxCost) {
                continue;
            }
            cost = AddRepeatTargetPenalty((Player*)self, o, cost, D_00274E34);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetCurve((TargetCurve*)o, &at2, 0, tCurveBest);
        ScorePlayerTargetPlacement((Player*)self, &self->v150, (BaseObject*)o->frame, &at2, 0, &t, 0, &cur0, &cur1);
        cur1.z = self->v150.z + t * self->f358;
        if (o != keep && AddTargetObstructionCost(t, (BaseObject*)self, 0, 0, self->f6D4, &self->v150, &cur0, &cur1, 0)) {
            continue;
        }
        bestCost = cost <? bestCost;
        best0 = cur0;
        best1 = cur1;
        bestCurve = o;
        kind = 0;
        bestT = t;
        bestCurveT = tCurveBest;
    }
    if (g_codeChecksumFailed != 0 && g_gameClock.time > RandomFloatInRange(30.0f, 120.0f)) {
        return self->subState;
    }
    s32 state;
    switch (kind) {
    case 3:
        self->targetObject = bestObject;
        state = 0xA;
        break;
    case 4:
        self->targetPath = bestPath;
        self->targetPathPlace = bestPathT;
        self->f23C4 = bestPath->shape->desc->m5(bestPath->shape, bestPathT);
        state = 0xB;
        break;
    case 1:
        self->targetPoint = bestPoint;
        self->targetPointPlace = bestPointT;
        state = 0xD;
        break;
    case 0:
        self->targetCurve = bestCurve;
        self->targetCurvePlace = bestCurveT;
        state = 0xC;
        break;
    case 6:
        self->aimVector = 0;
        self->aimObject = bestClass75;
        self->f2200 = bestClass75;
        SetPlayerAimMode((Player*)self, 0);
        UpdatePlayerAimTarget((Player*)self);
        state = 0xE;
        break;
    case 7:
        self->aimVector = bestVector;
        self->aimVectorPlace = bestVectorT;
        self->aimObject = 0;
        self->f2200 = 0;
        SetPlayerAimMode((Player*)self, 0);
        UpdatePlayerAimTarget((Player*)self);
        state = 0xF;
        break;
    default:
        StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E24, 0.0f, 0.0f, 0, 0);
        state = self->subState;
        break;
    }
    TargetRecord* r = self->aimRecord;
    r->time = g_gameClock.time + bestT;
    self->aimRecord->a = best0;
    self->aimRecord->a.z += 75.0f;
    self->aimRecord->b = best1;
    return state;
}

// What func_001D0B20 reads: the player's record at +0x23BC (a frame at +0x18 and a mover at
// +0x34), the angle at +0x23C4 and its flip flag at +0x23C8, and the target (a flag at +0x04,
// the radius at +0x08, a point at +0x10, a pair of points at +0x20).
struct TargetMover {
    struct Vt { u8 pad0[4]; void (*placeAt)(TargetMover* self, f32 angle, s32 flag, void* out); void (*place)(TargetMover* self, f32 angle, void* out, s32 flag); u8 pad0C[0x20 - 0x0C]; f32 (*limit)(TargetMover* self); u8 pad24[0x28 - 0x24]; void (*nearest)(TargetMover* self, void* pos, s32 a, void* b, void* dir, void* c, f32* t); void (*track)(TargetMover* self, f32 angle, void* pos, s32 zero, void* dir, void* up, f32* angleOut, f32* limitOut); };
    const Vt* vt;           // 0x00
    u8 pad04[4];
    s32 wraps;              // 0x08
    s32 count;              // 0x0C
    const f32* ends;        // 0x10: the angles the mover's pieces end at (func_001CFFD0 reads the last)
    const f32* low;         // 0x14: the angles the mover's pieces start at
};
// func_001D12F0 reads the record's active flag (+0x40), its limit (+0x44) and scale (+0x48), and
// the player's float at +0x23C0.
struct TargetFrameRecord {
    u8 pad0[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    TargetMover* mover;     // 0x34
    u8 pad38[0x40 - 0x38];
    s32 active;             // 0x40
    f32 limit;              // 0x44
    f32 scale;              // 0x48
    u8 pad4C[0x50 - 0x4C];
    u32 sides;              // 0x50: bits 0 and 1, the sides func_001CFFD0 may leave it by
    u8 pad54[0x58 - 0x54];
    TargetFrameRecord* facing;  // 0x58: a record whose direction func_001CFFD0 faces instead
};

// The phase clip a player's sub-states 0x11 and 0x14 advance (+0x2230): its clip, whose length
// is at +0x34, the time and the speed.
struct PhaseClip {
    u8 pad00[0x34];
    f32 length;             // 0x34
};
struct PhasePlayer {
    u8 pad00[8];
    PhaseClip* clip;        // 0x08
    u8 pad0C[0x14 - 0x0C];
    f32 time;               // 0x14
    f32 speed;              // 0x18
};

void FindTargetCurveLengthNearCollider(TargetCurve* self, f32* out, void* a2, void* a3);
void PlaceTargetPointNearCollider(TargetPoint* self, Vec02* out, f32* angleOut);
void FindRingPointTowardCollider(PlacedObject* self, Vec02* out, f32* angleOut);
u128 ApproachPointWithRamp(u128 from, u128 to, f32 dt, RampProfile* ramp, Vec02* vel);
void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 WrapAngle(f32 a);
void SetPlayerOnOffPhase(Player* self, s32 n);
struct BlendAnimationView;
struct TurnBlendRecords;
struct TurningCollider;
void SetPlayerBlendWeights(f32 f12, f32 f13, TurningCollider* a0, TurnBlendRecords* a1, BlendAnimationView* a2);
s32 AimPlayerAtTarget(Player* self);
void SetPlayerState(Player* self, s32 a, s32 b);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
extern f32 g_frameDt;

// v made unit length, or fallback when shorter than 0.0001 (as player_path.cpp's).
static inline Vu0::Vec NormalizeOrElse(Vu0::Vec v, Vu0::Vec fallback)
{
    u128 len = Vu0::Length(v.q);
    Vu0::Vec r;
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        r = fallback;
    } else {
        r.q = Vu0::DivX(v.q, len);
    }
    return r;
}

// The player's control on a target (sub-state at +0x239C): on a curve, point or part (0, 1) it
// eases toward the target's point and turns about it, on a record (4) it follows the record's
// mover, and every case ends in SetPlayerState. The locals are the function's own and shared
// between the cases, as retail's frame shows (0x00 to 0x90, then the four floats): b and i also
// serve as ramp profiles, k as the stack slot of the scale vectors, stored after their products.
void ControlPlayerOnTarget(Player* self, PadRecord* pad)
{
    Vec02 a;
    Vec02 b;
    Vec02 c;
    Vec02 d;
    Vec02 e;
    Vec02 f;
    Vec02 k;
    Vec02 h;
    Vec02 i;
    Vec02 j;
    f32 heading;
    f32 lo;
    f32 hi;
    f32 end;
    s32 mode = self->f2220;
    s32 sub = self->subState;
    switch (self->targetMode) {
    case 0:
    case 1: {
        if (self->targetCurve != 0) {
            FindTargetCurveLengthNearCollider((TargetCurve*)self->targetCurve, &self->targetCurvePos, &a, &heading);
        } else if (self->targetPoint != 0) {
            PlaceTargetPointNearCollider((TargetPoint*)self->targetPoint, &a, &heading);
        } else {
            FindRingPointTowardCollider((PlacedObject*)self->heldObject, &a, &heading);
        }
        f32 speed;
        if (self->targetMode == 0) {
            speed = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(*(Vec02*)((u8*)self + 0xAB0)))) *
                    ((PhasePlayer*)self->stateAnimPlayer)->speed;
        } else {
            speed = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(*(Vec02*)((u8*)self + 0xB80)))) *
                    ((PhasePlayer*)self->stateAnimPlayer)->speed;
        }
        a.z = self->pos.z;
        b.x = speed;
        b.y = 0.0f;
        b.z = D_00274E48;
        ApproachPointWithRamp(Vu0::Q(self->pos), Vu0::Q(a), g_gameClock.dt, (RampProfile*)&b, &c);
        f32 turn;
        if (self->targetMode == 0) {
            turn = heading + 1.57079637f;
        } else {
            turn = heading - 1.57079637f;
        }
        ComputePolarOffset((Vec3*)&d, turn, 1.0f, 0.0f);
        ComputePolarOffset((Vec3*)&e, self->stickHeading, 1.0f, 0.0f);
        f32 cosine = D_00274E50 * Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d), Vu0::Q(e)));
        f32 side;
        side = ClampBetween(cosine, -1.0f, 1.0f);
        side = side * self->stickLevel;
        if (__builtin_fabsf(side) < 0.2f) {
            side = 0.0f;
        }
        f32 v = side * speed;
        v = Fpu::Sqrt(speed * speed - Vu0::ToFloat(Vu0::Dot(Vu0::Q(c), Vu0::Q(c)))) <? v;
        f32 t;
        if (self->targetCurve != 0 && ((TargetFrameRecord*)self->targetCurve)->mover->wraps == 0) {
            ApproachValueWithRamp(self->targetCurvePos, 30.0f, g_gameClock.dt, (RampProfile*)&b, &lo);
            TargetMover* m = ((TargetFrameRecord*)self->targetCurve)->mover;
            ApproachValueWithRamp(self->targetCurvePos, m->low[m->count - 1] - 30.0f, g_gameClock.dt, (RampProfile*)&b, &hi);
            t = ClampBetween(v, lo, hi);
        } else {
            t = v;
        }
        Vu0::Vec s = Vu0::Vec::FromFloat(t);
        Vu0::Q(f) = Vu0::MulX(Vu0::Q(d), s.q);
        u128 vel = Vu0::Q(c);
        u128 local = Vu0::RotateTransposed(self->headingMatrix, Vu0::Add(vel, Vu0::Q(f)));
        *(Vu0::Vec*)&k = s;
        Vu0::Vec n = Vu0::Vec::FromFloat(-1.0f);
        u128 drive = Vu0::MulX(local, n.q);
        *(Vu0::Vec*)&k = n;
        *(Vu0::Vec*)&self->headingVelocity = *(Vu0::Vec*)&drive;
        if (D_00274E4C < Vu0::ToFloat(Vu0::Length(drive))) {
            sub = 0x11;
            if (self->targetMode == 0) {
                if (45.0f < Vu0::ToFloat(Vu0::Length(vel))) {
                    SetPlayerOnOffPhase(self, 0);
                } else if (20.0f < self->headingVelocity.y) {
                    SetPlayerOnOffPhase(self, 2);
                } else if (self->headingVelocity.y < -20.0f) {
                    SetPlayerOnOffPhase(self, 1);
                }
            }
        } else {
            sub = 0x10;
            if (v < -D_00274E4C && (((TargetFrameRecord*)self->targetCurve)->sides & 1)) {
                sub = self->targetMode == 0 ? 0x13 : 0x12;
            } else if (D_00274E4C < v && (((TargetFrameRecord*)self->targetCurve)->sides & 2)) {
                sub = self->targetMode == 0 ? 0x12 : 0x13;
            }
            if (self->targetMode == 0) {
                SetPlayerOnOffPhase(self, 3);
            }
        }
        self->f638 = heading;
        if (self->subState == 0x15) {
            f32 off = __builtin_fabsf(WrapAngle(ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x) - self->f638));
            if (D_00274E54 < off) {
                sub = 0x15;
            }
        }
        break;
    }
    case 2:
        if (self->subState == 0x10 || self->subState == 0x14) {
            if (0.0f < self->stickLevel) {
                sub = 0x14;
                SetPlayerBlendWeights(self->stickHeading, self->stickLevel, self, (TurnBlendRecords*)((u8*)self + 0xC40), *(BlendAnimationView**)((u8*)self + 0xE20));
            } else {
                Vu0::Q(self->headingVelocity) = Vu0::Zero();
                sub = 0x10;
            }
        }
        break;
    case 3:
        if (MaskWorldBitsBySave() & 0x2000) {
            if (0.0f < self->stickLevel) {
                sub = 0x14;
                SetPlayerBlendWeights(self->stickHeading, self->stickLevel * D_00274E58, self, (TurnBlendRecords*)((u8*)self + 0x720), self->sixWayBlend);
            } else {
                Vu0::Q(self->headingVelocity) = Vu0::Zero();
                sub = 0x10;
            }
        } else {
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            sub = 0x10;
        }
        break;
    case 5:
        self->f638 = self->stickHeading;
        Vu0::Q(self->headingVelocity) = Vu0::Zero();
        break;
    case 4: {
        TargetFrameRecord* rec = (TargetFrameRecord*)self->targetTrack;
        void* frame = rec->frame;
        TargetMover* m = rec->mover;
        TransformPointBetweenFrames(0, (PlacedObject*)frame, (Vec02*)self->probeVertex, &a);
        if (m->vt->track != 0) {
            m->vt->track(m, self->trackPos, &a, 0, &b, &c, &self->trackPos, &self->f23C4);
        }
        TransformPointBetweenFrames((PlacedObject*)frame, 0, &b, &d);
        TransformDirectionBetweenFrames((PlacedObject*)frame, 0, &c, &e);
        if (rec->active != 0 && m->wraps == 0) {
            if (self->trackPos <= 0.0f || m->ends[m->count - 1] <= self->trackPos) {
                mode = 2;
                sub = 2;
                break;
            }
        }
        e.z = 0.0f;
        *(Vu0::Vec*)&e = NormalizeOrElse(Vu0::Vec::Of(e), Vu0::Vec::Of(g_unitXVector));
        f32 angle = ArctangentOfRatio(e.y, e.x);
        ComputePolarOffset((Vec3*)&h, self->stickHeading, 1.0f, 0.0f);
        if (rec->facing == 0) {
            f = e;
        } else {
            void* frame2 = rec->facing->frame;
            TransformPointBetweenFrames(0, (PlacedObject*)frame2, (Vec02*)self->probeVertex, &i);
            TargetMover* m2 = rec->facing->mover;
            if (m2->vt->nearest != 0) {
                m2->vt->nearest(m2, &i, 0, 0, &j, 0, 0);
            }
            TransformDirectionBetweenFrames((PlacedObject*)frame2, 0, &j, &f);
        }
        f.z = 0.0f;
        *(Vu0::Vec*)&f = NormalizeOrElse(Vu0::Vec::Of(f), Vu0::Vec::Of(g_unitXVector));
        f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(h), Vu0::Q(f)));
        switch (self->pathStickSide) {
        case 0:
            if (self->stickLevel < 0.25f) {
                self->pathStickSide = -1;
            } else if (along < -0.7f) {
                self->pathStickSide = 1;
            }
            break;
        case 1:
            if (self->stickLevel < 0.25f) {
                self->pathStickSide = -1;
            } else if (0.7f < along) {
                self->pathStickSide = 0;
            }
            break;
        case -1:
            if (0.35f < pad->stickMagnitude) {
                if (0.0f <= along) {
                    self->pathStickSide = 0;
                } else {
                    self->pathStickSide = 1;
                }
            }
            break;
        }
        switch (self->pathStickSide) {
        case 0:
            self->trackReversed = 0;
            break;
        case 1:
            self->trackReversed = 1;
            break;
        }
        if (rec->active != 0) {
            along = 0.0f;
        } else {
            i.y = -*(f32*)((u8*)self + 0xE40);
            i.x = -*(f32*)((u8*)self + 0xE90);
            i.z = D_00274E5C;
            if (m->wraps != 0) {
                end = i.x;
            } else if (self->trackReversed != 0) {
                ApproachValueWithRamp(self->f23C4, D_00274E04, g_frameDt, (RampProfile*)&i, &end);
                end = -end;
            } else {
                ApproachValueWithRamp(self->f23C4, m->vt->limit(m) - D_00274E04, g_frameDt, (RampProfile*)&i, &end);
            }
            f32 r = (end - i.y) / (i.x - i.y);
            along = ClampBetween(self->stickLevel, 0.0f, r);
        }
        if (self->trackReversed != 0) {
            angle = WrapAngle(angle + 3.14159274f);
        }
        if (0.0f < along) {
            sub = 0x14;
            SetPlayerBlendWeights(angle, along, self, (TurnBlendRecords*)((u8*)self + 0xE30), *(BlendAnimationView**)((u8*)self + 0x1010));
        } else {
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->f638 = angle;
            sub = 0x10;
        }
        break;
    }
    case 6:
        AimPlayerAtTarget(self);
    default:
        Vu0::Q(self->headingVelocity) = Vu0::Zero();
        break;
    }
    SetPlayerState(self, mode, sub);
}

struct TargetPlayerView { u8 pad0[0x23BC]; TargetFrameRecord* record; f32 targetPathPlace; f32 angle; s32 flip; };
struct TargetProbe { u8 pad0[4]; s32 active; f32 radius; u8 pad0C[4]; Vec02 point; Vec02 end; };

f32 WrapModulo(f32 x, f32 y);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
s32 CollectBoundsSpans(Vec02* p, Vec02* a, Vec02* b, f32 radius, s32 count, ColliderSpan* out);


void CollectPlayerTargetSpans(TargetPlayerView* self, TargetProbe* t, u8* out)
{
    Vec02 pos;
    Vec02 local;
    ColliderSpan span;
    if (t->active == 0) {
        *(Vec02*)(out + 0x20) = D_00248D30;
        return;
    }
    TargetFrameRecord* rec = self->record;
    TargetMover* m = rec->mover;
    void* frame = rec->frame;
    f32 off = t->point.x;
    if (self->flip != 0) {
        off = -off;
    }
    f32 limit = m->vt->limit(m);
    f32 angle;
    if (m->wraps != 0) {
        angle = WrapModulo(self->angle + off, limit);
    } else {
        angle = ClampBetween(self->angle + off, *m->low, limit);
    }
    if (m->vt->place != 0) {
        m->vt->place(m, angle, &pos, 0);
    }
    TransformPointBetweenFrames((PlacedObject*)frame, (PlacedObject*)self, &pos, &local);
    if (CollectBoundsSpans(&t->end, &t->point, &local, t->radius, 1, &span) > 0) {
        Vu0::Q(*(Vec02*)(out + 0x20)) = Vu0::Sub(Vu0::Q(span.q[1]), Vu0::Q(t->point));
    }
}


extern f32 D_00274B64;
struct BlendSlot;
void UpdateEightEntryBlendWeights(Player* self, BlendSlot* slots, BlendAnimationView* gr);
void UpdateSixEntryBlendWeights(TurningCollider* p, void* e, BlendAnimationView* g, void* a3);
void PlayPhaseCrossingSound(Player* self, f32* p, f32 f);
void MeasurePlayerFootProbe(void* self, s32 a, s32 b, void* part, f32 k, void* d);

void UpdatePlayerTargetPhase(Player* self)
{
    switch (self->subState) {
    case 0x11: {
        void* slots;
        BlendAnimationView* n;
        void* sounds;
        switch (self->targetMode) {
        case 0:
            slots = (u8*)self + 0xA20;
            n = *(BlendAnimationView**)((u8*)self + 0xB20);
            sounds = (u8*)self + 0x2470;
            break;
        case 1:
            slots = (u8*)self + 0xB30;
            n = *(BlendAnimationView**)((u8*)self + 0xC30);
            sounds = (u8*)self + 0x2480;
            break;
        case 3:
            slots = (u8*)self + 0x910;
            n = self->eightWayBlend;
            sounds = (u8*)self + 0x2450;
            break;
        }
        UpdateEightEntryBlendWeights(self, (BlendSlot*)slots, n);
        PhasePlayer* ph = (PhasePlayer*)self->stateAnimPlayer;
        f32 t = WrapModulo((ph->time + D_00274B64 * ph->speed) / ph->clip->length, 1.0f);
        if (self->forcedOnOffObject == (s32)self->ownOnOffObject) {
            s32 m = self->onOffPhase;
            if (m < 3) {
                if (m > 0) {
                    if (m == 1) *(f32*)&self->f26A0 >?= *(f32*)((u8*)self + 0xA40); else *(f32*)&self->f26A0 >?= *(f32*)((u8*)self + 0xA20);
                }
            }
        }
        PlayPhaseCrossingSound(self, (f32*)sounds, t);
        break;
    }
    case 0x14: {
        switch (self->targetMode) {
        case 4:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0xE30, *(BlendAnimationView**)((u8*)self + 0x1010), self->stateAnimPlayer);
            break;
        case 2:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0xC40, *(BlendAnimationView**)((u8*)self + 0xE20), self->stateAnimPlayer);
            break;
        case 3:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0x720, self->sixWayBlend, self->stateAnimPlayer);
            break;
        }
        PhasePlayer* ph = (PhasePlayer*)self->stateAnimPlayer;
        f32 t = WrapModulo((ph->time + D_00274B64 * ph->speed) / ph->clip->length, 1.0f);
        PlayPhaseCrossingSound(self, (f32*)((u8*)self + 0x2440), t);
        break;
    }
    case 0x10:
        if (self->targetMode == 4) {
            f32 k = 5.0f;
            u8* p1 = (u8*)self + 0x1190;
            MeasurePlayerFootProbe(self, (s32)self->f628, (s32)self->f620, self->footPartA, k, p1);
            u8* p2 = (u8*)self + 0x1290;
            MeasurePlayerFootProbe(self, (s32)self->f62C, (s32)self->f624, self->footPartB, k, p2);
            CollectPlayerTargetSpans((TargetPlayerView*)self, (TargetProbe*)p1, (u8*)self->footPartA);
            CollectPlayerTargetSpans((TargetPlayerView*)self, (TargetProbe*)p2, (u8*)self->footPartB);
        }
        break;
    }
}

// What func_001D0F20 reads besides the record: the anchor at +0x23B8, the angle at +0x23C0
// and the limit at +0x23C4 the mover's track call writes back.
struct ContactPlayerView {
    u8 pad0[0x23B8];
    BaseObject* anchor;     // 0x23B8
    TargetFrameRecord* record;  // 0x23BC
    f32 angle;              // 0x23C0
    f32 limit;              // 0x23C4
};

void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void AddPlayerObjectContacts(Player* self, s32 flags, BaseObject* node, Vec02* origin, Vec02* axis, Vec02* offset);

void PinPlayerToTarget(Player* self)
{
    Vec02 pos;
    Vec02 local;
    Vec02 dir0;
    Vec02 world;
    Vec02 dir;
    Vec02 k;
    ContactPlayerView* p = (ContactPlayerView*)self;
    s32 code;
    switch (self->targetMode) {
    case 5:
        ConvertPositionToWorld((BaseObject*)p->anchor, &pos);
        AddPlayerObjectContacts(self, 0x23, p->anchor, &pos, 0, (Vec02*)self->probeVertex);
        break;
    case 4: {
        TargetFrameRecord* rec = p->record;
        void* frame = rec->frame;
        TargetMover* m = rec->mover;
        TransformPointBetweenFrames(0, (PlacedObject*)frame, (Vec02*)self->probeVertex, &pos);
        if (m->vt->track != 0) {
            m->vt->track(m, p->angle, &pos, 0, &local, &dir0, &p->angle, &p->limit);
        }
        TransformPointBetweenFrames((PlacedObject*)frame, 0, &local, &world);
        TransformDirectionBetweenFrames((PlacedObject*)frame, 0, &dir0, &dir);
        code = 0x22;
        if (p->record->active == 0 && m->wraps == 0) {
            f32 along = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->v150), Vu0::Q(dir)));
            f32 side = -Vu0::ToFloat(Vu0::Dot(Vu0::Rotate(self->rot, Vu0::Q(self->headingVelocity)), Vu0::Q(dir)));
            if (along < -2.0f || side < 2.0f) {
                f32 lim = m->low[0] + D_00274E04;
                if (p->limit < lim) {
                    if (m->vt->place != 0) {
                        m->vt->place(m, lim, &local, 0);
                    }
                    TransformPointBetweenFrames((PlacedObject*)frame, 0, &local, &world);
                    code = 0x2A;
                    goto call;
                }
            }
            if (2.0f < along || -2.0f < side) {
                f32 lim = m->low[m->count - 1] - D_00274E04;
                if (lim < p->limit) {
                    if (m->vt->place != 0) {
                        m->vt->place(m, lim, &local, 0);
                    }
                    TransformPointBetweenFrames((PlacedObject*)frame, 0, &local, &world);
                    Vu0::Q(k) = Vu0::FromFloat(-1.0f);
                    Vu0::Q(dir) = Vu0::MulX(Vu0::Q(dir), Vu0::Q(k));
                    code = 0x2A;
                    goto call;
                }
            }
        }
    call:
        AddPlayerObjectContacts(self, code, (BaseObject*)p->record, &world, &dir, (Vec02*)self->probeVertex);
        break;
    }
    }
}

void FreePooledContactChain(World* world, Contact03* head);

void SetPlayerOnOffPhase(Player* self, s32 n)
{
    if (n == self->onOffPhase) {
        return;
    }
    self->onOffPhase = n;
    self->onOffPhaseTime = g_gameClock.time;
    self->f26A0 = 0;
    if (n <= 0) {
        return;
    }
    if (n >= 3) {
        if (n == 3) {
            self->f268C = 1;
        }
        return;
    }
    {
        s32 v = self->forcedOnOffObject;
        if (v == (s32)self->ownOnOffObject) {
            self->f268C = 2;
        } else {
            self->f268C = 0;
        }
    }
}

void SetOnOffObjectForcedState(void* selfv, s32 value);

void ResetPlayerOnOffObject(Player* self)
{
    OnOffObject* o = self->ownOnOffObject;
    o->i414 = 5;
    o->f2D4 = 0;
    o->f2DC = 0;
    o->obj = 0;
    o->block2F0 = *(Block63*)&g_onOffObjectDefaults;
    o->f418 = 1;
    o->f388 = 3;
    o->f380 = 0;
    o->f384 = 0;
    o->f41C = 0;
    o->f390 = 0;
    o->f3A0 = 0;
    SetOnOffObjectForcedState(o, 0);
}

void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void AddColliderForce(Player* self, void* v);
void ApplyPlayerDefaultSteering(Player* self);

void StepPlayerAlongTarget(Player* self)
{
    Vec02 dir;
    Vec02 force;
    Vec02 k;
    f32 bounds[2];
    if (self->targetMode == 4) {
        TargetFrameRecord* rec = ((TargetPlayerView*)self)->record;
        if (rec->active != 0) {
            TargetMover* m = rec->mover;
            if (m->vt->placeAt != 0) {
                m->vt->placeAt(m, ((TargetPlayerView*)self)->targetPathPlace, 0, &dir);
            }
            TransformDirectionBetweenFrames((PlacedObject*)rec->frame, 0, &dir, &dir);
            f32 down = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->gravity)));
            f32 along = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->v150)));
            float* ramp = D_00274EF0;
            ApproachValueWithRamp(along, rec->limit, g_gameClock.dt, (RampProfile*)ramp, &bounds[0]);
            ApproachValueWithRamp(along, -rec->limit, g_gameClock.dt, (RampProfile*)ramp, &bounds[1]);
            f32 v = rec->scale * down;
            f32 hi = bounds[0];
            f32 lo = bounds[1];
            if (v < lo) {
                v = lo;
            } else if (hi < v) {
                v = hi;
            }
            Vu0::Q(k) = Vu0::FromFloat(v - down);
            Vu0::Q(force) = Vu0::MulX(Vu0::Q(dir), Vu0::Q(k));
            AddColliderForce(self, &force);
        }
    }
    ApplyPlayerDefaultSteering(self);
}

s32 HasNoActiveObject89(Player* self)
{
    void* arr[64];
    s32 n = GatherObjectsById(self->world, 5, 0x89, 0, 0x40, arr);
    for (s32 i = 0; i < n; i++) {
        ItemKeeper* o = (ItemKeeper*)arr[i];
        s32 v = o->state;
        if (v < 3) {
            if (v > 0) {
                return 0;
            }
        }
    }
    return 1;
}
