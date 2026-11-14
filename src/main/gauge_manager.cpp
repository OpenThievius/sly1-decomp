// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x14B6A8 to 0x14D0A8 (its .rodata from 0x249EF0, its .data from 0x261C90, its
// .bss from 0x27C00C): the rest of class 0x11 (from func_0014B6A8), class 0x12, class 0x68 and
// the gauge manager. Its .rodata provably starts here: func_0014B6A8's FLT_MAX lies on 16 at
// 0x249EF0, after 12 bytes of zeros that follow func_00149760's last jump table, the linker's
// padding before a new file's .rodata. Its start in the code is a choice: any function start
// from 0x14A7B8 to 0x14B6A8 links to the same bytes, and the functions between them could belong
// to camera_controller.cpp, to this file or to a third (camera_controller.cpp says why; they
// are now item_column.cpp, symmetric_solve.cpp and agent_registration.cpp, cut by role only). Classes 0x11, 0x12
// and 0x68 share it, since all three read the static D_0027C00C. Its name is ours, after its
// largest family, the gauge manager (class 0x68), which holds most of its code.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_notifier.h"
#include "world.h"
#include "camera.h"
#include "game_progress.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "object_pool.h"
#include "owner_message.h"
#include "vu0.h"
#include "scope_marker.h"
#include "mul_rotation.h"
#include "pad_record.h"
#include "ramp_profile.h"
#include "object_finder.h"
struct ColliderSpan;
struct PlaneNode;
struct Vec02;

struct PlacedObject;

struct BaseObject;
struct Mat02;
struct Vec02;


s32 IsObjectOfKind(BaseObject* list, s32 key);

void EnterAgentState(Agent* self, s32 evt, Animation* arg);

void SetAnimationPlayerSpeed(AnimationPlayer* self, f32 x);
// An agent of the world's list at +0x1CCC (linked at +0xC10), seen as its table of slots:
// slot 0x50 takes an owner message (func_0014BDC8, func_0014BEF8).
typedef void (*AgentMessageFn)(void* self, void* arg);

struct ListedAgentView {
    AgentMessageFn* vtbl;
    u8 pad0[0xC10 - 4];
    ListedAgentView* next;
};

// The 32-byte block func_0014BDC8 builds its owner message in (InitOwnerMessage fills the
// first 16 bytes; the frame has room for 32).
struct Scratch_0014BDC8 {
    s32 words[8];
};

s32 ChooseAgentState(Agent* self);

s32 IsContactBetweenParts(Collider* self, void* other);
void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner);
void ChangeAgentState(Agent* self, s32 state, void* context);
s32 IsPadSelectFlagHeld(World* self);

struct AgentHit;
struct Agent;
s32 HandleAgentObjectEvent(Agent* self, AgentHit* ev);
void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner);

void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);

// What SetSinCosPair fills: the two results of ComputeSinCos and a word it clears.
struct SinCosPair { f32 a; f32 b; s32 value; };

void ComputeSinCos(f32* sinOut, f32* cosOut, f32 angle);
void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);

void EnterAgentState(Agent* self, s32 evt, Animation* arg);
void CountDownGaugeContacts(GaugeManager* self, ContactAgent* agent);
void SetAnimationPlayerSpeed(AnimationPlayer* self, f32 x);
f32 RandomFloatInRange(f32 a, f32 b);

s32 HandleAgentObjectEvent(NumberedAgent* self, void* event);
extern u8 g_camera[];
extern u8 D_00248D30[];
f32 RandomFloatInRange(f32 a, f32 b);
extern u8 D_00248D30[];
f32 RandomFloatInRange(f32 a, f32 b);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);

void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void ApplyGaugeRatioToEffect(GaugeManager* self);
extern f32 g_gameClock[];
void UpdatePlacedObject(PlacedObject* self, f32 f);
void RunGaugeTimedEvent(GaugeManager* self);
void ActivateRandomGaugeSlot(GaugeManager* self);
void* GetActiveSwitchedCollider(void);
// The active collider seen as its table of slots: slot 81 (func_0014C6E0, func_0014CDC8).
typedef void (*ColliderSlotFn)(void* self);

struct ColliderSlots { ColliderSlotFn* vtbl; };

s32 AreMenusAndFadeClear(void);
extern f32 g_gameTime[];
f32 RandomFloatInRange(f32 a, f32 b);

