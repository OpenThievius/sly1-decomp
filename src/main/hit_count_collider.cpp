// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_functions.h"
#include "id_linked_object.h"
#include "asm_func.h"
#include "vu0.h"
#include "base_object.h"
#include "switched_collider.h"
#include "globals.h"
#include "screen_element.h"
#include "attachment.h"
#include "animation.h"
#include "owner_message.h"
#include "pad_record.h"
#include "object_finder.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/effect_spawner.h"
#include "functions/game_progress.h"
#include "functions/matrix.h"
#include "functions/path_follower.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/world.h"
struct Vec4;

struct MemberObject;

struct Mat3;
struct Vec4;


// Types other files define, named by the parameters of their functions declared here.
struct ObjectLink;

// A quadratic in t (c[0] + t * (c[1] + t * c[2])), on 16 bytes: the file's four start on a
// 16-byte line, so 0x274A48 is padding after the float before the first.
struct __attribute__((aligned(16))) PaddedQuadratic { f32 c[3]; };

// The file's .data, in retail's order.
s32 g_hitCountColliderLinks[36] = { 4, 1317, 1632, 4, 1320, 1580, 2, 354, 1420, 2, 355, 1424, 6, 352, 1412, 0, 1319, 1636, 0, 1321, 1560, 0, 1322, 1564, 0, 1323, 1568, 0, 1324, 1572, 0, 1325, 1652, 0, 1326, 1656 };
char D_00274A40[4] = "\r";
f32 g_hitCountHitRadius = 150.0f;
PaddedQuadratic D_00274A50 = { { 0.2f, 0.0f, 0.0f } };
f32 g_hitCountRotationRamp[3] = { 40.0f, 0.0f, 0.3f };
PaddedQuadratic D_00274A70 = { { 1.0f, 0.0f, -0.75f } };
PaddedQuadratic D_00274A80 = { { 0.7f, 0.3f, 0.0f } };
f32 g_hitCountStickSpeedScale[2] = { 1200.0f, 1.0f };
f32 g_hitCountMinSpeedLimit = 0.25f;
f32 g_hitCountAccelLimit = 3000.0f;
f32 D_00274AA0 = 0.1f;
f32 g_hitCountTurnRamp[3] = { 20.0f, 0.0f, 0.3f };
f32 g_hitCountPushSpeed = 1000.0f;
f32 g_hitCountItemSpeedRange[2] = { 0.0f, 300.0f };
PaddedQuadratic g_hitCountItemSpinRange = { { -1.0f, 1.0f, 0.0f } };


// Initialises a hit-count collider: the switched collider's defaults, state -1 and 5 hits left.
void InitHitCountCollider(HitCountCollider* self)
{
    InitSwitchedCollider(self);
    self->state = -1;
    self->hitsLeft = 5;
}

// Two floats (+0x2DC, +0x2E0 of f62C) copied as one unaligned doubleword, and a pointer stored
// unaligned into a screen element.
struct __attribute__((packed)) UnalignedFloatPair { u64 v; };
struct __attribute__((packed)) UnalignedPointer { void* p; };


struct StateGraph;
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void SetHitCountColliderState(HitCountCollider* self, s32 state);

// Start of the collider: starts the placed object, keeps its radius as the base radius, resolves
// its links, creates the state walker, and records its heading and its aim object's heading; it
// also points the two caption elements at its collected count and hits left.
void StartHitCountCollider(HitCountCollider* self)
{
    StartPlacedObject(self);
    self->baseRadius = self->radius3CC;
    ResolveObjectLinks(self, 0xC, (ObjectLink*)g_hitCountColliderLinks);
    self->walker = CreateStateWalker((StateGraph*)self->walkerGraph, self, -1, 0);
    self->heading = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    PlacedObject* v = self->aimObject;
    self->aimHeading = ArctangentOfRatio(v->rot.r[0].y, v->rot.r[0].x);
    *(UnalignedFloatPair*)&self->drivenBaseX = *(UnalignedFloatPair*)&((IdLinkedObject*)self->drivenObject)->f2DC;
    CounterCaption* g1 = &g_hitCountCaptionA;
    ((UnalignedPointer*)&g1->target)->p = (u8*)&self->collectedCount;
    CounterCaption* g2 = &g_hitCountCaptionB;
    ((UnalignedPointer*)&g2->target)->p = (u8*)&self->hitsLeft;
    *(void**)&g1->limit = D_00274A40;
    g2->rate = 4.0f;
    SetWorldActiveFollower(self->world, self);
    s32 c = self->itemCount;
    self->items[c] = self;
    self->itemCount = c + 1;
    SetHitCountColliderState(self, 1);
}

