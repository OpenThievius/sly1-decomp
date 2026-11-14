// SPDX-License-Identifier: AGPL-3.0-or-later
// The object cycler (class 0x40), 0x15AAE0 to 0x15C178 (its .rodata from 0x24A190, its .data
// from 0x262180): its set-up, load, copy, start, step, update, draw, events, states and the
// ground and support tests. Its edges are not proved by retail, only by the change of role:
// effect_spawner.cpp's scaling volume (class 0x60) before it and the fonts (font.cpp) after it.
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
#include "object_finder.h"
#include "functions/base_object.h"
#include "functions/collider.h"
#include "functions/curve_segment.h"
#include "functions/effect_spawner.h"
#include "functions/heap.h"
#include "functions/matrix.h"
#include "functions/object_cycler.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/sound_system.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
struct Vec02;

struct Mat02;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct ObjectLink;
struct ScaledTransform;






extern f32 g_gameTime;


extern f32 g_gameTime;



extern PackedFloatPair g_cyclerTargetRadiusRange;
extern PackedFloatPair g_cyclerTargetHeightRange;
extern PackedFloatPair g_cyclerTangentRadiusRange;
extern PackedFloatPair g_cyclerTangentHeightRange;
extern PackedFloatPair g_cyclerCheckDelayRange;
extern PackedFloatPair g_cyclerHoldExtraRange;
extern PackedFloatPair g_cyclerAdvanceDelayRange;
extern PackedFloatPair g_cyclerWrapDelayRange;
extern PackedFloatPair g_cyclerMessageIntervalRange;


// A message held back by SendMessageAfterDelay (a slot of the world's pool at +0x1BD0, in its
// list at +0x1BDC, linked at +0x64): the receiver, the 0x50-byte message, the time it is due.
struct DelayedMessageBody { Quad16 q[5]; };
struct DelayedMessage { void* owner; u8 pad0[0xC]; DelayedMessageBody body; f32 due; };

extern f32 g_gameClock[];

extern f32 g_gameTime;

extern f32 g_gameTime;
extern s32 g_objectCyclerStartLinks[6];



extern f32 g_gameTime;



struct CyclerEventMessage {
    u8 pad0[0x8];
    f32 impulse;
    s32 flags;
    u8 pad1[0x20 - 0x10];
    Quad16 origin;
    Quad16 target;
};
struct __attribute__((aligned(16))) GroupForwardMessage {
    s32 f0;
    u8 pad0[0x10 - 0x4];
    Quad16 f10;
    Quad16 f20;
    u8 pad1[0x50 - 0x30];
};


// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
extern f32 g_gameTime;

typedef int Quadword128 __attribute__((mode(TI)));

extern f32 g_gameClock[];

s32 FindObjectCyclerGroundPoint(ObjectCycler* self, Quadword128* out);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

extern f32 g_gameClock[];
extern s32 g_objectCyclerLoadLinks[6];

struct BufferedStream;

struct CyclerDrawParams { u8 pad[0x40]; f32 scale; u8 pad2[0x10 - 4]; };
extern f32 g_gameTime;
extern f32 g_cyclerShrinkCurve[4];
extern f32 g_cyclerGrowCurve[4];
extern f32 g_unitRange[];

struct GroundProbe {
    Vec02 q;
    s32 a;
    Collider** b;
};

extern f32 g_gameClock[];

typedef s32 (*ObjectFilterFn)(void* a, void* b);

struct GroundCandidate;
struct GroundFilterContext;
s32 FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);

struct GroundFilterContext { u8 pad[0x50]; s32 root; };
struct GroundCandidate { u8 pad0[0x50]; s32 root; u8 pad1[0x278]; u32 flagsHigh; u8 pad2[0x268]; u64 flags; };


struct FrameNode {
    u8 pad0[0x14];
    u8* f14;
    u8 pad18[0x1088 - 0x18];
    void* f1088;
};
typedef unsigned long u64;
extern const Vec02 D_00248D30;


