// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1D9AC8 to 0x1DDCE0: the rest of class 0x19 (contacts, update, control, screen elements),
// the world (class 0x6C) and its script functions. Its .data runs from 0x275600 to the zeroed
// globals D_00275710 (g_currentWorld) to D_00275728 that close it; its .rodata is the pairs of
// func_001DCD28 (0x24DC98 to 0x24DCA8). Its end is an edge retail proves. Its start is a choice:
// the cut after path_follower_helpers.cpp (that file's head), which no boundary signal shows. It reads
// D_002751D4 and D_002751DC, which path_follower.cpp defines. Its name is ours, after its largest
// family, the world and its script functions; it opens with the rest of the path follower.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "pad_record.h"
#include "deferred_request.h"
#include "list_iter.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "masked_collider.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "world.h"
#include "queued_call.h"
#include "effect.h"
#include "game_progress.h"
#include "buffered_stream.h"
#include "value_range.h"
#include "script_value.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "font.h"
#include "level_entry.h"
#include "message_body.h"
#include "path_curve_object.h"
#include "state_notifier.h"
#include "fpu.h"
#include "scope_marker.h"
#include "object_finder.h"
#include "functions/agent.h"
#include "functions/anim_record.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/child_group_object.h"
#include "functions/class75_list.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/collider_span.h"
#include "functions/display.h"
#include "functions/iop_commands.h"
#include "functions/matrix.h"
#include "functions/object_properties.h"
#include "functions/oscillator.h"
#include "functions/pad_input.h"
#include "functions/path_follower.h"
#include "functions/path_follower_helpers.h"
#include "functions/placed_object.h"
#include "functions/placed_object_model.h"
#include "functions/player_state2.h"
#include "functions/point_graph.h"
#include "functions/screen_element.h"
#include "functions/state_notifier.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/target_lists.h"
#include "functions/value.h"
#include "functions/world_contacts.h"
#include "functions/zone_collider.h"
struct ColliderPose;
struct ParentFrame;
struct PlacedObject;

struct BaseObject;

struct Mat02;


// Types other files define, named by the parameters of their functions declared here.
struct ScaledTransform;

extern f32 g_gameClock[];


void ResetPathFollower(void* self);

extern "C" void* FillMemory(void* p, s32 value, s32 size);

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void ResetPathFollower(PathFollower* self);


void SetCachedVoiceParam(s32 index, s32 value);


void RefreshCachedVoiceParam(s32 i, s32 unused1);


void* TakeCallRecord(World* self);

extern f32 g_gameTime;

void ReleaseCallRecords(World* self, T219CHook* node);

typedef void (*FollowerEffectFn)(void* self, s32 mode, PlacedObject* other);
struct FollowerEffectTarget { FollowerEffectFn* vtbl; };

void FindPathFollowerPathPosition(void* self);

struct NoticeLink { u8 pad[0x50]; void* owner; };
struct CountedNotice { u8 pad0[8]; s32 kind; u8 pad1[0x6CC - 0xC]; NoticeLink* link; };


void AlignBufferedStreamPosition(BufferedStream* self, s32 n);
void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);

void SetListLinkOffset(List01* self, s32 offset);

void UpdateColliderBounds(Collider* self);
void ExpandColliderBoundsBySphere(void* self, void* p, f32 f);

extern u8 D_0026DAAC[];

void SetWorldActiveFollower(World* self, void* v);
void SetPathFollowerMode(PathFollower* self, s32 mode);


s32 ReduceBufferedStreamBytesLeft(BufferedStream* self, s32 n);
s32 ReadBufferedS32(BufferedStream* self);

struct WalkerHolder { u8 pad[0x48]; void* walker; };

s32 AreMenusAndFadeClear(void);

struct MarkStacks;
void MarkPoolLiveEnds(MarkStacks* stacks);
struct ScriptScope;
s32 LookupScriptVariable(ScriptScope* scope, s32 key, s32 flag, ScriptValue* out);
struct R11B008Node;
struct ScriptValue;
void* EvalScriptExpression(ScriptValue* ret, R11B008Node* expr, ScriptScope* scope);
void* AssignScriptVariable(ScriptValue* ret, ScriptScope* scope, s32 key, ScriptValue* value);
extern u8 g_markStacks[];




void ProcessPathFollowerContacts(PathFollower* self);

extern u8 g_scatterController[];

struct ScatterController;
void RaiseScatterLevels(ScatterController* self, f32 amount);

// A quadratic by its three coefficients (func_001DB290).
struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

struct WorldRecord { u8 b; };

extern s32 g_buttonCodeFlags;

void SetIopChannel2Setting(World* self, s32 a, s32 b);
void* AllocateZeroedFrontMemory(s32 size);
void InitContactTables(World* self);
void SetListLinkOffset(List01* self, s32 offset);
void SetWorldGravityZ(World* self, f32 x);

#define SUB(off) ((WorldRecord*)((u8*)self + (off)))

typedef s32 VoiceParamIndex;

s32 GetCachedVoiceParam(s32 index);

extern s32 g_switchedColliderCount;
extern s32 g_padSelectFlags;
extern u8 g_elementStack[];
struct ColoredTriangleSet;
extern ColoredTriangleSet* g_coloredTriangleSet;
extern f32 g_stepScale;
extern s32 D_00261D38;

void StopAllSoundsAndWait(void);
void ResetElementStack(ElementStack* self);
void ResetFrontMemory(void);

struct __attribute__((packed)) PackedWord { s32 v; };

typedef int Quadword __attribute__((mode(TI)));

void *StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
void* StoreQuadword(u128* out, u128 v);
Quadword AddWeightedVectors(Quadword a, Quadword b, Quadword c, Quadword d);

struct BlendRange {
    f32 lo;
    f32 hi;
    void Blend(f32 y, const BlendRange& a, f32 x, const BlendRange& b)
    {
        lo = y * a.lo + x * b.lo;
        hi = y * a.hi + x * b.hi;
    }
};
struct RangeClamp {
    f32 lo;
    f32 hi;
    f32 Clamp(f32 v)
    {
        if (v < lo)
            return lo;
        if (hi < v)
            return hi;
        return v;
    }
};

s32 GetLevelEntryWord(s32 key);

// The four key/value slots after offset 0x44 of a level entry (SetEntrySlotValue, GetEntrySlotValue).
struct EntrySlot { s32 key; s32 value; };
struct EntrySlotTable { u8 pad[0x44]; EntrySlot slots[4]; };

void* GetLevelEntryByKey(s32 key);

s32 ComputeCompletionPercent(GameProgress* progress);

extern void* g_frameCount;
extern void* g_lightingChangeFrame;

f32 ClampToRange(ValueRange* span, f32 x);

void* PushSoundLevel(s32 level);


s32 RandomIntInRange(s32 a, s32 b);

struct ScatterController;
void SetScatterLevel(ScatterController* object, f32 level);

struct SoundLevelEntry;
struct SoundLevelEntry;
void RemoveSoundLevelAndRecompute(SoundLevelEntry* p);

typedef void (*ActiveFollowerFn)(void* self);
struct ActiveFollowerChild { ActiveFollowerFn* vtbl; };

void UnlinkContactTable(Contacts03* node, Contacts03** head);
void PushContactTable(Contacts03* node, Contacts03** head);

void PopStackElement(ElementStack* g);

struct __attribute__((packed)) PackedPageWord { s32 v; };

void SetPauseMenuLayerPage(T217D_6D0* self, s32 mode, s32 value);

s32 ReadBufferedU32(BufferedStream* self);
void SkipBufferedBlock(BufferedStream* self);

struct CloneBatch { s32 count; s32* values; };

struct __attribute__((packed)) PackedCloneBatch { s32 n; void* buf; };

void* AllocateFrontMemory(s32 size);

s32 HasStreamVoice(void);


struct __attribute__((aligned(16))) CurveSample { s32 v[4]; };
struct __attribute__((packed)) PackedCurveColor { s32 v; };
struct CurveFrame { CurveSample pts[10]; PackedCurveColor c; };

struct CurvePoint;
void SampleCurvePoints(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, s32 count,
                       CurvePoint* out, f32 start, f32 end);
struct ClipPoint;
struct PackedColor;
void DrawProjectedLine(ClipPoint* a, ClipPoint* b, PackedColor* c, u8* obj, s32 k);

extern u8 g_previousSoundLevel[];

void SetVolumeChannelFactor(s32 a, s32 b, f32 x);

void* AllocateZeroedFrontMemory(u32 n);

s32 IsPadSelectFlagHeld(World* self);

ConeVolume* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);


typedef u64 UQuadword __attribute__((mode(TI)));
struct __attribute__((aligned(16))) ClipPoint { f32 x, y, z, w; };
struct __attribute__((packed)) PackedColor { s32 v; };
struct SegmentEnd { f32 x, y, z; };
struct SegmentFrame { ClipPoint buf[4]; PackedColor tmp; };

extern SegmentEnd g_projectionScale;
extern SegmentEnd g_projectionOffset;

UQuadword TransformVector4(u8* self, UQuadword q);
s32 ClipSegmentToPlanes(ClipPoint* out);



// How many copies func_001DCD28 makes of the first object of a class.
struct ClassCopyCount { s32 classId; s32 count; };



u32 GetEntryFlags(s32 id);

struct ClipPlane { f32 x, y, z, w; };

f32 g_pushVelocity[4] = { 2000.0f, 0.0f, 2000.0f, 0.0f };
f32 g_pushVelocityShare = 0.5f;
f32 g_pushSpinScale = 0.00200000009f;
f32 D_00275618 = 800.0f;
f32 g_wheelAttachRamp[4] = { 2000.0f, 0.0f, 0.150000006f, 0.0f };
s32 g_coneVolumeMask[4] = { 1, 0, 0, 0 };
f32 g_coneVolumeColor[4] = { 0.0f, 255.0f, 255.0f, 0.0f };
f32 g_coneVolumeFirstAngle = 0;
f32 g_coneVolumeSecondLevel = 255.0f;
f32 g_coneVolumeSecondAngle = 240.0f;
f32 g_coneVolumeThirdLevel = 0;
f32 g_coneVolumeThirdAngle = 180.0f;
Vec02 g_coneVolumeDirection = { -0.2f, 0.3f, -1.0f, 0.0f };
f32 g_coneVolumePosition[4] = { 100.0f, -150.0f, 500.0f, 0.0f };
f32 g_coneVolumeMode1Range[2] = { 500.0f, 2500.0f };
f32 g_coneVolumeMode2Range[2] = { 500.0f, 2500.0f };
f32 g_coneVolumeMode3Range[4] = { 500.0f, 2500.0f, 0.0f, 0.0f };
ClipPlane g_clipVolumePlanes[6] = {
    { 1.0f, 0.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f },
    { 0.0f, -1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 1.0f }
};
World* g_currentWorld = 0;
u32 g_scriptStreamExtras = 0;
u8* D_00275718 = 0;
s32 g_bufferedBlockLoad = 0;
s32 g_bufferedBlockSize = 0;
s32 g_bufferedBlockKey = 0;
s32 g_bufferedBlockStart = 0;


