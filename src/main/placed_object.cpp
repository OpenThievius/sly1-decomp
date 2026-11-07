// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x1233C0 to 0x130F48: the state triggers (classes 0x22 and 0x2F), the placed object's set-up,
// update and loading (func_00123ED0 to func_001289C0), its range, sound and colour records, the
// code checksum, the animation players and their events, the id filter object, the sector stream
// reader and the curve segment helpers. One file between two edges; it could be several.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "timed_object.h"
#include "transform_object.h"
#include "state_walker.h"
#include "screen_element.h"
#include "masked_collider.h"
#include "world.h"
#include "animation.h"
#include "attachment.h"
#include "anim_curve.h"
#include "range_record.h"
#include "cursor_animator.h"
#include "sound_record.h"
#include "object_link.h"
#include "target_binding.h"
#include "globals.h"
#include "object_cycler.h"
#include "paired_object.h"
#include "code_checksum.h"
#include "switched_collider.h"
#include "shapes.h"
#include "id_filter_object.h"
#include "c8b.h"
#include "object_message.h"
#include "queued_call.h"
#include "stream_reader.h"
#include "key_id.h"
#include "game_progress.h"
#include "base_object.h"
#include "stream_reader_window.h"

f32 D_00260E70[4] = { 0.0f, 15.0f, 0.0149999997f, 0.0f };
f32 D_00260E80[4] = { 0.0f, 2.5f, 0.00249999994f, 0.0f };
f32 D_00260E90[4] = { 0.0f, 15.0f, 1.5f, 0.0f };
f32 D_00260EA0[4] = { 0.0f, 2.5f, 0.25f, 0.0f };
f32 D_00260EB0[4] = { 1500.0f, 0.0f, 0.5f, 4500.0f };
f32 D_00260EC0[4] = { 15.0f, 0.0f, 0.5f, 45.0f };
f32 g_fadeRampProfile[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00260EE0[4] = { -50.0f, 4.0f, 0.0f, 0.0f };
f32 D_00260EF0[4] = { 0.0f, 400.0f, 0.0f, 0.0f };

void* FindFirstObjectById(void* world, s32 kind, s32 id, void* scope);
void* FindFirstObjectByIdMode4(void* world, s32 id, void* scope);
AnimationPlayer* NewAnimationPlayer(World* pool);
void CloseStreamReader(StreamReader* a0);

void GatherAxisCurveTimes(WeightCurve** axis, s32* outCount, f32** outTimes);

extern void EvaluateVectorKeyCurve(s32, VectorKey*, s32, void*, void*);
extern void BuildEulerRotationMatrix(void*, void*);
extern void RotateVectorByTwoAngles(void*, void*, void*);

extern void EvaluateVectorKeyCurve(s32, VectorKey*);
extern void GetVectorKeyTimes(s32, VectorKey*, s32*, f32**);

extern void EvaluateAxisCurves(WeightCurve**, PlacedObject*, void*, Vec02*, void*, s32, f32, f32);
extern void FillMemory(void*, s32, s32);

void ReadAxisCurves(WeightCurve** a, Vec02* b, Stream83* c);

extern void EvaluateVectorKeyCurve(s32, VectorKey*, void*, f32*, s32, f32, f32);

extern void ReadVectorKeys(s32*, VectorKey**, Stream83*);

extern void* PopZeroedFreeSlot(void*);

extern World* g_currentWorld;

void CopyMemory(Attachment* self, Attachment* src, s32 size);

void InitPoseSource(Attachment* self, PlacedObject* a1);

void RemoveFromList(void* list, void* item);
void ReleasePoseSource(Attachment* self, s32 flags);

extern f32 g_gameTime[];
void GetOwnerPosition(Attachment* self, Vec02* a1, Vec02* a2);
s32 ApplyAnimationLoopMode(AnimationPlayer* t, f32* a, f32* b);

void GetOwnerRotation(Attachment* self, Mat02* a, Vec02* b);

extern void HandleMaskedColliderActivation(void*);

extern u8 g_flagTable[];
void InitCollider(Collider* self);
s32 TakeFlagTableIndex(void* p);

extern void CopyCollider(Collider*);


void UpdateCollider(Collider* self);
s32 IsObjectOfKind(void* node, s32 kind);

extern s32 UpsertKeyedEntry(void*, s32, void*, void*, void*, void*, void*);

s32 AppendPropertyToScriptList(void* a, void* b);

// An entry of PlacedObject::partStates: its word at +8.
struct PartState { u8 pad[8]; s32 value; };

// One of the 0x70-byte parts at PlacedObject::drawParts: the kind and the value
// func_00126BC0 gives each.
struct DrawPart {
    u8 pad00[0x14];
    s32 type;               // 0x14
    u8 pad18[0x6C - 0x18];
    s32 value;              // 0x6C
};

extern void MultiplyMatrices3x3(void*, void*, void*);
extern void MatrixToAxisAngle(void*, void*, void*);

extern f32 g_valueRampProfile[4];
extern f32 g_frameStep;
extern f32 g_frameDt;
extern f32 ApproachValueWithRamp(void*, s32, f32, f32, f32);

void* AppendQueuedCall(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void StartPlacedObject(void* self);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void ResolveAndStartObject(void* a);

void GetOwnerValue(Attachment* self, f32* value, f32* slope);

extern void GetOwnerValue(Attachment* self, f32* a1, f32* a2);

extern void GetIdentityMatrix(Attachment* self, Mat02* a1);

void SetCountedObjectCounter(CountedObject* node, StateTrigger* value);
void AddAgentStateTrigger(void* node, void* self);
s32 TestFlagTableBit(void* table, s32 v);

extern u8 D_002623D8[];

void StopSoundRecord(s32 a, s32 b);
void ReleaseSoundLevel(s32 a);
void SetGatheredWalkerTargets(void* a, s32 b, void* c, void* d, s32 e);
void ReleaseCounterRef(void* p);
void SetStateWalkerTarget(void* a, s32 b);
void TeleportStateWalker(void* a, s32 b);
s32 TestFlagTableBit(void* a, s32 b);
void SetFlagTableBit(void* a, s32 b);
void TriggerScriptEvent(BaseObject* self, s32 a, s32 b, s32 c);
s32 PushSoundLevel(s32 a);
s32 IncrementCounter(void* p);
void StartSoundEffect(s32 a0, void* a1, StateTrigger* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

// The position curves' tables, defined at the end of this file.
extern const PositionCurveVt g_positionCurveKind0Methods;
extern const PositionCurveVt g_positionCurveKind1Methods;
extern const PositionCurveVt g_positionCurveKind2Methods;
void* AllocateZeroedFrontMemory(s32 bytes);

void RemoveFromList(void* a, void* b);
void ConstrainColliderVector(void* a, void* b, void* c, void* d, s32 e);
void SetPlacedObjectVelocity(void* a, void* b);
void SetPlacedObjectSpin(void* a, void* b);
void PushFreeSlot(void* a, void* b);


s32 FindCyclicRangeIndex(f32 x, f32 period, s32 count, BlendTimeScale* p, f32* out);
f32 WrapAngle(f32 a);

extern const RotationCurveVt g_rotationCurveKind0Methods;
extern const RotationCurveVt g_rotationCurveKind1Methods;
extern const RotationCurveVt g_rotationCurveKind2Methods;

extern const ScaleCurveVt g_scaleCurveKind0Methods;
extern const ScaleCurveVt g_scaleCurveKind1Methods;
void* AllocateZeroedFrontMemory(u32 n);

extern u8 D_00219560[];

void InitPoseSource(Attachment* self);

// The dispatch tables func_00121160 gives each kind of curve: three functions, or one and a
// shared one, each table followed by a zero word.
void EvaluateTangentWeightCurve();
void ReadTangentWeightCurve();
void GetTangentWeightCurveTimes();
void EvaluateControlPointWeightCurve();
void ReadControlPointWeightCurve();
void GetControlPointWeightCurveTimes();
void EvaluateLinearWeightCurve();
void ReadLinearWeightCurve();
void GetLinearWeightCurveTimes();
void GetNoWeightCurveTimes();
void EvaluateAngleBlendCurve();
void EvaluateValueBlendCurve();
void GetAxisRotationCurveKeyTimes();
void EvaluateKeyedRotationCurve();
void GetKeyedRotationCurve();
void ReadKeyedRotationCurve();
void GetKeyedRotationCurveKeyTimes();
void EvaluateAxisScaleCurve();
void ReadAxisScaleCurve();
void GetAxisScaleCurveKeyTimes();
void EvaluateKeyedScaleCurve();
void ReadKeyedScaleCurve();
void GetKeyedScaleCurveKeyTimes();
extern const WeightCurveVt g_weightCurveKind0Methods;
extern const WeightCurveVt g_weightCurveKind1Methods;
extern const WeightCurveVt g_weightCurveKind2Methods;
extern const WeightCurveVt g_weightCurveKind3Methods;
extern const WeightCurveVt g_weightCurveKind4Methods;
void* AllocateZeroedFrontMemory(WeightCurve* n);

void SetListLinkOffset(void* list, s32 n);
void InitObject(BaseObject* self);

// Two stores of the set-up written as small inline helpers, the shape that matches: a value
// passed as an int, and a matrix copied through its own pointer (as each copy's own register).
struct SetupStores {
    static void SetB2CA(PlacedObject* o, s32 value) { o->b2CA = value; }
    static void Copy(Mat02* dst, const Mat02* src) { *dst = *src; }
};

#include "world.h"
#include "object_cycler.h"
#include "paired_object.h"

void UnregisterObject(BaseObject* self);
void ClearList(void* a);
void DissolveObjectLinkList(World* world, void* b);
void RemoveCameraObject(void* a, PlacedObject* b);
void ClearRootTries(PlacedObject* self);
void TriggerScriptEvent(PlacedObject* self, s32 a1, s32 a2, s32 a3);

extern WorldObjectNode* AddObjectNodeToWorld();
extern s32 IsObjectAttached(void*);

extern void MatrixToEulerAngles(void*, void*);


s32 IsObjectAttached(void* self);

// What slot 29 tells the object's listeners (kind 3): the position before, and the object.
struct MoveNotice {
    void* self;
    u8 pad[0xC];
    Vec02 q;
};

void SettlePoseSourceModes(void* p);

s32 IsVelocityNegligible(void* a);
void ClearRootTries(void* self);

s32 IsSpinNegligible(void* a);



void UpdateObjectTree(void* self, f32 f);


void ResolveFollowRecordObjects(void* self);
void SavePlacedObjectInitialFrame(void* self);
void SetAimTarget(void* self, void* v);
void BindAttachmentTargets(void* a, void* b);


void StartSoundEffect(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, s32 a5);

void RegisterObject(BaseObject* self);
void AppendToList(void* list, void* item);
void MergeObjectGroupMembers(World* world, PlacedObject* item);
void AddCameraObject(PlacedObject* a, PlacedObject* self);


void StartObject(BaseObject* self);
void StartAnimationFromContext(PlacedObject* self);
void* AppendQueuedCall(void* owner, void* fn, PlacedObject* arg, s32 a3, s32 a4);
void StartAttachments(void* a, PlacedObject* b);
s32 HasRangeRecordRanges(RangeRecord* p);
void StoreRangeRecordNear(RangeRecord* p, f32 v);
void StoreRangeRecordFar(RangeRecord* p, f32 v);
void BuildTexturePackets(void* a, RangeRecord* b);
void PrepareRangeRecord(RangeRecord* p);
void StartSoundEffect(s32 a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, PlacedObject* a2, s32 a3, void* a4, s32 a5);
s32 MatchesObjectId(BaseObject* a, s32 b);
s32 IsObjectAttached(BaseObject* p);

void CopyObjectData(BaseObject* self, BaseObject* src);
void CopyAttachmentBlock(u8* a, PlacedObject* self, u8* src);
void* CopyToFrontMemory(s32 size, void* src);
Attachment* ClonePoseSource(Attachment* src, World* world, PlacedObject* self);
void InsertAttachment(PlacedObject* self, void* v);
u8* TakePoolSlot(Pool6C* pool);
void CopyMemory(u8* dst, void* src, s32 n);
void ClearListLinks(u8* p);
void AddCameraObject(void* list, PlacedObject* item);

// NEAR: the branches and the 0x40-byte copy loop match; retail loads both quads of a pair before
// storing them (and computes the loop end in $v0), ours interleaves load and store.

struct ScaledTransform {
    Quad16 q[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4c;
};

extern u8 D_00248D40[];

void BuildScaledTransformMatrix(Vec02* a, Mat02* b, u8* c, void* d);

void ResolveAndStartObject(void* node);
void AddObjectListener(void* node, BaseObject* ctx);


struct ListWalkNext {
    static BaseObject* Of(ListFrame* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct ListWalkBegin {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = (ListFrame*)it;
    }
};



void* CreateObjectCopy(BaseObject* item, World* world, PlacedObject* parent);
void UpdateAnchorModeFlags(PlacedObject* self);


void UpdateAttachments(u8* sub, PlacedObject* self, f32 f);
void UpdateRangeRecord(void* p, f32 f);
void func_00126AC8(PlacedObject* self, f32 f);
void TriggerScriptEvent(PlacedObject* self, s32 a, s32 b, void** args);

void func_0012C9E8(Animation* a, PlacedObject* b, f32 c, void* d, f32* e, s32 f, s32 g);
void CreateAnimationPlayer(Animation* a, PlacedObject* b, s32 c, TargetBinding* d, f32 e, f32 f, s32 g, s32 h);

// A value kept within [lo, hi].
struct ClampRange {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

struct FindStartAnimation {
    static Animation* Of(PlacedObject* self, AnimationStart* ctx)
    {
        if (ctx->anim != 0) {
            return ctx->anim;
        }
        return (Animation*)FindFirstObjectById(self->world, 0x104, ctx->key, self);
    }
};

struct StartBindingFrame : TargetBinding { u8 pad0[8]; f32 tmp; };

struct TakeFrameLocals {
    u8 a20[16];
    u8 a30[16];
    u8 a40[16];
    u8 a50[16];
    u8 pad60[0x30];
};

void TransformPointBetweenFrames(PlacedObject* z, BaseObject* frame, void* c, u8* d);
void TransformRotationBetweenFrames(PlacedObject* z, BaseObject* frame, void* c, u8* d);
void func_00128330(BaseObject* a, BaseObject* b, void* c, void* d, void* e, s32 f, s32 g, u8* h, u8* i, s32 j, s32 k);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_002197C0[10];
Attachment* CreatePoseSource(World* root, BaseObject* item, void* table);

void SetOrientationSourceMode(void* self, s32 a1);

void EnsureAimAttachment(void* self);

extern u8 D_00275C40[];

extern u8 g_unitRange[];

void* EnsureRangeRecord(f32 x);
void StoreRangeRecordFar(void* p, f32 x);

extern RangeRecord D_0027B520;
void InitRangeRecord(void* p);

void* AllocateFrontMemory(s32 n);


void SetRotationRamp(void* self, f32* v);

void SetGroupActivityMode(void* self, s32 flag);

void* ResolveAimTarget(void* p);

Class75Object* FindOrCreateClass75Object(void* self);

void EnsureSoundRecord(void* self, f32 f);


void SetSoundRecordPitch(void* p);

extern ColorRecord g_colorPresets[4];

void EnsureColorRecord(void* self);


void* FindCommonAncestor(void* a0, s32 a1);


void* AllocateZeroedFrontMemory(s32 size);

void* PopZeroedFreeSlot(void* a0);
void InitRangeRecord(void* a0);
void AppendToList(void* a0, void* a1);

void EnsureAimAttachment(PlacedObject* self);

void* CreateTypedRecord(s32 a0, s32 a1, void* a2, s32 a3, s32 a4);

void* EnsureRangeRecord(void* self);
void LinkRangeRecord(void* self, s32 value);

void* EnsureRangeRecord(void* self, f32 x);
void StoreRangeRecordNear(void* self, f32 v);





void EnsureSoundRecord(PlacedObject* self);

s32 IsObjectAttached(PlacedObject* self);
void AddCameraObject(Camera* a, PlacedObject* self);
void RemoveCameraObject(Camera* a, PlacedObject* self);

void StoreRangeRecordInner(void* self, f32 x);

void StoreRangeRecordOuter(void* self, f32 x);

void ScaleRangeRecordByAngle(void* self, f32 x);

void StoreRangeRecordVector(void* self, void* src);

// A quadword moved whole (lq/sq), and the frame of the four scaled-spring setters: the
// default profile, the argument as a quadword and their product.
typedef u64 U128 __attribute__((mode(TI)));
struct ScaledSpringFrame { U128 r; U128 a; U128 b; };

void StoreFloatAsQuadword(U128* out, void* src);
void* CopyQuadword(U128* out, void* src);
U128 ScaleQuadword(U128 a, U128 b);
U128 StoreQuadword(U128* out, U128 v);
void SetVelocitySpring(void* self, U128* src);

// A ramp profile (+0x21C, +0x220) as the setters copy it: four floats at an address they do not
// trust to be aligned.
struct __attribute__((packed)) RampProfile { f32 x, y, z, w; };

void SetPositionRamp(PlacedObject* self, RampProfile* src);

void* AllocateFrontMemory(s32 size);


extern void SetRotationRamp(PlacedObject* self, RampProfile* in);

void* AllocateFrontMemory(u32 size);


void SetSoundRecordVolume(void* p);

RangeRecord* GetRangeRecord(void* self);

s32 MatchesObjectId(void* key, s32 item);





void SetPositionSpring(void* self, U128* v);


// Newly matched US functions from the small-function wave.
extern void SetPositionSourceMode(void*, s32);
extern void InitSoundParams(void*);
extern s32 MatchesObjectId(void*, s32);
extern void EnsureBaseAttachment(void*);
extern void SortAttachments(void*);
extern void EnsureAimAttachment(void*);
extern void EnsureSoundRecord(void*);
extern void StopSoundRecord(void*, s32);
extern void EnsureColorRecord(void*);

f32 ArctangentOfRatio(f32 a, f32 b);

void SetScrollScale(void* part, f32 a, f32 b);

void SetCrossfadeRatio(void* part, f32 value);

extern ColorRecord g_defaultColorRecord[2];

void StopSoundRecord(void* ptr, s32 value);

void InsertBeforeInList(void* list, Attachment* before, Attachment* value);

void MatrixToEulerAngles(void* a, f32* out);

struct EulerLocals { f32 tmp[4]; f32 out[4]; u8 pad[0x20]; };

void BuildEulerRotationMatrix(void* a, void* b);

void InitObject(void* self);
void SetListLinkOffset(void* self, s32 value);

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)

void StopSoundRecord(void* self, s32 n);
void StartSoundEffect(void* a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, void* a2, s32 a3, void* a4, s32 a5);

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)

// NEAR: same bytes except the prologue order: retail loads the crc word and the table base before the n > 0 test (lw v0, addiu t1, then blez); ours tests first
s32 g_checksumMismatch[4];

void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);

s32 ReadBufferedS16(Stream83* p);
s32 ReadBufferedU16(Stream83* p);
s32 ReadBufferedS8(Stream83* p);
s32 ReadBufferedU8(Stream83* p);
void MoveAnimationTrackToEnd(Animation* a, Track83* b);
void ReadAnimationEvents(Animation* a, Stream83* b, s32 c, s32* d, AnimEvent** e);
void ReadPropertyRecords(Animation* a, Stream83* b);
PositionCurve* CreatePositionCurve(s32 cc);
RotationCurve* CreateRotationCurve(s32 cc);
ScaleCurve* CreateScaleCurve(s32 cc);
WeightCurve* CreateWeightCurve(s32 cc);

void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);
void TransformRotationBetweenFrames(void* a, void* b, void* c, void* d);

s32 ReadBufferedU32(void* a);
void ReadBufferedRotation3(void* a, void* b);
s32 ReadBufferedS16(void* a);
void ReadBufferedVector3(void* a, void* b);
f32 ReadBufferedFloat(void* a);
s32 ReadBufferedU8(void* a);

void SetRotationSpring(PlacedObject* self, U128* src);

void SetSpinSpring(PlacedObject* self, U128* src);

void InsertAttachment(PlacedObject* self, Attachment* src);

extern u8 D_0021A790[];

extern const Fn_Table D_002195D8[];

void AssignAimTarget(void* a, void* b, void* c);

extern const Fn_Table D_00219600[];




void FillMemory(void** p, s32 v, s32 n);
void SettlePoseSourceModes(Attachment* n);

struct Sub_12BC38 { s32 w0; s32 w4; s32 w8; s32 wC; s32 w10; };
// The 0x28-byte record of a kind 0 event (a sound): up to six sound ids, one picked at random
// each time other than the last (func_0012D5D0), the object it plays on, and its ranges.
struct SoundChoice {
    s16 count;
    s16 ids[6];
    s16 cur;
    s16 target;
    u8 pad12[2];
    s32 f14;
    s32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
};

s32 ReadBufferedS8(Stream83* r);
void* AllocateZeroedFrontMemory(s32 n);
void ReadOptionalBufferedBlock(Stream83* r, void* out);
s32 ReadBufferedS16(Stream83* r);
s32 ReadBufferedS32(Stream83* r);
f32 ReadBufferedFloat(Stream83* r);
s32 ReadBufferedU8(Stream83* r);
s32 ReadBufferedU16(Stream83* r);
void ReadBufferedStreamBytes(Stream83* r, s32 n, void* dst);
void ReadBufferedString(Stream83* r, void* out);

#define F32(x) (*(f32*)&(x))
#define H0(x) (*(s16*)&(x))
#define H2(x) (*((s16*)&(x) + 1))

// An entry of the table at PlacedObject::f2BC (f2B8 of them): a key and the values it selects.
struct KeyedValues { s32 key; f32* values; };

// Sets an attachment's mode3 and tells whether it changed.
struct SetMode3 {
    static s32 Of(Attachment* a, s32 v) { s32 o = a->mode3; a->mode3 = v; return o != v; }
};
extern const Fn_Table D_002195B0[];

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void CopyPoseSource();
void ReleasePoseSource();
void InitLinkedPoseSource();
void GetLinkedPosition();
void GetLinkedRotation();
void GetLinkedValue();
void GetLinkedMatrix();
f32 GetLinkedIndexedValue();
void InitIdentityPoseSource();
void GetIdentityPosePosition();
void GetIdentityPoseRotation();
void GetNextPoseSourceValue();
void GetIdentityPoseMatrix();
f32 GetIdentityPoseIndexedValue();
void EvaluateNoPositionCurve();
void GetNoPositionCurveTimes();
void EvaluateNoRotationCurve();
void GetNoRotationCurve();
void GetNoRotationCurveTimes();
void EvaluateNoScaleCurve();
void GetNoScaleCurveTimes();
void EvaluateNoWeightCurve();
void GetOwnerPosition();
void GetOwnerValue();
void GetIdentityMatrix();
f32 GetOwnerIndexedValue();
void InitAimPoseSource();
void GetAimPoseRotation();
extern const Fn_Table D_002195B0[10];
extern const Fn_Table D_002195D8[10];
extern const Fn_Table D_00219600[26];

// The script list a property getter fills (file_1B7968 defines it; AppendPropertyToScriptList).
struct ScriptListBuilder;
s32 AppendPropertyToScriptList(ScriptListBuilder* context, PlacedObject** obj);

struct ListWalkNextPlaced {
    static PlacedObject* Of(ListFrame* it)
    {
        PlacedObject* obj = *(PlacedObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

void RemoveFromList(List01* list, Attachment* node);
void InsertBeforeInList(List01* list, Attachment* at, Attachment* node);

struct NextAttachment {
    static Attachment* Of(ListFrame* it)
    {
        Attachment* node = *(Attachment**)it->link;
        it->link = (u8*)node + it->offset;
        return node;
    }
};

ColorRecord g_colorPresets[4] = {
    { { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x42F00000, 0x433E0000, 0x42E60000, 0x00000000, 0x42F00000, 0x433E0000, 0x42700000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x437F0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x42F00000, 0x437F0000, 0x437F0000, 0x00000000, 0x42F00000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x43700000, 0x437F0000, 0x437F0000, 0x00000000, 0x43700000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } }
};

ColorRecord g_defaultColorRecord[2] = {
    { { 0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x437F0000, 0x437F0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000005, 0x00000000, 0x00000000, 0x00000000, 0x43960000, 0x437F0000, 0x437F0000, 0x00000000, 0x43960000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } }
};

void InitPoseSource();
void CopyTrackPoseSource();
void ReleaseTrackPoseSource();
void GetTrackPosition();
void GetTrackRotation();
void GetTrackValue();
void GetTrackScaleMatrix();
void GetTrackIndexedValue();

extern u8 D_00148D64[];
void InitPlacedObject(void* self);

s32 CreateAnimationPlayer(void* a, void* b, s32 c, s32 d, s32 e, s32 f);

void* FindEntryByObjectId(void);

s32 MatchesObjectId(void* a, void* b);

void ApplyPoseSource(void* n, void* b);


void AddCallbackNode(void* a, void* b, void* c, s32 d);

s32 IsReadPending(StreamReader* self);
s32 CloseFile(s32 h);
s32 SyncDiscNCommand(s32 x);
void CommitChunk(StreamReader* self);

void CopyObjectData(void);

void StartObject(void* self);
void StartLinkedObjectAnimation(void* self);
void AppendQueuedCallOnce(void* host, void* cb, void* ctx, s32 a3, s32 a4);

s32 CreateAnimationPlayerWithoutPresetTargets(void* self, s32 a1, s32 a2, s32* out, f32 fa, f32 fb);

void CreateAnimationPlayer(void* self, s32 a1, s32 a2, s32 a3, s32 a4, void** out);

void* FindAnimationPlayerByScope(void* self, s32 key);
s32 CreateAnimationPlayerWithoutPresetTargets(void* self, s32 a1, s32 a2, void** out, f32 fa, f32 fb);
void SeekAnimationPlayer(void* obj, s32 a1, f32 fa, f32 fb);

void FindOrCreateAnimationPlayerAndSeek(void* self, s32 key, s32 a2, s32 a3, void** out, f32 fa, f32 fb);

void SetAnimationPlayerSpeed(AnimationPlayer* self, f32 x);
void ApplyListedPoseSources(AnimationPlayer* self, s32 zero);
void SettleListedPoseSources(AnimationPlayer* self);
void RunSeekAnimationEvents(AnimationPlayer* self, Animation* sub, s32* out);
void StopAnimationPlayer(AnimationPlayer* self);
void SeekAnimationEventCursor(AnimationPlayer* self);

void SettlePoseSourceModes(T2195_7C0* item);

void RemoveFromList(u8* a, void* b);
void PushFreeSlot(u8* a, void* b);

Attachment* FindPlayerAttachmentByOwner(void* a0, void* a1);

void SortAttachments(void* p);


void* FindAnimationMarkerEvent(void);

void AddCallbackNode(void* a, void* b, void* c, void* d);

void SetColliderAnchors(Collider* self, s32 a, Vec02* b, s32 c, Vec02* d);

void CopyCollider(Collider* self);
void InitContactPairFlags(void* a, void* b);

s32 ControlFile(s32 a, s32 b, s32* c);
s32 GetDiscError(void);

void FreeObjectMemory(void* self);

s32 OpenSectorStream(void* self, s32 a, s32 b);

void AcquirePadSelectFlag(void* a);
void ReleasePadSelectFlag(void* a);

void StopAnimationPlayer(void* obj);
s32 CreateAnimationPlayerWithoutPresetTargets(void* self, void* a1, f32 fa, f32 fb, void* a2, void** out);

s32 MatchesObjectId(void* a, s32 b);


s32 TestCollidersMayContact(Collider* self, Collider* key);
s32 IsObjectOfKind(void* key, s32 kind);

void StartChunkRead(StreamReader *self);

s32 PollChunkRead(StreamReader* a0);

struct AnimationPlayerTable { const void* tinfo; s32 f4; };
extern const AnimationPlayerTable g_animationPlayerMethods;
void* PopZeroedFreeSlot(Pool6C* pool);
void SetListLinkOffset(List01* self, s32 value);


void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);

struct EndEventLocals { s32 a; s32 b; };

void RunAnimationEvent(AnimationPlayer* self, AnimEvent* item, EndEventLocals* out);
void NotifyAnimationPlayerCallbacks(AnimationPlayer* self, s32 a, AnimationPlayer* b);
void ReleaseCallRecords(u8* self, void* node);
void UnregisterObjectGroup(u8* a, u8* s);
void SetAnimationPlayerPadSelect(AnimationPlayer* self, s32 v);
void RemoveQueuedCalls(u8* a, s32 b, s32 c, AnimationPlayer* d, s32 e, s32 f);
void RemoveFromList(u8* a, AnimationPlayer* b);
void AppendToList(u8* a, AnimationPlayer* b);
void ClearSoundRecordHandle(s32* slot);
void TriggerScriptEvent(Animation* self, s32 a, s32 b, s32* c);

f32 FloatRemainder(f32 a, f32 b);
f32 WrapModulo(f32 a, f32 b);

void MoveMemory(Track83* dst, Track83* src, s32 bytes);


// was NEAR: call result is stored directly (retail copies v0 to v1 first, then s1=v1 for the out pointer); 5 lines differ


void* AllocateBackMemory(s32 size);

struct EventObjectPair {
    s32 f0;
    s32 f4;
    s32 f8;
    f32 fC;
};
union EventScratch {
    SlotMessage req;
    Vec4U v[3];
    void* p[3];
    s32 w[3];
};


extern u8 g_screenFade[];

extern u8 g_padRecord[];
extern u8 g_moviePlayer[];
extern u8 g_elementStack[];

s32 CheckStreamVoicePending(void);
void OpenKeyRecord(void* p);
void StopStreamVoice(void);
s32 RandomIntInRange(s32 lo, s32 hi);
s32 IsSoundEntryAvailable(s32 id);
void StartSoundEffect(s32 id, void** handle, Collider* target, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void StopSoundRecord(void* h, s32 n);
void RestoreVolumeChannel2(void);
void SilenceVolumeChannel2(void);
void ChooseStepSequenceState(Collider* t);
s32 FadeInPlacedObject(Collider* t, f32 v);
s32 FadeOutPlacedObject(Collider* t, f32 v);
void SetColliderAnchors(Collider* t, s32 a, s32 b, s32 c, s32 d);
void PushObjectCameraController(Collider* t);
void RemoveObjectCameraController(Collider* t);
void SwitchPlayerState11(Player* g, s32 flag);
void ApplyListedPoseSources(AnimationPlayer* self, s32 v);
// the node keeps the inline setter of its second mode byte that retail's code calls (see NOTES.md)
struct TrackAttachment : T2195_7C0 {
    void SetMode(s32 mode) { mode1 = mode; }
};
TrackAttachment* FindPlayerAttachmentByOwner(AnimationPlayer* self, s32 key);
void ChoosePoseSourceModes(TrackAttachment* n);
void StartScreenFade(u8* dst, s32 a, s32 b);
void SaveFadeRequest(u8* dst, s32 a, s32 b);
void BeginLevelExit(s32 a, s32 b);
void StartTimer(T217D_510* p, f32 x);
void StartTimerCounting(T217D_510* p);
void StopTimer(T217D_510* p);
s32 CreateAnimationPlayerWithoutPresetTargets(Collider* a, Collider* b, s32 c, s32 d, f32 x, f32 y);
void StartPadRecordPattern(u8* p, s32 n, f32 f);
void TriggerScriptEvent(void* self, s32 a, s32 b, void* c);
void NotifyAnimationPlayerCallbacks(AnimationPlayer* self, s32 a, void* b);
void SelectValueEntryByKey(Collider* t, s32 key);
void* FindListNodeByKey(Collider* a, Collider* b);
void* CreateStateWalker(Collider* a, Collider* b, s32 c, s32 d);
void DestroyStateWalker(void* o);
s32 IsObjectOfKind(Collider* n, s32 kind);
void ConvertPositionToWorld(Collider* n, Vec4U* out);
s32 GetObjectWorldPosition(Collider* n, Vec4U* out);
s32 IsObjectAttached(void* p);
void ShowCountedScreenElement(World* w);
void HideCountedScreenElement(World* w);
void QueueMovie(u8* a, s32 b);
void ResizeItemColumn(T217D_720* self, s32 n, f32 x, f32 y);
void ClearItemColumn(T217D_720* self);
void PostItemColumnEntry(T217D_720* self, s32 a, s32 b, f32 x);
void SetElementStackState(u8* obj, s32 mode);
void SetWorldValueAndTarget(World* w, f32 v);
void SetWorldValueTarget(World* w, f32 v);
void BindEntryQueueToObject(Collider* t, Player* g);

struct FalloffRange { u32 field0; f32 minimum; f32 maximum; };
struct RangeFalloffOwner { u8 pad0[8]; FalloffRange* range; };

s32 ReadFile(void* p, s32 a, s32 b);
void StartLowLevelDiscReadUntilAccepted(void* p, s32 n, s32 base);



void StartPlacedObject(PlacedObject* self);
s32 IsObjectOfKind(void* n, s32 kind);


// kept: the bitfields make `n->f10 = n->f11 = 3` store from two registers, as retail does
struct TrackAttachmentBits {
    u8 pad0[0x10]; s32 f10 : 8; s32 f11 : 8; s32 f12 : 8; s32 f13 : 8; s32 f14;
    u8 pad1[0x1C - 0x18]; AnimationPlayer* f1C;
    u8 pad2[0x28 - 0x20]; s32 f28;
};

void AppendToList(u8* list, AnimationPlayer* o);
void AppendToList(u8* list, TrackAttachmentBits* n);
void PushBackMemoryMark(void);
TrackAttachmentBits* CreateTrackAttachment(PlacedObject* h);
void PushFreeSlot(u8* list, TrackAttachmentBits* n);
void ChoosePoseSourceModes(TrackAttachmentBits* n);
void InsertAttachment(PlacedObject* h, TrackAttachmentBits* n);
void PopBackMemoryMark(void);
void RegisterObjectGroup(World* w, u8* p);
void RunAnimationEvent(AnimationPlayer* o, AnimEvent* item, s32* out);
void ApplyListedPoseSources(AnimationPlayer* o, s32 flag);
void TriggerScriptEvent(Animation* self, s32 a, s32 b, AnimationPlayer*** c);

void SampleCurvePoints(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, s32 n, void* buf);
void AccumulateSegmentLengths(s32 n, void* buf, s32 zero);

void SetTextPanelSubject(void* self, s32 arg);

void StartChunkRead(void* self);
void CommitChunk(void* self);

extern u8 g_markStacks[];
void* NewKeyedList(void);
void AddMarkRootList(void* dst, void* value);


struct SampledCurve;
struct CurvePoint { u8 pad0[16]; };

void EvaluateHermiteVectorSegment(f32 f12, SampledCurve* a, u8* b, u8* c, u8* d, f32 f13, f32 f14, s32 a4, s32 a5, s32 a6);

void ReleaseCountedObject(CountedObject* object)
{
	if (!object->hold)
		CountStateTriggerDone(object->counter);
	HandleMaskedColliderActivation(object);
}

void SetCountedObjectCounter(CountedObject* state, StateTrigger* value)
{
    state->counter = value;
}

void InitStateTrigger(StateTrigger* self)
{
    InitCollider(self);
    self->state = -1;
    self->id6B0 = TakeFlagTableIndex(g_flagTable);
}

void StartStateTrigger(StateTrigger* self)
{
    WordListFrame fr;
    s32 s0;
    AppendQueuedCall(self->world, (void*)ResolveStateTriggerObjects, self, 0, 0);
    StartPlacedObject(self);
    s32 e = (s32)&self->children;
    fr.link = e;
    fr.list = e;
    s32 link = *(s32*)(e + 8);
    s32 old = (s32)g_activeListFrames;
    fr.prev = old;
    fr.offset = link;
    g_activeListFrames = (ListFrame*)&fr;
    s32 head = *(s32*)e;
    fr.link = head + fr.offset;
    s0 = head;
    if (s0 != 0) {
        do {
            if (IsObjectOfKind((void*)s0, 0x88) != 0) {
                if (self->found558 == 0) {
                    self->found558 = (void*)s0;
                }
            }
            s32 nx = *(s32*)fr.link;
            fr.link = nx + fr.offset;
            s0 = nx;
        } while (s0 != 0);
    }
    if (self->found558 != 0) {
        self->f55C = (StateWalker*)CreateStateWalker(self->found558, self, -1, 1);
        ResolveAndStartObject(self->found558);
    }
    g_activeListFrames = (ListFrame*)fr.prev;
}

void CopyStateTrigger(StateTrigger* object)
{
	s32 value = object->id6B0;
	CopyCollider(object);
	object->id6B0 = value;
}

void UpdateStateTrigger(StateTrigger* self)
{
    UpdateCollider(self);
    if (self->state == 2 && self->timeout != 0.0f) {
        if (self->timeout < g_gameTime[0] - self->stateTime) {
            SetStateTriggerState(self, 0);
            goto done;
        }
    }
    if (self->count1 > 0) {
        if (self->done == self->count1) {
            SetStateTriggerState(self, 1);
            goto done;
        }
    }
    if (self->state != 2) {
        goto done;
    }
    if (g_player->f2220 != 9) {
        goto done;
    }
    for (s32 i = 0; i < self->count1; i++) {
        void* p = FindFirstObjectById(self->world, 0x104, self->items1[i], self);
        if (p != 0 && IsObjectOfKind(p, 0x22) != 0) {
            CountedObject* o = (CountedObject*)p;
            o->desc20()->m48(o);
        }
    }
done:
    ;
}

void ResolveStateTriggerObjects(StateTrigger* self)
{
    s32 kept = 0;
    s32 i;
    for (i = 0; i < self->count1; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items1[i], self);
        if (node && IsObjectOfKind(node, 0x22)) {
            SetCountedObjectCounter((CountedObject*)node, self);
            kept++;
        }
    }
    self->count1 = kept;
    for (i = 0; i < self->count2; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items2[i], self);
        if (node && IsObjectOfKind(node, 0x30)) {
            s32 idx = self->outCount;
            self->outItems[idx] = (TimedObject*)node;
            self->outCount = idx + 1;
            ((TimedObject*)node)->desc30()->m4C((TimedObject*)node, self);
        }
    }
    for (i = 0; i < self->count3; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items3[i], self);
        if (node && IsObjectOfKind(node, 8)) {
            AddAgentStateTrigger(node, self);
        }
    }
    if (TestFlagTableBit(g_flagTable, self->id6B0)) {
        SetStateTriggerState(self, 1);
    } else {
        SetStateTriggerState(self, 0);
    }
}

void SetStateTriggerState(StateTrigger* self, s32 mode)
{
    s32 cur = self->state;
    if (cur == mode) {
        return;
    }
    if (cur < 0) {
        goto store;
    }
    if (cur < 2) {
        goto store;
    }
    if (cur != 2) {
        goto store;
    }
    StopSoundRecord(self->f620, 0);
    ReleaseSoundLevel(self->f624);
    SetGatheredWalkerTargets(self->world, self->count62C, self->table630, self, 0);
    if (mode == 1) {
        ReleaseCounterRef(D_002623D8);
    }
store:
    self->state = mode;
    self->stateTime = g_gameTime[0];
    if (mode == 1) {
        goto arm1;
    }
    if (mode < 2) {
        if (mode == 0) {
            goto arm0;
        }
        return;
    }
    if (mode == 2) {
        goto arm2;
    }
    return;
arm0:
    if (self->f55C != 0) {
        SetStateWalkerTarget(self->f55C, 0x21A);
    }
    ResetStateTriggerOutputModes(self);
    return;
arm1:
    if (self->f55C != 0) {
        TeleportStateWalker(self->f55C, 0x220);
    }
    EndStateTriggerOutputs(self);
    if (TestFlagTableBit(g_flagTable, self->id6B0) != 0) {
        TriggerScriptEvent(self, 0x16, 0, 0);
    } else {
        TriggerScriptEvent(self, 3, 0, 0);
    }
    SetFlagTableBit(g_flagTable, self->id6B0);
    return;
arm2:
    if (self->f55C != 0) {
        SetStateWalkerTarget(self->f55C, 0x21F);
    }
    if (self->f628 == 0) {
        StartSoundEffect(0x15, &self->f620, self, 0, 8000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    self->f624 = PushSoundLevel(0x6B);
    FinishStateTriggerOutputs(self);
    SetGatheredWalkerTargets(self->world, self->count62C, self->table630, self, 1);
    TriggerScriptEvent(self, 2, 0, 0);
    IncrementCounter(D_002623D8);
}

void SetStateTriggerStateFromMessage(StateTrigger* object, s32 mode)
{
    s32 mapped;
    switch (mode) {
    case 0: mapped = 2; break;
    case 1: mapped = 0; break;
    case 2: mapped = 1; break;
    default: return;
    }
    SetStateTriggerState(object, mapped);
}

void CountStateTriggerDone(StateTrigger* counter)
{
	counter->done++;
}

void ResetStateTriggerOutputModes(StateTrigger* self)
{
    for (s32 i = 0; i < self->outCount; i++) {
        TimedObject* e = self->outItems[i];
        if (e->f560 == -1 && e->desc30()->m49 != 0) {
            e->desc30()->m49(e, 0);
        }
    }
}

void EndStateTriggerOutputs(StateTrigger* self)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        TimedObject* c = self->outItems[i];
        void (*fn)(TimedObject*) = c->desc30()->m4A;
        if (fn != 0) {
            fn(c);
        }
    }
}

void FinishStateTriggerOutputs(StateTrigger* self)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        TimedObject* it = self->outItems[i];
        void (*fn)(TimedObject*) = it->desc30()->m4B;
        if (fn != 0) {
            fn(it);
        }
    }
}

