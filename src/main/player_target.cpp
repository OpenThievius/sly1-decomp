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
struct C17_1CDFB8 { u8 pad0[0x618]; void* f618; u8 pad61C[0x760 - 0x61C]; s32 f760; };
struct World_1CDFB8 { u8 pad0[0x1CE4]; C17_1CDFB8* f1CE4; u8 pad1CE8[0x2300 - 0x1CE8]; s32 count2300; };
struct Chooser_1CDFB8 {
    u8 pad0[0x14];
    World_1CDFB8* world;            // 0x14
    u8 pad18[0x140 - 0x18];
    Vec02 pos;                      // 0x140
    u8 pad150[0x2200 - 0x150];
    void* f2200;                    // 0x2200
    void* f2204;                    // 0x2204
    void* f2208;                    // 0x2208
    f32 f220C;                      // 0x220C
    void* f2210;                    // 0x2210
    u8 pad2214[0x23A0 - 0x2214];
    void* f23A0;                    // 0x23A0
    f32 f23A4;                      // 0x23A4
    void* f23A8;                    // 0x23A8
    u8 pad23AC[0x23B0 - 0x23AC];
    void* f23B0;                    // 0x23B0
    u8 pad23B4[0x23CC - 0x23B4];
    void* f23CC;                    // 0x23CC
};
extern List01 g_class75List;
void TransformPointBetweenFrames(void* a, void* b, void* c, Vec02* d);
void ConvertPositionToWorld(void* obj, Vec02* out);
s32 IsObjectOfKind(void* obj, s32 kind);
s32 GetObjectWorldPosition(void* obj, Vec02* out);
s32 CompletesWorldBits(s32 bits);
void func_001C61E0(Chooser_1CDFB8* self, s32 mode);
void UpdatePlayerAimTarget(Chooser_1CDFB8* self);
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
        TransformPointBetweenFrames(0, c->parent, &self->pos, &a);
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
        if (o != self->f2210 && (o->flags88 & 1) && (target == 0 || o == target) && IsObjectOfKind(o, 0x76) != 0) {
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
        TransformPointBetweenFrames(0, v->parent, &self->pos, &a);
        TargetShape_1CDFB8* s = v->shape;
        if (s->vtbl[10] != 0) {
            s->vtbl[10](s, &a, 0, &b, 0, 0, &vectorT);
        }
        TransformPointBetweenFrames(v->parent, 0, &b, &b);
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
    if (c != 0 && n >= w->count2300 && CompletesWorldBits(c->f760) == 0) {
        GetObjectWorldPosition(self->world->f1CE4->f618, &a);
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
        self->f23A0 = curve;
        self->f23A4 = curveU;
        break;
    case 1:
        *out = point->mode58;
        r = 0x15;
        self->f23A8 = point;
        break;
    case 2:
        *out = 1;
        r = 0x15;
        self->f23B0 = part;
        break;
    case 6:
        self->f2204 = obj;
        self->f2200 = obj;
        self->f2208 = 0;
        func_001C61E0(self, 0);
        UpdatePlayerAimTarget(self);
        *out = 6;
        r = 0x10;
        break;
    case 7:
        self->f2208 = vector;
        self->f220C = vectorU;
        self->f2204 = 0;
        self->f2200 = 0;
        func_001C61E0(self, 0);
        UpdatePlayerAimTarget(self);
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
        f32 fall = -dz / g;
        f32 tt = fall >? 0.0f;
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
        *(Vu0::Vec*)&vel = Vu0::Add(Vu0::Vec::Of(vel), Vu0::Vec::Of(*extra));
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

typedef void (*PathShapeFn)(void* self, void* out, s32 x);

struct PathShape {
    PathShapeFn* vtbl;
};

struct PathTarget {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1C[0x34 - 0x1C];
    PathShape* f34;
};

typedef f32 (*ShapeScalarFn)(void* self, f32 t);
typedef f32 (*ShapeLimitFn)(void* self);
void TransformDirectionBetweenFrames(void* frame, s32 zero, void* in, void* out);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, RampProfile* p, f32* out);

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
    PathShape* shape = node->f34;
    if (shape->vtbl[1] != 0) {
        shape->vtbl[1](shape, &a, (s32)&b);
    }
    TransformPointBetweenFrames((void*)node->f18, 0, &a, &c);
    TransformDirectionBetweenFrames((void*)node->f18, 0, &b, &d);
    ComputePolarOffset(&e, self->f630, Vu0::ToFloat(Vu0::Length(Vu0::Q(*(Vec02*)((u8*)self + 0xE90)))) * self->f634, 0.0f);
    f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(e), Vu0::Q(d)));
    PathShape* s2 = node->f34;
    f32 value = ((ShapeScalarFn)s2->vtbl[5])(s2, t);
    f.y = -*(f32*)((u8*)self + 0xE40);
    f.x = -*(f32*)((u8*)self + 0xE90);
    f.z = D_00274E1C;
    ApproachValueWithRamp(value, D_00274E04, g_gameClock.dt, (RampProfile*)&f, &lo);
    PathShape* s3 = node->f34;
    ApproachValueWithRamp(value, ((ShapeLimitFn)s3->vtbl[8])(s3) - D_00274E04, g_gameClock.dt, (RampProfile*)&f, &hi);
    *outA = c;
    f32 clamped = ClampBetween(along, lo, hi);
    Vu0::Q(*outB) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(clamped));
}

