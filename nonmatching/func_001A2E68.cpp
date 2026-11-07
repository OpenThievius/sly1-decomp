// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 408/412 (99.0%), checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): exact but for the two quadword copies of the node query: retail loads *where into $v1 and the effect's qA0 into $v0 (here the reverse, stores in the same order); all 120 orders of the five field assignments (tools/permute.py) leave this 4-byte difference, the best being this one.
#include "common.h"
#include "node_query.h"
#include "vu0.h"
#include "list_iter.h"
#include "c8b.h"
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

void AddCallbackNode(void* world, void* list, void* a, void* b);
void RemoveCallbackNode(void* world, void* list, void* a, void* b);



void InitCollider(Collider* self);

void SetListLinkOffset(void* p, s32 n);

void* PopFreeSlot(void* p);

void FillMemory(void* p, s32 zero, s32 size);

const Vt219C* GetEffectKindTable(u32 n);

void AppendToList(void* list, void* item);

void CountEffectUse(Effect* self);

void RemoveFromList(void* table, void* self);

void ReleaseEffect(Effect* self);

void ReleaseCallRecords(void* a, void* b);

void PushFreeSlot(void* a, void* b);

extern f32 g_gameClock[];

void InitEffect(Effect* self);



extern f32 g_gameTime;

void RemoveEffect(Effect* self);

s32 IsObjectAttached(void* p);

s32 func_0013E658(void* a, s32 b);

void ComputeOscillatorDisplacement(f32 f, void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5);

s32 DrawEffectAt(void* self, void* a1, void* a2, void* a3);
void BuildBasisFromXAndZHint(void* a, void* b, void* c);

struct ColorFade;





s32 CollectTreeNodeSpans(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);

Effect* CreateEffect(s32 kind, EffectOwner* sys);


extern Camera* g_camera;






s32 TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);

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

void RemoveEffect(Effect* node);

void UnregisterCollider(Collider* self);


void ComputeGridBlendWeights(f32 x, f32 y, f32 z, C8B* o, void* p);

typedef void (*Fn_Table)();

extern const Fn_Table g_basicEffectMethods[];

extern const Fn_Table g_fallingEffectMethods[];

extern const Fn_Table g_risingEffectMethods[];

extern const Fn_Table g_impactEffectMethods[];

extern const Fn_Table g_growingEffectMethods[];

extern const Fn_Table g_shrinkingFallEffectMethods[];

extern const Fn_Table g_droppingEffectMethods[];

extern const Fn_Table g_streakEffectMethods[];

extern const Fn_Table g_scaledEffectMethods[];

extern const Fn_Table g_trailSegmentEffectMethods[];

extern const Fn_Table g_spawningEffectMethods[];

extern const Fn_Table g_followUpEffectMethods[];

extern const Fn_Table g_wideTrailSegmentEffectMethods[];

extern const Fn_Table g_shortFallingEffectMethods[];

extern u8 g_emitterEffectMethods[];

extern const Fn_Table g_cameraSpaceEffectMethods[];

extern const Fn_Table g_longStreakEffectMethods[];

extern const Fn_Table g_phasedEffectMethods[];

extern const Fn_Table g_projectileEffectMethods[];

extern const Fn_Table g_hitMarkEffectMethods[];

extern const Fn_Table g_tumblingEffectMethods[];

extern const Fn_Table g_aimedEffectMethods[];

extern const Fn_Table g_streakedEffectMethods[];

extern const Fn_Table g_spinningEffectMethods[];

extern const Fn_Table g_facingEffectMethods[];

extern const Fn_Table g_delayedEffectMethods[];

extern const Fn_Table g_messageEffectMethods[];






void RemoveFromList(List01 *a, ObjectGatherer *b);

void AppendToList(List01 *a, ObjectGatherer *b);


void EndEffect();

void HandleEffectContact();

void MoveEffect();

void InitRisingEffect();

void MoveDriftingEffect();

void EndEffectWithImpactOnExit();

void InitImpactEffect();

void UpdateDroppingEffect();

void DrawDroppingEffect();

void EndDroppingEffect();

void InitStreakEffect();

void DrawStreakEffect();

void InitScaledEffect();

void InitTrailSegment();

void DetachTrailSegment();

void MoveTrailSegment();

void DrawTrailSegment();

void InitSpawningEffect();

void SpawnFollowUpEffect();

void InitFollowUpEffect();

void InitWideTrailSegment();

void InitShortFallingEffect();

void InitCameraSpaceEffect();

void MoveCameraSpaceEffect();

void DrawCameraSpaceEffect();

void RunEffectEndCallback();

void InitLongStreakEffect();

void InitPhasedEffect();

void KeepPhasedEffectStill();

void AdvanceEffectPhases();

void DrawPhasedEffect();

void CopyEffectSourceIds();

void DrawProjectileEffect();

s32 HandleEffectImpact();

void UpdateEffectUntilDetached();

void DrawHitMarkEffect();

void SetRandomEffectSpin();