s32 IsObjectOfKind(BaseObject* list, s32 key);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);

struct StateGraph;
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);

void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void AddStateWalkerListener(StateWalker* self, PlacedObject** p);
void ComputeGaugeOutputs(GaugeManager* self);
extern f32 g_gameTime[];

void AddToGaugeAmount(GaugeManager* self, NumberedAgent* arg);
typedef s32 (*ColliderQueryFn)(void* self);

struct ColliderQuerySlots { ColliderQueryFn* vtbl; };

f32 RandomFloatInRange(f32 a, f32 b);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void* GetActiveSwitchedCollider(void);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void ChangeAgentState(Agent* self, s32 state, void* context);
void StopTimer(T217D_510* self);
void ComputeGaugeOutputs(GaugeManager* self);
extern f32 g_gameTime[];
void RaiseScatterLevels(ScatterController* self, f32 amount);
extern u8 D_00248D30[];
extern u8 D_00248D30[];
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);

extern u8 D_00248D30[];
void ChooseObjectPoolItem(ObjectPool* p);
s32 RandomIntInRange(s32 a, s32 b);
s32 LaunchChosenPoolObject(ObjectPool* h, s32 v);
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
void GetObjectWorldRotation(BaseObject* self, Mat02* out);
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void AddAnimationPlayerRecordCallback(AnimationPlayer* a0, PlacedObject** a1);
f32 RandomFloatInRange(f32 a, f32 b);

void InitPlacedObject(PlacedObject* self);
typedef void (*TimerDoneFn)(void* self);
void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void SetWorldActiveFollower(World* self, void* v);
void StartTimer(T217D_510* self, f32 v);
void SetTimerLimit(T217D_510* self, f32 limit, T217D_510_Fn onEnd);
void StartTimerCounting(T217D_510* self);
void FinishGaugeOnTimeout(T217D_510* timer, s32 mode);

// The coefficients of a quadratic in the gauge fraction (GaugeCurve::Eval).
struct Quadratic {
    f32 a;
    f32 b;
    f32 c;
};

// The helpers func_0014C2F0 maps the gauge fraction with: a quadratic, a clamp, a blend.
struct GaugeCurve {
    static f32 Eval(Quadratic* q, f32 t) { return q->a + t * (q->b + t * q->c); }
    static f32 Limit(f32 g, f32 lo, f32 hi)
    {
        if (g < lo) return lo;
        if (hi < g) return hi;
        return g;
    }
    static f32 Lerp(f32 s, f32 a, f32 b) { return (1.0f - s) * a + s * b; }
};

// GaugeManager::blend, the blend of the two parameter sets, as func_0014C2F0 reads it: pairs of
// limits and the quadratics that pick between them.
struct BlendedGaugeParams {
    f32 agentCountFrom;
    f32 agentCountTo;
    u8 pad08[8];
    Quadratic q10;
    u8 pad1C[4];
    f32 delayMinFrom;
    f32 delayMaxFrom;
    f32 delayMinTo;
    f32 delayMaxTo;
    Quadratic q30;
    u8 pad3C[4];
    f32 triggerFraction;
    f32 waitMinFrom;
    f32 waitMaxFrom;
    f32 waitMinTo;
    f32 waitMaxTo;
    u8 pad54[0xC];
    Quadratic q60;
    u8 pad6C[4];
    f32 f70;
    f32 f74;
    u8 pad78[8];
    Quadratic q80;
    u8 pad8C[4];
    f32 f90;
    f32 f94;
    u8 pad98[8];
    Quadratic qA0;
};

extern f32 g_gameClock[];

// The file's statics (.bss from 0x27C00C).
static GaugeManager* g_gaugeManager;  // the gauge manager, set by its set-up (func_0014C018)

s32 g_agentGoalPeriod = 4;
f32 g_agentNearRadius = 900.0f;
f32 g_agentFarRadius = 1200.0f;
ObjectLink g_gaugeManagerLinks[3] = { { 5, 0x3F8, 0x420 }, { 5, 0x3F9, 0x424 }, { 1, 0x3FA, 0x428 } };

