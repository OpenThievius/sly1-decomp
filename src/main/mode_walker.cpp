// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x180EB0 to 0x182470 (its .rodata from 0x24B164, its .data from 0x2640B0): class
// 0x72's three list methods, the mode walker (class 0x1A) and its spinning sprite element. It
// ends where the path-speed collider begins (path_speed_collider.cpp), a cut by role only, which
// that file's head explains. One file between an exact edge and a chosen one; it could be
// several (class 0x72's methods have no role in common with the walker). Its name is ours, after
// the mode walker, which holds most of its code.
#include "common.h"
#include "vu0.h"
#include "list_iter.h"
#include "screen_element.h"
#include "switched_collider.h"
#include "path_curve_object.h"
#include "cone_volume.h"
#include "world.h"
#include "masked_collider.h"
#include "object_link.h"
#include "message_body.h"
#include "shapes.h"
#include "game_progress.h"
#include "globals.h"
#include "script_value.h"
#include "fpu.h"
#include "collider.h"
#include "state_walker.h"
#include "asm_func.h"
#include "transform_object.h"
#include "ramp_profile.h"
#include "path_curve.h"
struct PathFollower;
struct ColliderPose;
struct BaseObject;

struct Mat02;


struct ScaledTransform;
// Types other files define, named by the parameters of their functions declared here.

void CopyObjectData(BaseObject* self, BaseObject* src);

void FinishSwitchedCollider(SwitchedCollider* self);

void SetModeWalkerMode(ModeWalker* self, s32 n);

void RemoveFromList(List01* list, void* item);

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

void ComputeColliderJumpVelocity(Collider* self, f32* p, f32* out, f32 a);

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

f32 WrapAngle(f32 a);

void TurnColliderTowardHeading(TurningCollider* self);

void SetPlayerState(Player* self, s32 state, s32 sub);

void ExtractContactsByPartMode(Collider* self, Contact03** out);

void StartMaskedCollider(void* self);

void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);

StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);

s32 CreateWeightCurve(s32 a);

void* AllocateFrontMemory(s32 size);

void RemoveFromList(List01* list, void* item);

void AppendToList(List01* self, void* item);

void AppendToList(List01* self, void* item);

void RegisterObject(BaseObject* self);

void AppendToList(List01* self, void* item);

void RemoveFromList(List01* list, void* item);

void UnregisterObject(BaseObject* self);

void RemoveFromList(List01* list, void* item);

void InitPathFollower(PathFollower* self);

void CapturePathFollowerPose(PathFollower* self, ColliderPose* pose);

struct CountedNotice;
struct PathFollower;
void HandlePathFollowerNotification(PathFollower* self, s32 code, CountedNotice* rec);

void InitPlayerFlaggedCollider(void* self);

void AppendToList(List01* self, void* item);

typedef void (*LaunchFn)(void* unused, void* obj);

s32 HasSpareCount();

void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value);

void SetPlayerState(Player* self, s32 state, s32 sub);

void ActivateSwitchedCollider(void* value);

struct OwnerMessage;
void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner);

void LaunchPlayerFromModeWalker(void* unused, void* obj_);

extern f32 g_gameTime;

// What func_00181BC8 builds on its stack: an owner message (InitOwnerMessage) whose function
// the player calls (slot 76), then the two words it tells its listeners (kind 0x17).
struct LaunchMessage { void* self; s32 val; s32 pad8; LaunchFn fn; };

extern f32 g_gameClock[];

extern f32 g_unitRange[];

void UpdatePathFollower(PathFollower* self, f32 t);

void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner);

void FreePooledContactChain(World* world, Contact03* head);

void SetScaledPositionSpring(PlacedObject* self, f32 scale);

void SetScaledRotationSpring(PlacedObject* self, f32 scale);

s32 IsPadSelectFlagHeld(World* self);


void StartPathFollower(PathFollower* self);

void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);

void AddMatrixAttachment(PlacedObject* self, s32 key, Attachment** out);

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

s32 FindAnimRecord(s32 key);

void SetStateWalkerTarget(StateWalker* self, s32 key);

void TeleportStateWalker(StateWalker* self, s32 key);

struct ClampHelper
{
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo)
        {
            return lo;
        }
        if (hi < x)
        {
            return hi;
        }
        return x;
    }
};

