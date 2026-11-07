// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1D62E0 to 0x1DDCE0: classes 0x07 and 0x3F, the output buffer, class 0x19, the world
// (class 0x6C) and its script functions. Its .data runs from 0x275140 to the zeroed globals
// D_00275710 (g_currentWorld) to D_00275728 that close it; its .rodata is the "%s" of
// func_001D72C8, the float of func_001D8470 and the pairs of func_001DCD28. One file between
// two edges with no evidence inside it: it could be several.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
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

INCLUDE_ASM(func_001D62E0);

s32 GetPlayerRequestPhase(Player* self)
{
    if (self->f2220 != 4) {
        return self->f26C4 != 0;
    }
    if (self->f2228 < 45) {
        return 1;
    }
    return 2;
}

INCLUDE_ASM(func_001D6608);

INCLUDE_ASM(func_001D66A8);

f32 ComputeOscillatorDisplacement(void* osc, void* pos, f32 t, s32 a, Vec02* out, s32 b, s32 c);
s32 CollectTreeNodeSpans(void* nodes, void* a, void* b, s32 c, s32 d, void* out);

s32 func_001D6A18(Player* self, Collider* col, Vec02* out)
{
    Vec02 moved;
    Vec02 shift;
    Vec02 start;
    Vec02 end;
    ColliderSpan hit;
    if (col->f278 != 0) {
        ComputeOscillatorDisplacement(((void**)col->f278)[3], &self->v140, 50.0f, 0, &moved, 0, 0);
        Vu0::Q(shift) = Vu0::Sub(Vu0::Q(moved), Vu0::Q(self->v140));
    } else {
        shift = D_00248D30;
    }
    u128 base = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(shift));
    Vu0::Q(end) = base;
    Vu0::Q(start) = base;
    end.z += D_00275164;
    start.z += D_00275168;
    if (CollectTreeNodeSpans(col->tree.nodes, &end, &start, 0, 1, &hit) == 0) {
        return 0;
    }
    Vu0::Q(*out) = Vu0::Add(Vu0::Q(hit.q[0]), Vu0::Q(shift));
    return 1;
}

INCLUDE_ASM(func_001D6B18);

void SwapInPlayerStandIn(Player* self)
{
    StandIn* obj = (StandIn*)self->f1518;
    if (obj != 0) {
        BaseObject* s0 = 0;
        u32 i = 0;
        while (i < 4) {
            s0 = (BaseObject*)self->f1508[i];
            if (s0 != 0 && IsObjectAttached(s0) != 0) {
                break;
            }
            i++;
        }
        if (i >= 4) {
            s0 = (BaseObject*)self->f1504;
        }
        obj->desc->m02(obj);
        ((VFnB)((void**)obj->desc)[25])(obj, 0);
        ((VFnB)((void**)obj->desc)[35])(obj, s0);
        obj->f690 = g_gameClock[1];
        obj->f694 = 1;
        if (s0 != self->f1504) {
            s0->desc->m03(s0);
        }
    }
}

s32 TestStandInMayContact(StandIn* self, s32 value)
{
    if (value == (s32)g_player) {
        return 1;
    }
    return TestCollidersMayContact(self, value);
}

INCLUDE_ASM(func_001D6DD8);

void StopStandIn(StandIn* self)
{
    HandleChildGroupObjectContact(self);
    self->f694 = 0;
}

void HandleStandInNotification(StandIn* self, s32 kind, ObjectMessage* ref)
{
    HandleChildGroupNotification(self, kind, ref);
    if (kind == 10 && ref->target == self) {
        ((StandIn*)ref->target)->f694 = 0;
    }
}

void InitOwnerMessage(OwnerMessage* self, s32 mode, s32 owner) { FillMemory(self, 0, 0x10); self->owner = owner; self->mode = mode; self->c = owner; }

ASM_FUNC(func_001D70E8);

OutputBuffer* InitOutputBuffer(OutputBuffer* self, s32 handle)
{
    self->handle = handle;
    self->targetWord = 0;
    self->capacity = 0;
    self->used = 0;
    self->count = 0;
    self->pending = 0;
    return self;
}

OutputBuffer* InitStringOutputBuffer(OutputBuffer* self, u8* target, s32 capacity) { self->target = target; self->capacity = capacity; self->used = 0; self->handle = -1; self->count = 0; self->pending = 0; return self; }

void DestroyOutputBuffer(OutputBuffer* a0, s32 a1)
{
    FlushOutputBuffer(a0, a1);
    if (a1 & 1) FreeObjectMemory(a0);
}

s32 AppendToOutputBuffer(OutputBuffer* self, void* src, s32 size)
{
    s32 n = size;
    s32 done = 0;

    if (self->target != 0 && self->capacity != 0 && n != 0) {
        s32 avail = self->capacity - self->used;
        if (avail < n) {
            n -= avail;
        }
    }
    if (n == 0) {
        return 0;
    }
    if (self->target != 0) {
        CopyMemory(self->target + self->used, src, n);
        self->used += n;
        done = n;
    } else if (n > 0) {
        do {
            s32 room = 0x400 - self->pending;
            s32 rem = n - done;
            s32 take = (room < rem) ? room : rem;
            if (take != 0) {
                CopyMemory((u8*)self + (self->pending + 0x18), (u8*)src + done, take);
                done += take;
                self->pending += take;
            }
            if (self->pending == 0x400) {
                FlushOutputBuffer(self);
            }
        } while (done < n);
    }
    self->count += done;
    return n;
}

