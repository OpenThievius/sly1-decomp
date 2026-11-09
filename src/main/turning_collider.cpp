// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "vu0.h"
#include "globals.h"
#include "object_link.h"
#include "attachment.h"
#include "pad_record.h"
#include "game_clock.h"
#include "vu0.h"


// The file's .data, in retail's order.
f32 D_00274AD0[2] = { 1.0f, -1.0f };
ObjectLink g_turningColliderLinks[6] = { {6, 0x36, 0x61C}, {6, 0x35, 0x618}, {6, 0x37, 0x628}, {6, 0x3A, 0x62C}, {6, 0x38, 0x620}, {6, 0x3B, 0x624} };
f32 D_00274B20 = 0.5f;
Vec02 D_00274B30 = { 1.0f, -1.0f, 0.0f, 0.0f };
s32 D_00274B40[3] = { 0x453B8000, 0, 0x40000000 };
s32 D_00274B50[3] = { 0x453B8000, 0, 0x3E800000 };
f32 D_00274B5C = 0;
f32 D_00274B60[1] = { 0.1f };
f32 D_00274B64 = -0.033f;
f32 D_00274B68[3] = { 300.0f, 0.0f, 0.25f };
f32 D_00274B74 = 1.5f;
f32 D_00274B78 = 2.0f;
f32 D_00274B7C = 0.0333333351f;
f32 D_00274B80[3] = { 25.0f, 0.0f, 0.25f };

// Three words copied whole from .data to a place only 4-aligned: the first two as one
// unaligned doubleword.
struct __attribute__((packed)) UnalignedPair { u64 v; };
struct ThreeWords { UnalignedPair a; s32 b; };

void InitSwitchedCollider(void* self);
void ScaleTurningColliderRamp(void* self, f32 x);

void InitTurningCollider(TurningCollider* self)
{
    InitSwitchedCollider(self);
    self->f700 = 1.0f;
    self->f360 = D_00274B20;
    ScaleTurningColliderRamp(self, 1.0f);
    self->v6F0 = D_00274B30;
    *(ThreeWords*)self->f710 = *(ThreeWords*)D_00274B40;
    *(ThreeWords*)self->f704 = *(ThreeWords*)D_00274B50;
}

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* table);
void SetTurningColliderLinkFlag(void* self, s32 a1);

void StartTurningCollider(TurningCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 6, g_turningColliderLinks);
    SetTurningColliderLinkFlag(self, 1);
    if (self->f628 == 0) {
        self->f610 = self->f620;
    } else {
        self->f610 = self->f628;
    }
    if (self->f62C == 0) {
        self->f614 = self->f624;
    } else {
        self->f614 = self->f62C;
    }
    Mat02* dst = &self->m660;
    *dst = g_identityMatrix;
}

void SetTurningColliderLinkFlag(TurningCollider* self, s32 a1)
{
    PlacedObject* h = (PlacedObject*)self->f61C;
    if (h != 0) {
        Rec2195_224* s = h->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else s->f98 &= ~2;
        }
    }
    PlacedObject* v = (PlacedObject*)self->f618;
    if (v != 0) {
        Rec2195_224* s = v->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else ((PlacedObject*)self->f61C)->f224->f98 &= ~2;
        }
    }
}

struct FollowProbe {
    u8 pad00[0x50];
    s32 f50;
    u8 pad54[0x60 - 0x54];
    Vec02 v60;
    Vec02 v70;
    f32 f80;
    u8 pad84[0xD0 - 0x84];
    f32 fD0;
};
void TransformPointBetweenFrames(void* from, void* to, void* in, void* out);

