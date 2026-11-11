// SPDX-License-Identifier: AGPL-3.0-or-later
// The object cycler (class 0x40), 0x15AAE0 to 0x15C178 (its .rodata from 0x24A190, its .data
// from 0x262180): its set-up, load, copy, start, step, update, draw, events, states and the
// ground and support tests. Its edges are not proved by retail, only by the change of role:
// file_1549C8.cpp's scaling volume (class 0x60) before it and the fonts (font.cpp) after it.
// Its .rodata (four jump tables, a double and FLT_MAX) and .data (its ranges, link tables and
// vectors) sit between theirs in code order, read by its functions only, and fall on the
// alignment its own objects ask for, so the cut before could lie from 0x15AA50 to 0x15AAE0 and
// the one after from 0x15C0A0 to 0x15C178. The name is ours, after its role.
#include "common.h"
#include "effect_spawner.h"
#include "vu0.h"
#include "asm_func.h"
#include "system.h"
#include "effect_owner.h"
#include "effect.h"
#include "shapes.h"
#include "active_set_solver.h"
#include "list_iter.h"
#include "transform_object.h"
#include "object_group.h"
#include "cursor_animator.h"
#include "object_cycler.h"
#include "scaling_volume.h"
#include "world.h"
#include "globals.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "base_object.h"
#include "packet_writer.h"
#include "font.h"
#include "render_frame.h"
#include "text_reader.h"
#include "layout_137228.h"
#include "scope_marker.h"
#include "vu0.h"



void TransformPointBetweenFrames(void* from, void* to, void* point, Vec02* out);



extern f32 g_gameTime;

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32,f32);



void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
f32 RandomFloatInRange(f32 a, f32 b);
f32 RandomFloatInRange(f32 a, f32 b);
extern PackedFloatPair D_00262180;
extern PackedFloatPair D_00262188;
extern PackedFloatPair D_00262190;
extern PackedFloatPair D_00262198;
extern PackedFloatPair D_002621A0;
extern PackedFloatPair D_002621A8;
extern PackedFloatPair D_002621B0;
extern PackedFloatPair D_002621B8;
extern PackedFloatPair D_002621C0;

void InitCollider(Collider* self);
void AppendToList(List01* a, ObjectCycler* b);

// A message held back by SendMessageAfterDelay (a slot of the world's pool at +0x1BD0, in its
// list at +0x1BDC, linked at +0x64): the receiver, the 0x50-byte message, the time it is due.
struct DelayedMessageBody { Quad16 q[5]; };
struct DelayedMessage { void* owner; u8 pad0[0xC]; DelayedMessageBody body; f32 due; };

extern f32 g_gameClock[];
void AppendToList(void* list, void* item);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);
extern s32 g_objectCyclerStartLinks[6];

void ResolveObjectLinks(void* self, s32 n, void* p);
f32 RandomFloatInRange(f32 a, f32 b);
void SetObjectCyclerState(ObjectCycler* self, s32 x);
void StartPlacedObject(void* self);
void AppendToList(void* where, WorldObjectNode* node);



void RemoveFromList(void* where, WorldObjectNode* node);
void BuildPlacedObjectTransform(void* obj, void* c, void* out);

extern f32 g_gameTime;


void AppendToList(void* list, void* item);

struct CyclerEventMessage {
    u8 pad0[0x8];
    f32 f8;
    s32 fC;
    u8 pad1[0x20 - 0x10];
    Quad16 f20;
    Quad16 f30;
};
struct __attribute__((aligned(16))) GroupForwardMessage {
    s32 f0;
    u8 pad0[0x10 - 0x4];
    Quad16 f10;
    Quad16 f20;
    u8 pad1[0x50 - 0x30];
};