void MoveTumblingEffect();

s32 HandleTumblingEffectImpact();

void AimEffectAtNearestObject();

void PlaceEffectAtSource();

void DrawStreakedEffect();

void HandleStreakedEffectImpact();

void RandomizeEffectSpin();

s32 HandleEffectContactUnlessKind6();

void DrawSpinningEffect();

void InitFacingEffect();

void DrawFacingEffect();

void InitDelayedEffect();

void MoveDelayedEffect();

void UpdateDelayedEffect();

void DrawDelayedEffect();

void ResolveEffectTarget();

void SendEffectMessagesAtRate();

void CountEffectUse(Effect* node);

void ReleaseEffect(Effect* node);

u32 IsListEmpty(List01* list);

void CollideEffects(EffectOwner* self);

void ClearRootTries(PlacedObject* self);

struct NextEffect {
    static Effect* Of(ListFrame* it)
    {
        Effect* obj = *(Effect**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};


void ComputeGridBlendWeights(C8B* self, f32* out, f32 a, f32 b, f32 c);

struct BeginListWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

struct NextListItem {
    static u8* Of(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct EndListWalk {
    static void Of(ListFrame* it)
    {
        g_activeListFrames = it->prev;
    }
};

void PushBackMemoryMark(void);

void* AllocateBackMemory(s32 size);

void PopBackMemoryMark(void);

s32 func_0013E430(u8* a0, u8* a1, void** a2, f32 scale);

s32 CollectColliderSpansInTree(Collider* self, void* a1, void* a2, void* a3, s32 a4, ColliderSpan* a5);

u32 IsListEmpty(List01* p);


void UpdateEffect(Effect* self);

s32 IsObjectAttached(s32 handle);

void LoadCollider(void* self);

void ResolveObjectLinks(void* self, s32 n, void* data);

extern Quad219C D_00275C50;

void SetTrailSegmentAnchor(void* self, s32 kind, s32 extra);

void InitStreakEffect(Effect* self);

void SetEffectPhase(Effect* self, s32 n);

struct AngledPoint { u8 pad00[0x20]; f32 angle; };



extern s32 D_0026B6C0[4];

void AttachHitMarkEffect(Effect* self, s32 v, void* other, void* a2, void* a3, s32 zero);

s32 IsObjectOfKind(void* self, s32 kind);

s32 HandleEffectContact(Effect* a, void* b, void* c, void* d);



void TakeDelayedEffectSourcePose(Effect* self);

void DrawEffect(Effect* self);

void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);

void TransformRotationBetweenFrames(void* a0, void* a1, void* a2, void* a3);


s32 IsObjectOfKind(void* node, s32 kind);

void AttachHitMarkEffect(Effect* self, s32 v, void* other, void* a2, void* a3, void* out);




extern f32 D_0026B5B0[4];

extern f32 D_0026B5C0[4];

s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);



void StartPlacedObject(void* self);

void ResolveObjectLinks(void* self, s32 a1, void* a2);

void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);

void* CreateStateWalker(void* a, void* b, s32 c, s32 d);

s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

void SetWalkerColliderState(void* self, s32 n);

void SetWalkerColliderSubState(void* self, s32 v);


void ComputeCameraRelativeStickHeading(void* a, void* b, s32 c, void* d);

extern f32 D_0026B710[4];

extern f32 D_0026B720[4];

void InitEffect(Effect* self, f32 x);


void UpdateEffect(Effect* self, f32 s);

typedef int Quadword128 __attribute__((mode(TI)));

void InitEffect(Effect* self, f32 f);

void StoreFloatAsQuadword(void* out, f32 f);

void* CopyQuadword(void* out, void* in);

Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);

void* StoreQuadword(void* dst, Quadword128 v);

extern f32 D_0026B570[4];

extern f32 D_0026B580[4];

extern f32 D_0026B5D0[4];

extern f32 D_0026B5E0[4];

void SetTrailSegmentAnchor(void* self, s32 kind, void* extra);

extern f32 D_0026B560[4];

struct RampParams { s64 a __attribute__((packed)); s32 b; };

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

void BuildYawPitchMatrix(f32* out, f32 unused, f32 value);

extern f32 D_0026B6A0[4];

extern f32 D_0026B6B0[4];

void InitSwitchedCollider(void* self);

void* StoreQuadword(Quad219C* dst, Quadword128 v);

extern f32 D_0026B590[4];

extern f32 D_0026B5A0[4];

void SetSoundStateObjectState(void* child, int flag);

void ResolveObjectLinks(void* self, int idx, void* table);

void FindOrBuildMemberGroup(void* sub, void* self);

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

struct PadStep {
    u8 bytes[2];            // 0x00
    u8 pad02[0x04 - 0x02];
    f32 delay;              // 0x04
};

struct PadPattern {
    s32 count;              // 0x00
    PadStep steps[32];      // 0x04
};

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


struct QuadraticCoeffs { f32 a, b, c; };

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


f32 D_0026B530[4] = { 1.0f, 1.666667f, -2.666667f, 0.0f };