extern f32 g_gameTime[];
extern f32 g_stepScale;
extern f32 g_gameClock[];
extern s32 D_0026E228[8];

struct Vec4;
struct RampProfile;
struct Mat3;
void SendHitCountColliderRequest(HitCountCollider* self, BaseObject* value);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void ApproachRotationWithRamp(Mat3* from, Mat3* to, RampProfile* ramp, Mat3* outRot, Vec4* outSpin, f32 limit);
extern "C" f32 Cosine(f32 x);

// Per-frame update of the hit-count collider: updates it as a switched collider, handles a
// collected or touched object, plays the hit clip (each hit uses one of hitsLeft) and sets the step
// scale and radius from the clip's progress. The accepted mark clears 2 s after it was set.
void UpdateHitCountCollider(HitCountCollider* self, f32 t)
{
    f32 buf[12];
    f32 buf2[12];
    u32 ca[4];
    u32 cb[4];
    UpdateSwitchedCollider(self, t);
    if (self->collectedObject) {
        void* h = FindFirstObjectByIdGathered(self->world, 0x101, 0x77, self->collectedObject);
        if (h) SendEmptyMessage((MemberObject*)h);
        self->collectedCount = self->collectedCount + 1;
        self->collectedObject->desc->m03(self->collectedObject);
        self->collectedObject = 0;
    }
    if (self->touchedObject) {
        SendHitCountColliderRequest(self, self->touchedObject);
        self->touchedObject = 0;
    }
    if (self->hitPlayer) {
        if (self->hitPlayer->speed == 0.0f) {
            StopAnimationPlayer(self->hitPlayer);
            self->hitPlayer = 0;
        }
    } else if (self->hitPending) {
        CreateAnimationPlayerWithoutPresetTargets((Animation*)self->hitClip, self, 0, &self->hitPlayer, 0.0f, 1.0f);
        self->hitsLeft = self->hitsLeft - 1;
        D_0026E228[0] = -1;
    }
    self->hitPending = 0;
    f32 u;
    if (self->hitPlayer) {
        f32* lim = &g_unitRange.lo;
        f32 r = self->hitPlayer->time / self->hitPlayer->anim->length;
        f32* pp = D_00274A50.c;
        f32 lo = lim[0];
        f32 hi = lim[1];
        f32 v = pp[0] + r * (pp[1] + r * pp[2]);
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        g_stepScale = v;
        u = r;
    } else {
        g_stepScale = 1.0f;
        u = 0.0f;
    }
    f32 w = u * g_hitCountHitRadius + (1.0f - u) * self->baseRadius;
    self->radius3D0 = w;
    self->radius3CC = w;
    if (self->acceptedMark) {
        if (g_gameTime[0] - self->markStartTime > 2.0f) self->acceptedMark = 0;
    }
    f32 ang = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    BuildAxisAngleMatrix((const Vec4*)&g_unitZVector, (Mat3*)buf, self->aimHeading - ang);
    ApproachRotationWithRamp(&self->aimObject->rot, (Mat3*)buf, (RampProfile*)g_hitCountRotationRamp, (Mat3*)buf2, 0, t);
    self->aimObject->desc02()->m1E(self->aimObject, (Mat3*)buf2);
    ca[0] = 0x8010FF00;
    cb[0] = 0x800000FF;
    if (self->acceptedMark) {
        f32 q;
        if (self->state != 2) q = (g_gameClock[1] - self->stateTime) * 0.5f;
        else q = 0.0f;
        f32 z = Cosine((g_gameClock[1] - self->acceptedTime) * 10.0f);
        f32 x0 = D_00274A70.c[0] + q * (D_00274A70.c[1] + q * D_00274A70.c[2]);
        f32 lo = g_unitRange.lo;
        f32 hi = g_unitRange.hi;
        f32 x = x0 < lo ? lo : (hi < x0 ? hi : x0);
        f32 y = D_00274A80.c[0] + z * (D_00274A80.c[1] + z * D_00274A80.c[2]);
        f32 lo2 = g_unitRange.lo;
        f32 hi2 = g_unitRange.hi;
        if (y < lo2) y = lo2;
        else if (hi2 < y) y = hi2;
        f32 m = x * y;
        f32 n = 1.0f - m;
        f32 r0 = n * ((u8*)ca)[0] + m * ((u8*)cb)[0];
        f32 r1 = n * ((u8*)ca)[1] + m * ((u8*)cb)[1];
        f32 r2 = n * ((u8*)ca)[2] + m * ((u8*)cb)[2];
        ((u8*)ca)[0] = (s32)r0;
        ((u8*)ca)[2] = (s32)r2;
        ((u8*)ca)[1] = (s32)r1;
    }
    SetObjectTreeRecordValue(self, ca[0]);
    ((IdLinkedObject*)self->drivenObject)->f2DC = self->stickGain * self->drivenBaseX;
    ((IdLinkedObject*)self->drivenObject)->f2E0 = self->stickGain * self->drivenBaseY;
    ((IdLinkedObject*)self->drivenObject)->linkId = 0;
}