void func_001C4618(s32 a0, PlacedObject* self, s32 a2, PlacedObject* obj, FollowProbe* out, f32 radius)
{
    Vec02 pos;
    Vec02 dir;
    out->f50 = 0;
    Rec2195_224* rec = obj->f224;
    if (rec != 0 && (rec->fB0 & 0x20) != 0) {
        TransformPointBetweenFrames(obj, 0, (u8*)rec + 0x60, &pos);
        Vu0::Q(dir) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(((PlacedObject*)obj->f224->f80)->v140));
        u128 len = Vu0::Length(Vu0::Q(dir));
        const Vec02* fallback = &g_unitXVector;
        if (Vu0::ToFloat(len) < 0.0001f) {
            dir = *fallback;
        } else {
            Vu0::Q(dir) = Vu0::DivX(Vu0::Q(dir), len);
        }
        f32 dist = Vu0::ToFloatMoved(len) - 15.0f;
        out->f80 = dist;
        if (dist < 0.0001f) {
            return;
        }
        u128 base = Vu0::MulAddX(Vu0::Q(self->v140), Vu0::Q(g_unitZVector), Vu0::Scalar(-radius));
        u128 tip = Vu0::MulAddX(base, Vu0::Q(dir), Vu0::Scalar(-dist));
        Vu0::Q(out->v70) = tip;
        out->f50 = 1;
        Vu0::Q(out->v60) = base;
        out->fD0 = 3.40282347e+38f;
    }
}

s32 CollectColliderSpansInTree(void* self, void* a1, void* a2, void* a3, s32 a4, void* a5);

void KeepNearestPartSpan(void* unused, void* a1, void* a2, Part07* self)
{
    ColliderSpan ents[2];
    s32 n;
    s32 idx;
    if (self->f50 == 0) return;
    n = CollectColliderSpansInTree(a1, a2, &self->v70, &self->v60, 2, ents);
    idx = 0;
    if (n > 0) {
        if (ents[0].time[0] == 0.0f) idx = 1;
    }
    if (!(idx < n)) return;
    if (ents[idx].time[0] < self->span.time[0]) {
        self->span = ents[idx];
    }
}

void TransformPointBetweenFrames(void* from, void* to, void* in, void* out);
void TransformDirectionBetweenFrames(void* from, void* to, void* in, void* out);
void ComputeObjectMotionInFrame(void* a, s32 b, void* c, void* d, s32 e, s32 f, s32 g);

void func_001C4848(s32 a0, PlacedObject* other, PlacedObject* self, Part07* rec)
{
    Vec02 dir;
    Vec02 pos;
    Vec02 vel;
    if (rec->f50 != 0) {
        rec->f50 = 0;
        if (rec->span.time[0] != 3.40282347e+38f) {
            u128 k = Vu0::FromFloatAt(rec->f80);
            Vu0::Set(vel, k);
            Vu0::Q(dir) = Vu0::DivX(Vu0::Sub(Vu0::Q(rec->v60), Vu0::Q(rec->v70)), k);
            Vu0::Q(pos) = Vu0::Add(Vu0::Add(Vu0::Q(self->v140), Vu0::Sub(Vu0::Q(rec->span.q[0]), Vu0::Q(rec->v60))), Vu0::Q(dir));
            TransformPointBetweenFrames(0, self->parent, &pos, &pos);
            self->desc02()->m1D(self, &pos);
            ComputeObjectMotionInFrame(self, 0, &other->v140, &vel, 0, 0, 0);
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(vel), Vu0::Q(rec->span.q[2])));
            if (d < 0.0f) {
                TransformDirectionBetweenFrames(0, self->parent, &rec->span.q[2], &dir);
                const Desc02* ds = self->desc02();
                Vu0::Q(vel) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(dir), Vu0::Scalar(-d));
                ds->m20(self, &vel);
            }
        }
    }
}


void DrawCollider(void);

void DrawTurningCollider(void)
{
    DrawCollider();
}

void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);

void func_001C49E8(TurningCollider* self, PadRecord* pad)
{
    D_00274B5C = (D_00274B5C - 0.25f >? 0.0f);
    if (D_00274B5C < pad->f48) {
        ComputeCameraRelativeStickHeading(g_camera, pad, 0, &self->f630);
    } else {
        self->f630 = self->f638;
    }
    f32 level = pad->f48;
    self->f634 = level;
    D_00274B5C = level;
}

