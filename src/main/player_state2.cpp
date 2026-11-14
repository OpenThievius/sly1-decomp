// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x17D248 to 0x17FE00: the player's mode 2 (StepPlayerState2, ControlPlayerState2,
// UpdatePlayerState2) with its ledge contacts and jump velocities, then the point objects' list.
// Its name is ours, after the player's mode 2, which holds nearly all of its code.
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"
#include "node_query.h"
#include "list_iter.h"
#include "transform_object.h"
struct BaseObject;

struct BaseObject;

struct BaseObject;


// Types other files define, named by the parameters of their functions declared here.
struct TargetHit;
struct TargetCurve;

// From 0x17D248 to colored_triangle_set: player helpers in VU0 code, the probe test func_0017DE88, and the
// point-object list of class 0x80. Its .data runs from 0x263E50 to 0x264094 (tuning floats the
// VU0 functions read, vectors, the probe segments and the list head g_pointObjects); its
// .rodata from 0x24B060 to 0x24B164 is the jump tables of its VU0 functions.

f32 D_00263E50 = 0.150000006f;
f32 D_00263E54 = 300.0f;
f32 D_00263E58 = 2.5f;
f32 D_00263E5C = 3.5f;
f32 D_00263E60 = 2.5f;
f32 D_00263E64 = 60.0f;
f32 D_00263E68 = 20.0f;
f32 D_00263E6C = 10.0f;
f32 D_00263E70 = 0.0700000003f;
f32 D_00263E74 = 0.300000012f;
f32 D_00263E78 = -750.0f;
f32 D_00263E7C = 5.0f;
f32 D_00263E80 = 700.0f;
f32 D_00263E84 = 245.0f;
f32 D_00263E88 = 900.0f;
f32 D_00263E8C = 800.0f;
f32 D_00263E90[4] = { 0.0f, 5.0f, 0.0f, 0.0f };
f32 D_00263EA0[4] = { 0.0f, 10.0f, 0.0f, 0.0f };
f32 D_00263EB0[4] = { 0.400000006f, 0.0f, 0.0f, 0.0f };
// The 22 segment ends func_0017DE88 transforms; func_00188700 loads each whole (lqc2).
Vec02 D_00263EC0[22] = {
    { 50.0f, 0.0f, 75.0f, 0.0f },
    { 50.0f, 0.0f, -150.0f, 0.0f },
    { 50.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, -50.0f, 0.0f },
    { -57.96f, 15.53f, 75.0f, 0.0f },
    { -57.96f, 15.53f, -50.0f, 0.0f },
    { -51.96f, 30.0f, 75.0f, 0.0f },
    { -51.96f, 30.0f, -50.0f, 0.0f },
    { -42.43f, 42.43f, 75.0f, 0.0f },
    { -42.43f, 42.43f, -50.0f, 0.0f },
    { -30.0f, 51.96f, 75.0f, 0.0f },
    { -30.0f, 51.96f, -50.0f, 0.0f },
    { -57.96f, -15.53f, 75.0f, 0.0f },
    { -57.96f, -15.53f, -50.0f, 0.0f },
    { -51.96f, -30.0f, 75.0f, 0.0f },
    { -51.96f, -30.0f, -50.0f, 0.0f },
    { -42.43f, -42.43f, 75.0f, 0.0f },
    { -42.43f, -42.43f, -50.0f, 0.0f },
    { -30.0f, -51.96f, 75.0f, 0.0f },
    { -30.0f, -51.96f, -50.0f, 0.0f },
};
f32 D_00264020 = 60.0f;
f32 D_00264024 = 70.0f;
f32 D_00264028 = 300.0f;
f32 D_0026402C = 500.0f;
f32 D_00264030 = 1000.0f;
f32 D_00264034 = 3000.0f;
f32 D_00264038[2] = { -150.0f, 150.0f };
f32 D_00264040 = 0.349999994f;
f32 D_00264044 = 0.349999994f;
f32 D_00264048[2] = { 10000.0f, 0.0f };
f32 D_00264050[4] = { 682.0f, 0.5f, 0.0f, 0.0f };
f32 D_00264060[4] = { -3.40282347e+38f, 682.0f, 0.0f, 0.0f };
f32 D_00264070[4] = { 682.0f, 1.0f, 0.0f, 0.0f };
f32 D_00264080[2] = { -3.40282347e+38f, 682.0f };
// size: list head of three words, link offset at +8 (0x50)
List01 g_pointObjects = {0};