extern Rgba4 D_002623E0[];

extern "C" f32 Cosine(f32 x);

void SetObjectTreeRecordValue(PlacedObject* object, u32 value);

void ApplyPlacedObjectTransform(PlacedObject* self, Camera* cam, ScaledTransform* xf);

extern "C" f32 Cosine(f32 x);

// The file's .data, 0x2640B0 to 0x264230, in retail's order. GCC puts an object of eight bytes
// or more on 8, so the words after D_00264128, D_00264154 and D_00264190 are padding: the three
// vectors at 0x264160 are on 16 (Vec02; func_00128018 loads D_00264180 with lqc2).
ObjectLink g_modeWalkerLinks[10] = {
    { 0, 0x35D, 0xBB8 }, { 4, 0x363, 0xBC0 }, { 4, 0x364, 0xBC4 }, { 4, 0x60, 0xBCC }, { 4, 0x365, 0xBC8 },
    { 2, 0x161, 0x588 }, { 2, 0x162, 0x58C }, { 2, 0x163, 0x590 }, { 4, 0x160, 0x584 }, { 7, 0x366, 0xC08 }
};
f32 D_00264128 = 0.150000006f;
f32 D_00264130[3] = { 30.0f, 0.0f, 0.5f };
f32 D_0026413C = 0.5f;
f32 D_00264140[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_00264150 = 6.0f;
f32 D_00264154 = 3.0f;
Vec02 D_00264160 = { 1.0f, 0.0f, -0.75f, 0.0f };
Vec02 D_00264170 = { 0.699999988f, 0.300000012f, 0.0f, 0.0f };
Vec02 D_00264180 = { -300.0f, 0.0f, 200.0f, 0.0f };
f32 D_00264190 = 150.0f;
f32 D_00264198[3] = { 20.0f, 0.0f, 0.100000001f };
f32 D_002641A4 = 1.5f;
f32 D_002641A8[4] = { 5000.0f, 500.0f, 0.150000006f, 0.0f };
f32 D_002641B8[3] = { 5.0f, 0.0f, 0.100000001f };
f32 D_002641C4 = 3.0f;
f32 D_002641C8[10] = { 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002641F0[16] = { 24.0f, -24.0f, 0.0f, 0.0f, 24.0f, 24.0f, 0.0f, 0.0f, -24.0f, -24.0f, 0.0f, 0.0f, -24.0f, 24.0f, 0.0f, 0.0f };

void RegisterListedKeepObject(ListedKeepObject* self)
{
    RegisterObject(self);
    AppendToList(&self->world->list1C9C, self);
}

void UnregisterListedKeepObject(ListedKeepObject* self)
{
    UnregisterObject(self);
    RemoveFromList(&self->world->list1C9C, self);
}

void CopyListedKeepObject(ListedKeepObject* self, ListedKeepObject* src)
{
    PathCurveKeptBits saved = self->keep;
    CopyObjectData(self, src);
    self->keep = saved;
}

void InitModeWalkerObject(ModeWalker* self)
{
    InitPathFollower(self);
    self->pulseStartTime = -10.0f;
}

void StartModeWalkerObject(ModeWalker* self)
{
    StartPathFollower(self);
    ResolveObjectLinks(self, 0xA, g_modeWalkerLinks);
    self->stateWalker = (StateWalker*)CreateStateWalker((StateGraph*)self->stateGraph, self, -1, 0);
    AddMatrixAttachment((PlacedObject*)self->fBCC, 5, (Attachment**)&self->fBD0);
    ((u8*)self->fBD0)[0x10] = 9;
    ((u8*)self->fBD0)[0x11] = 9;
    ((PlacedObject*)self->fBCC)->desc02()->m2B((PlacedObject*)self->fBCC);
    TransformPointBetweenFrames(0, (PlacedObject*)self->fBC0, (Vec02*)((u8*)self->fBCC + 0x140), (Vec02*)((u8*)self + 0xBE0));
    SetModeWalkerMode(self, 1);
    self->paceChangeTime = 3.4028234663852886e+38f;
    T217D_BF0* base = &g_spinningSpriteElement;
    ((T217D_Float*)&base->alphaScale)->v = 0.0f;
    base->icon = FindAnimRecord(0x36A);
}

// A pad record's stick and buttons (PadRecord's 0x40, 0x44, 0xA8 and 0xAA: pad_record.h's ranges
// clash with this file's view of g_unitRange).
struct PadStick {
    u8 pad00[0x40];
    f32 x;                  // 0x40
    f32 y;                  // 0x44
    u8 pad48[0xA8 - 0x48];
    u16 held;               // 0xA8: func_00181078 tests 0x80
    u16 pressed;            // 0xAA: func_00181078 tests and clears 0x40
};

extern T217D_BF0 g_spinningSpriteElement;
extern u8 g_blankPadRecord[];
extern u8 D_002708C0[];
void ControlPathFollower(PathFollower* self, PadStick* pad, f32 dt);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void ClearPadPressedBits(PadRecord* self, u32 mask);
void UnprojectCameraPoint(Camera* camera, f32* a, Vec02* out);
void BuildBasisFromXAndZHint(const Vec02* x, const Vec02* hint, Mat02* out);
void TransformRotationBetweenFrames(PlacedObject* from, PlacedObject* to, Mat02* in, Mat02* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void ApproachRotationWithRamp(Mat02* from, Mat02* to, RampProfile* ramp, Mat02* outRot, Vec02* outSpin, f32 limit);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
void ClearRootTries(PlacedObject* self);
void SteerWalkerAimAtNearestTarget(T217D_BF0* self, PadStick* pad);
typedef void (*FrameFn)(void* self, Mat02* m);

// The rotation's weight is a Scalar passed straight to MulX (its expand-time slot, a scalar's
// memory, stored after the product as retail's is), and m2 and the axis are declared after
// that statement: the slot is freed there and the axis takes it (retail's 0x50, between d and m2).
void ControlModeWalker(ModeWalker* self, PadStick* pad, f32 dt)
{
    s32 cur;
    s32 target;
    Mat02 m;
    Vec02 pos;
    Vec02 d;
    f32 angle;
    ControlPathFollower(self, pad, dt);
    GetStateWalkerCurrentKey(self->stateWalker, &cur);
    GetStateWalkerTargetKey(self->stateWalker, &target);
    switch (self->walkerMode) {
    case 1:
        if ((pad->held & 0x80) != 0) {
            SetStateWalkerTarget(self->stateWalker, 0x360);
        } else {
            SetStateWalkerTarget(self->stateWalker, 0x35F);
        }
        break;
    case 2:
        if (cur == 0x35F) {
            self->desc05()->m50(self);
        } else {
            if ((pad->pressed & 0x40) != 0) {
                ClearPadPressedBits((PadRecord*)pad, 0x40);
                self->buttonPressTime = g_gameTime;
            }
            if (self->fC00 != 0 && g_gameTime - self->buttonPressTime < D_00264128) {
                self->desc05()->m50(self);
                TeleportStateWalker(self->stateWalker, 0x35F);
                GetStateWalkerCurrentKey(self->stateWalker, &cur);
                GetStateWalkerTargetKey(self->stateWalker, &target);
            }
        }
        break;
    }
    if ((u32)(cur - 0x35F) < 2) {
        if (target == -1 || target == 0x35F || target == 0x360) {
            if (self->walkerMode == 2) {
                pad = (PadStick*)g_blankPadRecord;
            }
            SteerWalkerAimAtNearestTarget(&g_spinningSpriteElement, pad);
            Vu0::Q(m.r[2]) = Vu0::Q(self->m110.r[2]);
            u128 n = Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(m.r[2]), Vu0::Q(((Vec02*)((u8*)g_camera + 0x80))[0])), *(u128*)&self->m110.r[1]);
            Vu0::Q(m.r[1]) = n;
            Vu0::Q(m.r[0]) = Vu0::Cross(n, Vu0::Q(m.r[2]));
            TransformRotationBetweenFrames(0, (PlacedObject*)(((PlacedObject*)self->fBC4)->parent), &m, &m);
            ApproachRotationWithRamp((Mat02*)((u8*)self->fBC4 + 0xD0), &m, (RampProfile*)D_00264130, &m, 0, dt);
            (*(FrameFn**)self->fBC4)[34](self->fBC4, &m);
            UnprojectCameraPoint(g_camera, (f32*)D_002708C0, &pos);
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(((PlacedObject*)self->fBC0)->v140));
            BuildBasisFromXAndZHint(&d, (const Vec02*)&g_unitZVector, &m);
            TransformRotationBetweenFrames(0, (PlacedObject*)(((PlacedObject*)self->fBC0)->parent), &m, &m);
            (*(FrameFn**)self->fBC0)[34](self->fBC0, &m);
            u128 v = Vu0::Q(self->vBE0);
            u128 rot = Vu0::RotateUntied(m, v);
            Vu0::Q(d) = Vu0::MulX(Vu0::Sub(rot, v), Vu0::ScalarAt(D_0026413C));
            Mat02 m2;
            Vec02 k;
            TransformDirectionBetweenFrames((PlacedObject*)((PlacedObject*)self->fBC0)->parent, (PlacedObject*)((PlacedObject*)self->fBCC)->parent, &d, (Vec02*)((u8*)self->fBD0 + 0x20));
            MultiplyMatrices3x3((Mat02*)((u8*)self->fBC0 + 0x1A0), &m, &m2);
            TransformRotationBetweenFrames((PlacedObject*)((PlacedObject*)self->fBC0)->parent, (PlacedObject*)((PlacedObject*)self->fBCC)->parent, &m2, &m2);
            MatrixToAxisAngle(&m2, &angle, &k);
            BuildAxisAngleMatrix(&k, (Mat02*)((u8*)self->fBD0 + 0x40), D_0026413C * angle);
            ClearRootTries(self);
        }
    }
}