extern f32 g_gameTime[];
extern s32 D_00605548;
f32 WrapModulo(f32 x, f32 y);
s32 RandomIntInRange(s32 a, s32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, u8* a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void PlaySoundWithWanderingPitch();

void PlayPhaseCrossingSound(Player* self, f32* p, f32 f) {
    f32 old = self->f6C4;
    f32 ang;
    self->f6C4 = f;
    if (g_gameTime[0] - self->f6C8 < D_00274B60[0]) return;
    if (WrapModulo(f - p[0], 1.0f) < 0.5f && 0.5f < WrapModulo(old - p[0], 1.0f)) {
        ang = p[2];
    } else if (WrapModulo(self->f6C4 - p[1], 1.0f) < 0.5f && 0.5f < WrapModulo(old - p[1], 1.0f)) {
        ang = p[3];
    } else {
        return;
    }
    s32 idx = RandomIntInRange(0x47, 0x4A);
    if (idx == D_00605548) {
        s32 x = idx - 0x46;
        idx = x % 4 + 0x47;
    }
    D_00605548 = idx;
    StartSoundEffect(idx, 0, 0, (u8*)&self->v140, 0, 0, 1000.0f, 200.0f, ang, 0.0f, 0.0f);
    PlaySoundWithWanderingPitch();
}

INCLUDE_ASM(func_001C4C20);

// A face of a collision mesh as func_001C4D60 reads it: its plane, the normal and the distance.
struct MeshFace {
    Vec02 normal;           // 0x00
    f32 d;                  // 0x10
    u8 pad14[0x20 - 0x14];
};

void ClearRootObjectStateBits(World* a, void* self, s32 n);
void func_001BBEB8(TurningCollider* self, f32 t);

// The point is a Vu0::Vec value: its temporaries are stores in the plane loop when CSE runs,
// so cse_around_loop keeps the loop's own read of the face count, which GCSE and loop.c turn
// into retail's `move a3,v0`. `changed = 0` after the pointers keeps jump.c from hoisting
// `changed = 1` above the test of `other` (docs/TOOLCHAIN.md).
void func_001C4D60(TurningCollider* self, Collider* other, s32 all)
{
    if (other == self->f6DC) {
        return;
    }
    s32 changed;
    if (other == 0) {
        changed = 1;
    } else {
        Vec02* vel = *(Vec02**)self->hook;
        Vec02* out = (Vec02*)self->mesh.verts;
        Vec02* in = (Vec02*)other->mesh.verts;
        changed = 0;
        for (s32 i = 0; i < other->mesh.vertCount; i++) {
            Vu0::Vec p = Vu0::Add(Vu0::Vec::Of(other->pos), Vu0::Rotate(other->rot, Vu0::Vec::Of(in[i])));
            if (all == 0) {
                for (s32 j = 0; j < other->mesh.faceCount; j++) {
                    MeshFace* f = &((MeshFace*)self->mesh.faces)[j];
                    if (Vu0::ToFloat(Vu0::Dot(p, Vu0::Vec::Of(f->normal))) - f->d > 1.0f) {
                        goto next;
                    }
                }
            }
            changed = 1;
            Vu0::Q(out[i]) = p.q;
            vel[i] = D_00248D30;
        next:;
        }
    }
    if (changed) {
        ClearRootObjectStateBits(self->world, self, 7);
        if (self->hook != 0) {
            func_001BBEB8(self, 0.0f);
        }
    }
    self->f6DC = other;
}


void UpdateSwitchedCollider(void* self);
void func_001C4C20(void* self);

void UpdateTurningCollider(TurningCollider* self)
{
    UpdateSwitchedCollider(self);
    func_001C4C20(self);
}

s32 GetTurningColliderContactMode(void) { return 3; }

void ComputeColliderImpulseResponse(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void ComputeTurningColliderImpulseResponse(TurningCollider* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 old = self->mode470;
    self->mode470 = self->desc06()->m55(self);
    ComputeColliderImpulseResponse(self, a1, a2, a3, a4, a5);
    self->mode470 = old;
}

void SetColliderRotation(void* self, void* src);
f32 ArctangentOfRatio(f32 a, f32 b);

void SetTurningColliderRotation(TurningCollider* self, Mat02* rot)
{
    SetColliderRotation(self, rot);
    f32 r = ArctangentOfRatio(rot->r[0].y, rot->r[0].x);
    self->f638 = r;
    self->f630 = r;
    self->desc06()->m54(self);
}

void CopyColliderMeshesInFrame(void* self);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4* out);
void TransformByMatrixWithW(Mat4* m, Vec02* in, void* out, f32 w);

void func_001C4FF8(TurningCollider* self)
{
    Mat4 world;
    Vec02 k;
    s32 lowest = -1;
    s32 i = 0;
    CopyColliderMeshesInFrame(self);
    BuildMatrixFromRotationAndTranslation(&self->v140, &self->m110, &world);
    f32 lowZ = 3.40282347e+38f;
    for (; i < self->mesh.vertCount; i++) {
        Vec02* v = (Vec02*)self->mesh.verts + i;
        if (i == self->mesh.vertCount - 1) {
            Vu0::Vec low = Vu0::Vec::Of(((Vec02*)self->mesh.verts)[lowest]);
            Vu0::Q(k) = Vu0::FromFloat(-self->f6CC);
            Vu0::Q(*v) = Vu0::MulAddX(low, Vu0::Vec::Of(g_unitZVector), Vu0::Vec::Of(k)).q;
            self->f6D0 = i;
            Vec02* dst = (Vec02*)self->meshCopy.verts + i;
            self->f6D4 = (s32)dst;
            TransformByMatrixWithW(&world, v, dst, 1.0f);
        } else if (v->z < lowZ) {
            lowZ = v->z;
            lowest = i;
            self->f6D8 = ((Vec02*)self->meshCopy.verts + i);
        }
    }
}

void StepCollider(void* self);
void ApplyTurningColliderDrive(TurningCollider* self);

void StepTurningCollider(TurningCollider* self)
{
    StepCollider(self);
    ApplyTurningColliderDrive(self);
}

extern f32 g_frameDt;
void TurnColliderTowardRotation(TurningCollider* self, f32 t, Mat02* out, void* data);
void ConstrainColliderVector(void* a, void* b, void* c, void* d, s32 e);
void AddColliderForce(void* target, void* slot);

void func_001C5148(TurningCollider* self)
{
    TurnColliderTowardRotation(self, g_frameDt, &self->m660, &self->f6E0);
    if (self->f6DC == 0) {
        return;
    }
    Vec02* pivot;
    if (self->f690 != 0) {
        pivot = &self->v6A0;
    } else {
        pivot = (Vec02*)self->f6D4;
    }
    Vec02 arm;
    Vec02 v;
    Vec02 w;
    Vu0::Q(arm) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*pivot));
    Vu0::Q(v) = Vu0::Cross(Vu0::Q(self->v180), Vu0::Q(arm));
    ConstrainColliderVector(self, &self->v440, &v, &v, 0);
    AddColliderForce(self, &v);
    Vu0::Q(w) = Vu0::Cross(Vu0::Q(self->v160), Vu0::Q(arm));
    Vu0::Q(v) = Vu0::Cross(Vu0::Q(self->v160), Vu0::Q(w));
    ConstrainColliderVector(self, &self->v440, &v, &v, 0);
    AddColliderForce(self, &v);
}

