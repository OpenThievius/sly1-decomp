// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x14EE40 to 0x1533A8 (its .rodata from 0x249FE0, its .data from 0x261CC8 to 0x261F28): the
// methods of classes 0x46, 0x23, 0x65 and 0x61, the threshold tables of ScatterController and the
// display-list writer (PacketWriter, with its base vtable D_0024A0E0). Its .rodata ends with
// that vtable at 0x24A100: GCC 2.95 writes a file's vtables after all of its functions' literals
// and jump tables, so PivotActiveSet's jump table after it starts the next file
// (active_set_solver.cpp, which says why its start in the code is a choice). Its .data ends with
// the fifth DMA channel word: DrawPlacedObjectParts' matrix D_00261F30, which MultiplyMatrices
// reads with lqc2, is 16-aligned and this file's .data starts at 8 mod 16, so the matrix starts
// the next file's .data. One file between two edges otherwise; it could be several. Its name is
// ours, after its first and largest family, the pooled objects and their holder; the step
// sequence is nearly as large, and none of its families names the whole.
#include "common.h"
#include "gauge_manager.h"
#include "asm_func.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "world.h"
#include "screen_element.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "list_iter.h"
#include "texture_render_object.h"
#include "step_sequence.h"
#include "animation.h"
#include "attachment.h"
#include "camera.h"
#include "flagged_object.h"
#include "packet_writer.h"
#include "globals.h"
#include "game_progress.h"
#include "threshold_range.h"
#include "pad_record.h"
#include "active_set_solver.h"
#include "buffered_stream.h"
#include "texture_header.h"
#include "range_record.h"
#include "effect_spawner.h"
#include "effect_owner.h"
#include "effect.h"
#include "deferred_request.h"
#include "cursor_animator.h"
#include "texture_table.h"
#include "owner_message.h"
#include "switched_collider.h"
#include "vu0.h"
#include "fpu.h"
#include "object_finder.h"
struct BufferedStream;
struct StateNotifier;
struct Vec02;

struct StateNotifier;

struct PlacedObject;

struct BaseObject;
struct Mat02;
struct Vec02;

struct Mat02;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct ScaledTransform;
struct NodeQuery;


s32 FindPathCurveSegment(s32 n, f32* arr, void* p2, f32* lo, f32* hi);


s32 ReadBufferedU8(BufferedStream* self);
f32 ReadBufferedFloat(BufferedStream* r);
void ReadBufferedVector3(BufferedStream* src, void* dst);
u8* AllocateFrontMemory(s32 size);

s32 FindPathCurveSegmentByTime(void* self, f32* a, f32* b);

void WalkToNearestPathCurveSegment(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

f32 MeasureCurveSegmentLength(const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, f32 dur, f32 end);

void RegisterCollider(Collider* self);
s32 IsInList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);
s32 IsObjectOfKind(BaseObject* list, s32 key);
extern ObjectLink g_pooledObjectLinks[1];
void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);


extern GaugeManager* D_0027C00C;

void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void ApplyGaugeRatioToEffect(GaugeManager* self);

extern f32 g_gameClock[];

void UpdatePlacedObject(PlacedObject* self, f32 f);
void RunGaugeTimedEvent(void* self);
void ActivateRandomGaugeSlot(void* self);



void* AreMenusAndFadeClear(void* zero);

extern f32 g_gameTime[];

f32 RandomFloatInRange(f32 a, f32 b);


void PostLoadPlacedObject(PlacedObject* self);
s32 IsObjectOfKind(BaseObject* list, s32 key);

s32 TestCollidersMayContact(Collider* a, Collider* b);

// Slot 2 of the held record's table, as func_0014FC38 calls it.
typedef void (*Held23Slot2Fn)(void* self, s32 arg);

void TeleportStateWalker(StateWalker* self, s32 key);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void DestroyStateWalker(StateWalker* self);
void HandleMaskedColliderActivation(MaskedCollider* self);

void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(StateWalker* self, s32 key);

void InterpolatePathCurvePoint(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void InterpolatePathCurvePoint(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

struct ClipPoint;
struct PackedColor;
void TransformByMatrixWithW(const Quad16* m, const Vec02* v, f32 w, Vec02* out);
void DrawProjectedLine(ClipPoint* a, ClipPoint* b, PackedColor* c, u8* obj, s32 k);

struct CurvePoint;
void SampleCurvePoints(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, s32 count,
                       CurvePoint* out, f32 start, f32 end);
f32 AccumulateSegmentLengths(s32 n, void* buf, void* other);


void InitCollider(Collider* self);

void TransformByMatrixWithW(const Quad16* m, const Vec02* v, f32 w, Vec02* out);

void FindNearestPathCurveSegment(void* a0, void* a1, s32 count, void* a3, void* a4, void* a5, s32* outIdx, f32* outT);

void InitPlayerFlaggedCollider(PlayerFlaggedCollider* self);

s32 FindPathCurveSegment(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

s32 FindPathCurveSegment(s32 n, f32* arr, void* p2, f32* lo, f32* hi);
void WalkToNearestPathCurveSegment(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);


s32 ReadBufferedU8(BufferedStream* self);
f32 ReadBufferedFloat(BufferedStream* r);
void ReadBufferedVector3(BufferedStream* src, void* dst);
u8* AllocateFrontMemory(s32 size);
void ResetSplineSegmentCache(void* self);
void RemoveObjectFromParentList(BaseObject* self);
void AppendToList(List01* self, void* item);


void CopyCollider(Collider* self, Collider* other);

void LoadCollider(Collider* self, BufferedStream* stream);
void FindOrBuildMemberGroup(void** out, void* self);

void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);

void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void DestroyStateWalker(StateWalker* self);

s32 FindPathCurveSegment(f32 x, s32 n, f32* arr, void* p2, f32* lo, f32* hi);


extern ObjectLink g_takerLinks[3];

void StartMaskedCollider(MaskedCollider* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void* CreateObjectCopy(BaseObject* self, World* world, BaseObject* parent);
void SyncPooledHolderWithPlayer(PooledHolder* self);
struct StateGraph;
void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);



extern ObjectLink g_gaugeManagerLinks[3];

void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void AddStateWalkerListener(StateWalker* self, PlacedObject** p);
void ComputeGaugeOutputs(GaugeManager* self);

extern f32 g_gameTime[];



f32 RandomFloatInRange(f32 a, f32 b);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void ChangeAgentState(Agent* self, s32 state, void* context);
void StopTimer(void* obj);
void ComputeGaugeOutputs(GaugeManager* self);



extern f32 g_gameTime[];

void FadeOutPlacedObject(Collider* self, f32 time);

void RaiseScatterLevels(ScatterController* self, f32 amount);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table g_pathCurveKind0Methods[];
extern const Fn_Table g_pathCurveKind1Methods[];

void* AllocateZeroedFrontMemory(u32 n);

// NEAR: the calls and branches match; the store of 1 into the inner object comes before the
// float load of D_0026185C in retail, ours schedules the float load first (5 instructions).

s32 AcquirePooledObject(PooledHolder* self);
PooledObject* FindFirstAttachedPooledObject(PooledHolder* self);
s32 IsObjectAttached(BaseObject* self);
void AssignAimTarget(T2195_790* self, void* obj, Vec02* src);

// NEAR: the tail stores differ in order and register: retail does sw f6C8, then lui v1 / li v0,1 / lwc1 v1, we do lui v0 before the sw and use v0 for the address.


u32 IsListEmpty(List01* p);
void SelectEarliestPooledObject(PooledHolder* self);
void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4);

// NEAR: the search index is kept in a0 where retail uses a2, and hi is saved in s3 before the call in retail; the loop shape is otherwise the same.



void UpdateCollider(Collider* self, f32 dt);
void UpdateHeldPooledObject(PooledObject* self, f32 f);

void UpdateMaskedCollider(MaskedCollider* self, f32 dt);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void UpdatePooledHolderAim(PooledHolder* self, s32* state);
void ThrowHeldPooledObject(PooledHolder* self);
void SetPooledHolderWalkerState(PooledHolder* self, s32 state);

extern const f32 D_00249FB8;

s32 RandomIntInRange(s32 a, s32 b);
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
void GetObjectWorldRotation(BaseObject* self, Mat02* out);
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void AddAnimationPlayerRecordCallback(AnimationPlayer* a0, PlacedObject** a1);
f32 RandomFloatInRange(f32 a, f32 b);


void func_0014DB70(void);


f32 MeasureSplinePathDistance(void);

extern const GaugeParams g_defaultGaugeParams;
extern const f32 D_00249FB0;

void InitPlacedObject(PlacedObject* self);


// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
// Defined in src/main/path_curve.cpp.
extern const Fn_Table g_pathCurveKind0Methods[14];
extern const Fn_Table g_pathCurveKind1Methods[14];


void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void SetWorldActiveFollower(World* self, void* v);
void StartTimer(T217D_510* self, f32 v);
void StartTimerCounting(T217D_510* self);
void FinishGaugeOnTimeout(T217D_510* timer, s32 mode);




extern f32 g_gameClock[];
extern const GaugeParams g_defaultGaugeParams;


PooledObject* FindEarliestPooledChild(PlacedObject* self);

extern s32 IsObjectAttached(BaseObject* self);

s32 IsObjectOfKind(BaseObject* list, s32 key);


void LoadPlacedObject(PlacedObject* self, void* r);
void ReadSequenceSteps(void* unused, BufferedStream* rd, s32* outCount, SequenceStep** outArr);

void StartPlacedObject(PlacedObject* self);
void* GetIndexedTargetSlot(void* self, s32 index);

extern void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);

extern u8 g_elementStack[];
void PushStackElement(ElementStack* self, ScreenElement* node);


// The caption box as func_00150790 clears its child (T217D_440::child, +0x324): an unaligned
// store (swl/swr), so a packed view.
struct __attribute__((packed)) CaptionBoxPacked { u8 pad0[0x324]; void* child; };

void SetStepSequenceState(StepSequence* self, s32 arg);

extern void* GetLevelEntryByKey(s32 key);
extern void* GetIndexedTargetSlot(void* self, s32 index);

extern "C" void* FillMemory(void* p, s32 value, s32 size);

f32 ClampToRange(ValueRange* span, f32 x);
void SetScatterLevel(ScatterController* object, f32 unused);
f32 ClampToRange(ValueRange* span, f32 x);

extern f32 ClampToRange(ValueRange* span, f32 x);

// An item's link in a list (List01::offset bytes into it): the next and the previous item.
struct ListLink { void* next; void* prev; };

void PrependToList(List01*, u32);

extern "C" s32 ResetDmaController(s32 mode);
extern void ResetGsPaths();
struct DmaChannel;
extern "C" u32 GetDmaChannel(u32 index);
extern u32 g_vif0Channel, g_vif1Channel, g_gifChannel, g_fromSprChannel, g_toSprChannel;