// For each contact of the follower with another body that it has not pushed yet, gives that body a
// push (the g_pushVelocity turned into the follower's frame plus half its velocity, and a spin from
// it) and records it as pushed.
void ProcessPathFollowerContacts(PathFollower* self)
{
    Vec02 pos;
    Vec02 spin;
    if (self->contacts == 0) {
        return;
    }
    for (Contact03* c = self->contacts; c != 0; c = c->next) {
        s32 side = c->end[0].body == (Collider*)self;
        Collider* other = c->end[side].body;
        s32 i;
        for (i = 0; i < self->pushedCount; i++) {
            if (other == self->pushed[i]) {
                break;
            }
        }
        if (i < self->pushedCount) {
            continue;
        }
        TransformDirectionBetweenFrames(self, 0, (Vec02*)g_pushVelocity, &pos);
        Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(self->v150), Vu0::ScalarAtCall(g_pushVelocityShare));
        Vu0::Set(spin, Vu0::MulX(Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(pos)), Vu0::ScalarAtCall(g_pushSpinScale)));
        other->desc02()->m20(other, &pos);
        other->desc02()->m21(other, &spin);
        if ((u32)self->pushedCount < 8) {
            self->pushed[self->pushedCount++] = other;
        }
        if (IsObjectOfKind(other, 0x19)) {
            ((PathFollower*)other)->pushedTime = g_gameClock[1];
        } else if (IsObjectOfKind(other, 8)) {
            ChangeAgentState((Agent*)other, 0x10, 0);
        }
    }
    FreePooledContactChain(self->world, self->contacts);
    self->contacts = 0;
}

// Per-frame update of the path follower: updates it as a switched collider, then, in mode 1, its
// pace, its movement along the path and heading, and in all modes its sound, steering, wheel
// particles, entry advance and contacts; notes when it is upright.
void UpdatePathFollower(PathFollower* self, f32 t)
{
    s32 local = 0;
    UpdateSwitchedCollider(self, t);
    if (self->mode != 1) {
        if (self->mode < 2) {
            if (self->mode == 0) {
                self->targetSpeed = 0;
            }
        }
    } else {
        UpdatePathFollowerPace(self);
        AdvancePathFollowerAlongPath(self, &local);
        ComputePathFollowerHeadingTarget(self);
    }
    UpdatePathFollowerSound(self, t);
    SteerPathFollower(self);
    EmitPathFollowerWheelParticles(self);
    AdvancePathFollowerEntry(self, local);
    ProcessPathFollowerContacts(self);
    if (self->rot.r[2].z > 0.5f) {
        self->uprightTime = g_gameTime;
    }
    if (self->mode != 0) {
        ClearRootTries(self);
    }
}

extern s32 g_movieChecksumFailed;
extern float D_002751DC;
extern s32 D_002751D4;

// The pad's control of a path follower: its heading from the stick, its pace in mode 2 and the
// button 0x80, then by kind the race places (0) or the end of the round (1).
void ControlPathFollower(PathFollower* self, PadRecord* pad, f32 dt)
{
    if (self->mode != 1) {
        if (0.0f < pad->stickMagnitude) {
            ComputeCameraRelativeStickHeading(g_camera, pad, 0, &self->targetHeading);
        } else {
            self->targetHeading = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
        }
    }
    if (self->mode == 2) {
        self->targetSpeed = self->maxSpeed * pad->stickMagnitude;
        if (g_movieChecksumFailed != 0) {
            self->targetSpeed = self->targetSpeed * 0.4f;
        }
        if ((pad->flags & 0x80) != 0) {
            ClearPadPressedBits(pad, 0x80);
            switch (self->kind) {
            case 0:
                if (self->lapsLeft > 0 && D_002751DC < g_gameTime - self->lapTime) {
                    CountDownPathFollowerLap(self);
                    StartSoundEffect(0x5A, 0, 0, 0, 0.0f, 0.0f, 2.0f, -0.25f, 0.0f, 0, 0);
                } else {
                    StartSoundEffect(0x73, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                }
                break;
            case 1:
                if (self->walkerGraph != 0) {
                    SetStateWalkerTarget((StateWalker*)self->walker, 0x485);
                    self->pushedCount = 0;
                }
                break;
            case 2:         // a kind with nothing to do: retail's compare tree has it
                break;
            }
        }
    }
    HandleStepSequenceSkipButtons(self, pad);
    if (self->activeZone != 0) {
        self->targetSpeed = self->activeZone->maxSpeed <? self->targetSpeed;
    }
    switch (self->kind) {
    case 0: {
        WalkerHolder* r = (WalkerHolder*)FindFirstObjectById(self->world, 5, 0x42C, 0);
        if (r != 0) {
            void* dev = r->walker;
            s32 code;
            GetStateWalkerTargetKey((StateWalker*)dev, &code);
            if (code == -1) {
                GetStateWalkerCurrentKey((StateWalker*)dev, &code);
            }
            if (code < 0x431) {
                if (code >= 0x42F && 0.5f < g_gameClock[1] - self->placeChangeTime && self->path != 0) {
                    PathFollower* found[16];
                    s32 n = GatherObjectsById(self->world, 5, 0x19, 0, 0x10, found);
                    s32 place = 1;
                    for (s32 i = 0; i < n; i++) {
                        if (self != found[i] && IsPathFollowerAhead(found[i], self) != 0) {
                            place++;
                        }
                    }
                    if (place != self->place || n != self->placeCount) {
                        self->place = place;
                        self->placeCount = n;
                        self->placeChangeTime = g_gameClock[1];
                    }
                }
            }
        }
        break;
    }
    case 1: {
        WalkerHolder* r = (WalkerHolder*)FindFirstObjectById(self->world, 5, 0x42C, 0);
        if (r != 0) {
            void* dev = r->walker;
            s32 code;
            GetStateWalkerTargetKey((StateWalker*)dev, &code);
            if (code == -1) {
                GetStateWalkerCurrentKey((StateWalker*)dev, &code);
            }
            if (code == 0x42F) {
                if (g_firstTallyCaption.own >= D_002751D4) {
                    SetStateWalkerTarget((StateWalker*)dev, 0x432);
                } else if (g_secondTallyCaption.own >= D_002751D4) {
                    SetStateWalkerTarget((StateWalker*)dev, 0x431);
                    RaiseScatterLevels((ScatterController*)g_scatterController, 1.0f);
                }
            }
        }
        break;
    }
    case 2:             // as above
        break;
    }
}

// Shows or hides the follower's on-screen captions (two count captions and two tally captions)
// according to its kind: kind 0 shows the counts while a state walker is at a key in 0x42F..0x430
// and menus and fades are clear, kind 1 shows the tally when menus and fades are clear.
void UpdatePathFollowerScreenElements(PathFollower* self)
{
    s32 a = 0;
    s32 b = 0;
    switch (self->kind) {
    case 0: {
        WalkerHolder* r = (WalkerHolder*)FindFirstObjectById(self->world, 5, 0x42C, 0);
        if (r != 0) {
            void* dev = r->walker;
            s32 code;
            GetStateWalkerTargetKey((StateWalker*)dev, &code);
            if (code == -1) {
                GetStateWalkerCurrentKey((StateWalker*)dev, &code);
            }
            if (code < 0x431) {
                if (code >= 0x42F) {
                    a = AreMenusAndFadeClear();
                }
            }
        }
        break;
    }
    case 1:
        b = AreMenusAndFadeClear();
        break;
    }
    if (a != 0) {
        D_0026D848.vt->m14(&D_0026D848);
        g_pathFollowerFirstCountCaption.vt->m14(&g_pathFollowerFirstCountCaption);
        g_pathFollowerSecondCountCaption.vt->m14(&g_pathFollowerSecondCountCaption);
    } else {
        D_0026D848.vt->m15(&D_0026D848);
        g_pathFollowerFirstCountCaption.vt->m15(&g_pathFollowerFirstCountCaption);
        g_pathFollowerSecondCountCaption.vt->m15(&g_pathFollowerSecondCountCaption);
    }
    if (b != 0) {
        g_firstTallyCaption.vt->m14(&g_firstTallyCaption);
        g_secondTallyCaption.vt->m14(&g_secondTallyCaption);
    } else {
        g_firstTallyCaption.vt->m15(&g_firstTallyCaption);
        g_secondTallyCaption.vt->m15(&g_secondTallyCaption);
    }
}

// Advances the follower's contact stamp by one, which makes its current contacts count as
// released.
void ReleasePathFollowerContacts(PathFollower* self) { self->contactStamp++; }

struct FaceRef;
struct PooledContact;
struct MaskedCollider;

// Whether a lies below b along axis (their dot products with it).
static inline s32 IsLowerAlong(const Vec02& a, const Vec02& b, const Vec02& axis)
{
    return Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(a), Vu0::Q(axis))) < Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(b), Vu0::Q(axis)));
}

