// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1A3AE0 to 0x1A7FE8 (its .rodata from 0x24C9C0, its .data from 0x26B778): class
// 0x15 (the walker collider), the pair controller (class 0x5F) and the paired objects (class
// 0x42), classes 0x43, 0x44 and 0x45 (the hit target, the sound state object, the object
// creator) and the pad pattern player. It ends at an exact edge (object_pool.cpp's start). Its
// start is NOT proved by retail: the cut from effect.cpp at 0x1A3AE0 follows the change of role
// only (effect.cpp says what range retail's data allows), and these families could themselves
// be several files. Its .rodata is the FLT_MAX constants of its functions (literals in their code),
// the jump tables, the triangle func_001A3C40 copies and the pose table func_001A4718 copies; its
// .data is the globals below. Its name is ours, after its largest family, the pair controller and
// the paired objects (classes 0x5F and 0x42); none of its families names the whole.
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
#include "object_finder.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/collider_span.h"
#include "functions/effect_spawner.h"
#include "functions/heap.h"
#include "functions/matrix.h"
#include "functions/oscillator.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
struct BufferedStream;
struct BaseObject;

struct BaseObject;









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












extern Quad219C g_unitXQuad;











struct StateGraph;


void SetWalkerColliderState(WalkerCollider* self, s32 n);

void SetWalkerColliderSubState(WalkerCollider* self, s32 state);



// The three floats of ApproachAngleWithRamp's ramp (D_0024C9C0), copied as a doubleword and a word.
struct RampParams { s64 a __attribute__((packed)); s32 b; };

// What func_001A3C40 turns its object with: the yaw matrix it builds and the ramp it approaches the
// heading by.
struct HeadingFrame {
    Mat02 rot;          // 0x00
    RampParams ramp;    // 0x30
};

extern const f32 g_walkerControlRamp[4];

extern f32 g_frameDt;


void ReadWalkerColliderInput(WalkerCollider* self, PadRecord* src);

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);




void SetSoundStateObjectState(SoundStateObject* self, s32 idx);



// Eight bytes kept across a copy, at any alignment.
struct Bytes8 { u8 b[8]; };



void SetPairedState(PairedObject* self, s32 mode);





void SetHitTargetState(HitTarget* self, s32 value);

extern f32 g_hitTargetTurnRamp[4];





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

// The pad pattern player (0x20 bytes, PadRecord::patternPlayer): the pad it drives, its state (0 and 1
// idle, 2 playing, 3 and 4 stopping), the pattern and its step, the time left to play and the time
// left in the step (or before stopping).
struct PadPatternPlayer {
    u8 pad00[0x04];
    s32 port;               // 0x04: PadRecord::port (func_001A7B20)
    s32 slot;               // 0x08: PadRecord::slot
    s32 state;              // 0x0C
    PadPattern* pattern;    // 0x10
    s32 step;               // 0x14
    f32 timeLeft;           // 0x18
    f32 stepTime;           // 0x1C
};

int IsPadPatternEnabled(GameProgress* ctx);



void SetSoundStateObjectState(SoundStateObject* self, s32 idx);

void DetachPairedPartner(void* self, void* obj);

s32 PairWithNearestWaitingObject(void* self, void* child);


void SetPairedState(PairedObject* self, s32 mode);

s32 PairWithNearestFreeObject(void* self, void* child);


extern f32 g_walkerTurnRamp[4];



extern PadPattern g_padPatterns[11];

extern "C" s32 SetPadActuatorBytes(s32 port, s32 slot, u8* src);


extern s32 g_padPatternSetting;

s32 GetCurrentEntryVariant(void);

void UpdatePairControllerTuning(PairController* self, f32 dt);

void SetPairControllerState(void* self, void* p);




void SetSoundStateObjectState(SoundStateObject* self, s32 idx);


s32 GetSoundStateObjectState(SoundStateObject* self);

void SetSoundStateObjectState(SoundStateObject* self, s32 idx);





s32 ChooseHitTargetState(HitTarget* self);

void SetHitTargetState(HitTarget* self, s32 value);




struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);


void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);









void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

extern s32 g_hitTargetStateIds[10];

void RemoveFinishedHitTarget(PairController* self, HitTarget* obj);



struct Contact03;
struct ContactEnd03;
struct ImpulseRow;






// A pair controller's pose (0xC0 bytes, twelve quadwords): the table func_001A4718 copies into
// PairController::poseA and poseB (g_pairControllerPoseTable).
struct __attribute__((aligned(16))) PairPose {
    AlignedQuad q[12];
};

extern const PairPose g_pairControllerPoseTable;











struct LinkedObject { u8 pad0[0x2D4]; s32 f2D4; };


s32 ChoosePairControllerState(PairController* self);

void SetPairControllerState(PairController* self, s32 mode);

void SpawnPairedObject(PairController* self);

void StartPairedObjects(PairController* self);

void SetObjectCreatorState(ObjectCreator* t, s32 flag);

extern void SetPairedState(PairedObject* self, s32 mode);


void StopPadPatternOutput(PadPatternPlayer* self);

void SetPadPatternState(PadPatternPlayer* self, s32 state);

// func_001A7CE8 passes no time (whatever $f12 holds): this declaration leaves the float out.
void StartPadPattern(PadPatternPlayer* self, PadPattern* p, f32 f);

extern f32 g_frameStep;

extern u8 g_elementStack[];

extern u8 g_scatterController[];



void SetPairedState(PairedObject* self, s32 mode);

void SetWalkerColliderState(WalkerCollider* self, s32 n);

struct ScatterController;


void SetPauseMenuLayerPage(T217D_6D0* self, s32 idx, s32 value);



void ReleasePairedAttachment(u8* self, PairedObject* obj);

void ActivatePairedAttachment(void* p, PairedObject* o);

void FinishPairedObjectTransition(PairController* self, PairedObject* obj);

void RemovePairedObject(PairController* self, PairedObject* obj);

void AttachPairedPartner(void* a0, void* a1);



// A quadratic evaluated at t and clamped to a range (func_001A5760).
#include "clamped_quadratic.h"

ObjectLink g_walkerColliderLoadLinks[2] = { { 0x2, 0x28E, 0x640 }, { 0x2, 0x292, 0x650 } };

ObjectLink g_walkerColliderStartLinks[6] = {
    { 0x4, 0x291, 0x64C },
    { 0x4, 0x299, 0x664 },
    { 0x4, 0x297, 0x65C },
    { 0x4, 0x298, 0x660 },
    { 0x2, 0x29A, 0x680 },
    { 0x2, 0x29B, 0x67C },
};

f32 g_walkerTurnRamp[4] = { 20.0f, 0.0f, 0.30000001192092896f, 0.0f };

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

f32 g_hitTargetTurnRamp[4] = { 2.0f, 0.0f, 0.699999988079071f, 0.0f };

s32 g_hitTargetStateIds[10] = { 0x2A4, 0x2A5, 0x2A6, 0x2A7, 0x2A8, 0x2A9, 0x2AA, 0x2AB, 0x2AC, 0x2AD };

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





f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);
extern const Vec02 g_unitZVector;

// Slot 0 of the walker collider: switched-collider init, both states -1 and a speed scale of
// 2000.0.
void InitWalkerCollider(WalkerCollider* self)
{
    WalkerCollider* o = self;
    InitSwitchedCollider(self);
    o->state = -1;
    o->speedScale = 2000.0f;
    o->subState = -1;
}

// Slot 10 of the walker collider: loads the collider and resolves its two object links.
void LoadWalkerCollider(WalkerCollider* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 2, g_walkerColliderLoadLinks);
}