void UpdateModeWalkerObject(ModeWalker* self, f32 dt)
{
    s32 buf[4];
    UpdatePathFollower(self, dt);
    if (self->contactChainHead != 0) {
        Contact03* n = (Contact03*)self->contactChainHead;
        do {
            s32 j = (n->end[0].body != self);
            Collider* c = n->end[1 - j].part;
            while (c != 0 && c->partMode == 0) c = (Collider*)c->parent;
            if (c != 0 && (c->partMode == 1 || c->partMode == 4)) {
                InitOwnerMessage((OwnerMessage*)buf, 0, c);
                while (c != 0) {
                    if (((s32 (*)(Collider*, Contact03*, void*))c->desc03()->m47)(c, n, buf) != 0) break;
                    c = (Collider*)c->parent;
                }
                ((Desc05*)self->desc)->m4C(self, buf);
            }
            n = n->next;
        } while (n != 0);
        FreePooledContactChain((World*)self->world, (Contact03*)self->contactChainHead);
        self->contactChainHead = 0;
    }
    f32 t = g_gameClock[1] - self->pulseStartTime;
    f32 v = D_00264140[0] + t * (D_00264140[1] + t * D_00264140[2]);
    f32* r = g_unitRange;
    f32 lo = g_unitRange[0];
    f32 hi = r[1];
    f32 x;
    if (v < lo) x = lo;
    else if (hi < v) x = hi;
    else x = v;
    SetScaledPositionSpring((PlacedObject*)self->fBCC, x * D_00264150);
    SetScaledRotationSpring((PlacedObject*)self->fBCC, x * D_00264154);
    if (self->pulseActive != 0 && self->walkerMode != 2 && g_gameClock[1] - self->pulseFadeStart > 2.0f) self->pulseActive = 0;
}