// Collision of the path follower's four wheels with another collider that is flagged as ground
// (flag bit 40 or its class flag 0x10): for each wheel it sweeps a segment from the wheel's last
// position to its new one, lowered by the wheel radius (front pair and rear pair differ), in the
// follower's frame and looks for a hit.
void CollidePathFollowerWithObject(PathFollower* self, Collider* other, s32 a2, void* a3, void* a4)
{
    if ((other->flags538 & ((u64)0x8000 << 40)) != 0 || (((u32*)other->desc)[2] & 0x10) != 0) {
        for (u32 i = 0; i < 4; i++) {
            Slot19* slot = &self->wheels[i];
            s32 first = (s32)i < 2;
            Vec02 p;
            Vec02 q;
            Vec02 k;
            ColliderSpan hit;
            p = *(Vec02*)((u8*)slot->obj8 + 0x40);
            p.z = p.z - (first ? self->frontWheelRadius : self->rearWheelRadius);
            TransformPointBetweenFrames(self, 0, &p, &p);
            q = slot->obj->v190;
            q.z = q.z - (first ? self->frontWheelRadius : self->rearWheelRadius);
            TransformPointBetweenFrames(self, 0, &q, &q);
            u128* pp = &Vu0::Q(p);
            u128 base = *pp;
            f32 r = first ? self->frontWheelRadius : self->rearWheelRadius;
            u128 d = Vu0::Sub(Vu0::Q(p), Vu0::Q(q));
            Vu0::Q(k) = Vu0::FromFloat(r);
            *pp = Vu0::MulAddX(base, Vu0::DivX(d, Vu0::Sqrt(Vu0::Dot(d, d))), Vu0::Q(k));
            if (CollectColliderSpansInTree(other, a4, &p, &q, 1, &hit) > 0 && hit.time[0] > 0.0f) {
                if (slot->contactStamp != self->contactStamp + 1 || IsLowerAlong(slot->contactPoint, *(Vec02*)&hit.q[0], self->rot.r[2])) {
                    slot->contactStamp = self->contactStamp + 1;
                    slot->contactPoint = *(Vec02*)&hit.q[0];
                    slot->contactDirection = *(Vec02*)&hit.q[2];
                    ComputeObjectMotionInFrame(other, 0, &slot->contactPoint, &slot->contactVelocity, 0, 0, 0);
                }
                if (other->id != 1) {
                    if ((other->desc->flags & 0x20) != 0) {
                        if (((ChildGroupObject*)other)->contactMode == 0) {
                            StartChildGroupDelay((ChildGroupObject*)other, 0.0f);
                        }
                    } else if (IsObjectOfKind(other, 0x25) != 0 && ((MassScalingCollider*)other)->busy == 0 && IsObjectAccepted((MaskedCollider*)other, self) != 0) {
                        if (((MassScalingCollider*)other)->sel6C4 != -1) {
                            SetColliderTurnAnchorPreset(other, ((MassScalingCollider*)other)->sel6C4);
                        }
                        if (((MassScalingCollider*)other)->sel6C8 != -1) {
                            SetColliderMoveAnchorPreset(other, ((MassScalingCollider*)other)->sel6C8);
                        }
                        f32 m = other->mass;
                        ((MassScalingCollider*)other)->busy = 1;
                        ((MassScalingCollider*)other)->cur = self;
                        other->mass = m * ((MassScalingCollider*)other)->scale;
                    }
                }
            }
        }
    } else if (self->contactMesh != 0 && IsObjectAttached((Collider*)self->contactMesh) != 0) {
        if ((other->flags538 & ((u64)0x8000 << 25)) != 0) {
            Collider* c = (Collider*)self->contactMesh;
            AddMeshContacts(other, other->radius3CC, &other->v140, c, c->tree.count, (FaceRef*)c->tree.nodes, 0, (PooledContact**)&self->contacts);
        } else if (a3 != 0) {
            CreateMeshPairContacts((Collider*)self->contactMesh, other, a2, (FaceRef*)a3, (u8*)a4, (PooledContact**)&self->contacts);
        }
    }
}

ASM_FUNC(func_001DA6E0);

typedef u64 Quad_1DA7E0 __attribute__((mode(TI)));
struct Vec02;
struct RampProfile;
Quad_1DA7E0 ApproachPointWithRamp(u128 from, u128 to, f32 limit, RampProfile* ramp, Vec02* vel);

static inline void MulMatInto(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    out->r[0] = r.r[0];
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    out->r[1] = r.r[1];
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    out->r[2] = r.r[2];
}

// Updates the follower's attachment frames, then turns each of its four wheels: advances its spin
// angle, places it on its contact point (raised by the wheel radius) when it touched the ground
// this frame, or eases it toward the object's position, and builds the wheel's matrix from the
// steering tilt (front pair only) and the spin.
void UpdatePathFollowerAttachmentFrames(PathFollower* self, ParentFrame* frame)
{
    u32 i = 0;
    UpdateAttachmentFrames(self, frame);
    for (; i < 4; i++) {
        Slot19* s = &self->wheels[i];
        Mat02 world;
        Mat02 tilt;
        Mat02 turn;
        s->turnAngle += s->turnRate * g_gameClock[2];
        if (s->contactStamp == self->contactStamp) {
            TransformPointBetweenFrames(0, self, &s->contactPoint, &s->placedPos);
            s->placedPos.z = s->placedPos.z + (((s32)i < 2) ? self->frontWheelRadius : self->rearWheelRadius);
        } else {
            *(Quad_1DA7E0*)&s->placedPos = ApproachPointWithRamp(*(Quad_1DA7E0*)&s->placedPos, *(Quad_1DA7E0*)&s->obj->v190, g_gameClock[2], (RampProfile*)g_wheelAttachRamp, 0);
        }
        if ((s32)i < 2) {
            BuildAxisAngleMatrix(&g_unitZVector, &tilt, self->steerAngle);
        } else {
            tilt = g_identityMatrix;
        }
        BuildAxisAngleMatrix(&g_unitYVector, &turn, s->turnAngle);
        MulMatInto(&world, tilt, turn);
        if (s->obj2 != 0) {
            Vec02 moved;
            TransformPointBetweenFrames((PlacedObject*)s->obj->parent, (PlacedObject*)s->obj2->parent, &s->placedPos, &moved);
            s->obj2->desc02()->m1D(s->obj2, &moved);
        }
        s->obj->desc02()->m1D(s->obj, &s->placedPos);
        s->obj->desc02()->m1E(s->obj, &world);
    }
}

struct DrawScale {
    u8 pad00[0x40];
    f32 f40;
};


// Draws the follower as a collider, then its body object (turned upright, scaled by the largest
// axis lengths, placed at its own offset) and, if they exist, the front and rear beams.
void DrawPathFollower(PathFollower* self, void* a, DrawScale* b)
{
    DrawCollider(self, a, b);
    if (self->bodyObject != 0) {
        f32 len[3];
        DrawTransform m;
        Vec02 pos;
        Mat02 rot;
        for (s32 i = 0; i < 3; i++) {
            Vu0::StoreX(len[i], Vu0::Length(Vu0::Q(self->m110.r[i])));
        }
        BuildPlacedObjectTransform(self, (Quad16*)b, (ScaledTransform*)&m);
        RotateMatrixUpright(&self->m110, 0, &rot);
        f32 sx = len[2] >? len[0];
        f32 sy = len[2] >? len[1];
        Vu0::Q(rot.r[0]) = Vu0::MulX(Vu0::Q(rot.r[0]), Vu0::Scalar(sx));
        Vu0::Q(rot.r[1]) = Vu0::MulX(Vu0::Q(rot.r[1]), Vu0::Scalar(sy));
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(self->v140), Vu0::Rotate(rot, Vu0::Q(self->bodyObject->pos)));
        BuildMatrixFromRotationAndTranslation(&pos, &rot, (Mat4A*)&m);
        self->bodyObject->desc02()->m26(self->bodyObject, a, &m);
    }
    if (self->frontBeam != 0 || self->rearBeam != 0) {
        Vec02 q[4];
        for (s32 i = 0; i < 4; i++) {
            TransformPointBetweenFrames(self, 0, &self->wheels[i].placedPos, &q[i]);
        }
        if (self->frontBeam != 0) {
            DrawBeamBetweenPoints((PlacedObject*)self->frontBeam, (PlacedObject*)a, &q[0], &q[1], 1.0f, b != 0 ? b->f40 : 1.0f);
        }
        if (self->rearBeam != 0) {
            DrawBeamBetweenPoints((PlacedObject*)self->rearBeam, (PlacedObject*)a, &q[2], &q[3], 1.0f, b != 0 ? b->f40 : 1.0f);
        }
    }
}

// Updates the collider bounds and expands them by a sphere around each of the four wheel
// objects (front wheels use the front radius, rear ones the rear radius).
void UpdatePathFollowerBounds(PathFollower* self)
{
    u32 i;
    Quad16 q;
    UpdateColliderBounds(self);
    for (i = 0; i < 4; i++) {
        Slot19* slot = &self->wheels[i];
        if (slot->obj != 0) {
            f32 f;
            q = *(Quad16*)&slot->obj->v190;
            TransformPointBetweenFrames(self, 0, (Vec02*)&q, (Vec02*)&q);
            f = ((s32)i < 2) ? self->frontWheelRadius : self->rearWheelRadius;
            ExpandColliderBoundsBySphere(self, &q, f);
        }
    }
}

// Starts an effect through the follower's partner (after resetting the partner's main clip),
// or, with no partner, through the base switched collider.
void StartPathFollowerEffect(PathFollower* self, s32 a, PlacedObject* b)
{
    if (((FollowerEffectTarget*)self->partner) != 0) {
        SetAgentMainClip((Agent*)(((FollowerEffectTarget*)self->partner)), 0);
        FollowerEffectTarget* t = ((FollowerEffectTarget*)self->partner);
        t->vtbl[82](t, a, b);
    } else {
        StartSwitchedColliderEffect(self, a, b);
    }
}

// Finds where the follower is on its path: the nearest path time and point, the distance along the
// path and the signed side offset from it (the dot of the offset with the side direction).
void FindPathFollowerPathPosition(PathFollower* self)
{
    if (self->path != 0) {
        Vec02 p;
        Vec02 tangent;
        Vec02 side;
        PathCurve* o = self->path->curve;
        if (o->vt->m11) {
            o->vt->m11(o, self->pathTime, (u8*)&self->pos, 0, (f32*)&p, (f32*)&tangent, &self->pathTime, 0);
        }
        u128 c = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(tangent));
        Vu0::Q(side) = Vu0::DivX(c, Vu0::Length(c));
        self->pathDistance = self->path->curve->vt->m05(self->path->curve, self->pathTime);
        Vu0::StoreX(self->sideOffset, Vu0::Dot(Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(p)), Vu0::Q(side)));
    }
}

// Recomputes the collider's frame, then the follower's position on its path.
void RecomputePathFollowerFrame(PathFollower* self)
{
    RecomputeColliderFrame(self);
    FindPathFollowerPathPosition(self);
}

void CapturePathFollowerPose(PathFollower* self, ColliderPose* pose)
{
    CaptureColliderPose(self, pose);
}

// After the base handling, an activation points the two count captions at the follower's lap
// and place counters and makes it the world's active follower; a deactivation puts a follower
// in mode 2 back to mode 0.
void HandlePathFollowerActivation(PathFollower* self, void* v)
{
    HandleSwitchedColliderActivation(self, v);
    if (v != 0) {
        T217D_E30* a = &g_pathFollowerFirstCountCaption;
        *(void**)(D_0026DAAC) = (u8*)&self->lapsLeft;
        T217D_E30* b = &g_pathFollowerSecondCountCaption;
        a->target = &self->lap;
        a->limit = &self->lapCount;
        b->target = &self->place;
        b->limit = &self->placeCount;
        SetWorldActiveFollower(self->world, self);
    } else {
        if (self->mode == 2) {
            SetPathFollowerMode(self, 0);
        }
    }
}