void SetSinCosPair(f32 value, SinCosPair* self);
extern s32 g_frameCount;
s32 CollectSegmentSpansInPlaneTree(PlaneNode* root, Vec02* a, Vec02* b, s32 max, ColliderSpan* spans);
void FindClosestPointsOnSegments(const Vec02* p0, const Vec02* p1, const Vec02* q0, const Vec02* q1, f32* st, f32* dist, Vec02* dir);
void SetAgentGoalPoint(Agent* self, Vec02* goal);
void UpdateAgentGoal(Agent* self, s32 flag);
f32 WrapAngle(f32 a);
typedef NumberedAgent* (*TargetOfFn)(NumberedAgent* self);

void UpdateNumberedAgentGoal(NumberedAgent* self, s32 flag)
{
    typedef Vu0::Vec Vec;
    switch (self->state) {
    case 12:
    case 13:
        if (g_frameCount % g_agentGoalPeriod == self->number % g_agentGoalPeriod) {
            f32 step = 0.3926991f;
            f32 best = 3.40282347e+38f;
            f32 angle = self->heading;
            f32 frac;
            Vec02 bestPos;
            Vec02 probe;
            SinCosPair dir;
            for (s32 i = 0; i < 16; i++) {
                SetSinCosPair(angle, &dir);
                f32 score = 0.0f;
                Vu0::Set(probe, Vu0::MulAddX(Vec::Of(self->v140), Vec::Of(*(Vec02*)&dir), Vec::Scalar(3000.0f)).q);
                if (self->pathGraph != 0) {
                    ColliderSpan hits[8];
                    ScopeMarker scope;
                    s32 r = CollectSegmentSpansInPlaneTree((PlaneNode*)(*(void**)((u8*)self->pathGraph + 0x54)), &self->v140, &probe, 8, hits);
                    switch (r) {
                    case 0:
                        frac = 1.0f;
                        break;
                    case 1:
                        if (hits[0].time[0] == 0.0f && hits[0].time[1] == 1.0f) {
                            break;
                        }
                        if (hits[0].time[0] != 0.0f) {
                            frac = hits[0].time[0];
                            break;
                        }
                    default:
                        frac = hits[0].time[1];
                        break;
                    }
                    f32 v = (0.75f - frac) * 1.3333334f;
                    f32 lo = 0.0f;
                    f32 hi = 1.0f;
                    f32 c;
                    if (v < lo) {
                        c = 0.0f;
                    } else if (hi < v) {
                        c = hi;
                    } else {
                        c = v;
                    }
                    score = score + c * 4.0f;
                }
                NumberedAgent* tgt = ((TargetOfFn)((void**)self->desc)[0x198 / 4])(self);
                if (tgt != 0) {
                    Vec02 other;
                    Vec from = Vec::Of(tgt->v140);
                    Vec weight = Vec::Scalar(3.0f);
                    Vec vel = Vec::Of(tgt->v150);
                    Vu0::Q(other) = Vu0::MulAddX(from, vel, weight).q;
                    Vec02 onA;
                    Vec02 onB;
                    f32 d;
                    FindClosestPointsOnSegments(&self->v140, &probe, &tgt->v140, &other, (f32*)&onA, &d, &onB);
                    f32 q = d / ((tgt->radius3D0 + self->radius3D0) * 5.0f);
                    f32 hi = 1.0f;
                    if (q < 0.0f) {
                        q = 0.0f;
                    } else if (hi < q) {
                        q = hi;
                    }
                    score = score + (1.0f - q) * 3.0f;
                }
                f32 next = angle + step;
                for (NumberedAgent* o = (NumberedAgent*)self->world->list1CCC.head; o != 0;
                     o = *(NumberedAgent**)&o->listLink) {
                    if (o == self) {
                        continue;
                    }
                    Vec02 other;
                    Vec from = Vec::Of(o->v140);
                    Vec weight = Vec::Scalar(3.0f);
                    Vec vel = Vec::Of(o->v150);
                    Vu0::Q(other) = Vu0::MulAddX(from, vel, weight).q;
                    Vec02 onA;
                    Vec02 onB;
                    f32 d;
                    FindClosestPointsOnSegments(&self->v140, &probe, &o->v140, &other, (f32*)&onA, &d, &onB);
                    f32 q = d / ((o->radius3D0 + self->radius3D0) + (o->radius3D0 + self->radius3D0));
                    f32 hi = 1.0f;
                    if (q < 0.0f) {
                        q = 0.0f;
                    } else if (hi < q) {
                        q = hi;
                    }
                    score = score + (1.0f - q) * 0.5f;
                }
                f32 turn = WrapAngle(angle - self->heading) * 0.31830987f;
                score = score + (__builtin_fabsf(turn) + __builtin_fabsf(turn));
                if (score < best) {
                    best = score;
                    bestPos = probe;
                }
                angle = WrapAngle(next);
            }
            SetAgentGoalPoint(self, &bestPos);
        }
        break;
    case 4:
        if (flag != 0) {
            SetAgentGoalPoint(self, &self->v140);
        }
        break;
    default:
        UpdateAgentGoal(self, flag);
        break;
    }
}