void AddStateTriggerCountedId(StateTrigger* self, s32 value)
{
    u32 n = self->count1;
    if (n < 4) {
        self->items1[n] = value;
        self->count1 = n + 1;
    }
}

void AddStateTriggerItemId(StateTrigger* self, s32 value)
{
    u32 n = self->count2;
    if (n < 16) {
        self->items2[n] = value;
        self->count2 = n + 1;
    }
}

void AddStateTriggerAgentId(StateTrigger* self, s32 value)
{
    u32 n = self->count3;
    if (n < 6) {
        self->items3[n] = value;
        self->count3 = n + 1;
    }
}

void AddStateTriggerTableEntry(StateTrigger* object, void* a1, void* a2, void* a3, void* a4)
{
	UpsertKeyedEntry((u8*)object + 0x630, 8, (u8*)object + 0x62C,
			  a1, a2, a3, a4);
}

s32 TestStateTriggerItemsAccepted(StateTrigger* self, void* arg)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        if (AppendPropertyToScriptList(arg, &self->outItems[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

ASM_FUNC(func_00123DC0);

ASM_FUNC(func_00123E00);

ASM_FUNC(func_00123E48);

ASM_FUNC(func_00123E88);

void InitPlacedObject(PlacedObject* self)
{
    SetListLinkOffset(&self->children, 0x1C);
    SetListLinkOffset(&self->list60, 0x58);
    if (self->parent != 0) {
        self->bits24 = 1;
        self->bits26 = 0;
    } else {
        self->bits24 = 2;
        self->bits26 = 2;
    }
    InitObject(self);
    self->f80 = 3.4028235e+38f;
    self->f88 = 0x0FFFFFFF;
    self->f84 = 3.4028235e+38f;
    SetupStores::SetB2CA(self, -1);
    self->b2C9 = -1;
    self->p20C = (u8*)D_00260E70;
    self->p210 = (u8*)D_00260E80;
    self->p214 = (u8*)D_00260E90;
    self->p218 = (u8*)D_00260EA0;
    self->p21C = (u8*)D_00260EB0;
    self->p220 = (u8*)D_00260EC0;
    self->b2C8 = 0;
    SetupStores::Copy(&self->rot, &g_identityMatrix);
    SetupStores::Copy(&self->m110, &g_identityMatrix);
    SetupStores::Copy(&self->m1A0, &g_identityMatrix);
    SetListLinkOffset(&self->list1E0, 8);
}

void AttachPlacedObject(PlacedObject* self)
{
    ListFrame it;
    ListWalkBegin::Of(&it, &self->children);
    self->desc->m06(self);
    BaseObject* obj;
    while ((obj = ListWalkNext::Of(&it)) != 0) {
        obj->desc->m04(obj);
    }
    self->desc->m0E(self, 1, self);
    g_activeListFrames = (ListFrame*)it.prev;
}

void RegisterPlacedObject(PlacedObject* self)
{
    Vec02 v0;
    Vec02 v1;
    Mat02 rot;
    RegisterObject(self);
    World* ctx = self->world;
    if (!self->parent) {
        self->root = self;
        if (self->f294) {
            AppendToList(&ctx->list78, self);
        } else {
            AppendToList(&ctx->list54, self);
            self->flags |= 0x2000000000ULL;
            AppendToList(&ctx->list60, self);
            if (self->desc->flags & 2) AppendToList(&ctx->list6C, self);
            s32 n = self->count6C;
            self->f54 = self;
            self->list60.tail = self;
            n--;
            self->list60.head = self;
            for (; n >= 0; n--) MergeObjectGroupMembers(ctx, self->items70[n]);
        }
    } else {
        self->root = ((PlacedObject*)self->parent)->root;
        if (((PlacedObject*)self->parent)->flags & 0x4000000000ULL) {
            if (self->desc->m14) self->desc->m14(self, 1);
        }
    }
    if (self->f1EC) {
        self->f1EC->vt->getPos(self->f1EC, 0.0f, &v0, &v1);
        self->desc02()->m1D(self, &v0);
        self->desc02()->m20(self, &v1);
    }
    if (self->f1F0) {
        self->f1F0->vt->getRot(self->f1F0, 0.0f, &rot, &v0);
        self->desc02()->m1E(self, &rot);
        self->desc02()->m21(self, &v0);
    }
    if (self->flags & 0x1000000000ULL) AddCameraObject((PlacedObject*)g_camera, self);
    if (self->f284) AppendToList(&self->world->list1C00, self->f284);
    if (self->desc->m12) self->desc->m12(self);
    TriggerScriptEvent(self, 4, 0, 0);
    ClearRootTries(self);
}

void DetachPlacedObject(PlacedObject* self)
{
    ListFrame it;
    ListWalkBegin::Of(&it, &self->children);
    self->desc->m07(self);
    BaseObject* obj;
    while ((obj = ListWalkNext::Of(&it)) != 0) {
        obj->desc->m05(obj);
    }
    self->desc->m0E(self, 2, self);
    g_activeListFrames = (ListFrame*)it.prev;
}

void UnregisterPlacedObject(PlacedObject* self)
{
    UnregisterObject(self);
    World* s1 = self->world;
    if (self->parent == 0) {
        if (self->f294 != 0) {
            RemoveFromList(&s1->list78, self);
        } else {
            RemoveFromList(&s1->list54, self);
            u64 fl = self->flags;
            if ((fl & (1ull << 37)) != 0) {
                self->flags = fl & ~(1ull << 37);
                RemoveFromList(&s1->list60, self);
                if ((self->desc->flags & 2) != 0) {
                    RemoveFromList(&s1->list6C, self);
                }
            }
            DissolveObjectLinkList(s1, self->f54);
            self->f54 = 0;
            ClearList(&self->list60);
        }
    }
    if ((self->flags & (1ull << 36)) != 0) {
        RemoveCameraObject(g_camera, self);
    }
    if (self->f284 != 0) {
        RemoveFromList(&self->world->list1C00, self->f284);
    }
    if ((self->flags & (1ull << 38)) != 0) {
        void (*fn)(BaseObject* self, s32 on) = self->desc->m14;
        if (fn != 0) {
            fn(self, 0);
        }
    }
    ClearRootTries(self);
    self->root = 0;
    TriggerScriptEvent(self, 5, 0, 0);
}

void SavePlacedObjectInitialFrame(PlacedObject* object)
{
	object->v190 = object->pos;
	object->m1A0.r[0] = object->rot.r[0];
	object->m1A0.r[1] = object->rot.r[1];
	object->m1A0.r[2] = object->rot.r[2];
	object->desc02()->m2A(object, &object->m1A0);
	MatrixToEulerAngles(&object->m1A0, &object->v1D0);
}

ASM_FUNC(func_001245A8);

ASM_FUNC(func_00124868);

void PostLoadPlacedObject(PlacedObject* self)
{
    ListFrame frame;
    ResolveFollowRecordObjects(self);
    SavePlacedObjectInitialFrame(self);
    T2195_790* sub = self->f200;
    if (sub != 0 && sub->f20 != -1) {
        void* v = FindFirstObjectByIdMode4(self->world, sub->f20, self);
        if (v != 0) {
            SetAimTarget(self, v);
        }
    }
    BindAttachmentTargets(self->sub22C, self);
    for (BaseObject* p = (BaseObject*)self->children.head; p != 0; p = p->next) {
        void (*fn)(BaseObject* self) = p->desc->m0F;
        if (fn != 0) {
            fn(p);
        }
    }
}

void StartPlacedObject(PlacedObject* self)
{
    WordListFrame fr;
    Key02* k;
    BaseObject* s0;
    s32 old = (s32)g_activeListFrames;
    s32 e = (s32)&self->children;
    fr.list = e;
    fr.link = e;
    fr.offset = *(s32*)(e + 8);
    fr.prev = old;
    g_activeListFrames = (ListFrame*)&fr;
    StartObject(self);
    if (self->f2A0 != 0) {
        if (self->f2A0->anim != 0 || self->f2A0->key != -1) {
            AppendQueuedCall(self->world, (void*)StartAnimationFromContext, self, 0, 0);
        }
    }
    StartAttachments(self->sub22C, self);
    if (self->f284 != 0) {
        if (HasRangeRecordRanges(self->f284) == 0) {
            StoreRangeRecordNear(self->f284, self->f2A8);
            StoreRangeRecordFar(self->f284, self->f2A8 * 0.5f);
        }
        if ((self->f284)->fB0 != -1) {
            (self->f284)->fB4 = FindFirstObjectByIdMode4(self->world, (self->f284)->fB0, self);
            if ((self->f284)->fB4 != 0) {
                BuildTexturePackets((self->f284)->fB4, self->f284);
            }
        }
        PrepareRangeRecord(self->f284);
    }
    if (self->f2AC != 0) {
        if (self->f2AC->f00 == -1) {
            self->f2AC = 0;
        }
        if (self->f2AC != 0) {
            SoundRecord* q = self->f2AC;
            StartSoundEffect(q->f00, q->f04, q->f08, q->f0C, q->f10, q->f20, &q->f1C, self, 0, &q->b14, 0);
        }
    }
    if (self->f26C != 0) {
        self->f1F8 = (void**)AllocateZeroedFrontMemory(self->f26C << 2);
    }
    for (k = self->keys; k != 0; k = k->next) {
        if (MatchesObjectId(self, k->key) != 0) {
            s0 = self;
        } else {
            s0 = (BaseObject*)FindFirstObjectById(self->world, 1, k->key, self);
            if (s0 == 0) {
                continue;
            }
        }
        if (IsObjectAttached(s0) != 0 && s0 != self) {
            s0->desc->m10(s0);
        }
        s0->desc->m03(s0);
    }
    self->keys = 0;
    {
        s32 head = *(s32*)fr.link;
        s32 p;
        fr.link = head + fr.offset;
        p = head;
        while (p != 0) {
            ((BaseObject*)p)->desc->m10((BaseObject*)p);
            s32 nx = *(s32*)fr.link;
            fr.link = nx + fr.offset;
            p = nx;
        }
    }
    g_activeListFrames = (ListFrame*)fr.prev;
}

void StartAnimationFromContext(PlacedObject* self)
{
    AnimationStart* ctx = self->f2A0;
    Animation* node = FindStartAnimation::Of(self, ctx);
    if (node == 0) {
        return;
    }
    StartBindingFrame fr;
    switch (ctx->mode) {
    case 0:
        fr.tmp = ctx->value;
        break;
    case 1:
        fr.tmp = ClampRange::Of(ctx->value, 0.0f, 1.0f) * node->length;
        break;
    case 2:
        func_0012C9E8(node, self, 0.0f, (u8*)self + 0x100, &fr.tmp, 0, 0);
        break;
    default:
        return;
    }
    fr.key = node->id;
    fr.object = self;
    CreateAnimationPlayer(node, self, 1, &fr, fr.tmp, ctx->speedScale, 0, 0);
}

void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item)
{
    World* host = self->world;
    if (count <= 0) {
        return;
    }
    ObjectLink* it = item;
    s32 n = count;
    do {
        u32 f = it->flags;
        s32 kind = (f & 1) ? 5 : 1;
        if (f & 0x20) {
            kind |= 0x100;
        }
        void* node = FindFirstObjectById(host, kind, it->id, self);
        if (node) {
            if (!(it->flags & 8)) {
                *(void**)((u8*)self + it->offset) = node;
            }
            if (!(it->flags & 4)) {
                ResolveAndStartObject(node);
            }
            if (it->flags & 0x10) {
                AddObjectListener(node, self);
            }
        }
        n--;
        it++;
    } while (n != 0);
}

void UpdateObjectTree(void* self, f32 f)
{
    PlacedObject* obj = (PlacedObject*)self;
    WordListFrame fr;
    f32 saved = f;
    void (*pre)(BaseObject* self, f32 dt) = obj->desc->m11;
    if (pre != 0) {
        pre(obj, f);
    }
    if (IsObjectAttached(self) == 0) {
        return;
    }
    s32 e = (s32)&obj->children;
    fr.list = e;
    fr.link = e;
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.offset = link;
    *(s32*)&g_activeListFrames = (s32)&fr;
    s32 head = (s32)obj->children.head;
    fr.link = head + fr.offset;
    BaseObject* node = (BaseObject*)head;
    while (node != 0) {
        if ((node->desc->flags & 1) != 0) {
            UpdateObjectTree(node, saved);
        }
        s32 nx = *(s32*)fr.link;
        fr.link = nx + fr.offset;
        node = (BaseObject*)nx;
    }
    *(s32*)&g_activeListFrames = fr.prev;
}

void UpdatePlacedObject(PlacedObject* self, f32 f)
{
    UpdateAttachments(self->sub22C, self, f);
    if (self->f284 != 0) {
        UpdateRangeRecord(self->f284, f);
    }
    if (self->f288 != 0) {
        func_00126AC8(self, f);
    }
    ListFrame it;
    ListWalkBegin::Of(&it, &self->list1E0);
    Attachment* obj;
    while ((obj = NextAttachment::Of(&it)) != 0) {
        if (obj->vt->update != 0) {
            obj->vt->update(obj, f);
        }
    }
    g_activeListFrames = (ListFrame*)it.prev;
    void* args[1];
    args[0] = &f;
    TriggerScriptEvent(self, 1, 1, args);
}

void ClearObjectRecordValues(PlacedObject* records)
{
    for (s32 i = 0; i < records->drawPartCount; i++) {
        PartState* record = (PartState*)((u8*)records->partStates + i * 0x28);
        record->value = -1;
    }
}

void RecomputePlacedObjectFrame(PlacedObject* self)
{
    void (*fn)(BaseObject* self) = self->desc->m13;
    if (fn != 0) {
        fn(self);
    }
}

ASM_FUNC(func_00125138);

void BeginPlacedObjectMove(PlacedObject* self)
{
    (void)self;
}

ASM_FUNC(func_00125440);

ASM_FUNC(func_00125750);

ASM_FUNC(func_001259D8);

void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst)
{
    if (src != 0) {
        if (src != (Quad16*)dst) {
            *dst = *(ScaledTransform*)src;
        }
    } else {
        BuildScaledTransformMatrix(&self->v140, &self->m110, D_00248D40, dst);
        dst->f44 = 1.0f;
        dst->f40 = 1.0f;
    }
}

ASM_FUNC(func_00125BF0);

ASM_FUNC(func_00125C90);

void DrawPlacedObject(PlacedObject* self, void* b, void* m)
{
    Quad16* src = (Quad16*)m;
    self->desc02()->m2C(self);
    Rec2195_224* in = self->f224;
    if (in != 0 && (in->fB0 & 0x80) != 0) {
        if (src != 0) {
            in->fA4 = 1;
            Rec2195_224* p = self->f224;
            p->q60[0] = src[0];
            p->q60[1] = src[1];
            p->q60[2] = src[2];
            p->q60[3] = src[3];
        } else {
            in->fA4 = 0;
        }
    }
    self->desc02()->m26(self, b, src);
}

INCLUDE_RODATA(D_002499F4);

INCLUDE_RODATA(jtbl_00249A00);

ASM_FUNC(func_00126270);

ASM_FUNC(func_001268B8);

void SetObjectTreeRecordValue(PlacedObject* object, u32 value)
{
    ListFrame frame;
    PlacedObject* child = (PlacedObject*)object->children.head;
    *(u32*)(object->sub22C + 0x3C) = value;
    *(u32*)(object->sub22C + 0x38) |= 2;
    while (child != 0) {
        if ((child->desc->flags & 1) != 0)
            SetObjectTreeRecordValue(child, value);
        child = (PlacedObject*)child->next;
    }
}

void SetObjectRecordValue(PlacedObject* state, u32 value)
{
	*(u32*)(state->sub22C + 0x3C) = value;
	*(u32*)(state->sub22C + 0x38) |= 2;
}

ASM_FUNC(func_00126AC8);

void SetObjectTreeRecordsValue(PlacedObject* object, s32 value)
{
    ListFrame frame;
    for (s32 i = 0; i < object->drawPartCount; i++) {
        DrawPart* record = (DrawPart*)((u8*)object->drawParts + i * 0x70);
        record->type = 2;
        record->value = value;
    }
    PlacedObject* child = (PlacedObject*)object->children.head;
    while (child != 0) {
        if ((child->desc->flags & 1) != 0)
            SetObjectTreeRecordsValue(child, value);
        child = (PlacedObject*)child->next;
    }
}

void EnsureObjectWorldNode(PlacedObject* self)
{
    if (self->f298 == 0) {
        self->f298 = AddObjectNodeToWorld();
        if (IsObjectAttached(self) != 0) {
            self->f298->level = 1.0f;
        } else {
            self->f298->level = 0.0f;
        }
    }
}

ASM_FUNC(func_00126CB8);

ASM_FUNC(func_00126D60);

ASM_FUNC(func_00126DE8);

void ClonePlacedObject(PlacedObject* self, PlacedObject* owner)
{
    ListFrame it;
    ListWalkBegin::Of(&it, &owner->children);
    self->desc->m09(self, owner);
    BaseObject* obj = ListWalkNext::Of(&it);
    while (obj != 0) {
        (void)CreateObjectCopy(obj, self->world, self);
        obj = ListWalkNext::Of(&it);
    }
    if ((self->desc->flags & 2) && self->parent == 0) {
        UpdateAnchorModeFlags(self);
    }
    g_activeListFrames = (ListFrame*)it.prev;
}

void CopyPlacedObject(PlacedObject* self, PlacedObject* src)
{
    void* s54 = self->f54;
    PlacedObject* s50 = self->root;
    Link02 t48 = self->link48;
    u64 bit = (self->flags >> 37) & 1;
    Link02 t40 = self->link40;
    Link02 t58 = self->link58;
    List01 t60 = self->list60;
    List01 t1E0 = self->list1E0;
    CopyObjectData(self, src);
    CopyAttachmentBlock(self->sub22C, self, src->sub22C);
    if (self->f224) {
        self->f224 = (Rec2195_224*)CopyToFrontMemory(0xC0, self->f224);
    }
    ClearList(&self->children);
    self->link48 = t48;
    self->link40 = t40;
    self->link58 = t58;
    self->list60 = t60;
    self->f54 = s54;
    self->root = s50;
    self->flags = (self->flags & ~(1ULL << 37)) | ((u64)bit << 37);
    self->list1E0 = t1E0;
    self->desc02()->m2B(self);
    if (src->f1FC) {
        self->f1FC = ClonePoseSource(src->f1FC, self->world, self);
        InsertAttachment(self, self->f1FC);
    }
    if (src->f200) {
        self->f200 = (T2195_790*)ClonePoseSource(src->f200, self->world, self);
        InsertAttachment(self, self->f200);
    }
    if (src->f204) {
        self->f204 = (T2195_600*)ClonePoseSource(src->f204, self->world, self);
        InsertAttachment(self, self->f204);
    }
    if (src->f284) {
        u8* p = TakePoolSlot(&self->world->pool1BF4);
        CopyMemory(p, src->f284, 0x2E0);
        ClearListLinks(p + 0xB8);
        self->f284 = (RangeRecord*)p;
        AppendToList(&self->world->list1C00, p);
    }
    if (src->f2AC) {
        self->f2AC = (SoundRecord*)CopyToFrontMemory(0x24, src->f2AC);

    }
    if (src->f288) {
        self->f288 = (ColorRecord*)CopyToFrontMemory(0x40, src->f288);
    }
    if (self->flags & (1ULL << 36)) {
        if (IsObjectAttached(self)) {
            AddCameraObject(g_camera, self);
        }
    }
    if (self->p20C != (u8*)D_00260E70) self->p20C = (u8*)CopyToFrontMemory(0x10, self->p20C);
    if (self->p210 != (u8*)D_00260E80) self->p210 = (u8*)CopyToFrontMemory(0x10, self->p210);
    if (self->p214 != (u8*)D_00260E90) self->p214 = (u8*)CopyToFrontMemory(0x10, self->p214);
    if (self->p218 != (u8*)D_00260EA0) self->p218 = (u8*)CopyToFrontMemory(0x10, self->p218);
}

void HandlePlacedObjectNotification(PlacedObject* self, s32 mode)
{
    if (mode == 1) {
        SoundRecord* s = self->f2AC;
        if (s != 0) {
            if (g_gameTime[0] != 0.0f) {
                if (s->f1C == 0) {
                    StartSoundEffect(s->f00, &s->f1C, self, 0, s->f04, s->f08, s->f0C, s->f10, s->f20, &s->b14, 0);
                }
            }
        }
    }
}

void SetPlacedObjectPosition(PlacedObject* self, Vec02* src)
{
    MoveNotice f;
    f.q = self->v140;
    f.self = self;
    self->pos = *src;
    if (self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    if (self->f1EC != 0) {
        SettlePoseSourceModes(self->f1EC);
    }
    self->desc->m0E(self, 3, &f);
}

LINKER_REMNANT(func_00127468);

void SetPlacedObjectRotation(PlacedObject* self, Mat02* src)
{
    self->rot = *src;
    if (self->desc->m12)
        self->desc->m12(self);
    if (self->f1F0)
        SettlePoseSourceModes(self->f1F0);
    self->desc->m0E(self, 4, self);
}

void SetPlacedObjectVelocity(PlacedObject* self, Vec02* src)
{
    self->v150 = *src;
    if (self->f1EC != 0) {
        SettlePoseSourceModes(self->f1EC);
    }
    if (IsVelocityNegligible(src) == 0) {
        ClearRootTries(self);
    }
}

void SetPlacedObjectVelocityFromFloats(ObjectCycler* self, f32 x, f32 y, f32 z)
{
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    self->desc02()->m20(self, (Vec02*)&v);
}

void SetPlacedObjectSpin(PlacedObject* self, Vec02* src)
{
    self->v160 = *src;
    if (self->f1F0 != 0) {
        SettlePoseSourceModes(self->f1F0);
    }
    if (IsSpinNegligible(src) == 0) {
        ClearRootTries(self);
    }
}

void SetPlacedObjectSpinFromFloats(PairedObject* self, f32 x, f32 y, f32 z)
{
    f32 v[3];
    v[0] = x;
    v[1] = y;
    v[2] = z;
    self->desc02()->m21(self, (Vec02*)v);
}

ASM_FUNC(func_00127628);

ASM_FUNC(func_00127678);

void CopyPlacedObjectFrame(PlacedObject* self, PlacedObject* other)
{
    TakeFrameLocals L;
    TransformPointBetweenFrames(0, self->parent, &other->v140, L.a20);
    TransformRotationBetweenFrames(0, self->parent, &other->m110, L.a50);
    func_00128330(other->parent, self->parent, &other->v140, &other->v150, &other->v160, 0, 0, L.a30, L.a40, 0, 0);
    self->desc02()->m1D(self, (Vec02*)L.a20);
    self->desc02()->m1E(self, (Mat02*)L.a50);
    self->desc02()->m20(self, (Vec02*)L.a30);
    self->desc02()->m21(self, (Vec02*)L.a40);
    Rec2195_224* a = self->f224;
    if (a != 0 && (a->fB0 & 0x20)) {
        Rec2195_224* b = other->f224;
        if (b != 0 && (b->fB0 & 0x20)) {
            a->f90 = b->f90;
            self->f224->f94 = other->f224->f94;
        }
    }
    PlacedObject* n = (PlacedObject*)self->children.head;
    if (n != 0) {
        do {
            if ((n->desc->flags ^ 1) & 1)
                continue;
            PlacedObject* h = (PlacedObject*)FindFirstObjectById(self->world, 2, n->id, other);
            if (h == 0)
                continue;
            if ((h->desc->flags ^ 1) & 1)
                continue;
            if (n->f224 != 0 && (n->f224->fB0 & 0xC))
                continue;
            n->desc02()->m1F(n, h);
        } while ((n = (PlacedObject*)n->next) != 0);
    }
}

ASM_FUNC(func_001278A8);

ASM_FUNC(func_00127B20);

ASM_FUNC(func_00127E60);

ASM_FUNC(func_00128018);

ASM_FUNC(func_001280C0);

ASM_FUNC(func_00128150);

s32 HasAnimationDrivenAttachment(SwitchedCollider *self) {
    Attachment *p = self->f1EC;
    if (p != 0 && p->mode0 == 5) {
        return 1;
    }
    p = self->f1F0;
    if (p != 0) {
        if (p->mode1 == 5) {
            return 1;
        }
    }
    return 0;
}

void ReleaseAnimationDrivenAttachments(Player* self)
{
    Attachment* a = self->f1EC;
    if (a != 0 && a->mode0 == 5) {
        do {
            a->vt->release(a, 0);
            a = self->f1EC;
        } while (a != 0 && a->mode0 == 5);
    }
    Attachment* b = self->f1F0;
    if (b != 0 && b->mode1 == 5) {
        do {
            b->vt->release(b, 0);
            b = self->f1F0;
        } while (b != 0 && b->mode1 == 5);
    }
}

ASM_FUNC(func_00128330);

ASM_FUNC(func_00128598);

s32 TestChildrenAccepted(PlacedObject* self, ScriptListBuilder* context)
{
    ListFrame it;
    ListWalkBegin::Of(&it, (List01*)&self->children);
    PlacedObject* obj;
    for (obj = ListWalkNextPlaced::Of(&it); obj != 0; obj = ListWalkNextPlaced::Of(&it)) {
        if (AppendPropertyToScriptList(context, &obj) == 0) {
            g_activeListFrames = (ListFrame*)it.prev;
            return 0;
        }
    }
    g_activeListFrames = (ListFrame*)it.prev;
    return 1;
}

void CreateTrackAttachment(BaseObject* item)
{
    CreatePoseSource(item->world, item, (void*)D_002197C0);
}

INCLUDE_RODATA(D_00249A1C);

ASM_FUNC(func_001289C0);

void LoadFollowRecord(PlacedObject* self, void* a1)
{
    s32 flags = ReadBufferedU32(a1);
    if (flags) {
        u8* p = (u8*)AllocateZeroedFrontMemory(0xC0);
        self->f224 = (Rec2195_224*)p;
        *(s32*)(p + 0xB0) = flags;

        u8* q = p + 0x30;
        *(Mat02*)p = g_identityMatrix;
        *(Mat02*)q = g_identityMatrix;
        if (flags & 1) ReadBufferedRotation3(a1, p);
        if (flags & 2) ReadBufferedRotation3(a1, q);
        if (flags & 0xC) {
            s32 r = ReadBufferedS16(a1);
            if (r != -1) {
                *(s32*)(p + 0x60) = (s32)FindFirstObjectById(self->world, 3, r, self);
            }
        }
        if (flags & 0x10) {
            *(s32*)(p + 0x60) = ReadBufferedS16(a1);
        }
        if (flags & 0x20) {
            *(s32*)(p + 0x84) = ReadBufferedS16(a1);
            ReadBufferedVector3(a1, p + 0x60);
            ReadBufferedVector3(a1, p + 0x70);
            f32 f = WrapAngle(ReadBufferedFloat(a1));
            *(s32*)(p + 0x98) = 0;
            *(f32*)(p + 0x8C) = f;
            *(f32*)(p + 0x90) = f;
        }
        if (flags & 0x40) {
            *(s32*)(p + 0x60) = ReadBufferedS16(a1);
            *(s32*)(p + 0x64) = ReadBufferedS16(a1);
        }
        if (flags & 0x80) {
            *(s32*)(p + 0xA0) = ReadBufferedU8(a1);
        }
    }
}

void ResolveFollowRecordObjects(PlacedObject* self)
{
    Rec2195_224* p = self->f224;
    if (p == 0) return;
    s32 v = p->fB0 | 0x8000;
    p->fB0 = v;
    if (v & 0x10) {
        p->p60 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p60, self);
        p->p64 = (BaseObject*)1;
    }
    if (p->fB0 & 0x20) {
        BaseObject* r = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p84, self);
        p->p84 = r;
        s32 x = (s32)r->parent;
        p->f80 = x;
        p->p88 = FindCommonAncestor(self, x);
    }
    if (p->fB0 & 0x40) {
        p->p60 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p60, self);
        p->p64 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p64, self);
    }
}