void RecomputePathFollowerFrame(PathFollower* self);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void BuildBasisFromXAndZHint(const Vec02* x, const Vec02* hint, Mat02* out);
typedef void (*PathSampleFn)(PathCurve* self, f32 t, Vec02* pos, Vec02* dir);

// A matrix set from three rows passed by reference as the signed 128-bit type: the unsigned rows
// the caller passes are each copied to a temporary of their own, a scalar's memory, which retail's
// frame keeps after the matrix locals (docs/TOOLCHAIN.md, "Rows bound by reference as s128").
static inline void SetMatrixRows(Mat02& m, const s128& a, const s128& b, const s128& c)
{
    Vu0::Q(m.r[0]) = (u128)a;
    Vu0::Q(m.r[1]) = (u128)b;
    Vu0::Q(m.r[2]) = (u128)c;
}

void RecomputeModeWalker(ModeWalker* self)
{
    RecomputePathFollowerFrame(self);
    if (self->path != 0 && self->fC08 != 0) {
        Vec02 pos;
        Vec02 dir;
        Mat02 m1;
        Mat02 m2;
        PathCurve* curve = self->path->curve;
        PathSampleFn fn = (PathSampleFn)curve->vt->m01;
        if (fn) {
            fn(curve, self->pathTime, &pos, &dir);
        }
        MultiplyMatrices3x3(&self->m1A0, &self->fC08->m1A0, &m1);
        BuildBasisFromXAndZHint(&dir, (const Vec02*)&g_unitZVector, &m2);
        u128 r0 = Vu0::Q(m1.r[0]);
        u128 r1 = Vu0::Q(m1.r[1]);
        u128 r2 = Vu0::Q(m1.r[2]);
        u128 x = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[0]));
        u128 y = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[1]));
        u128 z = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[2]));
        Mat02 rot;
        SetMatrixRows(rot, x, y, z);
        m2 = rot;
        self->fC08->desc02()->m1D(self->fC08, &pos);
        self->fC08->desc02()->m1E(self->fC08, &m2);
    }
}