extern f32 g_gameClock[];
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* target, f32* gain);
void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);
void SteerColliderTowardPosition(Collider* self, Vec02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
f32 GetAnimationMarkerTime(Animation* self, s32 key);
void AddColliderForce(void* target, Vec02* force);
void BuildBasisFromX(Vec02* x, Mat02* out);

void StepPlayerState2(Player* self)
{
    Vec02 a;
    Vec02 b;
    TurnColliderTowardRotation(self, g_gameClock[2], &self->headingMatrix, &self->turnGain);
    switch (self->subState) {
    case 6:
        if (0.0001f < self->stickLevel) {
            ComputePolarOffset((Vec3*)&a, self->stickHeading, self->stickLevel * self->jumpSpeed, 0.0f);
            Vu0::Q(b) = Vu0::Add(Vu0::Q(self->v2290), Vu0::Q(a));
            b.z = self->v150.z;
            SteerColliderTowardPosition(self, 0, 0, &b, D_00263E90, g_gameClock[2]);
        }
        break;
    case 8: {
        f32 t0 = GetAnimationMarkerTime((Animation*)self->markerAnim, 0x1BA);
        f32 t1 = GetAnimationMarkerTime((Animation*)self->markerAnim, 0x1BB);
        if (*(f32*)((u8*)self->stateAnimPlayer + 0x14) < t1) {
            Vu0::Q(a) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Scalar(-1.0f));
            AddColliderForce(self, &a);
        }
        if (*(f32*)((u8*)self->stateAnimPlayer + 0x14) < t0) {
            b = D_00248D30;
        } else {
            Vu0::Q(b) = Vu0::FromFloats(0.0f, 0.0f, self->v150.z);
        }
        SteerColliderTowardPosition(self, 0, 0, &b, D_00263EA0, g_gameClock[2]);
        break;
    }
    case 4:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        break;
    default: {
        if (self->entryQueue != 0) {
            break;
        }
        Vec02 c;
        Mat02 m;
        Vec02 r;
        a = self->v150;
        a.z = 0.0f;
        const u128& fb = Vu0::Q(g_unitXVector);
        Vu0::Vec v = Vu0::Vec::Of(a);
        Vu0::Vec l = Vu0::Length(v);
        if (Vu0::ToFloat(l) < 0.0001f) {
            Vu0::Set(a, fb);
        } else {
            Vu0::Set(a, Vu0::DivX(v, l).q);
        }
        f32 len = Vu0::ToFloat(l);
        BuildBasisFromX(&a, &m);
        Vu0::Q(b) = Vu0::RotateTransposed(m, Vu0::Q(self->v2290));
        f32 s;
        f32 u;
        f32 x;
        if (self->subState == 0) {
            if (b.x < len) {
                s = D_00263E68;
            } else {
                s = D_00263E64;
            }
            u = D_00263E6C;
            x = b.x;
        } else {
            if (b.x < len) {
                s = D_00263E5C;
            } else {
                s = D_00263E58;
            }
            u = D_00263E60;
            x = b.x;
        }
        c.z = 0.0f;
        c.y = u * b.y;
        c.x = s * (x - len);
        if (self->subState != 6) {
            f32 speed = self->gravityScale;
            if (self->v150.z < D_00263E78 * Fpu::Sqrt(speed)) {
                c.z = (D_00263E78 * Fpu::Sqrt(speed) - self->v150.z) * D_00263E7C;
            }
        }
        Vu0::Q(r) = Vu0::Rotate(m, Vu0::Q(c));
        AddColliderForce(self, &r);
        break;
    }
    }
}

f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* t, f32* dist);
void InitContactPairFlags(World* self, Collider* obj);
void SetPlayerState(Player* self, s32 a, s32 b);
void ScorePlayerTargetPlacement(Player* self, Vec02* point, BaseObject* obj, Vec02* start, Vec02* extra, f32* outTime, f32* outCost, Vec02* outPoint, Vec02* outVel);
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
    ((LeapRecord_17D5D8*)p->selfPoseSource)->time = g_gameTime + t;
    ((LeapRecord_17D5D8*)p->selfPoseSource)->aim = aim;
    ((LeapRecord_17D5D8*)p->selfPoseSource)->aim.z += 75.0f;
    ((LeapRecord_17D5D8*)p->selfPoseSource)->land = land;
    ((LeapRecord_17D5D8*)p->selfPoseSource)->land.z = p->v150.z + t * p->gravity.z;
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
    return Vu0::ToFloat(Vu0::DotXY(d.q, d.q));
}

static inline f32 MinF(f32 a, f32 b) { return a <? b; }

