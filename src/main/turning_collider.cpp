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
#include "ramp_profile.h"
#include "vu0.h"
struct Mat02;
struct Mat4A;
struct Quad16;
struct Vec02;



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

void InitSwitchedCollider(SwitchedCollider* self);
void ScaleTurningColliderRamp(TurningCollider* self, f32 s);

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

void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void SetTurningColliderLinkFlag(TurningCollider* self, s32 a1);

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
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

void BuildPartProbeTowardLink(void* unused0, PlacedObject* self, void* unused2, PlacedObject* obj, FollowProbe* out, f32 radius)
{
    Vec02 pos;
    Vec02 dir;
    out->f50 = 0;
    Rec2195_224* rec = obj->f224;
    if (rec != 0 && (rec->fB0 & 0x20) != 0) {
        TransformPointBetweenFrames(obj, 0, (Vec02*)((u8*)rec + 0x60), &pos);
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

s32 CollectColliderSpansInTree(Collider* self, void* a1, void* a2, void* a3, s32 a4, ColliderSpan* a5);

void KeepNearestPartSpan(void* unused, void* a1, void* a2, Part07* self)
{
    ColliderSpan ents[2];
    s32 n;
    s32 idx;
    if (self->f50 == 0) return;
    n = CollectColliderSpansInTree((Collider*)a1, a2, &self->v70, &self->v60, 2, ents);
    idx = 0;
    if (n > 0) {
        if (ents[0].time[0] == 0.0f) idx = 1;
    }
    if (!(idx < n)) return;
    if (ents[idx].time[0] < self->span.time[0]) {
        self->span = ents[idx];
    }
}

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);

void PlacePartAtProbeSpan(void* unused0, PlacedObject* other, PlacedObject* self, Part07* rec)
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
            TransformPointBetweenFrames(0, (PlacedObject*)self->parent, &pos, &pos);
            self->desc02()->m1D(self, &pos);
            ComputeObjectMotionInFrame(self, 0, &other->v140, &vel, 0, 0, 0);
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(vel), Vu0::Q(rec->span.q[2])));
            if (d < 0.0f) {
                TransformDirectionBetweenFrames(0, (PlacedObject*)self->parent, (Vec02*)&rec->span.q[2], &dir);
                const Desc02* ds = self->desc02();
                Vu0::Q(vel) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(dir), Vu0::Scalar(-d));
                ds->m20(self, &vel);
            }
        }
    }
}


void DrawCollider(Collider* self, void* a1, void* a2);

void DrawTurningCollider(TurningCollider* self, void* unused1, void* unused2)
{
    DrawCollider(self, unused1, unused2);
}

void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);

void ReadTurningColliderStickHeading(TurningCollider* self, PadRecord* pad)
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
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
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
    StartSoundEffect(idx, 0, 0, (Vec02*)&self->v140, 1000.0f, 200.0f, ang, 0.0f, 0.0f, 0, 0);
    PlaySoundWithWanderingPitch();
}

// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);

// Each vertex's velocity toward the other mesh's vertex in the world: the vertex moved by
// the ramp over this frame, as a speed. The count runs down (`--i >= 0`) and the floats are
// read by index, which loop.c reduces to the walking pointers of retail's inner loop; written
// as pointer copies (`f32* c = (f32*)cur`), CSE after loop makes the copies canonical and the
// increments PRE hoisted read them (docs/TOOLCHAIN.md).
void TrackFollowedMeshVertexVelocities(TurningCollider* self)
{
    Collider* other = (Collider*)self->f6DC;
    if (other != 0) {
        Vec02* src = (Vec02*)other->mesh.verts;
        Vec02* cur = (Vec02*)self->mesh.verts;
        Vec02* dst = *(Vec02**)self->hook;
        for (s32 i = other->mesh.vertCount; --i >= 0; ) {
            Vec02 world;
            Vu0::Q(world) = Vu0::Add(Vu0::Q(other->pos), Vu0::Rotate(other->rot, Vu0::Q(*src)));
            for (s32 k = 0; k < 3; k++) {
                f32 t = ApproachValueWithRamp((&cur->x)[k], (&world.x)[k], g_gameClock.dt, (RampProfile*)D_00274B68, 0);
                (&dst->x)[k] = (t - (&cur->x)[k]) / g_gameClock.dt;
            }
            src++;
            cur++;
            dst++;
        }
    }
}