extern const Vec02 g_unitXVector;

s32 IsNumberedAgentFree(NumberedAgent* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0) {
        return 0;
    }
    switch (self->state) {
    case 4:
    case 0xB:
    case 0x10:
        return 0;
    }
    PlacedObject* target = (PlacedObject*)self->desc08()->m62(self);
    if (target == 0) {
        return 0;
    }
    u128 gap = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(target->v140));
    u128 gap2 = gap;
    f32 dist = Vu0::ToFloat(Vu0::Length(gap));
    if (self->targetNear != 0) {
        if (g_agentFarRadius < dist) {
            self->targetNear = 0;
        }
        return self->targetNear;
    }
    if (dist < g_agentNearRadius) {
        u128 facing = Vu0::NormalizeOr(Vu0::Q(target->v150), Vu0::Q(g_unitXVector));
        u128 facing2 = facing;
        u128 toward = Vu0::NormalizeOr(gap2, Vu0::Q(g_unitXVector));
        if (0.3f < Vu0::ToFloat(Vu0::Dot(facing2, toward))) {
            self->targetNear = 1;
        }
    }
    return self->targetNear;
}

s32 HandleNumberedAgentObjectEvent(NumberedAgent* self, void* event)
{
    if (self->state == 0x10) {
        return 1;
    }
    if (self->state == 0xB) {
        return 1;
    }
    if (HandleAgentObjectEvent(self, event) == 0) {
        return 0;
    }
    self->targetNear = 0;
    return 1;
}

void EnterNumberedAgentState(NumberedAgent* self, s32 evt, Animation* arg)
{
    EnterAgentState(self, evt, arg);
    switch (self->state) {
    case 0xB:
        AddToGaugeAmount(g_gaugeManager, self);
        if (((GaugeSlot*)self->slot) != 0) { ((GaugeSlot*)self->slot)->taken = 0; self->slot = 0; }
        break;
    case 0xC:
        if (((GaugeSlot*)self->slot) != 0) { ((GaugeSlot*)self->slot)->taken = 0; self->slot = 0; }
        SetAnimationPlayerSpeed(self->statePlayer, g_gaugeManager->speed448);
        break;
    }
}

s32 ChooseAgentStateByContact(ContactAgent* self)
{
    s32 result = ChooseAgentState(self);
    if (result == 0xB) return result;
    ListedAgentView* n = (ListedAgentView*)GetActiveSwitchedCollider();
    if (n != 0 && IsContactBetweenParts(self, n) != 0) {
        Scratch_0014BDC8 buf;
        InitOwnerMessage((OwnerMessage*)&buf, 0, self);
        result = 0xB;
        n->vtbl[0x50](n, &buf);
    }
    for (ListedAgentView* x = (ListedAgentView*)self->world->list1CCC.head; x != 0; x = x->next) {
        if (x != (void*)self && IsObjectOfKind((BaseObject*)x, 0x12) != 0 && IsContactBetweenParts(self, x) != 0) {
            ChangeAgentState((Agent*)x, 0xB, 0);
        }
    }
    return result;
}

s32 IsContactAgentFree(ContactAgent* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0) return 0;
    if (self->state == 0xB || self->state == 0x10) return 0;
    return 1;
}

s32 HandleContactAgentObjectEvent(ContactAgent* self, ListedAgentView** slot)
{
    if (self->state == 0x10 || self->state == 0xB) return 1;
    if (HandleAgentObjectEvent(self, (AgentHit*)slot) == 0) return 0;
    ListedAgentView* found = (ListedAgentView*)GetActiveSwitchedCollider();
    ListedAgentView* n = *slot;
    if (n == found) {
        OwnerMessage buf;
        InitOwnerMessage(&buf, 0, self);
        n->vtbl[0x50](n, &buf);
    }
    return 1;
}