void HandlePathFollowerActivation(PathFollower* self, void* v);

void HandleModeWalkerActivation(ModeWalker* self, void* active)
{
    HandlePathFollowerActivation(self, active);
    if (active) {
        T217D_BF0* e = &g_spinningSpriteElement;
        e->vt->m16(e, 2);
        Vu0::Q(e->aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    } else {
        g_spinningSpriteElement.vt->m16(&g_spinningSpriteElement, 0);
        self->pulseActive = 0;
    }
}

void ApplyModeWalkerTint(ModeWalker* o, void* a, void* b)
{
    Rgba4 c;
    u8 from[4];
    *(u32*)from = 0x800000A0;
    if (o->pulseActive) {
        f32 t;
        if (o->walkerMode != 2) {
            t = (g_gameClock[1] - o->pulseFadeStart) * 0.5f;
        } else {
            t = 0.0f;
        }
        f32 s = Cosine((g_gameClock[1] - o->pulseStartTime) * 10.0f);
        f32 p = D_00264160.x + t * (D_00264160.y + t * D_00264160.z);
        f32 x = ClampHelper::Of(p, g_unitRange[0], g_unitRange[1]);
        f32 q = D_00264170.x + s * (D_00264170.y + s * D_00264170.z);
        f32 y = ClampHelper::Of(q, g_unitRange[0], g_unitRange[1]);
        f32 w = x * y;
        f32 u = 1.0f - w;
        c.r = (u8)(u * D_002623E0[0].r + w * from[0]);
        c.g = (u8)(u * D_002623E0[0].g + w * from[1]);
        c.b = (u8)(u * D_002623E0[0].b + w * from[2]);
        c.a = D_002623E0[0].a;
    } else {
        c = D_002623E0[0];
    }
    SetObjectTreeRecordValue(o, *(u32*)&c);
    ApplyPlacedObjectTransform(o, (Camera*)a, (ScaledTransform*)b);
}

void CaptureModeWalkerTarget(ModeWalker* self, void* outv)
{
    Vec02* out = (Vec02*)((u8*)outv + 0x10);
    CapturePathFollowerPose((PathFollower*)self, (ColliderPose*)outv);
    *out = ((PlacedObject*)self->fBC0)->v140;
}

s32 IsModeWalkerRequestBlocked(ModeWalker* self)
{
    if (self->walkerMode != 1 || self->pulseActive != 0 || IsPadSelectFlagHeld(self->world) != 0) return 1;
    return 0;
}

s32 HasModeWalkerAcceptedRequest(ModeWalker* p) { return p->pulseActive != 0; }

void FinishModeWalker(ModeWalker* self)
{
    FinishSwitchedCollider(self);
    SetModeWalkerMode(self, 1);
}

void LaunchPlayerFromModeWalker(void* unused, void* obj_)
{
    Player* obj = (Player*)obj_;
    Vec02 first;
    Vec02 second;

    TransformPointBetweenFrames((PlacedObject*)unused, 0, &D_00264180, &first);
    ComputeColliderJumpVelocity(obj, (f32*)&first, (f32*)&second, D_00264190);
    obj->desc02()->m20(obj, &second);
    f32 r = ArctangentOfRatio(second.y, second.x);
    obj->heading = WrapAngle(r + 3.1415927f);
    TurnColliderTowardHeading(obj);
    SetPlayerState(obj, 4, 0x2B);
}

s32 AcceptModeWalkerRequest(ModeWalker* self, s32* arg)
{
    LaunchMessage loc;
    s32 r;
    Player* g;
    Player* gp;

    if (self->desc05()->m4B(self, arg[0])) {
        return 0;
    }
    if (HasSpareCount()) {
        self->pulseActive = 1;
    }
    self->pulseStartTime = g_gameTime;
    r = HasSpareCount();
    if (r == 0) {
        g = g_player;
        if (g != 0) {
            goto then_block;
        }
    }
    SetModeWalkerMode(self, 2);
    goto tail;
then_block:
    g_player->desc->m02(g_player);
    g_player->desc02()->m1F(g_player, (PlacedObject*)self->fBC8);
    ((BaseObject*)self->fBC8)->desc->m03((BaseObject*)self->fBC8);
    SetSwitchedColliderEnabled((SwitchedCollider*)g_player, 1);
    SetPlayerState(g_player, 2, 2);
    ActivateSwitchedCollider((void*)g_player);
    SetModeWalkerMode(self, 3);
    InitOwnerMessage((OwnerMessage*)&loc, 0, self);
    gp = g_player;
    gp = g_player;
    loc.fn = LaunchPlayerFromModeWalker;
    (void)gp->desc05()->m4C(gp, &loc);
tail:
    loc.self = self;
    loc.val = arg[1];
    self->desc->m0E(self, 0x17, &loc);
    return 1;
}

void HandleModeWalkerNotification(ModeWalker* self, s32 code, MessageBody* rec)
{
    if (code == 0x13) {
        StateWalker* sub = self->stateWalker;
        s32 key = rec->sourceId;
        if (sub != 0 && key == (s32)sub->player) {
            s32 kind = rec->code;
            if (kind != 0x15E) {
                if (kind == 0x15F) {
                    self->fC00 = 0;
                }
            } else {
                self->fC00 = 1;
            }
        }
    }
    HandlePathFollowerNotification(self, code, (CountedNotice*)rec);
}

void ExtractModeWalkerContacts(ModeWalker* self)
{
    ExtractContactsByPartMode(self, (Contact03**)((u8*)self + 0xC04));
}

void SetModeWalkerMode(ModeWalker* self, s32 mode)
{
    s32 old;

    if (mode == self->walkerMode) {
        return;
    }
    old = self->walkerMode;
    if (old < 4) {
        if (old >= 2) {
            self->pulseFadeStart = g_gameClock[1];
        }
    }
    switch (mode) {
    case 0:
        SetStateWalkerTarget(self->stateWalker, 0x35E);
        break;
    case 1:
        SetStateWalkerTarget(self->stateWalker, 0x35F);
        break;
    case 2:
        TeleportStateWalker(self->stateWalker, 0x361);
        self->pulseFadeStart = 3.40282347e+38f;
        break;
    case 3:
        TeleportStateWalker(self->stateWalker, 0x362);
        self->pulseFadeStart = 3.40282347e+38f;
        break;
    }
    if (mode == 0) {
        self->f580 = 0;
    } else if (mode < 0) {
        self->f580 = 1;
    } else if (mode >= 4) {
        self->f580 = 1;
    } else if (mode >= 2) {
        self->f580 = 0;
    } else {
        self->f580 = 1;
    }
    self->walkerMode = mode;
    self->walkerModeTime = g_gameClock[1];
}

extern u8 g_class75List[];
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
void ProjectPointToCamera(Camera* camera, Vec02* in, f32* out);
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);


