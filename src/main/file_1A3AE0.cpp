// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1A3AE0 to 0x1A7FE8 (its .rodata from 0x24C9C0, its .data from 0x26B778): class
// 0x15 (the walker collider), the pair controller (class 0x5F) and the paired objects (class
// 0x42), classes 0x43, 0x44 and 0x45 (the hit target, the sound state object, the object
// creator) and the pad pattern player. It ends at an exact edge (file_1A7FE8.cpp's start). Its
// start is NOT proved by retail: the cut from effect.cpp at 0x1A3AE0 follows the change of role
// only (effect.cpp says what range retail's data allows), and these families could themselves
// be several files. Its .rodata is the FLT_MAX constants of its functions (literals in their code),
// the jump tables, the triangle func_001A3C40 copies and the pose table func_001A4718 copies; its
// .data is the globals below. Named after its first address: none of its families names the whole.
#include "common.h"
#include "vu0.h"
#include "list_iter.h"
#include "aim_blend_grid.h"
#include "effect_owner.h"
#include "effect_spawner.h"
#include "world.h"
#include "camera.h"
#include "object_gatherer.h"
#include "switched_collider.h"
#include "packet_writer.h"
#include "effect.h"
#include "globals.h"
#include "group_marker.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "paired_object.h"
#include "hit_target.h"
#include "sound_state_object.h"
#include "object_creator.h"
#include "object_pool.h"
#include "pair_controller.h"
#include "screen_element.h"
#include "shapes.h"
#include "object_link.h"
#include "target_binding.h"
#include "game_progress.h"
#include "object_message.h"
#include "object_event.h"
#include "pad_record.h"
#include "animation.h"
#include "attachment.h"
#include "message_body.h"
#include "asm_func.h"
#include "mul_rotation.h"
#include "ramp_profile.h"
#include "node_query.h"




void InitCollider(Collider* self);

void SetListLinkOffset(void* p, s32 n);

void AppendToList(void* list, void* item);

void RemoveFromList(void* table, void* self);

extern f32 g_gameClock[];



extern f32 g_gameTime;


extern Camera* g_camera;

// A list walk whose frame pushes itself when it is made and pops itself when it goes out of scope.
struct ListWalk : ListFrame {
    ListWalk(List01* l)
    {
        list = l;
        link = (u8*)l;
        offset = l->offset;
        prev = g_activeListFrames;
        g_activeListFrames = this;
    }
    ~ListWalk() { g_activeListFrames = prev; }
    // The list's first element, from the list's head.
    void* First()
    {
        void* n = *(void**)list;
        link = (u8*)n + offset;
        return n;
    }
    void* Next()
    {
        void* n = *(void**)link;
        link = (u8*)n + offset;
        return n;
    }
};

// The loop walks an intrusive list with an iterator that registers itself on a global stack
// (D_0027B314) for its lifetime and unregisters in its destructor.





void RemoveFromList(List01 *a, ObjectGatherer *b);

void AppendToList(List01 *a, ObjectGatherer *b);

u32 IsListEmpty(List01* list);

void ClearRootTries(PlacedObject* self);

u32 IsListEmpty(List01* p);

void LoadCollider(void* self);

void ResolveObjectLinks(void* self, s32 n, void* data);

extern Quad219C D_00275C50;

s32 IsObjectOfKind(void* self, s32 kind);

void TransformRotationBetweenFrames(void* a0, void* a1, void* a2, void* a3);


s32 IsObjectOfKind(void* node, s32 kind);

s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);



void StartPlacedObject(void* self);

void ResolveObjectLinks(void* self, s32 a1, void* a2);

void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);

void* CreateStateWalker(void* a, void* b, s32 c, s32 d);

s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

void SetWalkerColliderState(void* self, s32 n);

void SetWalkerColliderSubState(void* self, s32 v);


void ComputeCameraRelativeStickHeading(void* a, void* b, s32 c, void* d);

// The three floats of ApproachAngleWithRamp's ramp (D_0024C9C0), copied as a doubleword and a word.
struct RampParams { s64 a __attribute__((packed)); s32 b; };

// What func_001A3C40 turns its object with: the yaw matrix it builds and the ramp it approaches the
// heading by.
struct HeadingFrame {
    Mat02 rot;          // 0x00
    RampParams ramp;    // 0x30
};

extern const f32 D_0024C9C0[4];

extern f32 g_frameDt;

void StopAnimationPlayer(AnimationPlayer* obj);

void ReadWalkerColliderInput(WalkerCollider* self, PadRecord* src);

f32 ArctangentOfRatio(f32 a, f32 b);

f32 ApproachAngleWithRamp(u8* p, s32 a, f32 b, f32 c, f32 d);

void BuildYawPitchMatrix(f32 unused, f32 value, f32* out);

void InitSwitchedCollider(void* self);

void SetSoundStateObjectState(void* child, int flag);

void ResolveObjectLinks(void* self, int idx, void* table);

void FindOrBuildMemberGroup(void* sub, void* self);

// Eight bytes kept across a copy, at any alignment.
struct Bytes8 { u8 b[8]; };

void CopyCollider(void* self);


void SetPairedState(PairedObject* self, int flag);

s32 IsObjectOfKind(void* self, int kind);




void SetHitTargetState(void* self, int flag);

extern f32 D_0026B850[4];

void StepCollider(void* self);

void RotateMatrixUpright(void* sub, int zero, void* out);

void TurnColliderTowardRotation(void* self, void* out, void* data, f32 scale);

void* FindFirstObjectByIdGathered(void* a, int b, int c, void* d);

void SetObjectCreatorState(ObjectCreator* self, int flag);

// A step of a pad pattern: the two bytes the actuators get, and how long they keep them.
struct PadStep {
    u8 bytes[2];            // 0x00
    u8 pad02[0x04 - 0x02];
    f32 delay;              // 0x04
};

// A pad pattern (g_padPatterns, 0x104 bytes): count steps, played in a loop.
struct PadPattern {
    s32 count;              // 0x00
    PadStep steps[32];      // 0x04
};

// The pad pattern player (0x20 bytes, PadRecord::fBC): the pad it drives, its state (0 and 1
// idle, 2 playing, 3 and 4 stopping), the pattern and its step, the time left to play and the time
// left in the step (or before stopping).
struct PadPatternPlayer {
    u8 pad00[0x04];
    s32 port;               // 0x04: PadRecord::f04 (func_001A7B20)
    s32 slot;               // 0x08: PadRecord::f08
    s32 state;              // 0x0C
    PadPattern* pattern;    // 0x10
    s32 step;               // 0x14
    f32 timeLeft;           // 0x18
    f32 stepTime;           // 0x1C
};

int IsPadPatternEnabled(void* a);

void RemoveFromList(void* a, void* b);

void AppendToList(void* a, void* b);

void SetSoundStateObjectState(void* child, s32 flag);

void DetachPairedPartner(void* self, void* obj);

s32 PairWithNearestWaitingObject(void* self, void* child);

f32 RandomFloatInRange(f32 a, f32 b);

void SetPairedState(void* self, s32 mode);

s32 PairWithNearestFreeObject(void* self, void* child);

void InitCollider(void* self);

extern f32 D_0026B7D8[4];

void StepCollider(WalkerCollider* self);

void TurnColliderTowardRotation(WalkerCollider* self, f32* buf, u8* table, f32 scale);

extern PadPattern g_padPatterns[11];

s32 SetPadActuatorBytes(s32 port, s32 slot, u8* bytes);

s32 HasAnimationDrivenAttachment(void* ctx);

extern s32 g_padPatternSetting;

s32 GetCurrentEntryVariant(void);

void UpdatePairControllerTuning(void* self, f32 t);

void SetPairControllerState(void* self, void* p);

void* AreMenusAndFadeClear(void* zero);

void RemoveFromList(void* table, void* node);

void AppendToList(void* table, void* node);

void SetSoundStateObjectState(void* node, s32 flag);

void UpdateCollider(void* self);

s32 GetSoundStateObjectState(SoundStateObject* self);

void SetSoundStateObjectState(SoundStateObject* node, s32 flag);

void SetColliderAnchors(Collider* self, s32 a, s32 b, s32 c, s32 d);

void RemoveFromList(u8* a, void* b);

void AppendToList(u8* a, void* b);

void ComputePolarOffset(void* self, f32 x, f32 y, f32 z);

s32 ChooseHitTargetState(HitTarget* self);

void SetHitTargetState(HitTarget* self, int flag);

void SetEffectSpawnerInactive(void* x);

void SetEffectSpawnerActiveForever(void* x);

void HandleSwitchedColliderNotification(void* self, s32 code, void* rec);

void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void SetEffectSpawnerInactive(void* self);

void StartSoundEffect(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, void* a5);

void TeleportStateWalker(void* a, s32 b);

void SetStateWalkerTarget(void* a, s32 b);


void StopAnimationPlayer(void* p);

s32 CreateAnimationPlayerWithoutPresetTargets(void* a, void* b, s32 c, void* d, f32 x, f32 y);

void TeleportStateWalker(void* p, s32 a);

void SetStateWalkerTarget(void* p, s32 a);

void StopSoundRecord(void* p, s32 flag);