u8* ReservePermanentMemory(s32 size);

extern u8* AllocateBackMemory(s32 size);

void CloseDmaTag(PacketWriter* self);

void CloseDmaTag(PacketWriter* self);
u32 CopyToFrontMemory(s32 size, void* src);

extern "C" void SyncDataCache(s32 unused);
struct DmaChannel;
extern "C" void StartDmaChain(DmaChannel* ch, void* tadr);

void CopyQuadwords(void* dst, void* src, s32 n);

void CloseDmaTag(PacketWriter* self);

struct SequenceMessage;
void HandleStepSequenceMessage(StepSequence* self, SequenceMessage* msg);
s32 TestStepWaitConditions(StepSequence* self);
void StopAnimationPlayer(AnimationPlayer* self);
void SkipRemainingSteps(StepSequence* self);


void DrawPlacedObjectParts(DeferredRequest* self);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);
void QueueDeferredRequest(DeferredRequest* src);


void* GetListLinks(void* a, void* b);

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void SetListLinkOffset(List01* self, s32 offset);


extern s32 D_00275F84;
s32 IsStreamVoiceLocked(void);
void SetStepSequenceState(StepSequence* self, s32 mode);

u32 GetListLinks(List01* node, u32 value);
void ClearList(List01* node);


extern s32 D_00275B00;
void SetSpareCount(s32 value);
f32 ClampToRange(ValueRange* span, f32 x);
void SetScatterLevel(void*, f32);
void CompleteSoundNotifiers(World* self);

// An entry of a GCC 2.95 vtable as this file defines D_0024A0E0 (packet_writer.h).
struct VtableEntry { s32 delta; void (*fn)(); };
void SkipDisplayListWriterSlot();
void ClearPacketBuffer(PacketWriter* p);


extern s32 D_00261D38;
extern f32 g_gameTime[];

void StopStreamVoice(void);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
void RemoveCameraControllers(Camera* self, s32 flags, s32 k0, CameraController* k1, void* k2, void* k3);
void ReleasePadSelectFlag(World* self);
void AcquirePadSelectFlag(World* a0);
s32 PopStackValue(TargetCameraController* s);
void PushStackValue(TargetCameraController* s, s32 value);
void PushCameraController(Camera* self, s32 key, CameraController* ctl, void* target, void* arg);
void StopAnimationPlayer(AnimationPlayer* self);
void SetVolumeChannelFactor(s32 a, s32 b, f32 f);
void SetTextPanelState(T217D_440* a, s32 b);
void SetTextPanelSubject(T217D_440* a, BaseObject* b);
void SetArcTarget(T217D_3F0* self, void* value);
void SetArcSpecialObject(T217D_3F0* self, void* a1);

void BuildContactItemRows(ActiveSetSolver* self, s32 a1, ActiveSetItem* n, s32 a3, s32 a4, s32 a5, s32 a6);
void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);
extern f32 D_BC23D70A;


void ClearList(List01* p);
void AppendToList(List01* self, void* item);


s32 ReadBufferedS8(BufferedStream* r);
void* AllocateZeroedFrontMemory(s32 n);
void ReadOptionalBufferedBlock(BufferedStream* self, u32* out);
s32 ReadBufferedS16(BufferedStream* r);
f32 ReadBufferedFloat(BufferedStream* r);
s32 ReadBufferedU8(BufferedStream* r);
void ReadBufferedString(BufferedStream* self, u8** out);

extern u8 g_elementStack[];
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
void ShowCountedScreenElement(World* self);
void HideCountedScreenElement(World* self);
void PopStackElement(ElementStack* g);

extern s32 D_00275F84;
extern s32 D_00270B30;
extern s32 D_002717A8;
extern u8 g_elementStack[];

void UpdatePlacedObject(PlacedObject* self, f32 f);
s32 IsStreamVoiceLocked(void);
void SetStepSequenceState(StepSequence* self, s32 mode);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
Ent65* GetActiveSwitchedCollider(void);
s32 IsTopCameraController(CameraController* p);
void ChooseStepSequenceState(StepSequence* self);
void ShowStepSequenceText(StepSequence* value, Ent65* object);
void SkipRemainingSteps(StepSequence* self);
void PopStackElement(ElementStack* g);
void RunStepSequence(StepSequence* self);


extern s32 g_padRouting;
extern u16 D_00261D08[16];
extern u8 D_00261D28[16];

s32 CheckStreamVoicePending(void);
s32 HasStreamVoice(void);
s32 IsTextPanelTextTyped(T217D_440* p);



void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);
void FactorSymmetricMatrix(s32 n, f32* mat, f32* vec);
void SolveFactoredSystem(s32 n, f32* a, f32* b, f32* c);

// The object a caption is spoken by (kind 0x104, found by id by func_00150DC0): its colour
// becomes the caption box's highlight, its state walker (+0x334) is sent key 0x34C.
struct StateWalker;
struct CaptionSpeaker { u8 pad0[0x2D0]; Rgba4 color; u8 pad1[0x334 - 0x2D4]; StateWalker* walker; };
// A word of a step sequence's message, read as an id or a time.
struct KeyRecord;
union MessageWord { s32 i; f32 f; KeyRecord* key; void* p; };

// The message HandleStepSequenceMessage takes.
struct SequenceMessage {
    u32 type;
    MessageWord f4, f8;
    s32 fC, f10;
    s8* text;
    s32 f18, f1C, f20, f24;
};

extern u8 g_moviePlayer[];

void OpenKeyRecord(KeyRecord* self);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void SetArcTarget(T217D_3F0* self, void* value);
void SetArcSpecialObject(T217D_3F0* self, void* a1);
s32 MatchesObjectId(BaseObject* self, s32 id);
void SetArcFade(T217D_3F0* a, s32 b);
void AddAnimationPlayerRecordCallback(AnimationPlayer* a0, PlacedObject** a1);
extern "C" u32 GetStringLength(const char* s);
void SetTextPanelValuePercent(T217D_440* a, f32 b);
void SetTextPanelSubject(T217D_440* a, BaseObject* b);
struct MoviePlayer;
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
void ShowCountedScreenElement(World* self);
void HideCountedScreenElement(World* self);
void QueueMovie(MoviePlayer* self, void* p);


s32 RandomIntInRange(s32 lo, s32 hi);
f32 ClampToRange(ValueRange* span, f32 x);
s32 ScatterObjectsAroundCircle(World* self, s32 a1, Vec02* a2, s32 n, StateNotifier** arr);

// Draws a count between two bounds by the level (g_currentEntry->dt), rounding toward the second.
struct LevelLerp
{
    static s32 Get(s32 lo, s32 hi)
    {
        f32 s = g_currentEntry->dt;
        if (lo == hi) return hi;
        if (lo < hi) return lo + (s32)(s * ((f32)hi + 0.999f - (f32)lo));
        return hi + (s32)((1.0f - s) * ((f32)lo + 0.999f - (f32)hi));
    }
};


void* InitGifPacket(PacketWriter* p);
void* InitPacketWriter(PacketWriter* p);
void PushBackMemoryMark(void);
void AllocateTempPacketBuffer(PacketWriter* buffer, u32 count);
void WriteVifFlushE(PacketWriter* p);
void SetupTextureRenderTarget(TextureHeader* src, void* dst);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRgbaEntry(PacketWriter* self, u32 value);
void AddGifXyzEntry(PacketWriter* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void EndGifPacket(PacketWriter* p);
void WriteVifDirectFromWriter(PacketWriter* p, PacketWriter* q);
void WriteVifBaseOffset(PacketWriter* s, u32 a, u32 b);
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4);
void ClearPacketBuffer(PacketWriter* p);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void ReserveGifPackedData(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, u8** out);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);
void PopBackMemoryMark(void);
void AddGifUvEntry(PacketWriter* p, s32 a, s32 b);
void WriteVifFlush(PacketWriter* p);





extern ScatterTable D_00261D70[2];
extern ScatterTable D_00261E30;
extern ScatterTable D_00261E90;
s32 RandomIntInRange(s32 a, s32 b);

void InitPlacedObject(PlacedObject* self);



void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void CopyMemory(void* dst, void* src, s32 size);
void InitActiveSetSolver(ActiveSetSolver* loc, s32 count);
void AppendToList(List01* self, void* item);
void RunActiveSetSolver(ActiveSetSolver* self, s32 a1, s32 a3, s32 a4, s32 a5, s32 a6);
void InitPooledObject(PooledObject* self)
{
    InitCollider(self);
    SetPooledObjectState(self, -1);
}

void RemoveFromWorldQueue(PooledObject* self)
{
    RegisterCollider(self);
    if (IsInList(&self->world->list1C78, self)) RemoveFromList(&self->world->list1C78, self);
    if (self->parent != 0 && IsObjectOfKind(self->parent, 0x3A) != 0) {
        self->flags538 |= (u64)0x8000 << 28;
    } else {
        self->flags538 &= ~((u64)1 << 43);
    }
}

void AddToWorldQueue(PooledObject* self)
{
    RemoveObjectFromParentList(self);
    AppendToList(&self->world->list1C78, self);
    SetPooledObjectState(self, 0);
}

void CopyPooledObject(PooledObject* self, Collider* other)
{
    Keep46 save = self->keep56C;
    CopyCollider(self, other);
    self->keep56C = save;
}

void LoadPooledObject(PooledObject* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    FindOrBuildMemberGroup(&self->member58C, self);
}

void HandlePooledObjectNotification(PooledObject* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 6) {
        if (msg == self->watched) {
            self->watched = 0;
            SetPooledObjectState(self, 4);
        }
    }
}

void StartPooledObject(PooledObject* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, g_pooledObjectLinks);
}

void UpdatePooledObject(PooledObject* self, f32 f)
{
    UpdateCollider(self, f);
    switch (self->state) {
    case 0:
    case 1:
    case 3:
    case 5:
        break;
    case 2:
        UpdateHeldPooledObject(self, f);
        break;
    case 4:
        if (self->delay < g_gameTime[0] - self->stateTime) {
            if (g_player == 0 || self->parent != (BaseObject*)g_player->heldObject)
                SetPooledObjectState(self, 5);
        }
        break;
    }
}

void SetPooledObjectState(PooledObject* self, s32 state)
{
    if (self->state != state) {
        if (self->state != 2) {
            self->state = state;
        } else {
            self->f57C = 0;
            self->f580 = 0;
            self->f584 = 0;
            self->taker = 0;
            self->state = state;
        }
        self->stateTime = g_gameTime[0];
        if (state == 5) {
            (void)FadeOutPlacedObject(self, self->fadeOutTime);
        }
    }
}