// Starts the walker collider: when it is enabled (f678), resolves its links, sets its anchors,
// creates its state and sub-state walkers (if it has their graphs), gathers up to three effect
// spawners (id 0x50) and enters state 2 and sub-state 0; otherwise the object is turned off.
void StartWalkerCollider(WalkerCollider* self)
{
    StartPlacedObject(self);
    if (self->f678 != 0) {
        ResolveObjectLinks(self, 6, g_walkerColliderStartLinks);
        SetColliderAnchors(self, 0, 0, 3, 0);
        if (self->stateGraph != 0) {
            self->stateWalker = CreateStateWalker((StateGraph*)self->stateGraph, self, -1, 0);
        }
        if (self->subStateGraph != 0) {
            self->subStateWalker = CreateStateWalker((StateGraph*)self->subStateGraph, self, -1, 1);
        }
        self->spawnerCount = GatherObjectsById(g_currentWorld, 1, 0x50, self->f664, 3, self->spawners);
        SetWalkerColliderState(self, 2);
        SetWalkerColliderSubState(self, 0);
    } else {
        self->desc->m03(self);
    }
}

extern const f32 g_walkerControlRamp[4] = { 30.0f, 0.0f, 0.2f, 0.0f };

// Pad control of the walker collider: finishes the state animation player once it is done, reads
// the stick input, sets the move offset from the heading and the stick length, and turns the
// controlled object toward the aim heading with an angle ramp, in the walker's frame.
void ControlWalkerCollider(WalkerCollider* self, PadRecord* src, f32 dt)
{
    HeadingFrame f;
    if (self->stateAnimDone != 0) {
        StopAnimationPlayer(((AnimationPlayer*)self->stateAnimPlayer));
        self->stateAnimPlayer = 0;
        self->stateAnimDone = 0;
    }
    ReadWalkerColliderInput(self, src);
    ComputePolarOffset((Vec3*)&self->moveOffset, self->heading, self->stickLength * self->speedScale, 0.0f);
    f.ramp = *(RampParams*)g_walkerControlRamp;
    f32 r = ArctangentOfRatio(((PlacedObject*)self->f64C)->m110.r[0].y, ((PlacedObject*)self->f64C)->m110.r[0].x);
    r = ApproachAngleWithRamp(r, self->aimHeading, g_frameDt, &f.ramp, 0);
    BuildYawPitchMatrix(r, 0.0f, (Mat02*)&f.rot);
    TransformRotationBetweenFrames(0, self, &f.rot, &f.rot);
    ((PlacedObject*)self->f64C)->desc02()->m1E(((PlacedObject*)self->f64C), &f.rot);
}

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

// Per-frame update of the walker collider: after the base update, when an animation drives it, it
// takes the attachment's position and velocity (in state 3 it moves toward that position by a
// ramp), sets them and the heading. It then steps the state and sub-state until
// ChooseWalkerColliderState and ChooseWalkerColliderSubState agree, and clears the root tries.
void UpdateWalkerCollider(WalkerCollider* self, f32 dt)
{
    UpdateSwitchedCollider(self, dt);
    if (HasAnimationDrivenAttachment(self) != 0) {
        Vec02 pos;
        Vec02 vel;
        Vec02 diff;
        Vec02 dir;
        Vec02 split;
        RampProfile ramp;
        f32 out;
        self->positionAttachment->vt->getPos(self->positionAttachment, 0.0f, &pos, &vel);
        if (self->state == 3) {
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
            f32 res = ApproachValueWithRamp(&ramp, &out, 0.0f, l, g_frameDt);
            u128 w = Vu0::Scalar(res);
            Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(dir), w);
            Vu0::Q(vel) = Vu0::MulAddX(Vu0::Q(split), Vu0::Q(dir), Vu0::ScalarAt(out));
        }
        self->desc02()->m1D(self, &pos);
        self->desc02()->m20(self, &vel);
        self->heading = ArctangentOfRatio(vel.y, vel.x);
    }
    s32 v;
    while ((v = ChooseWalkerColliderState(self)) != self->state) {
        SetWalkerColliderState(self, v);
    }
    s32 w;
    while ((w = ChooseWalkerColliderSubState(self)) != self->subState) {
        SetWalkerColliderSubState(self, w);
    }
    ClearRootTries(self);
}

// Reads the pad record's two stick magnitudes into the collider; above 0.3 (first stick) or 0.8
// (second) it also stores that stick's camera-relative heading.
void ReadWalkerColliderInput(WalkerCollider* out, PadRecord* src)
{
    if (0.3f < src->stickMagnitude) {
        ComputeCameraRelativeStickHeading(g_camera, src, 0, &out->heading);
    }
    out->stickLength = src->stickMagnitude;
    if (0.8f < src->secondStickMagnitude) {
        ComputeCameraRelativeStickHeading(g_camera, src, 1, &out->aimHeading);
    }
    out->aimLength = src->secondStickMagnitude;
}

// Next state of the walker collider: 0 to 1 when the first stick is pushed, 1 back to 0 when
// released, 2 to 1 when its state animation player is gone.
s32 ChooseWalkerColliderState(WalkerCollider* self)
{
    s32 r = self->state;
    switch (r) {
    case 0:
        if (0.0f < self->stickLength) {
            r = 1;
        }
        break;
    case 1:
        if (self->stickLength == 0.0f) {
            r = 0;
        }
        break;
    case 2:
        if (self->stateAnimPlayer == 0) {
            r = 1;
        }
        break;
    }
    return r;
}