void StartSoundEffect(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

extern void* g_hitTargetStateIds[10];

void RemoveFinishedHitTarget(void* a, void* b);

void TeleportStateWalker(void* self, void* item);

void SetStateWalkerTarget(void* self, void* item);

void ComputeColliderImpulseResponse(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 CountListItems(List01* list);

void RemoveFromList(void* list, void* item);

s32 RandomIntInRange(s32 a, s32 b);

void SetColliderAnchors(Collider* self, s32 a, void* b, s32 c, s32 d);

void SetColliderAnchors(Collider* self, s32 a, void* b, s32 c, void* d);

// A pair controller's pose (0xC0 bytes, twelve quadwords): the table func_001A4718 copies into
// PairController::poseA and poseB (g_pairControllerPoseTable).
struct __attribute__((aligned(16))) PairPose {
    AlignedQuad q[12];
};

extern const PairPose g_pairControllerPoseTable;

void InitPlacedObject(PairController* self);

void SetListLinkOffset(void* self, s32 value);

void CopyMemory(void* dst, void* src, s32 count);

void BeginLevelExit(WalkerCollider* a, s32 n);

void SetEffectSpawnerActiveForever(void* p);

void SetEffectSpawnerInactive(void* p);

void TeleportStateWalker(void* p, s32 n);

void SetStateWalkerTarget(void* p, s32 n);

s32 CreateAnimationPlayerWithoutPresetTargets(void* a, WalkerCollider* self, s32 c, s32* out, f32 fa, f32 fb);

void StopSoundRecord(s32* p, s32 n);

struct LinkedObject { u8 pad0[0x2D4]; s32 f2D4; };

void UpdatePlacedObject(PairController* self);

s32 ChoosePairControllerState(PairController* self);

void SetPairControllerState(PairController* self, s32 mode);

void SpawnPairedObject(PairController* self);

void StartPairedObjects(PairController* self);

void SetObjectCreatorState(ObjectCreator* t, s32 flag);

extern void SetPairedState(PairedObject* o, s32 n);


void StopPadPatternOutput(PadPatternPlayer* self);

void SetPadPatternState(PadPatternPlayer* self, s32 state);

// func_001A7CE8 passes no time (whatever $f12 holds): this declaration leaves the float out.
void StartPadPattern(PadPatternPlayer* self, PadPattern* p);

extern f32 g_frameStep;

extern u8 g_elementStack[];

extern u8 g_scatterController[];

void PushStackElement(u8* a, u8* b);

void SetWorldActiveFollower(void* host, PairController* self);

void SetPairedState(PairController* o, s32 n);

void SetWalkerColliderState(void* a, s32 n);

void RaiseScatterLevels(u8* a, f32 b);

void ResetScatterLevels(u8* a);

void SetPauseMenuLayerPage(u8* a, s32 b, s32 c);

void StopAnimationPlayer(PairedObject* o);

void DestroyStateWalker(PairedObject* o);

void ReleasePairedAttachment(void* p, PairedObject* o);

void ActivatePairedAttachment(void* p, PairedObject* o);

void FinishPairedObjectTransition(void* p, PairedObject* o);

void RemovePairedObject(void* p, PairedObject* o);

void AttachPairedPartner(void* p, PairedObject* o);

void CreateAnimationPlayer(f32 a, f32 b, void* h, PairedObject* o, s32 n, TargetBinding* buf, s32 e, void** out);


// The coefficients of a quadratic in t (a + bt + ct^2), as the pose holds them.
struct QuadraticCoeffs { f32 a, b, c; };

// A quadratic evaluated at t and clamped to a range (func_001A5760).
struct ClampedQuadratic {
    static f32 Eval(const QuadraticCoeffs* p, f32 t)
    {
        return p->a + t * (p->b + t * p->c);
    }
    static void Clamp(f32& c, f32 v, const ValueRange* r)
    {
        f32 lo = r->lo;
        f32 hi = r->hi;
        if (v < lo) {
            c = lo;
        } else if (hi < v) {
            c = hi;
        } else {
            c = v;
        }
    }
    static void Get(f32& c, const QuadraticCoeffs* p, f32 t)
    {
        Clamp(c, Eval(p, t), &g_unitRange);
    }
};

ObjectLink D_0026B778[2] = { { 0x2, 0x28E, 0x640 }, { 0x2, 0x292, 0x650 } };

ObjectLink D_0026B790[6] = {
    { 0x4, 0x291, 0x64C },
    { 0x4, 0x299, 0x664 },
    { 0x4, 0x297, 0x65C },
    { 0x4, 0x298, 0x660 },
    { 0x2, 0x29A, 0x680 },
    { 0x2, 0x29B, 0x67C },
};

f32 D_0026B7D8[4] = { 20.0f, 0.0f, 0.30000001192092896f, 0.0f };

ObjectLink g_pairedObjectLinks[6] = {
    { 0x2, 0x29C, 0x58C },
    { 0x2, 0x29D, 0x590 },
    { 0x2, 0x29E, 0x594 },
    { 0x2, 0x29F, 0x598 },
    { 0x2, 0x2A1, 0x5A0 },
    { 0x2, 0x2A2, 0x5A4 }
};

ObjectLink g_hitTargetLoadLinks[1] = { { 0x2, 0x2A3, 0x560 } };

ObjectLink g_hitTargetStartLinks[1] = { { 0x6, 0x2AE, 0x578 } };

f32 D_0026B850[4] = { 2.0f, 0.0f, 0.699999988079071f, 0.0f };

void* g_hitTargetStateIds[10] = { (void*)0x2A4, (void*)0x2A5, (void*)0x2A6, (void*)0x2A7, (void*)0x2A8, (void*)0x2A9, (void*)0x2AA, (void*)0x2AB, (void*)0x2AC, (void*)0x2AD };

ObjectLink g_soundStateObjectLinks[1] = { { 0x2, 0x2AF, 0x55C } };

s32 g_soundStateSoundIds[2] = { 688, 689 };

ObjectLink g_objectCreatorLinks[1] = { { 0x2, 0x2B3, 0x560 } };

PadPattern g_padPatterns[11] = {
    { 1, { { { 0x1, 0x0 }, { 0, 0 }, 0.05f } } },
    { 2, { { { 0x0, 0x96 }, { 0, 0 }, 0.05f }, { { 0x0, 0x0 }, { 0, 0 }, 0.05f } } },
    { 2, { { { 0x0, 0xD2 }, { 0, 0 }, 0.05f }, { { 0x0, 0x0 }, { 0, 0 }, 0.1f } } },
    { 2, { { { 0x0, 0xFF }, { 0, 0 }, 0.1f }, { { 0x0, 0x0 }, { 0, 0 }, 0.1f } } },
    { 7, { { { 0x0, 0xD2 }, { 0, 0 }, 0.1f }, { { 0x0, 0xBE }, { 0, 0 }, 0.01f }, { { 0x0, 0xAA }, { 0, 0 }, 0.01f }, { { 0x0, 0x96 }, { 0, 0 }, 0.01f }, { { 0x0, 0x82 }, { 0, 0 }, 0.01f }, { { 0x0, 0x6E }, { 0, 0 }, 0.01f }, { { 0x0, 0x0 }, { 0, 0 }, 0.25f } } },
    { 2, { { { 0x1, 0xFF }, { 0, 0 }, 0.1f }, { { 0x1, 0x0 }, { 0, 0 }, 0.05f } } },
    { 2, { { { 0x0, 0xAA }, { 0, 0 }, 0.05f }, { { 0x0, 0x0 }, { 0, 0 }, 0.1f } } },
    { 2, { { { 0x0, 0xAA }, { 0, 0 }, 0.05f }, { { 0x0, 0x0 }, { 0, 0 }, 0.1f } } },
    { 2, { { { 0x0, 0xAA }, { 0, 0 }, 0.05f }, { { 0x0, 0x0 }, { 0, 0 }, 0.1f } } },
    { 3, { { { 0x0, 0xA0 }, { 0, 0 }, 0.15f }, { { 0x0, 0x0 }, { 0, 0 }, 0.1f }, { { 0x0, 0x5A }, { 0, 0 }, 0.05f } } },
    { 5, { { { 0x0, 0xFF }, { 0, 0 }, 0.2f }, { { 0x0, 0x0 }, { 0, 0 }, 0.08f }, { { 0x0, 0xC8 }, { 0, 0 }, 0.13f }, { { 0x0, 0x0 }, { 0, 0 }, 0.06f }, { { 0x0, 0x96 }, { 0, 0 }, 0.11f } } }
};

s32 g_padPatternSetting = 0;
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);


void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void BuildBasisFromX(void* x, void* out);

void BuildBasisFromX(void* x, void* out);

f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);
void BuildBasisFromX(void* x, void* out);
extern const Vec02 g_unitZVector;

void InitWalkerCollider(WalkerCollider* self)
{
    WalkerCollider* o = self;
    InitSwitchedCollider(self);
    o->f610 = -1;
    o->f628 = 2000.0f;
    o->f614 = -1;
}

void LoadWalkerCollider(WalkerCollider* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 2, (void*)D_0026B778);
}

void StartWalkerCollider(WalkerCollider* self)
{
    StartPlacedObject(self);
    if (self->f678 != 0) {
        ResolveObjectLinks(self, 6, (void*)D_0026B790);
        SetColliderAnchors(self, 0, 0, 3, 0);
        if (self->f640 != 0) {
            self->f644 = CreateStateWalker(self->f640, self, -1, 0);
        }
        if (self->f650 != 0) {
            self->f654 = CreateStateWalker(self->f650, self, -1, 1);
        }
        self->f668 = GatherObjectsById(g_currentWorld, 1, 0x50, self->f664, 3, self->f66C);
        SetWalkerColliderState(self, 2);
        SetWalkerColliderSubState(self, 0);
    } else {
        self->desc->m03(self);
    }
}

extern const f32 D_0024C9C0[4] = { 30.0f, 0.0f, 0.2f, 0.0f };

void ControlWalkerCollider(WalkerCollider* self, PadRecord* src)
{
    HeadingFrame f;
    if (self->f688 != 0) {
        StopAnimationPlayer(((AnimationPlayer*)self->f684));
        self->f684 = 0;
        self->f688 = 0;
    }
    ReadWalkerColliderInput(self, src);
    ComputePolarOffset(&self->v630, self->f618, self->f61C * self->f628, 0.0f);
    f.ramp = *(RampParams*)D_0024C9C0;
    f32 r = ArctangentOfRatio(((PlacedObject*)self->f64C)->m110.r[0].y, ((PlacedObject*)self->f64C)->m110.r[0].x);
    r = ApproachAngleWithRamp((u8*)&f.ramp, 0, r, self->f620, g_frameDt);
    BuildYawPitchMatrix(r, 0.0f, (f32*)&f.rot);
    TransformRotationBetweenFrames(0, self, &f.rot, &f.rot);
    ((PlacedObject*)self->f64C)->desc02()->m1E(((PlacedObject*)self->f64C), &f.rot);
}