// What a target cost search passes to its scorer: the player, the target, and the record at
// +0x10 the scorer hands on.
struct TargetCostContext { void* p0; BaseObject* p4; u8 pad1[0x10 - 8]; };
struct ObjectPlacementScore { u8 vecA[0x10]; u8 vecB[0x10]; f32 result; };

void PlaceOnTargetObject(void* a0, void* a1, void* a2, void* a3);
void ScorePlayerTargetPlacement(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 ScoreTargetObjectAt(TargetCostContext* self)
{
    ObjectPlacementScore f;
    PlaceOnTargetObject(self->p0, self->p4, f.vecA, f.vecB);
    ScorePlayerTargetPlacement(self->p0, (u8*)self + 0x10, self->p4->parent, f.vecA, f.vecB, 0, &f.result, 0, 0);
    return f.result;
}

struct PointPlacementScore { u8 vecA[0x10]; f32 result; };

void PlaceOnTargetPoint(void* a0, void* a1, s32 a2);
void ScorePlayerTargetPlacement(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 ScoreTargetPointAt(TargetCostContext* self)
{
    PointPlacementScore f;
    PlaceOnTargetPoint(self->p4, f.vecA, 0);
    ScorePlayerTargetPlacement(self->p0, (u8*)self + 0x10, self->p4->parent, f.vecA, 0, 0, &f.result, 0, 0);
    return f.result;
}

void PlaceOnTargetCurve(void* a0, void* a1, s32 a2);
void ScorePlayerTargetPlacement(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 ScoreTargetCurveAt(TargetCostContext* self)
{
    PointPlacementScore f;
    PlaceOnTargetCurve(self->p4, f.vecA, 0);
    ScorePlayerTargetPlacement(self->p0, (u8*)self + 0x10, self->p4->parent, f.vecA, 0, 0, &f.result, 0, 0);
    return f.result;
}

void TransformPointAtTime(BaseObject* self, BaseObject* top, f32 t, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);
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

void func_001CEB18(Player* self, BaseObject* obj, Vec02* point, f32* out1, Vec02* out2, Vec02* out3, f32 t)
{
    Vec02 pos0;
    Vec02 p;
    Vec02 d;
    Vec02 acc;
    Vec02 vel;
    Vu0::Set(pos0, Vu0::MulAddX2(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Scalar(t), Vu0::Q(self->gravity), Vu0::Scalar(t * (t * 0.5f))));
    p = *point;
    TransformPointAtTime(obj, 0, t, &p, 0, 0, 0);
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
struct PathScoreArgs { s32 a; s32 b; s32 pad[2]; s32 c[4]; };
void func_001CEB18(f32 t, s32 a, s32 b, s32* c, f32* out, s32 d, s32 e);

f32 ScoreTargetPathAt(PathScoreArgs* o, f32 t)
{
    f32 out;
    func_001CEB18(t, o->a, o->b, o->c, &out, 0, 0);
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

void FindLocalMinimum(void* fn, void* b, f32 f12, f32 f13, f32 f14, f32 f15, s32 c, void* out);

f32 ScoreTargetPathNearest(PathScoreContext* self)
{
    PathScoreFrame l;
    PathTarget* n = self->node;
    PathShape* o = n->f34;
    if (o->vtbl[2] != 0) {
        o->vtbl[2](o, &l.a, 0);
    }
    f32 q = 0.25f;
    l.b[0] = self->f0;
    l.b[1] = n->f18;
    l.c = l.a;
    
    FindLocalMinimum((void*)ScoreTargetPathAt, l.b, 0.5f, q, q, 3.0f, 0, &l.out);
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
void GatherCollidersInBox(World* world, BaseObject* self, Vec02* lo, Vec02* hi, void* a, void* b, s32* n0, s32* n1);
void EvaluateHermiteVectorSegment(f32 t, f32 u, f32 v, void* a, void* b, void* c, void* d, Vec02* out, void* e, void* f);
s32 FindNearestSpanObject(s32 zero, Vec02* in, void* out, s32 n0, s32 n1, TargetSpanHit* hit);

s32 AddTargetObstructionCost(f32 limit, BaseObject* self, void* a1, void* a2, void* pa, void* pb, Vec02* pc, void* pd, Vec02* pe)
{
    Vec02 lo;
    Vec02 hi;
    Vec02 p;
    Vec02 q;
    TargetSpanHit hit;
    s32 n0;
    s32 n1;
    PushBackMemoryMark();
    if (pe != 0) {
        Vu0::Q(lo) = Vu0::Min(Vu0::Q(*(Vec02*)pa), Vu0::Min(Vu0::Q(*pc), Vu0::Q(*pe)));
        Vu0::Q(hi) = Vu0::Max(Vu0::Q(*(Vec02*)pa), Vu0::Max(Vu0::Q(*pc), Vu0::Q(*pe)));
    } else {
        lo = *(Vec02*)pa;
        hi = *pc;
    }
    GatherCollidersInBox(self->world, self, &lo, &hi, a1, a2, &n0, &n1);
    f32 t = 0.0f;
    for (;;) {
        EvaluateHermiteVectorSegment(limit, t, 1.0f, pa, pb, pc, pd, &q, 0, 0);
        if (t != 0.0f) {
            if (FindNearestSpanObject(0, &p, &q, n0, n1, &hit) != 0) {
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
        if (FindNearestSpanObject(0, &p, pe, n0, n1, &hit) != 0) {
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

f32 AddRepeatTargetPenalty(Player* self, s32 id, f32 a, f32 b)
{
    f32 r = a + b;
    if (id == self->penalizedTargetId) {
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
    void* f2204;            // 0x2204
    void* f2208;            // 0x2208
    f32 f220C;              // 0x220C
    void* f2210;            // 0x2210
    u8 pad2214[0x2228 - 0x2214];
    s32 f2228;              // 0x2228
    u8 pad222C[0x23A0 - 0x222C];
    void* f23A0;            // 0x23A0
    f32 f23A4;              // 0x23A4
    void* f23A8;            // 0x23A8
    f32 f23AC;              // 0x23AC
    u8 pad23B0[0x23B8 - 0x23B0];
    void* f23B8;            // 0x23B8
    void* f23BC;            // 0x23BC
    f32 f23C0;              // 0x23C0
    f32 f23C4;              // 0x23C4
    u8 pad23C8[0x2514 - 0x23C8];
    TargetRecord* f2514;    // 0x2514
};
// What a cost search hands its scorer: the player, the target, and the point at +0x10.
struct CostContext { Chooser* self; void* target; u8 pad08[8]; Vec02 v; };
// What ScoreTargetPathAt reads: the player, a frame, and a point in that frame.
struct PathArgs { Chooser* self; void* frame; u8 pad08[8]; Vec02 c; };
// What ScoreTargetPathNearest reads: the player and the vector target.
struct NearestContext { Chooser* self; void* target; };


void func_0017FC48(Chooser* self, Vec02* out);
void ScorePlayerTargetPlacement(Chooser* self, Vec02* from, void* frame, Vec02* at, Vec02* at2, f32* t, f32* cost,
                                Vec02* a, Vec02* b);
f32 AddRepeatTargetPenalty(Chooser* self, TargetCand* id, f32 a, f32 b);
s32 AddTargetObstructionCost(f32 limit, Chooser* self, void* a1, void* a2, void* pa, void* pb, Vec02* pc, Vec02* pd,
                             Vec02* pe);
f32 GetPathCurveSearchStep(TargetShape* shape);
void FindLocalMinimum(void* fn, void* ctx, f32 start, f32 step, f32 lo, f32 hi, f32* at, f32* min);
void PlaceOnTargetObject(Chooser* self, TargetCand* o, Vec02* a, Vec02* b, f32 t);
void func_001CEB18(Chooser* self, void* frame, Vec02* at, s32 a, Vec02* p, Vec02* q, f32 t);
f32 ArctangentOfRatio(f32 y, f32 x);
void PlaceOnTargetPoint(TargetCand* o, Vec02* out, s32 a, f32 t);
void PlaceOnTargetCurve(TargetCand* o, Vec02* out, s32 a, f32 t);
f32 RandomFloatInRange(f32 a, f32 b);
void func_001C61E0(Chooser* self, s32 mode);
void UpdatePlayerAimTarget(Chooser* self);
void StartSoundEffect(s32 sound, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

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
    func_0017FC48(self, &from);
    for (o = self->world->objects; o != 0; o = o->next50) {
        ConvertPositionToWorld(o, &at);
        if (o != keep && o->f58 < self->pos.z - at.z) {
            continue;
        }
        ScorePlayerTargetPlacement(self, &from, o->frame, &at, 0, &t, &cost, &cur0, &cur1);
        cur1.z = from.z + t * self->f358;
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E24);
            if (bestCost <= cost) {
                continue;
            }
            if (AddTargetObstructionCost(t, self, 0, 0, self->f6D4, &from, &cur0, &cur1, 0)) {
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
        TransformPointBetweenFrames(0, path->frame, self->f6D4, &at);
        if (path->shape->desc->m10) {
            path->shape->desc->m10(path->shape, &at, 0, &at2, 0, &tPath, 0);
        }
        TransformPointBetweenFrames(path->frame, 0, &at2, &at2);
        if (path != keep && path->f4C < self->pos.z - at2.z) {
            continue;
        }
        ctx.self = self;
        ctx.target = path;
        ctx.v = from;
        CostContext* c = &ctx;
        f32 start = tPath;
        f32 step = GetPathCurveSearchStep(path->shape);
        f32 lo = path->shape->desc->m6(path->shape, D_00274E04);
        FindLocalMinimum((void*)ScoreTargetObjectAt, c, start, step, lo,
                         path->shape->desc->m6(path->shape, path->shape->desc->m8(path->shape) - D_00274E04),
                         &tPathBest, &cost);
        if (path != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, path, cost, D_00274E28);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetObject(self, path, &at2, &q, tPathBest);
        ScorePlayerTargetPlacement(self, &from, path->frame, &at2, &q, &t, 0, &cur0, &cur1);
        cur1.z = from.z + t * self->f358;
        if (path != keep && AddTargetObstructionCost(t, self, 0, 0, self->f6D4, &from, &cur0, &cur1, 0)) {
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
            if (o == self->f2210) {
                continue;
            }
            if ((o->flags88 & 1) == 0) {
                continue;
            }
            if (!IsObjectOfKind(o, 0x76)) {
                continue;
            }
        }
        GetObjectWorldPosition(o, &at);
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
        FindLocalMinimum((void*)ScoreTargetPathAt, &args, 0.5f, 0.25f, 0.25f, 3.0f, &t, &cost);
        func_001CEB18(self, args.frame, &args.c, 0, &cur0, &cur1, t);
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E2C);
            if (bestCost <= cost) {
                continue;
            }
            TransformPointBetweenFrames(args.frame, 0, &args.c, &p);
            if (AddTargetObstructionCost(t, self, 0, 0, &self->v140, &self->v150, &cur0, &cur1, &p)) {
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
        TransformPointBetweenFrames(0, o->frame, &self->v140, &at);
        if (o->shape->desc->m10) {
            o->shape->desc->m10(o->shape, &at, 0, &at2, 0, 0, &tVector);
        }
        TransformPointBetweenFrames(o->frame, 0, &at2, &at2);
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
        FindLocalMinimum((void*)ScoreTargetPathNearest, n, start, 100.0f, 50.0f, o->shape->desc->m8(o->shape) - 50.0f,
                         &tVectorBest, &cost);
        if (o != keep) {
            if (cost >= D_00274E20) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E30);
            if (bestCost <= cost) {
                continue;
            }
        }
        args.self = self;
        args.frame = o->frame;
        if (o->shape->desc->m2) {
            o->shape->desc->m2(o->shape, &args.c, tVectorBest, 0);
        }
        FindLocalMinimum((void*)ScoreTargetPathAt, &args, 0.5f, 0.25f, 0.25f, 3.0f, &t, 0);
        func_001CEB18(self, args.frame, &args.c, 0, &cur0, &cur1, t);
        if (o != keep) {
            TransformPointBetweenFrames(o->frame, 0, &args.c, &p);
            if (AddTargetObstructionCost(t, self, 0, 0, &self->v140, &self->v150, &cur0, &cur1, &p)) {
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
        ConvertPositionToWorld(o, &at);
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
        FindLocalMinimum(fn, c, ArctangentOfRatio(d.y, d.x) * o->f5C, D_00274E40, lo, hi, &tPoint, &cost);
        cost = cost * weight;
        if (o != keep) {
            if (cost >= maxCost) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E38);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetPoint(o, &at, 0, tPoint);
        ScorePlayerTargetPlacement(self, &self->v150, o->frame, &at, 0, &t, 0, &cur0, &cur1);
        cur1.z = self->v150.z + t * self->f358;
        if (o != keep && AddTargetObstructionCost(t, self, 0, 0, self->f6D4, &self->v150, &cur0, &cur1, 0)) {
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
        TransformPointBetweenFrames(0, o->frame, self->f6D4, &at);
        if (o->shape->desc->m10) {
            o->shape->desc->m10(o->shape, &at, 0, &at2, 0, 0, &tCurve);
        }
        TransformPointBetweenFrames(o->frame, 0, &at2, &at2);
        if (o->f58 < self->pos.z - at2.z) {
            continue;
        }
        CostContext* c = &ctx;
        ctx.self = self;
        ctx.v = self->v150;
        ctx.target = o;
        f32 start = tCurve;
        FindLocalMinimum((void*)ScoreTargetCurveAt, c, start, D_00274E44, 30.0f, o->shape->desc->m8(o->shape) - 30.0f,
                         &tCurveBest, &cost);
        cost = cost * weight;
        if (o != keep) {
            if (cost >= maxCost) {
                continue;
            }
            cost = AddRepeatTargetPenalty(self, o, cost, D_00274E34);
            if (bestCost <= cost) {
                continue;
            }
        }
        PlaceOnTargetCurve(o, &at2, 0, tCurveBest);
        ScorePlayerTargetPlacement(self, &self->v150, o->frame, &at2, 0, &t, 0, &cur0, &cur1);
        cur1.z = self->v150.z + t * self->f358;
        if (o != keep && AddTargetObstructionCost(t, self, 0, 0, self->f6D4, &self->v150, &cur0, &cur1, 0)) {
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
        return self->f2228;
    }
    s32 state;
    switch (kind) {
    case 3:
        self->f23B8 = bestObject;
        state = 0xA;
        break;
    case 4:
        self->f23BC = bestPath;
        self->f23C0 = bestPathT;
        self->f23C4 = bestPath->shape->desc->m5(bestPath->shape, bestPathT);
        state = 0xB;
        break;
    case 1:
        self->f23A8 = bestPoint;
        self->f23AC = bestPointT;
        state = 0xD;
        break;
    case 0:
        self->f23A0 = bestCurve;
        self->f23A4 = bestCurveT;
        state = 0xC;
        break;
    case 6:
        self->f2208 = 0;
        self->f2204 = bestClass75;
        self->f2200 = bestClass75;
        func_001C61E0(self, 0);
        UpdatePlayerAimTarget(self);
        state = 0xE;
        break;
    case 7:
        self->f2208 = bestVector;
        self->f220C = bestVectorT;
        self->f2204 = 0;
        self->f2200 = 0;
        func_001C61E0(self, 0);
        UpdatePlayerAimTarget(self);
        state = 0xF;
        break;
    default:
        StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, D_00262E24, 0.0f, 0.0f, 0, 0);
        state = self->f2228;
        break;
    }
    TargetRecord* r = self->f2514;
    r->time = g_gameClock.time + bestT;
    self->f2514->a = best0;
    self->f2514->a.z += 75.0f;
    self->f2514->b = best1;
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

void FindTargetCurveLengthNearCollider(void* curve, f32* length, Vec02* pos, f32* heading);
void PlaceTargetPointNearCollider(void* point, Vec02* pos, f32* heading);
void FindRingPointTowardCollider(void* part, Vec02* pos, f32* heading);
u128 ApproachPointWithRamp(u128 from, u128 to, f32 dt, RampProfile* ramp, Vec02* vel);
void ComputePolarOffset(Vec02* out, f32 heading, f32 distance, f32 z);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, RampProfile* p, f32* out);
f32 ArctangentOfRatio(f32 y, f32 x);
f32 WrapAngle(f32 a);
void SetPlayerOnOffPhase(Player* self, s32 n);
void SetPlayerBlendWeights(f32 angle, f32 t, Player* self, void* records, s32 n);
s32 AimPlayerAtTarget(void* self);
void SetPlayerState(Player* self, s32 a, s32 b);
void TransformDirectionBetweenFrames(void* frame, s32 a, void* in, void* out);
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
    s32 sub = self->f2228;
    switch (self->f239C) {
    case 0:
    case 1: {
        if (self->f23A0 != 0) {
            FindTargetCurveLengthNearCollider(self->f23A0, &self->f23A4, &a, &heading);
        } else if (self->f23A8 != 0) {
            PlaceTargetPointNearCollider(self->f23A8, &a, &heading);
        } else {
            FindRingPointTowardCollider(self->heldObject, &a, &heading);
        }
        f32 speed;
        if (self->f239C == 0) {
            speed = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(*(Vec02*)((u8*)self + 0xAB0)))) *
                    ((PhasePlayer*)self->watched2230)->speed;
        } else {
            speed = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(*(Vec02*)((u8*)self + 0xB80)))) *
                    ((PhasePlayer*)self->watched2230)->speed;
        }
        a.z = self->pos.z;
        b.x = speed;
        b.y = 0.0f;
        b.z = D_00274E48;
        ApproachPointWithRamp(Vu0::Q(self->pos), Vu0::Q(a), g_gameClock.dt, (RampProfile*)&b, &c);
        f32 turn;
        if (self->f239C == 0) {
            turn = heading + 1.57079637f;
        } else {
            turn = heading - 1.57079637f;
        }
        ComputePolarOffset(&d, turn, 1.0f, 0.0f);
        ComputePolarOffset(&e, self->f630, 1.0f, 0.0f);
        f32 cosine = D_00274E50 * Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d), Vu0::Q(e)));
        f32 side;
        side = ClampBetween(cosine, -1.0f, 1.0f);
        side = side * self->f634;
        if (__builtin_fabsf(side) < 0.2f) {
            side = 0.0f;
        }
        f32 v = side * speed;
        v = Fpu::Sqrt(speed * speed - Vu0::ToFloat(Vu0::Dot(Vu0::Q(c), Vu0::Q(c)))) <? v;
        f32 t;
        if (self->f23A0 != 0 && ((TargetFrameRecord*)self->f23A0)->mover->wraps == 0) {
            ApproachValueWithRamp(self->f23A4, 30.0f, g_gameClock.dt, (RampProfile*)&b, &lo);
            TargetMover* m = ((TargetFrameRecord*)self->f23A0)->mover;
            ApproachValueWithRamp(self->f23A4, m->low[m->count - 1] - 30.0f, g_gameClock.dt, (RampProfile*)&b, &hi);
            t = ClampBetween(v, lo, hi);
        } else {
            t = v;
        }
        Vu0::Vec s = Vu0::Vec::FromFloat(t);
        Vu0::Q(f) = Vu0::MulX(Vu0::Q(d), s.q);
        u128 vel = Vu0::Q(c);
        u128 local = Vu0::RotateTransposed(self->m660, Vu0::Add(vel, Vu0::Q(f)));
        *(Vu0::Vec*)&k = s;
        Vu0::Vec n = Vu0::Vec::FromFloat(-1.0f);
        u128 drive = Vu0::MulX(local, n.q);
        *(Vu0::Vec*)&k = n;
        *(Vu0::Vec*)&self->v640 = *(Vu0::Vec*)&drive;
        if (D_00274E4C < Vu0::ToFloat(Vu0::Length(drive))) {
            sub = 0x11;
            if (self->f239C == 0) {
                if (45.0f < Vu0::ToFloat(Vu0::Length(vel))) {
                    SetPlayerOnOffPhase(self, 0);
                } else if (20.0f < self->v640.y) {
                    SetPlayerOnOffPhase(self, 2);
                } else if (self->v640.y < -20.0f) {
                    SetPlayerOnOffPhase(self, 1);
                }
            }
        } else {
            sub = 0x10;
            if (v < -D_00274E4C && (((TargetFrameRecord*)self->f23A0)->sides & 1)) {
                sub = self->f239C == 0 ? 0x13 : 0x12;
            } else if (D_00274E4C < v && (((TargetFrameRecord*)self->f23A0)->sides & 2)) {
                sub = self->f239C == 0 ? 0x12 : 0x13;
            }
            if (self->f239C == 0) {
                SetPlayerOnOffPhase(self, 3);
            }
        }
        self->f638 = heading;
        if (self->f2228 == 0x15) {
            f32 off = __builtin_fabsf(WrapAngle(ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x) - self->f638));
            if (D_00274E54 < off) {
                sub = 0x15;
            }
        }
        break;
    }
    case 2:
        if (self->f2228 == 0x10 || self->f2228 == 0x14) {
            if (0.0f < self->f634) {
                sub = 0x14;
                SetPlayerBlendWeights(self->f630, self->f634, self, (u8*)self + 0xC40, *(s32*)((u8*)self + 0xE20));
            } else {
                Vu0::Q(self->v640) = Vu0::Zero();
                sub = 0x10;
            }
        }
        break;
    case 3:
        if (MaskWorldBitsBySave() & 0x2000) {
            if (0.0f < self->f634) {
                sub = 0x14;
                SetPlayerBlendWeights(self->f630, self->f634 * D_00274E58, self, (u8*)self + 0x720, self->f900);
            } else {
                Vu0::Q(self->v640) = Vu0::Zero();
                sub = 0x10;
            }
        } else {
            Vu0::Q(self->v640) = Vu0::Zero();
            sub = 0x10;
        }
        break;
    case 5:
        self->f638 = self->f630;
        Vu0::Q(self->v640) = Vu0::Zero();
        break;
    case 4: {
        TargetFrameRecord* rec = (TargetFrameRecord*)self->f23BC;
        void* frame = rec->frame;
        TargetMover* m = rec->mover;
        TransformPointBetweenFrames(0, frame, (void*)self->f6D4, &a);
        if (m->vt->track != 0) {
            m->vt->track(m, self->f23C0, &a, 0, &b, &c, &self->f23C0, &self->f23C4);
        }
        TransformPointBetweenFrames(frame, 0, &b, &d);
        TransformDirectionBetweenFrames(frame, 0, &c, &e);
        if (rec->active != 0 && m->wraps == 0) {
            if (self->f23C0 <= 0.0f || m->ends[m->count - 1] <= self->f23C0) {
                mode = 2;
                sub = 2;
                break;
            }
        }
        e.z = 0.0f;
        *(Vu0::Vec*)&e = NormalizeOrElse(Vu0::Vec::Of(e), Vu0::Vec::Of(g_unitXVector));
        f32 angle = ArctangentOfRatio(e.y, e.x);
        ComputePolarOffset(&h, self->f630, 1.0f, 0.0f);
        if (rec->facing == 0) {
            f = e;
        } else {
            void* frame2 = rec->facing->frame;
            TransformPointBetweenFrames(0, frame2, (void*)self->f6D4, &i);
            TargetMover* m2 = rec->facing->mover;
            if (m2->vt->nearest != 0) {
                m2->vt->nearest(m2, &i, 0, 0, &j, 0, 0);
            }
            TransformDirectionBetweenFrames(frame2, 0, &j, &f);
        }
        f.z = 0.0f;
        *(Vu0::Vec*)&f = NormalizeOrElse(Vu0::Vec::Of(f), Vu0::Vec::Of(g_unitXVector));
        f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(h), Vu0::Q(f)));
        switch (self->f241C) {
        case 0:
            if (self->f634 < 0.25f) {
                self->f241C = -1;
            } else if (along < -0.7f) {
                self->f241C = 1;
            }
            break;
        case 1:
            if (self->f634 < 0.25f) {
                self->f241C = -1;
            } else if (0.7f < along) {
                self->f241C = 0;
            }
            break;
        case -1:
            if (0.35f < pad->f48) {
                if (0.0f <= along) {
                    self->f241C = 0;
                } else {
                    self->f241C = 1;
                }
            }
            break;
        }
        switch (self->f241C) {
        case 0:
            self->f23C8 = 0;
            break;
        case 1:
            self->f23C8 = 1;
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
            } else if (self->f23C8 != 0) {
                ApproachValueWithRamp(self->f23C4, D_00274E04, g_frameDt, (RampProfile*)&i, &end);
                end = -end;
            } else {
                ApproachValueWithRamp(self->f23C4, m->vt->limit(m) - D_00274E04, g_frameDt, (RampProfile*)&i, &end);
            }
            f32 r = (end - i.y) / (i.x - i.y);
            along = ClampBetween(self->f634, 0.0f, r);
        }
        if (self->f23C8 != 0) {
            angle = WrapAngle(angle + 3.14159274f);
        }
        if (0.0f < along) {
            sub = 0x14;
            SetPlayerBlendWeights(angle, along, self, (u8*)self + 0xE30, *(s32*)((u8*)self + 0x1010));
        } else {
            Vu0::Q(self->v640) = Vu0::Zero();
            self->f638 = angle;
            sub = 0x10;
        }
        break;
    }
    case 6:
        AimPlayerAtTarget(self);
    default:
        Vu0::Q(self->v640) = Vu0::Zero();
        break;
    }
    SetPlayerState(self, mode, sub);
}

struct TargetPlayerView { u8 pad0[0x23BC]; TargetFrameRecord* record; f32 f23C0; f32 angle; s32 flip; };
struct TargetProbe { u8 pad0[4]; s32 active; f32 radius; u8 pad0C[4]; Vec02 point; Vec02 end; };

f32 WrapModulo(f32 x, f32 y);
void TransformPointBetweenFrames(void* frame, void* player, void* in, void* out);
s32 CollectBoundsSpans(void* a, void* b, void* c, s32 d, void* e, f32 x);


void func_001D0B20(TargetPlayerView* self, TargetProbe* t, u8* out)
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
    TransformPointBetweenFrames(frame, self, &pos, &local);
    if (CollectBoundsSpans(&t->end, &t->point, &local, 1, &span, t->radius) > 0) {
        Vu0::Q(*(Vec02*)(out + 0x20)) = Vu0::Sub(Vu0::Q(span.q[1]), Vu0::Q(t->point));
    }
}


extern f32 D_00274B64;
void UpdateEightEntryBlendWeights(Player* self, void* slots, s32 n);
void UpdateSixEntryBlendWeights(Player* self, void* slots, s32 n, void* phase);
void PlayPhaseCrossingSound(Player* self, void* sounds, f32 t);
void func_001719E8(void* self, s32 a, s32 b, void* part, f32 k, void* d);

void UpdatePlayerTargetPhase(Player* self)
{
    switch (self->f2228) {
    case 0x11: {
        void* slots;
        s32 n;
        void* sounds;
        switch (self->f239C) {
        case 0:
            slots = (u8*)self + 0xA20;
            n = *(s32*)((u8*)self + 0xB20);
            sounds = (u8*)self + 0x2470;
            break;
        case 1:
            slots = (u8*)self + 0xB30;
            n = *(s32*)((u8*)self + 0xC30);
            sounds = (u8*)self + 0x2480;
            break;
        case 3:
            slots = (u8*)self + 0x910;
            n = self->fA10;
            sounds = (u8*)self + 0x2450;
            break;
        }
        UpdateEightEntryBlendWeights(self, slots, n);
        PhasePlayer* ph = (PhasePlayer*)self->watched2230;
        f32 t = WrapModulo((ph->time + D_00274B64 * ph->speed) / ph->clip->length, 1.0f);
        if (self->f2674 == (s32)self->f2678) {
            s32 m = self->f2684;
            if (m < 3) {
                if (m > 0) {
                    if (m == 1) *(f32*)&self->f26A0 >?= *(f32*)((u8*)self + 0xA40); else *(f32*)&self->f26A0 >?= *(f32*)((u8*)self + 0xA20);
                }
            }
        }
        PlayPhaseCrossingSound(self, sounds, t);
        break;
    }
    case 0x14: {
        switch (self->f239C) {
        case 4:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0xE30, *(s32*)((u8*)self + 0x1010), self->watched2230);
            break;
        case 2:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0xC40, *(s32*)((u8*)self + 0xE20), self->watched2230);
            break;
        case 3:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0x720, self->f900, self->watched2230);
            break;
        }
        PhasePlayer* ph = (PhasePlayer*)self->watched2230;
        f32 t = WrapModulo((ph->time + D_00274B64 * ph->speed) / ph->clip->length, 1.0f);
        PlayPhaseCrossingSound(self, (u8*)self + 0x2440, t);
        break;
    }
    case 0x10:
        if (self->f239C == 4) {
            f32 k = 5.0f;
            u8* p1 = (u8*)self + 0x1190;
            func_001719E8(self, (s32)self->f628, (s32)self->f620, self->f250C, k, p1);
            u8* p2 = (u8*)self + 0x1290;
            func_001719E8(self, (s32)self->f62C, (s32)self->f624, self->f2510, k, p2);
            CollectPlayerTargetSpans((TargetPlayerView*)self, (TargetProbe*)p1, (u8*)self->f250C);
            CollectPlayerTargetSpans((TargetPlayerView*)self, (TargetProbe*)p2, (u8*)self->f2510);
        }
        break;
    }
}