extern f32 D_00261CD4;
extern f32 D_00261CD8;
void SetPlayerState(Player* self, s32 state, s32 sub);

// The owner-message callback of a pooled object's launch: gives the other object, through its
// slot 36, the pooled object's horizontal direction (its velocity with z cleared, unit length,
// or X when it has none) times D_00261CD4 plus D_00261CD8 upward; a kind-7 object is put in
// state 0x2B.
// As ApplyChildGroupKnockback: the unit vector is stored through a pointer as a structure and
// the weights are read as the floats themselves, so the first weight's load does not wait for
// that store in sched2 (docs/toolchain/sched1.md, "Why the arms' stores cannot be written
// plainly").
void LaunchObjectFromPooledObject(PlacedObject* self, PlacedObject* other)
{
    Vec02 d = self->v150;
    d.z = 0.0f;
    Vec02* p = &d;
    Vec02 r;
    *(Vu0::Vec*)p = Vu0::NormalizeOr(Vu0::Vec::Of(d), Vu0::Vec::Of(g_unitXVector));
    const Desc02* desc = other->desc02();
    Vu0::Q(r) = Vu0::MulXSum(Vu0::Q(d), Vu0::ScalarAtValue(D_00261CD4), Vu0::Q(g_unitZVector), Vu0::ScalarAtValue(D_00261CD8));
    desc->m20(other, &r);
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState((Player*)other, 4, 0x2B);
    }
}

void* FindContactingPart(Collider* self);
void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner);
void StartPadRecordPattern(PadRecord* self, s32 pattern, f32 duration);
s32 CountHeldPooledChildren(PlacedObject* self);
PlacedObject *FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list);
void SendPointEventToWorldListener(Quad16* a0, f32 f);
void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);
void BuildBasisFromX(Vec02* x, Mat02* out);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// The query FindNodeForQuery takes for an object that touched a held one (func_0014F270).
struct HeldTouchQuery {
    PooledObject* self;     // 0x00
    Collider* other;        // 0x04
    u8 pad08[0x20 - 0x08];
    Vec02 pos;              // 0x20
    Vec02 vel;              // 0x30

    void Clear() { FillMemory(this, 0, (s32)sizeof(*this)); }
};

// What a group member's slot 0x7C is told when a held object lands (func_0014F270).
struct HeldLandEvent {
    s32 kind;               // 0x00: 4
    u8 pad04[0x20 - 0x04];
    Vec02 pos;              // 0x20
};

typedef void (*ObjFn)(void* self);
typedef void (*ObjPtrFn)(void* self, void* a);

void UpdateHeldPooledObject(PooledObject* self, f32 dt)
{
    typedef Vu0::Vec Vec;
    Collider* c = (Collider*)FindContactingPart(self);
    if (c != 0) {
        s32 lands = 1;
        if (c == (Collider*)g_player && (g_player->state != 6 || g_player->targetMode != 2)) {
            OwnerMessage m;
            InitOwnerMessage(&m, 0, self);
            m.fn = (void (*)())LaunchObjectFromPooledObject;
            ((s32 (*)(void*, void*))((void**)g_player->desc)[0x140 / 4])(g_player, &m);
        } else if (IsObjectOfKind(c, 0x3A)) {
            StartSoundEffect(0x34, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            if (g_player != 0 && g_player->heldObject == c) {
                StartPadRecordPattern(&g_padRecord, 4, 0.25f);
            }
            if (!(CountHeldPooledChildren(c) < *(s32*)((u8*)c + 0x564))) {
                PooledObject* e = FindEarliestPooledChild((PooledObject*)c);
                if (e != 0) {
                    SetPooledObjectState(e, 5);
                }
            }
            ((ObjPtrFn)((void**)self->desc)[0x64 / 4])(self, c);
            ((ObjPtrFn)((void**)self->desc)[0x90 / 4])(self, (void*)&D_00248D30);
            ((ObjPtrFn)((void**)self->desc)[0x94 / 4])(self, (void*)&D_00248D30);
            SetColliderAnchors(self, 3, 0, 3, 0);
            SetPooledObjectState(self, 4);
            if (self->watchedAnimation != 0) {
                CreateAnimationPlayerWithoutPresetTargets((Animation*)self->watchedAnimation, self, 0, (AnimationPlayer**)&self->watched, 0.0f, 1.0f);
                if (self->watched != 0) {
                    SetPooledObjectState(self, 3);
                }
            }
            lands = 0;
        } else if (IsObjectOfKind(c, 0x46)) {
            switch (((PooledObject*)c)->state) {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
            case 4:
            case 5:
                lands = 0;
                ((ObjPtrFn)((void**)c->desc)[0x64 / 4])(c, 0);
                ((ObjFn)((void**)c->desc)[0x1C / 4])(c);
                break;
            }
        } else {
            HeldTouchQuery q;
            q.Clear();
            q.other = c;
            q.pos = self->v140;
            q.vel = self->v150;
            q.self = self;
            FindNodeForQuery((NodeQuery*)&q, 0, 0);
        }
        if (lands) {
            StartSoundEffect(0x33, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            void* g = self->member58C;
            if (g != 0) {
                HeldLandEvent ev;
                ev.kind = 4;
                ev.pos = self->v140;
                ((ObjPtrFn)((void**)*(void**)g)[0x7C / 4])(g, &ev);
            } else {
                SendPointEventToWorldListener((Quad16*)&self->v140, self->landEventValue);
            }
            ((ObjPtrFn)((void**)self->desc)[0x64 / 4])(self, 0);
            ((ObjFn)((void**)self->desc)[0x1C / 4])(self);
        }
        return;
    }
    if (g_player != 0 && g_player->state == 4) {
        return;
    }
    Vec02 at;
    Vec02 dir;
    Mat02 basis;
    at = self->holder->v140;
    at.z = at.z + self->holdHeight;
    f32 t = Vu0::Distance(at, self->v140) / self->holdSpeed;
    f32 lo = 0.0f;
    f32 hi = 0.25f;
    if (t < lo) {
        t = lo;
    } else if (hi < t) {
        t = hi;
    }
    ComputeObjectFrameAtTime(self->holder, 0, &at, 0, 0, 0, t);
    at.z = at.z + self->holdHeight;
    u128 k = Vu0::ScalarAt(self->holdSpeed);
    Vu0::Set(dir, Vu0::MulX(Vu0::NormalizeOr(Vu0::Sub(Vec::Of(at), Vec::Of(self->v140)), Vec::Of(D_00248D30)).q, k));
    ((ObjPtrFn)((void**)self->desc)[0x90 / 4])(self, &dir);
    BuildBasisFromX(&dir, &basis);
    ((ObjPtrFn)((void**)self->desc)[0x88 / 4])(self, &basis);
}

void InitPooledHolder(PooledHolder* self)
{
    InitPlayerFlaggedCollider(self);
    self->templateId = -1;
}

void HandlePooledHolderNotification(PooledHolder* self, s32 kind, void* msg)
{
    s32 result;

    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0x14) {
        if (msg == self->walker) {
            GetStateWalkerTargetKey((StateWalker*)msg, &result);
            if (result == 0x2B7) {
                if (self->hold != 0) {
                    DestroyStateWalker((StateWalker*)self->walker);
                    self->walker = 0;
                } else {
                    ((Held23*)self->p734->aimAttachment)->f4C = 1;
                    ((Held23*)self->p734->aimAttachment)->aimAtTarget = 0;
                    self->p734->desc02()->m1D(self->p734, &self->p734->v190);
                    self->p734->desc02()->m1E(self->p734, &self->p734->m1A0);
                    self->p738->desc02()->m1E(self->p738, &self->p738->m1A0);
                }
            }
        }
    }
}

void PostLoadPooledHolder(PooledHolder* self)
{
    s32 i = 0;
    PostLoadPlacedObject(self);
    if (self->count744 > 0) {
        do {
            void* p = FindFirstObjectByIdMode4(self->world, self->items748[i], self);
            if (p != 0) {
                if (IsObjectOfKind((BaseObject*)p, 0x41) != 0) {
                    s32 n = self->count768;
                    self->items76C[n] = p;
                    self->count768 = n + 1;
                }
            }
            i++;
        } while (i < self->count744);
    }
}

void SyncPooledHolderWithPlayer(PooledHolder* self)
{
    if (g_player != 0) {
        self->throwTarget = (s32)g_player->rigObject;
    }
}

void StartPooledHolder(PooledHolder* self)
{
    StartMaskedCollider(self);
    ResolveObjectLinks(self, 3, g_takerLinks);
    ((Held23*)self->p734->aimAttachment)->f4C = 1;
    PlacedObject* s2 = (PlacedObject*)FindFirstObjectByIdMode1(self->world, self->templateId, self);
    *(Quad16*)&self->savedPose[0] = *(Quad16*)&s2->v190;
    *(Quad16*)&self->savedPose[1] = *(Quad16*)&s2->m1A0.r[0];
    *(Quad16*)&self->savedPose[2] = *(Quad16*)&s2->m1A0.r[1];
    *(Quad16*)&self->savedPose[3] = *(Quad16*)&s2->m1A0.r[2];
    self->savedParent = s2->parent;
    s32 i = 1;
    if (i < self->cnt) {
        do {
            BaseObject* e = (BaseObject*)CreateObjectCopy(s2, s2->world, 0);
            if (e->desc->m0F != 0) {
                e->desc->m0F(e);
            }
            i++;
            e->desc->m10(e);
            e->desc->m03(e);
        } while (i < self->cnt);
    }
    s2->desc->m15(s2, 0);
    s2->desc->m03(s2);
    AppendQueuedCall(self->world, (void*)(void (*)(void*))SyncPooledHolderWithPlayer, self, 0, 0);
    self->walker = CreateStateWalker((StateGraph*)self->stateGraph, self, 0x2B7, 1);
}

void UpdatePooledHolder(PooledHolder* self, f32 dt)
{
    s32 st[2];
    UpdateMaskedCollider(self, dt);
    if (self->hold == 0 && self->throwTarget != 0 && self->walker != 0) {
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &st[0]);
        GetStateWalkerTargetKey((StateWalker*)self->walker, &st[1]);
        if (st[1] == -1) st[1] = st[0];
        if (st[0] == st[1]) {
            switch (st[0]) {
            case 0x2B7:
                if (self->f7B0 != 0) st[1] = 0x2B8;
                else if (self->collectedCount > 0) st[1] = 0x2B9;
                break;
            case 0x2B8:
                if (self->f7B0 == 0) {
                    if (self->collectedCount > 0) st[1] = 0x2B9;
                    else st[1] = 0x2B7;
                } else {
                    UpdatePooledHolderAim(self, &st[1]);
                }
                break;
            case 0x2B9:
                if (self->f7B0 != 0) st[1] = 0x2B8;
                else if (self->collectedCount <= 0) st[1] = 0x2B7;
                else UpdatePooledHolderAim(self, &st[1]);
                break;
            case 0x2BA:
                ThrowHeldPooledObject(self);
                st[1] = 0x2B8;
                break;
            case 0x2BB:
                ThrowHeldPooledObject(self);
                st[1] = 0x2B9;
                break;
            }
            if (st[1] != st[0]) SetPooledHolderWalkerState(self, st[1]);
        }
    }
}