f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, RampProfile* p, f32* out);
void UpdateSwitchedCollider(void* self);
s32 ChooseWalkerColliderState(WalkerCollider* self);
s32 ChooseWalkerColliderSubState(WalkerCollider* self);

// Vu0::NormalizeOr that also gives the length it found.
static inline u128 NormalizeOrLength(u128 v, u128 fallback, f32& length)
{
    u128 len = Vu0::Length(v);
    length = Vu0::ToFloat(len);
    if (length < 0.0001f) {
        return fallback;
    }
    return Vu0::DivX(v, len);
}

void UpdateWalkerCollider(WalkerCollider* self)
{
    UpdateSwitchedCollider(self);
    if (HasAnimationDrivenAttachment(self) != 0) {
        Vec02 pos;
        Vec02 vel;
        Vec02 diff;
        Vec02 dir;
        Vec02 split;
        RampProfile ramp;
        f32 out;
        self->f1EC->vt->getPos(self->f1EC, 0.0f, &pos, &vel);
        if (self->f610 == 3) {
            u128 d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos));
            Vu0::Q(diff) = d;
            Vu0::Q(dir) = d;
            f32 l;
            Vu0::Set(dir, NormalizeOrLength(d, Vu0::Q(g_unitXVector), l));
            f32 along = SplitVectorAlongAxis(&vel, &dir, 0, &split);
            f32* lim = (f32*)self->p21C;
            ramp.maxSpeed = lim[0] + along;
            ramp.endSpeed = lim[1] + along;
            ramp.rampTime = lim[2];
            f32 res = ApproachValueWithRamp(0.0f, l, g_frameDt, &ramp, &out);
            u128 w = Vu0::Scalar(res);
            Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(dir), w);
            Vu0::Q(vel) = Vu0::MulAddX(Vu0::Q(split), Vu0::Q(dir), Vu0::ScalarAt(out));
        }
        self->desc02()->m1D(self, &pos);
        self->desc02()->m20(self, &vel);
        self->f618 = ArctangentOfRatio(vel.y, vel.x);
    }
    s32 v;
    while ((v = ChooseWalkerColliderState(self)) != self->f610) {
        SetWalkerColliderState(self, v);
    }
    s32 w;
    while ((w = ChooseWalkerColliderSubState(self)) != self->f614) {
        SetWalkerColliderSubState(self, w);
    }
    ClearRootTries(self);
}

void ReadWalkerColliderInput(WalkerCollider* out, PadRecord* src)
{
    if (0.3f < src->f48) {
        ComputeCameraRelativeStickHeading(g_camera, src, 0, &out->f618);
    }
    out->f61C = src->f48;
    if (0.8f < src->f7C) {
        ComputeCameraRelativeStickHeading(g_camera, src, 1, &out->f620);
    }
    out->f624 = src->f7C;
}

s32 ChooseWalkerColliderState(WalkerCollider* self)
{
    s32 r = self->f610;
    switch (r) {
    case 0:
        if (0.0f < self->f61C) {
            r = 1;
        }
        break;
    case 1:
        if (self->f61C == 0.0f) {
            r = 0;
        }
        break;
    case 2:
        if (self->f684 == 0) {
            r = 1;
        }
        break;
    }
    return r;
}

void SetWalkerColliderState(WalkerCollider* self, s32 n)
{
    s32 old = self->f610;
    if (old == n) return;
    void* h = 0;
    self->f610 = n;
    s32 snd = -1;
    s32 flag = 0;
    s32 kind = 0x14D;
    switch (n) {
    case 0:
        snd = 0x28F;
        flag = 1;
        kind = -1;
        break;
    case 1:
        snd = 0x290;
        break;
    case 2:
        snd = 0x290;
        h = self->f680;
        break;
    case 3:
        snd = 0x290;
        h = self->f67C;
        BeginLevelExit(0, 1);
        break;
    }
    for (s32 i = 0; i < self->f668; i++) {
        if (flag) SetEffectSpawnerActiveForever(((void**)self->f66C)[i]);
        else SetEffectSpawnerInactive(((void**)self->f66C)[i]);
    }
    if (self->f644) {
        if (old == -1) TeleportStateWalker(self->f644, snd);
        else SetStateWalkerTarget(self->f644, snd);
    }
    if (h) {
        CreateAnimationPlayerWithoutPresetTargets(h, self, 1, (s32*)&self->f684, 0.0f, 1.0f);
    }
    if (self->f648) {
        if (kind == *self->f648) return;
        StopSoundRecord(self->f648, 0);
        self->f648 = 0;
    }
    if (kind != -1) {
        StartSoundEffect(kind, (void*)&self->f648, (void*)self, 0, 10000.0f, 6000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    }
}

s32 ChooseWalkerColliderSubState(WalkerCollider* self)
{
    s32 r = self->f614;
    switch (r) {
    case 0:
        if (0.8f <= self->f624) {
            r = 1;
        }
        break;
    case 1:
        if (self->f624 < 0.8f) {
            r = 0;
        }
        break;
    }
    return r;
}

void SetWalkerColliderSubState(WalkerCollider* self, s32 state)
{
    s32 old = self->f614;
    if (old == state) {
        return;
    }
    self->f614 = state;
    s32 a2;
    s32 s1;
    switch (state) {
    case 0:
        a2 = 0x293;
        s1 = -1;
        break;
    case 1:
        a2 = 0x294;
        s1 = 0x150;
        break;
    }
    if (self->f654 != 0) {
        if (old == -1) {
            TeleportStateWalker(self->f654, a2);
        } else {
            SetStateWalkerTarget(self->f654, a2);
        }
    }
    s32 cur = -1;
    if (self->f658 != 0) {
        cur = *(s32*)self->f658;
        if (s1 == cur) {
            return;
        }
        StopSoundRecord(self->f658, 0);
        self->f658 = 0;
        cur = -1;
    }
    if (s1 == cur) {
        return;
    }
    f32 zero = 0.0f;
    StartSoundEffect(s1, &self->f658, self, 0, 10000.0f, 6000.0f, 1.0f, zero, zero, 0, 0);
}

void HandleWalkerColliderNotification(WalkerCollider* self, s32 code, MessageBody* rec)
{
    HandleSwitchedColliderNotification(self, code, rec);
    if (code == 5) {
        goto code5;
    }
    if (code != 0x13) {
        return;
    }
    if (rec->code == 0x295) {
        goto kind295;
    }
    if (rec->code == 0x296) {
        goto kind296;
    }
    return;
kind295:
    StartSoundEffect(0x152, 0, 0, (s32)((u8*)self + 0x140), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    SetEffectSpawnerInactive(self->f65C);
    return;
kind296:
    StartSoundEffect(0x152, 0, 0, (s32)((u8*)self + 0x140), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    SetEffectSpawnerInactive(self->f660);
    return;
code5:
    if (rec == self->f684) {
        self->f688 = 1;
    }
}

void StepWalkerCollider(WalkerCollider* self)
{
    f32 buf[12];
    StepCollider(self);
    BuildYawPitchMatrix(self->f618, 0.0f, buf);
    TurnColliderTowardRotation(self, buf, D_0026B7D8, g_frameDt);
}

s32 HasAnimationDrivenAttachment(void* ctx);

// What func_001A4538 moves: a walker's point (+0x630), and a contact record's normal (+0x80)
// with its entries of 0x40 bytes, each with a point at +0x30.
struct Walker_001A4538 {
    u8 pad0[0x630];
    Vec02 point;            // 0x630
};

struct ContactEntry_001A4538 {
    u8 pad0[0x30];
    Vec02 point;            // 0x30
};

union Contact_001A4538 {
    ContactEntry_001A4538 entries[1];   // 0x00
    struct {
        u8 pad0[0x80];
        Vec02 normal;       // 0x80
    };
};

void ResolveWalkerColliderContact(Walker_001A4538* self, Contact_001A4538* c, s32 i)
{
    if (HasAnimationDrivenAttachment(self) == 0) {
        Vec02* p = &c->entries[i].point;
        Vec02 d;
        Vu0::Vec e = Vu0::Vec::Of(*p);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->point),
                             Vu0::MulX(Vu0::Q(c->normal), Vu0::Dot(Vu0::Q(self->point), Vu0::Q(c->normal))));
        Vu0::Q(*p) = Vu0::Sub(e.q, Vu0::Q(d));
    }
}

void ComputeWalkerColliderContactValue(WalkerCollider* ctx, Contact03* obj)
{
    if (HasAnimationDrivenAttachment(ctx) != 0) {
        return;
    }
    if (0.7f < obj->v80.z) {
        obj->f94 = 20.0f;
    }
}

void ComputeWalkerColliderImpulseResponse(WalkerCollider* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    Vec02 s0;
    Vec02 s1;
    s32 n = *(s32*)(a2 + ((1 - a3) << 6));
    s0 = self->v440;
    s1 = self->q450;
    if (n != 0) {
        if (IsObjectOfKind((void*)n, 0x43) || IsObjectOfKind((void*)n, 0x42)) {
            self->mode450 = 1;
            self->v440 = g_unitZVector;
        }
    }
    ComputeColliderImpulseResponse(self, a1, a2, a3, a4, a5);
    self->v440 = s0;
    self->q450 = s1;
}

s32 IsWalkerColliderCameraFree(void)
{
    return 0;
}

extern const PairPose g_pairControllerPoseTable = { {
    { 2.0f, 5.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 8.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 1.0f, 2.5f, 0.10000000149011612f, 0.30000001192092896f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 1.5f, 3.0f, 0.15000000596046448f, 0.4000000059604645f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 400.0f, 1500.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 3.0f, 6.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f }
} };

void InitPairController(PairController* self)
{
    PairPose tmp;

    InitPlacedObject(self);
    SetListLinkOffset(self->list35C, 0x5A0);
    SetListLinkOffset(self->list368, 0x5A0);
    SetListLinkOffset(self->list374, 0x5A0);
    SetListLinkOffset(self->list384, 0x5B0);
    SetListLinkOffset(self->list390, 0x5B0);
    SetListLinkOffset(self->list3A0, 0x568);
    SetListLinkOffset(self->list3AC, 0x568);
    self->id2D0 = -1;
    self->id2D4 = -1;
    self->id2D8 = -1;
    self->id2DC = -1;
    self->id64C = -1;
    self->state = -1;
    self->limit3B8 = 0x28;
    tmp = g_pairControllerPoseTable;
    CopyMemory(self->poseA, &tmp, 0xC0);
    CopyMemory(self->poseB, &tmp, 0xC0);
    self->q3D0 = *(AlignedQuad*)&D_00275C50;
    f32 k2300 = 2300.0f;
    f32 k1500 = 1500.0f;
    f32 k146 = 1.46f;
    f32 k3000 = 3000.0f;
    self->tune350 = k3000;
    self->tune348 = k2300;
    self->tune344 = k1500;
    self->tune34C = k146;
    self->mode340 = 0;
}

void SetPairControllerFirstTemplateId(PairController* obj, s32 value)
{
    obj->id2D0 = value;
}

void SetPairControllerSecondTemplateId(PairController* obj, s32 value)
{
    obj->id2D4 = value;
}

void SetPairControllerHostId(u8* self, s32 value)
{
    *(s32*)(self + 0x2D8) = value;
}

void SetPairControllerExtraId(PairController* obj, s32 value)
{
    obj->id2DC = value;
}

void AppendPairControllerId(PairController* list, s32 value)
{
    s32 n = list->idCount;
    list->ids[n] = value;
    list->idCount = n + 1;
}

s32 GetCurrentEntryVariant(void)
{
    s32 flags = g_currentEntry->flags;
    if ((flags & 4) == 0) {
        s32 bit = flags & 2;
        return bit != 0;
    }
    return 2;
}

// The larger of two floats (max.s; through an inline function, b >? a reads a first and gives
// the result b's register, as retail's pose counts are).
static inline f32 MaxF(f32 a, f32 b) { return b >? a; }

struct Controlled558 {
    u8 pad[0x558];
    void* controller;
};

struct Controlled678 {
    u8 pad[0x678];
    void* controller;
};

void PostLoadPlacedObject(void* self);
void* FindFirstObjectByIdMode4(World* w, s32 id, void* self);
s32 GatherObjectsByMode(World* w, s32 a, s32 id, void* self, s32 mode, void** out);
void* CreateObjectCopy(void* obj, World* w, s32 n);

void ResolvePairControllerLinks(PairController* self)
{
    PostLoadPlacedObject(self);
    if (self->id64C == GetCurrentEntryVariant()) {
        u8* s = (u8*)self;
        void* first = FindFirstObjectByIdMode4(g_currentWorld, self->id2D8, self);
        self->f354 = first;
        ((Controlled678*)first)->controller = self;
        PairedObject* a = (PairedObject*)FindFirstObjectByIdMode4(g_currentWorld, self->id2D0, self);
        a->controller = self;
        PairedObject* b = (PairedObject*)FindFirstObjectByIdMode4(g_currentWorld, self->id2D4, self);
        b->controller = self;
        if (self->id2DC != -1) {
            self->target = (ObjectCreator*)FindFirstObjectByIdMode4(g_currentWorld, self->id2DC, self);
            ((HitTarget*)self->target)->controller = self;
        }
        s32 i;
        for (i = 0; (f32)i < MaxF(self->poseA[1], self->poseB[1]); i++) {
            void* o;
            if (i == 0) {
                o = a;
            } else {
                o = CreateObjectCopy(a, g_currentWorld, *(s32*)((u8*)a + 0x18));
            }
            AppendToList(s + 0x374, o);
        }
        for (i = 0; (f32)i < MaxF(self->poseA[9], self->poseB[9]); i++) {
            void* o;
            if (i == 0) {
                o = b;
            } else {
                o = CreateObjectCopy(b, g_currentWorld, *(s32*)((u8*)b + 0x18));
            }
            AppendToList(s + 0x390, o);
        }
        for (i = 0; i < self->idCount; i++) {
            void* found[4];
            s32 n = GatherObjectsByMode(g_currentWorld, 0x104, self->ids[i], self, 2, found);
            void* hit = 0;
            for (s32 k = 0; k < n; k++) {
                if (IsObjectOfKind(found[k], 0x44) != 0) {
                    hit = found[k];
                    break;
                }
            }
            ((Controlled558*)hit)->controller = self;
            AppendToList(s + 0x3A0, hit);
        }
    }
}

void BlendPairControllerPose(PairController* self)
{
    StartPlacedObject(self);
    if (self->id64C != GetCurrentEntryVariant()) {
        self->desc->m03(self);
    } else {
        BlendMotion* k = &self->kin;
        f32 dt = g_currentEntry->dt;
        f32 v = k->pos + dt * (k->vel + dt * k->acc);
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
        f32* pa = self->poseA;
        f32* pb = self->poseB;
        f32* po = self->poseOut;
        for (u32 i = 0; i < 48; i++) {
            *po++ = u * *pa++ + t * *pb++;
        }
        UpdatePairControllerTuning(self, 0.0f);
        SetPairControllerState(self, 0);
    }
}

void UpdatePairController(PairController* self)
{
    ObjectCreator* t;
    s32 st;
    UpdatePlacedObject(self);
    while ((st = ChoosePairControllerState(self)) != self->state) {
        SetPairControllerState(self, st);
    }
    switch (st) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 6:
        break;
    case 2:
        if (self->count3BC < self->limit3B8) {
            if (self->f634 < g_gameClock[1]) {
                SpawnPairedObject(self);
            }
        }
        if (self->f640 < g_gameClock[1]) {
            StartPairedObjects(self);
        }
        break;
    case 5: {
        t = self->target;
        if (t) {
            if (t->state == 0) {
                LinkedObject* s = self->link;
                if (s == 0 || s->f2D4 != 3) {
                    SetObjectCreatorState(t, 1);
                }
            }
        }
        break;
    }
    }
}