s32 AreMenusAndFadeClear();

// Shows the two counter captions (method 0x14) while the menus and fade are clear and hides them
// (method 0x15) otherwise.
void ShowHitCountColliderCounters()
{
    if (AreMenusAndFadeClear()) {
        g_hitCountCaptionA.vt->m14(&g_hitCountCaptionA);
        g_hitCountCaptionB.vt->m14(&g_hitCountCaptionB);
    } else {
        g_hitCountCaptionA.vt->m15(&g_hitCountCaptionA);
        g_hitCountCaptionB.vt->m15(&g_hitCountCaptionB);
    }
}


void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);
void SetHitCountColliderState(HitCountCollider* self, s32 state);

// Per-frame control while the player drives the collider: with an object in f628 that has run out
// (its value at 0x18 is 0) it calls m50 in state 2 or moves 3 to 4; outside state 1 it resets its
// movement vector and handles the pad input.
void ControlHitCountCollider(HitCountCollider* self, PadRecord* ev, f32 dt)
{
    AnimationPlayer* obj = self->animPlayer;
    if (obj != 0 && obj->speed == 0.0f) {
        switch (self->state) {
        case 2:
            self->desc05()->m50(self);
            break;
        case 3:
            SetHitCountColliderState(self, 4);
            break;
        }
    }
    if (self->state != 1) {
        self->speedLimit = g_hitCountMinSpeedLimit;
        self->desiredVelocity = g_zeroVector;
    } else {
        if (0.0f < ev->stickMagnitude) {
            ComputeCameraRelativeStickHeading(g_camera, ev, 0, &self->heading);
        }
        f32 k = g_hitCountStickSpeedScale[0];
        f32 m = g_hitCountMinSpeedLimit;
        m = m >? ev->stickMagnitude;
        self->speedLimit = m;
        ComputePolarOffset((Vec3*)&self->desiredVelocity, self->heading, k * ev->stickMagnitude, 0.0f);
        self->stickGain = (D_00274AA0 >? ev->stickMagnitude);
        if (0.0f < ev->secondStickMagnitude) {
            ComputeCameraRelativeStickHeading(g_camera, ev, 1, &self->aimHeading);
            if (self->walker != 0) {
                SetStateWalkerTarget((StateWalker*)self->walker, 0x485);
            }
        } else if (self->walker != 0) {
            SetStateWalkerTarget((StateWalker*)self->walker, 0x484);
        }
    }
    HandleStepSequenceSkipButtons(self, ev);
    ClearRootTries(self);
}


void ClampVectorLength(Vec4* v, Vec4* out, f32 max);

// Per-frame step: steps the collider, turns it toward its heading (yaw only) with the turn ramp,
// and applies a force that pulls its velocity toward the target velocity at 0x650, limited to a
// maximum acceleration, divided by dt.
void StepHitCountCollider(HitCountCollider* self, f32 dt)
{
    Mat3 rot;
    Vec4 accel;
    Vec4 t;
    StepCollider(self, dt);
    BuildYawPitchMatrix(self->heading, 0.0f, &rot);
    TurnColliderTowardRotation(self, dt, &rot, g_hitCountTurnRamp);
    Vu0::Q(accel) = Vu0::Sub(Vu0::Q(self->desiredVelocity), Vu0::Q(self->v150));
    ClampVectorLength(&accel, &accel, g_hitCountAccelLimit * self->speedLimit * dt);
    Vu0::Q(t) = Vu0::FromFloat(dt);
    Vu0::Q(accel) = Vu0::DivX(Vu0::Q(accel), Vu0::Q(t));
    AddColliderForce(self, &accel);
}