f32 D_0026B540 = 0.5f;

f32 D_0026B544 = 0.5f;

f32 D_0026B548 = 1.5f;

f32 D_0026B54C = 200.0f;

f32 D_0026B550[4] = { 0.25f, 0.0f, 0.0f, 0.0f };

f32 D_0026B560[4] = { 0.5f, 2.0f, -2.0f, 0.0f };

f32 D_0026B570[4] = { 0.5f, -0.5f, 0.0f, 0.0f };

f32 D_0026B580[4] = { 1.0f, -1.0f, 0.0f, 0.0f };

f32 D_0026B590[4] = { 0.0f, 2.0f, -1.0f, 0.0f };

f32 D_0026B5A0[4] = { 4.0f, -4.0f, 0.0f, 0.0f };

f32 D_0026B5B0[4] = { 0.699999988079071f, 0.0f, -0.699999988079071f, 0.0f };

f32 D_0026B5C0[4] = { 0.0f, 0.0f, 50.0f, 0.0f };

f32 D_0026B5D0[4] = { 0.75f, -0.75f, -0.0f, 0.0f };

f32 D_0026B5E0[4] = { 1.0f, 2.0f, -3.0f, 0.0f };

f32 D_0026B5F0[4] = { 0.5f, 0.0f, 0.0f, 0.0f };

f32 D_0026B600[4] = { 0.0f, 0.0f, 1.0f, 0.0f };

f32 D_0026B610[4] = { 1.0f, -0.7f, 0.0f, 0.0f };

f32 D_0026B620[4] = { 135.0f, 0.0f, -85.0f, 0.0f };

f32 D_0026B630[4] = { 50.0f, 170.0f, -85.0f, 0.0f };

f32 D_0026B640[4] = { 1.0f, 0.0005f, 0.0f, 0.0f };

f32 D_0026B650[4] = { 1.0f, 10.0f, 0.0f, 0.0f };

f32 D_0026B660[4] = { 1.65f, -0.0002f, 0.0f, 0.0f };

f32 D_0026B670[4] = { 0.65f, 1.0f, 0.0f, 0.0f };

f32 D_0026B680[4] = { 0.0f, 6.0f, 0.0f, 0.0f };

f32 D_0026B690[4] = { 5.0f, 16.0f, 0.0f, 0.0f };

f32 D_0026B6A0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

f32 D_0026B6B0[4] = { 1.0f, -1.0f, 0.0f, 0.0f };

s32 D_0026B6C0[4] = { 0x40, 5, 0x42, 0x43 };

f32 D_0026B6D0[4] = { 0.0f, -0.01f, 0.0f, 0.0f };

f32 D_0026B6E0[2] = { -10.0f, 10.0f };

f32 D_0026B6E8 = -1.0f;

f32 D_0026B6EC = 200.0f;

f32 D_0026B6F0[4] = { 0.75f, 1.25f, 0.0f, 0.0f };

f32 D_0026B700[4] = { 0.0f, 0.001f, 0.0f, 0.0f };

f32 D_0026B710[4] = { 0.0f, 4.0f, -4.0f, 0.0f };

f32 D_0026B720[4] = { 0.25f, 3.0f, -3.0f, 0.0f };

f32 D_0026B730[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

f32 D_0026B740[4] = { 0.0f, 0.75f, 0.0f, 0.0f };

f32 D_0026B750[4] = { 1.0f, 5.0f, 0.0f, 0.0f };

f32 D_0026B760[4] = { 0.5f, 0.0f, 0.5f, 0.0f };

f32 D_0026B770[2] = { 0.5f, 1.0f };

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


void FillMemory(void* p, s32 v, s32 n);
s32 FindNodeForQuery(void* p, s32 a, s32 b);
void BuildBasisFromX(void* a, void* b);

s32 HandleStreakedEffectImpact(Effect* self, void* hold, Vec02* where, Vec02* dir)
{
    if (self->i124 != 0) {
        NodeQuery q;
        FillMemory(&q, 0, 0x40);
        q.pos = *where;
        q.dir = *(Vec02*)&self->qA0;
        q.hold = hold;
        q.p00 = self->owner;
        q.kind = 0x10;
        if (FindNodeForQuery(&q, 0, 0) != 0) {
            goto remove;
        }
    }
    if (self->i120 != 0) {
        Mat02 basis;
        Vec02 v;
        *(Vec02*)&self->q80 = *where;
        BuildBasisFromX(dir, &basis);
        Vu0::Q(v) = Vu0::RotateTransposed(basis, Vu0::Q(self->qA0));
        v.x *= RandomFloatInRange(-0.95f, -0.85f);
        v.y += RandomFloatInRange(-400.0f, 400.0f);
        v.z += RandomFloatInRange(-400.0f, 400.0f);
        Vu0::Q(self->qA0) = Vu0::Rotate(basis, Vu0::Q(v));
        return 1;
    }
remove:
    RemoveEffect(self);
    return 1;
}