void ShowPairControllerElement(PairController* self)
{
    void* p = 0;
    if (self->state == 2) {
        p = AreMenusAndFadeClear(p);
    }
    if (p != 0) {
        D_0026D0C8.vt->m14(&D_0026D0C8);
    } else {
        D_0026D0C8.vt->m15(&D_0026D0C8);
    }
}

s32 ChoosePairControllerState(PairController* self)
{
    u32 s = self->state;
    switch (s) {
    case 0:
        { u32 one = 1;
        if (((WalkerCollider*)self->f354)->f610 <= one) s = one; }
        break;
    case 1:
        if (!self->link || self->link->f2D4 != 3) s = 2;
        break;
    case 2:
        if (self->f3C0) { s = 3; break; }
        if (self->f3C4 == self->limit3B8) s = 5;
        break;
    case 3:
        if (self->link->f2D4 != 3) s = 4;
        break;
    case 5:
        if (self->target) {
            if (self->target->state == 3 && self->target->stateTime + 3.0f < g_gameClock[1]) s = 6;
        } else if (self->f654 + 5.0f < g_gameClock[1]) {
            if (!self->link || self->link->f2D4 != 3) s = 6;
        }
        break;
    case 4:
    case 6:
        break;
    }
    return s;
}

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))
#define O(o, off) (*(PairController**)((u8*)(o) + (off)))
void SetPairControllerState(PairController* self, s32 state)
{
    PairController* o;
    s32 v;
    ListFrame frame;
    if (W(self, 0x650) == state) return;
    W(self, 0x650) = state;
    F(self, 0x654) = g_gameClock[1];
    W(self, 0x658) = 0;
    switch (state) {
    case 0:
        break;
    case 1: {
        if (W(self, 0x64C) < 3) {
            if (W(self, 0x64C) >= 0) {
                if (g_currentEntry->f14) {
                    W(self, 0x658) = 0;
                } else {
                    W(self, 0x658) = FindFirstObjectById(self->world, 0x105, 0x33B, 0);
                }
            }
        }
        s32 w = W(self, 0x658);
        if (w) {
            T217D_440* box = &g_typedTextCaptionBox;
            ((U32P*)&box->child)->v = w;
            PushStackElement(g_elementStack, (u8*)box);
        }
        break;
    }
    case 2: {
        D_0026D0C8.target = &self->f3C4;
        D_0026D0C8.limit = &self->limit3B8;
        SetWorldActiveFollower(self->world, self);
        break;
    }
    case 5:
        v = FindFirstObjectById(self->world, 0x105, 0x33D, 0);
        W(self, 0x658) = v;
        if (v) {
            g_typedTextCaptionBox.child = (void*)v;
            PushStackElement(g_elementStack, (u8*)&g_typedTextCaptionBox);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) SetPairedState(o, 8);
        ResetScatterLevels(g_scatterController);
        break;
    case 3:
        v = FindFirstObjectById(self->world, 0x105, 0x33E, 0);
        W(self, 0x658) = v;
        if (v) {
            g_typedTextCaptionBox.child = (void*)v;
            PushStackElement(g_elementStack, (u8*)&g_typedTextCaptionBox);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) {
            BaseObject* l = (BaseObject*)P(o, 0x55C);
            if (l == 0 || l->parent != o) SetPairedState(o, 7);
        }
        RaiseScatterLevels(g_scatterController, 1.0f);
        break;
    case 4:
        SetPauseMenuLayerPage((u8*)&g_pauseMenuElement, 0, 0x1A);
        break;
    case 6:
        SetWalkerColliderState(P(self, 0x354), 3);
        g_buttonHintElement.vt->m15(&g_buttonHintElement);
        break;
    }
}
#undef F
#undef W
#undef P
#undef O

INCLUDE_RODATA(D_0024CAEC);

extern const f32 D_0024CAEC;
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void* GetActiveSwitchedCollider(void);
extern const Vec02 g_unitZVector;

// Whether the spot is within reach of n: the xy distance to its position is less than the two radii.
static inline s32 IsNearSpot(const Vec02& pos, PairedObject* n, PairedObject* o)
{
    s32 near = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vu0::Q(pos), Vu0::Q(n->v140)), Vu0::Sub(Vu0::Q(pos), Vu0::Q(n->v140))))) < o->radius3D0 + n->radius3D0;
    return near;
}