s32 IsTurningColliderGroundContact(TurningCollider* self, Contact03* a, s32 idx)
{
    if (self->f6DC == 0) {
        return 0;
    }
    if (a->v80.z * D_00274AD0[idx] < 0.7f) {
        return 0;
    }
    s32 kind = a->kind;
    switch (kind) {
    case 1: {
        s32 r = 0;
        if (idx == 0 && a->fA0 == self->f6D4) {
            r = 1;
        }
        return r;
    }
    case 4: {
        s32 r = 0;
        if (idx == 1 && a->fA4 == self->f6D4) {
            r = 1;
        }
        return r;
    }
    case 10: {
        s32 r = 0;
        if (idx == 0) {
            r = a->fA0 == self->f6D4;
        }
        return r;
    }
    }
    return 0;
}

// Slot 86 (func_001C5248: does a contact hold the body up), called with the caller's own
// arguments left in place.
typedef s32 (*ContactTestFn)(void* self);
void ComputeTurningColliderContactValue(TurningCollider* self, Contact03* out)
{
    if (((ContactTestFn*)self->desc)[0x168 / 4](self)) {
        f32 d = D_00274B74;
        out->f98 = 0;
        out->f94 = d;
    } else {
        out->f94 = 0.0f;
        out->f98 = 0;
    }
}

void ClampColliderContactLimit(void);

void ClampTurningColliderContactLimit(void)
{
    ClampColliderContactLimit();
}

void ClampColliderContactLimit(void)
{
}