// Switches the walker collider's state (nothing if unchanged): picks a sound for the walker's state
// walker (0x28F or 0x290) and a looping sound (0x14D, or none for state 0), turns its effect
// spawners on for state 0 and off otherwise, and for 2 and 3 starts an animation (state 3 also
// begins the level exit).
void SetWalkerColliderState(WalkerCollider* self, s32 n)
{
    s32 old = self->state;
    if (old == n) return;
    void* h = 0;
    self->state = n;
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
    for (s32 i = 0; i < self->spawnerCount; i++) {
        if (flag) SetEffectSpawnerActiveForever((EffectSpawner*)(((void**)self->spawners)[i]));
        else SetEffectSpawnerInactive((EffectSpawner*)(((void**)self->spawners)[i]));
    }
    if (self->stateWalker) {
        if (old == -1) TeleportStateWalker((StateWalker*)self->stateWalker, snd);
        else SetStateWalkerTarget((StateWalker*)self->stateWalker, snd);
    }
    if (h) {
        CreateAnimationPlayerWithoutPresetTargets((Animation*)h, self, 1, (AnimationPlayer**)&self->stateAnimPlayer, 0.0f, 1.0f);
    }
    if (self->stateSound) {
        if (kind == *self->stateSound) return;
        StopSoundRecord((PlayingSound*)self->stateSound, 0);
        self->stateSound = 0;
    }
    if (kind != -1) {
        StartSoundEffect(kind, (PlayingSound**)&self->stateSound, (BaseObject*)self, 0, 10000.0f, 6000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    }
}

// Next sub-state of the walker collider: 0 to 1 when the second stick reaches 0.8, back to 0 below
// it.
s32 ChooseWalkerColliderSubState(WalkerCollider* self)
{
    s32 r = self->subState;
    switch (r) {
    case 0:
        if (0.8f <= self->aimLength) {
            r = 1;
        }
        break;
    case 1:
        if (self->aimLength < 0.8f) {
            r = 0;
        }
        break;
    }
    return r;
}

// Switches the walker collider's sub-state (nothing if unchanged): sends its sub-state walker to
// key 0x293 (state 0) or 0x294 (state 1), and, for state 1, starts the looping sound 0x150 (state 0
// has none), replacing the previous sound.
void SetWalkerColliderSubState(WalkerCollider* self, s32 state)
{
    s32 old = self->subState;
    if (old == state) {
        return;
    }
    self->subState = state;
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
    if (self->subStateWalker != 0) {
        if (old == -1) {
            TeleportStateWalker((StateWalker*)self->subStateWalker, a2);
        } else {
            SetStateWalkerTarget((StateWalker*)self->subStateWalker, a2);
        }
    }
    s32 cur = -1;
    if (self->subStateSound != 0) {
        cur = *(s32*)self->subStateSound;
        if (s1 == cur) {
            return;
        }
        StopSoundRecord((PlayingSound*)self->subStateSound, 0);
        self->subStateSound = 0;
        cur = -1;
    }
    if (s1 == cur) {
        return;
    }
    f32 zero = 0.0f;
    StartSoundEffect(s1, (PlayingSound**)&self->subStateSound, self, 0, 10000.0f, 6000.0f, 1.0f, zero, zero, 0, 0);
}

// Handles notifications after the base handler: code 5 from the state animation player marks it as
// done; code 0x13 with message 0x295 or 0x296 plays sound 0x152 at the collider and turns one of
// its two effect spawners off.
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
    StartSoundEffect(0x152, 0, 0, &self->v140, 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    SetEffectSpawnerInactive((EffectSpawner*)self->f65C);
    return;
kind296:
    StartSoundEffect(0x152, 0, 0, &self->v140, 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    SetEffectSpawnerInactive((EffectSpawner*)self->f660);
    return;
code5:
    if (rec == self->stateAnimPlayer) {
        self->stateAnimDone = 1;
    }
}

// Slot 0x80 of the walker collider: steps the collider and turns it toward its heading with the
// walker's turn ramp.
void StepWalkerCollider(WalkerCollider* self, f32 dt)
{
    f32 buf[12];
    StepCollider(self, dt);
    BuildYawPitchMatrix(self->heading, 0.0f, (Mat02*)buf);
    TurnColliderTowardRotation(self, g_frameDt, (Mat02*)buf, g_walkerTurnRamp);
}


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

// Slot 0x104 of the walker collider: unless its attachment is animation-driven, removes from the
// contact point the part of its drive along the contact normal.
void ResolveWalkerColliderContact(Walker_001A4538* self, Contact_001A4538* c, s32 i)
{
    if (HasAnimationDrivenAttachment((SwitchedCollider*)self) == 0) {
        Vec02* p = &c->entries[i].point;
        Vec02 d;
        Vu0::Vec e = Vu0::Vec::Of(*p);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->point),
                             Vu0::MulX(Vu0::Q(c->normal), Vu0::Dot(Vu0::Q(self->point), Vu0::Q(c->normal))));
        Vu0::Q(*p) = Vu0::Sub(e.q, Vu0::Q(d));
    }
}

// Slot 0x100 of the walker collider: unless animation-driven, a contact whose normal points up (z
// above 0.7) gets friction 20.
void ComputeWalkerColliderContactValue(WalkerCollider* ctx, Contact03* obj)
{
    if (HasAnimationDrivenAttachment(ctx) != 0) {
        return;
    }
    if (0.7f < obj->normal.z) {
        obj->friction = 20.0f;
    }
}

// Computes the collision response as the collider's does, but when the other object of the contact
// is of kind 0x43 or 0x42 it first sets the mode at +0x450 to 1 and the up vector to the z axis for
// that call, then restores both.
void ComputeWalkerColliderImpulseResponse(WalkerCollider* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    Vec02 s0;
    Vec02 s1;
    s32 n = *(s32*)(a2 + ((1 - a3) << 6));
    s0 = self->v440;
    s1 = self->q450;
    if (n != 0) {
        if (IsObjectOfKind((BaseObject*)n, 0x43) || IsObjectOfKind((BaseObject*)n, 0x42)) {
            self->mode450 = 1;
            self->v440 = g_unitZVector;
        }
    }
    ComputeColliderImpulseResponse(self, a1, (Contact03*)a2, a3, (ContactEnd03*)a4, (ImpulseRow*)a5);
    self->v440 = s0;
    self->q450 = s1;
}

// Slot 0x138 of the walker collider: always 0.
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

// Initialises the controller: its seven lists get the link offsets of the object kind they hold,
// the ids and state are set to -1, the limit to 0x28, two pose tables are copied from the defaults
// and the tuning values (1500, 2300, 1.46 and 3000) are set.
void InitPairController(PairController* self)
{
    PairPose tmp;

    InitPlacedObject(self);
    SetListLinkOffset((List01*)self->list35C, 0x5A0);
    SetListLinkOffset((List01*)self->list368, 0x5A0);
    SetListLinkOffset((List01*)self->list374, 0x5A0);
    SetListLinkOffset((List01*)self->list384, 0x5B0);
    SetListLinkOffset((List01*)self->list390, 0x5B0);
    SetListLinkOffset((List01*)self->list3A0, 0x568);
    SetListLinkOffset((List01*)self->list3AC, 0x568);
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
    self->q3D0 = *(AlignedQuad*)&g_unitXQuad;
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

// Appends an id to the controller's list of ids.
void AppendPairControllerId(PairController* list, s32 value)
{
    s32 n = list->idCount;
    list->ids[n] = value;
    list->idCount = n + 1;
}

// The variant of the current entry from its flags: 2 when bit 2 is set, else 1 when bit 1 is set,
// else 0; the pair controller acts only when it equals its own.
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


// After loading, only for the entry variant it belongs to: finds the objects it controls by id (a
// watched object, two kinds of paired object, an optional target) and tells each its controller;
// makes copies of the two paired objects (enough for the larger pose count) onto list374 and
// list390, and finds for each of its ids a kind-0x44 object for list3A0.
void ResolvePairControllerLinks(PairController* self)
{
    PostLoadPlacedObject(self);
    if (self->id64C == GetCurrentEntryVariant()) {
        u8* s = (u8*)self;
        void* first = FindFirstObjectByIdMode4(g_currentWorld, self->id2D8, self);
        self->watchedObject = first;
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
                o = CreateObjectCopy(a, g_currentWorld, a->parent);
            }
            AppendToList((List01*)(s + 0x374), o);
        }
        for (i = 0; (f32)i < MaxF(self->poseA[9], self->poseB[9]); i++) {
            void* o;
            if (i == 0) {
                o = b;
            } else {
                o = CreateObjectCopy(b, g_currentWorld, b->parent);
            }
            AppendToList((List01*)(s + 0x390), o);
        }
        for (i = 0; i < self->idCount; i++) {
            void* found[4];
            s32 n = GatherObjectsByMode(g_currentWorld, 0x104, self->ids[i], self, 2, found);
            void* hit = 0;
            for (s32 k = 0; k < n; k++) {
                if (IsObjectOfKind((BaseObject*)found[k], 0x44) != 0) {
                    hit = found[k];
                    break;
                }
            }
            ((Controlled558*)hit)->controller = self;
            AppendToList((List01*)(s + 0x3A0), hit);
        }
    }
}

// Starts the object and, if this is the entry variant it belongs to, blends its two tables of 48
// values by a clamped quadratic of the current entry's time (poseOut = (1 - t) * poseA + t *
// poseB), updates the tuning values at 0 and enters state 0; for another variant the object is
// turned off.
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