ASM_FUNC(func_00128E88);

ASM_FUNC(func_00128FD0);

ASM_FUNC(func_001290B8);

ASM_FUNC(func_001290E0);

AnimationStart* EnsureTimerRecord(PlacedObject* self)
{
    if (self->f2A0 == 0) {
        AnimationStart* t = (AnimationStart*)AllocateZeroedFrontMemory(0x14);
        self->f2A0 = t;
        t->key = -1;
        self->f2A0->mode = 0;
        self->f2A0->value = 0;
        self->f2A0->speedScale = 1.0f;
    }
    return self->f2A0;
}

void SetPlacedObjectScaleXY(PlacedObject* self, f32 x)
{
    self->f28C = x * 0.01f;
}

void GetPlacedObjectScaleXY(PlacedObject* self, f32* out)
{
    *out = self->f28C * 100.0f;
}

void SetPlacedObjectScaleZ(PlacedObject* self, f32 x)
{
    self->f290 = x * 0.01f;
}

void GetPlacedObjectScaleZ(PlacedObject* self, f32* out)
{
    *out = self->f290 * 100.0f;
}

void* EnsureRangeRecord(PlacedObject* self)
{
    if (self->f284 == 0) {
        void* o = PopZeroedFreeSlot((u8*)self->world + 0x1BF4);
        self->f284 = (RangeRecord*)o;
        InitRangeRecord(o);
        AppendToList((u8*)self->world + 0x1C00, self->f284);
    }
    return self->f284;
}

