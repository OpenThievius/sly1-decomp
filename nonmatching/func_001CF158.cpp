// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 3637/3704 (98.2%), checked 2026-11-08
// NEAR (2026-11-08, night-large5): ChoosePlayerTargetByCost (func_001CF158, 3704 bytes): the six
// candidate loops (objects, paths, class 0x75, target vectors, points, curves), the checksum
// check, the switch on the best kind and the record update follow retail at the same size; the
// cost contexts go to FindLocalMinimum through pointers (retail hoists and spills those
// addresses), the extremes are literals (retail's D_0024DAD0 and D_0024DAD4 are this function's).
// Found (night-close10): the squared distance read through ToFloatMoved and the plain distance
// as u128 helpers through ToFloatMoved (the Vec copies kept the vector loop at 162 insns at the
// second loop pass, two over loop.c's 160, so the limit's and D_00274E20's %hi stayed in it);
// the point loop's scorer named first in the body (`void* fn`), so loop.c hoists its %hi in the
// first pass and the extremes' %hi parts take s7 and s8 as retail's do. Left, 19 lines: in the
// vector loop the 50.0 (mov.s $f14) is set before a0 and a1, retail after; in the curve loop
// retail's s8 holds ScoreTargetCurveAt's %hi, ours D_00274E20's (all three of the function's,
// D_00274E10's and D_00274E20's %hi are moved in the second pass, the last one found, with the
// shortest life, gets the register; a named fn local in that loop does not change it).
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "game_clock.h"
#include "globals.h"

extern const f32 D_0024DAD0;
extern const f32 D_0024DAD4;
extern f32 D_00274E04;
extern f32 D_00274E0C;
extern f32 D_00274E10;
extern f32 D_00274E20;
extern f32 D_00274E24;
extern f32 D_00274E28;
extern f32 D_00274E2C;
extern f32 D_00274E30;
extern f32 D_00274E34;
extern f32 D_00274E38;
extern f32 D_00274E40;
extern f32 D_00274E44;
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

extern List01 g_class75List;

void func_0017FC48(Chooser* self, Vec02* out);
void ConvertPositionToWorld(void* obj, Vec02* out);
void ScorePlayerTargetPlacement(Chooser* self, Vec02* from, void* frame, Vec02* at, Vec02* at2, f32* t, f32* cost,
                                Vec02* a, Vec02* b);
f32 AddRepeatTargetPenalty(Chooser* self, TargetCand* id, f32 a, f32 b);
s32 AddTargetObstructionCost(f32 limit, Chooser* self, void* a1, void* a2, void* pa, void* pb, Vec02* pc, Vec02* pd,
                             Vec02* pe);
void TransformPointBetweenFrames(void* a, void* b, void* c, Vec02* d);
f32 GetPathCurveSearchStep(TargetShape* shape);
void FindLocalMinimum(f32 start, f32 step, f32 lo, f32 hi, void* fn, void* ctx, f32* at, f32* min);
f32 ScoreTargetObjectAt(CostContext* self);
f32 ScoreTargetPathAt(PathArgs* self);
f32 ScoreTargetPathNearest(NearestContext* self);
f32 ScoreTargetPointAt(CostContext* self);
f32 ScoreTargetCurveAt(CostContext* self);
void PlaceOnTargetObject(Chooser* self, TargetCand* o, Vec02* a, Vec02* b, f32 t);
s32 IsObjectOfKind(void* obj, s32 kind);
s32 GetObjectWorldPosition(void* obj, Vec02* out);
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

s32 func_001CF158(Chooser* self, TargetCand* keep)
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
    f32 bestCurveT;
    f32 bestVectorT;
    f32 bestPointT;
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
        FindLocalMinimum(start, step, lo, path->shape->desc->m6(path->shape, path->shape->desc->m8(path->shape) - D_00274E04),
                         (void*)ScoreTargetObjectAt, c, &tPathBest, &cost);
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
        FindLocalMinimum(0.5f, 0.25f, 0.25f, 3.0f, (void*)ScoreTargetPathAt, &args, &t, &cost);
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
        FindLocalMinimum(start, 100.0f, 50.0f, o->shape->desc->m8(o->shape) - 50.0f, (void*)ScoreTargetPathNearest,
                         n, &tVectorBest, &cost);
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
        FindLocalMinimum(0.5f, 0.25f, 0.25f, 3.0f, (void*)ScoreTargetPathAt, &args, &t, 0);
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
        FindLocalMinimum(ArctangentOfRatio(d.y, d.x) * o->f5C, D_00274E40, lo, hi,
                         fn, c, &tPoint, &cost);
        cost = cost * D_00274E10;
        if (o != keep) {
            if (cost >= D_00274E20) {
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
        FindLocalMinimum(start, D_00274E44, 30.0f, o->shape->desc->m8(o->shape) - 30.0f, (void*)ScoreTargetCurveAt,
                         c, &tCurveBest, &cost);
        cost = cost * D_00274E10;
        if (o != keep) {
            if (cost >= D_00274E20) {
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