// After the base switched-collider handling, on notification 0xE of kind 0x426 counts one for
// the first or the second caption counter (by which follower the notice's link belongs to)
// while both are under their limit.
void HandlePathFollowerNotification(PathFollower* self, s32 code, CountedNotice* rec)
{
    HandleSwitchedColliderNotification(self, code, rec);
    if (code == 0xE && rec->kind == 0x426) {
        T217D_E30* a = &g_firstTallyCaption;
        s32 lim = D_002751D4;
        if (a->own < lim) {
            T217D_E30* b = &g_secondTallyCaption;
            if (b->own < lim) {
                if (rec->link->owner == self) {
                    a->own = a->own + 1;
                } else {
                    b->own = b->own + 1;
                }
            }
        }
    }
}

// Gives the follower a path curve: finds its start time and position on it, takes the path length
// and the path length position of every marker that is an item (kind 0).
void SetPathFollowerPath(PathFollower* self, PathCurveObject* arg)
{
    self->path = arg;
    PathCurve* o = arg->curve;
    if (o->vt->m10) o->vt->m10(o, (u8*)&self->pos, 0, 0, 0, &self->pathTime, 0);
    FindPathFollowerPathPosition(self);
    self->sideTarget = self->sideOffset;
    self->pathLength = self->path->curve->vt->m08(self->path->curve);
    for (s32 i = 0; i < self->markerCount; i++) {
        PathMarker* e = &self->markers[i];
        if (e->kind == 0) {
            s32 loc[4];
            GetObjectWorldPosition((BaseObject*)e->item, (Vec02*)loc);
            PathCurve* o2 = self->path->curve;
            if (o2->vt->m10) o2->vt->m10(o2, loc, 0, 0, 0, 0, &e->pathLength);
        }
    }
}

// Sets the follower's second path object and asks its curve for the position along it nearest
// the follower, stored at +0x84C.
void SetPathFollowerSecondPath(u8* self, PathCurveObject* obj)
{
    s32 loc[4];
    PathCurve* inner;

    *(PathCurveObject**)(self + 0x848) = obj;
    inner = obj->curve;
    if (inner->vt->m10 != 0) {
        inner->vt->m10(inner, self + 0x100, 0, loc, 0, (f32*)(self + 0x84C), 0);
    }
}

// Adds an object as a passive marker (kind 0, at most 16) to the follower's circular marker
// list; with a path set, also asks the path's curve for the object's position along it (stored
// in the marker's pathLength).
void AddPathFollowerEntry(PathFollower* self, void* item)
{
    if (item == 0) {
        return;
    }
    s32 n = self->markerCount;
    if ((u32)n >= 16) {
        return;
    }
    self->markerCount = n + 1;
    PathMarker* e = &self->markers[n];
    e->item = item;
    e->kind = 0;
    if (self->firstMarker == 0) {
        self->currentMarker = e;
        self->firstMarker = e;
        e->next = e;
    } else {
        e->next = self->firstMarker->next;
        self->firstMarker->next = e;
        e->index = e->next->index + 1;
    }
    if (self->path != 0) {
        Quad16 tmp;
        GetObjectWorldPosition((BaseObject*)item, (Vec02*)&tmp);
        PathCurve* o = self->path->curve;
        void (*fn)(PathCurve*, void*, void*, void*, void*, f32*, f32*) = o->vt->m10;
        if (fn != 0) {
            fn(o, &tmp, 0, 0, 0, 0, &e->pathLength);
        }
    }
}

// Adds an object as an active marker (kind 1, at most 16) with two floats and two words of
// parameters.
void AddPathFollowerActiveEntry(PathFollower* self, void* a, f32 x, f32 y, s32 b, s32 c) { if (a && (u32)self->markerCount < 16) { PathMarker* e = &self->markers[self->markerCount]; self->markerCount++; e->item = a; e->kind = 1; e->x = x; e->y = y; e->b = b; e->c = c; } }

// Changes the follower's mode (recording the time of the change); mode 2 also makes it the
// active switched collider.
void SetPathFollowerMode(PathFollower* self, s32 mode)
{
    if (mode != self->mode) {
        *(s32*)((u8*)self + 0xB34) = mode;
        self->modeTime = g_gameTime;
        if (mode == 2 && self != GetActiveSwitchedCollider()) {
            ActivateSwitchedCollider(self);
        }
    }
}

// Puts the follower back at the start: lap 1, the first marker, the timers at -10 (long ago) and
// the pace blend recomputed from the current entry's time (dt).
void ResetPathFollower(PathFollower* self)
{
    self->lap = 1;
    self->currentMarker = self->firstMarker;
    self->lapsLeft = 0;
    self->lapTime = -10.0f;
    self->paceChangeTime = -10.0f;
    self->pushedTime = -10.0f;
    self->placeChangeTime = -10.0f;
    G27C230* rec = g_currentEntry;
    f32 t = ((QuadraticCurve*)&self->paceBlendCurve)->Eval(rec->dt);
    f32 l = g_unitRange.lo;
    f32 h = g_unitRange.hi;
    f32 x;
    if (t < l)
        x = l;
    else if (h < t)
        x = h;
    else
        x = t;
    f32 y = 1.0f - x;
    u8* p630 = self->firstEnd;
    u8* p650 = self->secondEnd;
    u8* p670 = self->blendedEnd;
    Quadword a, b, c, d;
    Quadword a2, b2, c2, d2;
    StoreFloatAsQuadword((u128*)&a, y);
    a2 = a;
    CopyQuadword((u128*)&b, p630);
    b2 = b;
    StoreFloatAsQuadword((u128*)&c, x);
    c2 = c;
    CopyQuadword((u128*)&d, p650);
    d2 = d;
    StoreQuadword((u128*)p670, AddWeightedVectors(a2, b2, c2, d2));
    ((BlendRange*)&self->paceMin)->Blend(y, *(BlendRange*)&self->firstRangeLo, x, *(BlendRange*)&self->secondRangeLo);
    f32 r = ((RangeClamp*)&self->paceMin)->Clamp(*(f32*)p670);
    self->paceTarget = r;
    self->pace = r;
}

LINKER_REMNANT(func_001DB448);

ASM_FUNC(func_001DB460);

// Sets the link offset (0xC) of each of the world's 0x200 hash lists.
void InitWorldHashLists(u8* self)
{
    u32 i;
    for (i = 0; i < 0x200; i++) {
        SetListLinkOffset((List01*)(self + 0x84 + i * 0xC), 0xC);
    }
}

// Sets up a world's memory: the two big buffers, the contact tables and the many fixed-size slot
// pools (each by its slot size and count), then the world's lists and default values.
void InitWorldPools(World* self)
{
    f32 x;
    InitObject(self);
    SetIopChannel2Setting(self, 0, 0);
    self->buf1AD8 = (void*)AllocateFrontMemory(0x4800);
    self->buf1ADC = AllocateZeroedFrontMemory(0x10000);
    InitContactTables(self);
    InitSlotPool(&self->pool1AF0, 0x10, 0x400);
    InitSlotPool(&self->pool1AFC, 0xE0, 0x100);
    InitSlotPool(&self->pool1B08, 0x10, 0x80);
    InitSlotPool(&self->pool1B14, 0x14, 0x400);
    InitSlotPool(&self->pool1B2C, 0x140, 0x180);
    InitAlignedSlotPool(&self->pool1B40, 0x10C0, 0x80);
    InitSlotPool((Pool6C*)(SUB(0x1B4C)), 0x580, 0x20);
    InitSlotPool(&self->pool1B58, 0xEC, 0x100);
    InitSlotPool(&self->pool1B20, 0xD0, 0x400);
    InitSlotPool((Pool6C*)(SUB(0x1BA0)), 0x90, 0x80);
    InitSlotPool(&self->pool1BB8, 0xC, 0x20);
    InitSlotPool(&self->pool1B88, 0x40, 0x100);
    InitSlotPool(&self->pool1BF4, 0x2E0, 0x20);
    InitSlotPool(&self->pool1BD0, 0x70, 0x20);
    InitSlotPool((Pool6C*)(SUB(0x1C0C)), 0x8, 0x80);
    InitSlotPool((Pool6C*)(SUB(0x1C18)), 0x14, 0x100);
    self->regroupObjects = (PlacedObject**)AllocateFrontMemory(0x1000);
    SetListLinkOffset((List01*)(SUB(0x48)), 0x1C);
    SetListLinkOffset((List01*)(SUB(0x54)), 0x48);
    SetListLinkOffset((List01*)(SUB(0x78)), 0x48);
    SetListLinkOffset((List01*)(SUB(0x60)), 0x40);
    SetListLinkOffset((List01*)(SUB(0x6C)), 0x414);
    SetListLinkOffset((List01*)(SUB(0x3C)), 0x2D0);
    SetListLinkOffset((List01*)(SUB(0x1B64)), 0x34);
    SetListLinkOffset((List01*)(SUB(0x1B70)), 0x34);
    SetListLinkOffset((List01*)(SUB(0x1B7C)), 0x34);
    SetListLinkOffset((List01*)(SUB(0x1B94)), 0x10);
    SetListLinkOffset((List01*)(SUB(0x1BAC)), 0x64);
    SetListLinkOffset((List01*)(SUB(0x1BC4)), 0x4);
    SetListLinkOffset((List01*)(SUB(0x1BE8)), 0x410);
    SetListLinkOffset((List01*)(SUB(0x1C00)), 0xB8);
    SetListLinkOffset((List01*)(SUB(0x1BDC)), 0x64);
    SetListLinkOffset((List01*)(SUB(0x1C3C)), 0x2DC);
    SetListLinkOffset((List01*)(SUB(0x1C48)), 0x5DC);
    SetListLinkOffset((List01*)(SUB(0x1C54)), 0x374);
    SetListLinkOffset((List01*)(SUB(0x1C60)), 0x600);
    SetListLinkOffset((List01*)(SUB(0x1C6C)), 0x90);
    SetListLinkOffset((List01*)(SUB(0x1C78)), 0x56C);
    SetListLinkOffset((List01*)(SUB(0x1C84)), 0x50);
    SetListLinkOffset((List01*)(SUB(0x1C90)), 0x38);
    SetListLinkOffset((List01*)(SUB(0x1C9C)), 0x38);
    SetListLinkOffset((List01*)(SUB(0x1CA8)), 0xAF0);
    SetListLinkOffset((List01*)(SUB(0x1CB4)), 0x630);
    SetListLinkOffset((List01*)(SUB(0x1CC0)), 0x630);
    SetListLinkOffset((List01*)(SUB(0x1C24)), 0xC);
    SetListLinkOffset((List01*)(SUB(0x1C30)), 0xC);
    SetListLinkOffset((List01*)(SUB(0x1CCC)), 0xC10);
    SetListLinkOffset((List01*)(SUB(0x1CD8)), 0x34);
    x = -1500.0f;
    if (g_buttonCodeFlags & 4) {
        x = -900.0f;
    }
    SetWorldGravityZ(self, x);
    self->fillRed = 0x10;
    self->fillGreen = 0x10;
    self->fillBlue = 0x40;
    self->f1D68 = 50.0f;
    self->soundBank = -1;
    self->stagedBank = 0;
    self->f2308 = 15.0f;
    self->timerDuration = 180.0f;
    self->value = 1.0f;
    self->valueTarget = 1.0f;
    self->f2354 = 1;
    self->flagBits = 0xF03FFFFF;
}