void SetRangeRecordPresent(PlacedObject* self, s32 flag)
{
    if (flag != 0) {
        EnsureRangeRecord(self);
        return;
    }
    if (self->f284 == 0) {
        return;
    }
    RemoveFromList((u8*)self->world + 0x1C00, self->f284);
    AppendToList(&g_deferredReleaseListC, self->f284);
    self->f284 = 0;
}

void SetRangeRecordKey(void* self, s32 value)
{
    LinkRangeRecord(EnsureRangeRecord(self), value);
}

void SetRangeRecordNear(void* self, f32 x)
{
    StoreRangeRecordNear(EnsureRangeRecord(self, x), x);
}

void SetRangeRecordFar(f32 x)
{
    StoreRangeRecordFar(EnsureRangeRecord(x), x);
}

void SetRangeRecordInner(f32 x)
{
    StoreRangeRecordInner(EnsureRangeRecord(x), x);
}

void SetRangeRecordOuter(f32 x)
{
    StoreRangeRecordOuter(EnsureRangeRecord(x), x);
}

void SetRangeRecordInnerAndOuter(f32 x)
{
    ScaleRangeRecordByAngle(EnsureRangeRecord(x), x);
}

void SetRangeRecordVector(void* self, void* src)
{
    StoreRangeRecordVector(EnsureRangeRecord(self), src);
}

void SetRangeRecordCode(void* self, s32 value)
{
    ((RangeRecord*)EnsureRangeRecord(self))->fB0 = value;
}

RangeRecord* GetRangeRecord(PlacedObject* self)
{
    if (self->f284 != 0) return self->f284;
    InitRangeRecord(&D_0027B520);
    return &D_0027B520;
}

void GetRangeRecordPresent(PlacedObject* self, s32* out)
{
    *out = self->f284 != 0;
}

void GetRangeRecordKeyValue(PlacedObject* self, s32* out)
{
    RangeRecord* p = self->f284;
    if (p == 0) {
        goto fail;
    }
    {
        AnimRecord* n = p->link;
        if (n == 0) {
            goto fail;
        }
        *out = n->key;
        return;
    }
fail:
    *out = -1;
}

void GetRangeRecordNear(void* self, f32* out)
{
    RangeRecord* s = GetRangeRecord(self);
    *out = s->f04;
}

void GetRangeRecordFar(void* self, f32* out)
{
    *out = GetRangeRecord(self)->f08;
}

void GetRangeRecordInner(void* self, f32* out)
{
    *out = GetRangeRecord(self)->f40;
}

void GetRangeRecordOuter(PlacedObject* self, f32* out)
{
    *out = GetRangeRecord(self)->f44;
}

void GetRangeRecordAngle(void* self, f32* out)
{
    RangeRecord* sub = GetRangeRecord(self);
    f32 value = ArctangentOfRatio(sub->f04 / sub->f40, 1.0f) * 57.2957763671875f;
    *out = value + value;
}

void GetRangeRecordVector(void* self, Vec02* out)
{
    *out = GetRangeRecord(self)->v30;
}

void GetRotationDegrees(PlacedObject* self, f32* out)
{
    Vec02 a[3];
    a[0] = self->rot.r[0];
    a[1] = self->rot.r[1];
    a[2] = self->rot.r[2];
    self->desc02()->m2A(self, a);
    MatrixToEulerAngles(a, out);
    s32 n = 2;
    f32* p = out;
    do {
        n--;
        *p = *p * 57.295776f;
        p++;
    } while (n >= 0);
}

void SetRotationDegrees(PlacedObject* self, f32* src)
{
    EulerLocals l;
    f32* out = l.out;
    f32* dst = l.tmp;
    f32 k = 0.01745329424738884f;
    s32 i = 2;
    do {
        *dst = *src * k;
        i--;
        src++;
        dst++;
    } while (i >= 0);
    BuildEulerRotationMatrix(l.tmp, out);
    self->desc02()->m29(self, (Mat02*)out, 0);
    self->desc02()->m1E(self, (Mat02*)out);
}

void EnsureBaseAttachment(PlacedObject* self)
{
    if (self->f1FC == 0) {
        Attachment* v = CreatePoseSource(self->world, self, D_00219560);
        self->f1FC = v;
        InsertAttachment(self, v);
    }
}

void EnsureAimAttachment(PlacedObject* self)
{
    if (self->f200 == 0) {
        T2195_790* v = (T2195_790*)CreatePoseSource(self->world, self, D_0021A790);
        self->f200 = v;
        InsertAttachment(self, v);
    }
}

void ChooseActiveAttachments(PlacedObject* self)
{
    Attachment* s3 = 0;
    Attachment* s2 = 0;
    Attachment* s1 = 0;
    s32 i;
    if (self->f1F8) FillMemory(self->f1F8, 0, self->f26C << 2);
    for (Attachment* n = (Attachment*)self->list1E0.head; n != 0; n = n->link.next) {
        if (s1 == 0) if (n->mode0 != -1) s1 = n;
        if (s2 == 0) if (n->mode1 != -1) s2 = n;
        if (s3 == 0) if (n->mode2 != -1) s3 = n;
        if (n->mode3 == -1) continue;
        if (n->vt == (const T2195_Vt*)D_002197C0) {
            Track83* e = &((T2195_7C0*)n)->player->anim->tracks[((T2195_7C0*)n)->index];
            for (i = 0; i < e->morphCount; i++) {
                if (e->morph[i] != 0) {
                    if (self->f1F8[i] == 0) self->f1F8[i] = n;
                }
            }
        } else {
            for (i = 0; i < self->f26C; i++) {
                if (self->f1F8[i] == 0) self->f1F8[i] = n;
            }
        }
    }
    if (s1 && s1->mode0 == 0) s1 = 0;
    if (s2 && s2->mode1 == 0) s2 = 0;
    if (s3 && s3->mode2 == 0) s3 = 0;
    if (self->f1F8) {
        for (i = 0; i < self->f26C; i++) {
            if (self->f1F8[i] != 0) {
                if (((Attachment*)self->f1F8[i])->mode3 == 0) self->f1F8[i] = 0;
            }
        }
    }
    self->f1F4 = s3;
    if (s1 != self->f1EC || s2 != self->f1F0) {
        ClearRootTries(self);
        if (s1 != self->f1EC) {
            self->f1EC = s1;
            if (s1) SettlePoseSourceModes(s1);
        }
        if (s2 != self->f1F0) {
            self->f1F0 = s2;
            if (s2) SettlePoseSourceModes(s2);
        }
    }
}

void InsertAttachment(PlacedObject* self, Attachment* src)
{
    ListFrame frame;
    Attachment* node = (Attachment*)self->list1E0.head;
    if (node != 0 && node->key > src->key) {
        node = node->link.next;
        while (node != 0 && node->key > src->key) {
            node = node->link.next;
        }
    }
    InsertBeforeInList(&self->list1E0, node, src);
    self->desc02()->m2B(self);
}

void SortAttachments(PlacedObject* self)
{
    ListFrame it;
    Attachment* nodes[20];
    s32 n = 0;
    Attachment* node;
    ListWalkBegin::Of(&it, &self->list1E0);
    for (node = NextAttachment::Of(&it); node != 0; node = NextAttachment::Of(&it)) {
        nodes[n] = node;
        RemoveFromList(&self->list1E0, node);
        n++;
    }
    while (--n >= 0) {
        Attachment* c = (Attachment*)self->list1E0.head;
        node = nodes[n];
        while (c != 0 && c->key > node->key) c = c->link.next;
        InsertBeforeInList(&self->list1E0, c, node);
    }
    self->desc02()->m2B(self);
    g_activeListFrames = (ListFrame*)it.prev;
}

AnimationPlayer* FindObjectAnimationPlayer(PlacedObject* self, s32 key)
{
    ListFrame frame;
    AnimationPlayer* node = (AnimationPlayer*)self->world->f1B64;
    while (node != 0) {
        if (node->fC == self) {
            if (key == -1) return node;
            if (MatchesObjectId(node->anim, key) != 0) return node;
        }
        node = node->next;
    }
    return 0;
}

StateWalker* FindObjectHandle(PlacedObject* self, s32 key)
{
    ListFrame frame;
    StateWalker* n = (StateWalker*)self->world->list1B94.head;

    while (n != 0) {
        if (n->f1C == (s32)self) {
            if (key == -1) return n;
            if (MatchesObjectId(n->owner, key) != 0) return n;
        }
        n = n->worldNext;
    }
    return 0;
}

void* FindTrackPlayer(PlacedObject* node)
{
    while (node != 0) {
        Attachment* a = node->f1EC;
        if (a != 0 && a->vt == (const T2195_Vt*)D_002197C0) {
            return ((T2195_7C0*)a)->player;
        }
        a = node->f1F0;
        if (a != 0 && a->vt == (const T2195_Vt*)D_002197C0) {
            return ((T2195_7C0*)a)->player;
        }
        node = (PlacedObject*)node->parent;
    }
    return 0;
}

void AddMatrixAttachment(PlacedObject* self, s32 key, Attachment** out)
{
    Attachment* n;

    if (self != 0) {
        n = CreatePoseSource(self->world, self, ((u8*)D_002195D8));
        n->key = key;
        InsertAttachment(self, n);
        *out = n;
    }
}