void FlushOutputBuffer(OutputBuffer* self)
{
    u8 buf[0x90];
    s32 done;
    u8* p;
    s32 chunk;
    s32 rem;

    if (self->pending == 0) {
        return;
    }
    if (self->targetWord != 0) {
        return;
    }
    if (self->handle < 0) {
        p = self->buf;
        for (done = 0; done < self->pending; done += chunk) {
            rem = self->pending - done;
            chunk = 0x80;
            if (!(rem > 0x7F)) {
                chunk = rem;
            }
            CopyMemory(buf, p, chunk);
            p += chunk;
            buf[chunk] = 0;
            PrintBuffered((void*)"%s", buf);
        }
    } else {
        WriteFile(self->handle, self->buf, self->pending);
    }
    self->pending = 0;
}

void InitPathFollower(PathFollower* self)
{
    InitSwitchedCollider(self);
    self->f614 = 50.0f;
    self->f610 = 50.0f;
    self->f618 = 3000.0f;
    self->f61C = 1300.0f;
    self->f868 = 2.0f;
    self->fB04 = 3;
    (*(Quad16*)&self->v620) = *(Quad16*)D_00275290;
    CopyMemory(self->f630, D_00275250, 0x40);
    ResetPathFollower(self);
}

void StartPathFollower(PathFollower* self)
{
    BaseObject* buf[16];
    s32 id0;
    s32 id1;
    s32 id2;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x14, D_002752A0);
    self->f694 = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    if (self->fB44 != 0) {
        StateTrigger* v = CreateStateWalker(self->fB44, self, -1, 0);
        self->fB48 = v;
        SetStateWalkerTarget(v, self->fB30 == 1 ? 0x484 : 0x384);
    }
    switch (g_currentWorld->f1D70) {
    case 3:
        id0 = self->f550 ? 0x1D2 : 0x1AD;
        id1 = 0x1BB;
        id2 = 0x1AF;
        goto spawn;
    case 5:
        id0 = self->f550 ? 0x2A6 : 0x280;
        id1 = 0x27F;
        id2 = 0x27D;
        goto spawn;
    case 6:
        id0 = self->f550 ? 0x2DE : 0x2DC;
        id1 = 0x2DB;
        id2 = 0x2DD;
    spawn:
        StartSoundEffect(id0, self->fB80, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id1, self->fB84, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id2, self->fB7C, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        {
            f32 r = RandomFloatInRange(-0.1f, 0.1f);
            self->fB8C = self->fB90 = self->fB94 = self->fB98 = r;
        }
        break;
    default:
        break;
    }
    {
        void* c = FindFirstObjectById(g_currentWorld, 0x104, 7, self);
        if (c != 0) {
            self->f594 = 200.0f;
            self->fB78 = c;
            self->f598 = c;
        }
    }
    if (self->fB30 == 1) {
        s32 n = GatherObjectsByMode(self->world, 0x105, 0x426, 0, 0x10, buf);
        for (s32 i = 0; i < n; i++) {
            buf[i]->desc->m17(buf[i], self);
        }
        T217D_E30* boxA = &D_00272430;
        T217D_E30* boxB = &D_002726B0;
        ((U32P*)&boxA->own)->v = 0;
        ((U32P*)&boxB->own)->v = 0;
        boxA->target = &boxA->own;
        boxB->target = &boxB->own;
    }
    for (s32 k = 0; k < 4; k++) {
        Slot19* s = &self->f6B0[k];
        s->v10 = s->obj->pos;
    }
    ResetPathFollower(self);
}

INCLUDE_ASM(func_001D7778);

f32 FindNearestValueOutsideSpans(s32 count, ValueRange* spans, f32 x)
{
    if (IsInsideAnyRange(count, spans, x) == 0) {
        return x;
    }
    f32 bestDist = 3.4028234663852886e+38f;
    f32 best = bestDist;
    if (count > 0) {
        ValueRange* s = spans;
        s32 n = count;
        do {
            f32 d = __builtin_fabsf(x - s->lo);
            if (d < bestDist) {
                if (IsInsideAnyRange(count, spans, s->lo) == 0) {
                    best = s->lo;
                    bestDist = d;
                }
            }
            d = __builtin_fabsf(x - s->hi);
            if (d < bestDist) {
                if (IsInsideAnyRange(count, spans, s->hi) == 0) {
                    best = s->hi;
                    bestDist = d;
                }
            }
            s++;
            n--;
        } while (n != 0);
    }
    return best;
}

void UpdatePathFollowerPace(PathFollower* self)
{
    if (self != GetActiveSwitchedCollider()) {
        self->f85C = ApproachValueWithRamp((u8*)D_00275490, 0, self->f85C, self->f860, g_gameClock[2]);
        if (!(g_gameClock[1] < self->f864)) {
            f32 one = 1.0f;  // hoisted: retail holds 1.0f in $f3 before the multiply
            s32 idx = 3 * (self->fB00 - 1) + self->fAF8->index;
            f32 t = (f32)idx * 0.1f;
            f32 w;
            if (t < 0.0f) {
                w = 0.0f;
            } else if (one < t) {
                w = one;
            } else {
                w = t;
            }
            f32 val = ((QuadraticCurve*)&self->f670)->Eval(w);
            f32 lo = self->f680;
            f32 hi = self->f684;
            if (val < lo) {
                val = lo;
            } else if (hi < val) {
                val = hi;
            }
            self->f860 = val;
            f32 r = RandomFloatInRange(-0.05f, 0.05f);
            self->f860 = self->f860 + r;
            f32 r2 = RandomFloatInRange(D_002754A0[0], D_002754A0[1]);
            self->f864 = g_gameClock[1] + r2;
        }
    }
}