void InitObjectCycler(ObjectCycler* self)
{
    InitCollider(self);
    self->state = -1;
    self->p610.pk = g_cyclerTargetRadiusRange;
    self->p618.pk = g_cyclerTargetHeightRange;
    self->p620.pk = g_cyclerTangentRadiusRange;
    self->p628.pk = g_cyclerTangentHeightRange;
    self->swapKind = -1;
    self->checkDelay.pk = g_cyclerCheckDelayRange;
    self->p650.pk = g_cyclerHoldExtraRange;
    self->p658.pk = g_cyclerAdvanceDelayRange;
    self->p660.pk = g_cyclerWrapDelayRange;
    self->p670.pk = g_cyclerMessageIntervalRange;
    self->indexStep = 1;
    self->f690 = -1;
    AppendToList(&self->world->list1C48, self);
}

void LoadObjectCycler(ObjectCycler* self, void* arg)
{
    u32 i;
    LoadCollider(self, (BufferedStream*)arg);
    ResolveObjectLinks(self, 2, (ObjectLink*)g_objectCyclerLoadLinks);
    FindOrBuildMemberGroup((void**)&self->group, self);
    for (i = 0; i < 16; i++) {
        s32 kind = i + 0x23C;
        BaseObject* p = FindFirstObjectByIdMode1(self->world, kind, self);
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
            BaseObject* p = FindFirstObjectByIdMode1(self->world, i + 0x24D, self);
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

void CopyObjectCycler(ObjectCycler* self, ObjectCycler* src)
{
    PackedFloatPair tmp;
    tmp = self->f5DC;
    CopyCollider(self, src);
    self->f5DC = tmp;
    if (self->mode == 0) {
        StartSoundEffect(0x41, (PlayingSound**)&self->handle, self, 0, 700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
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
            StopSoundRecord((PlayingSound*)self->handle, 0);
        } else {
            StartSoundEffect(0x41, (PlayingSound**)&self->handle, self, 0, 700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
}

void StartObjectCycler(ObjectCycler* self)
{
    ResolveObjectLinks(self, 2, (ObjectLink*)g_objectCyclerStartLinks);
    if (self->mode == 1) {
        f32 t = RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
        self->nextCheckTime = g_gameClock[1] + t;
        t = RandomFloatInRange(self->p670.a, self->p670.b);
        self->nextMessageTime = g_gameClock[1] + t;
    }
    SetObjectCyclerState(self, self->startState);
    StartPlacedObject(self);
    self->searchRadius = self->radius3CC + self->radius3CC;
}

extern f32 g_cyclerRotationRamp[6];
extern f32 g_cyclerFallPositionSteer[4];
extern f32 g_cyclerFallRotationSteer[4];
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void EvaluateHermiteVectorSegment(f32 dur, f32 t, f32 k, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, Vec02* pos, Vec02* vel, Vec02* acc);
void AddColliderForce(Collider* self, Vec02* force);
struct RampProfile;
struct Mat02;

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
        EvaluateHermiteVectorSegment(t, dt, 1.0f, &self->pos, &self->v150, &self->v5F0, &self->v600, &pos, &vel, 0);
        Vu0::Q(accel) = Vu0::Sub(Vu0::Q(vel), Vu0::Q(self->v150));
        *(u128*)&k = Vu0::FromFloat(1.0f / dt);
        Vu0::Q(accel) = Vu0::MulX(Vu0::Q(accel), *(u128*)&k);
        ClampVectorLength(&accel, &accel, 3000.0f);
        AddColliderForce(self, &accel);
        Vu0::Q(accel) = Vu0::Sub(Vu0::Q(accel), Vu0::Q(self->gravity));
        BuildBasisFromXAndZHint(&vel, &accel, &basis);
        ApproachRotationWithRamp(&self->rot, &basis, (RampProfile*)g_cyclerRotationRamp, 0, &k, dt);
        self->desc02()->m21(self, &k);
        break;
    }
    case 1:
        AddColliderForce(self, &self->gravity);
        SteerColliderTowardPosition(self, 0, 0, (Vec02*)&D_00248D30, g_cyclerFallPositionSteer, dt);
        SteerColliderTowardRotation(self, 0, 0, (Vec02*)&D_00248D30, g_cyclerFallRotationSteer, dt);
        break;
    case 6:
        StepCollider(self, dt);
        break;
    }
}

void UpdateObjectCycler(ObjectCycler* self, f32 dt)
{
    UpdateCollider(self, dt);
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
                StartSoundEffect(0x41, (PlayingSound**)&self->handle, self, 0, 700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
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
    BuildPlacedObjectTransform(self, (Quad16*)a2, (ScaledTransform*)&out);
    switch (self->state) {
    case 1: {
        f32 base = self->stateStart;
        f32 num = g_gameTime - base;
        f32 den = self->stateEnd - base;
        f32 t = num / den;
        f32 v = g_cyclerShrinkCurve[0] + t * (g_cyclerShrinkCurve[1] + t * g_cyclerShrinkCurve[2]);
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
        f32 v = g_cyclerGrowCurve[0] + t * (g_cyclerGrowCurve[1] + t * g_cyclerGrowCurve[2]);
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
        if ((r->flags & 8) != 0) {
            ApplyColliderImpulseEvent(self, r->impulse, &r->origin, &r->target);
        }
        if (self->group != 0) {
            GroupForwardMessage loc;
            loc.f0 = 6;
            loc.f20 = r->origin;
            loc.f10 = r->target;
            self->group->desc->m1B(self->group, &loc);
        }
    }
    return 1;
}

struct ScatterController;
extern u8 g_scatterController[];
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

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
        self->nextMessageTime = g_gameClock[1] + RandomFloatInRange(self->p670.a, self->p670.b);
        break;
    }
    self->obj5D8->visibilityMask = 14;
    self->stateEnd = g_gameClock[1];
    switch (state) {
    case 0:
    case 3:
    case 5: {
        self->b2C8 = 11;
        if (state != 5) {
            f32 a = RandomFloatInRange(-3.14159274f, 3.14159274f);
            f32 b = RandomFloatInRange(self->p610.a, self->p610.b);
            ComputePolarOffset((Vec3*)&self->v5F0, a, b, RandomFloatInRange(self->p618.a, self->p618.b));
            Vu0::Q(self->v5F0) = Vu0::Add(Vu0::Q(self->v5F0), Vu0::Q(self->v190));
        }
        if (state == 5) {
            u128 d = Vu0::Sub(Vu0::Q(self->v5F0), Vu0::Q(self->pos));
            Vu0::Q(self->v600) = Vu0::MulX(Vu0::DivX(d, Vu0::Length(d)), Vu0::Scalar(50.0f));
        } else {
            f32 a = RandomFloatInRange(-3.14159274f, 3.14159274f);
            f32 b = RandomFloatInRange(self->p620.a, self->p620.b);
            ComputePolarOffset((Vec3*)&self->v600, a, b, RandomFloatInRange(self->p628.a, self->p628.b));
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
        ScatterObjectsAtPoint((ScatterController*)g_scatterController, &self->v140, self->f690, self->f694);
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
        self->lastLookTime = g_gameClock[1];
        self->stateEnd += RandomFloatInRange(self->p650.a, self->p650.b);
        break;
    }
    }
    self->state = state;
    self->stateStart = g_gameClock[1];
}

extern const f32 D_0024A218[2] = {3.4028235e+38f, 0.0f};


void SendObjectCyclerMessage(ObjectCycler* self)
{
    GroupForwardMessage loc;
    if (self->receiver678 && self->nextMessageTime <= g_gameClock[1]) {
        loc.f0 = 6;
        if (self->source67C)
            ConvertPositionToWorld(self->source67C, (Vec02*)&loc.f20);
        else
            loc.f20 = *(Quad16*)&self->v140;
        Vu0::Q(loc.f10) = Vu0::MulX(Vu0::Q(self->v150), Vu0::Scalar(-1.0f));
        ((f32*)&loc.f10)[2] = 0.0f;
        self->receiver678->desc->m1B(self->receiver678, &loc);
        self->nextMessageTime = g_gameClock[1] + RandomFloatInRange(self->p670.a, self->p670.b);
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
// Left with an integer: the collider list is an s32 that GatherCollidersInSphere fills.

s32 FindObjectCyclerGroundPoint(ObjectCycler* self, Quadword128* out)
{
    ListFrame frame;
    Vec02 hit;
    f32 best = D_0024A218[0];
    for (ListedFrameItem* n = (ListedFrameItem*)self->world->list1C9C.head; n != 0; n = n->next) {
        Vec02 from;
        Vec02 nearest;
        TransformPointBetweenFrames(0, (PlacedObject*)n->frame, &self->v140, &from);
        ItemPointFn fn = (ItemPointFn)((void**)n->item->desc)[10];
        if (fn != 0) {
            fn(n->item, &from, 0, &nearest, 0, 0, 0);
        }
        f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(from), *(u128*)&nearest)));
        if (d < best) {
            best = d;
            TransformPointBetweenFrames((PlacedObject*)n->frame, 0, &nearest, &hit);
        }
    }
    if (best < D_0024A218[0]) {
        ColliderSpan span;
        Vec02 below;
        s32 count;
        Collider** list;
        PushBackMemoryMark();
        GatherCollidersInSphere(self->world, self, 500.0f, &hit, 0, 0, &count, &list);
        below = hit;
        below.z = below.z - 500.0f;
        s32 r = FindNearestSpanObject(0, &hit, &below, count, list, &span);
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
    if (Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(self->v5F0)))) < self->searchRadius) {
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
        s32 inside = LengthSquared(Vu0::Sub(Vu0::Q(point), Vu0::Q(self->v140))) < self->triggerDistance * self->triggerDistance;
        if (inside) {
            return 1;
        }
    }
    return 0;
}