static inline s32 IsNearSpotOf(const Vec02& pos, PairedObject* n, PairedObject* o)
{
    s32 near = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vu0::Q(pos), Vu0::Q(n->v140)), Vu0::Sub(Vu0::Q(pos), Vu0::Q(n->v140))))) < n->radius3D0 + o->radius3D0;
    return near;
}

void SpawnPairedObject(PairController* self)
{
    Vec02 pos;
    Vec02 spare;
    Mat02 turn;
    PairedObject* o;
    PairedObject* n;
    PairedObject* m;
    PairedObject* other;
    s32 i;

    if (self->count380 >= self->limit624) {
        self->f634 = D_0024CAEC;
        return;
    }
    o = *(PairedObject**)self->list374;
    for (i = 0; i < 8; i++) {
        f32 angle = RandomFloatInRange(0.0f, 6.2831855f);
        f32 radius = RandomFloatInRange(*(f32*)((u8*)self + 0x340) + o->radius3D0, *(f32*)((u8*)self + 0x344));
        other = (PairedObject*)GetActiveSwitchedCollider();
        ComputePolarOffset((void*)&pos, angle, radius, 0.0f);
        pos.y = pos.y * self->tune34C;
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(*(Vec02*)((u8*)self + 0x330)), Vu0::Q(pos));
        if (other != 0 && IsNearSpot(pos, other, o)) {
            continue;
        }
        for (n = *(PairedObject**)self->list384; n != 0; n = *(PairedObject**)((u8*)n + 0x5B0)) {
            if (IsNearSpotOf(pos, n, o)) {
                break;
            }
        }
        if (n != 0) {
            continue;
        }
        for (m = *(PairedObject**)self->list35C; m != 0; m = *(PairedObject**)((u8*)m + 0x5A0)) {
            if (m->parent == 0 && IsNearSpot(pos, m, o)) {
                break;
            }
        }
        if (m != 0) {
            continue;
        }
        for (m = *(PairedObject**)self->list368; m != 0; m = *(PairedObject**)((u8*)m + 0x5A0)) {
            if (m != o && IsNearSpot(pos, m, o)) {
                break;
            }
        }
        if (m == 0) {
            break;
        }
    }
    if (i < 8) {
        self->count3BC++;
        self->count380++;
        o->desc->m02(o);
        pos.z = self->tune350;
        o->desc02()->m1D(o, &pos);
        f32 spin = RandomFloatInRange(0.0f, 6.2831855f);
        BuildAxisAngleMatrix(&g_unitZVector, &turn, spin);
        o->desc02()->m1E(o, &turn);
        o->desc02()->m20(o, (Vec02*)&D_00248D30);
        o->desc02()->m21(o, (Vec02*)&D_00248D30);
        SetColliderAnchors(o, 2, (s32)&g_unitZVector, 3, 0);
        SetHitTargetState(o, 0);
        RemoveFromList(self->list374, o);
        AppendToList(self->list368, o);
        PairWithNearestWaitingObject(self, o);
        self->f634 = g_gameTime + RandomFloatInRange(self->f62C, self->f630);
    }
}