// Tears down the world's global state before another one loads: switched colliders, the player and
// pad routing, the camera, object lists, sounds, screen resources, the script pools and front
// memory, and clears a range of globals.
void ResetWorldSubsystems(World* a0)
{
    if (a0 != 0) {
        ActivateSwitchedColliderIndex(-1);
        g_switchedColliderCount = 0;
        g_player = 0;
        g_padSelectFlags = 0;
        UpdatePadRouting();
        ClearCameraObjectList(g_camera);
        ClearClass75List();
        ClearPointObjectList();
        ClearTargetVectorList();
        ClearObjectLists();
        StopAllSoundsAndWait();
        ResetScreenResources();
        ShutDownScriptValuePools();
        ResetElementStack((ElementStack*)g_elementStack);
        ResetFrontMemory();
        u8* c = (u8*)&D_0026CE48;
        u8* e = (u8*)&g_timerElement;
        g_camera = 0;
        g_coloredTriangleSet = 0;
        g_stepScale = 1.0f;
        ((PackedWord*)(c + 0x274))->v = 0;
        ((PackedWord*)(e + 0x280))->v = 0;
        D_00261D38 = 0;
        *(s32*)(c + 0x278) = 0;
        *(s32*)(e + 0x28C) = 0;
    }
}

// Reads the header of a block from a buffered stream (two ints, a size and a key, in the stream's
// mode) and allocates front memory of that size for the block, adjusting the bytes left to read.
void ReadBufferedBlockHeader(s32 a0, BufferedStream* self)
{
    s32 s2 = a0;
    s32 s3;
    s32 s0;
    if (self->mode == 1) {
        if (s2 == 0) {
            ReduceBufferedStreamBytesLeft(self, g_bufferedBlockStart);
            self->bytesToRead -= g_bufferedBlockStart;
        }
        s3 = ReadBufferedS32(self);
        s0 = ReadBufferedS32(self);
    } else {
        s3 = ReadBufferedS32(self);
        s0 = ReadBufferedS32(self);
        if (s0 != g_bufferedBlockKey) s2 = 1;
        if (s2 == 0) {
            s32 v = self->bytesToRead - g_bufferedBlockStart;
            self->bytesToRead = (s2 < v) ? v : 0;
        }
    }
    u8* r = (u8*)AllocateFrontMemory(s3);
    g_bufferedBlockKey = s0;
    g_bufferedBlockSize = s3;
    D_00275718 = r;
    g_bufferedBlockLoad = s2;
}

// When a block load is wanted, notes where the block starts, aligns to 16 bytes and reads the
// block's bytes into its buffer.
void ReadBufferedBlockBody(BufferedStream* self)
{
    if (g_bufferedBlockLoad != 0) {
        g_bufferedBlockStart = self->bytesToRead;
        AlignBufferedStreamPosition(self, 0x10);
        ReadBufferedStreamBytes(self, g_bufferedBlockSize, D_00275718);
    }
}

// Sets the world's gravity vector to (0, 0, z).
void SetWorldGravityZ(World* self, f32 z)
{
    Vu0::Q(self->gravity) = Vu0::FromFloats(0.0f, 0.0f, z);
}

void SetCachedVoiceParamBuiltin(void* self, s32 a, s32 b)
{
    SetCachedVoiceParam(a, b);
}

s32 GetCachedVoiceParamBuiltin(void* unused, s32 index)
{
    return GetCachedVoiceParam(index);
}

void* RefreshCachedVoiceParamBuiltin(void* unused, s32 a1, s32 a2)
{
    RefreshCachedVoiceParam(a1, a2);
}

// True for an object whose descriptor has flag 2 when the world already holds 0xF7 or more
// bodies and value is 0.
s32 IsWorldBodyLimitReached(World* self, BaseObject* obj, u32 value) { return (obj->desc->flags & 2) && self->count38 >= 0xF7 && value == 0; }

// Takes a 16-byte attach record from the world's pool, zeroed.
void* TakeAttachRecord(World* self)
{
    void* p = TakePoolSlot(&self->pool1B08);
    FillMemory(p, 0, 16);
    return p;
}

// Gives a chain of attach records (linked through nextOwn) back to the world's attach pool.
void ReleaseAttachRecords(World* self, Attach03* node)
{
    if (node) {
        do {
            Attach03* next = node->nextOwn;
            PushFreeSlot(&self->pool1B08, node);
            node = next;
        } while (node);
    }
}

// Takes a 0x14-byte call record from the world's pool, zeroed.
void* TakeCallRecord(World* self)
{
    void* p = TakePoolSlot(&self->pool1B14);
    FillMemory(p, 0, 0x14);
    return p;
}

// Gives a chain of call records back to the world's call-record pool.
void ReleaseCallRecords(World* self, T219CHook* node)
{
    while (node != 0) {
        T219CHook* next = node->next;
        PushFreeSlot(&self->pool1B14, node);
        node = next;
    }
}

QueuedCall* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);

// Queues a call unless an identical one is already waiting in the world's queue.
void AppendQueuedCallOnce(World* self, void* a1, void* a2, s32 a3, s32 a4)
{
    QueuedCall* n = self->queuedCallHead;
    if (n != 0) {
        do {
            if (n->code == a1 && n->arg == a2 && n->k2 == a3 && n->k3 == a4) {
                return;
            }
            n = n->next;
        } while (n != 0);
    }
    AppendQueuedCall(self, a1, a2, a3, a4);
}

// Queues a call (code, arg and two more words) at the end of the world's queued-call list, to
// be run by RunQueuedCalls.
QueuedCall* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d)
{
    QueuedCall* e = (QueuedCall*)TakeCallRecord(self);
    e->code = code;
    e->arg = arg;
    e->k2 = c;
    e->k3 = d;
    if (self->queuedCallTail != 0) self->queuedCallTail->next = e;
    else self->queuedCallHead = e;
    self->queuedCallTail = e;
}

// Removes the queued calls that match: mask bits 1, 2, 4 and 8 say which of the call's code, arg
// and two keys must equal the arguments given.
void RemoveQueuedCalls(World* self, u32 mask, void* code, void* arg, s32 k2, s32 k3)
{
    QueuedCall* prev = 0;
    QueuedCall* removed = 0;
    QueuedCall* cur = self->queuedCallHead;
    QueuedCall* next;
    s32 bit;

    if (cur != 0) {
        do {
            next = cur->next;
            bit = 1;
            while (bit < 16) {
                if (mask & bit) {
                    switch (bit) {
                    case 1:
                        if (cur->code != code) goto miss;
                        break;
                    case 2:
                        if (cur->arg != arg) goto miss;
                        break;
                    case 4:
                        if (cur->k2 != k2) goto miss;
                        break;
                    case 8:
                        if (cur->k3 != k3) goto miss;
                        break;
                    }
                }
                bit <<= 1;
            }
            if (prev != 0) {
                prev->next = next;
            } else {
                self->queuedCallHead = next;
            }
            if (next == 0) {
                self->queuedCallTail = prev;
            }
            cur->next = removed;
            removed = cur;
            goto advance;
        miss:
            prev = cur;
        advance:
            cur = next;
        } while (cur != 0);
    }
    ReleaseCallRecords(self, (T219CHook*)removed);
}

// Runs and releases every call queued on the world (AppendQueuedCall), in order, calling fn
// with the call's arg and two keys.
void RunQueuedCalls(World* self)
{
    while (self->queuedCallHead != 0) {
        QueuedCall* node = self->queuedCallHead;
        if (node == self->queuedCallTail) self->queuedCallTail = 0;
        self->queuedCallHead = node->next;
        node->next = 0;
        node->fn(node->arg, node->k2, node->k3);
        ReleaseCallRecords(self, (T219CHook*)node);
    }
}

// Walks the list of delayed script calls kept in a script variable of the world: each entry's time
// is reduced by the elapsed time limit, and the ones that have run out are evaluated (their
// expression) and dropped from the list, which is stored back.
void RunDueDelayedScriptCalls(World* self, f32 limit)
{
    ScriptValue a;
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&a);
    InitScriptValue(&q);
    MarkPoolLiveEnds((MarkStacks*)g_markStacks);
    LookupScriptVariable((ScriptScope*)self->scriptScope, self->scopeVariableId, 0, &a);
    R11B008Node* n;
    s32 found;
    if (a.tag != 0x1E) {
        goto fin;
    }
    {
        n = a.node;
        found = 0;
        while (n) {
            R11B008Node* e = n->node;
            f32 d = e->f - limit;
            if (d <= 0.0f) {
                found = 1;
                EvalScriptExpression(&t, (R11B008Node*)e->next, (ScriptScope*)self->scriptScope);
                AssignScriptValue(&q, &t);
                DestroyScriptValue(&t, 2);
                SetScriptValueTag(n, 0);
            } else {
                SetScriptValueFloat(e, d);
            }
            n = n->next;
        }
        if (!found) {
        fin:
            DestroyScriptValue(&q, 2);
            DestroyScriptValue(&a, 2);
            return;
        }
    }
    LookupScriptVariable((ScriptScope*)self->scriptScope, self->scopeVariableId, 0, &a);
    {
        R11B008Node* head = a.node;
        R11B008Node* prev = 0;
        for (n = a.node; n; n = n->next) {
            if (n->tag == 0x1E) {
                prev = n;
            } else if (prev) {
                prev->next = n->next;
            } else {
                head = n->next;
            }
        }
        if (head != a.node) {
            if (head) {
                SetScriptValueChain(&a, head);
            } else {
                SetScriptValueTag(&a, 0);
            }
            AssignScriptVariable(&t, (ScriptScope*)self->scriptScope, self->scopeVariableId, &a);
            DestroyScriptValue(&t, 2);
        }
    }
    DestroyScriptValue(&q, 2);
    DestroyScriptValue(&a, 2);
}

// Takes an 8-byte touch node from the world's pool, zeroed.
void* AllocateTouchNode(World* self)
{
    void* p = TakePoolSlot(&self->pool1C0C);
    FillMemory(p, 0, 0x8);
    return p;
}

// Gives a chain of touch nodes back to the world's touch-node pool.
void FreeTouchNodes(World* owner, Touch03* node)
{
    while (node != 0) {
        Touch03* next = node->next;
        PushFreeSlot(&owner->pool1C0C, node);
        node = next;
    }
}