// Per-frame update of the controller: after the placed object update it steps its state until
// ChoosePairControllerState agrees. In state 2 it spawns paired objects (below the limit and once
// the start time has come) and attaches them when the attach time has come; in state 5 it starts
// the target creator once the link is not in its state 3.
void UpdatePairController(PairController* self, f32 dt)
{
    ObjectCreator* t;
    s32 st;
    UpdatePlacedObject(self, dt);
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
            if (self->nextStartTime < g_gameClock[1]) {
                SpawnPairedObject(self);
            }
        }
        if (self->nextAttachTime < g_gameClock[1]) {
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

// Slot 0xC8 of the pair controller: shows its caption element (slot 14) in state 2 while the menus
// and fade are clear, otherwise hides it (slot 15).
void ShowPairControllerElement(PairController* self)
{
    s32 p = 0;
    if (self->state == 2) {
        p = AreMenusAndFadeClear();
    }
    if (p != 0) {
        g_pairControllerCountCaption.vt->m14(&g_pairControllerCountCaption);
    } else {
        g_pairControllerCountCaption.vt->m15(&g_pairControllerCountCaption);
    }
}

// Chooses the controller's next state: 0 goes to 1 when the watched object's state is 1 or less, 1
// to 2 when the link is not in its state 3, 2 to 3 once a transition is counted or to 5 when the
// finished count reaches the limit, 3 to 4 when the link leaves its state 3, and 5 to 6 three
// seconds after the target reached its state 3 (five seconds on with no target). 4 and 6 are final.
s32 ChoosePairControllerState(PairController* self)
{
    u32 s = self->state;
    switch (s) {
    case 0:
        { u32 one = 1;
        if (((WalkerCollider*)self->watchedObject)->state <= one) s = one; }
        break;
    case 1:
        if (!self->link || self->link->f2D4 != 3) s = 2;
        break;
    case 2:
        if (self->transitionCount) { s = 3; break; }
        if (self->finishedCount == self->limit3B8) s = 5;
        break;
    case 3:
        if (self->link->f2D4 != 3) s = 4;
        break;
    case 5:
        if (self->target) {
            if (self->target->state == 3 && self->target->stateTime + 3.0f < g_gameClock[1]) s = 6;
        } else if (self->stateStartTime + 5.0f < g_gameClock[1]) {
            if (!self->link || self->link->f2D4 != 3) s = 6;
        }
        break;
    case 4:
    case 6:
        break;
    }
    return s;
}

// Switches the controller's state: 1 shows a caption from object 0x33B (some entry variants); 2
// points the count caption at the finished and limit counts and becomes the world's active
// follower; 5 shows 0x33D, sets the active objects to state 8 and resets scatter levels; 3 shows
// 0x33E, sets unpaired ones to 7; 4 opens pause page 0x1A; 6 sets the watched object to state 3.
void SetPairControllerState(PairController* self, s32 state)
{
    PairedObject* o;
    void* v;
    ListFrame frame;
    if (self->state == state) return;
    self->state = state;
    self->stateStartTime = g_gameClock[1];
    self->link = 0;
    switch (state) {
    case 0:
        break;
    case 1: {
        if (self->id64C < 3) {
            if (self->id64C >= 0) {
                if (g_currentEntry->f14) {
                    self->link = 0;
                } else {
                    self->link = (LinkedObject*)FindFirstObjectById(self->world, 0x105, 0x33B, 0);
                }
            }
        }
        void* w = self->link;
        if (w) {
            T217D_440* box = &g_typedTextCaptionBox;
            ((PtrP*)&box->child)->v = w;
            PushStackElement((ElementStack*)g_elementStack, box);
        }
        break;
    }
    case 2: {
        g_pairControllerCountCaption.target = &self->finishedCount;
        g_pairControllerCountCaption.limit = &self->limit3B8;
        SetWorldActiveFollower(self->world, self);
        break;
    }
    case 5:
        v = FindFirstObjectById(self->world, 0x105, 0x33D, 0);
        self->link = (LinkedObject*)v;
        if (v) {
            g_typedTextCaptionBox.child = (void*)v;
            PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
        }
        for (o = self->head384; o; o = o->nextActive) SetPairedState(o, 8);
        ResetScatterLevels((ScatterController*)g_scatterController);
        break;
    case 3:
        v = FindFirstObjectById(self->world, 0x105, 0x33E, 0);
        self->link = (LinkedObject*)v;
        if (v) {
            g_typedTextCaptionBox.child = (void*)v;
            PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
        }
        for (o = self->head384; o; o = o->nextActive) {
            BaseObject* l = (BaseObject*)o->partner;
            if (l == 0 || l->parent != o) SetPairedState(o, 7);
        }
        RaiseScatterLevels((ScatterController*)g_scatterController, 1.0f);
        break;
    case 4:
        SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0x1A);
        break;
    case 6:
        SetWalkerColliderState((WalkerCollider*)(self->watchedObject), 3);
        g_buttonHintElement.vt->m15(&g_buttonHintElement);
        break;
    }
}

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

// Brings one object of the free list (list374) into play unless the limit is reached. It tries up
// to eight random points around the controller and takes the first not near the active collider or
// any object of the active lists; the object is turned on there with a random heading, moved to the
// active list, paired with the nearest waiting object, and the next start is scheduled.
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
        self->nextStartTime = 3.4028235e+38f;
        return;
    }
    o = *(PairedObject**)self->list374;
    for (i = 0; i < 8; i++) {
        f32 angle = RandomFloatInRange(0.0f, 6.2831855f);
        f32 radius = RandomFloatInRange(self->minRadius340 + o->radius3D0, self->tune344);
        other = (PairedObject*)GetActiveSwitchedCollider();
        ComputePolarOffset((Vec3*)&pos, angle, radius, 0.0f);
        pos.y = pos.y * self->tune34C;
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(self->f330), Vu0::Q(pos));
        if (other != 0 && IsNearSpot(pos, other, o)) {
            continue;
        }
        for (n = self->head384; n != 0; n = n->nextActive) {
            if (IsNearSpotOf(pos, n, o)) {
                break;
            }
        }
        if (n != 0) {
            continue;
        }
        for (m = self->head35C; m != 0; m = m->nextFree) {
            if (m->parent == 0 && IsNearSpot(pos, m, o)) {
                break;
            }
        }
        if (m != 0) {
            continue;
        }
        for (m = self->head368; m != 0; m = m->nextFree) {
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
        SetColliderAnchors(o, 2, (Vec02*)&g_unitZVector, 3, 0);
        SetHitTargetState((HitTarget*)o, 0);
        RemoveFromList((List01*)self->list374, o);
        AppendToList((List01*)self->list368, o);
        PairWithNearestWaitingObject(self, o);
        self->nextStartTime = g_gameTime + RandomFloatInRange(self->startDelayMin, self->startDelayMax);
    }
}