// A face of a collision mesh as func_001C4D60 reads it: its plane, the normal and the distance.
struct MeshFace {
    Vec02 normal;           // 0x00
    f32 d;                  // 0x10
    u8 pad14[0x20 - 0x14];
};

void ClearRootObjectStateBits(void* a0, Collider* owner, u32 mask);
void AdvanceColliderMeshMotion(Collider* self, f32 dt);

// The point is a Vu0::Vec value: its temporaries are stores in the plane loop when CSE runs,
// so cse_around_loop keeps the loop's own read of the face count, which GCSE and loop.c turn
// into retail's `move a3,v0`. `changed = 0` after the pointers keeps jump.c from hoisting
// `changed = 1` above the test of `other` (docs/TOOLCHAIN.md).
void SetTurningColliderFollowedMesh(TurningCollider* self, Collider* other, s32 all)
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
            AdvanceColliderMeshMotion(self, 0.0f);
        }
    }
    self->f6DC = other;
}


void UpdateSwitchedCollider(SwitchedCollider* self, f32 dt);

void UpdateTurningCollider(TurningCollider* self, f32 dt)
{
    UpdateSwitchedCollider(self, dt);
    TrackFollowedMeshVertexVelocities(self);
}

s32 GetTurningColliderContactMode(void) { return 3; }

struct Contact03;
struct ContactEnd03;
struct ImpulseRow;
void ComputeColliderImpulseResponse(void* self, s32 a1, Contact03* c, s32 idx, ContactEnd03* hit, ImpulseRow* rows);

void ComputeTurningColliderImpulseResponse(TurningCollider* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 old = self->mode470;
    self->mode470 = self->desc06()->m55(self);
    ComputeColliderImpulseResponse(self, a1, (Contact03*)a2, a3, (ContactEnd03*)a4, (ImpulseRow*)a5);
    self->mode470 = old;
}

void SetColliderRotation(Collider* self, Mat02* src);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

void SetTurningColliderRotation(TurningCollider* self, Mat02* rot)
{
    SetColliderRotation(self, rot);
    f32 r = ArctangentOfRatio(rot->r[0].y, rot->r[0].x);
    self->f638 = r;
    self->f630 = r;
    self->desc06()->m54(self);
}

void CopyColliderMeshesInFrame(Collider* self, Collider* other, s32 mode);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
void TransformByMatrixWithW(const Quad16* m, const Vec02* v, f32 w, Vec02* out);

void CopyTurningColliderMeshesInFrame(TurningCollider* self, Collider* other, s32 mode)
{
    Mat4 world;
    Vec02 k;
    s32 lowest = -1;
    s32 i = 0;
    CopyColliderMeshesInFrame(self, other, mode);
    BuildMatrixFromRotationAndTranslation(&self->v140, &self->m110, (Mat4A*)&world);
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
            TransformByMatrixWithW((const Quad16*)&world, v, 1.0f, dst);
        } else if (v->z < lowZ) {
            lowZ = v->z;
            lowest = i;
            self->f6D8 = ((Vec02*)self->meshCopy.verts + i);
        }
    }
}

void StepCollider(Collider* self, f32 t);
void ApplyTurningColliderDrive(TurningCollider* self);

void StepTurningCollider(TurningCollider* self, f32 dt)
{
    StepCollider(self, dt);
    ApplyTurningColliderDrive(self);
}

extern f32 g_frameDt;
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* target, f32* gain);
void ConstrainColliderVector(void* a, void* b, void* c, void* d, s32 e);
void AddColliderForce(void* target, void* slot);

void ApplyTurningColliderDrive(TurningCollider* self)
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

void ClampColliderContactLimit(Collider* self, s32 flags, ContactLimit03* limit);