// What func_001D0F20 reads besides the record: the anchor at +0x23B8, the angle at +0x23C0
// and the limit at +0x23C4 the mover's track call writes back.
struct ContactPlayerView {
    u8 pad0[0x23B8];
    void* anchor;           // 0x23B8
    TargetFrameRecord* record;  // 0x23BC
    f32 angle;              // 0x23C0
    f32 limit;              // 0x23C4
};

void TransformDirectionBetweenFrames(void* frame, s32 a, void* in, void* out);
void AddPlayerObjectContacts(void* self, s32 code, void* a, void* b, void* c, void* d);

void func_001D0F20(Player* self)
{
    Vec02 pos;
    Vec02 local;
    Vec02 dir0;
    Vec02 world;
    Vec02 dir;
    Vec02 k;
    ContactPlayerView* p = (ContactPlayerView*)self;
    s32 code;
    switch (self->f239C) {
    case 5:
        ConvertPositionToWorld(p->anchor, &pos);
        AddPlayerObjectContacts(self, 0x23, p->anchor, &pos, 0, (void*)self->f6D4);
        break;
    case 4: {
        TargetFrameRecord* rec = p->record;
        void* frame = rec->frame;
        TargetMover* m = rec->mover;
        TransformPointBetweenFrames(0, frame, (void*)self->f6D4, &pos);
        if (m->vt->track != 0) {
            m->vt->track(m, p->angle, &pos, 0, &local, &dir0, &p->angle, &p->limit);
        }
        TransformPointBetweenFrames(frame, 0, &local, &world);
        TransformDirectionBetweenFrames(frame, 0, &dir0, &dir);
        code = 0x22;
        if (p->record->active == 0 && m->wraps == 0) {
            f32 along = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->v150), Vu0::Q(dir)));
            f32 side = -Vu0::ToFloat(Vu0::Dot(Vu0::Rotate(self->rot, Vu0::Q(self->v640)), Vu0::Q(dir)));
            if (along < -2.0f || side < 2.0f) {
                f32 lim = m->low[0] + D_00274E04;
                if (p->limit < lim) {
                    if (m->vt->place != 0) {
                        m->vt->place(m, lim, &local, 0);
                    }
                    TransformPointBetweenFrames(frame, 0, &local, &world);
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
                    TransformPointBetweenFrames(frame, 0, &local, &world);
                    Vu0::Q(k) = Vu0::FromFloat(-1.0f);
                    Vu0::Q(dir) = Vu0::MulX(Vu0::Q(dir), Vu0::Q(k));
                    code = 0x2A;
                    goto call;
                }
            }
        }
    call:
        AddPlayerObjectContacts(self, code, p->record, &world, &dir, (void*)self->f6D4);
        break;
    }
    }
}