void EnterContactAgentState(ContactAgent* self, s32 evt, Animation* arg)
{
    EnterAgentState(self, evt, arg);
    switch (self->state) {
    case 0xB:
        CountDownGaugeContacts(g_gaugeManager, self);
        if (((GaugeSlot*)self->slot) != 0) {
            ((GaugeSlot*)self->slot)->taken = 0;
            self->slot = 0;
        }
        break;
    case 0xC:
        if (((GaugeSlot*)self->slot) != 0) {
            ((GaugeSlot*)self->slot)->taken = 0;
            self->slot = 0;
        }
        SetAnimationPlayerSpeed(self->statePlayer, self->clipSpeed);
        break;
    }
}

extern const GaugeParams g_defaultGaugeParams = {
    { 0x41000000, 0x40C00000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3E99999A, 0x3F19999A, 0x3F4CCCCD, 0x3FA66666, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3E99999A },
    { 3.5f, 5.0f }, { 2.0f, 2.5f },
    { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F59999A, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F4CCCCD, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000 }
};

void InitGaugeManager(GaugeManager* self)
{
    InitPlacedObject(self);
    self->maxAmount = 50;
    self->timerSeconds = 90.0f;
    GaugeParams params = g_defaultGaugeParams;
    self->params0 = params;
    self->params1 = params;
    self->params1.p44.Set(12.0f, 12.0f);
    self->params1.p4C.Set(12.0f, 12.0f);
    self->timer.Init();
    self->nextContactTime = 3.4028235e+38f;
    self->maxContactAgents = 2;
    self->contactsStarted = 0;
    g_gaugeManager = self;
}

void BlendParamSets(GaugeManager* self)
{
    s32 i = 0;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, g_gaugeManagerLinks);
    self->device = CreateStateWalker((StateGraph*)self->deviceGraph, 0, 0x3FB, 0);
    GetStateWalkerCurrentKey((StateWalker*)self->device, (s32*)self->buf430);
    AddStateWalkerListener((StateWalker*)self->device, (PlacedObject**)self);
    for (; i < self->slotCount; i++) {
        GaugeSlot* s = &self->slots[i];
        BaseObject* n = FindFirstObjectByIdMode4(self->world, s->id, self);
        s->obj = n;
        s->animation = FindFirstObjectByIdMode1(n->world, 0x3F7, n);
        s->anchor = FindFirstObjectByIdMode1(n->world, 0x3F6, n);
    }
    f32* p = self->poly;
    f32 g = g_currentEntry->dt;
    f32 v = self->poly[0] + g * (p[1] + g * p[2]);
    f32 lo = g_unitRange.lo;
    f32 hi = g_unitRange.hi;
    f32 t;
    if (v < lo) {
        t = lo;
    } else if (hi < v) {
        t = hi;
    } else {
        t = v;
    }
    f32 u = 1.0f - t;
    f32* pa = (f32*)&self->params0;
    f32* pb = (f32*)&self->params1;
    f32* po = self->blend;
    for (u32 k = 0; k < 44; k++) {
        *po++ = u * *pa++ + t * *pb++;
    }
    self->maxSlotAgents = (s32)self->blend[0];
    ComputeGaugeOutputs(self);
}

