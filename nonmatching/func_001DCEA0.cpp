// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 749/884 (84.7%), checked 2026-11-08
// NEAR (2026-11-08, night-gamec): retail sets the high parts of D_00275714 and g_camera in s0 and s1 in the prologue, so self is s2 and the stream s3 (s1 and s2 here); the frame, both walks and the calls are retail's
// In the context of its file, src/main/file_1D62E0.cpp: its declarations before the function, bodies cut.
// From 0x1D62E0 to 0x1DDCE0: classes 0x07 and 0x3F, the output buffer, class 0x19, the world
// (class 0x6C) and its script functions. Its .data runs from 0x275140 to the zeroed globals
// D_00275710 (g_currentWorld) to D_00275728 that close it; its .rodata is the "%s" of
// func_001D72C8, the float of func_001D8470 and the pairs of func_001DCD28. One file between
// two edges with no evidence inside it: it could be several.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "deferred_request.h"
#include "list_iter.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
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

extern f32 g_gameClock[];

typedef void (*VFnA)(void* self);
typedef void (*VFnB)(void* self, void* arg);

s32 IsObjectAttached(void* node);

s32 TestCollidersMayContact(void* self, s32 value);

void InitSwitchedCollider(void* self);
void CopyMemory(void* dst, void* src, u32 size);
void ResetPathFollower(void* self);

void HandleChildGroupNotification(StandIn* self, s32 kind, ObjectMessage* ref);

void FillMemory(OwnerMessage* p, s32 zero, s32 size);

void FlushOutputBuffer(OutputBuffer* a0, s32 a1);
void FreeObjectMemory(OutputBuffer* a0);

void CopyMemory(void* dst, void* src, s32 bytes);
s32 PrintBuffered(void* a, void* b);
void WriteFile(s32 a, void* b, s32 n);

void CopyMemory(void* dst, void* src, s32 count);
void FlushOutputBuffer(OutputBuffer* self);