void StartPairedObjects(PairController* self)
{
    if (self->count39C >= self->f628) {
        self->f640 = 3.4028234663852886e+38f;
    } else {
        PairedObject* owner = *(PairedObject**)(self->list390);
        s32 count = CountListItems((List01*)self->list3A0);
        if (count != 0) {
            ListWalk w((List01*)self->list3A0);
            u8* node;
            s32 r = RandomIntInRange(0, count - 1);
            s32 j = r;
            j--;
            if (r >= 0) {
                do {
                    node = (u8*)w.Next();
                } while (j-- >= 0);
            }
            RemoveFromList(self->list3A0, node);
            AppendToList(self->list3AC, node);
            RemoveFromList(self->list390, owner);
            AppendToList(self->list384, owner);
            owner->attachment = node;
            (self->count39C)++;
            owner->desc->m02(owner);
            owner->desc02()->m1D(owner, (Vec02*)(node + 0x140));
            owner->desc02()->m1E(owner, (Mat02*)(node + 0x110));
            SetPairedState(owner, 1);
            SetSoundStateObjectState(*(void**)((u8*)owner + 0x560), 1);
            *(f32*)((u8*)owner + 0x564) = self->f644;
            *(f32*)((u8*)owner + 0x568) = self->f648;
            f32* fp = &self->f638;
            self->f640 = g_gameClock[1] + RandomFloatInRange(self->f638, fp[1]);
            StartSoundEffect(-1, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            StartSoundEffect(0x14E, 0, (s32)node, 0, 12000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
}

#define F(o) (*(f32*)((u8*)self + (o)))
#define I(o) (*(s32*)((u8*)self + (o)))
#define P(o) ((const QuadraticCoeffs*)((u8*)self + (o)))
void UpdatePairControllerTuning(PairController* self, f32 dt)
{
    f32 t0;
    ClampedQuadratic::Get(t0, P(0x5B0), dt);
    F(0x62C) = (1.0f - t0) * F(0x5A0) + t0 * F(0x5A8);
    F(0x630) = (1.0f - t0) * F(0x5A4) + t0 * F(0x5AC);

    f32 t1;
    ClampedQuadratic::Get(t1, P(0x5D0), dt);
    F(0x638) = (1.0f - t1) * F(0x5C0) + t1 * F(0x5C8);
    F(0x63C) = (1.0f - t1) * F(0x5C4) + t1 * F(0x5CC);

    f32 t2;
    ClampedQuadratic::Get(t2, P(0x5F0), dt);
    F(0x644) = (1.0f - t2) * F(0x5E0) + t2 * F(0x5E4);

    f32 t3;
    ClampedQuadratic::Get(t3, P(0x610), dt);
    F(0x648) = (1.0f - t3) * F(0x600) + t3 * F(0x604);

    f32 t4;
    ClampedQuadratic::Get(t4, P(0x570), dt);
    s32 n = (s32)((1.0f - t4) * F(0x560) + t4 * F(0x564));
    if (I(0x624) < n && I(0x380) == I(0x624)) {
        F(0x634) = g_gameClock[1] + RandomFloatInRange(F(0x62C), F(0x630));
    }
    I(0x624) = n;

    f32 t5;
    ClampedQuadratic::Get(t5, P(0x590), dt);
    n = (s32)((1.0f - t5) * F(0x580) + t5 * F(0x584));
    if (I(0x628) < n && I(0x39C) == I(0x628)) {
        F(0x640) = g_gameClock[1] + RandomFloatInRange(F(0x638), F(0x63C));
    }
    I(0x628) = n;
}
#undef F
#undef I
#undef P

void RemoveFinishedHitTarget(PairController* self, HitTarget* obj)
{
    s32 n = self->f3C4 + 1;
    f32 x = (f32)self->limit3B8;
    self->f3C4 = n;
    UpdatePairControllerTuning(self, (f32)n / x);
    if (obj->partner != 0) {
        RemoveFromList(self->list35C, obj);
    } else {
        RemoveFromList(self->list368, obj);
    }
    AppendToList(self->list374, obj);
    if (obj->partner != 0) {
        if (PairWithNearestFreeObject(self, obj->partner) != 0) {
            SetPairedState(obj->partner, 3);
        } else {
            ((HitTarget*)obj->partner)->partner = 0;
            SetPairedState(obj->partner, 2);
        }
    }
    obj->partner = 0;
    obj->desc->m03(obj);
    if (self->count380 == self->limit624) {
        f32 t = RandomFloatInRange(self->f62C, self->f630);
        self->f634 = g_gameClock[1] + t;
    }
    self->count380 = self->count380 - 1;
}

void ReleasePairedAttachment(u8* self, PairedObject* obj)
{
    RemoveFromList(self + 0x3AC, obj->attachment);
    AppendToList(self + 0x3A0, obj->attachment);
    SetSoundStateObjectState(obj->attachment, 0);
    obj->attachment = 0;
}

void AttachPairedPartner(void* a0, void* a1)
{
    PairedObject* s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc->m15((Collider*)s->partner, (BaseObject*)a1);
    s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc02()->m20((Collider*)s->partner, (Vec02*)&D_00248D30);
    s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc02()->m21((Collider*)s->partner, (Vec02*)&D_00248D30);
    SetColliderAnchors((Collider*)((PairedObject*)a1)->partner, 3, 0, 3, 0);
    StartSoundEffect(0x151, (void*)0, 0, (void*)0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

void DetachPairedPartner(PairController* unused, PairedObject* h)
{
    Collider* o = (Collider*)h->partner;

    (void)unused;
    o->desc->m15(o, 0);
    o->desc02()->m20(o, (Vec02*)&D_00248D30);
    o->desc02()->m21(o, (Vec02*)&D_00248D30);
    SetColliderAnchors(o, 2, (void*)&g_unitZVector, 3, 0);
}

void ActivatePairedAttachment(void* unused, PairedObject* obj)
{
    SetSoundStateObjectState(obj->attachment, 1);
}

void FinishPairedObjectTransition(PairController* self, PairedObject* obj)
{
    self->f3C0 = self->f3C0 + 1;
    RemoveFromList(self->list35C, obj->partner);
    AppendToList(self->list374, obj->partner);
    RemoveFromList(self->list384, obj);
    AppendToList(self->list390, obj);
    RemoveFromList(self->list3AC, obj->attachment);
    AppendToList(self->list3A0, obj->attachment);
    {
        PairedObject* p = (PairedObject*)obj->partner;
        p->desc->m15(p, 0);
    }
    {
        PairedObject* q = (PairedObject*)obj->partner;
        q->desc->m03(q);
    }
    obj->desc->m03(obj);
    SetSoundStateObjectState(obj->attachment, 0);
    obj->attachment = 0;
    ((PairedObject*)obj->partner)->partner = 0;
    obj->partner = 0;
    if (self->count380 == self->limit624) {
        f32 t = RandomFloatInRange(self->f62C, self->f630);
        self->f634 = g_gameClock[1] + t;
    }
    self->count380 = self->count380 - 1;
    if (self->count39C == self->f628) {
        f32 t2 = RandomFloatInRange(self->f638, self->f63C);
        self->f640 = g_gameClock[1] + t2;
    }
    self->count39C = self->count39C - 1;
    StartSoundEffect(0x51, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

void RemovePairedObject(PairController* self, PairedObject* obj)
{
    RemoveFromList(self->list384, obj);
    AppendToList(self->list390, obj);
    if (obj->attachment != 0) {
        RemoveFromList(self->list3AC, obj->attachment);
        AppendToList(self->list3A0, obj->attachment);
        SetSoundStateObjectState(obj->attachment, 0);
    }
    PairedObject* child = (PairedObject*)obj->partner;
    if (child != 0) {
        if (child->parent == obj) {
            DetachPairedPartner(self, obj);
        }
        RemoveFromList(self->list35C, child);
        AppendToList(self->list368, child);
        if (PairWithNearestWaitingObject(self, child) == 0) {
            child->partner = 0;
        }
    }
    obj->attachment = 0;
    obj->partner = 0;
    obj->desc->m03(obj);
    if (self->count39C == self->f628) {
        f32 r = RandomFloatInRange(self->f638, self->f63C);
        self->f640 = g_gameClock[1] + r;
    }
    self->count39C = self->count39C - 1;
}

s32 PairWithNearestFreeObject(void* self, void* child)
{
    ListFrame frame;
    PairController* c = (PairController*)self;
    PairedObject* o = (PairedObject*)child;
    if (IsListEmpty((List01*)c->list368) != 0) {
        return 0;
    }
    f32 best = 3.4028234663852886e+38f;
    PairedObject* found;
    for (PairedObject* p = *(PairedObject**)c->list368; p != 0; p = *(PairedObject**)((u8*)p + 0x5A0)) {
        u128 d = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(o->v140));
        f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (dist < best) {
            best = dist;
            found = p;
        }
    }
    o->partner = found;
    found->partner = o;
    RemoveFromList(c->list368, found);
    AppendToList(c->list35C, found);
    return 1;
}

void LinkPairedObjects(u8* self, PairedObject* obj, PairedObject* node)
{
    PairedObject* cur = (PairedObject*)obj->partner;
    if (cur != 0 && cur == node) {
        return;
    }
    PairedObject* s2 = (PairedObject*)node->partner;
    obj->partner = node;
    node->partner = obj;
    if (s2 == 0) {
        RemoveFromList(self + 0x368, node);
        AppendToList(self + 0x35C, node);
    }
    if (cur != 0) {
        RemoveFromList(self + 0x35C, cur);
        AppendToList(self + 0x368, cur);
        cur->partner = 0;
        PairWithNearestWaitingObject(self, cur);
    }
    if (s2 != 0) {
        s2->partner = 0;
        SetPairedState(s2, 2);
        if (PairWithNearestFreeObject(self, s2) != 0) {
            SetPairedState(s2, 3);
        }
    }
}

s32 PairWithNearestWaitingObject(void* self, void* child)
{
    ListFrame frame;
    PairController* c = (PairController*)self;
    PairedObject* o = (PairedObject*)child;
    f32 best = 3.4028234663852886e+38f;
    PairedObject* found = 0;
    for (PairedObject* p = *(PairedObject**)c->list384; p != 0; p = *(PairedObject**)((u8*)p + 0x5B0)) {
        if (p->partner == 0 && p->state == 2) {
            u128 d = Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(p->v140));
            f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
            if (dist < best) {
                best = dist;
                found = p;
            }
        }
    }
    if (found == 0) {
        return 0;
    }
    o->partner = found;
    found->partner = o;
    RemoveFromList(c->list368, o);
    AppendToList(c->list35C, o);
    SetPairedState(found, 3);
    return 1;
}

s32 AssignNearestListedObjectToPair(PairController* self, PairedObject* obj)
{
    ListFrame frame;
    if (IsListEmpty((List01*)self->list3A0) != 0) {
        return 0;
    }
    f32 best = 3.4028234663852886e+38f;
    PlacedObject* found = 0;
    for (PlacedObject* p = *(PlacedObject**)self->list3A0; p != 0; p = *(PlacedObject**)((u8*)p + 0x568)) {
        u128 d = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(obj->v140));
        f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (dist < best) {
            best = dist;
            found = p;
        }
    }
    RemoveFromList(self->list3A0, found);
    AppendToList(self->list3AC, found);
    obj->attachment = found;
    return 1;
}

void RandomizePairedObjectOffset(PairController* self, PairedObject* b)
{
    f32 r0 = RandomFloatInRange(0.0f, 6.2831855f);
    f32 r1 = RandomFloatInRange(0.0f, self->tune348);
    ComputePolarOffset((u8*)b + 0x570, r0, r1, 0.0f);
    b->f574 = b->f574 * self->tune34C;
}

void* GetPairControllerPose(void* self)
{
    PairController* obj = (PairController*)self;
    return (u8*)self + (obj->poseIndex * 0xC0 + 0x3E0);
}

void InitPairedObject(PairedObject* self)
{
    InitCollider(self);
    self->state = -1;
    self->f584 = 1.0f;
    self->f588 = 2.5f;
    SetColliderAnchors(self, 1, (void*)&g_unitZVector, 2, (void*)&g_unitZVector);
}

void LoadPairedObject(PairedObject* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 6, g_pairedObjectLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

void CopyPairedObject(PairedObject* self)
{
    Bytes8 tmp = *(Bytes8*)&self->blob5B0;
    CopyCollider(self);
    *(Bytes8*)&self->blob5B0 = tmp;
}

void StartPairedObject(PairedObject* self)
{
    StartPlacedObject(self);
    SetPairedState(self, 0);
    self->desc->m03(self);
}

s32 ChoosePairedObjectState(PairedObject* self);
void SteerPairedObjectWithinArea(PairedObject* self, Vec02* goal, s32 flag);
void ConvertPositionToWorld(void* frame, Vec02* out);

// The distance from b to a on the ground (their x and y).
static inline f32 GroundDistance(u128 a, u128 b)
{
    u128 d = Vu0::Sub(a, b);
    return Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
}

// Each frame: the state the object should be in, then where it steers in it.
void UpdatePairedObject(PairedObject* self)
{
    Vec02 v;
    UpdateCollider(self);
    s32 s;
    for (;;) {
        s = ChoosePairedObjectState(self);
        if (s == self->state) {
            break;
        }
        SetPairedState(self, s);
    }
    switch (s) {
    case 1:
        ConvertPositionToWorld(*(void**)((u8*)self->attachment + 0x564), &v);
        SteerPairedObjectWithinArea(self, &v, 0);
        break;
    case 2: {
        if (self->f580 < g_gameClock[1] || GroundDistance(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)((u8*)self + 0x570))) < 50.0f) {
            RandomizePairedObjectOffset((PairController*)self->controller, self);
            self->f580 = g_gameClock[1] + RandomFloatInRange(self->f584, self->f588);
        }
        SteerPairedObjectWithinArea(self, (Vec02*)((u8*)self + 0x570), 0);
        break;
    }
    case 3:
        SteerPairedObjectWithinArea(self, &((PlacedObject*)self->partner)->v140, 0);
        break;
    case 5:
        ConvertPositionToWorld(*(void**)((u8*)self->attachment + 0x564), &v);
        SteerPairedObjectWithinArea(self, &v, 1);
        break;
    case 6:
        SteerPairedObjectWithinArea(self, &((PlacedObject*)self->attachment)->v140, 1);
        break;
    case 0:
    case 4:
    case 7:
    case 8:
    case 9:
    case 10:
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
        break;
    }
}

// The ground a paired object keeps to (its controller): a circle around center.
struct PairArea {
    u8 pad000[0x330];
    Vec02 center;           // 0x330
    f32 radius;             // 0x340
};

// v made unit length (no test for zero; func_001A6788).
static inline u128 Normalized(Vec02 v)
{
    return Vu0::DivX(Vu0::Q(v), Vu0::Length(Vu0::Q(v)));
}

// The smaller of two floats (min.s; through an inline function the result takes b's register).
static inline f32 MinF(f32 a, f32 b) { return a <? b; }

s32 CollectBoundsSpans(Vec02* p, Vec02* a, Vec02* b, f32 radius, s32 count, ColliderSpan* out);
f32 WrapAngle(f32 a);
void SetPlacedObjectLocalVelocity(PlacedObject* self, Vec02* v);
void SetPlacedObjectSpinFromFloats(PlacedObject* self, f32 x, f32 y, f32 z);

void SteerPairedObjectWithinArea(PairedObject* self, Vec02* goal, s32 backwards)
{
    Vec02 from;
    Vec02 to;
    Vec02 delta;
    from = self->v140;
    from.z = 0.0f;
    to = *goal;
    to.z = 0.0f;
    PairArea* area = (PairArea*)self->controller;
    if (0.0001f < area->radius) {
        ColliderSpan span;
        if (CollectBoundsSpans(&area->center, &from, &to, area->radius, 1, &span)) {
            Vec02 mid;
            Vec02 dir;
            Vu0::Q(mid) = Vu0::MulXSum(Vu0::Q(span.q[0]), Vu0::Scalar(0.5f), Vu0::Q(span.q[1]), Vu0::Scalar(0.5f));
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(mid), Vu0::Q(((PairArea*)self->controller)->center));
            Vu0::Q(dir) = Normalized(dir);
            Vu0::Q(to) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(((PairArea*)self->controller)->radius * 1.5f));
        }
    }
    Vu0::Q(delta) = Vu0::Sub(Vu0::Q(to), Vu0::Q(from));
    f32 bearing = ArctangentOfRatio(delta.y, delta.x);
    f32 heading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
    if (backwards) {
        heading = WrapAngle(heading + 3.1415927f);
    }
    f32 turn = WrapAngle(bearing - heading);
    if (0.05235988f < __builtin_fabsf(turn)) {
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
    } else {
        f32 speed = MinF(Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(delta))) / g_gameClock[2], self->maxSpeed);
        if (backwards) {
            speed = -speed;
        }
        Vec02 v;
        Vu0::Q(v) = Vu0::FromFloats(speed, 0.0f, 0.0f);
        SetPlacedObjectLocalVelocity(self, &v);
    }
    f32 w = turn / g_gameClock[2];
    f32 lo = -self->maxTurn;
    if (w < lo) {
        w = lo;
    } else if (self->maxTurn < w) {
        w = self->maxTurn;
    }
    SetPlacedObjectSpinFromFloats(self, 0.0f, 0.0f, w);
}