void ClampTurningColliderContactLimit(TurningCollider* self, s32 flags, ContactLimit03* limit)
{
    ClampColliderContactLimit(self, flags, limit);
}

void ClampColliderContactLimit(Collider* self, s32 flags, ContactLimit03* limit)
{
}

void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);

void BuildTurningColliderHeadingMatrix(TurningCollider* self)
{
    BuildAxisAngleMatrix(&g_unitZVector, (Mat02*)((u8*)self + 0x660), self->f638);
}

void ResolveTurningColliderGroundContact(TurningCollider* self, Contact03* c, s32 e);

void ResolveTurningColliderContact(TurningCollider* self, void* b, s32 c)
{
    if (((ContactTestFn*)self->desc)[90](self)) {
        ResolveTurningColliderGroundContact(self, (Contact03*)b, c);
    }
}


void RecomputeColliderFrame(Collider* self);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
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

// A ramp's three words copied to the stack, read back as floats.
union RampCopy {
    ThreeWords w;
    f32 f[3];
};

f32 ClampToMagnitude(f32 a, f32 b);

// v less its part along the unit vector n.
static inline u128 RemoveAlong(u128 v, u128 n)
{
    return Vu0::Sub(v, Vu0::MulX(n, Vu0::Dot(v, n)));
}

// The ground contact's push along the collider's up axis (m110.r[2]) at end e: none when the
// collider has no ground vertex or no push speed; else the ends' closing speed over the
// contact's weight, raised to the ramp's value toward -f6CC and eased toward the ramp's value
// toward rest. A contact deeper than 2 is first moved out to the ground vertex's height. The
// end's velocity then gains the push and the heading's velocity (m660 times v640) less its part
// along the contact's normal, scaled by f63C.
//
// The frame (208 bytes: the ground push's weight at 32, the tail's weights at 64, out1 and
// out2 at 80 and 84) needs d0 and d1 declared at the top and the ramp copies at function scope
// after the ground push, live through the tail: the zero-push path jumps over them with a
// goto (docs/toolchain/stack-slots.md, "Ramp copies live through a tail: a goto over
// function-scope locals"). The tail is one expression, each weight before its vector, so the
// rotation's loads follow the weights in the insn stream and self dies at its first row
// (docs/toolchain/sched1.md, "Two weights' qmtc2s tied on priority").
void ResolveTurningColliderGroundContact(TurningCollider* self, Contact03* c, s32 e)
{
    Vec02 d0;
    Vec02 d1;
    f32 push;
    f32 w;
    f32 cur;
    if (self->f6DC == 0 || self->f6CC == 0.0f) {
        push = 0.0f;
        goto apply;
    }
    w = Vu0::ToFloat(Vu0::Dot(Vu0::Q(c->v80), Vu0::Q(self->m110.r[2]))) * D_00274AD0[e];
    if (c->f90 < -2.0f) {
        f32 f90 = c->f90;
        u128 v = Vu0::Q(c->end[e].v10);
        f32 t = (f90 + 1.0f) / w;
        f32 ground = ((Vec02*)self->mesh.verts)[self->f6D0].z + 10.0f;
        f32 m = ground >? t;
        Vu0::Q(c->end[e].v10) = Vu0::MulAddX(v, Vu0::Q(self->m110.r[2]), Vu0::Scalar(-m));
        Vu0::Q(d0) = Vu0::Sub(Vu0::Q(c->end[0].v10), Vu0::Q(c->end[1].v10));
        Vu0::StoreX(c->f90, Vu0::Dot(Vu0::Q(d0), Vu0::Q(c->v80)));
    }
    RampCopy A;
    RampCopy B;
    f32 out1;
    f32 out2;
    Vu0::Q(d0) = Vu0::Sub(Vu0::Q(*(Vec02*)self->f6D4), Vu0::Q(c->end[e].v10));
    Vu0::Q(d1) = Vu0::Sub(Vu0::Q(c->end[0].v30), Vu0::Q(c->end[1].v30));
    cur = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d0), Vu0::Q(self->m110.r[2])));
    push = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d1), Vu0::Q(c->v80))) / w;
    A.w = *(ThreeWords*)self->f710;
    B.w = *(ThreeWords*)self->f704;
    A.f[0] = A.f[0] * self->f700;
    B.f[0] = B.f[0] * self->f700;
    ApproachValueWithRamp(cur, 0.0f, g_gameClock.dt, (RampProfile*)&A, &out1);
    ApproachValueWithRamp(cur, -self->f6CC, g_gameClock.dt, (RampProfile*)&B, &out2);
    if (push < out2) {
        push = out2;
    }
    push = push + ClampToMagnitude(out1 - push, g_gameClock.dt * (B.f[0] - B.f[1]) / B.f[2]);