void FreePooledContactChain(void* a, s32 b);

void SetPlayerOnOffPhase(Player* self, s32 n)
{
    if (n == self->f2684) {
        return;
    }
    self->f2684 = n;
    self->f2688 = g_gameClock.time;
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
        s32 v = self->f2674;
        if (v == (s32)self->f2678) {
            self->f268C = 2;
        } else {
            self->f268C = 0;
        }
    }
}

void SetOnOffObjectForcedState(OnOffObject* o, s32 v);

void ResetPlayerOnOffObject(Player* self)
{
    OnOffObject* o = self->f2678;
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

void TransformDirectionBetweenFrames(void* frame, s32 a, void* in, void* out);
void ApproachValueWithRamp(f32 value, f32 target, f32 dt, float* ramp, f32* out);
void AddColliderForce(Player* self, void* v);
void func_0016FD70(Player* self);

void func_001D12F0(Player* self)
{
    Vec02 dir;
    Vec02 force;
    Vec02 k;
    f32 bounds[2];
    if (self->f239C == 4) {
        TargetFrameRecord* rec = ((TargetPlayerView*)self)->record;
        if (rec->active != 0) {
            TargetMover* m = rec->mover;
            if (m->vt->placeAt != 0) {
                m->vt->placeAt(m, ((TargetPlayerView*)self)->f23C0, 0, &dir);
            }
            TransformDirectionBetweenFrames(rec->frame, 0, &dir, &dir);
            f32 down = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->gravity)));
            f32 along = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->v150)));
            float* ramp = D_00274EF0;
            ApproachValueWithRamp(along, rec->limit, g_gameClock.dt, ramp, &bounds[0]);
            ApproachValueWithRamp(along, -rec->limit, g_gameClock.dt, ramp, &bounds[1]);
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
    func_0016FD70(self);
}

s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
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