// Makes n-1 copies of the source object (CreateObjectCopy) in a freshly allocated array and
// records the array and count as the world's next clone batch.
void PushCloneBatch(World* self, void* src, s32 n)
{
    struct PackedCloneBatch tmp;
    s32 i;
    s32 idx;

    tmp.n = n - 1;
    if (tmp.n > 0) {
        tmp.buf = AllocateFrontMemory(tmp.n * 4);
        for (i = 0; i < tmp.n; i++) {
            ((void**)tmp.buf)[i] = CreateObjectCopy((BaseObject*)src, self, 0);
        }
    }
    idx = self->cloneBatchCount;
    ((PackedCloneBatch*)self->cloneBatches)[idx] = tmp;
    self->cloneBatchCount = idx + 1;
}

// Pops and gives back the last value of the world's clone batch number index.
s32 PopSpawnedClone(World* self, s32 index) { CloneBatch* s = &((CloneBatch*)self->cloneBatches)[index]; s->count--; return s->values[s->count]; }

// A list walk's frame (as ListFrame) that pushes itself and pops itself when it goes.
struct ColliderListWalker {
    List01* list;
    s32* cur;
    s32 step;
    ColliderListWalker* prev;
    ColliderListWalker(List01* l)
    {
        list = l;
        cur = (s32*)&l->head;
        step = l->offset;
        prev = (ColliderListWalker*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~ColliderListWalker() { g_activeListFrames = (ListFrame*)prev; }
    s32 Next()
    {
        s32 n = *cur;
        cur = (s32*)(n + step);
        return n;
    }
};
void* AllocateBackMemory(s32 size);

// Collects the world's colliders whose bounding boxes touch the box between a and b, apart from
// skip and those the filter callback refuses, into a back-memory array (*out), and gives their
// count. Gives none when skip is flagged as not colliding.
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out)
{
    s32 size = world->count34 * 4;
    ColliderListWalker walk((List01*)&world->list6C);
    Collider** cursor = *out = (Collider**)AllocateBackMemory(size);
    if (skip != 0 && ((skip->flags538 & 0x80000000000ull) != 0 || (skip->root03()->flags538 & 0x40000000000ull) != 0)) {
        goto done;
    }
    {
        Vec02 lo;
        Vec02 hi;
        ScopeMarker scope;
        Vu0::Q(lo) = Vu0::Min(Vu0::Q(*a), Vu0::Q(*b));
        Vu0::Q(hi) = Vu0::Max(Vu0::Q(*a), Vu0::Q(*b));
        Collider* c;
        while ((c = (Collider*)walk.Next()) != 0) {
            if (c == skip) {
                continue;
            }
            if (c->boundsMin.x > hi.x || c->boundsMax.x < lo.x || c->boundsMin.y > hi.y || c->boundsMax.y < lo.y ||
                c->boundsMin.z > hi.z || c->boundsMax.z < lo.z) {
                continue;
            }
            if (c->root03()->flags538 & 0x40000000000ull) {
                continue;
            }
            if (skip != 0) {
                if (skip->desc03()->m38(skip, c) != 0) {
                    continue;
                }
                if (c->desc03()->m38(c, skip) != 0) {
                    continue;
                }
            }
            for (Collider* part = (Collider*)c->parts.head; part != 0; part = (Collider*)part->link2E4.next) {
                if (filter != 0) {
                    if (filter(arg, part) == 0) {
                        continue;
                    }
                } else if ((part->flags538 & 0x80000000000ull) != 0) {
                    continue;
                }
                *cursor++ = part;
            }
        }
    }
done:
    *count = cursor - *out;
}

// Collects the world's colliders whose bounding sphere touches the sphere (center, radius), apart
// from skip and those the filter callback refuses, into a back-memory array (*out), and gives their
// count.
void GatherCollidersInSphere(World* world, Collider* skip, f32 radius, Vec02* center, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out)
{
    s32 size = world->count34 * 4;
    ColliderListWalker walk((List01*)&world->list6C);
    Collider** cursor = *out = (Collider**)AllocateBackMemory(size);
    if (skip != 0 && ((skip->flags538 & 0x80000000000ull) != 0 || (skip->root03()->flags538 & 0x40000000000ull) != 0)) {
        goto done;
    }
    {
        Collider* c;
        while ((c = (Collider*)walk.Next()) != 0) {
            if (c == skip) {
                continue;
            }
            Vec02 d;
            ScopeMarker scope;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*center), Vu0::Q(c->v140));
            f32 dist = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
            f32 reach = radius + c->radius3D0;
            if (reach * reach < dist) {
                continue;
            }
            if (c->root03()->flags538 & 0x40000000000ull) {
                continue;
            }
            if (skip != 0) {
                if (skip->desc03()->m38(skip, c) != 0) {
                    continue;
                }
                if (c->desc03()->m38(c, skip) != 0) {
                    continue;
                }
            }
            for (Collider* part = (Collider*)c->parts.head; part != 0; part = (Collider*)part->link2E4.next) {
                if (filter != 0) {
                    if (filter(arg, part) == 0) {
                        continue;
                    }
                } else if ((part->flags538 & 0x80000000000ull) != 0) {
                    continue;
                }
                *cursor++ = part;
            }
        }
    }
done:
    *count = cursor - *out;
}

// Removes a contact table from the doubly linked list whose head is *a1.
void UnlinkContactTable(Contacts03* a0, Contacts03** a1) {
    Contacts03* next;
    if (a0->next == 0) {
        next = a0->prev;
    } else {
        a0->next->prev = a0->prev;
        next = a0->prev;
    }
    if (next != 0) {
        next->next = a0->next;
    } else {
        *a1 = a0->next;
    }
}

// Allocates 0x100 contact tables of 16 bytes and links them into a free list.
void InitContactTables(World* self)
{
    void* mem = AllocateZeroedFrontMemory(0x1000);
    self->tables = (Contacts03*)mem;
    self->freeTables = (Contacts03*)mem;
    for (s32 i = 0; i < 0x100; i++) {
        Contacts03* n = (Contacts03*)((u8*)self->tables + (i << 4));
        n->prev = (i < 1) ? 0 : n - 1;
        n->next = (i > 0xFE) ? 0 : n + 1;
    }
}

// Puts a contact table at the head of the doubly linked list *head.
void PushContactTable(Contacts03* node, Contacts03** head)
{
    node->next = *head;
    node->prev = 0;
    if (*head != 0) {
        (*head)->prev = node;
    }
    *head = node;
}

// Moves a table from the world's free list to its used list and gives it to the collider.
Contacts03* TakeContactTable(World* owner, Collider* self)
{
    Contacts03* n = owner->freeTables;
    UnlinkContactTable(n, &owner->freeTables);
    PushContactTable(n, &owner->usedTables);
    n->owner = self;
    return n;
}

// Frees a body's contact table: for each row it unlinks the matching row of the other body, frees
// the pooled contact chain (clearing the root tries of both bodies unless flag bit 55 is set) and
// returns both rows to the pool.
void ReleaseContactTable(World* owner, Contacts03* handle)
{
    ContactRow03* e = handle->head;
    if (e != 0) {
        void* freeList = &owner->pool1AF0;
        do {
            ContactRow03* next = e->next;
            ContactRow03* s1 = UnlinkContactRow(owner, &e->other->contacts->head, handle);
            if (e->head != 0) {
                FreePooledContactChain(owner, e->head);
                if (!(e->other->flags538 & (1ULL << 55))) {
                    ClearRootTries(e->other);
                }
                if (!(s1->other->flags538 & (1ULL << 55))) {
                    ClearRootTries(s1->other);
                }
            }
            s1->head = 0;
            e->head = 0;
            PushFreeSlot((Pool6C*)freeList, e);
            PushFreeSlot((Pool6C*)freeList, s1);
            e = next;
        } while (e != 0);
    }
    handle->head = 0;
    Contacts03** hb = &owner->usedTables;
    s32 a3 = handle - owner->tables;
    Contacts03* p = *hb;
    if (p != 0) {
        do {
            s32 b = p - owner->tables;
            u8* tab = (u8*)owner->buf1ADC;
            u8* r1 = tab + (a3 << 8);
            u8* r2 = tab + (b << 8);
            r2[a3] = 0;
            r1[b] = 0;
            p = p->next;
        } while (p != 0);
    }
    handle->owner = 0;
    UnlinkContactTable(handle, hb);
    PushContactTable(handle, &owner->freeTables);
}

// Creates the world's default cone volume objects (class 0x51): one for each bit of
// g_coneVolumeMask, with a colour, three cone angles and levels and a direction taken from the
// g_coneVolume globals; the second has mode 1.
void CreateConeVolumes(World* self)
{
    ConeVolume* p;

    if (g_coneVolumeMask[0] & 1) {
        p = CreateTypedRecord(0x51, self, 0, 0x201, -1);
        SetConeVolumeColor(p, (Quad16*)g_coneVolumeColor);
        SetConeVolumeFirstAngle(p, g_coneVolumeFirstAngle);
        SetConeVolumeSecondLevel(p, g_coneVolumeSecondLevel);
        SetConeVolumeSecondAngle(p, g_coneVolumeSecondAngle);
        SetConeVolumeThirdLevel(p, g_coneVolumeThirdLevel);
        SetConeVolumeThirdAngle(p, g_coneVolumeThirdAngle);
        SetConeVolumeDirection(p, (Quad16*)&g_coneVolumeDirection);
    }
    if (g_coneVolumeMask[0] & 2) {
        p = CreateTypedRecord(0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 1);
        SetConeVolumeColor(p, (Quad16*)g_coneVolumeColor);
        SetConeVolumeFirstAngle(p, g_coneVolumeFirstAngle);
        SetConeVolumeSecondLevel(p, g_coneVolumeSecondLevel);
        SetConeVolumeSecondAngle(p, g_coneVolumeSecondAngle);
        SetConeVolumeThirdLevel(p, g_coneVolumeThirdLevel);
        SetConeVolumeThirdAngle(p, g_coneVolumeThirdAngle);
        SetConeVolumeRange(p, (U64P*)g_coneVolumeMode1Range);
        p->desc02()->m1D(p, (Vec02*)g_coneVolumePosition);
    }
    if (g_coneVolumeMask[0] & 4) {
        p = CreateTypedRecord(0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 2);
        SetConeVolumeColor(p, (Quad16*)g_coneVolumeColor);
        SetConeVolumeFirstAngle(p, g_coneVolumeFirstAngle);
        SetConeVolumeSecondLevel(p, g_coneVolumeSecondLevel);
        SetConeVolumeSecondAngle(p, g_coneVolumeSecondAngle);
        SetConeVolumeThirdLevel(p, g_coneVolumeThirdLevel);
        SetConeVolumeThirdAngle(p, g_coneVolumeThirdAngle);
        SetConeVolumeDirection(p, (Quad16*)&g_coneVolumeDirection);
        SetConeVolumeRange(p, (U64P*)g_coneVolumeMode2Range);
        p->desc02()->m1D(p, (Vec02*)g_coneVolumePosition);
    }
    if (g_coneVolumeMask[0] & 8) {
        p = CreateTypedRecord(0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 3);
        SetConeVolumeColor(p, (Quad16*)g_coneVolumeColor);
        SetConeVolumeFirstAngle(p, g_coneVolumeFirstAngle);
        SetConeVolumeSecondLevel(p, g_coneVolumeSecondLevel);
        SetConeVolumeSecondAngle(p, g_coneVolumeSecondAngle);
        SetConeVolumeThirdLevel(p, g_coneVolumeThirdLevel);
        SetConeVolumeThirdAngle(p, g_coneVolumeThirdAngle);
        SetConeVolumeDirection(p, (Quad16*)&g_coneVolumeDirection);
        SetConeVolumeRange(p, (U64P*)g_coneVolumeMode3Range);
        p->desc02()->m1D(p, (Vec02*)g_coneVolumePosition);
    }
}