void ComputeGaugeOutputs(GaugeManager* o)
{
    f32 t = GaugeCurve::Limit((f32)o->amount / (f32)o->maxAmount, 0.0f, 1.0f);
    BlendedGaugeParams* p = (BlendedGaugeParams*)o->blend;
    f32 s;

    s = GaugeCurve::Limit(GaugeCurve::Eval(&p->q30, t), g_unitRange.lo, g_unitRange.hi);
    *(f32*)(o->buf430 + 4) = GaugeCurve::Lerp(s, p->delayMinFrom, p->delayMinTo);
    *(f32*)(o->buf430 + 8) = GaugeCurve::Lerp(s, p->delayMaxFrom, p->delayMaxTo);

    s = GaugeCurve::Limit(GaugeCurve::Eval(&p->q60, t), g_unitRange.lo, g_unitRange.hi);
    *(f32*)(o->buf430 + 0xC) = GaugeCurve::Lerp(s, p->waitMinFrom, p->waitMinTo);
    *(f32*)(o->buf430 + 0x10) = GaugeCurve::Lerp(s, p->waitMaxFrom, p->waitMaxTo);

    *(f32*)(o->buf430 + 0x14) = GaugeCurve::Lerp(GaugeCurve::Limit(GaugeCurve::Eval(&p->q80, t), g_unitRange.lo, g_unitRange.hi), p->f70, p->f74);

    *(f32*)(o->buf430 + 0x18) = GaugeCurve::Lerp(GaugeCurve::Limit(GaugeCurve::Eval(&p->qA0, t), g_unitRange.lo, g_unitRange.hi), p->f90, p->f94);

    o->maxSlotAgents = (s32)GaugeCurve::Lerp(GaugeCurve::Limit(GaugeCurve::Eval(&p->q10, t), g_unitRange.lo, g_unitRange.hi), p->agentCountFrom, p->agentCountTo);

    if (p->triggerFraction < t && o->contactsStarted == 0) {
        o->contactsStarted = 1;
        o->nextContactTime = g_gameClock[1];
    }
}

void ApplyGaugeRatioToEffect(GaugeManager* self)
{
    f32 one = 1.0f;
    f32 ratio = (f32)self->amount / (f32)self->maxAmount;
    f32 c;
    if (ratio < 0.0f) {
        c = 0.0f;
    } else if (one < ratio) {
        c = 1.0f;
    } else {
        c = ratio;
    }
    RaiseScatterLevels(&g_scatterController, 1.0f - c * 0.8f);
}

void FinishGaugeOnTimeout(T217D_510* timer, s32 mode)
{
    if (mode == 1) {
        s32 t[2];
        GetStateWalkerTargetKey((StateWalker*)g_gaugeManager->device, &t[0]);
        GetStateWalkerCurrentKey((StateWalker*)g_gaugeManager->device, &t[1]);
        if (t[0] != 0x3FE && t[1] != 0x3FE) {
            SetStateWalkerTarget((StateWalker*)g_gaugeManager->device, 0x3FF);
            ApplyGaugeRatioToEffect(g_gaugeManager);
        }
    }
}

void UpdateGaugeManager(GaugeManager* self, f32 dt)
{
    s32 tag;
    UpdatePlacedObject(self, dt);
    GetStateWalkerCurrentKey((StateWalker*)self->device, &tag);
    if (tag == 0x3FD) {
        if (self->nextContactTime < g_gameClock[1]) {
            RunGaugeTimedEvent(self);
        }
        if (self->nextSlotTime < g_gameClock[1]) {
            ActivateRandomGaugeSlot(self);
        }
        void* p = GetActiveSwitchedCollider();
        ColliderSlots* o = (ColliderSlots*)p;
        o->vtbl[81](p);
    }
}

void ShowGaugeManagerDisplays(GaugeManager* self)
{
    s32 tag;
    GetStateWalkerCurrentKey((StateWalker*)self->device, &tag);
    s32 p = 0;
    if (tag == 0x3FD) {
        p = AreMenusAndFadeClear();
    }
    if (p) {
        g_gaugeAmountCaption.vt->m14(&g_gaugeAmountCaption);
        g_timerElement.vt->m14(&g_timerElement);
    } else {
        g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
        g_timerElement.vt->m15(&g_timerElement);
    }
}

void* GetGaugeParams(GaugeManager* self)
{
    return (u8*)self + (self->setIndex * 0xB0 + 0x480);
}

void AppendGaugeSlot(GaugeManager* self, s32 value)
{
    s32 i = self->slotCount;
    self->slotCount = i + 1;
    self->slots[i].id = value;
}

void ProjectPointToCamera(Camera* camera, Vec02* in, f32* out);