void* FindHitTargetChild(Collider* self);

// The state the paired object should be in: free (1) until it reaches its attachment and a
// free partner takes it (3) or none (2); while paired (2, 3) until a hit target child links
// it (4); then back to an attachment (5) and close in on it (6, then 0); 9 ends in 10.
s32 ChoosePairedObjectState(PairedObject* self)
{
    Vec02 v;
    s32 s = self->state;
    switch (s) {
    case 1: {
        void* h = FindHitTargetChild(self);
        if (h != 0) {
            LinkPairedObjects((u8*)self->controller, self, (PairedObject*)h);
            s = 4;
            break;
        }
        ConvertPositionToWorld(*(void**)((u8*)self->attachment + 0x564), &v);
        if (GroundDistance(Vu0::Q(v), Vu0::Q(self->v140)) < 10.0f) {
            s = 2;
            if (PairWithNearestFreeObject(self->controller, self) != 0) {
                s = 3;
            }
        }
        break;
    }
    case 2:
    case 3: {
        void* h = FindHitTargetChild(self);
        if (h != 0) {
            LinkPairedObjects((u8*)self->controller, self, (PairedObject*)h);
            s = 4;
        }
        break;
    }
    case 4: {
        u8* p = (u8*)self->activeHandle;
        if (p != 0 && *(f32*)(p + 0x14) < *(f32*)((u8*)self->f594 + 0x34)) {
            s = 4;
            break;
        }
        if (AssignNearestListedObjectToPair((PairController*)self->controller, self) != 0) {
            s = 5;
        } else {
            s = 2;
        }
        break;
    }
    case 5:
        ConvertPositionToWorld(*(void**)((u8*)self->attachment + 0x564), &v);
        if (GroundDistance(Vu0::Q(self->v140), Vu0::Q(v)) < 10.0f) {
            s = 6;
        }
        break;
    case 6:
        if (GroundDistance(Vu0::Q(self->v140), Vu0::Q(((PlacedObject*)self->attachment)->v140)) < 10.0f) {
            s = 0;
        }
        break;
    case 0:
    case 7:
    case 8:
    case 10:
        break;
    case 9:
        s = 10;
        break;
    }
    return s;
}

void SetPairedState(PairedObject* self, s32 mode)
{
    TargetBinding buf[2];
    TargetBinding* w;
    void* h;
    void* s3;

    if (self->state == mode) return;
    if (self->activeHandle) {
        StopAnimationPlayer((PairedObject*)self->activeHandle);
        self->activeHandle = 0;
    }
    if (self->soundHandle) {
        DestroyStateWalker((PairedObject*)self->soundHandle);
        self->soundHandle = 0;
    }
    switch (self->state) {
    case 1:
        ReleasePairedAttachment(self->controller, self);
        break;
    case 5:
        if (mode == 6) ActivatePairedAttachment(self->controller, self);
        break;
    case 6:
        if (mode == 0) FinishPairedObjectTransition(self->controller, self);
        break;
    case 9:
        RemovePairedObject(self->controller, self);
        break;
    default:
        break;
    }
    self->state = mode;
    h = 0;
    s3 = 0;
    self->stateTime = g_gameClock[1];
    w = buf;
    switch (mode) {
    case 0: case 10:
        break;
    case 1: case 2: case 3:
        h = self->f58C;
        break;
    case 4:
        AttachPairedPartner(self->controller, self);
        w->key = 0x2A0; w->object = self->partner; w++;
        h = self->f594;
        break;
    case 5: case 6:
        w->key = 0x2A0; w->object = self->partner; w++;
        h = self->f590;
        break;
    case 7:
        s3 = self->f5A0;
        break;
    case 8:
        s3 = self->f5A4;
        break;
    case 9:
        h = self->f598;
        break;
    }
    if (h) CreateAnimationPlayer(0.0f, 1.0f, h, self, w - buf, buf, 1, &self->activeHandle);
    if (s3) self->soundHandle = CreateStateWalker(s3, self, -1, 1);
}