s32 IsObjectTreeAtRest(Actor6C* self)
{
    Actor6C* n;
    if (IsVelocityNegligible((u8*)self + 0x150) == 0) return 0;
    if (IsSpinNegligible((u8*)self + 0x160) != 0) goto body;
    return 0;
body:
    n = (Actor6C*)self->f34;
    while (n != 0) {
        if ((n->vtable->f8 & 1) != 0) {
            if (IsObjectTreeAtRest(n) == 0) return 0;
        }
        n = (Actor6C*)n->f1C;
    }
    return 1;
}

void ClearRootTries(PlacedObject* self)
{
    if (self->root != 0) self->root->tries = 0;
}

void SetScaledPositionSpring(void* self, void* src)
{
    ScaledSpringFrame f;
    u8* p = (u8*)D_00260E70;
    StoreFloatAsQuadword(&f.a, src);
    U128 av = f.a;
    CopyQuadword(&f.b, p);
    (void)StoreQuadword(&f.r, ScaleQuadword(av, f.b));
    SetPositionSpring(self, &f.r);
}

void SetPositionSpring(PlacedObject* self, Quad16* value)
{
    if (self->p20C == (u8*)D_00260E70)
        self->p20C = (u8*)AllocateFrontMemory(16);
    *(Quad16*)self->p20C = *value;
}

void SetScaledVelocitySpring(void* self, void* src)
{
    ScaledSpringFrame f;
    u8* p = (u8*)D_00260E80;
    StoreFloatAsQuadword(&f.a, src);
    U128 av = f.a;
    CopyQuadword(&f.b, p);
    (void)StoreQuadword(&f.r, ScaleQuadword(av, f.b));
    SetVelocitySpring(self, &f.r);
}

void SetVelocitySpring(PlacedObject* self, Quad16* src)
{
    if (self->p210 == (u8*)D_00260E80) self->p210 = (u8*)AllocateFrontMemory(16);
    *(Quad16*)self->p210 = *src;
}

void SetScaledRotationSpring(PlacedObject* self, void* src)
{
    ScaledSpringFrame f;
    u8* p = (u8*)D_00260E90;
    StoreFloatAsQuadword(&f.a, src);
    U128 av = f.a;
    CopyQuadword(&f.b, p);
    (void)StoreQuadword(&f.r, ScaleQuadword(av, f.b));
    SetRotationSpring(self, &f.r);
}

void SetRotationSpring(PlacedObject* self, Quad16* src)
{
    if (self->p214 == (u8*)D_00260E90) self->p214 = (u8*)AllocateFrontMemory(16);
    *(Quad16*)self->p214 = *src;
}

void SetScaledSpinSpring(PlacedObject* self, void* src)
{
    ScaledSpringFrame f;
    u8* p = (u8*)D_00260EA0;
    StoreFloatAsQuadword(&f.a, src);
    U128 av = f.a;
    CopyQuadword(&f.b, p);
    (void)StoreQuadword(&f.r, ScaleQuadword(av, f.b));
    SetSpinSpring(self, &f.r);
}

void SetSpinSpring(PlacedObject* self, Quad16* src)
{
    if (self->p218 == (u8*)D_00260EA0) self->p218 = (u8*)AllocateFrontMemory(16);
    *(Quad16*)self->p218 = *src;
}

void SetScaledPositionRamp(PlacedObject* self, f32 scale)
{
    Vec4U tmp;
    tmp.x = D_00260EB0[0] * scale;
    tmp.y = D_00260EB0[1] * scale;
    tmp.z = D_00260EB0[2];
    tmp.w = D_00260EB0[3] * scale;
    SetPositionRamp(self, (RampProfile*)&tmp);
}

void SetPositionRampAccelScale(PlacedObject* self, f32 scale)
{
    RampProfile tmp = *(RampProfile*)self->p21C;
    tmp.w = scale * (tmp.x - tmp.y) / tmp.z;
    SetPositionRamp(self, &tmp);
}

void SetPositionRamp(PlacedObject* self, RampProfile* src)
{
    if (self->p21C == (u8*)D_00260EB0) {
        self->p21C = (u8*)AllocateFrontMemory(16);
    }
    *(RampProfile*)self->p21C = *src;
}

void SetScaledRotationRamp(void* self, f32 s)
{
    f32 v[4];
    f32* m = (f32*)D_00260EC0;
    v[0] = m[0] * s;
    v[1] = m[1] * s;
    v[2] = m[2];
    v[3] = m[3] * s;
    SetRotationRamp(self, v);
}

void SetRotationRampAccelScale(PlacedObject* self, f32 scale)
{
    RampProfile tmp;
    tmp = *(RampProfile*)self->p220;
    tmp.w = scale * (tmp.x - tmp.y) / tmp.z;
    SetRotationRamp(self, &tmp);
}

void SetRotationRamp(PlacedObject* self, RampProfile* src)
{
    if (self->p220 == (u8*)D_00260EC0) {
        self->p220 = (u8*)AllocateFrontMemory(0x10);
    }
    *(RampProfile*)self->p220 = *src;
}

void SetDefaultPositionMode(void* self, s8 value) { *((s8*)((u8*)self + 0x2C9)) = value; }

void SetDefaultOrientationMode(void* self, s8 value) { *((s8*)((u8*)self + 0x2CA)) = value; }

void SetPositionSourceEnabled(void* self, s32 value) { SetPositionSourceMode(self, value ? 1 : -1); }

void SetGroupActivityModeEnabled(void* self, s32 a1)
{
    SetGroupActivityMode(self, a1 != 0);
}

void SetGroupActivityMode(PlacedObject* self, u32 value)
{
    self->flags = (self->flags & ~(3ull << 40)) | ((u64)(value & 3) << 40);
}

void GetGroupActivityMode(PlacedObject* self, u32* out)
{
    u32 value = (u32)(self->flags >> 40);
    value &= 3;
    *out = value;
}

void SetPositionSourceMode(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    self->f1FC->mode0 = value;
    self->desc02()->m2B(self);
}

void SetOrientationSourceEnabled(void* self, s32 a1)
{
    SetOrientationSourceMode(self, a1 != 0 ? 1 : -1);
}

void SetOrientationSourceMode(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    self->f1FC->mode1 = value;
    self->desc02()->m2B(self);
}

void SetBaseAttachmentSortKey(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    self->f1FC->key = value;
    SortAttachments(self);
}

void SetAimOrientationMode(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    if (value == 3) value = 9;
    self->f200->mode1 = value;
    self->desc02()->m2B(self);
}

void SetAimRange(PlacedObject* self, f32 f)
{
    EnsureAimAttachment(self);
    self->f200->f40 = f;
}

void GetAimRange(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f200 != 0) r = self->f200->f40;
    *out = r;
}

void SetAimYawCurve(PlacedObject* self, Vec02* src)
{
    EnsureAimAttachment(self);
    self->f200->v50 = *src;
}

void GetAimYawCurve(PlacedObject* self, Quad16* out)
{
    Quad16* src = self->f200 != 0 ? (Quad16*)((u8*)self->f200 + 0x50) : (Quad16*)D_00275C40;
    *out = *src;
}

void SetAimYawLimits(PlacedObject* self, Pk8_2195* src)
{
    EnsureAimAttachment(self);
    self->f200->p60 = *src;
}

void GetAimYawLimits(PlacedObject* self, U64P* out)
{
    U64P* src = self->f200 != 0 ? (U64P*)((u8*)self->f200 + 0x60) : (U64P*)g_unitRange;
    *out = *src;
}

void SetAimPitchCurve(PlacedObject* self, Vec02* src)
{
    EnsureAimAttachment(self);
    self->f200->v70 = *src;
}

void GetAimPitchCurve(PlacedObject* self, Quad16* out)
{
    Quad16* src = self->f200 != 0 ? (Quad16*)((u8*)self->f200 + 0x70) : (Quad16*)D_00275C40;
    *out = *src;
}

void SetAimPitchLimits(PlacedObject* self, Pk8_2195* src)
{
    EnsureAimAttachment(self);
    self->f200->p80 = *src;
}

void GetAimPitchLimits(PlacedObject* self, U64P* out)
{
    U64P* src = self->f200 != 0 ? (U64P*)((u8*)self->f200 + 0x80) : (U64P*)g_unitRange;
    *out = *src;
}

void SetAimNearKey(PlacedObject* self, s32 v)
{
    EnsureAimAttachment(self);
    self->f200->f44 = v;
}

void GetAimNearKey(PlacedObject* self, s32* out)
{
    s32 r = 0;
    if (self->f200 != 0) r = self->f200->f44;
    *out = r;
}

void SetAimFarKey(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    self->f200->f48 = value;
}

void GetAimFarKey(PlacedObject* self, s32* out)
{
    s32 v = 0;
    if (self->f200 != 0) {
        v = self->f200->f48;
    }
    *out = v;
}

void func_0012A810(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    self->f200->f20 = value;
}

void func_0012A848(PlacedObject* self, s32* out)
{
    s32 v = -1;
    if (self->f200 != 0) {
        v = self->f200->f20;
    }
    *out = v;
}

void SetAimTarget(PlacedObject* self, void* b)
{
    AssignAimTarget(self->f200, b, (void*)&D_00248D30);
}

void GetAimTarget(PlacedObject* self, void** out)
{
    *out = ResolveAimTarget(self->f200);
}

void ClearAimHold(PlacedObject* self)
{
    self->f200->hold = 0;
}

void SetAimHold(PlacedObject* self)
{
    self->f200->hold = 1;
}

void SetValueAttachment(PlacedObject* self, s32 a1, f32 x, f32 y)
{
    if (self->f204 == 0) {
        T2195_600* r = (T2195_600*)CreatePoseSource(self->world, self, ((u8*)D_00219600));
        self->f204 = r;
        InsertAttachment(self, r);
    }
    self->f204->mode1 = a1;
    self->f204->f1C = x;
    self->f204->f20 = y;
    self->desc02()->m2B(self);
}

Class75Object* FindOrCreateClass75Object(PlacedObject* self)
{
    void* r = FindFirstObjectById(self->world, 0x102, 0x22A, self);
    if (r != 0) {
        return (Class75Object*)r;
    }
    return (Class75Object*)CreateTypedRecord(0x75, (s32)self->world, self, 0x22A, -1);
}

void SetClass75ObjectCount(PlacedObject* self, s32 value)
{
    Class75Object* o = FindOrCreateClass75Object(self);
    if (value != -1) {
        o->count = value;
    }
}

void SetClass75ObjectScale(void* self, f32 value)
{
    FindOrCreateClass75Object(self)->scale = value;
}

void func_0012AA28(void* self, void* value)
{
    Class75Object* ctx = FindOrCreateClass75Object(self);
    ctx->f90 = value;
}

void SetElementsScrollScale(PlacedObject* self, f32 a, f32 b)
{
    for (s32 i = 0; i < self->elemCount; i++) {
        Elem02* p = self->elems[i];
        if (p->kind == 6) SetScrollScale(p, a, b);
    }
}

void SetCrossfadeRatioDeep(PlacedObject* self, f32 value)
{
    ListFrame frame;
    for (s32 i = 0; i < self->elemCount; i++) {
        Elem02* p = self->elems[i];
        if (p->kind == 5) SetCrossfadeRatio(p, value);
    }
    for (PlacedObject* child = (PlacedObject*)self->children.head; child; child = (PlacedObject*)child->next) {
        if (child->desc->flags & 1) SetCrossfadeRatioDeep(child, value);
    }
}

void EnsureSoundRecord(PlacedObject* self)
{
    if (self->f2AC == 0) InitSoundParams(&self->f2AC);
}

void SetSoundRecordId(PlacedObject* self, s32 value)
{
    EnsureSoundRecord(self);
    self->f2AC->f00 = value;
}

void RestartSoundWithId(PlacedObject* self, void* value)
{
    EnsureSoundRecord(self);
    StopSoundRecord(self->f2AC->p1C, 0);
    self->f2AC->p00 = value;
    SoundRecord* p = self->f2AC;
    StartSoundEffect(p->p00, p->f04, p->f08, p->f0C, p->f10, p->f20, &p->p1C, self, 0, &p->b14, 0);
}

void GetSoundRecordId(PlacedObject* self, s32* out)
{
    s32 v = -1;
    if (self->f2AC != 0) v = self->f2AC->f00;
    *out = v;
}

void SetSoundOuterRange(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    self->f2AC->f04 = value;
}

void GetSoundOuterRange(PlacedObject* self, f32* out)
{
    SoundRecord* s = self->f2AC;
    f32 v = 3000.0f;
    if (s != 0) v = s->f04;
    *out = v;
}

void SetSoundInnerRange(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    self->f2AC->f08 = value;
}

void SetSoundRecordPair(PlacedObject* self, U64P* src)
{
    EnsureSoundRecord(self);
    self->f2AC->b14 = *src;
}

void GetSoundInnerRange(PlacedObject* self, f32* out)
{
    SoundRecord* s = self->f2AC;
    f32 v = 300.0f;
    if (s != 0) v = s->f08;
    *out = v;
}

void SetSoundRecordScale(PlacedObject* self, f32 f)
{
    EnsureSoundRecord(self, f);
    self->f2AC->f0C = f;
}

void func_0012ADD0(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    self->f2AC->f20 = value;
}

void func_0012AE08(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f2AC != 0) {
        r = self->f2AC->f20;
    }
    *out = r;
}

void SetPlayingSoundVolume(PlacedObject* self)
{
    SoundRecord* part = self->f2AC;
    if (part != 0) {
        void* p = part->p1C;
        if (p != 0) {
            SetSoundRecordVolume(p);
        }
    }
}

void GetSoundRecordScale(PlacedObject* self, f32* out)
{
    f32 v = 1.0f;
    if (self->f2AC != 0) {
        v = self->f2AC->f0C;
    }
    *out = v;
}

void SetSoundStartPitch(PlacedObject* self, f32 f)
{
    EnsureSoundRecord(self, f);
    self->f2AC->f10 = f;
}

void SetPlayingSoundPitch(PlacedObject* self)
{
    SoundRecord* in = self->f2AC;
    if (in != 0) {
        if (in->p1C != 0) SetSoundRecordPitch(in->p1C);
    }
}

void GetSoundStartPitch(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f2AC != 0) {
        r = self->f2AC->f10;
    }
    *out = r;
}

void GetSoundRecordPair(PlacedObject* self, U64P* out)
{
    SoundRecord* s = self->f2AC;
    if (s != 0) {
        *out = s->b14;
    } else {
        f32* f = (f32*)out;
        f[0] = -1.0f;
        f[1] = -1.0f;
    }
}

void StartSoundWithParams(PlacedObject* self, void* value, U64P* src, f32 x, f32 y, f32 z)
{
    EnsureSoundRecord(self);
    self->f2AC->p00 = value;
    self->f2AC->f04 = x;
    self->f2AC->f08 = y;
    self->f2AC->f0C = z;
    self->f2AC->b14 = *src;
    StopSoundRecord(self->f2AC->p1C, 0);
    SoundRecord* p = self->f2AC;
    StartSoundEffect(p->p00, p->f04, p->f08, p->f0C, p->f10, p->f20, &p->p1C, self, 0, &p->b14, 0);
}

void StopPlayingSound(PlacedObject* self)
{
    SoundRecord* inner = self->f2AC;
    if (inner != 0) StopSoundRecord(inner->p1C, 0);
}

void EnsureColorRecord(void* ptr)
{
    PlacedObject* self = (PlacedObject*)ptr;
    if (!self->f288) {
        self->f288 = (ColorRecord*)AllocateFrontMemory(64);
        *self->f288 = g_defaultColorRecord[0];
        self->f288->preset = -1;
    }
}

void SetColorPreset(PlacedObject* self, s32 a1)
{
    EnsureColorRecord(self);
    self->f288->preset = a1;
    ColorRecord* e = self->f288;
    s32 k = e->preset;
    if (k != -1) *e = g_colorPresets[k];
}

void GetColorPreset(PlacedObject* self, s32* out) { *out = self->f288 ? *(s32*)self->f288 : -1; }

void SetColorRecordFirstColor(PlacedObject* self, Quad16* input)
{
    EnsureColorRecord(self);
    *(Quad16*)((u8*)self->f288 + 0x10) = *input;
}

void GetColorRecordFirstColor(PlacedObject* self, Quad16* out)
{
    u8* src = self->f288 ? (u8*)self->f288 + 0x10 : (u8*)&D_00248D30;
    *out = *(Quad16*)src;
}

void SetColorRecordSecondColor(PlacedObject* self, Quad16* input)
{
    EnsureColorRecord(self);
    *(Quad16*)((u8*)self->f288 + 0x20) = *input;
}

void GetColorRecordSecondColor(PlacedObject* self, Quad16* out)
{
    u8* src = self->f288 ? (u8*)self->f288 + 0x20 : (u8*)&D_00248D30;
    *out = *(Quad16*)src;
}

void SetColorRecordFactor(PlacedObject* self, f32 value)
{
    EnsureColorRecord(self);
    self->f288->factor = value;
}

void GetColorRecordFactor(PlacedObject* self, f32* out)
{
    f32 v = 0.0f;
    ColorRecord* p = self->f288;
    if (p != 0) v = p->factor;
    *out = v;
}

void SetTintRgb(PlacedObject* self, s32 v)
{
    self->tint[2] = v;
    self->tint[1] = v;
    self->tint[0] = v;
}

void GetTintRgb(PlacedObject* self, s32* out)
{
    *out = self->tint[0];
}

void SetTintByte0(PlacedObject* self, s32 v)
{
    self->tint[0] = v;
}

void GetTintByte0(PlacedObject* self, s32* out)
{
    *out = self->tint[0];
}

void SetTintByte1(PlacedObject* self, u8 value) { self->tint[1] = value; }

void GetTintByte1(PlacedObject* self, s32* out)
{
    *out = self->tint[1];
}

void SetTintByte2(PlacedObject* self, s32 v)
{
    self->tint[2] = v;
}

void GetTintByte2(PlacedObject* self, s32* out)
{
    *out = self->tint[2];
}

void SetTintByte3(PlacedObject* self, s32 value)
{
    self->tint[3] = value;
}

void GetTintByte3(PlacedObject* self, s32* out)
{
    *out = self->tint[3];
}

void SetTintByte4(PlacedObject* self, u8 v)
{
    self->f2B4 = v;
}

void GetTintByte4(PlacedObject* self, s32* out)
{
    *out = self->f2B4;
}

s32 TestOtherFlagged(PlacedObject* self, BaseObject* a1)
{
    return a1->f0C != 0;
}

void SelectValueEntryByKey(PlacedObject* self, s32 key)
{
    s32 callVt = 0;
    s32 i;
    T2195_5B0* st;

    if (key == -1) {
        st = self->f2C0;
        if (st != 0) {
            callVt = SetMode3::Of(st, -1);
        }
    } else {
        for (i = 0; i < self->f2B8; i++) {
            if (((KeyedValues*)self->f2BC)[i].key == key) {
                break;
            }
        }
        if (i < self->f2B8) {
            if (self->f2C0 == 0) {
                self->f2C0 = (T2195_5B0*)CreatePoseSource(self->world, self, ((u8*)D_002195B0));
                InsertAttachment(self, self->f2C0);
            }
            callVt = SetMode3::Of(self->f2C0, 3);
            self->f2C0->count = &self->f26C;
            self->f2C0->values = ((KeyedValues*)self->f2BC)[i].values;
        }
    }
    if (callVt != 0) {
        self->desc02()->m2B(self);
    }
}

void SetObjectCameraTracked(PlacedObject* self, s32 flag)
{
    u64 want = flag != 0;
    if (want != (((self->flags >> 36) ^ 1) & 1)) {
        return;
    }
    u64 bit = (u64)(flag & 1) << 36;
    self->flags = (self->flags & 0xFFFFFFEFFFFFFFFFULL) | bit;
    if (IsObjectAttached(self) == 0) {
        return;
    }
    if (flag != 0) {
        AddCameraObject(g_camera, self);
    } else {
        RemoveCameraObject(g_camera, self);
    }
}