// Attaches one object of list390 to a random node of list3A0 (both move to their active lists)
// unless the attach limit is reached (then the next attach time is the largest float). The object
// is turned on at the node's position and orientation in state 1 with the controller's speed and
// turn limits, sounds start and the next attach time is scheduled.
void StartPairedObjects(PairController* self)
{
    if (self->count39C >= self->attachLimit) {
        self->nextAttachTime = 3.4028234663852886e+38f;
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
            RemoveFromList((List01*)self->list3A0, node);
            AppendToList((List01*)self->list3AC, node);
            RemoveFromList((List01*)self->list390, owner);
            AppendToList((List01*)self->list384, owner);
            owner->attachment = (SoundStateObject*)node;
            (self->count39C)++;
            owner->desc->m02(owner);
            owner->desc02()->m1D(owner, (Vec02*)(node + 0x140));
            owner->desc02()->m1E(owner, (Mat02*)(node + 0x110));
            SetPairedState(owner, 1);
            SetSoundStateObjectState(owner->attachment, 1);
            owner->maxSpeed = self->f644;
            owner->maxTurn = self->f648;
            f32* fp = &self->attachDelayMin;
            self->nextAttachTime = g_gameClock[1] + RandomFloatInRange(self->attachDelayMin, fp[1]);
            StartSoundEffect(-1, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            StartSoundEffect(0x14E, 0, (BaseObject*)node, 0, 12000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
}

// Recomputes the controller's current tuning values from pairs of start and end values (blended by
// a clamped quadratic of dt each): the two delay ranges, two further ranges, two single values and
// the two limits of active objects. When a limit rises while the old limit was reached, the next
// start (or attach) time is scheduled at once.
void UpdatePairControllerTuning(PairController* self, f32 dt)
{
    f32 t0;
    ClampedQuadratic::Get(t0, &self->blend.startDelay.q, dt);
    self->startDelayMin = (1.0f - t0) * self->blend.startDelay.value[0] + t0 * self->blend.startDelay.value[2];
    self->startDelayMax = (1.0f - t0) * self->blend.startDelay.value[1] + t0 * self->blend.startDelay.value[3];

    f32 t1;
    ClampedQuadratic::Get(t1, &self->blend.attachDelay.q, dt);
    self->attachDelayMin = (1.0f - t1) * self->blend.attachDelay.value[0] + t1 * self->blend.attachDelay.value[2];
    self->attachDelayMax = (1.0f - t1) * self->blend.attachDelay.value[1] + t1 * self->blend.attachDelay.value[3];

    f32 t2;
    ClampedQuadratic::Get(t2, &self->blend.speed.q, dt);
    self->f644 = (1.0f - t2) * self->blend.speed.value[0] + t2 * self->blend.speed.value[1];

    f32 t3;
    ClampedQuadratic::Get(t3, &self->blend.turn.q, dt);
    self->f648 = (1.0f - t3) * self->blend.turn.value[0] + t3 * self->blend.turn.value[1];

    f32 t4;
    ClampedQuadratic::Get(t4, &self->blend.limit.q, dt);
    s32 n = (s32)((1.0f - t4) * self->blend.limit.value[0] + t4 * self->blend.limit.value[1]);
    if (self->limit624 < n && self->count380 == self->limit624) {
        self->nextStartTime = g_gameClock[1] + RandomFloatInRange(self->startDelayMin, self->startDelayMax);
    }
    self->limit624 = n;

    f32 t5;
    ClampedQuadratic::Get(t5, &self->blend.attachLimit.q, dt);
    n = (s32)((1.0f - t5) * self->blend.attachLimit.value[0] + t5 * self->blend.attachLimit.value[1]);
    if (self->attachLimit < n && self->count39C == self->attachLimit) {
        self->nextAttachTime = g_gameClock[1] + RandomFloatInRange(self->attachDelayMin, self->attachDelayMax);
    }
    self->attachLimit = n;
}

// Takes a finished hit target out of play: counts it as finished (and updates the controller's
// tuning to the finished fraction), returns it to the free list, re-pairs its partner with the
// nearest free object (state 3) or, if there is none, leaves it unpaired (state 2), turns it off,
// and, where the limit had been reached, schedules the next start time.
void RemoveFinishedHitTarget(PairController* self, HitTarget* obj)
{
    s32 n = self->finishedCount + 1;
    f32 x = (f32)self->limit3B8;
    self->finishedCount = n;
    UpdatePairControllerTuning(self, (f32)n / x);
    if (obj->partner != 0) {
        RemoveFromList((List01*)self->list35C, obj);
    } else {
        RemoveFromList((List01*)self->list368, obj);
    }
    AppendToList((List01*)self->list374, obj);
    if (obj->partner != 0) {
        if (PairWithNearestFreeObject(self, obj->partner) != 0) {
            SetPairedState((PairedObject*)obj->partner, 3);
        } else {
            ((HitTarget*)obj->partner)->partner = 0;
            SetPairedState((PairedObject*)obj->partner, 2);
        }
    }
    obj->partner = 0;
    obj->desc->m03(obj);
    if (self->count380 == self->limit624) {
        f32 t = RandomFloatInRange(self->startDelayMin, self->startDelayMax);
        self->nextStartTime = g_gameClock[1] + t;
    }
    self->count380 = self->count380 - 1;
}

// Moves the paired object's attachment back from the used list to the free list, sets its state to
// 0 and clears the field.
void ReleasePairedAttachment(u8* self, PairedObject* obj)
{
    RemoveFromList((List01*)(self + 0x3AC), obj->attachment);
    AppendToList((List01*)(self + 0x3A0), obj->attachment);
    SetSoundStateObjectState(obj->attachment, 0);
    obj->attachment = 0;
}

// Makes the paired object the parent of its partner, stops the partner's velocity and spin, fixes
// its anchors and plays sound 0x151.
void AttachPairedPartner(void* a0, void* a1)
{
    PairedObject* s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc->m15((Collider*)s->partner, (BaseObject*)a1);
    s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc02()->m20((Collider*)s->partner, (Vec02*)&D_00248D30);
    s = (PairedObject*)a1;
    ((Collider*)s->partner)->desc02()->m21((Collider*)s->partner, (Vec02*)&D_00248D30);
    SetColliderAnchors((Collider*)((PairedObject*)a1)->partner, 3, 0, 3, 0);
    StartSoundEffect(0x151, (PlayingSound**)0, 0, (Vec02*)0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

// Releases the partner from its parent, stops its velocity and spin and lets it move only along z
// again.
void DetachPairedPartner(PairController* unused, PairedObject* h)
{
    Collider* o = (Collider*)h->partner;

    (void)unused;
    o->desc->m15(o, 0);
    o->desc02()->m20(o, (Vec02*)&D_00248D30);
    o->desc02()->m21(o, (Vec02*)&D_00248D30);
    SetColliderAnchors(o, 2, (Vec02*)&g_unitZVector, 3, 0);
}

// Sets the paired object's attachment to state 1; SetPairedState calls it on the transition from
// state 5 to 6.
void ActivatePairedAttachment(void* unused, PairedObject* obj)
{
    SetSoundStateObjectState(obj->attachment, 1);
}

// Ends a pairing: counts the transition, returns the partner to its free list (list374), the object
// to list390 and the attachment node to list3A0 (and turns the node's state to 0), turns both
// objects off, clears the links and, where a limit had been reached, schedules the next start and
// attach times. Plays sound 0x51.
void FinishPairedObjectTransition(PairController* self, PairedObject* obj)
{
    self->transitionCount = self->transitionCount + 1;
    RemoveFromList((List01*)self->list35C, obj->partner);
    AppendToList((List01*)self->list374, obj->partner);
    RemoveFromList((List01*)self->list384, obj);
    AppendToList((List01*)self->list390, obj);
    RemoveFromList((List01*)self->list3AC, obj->attachment);
    AppendToList((List01*)self->list3A0, obj->attachment);
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
        f32 t = RandomFloatInRange(self->startDelayMin, self->startDelayMax);
        self->nextStartTime = g_gameClock[1] + t;
    }
    self->count380 = self->count380 - 1;
    if (self->count39C == self->attachLimit) {
        f32 t2 = RandomFloatInRange(self->attachDelayMin, self->attachDelayMax);
        self->nextAttachTime = g_gameClock[1] + t2;
    }
    self->count39C = self->count39C - 1;
    StartSoundEffect(0x51, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

// Takes a paired object out of play: back to the list390 (and its attachment node to list3A0 and
// state 0), its partner detached and returned to the free list (re-paired with the nearest waiting
// object if there is one), the links cleared, the object turned off, and, where the attach limit
// had been reached, the next attach time scheduled.
void RemovePairedObject(PairController* self, PairedObject* obj)
{
    RemoveFromList((List01*)self->list384, obj);
    AppendToList((List01*)self->list390, obj);
    if (obj->attachment != 0) {
        RemoveFromList((List01*)self->list3AC, obj->attachment);
        AppendToList((List01*)self->list3A0, obj->attachment);
        SetSoundStateObjectState(obj->attachment, 0);
    }
    PairedObject* child = (PairedObject*)obj->partner;
    if (child != 0) {
        if (child->parent == obj) {
            DetachPairedPartner(self, obj);
        }
        RemoveFromList((List01*)self->list35C, child);
        AppendToList((List01*)self->list368, child);
        if (PairWithNearestWaitingObject(self, child) == 0) {
            child->partner = 0;
        }
    }
    obj->attachment = 0;
    obj->partner = 0;
    obj->desc->m03(obj);
    if (self->count39C == self->attachLimit) {
        f32 r = RandomFloatInRange(self->attachDelayMin, self->attachDelayMax);
        self->nextAttachTime = g_gameClock[1] + r;
    }
    self->count39C = self->count39C - 1;
}

// Pairs the object with the nearest (in xy) object of the free list list368: both become partners
// and the found one moves to list35C. Gives 1, or 0 if the list is empty.
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
    for (PairedObject* p = c->head368; p != 0; p = p->nextFree) {
        u128 d = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(o->v140));
        f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (dist < best) {
            best = dist;
            found = p;
        }
    }
    o->partner = found;
    found->partner = o;
    RemoveFromList((List01*)c->list368, found);
    AppendToList((List01*)c->list35C, found);
    return 1;
}

// Pairs obj with node (each becomes the other's partner), moving node from the controller's waiting
// list to its paired list; whoever either had as a partner before is unpaired and looks for a new
// one.
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
        RemoveFromList((List01*)(self + 0x368), node);
        AppendToList((List01*)(self + 0x35C), node);
    }
    if (cur != 0) {
        RemoveFromList((List01*)(self + 0x35C), cur);
        AppendToList((List01*)(self + 0x368), cur);
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

// Pairs the object with the nearest (in xy) attached object that has no partner and is in state 2:
// both become partners, the object moves to list35C, and the other is put in state 3. Gives 1, or 0
// if there is none.
s32 PairWithNearestWaitingObject(void* self, void* child)
{
    ListFrame frame;
    PairController* c = (PairController*)self;
    PairedObject* o = (PairedObject*)child;
    f32 best = 3.4028234663852886e+38f;
    PairedObject* found = 0;
    for (PairedObject* p = c->head384; p != 0; p = p->nextActive) {
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
    RemoveFromList((List01*)c->list368, o);
    AppendToList((List01*)c->list35C, o);
    SetPairedState(found, 3);
    return 1;
}

// Takes the object of the controller's free list nearest (in x and y) to the paired object, moves
// it to the used list and stores it as the paired object's attachment; 0 when the free list is
// empty.
s32 AssignNearestListedObjectToPair(PairController* self, PairedObject* obj)
{
    ListFrame frame;
    if (IsListEmpty((List01*)self->list3A0) != 0) {
        return 0;
    }
    f32 best = 3.4028234663852886e+38f;
    SoundStateObject* found = 0;
    for (SoundStateObject* p = self->head3A0; p != 0; p = p->listNext) {
        u128 d = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(obj->v140));
        f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (dist < best) {
            best = dist;
            found = p;
        }
    }
    RemoveFromList((List01*)self->list3A0, found);
    AppendToList((List01*)self->list3AC, found);
    obj->attachment = found;
    return 1;
}

// Gives the paired object a random offset in the plane (random angle, radius up to the
// controller's) and scales its +0x574 value by the controller's.
void RandomizePairedObjectOffset(PairController* self, PairedObject* b)
{
    f32 r0 = RandomFloatInRange(0.0f, 6.2831855f);
    f32 r1 = RandomFloatInRange(0.0f, self->tune348);
    ComputePolarOffset((Vec3*)&b->offset570, r0, r1, 0.0f);
    b->offset570.y = b->offset570.y * self->tune34C;
}

// Address of the controller's current pose record (0xC0 bytes each, from +0x3E0).
void* GetPairControllerPose(void* self)
{
    PairController* obj = (PairController*)self;
    return (u8*)self + (obj->poseIndex * 0xC0 + 0x3E0);
}

// Slot 0 of the paired object: collider init, state -1, offset wait times of 1.0 and 2.5 and its
// anchors.
void InitPairedObject(PairedObject* self)
{
    InitCollider(self);
    self->state = -1;
    self->offsetWaitMin = 1.0f;
    self->offsetWaitMax = 2.5f;
    SetColliderAnchors(self, 1, (Vec02*)&g_unitZVector, 2, (Vec02*)&g_unitZVector);
}

// Slot 10 of the paired object: loads the collider, resolves its six object links and sets up its
// notify group.
void LoadPairedObject(PairedObject* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 6, g_pairedObjectLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

// Slot 9 of the paired object: copies as a collider but keeps its own 8-byte field at +0x5B0.
void CopyPairedObject(PairedObject* self, PairedObject* src)
{
    Bytes8 tmp = *(Bytes8*)&self->blob5B0;
    CopyCollider(self, src);
    *(Bytes8*)&self->blob5B0 = tmp;
}

// Slot 16 of the paired object: starts the placed object, sets state 0 and calls its slot 3.
void StartPairedObject(PairedObject* self)
{
    StartPlacedObject(self);
    SetPairedState(self, 0);
    self->desc->m03(self);
}

s32 ChoosePairedObjectState(PairedObject* self);
void SteerPairedObjectWithinArea(PairedObject* self, Vec02* goal, s32 flag);

// The distance from b to a on the ground (their x and y).
static inline f32 GroundDistance(u128 a, u128 b)
{
    u128 d = Vu0::Sub(a, b);
    return Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
}

// Each frame: the state the object should be in, then where it steers in it.
void UpdatePairedObject(PairedObject* self, f32 dt)
{
    Vec02 v;
    UpdateCollider(self, dt);
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
        ConvertPositionToWorld((BaseObject*)self->attachment->child7E, &v);
        SteerPairedObjectWithinArea(self, &v, 0);
        break;
    case 2: {
        if (self->nextOffsetTime < g_gameClock[1] || GroundDistance(Vu0::Q(self->v140), Vu0::Q(self->offset570)) < 50.0f) {
            RandomizePairedObjectOffset((PairController*)self->controller, self);
            self->nextOffsetTime = g_gameClock[1] + RandomFloatInRange(self->offsetWaitMin, self->offsetWaitMax);
        }
        SteerPairedObjectWithinArea(self, &self->offset570, 0);
        break;
    }
    case 3:
        SteerPairedObjectWithinArea(self, &((PlacedObject*)self->partner)->v140, 0);
        break;
    case 5:
        ConvertPositionToWorld((BaseObject*)self->attachment->child7E, &v);
        SteerPairedObjectWithinArea(self, &v, 1);
        break;
    case 6:
        SteerPairedObjectWithinArea(self, &self->attachment->v140, 1);
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


// Steers the object toward goal in the horizontal plane without leaving the controller's circular
// area (a goal outside is moved to 1.5 radii from the centre on the line it crosses). Facing more
// than 3 degrees off it stops and turns; otherwise it moves at up to maxSpeed (backwards if asked)
// and turns at up to maxTurn per second.
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
        ConvertPositionToWorld((BaseObject*)self->attachment->child7E, &v);
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
        AnimationPlayer* p = (AnimationPlayer*)self->activeHandle;
        if (p != 0 && p->time < ((Animation*)self->attachAnimation)->length) {
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
        ConvertPositionToWorld((BaseObject*)self->attachment->child7E, &v);
        if (GroundDistance(Vu0::Q(self->v140), Vu0::Q(v)) < 10.0f) {
            s = 6;
        }
        break;
    case 6:
        if (GroundDistance(Vu0::Q(self->v140), Vu0::Q(self->attachment->v140)) < 10.0f) {
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

// Switches the paired object's state: stops its animation player and state walker, runs the old
// state's exit action (release the attachment from 1, activate it from 5 to 6, finish the
// transition from 6 to 0, remove from 9), then starts what the new state needs: an animation (roam,
// attach, paired or remove, with the partner bound by key 0x2A0) or the state graph of 7 or 8.
void SetPairedState(PairedObject* self, s32 mode)
{
    TargetBinding buf[2];
    TargetBinding* w;
    void* h;
    void* s3;

    if (self->state == mode) return;
    if (self->activeHandle) {
        StopAnimationPlayer((AnimationPlayer*)self->activeHandle);
        self->activeHandle = 0;
    }
    if (self->soundHandle) {
        DestroyStateWalker((StateWalker*)self->soundHandle);
        self->soundHandle = 0;
    }
    switch (self->state) {
    case 1:
        ReleasePairedAttachment((u8*)self->controller, self);
        break;
    case 5:
        if (mode == 6) ActivatePairedAttachment(self->controller, self);
        break;
    case 6:
        if (mode == 0) FinishPairedObjectTransition((PairController*)self->controller, self);
        break;
    case 9:
        RemovePairedObject((PairController*)self->controller, self);
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
        h = self->roamAnimation;
        break;
    case 4:
        AttachPairedPartner(self->controller, self);
        w->key = 0x2A0; w->object = self->partner; w++;
        h = self->attachAnimation;
        break;
    case 5: case 6:
        w->key = 0x2A0; w->object = self->partner; w++;
        h = self->pairedAnimation;
        break;
    case 7:
        s3 = self->graphState7;
        break;
    case 8:
        s3 = self->graphState8;
        break;
    case 9:
        h = self->removeAnimation;
        break;
    }
    if (h) CreateAnimationPlayer((Animation*)h, self, w - buf, buf, 1, (AnimationPlayer**)&self->activeHandle, 0.0f, 1.0f);
    if (s3) self->soundHandle = CreateStateWalker((StateGraph*)s3, self, -1, 1);
}

// Handles a hit event (flag 0x20) on a paired object: from most states it goes to state 9
// (removal), from state 6 it takes its partner target to state 9 as well. When it has reached state
// 9 it sends its notify record a message (kind 6, with the hit's vectors, 3000 above in z) and
// plays sound 0x37. Gives whether the event had any flags.
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

// Returns the first object among the collider's contacts, with data, that is a hit target (kind
// 0x43); 0 if none.
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

// Slot 0 of the hit target: collider init, anchors, state -1, a hit limit of 8, recover delay 1.0
// and hit interval 0.2, with its scale polynomial reset to 1.
void InitHitTarget(HitTarget* self)
{
    s32* z;
    InitCollider(self);
    SetColliderAnchors(self, 2, (Vec02*)&g_unitZVector, 3, 0);
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

// Slot 10 of the hit target: loads the collider, resolves its object link and sets up its notify
// group.
void LoadHitTarget(HitTarget* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 1, g_hitTargetLoadLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

// Slot 9 of the hit target: copies as a collider but keeps its own 8-byte field at +0x5A0.
void CopyHitTarget(HitTarget* self, HitTarget* src)
{
    Bytes8 tmp = *(Bytes8*)&self->blob5A0;
    CopyCollider(self, src);
    *(Bytes8*)&self->blob5A0 = tmp;
}

// Slot 16 of the hit target: starts the placed object, resolves its link, copies the pair of values
// from its scaled object, creates its sound walker, sets state 0 and calls its slot 3.
void StartHitTarget(HitTarget* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, g_hitTargetStartLinks);
    if (self->scaledObject != 0) {
        self->spawnerInterval = self->scaledObject->delay;
    }
    if (self->soundId != 0) {
        self->soundHandle = (void*)CreateStateWalker((StateGraph*)self->soundId, self, -1, 0);
    }
    SetHitTargetState(self, 0);
    self->desc->m03(self);
}

// Per-frame update of the hit target: after the base update it steps its state until
// ChooseHitTargetState agrees, then drives the effect spawner of its scaled object from the upward
// speed: stopped while the object is not falling, otherwise its interval range scaled by a clamped
// quadratic of the speed.
void UpdateHitTarget(HitTarget* self, f32 dt)
{
    UpdateCollider(self, dt);
    s32 n;
    while ((n = ChooseHitTargetState(self)) != self->state) {
        SetHitTargetState(self, n);
    }
    if (self->scaledObject != 0) {
        f32 t = -self->v150.z;
        if (9.99999975e-05f < t) {
            SetEffectSpawnerInactive(self->scaledObject);
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
            f32 a = self->spawnerIntervalMin * x;
            f32 b = self->spawnerIntervalMax * x;
            EffectSpawner* o = self->scaledObject;
            o->delayMin = a;
            o->delayMax = b;
        } else {
            SetEffectSpawnerActiveForever(self->scaledObject);
        }
    }
}

// Slot 0x80 of the hit target: steps the collider and, without a parent, turns it toward its
// upright rotation with the hit target's turn ramp.
void StepHitTarget(HitTarget* self, f32 dt)
{
    StepCollider(self, dt);
    if (self->parent == 0) {
        u8 buf[0x30];
        RotateMatrixUpright(&self->m110, 0, (Mat02*)buf);
        TurnColliderTowardRotation(self, g_frameDt, (Mat02*)buf, g_hitTargetTurnRamp);
    }
}

// Slot 0x100 of the hit target: scales the contact's bounce by 0.6.
void ComputeHitTargetContactValue(HitTarget* self, Contact03* obj)
{
    obj->bounce = obj->bounce * 0.6f;
}

// Handles a hit event on a hit target: if the event has flag 0x10, the target has no parent, is not
// in state 9 and its hit interval has passed, it steps to the next state; at the hit limit it goes
// to state 9, sends its notify record a message (kind 6, with the hit's vectors, 1000 above in z)
// and plays sound 0x23, otherwise it plays sound 0x14F. Gives whether the event had any flags.
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

// Next state of a hit target: one lower once the recover delay has passed since the last change,
// and 0 from state 9.
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

// Changes a hit target's state: stamps the clock, tells the controller when it leaves state 9 and
// moves its sound walker to the sound of the new state (jumping straight there for the first
// state).
void SetHitTargetState(HitTarget* self, s32 value)
{
    s32 old = self->state;
    if (value == old) {
        return;
    }
    if (old == 9) {
        RemoveFinishedHitTarget((PairController*)self->controller, self);
    }
    self->state = value;
    self->stateTime = g_gameClock[1];
    void* a2 = self->soundHandle;
    if (a2 != 0) {
        s32 item = g_hitTargetStateIds[value];
        if (old == -1) {
            TeleportStateWalker((StateWalker*)a2, item);
        } else {
            SetStateWalkerTarget((StateWalker*)a2, item);
        }
    }
}

// Slot 0 of the sound-state object: collider init and state -1.
void InitSoundStateObject(SoundStateObject* self)
{
    InitCollider(self);
    self->state = -1;
}

// Slot 10 of the sound-state object: loads the collider and resolves its object link.
void LoadSoundStateObject(SoundStateObject* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 1, g_soundStateObjectLinks);
}

// Slot 9 of the sound-state object: copies as a collider but keeps its own 8 bytes of kept data.
void CopySoundStateObject(SoundStateObject* self, SoundStateObject* src)
{
    PackedWord8 tmp;
    tmp = self->keptBytes;
    CopyCollider(self, src);
    self->keptBytes = tmp;
}

// Slot 16 of the sound-state object: starts the placed object, creates its sound walker, finds its
// first child of kind 0x7E and sets state 0.
void StartSoundStateObject(SoundStateObject* self)
{
    ListFrame frame;
    StartPlacedObject(self);
    if (self->soundId != 0) {
        self->soundHandle = (void*)CreateStateWalker((StateGraph*)self->soundId, self, -1, 1);
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

// Slot 17 of the sound-state object: updates the collider, then changes state until the chosen
// state equals the current one.
void UpdateSoundStateObject(SoundStateObject* self, f32 dt)
{
    UpdateCollider(self, dt);
    s32 v;
    while ((v = GetSoundStateObjectState(self)) != self->state) {
        SetSoundStateObjectState(self, v);
    }
}

s32 GetSoundStateObjectState(SoundStateObject* p) { return p->state; }

// Changes a sound-state object's state, stamps the clock and moves its sound walker to the sound of
// the new state (jumping straight there for the first state).
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
    if (old == -1) TeleportStateWalker((StateWalker*)child, v);
    else SetStateWalkerTarget((StateWalker*)child, v);
}

// Slot 0 of the object creator: collider init, state -1 and its anchors.
void InitObjectCreator(ObjectCreator* self)
{
    InitCollider(self);
    self->state = -1;
    SetColliderAnchors(self, 3, 0, 3, 0);
}

// Slot 10 of the object creator: loads the collider, resolves its object link and sets up its
// notify group.
void LoadObjectCreator(ObjectCreator* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 1, g_objectCreatorLinks);
    FindOrBuildMemberGroup(&self->notifyRecord, self);
}

// Slot 16 of the object creator: starts the placed object, then either calls its slot 3 or, when it
// creates an object, finds that object and sets state 0.
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

// Per-frame update of the creator: after the base update it steps its state until it agrees with
// ChooseObjectCreatorState; in state 2 it flies the created object toward the point of the object
// it creates for, at a speed taken from a ramp (limit 3000) and turned to face it.
void UpdateObjectCreator(ObjectCreator* self, f32 dt)
{
    Vec02 dir;
    RampProfile ramp;
    Vec02 vel;
    UpdateCollider(self, dt);
    s32 v;
    while ((v = ChooseObjectCreatorState(self)) != self->state) {
        SetObjectCreatorState(self, v);
    }
    if (v == 2) {
        PairController* anchor = (PairController*)self->createsObject;
        SetDirectionOr(dir, Vu0::Sub(Vu0::Q(((PlacedObject*)anchor->watchedObject)->v140), Vu0::Q(((PlacedObject*)self->created)->v140)), g_unitXVector);
        f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(((PlacedObject*)self->created)->v150)));
        ramp.Set(3000.0f, 0.0f, 0.2f);
        f32 speed = ApproachValueWithRamp(&ramp, 0, len, 3000.0f, g_frameDt);
        Vu0::Q(vel) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(speed));
        PlacedObject* o = (PlacedObject*)self->created;
        o->desc02()->m20(o, &vel);
        Mat02 basis;
        BuildBasisFromX(&dir, &basis);
        ((PlacedObject*)self->created)->desc02()->m1E((PlacedObject*)self->created, &basis);
    }
}

// Switches the creator's state (nothing if unchanged): stops its animation player; state 1 starts
// its start animation and sends its notify record a message (kind 4, with its position); state 2
// calls method 0x15 and 0x2F on the created object.
void SetObjectCreatorState(ObjectCreator* self, s32 idx)
{
    if (self->state != idx) {
        if (self->activeHandle != 0) {
            StopAnimationPlayer((AnimationPlayer*)self->activeHandle);
            self->activeHandle = 0;
        }
        self->state = idx;
        void* s2 = 0;
        self->stateTime = g_gameClock[1];
        switch (idx) {
        case 1: {
            void* a2 = self->notifyRecord;
            s2 = self->startAnimation;
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
        if (s2 != 0) CreateAnimationPlayerWithoutPresetTargets((Animation*)s2, self, 0, (AnimationPlayer**)&self->activeHandle, 0.0f, 1.0f);
    }
}

// Next state of the object creator: 1 becomes 2 when its handle's animation has ended; bit 1 of the
// current entry's flags then gives 3 from states 1 and 2.
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

// Selects the pad port and slot to play on; goes to state 1 when idle and to state 3 otherwise.
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

// Steps the vibration pattern player once per frame: in state 2 it counts down the step and total
// times and, at the end of a step, goes on to the next one (wrapping) and sends its two actuator
// bytes to the pad; when the total time is used up it goes to state 3. In states 3 and 4 it stops
// the output while the step time lasts, then changes state (to 1 from state 3).
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

// Starts pad pattern number index of the global pattern table.
void StartPadPatternFromTable(PadPatternPlayer* self, s32 index, f32 time)
{
    StartPadPattern(self, &g_padPatterns[index], time);
}

// Starts a pad pattern when the player is not idle-off, the pattern has steps and pad patterns are
// enabled: stores the pattern and its first delay and enters state 2.
void StartPadPattern(PadPatternPlayer* self, PadPattern* p, f32 f)
{
    if (self->state != 0 && p->count > 0) {
        if (IsPadPatternEnabled(g_saveData) != 0) {
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

// State change of a pad pattern player: state 2 sends the first step's two bytes to the pad, states
// 3 and 4 stop the pad output and set the step time to four frame steps; stores the state.
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

// Sends zeros to the pad's actuators for the player's port and slot, stopping the output.
void StopPadPatternOutput(PadPatternPlayer* self)
{
    u8 bytes[2];
    bytes[0] = 0;
    bytes[1] = 0;
    SetPadActuatorBytes(self->port, self->slot, bytes);
}

// Sets the pad pattern setting to 1 (follow the option flag) when it is still unset.
void InitPadPatternSetting(void)
{
    if (g_padPatternSetting == 0) {
        g_padPatternSetting = 1;
    }
}

// Writes the pad pattern setting into bit 5 of the option flags: 2 clears it, 3 sets it.
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
    ctx->optionFlags &= 0xFFFFFFDF;
    return;
set:
    ctx->optionFlags |= 0x20;
}

// Whether pad patterns are on: setting 2 is always on, 0 and 3 off, 1 follows the inverse of bit 5
// of the option flags.
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
    return ((ctx->optionFlags >> 5) ^ 1) & 1;
}

// Applies the pad pattern setting to bit 5 of the option flags (1 toggles, 2 sets, 3 clears) and
// then records which way the bit is now (3 set, 2 clear).
void TogglePadPatternSetting(GameProgress* self)
{
    s32 g = g_padPatternSetting;
    switch (g) {
    case 1: self->optionFlags = self->optionFlags ^ 0x20; break;
    case 2: self->optionFlags = self->optionFlags | 0x20; break;
    case 3: self->optionFlags = self->optionFlags & 0xFFFFFFDF; break;
    }
    if (self->optionFlags & 0x20) {
        g_padPatternSetting = 3;
        return;
    }
    g_padPatternSetting = 2;
}