s32 TestPooledHolderMayContact(PooledHolder* self, Collider* obj)
{
    if (IsObjectOfKind(obj, 0x46) != 0) {
        if (((PooledObject*)obj)->taker == self) {
            return 1;
        }
    }
    return TestCollidersMayContact(self, obj);
}

void ReleasePooledHolder(PooledHolder* self)
{
    s32 status;

    if (self->heldObject != 0) {
        self->heldObject->desc->m15(self->heldObject, 0);
        self->heldObject->desc->m03(self->heldObject);
    }
    if (self->walker != 0) {
        TeleportStateWalker((StateWalker*)self->walker, 0x2B7);
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &status);
        if (status == 0x2B7) {
            DestroyStateWalker((StateWalker*)self->walker);
            self->walker = 0;
        }
    }
    {
        Held23* o = (Held23*)self->p734->aimAttachment;
        ((Held23Slot2Fn)o->vtbl[2])(o, 7);
    }
    HandleMaskedColliderActivation(self);
}

void SetPooledHolderWalkerState(PooledHolder* self, s32 code)
{
    s32 r;

    GetStateWalkerTargetKey((StateWalker*)self->walker, &r);
    if (r == -1) {
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &r);
    }
    if (code == r) {
        return;
    }
    if (r == 0x2B7) {
        ((Held23*)self->p734->aimAttachment)->f4C = 0;
    }
    if (code < 0x2BA) {
        if (code >= 0x2B8) {
            ((Held23*)self->p734->aimAttachment)->aimAtTarget = (code == 0x2B9);
            if (!((u32)(r - 0x2BA) < 2)) {
                self->acquireTime = 0;
            }
        }
    }
    SetStateWalkerTarget((StateWalker*)self->walker, code);
}

void UpdatePooledHolderAim(PooledHolder* self, s32* state)
{
    if (*state == 0x2B8) {
        ((Held23*)self->p734->aimAttachment)->aimAtTarget = 0;
        if (self->acquireDelay < g_gameTime[0] - self->acquireTime) {
            if (AcquirePooledObject(self)) {
                *state = 0x2BA;
            }
        }
        return;
    }
    if (self->targetObject == 0 || IsObjectAttached(self->targetObject) == 0
        || self->targetObject->state == 3 || self->targetObject->state == 4) {
        self->targetObject = FindFirstAttachedPooledObject(self);
    }
    if (self->targetObject == 0) {
        return;
    }
    AssignAimTarget((T2195_790*)self->p734->aimAttachment, self->targetObject, (Vec02*)&D_00248D30);
    if (self->acquireDelay < g_gameTime[0] - self->acquireTime) {
        if (AcquirePooledObject(self)) {
            *state = 0x2BB;
        }
    }
}

s32 AcquirePooledObject(PooledHolder* self) {
    PooledObject* s0;

    if (self->heldObject != 0) {
        return 1;
    }
    if (self->reservedObject != 0) {
        if (self->reservedObject->state != 5) {
            self->reservedObject = 0;
        }
    }
    if (IsListEmpty(&self->world->list1C78) != 0 || self->reservedObject != 0) {
        SelectEarliestPooledObject(self);
        return 0;
    }
    s0 = (PooledObject*)self->world->list1C78.head;
    s0->taker = self;
    s0->desc->m02(s0);
    s0->desc->m15(s0, self->savedParent);
    SetColliderAnchors(s0, 3, 0, 3, 0);
    s0->desc03()->m1D(s0, &self->savedPose[0]);
    s0->desc03()->m1E(s0, (Mat02*)&self->savedPose[1]);
    s0->desc03()->m20(s0, (Vec02*)&D_00248D30);
    s0->desc03()->m21(s0, (Vec02*)&D_00248D30);
    SetPooledObjectState(s0, 1);
    self->heldObject = s0;
    self->acquireTime = g_gameTime[0];
    return 1;
}

#define OBJV ((PooledView*)obj)
struct PooledView { u8 pad00[0x558]; f32 throwSpeed; f32 throwEventRadius; u8 pad560[0x580 - 0x560]; f32 flightTime; f32 throwHeight; };
void SetPooledObjectState(PooledObject* self, s32 state);
void BuildBasisFromX(Vec02* x, Mat02* out);
void SendPointEventToWorldListener(Quad16* a0, f32 f);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

void ThrowHeldPooledObject(PooledHolder* self)
{
    Vec02 pos;
    Vec02 d;
    Vec02 dir;
    Vec02 step;
    Vec02 vel;
    Mat02 basis;
    PooledObject* obj;
    void* args[1];
    PlacedObject* source;
    f32 speed;
    if (self->targetObject != 0 && ((Held23*)self->p734->aimAttachment)->aimAtTarget != 0) {
        if (IsObjectAttached(self->targetObject) == 0 || self->targetObject->state == 3 || self->targetObject->state == 4) {
            self->targetObject = 0;
            return;
        }
        speed = 15.0f;
        source = self->targetObject;
    } else {
        source = (PlacedObject*)self->throwTarget;
        speed = *(f32*)((u8*)self + 0x6D4);
    }
    obj = (PooledObject*)self->heldObject;
    self->targetObject = 0;
    self->heldObject = 0;
    obj->desc->m15(obj, 0);
    SetColliderAnchors(obj, 0, 0, 0, 0);
    if (obj->baseAttachment != 0) {
        typedef void (*AttachedFn)(void* self, s32 arg);
        void* att = obj->baseAttachment;
        (*(AttachedFn**)att)[2](att, 7);
    }
    pos = source->v140;
    pos.z += speed;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(obj->v140));
    BuildBasisFromX(&d, &basis);
    obj->desc02()->m1E(obj, &basis);
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(d)));
    OBJV->flightTime = len / OBJV->throwSpeed;
    TransformDirectionBetweenFrames(source->root, 0, &source->root->v150, &dir);
    Vu0::Q(step) = Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(OBJV->flightTime));
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(step));
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(obj->v140));
    f32 len2 = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(d)));
    OBJV->flightTime = len2 / OBJV->throwSpeed;
    Vu0::Q(d) = Vu0::DivX(Vu0::Q(d), Vu0::Length(Vu0::Q(d)));
    Vu0::Q(vel) = Vu0::MulX(Vu0::Q(d), Vu0::ScalarAt(OBJV->throwSpeed));
    obj->desc02()->m20(obj, &vel);
    SetPooledObjectState(obj, 2);
    obj->f57C = (s32)source;
    OBJV->throwHeight = speed;
    SendPointEventToWorldListener((Quad16*)&obj->v140, OBJV->throwEventRadius);
    args[0] = &obj;
    TriggerScriptEvent(self, 0xD, 1, args);
}

void SelectEarliestPooledObject(PooledHolder* self)
{
	ListFrame frame;
	if (self->reservedObject != 0) return;
	PooledObject* current = (PooledObject*)g_partList.head;
	PooledObject* best = 0;
	f32 minimum = 3.4028235e+38f;
	while (current != 0) {
		PooledObject* candidate = FindEarliestPooledChild(current);
		current = current->next;

		if (candidate != 0 && candidate->stateTime < minimum) { best = candidate; minimum = candidate->stateTime; }
	}
	if (best != 0) { SetPooledObjectState(best, 5); self->reservedObject = best; }
}

PooledObject* FindFirstAttachedPooledObject(PooledHolder* state)
{
	for (s32 i = 0; i < state->collectedCount; ++i) {
		PooledObject* item = (PooledObject*)state->collected[i];
		if (IsObjectAttached(item) == 0) continue;
		if (item->state == 3) continue;
		if (item->state == 4) continue;
		return item;
	}
	return 0;
}

void AddPooledHolderItem(PooledHolder* self, s32 item)
{
    u32 n = (u32)self->count744;
    if (n < 8) {
        self->items748[n] = item;
        self->count744 = n + 1;
    }
}

void ResetCollectedItems(PooledHolder* self)
{
    self->collectedCount = 0;
    self->f7B0 = 0;
}

void RecordCollectedItem(PooledHolder* self, void* event)
{
    if (IsObjectOfKind((BaseObject*)event, 7)) {
        self->f7B0 = 1;
        return;
    }
    if (!IsObjectOfKind((BaseObject*)event, 0x41)) {
        return;
    }
    s32 found = 0;
    for (s32 i = 0; i < self->count768; i++) {
        if (self->items76C[i] == event) {
            found = 1;
            break;
        }
    }
    if (found) {
        u32 count = self->collectedCount;
        if (count < 8) {
            self->collected[count] = event;
            self->collectedCount = count + 1;
        }
    }
}

void InitStepSequence(StepSequence* state)
{
	InitPlacedObject(state);
	state->flags |= ((u64)0x8000u << 17);
	state->second300 = -1;
	state->first30C = -1;
}

void LoadStepSequence(StepSequence* self, BufferedStream* arg)
{
    LoadPlacedObject(self, arg);
    ReadSequenceSteps(self, arg, &self->count2DC, (SequenceStep**)&self->steps2E0);
}

void ReadSequenceSteps(void* unused, BufferedStream* rd, s32* outCount, SequenceStep** outArr)
{
    s32 i = 0;
    *outCount = ReadBufferedS8(rd);
    *outArr = (SequenceStep*)AllocateZeroedFrontMemory(*outCount * 0x28);
    for (i = 0; i < *outCount; i++) {
        SequenceStep* e = (SequenceStep*)((u8*)*outArr + i * 0x28);
        e->type = ReadBufferedS8(rd);
        switch (e->type) {
        case 0:
        case 7:
            ReadOptionalBufferedBlock(rd, (u32*)&e->w4);
            break;
        case 1:
        case 2:
            e->w4 = ReadBufferedS16(rd);
            e->w8 = ReadBufferedS16(rd);
            break;
        case 3:
            *(f32*)&e->w4 = ReadBufferedFloat(rd);
            *(f32*)&e->w8 = ReadBufferedFloat(rd);
            e->wC = ReadBufferedU8(rd);
            e->w10 = ReadBufferedU8(rd);
            e->w18 = ReadBufferedS16(rd);
            e->w1C = ReadBufferedS16(rd);
            e->w20 = ReadBufferedS16(rd);
            e->w24 = ReadBufferedS16(rd);
            ReadBufferedString(rd, (u8**)e->w14);
            break;
        case 4:
            e->w4 = ReadBufferedS16(rd);
            break;
        }
    }
}

