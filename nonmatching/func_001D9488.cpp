// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 456/492, checked 2026-11-12
// w32-sizeA (2026-11-11): the final code's blocks align with retail's except the preheader (retail's six constants outside the loop, ours kept inside: 36 bytes). -dL on this source: `Loop from 17 to 322: 91 real insns` in pass 1, 89 in pass 2, every constant `savings 1 not desirable`. One lead not yet tried: loop.c's combine_movables adds the savings of matching movables (the same constant set twice), which doubles T*savings for that constant; retail's pass-1 moves (the giv's li 40 and the kind test's 1) would follow if the source set each of those twice (two kind tests against 1, or &self->f874[i] taken twice), instead of a 15-insn smaller loop.
// DECLS (2026-11-11, w28-nmdecls): PrintBuffered, RefreshCachedVoiceParam, RemoveSoundLevelAndRecompute, ComputeOscillatorDisplacement now void, GetObjectWorldPosition s32, StoreFloatAsQuadword void*: neutral, 75/123.
// NEAR (2026-11-10, w15): EXACT with this source under -mvu0-use-vf0-vf30 or -vf31 (loop.c's threshold 94-95 instead of 79); under the file's flags the loop is 91 insns in pass 1 where retail's moves need 74-76 (docs/toolchain/loops.md, func_001D9488)
// w38-f5 (2026-11-12): the life-2 and second-movable leads do not hold. A comparison through an inline folds to xori/sltiu (no register constant, nothing to move); the marker indexed at each use gives 100 insns and three unmatched `self + 0x874` movables; and even with the li 40 and the 1 moved in pass 1, the -1, 0x42F and 0x430 have life 1 in pass 2 against 87 insns, which the final code's own insns do not let fall to 79. What builds retail from this source unchanged is loop.c's threshold 94: EXACT with -mvu0-use-vf0-vf30 (and vf31), with no N below 30. The window is three wide (91 <= T - 3 and T - 6 < 91) and the plain source sits in it. func_0013AD80 (EXACT for N = 23 to 30, now matched with its file's row at vf30) and func_00130C58 (6 lines at N >= 29) agree on 94. This file's func_001D66A8, func_001D7778 and func_001D9AC8 stop matching by N = 29, 20 and 26, so the file cannot take the row as it stands: the open question is the file's boundaries (or what else sets n_non_fixed_regs between its functions), not this source. docs/toolchain/loops.md, "A threshold of 94".
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

void* FillMemory(OwnerMessage* p, s32 zero, s32 size);

void FlushOutputBuffer(OutputBuffer* a0, s32 a1);
void FreeObjectMemory(OutputBuffer* a0);

void CopyMemory(void* dst, void* src, s32 bytes);
void PrintBuffered(const char* fmt, ...);
s32 WriteFile(s32 a, void* b, s32 n);

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
void* FillMemory(void* p, s32 value, u32 size);

void RefreshCachedVoiceParam(void* a, void* b);

void* TakePoolSlot(void* p);
void* FillMemory(void* p, s32 a, s32 b);

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
s32 GetObjectWorldPosition(void* self, void* arg);

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

s32 GetObjectWorldPosition(void* item, void* out);

extern f32 g_gameTime;
void* GetActiveSwitchedCollider(void);
void ActivateSwitchedCollider(void* self);

void UpdateSwitchedCollider(PathFollower* self, f32 t);
void UpdatePathFollowerPace(PathFollower* self);
void AdvancePathFollowerAlongPath(PathFollower* self, s32* out);
void ComputePathFollowerHeadingTarget(PathFollower* self);
void UpdatePathFollowerSound(PathFollower* self, f32 t);
void SteerPathFollower(PathFollower* self);
void EmitPathFollowerWheelParticles(PathFollower* self);
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

void* StoreFloatAsQuadword(void* out, f32 f);
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
void* FillMemory(void* p, s32 value, u32 size);

extern void* g_frameCount;
extern void* g_lightingChangeFrame;

f32 ClampToRange(void* p);

void* PushSoundLevel(void* p);

void HandleSwitchedColliderActivation(void* self, void* p);

void* RandomIntInRange(void* a, void* b);
s32 ScatterObjectsAroundCircle(void* heap, int size, void* c, void* d, int e);

extern u8 g_scatterController[];

void SetScatterLevel(void* p);

void RemoveSoundLevelAndRecompute(void* p);

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

void ComputeOscillatorDisplacement(void* osc, void* pos, f32 t, s32 a, Vec02* out, s32 b, s32 c);
s32 CollectTreeNodeSpans(void* nodes, void* a, void* b, s32 c, s32 d, void* out);

s32 ProbeColliderBelowPoint(Player* self, Collider* col, Vec02* out);

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

s32 TestPointAgainstObjectShape(void* item, void* point);
void ResetScatterLevels(void* scatter);
void RecordPathFollowerProgress(PathFollower* self);

void AdvancePathFollowerEntry(PathFollower* self, s32 v)
{
    for (s32 i = 0; i < self->f870; i++) {
        PathMarker* e = &self->f874[i];
        s32 r = TestPointAgainstObjectShape(e->item, (u8*)self + 0x100);
        if (r == *(s32*)((u8*)e + 8)) {
            continue;
        }
        s32 kind = e->kind;
        *(s32*)((u8*)e + 8) = r;
        switch (kind) {
        case 0:
            if (r != 0 && e->next == self->fAF8) {
                self->fAF8 = e;
                if (e == self->fAF4) {
                    s32 n = self->fB00 + 1;
                    self->fB00 = n;
                    if (self->fB04 < n) {
                        void* w = FindFirstObjectById((void*)self->world, 4, 0x42C, (void*)self)->f48;
                        s32 key;
                        GetStateWalkerTargetKey(w, &key);
                        if (key == -1) {
                            GetStateWalkerCurrentKey(w, &key);
                        }
                        if (self == GetActiveSwitchedCollider()) {
                            self->fB00 = self->fB04;
                        }
                        switch (key) {
                        case 0x42F:
                            if (self == GetActiveSwitchedCollider()) {
                                SetStateWalkerTarget((StateTrigger*)w, 0x432);
                                ResetScatterLevels(g_scatterController);
                            } else {
                                SetStateWalkerTarget((StateTrigger*)w, 0x430);
                            }
                            break;
                        case 0x430:
                            if (self == GetActiveSwitchedCollider()) {
                                SetStateWalkerTarget((StateTrigger*)w, 0x431);
                                RecordPathFollowerProgress(self);
                            }
                            break;
                        }
                    }
                }
            }
            break;
        case 1:
            if (r != 0) {
                *(PathMarker**)((u8*)self + 0xAFC) = e;
            } else {
                *(PathMarker**)((u8*)self + 0xAFC) = 0;
            }
            break;
        }
    }
}