f32 GetWrappedDifference(f32 x, f32 lim, f32 base)
{
    f32 d = lim - base;
    if (x * 0.5f < d)
        d = d - x;
    else if (d < x * -0.5f)
        d = d + x;
    return d;
}

s32 IsPathFollowerAhead(PathFollower* self, PathFollower* other)
{
    s32 d = self->fB00 - other->fB00;
    if (d > 0) return 1;
    if (d < 0) return 0;
    d = self->fAF8->index - other->fAF8->index;
    if (d > 0) return 1;
    if (d < 0) return 0;
    f32 r = GetWrappedDifference(self->f834, self->f83C, other->f83C);
    return 0.0f < r;
}

INCLUDE_ASM(func_001D87C8);

INCLUDE_ASM(func_001D8BD0);

void SteerPathFollower(PathFollower* self)
{
    f32 a = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 b = WrapAngle(self->f694 - a);
    f32 c = ClampToMagnitude(D_002754F8 * b, D_002754F4);
    self->f69C = ApproachAngleWithRamp((u8*)D_002754E8, 0, self->f69C, c, g_frameDt);
    for (u32 i = 0; i < 4; i++) {
        Slot19* s = &self->f6B0[i];
        if ((s32)i < 2) {
            s->f50 = self->f698 / self->f610;
        } else {
            s->f50 = self->f698 / self->f614;
        }

    }
}

INCLUDE_ASM(func_001D8E40);

void CountDownPathFollowerLap(PathFollower* self)
{
    self->f854 = g_gameTime;
    self->f858 = self->f858 - 1;
    BaseObject* s = self->fB14;
    if (s != 0) {
        s->desc->m02(s);
    }
}

void RecordPathFollowerProgress(PathFollower* self)
{
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    s32 idx = self->fB00 - 1;
    f32 f = (f32)(idx * 3 + self->fAF8->index) * 0.1f;
    if (f < lo) {
        f = lo;
    } else if (hi < f) {
        f = hi;
    }
    s32 s0 = self->fB0C - self->fB08;
    s32 t = 0;
    if (s0 >= 3) {
        s32 mk = 1 << (s0 & 7);
        t = g_currentEntry->bits74[s0 / 8] & mk;
    }
    if (s0 < 3 || t) {
        RaiseScatterLevels(g_scatterController, f);
    }
    if (s0 >= 0) {
        do {
            G27C230* g = g_currentEntry;
            u8* bb = g->bits74;
            u8* byte = bb + s0 / 8;
            s32 mask = 1 << (s0 & 7);
            if ((*byte & mask) == 0) {
                *byte = (u8)(*byte | mask);
                g->count70++;
            }
            s0--;
        } while (s0 >= 0);
    }
}

INCLUDE_ASM(func_001D9488);

INCLUDE_ASM(func_001D9678);

INCLUDE_ASM(func_001D9AC8);

void UpdatePathFollower(PathFollower* self, f32 t)
{
    s32 local = 0;
    UpdateSwitchedCollider(self, t);
    if (self->fB34 != 1) {
        if (self->fB34 < 2) {
            if (self->fB34 == 0) {
                self->f698 = 0;
            }
        }
    } else {
        UpdatePathFollowerPace(self);
        AdvancePathFollowerAlongPath(self, &local);
        ComputePathFollowerHeadingTarget(self);
    }
    UpdatePathFollowerSound(self, t);
    SteerPathFollower(self);
    func_001D8E40(self);
    AdvancePathFollowerEntry(self, local);
    ProcessPathFollowerContacts(self);
    if (self->rot.r[2].z > 0.5f) {
        self->f850 = g_gameTime;
    }
    if (self->fB34 != 0) {
        ClearRootTries(self);
    }
}

INCLUDE_ASM(func_001D9D78);