void StartStepSequence(StepSequence* self)
{
    StartPlacedObject(self);
    if (self->first30C == -1) {
        self->first30C = self->id;
    }
    void* v = GetIndexedTargetSlot(g_currentEntry, self->first30C);
    self->target304 = v;
    if (!v) {
        self->target304 = self->fallback308;
    }
}

void SetStepSequenceModeOne(StepSequence* self)
{
    self->mode2D0 = 1;
}

void SetStepSequenceCameraMode(StepSequence* self)
{
    self->mode2D0 = 2;
}

void ReadSequenceTarget(StepSequence* self, s32* out)
{
    *out = *(s32*)self->target304;
}

void WriteSequenceTarget(StepSequence* self, s32 value)
{
    *(s32*)self->target304 = value;
}

void SetStepSequenceState(StepSequence* self, s32 next)
{
    s32 cur = self->state2D4;
    if (next == cur) {
        return;
    }
    switch (cur) {
    case 5:
        if (D_0026F5A0.owner == self) {
            D_0026F5A0.owner = 0;
        }
        break;
    case 1:
        if (self->mode2D0 != cur) {
            D_00261D38 = D_00261D38 - 1;
        }
        break;
    case 3:
        *(s32*)self->target304 = 1;
        StopStreamVoice();
        TriggerScriptEvent(self, 0x15, 0, 0);
        if (self->mode2D0 == 2) {
            RemoveCameraControllers(g_camera, 0xF, 6, &g_camera->ctl460, 0, 0);
            ReleasePadSelectFlag(g_currentWorld);
        }
        (void)PopStackValue(&g_camera->ctl460);
        if ((self->waitFlags & 0x10) != 0 && self->player2F8 != 0) {
            StopAnimationPlayer(self->player2F8);
        }
        if (self->mode2D0 == 2 && self->f330 != 0) {
            f32 f = 1.0f;
            SetVolumeChannelFactor(9, 0, f);
            SetVolumeChannelFactor(9, 1, f);
        }
        break;
    case 4:
        ((CaptionBoxPacked*)&g_typedTextCaptionBox)->child = 0;
        SetTextPanelState(&g_typedTextCaptionBox, 0);
        break;
    }
    switch (next) {
    case 5:
        if (D_0026F5A0.owner != 0) {
            SetStepSequenceState(D_0026F5A0.owner, 0);
        }
        D_0026F5A0.owner = self;
        self->state2D4 = next;
        break;
    case 1:
        if (self->mode2D0 != next) {
            D_00261D38 = D_00261D38 + 1;
        }
        self->state2D4 = next;
        break;
    case 3:
        self->step2E4 = -1;
        self->waitFlags = 0;
        if (self->mode2D0 == 2) {
            PushStackValue(&g_camera->ctl460, 4);
            PushCameraController(g_camera, 6, &g_camera->ctl460, 0, 0);
            AcquirePadSelectFlag(g_currentWorld);
            SetTextPanelSubject(&g_typedTextCaptionBox, 0);
            if (self->f330 != 0) {
                f32 f = 0.6f;
                SetVolumeChannelFactor(9, 0, f);
                SetVolumeChannelFactor(9, 1, f);
            }
        } else {
            PushStackValue(&g_camera->ctl460, 3);
            if (self->mode2D0 == 0) {
                if (self->second300 != -1) {
                    g_camera->ctl460.anchorObject = FindFirstObjectByIdMode4(self->world, self->second300, 0);
                } else {
                    g_camera->ctl460.anchorObject = 0;
                }
            }
        }
        self->state2D4 = next;
        break;
    case 4:
        SetArcTarget(&D_002708E0, 0);
        SetArcSpecialObject(&D_002708E0, 0);
        SetArcTarget(&D_00271558, 0);
        SetArcSpecialObject(&D_00271558, 0);
        self->state2D4 = next;
        break;
    default:
        self->state2D4 = next;
        break;
    }
    self->time2D8 = g_gameTime[0];
}

void UpdateStepSequence(StepSequence* self, f32 dt)
{
    s32 q[2];
    s32 s1;
    Ent65* s2;

    UpdatePlacedObject(self, dt);
    if (!(g_timerCaption.state < 2 && g_timerCaption.pressed == 0 && IsStreamVoiceLocked() == 0 && D_00275F84 != 1)) {
        s32 st = self->state2D4;
        switch (st) {
        case 1:
        case 5:
        case 6:
            SetStepSequenceState(self, 0);
            return;
        }
    }
    FillMemory(q, 0, 8);
    s2 = GetActiveSwitchedCollider();
    if (IsTopCameraController(&g_camera->ctl454) != 0) {
        q[1] = 0;
        q[0] = 0;
    } else if (s2 != 0) {
        s2->vt->f154(s2, self, q);
    } else {
        q[1] = 1;
    }
    s1 = self->state2D4;
    switch (s1) {
    case 0:
        if (self->startPending != 0) {
            if (D_00275F84 == 0 && q[1] != 0) {
                self->startPending = 0;
                ChooseStepSequenceState(self);
                s1 = self->state2D4;
            }
        }
        break;
    case 5:
        if (q[0] == 0) {
            s1 = 6;
            break;
        }
        goto timer;
    case 6:
        if (q[0] != 0) {
            s1 = 5;
            break;
        }
        goto timer;
    case 1:
        if (q[1] != 0) {
            StepSequence* o = D_0027051C;
            if (o == 0) {
                ShowStepSequenceText(self, s2);
                s1 = self->state2D4;
            } else if (o != self) {
                if (o->f328 == 0 && o->state2D4 == 3) {
                    SkipRemainingSteps(o);
                }
            }
            break;
        }
    timer:
        if (g_gameTime[0] - self->time2D8 >= 5.0f) s1 = 0;
        break;
    case 3:
        if (self->mode2D0 != 2) {
            if (!(self->step2E4 < self->count2DC) || D_00275F84 == 1) {
                PopStackElement((ElementStack*)g_elementStack);
                s1 = self->state2D4;
            }
        }
        break;
    case 4:
        if (D_00270B30 == 0) {
            if (D_002717A8 == 0) s1 = 0;
        }
        break;
    }
    SetStepSequenceState(self, s1);
    switch (self->state2D4) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        break;
    case 3:
        RunStepSequence(self);
        break;
    }
}

void HandleStepSequenceMessage(StepSequence* self, SequenceMessage* msg)
{
    CaptionSpeaker* s2;
    CaptionSpeaker* s4;
    s32 a2;
    BaseObject* a0;
    f32 f20;
    s8* nm;
    switch (msg->type) {
    case 0:
        OpenKeyRecord(msg->f4.key);
        self->waitFlags |= 1;
        break;
    case 1:
    case 2:
        if (msg->f4.i != -1) {
            s2 = (CaptionSpeaker*)FindFirstObjectById(self->world, 0x104, msg->f4.i, self->root ? self->root : self);
        } else {
            s2 = 0;
        }
        if (msg->f8.i != -1) {
            s4 = (CaptionSpeaker*)FindFirstObjectById(self->world, 0x104, msg->f8.i, self->root ? self->root : self);
        } else {
            s4 = 0;
        }
        if (s2 && s2->walker) {
            SetStateWalkerTarget(s2->walker, 0x34C);
        }
        switch (msg->type) {
        case 1:
            SetArcTarget(&D_002708E0, s2);
            SetArcSpecialObject(&D_002708E0, s4);
            self->p2F0 = s2;
            if (s2) {
                self->waitFlags |= 2;
            }
            break;
        case 2:
            SetArcTarget(&D_00271558, s2);
            SetArcSpecialObject(&D_00271558, s4);
            self->p2F4 = s2;
            if (s2) {
                self->waitFlags |= 4;
            }
            break;
        default:
            return;
        }
        break;
    case 3:
        if (self->p2F0 && MatchesObjectId((BaseObject*)self->p2F0, msg->f18)) {
            s2 = (CaptionSpeaker*)self->p2F0;
            SetArcFade(&D_002708E0, 1);
            SetArcFade(&D_00271558, 0);
        } else if (self->p2F4 && MatchesObjectId((BaseObject*)self->p2F4, msg->f18)) {
            s2 = (CaptionSpeaker*)self->p2F4;
            SetArcFade(&D_00271558, 1);
            SetArcFade(&D_002708E0, 0);
        } else {
            s2 = 0;
        }
        a2 = msg->f1C;
        a0 = 0;
        if (a2 != -1) {
            a0 = FindFirstObjectById(self->world, 2, a2, self);
            self->waitFlags |= 0x10;
        } else {
            if (s2) {
                a0 = FindFirstObjectById(self->world, 1, 0x54A, s2);
            }
        }
        if (a0) {
            CreateAnimationPlayerWithoutPresetTargets((Animation*)a0, (BaseObject*)s2, 1, &self->player2F8, 0.0f, 1.0f);
            AddAnimationPlayerRecordCallback(self->player2F8, (PlacedObject**)self);
        }
        nm = msg->text;
        if (nm && *nm) {
            g_typedTextCaptionBox.vt->m08(&g_typedTextCaptionBox, (const char*)nm);
            if (s2) {
                *(Rgba4*)&g_typedTextCaptionBox.highlight = s2->color;
            } else {
                g_typedTextCaptionBox.highlight = 0x80808080;
            }
            if (self->player2F8) {
                if (msg->f1C == -1) {
                    f20 = msg->f8.f;
                } else {
                    f20 = self->player2F8->anim->length;
                }
            } else {
                f20 = msg->f8.f;
            }
            if (0.0f < f20) {
                T217D_440* h2 = &g_typedTextCaptionBox;
                h2->charsPerSecond = (f32)(GetStringLength((const char*)msg->text) + 10) / f20;
            } else {
                T217D_440* h3 = &g_typedTextCaptionBox;
                h3->charsPerSecond = 15.0f;
            }
            self->waitFlags |= 0x20;
        }
        if (msg->f4.f >= 0.0f) {
            SetTextPanelValuePercent(&g_typedTextCaptionBox, msg->f4.f + 1.0f);
            self->waitFlags |= 0x40;
        }
        if (msg->f8.f >= 0.0f) {
            self->waitFlags |= 0x80;
            self->waitDeadline = g_gameTime[0] + msg->f8.f;
        }
        if (msg->f20 != -1) {
            BaseObject* r = FindFirstObjectById(self->world, 0x104, msg->f20, self->root ? self->root : self);
            SetTextPanelSubject(&g_typedTextCaptionBox, r);
        }
        if (msg->f24 != -1) {
            g_camera->ctl460.anchorObject = FindFirstObjectByIdMode4(self->world, msg->f24, 0);
        } else if (self->second300 != -1) {
            g_camera->ctl460.anchorObject = FindFirstObjectByIdMode4(self->world, self->second300, 0);
        } else {
            g_camera->ctl460.anchorObject = 0;
        }
        if (msg->fC) {
            self->waitFlags |= 0x100;
            self->waitKey = msg->f10;
        }
        self->waitFlags |= 8;
        break;
    case 4: {
        void* tmp = &msg->f4;
        TriggerScriptEvent(self, 0x10, 1, &tmp);
        break;
    }
    case 5:
        ShowCountedScreenElement(self->world);
        break;
    case 6:
        HideCountedScreenElement(self->world);
        break;
    case 7:
        QueueMovie((MoviePlayer*)g_moviePlayer, msg->f4.p);
        break;
    }
}