// Reads a block count and, when the script stream has its extras, skips all but the first of
// that many blocks.
void SkipBufferedBlocks(BufferedStream* self)
{
    s32 n = ReadBufferedU32(self);
    if (g_scriptStreamExtras) {
        s32 i = 1;
        if (i < n) {
            i = n - 1;
            do {
                SkipBufferedBlock(self);
                i--;
            } while (i != 0);
        }
    }
}

// After a world loads, makes extra copies of the first object of two classes (0x58 x 0x23 and 0x56
// x 5) from the world's notifier list, each started in mode 2.
void SpawnListedObjectCopies(World* self)
{
    ClassCopyCount pairs[2] = { { 0x58, 0x23 }, { 0x56, 0x5 } };
    u32 i;
    for (i = 0; i < 2; i++) {
        StateNotifier* n;
        for (n = (StateNotifier*)self->list1C54.head; n != 0; n = n->next374) {
            if (n->f334 == 0 && n->desc->id == pairs[i].classId) {
                break;
            }
        }
        if (n == 0) {
            continue;
        }
        for (s32 k = 0; k < pairs[i].count; k++) {
            StateNotifier* o = (StateNotifier*)CreateObjectCopy(n, self, 0);
            o->initialMode = 2;
            if (o->desc->m0F != 0) {
                o->desc->m0F(o);
            }
            o->desc->m10(o);
        }
    }
}

void ResetScatterController(ScatterController* self);
s32 ReadBufferedU8(BufferedStream* s);
s32 ReadBufferedS16(BufferedStream* s);
void SkipBufferedBlocks(BufferedStream* s);
void ReadPropertyRecords(void* self, void* obj);
void ReadOptionalBufferedBlock(BufferedStream* self, u32* out);
void ReadBufferedString(BufferedStream* self, u8** out);
void ReadSlotObjects(World* self, void* a1, void* a2);
void ReadBufferedBlockBody(BufferedStream* s);
s32 EnsureSoundBankLoaded(s32 bank);
void SilenceVolumeChannel2(void);
struct KeyRecord;
void RequestStagedBank(KeyRecord* self);
s32 IsListEmpty(List01* list);
void CreateConeVolumes(World* self);
extern u8 g_screenClearPacketA[];
void SpawnListedObjectCopies(World* self);
void RunQueuedCalls(World* self);
void UpdateScatterLevelLimits(ScatterController* self);
void ResumeElementStackState(void* stack);
void PlayStagedBank(void* self);
void StartWorldSoundEntries(World* self);

// Loads a level's world from its stream and brings it to a running state. In order:
//  1. resets the scatter controller and the script value pools; reads the script stream extras
//     byte and the world's sound bank id, skips a block;
//  2. creates the camera (type 0x6D) and the pools of 10 (type 0x1E) and 0x28 (type 0x4D) helper
//     records, calling each one's method 3 (probably its initialiser);
//  3. reads the script entry table, the property records, the optional commentary record, the
//     credits text, the optional staged bank, the screen resources and the placed objects;
//  4. loads the sound bank if the id is >= 0, silences volume channel 2 when the world has it off,
//     requests the staged bank and sends the resident images;
//  5. creates the cone volumes if none were read, sets the fill alpha to 0x80, fills the screen
//     clear packet with the world's colour and scales two floats by 1/255 (0.003921569);
//  6. spawns the listed object copies, then runs the queued calls, calls method 0x0F of every
//     object in the main list (list48) that has one, runs the queued calls again, calls method
//     0x10 of every object of that list (walked under a ListFrame so the list may change), and
//     runs the queued calls a third time;
//  7. updates the scatter level limits, resumes the element stack, and when no map screen is
//     current on a level other than 0 reserves 0x80000 bytes of zeroed front memory;
//  8. places the camera, updates the world's contacts, plays the staged bank and starts the
//     world's sound entries.
void LoadWorld(World* self, BufferedStream* s)
{
    Rgba4 color;
    ListFrame walk;
    ListFrame frame;
    s32 i;
    ResetScatterController((ScatterController*)g_scatterController);
    InitScriptValuePools();
    g_scriptStreamExtras = ReadBufferedU8(s);
    self->soundBank = ReadBufferedS16(s);
    SkipBufferedBlocks(s);
    g_camera = (Camera*)CreateTypedRecord(0x6D, self, 0, 4, -1);
    for (i = 0; i < 10; i++) {
        BaseObject* o = (BaseObject*)CreateTypedRecord(0x1E, self, 0, 0xA, -1);
        o->desc->m03(o);
    }
    for (i = 0; i < 0x28; i++) {
        BaseObject* o = (BaseObject*)CreateTypedRecord(0x4D, self, 0, 0xB, -1);
        o->desc->m03(o);
    }
    LoadScriptEntryTable(self, s);
    ReadPropertyRecords(self, s);
    ReadOptionalBufferedBlock(s, (u32*)&self->commentaryRecord);
    ReadBufferedString(s, (u8**)&self->creditsText);
    ReadOptionalBufferedBlock(s, (u32*)&self->stagedBank);
    LoadScreenResources(s);
    ReadSlotObjects(self, 0, s);
    ReadBufferedBlockBody(s);
    if (self->soundBank >= 0) {
        EnsureSoundBankLoaded(self->soundBank);
    }
    if (self->volumeChannel2On == 0) {
        SilenceVolumeChannel2();
    }
    RequestStagedBank(self->stagedBank);
    SendResidentImages();
    if (IsListEmpty(&self->list1BE8) != 0) {
        CreateConeVolumes(self);
    }
    self->fillAlpha = 0x80;
    color = self->color1D64;
    FillScreenColor(g_screenClearPacketA, &color, 0);
    self->f1D68 *= 0.003921569f;
    self->f1D6C *= 0.003921569f;
    SpawnListedObjectCopies(self);
    RunQueuedCalls(self);
    for (BaseObject* o = (BaseObject*)self->list48.head; o != 0; o = o->next) {
        if (o->desc->m0F != 0) {
            o->desc->m0F(o);
        }
    }
    RunQueuedCalls(self);
    List01* list = &self->list48;
    frame.list = list;
    frame.offset = list->offset;
    frame.prev = g_activeListFrames;
    g_activeListFrames = &frame;
    BaseObject* head = *(BaseObject**)frame.list;
    frame.link = (u8*)head + frame.offset;
    BaseObject* h = head;
    while (h != 0) {
        h->desc->m10(h);
        BaseObject* nx = *(BaseObject**)frame.link;
        frame.link = (u8*)nx + frame.offset;
        h = nx;
    }
    g_activeListFrames = frame.prev;
    RunQueuedCalls(self);
    UpdateScatterLevelLimits((ScatterController*)g_scatterController);
    ResumeElementStackState(g_elementStack);
    if (g_mapScreenList.current == 0 && g_saveData->levelIndex != 0) {
        AllocateZeroedFrontMemory(0x80000);
    }
    UpdateCameraLocation(g_camera);
    UpdateWorldContacts(self, 0);
    PlayStagedBank(self->stagedBank);
    StartWorldSoundEntries(self);
}

// Clips the segment of two 4-component points against the six planes of the clip volume, moving an
// end that is outside onto the plane. Returns 0 when the whole segment is outside, 1 otherwise.
s32 ClipSegmentToPlanes(ClipPoint* pts)
{
    u32 i;
    for (i = 0; i < 6; i++) {
        const ClipPlane* pl = &g_clipVolumePlanes[i];
        f32 d[2];
        s32 k;
        for (k = 0; k < 2; k++) {
            d[k] = pts[k].x * pl->x + pts[k].y * pl->y + pts[k].z * pl->z + pts[k].w * pl->w;
        }
        if (d[0] >= 0.0f && d[1] >= 0.0f) {
            continue;
        }
        if (d[0] < 0.0f && d[1] < 0.0f) {
            return 0;
        }
        f32 t = d[1] / (d[1] - d[0]);
        if (d[0] >= 0.0f) {
            f32 u = 1.0f - t;
            pts[1].x = t * pts[0].x + u * pts[1].x;
            pts[1].y = t * pts[0].y + u * pts[1].y;
            pts[1].z = t * pts[0].z + u * pts[1].z;
            pts[1].w = t * pts[0].w + u * pts[1].w;
        } else {
            f32 u = 1.0f - t;
            pts[0].x = t * pts[0].x + u * pts[1].x;
            pts[0].y = t * pts[0].y + u * pts[1].y;
            pts[0].z = t * pts[0].z + u * pts[1].z;
            pts[0].w = t * pts[0].w + u * pts[1].w;
        }
    }
    return 1;
}

// Draws a line between two points: both are transformed by the object's matrix at +0x100 (w set to
// 1), clipped by ClipSegmentToPlanes, and, if any of it is left, projected and drawn in the colour
// c.
void DrawProjectedLine(ClipPoint* a, ClipPoint* b, PackedColor* c, u8* obj, s32 k)
{
    SegmentFrame L;
    ClipPoint* base;
    ClipPoint* p;
    s32 n;

    base = &L.buf[2];

    L.buf[0] = *a;
    L.buf[0].w = 1.0f;
    L.buf[1] = *b;
    L.buf[1].w = 1.0f;

    p = base;
    n = 1;
    do {
        *(UQuadword*)p = TransformVector4(obj + 0x100, *(UQuadword*)(p - 2));
        n--;
        p++;
    } while (n >= 0);

    if (ClipSegmentToPlanes(base) != 0) {
        void* tp = &L.tmp;
        ClipPoint* q = base;
        n = 1;
        do {
            f32 r = 1.0f / q->w;
            q->x = q->x * r * g_projectionScale.x + g_projectionOffset.x;
            q->y = q->y * r * g_projectionScale.y + g_projectionOffset.y;
            q->z = q->z * r * g_projectionScale.z + g_projectionOffset.z;
            n--;
            q++;
        } while (n >= 0);
        L.tmp = *c;
        DrawLineSegment(*(s32*)&L.buf[2].x, *(s32*)&L.buf[2].y, *(s32*)&L.buf[2].z,
                      *(s32*)&L.buf[3].x, *(s32*)&L.buf[3].y, *(s32*)&L.buf[3].z,
                      tp, k);
    }
}