void SetPlacedObjectFrameStepClock(PlacedObject* self, s32 flag)
{
    if ((0 < (u32)flag) != (self->f294 == 0)) {
        goto done;
    }
    if (IsObjectAttached(self) == 0) {
        goto store;
    }
    if (self->parent != 0) {
        goto store;
    }
    self->desc->m03(self);
    self->f294 = flag;
    self->desc->m02(self);
    goto done;
store:
    self->f294 = flag;
done:
    return;
}

void SetPlacedObjectSpecialFlag(PlacedObject* ctx, s32 on)
{
    if (on != 0) {
        ctx->flags |= (u64)1 << 32;
    } else {
        ctx->flags &= ~((u64)1 << 32);
    }
}

void GetPlacedObjectSpecialFlag(PlacedObject* ctx, s32* out)
{
    if ((ctx->flags & ((u64)1 << 32)) != 0) {
        *out = 1;
    } else {
        *out = 0;
    }
}

void SetFollowObjects(PlacedObject* self, void* a1, void* a2)
{
    void* t = self->parent;
    if (a1 == t || a2 == t || a1 == a2) {
        if (a1 != 0 || a2 != 0) {
            if (self->f224 == 0) {
                self->f224 = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);
            }
        }
        Rec2195_224* p = self->f224;
        if (a1 != self->parent) {
            p->p60 = (BaseObject*)a1;
            p->fB0 = p->fB0 | 4;
        } else {
            p->fB0 = p->fB0 & 4;
        }
        if (a2 != self->parent) {
            p->p60 = (BaseObject*)a2;
            p->fB0 = p->fB0 | 8;
        } else {
            p->fB0 = p->fB0 & 8;
        }
        TransformPointBetweenFrames(0, a1, (u8*)self + 0x140, (u8*)self + 0x100);
        TransformRotationBetweenFrames(0, a2, (u8*)self + 0x110, (u8*)self + 0xD0);
    }
}

ASM_FUNC(func_0012B6A0);

void InitCodeChecksum(CodeChecksum* self)
{
    u32 c;
    InitPlacedObject(self);
    self->start = 0x100018;
    self->end = D_00148D64;
    self->crc = 0xFFFFFFFF;
    for (s32 i = 0; i < 256; i++) {
        c = (u32)i;
        s32 k = 7;
        do {
            if (c & 1) {
                c = (c >> 1) ^ 0xEDB88320;
            } else {
                c >>= 1;
            }
        } while (--k >= 0);
        self->table[i] = c;
    }
}

void UpdateCodeChecksum(CodeChecksum* self)
{
    if (self->remaining != 0) {
        s32 n = self->remaining;
        u32* p = self->cursor;
        u32 crc = self->crc;
        u8* tbl = (u8*)self->table;
        s32 i = 0;
        if (n > 0) {
            do {
                u32 w = *p;
                i++;
                n -= 4;
                crc = *(u32*)(tbl + (((crc ^ w) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 8)) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 16)) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 24)) & 0xFF) << 2)) ^ (crc >> 8);
                p++;
                if (i >= 64) break;
            } while (n > 0);
        }
        self->cursor = p;
        self->crc = crc;
        self->remaining = n;
        if (n == 0 && crc != 0) {
            g_checksumMismatch[0] = 1;
            TriggerScriptEvent(self, 2, 0, 0);
        }
    }
}

void InitPlacedObjectModule(void) {}

void InitAnimation(Animation* self)
{
    InitObject(self);
    SetListLinkOffset(&self->props6C, 0x3C);
    Kin83* k = &self->kin;
    k->pos = 1.0f;
    k->vel = 0.0f;
    k->acc = 0.0f;
    self->lo = 0.0f;
    self->hi = 1.0f;
    self->out = 1.0f;
}

void LoadAnimation(Animation* self, Stream83* other)
{
    s32 k;
    Track83* sel = 0;
    Track83* e;
    PositionCurve* qp;
    RotationCurve* qr;
    ScaleCurve* qs;
    WeightCurve* qw;
    s32 i;
    s32 j;
    s32 t;
    s32 flags;

    t = ReadBufferedS16(other);
    self->id = t;
    t = ReadBufferedS16(other);
    self->length = (f32)t * 0.01666666753590107f;
    t = ReadBufferedU16(other);
    self->targetCount = t;
    self->targets = (s32*)AllocateFrontMemory(t << 2);
    for (k = 0; k < self->targetCount; k++) {
        self->targets[k] = ReadBufferedS16(other);
    }
    t = ReadBufferedS8(other);
    self->trackCount = t;
    self->tracks = (Track83*)AllocateZeroedFrontMemory(t * 28);
    for (i = 0; i < self->trackCount; i++) {
        e = &self->tracks[i];
        e->target = ReadBufferedS16(other);
        flags = ReadBufferedS8(other);
        if (flags & 1) {
            qp = CreatePositionCurve(ReadBufferedS8(other));
            e->pos = qp;
            if (qp->vt->read) qp->vt->read(qp, other);
        }
        if (flags & 2) {
            qr = CreateRotationCurve(ReadBufferedS8(other));
            e->rot = qr;
            if (qr->vt->read) qr->vt->read(qr, other);
        }
        if (flags & 4) {
            qs = CreateScaleCurve(ReadBufferedS8(other));
            e->scale = qs;
            if (qs->vt->read) qs->vt->read(qs, other);
        }
        if (flags & 8) {
            qw = CreateWeightCurve(ReadBufferedS8(other));
            e->weight = qw;
            if (qw->vt->read) qw->vt->read(qw, other);
        }
        if (flags & 0x10) {
            e->morphCount = ReadBufferedU8(other);
            e->morph = (WeightCurve**)AllocateZeroedFrontMemory(e->morphCount << 2);
            for (j = 0; j < e->morphCount; j++) {
                t = ReadBufferedS8(other);
                if (t != -1) {
                    e->morph[j] = CreateWeightCurve(t);
                    qw = e->morph[j];
                    if (qw->vt->read) qw->vt->read(qw, other);
                }
            }
        }
        sel = (flags & 0x20) ? e : sel;
    }
    if (sel != 0) MoveAnimationTrackToEnd(self, sel);
    ReadAnimationEvents(self, other, 0, &self->startCount, &self->startList);
    ReadAnimationEvents(self, other, 1, &self->timedCount, &self->timedList);
    ReadAnimationEvents(self, other, 0, &self->endCount, &self->endList);
    ReadPropertyRecords(self, other);
}

void ReadAnimationEvents(void* unused, Stream83* r, s32 flag, s32* count, AnimEvent** out)
{
    AnimEvent* e;
    s32 i;
    s32 merged;
    *count = ReadBufferedS8(r);
    *out = (AnimEvent*)AllocateZeroedFrontMemory(*count * 16);
    for (i = 0; i < *count; i++) {
        e = &(*out)[i];
        e->kind = ReadBufferedS8(r);
        if (flag) e->a0.f = (f32)ReadBufferedS16(r) * 0.016666668f;
        switch (e->kind) {
        case 44:
        case 51:
            ReadOptionalBufferedBlock(r, &e->a8.i);
            break;
        case 0: {
            SoundChoice t;
            SoundChoice* g;
            s32 j;
            s32 k;
            AnimEvent* q;
            merged = 0;
            t.ids[0] = ReadBufferedS16(r);
            t.target = ReadBufferedS16(r);
            t.f14 = ReadBufferedS32(r);
            t.f18 = ReadBufferedS32(r);
            t.f24 = ReadBufferedFloat(r);
            t.f1C = ReadBufferedFloat(r);
            t.f20 = ReadBufferedFloat(r);
            t.count = 1;
            t.cur = 0;
            k = i - 1;
            do {
                j = k;
                goto test;
            ins:
                g->ids[g->count++] = t.ids[0];
                goto done;
            } while (0);
        test:
            q = &(*out)[j];
            if (q->a0.f != e->a0.f) goto done;
            if (j < 0) goto done;
            if (q->kind != 0) {
                j--;
                goto test;
            }
            *count = *count - 1;
            i = k;
            merged = 1;
            g = (SoundChoice*)q->a8.i;
            if (g->count < 6) goto ins;
        done:
            if (!merged) {
                e->a8.i = (s32)AllocateFrontMemory(0x28);
                *(SoundChoice*)e->a8.i = t;
            }
            break;
        }
        case 4:
        case 7:
            F32(e->a8.i) = (f32)ReadBufferedS16(r) * 0.016666668f;
            F32(e->aC.i) = ReadBufferedFloat(r);
            break;
        case 19:
        case 20:
            e->a8.i = ReadBufferedS16(r);
            e->aC.i = ReadBufferedU8(r);
            break;
        case 16:
            e->a8.i = ReadBufferedS16(r);
            H0(e->aC.i) = ReadBufferedS8(r);
            H2(e->aC.i) = ReadBufferedS8(r);
            break;
        case 21:
        case 23:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0xC);
            ((Sub_12BC38*)e->a8.i)->w0 = ReadBufferedS16(r);
            F32(((Sub_12BC38*)e->a8.i)->w4) = ReadBufferedFloat(r);
            F32(((Sub_12BC38*)e->a8.i)->w8) = ReadBufferedFloat(r);
            break;
        case 25:
        case 26:
            H0(e->a8.i) = ReadBufferedS16(r);
            e->aC.i = (s32)AllocateZeroedFrontMemory(0x14);
            ((Sub_12BC38*)e->aC.i)->w0 = 1;
            ((Sub_12BC38*)e->aC.i)->w8 = ReadBufferedS16(r);
            ((Sub_12BC38*)e->aC.i)->wC = -1;
            ((Sub_12BC38*)e->aC.i)->w10 = 0;
            ((Sub_12BC38*)e->aC.i)->w4 = (s32)AllocateZeroedFrontMemory(0x20);
            ReadBufferedStreamBytes(r, 0x20, (void*)((Sub_12BC38*)e->aC.i)->w4);
            break;
        case 27:
            e->a8.i = ReadBufferedU8(r);
            e->aC.i = ReadBufferedS16(r);
            break;
        case 28:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0x10);
            ((Sub_12BC38*)e->a8.i)->w0 = ReadBufferedS16(r);
            ((Sub_12BC38*)e->a8.i)->w4 = ReadBufferedS16(r);
            F32(((Sub_12BC38*)e->a8.i)->w8) = ReadBufferedFloat(r);
            F32(((Sub_12BC38*)e->a8.i)->wC) = ReadBufferedFloat(r);
            break;
        case 37:
            H0(e->a8.i) = ReadBufferedS16(r);
            H2(e->a8.i) = ReadBufferedS16(r);
            break;
        case 6: case 12: case 13: case 17: case 18: case 22: case 24:
        case 29: case 30: case 31: case 32: case 35: case 36: case 39:
        case 41: case 59:
            e->a8.i = ReadBufferedS16(r);
            break;
        case 40:
            e->a8.i = ReadBufferedU16(r);
            break;
        case 38:
        case 45:
        case 47:
            e->a8.i = ReadBufferedS16(r);
            e->aC.i = ReadBufferedS16(r);
            break;
        case 48:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0x10);
            ((Sub_12BC38*)e->a8.i)->w0 = ReadBufferedS16(r);
            ((Sub_12BC38*)e->a8.i)->w4 = ReadBufferedS16(r);
            ((Sub_12BC38*)e->a8.i)->w8 = ReadBufferedS16(r);
            F32(((Sub_12BC38*)e->a8.i)->wC) = ReadBufferedFloat(r);
            break;
        case 9:
        case 10:
            e->a8.i = ReadBufferedS16(r);
            F32(e->aC.i) = ReadBufferedFloat(r);
            break;
        case 46:
        case 52:
            H0(e->a8.i) = ReadBufferedS16(r);
            H2(e->a8.i) = ReadBufferedS16(r);
            H0(e->aC.i) = ReadBufferedS16(r);
            break;
        case 54:
            H0(e->a8.i) = ReadBufferedS16(r);
            H2(e->a8.i) = ReadBufferedS16(r);
            ReadBufferedString(r, &e->aC.i);
            break;
        case 5:
        case 33:
        case 57:
        case 58:
            F32(e->a8.i) = ReadBufferedFloat(r);
            break;
        }
    }
}

void CopyAnimation(void)
{
    CopyObjectData();
}

void StartClampedKinematicValue(Animation* self)
{
    StartObject(self);
    Kin83* k = &self->kin;
    f32 t = g_currentEntry->dt;
    f32 v = k->pos + t * (k->vel + t * k->acc);
    f32 lo = self->lo;
    f32 hi = self->hi;
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    self->out = v;
    if (self->enabled) {
        AppendQueuedCallOnce(self->world, (void*)StartLinkedObjectAnimation, self, 0, 0);
    }
}

void StartLinkedObjectAnimation(Animation* self)
{
    s32 scratch[4];
    s32 v;
    if (self->id != -1) {
        v = (s32)FindFirstObjectById(self->world, 4, self->id, self);
        if (v == 0) {
            v = (s32)FindFirstObjectById(self->world, 0x104, self->id, self);
        }
    } else {
        v = 0;
    }
    CreateAnimationPlayerWithoutPresetTargets(self, v, 0, scratch, 0.0f, 1.0f);
}

void CreateAnimationPlayer(Animation* self, Animation* alt, s32 npairs, TargetBinding* pairs, s32 flags, AnimationPlayer** out, f32 fa, f32 fb)
{
    s32 tmp;
    AnimationPlayer* obj;
    AnimationPlayer** pobj;
    World* world = self->world;
    obj = NewAnimationPlayer(world);
    if (out != 0) *out = obj;
    obj->time = fa;
    obj->anim = self;
    obj->fC = alt;
    obj->f1C = *(f32*)((u8*)self + 0x7C);
    SetAnimationPlayerSpeed(obj, fb);
    AppendToList(self->props6C, obj);
    if (self->f50 != 0) {
        AppendToList((u8*)&world->f1B70, obj);
    } else {
        AppendToList((u8*)&world->f1B64, obj);
    }
    PushBackMemoryMark();
    Animation* ctx;
    if (alt == 0) ctx = self; else ctx = alt;
    PlacedObject** hosts = (PlacedObject**)AllocateBackMemory(self->targetCount * 4);
    s32 i;
    for (i = 0; i < self->targetCount; i++) {
        hosts[i] = (PlacedObject*)FindFirstObjectById(world, 4, self->targets[i], ctx);
    }
    s32 count = self->trackCount + (self->f9C != 0);
    for (s32 k = 0; k < count; k++) {
        Track83* e = &self->tracks[k];
        s32 key = e->target;
        PlacedObject* h;
        s32 j;
        for (j = 0; j < npairs; j++) {
            if (key == pairs[j].key) {
                h = (PlacedObject*)pairs[j].object;
                goto found;
            }
        }
        h = (PlacedObject*)FindFirstObjectById(world, 4, key, ctx);
        if (h == 0) {
            for (i = 0; i < self->targetCount; i++) {
                h = (PlacedObject*)FindFirstObjectById(world, 1, key, hosts[i]);
                if (h != 0) break;
            }
            if (h == 0) {
                h = (PlacedObject*)FindFirstObjectById(world, 0x104, key, ctx);
                if (h == 0) continue;
            }
        }
    found:
        TrackAttachmentBits* n = CreateTrackAttachment(h);
        n->f28 = k;
        n->f1C = obj;
        n->f14 = *(s32*)((u8*)self + 0x78);
        if (k >= self->trackCount) {
            if (e->scale == 0 && e->morph == 0) {
                PushFreeSlot((u8*)&self->world->pool1B20, n);
                continue;
            }
        } else {
            if (flags & 1) {
                n->f10 = n->f11 = 3;
            } else {
                ChoosePoseSourceModes(n);
            }
            if (e->pos == 0) n->f10 = -1;
            if (e->rot == 0 && e->weight == 0) n->f11 = -1;
        }
        if (e->scale != 0) n->f12 = 2;
        if (e->morph != 0) n->f13 = 2;
        AppendToList((u8*)&obj->list44, n);
        InsertAttachment(h, n);
        PlacedObject* r = h->root;
        if (r == 0) {
            r = h;
            while (r->parent != 0) r = (PlacedObject*)r->parent;
        }
        if (!(r->flags & 0x400000000000)) {
            if ((u32)obj->f5C < 0x20) {
                r->flags |= 0x400000000000;
                ((PlacedObject**)obj->f60)[obj->f5C++] = r;
            }
        }
    }
    PopBackMemoryMark();
    for (s32 j = 0; j < obj->f5C; j++) {
        ((PlacedObject**)obj->f60)[j]->flags &= ~0x400000000000;
    }
    RegisterObjectGroup(world, obj->f54);
    if (self->f4C != 0) SetAnimationPlayerPadSelect(obj, 1);
    tmp = 0;
    for (s32 m = 0; m < self->startCount; m++) {
        RunAnimationEvent(obj, &self->startList[m], &tmp);
    }
    ApplyListedPoseSources(obj, flags & 4);
    if (flags & 2) {
        RunSeekAnimationEvents(obj, self, &tmp);
    } else {
        SeekAnimationEventCursor(obj);
    }
    pobj = &obj;
    TriggerScriptEvent(self, 9, 1, &pobj);
}

s32 CreateAnimationPlayerWithoutPresetTargets(void* a, void* b, s32 c, s32 d)
{
    return CreateAnimationPlayer(a, b, 0, 0, c, d);
}

void* CreateAnimationPlayerReturned(void* self, s32 key, s32 a2)
{
    void* out;
    CreateAnimationPlayer(self, key, 0, 0, a2, &out);
    return out;
}

AnimationPlayer* FindAnimationPlayerByScope(Animation* self, s32 key)
{
    ListFrame frame;
    AnimationPlayer* node = *(AnimationPlayer**)self->props6C;
    if (node != 0) {
        do {
            if ((s32)node->fC == key) {
                return node;
            }
            node = node->animNext;
        } while (node != 0);
    }
    return 0;
}

void FindOrCreateAnimationPlayerAndSeek(void* self, s32 key, s32 a2, s32 a3, void** out, f32 fa, f32 fb)
{
    void* hit;
    void** dst = out ? out : &hit;
    hit = FindAnimationPlayerByScope(self, key);
    if (hit) {
        *dst = hit;
    } else {
        CreateAnimationPlayerWithoutPresetTargets(self, key, a3, dst, 0.0f, 1.0f);
    }
    SeekAnimationPlayer(*dst, a2, fa, fb);
}

void* FindOrCreateSeekedAnimationPlayer(void* self, s32 key, s32 a2, s32 a3, f32 fa, f32 fb)
{
    void* out;
    FindOrCreateAnimationPlayerAndSeek(self, key, a2, a3, &out, fa, fb);
    return out;
}

void ReplaceAnimationPlayer(void* self, void* a1, void* a2, void** out, f32 fa, f32 fb)
{
    if (*out != 0) {
        StopAnimationPlayer(*out);
        *out = 0;
    }
    if (self != 0) {
        CreateAnimationPlayerWithoutPresetTargets(self, a1, fa, fb, a2, out);
    }
}

s32 HasAnimationEventKind19(Animation* a0)
{
    s32 n = a0->timedCount;
    if (n > 0) {
        s32 i = 0;
        u8* p = (u8*)a0->timedList + 4;
        do {
            i++;
            if (*(s32*)p == 0x19) return 1;
            p += 0x10;
        } while (i < n);
    }
    return 0;
}

INCLUDE_RODATA(D_00249B10);

ASM_FUNC(func_0012C9E8);

AnimEvent* FindAnimationMarkerEvent(Animation* self, s32 key) {
    s32 i;
    AnimEvent* p;
    for (i = 0; i < self->startCount; i++) {
        p = &self->startList[i];
        if (p->kind == 0x27 && p->a8.i == key) {
            return p;
        }
    }
    for (i = 0; i < self->timedCount; i++) {
        p = &self->timedList[i];
        if (p->kind == 0x27 && p->a8.i == key) {
            return p;
        }
    }
    for (i = 0; i < self->endCount; i++) {
        p = &self->endList[i];
        if (p->kind == 0x27 && p->a8.i == key) {
            return p;
        }
    }
    return 0;
}