void SteerWalkerAimAtNearestTarget(T217D_BF0* self, PadStick* pad)
{
    Vec02 p;
    Vec02 best;
    f32 bestScore = 3.40282347e+38f;
    Vu0::Q(best) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    Class75Object* chosen = 0;
    for (Class75Object* o = *(Class75Object**)g_class75List; o != 0; o = *(Class75Object**)&o->link) {
        GetObjectWorldPosition(o, &p);
        ProjectPointToCamera(g_camera, &p, (f32*)&p);
        if (p.z < 100.0f) {
            continue;
        }
        f32 r = o->scale / (p.z * *(f32*)((u8*)g_camera + 0x1F0));
        u128 d = Vu0::Sub(Vu0::Q(p), Vu0::Q(self->aim));
        f32 eps = 0.0001f;
        f32 score = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d))) - r;
        score = eps >? score;
        if (o == self->target) {
            score *= 0.5f;
        }
        if (score < bestScore || (score == bestScore && p.z < best.z)) {
            Vu0::Q(best) = Vu0::Q(p);
            bestScore = score;
            chosen = o;
        }
    }
    self->rateX = ApproachValueWithRamp((RampProfile*)D_00264198, 0, self->rateX, pad->x, g_gameClock[2]);
    f32 y = pad->y;
    if (g_saveData->optionFlags & 0x400) {
        y = -y;
    }
    self->rateY = ApproachValueWithRamp((RampProfile*)D_00264198, 0, self->rateY, y, g_gameClock[2]);
    self->aim[0] = ClampHelper::Of(self->aim[0] + g_gameClock[2] * self->rateX * D_002641A4, -1.0f, 1.0f);
    self->aim[1] = ClampHelper::Of(self->aim[1] - g_gameClock[2] * self->rateY * D_002641A4, -1.0f, 1.0f);
    f32 far = 1000.0f;
    self->aim[2] = ApproachValueWithRamp((RampProfile*)D_002641A8, 0, self->aim[2], far >? best.z, g_gameClock[2]);
    self->target = chosen;
}