void StartPlacedObject(PathFollower* self);
void ResolveObjectLinks(PathFollower* self, s32 n, void* table);
f32 ArctangentOfRatio(f32 a, f32 b);
StateTrigger* CreateStateWalker(StateTrigger* a, PathFollower* self, s32 b, s32 c);
void SetStateWalkerTarget(StateTrigger* a, s32 b);
void StartSoundEffect(s32 id, void* a1, PathFollower* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
f32 RandomFloatInRange(f32 a, f32 b);
void* FindFirstObjectById(World* host, s32 a1, s32 a2, PathFollower* ctx);
s32 GatherObjectsByMode(World* host, s32 a1, s32 a2, s32 a3, s32 a4, BaseObject** out);
void ResetPathFollower(PathFollower* self);

void CaptureColliderPose(void);

void SetCachedVoiceParam(void* a, void* b);

void* TakePoolSlot(void* p);
void FillMemory(void* p, s32 value, u32 size);

void* RefreshCachedVoiceParam(void* a, void* b);

void* TakePoolSlot(void* p);
void FillMemory(void* p, s32 a, s32 b);

void PushFreeSlot(void* list, void* item);

void PushFreeSlot(void* list, void* item);

void* TakeCallRecord(void* self);

extern f32 g_gameTime;

void ReleaseCallRecords(void* self, void* node);

typedef void (*FollowerEffectFn)(void* self, void* a, void* b);
struct FollowerEffectTarget { FollowerEffectFn* vtbl; };
void SetAgentMainClip(void* self, void* value);
void StartSwitchedColliderEffect(void* self, void* a, void* b);

void RecomputeColliderFrame(void* self);
void FindPathFollowerPathPosition(void* self);

struct NoticeLink { u8 pad[0x50]; void* owner; };
struct CountedNotice { u8 pad0[8]; s32 kind; u8 pad1[0x6CC - 0xC]; NoticeLink* link; };

void HandleSwitchedColliderNotification(void* self, s32 kind, CountedNotice* rec);

void AlignBufferedStreamPosition(void* self, s32 n);
void ReadBufferedStreamBytes(void* self, s32 size, s32 obj);

void SetListLinkOffset(void* self, s32 value);

void ReleaseCallRecords(void* self, void* node);

f32 GetWrappedDifference(f32 x, f32 lim, f32 base);

void UpdateColliderBounds(void* self);
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void ExpandColliderBoundsBySphere(void* self, void* p, f32 f);

extern u8 D_0026DAAC[];

void HandleSwitchedColliderActivation(void* a, void* b);
void SetWorldActiveFollower(void* sub, void* self);
void SetPathFollowerMode(void* self, s32 mode);

void FindPathFollowerPathPosition(void* self);
void GetObjectWorldPosition(void* self, void* arg);

s32 ReduceBufferedStreamBytesLeft(void* self, s32 n);
s32 ReadBufferedS32(void* self);

struct WalkerHolder { u8 pad[0x48]; void* f48; };

WalkerHolder* FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void GetStateWalkerTargetKey(void* dev, s32* out);
void GetStateWalkerCurrentKey(void* dev, s32* out);
s32 AreMenusAndFadeClear(void);

void MarkPoolLiveEnds(void* a);
s32 LookupScriptVariable(void* a, s32 b, s32 c, ScriptValue* d);
void* EvalScriptExpression(ScriptValue* t, R11B008Node* n, void* c);
void* AssignScriptVariable(ScriptValue* self, void* table, s32 key, ScriptValue* item);
extern u8 g_markStacks[];

extern f32 g_gameClock[];

void* GetActiveSwitchedCollider(void);
f32 ApproachValueWithRamp(void* p, s32 zero, f32 a, f32 b, f32 c);
f32 RandomFloatInRange(f32 a, f32 b);

void GetObjectWorldPosition(void* item, void* out);

extern f32 g_gameTime;
void* GetActiveSwitchedCollider(void);
void ActivateSwitchedCollider(void* self);

void UpdateSwitchedCollider(PathFollower* self, f32 t);
void UpdatePathFollowerPace(PathFollower* self);
void AdvancePathFollowerAlongPath(PathFollower* self, s32* out);
void ComputePathFollowerHeadingTarget(PathFollower* self);
void UpdatePathFollowerSound(PathFollower* self, f32 t);
void SteerPathFollower(PathFollower* self);
void func_001D8E40(PathFollower* self);
void AdvancePathFollowerEntry(PathFollower* self, s32 v);
void ProcessPathFollowerContacts(PathFollower* self);
void ClearRootTries(PathFollower* self);

extern f32 g_gameTime;

extern u8 g_scatterController[];

void RaiseScatterLevels(void* msg, f32 value);

s32 IsInsideAnyRange(s32 count, ValueRange* spans, f32 x);

// A quadratic by its three coefficients (func_001D8578, func_001DB290).
struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

struct WorldRecord { u8 b; };

extern s32 g_buttonCodeFlags;

void InitObject(World* self);
void SetIopChannel2Setting(World* self, s32 a, s32 b);
void* AllocateZeroedFrontMemory(s32 size);
void InitContactTables(World* self);
void InitSlotPool(WorldRecord* p, s32 a, s32 b);
void InitAlignedSlotPool(WorldRecord* p, s32 a, s32 b);
void SetListLinkOffset(WorldRecord* p, s32 a);
void SetWorldGravityZ(World* self, f32 x);

#define SUB(off) ((WorldRecord*)((u8*)self + (off)))

typedef s32 VoiceParamIndex;

s32 GetCachedVoiceParam(VoiceParamIndex index);

extern f32 D_002754F8; extern f32 D_002754F4; extern f32 g_frameDt; extern f32 D_002754E8[3];
f32 ArctangentOfRatio(f32 a, f32 b); f32 WrapAngle(f32 a); f32 ClampToMagnitude(f32 a, f32 b); f32 ApproachAngleWithRamp(void* p, void* out, f32 a, f32 b, f32 c);

extern s32 g_switchedColliderCount;
extern s32 g_padSelectFlags;
extern u8 g_elementStack[];
extern s32 g_coloredTriangleSet;
extern f32 g_stepScale;
extern s32 D_00261D38;

void ActivateSwitchedColliderIndex(s32 index);
void UpdatePadRouting(void);
void ClearCameraObjectList(void* obj);
void ClearClass75List(void);
void ClearPointObjectList(void);
void ClearTargetVectorList(void);
void ClearObjectLists(void);
void StopAllSoundsAndWait(void);
void ResetScreenResources(void);
void ShutDownScriptValuePools(void);
void ResetElementStack(void* a);
void ResetFrontMemory(void);

struct __attribute__((packed)) PackedWord { s32 v; };

typedef int Quadword __attribute__((mode(TI)));

void StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
void* StoreQuadword(void* dst, Quadword v);
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

s32 GetLevelEntryWord(void* obj);

s32 GetLevelEntryWord(void* obj);

s32 GetLevelEntryWord(void* obj);

s32 GetLevelEntryWord(void* obj);

// The four key/value slots after offset 0x44 of a level entry (SetEntrySlotValue, GetEntrySlotValue).
struct EntrySlot { s32 key; s32 value; };
struct EntrySlotTable { u8 pad[0x44]; EntrySlot slots[4]; };

void* GetLevelEntryByKey(void* obj);

s32 ComputeCompletionPercent(void* p);

void* TakePoolSlot(void* p);
void FillMemory(void* p, s32 value, u32 size);

extern void* g_frameCount;
extern void* g_lightingChangeFrame;

f32 ClampToRange(void* p);

void* PushSoundLevel(void* p);

void HandleSwitchedColliderActivation(void* self, void* p);

void* RandomIntInRange(void* a, void* b);
s32 ScatterObjectsAroundCircle(void* heap, int size, void* c, void* d, int e);

extern u8 g_scatterController[];

void SetScatterLevel(void* p);

void* RemoveSoundLevelAndRecompute(void* p);

typedef void (*ActiveFollowerFn)(void* self);
struct ActiveFollowerChild { ActiveFollowerFn* vtbl; };

void PushFreeSlot(void* list, void* item);

void UnlinkContactTable(Contacts03* node, Contacts03** head);
void PushContactTable(Contacts03* node, Contacts03** head);

extern u8 g_elementStack[];

void PopStackElement(void* g);

struct __attribute__((packed)) PackedPageWord { s32 v; };

void SetPauseMenuLayerPage(T217D_6D0* self, s32 mode, s32 value);

s32 ReadBufferedU32(void* src);
void SkipBufferedBlock(void* self);

struct CloneBatch { s32 count; s32* values; };

struct __attribute__((packed)) PackedCloneBatch { s32 n; void* buf; };

void* AllocateFrontMemory(s32 size);
void* CreateObjectCopy(void* a, void* b, void* c);

void* GetLevelEntryByKey(void* obj);

s32 HasStreamVoice(void);
void SetTintBlendColliderState(void* self, s32 flag);

void GetStateWalkerCurrentKey(void* dev, s32* out);
void GetStateWalkerTargetKey(void* dev, s32* out);
void HandleSwitchedColliderNotification(void* self, s32 kind, MessageBody* rec);

struct __attribute__((aligned(16))) CurveSample { s32 v[4]; };
struct __attribute__((packed)) PackedCurveColor { s32 v; };
struct CurveFrame { CurveSample pts[10]; PackedCurveColor c; };

void SampleCurvePoints(void* a0, void* a1, void* a2, void* a3, s32 n, void* out, f32 w0, f32 w1, f32 w2);
void DrawProjectedLine(void* a, void* b, void* c, s32 d, s32 e);

extern u8 g_previousSoundLevel[];

void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
void SendIopSoundLevel(s32 a);

void* AllocateZeroedFrontMemory(u32 n);

s32 IsPadSelectFlagHeld(void* p);

ConeVolume* CreateTypedRecord(s32 a0, World* a1, void* a2, s32 a3, s32 a4);
void SetConeVolumeMode(ConeVolume* p, s32 v);
void SetConeVolumeColor(ConeVolume* p, void* q);
void SetConeVolumeFirstAngle(ConeVolume* p, f32 v);
void SetConeVolumeSecondLevel(ConeVolume* p, f32 v);
void SetConeVolumeSecondAngle(ConeVolume* p, f32 v);
void SetConeVolumeThirdLevel(ConeVolume* p, f32 v);
void SetConeVolumeThirdAngle(ConeVolume* p, f32 v);
void SetConeVolumeDirection(ConeVolume* p, void* q);
void SetConeVolumeRange(ConeVolume* p, void* q);

extern f32 g_gameTime;

void UnlinkContactTable(Contacts03* node, Contacts03** head);
void PushContactTable(Contacts03* node, Contacts03** head);
ContactRow03* UnlinkContactRow(void* owner, Contacts03* h, Contacts03* handle);
void FreePooledContactChain(void* a, Contact03* b);
void ClearRootTries(void* self);
void PushFreeSlot(void* list, void* item);

typedef u64 UQuadword __attribute__((mode(TI)));
struct __attribute__((aligned(16))) ClipPoint { f32 x, y, z, w; };
struct __attribute__((packed)) PackedColor { s32 v; };
struct SegmentEnd { f32 x, y, z; };
struct SegmentFrame { ClipPoint buf[4]; PackedColor tmp; };

extern SegmentEnd g_projectionScale;
extern SegmentEnd g_projectionOffset;

UQuadword TransformVector4(u8* self, UQuadword q);
s32 ClipSegmentToPlanes(ClipPoint* out);
void DrawLineSegment(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, void* tmp, s32 k);

s32 SetPadSelectFlags(s32 bits);

void ClearPadSelectFlags(s32 n);
f32 ArctangentOfRatio(f32 a, f32 b);
void BuildAxisAngleMatrix(const Vec02* t, void* out, f32 x);
void ResolveObjectLinks(void* self, s32 n, void* table);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void SetTintBlendColliderState(void* self, s32 flag);

extern f32 g_gameClock[];
void InitOwnerMessage(OwnerMessage* l, s32 zero, Collider* c);
void FreePooledContactChain(World* a0, Contact03* a1);
// How many copies func_001DCD28 makes of the first object of a class.
struct ClassCopyCount { s32 classId; s32 count; };

StateNotifier* CreateObjectCopy(StateNotifier* node, World* self, void* z);

extern f32 g_gameClock[];

void SetStateWalkerTarget(StateTrigger* h, s32 b);
void BuildAxisAngleMatrix(const Vec02* tab, void* out, f32 v);

u32 GetEntryFlags(void* a);

extern f32 g_gameClock[];

struct ClipPlane { f32 x, y, z, w; };

float D_00275140[4] = {1.0f, 0.0f, -0.75f, 0.0f};
float D_00275150[4] = {0.699999988f, 0.300000012f, 0.0f, 0.0f};
float D_00275160 = 650.0f;
float D_00275164 = 100.0f;
float D_00275168 = -100.0f;
float D_0027516C = 50.0f;
float D_00275170[2] = {-10.0f, 0.0f};
float D_00275178[4] = {250.0f, 0.0f, 1.0f, 4500.0f};
float D_00275188 = 10.0f;
float D_0027518C = 50.0f;
float D_00275190[4] = {0.0f, 45.0f, 0.0f, 0.0f};
float D_002751A0[4] = {0.0f, 2.5f, 0.0f, 0.0f};
float D_002751B0[4] = {0.0f, 7.5f, 0.0f, 0.0f};
float D_002751C0[4] = {0.0f, 4.0f, 0.0f, 0.0f};
float D_002751D0 = 850.0f;
s32 D_002751D4 = 60;
float D_002751D8 = 1.25f;
float D_002751DC = 0.75f;
float D_002751E0[4] = {1.35000002f, 0.0f, -0.349999994f, 0.0f};
float D_002751F0[4] = {1.0f, 1.35000002f, 0.0f, 0.0f};
float D_00275200[4] = {1.5f, 0.0f, -0.5f, 0.0f};
float D_00275210[4] = {1.0f, 1.5f, 0.0f, 0.0f};
float D_00275220[4] = {9000.0f, 0.0f, -9000.0f, 0.0f};
float D_00275230[4] = {0.0f, 9000.0f, 0.0f, 0.0f};
float D_00275240[4] = {1.0f, -1.0f, 0.0f, 0.0f};
f32 D_00275250[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
};
f32 D_00275290[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
ObjectLink D_002752A0[20] = {
    { 4, 0x416, 0x6B0 }, { 4, 0x417, 0x710 }, { 4, 0x418, 0x770 }, { 4, 0x419, 0x7D0 },
    { 0, 0x41A, 0x6B8 }, { 0, 0x41B, 0x718 }, { 0, 0x41C, 0x778 }, { 0, 0x41D, 0x7D8 },
    { 6, 0x41E, 0x6B4 }, { 6, 0x41F, 0x714 }, { 6, 0x420, 0x774 }, { 6, 0x421, 0x7D4 },
    { 0, 0x422, 0x690 }, { 2, 0x428, 0xB28 }, { 2, 0x429, 0xB2C }, { 2, 0x42A, 0xB44 },
    { 2, 0x42B, 0xB4C }, { 0x22, 0x423, 0xB14 }, { 0x20, 0x424, 0xB18 }, { 0x20, 0x425, 0xB1C }
};
float D_00275390 = 1.0f;
f32 D_00275394 = 2.0f;
Vec02 D_002753A0 = { 0.0f, 30.0f, 3.0f, 0.0f };
float D_002753B0[4] = {0.0f, 0.00999999978f, 0.0f, 0.0f};
float D_002753C0[2] = {0.0f, 45.0f};
float D_002753C8 = 15.0f;
float D_002753CC = 90.0f;
float D_002753D0[4] = {0.0f, 0.25f, 0.75f, 0.0f};
float D_002753E0[4] = {0.0f, 0.0f, 1.0f, 0.0f};
float D_002753F0[4] = {0.0f, 0.0f, 1.0f, 0.0f};
float D_00275400[4] = {0.0f, 2.5f, 0.25f, 0.0f};
float D_00275410 = 6000.0f;
float D_00275414 = 11250.0f;
float D_00275418 = 7.0f;
float D_0027541C = 2500.0f;
f32 D_00275420[4] = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 D_00275430[4] = { 0.5f, 1.0f, 0.0f, 0.0f };
f32 D_00275440[2] = { 0.5f, 1.0f };
f32 D_00275448[4] = { 4000.0f, 0.0f, 2.0f, 0.0f };
f32 D_00275458[6] = { 2000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };
f32 D_00275470[4] = { 0.0f, 0.0333333313f, 0.0f, 0.0f };
f32 D_00275480[2] = { 0.0f, 50.0f };
f32 D_00275488 = -10.0f;
f32 D_00275490[4] = { 0.05f, 0.0f, 0.25f, 0.0f };
f32 D_002754A0[4] = { 1.5f, 2.5f, 0.0f, 0.0f };
f32 D_002754B0[4] = { 1000.0f, -0.5f, 0.0f, 0.0f };
f32 D_002754C0[2] = { 0.0f, 625.0f };
ValueRange D_002754C8 = { -1300.0f, 1300.0f };
f32 D_002754D0[3] = { 1125.0f, 0.0f, 0.100000001f };
f32 D_002754DC = 750.0f;
f32 D_002754E0[2] = { 1.0f, 0.0f };
f32 D_002754E8[3] = { 8.0f, 0.0f, 0.25f };
f32 D_002754F4 = 0.7f;
f32 D_002754F8 = 0.5f;
f32 D_00275500[2] = { 0.400000006f, 0.800000012f };
f32 D_00275508[2] = { 0.0500000007f, 0.300000012f };
f32 D_00275510[2] = { 0.100000001f, 0.400000006f };
f32 D_00275518[3] = { 10.0f, 0.0f, 0.100000001f };
f32 D_00275524 = 4000.0f;
Vec02 D_00275530 = { -0.5f, 0.699999988f, 0.0f, 0.0f };
f32 D_00275540[4] = { 1.0f, -0.5f, 0.0f, 0.0f };
f32 D_00275550[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_00275560[4] = { -0.5f, 2.0f, 0.0f, 0.0f };
f32 D_00275570[4] = { 0.5f, 4.0f, 0.0f, 0.0f };
f32 D_00275580[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_00275590[4] = { 1.0f, -0.600000024f, 0.0f, 0.0f };
f32 D_002755A0[2] = { 0.25f, 1.0f };
f32 D_002755A8 = 1.10000002f;
f32 D_002755AC = 1000.0f;
f32 D_002755B0[4] = { 0.5f, 0.25f, 0.0f, 0.0f };
f32 D_002755C0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_002755D0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002755E0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002755F0[2] = { 0.0f, 1.0f };
f32 D_002755F8 = 0.75f;
f32 D_00275600[4] = { 2000.0f, 0.0f, 2000.0f, 0.0f };
f32 D_00275610 = 0.5f;
f32 D_00275614 = 0.00200000009f;
f32 D_00275618 = 800.0f;
f32 D_00275620[4] = { 2000.0f, 0.0f, 0.150000006f, 0.0f };
s32 g_coneVolumeMask[4] = { 1, 0, 0, 0 };
f32 D_00275640[4] = { 0.0f, 255.0f, 255.0f, 0.0f };
f32 D_00275650 = 0;
f32 D_00275654 = 255.0f;
f32 D_00275658 = 240.0f;
f32 D_0027565C = 0;
f32 D_00275660 = 180.0f;
Vec02 D_00275670 = { -0.2f, 0.3f, -1.0f, 0.0f };
f32 D_00275680[4] = { 100.0f, -150.0f, 500.0f, 0.0f };
f32 D_00275690[2] = { 500.0f, 2500.0f };
f32 D_00275698[2] = { 500.0f, 2500.0f };
f32 D_002756A0[4] = { 500.0f, 2500.0f, 0.0f, 0.0f };
ClipPlane D_002756B0[6] = {
    { 1.0f, 0.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f },
    { 0.0f, -1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 1.0f }
};
World* g_currentWorld = 0;
s32 D_00275714 = 0;
s32 D_00275718 = 0;
s32 D_0027571C = 0;
s32 D_00275720 = 0;
s32 D_00275724 = 0;
s32 D_00275728 = 0;

struct RingSource {
    u8 pad00[0x40];
    Vec02 v40;              // 0x40
    u8 pad50[0x30];
    Vec02 v80;              // 0x80
};

typedef void (*RingDrawFn)(void* request);
void DrawPlayerMarkerRing1(void* request);
void DrawPlayerMarkerRing2(void* request);
void DrawPlayerMarkerRing3(void* request);
s32 MaskWorldBitsBySave(void);
void QueueDeferredRequest(DeferredRequest* src);
void SetObjectTreeRecordValue(void* obj, u32 value);
f32 Cosine(f32 x);
extern Rgba4 D_002623E0[];

struct RingClamp {
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

void QueuePlayerMarkerRingDraw(Player* self, RingSource* a, void* b);

s32 GetPlayerRequestPhase(Player* self);

void FinishSwitchedCollider(Player* self);
void SetPlayerState(Player* self, s32 a, s32 b);

void FinishPlayerRequest(Player* self);

f32 ComputeOscillatorDisplacement(void* osc, void* pos, f32 t, s32 a, Vec02* out, s32 b, s32 c);
s32 CollectTreeNodeSpans(void* nodes, void* a, void* b, s32 c, s32 d, void* out);

s32 func_001D6A18(Player* self, Collider* col, Vec02* out);

void SwapInPlayerStandIn(Player* self);

s32 TestStandInMayContact(StandIn* self, s32 value);

void StopStandIn(StandIn* self);

void HandleStandInNotification(StandIn* self, s32 kind, ObjectMessage* ref);

void InitOwnerMessage(OwnerMessage* self, s32 mode, s32 owner);

OutputBuffer* InitOutputBuffer(OutputBuffer* self, s32 handle);

OutputBuffer* InitStringOutputBuffer(OutputBuffer* self, u8* target, s32 capacity);

void DestroyOutputBuffer(OutputBuffer* a0, s32 a1);

s32 AppendToOutputBuffer(OutputBuffer* self, void* src, s32 size);

void FlushOutputBuffer(OutputBuffer* self);

void InitPathFollower(PathFollower* self);

void StartPathFollower(PathFollower* self);

f32 FindNearestValueOutsideSpans(s32 count, ValueRange* spans, f32 x);

void UpdatePathFollowerPace(PathFollower* self);

f32 GetWrappedDifference(f32 x, f32 lim, f32 base);

s32 IsPathFollowerAhead(PathFollower* self, PathFollower* other);

void SteerPathFollower(PathFollower* self);

void CountDownPathFollowerLap(PathFollower* self);

void RecordPathFollowerProgress(PathFollower* self);

void UpdatePathFollower(PathFollower* self, f32 t);

void UpdatePathFollowerScreenElements(PathFollower* self);

void ReleasePathFollowerContacts(PathFollower* self);

struct DrawScale {
    u8 pad00[0x40];
    f32 f40;
};

void DrawCollider(Collider* self, void* a, void* m);
void BuildPlacedObjectTransform(void* obj, void* c, void* out);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);
void BuildMatrixFromRotationAndTranslation(void* pos, void* rot, void* out);
void func_001268B8(void* world, void* a1, void* a2, void* a3, f32 a, f32 b);

void DrawPathFollower(PathFollower* self, void* a, DrawScale* b);

void UpdatePathFollowerBounds(PathFollower* self);

void StartPathFollowerEffect(PathFollower* self, void* a, void* b);

void FindPathFollowerPathPosition(PathFollower* self);

void RecomputePathFollowerFrame(PathFollower* self);

void CapturePathFollowerPose(void);

void HandlePathFollowerActivation(PathFollower* self, void* v);

void HandlePathFollowerNotification(PathFollower* self, s32 code, CountedNotice* rec);

void SetPathFollowerPath(PathFollower* self, PathCurveObject* arg);

void SetPathFollowerSecondPath(u8* self, PathCurveObject* obj);

void AddPathFollowerEntry(PathFollower* self, void* item);

void AddPathFollowerActiveEntry(PathFollower* self, s32 a, s32 b, s32 c, f32 x, f32 y);

void SetPathFollowerMode(PathFollower* self, s32 mode);

void ResetPathFollower(PathFollower* self);

void InitWorldHashLists(u8* self);

void InitWorldPools(World* self);

void ResetWorldSubsystems(s32 a0);

void ReadBufferedBlockHeader(s32 a0, BufferedStream* self);

void ReadBufferedBlockBody(BufferedStream* self);

void SetCachedVoiceParamBuiltin(void* self, void* a, void* b);

s32 GetCachedVoiceParamBuiltin(s32 unused, VoiceParamIndex index);

void* RefreshCachedVoiceParamBuiltin(void* unused, void* a1, void* a2);

s32 IsWorldBodyLimitReached(World* self, BaseObject* obj, u32 value);

void* TakeAttachRecord(u8* self);

void ReleaseAttachRecords(u8* self, Attach03* node);

void* TakeCallRecord(u8* self);

void ReleaseCallRecords(u8* self, T219CHook* node);

QueuedCall* AppendQueuedCall(World* self, s32 a, s32 b, s32 c, s32 d);

void AppendQueuedCallOnce(World* self, s32 a1, s32 a2, s32 a3, s32 a4);

QueuedCall* AppendQueuedCall(World* self, s32 a, s32 b, s32 c, s32 d);

void RemoveQueuedCalls(World* self, u32 mask, s32 k0, s32 k1, s32 k2, s32 k3);

void RunQueuedCalls(World* self);

void RunDueDelayedScriptCalls(World* self, f32 limit);

void* AllocateTouchNode(u8* self);

void FreeTouchNodes(u8* owner, Touch03* node);

void PushCloneBatch(World* self, void* src, s32 n);

s32 PopSpawnedClone(World* self, s32 index);

void UnlinkContactTable(Contacts03* a0, Contacts03** a1);

void InitContactTables(World* self);

void PushContactTable(Contacts03* node, Contacts03** head);

Contacts03* TakeContactTable(World* owner, Collider* self);

void ReleaseContactTable(World* owner, Contacts03* handle);

void CreateConeVolumes(World* self);

void SkipBufferedBlocks(void* self);

void SpawnListedObjectCopies(World* self);

void ResetScatterController(void* scatter);
void InitScriptValuePools(void);
s32 ReadBufferedU8(BufferedStream* s);
s32 ReadBufferedS16(BufferedStream* s);
void SkipBufferedBlocks(BufferedStream* s);
void LoadScriptEntryTable(World* self, BufferedStream* s);
void ReadPropertyRecords(void* self, BufferedStream* s);
void ReadOptionalBufferedBlock(BufferedStream* s, void* out);
void ReadBufferedString(BufferedStream* s, void* out);
void LoadScreenResources(BufferedStream* s);
void ReadSlotObjects(World* self, BaseObject* parent, BufferedStream* s);
void ReadBufferedBlockBody(BufferedStream* s);
void EnsureSoundBankLoaded(s32 bank);
void SilenceVolumeChannel2(void);
void RequestStagedBank(s32 bank);
void SendResidentImages(void);
s32 IsListEmpty(List01* list);
void CreateConeVolumes(World* self);
extern u8 D_002BDC20[];
void FillScreenColor(void* screen, Rgba4* color, s32 a);
void SpawnListedObjectCopies(World* self);
void RunQueuedCalls(World* self);
void UpdateScatterLevelLimits(void* scatter);
void ResumeElementStackState(void* stack);
void UpdateCameraLocation(Camera* camera);
void UpdateWorldContacts(World* self, s32 a);
void PlayStagedBank(s32 bank);
void StartWorldSoundEntries(World* self);

void LoadWorld(World* self, BufferedStream* s)
{
    Rgba4 color;
    ListFrame walk;
    ListFrame frame;
    s32 i;
    ResetScatterController(g_scatterController);
    InitScriptValuePools();
    D_00275714 = ReadBufferedU8(s);
    self->f1D70 = ReadBufferedS16(s);
    SkipBufferedBlocks(s);
    g_camera = (Camera*)CreateTypedRecord(0x6D, self, 0, 4, -1);
    for (i = 9; i >= 0; i--) {
        BaseObject* o = (BaseObject*)CreateTypedRecord(0x1E, self, 0, 0xA, -1);
        o->desc->m03(o);
    }
    for (i = 0x27; i >= 0; i--) {
        BaseObject* o = (BaseObject*)CreateTypedRecord(0x4D, self, 0, 0xB, -1);
        o->desc->m03(o);
    }
    LoadScriptEntryTable(self, s);
    ReadPropertyRecords(self, s);
    ReadOptionalBufferedBlock(s, &self->f2310);
    ReadBufferedString(s, &self->f2314);
    ReadOptionalBufferedBlock(s, &self->f1D74);
    LoadScreenResources(s);
    ReadSlotObjects(self, 0, s);
    ReadBufferedBlockBody(s);
    if (self->f1D70 >= 0) {
        EnsureSoundBankLoaded(self->f1D70);
    }
    if (self->f1D78 == 0) {
        SilenceVolumeChannel2();
    }
    RequestStagedBank(self->f1D74);
    SendResidentImages();
    if (IsListEmpty(&self->list1BE8) != 0) {
        CreateConeVolumes(self);
    }
    self->f1D67 = 0x80;
    color = self->color1D64;
    FillScreenColor(D_002BDC20, &color, 0);
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
    frame.prev = g_activeListFrames;
    frame.offset = list->offset;
    g_activeListFrames = &frame;
    BaseObject* h = (BaseObject*)list->head;
    frame.link = (u8*)h + frame.offset;
    while (h != 0) {
        h->desc->m10(h);
        BaseObject* nx = *(BaseObject**)frame.link;
        frame.link = (u8*)nx + frame.offset;
        h = nx;
    }
    g_activeListFrames = frame.prev;
    RunQueuedCalls(self);
    UpdateScatterLevelLimits(g_scatterController);
    ResumeElementStackState(g_elementStack);
    if (g_mapScreenList.current == 0 && g_saveData->f19D8 != 0) {
        AllocateZeroedFrontMemory(0x80000);
    }
    UpdateCameraLocation(g_camera);
    UpdateWorldContacts(self, 0);
    PlayStagedBank(self->f1D74);
    StartWorldSoundEntries(self);
}