f32 GetAnimationMarkerTime(void)
{
    f32* p = (f32*)FindAnimationMarkerEvent();
    f32 r = 0.0f;
    if (p != 0) {
        r = *p;
    }
    return r;
}

void* FindEntryByObjectId(Gr8B* self, void* key)
{
    for (s32 i = 0; i < self->f38; i++) {
        Entry8B* e = (Entry8B*)(self->f3C + i * 0x1C);
        if (MatchesObjectId(key, e->key) != 0) {
            return e;
        }
    }
    return 0;
}

ASM_FUNC(func_0012CD78);

void GatherAnimationEventObjects(Animation* self, void* ctx, s32* outCount, s32** outArr)
{
    s32 n = 0;
    s32 i;
    u8* p;
    if (self->timedCount > 0) {
        i = self->timedCount;
        p = (u8*)self->timedList + 4;
        do {
            if (*(s32*)p == 0x29) n++;
            p += 16;
        } while (--i != 0);
    }
    if (outCount != 0) {
        *outCount = n;
    }
    if (outArr != 0) {
        s32* res = (s32*)AllocateBackMemory(n * 4);
        *outArr = res;
        i = 0;
        if (i < self->timedCount) {
            s32* out = res;
            do {
                AnimEvent* e = (AnimEvent*)(i * 16 + (u8*)self->timedList);
                if (e->kind == 0x29) {
                    *out = (s32)FindFirstObjectById(self->world, 0x104, e->a8.i, ctx);
                    out++;
                }
                i++;
            } while (i < self->timedCount);
        }
    }
}

void MoveAnimationTrackToEnd(Animation* self, Track83* p)
{
    Track83 tmp = *p;
    s32 idx = p - self->tracks;
    self->trackCount = self->trackCount - 1;
    if (idx < self->trackCount) {
        MoveMemory(p, p + 1, (self->trackCount - idx) * 0x1C);
    }
    p = self->tracks + self->trackCount;

    *p = tmp;
    self->f9C = p;
}

void MoveObjectAnimationTrackToEnd(Animation* a0)
{
    if (a0->f9C == 0) {
        void* r = FindEntryByObjectId();
        if (r) MoveAnimationTrackToEnd(a0, (Track83*)r);
    }
}

void SkipAnimationPlayerLoad() {}

void SkipAnimationPlayerStart() {}

void SkipAnimationPlayerCopy() {}

AnimationPlayer* NewAnimationPlayer(World* pool)
{
    AnimationPlayer* o = (AnimationPlayer*)PopZeroedFreeSlot(&pool->pool1B58);

    o->vt = &g_animationPlayerMethods;
    SetListLinkOffset(&o->list44, 0x20);
    o->f60 = (u8*)o + 0x64;

    return o;
}

void SetAnimationPlayerPadSelect(AnimationPlayer* self, s32 v)
{
    if (v == self->state24) {
        return;
    }
    if (v != 0) {
        AcquirePadSelectFlag(g_currentWorld);
    } else {
        ReleasePadSelectFlag(g_currentWorld);
    }
    self->state24 = (s8)v;
}

void SeekAnimationEventCursor(AnimationPlayer* self)
{
    Animation* track = self->anim;
    s32 n = track->timedCount;
    s32 i;
    if (n == 0) {
        return;
    }
    if (self->speed >= 0.0f) {
        i = 0;
        if (n > 0) {
            AnimEvent* keys = track->timedList;
            for (i = 0; i < track->timedCount; i++) {
                if (keys[i].a0.f >= self->time) {
                    break;
                }
            }
        }
        self->f20 = i;
    } else {
        for (i = n - 1; i >= 0; i--) {
            AnimEvent* k = &track->timedList[i];
            if (k->a0.f <= self->time) {
                break;
            }
        }
        self->f20 = i + 1;
    }
}

T2195_7C0* FindPlayerAttachmentByOwner(AnimationPlayer* a0, void* a1)
{
    ListFrame frame;
    T2195_7C0* n = (T2195_7C0*)a0->list44.head;
    while (n) {
        if (MatchesObjectId(n->owner, a1)) return n;
        n = (T2195_7C0*)n->w20.lo;
    }
    return 0;
}

LINKER_REMNANT(func_0012D5C8);

void RunAnimationEvent(AnimationPlayer* self, AnimEvent* msg, s32* out)
{
    EventScratch u;
    s32 rev = 0;
    Animation* owner = self->anim;
    World* world = owner->world;

    if (self->speed < 0.0f && msg >= owner->timedList) {
        rev = msg < &owner->timedList[owner->timedCount];
    }
    switch (msg->kind) {
    case 42:
        if (CheckStreamVoicePending() != 0) {
            self->time = ClampRange::Of(msg->a0.f, 0.0f, owner->length);
            self->f20--;
            *out = 1;
        }
        break;
    case 44:
        OpenKeyRecord(msg->a8.p);
        break;
    case 43:
        StopStreamVoice();
        break;
    case 0: {
#define Q_12D5D0 ((SoundChoice*)msg->a8.p)
        s32 idx;
        s32 busy;
        s32 id;
        Collider* tgt;
        if (Q_12D5D0->count < 2) {
            idx = 0;
        } else {
            s32 r = RandomIntInRange(0, Q_12D5D0->count - 2);
            idx = (Q_12D5D0->cur + r + 1) % Q_12D5D0->count;
            Q_12D5D0->cur = idx;
        }
        id = Q_12D5D0->ids[idx];
        if (id == -1) {
            return;
        }
        busy = IsSoundEntryAvailable(id);
        if (self->p50 != 0 && busy != 0) {
            return;
        }
        if (Q_12D5D0->target != -1) {
            tgt = (Collider*)FindFirstObjectById(world, 0x104, Q_12D5D0->target, self->fC ? self->fC : (void*)self->anim);
        } else {
            tgt = (Collider*)self->fC;
        }
        if (tgt != 0) {
            StartSoundEffect(id, busy ? (void**)&self->p50 : 0, tgt, 0, (f32)Q_12D5D0->f18, (f32)Q_12D5D0->f14, Q_12D5D0->f24,
                          Q_12D5D0->f1C, Q_12D5D0->f20, 0, 0);
            if (busy && self->p50 != 0) {
                tgt->desc->m0E(tgt, 8, self->p50);
            }
        } else {
            StartSoundEffect(id, busy ? (void**)&self->p50 : 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
#undef Q_12D5D0
        break;
    }
    case 1:
        if (self->p50 != 0) {
            StopSoundRecord((void*)self->p50, 0);
        }
        break;
    case 2:
        RestoreVolumeChannel2();
        break;
    case 3:
        SilenceVolumeChannel2();
        break;
    case 11:
        self->time = ClampRange::Of(msg->a0.f, 0.0f, owner->length);
        self->speed = 0.0f;
        break;
    case 4:
    case 7:
        self->time = msg->a8.f;
        SetAnimationPlayerSpeed(self, msg->aC.f);
        SeekAnimationEventCursor(self);
        SettleListedPoseSources(self);
        break;
    case 5:
        SetAnimationPlayerSpeed(self, msg->a8.f);
        break;
    case 6: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t != 0) {
            ChooseStepSequenceState(t);
        }
        break;
    }
    case 8:
        StopAnimationPlayer(self);
        *out = 1;
        break;
    case 9:
    case 10: {
        s32 on = msg->kind == 9;
        if (rev) {
            on = !on;
        }
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t == 0) {
            return;
        }
        if (msg->aC.f != 0.0f) {
            if (on) {
                FadeInPlacedObject(t, msg->aC.f);
            } else {
                FadeOutPlacedObject(t, msg->aC.f);
            }
        } else {
            if (on) {
                t->desc->m02(t);
            } else {
                t->desc->m03(t);
            }
        }
        break;
    }
    case 16: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)self->anim);
        if (t != 0) {
            SetColliderAnchors(t, msg->aC.h.lo < 0 ? t->mode450 : msg->aC.h.lo, 0, msg->aC.h.hi < 0 ? t->mode470 : msg->aC.h.hi, 0);
        }
        break;
    }
    case 12:
    case 13: {
        s32 on = msg->kind == 12;
        Collider* t;
        if (rev) {
            on = !on;
        }
        t = (Collider*)FindFirstObjectById(world, 4, msg->a8.i, self->anim);
        if (t != 0) {
            if (on) {
                PushObjectCameraController(t);
            } else {
                RemoveObjectCameraController(t);
            }
        }
        break;
    }
    case 14:
    case 15:
    {
        s32 on = msg->kind == 14;
        if (rev) {
            on = !on;
        }
        SetAnimationPlayerPadSelect(self, on);
    }
        break;
    case 19:
    case 20: {
        s32 on = msg->kind == 19;
        if (rev) {
            on = !on;
        }
        SwitchPlayerState11(g_player, on);
        if (on && msg->aC.i != 0) {
            ApplyListedPoseSources(self, 1);
        }
        break;
    }
    case 17:
    case 18: {
        TrackAttachment* n = FindPlayerAttachmentByOwner(self, msg->a8.i);
        if (n != 0) {
            if ((msg->kind != 17) != !rev) {
                n->SetMode(5);
                n->mode0 = 5;
            } else {
                ChoosePoseSourceModes(n);
            }
        }
        break;
    }
    case 21:
    case 22:
    case 23:
    case 24: {
        TrackAttachment* n;
        s32 key;
        if (msg->kind == 21 || msg->kind == 23) {
            key = *(s32*)msg->a8.p;
        } else {
            key = msg->a8.i;
        }
        n = FindPlayerAttachmentByOwner(self, key);
        if (n == 0) {
            break;
        }
        switch (msg->kind) {
        case 21:
            self->driven = n;
            self->f2C = msg;
            break;
        case 22:
            self->f2C = 0;
            if (self->f30 == 0) {
                self->driven = 0;
            }
            break;
        case 23:
            self->driven = n;
            self->f30 = msg;
            break;
        case 24:
            self->f30 = 0;
            if (self->f2C == 0) {
                self->driven = 0;
            }
            break;
        }
        break;
    }
    case 25:
        StartScreenFade(g_screenFade, msg->aC.i, msg->a8.h.lo);
        break;
    case 26:
        SaveFadeRequest(g_screenFade, msg->aC.i, msg->a8.h.lo);
        break;
    case 27: {
        Player* g = g_player;
        if (g != 0 && *(s32*)((u8*)g + 0x2220) == 9 && *(s32*)((u8*)g + 0x2228) == 0x1C && g_currentEntry == g_currentLevelRecord) {
            return;
        }
        BeginLevelExit(msg->a8.i, msg->aC.i);
        break;
    }
    case 33:
        StartTimer(&g_timerElement, msg->a8.f);
        StartTimerCounting(&g_timerElement);
        break;
    case 34:
        StopTimer(&g_timerElement);
        break;
    case 28: {
        Collider* a = (Collider*)FindFirstObjectByIdMode4(world, ((EventObjectPair*)msg->a8.p)->f0, owner->parent);
        Collider* b;
        if (((EventObjectPair*)msg->a8.p)->f4 != -1) {
            b = (Collider*)FindFirstObjectByIdMode4(owner->world, ((EventObjectPair*)msg->a8.p)->f4, owner->parent);
        } else {
            b = 0;
        }
        if (a != 0) {
            CreateAnimationPlayerWithoutPresetTargets(a, b, 0, 0, *(f32*)&((EventObjectPair*)msg->a8.p)->f8, ((EventObjectPair*)msg->a8.p)->fC);
        }
        break;
    }
    case 29:
    case 30:
    case 31:
    case 32: {
        TrackAttachment* n = FindPlayerAttachmentByOwner(self, msg->a8.i);
        u8 go = 0;
        if (n != 0) {
            Track83* e = &owner->tracks[n->index];
            switch (msg->kind) {
            case 29:
                if (e->scale != 0) {
                    u8 v = n->mode2;
                    n->mode2 = 2;
                    go = (u8)(v + 1) < 2;
                }
                break;
            case 30:
                if (e->scale != 0) {
                    s8 v = n->mode2;
                    n->mode2 = -1;
                    go = v != -1;
                }
                break;
            case 31:
                if (e->morph != 0) {
                    u8 v = n->mode3;
                    n->mode3 = 2;
                    go = (u8)(v + 1) < 2;
                }
                break;
            case 32:
                if (e->morph != 0) {
                    s8 v = n->mode3;
                    n->mode3 = -1;
                    go = v != -1;
                }
                break;
            }
        }
        if (go) {
            n->owner->desc02()->m2B(n->owner);
        }
        break;
    }
    case 35:
    case 36: {
        TrackAttachment* n = FindPlayerAttachmentByOwner(self, msg->a8.i);
        if (n == 0) {
            break;
        }
        Track83* e = &owner->tracks[n->index];
        PlacedObject* o = n->owner;
        if (msg->kind == 35) {
            e->pos->vt->eval(e->pos, o, 0, &u.v[0], &u.v[1], msg->a0.f, self->speed);
            o->desc02()->m1D(o, (Vec02*)&u.v[0]);
            o->desc02()->m20(o, (Vec02*)&u.v[1]);
        } else {
            e->rot->vt->eval(e->rot, o, 0, &u.v[2], &u.v[0], msg->a0.f, self->speed);
            o->desc02()->m1E(o, (Mat02*)&u.v[2]);
            o->desc02()->m21(o, (Vec02*)&u.v[0]);
        }
        break;
    }
    case 37:
        StartPadRecordPattern(g_padRecord, msg->a8.h.hi, (f32)msg->a8.h.lo * 0.016666668f);
        break;
    case 38: {
        Collider* t;
        if (msg->a8.i == -1) {
            t = (Collider*)self->fC;
        } else {
            t = (Collider*)FindFirstObjectByIdMode4(world, msg->a8.i, self->fC);
        }
        if (t == 0) {
            break;
        }
        u.p[1] = (void*)msg->aC.i;
        u.p[0] = self;
        t->desc->m0E(t, 0x12, u.p);
        break;
    }
    case 39: {
        *(f32*)&u.w[1] = msg->a0.f;
        u.w[2] = msg->a8.i;
        u.p[0] = self;
        NotifyAnimationPlayerCallbacks(self, 0x13, u.w);
        break;
    }
    case 40: {
        u.p[1] = &msg->a8;
        u.p[0] = &self;
        TriggerScriptEvent(self->anim, 0xA, 2, u.p);
        break;
    }
    case 41: {
        Collider* t;
        if (self->fC == 0) {
            break;
        }
        t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC);
        if (t == 0) {
            break;
        }
        u.p[1] = t;
        *(f32*)&u.w[2] = msg->a0.f;
        u.p[0] = self;
        NotifyAnimationPlayerCallbacks(self, 0x15, u.w);
        break;
    }
    case 45: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC);
        if (t != 0) {
            SelectValueEntryByKey(t, msg->aC.i);
        }
        break;
    }
    case 46: {
        void* scope = self->fC ? self->fC : (void*)self->anim;
        Collider* a = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.h.lo, scope);
        Collider* b;
        void* link;
        if (a == 0) {
            break;
        }
        b = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.h.hi, scope);
        link = FindListNodeByKey(a, b);
        if (link == 0) {
            link = CreateStateWalker(a, b, msg->aC.h.lo, 1);
        }
        SetStateWalkerTarget(link, msg->aC.h.lo);
        break;
    }
    case 47: {
        void* link = 0;
        void* scope = self->fC;
        if (scope == 0) {
            scope = self->anim;
        }
        Collider* a = (Collider*)FindFirstObjectByIdMode4(world, msg->a8.i, scope);
        if (a != 0) {
            link = FindListNodeByKey(a, (Collider*)FindFirstObjectByIdMode4(world, msg->aC.i, scope));
        }
        if (link != 0) {
            DestroyStateWalker(link);
        }
        break;
    }
    case 48: {
        EventObjectPair* in = (EventObjectPair*)msg->a8.p;
        void* scope = self->fC ? self->fC : (void*)owner;
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, in->f0, scope);
        if (t == 0) {
            break;
        }
        u.req.flags = 0;
        if (in->f4 != -1) {
            Collider* s = (Collider*)FindFirstObjectById(world, 4, in->f4, scope);
            if (s != 0) {
                if (IsObjectOfKind(s, 2) != 0) {
                    u.req.owner = s;
                    u.req.flags |= 1;
                } else if (IsObjectOfKind(s, 0x7E) != 0) {
                    u.req.flags |= 4;
                    ConvertPositionToWorld(s, (Vec4U*)&u.req.qb);
                } else if (IsObjectOfKind(s, 0x73) != 0) {
                    u.req.flags |= 4;
                    GetObjectWorldPosition(s, (Vec4U*)&u.req.qb);
                }
            }
        }
        if (u.req.flags == 0) {
            if (t->parent != 0 && IsObjectAttached(t->parent) != 0) {
                u.req.flags |= 1;
                u.req.owner = t->parent;
            } else {
                u.req.flags |= 4;
                GetObjectWorldPosition(t, (Vec4U*)&u.req.qb);
            }
        }
        if (in->f8 != -1) {
            Collider* s = (Collider*)FindFirstObjectById(world, 4, in->f8, scope);
            if (s != 0) {
                u.req.f38 = s;
                u.req.flags |= 0x20;
            }
        }
        if (in->fC != 1.0f) {
            u.req.flags |= 0x18;
            u.req.f30 = in->fC;
        }
        t->desc->m1B(t, &u.req);
        break;
    }
    case 49:
        ShowCountedScreenElement(world);
        break;
    case 50:
        HideCountedScreenElement(world);
        break;
    case 51:
        QueueMovie(g_moviePlayer, msg->a8.i);
        break;
    case 52:
        g_stackedCaptionGroup.vt->m17(&g_stackedCaptionGroup, &self->time);
        ResizeItemColumn(&g_stackedCaptionGroup, msg->aC.h.lo, (f32)msg->a8.h.lo, (f32)msg->a8.h.hi);
        break;
    case 53:
        g_stackedCaptionGroup.vt->m17(&g_stackedCaptionGroup, 0);
        ClearItemColumn(&g_stackedCaptionGroup);
        break;
    case 54:
        PostItemColumnEntry(&g_stackedCaptionGroup, msg->a8.h.lo, msg->aC.i, (f32)msg->a8.h.hi * 0.00390625f);
        break;
    case 55:
    {
        u8* sys = g_elementStack;
        ((U32P*)(sys + 0x30))->v = 0;
        SetElementStackState(sys, 0);
    }
        break;
    case 56:
    {
        u8* sys = g_elementStack;
        *(s32*)(sys + 0x30) = 1;
        SetElementStackState(sys, 1);
    }
        break;
    case 57:
        SetWorldValueAndTarget(world, msg->a8.f);
        break;
    case 58:
        SetWorldValueTarget(world, msg->a8.f);
        break;
    case 59: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t != 0) {
            BindEntryQueueToObject(t, g_player);
        }
        break;
    }
    }
}

void RunSeekAnimationEvents(AnimationPlayer* self, Animation* sub, s32* out)
{
    f32 limit = self->time + 0.0001f;
    if (sub->timedCount != 0) {
    while (self->f20 < sub->timedCount && sub->timedList[self->f20].a0.f < limit) {
        AnimEvent* it = &sub->timedList[self->f20++];
        switch (it->kind) {
        case 8:
            self->time = it->a0.f;
            self->speed = 0;
            *out = 1;
            return;
        case 9:
        case 10:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 28:
        case 39:
            RunAnimationEvent(self, it, out);
            break;
        }
    }
    }
}

void RunAnimationEventsToTime(AnimationPlayer* self, Animation* list, s32* out)
{
    if (list->timedCount == 0) return;
    for (;;) {
        if (self->f20 < list->timedCount) {
            if (list->timedList[self->f20].a0.f < self->time || (self->time == list->timedList[self->f20].a0.f && 0.0f < self->speed)) {
                AnimEvent* e = &list->timedList[self->f20];
                self->f20 = self->f20 + 1;
                RunAnimationEvent(self, e, out);
                if (*out != 0) return;
                continue;
            }
        }
        if (self->f20 <= 0) return;
        if (self->time < list->timedList[self->f20 - 1].a0.f || (self->time == list->timedList[self->f20 - 1].a0.f && self->speed < 0.0f)) {
            self->f20 = self->f20 - 1;
            RunAnimationEvent(self, &list->timedList[self->f20], out);
            if (*out != 0) return;
            continue;
        }
        return;
    }
}