// Contact method: notes what touched the collider (the other end of the contact): a kind-0x21 body
// sets hitPending while hits are left, else is kept as touchedObject unless hitPlayer is set; a
// body with id 0x52F is kept as collectedObject.
void NoteHitCountColliderContact(HitCountCollider* self, BodyContact* c, s32 end)
{
    ContactEnd03* e = &c->end[1 - end];
    if (IsObjectOfKind(e->body, 0x21)) {
        if (self->hitsLeft > 0) {
            self->hitPending = 1;
            return;
        }
        if (self->hitPlayer == 0) self->touchedObject = e->body;
        return;
    }
    if (MatchesObjectId(e->body, 0x52F)) self->collectedObject = e->body;
}

// The velocity is read first, and each of the three references to the end takes its address
// again through Q (docs/toolchain/reloads-and-stores.md, "Three adds of one address").
void ResolveHitCountColliderContact(HitCountCollider* self, BodyContact* c, s32 end)
{
    AnimationPlayer* p = self->hitPlayer;
    if (p != 0) {
        u128 vel = Vu0::Q(c->end[end].v30);
        u128 k = Vu0::Scalar((g_hitCountHitRadius - self->baseRadius) / p->anim->length);
        u128 d = Vu0::Sub(Vu0::Q(c->end[end].point), Vu0::Q(self->v140));
        Vu0::Q(c->end[end].v30) = Vu0::MulAddX(vel, Vu0::DivX(d, Vu0::Length(d)), k);
    }
}

extern s32 g_buttonCodeFlags;

// A request is blocked while button-code flag bit 1 is set or the pad-select flag is held.
s32 IsHitCountColliderRequestBlocked(HitCountCollider* self)
{ if ((g_buttonCodeFlags & 1) || IsPadSelectFlagHeld(self->world)) return 1; return 0; }

// What slot 76 tells its own slot 14 (kind 0x17) when it is hit: itself and the message's owner.
struct OwnerNotice { void* sender; void* owner; };
void SetHitCountColliderState(HitCountCollider* self, s32 state);

// Handles a request to take over the collider: refused when m4B says so, replies to a mode 0
// request, and when it is in state 2 to 4 or has a mark it just reports it accepted; otherwise,
// with a spare available, it goes to state 2 and sets the accepted mark.
s32 AcceptHitCountColliderRequest(HitCountCollider* self, OwnerMessage* arg)
{
    OwnerNotice local;
    s32 m;
    if (self->desc05()->m4B(self, arg->mode)) return 0;
    if (arg->mode == 0) {
        if (arg->reply != 0) arg->reply(arg->c, self);
    }
    m = self->state;
    if (m < 5) {
        if (!(m < 2)) return 1;
    }
    if (self->acceptedMark != 0) return 1;
    if (HasSpareCount()) {
        SetHitCountColliderState(self, 2);
        self->acceptedMark = 1;
        self->acceptedTime = g_gameTime[0];
    } else {
        SetHitCountColliderState(self, 3);
    }
    local.sender = self;
    local.owner = arg->owner;
    self->desc->m0E(self, 0x17, &local);
    return 1;
}

// True while in states 2 to 4 or once the accepted mark is set.
s32 HasHitCountColliderAcceptedRequest(HitCountCollider* self) { if (self->state < 5) { if (self->state >= 2) return 1; } return self->acceptedMark != 0; }

void SetHitCountColliderState(HitCountCollider* self, s32 state);

// Finishes the switched collider and enters state 1.
void FinishHitCountCollider(HitCountCollider* self)
{
    FinishSwitchedCollider(self);
    SetHitCountColliderState(self, 1);
}

// The reply of a hit-count collider's request: pushes the receiver away from the sender,
// horizontally (z dropped), with a fixed speed, by calling the receiver's method 0x20; with no
// distance it pushes along the x axis.
void PushRequesterAwayFromSender(void* c, void* receiver)
{
    PlacedObject* from = (PlacedObject*)c;
    PlacedObject* to = (PlacedObject*)receiver;
    Vec4 d;
    Vec4 v;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(to->v140), Vu0::Q(from->v140));
    d.z = 0.0f;
    u128 s = Vu0::ScalarAt(g_hitCountPushSpeed);
    Vu0::Set(v, Vu0::MulX(Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector)), s));
    to->desc02()->m20(to, &v);
}


// Sends the collider a request message from value, with PushRequesterAwayFromSender as its reply,
// through the collider's method 0x4C.
void SendHitCountColliderRequest(HitCountCollider* self, BaseObject* value)
{
    OwnerMessage local;
    InitOwnerMessage(&local, 0, value);
    local.c = value;
    local.reply = PushRequesterAwayFromSender;
    self->desc05()->m4C(self, (void*)&local);
}