// Picks a free gauge slot for each of up to two agents: the farthest from the player (and, for the
// second, from the first's place) among the slots on screen, then any. The slot's size is a named
// stride (as DrawTrailRibbon's): its constant then lives across the loop without a register and is
// rematerialised before the multiply, as retail's `li v1,20` shows; the position and rotation
// pointers are set where they are used, so loop.c hoists them after the wait pointer's address.
void RunGaugeTimedEvent(GaugeManager* self)
{
    Vec02 anchor;
    Vec02 pos;
    f32 screen[2];
    Vec02 rot[3];
    Vec02* posp;
    s32 made = 0;
    Vec02* rotp;
    f32* wait = &self->waitMin;
    s32 pass;
    s32 best;
    s32 i;
    f32 bestDist;
    GaugeSlot* slot;
    void* player;
    s32 slotSize = sizeof(GaugeSlot);

    do {
        if (self->contactAgents >= 2) {
            self->nextContactTime = 3.4028235e+38f;
            return;
        }
        ChooseObjectPoolItem((ObjectPool*)self->contactPool);
        if (((ObjectPool*)self->contactPool)->chosenItem == 0) {
            return;
        }
        player = GetActiveSwitchedCollider();
        best = -1;
        bestDist = 0.0f;
        pass = 0;
        do {
            for (i = 0; i < self->slotCount; i++) {
                GaugeSlot* cand = &self->slots[i];
                if (cand->taken != 0 || cand->key != 0) {
                    continue;
                }
                GetObjectWorldPosition((BaseObject*)cand->anchor, (Vec02*)&pos);
                if (pass == 0) {
                    ProjectPointToCamera(*(Camera**)g_camera, (Vec02*)((u8*)cand->obj + 0x140), screen);
                    if (screen[0] < -1.0f || 1.0f < screen[0] || screen[1] < -1.0f || 1.0f < screen[1]) {
                        continue;
                    }
                }
                f32 dist = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(((PlacedObject*)player)->v140), Vu0::Q(pos))));
                if (made == 1) {
                    dist = dist + Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(anchor), Vu0::Q(pos))));
                }
                if (bestDist < dist) {
                    bestDist = dist;
                    best = i;
                }
            }
            if (best >= 0) {
                break;
            }
            pass++;
        } while (pass < 2);
        if (best < 0) {
            return;
        }
        ObjectPool* h = (ObjectPool*)self->contactPool;
        ContactAgent* agent = (ContactAgent*)h->chosenItem;
        slot = (GaugeSlot*)((u8*)self->slots + best * slotSize);
        LaunchChosenPoolObject(h, 0);
        posp = &pos;
        rotp = &rot[0];
        GetObjectWorldPosition((BaseObject*)slot->anchor, (Vec02*)posp);
        GetObjectWorldRotation((BaseObject*)slot->anchor, (Mat02*)rotp);
        agent->desc02()->m1D(agent, posp);
        agent->desc02()->m1E(agent, (Mat02*)rotp);
        agent->desc02()->m20(agent, (Vec02*)D_00248D30);
        agent->desc02()->m21(agent, (Vec02*)D_00248D30);
        if (made == 0) {
            anchor = pos;
        }
        CreateAnimationPlayerWithoutPresetTargets((Animation*)slot->animation, (BaseObject*)slot->obj, 0, (AnimationPlayer**)&slot->key, 0.0f, 1.0f);
        made++;
        AddAnimationPlayerRecordCallback((AnimationPlayer*)slot->key, (PlacedObject**)self);
        self->contactAgents = self->contactAgents + 1;
        self->nextContactTime = g_gameClock[1] + RandomFloatInRange(self->waitMin, wait[1]);
        agent->slot = slot;
        slot->taken = 1;
        agent->clipSpeed = *(f32*)(self->buf430 + 0x14);
    } while (made < 2);
}