void SetObjectCyclerState(void* self, s32 x);
void ApplyColliderImpulseEvent(void* a0, f32 x, void* a1, void* a2);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void CopyCollider();
s32 IsInList(void* sub, ObjectCycler* self);
void RemoveFromList(void* data, ObjectCycler* self);
void StartSoundEffect(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void StopSoundRecord(void* self, s32 n);
void StartSoundEffect(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);
extern f32 g_gameTime;
void RemoveFromList(u8* a, ColorFade* b);

typedef int Quadword128 __attribute__((mode(TI)));

extern f32 g_gameClock[];

void UpdateCollider(ObjectCycler* self);
void SetObjectCyclerState(ObjectCycler* self, s32 mode);
s32 ChooseObjectCyclerNextState(ObjectCycler* self);
s32 FindObjectCyclerGroundPoint(ObjectCycler* self, Quadword128* out);
void SendObjectCyclerMessage(ObjectCycler* self);
s32 IsObjectCyclerUnsupported(ObjectCycler* self);
s32 IsActiveColliderNearObjectCycler(ObjectCycler* self);
f32 RandomFloatInRange(f32 a, f32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

extern f32 g_gameClock[];
void RemoveFromList(List01* list, DelayedMessage* node);
extern s32 g_objectCyclerLoadLinks[6];

void LoadCollider(ObjectCycler* self, void* arg);
void ResolveObjectLinks(ObjectCycler* self, s32 n, void* table);
void FindOrBuildMemberGroup(void** out, ObjectCycler* self);
s32 FindFirstObjectByIdMode1(u8* self, s32 kind, ObjectCycler* arg);
void ResolveAndStartObject(s32 a);
s32 IsInList(List01* sub, ObjectCycler* self);
void RemoveFromList(List01* data, ObjectCycler* self);

struct CyclerDrawParams { u8 pad[0x40]; f32 scale; u8 pad2[0x10 - 4]; };
extern f32 g_gameTime;
extern f32 D_00262230[4];
extern f32 D_00262240[4];
extern f32 g_unitRange[];
void BuildPlacedObjectTransform(ObjectCycler* self, void* c, void* out);

struct GroundProbe {
    Vec02 q;
    s32 a;
    s32 b;
};

extern f32 g_gameClock[];

typedef s32 (*ObjectFilterFn)(void* a, void* b);

s32 IsCyclerGroundCandidate(void* a, void* b);
void PushBackMemoryMark(void* self);
s32 FindNearestSpanObject(s32 zero, void* p, void* q, s32 a, s32 b, s32 c);
void PopBackMemoryMark(void);
void GatherCollidersInSphere(s32 a0, s32 a1, void* a2, ObjectFilterFn a3, void* a4, s32* a5, s32* a6, f32 f12);

struct GroundFilterContext { u8 pad[0x50]; s32 f50; };
struct GroundCandidate { u8 pad0[0x50]; s32 f50; u8 pad1[0x278]; u32 f2CC; u8 pad2[0x268]; u64 f538; };


struct FrameNode {
    u8 pad0[0x14];
    u8* f14;
    u8 pad18[0x1088 - 0x18];
    void* f1088;
};
void RemoveFromList(List01* l, FrameNode* n);
void AppendToList(u8* l, FrameNode* n);
typedef unsigned long u64;
void ComputePolarOffset(Vec02* out, f32 angle, f32 a, f32 b);
void TransformPointBetweenFrames(void* from, s32 to, Vec02* point, Vec02* out);
extern const Vec02 D_00248D30;


void InitObjectCycler(ObjectCycler* self)
{
    InitCollider(self);
    self->state = -1;
    self->p610.pk = D_00262180;
    self->p618.pk = D_00262188;
    self->p620.pk = D_00262190;
    self->p628.pk = D_00262198;
    self->swapKind = -1;
    self->checkDelay.pk = D_002621A0;
    self->p650.pk = D_002621A8;
    self->p658.pk = D_002621B0;
    self->p660.pk = D_002621B8;
    self->p670.pk = D_002621C0;
    self->indexStep = 1;
    self->f690 = -1;
    AppendToList(&self->world->list1C48, self);
}

void LoadObjectCycler(ObjectCycler* self, void* arg)
{
    u32 i;
    LoadCollider(self, arg);
    ResolveObjectLinks(self, 2, g_objectCyclerLoadLinks);
    FindOrBuildMemberGroup((void**)&self->group, self);
    for (i = 0; i < 16; i++) {
        s32 kind = i + 0x23C;
        s32 p = FindFirstObjectByIdMode1((u8*)self->world, kind, self);
        if (!p)
            continue;
        ResolveAndStartObject(p);
        if (self->mode == 1) {
            if (self->swapKind == kind)
                self->swapIndex = self->count;
        }
        self->objs[self->count++] = (PlacedObject*)p;
    }
    if (self->mode == 1) {
        for (i = 0; i < 8; i++) {
            s32 p = FindFirstObjectByIdMode1((u8*)self->world, i + 0x24D, self);
            if (p) {
                ResolveAndStartObject(p);
                self->altObjects[self->altCount++] = (PlacedObject*)p;
            }
        }
    }
    if (self->mode) {
        if (IsInList(&self->world->list1C48, self))
            RemoveFromList(&self->world->list1C48, self);
    }
}

void CopyObjectCycler(ObjectCycler* self)
{
    PackedFloatPair tmp;
    tmp = self->f5DC;
    CopyCollider();
    self->f5DC = tmp;
    if (self->mode == 0) {
        StartSoundEffect(700.0f, 10.0f, 1.0f, 0.0f, 0x41, &self->handle, self, 0, 0.0f, 0, 0);
    } else {
        if (IsInList(&self->world->list1C48, self) != 0) {
            RemoveFromList(&self->world->list1C48, self);
        }
    }
}

void SetObjectCyclerHandle(ObjectCycler* self, s32 flag)
{
    if (self->mode == 0) {
        if (flag != 0) {
            StopSoundRecord(self->handle, 0);
        } else {
            StartSoundEffect(700.0f, 10.0f, 1.0f, 0.0f, 0x41, &self->handle, self, 0, 0.0f, 0, 0);
        }
    }
}

void StartObjectCycler(ObjectCycler* self)
{
    ResolveObjectLinks(self, 2, g_objectCyclerStartLinks);
    if (self->mode == 1) {
        f32 t = RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
        self->nextCheckTime = g_gameClock[1] + t;
        t = RandomFloatInRange(self->p670.a, self->p670.b);
        self->f680 = g_gameClock[1] + t;
    }
    SetObjectCyclerState(self, self->startState);
    StartPlacedObject(self);
    self->f64C = self->radius3CC + self->radius3CC;
}

extern f32 D_002621F8[6];
extern f32 D_00262210[4];
extern f32 D_00262220[4];
void EvaluateHermiteVectorSegment(f32 t, f32 dt, f32 scale, Vec02* p0, Vec02* v0, Vec02* p1, void* v1, Vec02* outPos, Vec02* outVel, s32 zero);
void ClampVectorLength(Vec02* out, Vec02* in, f32 limit);
void AddColliderForce(Collider* self, Vec02* force);
void BuildBasisFromXAndZHint(Vec02* x, Vec02* zHint, Mat02* out);
void ApproachRotationWithRamp(Mat02* current, Mat02* target, const f32* ramp, f32 dt, s32 zero, Vec02* out);
void SteerColliderTowardPosition(Collider* self, void* a, void* b, const Vec02* zero, const f32* ramp, f32 dt);
void SteerColliderTowardRotation(Collider* self, void* a, void* b, const Vec02* zero, const f32* ramp, f32 dt);
void StepCollider(Collider* self, f32 dt);

// k, the ramp's output, is read and written at its own address (*(u128*)&k): through Vu0::Q
// its address stays in a saved register, where retail forms it again for each call.
void StepObjectCycler(ObjectCycler* self, f32 dt)
{
    switch (self->state) {
    case 0:
    case 3:
    case 5: {
        Vec02 pos;
        Vec02 vel;
        Vec02 accel;
        Vec02 k;
        Mat02 basis;
        f32 t = self->stateEnd + dt - g_gameClock[1];
        EvaluateHermiteVectorSegment(t, dt, 1.0f, &self->pos, &self->v150, &self->v5F0, (u8*)self + 0x600, &pos, &vel, 0);
        Vu0::Q(accel) = Vu0::Sub(Vu0::Q(vel), Vu0::Q(self->v150));
        *(u128*)&k = Vu0::FromFloat(1.0f / dt);
        Vu0::Q(accel) = Vu0::MulX(Vu0::Q(accel), *(u128*)&k);
        ClampVectorLength(&accel, &accel, 3000.0f);
        AddColliderForce(self, &accel);
        Vu0::Q(accel) = Vu0::Sub(Vu0::Q(accel), Vu0::Q(self->gravity));
        BuildBasisFromXAndZHint(&vel, &accel, &basis);
        ApproachRotationWithRamp(&self->rot, &basis, D_002621F8, dt, 0, &k);
        self->desc02()->m21(self, &k);
        break;
    }
    case 1:
        AddColliderForce(self, &self->gravity);
        SteerColliderTowardPosition(self, 0, 0, &D_00248D30, D_00262210, dt);
        SteerColliderTowardRotation(self, 0, 0, &D_00248D30, D_00262220, dt);
        break;
    case 6:
        StepCollider(self, dt);
        break;
    }
}

void UpdateObjectCycler(ObjectCycler* self)
{
    UpdateCollider(self);
    if (self->stateEnd <= g_gameClock[1]) {
        s32 a1 = self->state;
        switch (a1) {
        case 0:
        case 3:
            SetObjectCyclerState(self, -1);
            a1 = 0;
            break;
        case 1:
            a1 = 2;
            break;
        case 5:
            a1 = ChooseObjectCyclerNextState(self);
            break;
        case 6:
            a1 = 0;
            break;
        default:
            break;
        }
        SetObjectCyclerState(self, a1);
    }
    s32 st = self->state;
    switch (st) {
    case 0:
    case 3:
    case 5: {
        s32 sub = self->mode;
        switch (sub) {
        case 0:
            if (self->handle == 0) {
                StartSoundEffect(0x41, &self->handle, (s32)self, 0, 700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            self->index = (self->index + 1) % self->count;
            break;
        case 1:
            if (st == 0) {
                if (self->nextCheckTime <= g_gameClock[1]) {
                    Quadword128 tmp;
                    if (FindObjectCyclerGroundPoint(self, &tmp)) {
                        *(Quadword128*)&self->v5F0 = tmp;
                        SetObjectCyclerState(self, 5);
                    } else {
                        self->nextCheckTime = g_gameClock[1] + RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
                    }
                }
            }
            if (self->nextStepTime <= g_gameClock[1]) {
                s32 n = self->count;
                if (n >= 2) {
                    s32 v = self->index + self->indexStep;
                    self->index = v;
                    if (v >= n) {
                        self->index = n - 2;
                        self->indexStep = -1;
                    } else if (v < 0) {
                        self->index = 1;
                        self->indexStep = 1;
                    }
                    self->nextStepTime = g_gameClock[1] + self->stepInterval;
                }
            }
            break;
        }
        if (0.15f < g_gameClock[1] - self->stateStart) {
            ContactRow03* n = self->contacts->head;
            if (n != 0) {
                for (; n != 0; n = n->next) {
                    if (n->head != 0) {
                        self->stateEnd = g_gameClock[1];
                        break;
                    }
                }
            }
        }
        break;
    }
    case 6:
        if (IsObjectCyclerUnsupported(self) || IsActiveColliderNearObjectCycler(self)) {
            SetObjectCyclerState(self, 0);
        } else if (self->nextAdvanceTime <= g_gameClock[1]) {
            s32 idx = (self->index + 1) % self->altCount;
            self->index = idx;
            self->nextAdvanceTime = g_gameClock[1];
            f32 x, y;
            if (idx == 0) {
                x = self->p660.a;
                y = self->p660.b;
            } else {
                x = self->p658.a;
                y = self->p658.b;
            }
            self->nextAdvanceTime += RandomFloatInRange(x, y);
        }
        break;
    }
    if (self->mode == 1) {
        s32 s = self->state;
        if (s == 0 || s == 5) {
            SendObjectCyclerMessage(self);
        }
    }
}

void DrawObjectCycler(ObjectCycler* self, void* a1, void* a2)
{
    CyclerDrawParams out;
    BuildPlacedObjectTransform(self, a2, &out);
    switch (self->state) {
    case 1: {
        f32 base = self->stateStart;
        f32 num = g_gameTime - base;
        f32 den = self->stateEnd - base;
        f32 t = num / den;
        f32 v = D_00262230[0] + t * (D_00262230[1] + t * D_00262230[2]);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        out.scale = out.scale * v;
        self->obj5D0->desc02()->m24(self->obj5D0, a1, &out);
        break;
    }
    case 3: {
        f32 base = self->stateStart;
        f32 num = g_gameTime - base;
        f32 den = self->stateEnd - base;
        f32 t = num / den;
        f32 v = D_00262240[0] + t * (D_00262240[1] + t * D_00262240[2]);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        out.scale = out.scale * v;
        self->objs[self->index]->desc02()->m24(self->objs[self->index], a1, &out);
        break;
    }
    case 6: {
        self->altObjects[self->index]->desc02()->m24(self->altObjects[self->index], a1, &out);
        break;
    }
    default: {
        s32 idx = self->index;
        if (self->mode == 1 && self->swapKind != -1) {
            f32 t = (g_gameTime - self->stateStart) / (self->stateEnd - self->stateStart);
            if (1.0f - self->swapTail < t) idx = self->swapIndex;
        }
        self->objs[idx]->desc02()->m24(self->objs[idx], a1, &out);
        break;
    }
    }
}

s32 HandleObjectCyclerObjectEvent(ObjectCycler* self, CyclerEventMessage* r)
{
    if (self->state != 1) {
        SetObjectCyclerState(self, 1);
        if ((r->fC & 8) != 0) {
            ApplyColliderImpulseEvent(self, r->f8, &r->f20, &r->f30);
        }
        if (self->group != 0) {
            GroupForwardMessage loc;
            loc.f0 = 6;
            loc.f20 = r->f20;
            loc.f10 = r->f30;
            self->group->desc->m1B(self->group, &loc);
        }
    }
    return 1;
}

void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void ComputePolarOffset(Vec02* out, f32 angle, f32 a, f32 b);
void FindEarliestTimeWithinCurveLimits(s32 n, f32* a, double ka, f32* b, double kb, f32* c, double kc, f32* out);
void SetPlacedObjectVelocityFromFloats(PlacedObject* self, f32 x, f32 y, f32 z);
void ScatterObjectsAtPoint(void* scatter, Vec02* at, s32 a, s32 b);
void RotateMatrixUpright(Mat02* m, s32 zero, Mat02* out);
extern u8 g_scatterController[];
void StartSoundEffect(s32 a0, void* a1, void* a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void SetObjectCyclerState(ObjectCycler* self, s32 state)
{
    if (self->state == state) {
        return;
    }
    switch (self->state) {
    case 0:
    case 3:
    case 5:
        self->b2C8 = 0;
        break;
    case 2:
        self->desc->m02(self);
        break;
    case 6:
        SetColliderAnchors(self, 0, 0, 0, 0);
        self->index = 0;
        self->f680 = g_gameClock[1] + RandomFloatInRange(self->p670.a, self->p670.b);
        break;
    }
    (*(PlacedObject**)((u8*)self + 0x5D8))->f88 = 14;
    self->stateEnd = g_gameClock[1];
    switch (state) {
    case 0:
    case 3:
    case 5: {
        self->b2C8 = 11;
        if (state != 5) {
            f32 a = RandomFloatInRange(-3.14159274f, 3.14159274f);
            f32 b = RandomFloatInRange(self->p610.a, self->p610.b);
            ComputePolarOffset(&self->v5F0, a, b, RandomFloatInRange(self->p618.a, self->p618.b));
            Vu0::Q(self->v5F0) = Vu0::Add(Vu0::Q(self->v5F0), Vu0::Q(self->v190));
        }
        if (state == 5) {
            u128 d = Vu0::Sub(Vu0::Q(self->v5F0), Vu0::Q(self->pos));
            Vu0::Q(self->v600) = Vu0::MulX(Vu0::DivX(d, Vu0::Length(d)), Vu0::Scalar(50.0f));
        } else {
            f32 a = RandomFloatInRange(-3.14159274f, 3.14159274f);
            f32 b = RandomFloatInRange(self->p620.a, self->p620.b);
            ComputePolarOffset(&self->v600, a, b, RandomFloatInRange(self->p628.a, self->p628.b));
        }
        f32 m[3][4];
        f32 t;
        f32* p = &self->pos.x;
        f32* q = &self->v150.x;
        f32* r = &self->v5F0.x;
        f32* s = &self->v600.x;
        for (s32 i = 0; i < 3; i++) {
            m[i][0] = p[i];
            m[i][1] = q[i];
            m[i][2] = r[i];
            m[i][3] = s[i];
        }
        FindEarliestTimeWithinCurveLimits(3, m[0], 1500.0, m[1], 1500.0, m[2], 1500.0, &t);
        t = (f32)((s32)(t * 60.0f) + 1) * 0.0166666675f;
        self->stateEnd += t;
        if (self->state == 6 && state == 0) {
            SetPlacedObjectVelocityFromFloats(self, self->v600.x, self->v600.y, 400.0f);
            self->nextCheckTime = g_gameClock[1] + RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
        }
        break;
    }
    case 1:
        StartSoundEffect(0x3A, 0, 0, &self->v140, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        ScatterObjectsAtPoint(g_scatterController, &self->v140, self->f690, *(s32*)((u8*)self + 0x694));
        self->stateEnd += 2.0f;
        break;
    case 2:
        self->desc->m03(self);
        self->state = state;
        self->stateStart = g_gameClock[1];
        return;
    case 6: {
        Mat02 m;
        RotateMatrixUpright(&self->m110, 0, &m);
        self->desc02()->m1E(self, &m);
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
        SetColliderAnchors(self, 3, 0, 3, 0);
        self->index = 0;
        self->nextAdvanceTime = g_gameClock[1] + RandomFloatInRange(self->p658.a, self->p658.b);
        self->f66C = g_gameClock[1];
        self->stateEnd += RandomFloatInRange(self->p650.a, self->p650.b);
        break;
    }
    }
    self->state = state;
    self->stateStart = g_gameClock[1];
}

extern const f32 D_0024A218[2] = {3.4028235e+38f, 0.0f};

void ConvertPositionToWorld(BaseObject* self, Quad16* out);

void SendObjectCyclerMessage(ObjectCycler* self)
{
    GroupForwardMessage loc;
    if (self->receiver678 && self->f680 <= g_gameClock[1]) {
        loc.f0 = 6;
        if (self->source67C)
            ConvertPositionToWorld(self->source67C, &loc.f20);
        else
            loc.f20 = *(Quad16*)&self->v140;
        Vu0::Q(loc.f10) = Vu0::MulX(Vu0::Q(self->v150), Vu0::Scalar(-1.0f));
        ((f32*)&loc.f10)[2] = 0.0f;
        self->receiver678->desc->m1B(self->receiver678, &loc);
        self->f680 = g_gameClock[1] + RandomFloatInRange(self->p670.a, self->p670.b);
    }
}

struct ListedFrameItem {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    BaseObject* item;       // 0x34
    ListedFrameItem* next;  // 0x38
};
typedef void (*ItemPointFn)(BaseObject* self, Vec02* in, s32 a, Vec02* out, s32 b, s32 c, s32 d);

// nearest is read at its own address (*(u128*)&nearest): through Vu0::Q the address stays in
// a pseudo that CSE keeps in a saved register across the walk, where retail forms it again.
s32 FindObjectCyclerGroundPoint(ObjectCycler* self, Quadword128* out)
{
    ListFrame frame;
    Vec02 hit;
    f32 best = D_0024A218[0];
    for (ListedFrameItem* n = (ListedFrameItem*)self->world->list1C9C.head; n != 0; n = n->next) {
        Vec02 from;
        Vec02 nearest;
        TransformPointBetweenFrames(0, n->frame, &self->v140, &from);
        ItemPointFn fn = (ItemPointFn)((void**)n->item->desc)[10];
        if (fn != 0) {
            fn(n->item, &from, 0, &nearest, 0, 0, 0);
        }
        f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(from), *(u128*)&nearest)));
        if (d < best) {
            best = d;
            TransformPointBetweenFrames(n->frame, 0, &nearest, &hit);
        }
    }
    if (best < D_0024A218[0]) {
        ColliderSpan span;
        Vec02 below;
        s32 count;
        s32 list;
        PushBackMemoryMark();
        GatherCollidersInSphere((s32)self->world, (s32)self, &hit, 0, 0, &count, &list, 500.0f);
        below = hit;
        below.z = below.z - 500.0f;
        s32 r = FindNearestSpanObject(0, &hit, &below, count, list, (s32)&span);
        PopBackMemoryMark();
        if (r != 0) {
            *out = *(Quadword128*)&span;
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 ChooseObjectCyclerNextState(ObjectCycler* self)
{
    s32 touching = 0;
    s32 next;
    for (ContactRow03* n = self->contacts->head; n != 0; n = n->next) {
        if (n->head != 0) {
            touching = 1;
            break;
        }
    }
    if (Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(self->v5F0)))) < self->f64C) {
        next = 6;
    } else if (touching) {
        next = 0;
        self->nextCheckTime = g_gameTime + RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
    } else {
        SetObjectCyclerState(self, -1);
        next = 5;
    }
    return next;
}

void* GetActiveSwitchedCollider(void);

// The squared length of d. ToFloatMoved: the qmfc2 is the compiler's and the mtc1 the helper's
// (one cycle each, where the compiler's mtc1 costs two), so in sched2 the difference's load has
// f684's priority, not one more, and f684's load and square come before it, as in retail.
static inline f32 LengthSquared(u128 d)
{
    return Vu0::ToFloatMoved(Vu0::Dot(d, d));
}

// Whether the active collider's point (its position plus half its velocity) is within f684 of
// the cycler. The position is named first: its load is expanded before the weight's slot store
// and passes it in both schedules, while the velocity, read inside the sum after the Scalar,
// waits for the store, as retail's lqc2 order shows.
s32 IsActiveColliderNearObjectCycler(ObjectCycler* self)
{
    Vec02 point;
    PlacedObject* active = (PlacedObject*)GetActiveSwitchedCollider();
    if (active != 0) {
        Vu0::Vec pos = Vu0::Vec::Of(active->v140);
        Vu0::Q(point) = Vu0::MulAddX(pos.q, Vu0::Q(active->v150), Vu0::Scalar(0.5f));
        s32 inside = LengthSquared(Vu0::Sub(Vu0::Q(point), Vu0::Q(self->v140))) < self->f684 * self->f684;
        if (inside) {
            return 1;
        }
    }
    return 0;
}

s32 IsCyclerGroundCandidate(GroundFilterContext* a0, GroundCandidate* a1)
{
    if ((a1->f538 & 0x80000000000ULL) || a1->f50 == a0->f50) return 0;
    u64 v = a1->f2CC;
    return ((s32)v ^ 1) & 1;
}

s32 IsObjectCyclerUnsupported(ObjectCycler* self)
{
    f32* tbl = g_gameClock;
    if (tbl[1] - self->f66C < 0.05f) {
        return 0;
    }
    PushBackMemoryMark(self);
    GroundProbe fr;
    GatherCollidersInSphere((s32)self->world, 0, &self->v140, IsCyclerGroundCandidate, self, &fr.a, &fr.b, self->f64C);
    fr.q = self->v140;
    fr.q.z = fr.q.z - self->f64C;
    s32 r = FindNearestSpanObject(0, &self->v140, &fr.q, fr.a, fr.b, 0);
    PopBackMemoryMark();
    self->f66C = tbl[1];
    return r == 0;
}

// The file's .data, 0x262180 to 0x262250, in retail's order.
PackedFloatPair D_00262180 = { 0x4348000043480000ULL };
PackedFloatPair D_00262188 = { 0x42C8000042C80000ULL };
PackedFloatPair D_00262190 = { 0x4448000043FA0000ULL };
PackedFloatPair D_00262198 = { 0x43960000C3960000ULL };
PackedFloatPair D_002621A0 = { 0x4270000041700000ULL };
PackedFloatPair D_002621A8 = { 0x42F0000041F00000ULL };
PackedFloatPair D_002621B0 = { 0x3E4CCCCD3D4CCCCDULL };
PackedFloatPair D_002621B8 = { 0x3F4CCCCD3DCCCCCDULL };
PackedFloatPair D_002621C0 = { 0x4170000040A00000ULL };
s32 g_objectCyclerLoadLinks[6] = { 0, 0x256, 0x5D0, 2, 0x259, 0x678 };
s32 g_objectCyclerStartLinks[6] = { 4, 0x258, 0x5D8, 2, 0x25A, 0x67C };
f32 D_002621F8[6] = { 7.0f, 1.0f, 0.25f, 0.0f, 0.0f, 0.0f };
f32 D_00262210[4] = { 0.0f, 0.25f, 0.000250000012f, 0.0f };
f32 D_00262220[4] = { 0.0f, 0.25f, 0.0250000004f, 0.0f };
f32 D_00262230[4] = { 1.0f, 1.5f, -2.5f, 0.0f };
f32 D_00262240[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