void ControlPlayerState2(Player* p, PadRecord* pad)
{
    Vec02 aim;
    switch (p->subState) {
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
        ComputePolarOffset((Vec3*)&aim, p->stickHeading, p->stickLevel * p->jumpSpeed, 0.0f);
        Vu0::Q(p->headingVelocity) = Vu0::MulX(Vu0::RotateTransposed(p->headingMatrix, Vu0::Q(aim)), Vu0::Scalar(-1.0f));
        if ((p->subState != 0 || p->jumpStickPhase == 3) && p->steerKeepsDirection == 0) {
            Vec02 dir;
            Vec02 side;
            dir = p->v150;
            dir.z = 0.0f;
            f32 speed = Vu0::ToFloat(NormalizeVectorOr(dir, g_unitXVector));
            f32 d = SplitVectorAlongAxis(&aim, &dir, 0, &side);
            if (d < speed && speed * -0.25f < d) {
                Vu0::Q(aim) = Vu0::MulAddX(Vu0::Q(side), Vu0::Q(dir), Vu0::Scalar(speed));
            }
        }
        p->v2290 = aim;
        break;
    }
    switch (p->subState) {
    case 3:
        if (!(D_00263EB0[0] < g_gameTime - p->subStateStartTime)) {
            return;
        }
    case 1:
    case 2:
    case 5:
    default: {
        Vec02 bestAim;
        Vec02 land;
        Vec02 bestLand;
        ListFrame frame;                // the list walks' frame: retail leaves its 16 bytes at 0x50 untouched
        LeapPart_17D5D8* best = 0;
        LeapPoint_17D5D8* bestPoint = 0;
        f32 bestCost = 1500.0f;
        f32 bestT;
        f32 t;
        f32 cost;
        for (LeapPart_17D5D8* q = (LeapPart_17D5D8*)g_partList.head; q != 0; q = q->next) {
            if (360000.0f < GroundDistanceSquared(q->v140, p->v140)) {
                continue;
            }
            if (q->v140.z + q->height < p->v140.z) {
                continue;
            }
            ScorePlayerTargetPlacement(p, &p->v150, (BaseObject*)q, &q->v140, 0, &t, &cost, &aim, &land);
            if (bestCost < cost) {
                continue;
            }
            Vec02 rel;
            Vec02 dv;
            Vec02 end;
            f32 a;
            f32 b;
            Vu0::Q(rel) = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(q->pos));
            Vu0::Q(dv) = Vu0::Sub(Vu0::Q(p->v150), Vu0::Q(q->v150));
            Vu0::Q(end) = Vu0::MulAddX(Vu0::Q(rel), Vu0::Q(dv), Vu0::Scalar(MinF(0.25f, t)));
            rel.z = end.z = 0.0f;
            MeasurePointToSegment((Vec02*)&D_00248D30, &rel, &end, &a, &b);
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
            Vec02 pos;
            Vec02 vel;
            Vec02 rel;
            Vec02 dv;
            Vec02 dir;                      // a local the original declared and never used: retail leaves its 16-byte slot at 0xA0 untouched
            Vec02 end;
            f32 a;
            f32 b;
            ConvertPositionToWorld((BaseObject*)q, &pos);
            if (360000.0f < GroundDistanceSquared(pos, p->v140)) {
                continue;
            }
            ScorePlayerTargetPlacement(p, (Vec02*)&p->v150, (BaseObject*)q->parent, &pos, 0, &t, &cost, &aim, &land);
            if (bestCost < cost) {
                continue;
            }
            ComputeObjectMotionInFrame((PlacedObject*)q->parent, 0, &pos, &vel, 0, 0, 0);
            Vu0::Q(rel) = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(pos));
            Vu0::Q(dv) = Vu0::Sub(Vu0::Q(p->v150), Vu0::Q(vel));
            Vu0::Q(end) = Vu0::MulAddX(Vu0::Q(rel), Vu0::Q(dv), Vu0::Scalar(MinF(0.25f, t)));
            rel.z = end.z = 0.0f;
            MeasurePointToSegment((Vec02*)&D_00248D30, &rel, &end, &a, &b);
            if ((b > q->radius || a == 0.0f) && (q->radius * 0.25f < b || 0.0f < p->v150.z)) {
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
            if (p->f2220 != 2 || p->subState != 5) {
                void* held = p->heldObject;
                if (held != best) {
                    InitContactPairFlags(p->world, (Collider*)best);
                    if (held != 0) {
                        InitContactPairFlags(p->world, (Collider*)held);
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
            p->leapTarget = bestPoint;
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

// An edge of a mesh: the two vertices it joins and the two faces it lies between.
struct MeshEdge {
    s16 vertA;
    s16 vertB;
    s16 faceA;
    s16 faceB;
};

// A face of a mesh: its normal, then its slope (the normal's y) at +8.
struct MeshFace {
    Vec02 normal;           // 0x00
    u8 pad10[0x20 - 0x10];
};

s32 ComputeLedgeEdgeOffset(void* unused, Collider* c, MeshEdge* e, Vec02* out)
{
    Mesh03* mesh = &c->meshCopy;
    MeshFace* faces = (MeshFace*)mesh->faces;
    MeshFace* fa = &faces[e->faceA];
    MeshFace* fb = &faces[e->faceB];
    MeshFace* flat;
    if (0.7f < fa->normal.z && fb->normal.z < 0.55f) {
        flat = fb;
    } else if (fa->normal.z < 0.55f && 0.7f < fb->normal.z) {
        flat = fa;
    } else {
        return 0;
    }
    Vec02* verts = (Vec02*)mesh->verts;
    Vec02 d;
    Vec02 n;
    u128 vb = Vu0::Q(verts[e->vertB]);
    u128 va = Vu0::Q(verts[e->vertA]);
    Vu0::Q(d) = Vu0::Sub(vb, va);
    n.z = 0.0f;
    n.y = d.x;
    n.x = -d.y;
    Vu0::Set(n, Vu0::NormalizeOr(Vu0::Q(n), Vu0::Q(g_unitXVector)));
    if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(n), Vu0::Q(flat->normal))) < 0.0f) {
        Vu0::Q(n) = Vu0::MulX(Vu0::Q(n), Vu0::Scalar(-1.0f));
    }
    *out = n;
    return 1;
}


void BuildPerpendicularPair(Quad16* q, void* out, const Vec02* a, const Vec02* b);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
void TransformByMatrixWithW(const Quad16* m, const Vec02* v, f32 w, Vec02* out);
s32 CollectColliderSpans(Collider* self, Vec02* a1, Vec02* a2, s32 a3, ColliderSpan* a4);

s32 TestProbeSegmentsAgainstColliders(Collider* self, void* ctx, Quad16* src)
{
    u8 buf[0x100] __attribute__((aligned(16)));
    Quad16& q = *(Quad16*)buf;
    q = *src;
    s32 hits = 0;
    BuildPerpendicularPair(&q, buf + 0x10, &g_unitZVector, &g_unitZVector);
    BuildMatrixFromRotationAndTranslation((const Vec02*)ctx, (const Mat02*)&q, (Mat4A*)(buf + 0x30));
    for (s32 i = 0; (u32)i < 0x16; i += 2) {
        TransformByMatrixWithW((const Quad16*)(buf + 0x30), &D_00263EC0[i], 1.0f, (Vec02*)(buf + 0x70));
        TransformByMatrixWithW((const Quad16*)(buf + 0x30), &D_00263EC0[i + 1], 1.0f, (Vec02*)(buf + 0x80));
        ContactRow03* n = self->contacts->head;
        while (n) {
            Collider* a = n->other;
            if (!(a->flags538 & 0x40000000000ULL)) {
                Collider* c = (Collider*)a->parts.head;
                while (c) {
                    if (!(c->flags538 & 0x80000000000ULL)) {
                        if (CollectColliderSpans(c, (Vec02*)(buf + 0x70), (Vec02*)(buf + 0x80), 1, (ColliderSpan*)(buf + 0x90)) > 0) {
                            if (i < 4) return 0;
                            if (*(f32*)(buf + 0xD0) == 0.0f) return 0;
                            if (0.7f < *(f32*)(buf + 0xB8)) hits++;
                        }
                    }
                    c = (Collider*)c->link2E4.next;
                }
            }
            n = n->next;
        }
    }
    return hits >= 2;
}

struct EdgeNode : MeshEdge {
    EdgeNode* next8;
    EdgeNode* nextC;
};
struct EdgeGroup {
    u8 pad00[8];
    f32 f8;
    u8 padC[8];
    EdgeNode* list14;
    EdgeNode* list18;
};
struct KeyedPointSet;
struct KeyedEdge;
s32 CollectEntriesForKey(KeyedPointSet* dst, KeyedPointSet* src, s32 key, s32 maxOut, KeyedEdge** out);
s32 CollectTreeNodeSpans(TreeNode03* root, Vec02* a, Vec02* b, s32* groups, s32 max, ColliderSpan* spans);
s32 ComputeLedgeOffsetForContact(Collider* self, Collider* part, Vec02* point, s32 kind, void* arg, Vec02* out)
{
    u8 buf[0x100] __attribute__((aligned(16)));
    Vec02 gap;
    switch (kind) {
    case 1: {
        Mesh03* mesh = &part->meshCopy;
        u128 acc = Vu0::Q(D_00248D30);
        s32 found = 0;
        s32 n = CollectEntriesForKey((KeyedPointSet*)mesh, (KeyedPointSet*)&part->tree, (Vec02*)arg - (Vec02*)mesh->verts, 0x40, (KeyedEdge**)buf);
        for (s32 i = 0; i < n; i++) {
            if (ComputeLedgeEdgeOffset(self, part, ((MeshEdge**)buf)[i], &gap) != 0) {
                found = 1;
                acc = Vu0::Add(acc, Vu0::Q(gap));
            }
        }
        if (found == 0) {
            return 0;
        }
        Vu0::Q(*out) = Vu0::NormalizeOr(acc, Vu0::Q(g_unitXVector));
        break;
    }
    case 3:
        if (ComputeLedgeEdgeOffset(self, part, (MeshEdge*)arg, out) == 0) {
            return 0;
        }
        break;
    case 2: {
        EdgeGroup* g = (EdgeGroup*)arg;
        if (g->f8 < 0.7f) {
            return 0;
        }
        u128 sum = Vu0::Q(D_00248D30);
        s32 found = 0;
        Vec02* verts;
        for (EdgeNode* e = g->list14; e != 0; e = e->next8) {
            if (ComputeLedgeEdgeOffset(self, part, e, (Vec02*)buf) != 0) {
                verts = (Vec02*)part->meshCopy.verts;
                if (CollectTreeNodeSpans(self->tree.nodes, verts + e->vertA, verts + e->vertB, 0, 2, (ColliderSpan*)(buf + 0x10)) > 0) {
                    found = 1;
                    sum = Vu0::Add(sum, Vu0::Q(*(Vec02*)buf));
                }
            }
        }
        for (EdgeNode* e = g->list18; e != 0; e = e->nextC) {
            if (ComputeLedgeEdgeOffset(self, part, e, (Vec02*)buf) != 0) {
                verts = (Vec02*)part->meshCopy.verts;
                if (CollectTreeNodeSpans(self->tree.nodes, verts + e->vertA, verts + e->vertB, 0, 2, (ColliderSpan*)(buf + 0x10)) > 0) {
                    found = 1;
                    sum = Vu0::Add(sum, Vu0::Q(*(Vec02*)buf));
                }
            }
        }
        if (found == 0) {
            return 0;
        }
        Vu0::Q(*out) = Vu0::NormalizeOr(sum, Vu0::Q(g_unitXVector));
        break;
    }
    default:
        break;
    }
    return TestProbeSegmentsAgainstColliders(self, point, (Quad16*)out);
}

extern f32 g_gameTime;
extern f32 D_00274AD0[];
void NotifyContactEnds(World* world, s32 n, Contact03** list);
s32 FindPlaneTreeNodeForPoint(Vec02* p, void* tree);
Contact03* FindPlayerLedgeContact(Player* self, s32* outEnd, Vec02* outPos)
{
    Vec02 tmp;
    Vec02 p;
    Contact03* c;
    if (g_gameTime - self->stateStartTime < 0.15f) {
        return 0;
    }
    Contact03* best = 0;
    for (ContactRow03* row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            s32 side = (Collider*)self != c->end[0].body;
            Collider* other = c->end[1 - side].part;
            Collider* v = other;
            while (v != 0 && (v->flags538 & (0xF000ULL << 24)) == 0) {
                v = (Collider*)v->parent;
            }
            if (v != 0 && (v->flags538 & (0xF000ULL << 24)) == (0x8000ULL << 22)) {
                continue;
            }
            s32 extra;
            switch (c->kind) {
            case 1:
                if (side == 0) {
                    continue;
                }
                extra = c->featureEnd0;
                break;
            case 3:
                if (side == 0) {
                    extra = c->featureEnd1;
                } else {
                    extra = c->featureEnd0;
                }
                break;
            case 2:
                if (side == 1) {
                    continue;
                }
                extra = c->featureEnd1;
                break;
            default:
                continue;
            }
            if (ComputeLedgeOffsetForContact(self, other, &c->end[1 - side].v10, c->kind, (void*)extra, &tmp) == 0) {
                continue;
            }
            if ((self->f4B8 & 2) == 0 || (c->end[1 - side].body->f4B8 & 2) == 0) {
                NotifyContactEnds(self->world, 1, &c);
            }
            if (0.0f < D_00274AD0[side] * *(f32*)((u8*)c + 0xB8)) {
                continue;
            }
            Vu0::Q(p) = Vu0::MulAddX2(Vu0::Vec::Of(c->end[1 - side].v10), Vu0::Vec::Of(tmp), Vu0::Vec::Scalar(-D_00264020),
                                      Vu0::Vec::Of(g_unitZVector), Vu0::Vec::ScalarAtCall(D_00264024)).q;
            if (FindPlaneTreeNodeForPoint(&p, other->tree.nodes) != 0) {
                continue;
            }
            if (best == 0 || !(c->end[1 - side].v10.z < best->end[1 - side].v10.z)) {
                *outEnd = side;
                *outPos = tmp;
                best = c;
            }
        }
    }
    return best;
}

s32 ChoosePlayerNextState(Player* self)
{
    s32 r;
    if (0.0f < self->stickLevel) {
        if (self->sixWayBlend != 0) {
            r = 1;
        } else {
            r = self->eightWayBlend ? 5 : 0;
        }
    } else r = 0;
    return r;
}

s32 IsObjectAttached(BaseObject* self);
void RecordCameraTimestamp(Camera* camera);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInSphere(World* world, Collider* skip, f32 radius, Vec02* center, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
PlacedObject* FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list);
// A hit CollectMeshHits gives (0x30 bytes): its point first.
struct MeshPointHit {
    Vec02 point;
    u8 pad10[0x30 - 0x10];
};
struct FaceRef;
struct MeshHitEntry;
struct ValueRange;
s32 CollectMeshHits(Vec02* center, f32 radius, s32 count, FaceRef* list, FaceRef* cursor, Mesh03* mesh, s32 cap, MeshHitEntry* out);
s32 IsInsideRange(ValueRange* span, f32 x);
s32 RandomIntInRange(s32 lo, s32 hi);
extern List01 g_class75List;

// A walk of a list that RemoveFromList keeps valid: the frame is pushed on g_activeListFrames
// (list_iter.h) and each step reads the next item through the link (as effect_spawner.cpp's).
struct BeginListWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = ((List01*)it->list)->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

template <class T> struct NextInList {
    static T* Of(ListFrame* it)
    {
        T* obj = *(T**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

// v made unit length, or fallback when v is shorter than 0.0001, over vector values (as
// effect_spawner.cpp's): this function's search loop leaves cse2 a jump to change, so jump.c runs
// again after it and would turn the u128 NormalizeOr's arms into a preset of the fallback
// (docs/toolchain/conditional-moves.md); the copies of the vector values keep the arms.
static inline Vu0::Vec NormalizedOr(Vu0::Vec v, Vu0::Vec fallback)
{
    u128 len = Vu0::Length(v.q);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        return fallback;
    }
    Vu0::Vec r;
    r.q = Vu0::DivX(v.q, len);
    return r;
}

// The player's reach of the frame with the object at 0x25E4: the class 0x75 objects near its
// point at 0x6A0 (within 300, 500 under a class 0x58 parent, and within 150 up or down) and the
// colliders gathered around it (the attached ones whose mesh reaches the point within that height,
// or that are near enough themselves) become queries of kind 0x20 aimed from the point.
void CollectPlayerHoldQueries(Player* self)
{
    f32 band[2];
    ListFrame fr;
    s32 count;
    Collider** list;
    Class75Object* n;
    s32 i;

    if (!IsObjectAttached((BaseObject*)self->f25D8[3])) {
        return;
    }
    RecordCameraTimestamp(g_camera);
    PushBackMemoryMark();
    GatherCollidersInSphere(self->world, self, D_00264028, &self->v140, 0, 0, &count, &list);
    for (i = 0; i < count; i++) {
        list[i]->flags538 |= (u64)0x8000 << 47;
    }
    band[0] = self->groundContactPoint.z + D_00264038[0];
    band[1] = self->groundContactPoint.z + D_00264038[1];
    BeginListWalk::Of(&fr, &g_class75List);
    n = NextInList<Class75Object>::Of(&fr);
    while (n != 0) {
        NodeQuery q;
        Vec02 pos;
        f32 range = D_00264028;
        PlacedObject* p;
        s32 far;
        for (p = (PlacedObject*)n->parent; p != 0; p = (PlacedObject*)p->parent) {
            if ((p->desc->flags & 2) && (((Collider*)p)->flags538 & ((u64)0x8000 << 47))) {
                goto next;
            }
            if (IsObjectOfKind(p, 0x58)) {
                range = D_0026402C;
            }
        }
        GetObjectWorldPosition(n, &pos);
        far = range < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->groundContactPoint)),
                                                         Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->groundContactPoint))))) - n->scale;
        if (far) {
            goto next;
        }
        if (pos.z + n->scale < band[0] || band[1] < pos.z - n->scale) {
            goto next;
        }
        q.Clear();
        q.p00 = self;
        q.hold = n;
        {
            Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->groundContactPoint));
            Vu0::Q(q.pos) = Vu0::Q(pos);
            Vu0::Set(q.dir, Vu0::MulX(NormalizedOr(d, Vu0::Vec::Of(g_unitXVector)), Vu0::Vec::ScalarAtCall(D_00264030)).q);
            q.weight = self->mass * D_00264034;
            q.kind = 0x20;
        }
        FindNodeForQuery(&q, 0, 0);
    next:
        n = NextInList<Class75Object>::Of(&fr);
    }
    for (i = 0; i < count; i++) {
        Collider* o = list[i];
        NodeQuery q;
        if (!IsObjectAttached(o)) {
            continue;
        }
        if (o->flags538 & ((u64)0x8000 << 25)) {
            s32 out = D_00264028 < Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(self->groundContactPoint))))
                || o->v140.z + o->radius3CC < band[0] || band[1] < o->v140.z - o->radius3CC;
            if (out) {
                continue;
            }
        } else if (o->tree.nodes != 0) {
            MeshPointHit hits[32];
            s32 hitCount = CollectMeshHits(&self->groundContactPoint, D_00264028, o->tree.count2, (FaceRef*)o->tree.nodes, 0, &o->meshCopy, 32, (MeshHitEntry*)hits);
            s32 j;
            for (j = 0; j < hitCount; j++) {
                if (IsInsideRange((ValueRange*)band, hits[j].point.z)) {
                    break;
                }
            }
            if (j >= hitCount) {
                continue;
            }
        }
        q.Clear();
        q.p00 = self;
        q.hold = o;
        if (o->meshCopy.vertCount > 0) {
            q.pos = ((Vec02*)o->meshCopy.verts)[RandomIntInRange(0, o->meshCopy.vertCount - 1)];
        } else {
            q.pos = o->v140;
        }
        {
            Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(o->v140), Vu0::Vec::Of(self->groundContactPoint));
            Vu0::Set(q.dir, Vu0::MulX(NormalizedOr(d, Vu0::Vec::Of(g_unitXVector)), Vu0::Vec::ScalarAtCall(D_00264030)).q);
            q.weight = self->mass;
            q.weight *= D_00264034;
            q.kind = 0x20;
        }
        FindNodeForQuery(&q, 0, 0);
    }
    for (i = 0; i < count; i++) {
        list[i]->flags538 &= ~((u64)0x8000 << 47);
    }
    PopBackMemoryMark();
    g_activeListFrames = fr.prev;
}