s32 IsCyclerGroundCandidate(GroundFilterContext* a0, GroundCandidate* a1)
{
    if ((a1->flags & 0x80000000000ULL) || a1->root == a0->root) return 0;
    u64 v = a1->flagsHigh;
    return ((s32)v ^ 1) & 1;
}

s32 IsObjectCyclerUnsupported(ObjectCycler* self)
{
    f32* tbl = g_gameClock;
    if (tbl[1] - self->lastLookTime < 0.05f) {
        return 0;
    }
    PushBackMemoryMark();
    GroundProbe fr;
    GatherCollidersInSphere(self->world, 0, self->searchRadius, &self->v140, (s32 (*)(void*, Collider*))(s32 (*)(GroundFilterContext*, GroundCandidate*))IsCyclerGroundCandidate, self, &fr.a, &fr.b);
    fr.q = self->v140;
    fr.q.z = fr.q.z - self->searchRadius;
    s32 r = FindNearestSpanObject(0, &self->v140, &fr.q, fr.a, fr.b, 0);
    PopBackMemoryMark();
    self->lastLookTime = tbl[1];
    return r == 0;
}

// The file's .data, 0x262180 to 0x262250, in retail's order.
PackedFloatPair g_cyclerTargetRadiusRange = { 0x4348000043480000ULL };
PackedFloatPair g_cyclerTargetHeightRange = { 0x42C8000042C80000ULL };
PackedFloatPair g_cyclerTangentRadiusRange = { 0x4448000043FA0000ULL };
PackedFloatPair g_cyclerTangentHeightRange = { 0x43960000C3960000ULL };
PackedFloatPair g_cyclerCheckDelayRange = { 0x4270000041700000ULL };
PackedFloatPair g_cyclerHoldExtraRange = { 0x42F0000041F00000ULL };
PackedFloatPair g_cyclerAdvanceDelayRange = { 0x3E4CCCCD3D4CCCCDULL };
PackedFloatPair g_cyclerWrapDelayRange = { 0x3F4CCCCD3DCCCCCDULL };
PackedFloatPair g_cyclerMessageIntervalRange = { 0x4170000040A00000ULL };
s32 g_objectCyclerLoadLinks[6] = { 0, 0x256, 0x5D0, 2, 0x259, 0x678 };
s32 g_objectCyclerStartLinks[6] = { 4, 0x258, 0x5D8, 2, 0x25A, 0x67C };
f32 g_cyclerRotationRamp[6] = { 7.0f, 1.0f, 0.25f, 0.0f, 0.0f, 0.0f };
f32 g_cyclerFallPositionSteer[4] = { 0.0f, 0.25f, 0.000250000012f, 0.0f };
f32 g_cyclerFallRotationSteer[4] = { 0.0f, 0.25f, 0.0250000004f, 0.0f };
f32 g_cyclerShrinkCurve[4] = { 1.0f, 1.5f, -2.5f, 0.0f };
f32 g_cyclerGrowCurve[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