void BuildAxisAngleMatrix(const Vec02* t, f32 x, void* p);

void BuildTurningColliderHeadingMatrix(TurningCollider* self)
{
    BuildAxisAngleMatrix(&g_unitZVector, self->f638, (u8*)self + 0x660);
}

void ResolveTurningColliderGroundContact(TurningCollider* self, void* b, s32 c);

void ResolveTurningColliderContact(TurningCollider* self, void* b, s32 c)
{
    if (((ContactTestFn*)self->desc)[90](self)) {
        ResolveTurningColliderGroundContact(self, b, c);
    }
}


void RecomputeColliderFrame(TurningCollider* self);
f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);

void RecomputeTurningColliderFrame(TurningCollider* self)
{
    RecomputeColliderFrame(self);
    f32 t = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 ay = __builtin_fabsf(WrapAngle(self->f638 - t));
    ValueRange* lim = &g_unitRange;
    Vec02* p = &self->v6F0;
    f32 v = self->v6F0.x + ay * (p->y + ay * p->z);
    f32 lo = lim->lo;
    f32 hi = lim->hi;
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    self->f63C = v;
}

INCLUDE_ASM(func_001C54D0);

s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);
void FreePooledContactChain(World* w, Contact03* head);

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

void func_001C57C8(TurningCollider* self)
{
    Contact03* freed = 0;
    Contact03* best = 0;
    f32 bestHeight = 3.40282347e+38f;
    self->f690 = 0;
    ContactRow03* row = self->contacts->head;
    for (;;) {
        Contact03* c = row != 0 ? row->head : self->contacts4B4;
        for (; c != 0; c = c->next) {
            s32 j = (self != c->end[0].body);
            if (((s32 (*)(TurningCollider*, Contact03*, s32))self->desc06()->m56)(self, c, j) != 0) {
                Vec02 arm;
                Vu0::Q(arm) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(c->end[1 - j].v10));
                f32 h = Vu0::ToFloat(Vu0::Dot(Vu0::Q(arm), Vu0::Q(self->m110.r[2])));
                if (h < bestHeight) {
                    self->f690 = 1;
                    bestHeight = h;
                    self->f694 = g_gameClock.time;
                    self->v6A0 = c->end[1 - j].v10;
                    Vu0::Q(self->v6B0) = Vu0::MulX(Vu0::Q(c->v80), Vu0::ScalarAt(D_00274AD0[j]));
                    self->f6C0 = c->end[1 - j].part;
                    best = c;
                }
            }
        }
        if (row == 0) {
            break;
        }
        row = row->next;
    }
    if (self->f6DC == 0) {
        return;
    }
    row = self->contacts->head;
    for (;;) {
        Contact03** link = row != 0 ? &row->head : &self->contacts4B4;
        Contact03* c;
        while ((c = *link) != 0) {
            s32 j = (self != c->end[0].body);
            if (c->end[j].part != self) {
                link = &c->next;
                continue;
            }
            s32 kind = c->kind;
            if ((kind == 1 && c->fA0 == (s32)self->f6D8) || (kind == 4 && c->fA4 == (s32)self->f6D8)) {
                if (self->f690 != 0) {
                    goto drop;
                }
            } else {
                if ((kind == 1 && c->fA0 == self->f6D4) || (kind == 4 && c->fA4 == self->f6D4) ||
                    (kind == 10 && c->fA0 == self->f6D4)) {
                    if (c != best) {
                        goto drop;
                    }
                }
                if (kind == 3 || (j == 1 && (kind == 1 || kind == 4 || kind == 5 || kind == 6))) {
                    f32 sign = D_00274AD0[j];
                    if (0.0f < sign * c->v80.z) {
                        Vec02 n;
                        Vec02 d;
                        Vec02 p;
                        Vu0::Vec sv = Vu0::Vec::Scalar(sign);
                        *(Vu0::Vec*)&n = Vu0::MulX(Vu0::Vec::Of(c->v80), sv);
                        n.z = 0.0f;
                        Vu0::Q(n) = NormalizeOrElse(Vu0::Vec::Of(n), Vu0::Vec::Of(g_unitXVector)).q;
                        *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(c->end[j].v10), Vu0::Vec::Of(c->end[1 - j].v10));
                        Vu0::Vec dot = Vu0::Dot(Vu0::Vec::Of(d), Vu0::Vec::Of(n));
                        f32 depth = Vu0::ToFloat(dot);
                        *(Vu0::Vec*)&p = Vu0::MulAddX(Vu0::Vec::Of(c->end[1 - j].v10), Vu0::Vec::Of(n),
                                                 Vu0::Vec::Scalar(depth));
                        CreatePooledContact(depth, self, c->end[1 - j].part, &p, &n, 10, 0, 0, &c->next);
                    }
                }
            }
        
            link = &c->next;
            continue;
        drop:
            *link = c->next;
            c->next = freed;
            freed = c;
        }
        if (row == 0) {
            break;
        }
        *row->link = row->head;
        row = row->next;
    }
    FreePooledContactChain(self->world, freed);
}

