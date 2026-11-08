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

// The rest of the file's .rodata, in retail's order after func_001CDFB8's literal and jump
// table: the constants and jump tables only its assembly reads.
extern const f32 D_0024DAD0 = -3.40282347e+38f;
INCLUDE_RODATA(D_0024DAD4);
INCLUDE_RODATA(jtbl_0024DAE0);
INCLUDE_RODATA(jtbl_0024DB00);

INCLUDE_ASM(func_001CE590);

INCLUDE_ASM(func_001CE800);

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

INCLUDE_ASM(func_001CEB18);

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

void FindLocalMinimum(f32 f12, f32 f13, f32 f14, f32 f15, void* fn, void* b, s32 c, void* out);

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
    
    FindLocalMinimum(0.5f, q, q, 3.0f, (void*)ScoreTargetPathAt, l.b, 0, &l.out);
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

INCLUDE_ASM(func_001CF158);

INCLUDE_ASM(func_001CFFD0);

// What func_001D0B20 reads: the player's record at +0x23BC (a frame at +0x18 and a mover at
// +0x34), the angle at +0x23C4 and its flip flag at +0x23C8, and the target (a flag at +0x04,
// the radius at +0x08, a point at +0x10, a pair of points at +0x20).
struct TargetMover {
    struct Vt { u8 pad0[4]; void (*placeAt)(TargetMover* self, f32 angle, s32 flag, void* out); void (*place)(TargetMover* self, f32 angle, void* out, s32 flag); u8 pad0C[0x20 - 0x0C]; f32 (*limit)(TargetMover* self); };
    const Vt* vt;           // 0x00
    u8 pad04[4];
    s32 wraps;              // 0x08
    u8 pad0C[0x14 - 0x0C];
    const f32* low;         // 0x14
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
};
struct TargetPlayerView { u8 pad0[0x23BC]; TargetFrameRecord* record; f32 f23C0; f32 angle; s32 flip; };
struct TargetProbe { u8 pad0[4]; s32 active; f32 radius; u8 pad0C[4]; Vec02 point; Vec02 end; };

f32 WrapModulo(f32 x, f32 y);
void TransformPointBetweenFrames(void* frame, void* player, void* in, void* out);
s32 CollectBoundsSpans(void* a, void* b, void* c, s32 d, void* e, f32 x);

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

INCLUDE_ASM(func_001D0C78);

INCLUDE_ASM(func_001D0F20);

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