// Draws a curve through four control points as 9 projected line segments (10 samples) in the
// colour a4 points to.
void DrawProjectedCurve(void* a0, void* a1, void* a2, void* a3, void* a4, u8* obj, s32 unused6, f32 x)
{
    CurveFrame L;
    CurveSample* p;
    CurveSample* q;
    u32 i;

    SampleCurvePoints(x, (const Vec02*)a0, (const Vec02*)a1, (const Vec02*)a2, (const Vec02*)a3, 10, (CurvePoint*)L.pts, 0.0f, x);
    i = 1;
    q = &L.pts[1];
    p = &L.pts[0];
    do {
        L.c = *(PackedCurveColor*)a4;
        DrawProjectedLine((ClipPoint*)p, (ClipPoint*)q, (PackedColor*)&L.c, obj, 1);
        i++;
        q++;
        p++;
    } while (i < 10);
}

// Sets the world's first lighting parameter and notes the frame it changed in.
void SetWorldLightingParamA(World* self, f32 v)
{
    self->f1D6C = v;
    g_lightingChangeFrame = g_frameCount;
}

// Sets the world's second lighting parameter and notes the frame it changed in.
void SetWorldLightingParamB(World* self, f32 v)
{
    self->f1D68 = v;
    g_lightingChangeFrame = g_frameCount;
}

// Sets the world's sound level, forces the previous-level cache to refresh and sends the
// rounded level to the IOP.
void SetWorldSoundLevel(void* self, f32 x)
{
    World* s = (World*)self;

    s->soundLevel = x;
    *(s32*)g_previousSoundLevel = -100;
    SetVolumeChannelFactor(7, 1, 1.0f);
    SendIopSoundLevel((s32)(s->soundLevel + 0.5f));
}

// Whether bit 1 of the level entry's first word is set (script builtin).
s32 TestLevelEntryFlag1(void* self, s32 obj)
{
    return GetLevelEntryWord(obj) & 0x1;
}

// Whether bit 2 of the level entry's first word is set (script builtin).
s32 TestLevelEntryFlag2(void* self, s32 obj)
{
    return GetLevelEntryWord(obj) & 0x2;
}

// Whether bit 4 of the level entry's first word is set (script builtin).
s32 TestLevelEntryFlag4(void* self, s32 obj)
{
    return GetLevelEntryWord(obj) & 0x4;
}

// Whether bit 8 of the level entry's first word is set (script builtin).
s32 TestLevelEntryFlag8(void* self, s32 obj)
{
    return GetLevelEntryWord(obj) & 0x8;
}

// True when the entry's flags have bit 2 set and the current entry has flag bit 1.
s32 CheckEntryOneBitRequirement(World* a0, s32 a1)
{
    s32 one = 1;
    u32 m = GetEntryFlags(a1);
    s32 r = 0;
    if (m & 2) r = (g_currentEntry->flags & 1) ? one : 0;
    return r;
}

// True when the entry's flags have bit 4 set and the current entry has every flag bit in the
// low two bits of the entry's flags.
s32 CheckEntryTwoBitRequirement(void* self, s32 obj)
{
    u32 flags = GetEntryFlags(obj);
    u32 bits = flags & 3;
    s32 r = 0;
    if (flags & 4) {
        G27C230* g = g_currentEntry;
        u32 m = (u32)g->flags;
        r = ((bits & m) ^ bits) < 1;
    }
    return r;
}

// True when the entry's flags have bit 8 set and the current entry has every flag bit in the
// low three bits of the entry's flags.
s32 CheckEntryThreeBitRequirement(void* self, s32 obj)
{
    u32 flags = GetEntryFlags(obj);
    u32 bits = flags & 7;
    s32 r = 0;
    if (flags & 8) {
        G27C230* g = g_currentEntry;
        u32 m = (u32)g->flags;
        r = ((bits & m) ^ bits) < 1;
    }
    return r;
}

// Stores value under key in the first of the four slots of the level entry obj, reusing the
// slot that already has that key and otherwise the first free one.
void SetEntrySlotValue(void* self, s32 obj, s32 key, s32 value)
{
    EntrySlotTable* t = (EntrySlotTable*)GetLevelEntryByKey(obj);
    if (t) {
        EntrySlot* found = 0;
        for (u32 i = 0; i < 4; i++) {
            EntrySlot* p = &t->slots[i];
            if (found == 0 && p->key == 0) {
                found = p;
                continue;
            }
            if (p->key == key) {
                found = p;
                break;
            }
        }
        if (found) {
            found->key = key;
            found->value = value;
        }
    }
}

// The value stored under key in the four slots of the level entry obj, or 0.
s32 GetEntrySlotValue(void* self, s32 obj, s32 key)
{
    EntrySlotTable* t = (EntrySlotTable*)GetLevelEntryByKey(obj);
    if (t != 0) {
        EntrySlot* p = t->slots;
        for (u32 i = 0; i < 4; i++) {
            if (p->key == key) {
                return p->value;
            }
            p++;
        }
    }
    return 0;
}

// Whether bit 1 of the saved level record's flag word is set.
s32 IsLevelRecordComplete(void* self, s32 index)
{
    return g_saveData->levels[index].f448 & 1;
}

// Whether bit 0x20 (set by MarkLevelDone) of the saved level record's flag word is set.
s32 IsLevelDone(void* self, s32 index)
{
    return g_saveData->levels[index].f448 & 0x20;
}

s32 RecomputeSaveCompletion(void* self)
{
    return ComputeCompletionPercent(g_saveData);
}

// Picks a random count between a and b and, if it is not 0, scatters that many objects (type
// 0x58) around the point c in the current world.
void ScatterRandomObjects(void* unused, s32 a, s32 b, void* c)
{
    s32 r = RandomIntInRange(a, b);
    if (r != 0) {
        ScatterObjectsAroundCircle(g_currentWorld, 0x58, (Vec02*)c, r, 0);
    }
}

void SetScatterLevelBuiltin(f32 level)
{
    SetScatterLevel((ScatterController*)g_scatterController, level);
}

void GetGameStateDeltaTime(void* unused, f32* out)
{
    *out = g_currentEntry->dt;
}

// Clamps level to the unit range and stores it in the current entry.
void SetCurrentScatterLevel(void* unused, f32 level)
{
    f32 r = ClampToRange(&g_unitRange, level);
    g_currentEntry->f10 = r;
}

void GetCurrentScatterLevel(void* unused, f32* out)
{
    *out = g_currentEntry->f10;
}

// Counts one more hold on the pad-select flag; the first hold sets pad select flag 2.
void AcquirePadSelectFlag(World* a0) {
    s32 n = a0->padSelectHolds + 1;
    a0->padSelectHolds = n;
    if (n == 1) {
        SetPadSelectFlags(2);
    }
}

// Drops one hold on the pad-select flag; when the count reaches 0, pad select flag 2 is
// cleared.
void ReleasePadSelectFlag(World* self)
{
    s32 v = self->padSelectHolds - 1;
    self->padSelectHolds = v;
    if (v == 0) {
        ClearPadSelectFlags(2);
    }
}

s32 IsPadSelectFlagHeld(World* self) { return self->padSelectHolds > 0; }

void GetHasStreamVoice(void* self, s32* out)
{
    *out = HasStreamVoice();
}

// Sets both the world's value and its target to v, so there is no transition.
void SetWorldValueAndTarget(World* self, f32 v)
{
    self->valueTarget = v;
    self->value = v;
}

void SetWorldValueTarget(World* self, f32 value) { self->valueTarget = value; }

// Pops the element stack when the active step sequence is in mode 1 or 2 and not in state 4.
void PopActiveSequenceElement(World* world)
{
    StepSequence* ctx = g_activeStepSequence;
    if (ctx != 0 && ctx->state2D4 != 4) {
        u32 t = (u32)(ctx->mode2D0 - 1);
        if (t < 2) PopStackElement((ElementStack*)g_elementStack);
    }
}

// Stores a2 as the pause menu's page word and shows page a1 of its layer.
void ShowPauseMenuPageWith(void* unused, s32 a1, s32 a2)
{
    s32 saved = a1;
    u8* p = (u8*)&g_pauseMenuElement;
    ((PackedPageWord*)(p + 0x280))->v = a2;
    SetPauseMenuLayerPage(&g_pauseMenuElement, 0, saved);
}

// Counts one more hold on the letterbox element; the first hold shows it with a hold time of 0.
void ShowCountedScreenElement(World* self)
{
    if (++self->elementHolds == 1) {
        SetScreenElementHoldTime(&g_letterboxElement, 0.0f);
        g_letterboxElement.vt->m14(&g_letterboxElement);
    }
}

// Drops one hold on the letterbox element; when the count reaches 0 it is hidden.
void HideCountedScreenElement(World* self)
{
    if (--self->elementHolds == 0) {
        g_letterboxElement.vt->m15(&g_letterboxElement);
    }
}

LINKER_REMNANT(func_001DDBF0);

void* PushSoundLevelBuiltin(void* self, s32 p)
{
    return PushSoundLevel(p);
}

void RemoveSoundLevelBuiltin(void* unused, void* p)
{
    RemoveSoundLevelAndRecompute((SoundLevelEntry*)p);
}

void SetWorldActiveFollower(World* self, void* v)
{
    self->activeFollower = v;
}

// Calls slot 50 of the active follower's method table, if there is a follower and a method.
void NotifyWorldActiveFollower(World* self)
{
    ActiveFollowerChild* p = (ActiveFollowerChild*)self->activeFollower;
    if (p != 0) {
        ActiveFollowerFn fn = p->vtbl[50];
        if (fn != 0) {
            fn(p);
        }
    }
}

// Sets bit number bit of the world's flag bits.
void SetWorldFlagBit(World* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->flagBits |= m;
}

// Clears bit number bit of the world's flag bits.
void ClearWorldFlagBit(World* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->flagBits &= ~m;
}

void GetSaveSpareCount(void* self, s32* out)
{
    *out = g_saveData->spareCount;
}

void GetReserveUnitCount(void* unused, s32* out)
{
    *out = g_saveData->reserveCount;
}