apply:
    ContactEnd03* end = &c->end[e];
    Vu0::Q(end->v30) = Vu0::MulAddX2WeightFirst(Vu0::Vec::Of(end->v30).q, Vu0::Scalar(-push), Vu0::Vec::Of(self->m110.r[2]).q, Vu0::ScalarAt(self->f63C), RemoveAlong(Vu0::RotateMembers(self->m660, Vu0::Vec::Of(self->v640).q), Vu0::Vec::Of(c->v80).q));
}

struct PooledContact;
PooledContact* CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, void* a5, void* a6, void* a7);
void FreePooledContactChain(World* world, Contact03* head);

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

void CollectTurningColliderContacts(TurningCollider* self)
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

void AddTurningColliderProbeContact(TurningCollider* self, Collider* obj, void* filter, void* out);

void CollideTurningColliderWithObject(TurningCollider* self, Collider* obj, void* unused2, void* unused3, void* filter,
                                      void* out)
{
    AddTurningColliderProbeContact(self, obj, filter, out);
}

PooledContact* CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, void* a5, void* a6, void* a7);

void AddTurningColliderProbeContact(TurningCollider* self, Collider* obj, void* filter, void* out)
{
    if (self->f6DC != 0) {
        ColliderSpan span;
        if (CollectColliderSpansInTree(obj, filter, &self->v140, (void*)self->f6D4, 1, &span) > 0 && span.time[0] > 0.0f) {
            Vec02 diff;
            Vu0::Q(diff) = Vu0::Sub(Vu0::Q(*(Vec02*)self->f6D4), Vu0::Q(span.q[0]));
            switch (span.f48) {
            case 0: {
                f32 d0 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(diff), Vu0::Q(span.q[2])));
                CreatePooledContact(d0, self, obj, (void*)self->f6D4, &span.q[2], 1, (void*)self->f6D4, span.face50, out);
                break;
            }
            case 1: {
                Vec02 k;
                Vu0::Q(k) = Vu0::FromFloat(-1.0f);
                Vu0::Q(span.q[2]) = Vu0::MulX(Vu0::Q(span.q[2]), Vu0::Q(k));
                f32 d1 = Vu0::ToFloatViaBits(Vu0::Dot(Vu0::Q(diff), Vu0::Q(span.q[2])));
                d1 = -d1;
                CreatePooledContact(d1, obj, self, (void*)self->f6D4, &span.q[2], 4, 0, (void*)self->f6D4, out);
                break;
            }
            }
        }
    }
}

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
f32 ApproachAngleWithRamp(f32 a, f32 b, f32 c, void* self, f32* out);

void TurnColliderTowardHeading(TurningCollider* self)
{
    Vec02 q = self->v160;
    f32 r = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    ApproachAngleWithRamp(r, self->f638, 0.0f, (u8*)self + 0x6E0, &q.z);
    self->desc02()->m21(self, &q);
}

void GetTurningColliderPose(TurningCollider* self, void* matrix, Vec02* out, f32 limit)
{
    f32 turn;
    f32 r = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 angle = ApproachAngleWithRamp(r, self->f638, limit, (u8*)self + 0x6E0, &turn);
    BuildAxisAngleMatrix(&g_unitZVector, (Mat02*)matrix, angle);
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

void SetTurningColliderGravityScale(TurningCollider* self, f32 s)
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