void UpdatePathFollowerScreenElements(PathFollower* self)
{
    s32 a = 0;
    s32 b = 0;
    switch (self->fB30) {
    case 0: {
        WalkerHolder* r = (WalkerHolder*)FindFirstObjectById(self->world, 5, 0x42C, 0);
        if (r != 0) {
            void* dev = r->f48;
            s32 code;
            GetStateWalkerTargetKey(dev, &code);
            if (code == -1) {
                GetStateWalkerCurrentKey(dev, &code);
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
        D_0026D5C8.vt->m14(&D_0026D5C8);
        D_0026DAC8.vt->m14(&D_0026DAC8);
    } else {
        D_0026D848.vt->m15(&D_0026D848);
        D_0026D5C8.vt->m15(&D_0026D5C8);
        D_0026DAC8.vt->m15(&D_0026DAC8);
    }
    if (b != 0) {
        D_00272430.vt->m14(&D_00272430);
        D_002726B0.vt->m14(&D_002726B0);
    } else {
        D_00272430.vt->m15(&D_00272430);
        D_002726B0.vt->m15(&D_002726B0);
    }
}

void ReleasePathFollowerContacts(PathFollower* self) { self->f6A0++; }

INCLUDE_ASM(func_001DA320);

ASM_FUNC(func_001DA6E0);

INCLUDE_ASM(func_001DA7E0);

INCLUDE_ASM(func_001DAA18);

void UpdatePathFollowerBounds(PathFollower* self)
{
    u32 i;
    Quad16 q;
    UpdateColliderBounds(self);
    for (i = 0; i < 4; i++) {
        Slot19* slot = &self->f6B0[i];
        if (slot->obj != 0) {
            f32 f;
            q = *(Quad16*)&slot->obj->v190;
            TransformPointBetweenFrames(self, 0, &q, &q);
            f = ((s32)i < 2) ? self->f610 : self->f614;
            ExpandColliderBoundsBySphere(self, &q, f);
        }
    }
}

void StartPathFollowerEffect(PathFollower* self, void* a, void* b)
{
    if (((FollowerEffectTarget*)self->fB78) != 0) {
        SetAgentMainClip(((FollowerEffectTarget*)self->fB78), 0);
        FollowerEffectTarget* t = ((FollowerEffectTarget*)self->fB78);
        t->vtbl[82](t, a, b);
    } else {
        StartSwitchedColliderEffect(self, a, b);
    }
}

INCLUDE_ASM(func_001DAD28);

void RecomputePathFollowerFrame(PathFollower* self)
{
    RecomputeColliderFrame(self);
    FindPathFollowerPathPosition(self);
}

void CapturePathFollowerPose(void)
{
    CaptureColliderPose();
}

void HandlePathFollowerActivation(PathFollower* self, void* v)
{
    HandleSwitchedColliderActivation(self, v);
    if (v != 0) {
        T217D_E30* a = &D_0026D5C8;
        *(void**)(D_0026DAAC) = (u8*)self + 0x858;
        T217D_E30* b = &D_0026DAC8;
        a->target = (s32*)((u8*)self + 0xB00);
        a->limit = (s32*)((u8*)self + 0xB04);
        b->target = (s32*)((u8*)self + 0xB08);
        b->limit = (s32*)((u8*)self + 0xB0C);
        SetWorldActiveFollower(*(void**)((u8*)self + 0x14), self);
    } else {
        if (self->fB34 == 2) {
            SetPathFollowerMode(self, 0);
        }
    }
}

void HandlePathFollowerNotification(PathFollower* self, s32 code, CountedNotice* rec)
{
    HandleSwitchedColliderNotification(self, code, rec);
    if (code == 0xE && rec->kind == 0x426) {
        T217D_E30* a = &D_00272430;
        s32 lim = D_002751D4;
        if (a->own < lim) {
            T217D_E30* b = &D_002726B0;
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

void SetPathFollowerPath(PathFollower* self, PathCurveObject* arg)
{
    self->f830 = arg;
    PathCurve* o = arg->curve;
    if (o->vt->m10) o->vt->m10(o, (u8*)self + 0x100, 0, 0, 0, (f32*)((u8*)self + 0x838), 0);
    FindPathFollowerPathPosition(self);
    self->f844 = self->f840;
    self->f834 = self->f830->curve->vt->m08(self->f830->curve);
    for (s32 i = 0; i < self->f870; i++) {
        PathMarker* e = &self->f874[i];
        if (e->kind == 0) {
            s32 loc[4];
            GetObjectWorldPosition(e->item, loc);
            PathCurve* o2 = self->f830->curve;
            if (o2->vt->m10) o2->vt->m10(o2, loc, 0, 0, 0, 0, &e->pathLength);
        }
    }
}

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

void AddPathFollowerEntry(PathFollower* self, void* item)
{
    if (item == 0) {
        return;
    }
    s32 n = self->f870;
    if ((u32)n >= 16) {
        return;
    }
    self->f870 = n + 1;
    PathMarker* e = &self->f874[n];
    e->item = item;
    e->kind = 0;
    if (self->fAF4 == 0) {
        self->fAF8 = e;
        self->fAF4 = e;
        e->next = e;
    } else {
        e->next = self->fAF4->next;
        self->fAF4->next = e;
        e->index = e->next->index + 1;
    }
    if (self->f830 != 0) {
        Quad16 tmp;
        GetObjectWorldPosition(item, &tmp);
        PathCurve* o = self->f830->curve;
        void (*fn)(PathCurve*, void*, void*, void*, void*, f32*, f32*) = o->vt->m10;
        if (fn != 0) {
            fn(o, &tmp, 0, 0, 0, 0, &e->pathLength);
        }
    }
}

void AddPathFollowerActiveEntry(PathFollower* self, s32 a, s32 b, s32 c, f32 x, f32 y) { if (a && (u32)self->f870 < 16) { PathMarker* e = &self->f874[self->f870]; self->f870++; e->item = (void*)a; e->kind = 1; e->x = x; e->y = y; e->b = b; e->c = c; } }

void SetPathFollowerMode(PathFollower* self, s32 mode)
{
    if (mode != self->fB34) {
        *(s32*)((u8*)self + 0xB34) = mode;
        *(f32*)((u8*)self + 0xB38) = g_gameTime;
        if (mode == 2 && self != GetActiveSwitchedCollider()) {
            ActivateSwitchedCollider(self);
        }
    }
}

void ResetPathFollower(PathFollower* self)
{
    self->fB00 = 1;
    self->fAF8 = self->fAF4;
    self->f858 = 0;
    self->f854 = -10.0f;
    self->f864 = -10.0f;
    self->f86C = -10.0f;
    self->fB10 = -10.0f;
    G27C230* rec = g_currentEntry;
    f32 t = ((QuadraticCurve*)&self->v620)->Eval(rec->dt);
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
    u8* p630 = self->v630;
    u8* p650 = self->v650;
    u8* p670 = self->v670;
    Quadword a, b, c, d;
    Quadword a2, b2, c2, d2;
    StoreFloatAsQuadword(&a, y);
    a2 = a;
    CopyQuadword(&b, p630);
    b2 = b;
    StoreFloatAsQuadword(&c, x);
    c2 = c;
    CopyQuadword(&d, p650);
    d2 = d;
    StoreQuadword(p670, AddWeightedVectors(a2, b2, c2, d2));
    ((BlendRange*)&self->f680)->Blend(y, *(BlendRange*)&self->f640, x, *(BlendRange*)&self->f660);
    f32 r = ((RangeClamp*)&self->f680)->Clamp(*(f32*)p670);
    self->f860 = r;
    self->f85C = r;
}

ASM_FUNC(func_001DB448);

ASM_FUNC(func_001DB460);

void InitWorldHashLists(u8* self)
{
    u32 i;
    for (i = 0; i < 0x200; i++) {
        SetListLinkOffset(self + 0x84 + i * 0xC, 0xC);
    }
}

void InitWorldPools(World* self)
{
    f32 x;
    InitObject(self);
    SetIopChannel2Setting(self, 0, 0);
    self->buf1AD8 = (void*)AllocateFrontMemory(0x4800);
    self->buf1ADC = AllocateZeroedFrontMemory(0x10000);
    InitContactTables(self);
    InitSlotPool(SUB(0x1AF0), 0x10, 0x400);
    InitSlotPool(SUB(0x1AFC), 0xE0, 0x100);
    InitSlotPool(SUB(0x1B08), 0x10, 0x80);
    InitSlotPool(SUB(0x1B14), 0x14, 0x400);
    InitSlotPool(SUB(0x1B2C), 0x140, 0x180);
    InitAlignedSlotPool(SUB(0x1B40), 0x10C0, 0x80);
    InitSlotPool(SUB(0x1B4C), 0x580, 0x20);
    InitSlotPool(SUB(0x1B58), 0xEC, 0x100);
    InitSlotPool(SUB(0x1B20), 0xD0, 0x400);
    InitSlotPool(SUB(0x1BA0), 0x90, 0x80);
    InitSlotPool(SUB(0x1BB8), 0xC, 0x20);
    InitSlotPool(SUB(0x1B88), 0x40, 0x100);
    InitSlotPool(SUB(0x1BF4), 0x2E0, 0x20);
    InitSlotPool(SUB(0x1BD0), 0x70, 0x20);
    InitSlotPool(SUB(0x1C0C), 0x8, 0x80);
    InitSlotPool(SUB(0x1C18), 0x14, 0x100);
    self->regroupObjects = (PlacedObject**)AllocateFrontMemory(0x1000);
    SetListLinkOffset(SUB(0x48), 0x1C);
    SetListLinkOffset(SUB(0x54), 0x48);
    SetListLinkOffset(SUB(0x78), 0x48);
    SetListLinkOffset(SUB(0x60), 0x40);
    SetListLinkOffset(SUB(0x6C), 0x414);
    SetListLinkOffset(SUB(0x3C), 0x2D0);
    SetListLinkOffset(SUB(0x1B64), 0x34);
    SetListLinkOffset(SUB(0x1B70), 0x34);
    SetListLinkOffset(SUB(0x1B7C), 0x34);
    SetListLinkOffset(SUB(0x1B94), 0x10);
    SetListLinkOffset(SUB(0x1BAC), 0x64);
    SetListLinkOffset(SUB(0x1BC4), 0x4);
    SetListLinkOffset(SUB(0x1BE8), 0x410);
    SetListLinkOffset(SUB(0x1C00), 0xB8);
    SetListLinkOffset(SUB(0x1BDC), 0x64);
    SetListLinkOffset(SUB(0x1C3C), 0x2DC);
    SetListLinkOffset(SUB(0x1C48), 0x5DC);
    SetListLinkOffset(SUB(0x1C54), 0x374);
    SetListLinkOffset(SUB(0x1C60), 0x600);
    SetListLinkOffset(SUB(0x1C6C), 0x90);
    SetListLinkOffset(SUB(0x1C78), 0x56C);
    SetListLinkOffset(SUB(0x1C84), 0x50);
    SetListLinkOffset(SUB(0x1C90), 0x38);
    SetListLinkOffset(SUB(0x1C9C), 0x38);
    SetListLinkOffset(SUB(0x1CA8), 0xAF0);
    SetListLinkOffset(SUB(0x1CB4), 0x630);
    SetListLinkOffset(SUB(0x1CC0), 0x630);
    SetListLinkOffset(SUB(0x1C24), 0xC);
    SetListLinkOffset(SUB(0x1C30), 0xC);
    SetListLinkOffset(SUB(0x1CCC), 0xC10);
    SetListLinkOffset(SUB(0x1CD8), 0x34);
    x = -1500.0f;
    if (g_buttonCodeFlags & 4) {
        x = -900.0f;
    }
    SetWorldGravityZ(self, x);
    self->f1D64 = 0x10;
    self->f1D65 = 0x10;
    self->f1D66 = 0x40;
    self->f1D68 = 50.0f;
    self->f1D70 = -1;
    self->f1D74 = 0;
    self->f2308 = 15.0f;
    self->f230C = 180.0f;
    self->f234C = 1.0f;
    self->f2350 = 1.0f;
    self->f2354 = 1;
    self->f235C = 0xF03FFFFF;
}

void ResetWorldSubsystems(s32 a0)
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
        ResetElementStack(g_elementStack);
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

void ReadBufferedBlockHeader(s32 a0, BufferedStream* self)
{
    s32 s2 = a0;
    s32 s3;
    s32 s0;
    if (self->mode == 1) {
        if (s2 == 0) {
            ReduceBufferedStreamBytesLeft(self, D_00275728);
            self->f14 -= D_00275728;
        }
        s3 = ReadBufferedS32(self);
        s0 = ReadBufferedS32(self);
    } else {
        s3 = ReadBufferedS32(self);
        s0 = ReadBufferedS32(self);
        if (s0 != D_00275724) s2 = 1;
        if (s2 == 0) {
            s32 v = self->f14 - D_00275728;
            self->f14 = (s2 < v) ? v : 0;
        }
    }
    s32 r = (s32)AllocateFrontMemory(s3);
    D_00275724 = s0;
    D_00275720 = s3;
    D_00275718 = r;
    D_0027571C = s2;
}

void ReadBufferedBlockBody(BufferedStream* self)
{
    if (D_0027571C != 0) {
        D_00275728 = self->f14;
        AlignBufferedStreamPosition(self, 0x10);
        ReadBufferedStreamBytes(self, D_00275720, D_00275718);
    }
}

INCLUDE_ASM(func_001DBA90);

void SetCachedVoiceParamBuiltin(void* self, void* a, void* b)
{
    SetCachedVoiceParam(a, b);
}

s32 GetCachedVoiceParamBuiltin(s32 unused, VoiceParamIndex index)
{
    return GetCachedVoiceParam(index);
}

void* RefreshCachedVoiceParamBuiltin(void* unused, void* a1, void* a2)
{
    return RefreshCachedVoiceParam(a1, a2);
}

s32 IsWorldBodyLimitReached(World* self, BaseObject* obj, u32 value) { return (obj->desc->flags & 2) && self->count38 >= 0xF7 && value == 0; }

void* TakeAttachRecord(u8* self)
{
    void* p = TakePoolSlot(self + 0x1B08);
    FillMemory(p, 0, 16);
    return p;
}

void ReleaseAttachRecords(u8* self, Attach03* node)
{
    if (node) {
        do {
            Attach03* next = node->nextOwn;
            PushFreeSlot(self + 0x1B08, node);
            node = next;
        } while (node);
    }
}

void* TakeCallRecord(u8* self)
{
    void* p = TakePoolSlot(self + 0x1B14);
    FillMemory(p, 0, 0x14);
    return p;
}

void ReleaseCallRecords(u8* self, T219CHook* node)
{
    while (node != 0) {
        T219CHook* next = node->next;
        PushFreeSlot(self + 0x1B14, node);
        node = next;
    }
}

QueuedCall* AppendQueuedCall(World* self, s32 a, s32 b, s32 c, s32 d);

void AppendQueuedCallOnce(World* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    QueuedCall* n = self->f1EC8;
    if (n != 0) {
        do {
            if (n->k0 == a1 && n->k1 == a2 && n->k2 == a3 && n->k3 == a4) {
                return;
            }
            n = n->next;
        } while (n != 0);
    }
    AppendQueuedCall(self, a1, a2, a3, a4);
}

QueuedCall* AppendQueuedCall(World* self, s32 a, s32 b, s32 c, s32 d)
{
    QueuedCall* e = (QueuedCall*)TakeCallRecord(self);
    e->k0 = a;
    e->k1 = b;
    e->k2 = c;
    e->k3 = d;
    if (self->f1ECC != 0) self->f1ECC->next = e;
    else self->f1EC8 = e;
    self->f1ECC = e;
    return e;
}

void RemoveQueuedCalls(World* self, u32 mask, s32 k0, s32 k1, s32 k2, s32 k3)
{
    QueuedCall* prev = 0;
    QueuedCall* removed = 0;
    QueuedCall* cur = self->f1EC8;
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
                        if (cur->k0 != k0) goto miss;
                        break;
                    case 2:
                        if (cur->k1 != k1) goto miss;
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
                self->f1EC8 = next;
            }
            if (next == 0) {
                self->f1ECC = prev;
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
    ReleaseCallRecords(self, removed);
}

void RunQueuedCalls(World* self)
{
    while (self->f1EC8 != 0) {
        QueuedCall* node = self->f1EC8;
        if (node == self->f1ECC) self->f1ECC = 0;
        self->f1EC8 = node->next;
        node->next = 0;
        node->fn(node->k1, node->k2, node->k3);
        ReleaseCallRecords(self, node);
    }
}

void RunDueDelayedScriptCalls(World* self, f32 limit)
{
    ScriptValue a;
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&a);
    InitScriptValue(&q);
    MarkPoolLiveEnds(g_markStacks);
    LookupScriptVariable(self->f2C, self->f1EF8, 0, &a);
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
                EvalScriptExpression(&t, e->next, self->f2C);
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
    LookupScriptVariable(self->f2C, self->f1EF8, 0, &a);
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
            AssignScriptVariable(&t, self->f2C, self->f1EF8, &a);
            DestroyScriptValue(&t, 2);
        }
    }
    DestroyScriptValue(&q, 2);
    DestroyScriptValue(&a, 2);
}

void* AllocateTouchNode(u8* self)
{
    void* p = TakePoolSlot(self + 0x1C0C);
    FillMemory(p, 0, 0x8);
    return p;
}

void FreeTouchNodes(u8* owner, Touch03* node)
{
    while (node != 0) {
        Touch03* next = node->next;
        PushFreeSlot(owner + 0x1C0C, node);
        node = next;
    }
}

void PushCloneBatch(World* self, void* src, s32 n)
{
    struct PackedCloneBatch tmp;
    s32 i;
    s32 idx;

    tmp.n = n - 1;
    if (tmp.n > 0) {
        tmp.buf = AllocateFrontMemory(tmp.n * 4);
        for (i = 0; i < tmp.n; i++) {
            ((void**)tmp.buf)[i] = CreateObjectCopy(src, self, 0);
        }
    }
    idx = self->f1EFC;
    ((PackedCloneBatch*)self->f1F00)[idx] = tmp;
    self->f1EFC = idx + 1;
}

s32 PopSpawnedClone(World* self, s32 index) { CloneBatch* s = &((CloneBatch*)self->f1F00)[index]; s->count--; return s->values[s->count]; }

INCLUDE_ASM(func_001DC238);

INCLUDE_ASM(func_001DC4D0);

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

void PushContactTable(Contacts03* node, Contacts03** head)
{
    node->next = *head;
    node->prev = 0;
    if (*head != 0) {
        (*head)->prev = node;
    }
    *head = node;
}

Contacts03* TakeContactTable(World* owner, Collider* self)
{
    Contacts03* n = owner->freeTables;
    UnlinkContactTable(n, &owner->freeTables);
    PushContactTable(n, &owner->usedTables);
    n->owner = self;
    return n;
}

void ReleaseContactTable(World* owner, Contacts03* handle)
{
    ContactRow03* e = handle->head;
    if (e != 0) {
        void* freeList = &owner->pool1AF0;
        do {
            ContactRow03* next = e->next;
            ContactRow03* s1 = UnlinkContactRow(owner, e->other->contacts, handle);
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
            PushFreeSlot(freeList, e);
            PushFreeSlot(freeList, s1);
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

void CreateConeVolumes(World* self)
{
    ConeVolume* p;

    if (g_coneVolumeMask[0] & 1) {
        p = CreateTypedRecord(0x51, self, 0, 0x201, -1);
        SetConeVolumeColor(p, D_00275640);
        SetConeVolumeFirstAngle(p, D_00275650);
        SetConeVolumeSecondLevel(p, D_00275654);
        SetConeVolumeSecondAngle(p, D_00275658);
        SetConeVolumeThirdLevel(p, D_0027565C);
        SetConeVolumeThirdAngle(p, D_00275660);
        SetConeVolumeDirection(p, &D_00275670);
    }
    if (g_coneVolumeMask[0] & 2) {
        p = CreateTypedRecord(0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 1);
        SetConeVolumeColor(p, D_00275640);
        SetConeVolumeFirstAngle(p, D_00275650);
        SetConeVolumeSecondLevel(p, D_00275654);
        SetConeVolumeSecondAngle(p, D_00275658);
        SetConeVolumeThirdLevel(p, D_0027565C);
        SetConeVolumeThirdAngle(p, D_00275660);
        SetConeVolumeRange(p, D_00275690);
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
    if (g_coneVolumeMask[0] & 4) {
        p = CreateTypedRecord(0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 2);
        SetConeVolumeColor(p, D_00275640);
        SetConeVolumeFirstAngle(p, D_00275650);
        SetConeVolumeSecondLevel(p, D_00275654);
        SetConeVolumeSecondAngle(p, D_00275658);
        SetConeVolumeThirdLevel(p, D_0027565C);
        SetConeVolumeThirdAngle(p, D_00275660);
        SetConeVolumeDirection(p, &D_00275670);
        SetConeVolumeRange(p, D_00275698);
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
    if (g_coneVolumeMask[0] & 8) {
        p = CreateTypedRecord(0x51, self, 0, 0x201, -1);
        SetConeVolumeMode(p, 3);
        SetConeVolumeColor(p, D_00275640);
        SetConeVolumeFirstAngle(p, D_00275650);
        SetConeVolumeSecondLevel(p, D_00275654);
        SetConeVolumeSecondAngle(p, D_00275658);
        SetConeVolumeThirdLevel(p, D_0027565C);
        SetConeVolumeThirdAngle(p, D_00275660);
        SetConeVolumeDirection(p, &D_00275670);
        SetConeVolumeRange(p, D_002756A0);
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
}

void SkipBufferedBlocks(void* self)
{
    s32 n = ReadBufferedU32(self);
    if (D_00275714) {
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
            StateNotifier* o = CreateObjectCopy(n, self, 0);
            o->initialMode = 2;
            if (o->desc->m0F != 0) {
                o->desc->m0F(o);
            }
            o->desc->m10(o);
        }
    }
}

INCLUDE_ASM(func_001DCEA0);

s32 ClipSegmentToPlanes(ClipPoint* pts)
{
    u32 i;
    for (i = 0; i < 6; i++) {
        const ClipPlane* pl = &D_002756B0[i];
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

void DrawProjectedCurve(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, f32 x)
{
    CurveFrame L;
    CurveSample* p;
    CurveSample* q;
    u32 i;

    SampleCurvePoints(a0, a1, a2, a3, 10, L.pts, x, 0.0f, x);
    i = 1;
    q = &L.pts[1];
    p = &L.pts[0];
    do {
        L.c = *(PackedCurveColor*)a4;
        DrawProjectedLine(p, q, &L.c, a5, 1);
        i++;
        q++;
        p++;
    } while (i < 10);
}

void SetWorldLightingParamA(World* self, f32 v)
{
    self->f1D6C = v;
    g_lightingChangeFrame = g_frameCount;
}

void SetWorldLightingParamB(World* self, f32 v)
{
    self->f1D68 = v;
    g_lightingChangeFrame = g_frameCount;
}

void SetWorldSoundLevel(void* self, f32 x)
{
    World* s = (World*)self;

    s->f2318 = x;
    *(s32*)g_previousSoundLevel = -100;
    SetVolumeChannelFactor(7, 1, 1.0f);
    SendIopSoundLevel((s32)(s->f2318 + 0.5f));
}

s32 TestLevelEntryFlag1(void* self, void* obj)
{
    return GetLevelEntryWord(obj) & 0x1;
}

s32 TestLevelEntryFlag2(void* self, void* obj)
{
    return GetLevelEntryWord(obj) & 0x2;
}

s32 TestLevelEntryFlag4(void* self, void* obj)
{
    return GetLevelEntryWord(obj) & 0x4;
}

s32 TestLevelEntryFlag8(void* self, void* obj)
{
    return GetLevelEntryWord(obj) & 0x8;
}

s32 CheckEntryOneBitRequirement(World* a0, void* a1)
{
    s32 one = 1;
    u32 m = GetEntryFlags(a1);
    s32 r = 0;
    if (m & 2) r = (g_currentEntry->flags & 1) ? one : 0;
    return r;
}

s32 CheckEntryTwoBitRequirement(void* self, void* obj)
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

s32 CheckEntryThreeBitRequirement(void* self, void* obj)
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

void SetEntrySlotValue(void* self, void* obj, s32 key, s32 value)
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

s32 GetEntrySlotValue(void* self, void* obj, s32 key)
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

s32 IsLevelRecordComplete(void* self, s32 index)
{
    return g_saveData->levels[index].f448 & 1;
}

s32 IsLevelDone(void* self, s32 index)
{
    return g_saveData->levels[index].f448 & 0x20;
}

void RecomputeSaveCompletion(void* self)
{
    ComputeCompletionPercent(g_saveData);
}

void ScatterRandomObjects(void* unused, void* a, void* b, void* c)
{
    void* r = RandomIntInRange(a, b);
    if (r != 0) {
        ScatterObjectsAroundCircle(g_currentWorld, 0x58, c, r, 0);
    }
}

void SetScatterLevelBuiltin(void)
{
    SetScatterLevel(g_scatterController);
}

void GetGameStateDeltaTime(void* unused, f32* out)
{
    *out = g_currentEntry->dt;
}

void SetCurrentScatterLevel()
{
    f32 r = ClampToRange(&g_unitRange);
    g_currentEntry->f10 = r;
}

void GetCurrentScatterLevel(void* unused, f32* out)
{
    *out = g_currentEntry->f10;
}

void AcquirePadSelectFlag(World* a0) {
    s32 n = a0->f231C + 1;
    a0->f231C = n;
    if (n == 1) {
        SetPadSelectFlags(2);
    }
}

void ReleasePadSelectFlag(World* self)
{
    s32 v = self->f231C - 1;
    self->f231C = v;
    if (v == 0) {
        ClearPadSelectFlags(2);
    }
}

s32 IsPadSelectFlagHeld(World* self) { return self->f231C > 0; }

void GetHasStreamVoice(void* self, s32* out)
{
    *out = HasStreamVoice();
}

void SetWorldValueAndTarget(World* self, f32 v)
{
    self->f2350 = v;
    self->f234C = v;
}

void SetWorldValueTarget(World* self, f32 value) { self->f2350 = value; }

void PopActiveSequenceElement(void)
{
    StepSequence* ctx = D_0027051C;
    if (ctx != 0 && ctx->state2D4 != 4) {
        u32 t = (u32)(ctx->mode2D0 - 1);
        if (t < 2) PopStackElement(g_elementStack);
    }
}

void ShowPauseMenuPageWith(void* unused, s32 a1, s32 a2)
{
    s32 saved = a1;
    u8* p = (u8*)&g_pauseMenuElement;
    ((PackedPageWord*)(p + 0x280))->v = a2;
    SetPauseMenuLayerPage(&g_pauseMenuElement, 0, saved);
}

void ShowCountedScreenElement(World* self)
{
    if (++self->f2320 == 1) {
        SetScreenElementHoldTime(&D_002721D0, 0.0f);
        D_002721D0.vt->m14(&D_002721D0);
    }
}

void HideCountedScreenElement(World* self)
{
    if (--self->f2320 == 0) {
        D_002721D0.vt->m15(&D_002721D0);
    }
}

LINKER_REMNANT(func_001DDBF0);

void PushSoundLevelBuiltin(void* self, void* p)
{
    PushSoundLevel(p);
}

void* RemoveSoundLevelBuiltin(void* unused, void* p)
{
    return RemoveSoundLevelAndRecompute(p);
}

void SetWorldActiveFollower(World* self, void* v)
{
    self->f2324 = v;
}

void NotifyWorldActiveFollower(World* self)
{
    ActiveFollowerChild* p = (ActiveFollowerChild*)self->f2324;
    if (p != 0) {
        ActiveFollowerFn fn = p->vtbl[50];
        if (fn != 0) {
            fn(p);
        }
    }
}

void SetWorldFlagBit(World* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->f235C |= m;
}

void ClearWorldFlagBit(World* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->f235C &= ~m;
}

void GetSaveSpareCount(void* self, s32* out)
{
    *out = g_saveData->f19E4;
}

void GetReserveUnitCount(void* unused, s32* out)
{
    *out = g_saveData->f19E0;
}