void ReleaseWorldListEntry(void* a0)
{
    RemoveFromList((u8*)&g_currentWorld->list1B7C, a0);
    PushFreeSlot((u8*)&g_currentWorld->pool1B58, a0);
}

void StopAnimationPlayer(AnimationPlayer* self)
{
    WordListFrame fr;
    EndEventLocals tmp;
    s32 i = 0;
    Animation* sub = self->anim;
    u8* base = (u8*)sub->world;
    for (i = 0; i < sub->endCount; i++) {
        AnimEvent* it = (AnimEvent*)((u8*)sub->endList + i * 16);
        tmp.a = 0;
        RunAnimationEvent(self, it, &tmp);
    }
    NotifyAnimationPlayerCallbacks(self, 6, self);
    ReleaseCallRecords(base, self->fE4);
    self->fE4 = 0;
    UnregisterObjectGroup(base, self->f54);
    SetAnimationPlayerPadSelect(self, 0);
    RemoveQueuedCalls(base, 2, 0, self, -1, 0);
    RemoveFromList(sub->props6C, self);
    if (sub->f50 != 0) {
        RemoveFromList(base + 0x1B70, self);
    } else {
        RemoveFromList(base + 0x1B64, self);
    }
    AppendToList(base + 0x1B7C, self);
    s32 s0 = (s32)self + 0xC;
    s32 e = (s32)self + 0x44;
    fr.link = e;
    fr.list = e;
    s32 link = *(s32*)(e + 8);
    fr.prev = (s32)g_activeListFrames;
    g_activeListFrames = (ListFrame*)&fr;
    fr.offset = link;
    s32 head = *(s32*)e;
    fr.link = head + fr.offset;
    s32 a = head;
    if (a != 0) {
        do {
            Attachment* el = (Attachment*)a;
            el->vt->release(el, 7);
            s32 nx = *(s32*)fr.link;
            fr.link = nx + fr.offset;
            a = nx;
        } while (a != 0);
    }
    if (self->f50 != 0)
        ClearSoundRecordHandle(&self->f50);
    tmp.b = s0;
    TriggerScriptEvent(sub, 0xB, 1, &tmp.b);
    g_activeListFrames = (ListFrame*)fr.prev;
}

void ReleasePlayerAttachment(void* a0, void* a1, void* a2)
{
    Attachment* n = FindPlayerAttachmentByOwner(a0, a1);
    if (n) n->vt->release(n, (s32)a2);
}

f32 GetRangeFalloffScale(RangeFalloffOwner* self, f32 value)
{
    FalloffRange* range = self->range;
    f32 r;
    if (value < range->minimum) {
        r = 1.0f;
    } else if (range->maximum <= value) {
        r = 0.15f;
    } else {
        r = (value - range->maximum) / (range->minimum - range->maximum);
        r = r * 0.85f + 0.15f;
    }
    return r;
}

s32 ApplyAnimationLoopMode(AnimationPlayer* o, f32* pos, f32* vel)
{
    s32 r = 0;
    Animation* l = o->anim;
    f32 x = *pos;
    f32 lim = l->length;
    if (lim <= x) {
        switch (l->f44) {
        case 0:
            if (lim < x) {
                *pos = lim;
                *vel = 0.0f;
            }
            break;
        case 1:
            *pos = FloatRemainder(x, lim);
            break;
        case 2: {
            f32 d = lim + lim;
            s32 flag = 1;
            if (d <= x) {
                *pos = FloatRemainder(x, d);
                if (*pos < l->length) flag = 0;
                *vel = __builtin_fabsf(*vel);
            }
            if (flag) {
                *pos = d - *pos;
                *vel = -*vel;
            }
            break;
        }
        }
        r = 1;
    } else if (x < 0.0f) {
        switch (l->f44) {
        case 0:
            *pos = 0.0f;
            *vel = 0.0f;
            break;
        case 1:
            *pos = WrapModulo(x, lim);
            break;
        case 2: {
            x = -x;
            if (x <= lim) {
                *pos = x;
                *vel = -*vel;
            } else {
                f32 d = lim + lim;
                *vel = __builtin_fabsf(*vel);
                f32 q = WrapModulo(*pos, d);
                *pos = q;
                if (l->length <= q) {
                    *pos = d - q;
                    *vel = -*vel;
                }
            }
            break;
        }
        }
        r = 1;
    }
    return r;
}

ASM_FUNC(func_0012EBD8);

void SeekAnimationPlayer(AnimationPlayer* self, s32 mode, f32 a, f32 b)
{
    s32 flag = 0;
    f32 t;
    f32 base;
    switch (mode) {
    case 0:
        t = a;
        goto call;
    case 1:
        base = self->time;
        break;
    case 2:
    case 3:
        base = self->anim->length;
        break;
    default:
        goto call;
    }
    t = base + a;
call:
    SetAnimationPlayerSpeed(self, b);
    if (t == self->time) {
        return;
    }
    self->time = t;
    if (mode == 3) {
        RunSeekAnimationEvents(self, self->anim, &flag);
    } else {
        SeekAnimationEventCursor(self);
    }
    ApplyListedPoseSources(self, 0);
    SettleListedPoseSources(self);
    if (flag != 0) {
        StopAnimationPlayer(self);
    }
}

void ApplyListedPoseSources(AnimationPlayer* a0, void* a1)
{
    ListFrame frame;
    T2195_7C0* n = (T2195_7C0*)a0->list44.head;
    while (n) {
        ApplyPoseSource(n, a1);
        n = (T2195_7C0*)n->w20.lo;
    }
}

void SettleListedPoseSources(AnimationPlayer* self)
{
    ListFrame frame;
    for (T2195_7C0* p = (T2195_7C0*)self->list44.head; p != 0; p = (T2195_7C0*)p->w20.lo) {
        SettlePoseSourceModes(p);
    }
}

ASM_FUNC(func_0012F210);

void SetAnimationPlayerSpeed(AnimationPlayer* self, f32 x)
{
    self->speed = x * self->f1C * self->anim->out;
}

void SetAnimationPlayerSpeedScale(AnimationPlayer* self, f32 x)
{
    f32 denom = self->f1C * self->anim->out;
    f32 r = self->speed;
    if (denom != 0.0f) {
        r = r / denom;
    }
    self->f1C = x;

    SetAnimationPlayerSpeed(self, r);
}

void SetAttachmentSortKeys(AnimationPlayer* owner, s32 value)
{
    ListFrame frame;
    T2195_7C0* node = (T2195_7C0*)owner->list44.head;
    while (node != 0) {
        node->key = value;
        SortAttachments(node->owner);
        node = (T2195_7C0*)node->w20.lo;
    }
}

void NotifyAnimationPlayerCallbacks(AnimationPlayer* self, s32 a1, s32 a2)
{
    BaseObject* obj = (BaseObject*)self->fC;
    if (obj != 0) {
        obj->desc->m0E(obj, a1, (void*)a2);
    }
    QueuedCall* node = self->fE4;
    while (node != 0) {
        QueuedCall* next = node->next;
        node->fn(node->k1, a1, a2);
        node = next;
    }
}

void AddAnimationPlayerCallback(AnimationPlayer* a0, void* a1, s32 a2)
{
    AddCallbackNode(a0->anim->world, &a0->fE4, a1, a2);
}

void AddAnimationPlayerRecordCallback(AnimationPlayer* a0, PlacedObject** a1)
{
    AddCallbackNode(a0->anim->world, &a0->fE4, (void*)(*a1)->link40.prev, a1);
}

void InitIdFilterObject(IdFilterObject* self)
{
    InitCollider(self);
    SetColliderAnchors(self, 3, 0, 3, 0);
    self->id = -1;
}

void CopyIdFilterObject(IdFilterObject* self)
{
    CopyCollider(self);
    if (self->parent == 0) {
        InitContactPairFlags(self->world, self);
    }
}

void StartIdFilterObject(IdFilterObject* self)
{
    StartPlacedObject(self);
    if (self->id != -1) {
        self->id = (s32)FindFirstObjectByIdMode4(self->world, self->id, self);
        self->mode = 2;
        return;
    }
    ListFrame it;
    ListWalkBegin::Of(&it, &self->children);
    PlacedObject* n = ListWalkNextPlaced::Of(&it);
    if (n == 0 || IsObjectOfKind(n, 0x7E) == 0) {
        g_activeListFrames = (ListFrame*)it.prev;
        return;
    }
    if (ListWalkNextPlaced::Of(&it) != 0) {
        g_activeListFrames = (ListFrame*)it.prev;
        return;
    }
    TransformPointBetweenFrames(self, 0, (u8*)n + 0x40, &self->pos);
    self->mode = 1;
    n->desc->m03(n);
    g_activeListFrames = (ListFrame*)it.prev;
}

void UpdateIdFilterObject(IdFilterObject* self)
{
    Quad4 loc;
    PlacedObject* cur;
    UpdateCollider(self);
    if (self->pendingTarget != 0) {
        self->pendingTarget->desc02()->m20(self->pendingTarget, (Vec02*)&D_00248D30);
        self->pendingTarget->desc02()->m21(self->pendingTarget, (Vec02*)&D_00248D30);
        switch (self->mode) {
        case 1:
            self->pendingTarget->desc02()->m1D(self->pendingTarget, &self->pos);
            break;
        case 2: {
            PlacedObject* node = self->found;
            TransformPointBetweenFrames(node->parent, 0, &node->link40, &loc);
            self->pendingTarget->desc02()->m1D(self->pendingTarget, (Vec02*)&loc);
            break;
        }
        }
        cur = self->pendingTarget;
        self->pendingTarget = 0;
        self->placedTarget = cur;
    }
}

s32 TestIdFilterMatch(IdFilterObject* self, Collider* key)
{
    s32 hit;
    s32 i;
    s32 j;

    if (TestCollidersMayContact(self, key) != 0) {
        return 1;
    }
    for (i = 0; i < self->objectIds.count; i++) {
        if (MatchesObjectId(key, self->objectIds.items[i]) != 0) {
            break;
        }
    }
    if (i < self->objectIds.count) {
        hit = 1;
        goto tail;
    }
    for (j = 0; j < self->classIds.count; j++) {
        if (IsObjectOfKind(key, self->classIds.items[j]) != 0) {
            break;
        }
    }
    hit = j < self->classIds.count;
tail:
    if (self->acceptsListed != 0) {
        return hit;
    }
    return hit ^ 1;
}

ASM_FUNC(func_0012FB68);

void AddIdFilterObjectId(IdFilterObject* a0, s32 a1)
{
    a0->objectIds.items[a0->objectIds.count++] = a1;
}

void AddIdFilterClassId(IdFilterObject* obj, s32 value) { obj->classIds.items[obj->classIds.count++] = value; }

StreamReader* InitStreamReader(StreamReader* obj, s32 value)
{
    obj->sector = 0;
    obj->buffer = (value + 0x3F) & -64;
    obj->fileHandle = -1;
    obj->pendingDest = 0;
    obj->readyStart = 0;
    obj->total = 0;
    obj->remaining = 0;
    obj->pendingLength = 0;
    obj->usedLength = 0;
    obj->readyLength = 0;
    return obj;
}

void DestroyStreamReader(void* self, s32 flags)
{
    CloseStreamReader((StreamReader*)self);
    if (flags & 1) FreeObjectMemory(self);
}

s32 OpenSectorStreamRange(void* self, KeyId* pair)
{
    return OpenSectorStream(self, pair->first, pair->second);
}

LINKER_REMNANT(func_0012FD98);

s32 OpenSectorStream(StreamReader *self, s32 a1, s32 a2) {
    self->sector = a1;
    s32 t = self->buffer;
    self->total = a2;
    self->remaining = a2;
    self->sourceKind = 1;
    self->readyStart = t;
    self->readyLength = 0;
    self->usedLength = 0;
    StartChunkRead(self);
    return 1;
}

void CloseStreamReader(StreamReader* a0)
{
    switch (a0->sourceKind) {
    case 0:
        if (a0->fileHandle >= 0) CloseFile(a0->fileHandle);
        a0->fileHandle = -1;
        break;
    case 1:
        if (IsReadPending(a0)) {
            SyncDiscNCommand(0);
            CommitChunk(a0);
        }
        a0->sector = 0;
        break;
    }
    a0->sourceKind = -1;
}

void StartChunkRead(StreamReader* self)
{
    if (IsReadPending(self) != 0) {
        return;
    }
    s32 size = self->remaining;
    if (size == 0) {
        return;
    }
    s32 clamp = 0x4000;
    if (!(size > 0x3FFF)) {
        clamp = size;
    }
    s32 base = self->buffer;
    if (self->readyStart == base) {
        base += 0x4000;
    }
    self->pendingLength = clamp;
    self->pendingDest = base;
    switch (self->sourceKind) {
    case 0:
        ReadFile(self->fileRef, base, clamp);
        break;
    case 1:
        StartLowLevelDiscReadUntilAccepted(self->sectorRef, (s32)((u32)(clamp + 0x7FF) >> 11), base);
        break;
    }
}

s32 IsReadPending(StreamReader* a0)
{
    return a0->pendingLength != 0;
}

s32 PollChunkRead(StreamReader* a0)
{
    s32 r = 0;
    s32 done = 0;
    if (a0->readyLength == a0->usedLength && IsReadPending(a0)) {
        switch (a0->sourceKind) {
        case 0: {
            s32 tmp;
            done = ControlFile(a0->fileHandle, 1, &tmp);
            r = tmp == 0;
            break;
        }
        case 1:
            r = SyncDiscNCommand(1) == 0;
            if (r) done = GetDiscError();
            break;
        }
    }
    if (done) {
        a0->pendingLength = 0;
        a0->pendingDest = 0;
        r = 0;
    }
    return r;
}

void CommitChunk(StreamReader* self)
{
    if (PollChunkRead(self) == 0) {
        return;
    }
    if (self->sourceKind == 1) {
        self->sector += self->pendingLength / 2048;
    }
    s32 v = self->pendingLength;
    self->remaining -= v;
    self->readyLength = v;
    self->readyStart = self->pendingDest;
    self->pendingLength = 0;
    self->pendingDest = 0;
    self->usedLength = 0;
}

void PumpStreamReader(StreamReaderWindow* self)
{
    switch (self->sourceKind) {
    case 0:
        StartChunkRead(self);
        CommitChunk(self);
        break;
    case 1:
        CommitChunk(self);
        StartChunkRead(self);
        break;
    }
}

void ConsumeStreamBytes(StreamReaderWindow* a0, s32 a1)
{
    a0->usedLength += a1;
}

s32 IsObjectOfKind(BaseObject* list, s32 key)
{
    const Desc01* node = list->desc;
    while (node != 0) {
        if (node->id == key) {
            return 1;
        }
        node = (const Desc01*)node->parent;
    }
    return 0;
}

void EnsureKeyedList(BaseObject* self)
{
    if (self->f04 == 0) {
        void* v = NewKeyedList();
        self->f04 = v;
        AddMarkRootList(g_markStacks, v);

    }
}

// A property getter (func_00109488 installs it): the object's class id.
void GetObjectClassId(BaseObject* self, s32* out)
{
    *out = self->desc->id;
}

void SolveBezierSegment(f32 delta, f32 diff, f32 scale, f32 p4, f32 p18, f32 p1C, f32 p24, f32 p2C, f32 p30, f32* outF, f32* outI, s32 zero)
{
    f32 c[4];
    if (diff < 0.0001f) {
        diff = 0.0f;
    } else if (delta - diff < 0.0001f) {
        diff = 1.0f;
    } else {
        f32 d3 = (delta - p2C) * 3.0f;
        f32 g3 = p18 * 3.0f;
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        s32 k = 0;
        c[2] = g3;
        c[3] = -diff;
        f32 a = g3 - d3;
        f32 b = d3 - g3;
        b = b - g3;
        a = a + delta;
        c[1] = b;
        c[0] = a;
        do {
            f32 m = lo + 1.0f / (f32)(1 << (k + 1));
            f32 v = m * (m * (m * c[0] + c[1]) + c[2]) + c[3];
            if (v < 0.0f) {
                lo = m;
            } else if (0.0f < v) {
                hi = m;
            } else {
                break;
            }
        } while (++k < 16);
        diff = (lo + hi) * 0.5f;
    }
    if (outF != 0) {
        f32 a3 = p1C * 3.0f;
        f32 b3 = p30 * 3.0f;
        c[3] = p4;
        c[0] = a3 - p4 - b3 + p24;
        c[1] = p4 * 3.0f - p1C * 6.0f + b3;
        c[2] = p4 * -3.0f + a3;
        *outF = diff * (diff * (diff * c[0] + c[1]) + c[2]) + p4;
    }
    if (outI != 0) {
        c[0] = p4 * -3.0f + p1C * 9.0f - p30 * 9.0f + p24 * 3.0f;
        c[1] = p4 * 6.0f - p1C * 12.0f + p30 * 6.0f;
        c[2] = p4 * -3.0f + p1C * 3.0f;
        f32 num = diff * (diff * c[0] + c[1]) + c[2];
        f32 d3 = (delta - p2C) * 3.0f;
        f32 g3 = p18 * 3.0f;
        c[2] = g3;
        c[0] = g3 * 3.0f - d3 * 3.0f + delta * 3.0f;
        c[1] = g3 * -4.0f + (d3 + d3);
        f32 den = diff * (diff * c[0] + c[1]) + c[2];
        *outI = num * scale / den;
    }
}

void EvaluateHermiteSegment(f32* p0, f32* p1, f32* p2, f32 dur, f32 t, f32 e, f32 a, f32 b, f32 c, f32 dd)
{
    f32 u = t / dur;
    f32 v = 1.0f - u;
    f32 span = c - a;
    if (p0 != 0) {
        f32 uv = u * v;
        f32 vv = v * v;
        f32 uu = u * u;
        f32 uvv = uv * v;
        f32 vvv = vv * v;
        f32 uuv = uu * v;
        f32 t5 = uvv * 3.0f;
        f32 uvd = uvv * dur;
        f32 t4 = uuv * 3.0f;
        f32 t0 = vvv + t5;
        f32 uuu = uu * u;
        f32 p2b = uvd * b;
        f32 p1a = t0 * a;
        f32 q = uuv * dur;
        f32 t3 = uuu + t4;
        f32 s = p1a + p2b;
        f32 qd = q * dd;
        f32 t3c = t3 * c;
        f32 r = s - qd;
        *p0 = r + t3c;
    }
    if (p1 != 0) {
        f32 t1 = (u * (6.0f * v)) / dur * span;
        f32 t2 = (1.0f - (u * (4.0f - 3.0f * u))) * b;
        f32 w2 = 3.0f * u + -2.0f;
        f32 t3 = (u * w2) * dd;
        *p1 = ((t1 + t2) + t3) * e;
    }
    if (p2 != 0) {
        f32 dd2 = dur * dur;
        f32 ee = e * e;
        f32 s1 = (6.0f - 12.0f * u) / dd2 * span;
        f32 s2 = (6.0f * u - 4.0f) / dur * b;
        f32 s3 = (6.0f * u - 2.0f) / dur * dd;
        *p2 = ((s1 + s2) + s3) * ee;
    }
}

ASM_FUNC(func_00130540);

ASM_FUNC(func_00130748);

void SampleCurvePoints(f32 k, SampledCurve* self, u8* a1, u8* a2, u8* a3, s32 count, CurvePoint* out, f32 start, f32 end)
{
    f32 step = (end - start) / (f32)(count - 1);
    f32 cur = start;
    s32 i;
    for (i = 0; i < count; i++) {
        EvaluateHermiteVectorSegment(k, self, a1, a2, a3, cur, 1.0f, (s32)(out + i), 0, 0);
        cur += step;
    }
}

void MeasureCurveSegmentLength(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y)
{
    u8 buf[0x140];
    SampleCurvePoints(a, b, c, d, x, 0.0f, y, 20, buf);
    AccumulateSegmentLengths(20, buf, 0);
}

INCLUDE_RODATA(D_00249C90);

INCLUDE_ASM(func_00130C58);