struct SpritePackets {
    s32 count;
    u8* data;               // the quadwords, a GIF tag first
};

struct SpriteIcon {
    u8 pad00[0x1C];
    SpritePackets* packets;     // 0x1C
};

extern f32 g_frameStep;
s32 AreMenusAndFadeClear(void);
void AppendPacketQuadwords(PacketWriter* self, s32 n, void* src);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void AddGifStEntry(PacketWriter* b, f32 x, f32 y, f32 z);
void AddGifRgbaEntry(PacketWriter* b, u32 c);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);

void DrawSpinningSpriteElement(T217D_BF0* self)
{
    Rgba4 col;
    Mat02 m;
    Vec02 p;
    if (self->icon == 0) {
        return;
    }
    f32 target = AreMenusAndFadeClear() != 0 ? 1.0f : 0.0f;
    if (g_camera->snapping != 0) {
        self->alphaScale = target;
    } else {
        self->alphaScale = ApproachValueWithRamp((RampProfile*)D_002641B8, 0, self->alphaScale, target, g_frameStep);
    }
    if (self->alphaScale == 0.0f) {
        return;
    }
    AppendPacketQuadwords(&g_gsPacketWriter, ((SpriteIcon*)self->icon)->packets->count - 1, ((SpriteIcon*)self->icon)->packets->data + 0x10);
    BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x30000);
    *(u32*)&col = 0x80FFFFFF;
    BuildAxisAngleMatrix(&g_unitZVector, &m, g_gameTime * D_002641C4);
    BeginGifTag(&g_gsPacketWriter, 0x5C, 3, 0x412);
    col.a = (u8)(s32)(self->alphaScale * (f32)col.a);
    for (u32 i = 0; i < 4; i++) {
        f32 sx = self->aim[0] * 320.0f + 320.0f;
        f32 sy = self->aim[1] * -246.400009f + 246.400009f;
        Vu0::Q(p) = Vu0::Rotate(m, Vu0::Q(D_002641F0[i * 4]));
        p.x = p.x + sx;
        p.y = p.y + sy;
        AddGifStEntry(&g_gsPacketWriter, D_002641C8[i * 2], D_002641C8[i * 2 + 1], 1.0f);
        AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&col);
        f32 left = 1728.0f;
        s32 px = (s32)((p.x + left) * 16.0f);
        s32 py = (s32)((p.y * 0.45454547f + 1936.0f) * 16.0f);
        AddGifXyzfEntry(&g_gsPacketWriter, px, py, 0, 0);
    }
}