void* AllocateBackMemory(s32 size);
void SolveActiveSetSystem(s32 count, u8* data, f32* values, f32* out);
// Whether the contacts hold the player down: the least-squares push of the contact normals
// against straight down (the Gram matrix of the normals, the dots with down, the bounded solve),
// summed from down; true when the sum still points up by more than 0.1.
// Each dot is stored with Vu0::StoreX: the qmfc2 is then a reload, in v0, and reload hands its
// registers out in turn (allocate_reload_reg starts after the last one it gave), so the copy of
// the spilled down vector after the solve takes v1 (docs/toolchain/reloads-and-stores.md,
// "A reload where ours had a pseudo").
s32 ShouldPlayerLaunchAtTarget(Player* self)
{
    Vec02 acc;
    ContactRow03* row;
    Contact03* c;
    s32 n = 0;
    f32 now = g_gameTime;
    if (now - self->subStateStartTime < 1.0f) {
        return 0;
    }
    if (now - *(f32*)((u8*)self + 0x2238) < 1.0f) {
        return 0;
    }
    *(f32*)((u8*)self + 0x2238) = now;
    if (self->groundContact != 0) {
        return 0;
    }
    Contacts03* ct = self->contacts;
    if (ct != 0) {
        for (row = ct->head; row != 0; row = row->next) {
            for (c = row->head; c != 0; c = c->next) {
                n++;
            }
        }
    }
    if (n == 0) {
        return 0;
    }
    PushBackMemoryMark();
    Vu0::Vec down = Vu0::MulX(Vu0::Vec::Of(g_unitZVector), Vu0::Vec::Scalar(-1.0f));
    f32* gram = (f32*)AllocateBackMemory(n * n * 4);
    f32* rhs = (f32*)AllocateBackMemory(n * 4);
    f32* sol = (f32*)AllocateBackMemory(n * 4);
    f32* p = gram;
    for (row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            Vu0::Vec na = Vu0::Vec::Of(c->normal);
            if (c->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Vec::Scalar(-1.0f));
            }
            for (ContactRow03* rb = self->contacts->head; rb != 0; rb = rb->next) {
                for (Contact03* b = rb->head; b != 0; b = b->next) {
                    Vu0::Vec nb = Vu0::Vec::Of(b->normal);
                    if (b->end[0].body != (Collider*)self) {
                        nb = Vu0::MulX(nb, Vu0::Vec::Scalar(-1.0f));
                    }
                    Vu0::StoreX(*p, Vu0::Dot(na, nb).q);
                    p++;
                }
            }
        }
    }
    p = rhs;
    for (row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            Vu0::Vec na = Vu0::Vec::Of(c->normal);
            if (c->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Vec::Scalar(-1.0f));
            }
            Vu0::StoreX(*p, Vu0::Dot(na, down).q);
            p++;
        }
    }
    SolveActiveSetSystem(n, (u8*)gram, rhs, sol);
    Vu0::Q(acc) = down.q;
    p = sol;
    for (row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            Vu0::Vec na = Vu0::Vec::Of(c->normal);
            if (c->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Vec::Scalar(-1.0f));
            }
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Vec::Of(acc), na, Vu0::Vec::Scalar(*p++)).q;
        }
    }
    PopBackMemoryMark();
    return -0.1f < acc.z;
}

