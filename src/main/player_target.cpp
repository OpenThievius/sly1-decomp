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

// The file's .rodata, in retail's order: the constants and jump tables only its assembly reads.
extern const f32 D_0024DAA0 = -3.40282347e+38f;
INCLUDE_RODATA(jtbl_0024DAB0);
extern const f32 D_0024DAD0 = -3.40282347e+38f;
INCLUDE_RODATA(D_0024DAD4);
INCLUDE_RODATA(jtbl_0024DAE0);
INCLUDE_RODATA(jtbl_0024DB00);

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

INCLUDE_ASM(func_001CDFB8);

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

INCLUDE_ASM(func_001CEEC8);

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
    struct Vt { u8 pad0[8]; void (*place)(TargetMover* self, f32 angle, void* out, s32 flag); u8 pad0C[0x20 - 0x0C]; f32 (*limit)(TargetMover* self); };
    const Vt* vt;           // 0x00
    u8 pad04[4];
    s32 wraps;              // 0x08
    u8 pad0C[0x14 - 0x0C];
    const f32* low;         // 0x14
};
struct TargetFrameRecord { u8 pad0[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; TargetMover* mover; };
struct TargetPlayerView { u8 pad0[0x23BC]; TargetFrameRecord* record; u8 pad23C0[4]; f32 angle; s32 flip; };
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

INCLUDE_ASM(func_001D12F0);

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