void HandleStepSequenceNotification(StepSequence* state, s32 mode, void* value)
{
	HandlePlacedObjectNotification(state, mode, value);
	if (mode == 6 && value == state->player2F8)
		state->player2F8 = 0;
}

s32 TestStepWaitConditions(StepSequence* self)
{
    s32 flags = self->waitFlags;
    if (flags & 2) {
        SequenceStep* e = self->step2E4 < self->count2DC - 1 ? &((SequenceStep*)self->steps2E0)[self->step2E4 + 1] : 0;
        if (e != 0 && e->type == 2) {
            if (flags == 2) return 0;
        }
        if (D_002708E0.target == self->p2F0 && D_002708E0.phase == 1) flags &= 0xFFFFFFFD;
    }
    if (flags & 4) {
        SequenceStep* e = self->step2E4 < self->count2DC - 1 ? &((SequenceStep*)self->steps2E0)[self->step2E4 + 1] : 0;
        if (e != 0 && e->type == 1 && flags == 4) return 0;
        if (D_00271558.target == self->p2F4 && D_00271558.phase == 1) flags &= 0xFFFFFFFB;
    }
    if (flags & 1) {
        if (CheckStreamVoicePending() == 0) flags &= 0xFFFFFFFE;
    }
    if (flags & 8) {
        if (HasStreamVoice() == 0) flags &= 0xFFFFFFF7;
    }
    if (flags & 0x10) {
        if (self->player2F8 == 0) flags &= 0xFFFFFFEF;
    }
    if (flags & 0x20) {
        if (IsTextPanelTextTyped(&g_typedTextCaptionBox) != 0) flags &= 0xFFFFFFDF;
    }
    if (flags & 0x40) {
        if (g_camera->ctl460.zoomFraction == g_typedTextCaptionBox.value) flags &= 0xFFFFFFBF;
    }
    if (flags & 0x80) {
        if (self->waitDeadline <= g_gameTime[0]) flags &= 0xFFFFFF7F;
    }
    g_typedTextCaptionBox.buttonGlyph = 0;
    if (flags == 0x100) {
        s32 r;
        PadRecord* in = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
        s32 k = self->waitKey;
        r = 0;
        switch (k) {
        case 9:
            if (0.8f < in->stickMagnitude) r = 1;
            break;
        case 10:
            if (0.8f < in->secondStickMagnitude) r = 1;
            break;
        case 11:
            if (0.8f < __builtin_fabsf(in->stickX)) r = 1;
            break;
        case 12:
            if (0.8f < __builtin_fabsf(in->stickY)) r = 1;
            break;
        case 13:
            if (g_player != 0 && g_player->state == 2) r = g_player->subState == 3;
            break;
        case 14:
        {
            G27C230* fl = g_currentEntry;
            u32 t = fl->bits & 4;
            r = t != 0;
        }
            break;
        default:
            r = (in->flags & D_00261D08[k]) != 0;
            break;
        }
        if (r != 0) {
            flags = 0;
        } else {
            g_typedTextCaptionBox.buttonGlyph = D_00261D28[k];
        }
    }
    self->waitFlags = flags;
    return flags != 0;
}

void SkipRemainingSteps(StepSequence* self)
{
    if (self->state2D4 != 4) {
        if (self->step2E4 < self->count2DC) {
            for (self->step2E4++; self->step2E4 < self->count2DC; self->step2E4++) {
                SequenceStep* it = &((SequenceStep*)self->steps2E0)[self->step2E4];
                switch (it->type) {
                case 0: case 1: case 2: case 3: case 7:
                    break;
                case 4: {
                    s32* p = &it->w4;
                    TriggerScriptEvent(self, 0x10, 1, &p);
                    break;
                }
                case 5:
                    ShowCountedScreenElement(self->world);
                    break;
                case 6:
                    HideCountedScreenElement(self->world);
                    break;
                }
            }
        }
        if (self->mode2D0 == 2)
            PopStackElement((ElementStack*)g_elementStack);
    }
}

void RunStepSequence(StepSequence* self)
{
    s32 index;

    if (self->step2E4 < self->count2DC) {
        for (;;) {
            if (TestStepWaitConditions(self) != 0) {
                return;
            }
            if (self->player2F8 != 0) {
                StopAnimationPlayer(self->player2F8);
                self->player2F8 = 0;
            }
            index = self->step2E4 + 1;
            self->step2E4 = index;
            if (!(index < self->count2DC)) {
                break;
            }
            HandleStepSequenceMessage(self, (SequenceMessage*)((u8*)self->steps2E0 + index * 0x28));
        }
        SkipRemainingSteps(self);
    }
}

void ShowStepSequenceText(StepSequence* value, Ent65* object)
{
    if (object != 0) {
        object->vt->f158(object, value);
    } else {
        g_typedTextCaptionBox.child = value;
        PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
    }
}

void ChooseStepSequenceState(StepSequence* self)
{
    T217D_1380* g = &g_timerCaption;
    if (g->state >= 2 || g->pressed != 0)
        return;
    if (IsStreamVoiceLocked() != 0)
        return;
    if (D_00275F84 == 1)
        return;
    if (self == D_0027051C)
        return;
    s32 mode = 1;
    if (*(s32*)self->target304 != 0) {
        mode = (self->mode2D0 == 2) ? self->state2D4 : 5;
    } else {
        s32 n = self->extraTargetCount;
        if (n > 0) {
            for (s32 i = 0; i < n; i++) {
                if (*(s32*)self->extraTargets[i] != 0) {
                    mode = 5;
                    break;
                }
            }
        }
    }
    SetStepSequenceState(self, mode);
}

void ResetStepSequence(StepSequence* self)
{
    if (self->state2D4 != 1 && self->state2D4 != 3) {
        SetStepSequenceState(self, 0);
    }
}

void AddSequenceExtraTarget(StepSequence* collection, s32 key, u32 kind)
{
	if ((u32)collection->extraTargetCount >= 4) return;
	void* item = GetLevelEntryByKey(key);
	if (!item) return;
	void* value = GetIndexedTargetSlot(item, kind);
	if (!value) return;
	u32 count = collection->extraTargetCount;
	collection->extraTargets[count] = value;
	collection->extraTargetCount = count + 1;
}

void* GetScatterController(void)
{
    return &g_scatterController;
}

void ClearScatterController(void* state)
{
	FillMemory(state, 0, 0x24);
}

void ResetScatterController(ScatterController* self)
{
    self->refillLo = 4;
    self->refillHi = 6;
    self->countLo = 1;
    self->countHi = 3;
    GameProgress* g = g_saveData;
    if (g->levelIndex == 0 || g->levelIndex == 5 || g->entryIndex == 1) self->table = &D_00261E90;
    else if (!(g_currentEntry->flags & 2)) self->table = D_00261D70;
    else self->table = &D_00261E30;
    SetScatterLevel(self, g_currentEntry->dt);
    s32 a = ((ScatterTable*)self->table)->countLoStart;
    s32 b = ((ScatterTable*)self->table)->countLoEnd;
    f32 t = g_currentEntry->dt;
    s32 ra;
    if (a == b) ra = b;
    else if (a < b) ra = a + (s32)(t * ((f32)b + 0.99900001f - (f32)a));
    else ra = b + (s32)((1.0f - t) * ((f32)a + 0.99900001f - (f32)b));
    s32 c = ((ScatterTable*)self->table)->countHiStart;
    s32 d = ((ScatterTable*)self->table)->countHiEnd;
    t = g_currentEntry->dt;
    s32 rc;
    if (c == d) rc = d;
    else if (c < d) rc = c + (s32)(t * ((f32)d + 0.99900001f - (f32)c));
    else rc = d + (s32)((1.0f - t) * ((f32)c + 0.99900001f - (f32)d));
    s32 r = RandomIntInRange(ra, rc);
    s32 i = 0;
    ThresholdRange* e = 0;
    self->countdown = r;
    for (; i < ((ScatterTable*)self->table)->count; i++) {
        e = &((ScatterTable*)self->table)->ranges[i];
        if (e->threshold <= g_currentEntry->f10) break;
    }
    self->bandCountdown = RandomIntInRange(e->low, e->high);
    self->spareRaised = 0;
}

void UpdateScatterLevelLimits(ScatterController* self)
{
    if (D_00275B00 & 8) {
                if (((ScatterTable*)self->table)->bandStart1 <= g_currentEntry->dt && g_currentEntry->dt < ((ScatterTable*)self->table)->bandStart2) {
            if (g_saveData->spareCount < ((ScatterTable*)self->table)->spareCount1) {
                SetSpareCount(((ScatterTable*)self->table)->spareCount1);
                self->spareRaised = 1;
            }
        } else if (((ScatterTable*)self->table)->bandStart2 <= g_currentEntry->dt) {
            if (g_saveData->spareCount < ((ScatterTable*)self->table)->spareCount2) {
                SetSpareCount(((ScatterTable*)self->table)->spareCount2);
                self->spareRaised = 1;
            }
        }
    } else {
        f32 v = ClampToRange((ValueRange*)((u8*)((ScatterTable*)self->table)->levelRange), g_currentEntry->dt);
        SetScatterLevel(self, v);
    }
    CompleteSoundNotifiers(g_currentWorld);
}

void NotifyScatterControllerLoaded(void* self)
{
}

void RaiseScatterLevels(ScatterController* self, f32 amount)
{
    f32 x = g_currentEntry->dt + amount * *(f32*)((u8*)self->table + 0x10);
    SetScatterLevel(self, x);
    s32 index = g_saveData->reserveCount;
    f32 y;
    if (index < 0) {
        y = *(f32*)((u8*)self->table + 0x40);
    } else {
        y = *(f32*)((u8*)self->table + 0x3C);
        if (index <= *(s32*)((u8*)self->table + 0x4C)) {
            y += *(f32*)((u8*)self->table + 0x50);
        }
    }
    f32 result = ((f32 (*)(void*, f32))ClampToRange)(&g_unitRange, g_currentEntry->f10 + amount * y);
    g_currentEntry->f10 = result;
}