extern f32 g_gameClock[];
extern s32 D_0026E228[8];
extern u8 g_scatterController[];

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
f32 WrapAngle(f32 a);
struct ScatterController;
f32 ApproachAngleWithRamp(f32 a, f32 b, f32 c, void* self, f32* out);
void SetPauseMenuLayerPage(PauseMenu* a, s32 b, s32 c);

// Changes the collider's state (the value at +0x610). Leaving state 2 records the time and sets a
// mark; entering state 2 or 3 stores the opposite of the heading as the facing angle, and each new
// state sets the state walker's target and its own values.
void SetHitCountColliderState(HitCountCollider* self, s32 state)
{
    Animation* s2;
    f32 f12;
    if (state == self->state) return;
    if (self->state == 2) {
        f32 t = g_gameClock[1];
        self->hitsLeft = 3;
        self->markStartTime = t;
    }
    *(s32*)&self->stickGain = 0;
    if (state < 4) if (state >= 2) {
        Vec4 q;
        f32 a = ArctangentOfRatio(self->v150.y, self->v150.x);
        f32 b = WrapAngle(a + 3.14159274f);
        self->heading = b;
        self->aimHeading = b;
        q = g_zeroVector;
        f32 r = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
        ApproachAngleWithRamp(r, self->heading, 0.0f, g_hitCountTurnRamp, &q.z);
        self->desc02()->m21(self, (Vec4*)&q);
        self->hitsLeft = 0;
        D_0026E228[0] = -1;
        if (state == 3) RaiseScatterLevels((ScatterController*)g_scatterController, 1.0f);
    }
    f12 = 0.0f;
    switch (state) {
    case 0: s2 = self->stateAnims[0]; break;
    case 1: s2 = self->stateAnims[1]; break;
    case 2: s2 = self->stateAnims[2]; self->markStartTime = 3.4028235e+38f; break;
    case 3: s2 = self->stateAnims[3]; break;
    case 4:
        SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0x1A);
        s2 = self->stateAnims[3];
        f12 = s2->length;
        break;
    }
    ReplaceAnimationPlayer(s2, self, 1, &self->animPlayer, f12, 1.0f);
    self->state = state;
    self->stateTime = g_gameClock[1];
}

// Appends value to the collider's list of place points.
void AddHitCountColliderId(HitCountCollider* self, BaseObject* value)
{
    s32 n = self->placePointCount;
    self->placePoints[n] = value;
    self->placePointCount = n + 1;
}

f32 RandomFloatInRange(f32 a, f32 b);

// Puts an item object back into play: when it is not attached, picks the place point farthest from
// the attached items (in x and y), fades the item in there and, for a class 0x21 item, gives it a
// random velocity and spin; the item is kept in the collider's item array.
void PlaceHitCountColliderItem(HitCountCollider* self, PlacedObject* obj)
{
    s32 i;
    for (i = 0; i < self->itemCount; i++) {
        if (self->items[i] == obj) {
            break;
        }
    }
    s32 n = i + 1;
    if (!IsObjectAttached(obj)) {
        Vec4 p;
        Vec4 best;
        best = g_zeroVector;
        f32 bestDist = 0.0f;
        for (s32 j = 0; j < self->placePointCount; j++) {
            ConvertPositionToWorld(self->placePoints[j], &p);
            f32 nearest = 3.40282347e+38f;
            for (s32 k = 0; k < self->itemCount; k++) {
                PlacedObject* o = (PlacedObject*)self->items[k];
                if (IsObjectAttached(o)) {
                    u128 d = Vu0::Sub(Vu0::Q(p), Vu0::Q(o->pos));
                    nearest = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d))) <? nearest;
                }
            }
            if (bestDist < nearest) {
                bestDist = nearest;
                best = p;
            }
        }
        FadeInPlacedObject((Collider*)obj, 1.0f);
        best.z = obj->pos.z;
        obj->desc02()->m1D(obj, &best);
        if (IsObjectOfKind(obj, 0x21)) {
            Vec4 vel;
            Vec4 spin;
            ComputePolarOffset((Vec3*)&vel, RandomFloatInRange(-3.1415927f, 3.1415927f), RandomFloatInRange(g_hitCountItemSpeedRange[0], g_hitCountItemSpeedRange[1]), 0.0f);
            obj->desc02()->m20(obj, &vel);
            Vu0::Set(spin, Vu0::FromFloats(0.0f, 0.0f, RandomFloatInRange(g_hitCountItemSpinRange.c[0], g_hitCountItemSpinRange.c[1])));
            obj->desc02()->m21(obj, &spin);
        }
    }
    self->items[i] = obj;
    self->itemCount = n >? self->itemCount;
}