void AddTurningColliderProbeContact(void* a, s32 b, s32 c, s32 d);

void CollideTurningColliderWithObject(TurningCollider* a0, s32 a1, s32 unused2, s32 unused3, s32 a4, s32 a5)
{
    AddTurningColliderProbeContact(a0, a1, a4, a5);
}

s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

void AddTurningColliderProbeContact(void* a, s32 b, s32 c, s32 d)
{
    TurningCollider* self = (TurningCollider*)a;
    if (self->f6DC != 0) {
        ColliderSpan span;
        void* obj = (void*)b;
        if (CollectColliderSpansInTree(obj, (void*)c, &self->v140, (void*)self->f6D4, 1, &span) > 0 && span.time[0] > 0.0f) {
            Vec02 diff;
            Vu0::Q(diff) = Vu0::Sub(Vu0::Q(*(Vec02*)self->f6D4), Vu0::Q(span.q[0]));
            switch (span.f48) {
            case 0: {
                f32 d0 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(diff), Vu0::Q(span.q[2])));
                CreatePooledContact(d0, self, obj, (void*)self->f6D4, &span.q[2], 1, self->f6D4, (s32)span.face50, (void*)d);
                break;
            }
            case 1: {
                Vec02 k;
                Vu0::Q(k) = Vu0::FromFloat(-1.0f);
                Vu0::Q(span.q[2]) = Vu0::MulX(Vu0::Q(span.q[2]), Vu0::Q(k));
                f32 d1 = Vu0::ToFloatViaBits(Vu0::Dot(Vu0::Q(diff), Vu0::Q(span.q[2])));
                d1 = -d1;
                CreatePooledContact(d1, obj, self, (void*)self->f6D4, &span.q[2], 4, 0, self->f6D4, (void*)d);
                break;
            }
            }
        }
    }
}

f32 ArctangentOfRatio(f32 a, f32 b);
f32 ApproachAngleWithRamp(void* p, void* out, f32 a, f32 b, f32 c);

void TurnColliderTowardHeading(TurningCollider* self)
{
    Vec02 q = self->v160;
    f32 r = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    ApproachAngleWithRamp((u8*)self + 0x6E0, &q.z, r, self->f638, 0.0f);
    self->desc02()->m21(self, &q);
}

void func_001C5DB8(TurningCollider* self, void* matrix, Vec02* out, f32 limit)
{
    f32 turn;
    f32 r = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 angle = ApproachAngleWithRamp((u8*)self + 0x6E0, &turn, r, self->f638, limit);
    BuildAxisAngleMatrix(&g_unitZVector, angle, matrix);
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloatAt(turn);
    Vu0::Q(*out) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Q(k));
}


void ScaleTurningColliderRamp(TurningCollider* self, f32 s)
{
    *(ThreeWords*)&self->f6E0 = *(ThreeWords*)D_00274B80;
    self->f6E0 *= s;
    self->f6E4 *= s;
    self->f6E8 *= 1.0f / Fpu::Sqrt(s);
}

void SetColliderMass(Collider* self, f32 m);

void func_001C5EA8(TurningCollider* self, f32 s)
{
    f32 n = 0.1f;
    n >?= s;
    SetColliderMass(self, self->mass * self->f700 / n);
    f32 ratio = n / self->f700;
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloat(ratio);
    self->f700 = n;
    Vu0::Q(self->gravity) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Q(k));
}