void RaiseScatterLevelForObject(ScatterController* obj, FlaggedObject* node)
{
    f32 value;
    if (node != 0) {
        s32 idx = node->ordinal;
        s32 bit = 1 << (idx & 7);
        if (g_currentEntry->bits74[idx / 8] & bit) {
            value = ((ScatterTable*)obj->table)->raiseSeen;
            goto have;
        }
    }
    value = ((ScatterTable*)obj->table)->raiseNew;
have:
    SetScatterLevel(obj, g_currentEntry->dt + value);
    if (node != 0) {
        G27C230* m = g_currentEntry;
        s32 idx = node->ordinal;
        s32 bit = 1 << (idx & 7);
        u8 cur = m->bits74[idx / 8];
        if (cur & bit) return;
        m->bits74[idx / 8] = cur | bit;
        m->count70 = m->count70 + 1;
    }
}

void ResetScatterLevels(ScatterController* object)
{
	SetScatterLevel(object, 0.0f);
	G27C230* manager = g_currentEntry;
	manager->f10 = 0.0f;
	manager->count70 = 0;
	FillMemory(manager->bits74, 0, 1);
}

void ScatterObjectsAtPoint(ScatterController* self, void* p, s32 n, s32 flag)
{
    s32 did = 0;
    if ((g_currentWorld)->f2354 != 0 && n != 0) {
        if (!flag) {
            self->bandCountdown--;
            self->countdown--;
        }
        if (n > 0) {
            ScatterObjectsAroundCircle(g_currentWorld, 0x58, (Vec02*)p, n, 0);
        } else {
            if (self->bandCountdown < 0) {
                if (g_currentEntry->f10 != 0.0f) {
                    did = 1;
                    g_currentEntry->f10 = ClampToRange(&g_unitRange, g_currentEntry->f10 + ((ScatterTable*)self->table)->bandLevelStep);
                }
                s32 i = 0;
                ThresholdRange* r = 0;
                while (i < ((ScatterTable*)self->table)->count) {
                    r = &((ScatterTable*)self->table)->ranges[i];
                    if (g_currentEntry->f10 >= r->threshold) break;
                    i++;
                }
                self->bandCountdown = RandomIntInRange(r->low, r->high);
            }
            if (!flag) {
                for (s32 i = 0; i < ((ScatterTable*)self->table)->count - 1; i++) {
                    if (((ScatterTable*)self->table)->ranges[i].threshold <= g_currentEntry->f10) {
                        s32 v = RandomIntInRange(((ScatterTable*)self->table)->ranges[i].low, ((ScatterTable*)self->table)->ranges[i].high);
                        self->bandCountdown = (self->bandCountdown < v) ? self->bandCountdown : v;
                        goto done;
                    }
                }
            done:;
            }
            if (did) {
                ScatterObjectsAroundCircle(g_currentWorld, 0x57, (Vec02*)p, 1, 0);
            } else {
                s32 a, b;
                if (self->countdown < 0) {
                    a = self->refillLo;
                    b = self->refillHi;
                    self->countdown = RandomIntInRange(LevelLerp::Get(((ScatterTable*)self->table)->countLoStart, ((ScatterTable*)self->table)->countLoEnd), LevelLerp::Get(((ScatterTable*)self->table)->countHiStart, ((ScatterTable*)self->table)->countHiEnd));
                } else {
                    a = self->countLo;
                    b = self->countHi;
                }
                n = RandomIntInRange(a, b);
                if (n) ScatterObjectsAroundCircle(g_currentWorld, 0x58, (Vec02*)p, n, 0);
            }
        }
    }
    if (!flag) {
        g_currentEntry->f10 = ClampToRange(&g_unitRange, g_currentEntry->f10 + ((ScatterTable*)self->table)->levelStep);
    }
}

void SetScatterLevel(ScatterController* object, f32 unused)
{
	f32 value = ((f32 (*)(void*))ClampToRange)(object->table);
	g_currentEntry->dt = value;
}

void SetListLinkOffset(List01* self, s32 offset)
{
    self->offset = offset;
}

void ClearList(List01* p)
{
	p->tail = 0;
	p->head = 0;
}

void ClearListLinks(ListLink* p)
{
	p->prev = 0;
	p->next = 0;
}

ListLink* GetListLinks(List01* p, void* item)
{
	return (ListLink*)((u8*)item + p->offset);
}

void AppendToList(List01* self, void* item)
{
    ListLink* slot = GetListLinks(self, item);
    if (self->tail == 0) {
        self->head = item;
    } else {
        ListLink* oldTail = GetListLinks(self, self->tail);
        slot->prev = self->tail;
        oldTail->next = item;
    }
    self->tail = item;
}

void PrependToList(List01* self, void* item)
{
    ListLink* slot = GetListLinks(self, item);
    if (self->head == 0) {
        self->tail = item;
        self->head = item;
        return;
    }
    {
        ListLink* oldHead = GetListLinks(self, self->head);
        slot->next = self->head;
        oldHead->prev = item;
        self->head = item;
    }
}

void InsertBeforeInList(List01* self, void* before, void* item)
{
    if (before == 0) {
        AppendToList(self, item);
        return;
    }
    if (before == self->head) {
        PrependToList(self, item);
        return;
    }
    ListLink* next = GetListLinks(self, item);
    ListLink* previous = GetListLinks(self, before);
    void* after = previous->prev;
    ListLink* afterSlot = GetListLinks(self, after);
    next->next = before;
    next->prev = after;
    previous->prev = item;
    afterSlot->next = item;
}

LINKER_REMNANT(func_001525F8);

void RemoveFromList(List01* list, void* item)
{
    ListLink* link = GetListLinks(list, item);
    ListFrame* e = g_activeListFrames;
    while (e != 0) {
        if (e->link != (u8*)link) {
            e = e->prev;
            continue;
        }
        if (link->prev != 0) e->link = (u8*)GetListLinks(list, link->prev);
        else e->link = (u8*)list;
        e = e->prev;
    }
    if (link->prev != 0) {
        GetListLinks(list, link->prev)->next = link->next;
    } else {
        list->head = link->next;
    }
    if (link->next != 0) {
        GetListLinks(list, link->next)->prev = link->prev;
    } else {
        list->tail = link->prev;
    }
    link->next = 0;
    link->prev = 0;
}

s32 IsInList(List01* self, void* item)
{
    ListLink* slot = GetListLinks(self, item);
    s32 result = 0;
    if (slot->next != 0) {
        goto matched;
    }
    if (self->tail != item) {
        goto done;
    }
matched:
    result = 1;
done:
    return result;
}

u32 IsListEmpty(List01* p)
{
	return p->head == 0;
}

void SpliceListToEnd(List01* dst, List01* src)
{
    if (src->head != 0) {
        if (dst->head == 0) {
            *dst = *src;
            ClearList(src);
        } else {
            ListLink* p1 = GetListLinks(dst, dst->tail);
            ListLink* p2 = GetListLinks(src, src->head);
            p1->next = src->head;
            p2->prev = dst->tail;
            dst->tail = src->tail;
            ClearList(src);
        }
    }
}

s32 CountListItems(List01* list)
{
    s32 count = 0;
    u8* node = (u8*)list->head;
    if (node != 0) {
        s32 stride = list->offset;
        do {
            node = *(u8**)(node + stride);
            count++;
        } while (node != 0);
    }
    return count;
}

void InitDmaChannels()
{
	ResetDmaController(1);
	ResetGsPaths();
	g_vif0Channel = GetDmaChannel(0);
	g_vif1Channel = GetDmaChannel(1);
	g_gifChannel = GetDmaChannel(2);
	g_fromSprChannel = GetDmaChannel(8);
	g_toSprChannel = GetDmaChannel(9);
}

extern const VtableEntry D_0024A0E0[4] = {{0, 0}, {0, SkipDisplayListWriterSlot}, {0, 0}, {0, 0}};

PacketWriter* InitPacketBuffer(PacketWriter* self)
{
    self->f10 = 0;
    self->f14 = 0;
    self->vt = (const PacketWriterVt*)D_0024A0E0;
    ClearPacketBuffer(self);
    return self;
}

void ClearPacketBuffer(PacketWriter* p)
{
	p->end = 0;
	p->begin = 0;
	p->f08 = 0;
	p->cur = 0;
}

void RewindPacketBuffer(PacketWriter* p)
{
	u8* b = p->begin;
	p->f08 = 0;
	p->cur = b;
}

void AllocatePacketBuffer(PacketWriter* self, s32 count)
{
    s32 size = count << 4;
    u8* base = ReservePermanentMemory(size);
    self->cur = base;
    self->end = base + size;
    self->begin = base;
}

void AllocateQuadwordBuffer(PacketWriter* buffer, u32 count, u32 kind)
{
	u32 bytes = count << 4;
	u8* memory = AllocateFrontMemory(bytes);
	buffer->cur = memory;
	buffer->end = memory + bytes;
	buffer->begin = memory;
}

void AllocateTempPacketBuffer(PacketWriter* buffer, u32 count)
{
	u32 bytes = count << 4;
	u8* memory = AllocateBackMemory(bytes);
	buffer->cur = memory;
	buffer->end = memory + bytes;
	buffer->begin = memory;
}

void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory)
{
    u8* base = (u8*)memory;
    self->begin = base;
    self->cur = base;
    self->end = base + count * 16;
}

void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin)
{
    CloseDmaTag(self);
    if (outCount != 0) {
        *outCount = ((u32)self->cur - (u32)self->begin) >> 4;
    }
    if (outBegin != 0) {
        *outBegin = self->begin;
    }
    ClearPacketBuffer(self);
}

void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags)
{
    CloseDmaTag(self);
    u32 n = (self->curU - (u32)self->begin) >> 4;
    if (count != 0) {
        *count = n;
    }
    if (begin != 0) {
        *begin = (u32)self->begin;
    }
    if (out != 0) {
        *out = CopyToFrontMemory(n << 4, self->begin);
    }
    ClearPacketBuffer(self);
}

void SubmitPacketBuffer(PacketWriter* self, void* dma)
{
    CloseDmaTag(self);
    SyncDataCache(0);
    StartDmaChain((DmaChannel*)dma, self->begin);
    self->cur = self->begin;
}

LINKER_REMNANT(func_00152B30);

void BeginDmaTag(PacketWriter* self)
{
    CloseDmaTag(self);
    u8* q = self->cur;
    self->f08 = (s32*)q;
    self->cur = q + 16;
    *(u64*)q = 0x10000000;
    *(u64*)((u8*)self->f08 + 8) = 0;
}