void ActivateRandomGaugeSlot(GaugeManager* self)
{
    GaugeSlot* list[16];
    f32 v0[4];
    f32 v1[12];
    if (self->slotAgents >= self->maxSlotAgents) {
        self->nextSlotTime = 3.4028235e+38f;
        return;
    }
    ChooseObjectPoolItem((ObjectPool*)self->slotPool);
    if (!((ObjectPool*)self->slotPool)->chosenItem) return;
    s32 n = 0;
    for (s32 i = 0; i < self->slotCount; i++) {
        GaugeSlot* s = &self->slots[i];
        if (!s->taken && !s->key) list[n++] = s;
    }
    if (n <= 0) return;
    s32 idx = RandomIntInRange(0, n - 1);
    ObjectPool* h = (ObjectPool*)self->slotPool;
    NumberedAgent* c = (NumberedAgent*)h->chosenItem;
    GaugeSlot* s = list[idx];
    (void)LaunchChosenPoolObject(h, 0);
    GetObjectWorldPosition((BaseObject*)s->anchor, (Vec02*)v0);
    GetObjectWorldRotation((BaseObject*)s->anchor, (Mat02*)v1);
    c->desc02()->m1D(c, (Vec02*)v0);
    c->desc02()->m1E(c, (Mat02*)v1);
    c->desc02()->m20(c, (Vec02*)D_00248D30);
    c->desc02()->m21(c, (Vec02*)D_00248D30);
    CreateAnimationPlayerWithoutPresetTargets((Animation*)s->animation, (BaseObject*)s->obj, 0, (AnimationPlayer**)&s->key, 0.0f, 1.0f);
    AddAnimationPlayerRecordCallback((AnimationPlayer*)s->key, (PlacedObject**)self);
    self->slotAgents = self->slotAgents + 1;
    f32 r = RandomFloatInRange(*(f32*)(self->buf430 + 4), *(f32*)(self->buf430 + 8));
    self->nextSlotTime = (*(f32*)&g_gameTime) + r;
    c->slot = s;
    s->taken = 1;
}

void CountDownGaugeContacts(GaugeManager* self, ContactAgent* agent)
{
    if (self->contactAgents == self->maxContactAgents) {
        self->nextContactTime = g_gameTime[0] + RandomFloatInRange(self->waitMin, self->waitMax);
    }
    self->contactAgents = self->contactAgents - 1;
}

void AddToGaugeAmount(GaugeManager* self, NumberedAgent* arg)
{
    s32 hi = self->maxAmount;
    s32 v = self->amount + arg->fC24;
    if (v < 0) {
        v = 0;
    } else {
        if (hi < v) {
            v = hi;
        }
    }
    self->amount = v;
    if (!(v < self->maxAmount)) {
        s32 arr[32];
        s32 t1;
        s32 t2;
        GetStateWalkerCurrentKey((StateWalker*)self->device, &t1);
        GetStateWalkerTargetKey((StateWalker*)self->device, &t2);
        void* p = GetActiveSwitchedCollider();
        ColliderQuerySlots* o = (ColliderQuerySlots*)p;
        s32 r = o->vtbl[81](p);
        if (t1 != 0x3FF && t2 != 0x3FF && r != 2) {
            SetStateWalkerTarget((StateWalker*)self->device, 0x3FE);
            s32 n = GatherObjectsById(self->world, 5, 0x12, 0, 0x20, arr);
            if (n > 0) {
                s32 cnt = n;
                s32* q = arr;
                do {
                    ChangeAgentState((Agent*)*q, 0xB, 0);
                    q++;
                } while (--cnt != 0);
            }
        }
        StopTimer(&g_timerElement);
    }
    ComputeGaugeOutputs(self);
    if (self->slotAgents == self->maxSlotAgents) {
        self->nextSlotTime = g_gameTime[0] + RandomFloatInRange(*(f32*)(self->buf430 + 4), *(f32*)(self->buf430 + 8));
    }
    self->slotAgents = self->slotAgents - 1;
}

void HandleGaugeManagerNotification(GaugeManager* self, s32 kind, void* key)
{
    HandlePlacedObjectNotification(self, kind, key);
    switch (kind) {
    case 6: {
        s32 i;
        for (i = 0; i < self->slotCount; i++) {
            if (self->slots[i].key == key) {
                break;
            }
        }
        if (i < self->slotCount) {
            self->slots[i].key = 0;
        }
        break;
    }
    case 0x14:
        if (key == self->device) {
            s32 out;
            GetStateWalkerCurrentKey((StateWalker*)key, &out);
            if (out == 0x3FD) {
                g_gaugeAmountCaption.target = &self->amount;
                g_gaugeAmountCaption.limit = &self->maxAmount;
                SetWorldActiveFollower(self->world, self);
                StartTimer(&g_timerElement, self->timerSeconds);
                SetTimerLimit(&g_timerElement, 0.0f, FinishGaugeOnTimeout);
                StartTimerCounting(&g_timerElement);
            }
            if (self->tag430 == 0x3FD) {
                g_gaugeAmountCaption.vt->m15(&g_gaugeAmountCaption);
                g_timerElement.vt->m15(&g_timerElement);
                SetWorldActiveFollower(self->world, 0);
            }
            self->tag430 = out;
        }
        break;
    }
}