extern f32 D_00263E50;
extern f32 D_00263E54;
extern f32 D_00263E70;
extern f32 D_00263E74;
extern f32 D_00264040;
extern f32 D_00264044;
extern f32 D_00264048[2];
void PlaceOnTargetCurve(TargetCurve* self, Vec02* out, f32* angleOut, f32 t);
void PlaceOnTargetPoint(TargetPoint* self, Vec02* out, f32* angleOut, f32 t);
s32 AimPlayerAtTarget(Player* self);
Contact03* FindPlayerLedgeContact(Player* self, s32* end, Vec02* at);
s32 ShouldPlayerLaunchAtTarget(Player* self);
void LaunchPlayerAtTarget(Player* self, TargetHit* s2, f32 f);
void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);
s32 ChoosePlayerNextState(Player* self);
f32 GetAnimationMarkerTime(Animation* self, s32 key);
void CollectPlayerHoldQueries(Player* self);
void SeekAnimationPlayer(AnimationPlayer* self, s32 mode, f32 a, f32 b);
void TransformPointAtTime(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);
void ScorePlayerLeapToPoint(Player* self, BaseObject* obj, Vec02* point, f32* out1, Vec02* out2, Vec02* out3, f32 t);
void EvaluateHermiteVectorSegment(f32 dur, f32 t, f32 k, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, Vec02* pos, Vec02* vel, Vec02* acc);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void SetPlayerState(Player* self, s32 a, s32 b);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
extern f32 g_gameTime;
extern f32 g_gameClock[];
extern u16 D_00262D18;