void AddDmaRefTag(PacketWriter* self, s32 lo, s32 hi)
{
    s32 flag = 0;
    if (self->f08 != 0) {
        CloseDmaTag(self);
        flag = 1;
    }
    u8* p = self->cur;
    self->cur = p + 16;
    *(u64*)p = (u64)lo | 0x40000000 | ((u64)hi << 32);
    *(u64*)(p + 8) = 0;
    if (flag != 0) {
        u8* q = self->cur;
        self->f08 = (s32*)q;
        self->cur = q + 16;
        *(u64*)q = 0x10000000;
        *(u64*)((u8*)self->f08 + 8) = 0;
    }
}

void AddDmaCallTag(PacketWriter* self, s32 hi)
{
    s32 flag = 0;
    if (self->f08 != 0) {
        CloseDmaTag(self);
        flag = 1;
    }
    u8* p = self->cur;
    self->cur = p + 16;
    *(u64*)p = ((u64)hi << 32) | 0x50000000;
    *(u64*)(p + 8) = 0;
    if (flag != 0) {
        u8* q = self->cur;
        self->f08 = (s32*)q;
        self->cur = q + 16;
        *(u64*)q = 0x10000000;
        *(u64*)((u8*)self->f08 + 8) = 0;
    }
}

void AddDmaReturnTag(PacketWriter* self)
{
    CloseDmaTag(self);
    u64* p = (u64*)self->cur;
    self->cur = (u8*)p + 0x10;
    p[0] = 0x60000000ull;
    p[1] = 0;
}

void AppendPacketQuadwords(PacketWriter* self, s32 n, void* src)
{
    CopyQuadwords(*(void**)((u8*)self + 0xC), src, n);
    *(u8**)((u8*)self + 0xC) += n * 16;
}

void AddDmaEndTag(PacketWriter* self)
{
    CloseDmaTag(self);
    u8* cursor = *(u8**)((u8*)self + 0xC);
    *(u8**)((u8*)self + 0xC) = cursor + 0x10;
    *(u64*)cursor = 0x70000000;
    *(u64*)(cursor + 8) = 0;
}

void CloseDmaTag(PacketWriter* self)
{
    if (self->f10 != 0) {
        s32 p = self->curS;
        if ((p & 0xF) != 0) {
            *(s32*)p = 0;
            p += 4;
            while ((p & 0xF) != 0) { *(s32*)p = 0; p += 4; }
        }
        self->curS = p;
    } else if (self->f14 != 0) {
        const PacketWriterVt* t = self->vt;
        t->close((PacketWriter*)((u8*)self + t->adj1), 0);
    }
    s32* q = self->f08;
    if (q != 0) {
        *q = *q | (((self->curS - (s32)q) >> 4) - 1);
        self->f08 = 0;
    }
}

void SkipDisplayListWriterSlot() {}

LINKER_REMNANT(func_00152E20);

void InitTextureRenderObject(TextureRenderObject* self)
{
    InitPlacedObject(self);
}

void BuildTexturePackets(TextureRenderObject* self, RangeRecord* a)
{
    PacketWriter pa;
    PacketWriter pb;
    Vec4U v0;
    Vec4U v1;
    Quad4 q;
    TextureHeader* tex;
    s32 i;
    u64 bits;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;

    self->drawRange = a;
    if (a == 0) {
        return;
    }
    tex = (TextureHeader*)*a->link->elems->entries;
    InitGifPacket(&pa);
    InitPacketWriter(&pb);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&pa, 0x40);
    AllocateTempPacketBuffer(&pb, 0x40);
    WriteVifFlushE(&pb);
    SetupTextureRenderTarget(tex, &pa);
    BeginGifTag(&pa, 0x246, 3, 0x551);
    AddGifRgbaEntry(&pa, 0);
    AddGifXyzEntry(&pa, 0, 0, 0);
    AddGifXyzEntry(&pa, tex->w << 4, tex->h << 4, 0);
    BeginGifTag(&pa, 0x200, 1, 0xE);
    AddGifRegisterWrite(&pa, 0x41, ((u64)(tex->w - 2) << 16) | (((u64)(tex->h - 2) << 48) | 0x100000001ULL));
    EndGifPacket(&pa);
    WriteVifDirectFromWriter(&pb, &pa);
    v0.x = (f32)((tex->w - 1) * 8) * 1024.0f;
    v0.y = (f32)((tex->h - 1) * 8) * 1024.0f;
    v0.z = 0;
    v1.x = (f32)(tex->w * 8) * 1024.0f + 8589934592.0f;
    v1.y = (f32)(tex->h * 8) * 1024.0f + 8589934592.0f;
    v1.z = 0;
    WriteVifBaseOffset(&pb, 0, 0);
    CopyWordsToWriter(&pb, 8, 1, (u32*)&v0, 0);
    CopyWordsToWriter(&pb, 8, 1, (u32*)&v1, 1);
    ClearPacketBuffer(&pa);
    UsePacketBufferMemory(&pa, 1, &q);
    ReserveGifPackedData(&pa, 0x24D, 0, 3, 0x412, 0);
    CopyWordsToWriter(&pb, 0xC, 1, (u32*)&q, 0xC);
    DetachPacketBufferCopy(&pb, &self->firstPacket, 0, &self->firstPacketSize, 0x13);
    PopBackMemoryMark();
    PushBackMemoryMark();
    ClearPacketBuffer(&pa);
    ClearPacketBuffer(&pb);
    AllocateTempPacketBuffer(&pa, 0x80);
    AllocateTempPacketBuffer(&pb, 0x80);
    bits = (tex->tex0 & ~0x1800000000ULL) | 0x800000000ULL;
    BeginGifTag(&pa, 0x200, 1, 0xE);
    AddGifRegisterWrite(&pa, 0x3F, 0);
    AddGifRegisterWrite(&pa, 7, bits);
    AddGifRegisterWrite(&pa, 0x15, 0x61);
    AddGifRegisterWrite(&pa, 0x48, 0x31001);
    BeginGifTag(&pa, 0x316, 5, 0xE5353);
    x0 = tex->w << 4;
    y0 = tex->h << 4;
    x1 = x0 + 8;
    y1 = y0 + 8;
    for (i = 1; i >= 0; i--) {
        AddGifUvEntry(&pa, 0x10, 8);
        AddGifXyzEntry(&pa, 0, 0, 0);
        AddGifUvEntry(&pa, x0 + 0x10, y1);
        AddGifXyzEntry(&pa, x0, y0, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
        AddGifUvEntry(&pa, 8, 0x10);
        AddGifXyzEntry(&pa, 0, 0, 0);
        AddGifUvEntry(&pa, x1, y0 + 0x10);
        AddGifXyzEntry(&pa, x0, y0, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
        AddGifUvEntry(&pa, 8, 8);
        AddGifXyzEntry(&pa, 8, 8, 0);
        AddGifUvEntry(&pa, x1, y1);
        AddGifXyzEntry(&pa, x1, y1, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
    }
    EndGifPacket(&pa);
    WriteVifFlush(&pb);
    WriteVifDirectFromWriter(&pb, &pa);
    DetachPacketBufferCopy(&pb, &self->secondPacket, 0, &self->secondPacketSize, 0x13);
    PopBackMemoryMark();
}

void QueuePlacedObjectDraw(TextureRenderObject* self, s32 unused, void* a2)
{
    (void)unused;
    if (self->drawRange != 0) {
        self->desc02()->m27(self, a2);
        DeferredRequest f;
        (void)FillMemory(&f, 0, 0x80);
        f.callback = (void*)DrawPlacedObjectParts;
        f.group = 0;
        BuildPlacedObjectTransform(self, (Quad16*)a2, (ScaledTransform*)&f.block);
        f.arg = self;
        QueueDeferredRequest(&f);
    }
}


// The file's .data, 0x261CC8 to 0x261F28, in retail's order: the globals its functions read
// (D_00261EF0 and the DMA channel words are read by many files, which keep them extern).
ObjectLink g_pooledObjectLinks[1] = { { 2, 0x2BC, 0x574 } };
f32 D_00261CD4 = 500.0f;
f32 D_00261CD8 = 800.0f;
ObjectLink g_takerLinks[3] = { { 4, 0x2B4, 0x734 }, { 4, 0x2B5, 0x738 }, { 0, 0x2B6, 0x73C } };
u16 D_00261D08[16] = {0x40,0x40,0x80,0x20,0x10,4,1,8,2,0,0,0,0,0,0,0};
u8 D_00261D28[16] = {0x58,0x58,0x53,0x4F,0x54,0x4C,0x6C,0x52,0x72,0x28,0x29,0x28,0x28,0x58,0,0};
// size: s32 counter (lw/sw), 4 bytes before an 8-aligned next label
s32 D_00261D38 = 0;
ThresholdRange g_thresholdRanges[4] = {
    { 0.8f, 2, 5 }, { 0.4f, 6, 10 }, { 0.2f, 15, 25 }, { 0.0f, 50, 100 }
};
ScatterTable D_00261D70[2] = {
    { 0, 1.0f, 0.0f, 0.6f, 0.1f, -0.8f, 0.0f, 4, 6, 0, 2, 0.399f, 1, 0.799f, 2, 0.075f, 0.25f, -0.2f, -0.003f, 2, 0.075f, 4, g_thresholdRanges, 0 },
    { 0, 0.5f, 0.0f, 0.2f, 0.1f, -0.4f, -0.4f, 4, 6, 0, 2, 0.399f, 0, 0.799f, 0, 0.075f, 0.25f, -0.2f, -0.003f, 2, 0.075f, 4, g_thresholdRanges, 0 },
};
ScatterTable D_00261E30 = { 0, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.0f, 4, 6, 0, 2, 0.399f, 0, 0.799f, 0, 0.075f, 0.25f, -0.2f, -0.003f, 2, 0.075f, 4, g_thresholdRanges, 0 };
ScatterTable D_00261E90 = { 0, 1.0f, 0.0f, 0.0f, 0.1f, -0.8f, 0.0f, 4, 6, 0, 2, 0.399f, 1, 0.799f, 2, 0.075f, 0.25f, -0.2f, -0.003f, 2, 0.075f, 4, g_thresholdRanges, 0 };
// size: func_00151A68 clears 0x24 bytes of it
ScatterController g_scatterController = {};
// size: semaphore id from func_002027A0 (lw/sw), 4-byte label
u32 g_vif0Channel = 0;
u32 g_vif1Channel = 0;
u32 g_gifChannel = 0;
u32 g_fromSprChannel = 0;
// The file's last .data: the 8 zero bytes after it are the linker's padding before
// active_set_solver.cpp's 16-aligned .data (D_00261F30).
u32 g_toSprChannel = 0;