s32 HandlePairedHit(PairedObject* o, ObjectEvent* ev) {
    if (ev->eventFlags & 0x20) {
        switch (o->state) {
        case 1: case 2: case 3: case 4: case 5: case 7: case 8:
            SetPairedState(o, 9);
            break;
        case 6: {
            HitTarget* c = (HitTarget*)o->partner;
            SetPairedState(o, 9);
            if (c) SetHitTargetState(c, 9);
            break;
        }
        }
        if (o->state == 9) {
            HitTarget* t = (HitTarget*)o->notifyRecord;
            if (t) {
                SlotMessage m;
                m.kind = 6;
                m.va = ev->v30;
                m.vb = ev->pos;
                m.va.z += 3000.0f;
                t->desc->m1B(t, &m);
            }
            StartSoundEffect(0x37, 0, 0, &ev->pos, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    return ev->eventFlags != 0;
}

void* FindHitTargetChild(Collider* self)
{
    ContactRow03* cur = self->contacts->head;
    while (cur) {
        if (cur->head != 0 && IsObjectOfKind(cur->other, 0x43) != 0)
            return cur->other;
        cur = cur->next;
    }
    return 0;
}

void InitHitTarget(HitTarget* self)
{
    s32* z;
    InitCollider(self);
    SetColliderAnchors(self, 2, (void*)&g_unitZVector, 3, 0);
    f32 one = 1.0f;
    f32 pt2 = 0.2f;
    z = (s32*)&self->scalePoly;
self->recoverDelay = one;
self->scalePoly.x = one;
self->hitLimit = 8;
self->state = -1;
self->hitInterval = pt2;
z[1]=0;z[2]=0;
}

void LoadHitTarget(HitTarget* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_hitTargetLoadLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

void CopyHitTarget(HitTarget* self)
{
    Bytes8 tmp = *(Bytes8*)&self->blob5A0;
    CopyCollider(self);
    *(Bytes8*)&self->blob5A0 = tmp;
}

void StartHitTarget(HitTarget* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, g_hitTargetStartLinks);
    if (self->scaledObject != 0) {
        *(Bytes8*)&self->f57C = *(Bytes8*)((u8*)self->scaledObject + 0x2DC);
    }
    if (self->soundId != 0) {
        self->soundHandle = (void*)CreateStateWalker(self->soundId, self, -1, 0);
    }
    SetHitTargetState(self, 0);
    self->desc->m03(self);
}

void UpdateHitTarget(HitTarget* self)
{
    UpdateCollider(self);
    s32 n;
    while ((n = ChooseHitTargetState(self)) != self->state) {
        SetHitTargetState(self, n);
    }
    void* sub = self->scaledObject;
    if (sub != 0) {
        f32 t = -self->v150.z;
        if (9.99999975e-05f < t) {
            SetEffectSpawnerInactive(sub);
            TimePolynomial* v = &self->scalePoly;
            f32 p = v->x + t * (v->y + t * v->z);
            f32 lo = g_unitRange.lo;
            f32 hi = g_unitRange.hi;
            f32 x;
            if (p < lo) {
                x = lo;
            } else if (hi < p) {
                x = hi;
            } else {
                x = p;
            }
            f32 a = self->f57C * x;
            f32 b = self->f580 * x;
            u8* o = (u8*)self->scaledObject;
            *(f32*)(o + 0x2DC) = a;
            *(f32*)(o + 0x2E0) = b;
        } else {
            SetEffectSpawnerActiveForever(sub);
        }
    }
}

void StepHitTarget(HitTarget* self)
{
    StepCollider(self);
    if (self->parent == 0) {
        u8 buf[0x30];
        RotateMatrixUpright(&self->m110, 0, buf);
        TurnColliderTowardRotation(self, buf, D_0026B850, g_frameDt);
    }
}

void ComputeHitTargetContactValue(HitTarget* self, Contact03* obj)
{
    obj->f98 = obj->f98 * 0.6f;
}

s32 ApplyHitTargetHit(HitTarget* self, ObjectEvent* ev)
{
    s32 st;

    if ((ev->eventFlags & 0x10) == 0) {
        goto done;
    }
    if (self->parent != 0) {
        goto done;
    }
    st = self->state;
    if (st == 9) {
        goto done;
    }
    if (g_gameClock[1] < self->stateTime + self->hitInterval) {
        goto done;
    }
    st += 1;
    if (st >= self->hitLimit) {
        SetHitTargetState(self, 9);
        void* obj = self->notifyRecord;
        if (obj != 0) {
            SlotMessage msg;
            msg.va = ev->v30;
            f32 f = msg.va.z + 1000.0f;
            msg.kind = 6;
            msg.vb = ev->pos;
            msg.va.z = f;
            ((BaseObject*)obj)->desc->m1B((BaseObject*)obj, &msg);
        }
        StartSoundEffect(0x23, 0, 0, &ev->pos, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    } else {
        SetHitTargetState(self, st);
        StartSoundEffect(0x14F, 0, 0, &ev->pos, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
done:
    return ev->eventFlags != 0;
}

s32 ChooseHitTargetState(HitTarget* self)
{
    s32 v = self->state;
    if (v > 0) {
        if (v >= 9) {
            if (v == 9) {
                goto zero;
            }
            goto end;
        }
        f32 t = g_gameClock[1] - self->stateTime;
        if (self->recoverDelay < t) {
            v -= 1;
        }
        goto end;
    }
    goto end;
zero:
    v = 0;
end:
    return v;
}

void SetHitTargetState(HitTarget* self, s32 value)
{
    s32 old = self->state;
    if (value == old) {
        return;
    }
    if (old == 9) {
        RemoveFinishedHitTarget(self->controller, self);
    }
    self->state = value;
    self->stateTime = g_gameClock[1];
    void* a2 = self->soundHandle;
    if (a2 != 0) {
        void* item = g_hitTargetStateIds[value];
        if (old == -1) {
            TeleportStateWalker(a2, item);
        } else {
            SetStateWalkerTarget(a2, item);
        }
    }
}

void InitSoundStateObject(SoundStateObject* self)
{
    InitCollider(self);
    self->state = -1;
}

void LoadSoundStateObject(SoundStateObject* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_soundStateObjectLinks);
}

void CopySoundStateObject(SoundStateObject* self)
{
    PackedWord8 tmp;
    tmp = self->keptBytes;
    CopyCollider(self);
    self->keptBytes = tmp;
}

void StartSoundStateObject(SoundStateObject* self)
{
    ListFrame frame;
    StartPlacedObject(self);
    if (self->soundId != 0) {
        self->soundHandle = (void*)CreateStateWalker(self->soundId, self, -1, 1);
    }
    BaseObject* n = (BaseObject*)self->children.head;
    while (n != 0) {
        if (IsObjectOfKind(n, 0x7E) != 0) {
            self->child7E = n;
            break;
        }
        n = n->next;
    }
    SetSoundStateObjectState(self, 0);
}

void UpdateSoundStateObject(SoundStateObject* self)
{
    UpdateCollider(self);
    s32 v;
    while ((v = GetSoundStateObjectState(self)) != self->state) {
        SetSoundStateObjectState(self, v);
    }
}

s32 GetSoundStateObjectState(SoundStateObject* p) { return p->state; }

void SetSoundStateObjectState(SoundStateObject* self, s32 idx)
{
    s32 old = self->state;
    if (old == idx) return;
    self->state = idx;
    void* child = self->soundHandle;
    f32 d = g_gameClock[1];
    self->stateTime = d;
    if (child == 0) return;
    s32 v = g_soundStateSoundIds[idx];
    if (old == -1) TeleportStateWalker(child, v);
    else SetStateWalkerTarget(child, v);
}

void InitObjectCreator(ObjectCreator* self)
{
    InitCollider(self);
    self->state = -1;
    SetColliderAnchors(self, 3, 0, 3, 0);
}

void LoadObjectCreator(ObjectCreator* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_objectCreatorLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

void StartObjectCreator(ObjectCreator* self)
{
    StartPlacedObject(self);
    if (self->createsObject == 0) {
        self->desc->m03(self);
        return;
    }
    self->created = FindFirstObjectByIdGathered(self->world, 0x101, 0x59, self->children.head);
    SetObjectCreatorState(self, 0);
}

s32 ChooseObjectCreatorState(ObjectCreator* self);

// dir = d made unit length, or fallback when d is shorter than 0.0001.
static inline void SetDirectionOr(Vec02& dir, u128 d, const Vec02& fallback)
{
    Vu0::Q(dir) = d;
    u128 len = Vu0::Length(d);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        dir = fallback;
    } else {
        Vu0::Q(dir) = Vu0::DivX(d, len);
    }
}

void UpdateObjectCreator(ObjectCreator* self)
{
    Vec02 dir;
    RampProfile ramp;
    Vec02 vel;
    UpdateCollider(self);
    s32 v;
    while ((v = ChooseObjectCreatorState(self)) != self->state) {
        SetObjectCreatorState(self, v);
    }
    if (v == 2) {
        PlacedObject* anchor = (PlacedObject*)self->createsObject;
        SetDirectionOr(dir, Vu0::Sub(Vu0::Q(((PlacedObject*)*(void**)((u8*)anchor + 0x354))->v140), Vu0::Q(((PlacedObject*)self->created)->v140)), g_unitXVector);
        f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(((PlacedObject*)self->created)->v150)));
        ramp.Set(3000.0f, 0.0f, 0.2f);
        f32 speed = ApproachValueWithRamp(len, 3000.0f, g_frameDt, &ramp, 0);
        Vu0::Q(vel) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(speed));
        PlacedObject* o = (PlacedObject*)self->created;
        o->desc02()->m20(o, &vel);
        Mat02 basis;
        BuildBasisFromX(&dir, &basis);
        ((PlacedObject*)self->created)->desc02()->m1E((PlacedObject*)self->created, &basis);
    }
}

void SetObjectCreatorState(ObjectCreator* self, s32 idx)
{
    if (self->state != idx) {
        if (self->activeHandle != 0) {
            StopAnimationPlayer(self->activeHandle);
            self->activeHandle = 0;
        }
        self->state = idx;
        void* s2 = 0;
        self->stateTime = g_gameClock[1];
        switch (idx) {
        case 1: {
            void* a2 = self->notifyRecord;
            s2 = self->f560;
            if (a2 != 0) {
                SlotMessage buf;
                buf.kind = 4;
                buf.qb = *(Quad16*)&self->v140;
                ((BaseObject*)a2)->desc->m1B((BaseObject*)a2, &buf);
            }
            break;
        }
        case 2: {
            void* a = self->created;
            ((PlacedObject*)a)->desc->m15((PlacedObject*)a, 0);
            a = self->created;
            ((PlacedObject*)a)->desc02()->m2F((PlacedObject*)a, 1);
            break;
        }
        }
        if (s2 != 0) CreateAnimationPlayerWithoutPresetTargets(s2, self, 0, &self->activeHandle, 0.0f, 1.0f);
    }
}

s32 ChooseObjectCreatorState(ObjectCreator* self)
{
    s32 mode = self->state;
    s32 r = mode;
    AnimationPlayer* p;
    s32* g;
    s32 bits;
    if (mode == 1) {
        goto acc;
    }
    if (mode < 2) {
        goto out;
    }
    if (mode == 2) {
        goto flags;
    }
    goto out;
acc:
    p = (AnimationPlayer*)self->activeHandle;
    if (p == 0) {
        goto two;
    }
    if (!(p->anim->length <= p->time)) {
        goto flags;
    }
two:
    r = 2;
flags:
    g = *(s32**)&g_currentEntry;
    bits = *g;
    r = (bits & 2) ? 3 : r;
out:
    return r;
}

void RequestPadPattern(PadPatternPlayer* self, s32 a1, s32 a2)
{
    if (self->state == 0) {
        SetPadPatternState(self, 1);
    } else {
        SetPadPatternState(self, 3);
    }
    self->port = a1;
    self->slot = a2;
}

void UpdatePadPattern(PadPatternPlayer* s)
{
    f32 dt = g_gameClock[5];
    switch (s->state) {
    case 2:
        if (*(s32*)g_gameClock != 0 && s->timeLeft > 0.0f) {
            s->stepTime -= dt;
            if (s->stepTime <= 0.0f) {
                s->step++;
                if (s->step >= s->pattern->count) {
                    s->step = 0;
                }
                u8 bytes[2];
                bytes[0] = s->pattern->steps[s->step].bytes[0];
                bytes[1] = s->pattern->steps[s->step].bytes[1];
                SetPadActuatorBytes(s->port, s->slot, bytes);
                s->stepTime = s->pattern->steps[s->step].delay;
            }
            s->timeLeft -= dt;
        } else {
            SetPadPatternState(s, 3);
        }
        break;
    case 3:
    case 4:
        if (s->stepTime > 0.0f) {
            StopPadPatternOutput(s);
            s->stepTime -= dt;
        } else {
            SetPadPatternState(s, s->state == 3);
        }
        break;
    }
}

void StartPadPatternFromTable(PadPatternPlayer* self, s32 index)
{
    StartPadPattern(self, &g_padPatterns[index]);
}

void StartPadPattern(PadPatternPlayer* self, PadPattern* p, f32 f)
{
    if (self->state != 0 && p->count > 0) {
        if (IsPadPatternEnabled((void*)g_saveData) != 0) {
            self->timeLeft = f;
            self->pattern = p;
            self->step = 0;
            f32 x = p->steps[0].delay;
            self->state = -1;
            self->stepTime = x;
            SetPadPatternState(self, 2);
        }
    }
}

void SetPadPatternState(PadPatternPlayer* self, s32 state)
{
    u8 bytes[2];
    if (state == self->state) return;
    switch (state) {
    case 2:
        bytes[0] = self->pattern->steps[0].bytes[0];
        bytes[1] = self->pattern->steps[0].bytes[1];
        SetPadActuatorBytes(self->port, self->slot, bytes);
        self->state = state;
        return;
    case 3:
    case 4:
        StopPadPatternOutput(self);
        self->stepTime = g_frameStep * 4.0f;
        break;
    case 0:
    case 1:
        break;
    }
    self->state = state;
}

void StopPadPatternOutput(PadPatternPlayer* self)
{
    u8 bytes[2];
    bytes[0] = 0;
    bytes[1] = 0;
    SetPadActuatorBytes(self->port, self->slot, bytes);
}

void InitPadPatternSetting(void)
{
    if (g_padPatternSetting == 0) {
        g_padPatternSetting = 1;
    }
}

void ApplyPadPatternSetting(GameProgress* ctx)
{
    s32 v = g_padPatternSetting;
    if (v == 2) {
        goto clear;
    }
    if (v < 3) {
        return;
    }
    if (v == 3) {
        goto set;
    }
    return;
clear:
    ctx->f19EC &= 0xFFFFFFDF;
    return;
set:
    ctx->f19EC |= 0x20;
}

s32 IsPadPatternEnabled(GameProgress* ctx)
{
    s32 v = g_padPatternSetting;
    if (v == 1) {
        goto tail;
    }
    if (v < 2) {
        if (v == 0) {
            goto zero;
        }
        goto tail;
    }
    if (v == 2) {
        goto one;
    }
    if (v == 3) {
        goto zero;
    }
    goto tail;
one:
    return 1;
zero:
    return 0;
tail:
    return ((ctx->f19EC >> 5) ^ 1) & 1;
}

void TogglePadPatternSetting(GameProgress* self)
{
    s32 g = g_padPatternSetting;
    switch (g) {
    case 1: self->f19EC = self->f19EC ^ 0x20; break;
    case 2: self->f19EC = self->f19EC | 0x20; break;
    case 3: self->f19EC = self->f19EC & 0xFFFFFFDF; break;
    }
    if (self->f19EC & 0x20) {
        g_padPatternSetting = 3;
        return;
    }
    g_padPatternSetting = 2;
}