struct Leap_17F018 { u8 pad00[0x18]; f32 time; u8 pad1C[0x20 - 0x1C]; Vec02 aim; Vec02 land; };
struct Track_17F018;
struct TrackDesc_17F018 { void* m0; void (*m1)(Track_17F018* self, f32 t, Vec02* out, s32 a); };
struct Track_17F018 { TrackDesc_17F018* desc; };
struct TrackOwner_17F018 { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; Track_17F018* track; };
struct LeapTarget_17F018 { u8 pad00[0x18]; void* frame; u8 pad1C[0x40 - 0x1C]; union { Vec02 pos; s32 curveAttachKind; }; u8 pad50[0x58 - 0x50]; s32 pointAttachKind; };
struct Anim_17F018 { u8 pad00[0x14]; f32 f14; f32 f18; };

// The airborne player's step. Each leap state reads the game clock through a pointer of its own,
// formed before the leap record is loaded, as retail's order shows; state 6's test is written with
// named values so that cross-jumping merges it into state 7's compare.
void UpdatePlayerState2(Player* p)
{
    Vec02 at;
    Vec02 b;
    Vec02 c;
    s32 end;
    if (p->aimMode == -1) {
        switch (p->subState) {
        case 13:
            ((void (*)(void*, s32, f32*, f32))PlaceOnTargetPoint)(p->targetPoint, 0, &p->f638, p->targetPointPlace);
            break;
        case 12:
            ((void (*)(void*, s32, f32*, f32))PlaceOnTargetCurve)(p->targetCurve, 0, &p->f638, p->targetCurvePos);
            break;
        default:
            if (D_00263E54 < Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(p->v150), Vu0::Q(p->v150))))) {
                p->f638 = ArctangentOfRatio(p->v150.y, p->v150.x);
            }
            break;
        case 0:
            p->f638 = p->stickHeading;
            break;
        case 7:
        case 8:
            break;
        }
    } else if (AimPlayerAtTarget(p) == 0) {
        p->f638 = p->stickHeading;
    }
    switch (p->jumpStickPhase) {
    case 0:
        if (p->stickLevel == 1.0f) {
            p->jumpStickPhase = 1;
            p->stickFullTime = g_gameTime;
        } else if (D_00263E70 < g_gameTime - p->jumpStartTime) {
            p->steerKeepsDirection = 1;
        }
        break;
    case 1:
        if (p->stickLevel < 1.0f) {
            p->jumpStickPhase = 2;
            p->stickReleaseTime = g_gameClock[1];
            if (g_gameClock[1] - p->stickFullTime < D_00263E74) {
                p->steerKeepsDirection = 1;
            }
        }
        break;
    case 3:
        if (0.0f < p->stickLevel) {
            p->steerKeepsDirection = 1;
        }
        break;
    }
    Contact03* hit = FindPlayerLedgeContact(p, &end, &at);
    if (hit != 0) {
        ContactEnd03* e = &hit->end[1 - end];
        void* part = e->part;
        p->ledgeCollider = part;
        TransformPointBetweenFrames(0, (PlacedObject*)part, &e->v10, (Vec02*)p->ledgeLocalPoint);
        p->ledgeKind = hit->kind;
        s32 key;
        if (end == 0) {
            key = hit->featureEnd1;
        } else {
            key = hit->featureEnd0;
        }
        p->ledgeKey = key;
        p->ledgeOffset = at;
        SetPlayerState(p, 8, -1);
        return;
    }
    if (ShouldPlayerLaunchAtTarget(p) != 0) {
        LaunchPlayerAtTarget(p, 0, 0.0f);
        return;
    }
    switch (p->subState) {
    case 0:
        if (p->v150.z < 0.0f) {
            SetPlayerState(p, 2, 2);
        } else if (D_00263E50 < g_gameTime - p->subStateStartTime) {
            if (!(D_00262D18 & 0x40) && p->jumpStickPhase != 3) {
                p->steerKeepsDirection = 1;
            }
            SetPlayerState(p, 2, 1);
        }
        break;
    case 1:
    case 5:
        if (p->groundContact != 0 && 0.15f < g_gameTime - p->stateStartTime) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        } else if (p->v150.z < 0.0f) {
            SetPlayerState(p, 2, 2);
        }
        break;
    case 6:
        if (p->groundContact != 0) {
            f32 k = 0.15f;
            f32 t0 = p->stateStartTime;
            if (k < g_gameTime - t0) {
                SetPlayerState(p, ChoosePlayerNextState(p), -1);
            }
        }
        break;
    case 2:
        if (p->groundContact != 0) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    case 4: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->selfPoseSource;
        if (rec->time < clock[1]) {
            p->targetMode = 2;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        ComputeObjectFrameAtTime((PlacedObject*)p->heldObject, 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->selfPoseSource)->aim = b;
        ((Leap_17F018*)p->selfPoseSource)->aim.z += 75.0f;
        ((Leap_17F018*)p->selfPoseSource)->land = c;
        ((Leap_17F018*)p->selfPoseSource)->land.z = p->v150.z + (((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 7:
        if (p->groundContact != 0 && D_00264040 < g_gameTime - p->subStateStartTime) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    case 8:
        if (p->groundContact != 0 && D_00264044 < g_gameTime - p->subStateStartTime) {
            f32 t = GetAnimationMarkerTime((Animation*)p->markerAnim, 0x1BB);
            if (((Anim_17F018*)p->stateAnimPlayer)->f14 < t) {
                CollectPlayerHoldQueries(p);
                SeekAnimationPlayer((AnimationPlayer*)p->stateAnimPlayer, 0, t, ((Anim_17F018*)p->stateAnimPlayer)->f18);
            }
        }
        break;
    case 9: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->selfPoseSource;
        if (rec->time < clock[1]) {
            SetPlayerState(p, 2, 2);
            break;
        }
        b = ((LeapTarget_17F018*)p->leapTarget)->pos;
        c = D_00248D30;
        TransformPointAtTime((PlacedObject*)(((LeapTarget_17F018*)p->leapTarget)->frame), 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->selfPoseSource)->aim = b;
        ((Leap_17F018*)p->selfPoseSource)->aim.z += 75.0f;
        ((Leap_17F018*)p->selfPoseSource)->land = c;
        ((Leap_17F018*)p->selfPoseSource)->land.z = p->v150.z + (((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 10: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->selfPoseSource;
        if (rec->time < clock[1]) {
            p->targetMode = 5;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        b = ((LeapTarget_17F018*)p->targetNode)->pos;
        c = D_00248D30;
        TransformPointAtTime((PlacedObject*)(((LeapTarget_17F018*)p->targetNode)->frame), 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->selfPoseSource)->aim = b;
        ((Leap_17F018*)p->selfPoseSource)->aim.z += 75.0f;
        ((Leap_17F018*)p->selfPoseSource)->land = c;
        ((Leap_17F018*)p->selfPoseSource)->land.z = p->v150.z + (((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 11: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->selfPoseSource;
        if (rec->time < clock[1]) {
            p->targetMode = 4;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        Track_17F018* t = ((TrackOwner_17F018*)p->targetTrack)->track;
        if (t->desc->m1 != 0) {
            t->desc->m1(t, p->trackPos, &b, 0);
        }
        TransformPointAtTime((PlacedObject*)(((TrackOwner_17F018*)p->targetTrack)->frame), 0, &b, 0, 0, 0, ((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1]);
        ((Leap_17F018*)p->selfPoseSource)->aim = b;
        ((Leap_17F018*)p->selfPoseSource)->aim.z += 75.0f;
        break;
    }
    case 13: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->selfPoseSource;
        if (rec->time < clock[1]) {
            p->targetMode = ((LeapTarget_17F018*)p->targetPoint)->pointAttachKind;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        PlaceOnTargetPoint((TargetPoint*)p->targetPoint, &b, 0, p->targetPointPlace);
        TransformPointBetweenFrames(0, (PlacedObject*)(((LeapTarget_17F018*)p->targetPoint)->frame), &b, &b);
        c = D_00248D30;
        TransformPointAtTime((PlacedObject*)(((LeapTarget_17F018*)p->targetPoint)->frame), 0, &b, 0, &c, 0, ((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1]);
        ((Leap_17F018*)p->selfPoseSource)->aim = b;
        ((Leap_17F018*)p->selfPoseSource)->aim.z += 75.0f;
        ((Leap_17F018*)p->selfPoseSource)->land = c;
        ((Leap_17F018*)p->selfPoseSource)->land.z = p->v150.z + (((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 12: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->selfPoseSource;
        if (rec->time < clock[1]) {
            p->targetMode = ((LeapTarget_17F018*)p->targetCurve)->curveAttachKind;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        PlaceOnTargetCurve((TargetCurve*)p->targetCurve, &b, 0, p->targetCurvePos);
        TransformPointBetweenFrames(0, (PlacedObject*)(((LeapTarget_17F018*)p->targetCurve)->frame), &b, &b);
        c = D_00248D30;
        TransformPointAtTime((PlacedObject*)(((LeapTarget_17F018*)p->targetCurve)->frame), 0, &b, 0, &c, 0, ((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1]);
        ((Leap_17F018*)p->selfPoseSource)->aim = b;
        ((Leap_17F018*)p->selfPoseSource)->aim.z += 75.0f;
        ((Leap_17F018*)p->selfPoseSource)->land = c;
        ((Leap_17F018*)p->selfPoseSource)->land.z = p->v150.z + (((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 14: {
        Leap_17F018* rec = (Leap_17F018*)p->selfPoseSource;
        if (rec->time < g_gameTime) {
            SetPlayerState(p, 3, 0x33);
        } else {
            ScorePlayerLeapToPoint(p, (BaseObject*)(((TrackOwner_17F018*)p->boundObject)->frame), (Vec02*)((u8*)p->boundObject + 0x40), 0, &rec->aim, &rec->land, rec->time - g_gameTime);
        }
        break;
    }
    case 15:
        if (((Leap_17F018*)p->selfPoseSource)->time < g_gameTime) {
            SetPlayerState(p, 7, 0x17);
        }
        break;
    case 3:
        if (p->groundContact != 0) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    }
    if (p->subState < 16) {
        if (p->subState >= 9) {
            f32 t = ((Leap_17F018*)p->selfPoseSource)->time - g_gameClock[1] + g_gameClock[2];
            EvaluateHermiteVectorSegment(t, 0.0f, 1.0f, &p->pos, &p->v150, &((Leap_17F018*)p->selfPoseSource)->aim, &((Leap_17F018*)p->selfPoseSource)->land, 0, 0, &b);
            EvaluateHermiteVectorSegment(t, t, 1.0f, &p->pos, &p->v150, &((Leap_17F018*)p->selfPoseSource)->aim, &((Leap_17F018*)p->selfPoseSource)->land, 0, 0, &c);
            if (D_00264048[0] < (Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(b))) + Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(c)))) * (t * 0.5f)) {
                SetPlayerState(p, 2, 2);
            }
        }
    }
}

s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots);

s32 SolveArrivalTimeAtHeight(Player* self, Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out)
{
    f32 roots[2];
    s32 count = SolveQuadratic(self->gravity.z * 0.5f, b->z - d->z, a->z - c->z, roots);
    switch (count) {
    case 0:
        return 0;
    case 1:
        break;
    case 2:
        roots[0] = (roots[1] >? roots[0]);
        break;
    }
    if (roots[0] <= 0.0f) {
        return 0;
    }
    *out = roots[0];
    return 1;
}

static inline f32 MaxF(f32 a, f32 b) { return a >? b; }

// The state test with two equal arms is retail's: its dead `li v1,3` and `lw v0,0x2220` are
// what reorg leaves of a compare with 3 once the arms' repeated stores are deleted, and its
// join is why out->z is read again from memory for the max (docs/TOOLCHAIN.md, CSE).
void ComputePlayerJumpVelocity(Player* self, Vec02* out)
{
    f32 z;
    switch (self->jumpKind) {
    case 1:
        z = D_00263E80 * Fpu::Sqrt(self->gravityScale);
        break;
    case 4:
        z = D_00263E8C * Fpu::Sqrt(self->gravityScale);
        break;
    case 3:
        z = D_00263E88 * Fpu::Sqrt(self->gravityScale);
        break;
    case 0:
    case 2:
        z = Fpu::Sqrt(MaxF(0.0f, ((self->v140.z - (*(f32*)((u8*)self + 0x6A8) + D_00263E84)) + (self->v140.z - (*(f32*)((u8*)self + 0x6A8) + D_00263E84))) * self->gravity.z));
        break;
    }
    *out = self->v150;
    out->z = z;
    if (self->f2220 == 3) {
        out->z = z;
    } else {
        out->z = z;
    }
    out->z = out->z >? self->v150.z;
}

static inline f32 EvalClampedQuadratic(const f32* poly, const f32* range, f32 z)
{
    f32 v = poly[0] + z * (poly[1] + z * poly[2]);
    f32 lo = range[0];
    f32 hi = range[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    return v;
}

void ComputeUpwardBoostVelocity(PlacedObject* self, Vec02* out)
{
    *out = self->v150;
    f32 z = EvalClampedQuadratic(D_00264050, D_00264060, out->z);
    out->z = z;
    out->z = (z >? self->v150.z);
}
void ComputeUpwardBoostVelocityUnitSlope(PlacedObject* self, Vec02* out)
{
    *out = self->v150;
    f32 z = EvalClampedQuadratic(D_00264070, D_00264080, out->z);
    out->z = z;
    out->z = (z >? self->v150.z);
}

void SetListLinkOffset(List01* self, s32 offset);

void SetPointObjectListLinkOffset(void)
{
    SetListLinkOffset(&g_pointObjects, 0x50);
}

void ClearList(List01* p);

void ClearPointObjectList(void)
{
    ClearList(&g_pointObjects);
}

void RegisterObject(BaseObject* self);
void AppendToList(List01* self, void* item);

void RegisterPointObject(C80* self)
{
    RegisterObject(self);
    AppendToList(&g_pointObjects, self);
}

void UnregisterObject(BaseObject* self);
void RemoveFromList(List01* list, void* item);

void UnregisterPointObject(C80* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_pointObjects, self);
}
