// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"

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
void TurnColliderTowardRotation(void* self, Mat02* rot, void* data, f32 scale);
void ComputePolarOffset(Vec02* out, f32 heading, f32 distance, f32 z);
void SteerColliderTowardPosition(void* self, s32 a, s32 b, Vec02* pos, void* params, f32 dt);
f32 GetAnimationMarkerTime(void* obj, s32 id);
void AddColliderForce(void* target, Vec02* force);
void BuildBasisFromX(Vec02* x, Mat02* out);

void func_0017D248(Player* self)
{
    Vec02 a;
    Vec02 b;
    TurnColliderTowardRotation(self, &self->m660, &self->f6E0, g_gameClock[2]);
    switch (self->f2228) {
    case 6:
        if (0.0001f < self->f634) {
            ComputePolarOffset(&a, self->f630, self->f634 * self->f226C, 0.0f);
            Vu0::Q(b) = Vu0::Add(Vu0::Q(self->v2290), Vu0::Q(a));
            b.z = self->v150.z;
            SteerColliderTowardPosition(self, 0, 0, &b, D_00263E90, g_gameClock[2]);
        }
        break;
    case 8: {
        f32 t0 = GetAnimationMarkerTime(self->f25C8, 0x1BA);
        f32 t1 = GetAnimationMarkerTime(self->f25C8, 0x1BB);
        if (*(f32*)((u8*)self->watched2230 + 0x14) < t1) {
            Vu0::Q(a) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Scalar(-1.0f));
            AddColliderForce(self, &a);
        }
        if (*(f32*)((u8*)self->watched2230 + 0x14) < t0) {
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
        if (self->f2228 == 0) {
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
        if (self->f2228 != 6) {
            f32 speed = self->f700;
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

INCLUDE_RODATA(jtbl_0024B090);
INCLUDE_ASM(func_0017D5D8);

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

s32 func_0017DCE0(void* unused, Collider* c, MeshEdge* e, Vec02* out)
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
void BuildMatrixFromRotationAndTranslation(void* a, Quad16* b, void* out);
void TransformByMatrixWithW(void* a, f32 w, const void* b, void* c);
s32 CollectColliderSpans(Collider* self, void* a1, void* a2, s32 a3, void* a4);

s32 TestProbeSegmentsAgainstColliders(Collider* self, void* ctx, Quad16* src)
{
    u8 buf[0x100] __attribute__((aligned(16)));
    Quad16& q = *(Quad16*)buf;
    q = *src;
    s32 hits = 0;
    BuildPerpendicularPair(&q, buf + 0x10, &g_unitZVector, &g_unitZVector);
    BuildMatrixFromRotationAndTranslation(ctx, &q, buf + 0x30);
    for (s32 i = 0; (u32)i < 0x16; i += 2) {
        TransformByMatrixWithW(buf + 0x30, 1.0f, &D_00263EC0[i], buf + 0x70);
        TransformByMatrixWithW(buf + 0x30, 1.0f, &D_00263EC0[i + 1], buf + 0x80);
        ContactRow03* n = self->contacts->head;
        while (n) {
            Collider* a = n->other;
            if (!(a->flags538 & 0x40000000000ULL)) {
                Collider* c = (Collider*)a->parts.head;
                while (c) {
                    if (!(c->flags538 & 0x80000000000ULL)) {
                        if (CollectColliderSpans(c, buf + 0x70, buf + 0x80, 1, buf + 0x90) > 0) {
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

INCLUDE_ASM(func_0017E088);

extern f32 g_gameTime;
extern f32 D_00274AD0[];
s32 func_0017E088(Player* self, Collider* other, Vec02* point, s32 kind, s32 extra, Vec02* out);
void NotifyContactEnds(void* world, s32 n, Contact03** list);
s32 func_0013E658(Vec02* p, void* tree);
Contact03* func_0017E3C8(Player* self, s32* outEnd, Vec02* outPos)
{
    Vec02 tmp;
    Vec02 p;
    Contact03* c;
    if (g_gameTime - self->f2224 < 0.15f) {
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
                extra = c->fA0;
                break;
            case 3:
                if (side == 0) {
                    extra = c->fA4;
                } else {
                    extra = c->fA0;
                }
                break;
            case 2:
                if (side == 1) {
                    continue;
                }
                extra = c->fA4;
                break;
            default:
                continue;
            }
            if (func_0017E088(self, other, &c->end[1 - side].v10, c->kind, extra, &tmp) == 0) {
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
            if (func_0013E658(&p, other->tree.nodes) != 0) {
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
    if (0.0f < self->f634) {
        if (self->f900 != 0) {
            r = 1;
        } else {
            r = self->fA10 ? 5 : 0;
        }
    } else r = 0;
    return r;
}

INCLUDE_ASM(func_0017E710);

INCLUDE_ASM(func_0017ECE8);

extern f32 D_00263E50;
extern f32 D_00263E54;
extern f32 D_00263E70;
extern f32 D_00263E74;
extern f32 D_00264040;
extern f32 D_00264044;
extern f32 D_00264048[2];
void PlaceOnTargetCurve(void* curve, Vec02* out, s32 a, f32 t);
void PlaceOnTargetPoint(void* point, Vec02* out, s32 a, f32 t);
s32 AimPlayerAtTarget(void* self);
Contact03* func_0017E3C8(Player* self, s32* end, Vec02* at);
s32 func_0017ECE8(Player* self);
void LaunchPlayerAtTarget(Player* self, void* s2, f32 f);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, s32 c, Vec02* vel, s32 d, f32 t);
s32 ChoosePlayerNextState(Player* self);
f32 GetAnimationMarkerTime(void* obj, s32 id);
void func_0017E710(Player* self);
void SeekAnimationPlayer(void* obj, s32 a1, f32 fa, f32 fb);
void TransformPointAtTime(void* frame, s32 a, Vec02* point, s32 b, Vec02* vel, s32 d, f32 t);
void func_001CEB18(f32 t, Player* p, void* frame, void* point, s32 a, Vec02* aim, Vec02* land);
void EvaluateHermiteVectorSegment(f32 t, f32 u, f32 v, void* p0, void* v0, void* p1, void* v1, Vec02* pos, s32 a, Vec02* vel);
void SetPlayerState(Player* self, s32 a, s32 b);
void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);
f32 ArctangentOfRatio(f32 a, f32 b);
extern f32 g_gameTime;
extern f32 g_gameClock[];
extern u16 D_00262D18;

struct Leap_17F018 { u8 pad00[0x18]; f32 time; u8 pad1C[0x20 - 0x1C]; Vec02 aim; Vec02 land; };
struct Track_17F018;
struct TrackDesc_17F018 { void* m0; void (*m1)(Track_17F018* self, f32 t, Vec02* out, s32 a); };
struct Track_17F018 { TrackDesc_17F018* desc; };
struct TrackOwner_17F018 { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; Track_17F018* track; };
struct LeapTarget_17F018 { u8 pad00[0x18]; void* frame; u8 pad1C[0x40 - 0x1C]; union { Vec02 pos; s32 f40; }; u8 pad50[0x58 - 0x50]; s32 f58; };
struct Anim_17F018 { u8 pad00[0x14]; f32 f14; f32 f18; };

// The airborne player's step. Each leap state reads the game clock through a pointer of its own,
// formed before the leap record is loaded, as retail's order shows; state 6's test is written with
// named values so that cross-jumping merges it into state 7's compare.
void func_0017F018(Player* p)
{
    Vec02 at;
    Vec02 b;
    Vec02 c;
    s32 end;
    if (p->f223C == -1) {
        switch (p->f2228) {
        case 13:
            ((void (*)(void*, s32, f32*, f32))PlaceOnTargetPoint)(p->f23A8, 0, &p->f638, p->f23AC);
            break;
        case 12:
            ((void (*)(void*, s32, f32*, f32))PlaceOnTargetCurve)(p->f23A0, 0, &p->f638, p->f23A4);
            break;
        default:
            if (D_00263E54 < Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(p->v150), Vu0::Q(p->v150))))) {
                p->f638 = ArctangentOfRatio(p->v150.y, p->v150.x);
            }
            break;
        case 0:
            p->f638 = p->f630;
            break;
        case 7:
        case 8:
            break;
        }
    } else if (AimPlayerAtTarget(p) == 0) {
        p->f638 = p->f630;
    }
    switch (p->f2270) {
    case 0:
        if (p->f634 == 1.0f) {
            p->f2270 = 1;
            p->f2278 = g_gameTime;
        } else if (D_00263E70 < g_gameTime - p->f2274) {
            p->f2268 = 1;
        }
        break;
    case 1:
        if (p->f634 < 1.0f) {
            p->f2270 = 2;
            p->f227C = g_gameClock[1];
            if (g_gameClock[1] - p->f2278 < D_00263E74) {
                p->f2268 = 1;
            }
        }
        break;
    case 3:
        if (0.0f < p->f634) {
            p->f2268 = 1;
        }
        break;
    }
    Contact03* hit = func_0017E3C8(p, &end, &at);
    if (hit != 0) {
        ContactEnd03* e = &hit->end[1 - end];
        void* part = e->part;
        p->f24A0 = part;
        TransformPointBetweenFrames(0, part, &e->v10, p->f24B0);
        p->f24F0 = hit->kind;
        s32 key;
        if (end == 0) {
            key = hit->fA4;
        } else {
            key = hit->fA0;
        }
        p->f24F4 = key;
        p->v24C0 = at;
        SetPlayerState(p, 8, -1);
        return;
    }
    if (func_0017ECE8(p) != 0) {
        LaunchPlayerAtTarget(p, 0, 0.0f);
        return;
    }
    switch (p->f2228) {
    case 0:
        if (p->v150.z < 0.0f) {
            SetPlayerState(p, 2, 2);
        } else if (D_00263E50 < g_gameTime - p->f222C) {
            if (!(D_00262D18 & 0x40) && p->f2270 != 3) {
                p->f2268 = 1;
            }
            SetPlayerState(p, 2, 1);
        }
        break;
    case 1:
    case 5:
        if (p->f690 != 0 && 0.15f < g_gameTime - p->f2224) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        } else if (p->v150.z < 0.0f) {
            SetPlayerState(p, 2, 2);
        }
        break;
    case 6:
        if (p->f690 != 0) {
            f32 k = 0.15f;
            f32 t0 = p->f2224;
            if (k < g_gameTime - t0) {
                SetPlayerState(p, ChoosePlayerNextState(p), -1);
            }
        }
        break;
    case 2:
        if (p->f690 != 0) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    case 4: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->f2514;
        if (rec->time < clock[1]) {
            p->f239C = 2;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        ComputeObjectFrameAtTime(p->heldObject, 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 7:
        if (p->f690 != 0 && D_00264040 < g_gameTime - p->f222C) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    case 8:
        if (p->f690 != 0 && D_00264044 < g_gameTime - p->f222C) {
            f32 t = GetAnimationMarkerTime(p->f25C8, 0x1BB);
            if (((Anim_17F018*)p->watched2230)->f14 < t) {
                func_0017E710(p);
                SeekAnimationPlayer(p->watched2230, 0, t, ((Anim_17F018*)p->watched2230)->f18);
            }
        }
        break;
    case 9: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->f2514;
        if (rec->time < clock[1]) {
            SetPlayerState(p, 2, 2);
            break;
        }
        b = ((LeapTarget_17F018*)p->f23B4)->pos;
        c = D_00248D30;
        TransformPointAtTime(((LeapTarget_17F018*)p->f23B4)->frame, 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 10: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->f2514;
        if (rec->time < clock[1]) {
            p->f239C = 5;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        b = ((LeapTarget_17F018*)p->f23B8)->pos;
        c = D_00248D30;
        TransformPointAtTime(((LeapTarget_17F018*)p->f23B8)->frame, 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 11: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->f2514;
        if (rec->time < clock[1]) {
            p->f239C = 4;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        Track_17F018* t = ((TrackOwner_17F018*)p->f23BC)->track;
        if (t->desc->m1 != 0) {
            t->desc->m1(t, p->f23C0, &b, 0);
        }
        TransformPointAtTime(((TrackOwner_17F018*)p->f23BC)->frame, 0, &b, 0, 0, 0, ((Leap_17F018*)p->f2514)->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        break;
    }
    case 13: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->f2514;
        if (rec->time < clock[1]) {
            p->f239C = ((LeapTarget_17F018*)p->f23A8)->f58;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        PlaceOnTargetPoint(p->f23A8, &b, 0, p->f23AC);
        TransformPointBetweenFrames(0, ((LeapTarget_17F018*)p->f23A8)->frame, &b, &b);
        c = D_00248D30;
        TransformPointAtTime(((LeapTarget_17F018*)p->f23A8)->frame, 0, &b, 0, &c, 0, ((Leap_17F018*)p->f2514)->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 12: {
        const f32* clock = g_gameClock;
        Leap_17F018* rec = (Leap_17F018*)p->f2514;
        if (rec->time < clock[1]) {
            p->f239C = ((LeapTarget_17F018*)p->f23A0)->f40;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        PlaceOnTargetCurve(p->f23A0, &b, 0, p->f23A4);
        TransformPointBetweenFrames(0, ((LeapTarget_17F018*)p->f23A0)->frame, &b, &b);
        c = D_00248D30;
        TransformPointAtTime(((LeapTarget_17F018*)p->f23A0)->frame, 0, &b, 0, &c, 0, ((Leap_17F018*)p->f2514)->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    }
    case 14: {
        Leap_17F018* rec = (Leap_17F018*)p->f2514;
        if (rec->time < g_gameTime) {
            SetPlayerState(p, 3, 0x33);
        } else {
            func_001CEB18(rec->time - g_gameTime, p, ((TrackOwner_17F018*)p->f2204)->frame, (u8*)p->f2204 + 0x40, 0, &rec->aim, &rec->land);
        }
        break;
    }
    case 15:
        if (((Leap_17F018*)p->f2514)->time < g_gameTime) {
            SetPlayerState(p, 7, 0x17);
        }
        break;
    case 3:
        if (p->f690 != 0) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    }
    if (p->f2228 < 16) {
        if (p->f2228 >= 9) {
            f32 t = ((Leap_17F018*)p->f2514)->time - g_gameClock[1] + g_gameClock[2];
            EvaluateHermiteVectorSegment(t, 0.0f, 1.0f, &p->pos, &p->v150, &((Leap_17F018*)p->f2514)->aim, &((Leap_17F018*)p->f2514)->land, 0, 0, &b);
            EvaluateHermiteVectorSegment(t, t, 1.0f, &p->pos, &p->v150, &((Leap_17F018*)p->f2514)->aim, &((Leap_17F018*)p->f2514)->land, 0, 0, &c);
            if (D_00264048[0] < (Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(b))) + Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(c)))) * (t * 0.5f)) {
                SetPlayerState(p, 2, 2);
            }
        }
    }
}

s32 SolveQuadratic(f32* roots, f32 a, f32 b, f32 c);

s32 SolveArrivalTimeAtHeight(Player* self, Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out)
{
    f32 roots[2];
    s32 count = SolveQuadratic(roots, self->gravity.z * 0.5f, b->z - d->z, a->z - c->z);
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

INCLUDE_RODATA(jtbl_0024B150);
INCLUDE_ASM(func_0017FB78);

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

void func_0017FC48(PlacedObject* self, Vec02* out)
{
    *out = self->v150;
    f32 z = EvalClampedQuadratic(D_00264050, D_00264060, out->z);
    out->z = z;
    out->z = (z >? self->v150.z);
}
void func_0017FCC8(PlacedObject* self, Vec02* out)
{
    *out = self->v150;
    f32 z = EvalClampedQuadratic(D_00264070, D_00264080, out->z);
    out->z = z;
    out->z = (z >? self->v150.z);
}

void SetListLinkOffset(void* self, s32 value);

void SetPointObjectListLinkOffset(void)
{
    SetListLinkOffset(&g_pointObjects, 0x50);
}

void ClearList(void* p);

void ClearPointObjectList(void)
{
    ClearList(&g_pointObjects);
}

void RegisterObject(void* self);
void AppendToList(void* table, void* self);

void RegisterPointObject(C80* self)
{
    RegisterObject(self);
    AppendToList(&g_pointObjects, self);
}

void UnregisterObject(void* self);
void RemoveFromList(void* table, void* self);

void UnregisterPointObject(C80* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_pointObjects, self);
}
