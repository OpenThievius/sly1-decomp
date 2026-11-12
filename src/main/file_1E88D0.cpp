// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276680, which ends
// with a build stamp no code reads; the C library's state record after it is
// src/lib/library_state.c's (that file says why). Named after its first address until what it was is known.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "fpu.h"
#include "world.h"
#include "warp_page.h"
#include "screen_element.h"
#include "globals.h"
#include "shapes.h"
#include "object_link.h"
#include "owner_message.h"
#include "game_clock.h"
#include "pad_record.h"
#include "memory_card.h"
#include "timeline.h"
#include "value_list_object.h"
#include "state_reset_object.h"
#include "attached_set.h"
#include "packet_writer.h"
#include "screen_fade.h"
#include "transform_object.h"
#include "oscillator.h"
#include "camera.h"
#include "game_progress.h"
#include "item_keeper.h"
#include "attachment.h"
#include "animation.h"
#include "ramp_profile.h"
#include "mul_rotation.h"
#include "vu0.h"
#include "ring_params.h"
#include "deferred_request.h"
#include "asm_func.h"
#include "vu0.h"

void SteerAgentAlongPath(void);
void InitElementStack(void* p);
void QueueEachScreenElementDraw(void);
void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a, void* p);
void* CreateStateWalker(void* a, void* self, s32 b, s32 c);
void AppendQueuedCall(void* a, void* cb, void* ctx, s32 b, s32 c); // stays void: retail returns a value, but declared so func_001EB598 differs in registers
void CopyPlayerAttachBlock(BeatPressCollider* self);
void HandleSwitchedColliderActivation(void* self);
s32 FindFirstObjectByIdGathered(void* a, s32 b, s32 c, s32 d);
void SetStateWalkerTarget(void* a, s32 b);
extern s32 g_buttonCodeFlags;
s32 IsPadSelectFlagHeld(void* p);
s32 TestAgentMayContact(void* self, void* probe);
void SetElementStackState(void* self, s32 mode);
s32 IsStreamVoiceLocked(void);
void PauseStreamVoice(void);
f32 FloatRemainder(f32 v);
s32 IsInsideRange(ValueRange* span, f32 x);
void ResumeStreamVoice(void);
void DrawScreenElements(void);
extern float g_gameTime[];
void SetVolumeChannelFactor(int a, int b, float t);
void SetGameClockScale(float x);
void LoadCollider(void* self);
f32 WrapModulo(f32 x, f32 y);
s32 FindColliderFloorContact(void* a, s32 b, s32 c);
s32 FindNearestAgentKey(void* a, void* b);
void* FindObjectHandle(s32 a, s32 b);
void RestartAgentClip(void* a);
typedef void* (*TargetObjectFn)(void* self);
void SetAgentGoalPoint(KeyedConeAgent* self, void* p);
void UpdateAgentGoal(KeyedConeAgent* self);
s32 GetObjectWorldPosition(void* self, void* arg);
void FaceAgentTowardGoalPoint(KeyedConeAgent* self);
void UpdateAgentState(KeyedConeAgent* self);
extern u8 g_flagTable[];
void SetWorldActiveFollower(void* sub, void* self);
void* TakeFlagTableIndex(void* p);
void StartConeAgent(void* self);
s32 AreMenusAndFadeClear(void);
extern s32 D_00270458;
extern s32 D_00275DBC;
void InitAgent(void* self);
void* AllocateFrontMemory(s32 size);
void StopStagedBankVoice(void);
void PopStackElement(void* g);
void SetPadPatternState(void* self, s32 mode);
void ResetScreenElements(void);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, void* p, f32* out);
f32 WrapAngle(f32 a);
f32 ApproachValueClampingVelocity(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1);
s32 NextRandom(void);
s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots);
void InitConeAgent(void* self);
void StartAgent(void* self);
void* CreateStateWalker(void* a, s32 b, s32 c, s32 d);
void AddStateWalkerListener(void* a, void* self);
void* CopyToFrontMemory(s32 size, void* name);
s32 FindFirstObjectById(void* a, s32 b, s32 c, void* self);
// An object the tempo agent finds by id at its start (func_001EBFB0 copies D_00275D48 to
// 0xC9C and fills each obj).
struct TempoObjectRef { s32 id; f32 f04; s32 obj; };
f32 ApproachValueWithRamp(void* p, void* out, f32 a, f32 b, f32 c);
s32 ChooseAgentState(KeyedConeAgent* self);
extern s32 g_previousSoundLevel;
extern f32 g_elapsedTime[];
void ApplyStackTimeScale(ElementStack* a, f32 f);
void SetMemoryCardDisplayMode(MemoryCard* a, s32 v);
void SetScreenFadeMode(u8* a, s32 v);
void ReleasePadSelectFlag(void* a);
void AcquirePadSelectFlag(void* a);
void InitPadPatternSetting();
extern u32 g_padRouting;
extern u32 g_padSelectFlags;
extern s32 D_002701B8;
extern void ClearPadSelectFlags(s32 n);
extern void* FindActiveObjectSubGroup(void);
extern void StartObjectSubGroupFinish(void* x);
extern void ClearPadPressedBits(PadRecord* p, s32 n);
extern s32 ApplyMemoryCardImage(MemoryCard* g);
extern void ResetGameProgress(void* p);
extern void ResumeAtSavedLevel(void);
extern void SetPauseMenuLayerPage(void* self, s32 a, s32 b);
extern void PushStackElement(ElementStack* o, ScreenElement* g);
extern void ApplyStackTimeScale(ElementStack* o, f32 v);
extern void SetElementStackState(ElementStack* o, s32 mode);
extern void StepDiscSectorCheck(void);
extern void UpdateScreenElements(void);
typedef s32 (*BeatPressSlotFn)(BeatPressCollider* self, void* arg);
typedef void (*PlayerSlotFn)(Player* g, void* arg);
s32 GetObjectWorldPosition(void* a, Vec4U* out);
s32 GetObjectWorldRotation(void* a, Mat3U* out);
void StartSoundEffect(s32 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
s32 HasSpareCount(void);
void ActivateSwitchedCollider(Player* g);
void InitOwnerMessage(OwnerMessage* out, s32 mode, BeatPressCollider* self);
void ContinueBeatPressColliderRequest(PlacedObject* from, Player* self);
void EndHeldTimeline(TempoAgent* o);
void SetCachedVoiceParam(s32 a, s32 b);
void BindEntryQueueToObject(void* a, Player* g);
extern s32 D_00275C34;
extern u32* g_memoryChecksumCursor;
extern s32 g_memoryChecksumRemaining;
extern u32 g_memoryChecksumValue;
extern u8 D_00148D7C[];
extern u32 g_crc32Table[];
struct Crc32 {
    static u32 Step(u32 h, u8 b) { return g_crc32Table[(h ^ b) & 0xFF] ^ (h >> 8); }
};
void InitSwitchedCollider(BeatPressCollider* self);
f32 RandomFloatInRange(f32 lo, f32 hi);
f32 Logarithm(f32 x);
s32 IsPadSelectFlagHeld(World* p);
union DoubleBits {
    double d;
    u64 u;
};
double AddDoubles(double a, double b);
// An object of the world's lists at 0x78, 0x1B70 and 0x1C30 as func_001E9EE8 walks them: the
// slot at 0x7C of the first list's objects is called with the frame time.
struct ListedObject;
struct ListedObjectVt {
    u8 pad0[0x7C];
    void (*update)(ListedObject*, s32, f32);
};
struct ListedObject { ListedObjectVt* vtbl; };
struct BeginNodeWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        ListFrame* prev = g_activeListFrames;
        g_activeListFrames = it;
        it->prev = prev;
    }
};
struct NextNode {
    static ListedObject* Of(ListFrame* it)
    {
        ListedObject* obj = *(ListedObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct EndNodeWalk {
    static void Of(ListFrame* it) { g_activeListFrames = it->prev; }
};
void UpdateObjectTree(ListedObject* n, f32 dt);
void UpdateAnimationPlayer(ListedObject* n, f32 dt);
void StepObjectLevelRamp(ListedObject* n, f32 dt);
void RunQueuedCalls(World* self);
struct BeginByteWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};
struct NextByte {
    static u8* Of(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};
struct EndByteWalk {
    static void Of(ListFrame* it)
    {
        g_activeListFrames = it->prev;
    }
};
void StepMemoryChecksum(void);
SwitchedCollider* GetActiveSwitchedCollider(void);
void UpdateWorldObjectLists(World* self);
void UpdateObjectTree(u8* n, f32 dt);
void UpdateAnimationPlayer(u8* n, f32 dt);
void StepObjectLevelRamp(u8* n, f32 dt);
void DispatchDelayedMessages(World* self);
void UpdateSoundEmitters(void);
struct NextActor {
    static Actor6C* Of(ListFrame* it)
    {
        Actor6C* obj = *(Actor6C**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct BeginActorWalk {
    static void Of(ListFrame* it, ActorList6C* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};
void UpdateWorldStepLists(World* self, f32 t);
void UpdateWorldDeltaLists(World* self, f32 t);
void UpdateUnflaggedParts(World* self);
void UpdateWorldContacts(World* self, s32 a);
void ProcessColliderGroups(World* self, s32 a, f32 t);
s32 IsObjectTreeAtRest(Actor6C* n);
void ClearRootTries(Actor6C* n);
void UpdateTouchingParts(Actor6C* n);
void RunDueDelayedScriptCalls(World* self, f32 t);
void StepAnimators(f32 t);
void NotifyWorldActiveFollower(World* self);
void ReleaseWorldListEntry(Actor6C* n);
void UpdateCamera(Camera* a, s32 b, f32 t);
void StepWorldValueTowardTarget(World* self, f32 t);
void StartObject(void);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void RunTimelineEntry(Timeline* self, s32* p);
Entry90* AppendTimelineEntry(void* self, s32 kind, s32 p);
// What ComputeSinCos writes for func_001ED650.
struct SinCos { f32 sine; f32 cosine; };
void ComputeSinCos(f32* a, f32* b);
void RegisterSwitchedCollider(void);
void GetStateWalkerCurrentKey(void* sub, s32* out);
void AddAnimationPlayerRecordCallback(void* a, TempoAgent* self);
s32 ComputeBallisticLaunchVelocity(void* self);
s32 WriteVifUnpackHeader(PacketWriter* s);
void InitObject(BaseObject* self);
void RemoveColliderAttachment(Collider* o, Attach03* node);
void AddColliderAttachment(Collider* o, Attach03* node);
void ReleaseAttachRecords(void* owner, Attach03* list);
void SetScreenFadeMode(void* o, s32 mode);
void UnregisterObjectGroup(void* a, AttachedGroup* s);
void RegisterObjectGroup(void* a, AttachedGroup* s);
void OfferTrackedNodeLaunch(void* p);
void InitPlacedObject(void* self);
void SetStateAndNotify(void* self, s32 b);
s32 UpsertKeyedEntry(void* a, s32 b, void* c, s32 d, s32 e, s32 f, s32 g, s32 h);
void* AppendQueuedCall(s32 a, void* b, void* c, s32 d, s32 e);
void UnregisterSwitchedCollider(void);
void EndTimeline(void* p);
void ComputeSinCos(f32 angle, f32* a, f32* b);
typedef u64 Bits128 __attribute__((mode(TI)));
s32 QueryValueTreeMask(ValueListObject* self, s32 node, Bits128 point, f32 radius, s32* out);
typedef void (*AttachNotifyFn)(void* self, void* arg);
void BuildPlacedObjectTransform(void* obj, void* c, void* out);
void ApplyPlacedObjectTransform(void* obj, void* s, void* out);
void SetAgentGoalPoint(void* self, void* p);
void UpdateAgentGoal(void* self);
void InitObject(void* self);
void PadPacketToQuadSlot(void* s, s32 target);
s32 WriteVifUnpackHeader(void* self, s32 a, s32 b, s32 c);
void AddDmaRefTag(void* obj, s32 a, s32 b);
void ReadLinkedItemArray(void* src, s32* count, void** out);
s32 ReadBufferedU16(void* stream);
s32 ReadBufferedU32(void* src);
void ReadPropertyRecords(void* a, void* b);
// The message (kind 11) func_001EF3D8 sends the object it detaches.
struct DetachMsg { AttachedSet* self; Collider* obj; };
void RebuildAttachedSet(AttachedSet* self);
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void InitCollider(void* self);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void InitTrackedNodes(void* a, void* b);
extern s32 g_worldLoadRequest;
s32 RestoreFadeRequest(ScreenFade* self, s32 a1, s32 a2);
void SetScreenFadeMode(ScreenFade* self, s32 state);
void SetVolumeChannel6Factors(s32 flag, f32 x);
typedef void (*TempoCallFn)(void);
void UpdateAgent(TempoAgent* self);
void RestartTimeline(Timeline* sub);
void RunTimelineEntries(Timeline* sub);
void RefreshCachedVoiceParam(s32 a, void* b);
s32 GetCachedVoiceParam(s32 a);
void* AppendQueuedCall(World* world, TempoCallFn cb, TempoAgent* self, s32 a3, s32 a4);
void SyncTempoAgentEntries(void);
void LeaveAgentState(void* self, void* arg);
void AppendPacketQuadwords(void* self, s32 index, s32 count);
extern void* D_002505C0[6];
void* AllocateZeroedFrontMemory(u32 n);
void ReserveVifUnpack(void* s, void* a1, s32 size, void* a3, s32* outSize, u8** outCursor);
extern s32 g_coloredTriangleSet;
void DrawColoredTriangles(s32 a, f32 v);
void WriteColoredSpritePacket(s32 a, s32 b, s32 c, s32 d, void* e, f32 f, f32 g, f32 h, f32 i);
void DecrementGaugeCount(void* p);
void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag);
extern u8 D_0024A0E0[];
s32 InitPacketBuffer(PacketWriter* self);
// The ListFrame of func_001EECE0's walk of its children, opened and closed by its lifetime.
struct ChildWalkFrame {
    s32* a; s32* b; s32 c; ChildWalkFrame* prev;
    ChildWalkFrame(s32* p) : a(p), b(p), c(p[2]), prev((ChildWalkFrame*)g_activeListFrames) {}
    ~ChildWalkFrame() { g_activeListFrames = (ListFrame*)prev; }
};
void StartPlacedObject(AttachedSet* self);
void FillTrackedNodes(void* self);
// The message (kind 0x16) func_001EF900 sends with a state change: the old and new states.
struct StateChangeMsg {
    void* self;
    s32 old;
    s32 cur;
};
s32 SetGatheredWalkerTargets(World* mgr, s32 a, void* b, StateResetObject* self, s32 c);
void GetStateWalkerCurrentKey(s32 sub, s32* out);
void ScheduleTempoAgentBeatPress(TempoAgent* p);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32* c);
void ResetPadStepRepeat(void* p);
void StartSoundEffect(s32 a0, Timeline* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern u8 D_00625760[];
void* FillMemory(void* p, s32 value, s32 size);
// The dead "li v0,2" after the func_001ED090 call is the compare constant of an
// "if (n == 2)" whose two arms compile identically: jump2 cross-jumps the arms after
// reload, deletes the branch and leaves the constant load.
void EnterAgentState(TempoAgent* self, s32 a, s32 b);
void MarkLevelDone(s32 n);
void StartMemoryCardSave(void* p);
s32 TestFlagTableBit(void* table, s32 index);
void SetFlagTableBit(void* table, s32 index);
void RaiseScatterLevelForObject(void* controller, void* node);
extern u8 g_scatterController[];
f32 ArctangentOfRatio(f32 a, f32 b);
void CopyMemory(TempoPlayerEntry* dst, TempoPlayerEntry* src, s32 bytes);
void RunTimelineEntry(Timeline* self, Entry90* e);
void* MoveMemory(void* dst, void* src, s32 size);
// An array-move helper: its parameter copies give retail its (i * 4 + self) base shared by both pointers.
// Moves n bytes of the item list down over a removed item.
struct MoveItemsDown {
    static void Of(StateResetObject** dst, StateResetObject** src, s32 n)
    {
        MoveMemory(dst, src, n);
    }
};
void PopActiveSequenceElement(World* x);
struct SameAsFixedKey {
    static s32 Of(IdentityKey* t)
    {
        IdentityKey* p;
        p = &D_00275B04;
        if (t == p) {
            return 1;
        }
        if (p == 0) {
            return 0;
        }
        return ((p->signedWords[2] ^ p->signedWords[6]) ^ (t->signedWords[2] ^ t->signedWords[6])) == 0;
    }
};
void SnapCameraZoom(void* p, f32 v);
void BuildMatrixFromRotationAndTranslation(void* a, void* b, void* out);
// A FadeRequest moved as a 16-byte unaligned block and its last word.
struct FadeRequestBlock {
    QuadP pair;
    s32 mid;
};
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void TransformPointBetweenFrames(void* a, s32 b, void* c, s32 d);
void SetElementTextFromEntry(T217D_3D0* self, s32 a, s32 b);
void SetWarpPageSelectedEntry(void* self, s32 value);
extern s32 D_00276654;
void StartScreenFade(void* dst, void* args, s32 count);
void SetWarpPageMode(void* self, u32 mode);
void* AllocateFrontMemory(int size);
void StartObject(void* self);
void ResolveAndStartObject(void* a);
// The pad (include/c73.h's neighbours): its buttons at +0xAA, its direction timers at +0x30 .. 0x3C.
s32 IsWarpEntryAvailable(WarpPage* o, s32 n, s32* a, s32* b);
s32 GetPadHorizontalStep(PadRecord* t);
s32 GetPadVerticalStep(PadRecord* t);
void MoveWarpCursor(WarpPage* o, s32 n);
void ClearPadPressedBits(PadRecord* p, s32 n);
s32 GetCurrentWarpEntry(void);
void PopStackElement(ElementStack* q);
IdentityKey* LookupEntryById(s32 k);
void StartObjectFade(IdentityKey* v, s32 m, s32 n);
void StartSoundEffect(s32 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
f32 ApproachValueWithRamp(RampProfile* p, s32 a1, f32 f12, f32 f13, f32 f14);
void HideScreenElements(void* self);
s32 IsWarpEntryAvailable(void* o, s32 n, s32* a, s32* b);
void SetWarpCursor(void* self, s32 a1, s32 a2);
void BeginWarpPageClose(void* self);
void SetScreenElementSlideInTime(void* self, f32 v);
void SetScreenElementSlideOutTime(void* self, f32 v);
void PauseStagedBankVoice(void);
void ResumeStagedBankVoice(void);
s32 SetPadSelectFlags(s32 bits);
struct SameKeys {
    static s32 Of(IdentityKey* t, IdentityKey* o)
    {
        if (t == o) {
            return 1;
        }
        if (o == 0) {
            return 0;
        }
        return ((o->signedWords[2] ^ o->signedWords[6]) ^ (t->signedWords[2] ^ t->signedWords[6])) == 0;
    }
};
extern void* D_0026FA68;
extern s32 g_previousLevelIndex;
void QueueWorldLoad(void* a, s32 b, s32 c, s32 d, s32 e);
s32 GetEntryIdByKey(s32 a);
void ShowCountedScreenElement(void* a);
void FadeScreenToBlack(f32 t);
struct WarpTextStyle;
void* FillMemory(void* p, s32 value, s32 size);
// The text style the warp menu draws with: the static initialiser (func_001F2688) zeroes it, then
// sets its kind, two sizes given as integers, 0.3 twice and its colour.
struct WarpTextStyle {
    u8 pad0[4];
    u8 kind;
    u8 pad5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    s32 f18;
    WarpTextStyle(s32 a, s32 b)
    {
        FillMemory(this, 0, 0x1C);
        kind = 0x3D;
        f8 = a;
        fC = b;
        f14 = f10 = 0.3f;
        f18 = (s32)0xFF7D4B00;
    }
};
extern f32 D_00276650;
s32 IsFontLoaded(s32 n);
Font* GetFontById(s32 n);
void* FillMemory(void* p, s32 value, s32 size);
extern void StartPlacedObject(WarpPage* o);
s32 IsWarpEntryReachable(WarpPage* o, s32 n);
void SelectWarpPageEntry(WarpPage* o, s32 n);
void AnnouncePendingWarpEntry(WarpPage* o);
void SetWarpPageSelectedEntry(WarpPage* o, s32 n);
void StopSoundRecord(void* p, s32 n);
void RemoveObjectNodeFromWorld(WorldObjectNode* r);
void EnsureObjectWorldNode(PlacedObject* o);
void ReplaceAnimationPlayer(Animation* a, WarpPage* b, s32 c, void* d, f32 e, f32 f);
void StartSoundEffect(s32 a0, void** a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void PostLoadPlacedObject(WarpPage* self);
void ResolveObjectLinks(WarpPage* self, s32 n, void* table);
void ResolveAndStartObject(BaseObject* node);
struct NextPageNode {
    static BaseObject* Of(ListFrame* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct BeginPageWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};
HoldingMember* FindFirstObjectById(World* host, s32 kind, s32 id, HoldingMember* ctx);
extern s32 (*D_00276608[6])[4];
// The sounds MoveWarpCursor plays: the cursor moved, or it could not.
enum WarpCursorSound { WARP_SOUND_MOVE = 0x79, WARP_SOUND_REFUSE = 0x7B };
void StartSoundEffect(WarpCursorSound a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
BaseObject* FindFirstObjectById(void* o, s32 a, s32 b, WarpPage* c);
// A point of the fan func_001F1E38 draws: its colour and, at 0x10, its position.
struct FanPoint { s32 k; s32 pad[3]; f32 x; f32 y; };
void BeginGifTag(PacketWriter* f, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(PacketWriter* f, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* self, u32 value);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void InitElementStack(ElementStack* self);
void PushStackElement(ElementStack* self, ScreenElement* node);
void SetElementStackState(ElementStack* self, s32 state);
void ApplyStackTimeScale(float x);
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);
void AddTempoAgentEntry(TempoAgent* self, AnimationPlayer* a, s32 b);
void RestartTimeline(Timeline* self);
void EndTimeline(Timeline* self);
void RunTimelineEntries(Timeline* self);
void SetStateAndNotify(StateResetObject* self, s32 state);
s32 RestoreFadeRequest(ScreenFade* self, PadRecord* o, void* param2);
void SetWarpPageMode(WarpPage* self, u32 next);
void SetWarpCursor(WarpPage* self, s32 a1, s32 a2);
void SetWarpPageSelectedEntry(WarpPage* self, s32 idx);

ObjectLink D_00275B60[8] = {
    { 3, 0x2D5, 0xC50 }, { 3, 0x2E7, 0xC60 }, { 7, 0x2E1, 0xC64 }, { 7, 0x2E2, 0xC68 },
    { 7, 0x2E3, 0xC6C }, { 7, 0x2E4, 0xC70 }, { 7, 0x2E5, 0xC74 }, { 7, 0x2E6, 0xC78 }
};
// word read whole / address only, 4 bytes to next label
// readers pass only its address; byte buffer, size to next label
u8 g_elementStack[4] = {0};
INCLUDE_DATA(D_00275BC4);
// size: s32 read as one word (file_14EE40.cpp and screen_element.cpp test bit 8)
// size: s32 compared with 1 in item_column.cpp and 2 in pause_menu.cpp
s32 D_00275BEC = 0;
s32 D_00275BF0[10] = { 0, 0, 3, 10, 6, 63, 3, 11, 5, 31 };
f32 D_00275C18[4] = { 2.0f, 0.0f, 0.1f, 0.0f };
f32 D_00275C28[3] = { 1.0f, 0.0f, 0.1f };
s32 D_00275C34 = 0;
// size: func_0012A610/func_0012A6E0 copy it as a 16-byte vector
Quad16 D_00275C40 = {0};
f32 D_00275C50[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
ValueRange g_unitRange = { 0.0f, 1.0f };
ValueRange D_00275C68 = { -1.0f, 1.0f };
f32 D_00275C70[4] = { 0.5f, 0.8f, 0.0f, 0.0f };
f32 D_00275C80[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
ObjectLink D_00275C90[1] = { { 0, 0x4C9, 0x610 } };
ObjectLink D_00275CA0[4] = {
    { 4, 0x4D0, 0x618 }, { 4, 0x4D1, 0x61C }, { 4, 0x4D2, 0x620 }, { 4, 0x4D3, 0x624 }
};
f32 D_00275CD0 = 700.0f;
f32 D_00275CD4 = 650.0f;
s32 D_00275CD8[4] = { 1228, 1230, 1229, 1231 };
s32 D_00275CE8[4] = { 574, 576, 575, 577 };
s32 D_00275CF8[4] = { 1247, 1248, 1249, 1250 };
ObjectLink D_00275D08[5] = {
    { 1, 0x4EB, 0xC50 }, { 0, 0x4E7, 0xC24 }, { 0, 0x4E8, 0xC28 }, { 0, 0x4E9, 0xC2C },
    { 0, 0x4EA, 0xC30 }
};
TempoObjectRef D_00275D48[9] = {
    { 0x35, 50.0f, 0 }, { 0x36, 50.0f, 0 }, { 0x38, 80.0f, 0 }, { 0x3B, 80.0f, 0 },
    { 0x60, 70.0f, 0 }, { 0x50, 220.0f, 0 }, { 0x52, 80.0f, 0 }, { 0x53, 80.0f, 0 },
    { 0x54, 80.0f, 0 }
};
// The data from D_00275DB8 on is defined after DrawTempoAgentRing (func_001EC190), whose static's
// guard (D_00275DB4) retail's .data has before it: the compiler writes a guard out with its
// function. Declared here for the functions above that.
extern s32 D_00275DB8;
extern s32 D_00275DD0[16];
extern s32 D_00275E10[92];
extern ScreenFade g_screenFade;
extern f32 D_00275FC0;
extern s32 D_00275FC8[6];
extern ObjectLink D_00275FE0[52];
extern s32 D_00276250;
extern f32 D_00276258[4];
extern f32 D_00276268[4];
extern f32 D_00276278[4];
extern f32 D_00276288[4];
extern s32 D_00276298[11][4];
extern s32 D_00276348[11][4];
extern s32 D_002763F8[11][4];
extern s32 D_002764A8[11][4];
extern s32 D_00276558[11][4];
extern s32 (*D_00276608[6])[4];
#ifndef VERSION_EU
extern WarpTextStyle D_00276620;
#endif
#ifdef VERSION_EU
extern f32 D_eu_0027FDAC;
extern f32 D_eu_0027FDB0;
#else
extern f32 D_00276648;
extern f32 D_00276650;
#endif
extern s32 D_00276654;
extern f32 D_0027663C[];
extern char D_00276658[8];
extern char D_00276660[16];
extern char D_00276670[12];


void InitKeyedConeAgent(KeyedConeAgent* self)
{
    InitConeAgent(self);
    self->fC58 = 0x2D8;
    self->fC14 = 30000.0f;
    self->fC10 = 30000000.0f;
    self->fC20 = 3000000.0f;
    self->fC24 = 3000000.0f;
    self->fC28 = 0;
    self->fC2C = 6.2831855f;
}

// The file's first read-only data, for func_001E89F0.
extern const f32 D_0024E600[4] = {3.40282347e+38f, 0.0f, 0.0f, 0.0f};

void StartKeyedConeAgent(KeyedConeAgent* self)
{
    ResolveObjectLinks(self, 8, D_00275B60);
    SetWorldActiveFollower(self->world, self);
    if (self->fC50 != 0) {
        self->fC54 = CreateStateWalker(self->fC50, 0, 0x2D7, 0);
    }
    self->fC90 = 4;
    for (u32 i = 0; i < 4; i++) {
        self->fC80[i] = TakeFlagTableIndex(g_flagTable);
    }
    StartConeAgent(self);
}

ASM_FUNC(func_001E89F0);

void EnterKeyedConeAgentState(KeyedConeAgent* self, s32 a, s32 b)
{
    s32 key;
    s32 slot;

    switch (self->f724) {
    case 1:
        if (self->fC54 != 0) {
            SetStateWalkerTarget(self->fC54, self->fC58);
            void* near = ((TargetObjectFn*)self->desc)[102](self);
            if (near != 0) {
                key = FindNearestAgentKey(self, (u8*)near + 0x140);
            } else {
                key = 0;
            }
            for (u32 i = 0; i < 6; i++) {
                PlacedObject* root = self->fC64[i];
                s32 pick;
                switch (self->fC58) {
                case 0x2D7:
                case 0x2D8:
                case 0x2DA:
                    pick = 0x2DE;
                    break;
                case 0x2D9:
                case 0x2DB:
                case 0x2DC:
                case 0x2DD:
                    pick = 0x2DF;
                    if ((s32)root == key) {
                        pick = 0x2DE;
                    }
                    break;
                }
                void* h = FindObjectHandle((s32)root, -1);
                if (h != 0) {
                    SetStateWalkerTarget(h, pick);
                }
            }
        }
        if (self->fC58 != 0x2DA) {
            u128 d = Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(self->v190));
            if (Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d))) < 300.0f) {
                self->fC5C = 8;
            } else {
                self->fC5C = 5;
            }
        } else {
            self->fC5C = 5;
        }
        self->fC7C = 0;
        break;
    case 16:
        switch (self->fC58) {
        case 0x2D8:
            self->fC58 = 0x2D9;
            slot = 0;
            break;
        case 0x2D9:
            self->fC58 = 0x2DA;
            slot = 1;
            break;
        case 0x2DA:
            self->fC58 = 0x2DB;
            slot = 2;
            break;
        case 0x2DB:
            self->fC58 = 0x2DC;
            slot = 3;
            break;
        }
        if (TestFlagTableBit(g_flagTable, (s32)self->fC80[slot]) == 0) {
            RaiseScatterLevelForObject(g_scatterController, 0);
        }
        SetFlagTableBit(g_flagTable, (s32)self->fC80[slot]);
        self->fC90 = 3 - slot;
        DecrementGaugeCount(&g_gaugeBarElement);
        break;
    case 11:
        if (self->fC54 != 0) {
            SetStateWalkerTarget(self->fC54, 0x2DD);
        }
        for (u32 i = 0; i < 6; i++) {
            void* h = FindObjectHandle((s32)self->fC64[i], -1);
            if (h != 0) {
                SetStateWalkerTarget(h, 0x2DE);
            }
        }
        self->fC90 = 0;
        DecrementGaugeCount(&g_gaugeBarElement);
        MarkLevelDone(1);
        StartMemoryCardSave(&g_memoryCard);
        break;
    case 10:
    case 14:
        self->fC5C = 0;
        break;
    }
    EnterAgentState((TempoAgent*)self, a, b);
}

s32 ChooseKeyedConeAgentState(KeyedConeAgent* self)
{
    s32 a1;
    if (self->fC5C <= 0) {
        self->fBFC = 3.4028235e+38f;
    }
    a1 = self->f724;
    if (a1 == 10) {
        a1 = (self->f7E0 == 0) ? 8 : 10;
    } else {
        a1 = ChooseAgentState(self);
    }
    return a1;
}

s32 IsKeyedConeAgentFree(KeyedConeAgent* a0)
{
    if (a0->fC40 != 0) return 0;
    return a0->fC5C != 0;
}

s32 IsKeyedConeAgentTargetInRange(KeyedConeAgent* a0)
{
    if (a0->fC58 != 0x2DB) return 0;
    {
        s32 v = a0->fC5C;
        if (v == 5 || v == 0) return 0;
        return 1;
    }
}

void SteerKeyedConeAgentAlongPath(KeyedConeAgent* a0)
{
    if (a0->fC58 != 0x2DA) {
        s32 v = a0->fC5C - 1;
        if (!(0 < v)) v = 0;
        a0->fC5C = v;
    }
    SteerAgentAlongPath();
}

void RestartKeyedConeAgentClip(KeyedConeAgent* self)
{
    if (self->fC58 == 0x2DA && self->f724 == 0xC && FindColliderFloorContact(self, 0, 0) != 0) {
        s32 s = FindNearestAgentKey(self, (u8*)self + 0x140);
        if (s != self->fC7C) {
            s32 n = self->fC5C - 1;
            if (!(0 < n)) n = 0;
            self->fC5C = n;
            if (n > 0) {
                void* p = FindObjectHandle(s, -1);
                if (p != 0) SetStateWalkerTarget(p, 0x2E0);
                self->fC7C = s;
            }
        }
    }
    RestartAgentClip(self);
}

void UpdateKeyedConeAgentGoal(KeyedConeAgent* self)
{
    Vec4U loc;
    switch (self->f724) {
    case 4:
        if (self->fC40 != 0) {
            SetAgentGoalPoint(self, (u8*)self + 0x190);
        } else {
            GetObjectWorldPosition(self->fC60, &loc);
            SetAgentGoalPoint(self, &loc);
        }
        break;
    case 8: {
        void* r = ((TargetObjectFn*)self->desc)[102](self);
        if (r != 0) SetAgentGoalPoint(self, (u8*)r + 0x140);
        break;
    }
    default:
        UpdateAgentGoal(self);
        break;
    }
}

void UpdateKeyedConeAgentState(KeyedConeAgent* self)
{
    if (self->f724 == 8) {
        FaceAgentTowardGoalPoint(self);
    } else {
        UpdateAgentState(self);
    }
}

void ShowElementWhenMenusClear(void)
{
    if (AreMenusAndFadeClear()) {
        g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    } else {
        g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
    }
}

s32 TestAgentMayContactExceptKeys(KeyedConeAgent* self, Collider* probe)
{
    PlacedObject* key = probe->root;
    u32 i = 0;
    s32 result;
    do {
        if (key == self->fC64[i]) {
            result = 0;
            goto done;
        }
        i++;
    } while (i < 6);
    result = TestAgentMayContact(self, probe);
done:
    return result;
}

void InitGlobalElementStack(void)
{
    InitElementStack(g_elementStack);
}

void InitElementStack(ElementStack* self)
{
    self->resumeState = -1;
    self->state = -1;
    SetElementStackState(self, 3);
    self->items[0] = 0;
    self->count = 1;
}

void ResumeElementStackState(void* self)
{
    SetElementStackState(self, 3);
}

void UpdateElementStack(ElementStack* obj)
{
    f32 d = g_gameClock.elapsed - obj->stateTime;
    s32 s1 = obj->state;
    PadRecord* s2;
    s32 s5;
    if (g_padRouting & 4) {
        s2 = &g_padRecord;
    } else {
        s2 = &g_blankPadRecord;
    }
    s5 = 0;
    if (g_padSelectFlags & 0x80) {
        if (0.1f < g_gameClock.time) {
            ClearPadSelectFlags(0x80);
        }
    }
    switch (obj->state) {
    case 0: {
        s32 a2 = 0;
        if (D_002701B8 == 0) {
            s32 m = g_memoryCard.displayMode;
            if (m == 2 || (m == 1 && g_memoryCard.state == 5)) {
                a2 = 1;
            }
        }
        if (a2) {
            StartObjectSubGroupFinish(FindActiveObjectSubGroup());
        }
        break;
    }
    case 1: {
        u32 v = s2->flags;
        if (v & 0x800) {
            s32 t;
            ClearPadPressedBits(s2, 0x800);
            t = g_memoryCard.i4F48;
            g_memoryCard.i4F44 = t;
            if (t) {
                ApplyMemoryCardImage(&g_memoryCard);
            } else {
                ResetGameProgress(g_saveData);
            }
            ResumeAtSavedLevel();
            s1 = obj->state;
        } else if (v & 0x100) {
            ClearPadPressedBits(s2, 0x100);
            SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0x17);
            s1 = obj->state;
        }
        break;
    }
    case 3: {
        if (g_padSelectFlags & 2) break;
        if (g_screenFade.mode) break;
        {
            u32 v = s2->flags;
            if ((v & 0x800) || (s2->f14 == 1 && 5.0f <= g_gameClock.time)) {
                SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0);
                s1 = obj->state;
                ClearPadPressedBits(s2, 0x800);
            } else if ((v = s2->flags) & 0x100) {
                T217D_0F0* g2 = &g_mapScreenList;
                WarpPage* x = g2->current;
                if (x == 0) break;
                if (x->mode) break;
                PushStackElement(obj, g2);
                s1 = obj->state;
                ClearPadPressedBits(s2, 0x100);
            }
        }
        break;
    }
    case 4:
        if (d <= 0.2f) {
            ApplyStackTimeScale(obj, (0.2f - d) * 5.0f);
        } else {
            s1 = 5;
        }
        break;
    case 6:
        if (d <= 0.5f) {
            ApplyStackTimeScale(obj, d + d);
        } else {
            s1 = 3;
        }
        break;
    case 2:
    case 5:
    case 7:
        s5 = 1;
        break;
    case 8:
    default:
        break;
    }
    SetElementStackState(obj, s1);
    {
        ScreenElement* e = obj->items[obj->count - 1];
        if (e) {
            if (e->vt->m04) {
                e->vt->m04(e, s2);
            }
        } else if (s5) {
            SetElementStackState(obj, 3);
        }
    }
    StepDiscSectorCheck();
    UpdateScreenElements();
}

void PushStackElement(ElementStack* self, ScreenElement* node)
{
    if (IsStreamVoiceLocked() && self->count == 1) {
        PauseStreamVoice();
    }
    if (self->count >= 2) {
        ScreenElement* last = self->items[self->count - 1];
        if (last->vt->m03) {
            last->vt->m03(last, 0);
        }
    }
    if (node->vt->m03) {
        node->vt->m03(node, 1);
    }
    s32 index = self->count;
    self->items[index] = node;
    self->count = index + 1;
    if (node->vt->m06) {
        node->vt->m06(node);
    }
}

void PopStackElement(ElementStack* g)
{
    ScreenElement* item = g->items[--g->count];
    if (item->vt->m03) item->vt->m03(item, 0);
    if (item->vt->m07) item->vt->m07(item);
    if (g->count >= 2) {
        ScreenElement* other = g->items[g->count - 1];
        if (other->vt->m03) other->vt->m03(other, 1);
    }
    if (IsStreamVoiceLocked()) {
        if (g->count == 1) ResumeStreamVoice();
    }
}

void DrawAllScreenElements(void)
{
    DrawScreenElements();
}

void QueueScreenElementDraws(void)
{
    QueueEachScreenElementDraw();
}

void ResetElementStack(ElementStack* self)
{
    while (self->count >= 2) {
        PopStackElement(self);
    }
    s32 one = 1;
    self->resumeState = -1;
    u8* base = (u8*)&g_padRecord;
    self->count = one;
    self->items[0] = 0;
    SetPadPatternState(*(void**)(base + 0xBC), 3);
    ResetScreenElements();
}

void SetElementStackState(ElementStack* self, s32 state)
{
    if (state == 3) {
        s32 t = self->resumeState;
        if (t != -1) state = t;
    }
    if (self->state != state) {
        if (self->state != 0) {
            if (self->state == 1) {
                D_00272930.vt->m15(&D_00272930);
                D_00272B98.vt->m15(&D_00272B98);
                ReleasePadSelectFlag(g_currentWorld);
            }
        }
        self->state = state;
    self->stateTime = g_elapsedTime[0];
    switch (state) {
    case 0:
        if (g_memoryCard.displayMode == 0) SetMemoryCardDisplayMode(&g_memoryCard, 1);
        SetScreenFadeMode(&g_screenFade, 0);
        ApplyStackTimeScale(self, 1.0f);
        break;
    case 1:
        ApplyStackTimeScale(self, 1.0f);
        D_00272930.vt->m14(&D_00272930);
        D_00272B98.vt->m14(&D_00272B98);
        AcquirePadSelectFlag(g_currentWorld);
        InitPadPatternSetting();
        break;
    case 2:
        ApplyStackTimeScale(self, 1.0f);
        break;
    case 3:
        ApplyStackTimeScale(self, 1.0f);
        g_previousSoundLevel = -100;
        break;
    case 5:
    case 7:
        ApplyStackTimeScale(self, 0.0f);
        break;
    case 8:
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
        break;
    }
    }
}

void ApplyStackTimeScale(float x)
{
    if (0.0f < g_gameTime[0]) {
        float t = (1.0f - x) * 0.6f + x;
        SetVolumeChannelFactor(4, 1, t);
        SetVolumeChannelFactor(4, 0, t);
    }
    SetGameClockScale(x);
}

s32 AreMenusAndFadeClear(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (IsPadSelectFlagHeld((World*)g_currentWorld) != 0) goto fail;
    if (g_pauseMenuElement.open != 0 && g_pauseMenuElement.page != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode != 0) goto fail;
    if (D_00270458 == 2) goto fail;
    if (D_00270458 == 1) goto fail;
    if (D_00270458 != 4) goto ok;
fail:
    return 0;
ok:
    return 1;
}

s32 AreMenusClosed(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (g_pauseMenuElement.open != 0) goto fail;
    if (g_pauseMenuElement.mode != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}

s32 IsArcDrawAllowed(void)
{
    s32 m;
    if (g_screenFade.mode != 0) goto fail;
    if (g_pauseMenuElement.open != 0) goto fail;
    if (g_pauseMenuElement.mode != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode != 0) goto fail;
    m = D_00270458;
    if (m == 4) goto fail;
    if (m != 1) goto ok;
fail:
    return 0;
ok:
    return 1;
}

s32 AreArcMenusClosed(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (g_pauseMenuElement.open != 0) goto fail;
    if (g_pauseMenuElement.mode != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}

void StepMemoryChecksum(void) {
    if (D_00275C34 == 0) {
        if (g_memoryChecksumRemaining == 0) {
            g_memoryChecksumCursor = (u32*)0x100004;
            g_memoryChecksumRemaining = (s32)D_00148D7C;
            g_memoryChecksumValue = 0xFFFFFFFF;
        }
    }
    if (g_memoryChecksumRemaining == 0) {
        return;
    }
    u32* p = g_memoryChecksumCursor;
    s32 cnt = g_memoryChecksumRemaining;
    u32 h = g_memoryChecksumValue;
    for (s32 i = 0; i < 32 && cnt > 0; i++) {
        u32 w = *p;
        cnt -= 4;
        p++;
        h = Crc32::Step(h, w);
        h = Crc32::Step(h, w >> 8);
        h = Crc32::Step(h, w >> 16);
        h = Crc32::Step(h, w >> 24);
    }
    g_memoryChecksumCursor = p;
    g_memoryChecksumValue = h;
    g_memoryChecksumRemaining = cnt;
    if (cnt == 0 && h != 0) {
        D_00275C34 = 1;
    }
}

void UpdateWorldDeltaLists(World* self, f32 dt)
{
    StepMemoryChecksum();
    SwitchedCollider* h = GetActiveSwitchedCollider();
    if (h != 0) {
        const Desc05* vt = h->desc05();
        if (vt->m49 != 0) {
            PadRecord* a;
            if ((*(s32*)&g_padRouting) & 2)
                a = &g_padRecord;
            else
                a = &g_blankPadRecord;
            vt->m49(h, dt, a);
        }
    }
    UpdateWorldObjectLists(self);
    {
        ListFrame it;
        BeginByteWalk::Of(&it, (List01*)&self->list60);
        for (u8* n = NextByte::Of(&it); n != 0; n = NextByte::Of(&it)) {
            UpdateObjectTree(n, dt);
        }
        EndByteWalk::Of(&it);
    }
    {
        ListFrame it;
        BeginByteWalk::Of(&it, (List01*)&self->f1B64);
        for (u8* n = NextByte::Of(&it); n != 0; n = NextByte::Of(&it)) {
            UpdateAnimationPlayer(n, dt);
        }
        EndByteWalk::Of(&it);
    }
    {
        ListFrame it;
        BeginByteWalk::Of(&it, (List01*)&self->f1C24);
        for (u8* n = NextByte::Of(&it); n != 0; n = NextByte::Of(&it)) {
            StepObjectLevelRamp(n, dt);
        }
        EndByteWalk::Of(&it);
    }
    DispatchDelayedMessages(self);
    UpdateSoundEmitters();
    RunQueuedCalls(self);
}

void UpdateUnflaggedParts(World* self)
{
    ListFrame frame;
    Collider* s1 = (Collider*)self->list6C.head;
    if (s1 != 0) {
        do {
            Collider* s0 = (Collider*)s1->parts.head;
            if (s0 != 0) {
                do {
                    u64 bit = (u64)1 << 53;
                    if ((s0->flags538 & bit) == 0) {
                        ((Desc03*)s0->desc)->m44(s0);
                    }
                    s0->flags538 &= ~bit;
                    s0 = (Collider*)s0->link2E4.next;
                } while (s0 != 0);
            }
            s1 = (Collider*)s1->link414.next;
        } while (s1 != 0);
    }
}

void UpdateWorldStepLists(World* self, f32 dt)
{
    if (dt == 0.0f) return;
    ListFrame it;
    BeginNodeWalk::Of(&it, &self->list78);
    for (ListedObject* obj = NextNode::Of(&it); obj; obj = NextNode::Of(&it)) UpdateObjectTree(obj, dt);
    EndNodeWalk::Of(&it);
    BeginNodeWalk::Of(&it, (List01*)&self->f1B70);
    for (ListedObject* obj = NextNode::Of(&it); obj; obj = NextNode::Of(&it)) UpdateAnimationPlayer(obj, dt);
    EndNodeWalk::Of(&it);
    BeginNodeWalk::Of(&it, (List01*)&self->f1C30);
    for (ListedObject* obj = NextNode::Of(&it); obj; obj = NextNode::Of(&it)) StepObjectLevelRamp(obj, dt);
    EndNodeWalk::Of(&it);
    BeginNodeWalk::Of(&it, &self->list78);
    for (ListedObject* obj = NextNode::Of(&it); obj; obj = NextNode::Of(&it)) obj->vtbl->update(obj, 0, dt);
    EndNodeWalk::Of(&it);
    RunQueuedCalls(self);
}

void StepWorldValueTowardTarget(World* self, f32 x)
{
    World* o = self;
    f32 a = o->f234C;
    f32 b = o->f2350;
    if (b < a) {
        o->f234C = ApproachValueWithRamp(D_00275C18, 0, a, b, x);
    } else if (a < b) {
        o->f234C = ApproachValueWithRamp(D_00275C28, 0, a, b, x);
    }
}

void UpdateWorld(World* self)
{
    ListFrame it;
    GameClock* clock = &g_gameClock;
    UpdateWorldStepLists(self, clock->step);
    if (clock->dt != 0.0f) {
        UpdateWorldDeltaLists(self, clock->dt);
        UpdateUnflaggedParts(self);
        UpdateWorldContacts(self, 0);
        ProcessColliderGroups(self, 1, clock->dt);
        BeginActorWalk::Of(&it, &self->list6C);
        for (Actor6C* obj; (obj = NextActor::Of(&it)) != 0;) {
            if (obj->vtable->update != 0) {
                obj->vtable->update(obj, clock->dt);
            }
        }
        g_activeListFrames = it.prev;
        UpdateWorldContacts(self, 1);
        ProcessColliderGroups(self, 6, g_gameClock.dt);
        BeginActorWalk::Of(&it, &self->list60);
        for (Actor6C* obj; (obj = NextActor::Of(&it)) != 0;) {
            if (obj->tries < 2) {
                if (IsObjectTreeAtRest(obj) != 0) {
                    obj->tries++;
                } else {
                    ClearRootTries(obj);
                }
            }
        }
        g_activeListFrames = it.prev;
        BeginActorWalk::Of(&it, &self->list6C);
        for (Actor6C* obj; (obj = NextActor::Of(&it)) != 0;) {
            obj->vtable->post(obj);
            if (obj->flags & 0x8000000000000000ULL) {
                UpdateTouchingParts(obj);
            }
        }
        g_activeListFrames = it.prev;
        RunDueDelayedScriptCalls(self, g_gameClock.dt);
        RunQueuedCalls(self);
        StepAnimators(g_gameClock.dt);
    }
    NotifyWorldActiveFollower(self);
    BeginActorWalk::Of(&it, &self->list1B7C);
    for (Actor6C* obj; (obj = NextActor::Of(&it)) != 0;) {
        ReleaseWorldListEntry(obj);
    }
    g_activeListFrames = it.prev;
    UpdateCamera(g_camera, 1, g_gameClock.dt);
    StepWorldValueTowardTarget(self, g_gameClock.step);
}

f32 WrapAngle(f32 a)
{
    f32 r = a;
    if (a < -3.1415927f || a > 3.1415927f) {
        r = WrapModulo(a + 3.1415927f, 6.2831855f) - 3.1415927f;
    }
    return r;
}

f32 ClampToMagnitude(f32 a, f32 b)
{
    f32 r = a;
    if (b < r) {
        r = b;
    } else {
        b = -b;
        if (r < b) {
            r = b;
        }
    }
    return r;
}

f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z)
{
    f32 roots[4];
    s32 flip = 0;
    f32 d = x - y;
    f32 c = z;
    f32 half;
    f32 t;
    f32 res;
    f32 r;
    if (d < 0.0f) {
        flip = 1;
        d = -d;
    }
    half = (k->endSpeed + k->maxSpeed) * k->rampTime * 0.5f;
    if (half <= d) {
        f32 u = (d - half) / k->maxSpeed;
        if (c <= u) {
            res = d - k->maxSpeed * c;
            t = -k->maxSpeed;
            goto tail;
        }
        c = c - u;
        d = half;
    }
    SolveQuadratic((k->maxSpeed - k->endSpeed) / (k->rampTime + k->rampTime), k->endSpeed, -d, roots);
    r = roots[0] - c;
    if (0.0f < r) {
        res = (k->maxSpeed - k->endSpeed) * r * r / (k->rampTime + k->rampTime) + k->endSpeed * r;
        t = -(k->endSpeed + (k->maxSpeed - k->endSpeed) * r / k->rampTime);
    } else {
        t = -k->endSpeed;
        res = 0.0f;
    }
tail:
    if (flip) {
        res = y - res;
        if (out) {
            *out = -t;
        }
    } else {
        res = res + y;
        if (out) {
            *out = t;
        }
    }
    return res;
}

f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, void* self, f32* out)
{
    RampProfile* o = (RampProfile*)self;
    f32 tmp;
    f32 res = ApproachValueWithRamp(a, c, d, self, &tmp);
    f32 k = o->maxAccel;
    if (0.0f < k) {
        f32 hi = b + k * d;
        f32 lo = b - k * d;
        if (hi < tmp) {
            tmp = hi;
            res = a + b * d + (k * (d * 0.5f)) * d;
        } else if (tmp < lo) {
            tmp = lo;
            res = a + b * d - (k * (d * 0.5f)) * d;
        }
    }
    if (out != 0) *out = tmp;
    return res;
}

LINKER_REMNANT(func_001EA720);

f32 ApproachAngleWithRamp(f32 a, f32 b, f32 c, void* self, f32* out)
{
    f32 t = WrapAngle(b - a);
    f32 r = ApproachValueWithRamp(0.0f, t, c, self, out);
    return WrapAngle(a + r);
}

f32 ApproachAngleClampingVelocity(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1)
{
    f32 t = WrapAngle(f14 - f12);
    f32 r = ApproachValueClampingVelocity(0.0f, f13, t, f15, self, a1);
    return WrapAngle(f12 + r);
}

// from moved towards to by the ramp's step over the distance between them (limit the ramp's
// third value), the velocity stored to vel when it is given; to itself, and a zero velocity,
// when the two are nearer than 1e-4. The vectors are Vu0::Vec values: each inline call copies
// the difference into a pseudo of its own, so retail's difference lives in the frame across the
// call and its copy in vf3 is caller-saved, and the limit comes before the ramp in the prototype
// as the other callers have it: retail moves it to $f14 first.
u128 ApproachPointWithRamp(u128 from, u128 to, f32 limit, RampProfile* ramp, Vec02* vel)
{
    f32 step;
    Vu0::Vec f;
    Vu0::Vec t;
    f.q = from;
    t.q = to;
    Vu0::Vec d;
    d = Vu0::Sub(t, f);
    f32 len = Vu0::ToFloat(Vu0::Length(d));
    if (0.0001f < len) {
        f32 travel = ApproachValueWithRamp(0.0f, len, limit, ramp, &step);
        if (vel != 0) {
            *(Vu0::Vec*)vel = Vu0::MulX(d, Vu0::Vec::Scalar(step / len));
        }
        return Vu0::MulAddX(f, d, Vu0::Vec::Scalar(travel / len)).q;
    }
    if (vel != 0) {
        *vel = D_00248D30;
    }
    return to;
}

void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, f32* axis);
void BuildAxisAngleMatrix(Vec02* axis, Mat02* out, f32 angle);

void ApproachRotationWithRamp(Mat02* from, Mat02* to, RampProfile* ramp, Mat02* outRot, Vec02* outSpin, f32 limit)
{
    Mat02 rel;
    Mat02 built;
    Vec02 axis;
    f32 angle;
    f32 step;
    MultiplyMatrices3x3(from, to, &rel);
    MatrixToAxisAngle(&rel, &angle, (f32*)&axis);
    f32 a = angle;
    f32 travel = ApproachValueWithRamp(0.0f, a, limit, ramp, &step);
    if (outRot != 0) {
        if (travel == angle) {
            *outRot = *to;
        } else {
            BuildAxisAngleMatrix(&axis, &built, travel);
            MulRotationRowsX(outRot, built, *from);
        }
    }
    if (outSpin != 0) {
        Vu0::Q(*outSpin) = Vu0::MulX(Vu0::Q(axis), Vu0::ScalarAt(step));
    }
}

s32 RandomIntInRange(s32 a, s32 b)
{
    if (a == b) {
        return a;
    }
    s32 r = (s32)(u32)NextRandom();
    s32 span = b - a + 1;
    r = r % 0x95675;
    r = r % span;
    return a + r;
}

f32 RandomFloatInRange(f32 a, f32 b)
{
    f32 r;
    if (a != b) {
        s32 n = NextRandom();
        r = a + (b - a) * (f32)n * 0.0000000004656613f;
    } else {
        r = a;
    }
    return r;
}

f32 RandomGaussian(f32 mean, f32 deviation, f32 limit)
{
    f32 x;
    f32 y;
    f32 r;
    do {
        x = RandomFloatInRange(-1.0f, 1.0f);
        y = RandomFloatInRange(-1.0f, 1.0f);
        r = x * x + y * y;
    } while (r > 1.0f || r == 0.0f);
    f32 v = mean + deviation * y * Fpu::Sqrt(Logarithm(r) * -2.0f / r);
    if (limit != 0.0f) {
        f32 lo = mean - limit;
        f32 hi = mean + limit;
        if (v < lo) {
            v = lo;
        } else if (hi < v) {
            v = hi;
        }
    }
    return v;
}

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 tolerance)
{
    f32 scale = 1.0f;
    scale = scale >? __builtin_fabsf(a);
    return __builtin_fabsf(a - b) / scale < tolerance;
}

s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots)
{
    f32 disc = b * b - a * (4.0f * c);
    if (disc < 0.0f) {
        return 0;
    }
    a = a + a;
    disc = Fpu::Sqrt(disc) / a;
    b = b / a;
    if (__builtin_fabsf(disc) < 0.0001f) {
        roots[0] = -b;
        return 1;
    }
    roots[0] = -b + disc;
    roots[1] = -b - disc;
    return 2;
}

void RemapQuadraticParameter(Vec3* in, f32 s, f32 t, Vec3* out)
{
    out->z = in->z * s * s;
    out->y = (in->z + in->z) * s * t + in->y * s;
    out->x = (in->z * t * t + in->y * t) + in->x;
}

void ComputeSinCos(f32* sinOut, f32* cosOut, f32 angle)
{
    f32 t = (angle + 1.5707964f) * 0.31830987f;
    s32 n = (s32)t;
    if (t < 0.0f) {
        n--;
    }
    angle -= (f32)n * 3.1415927f;
    if (n & 1) {
        angle = -angle;
    }
    f32 x2 = angle * angle;
    f32 s = angle;
    angle *= x2;
    s += angle * -0.166666567f;
    angle *= x2;
    s += angle * 0.00833302550f;
    angle *= x2;
    s += angle * -0.000198074136f;
    angle *= x2;
    s += angle * 2.60188699e-06f;
    f32 c = Fpu::Sqrt(1.0f - s * s);
    if (n & 1) {
        *cosOut = -c;
    } else {
        *cosOut = c;
    }
    *sinOut = s;
}

double TruncateDouble(double x)
{
    DoubleBits v;
    v.d = x;
    s32 e = ((u16)(v.u >> 52) & 0x7FF) - 0x3FF;
    if (e < 0) {
        return 0.0;
    }
    if (e < 0x34) {
        u64 frac = ((u64)1 << (0x34 - e)) - 1;
        u64 mant = v.u & ((u64)-1 >> 12);
        if ((mant & frac) == frac) {
            v.u = (v.u & ((u64)0xFFF0 << 48)) | (mant & ~frac & ((u64)-1 >> 12));
            x = v.d;
            x = AddDoubles(x, 1.0);
        } else {
            v.u = (v.u & ((u64)0xFFF0 << 48)) | (mant & ~frac & ((u64)-1 >> 12));
            x = v.d;
        }
    }
    return x;
}

f32 TruncateFloat(f32 x)
{
    f32 buf[2];
    u64* qp = (u64*)buf;
    buf[0] = x;
    u64 bits = *qp;
    u32 ex = (u32)((s64)(bits << 9) >> 32) & 0xFF;
    s32 e = (s32)ex - 0x7F;
    if (e < 0)
        return 0.0f;
    if (e < 0x17) {
        s32 mask = (s32)(((u64)1 << (0x17 - e)) - 1);
        s32 frac = *(s32*)buf & 0x7FFFFF;
        if ((frac & mask) == mask) {
            { u64 lo = (u64)(s64)(frac & ~mask); *qp = (bits & (s32)0xFF800000) | lo; }
            buf[0] = buf[0] + 1.0f;
        } else {
            { u64 lo = (u64)(s64)(frac & ~mask); *qp = (bits & (s32)0xFF800000) | lo; }
        }
    }
    return buf[0];
}

f32 WrapModulo(f32 x, f32 y)
{
    f32 r = FloatRemainder(x);
    if (r < 0.0f) {
        r += y;
    }
    return r;
}

void FitQuadraticCurve(f32* a0, f32 x, f32 y, f32 z, f32 w)
{
    f32 p = w - x;
    f32 q = y - x;
    a0[0] = x;
    f32 r = p / z - q;
    r = r / (z - 1.0f);
    a0[2] = r;
    a0[1] = q - r;
}

s32 IsInsideRange(ValueRange* span, f32 x)
{
    s32 inside = 0;
    if (span->lo < x) {
        if (x < span->hi) {
            inside = 1;
        }
    }
    return inside;
}

s32 IsInsideAnyRange(s32 count, ValueRange* spans, f32 x)
{
    for (s32 i = 0; i < count; i++) {
        if (IsInsideRange(&spans[i], x)) {
            return 1;
        }
    }
    return 0;
}

f32 ClampToRange(ValueRange* span, f32 x)
{
    if (x < span->lo) {
        return span->lo;
    }
    if (span->hi < x) {
        return span->hi;
    }
    return x;
}

s32 CompareFloats(f32* a, f32* b)
{
    f32 x = *a;
    f32 y = *b;
    if (y < x) return 1;
    if (x < y) return -1;
    return 0;
}

void IgnoreStackLocal(void)
{
}

// A sample FindLocalMinimum keeps: an argument and the function's value there.
struct MinimumSample {
    f32 x;
    f32 y;
};

typedef f32 (*MinimumFn)(void* ctx, f32 x);

void FindLocalMinimum(MinimumFn fn, void* ctx, f32 x, f32 step, f32 lo, f32 hi, f32* outX, f32* outY)
{
    // The bracket's low end, the midpoint below the middle, the middle, the midpoint above it
    // and the high end.
    MinimumSample s[5];
    x = x < lo ? lo : (hi < x ? hi : x);
    s[0].x = lo >? x - step;
    s[0].y = fn(ctx, s[0].x);
    s[2].x = x;
    s[2].y = fn(ctx, s[2].x);
    s[4].x = hi <? x + step;
    s[4].y = fn(ctx, s[4].x);
    for (;;) {
        if (s[0].y < s[2].y) {
            s[4] = s[2];
            s[2] = s[0];
            s[0].x = lo >? s[2].x + s[2].x - s[4].x;
            s[0].y = fn(ctx, s[0].x);
        } else if (s[4].y < s[2].y) {
            s[0] = s[2];
            s[2] = s[4];
            s[4].x = hi <? s[2].x + s[2].x - s[0].x;
            s[4].y = fn(ctx, s[4].x);
        } else {
            break;
        }
    }
    for (s32 i = 9; i >= 0; i--) {
        s[1].x = (s[0].x + s[2].x) * 0.5f;
        s[1].y = fn(ctx, s[1].x);
        s[3].x = (s[2].x + s[4].x) * 0.5f;
        s[3].y = fn(ctx, s[3].x);
        if (s[1].y < s[2].y) {
            if (s[1].y < s[3].y) {
                s[4] = s[2];
                s[2] = s[1];
            } else {
                s[0] = s[2];
                s[2] = s[3];
            }
        } else if (s[2].y <= s[3].y) {
            s[0] = s[1];
            s[4] = s[3];
        } else {
            s[0] = s[2];
            s[2] = s[3];
        }
    }
    if (outX != 0) {
        *outX = s[2].x;
    }
    if (outY != 0) {
        *outY = s[2].y;
    }
}

LINKER_REMNANT(func_001EB458);

void InitBeatPressCollider(BeatPressCollider* self)
{
    InitSwitchedCollider(self);
    f32 t = g_currentEntry->dt;
    f32 x = D_00275C80[0] + t * (D_00275C80[1] + t * D_00275C80[2]);
    f32 lo = g_unitRange.lo;
    f32 hi = g_unitRange.hi;
    f32 c;
    if (x < lo) {
        c = lo;
    } else if (hi < x) {
        c = hi;
    } else {
        c = x;
    }
    self->f684 = (1.0f - c) * D_00275C70[0] + c * D_00275C70[1];
}

void LoadBeatPressCollider(BeatPressCollider* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, D_00275C90);
}

void CopyPlayerAttachBlock(BeatPressCollider* a0)
{
    a0->blk580 = g_player->blk580;
    a0->f604 = g_player->f604;
}

void StartBeatPressCollider(BeatPressCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 4, D_00275CA0);
    self->f614 = CreateStateWalker(self->f610, self, 0x4CA, 1);
    AppendQueuedCall(self->world, (void*)CopyPlayerAttachBlock, self, 0, 0);
}

void HandleBeatPressColliderActivation(BeatPressCollider* self, void* p)
{
    HandleSwitchedColliderActivation(self);
    TempoAgent* r = (TempoAgent*)FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
    if (p != 0) {
        SetStateWalkerTarget(self->f614, 0x4CB);
        r->fC3C = self;
        self->f68C = r;
    } else {
        SetStateWalkerTarget(self->f614, 0x4CA);
        *(f32*)((u8*)g_player + 0x26D0) = 2.0f;
    }
}

void TurnColliderTowardHeading(Player* self);
void SetPlayerState(Player* self, s32 a, s32 b);

void ContinueBeatPressColliderRequest(PlacedObject* from, Player* self)
{
    Vec02 dir;
    Vu0::Q(dir) = Vu0::MulXSum(Vu0::Q(from->m110.r[0]), Vu0::Scalar(-D_00275CD0), Vu0::Q(from->m110.r[2]), Vu0::ScalarAt(D_00275CD4));
    self->desc02()->m20(self, &dir);
    self->f638 = WrapAngle(ArctangentOfRatio(dir.y, dir.x) + 3.1415927f);
    TurnColliderTowardHeading(self);
    SetPlayerState(self, 4, 0x2B);
}

void JudgeBeatPressInput(BeatPressCollider* self, PadRecord* in)
{
    if (self->f67C != 0 && g_player != 0) {
        Vec4U pos;
        Mat3U mat;
        GetObjectWorldPosition(self->f67C, &pos);
        GetObjectWorldRotation(self->f67C, &mat);
        ((PlayerSlotFn*)g_player->desc)[0x84 / 4](g_player, &pos);
        ((PlayerSlotFn*)g_player->desc)[0x88 / 4](g_player, &mat);
        ((BeatPressSlotFn*)self->desc)[0x84 / 4](self, &pos);
        ((BeatPressSlotFn*)self->desc)[0x88 / 4](self, &mat);
    }
    if (self->f680 != 0) {
        u32 f = in->flags;
        if (f & 0xF0) {
            s32 dir;
            s32 ok;
            f32 at;
            if (f & 0x80) {
                dir = 0;
            } else if (f & 0x10) {
                dir = 1;
            } else if (f & 0x20) {
                dir = 2;
            } else if (f & 0x40) {
                dir = 3;
            }
            ok = 0;
            if (self->f62C < self->f630) {
                Ent1C* e = &self->f634[self->f62C];
                if (e->dir == dir) {
                    TempoAgent* g = ((TempoAgent*)self->f68C);
                    at = (f32)g->fC70 * 4.0f + g->fC7C;
                    if (__builtin_fabsf(e->t - at) < self->f684 * 0.5f) {
                        ok = 1;
                    }
                }
            }
            if (ok) {
                self->f678 = dir;
                self->f674 = at;
            } else {
                StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
    }
    if (self->f62C < self->f630) {
        Ent1C* e = &self->f634[self->f62C];
        TempoAgent* g = ((TempoAgent*)self->f68C);
        f32 at = (f32)g->fC70 * 4.0f + g->fC7C;
        f32 win = self->f684;
        if (self->f678 == e->dir && __builtin_fabsf(e->t - self->f674) < win * 0.5f) {
            SetStateWalkerTarget(self->f614, D_00275CD8[self->f678]);
            StartSoundEffect(D_00275CE8[self->f678], 0, 0, 0, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0, 0);
        } else {
            if (!(at - e->t > win * 0.5f)) {
                return;
            }
            StartSoundEffect(0x51, 0, 0, 0, 30000.0f, 20000.0f, 1.5f, 0.3f, 0.0f, 0, 0);
            if (HasSpareCount() == 0 && ((BeatPressSlotFn*)self->desc)[0x13C / 4](self, 0) == 0) {
                OwnerMessage msg;
                TempoAgent* o;
                ActivateSwitchedCollider(g_player);
                InitOwnerMessage(&msg, 0, self);
                msg.fn = (void (*)(void))ContinueBeatPressColliderRequest;
                ((s32 (*)(Player*, OwnerMessage*))((PlayerSlotFn*)g_player->desc)[0x140 / 4])(g_player, &msg);
                o = (TempoAgent*)FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
                EndHeldTimeline(o);
                o->fBFC = g_gameTime[0];
                SetCachedVoiceParam(2, 1);
                goto next;
            }
            if (((BeatPressSlotFn*)self->desc)[0x13C / 4](self, 0) == 0) {
                Timeline* l;
                ((void (*)(BeatPressCollider*))((BeatPressSlotFn*)self->desc)[0x150 / 4])(self);
                Player* gl = g_player;
                self->f688 = 1;
                gl->f26C4 = 1;
                f32 v = g_gameTime[0];
                *(f32*)((u8*)gl + 0x26CC) = v;
                gl->f26C8 = v;
                l = ((TempoAgent*)self->f68C)->fC38;
                *(f32*)((u8*)gl + 0x26D0) = 2.0f;
                if (l != 0) {
                    s32 j = l->index;
                    while (j < l->f34) {
                        Entry90* p = &((Entry90*)l->buffer)[j];
                        if (p->f0 == 3) break;
                        j++;
                    }
                    if (j < l->f34) {
                        Entry90* it = &((Entry90*)l->buffer)[j];
                        TempoAgent* gg = ((TempoAgent*)self->f68C);
                        *(f32*)((u8*)g_player + 0x26D0) = ((f32)it->f4 * 4.0f + it->f8 - ((f32)gg->fC70 * 4.0f + gg->fC7C)) * gg->fC88;
                    }
                }
            }
        }
        if (e->dir == 3) {
            ActivateSwitchedCollider(g_player);
            BindEntryQueueToObject(self->f628, g_player);
            self->f628 = 0;
        }
    next:
        self->f62C++;
        if (self->f62C == self->f630) {
            self->f62C = 0;
            self->f630 = 0;
        }
    }
}

s32 IsBeatPressColliderRequestBlocked(BeatPressCollider* self)
{
    if (g_buttonCodeFlags & 1) return 1;
    if (IsPadSelectFlagHeld(self->world) == 0) return self->f688 != 0;
    return 1;
}

void AppendBeatPressEntry(BeatPressCollider* list, const U64P* src)
{
    s32 n = list->f630;
    list->f630 = n + 1;
    U64P* dst = (U64P*)((u8*)list + (n * 8 + 0x634));
    *dst = *src;
}

s32 AcceptBeatPressColliderRequest(void)
{
    return 0;
}

// What GetBeatPressColliderPositionAt reads of its f67C: an object to place at a time (+0x18), a
// point in its frame (+0x40) and the rotation func_001EBDD0 turns the object's by (+0x50).
struct FramePoint_001EBD10 {
    u8 pad0[0x18];
    void* object;           // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 point;            // 0x40
    Mat02 m50;              // 0x50
};

void GetPlacedObjectPositionAt(void* self, f32 t, Vec02* pos, Vec02* vel);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, Vec02* e, Vec02* f, f32 t);

void GetBeatPressColliderPositionAt(BeatPressCollider* self, f32 t, Vec02* pos, Vec02* vel)
{
    if (self->f67C == 0) {
        GetPlacedObjectPositionAt(self, t, pos, vel);
        return;
    }
    Vec02 p;
    Mat02 rot;
    Vec02 v;
    Vec02 w;
    ComputeObjectFrameAtTime(((FramePoint_001EBD10*)self->f67C)->object, 0, &p, &rot, &v, &w, t);
    Vu0::Q(*pos) = Vu0::Add(Vu0::Q(p), Vu0::Rotate(rot, Vu0::Q(((FramePoint_001EBD10*)self->f67C)->point)));
    Vu0::Q(*vel) = Vu0::Add(Vu0::Q(v), Vu0::Cross(Vu0::Q(w), Vu0::Q(((FramePoint_001EBD10*)self->f67C)->point)));
}

void GetPlacedObjectRotationAt(void* self, f32 t, Mat02* rot, Vec02* spin);

void GetBeatPressColliderRotationAt(BeatPressCollider* self, f32 t, Mat02* rot, Vec02* spin)
{
    if (self->f67C == 0) {
        GetPlacedObjectRotationAt(self, t, rot, spin);
        return;
    }
    Mat02 m;
    Vec02 w;
    ComputeObjectFrameAtTime(((FramePoint_001EBD10*)self->f67C)->object, 0, 0, &m, 0, &w, t);
    FramePoint_001EBD10* f = (FramePoint_001EBD10*)self->f67C;
    MulRotationRowsIndexed(rot, m, f->m50);
    *spin = w;
}

void InitTempoAgent(TempoAgent* self)
{
    InitAgent(self);
    *(s32*)((u8*)self + 0xC5C) = 0x3C;
    self->fC8C = 1.0f;
    self->fC64 = 8.0f;
    self->fC70 = 0;
    self->fC78 = -1;
    self->fC74 = -1;
    self->fC60 = 8;
    *(s32*)((u8*)self + 0xC6C) = (s32)AllocateFrontMemory(0x400);
    self->world->f2358 = 1;
    StopStagedBankVoice();
    D_00275DB8 = 2;
    D_00275DBC = 0;
}

s32 ResolveAgentClip(void* self, s32 id);
void LoadAgent(Agent* self, void* reader);
void LoadTempoAgent(TempoAgent* self, void* reader)
{
    LoadAgent(self, reader);
    for (s32 i = 0; i < 4; i++) {
        self->fC10[i] = ResolveAgentClip(self, D_00275CF8[i]);
    }
}

void StartTempoAgent(TempoAgent* self)
{
    StartAgent(self);
    SetWorldActiveFollower(self->world, self);
    ResolveObjectLinks(self, 5, D_00275D08);
    void* r = CreateStateWalker(self->fC50, 0, -1, 0);
    self->fC54 = r;
    AddStateWalkerListener(r, self);
    self->fC98 = 9;
    self->fC9C = CopyToFrontMemory(0x6C, D_00275D48);
    s32 i = 0;
    if (self->fC98 > 0) {
        s32 off = 0;
        do {
            TempoObjectRef* e = (TempoObjectRef*)((u8*)self->fC9C + off);
            e->obj = FindFirstObjectById(self->world, 1, e->id, self);
            i++;
            off += 12;
        } while (i < self->fC98);
    }
}


void UnregisterTempoAgent(void)
{
    UnregisterSwitchedCollider();
}

void RegisterTempoAgent(void)
{
    RegisterSwitchedCollider();
}

s32 IsTempoAgentTargetInRange(TempoAgent* self)
{
    s32 r[4];
    GetStateWalkerCurrentKey(self->fC54, r);
    switch (r[0]) {
    case 0x4ED:
    case 0x4F0:
    case 0x4F3:
    case 0x4F6:
        if (self->fC20 == 0) goto zero;
    yes:
        return 1;
    case 0x4EE:
    case 0x4F1:
    case 0x4F4:
    case 0x4F7:
        if (self->fC94 == 1) goto zero;
        if (self->fC94 < 2) {
            if (self->fC94 == 0) goto set;
            return 0;
        }
        if (self->fC94 == 2) goto yes;
        return 0;
    set:
        self->fC94 = 1;
    }
zero:
    return 0;
}

s32 IsTempoAgentFree(void)
{
    return 1;
}

typedef int Quadword128 __attribute__((mode(TI)));
void* StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(void* dst, Quadword128 v);
AnimRecord* FindAnimRecord(s32 key);
void DrawAngleSortedRing(void* at, s32 nOffsets, f32* offsets, s32 nAnchors, void* anchors, RingParams* params, void* request);
extern f32 D_00275070[14];

// k times the quadword at p, into dst (the quadword helpers' product).
static inline void StoreScaledQuadword(void* dst, f32 k, void* p)
{
    Quadword128 t;
    StoreFloatAsQuadword(&t, k);
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword(&u, p);
    StoreQuadword(dst, ScaleQuadword(tv, u));
}

// The tempo agent's ring: the block's defaults are built once, as a function-local static with
// a brace initialiser (include/ring_params.h), and copied for each draw, where rows 1 and 2 are
// scaled by the agent's level. DrawTempoAgent queues it as a deferred request's callback, the
// agent the request's argument.
void DrawTempoAgentRing(DeferredRequest* request)
{
    TempoAgent* agent = (TempoAgent*)request->arg;
    static RingParams defaults = {
        1, 10.0f, 0.25f,
        {
            { { 0.0f, 0.0f, 0.0f }, 0.0f, 100.0f, RingColor(0x80FFFFFF) },
            { { 0.0f, 0.5f, 0.0f }, 0.0f, 50.0f, RingColor(0x80FFFFFF) },
            { { 500.0f, 1.0f, 0.0f }, 1.0f, -100.0f, RingColor(0x80FFFFFF) },
        },
    };
    if (agent->f298 != 0) {
        RingParams params = defaults;
        params.textures[0] = 0;
        params.textures[1] = FindAnimRecord(0x15D);
        f32 level = agent->f298->level;
        StoreScaledQuadword(&params.rows[1].shape, level * level, &params.rows[1].shape);
        StoreScaledQuadword(&params.rows[2].shape, agent->f298->level, &params.rows[2].shape);
        DrawAngleSortedRing(&agent->v140, 7, D_00275070, agent->fC98, agent->fC9C, &params, request);
    }
}

// The file's data from here on follows the static's guard (D_00275DB4) in retail's .data.
// size: s32 state compared/assigned in 001EC000
s32 D_00275DB8 = 0;
INCLUDE_DATA(D_00275DBC);
s32 D_00275DD0[16] = { 4, 2, 1, -1, 8, 4, 2, -1, 12, 6, 3, -1, 16, 8, 4, 2 };
s32 D_00275E10[92] = { 2, 0x2EB, 0x2DC };
// word read whole / address only, 4 bytes to next label
ScreenFade g_screenFade = { 0 };
f32 D_00275FC0 = 0.5f;
// Globals defined from C.
s32 D_00275FC8[6] = { 0, 2, 4, 4, 4, 0 };
ObjectLink D_00275FE0[52] = {
    { 0x2, 0x1CB, 0x2E4 },
    { 0x2, 0x1CC, 0x2E8 },
    { 0x2, 0x1CD, 0x2F8 },
    { 0x2, 0x1CE, 0x32C },
    { 0x2, 0x1CF, 0x360 },
    { 0x2, 0x1D0, 0x394 },
    { 0x2, 0x1D1, 0x3C8 },
    { 0x2, 0x1D2, 0x3FC },
    { 0x2, 0x1D3, 0x430 },
    { 0x2, 0x1D4, 0x464 },
    { 0x2, 0x1D5, 0x498 },
    { 0x2, 0x1D6, 0x500 },
    { 0x2, 0x1E2, 0x304 },
    { 0x2, 0x1E3, 0x338 },
    { 0x2, 0x1E4, 0x36C },
    { 0x2, 0x1E5, 0x3A0 },
    { 0x2, 0x1E6, 0x3D4 },
    { 0x2, 0x1E7, 0x408 },
    { 0x2, 0x1E8, 0x43C },
    { 0x2, 0x1E9, 0x470 },
    { 0x2, 0x1EA, 0x4A4 },
    { 0x2, 0x1EC, 0x50C },
    { 0x2, 0x1EB, 0x4D8 },
    { 0x2, 0x1D7, 0x2FC },
    { 0x2, 0x1D8, 0x330 },
    { 0x2, 0x1D9, 0x364 },
    { 0x2, 0x1DA, 0x398 },
    { 0x2, 0x1DB, 0x3CC },
    { 0x2, 0x1DC, 0x400 },
    { 0x2, 0x1DD, 0x434 },
    { 0x2, 0x1DE, 0x468 },
    { 0x2, 0x1DF, 0x49C },
    { 0x2, 0x1E1, 0x504 },
    { 0x2, 0x1E0, 0x4D0 },
    { 0x2, 0x1F8, 0x310 },
    { 0x2, 0x1F9, 0x378 },
    { 0x2, 0x1FA, 0x3AC },
    { 0x2, 0x1FB, 0x3E0 },
    { 0x2, 0x1FC, 0x414 },
    { 0x2, 0x1FD, 0x448 },
    { 0x2, 0x1FE, 0x47C },
    { 0x2, 0x1FF, 0x4B0 },
    { 0x2, 0x1ED, 0x30C },
    { 0x2, 0x1EE, 0x340 },
    { 0x2, 0x1EF, 0x374 },
    { 0x2, 0x1F0, 0x3A8 },
    { 0x2, 0x1F1, 0x3DC },
    { 0x2, 0x1F2, 0x410 },
    { 0x2, 0x1F3, 0x444 },
    { 0x2, 0x1F4, 0x478 },
    { 0x2, 0x1F5, 0x4AC },
    { 0x2, 0x1F7, 0x514 },
};
s32 D_00276250 = -1;
f32 D_00276258[4] = { 600.0f, 0.0f, 0.25f, 0.0f };
f32 D_00276268[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00276278[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00276288[4] = { 1.0f, 0.0f, 0.200000003f, 0.0f };
s32 D_00276298[11][4] = {
    { 1, 10, 10, 5 },
    { 2, 0, 3, 5 },
    { -1, 1, 3, 5 },
    { 2, 10, -1, 1 },
    { 8, -1, 5, 7 },
    { 2, 0, 1, 4 },
    { -1, 7, 7, 8 },
    { 6, 8, 4, 6 },
    { 6, -1, 7, -1 },
    { -1, -1, -1, -1 },
    { 0, -1, -1, 0 }
};
s32 D_00276348[11][4] = {
    { 4, 10, 4, 10 },
    { 8, 0, 4, 3 },
    { 5, 3, 1, -1 },
    { 2, 10, 1, -1 },
    { 7, 0, -1, 1 },
    { 8, 2, 8, -1 },
    { 8, 7, -1, 8 },
    { 6, 4, -1, 1 },
    { -1, 1, 6, 5 },
    { -1, -1, -1, -1 },
    { 3, -1, 0, -1 }
};
s32 D_002763F8[11][4] = {
    { 1, 10, 10, 1 },
    { 3, 0, 7, 2 },
    { 4, 0, 1, -1 },
    { 8, 1, 1, 4 },
    { 3, 2, 1, 2 },
    { 6, 10, -1, 8 },
    { -1, 5, -1, 8 },
    { -1, 0, 8, 1 },
    { -1, 7, 5, 7 },
    { -1, -1, -1, -1 },
    { 5, -1, -1, 0 }
};
s32 D_002764A8[11][4] = {
    { 1, 10, 10, 2 },
    { 7, 0, 4, 2 },
    { 5, 0, 1, 5 },
    { 8, 4, -1, 4 },
    { 3, 10, 3, 1 },
    { 6, 2, 1, -1 },
    { -1, 5, 7, -1 },
    { 8, 1, 8, 6 },
    { -1, 4, 3, 1 },
    { -1, -1, -1, -1 },
    { 4, -1, -1, 0 }
};
s32 D_00276558[11][4] = {
    { 2, 10, 2, 4 },
    { -1, -1, -1, -1 },
    { 3, 0, -1, 3 },
    { 8, 0, 2, 4 },
    { 5, 0, 3, 5 },
    { 6, 4, 4, -1 },
    { 8, 5, 8, -1 },
    { -1, -1, -1, -1 },
    { -1, 3, -1, 6 },
    { -1, -1, -1, -1 },
    { 0, -1, -1, 0 }
};
s32 (*D_00276608[6])[4] = { 0, (s32(*)[4])D_00276298, (s32(*)[4])D_00276348, (s32(*)[4])D_002763F8, (s32(*)[4])D_002764A8, (s32(*)[4])D_00276558 };
#ifndef VERSION_EU
// PAL has no style here (its func_001F1960 draws without one): its static initialiser only
// sets D_00276650.
WarpTextStyle D_00276620(2, 1);
#endif
INCLUDE_DATA(D_0027663C);
#ifdef VERSION_EU
// PAL's own addresses for these two, which the tools do not pair with US's (VERSION_NAME).
f32 D_eu_0027FDAC = 24.0f;
f32 D_eu_0027FDB0 = D_eu_0027FDAC * 0.75f;
#else
f32 D_00276648 = 24.0f;
f32 D_00276650 = D_00276648 * 0.75f;
#endif
s32 D_00276654 = 0;
extern f32 D_0027663C[];
char D_00276658[8] = "jojo";
char D_00276660[16] = "08/24/02 22:06";
char D_00276670[12] = "0824.2206";

void ApplyTempoAgentTransform(TempoAgent* self, void* s, void* c)
{
    u8 tmp[0x50];
    void* out = c;
    if (self->f724 == 16) {
        BuildPlacedObjectTransform(self, c, tmp);
        *(s32*)(tmp + 0x44) = 0;
        out = tmp;
    }
    ApplyPlacedObjectTransform(self, s, out);
}

#include "deferred_request.h"
void DrawAgent(TempoAgent* self, Camera* cam);
void QueueDeferredRequest(DeferredRequest* r);
void DrawTempoAgentRing(DeferredRequest* self);

void DrawTempoAgent(TempoAgent* self, Camera* cam)
{
    DrawAgent(self, cam);
    if (self->f724 == 16) {
        DeferredRequest r;
        FillMemory(&r, 0, 0x80);
        f32 d = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->f40)), Vu0::Q(cam->f80)));
        r.group = 0xD;
        r.f04 = d;
        r.arg = self;
        r.callback = (void*)DrawTempoAgentRing;
        QueueDeferredRequest(&r);
    }
}

void LeaveTempoAgentState(TempoAgent* self, void* arg)
{
    s32 out;
    s32 sel;
    LeaveAgentState(self, arg);
    s32 st = self->f724;
    if (st != 0xE) {
        if (st != 0x10) {
            return;
        }
        self->fC94 = 0;
        GetStateWalkerCurrentKey(*(void**)((u8*)self + 0xC54), &out);
        switch (out) {
        case 0x4EE:
            sel = 0x4EF;
            break;
        case 0x4F1:
            sel = 0x4F2;
            break;
        case 0x4F4:
            sel = 0x4F5;
            break;
        }
        SetStateWalkerTarget(*(void**)((u8*)self + 0xC54), sel);
    } else {
        self->fC94 = 0;
    }
}

void DecrementTempoAgentGauge(TempoAgent* self)
{
    T217D_2E0* g = &g_gaugeBarElement;
    DecrementGaugeCount((u8*)&g_gaugeBarElement);
    self->fA68 = 2;
    g->fill = g->fillTarget;
}

void EnterTempoAgentState(TempoAgent* self, s32 a, s32 b)
{
    s32 r[3];
    switch (self->f724) {
    case 0xE:
        GetStateWalkerCurrentKey(self->fC54, &r[0]);
        switch (r[0]) {
        case 0x4ED:
        case 0x4F0:
        case 0x4F3:
        case 0x4F6:
            b = self->fC20;
            self->fC20 = 0;
            break;
        }
        break;
    case 0x10:
        DecrementGaugeCount(&g_gaugeBarElement);
        break;
    case 0xB:
        DecrementGaugeCount(&g_gaugeBarElement);
        MarkLevelDone(3);
        StartMemoryCardSave(&g_memoryCard);
        break;
    }
    EnterAgentState(self, a, b);
    switch (self->f724) {
    case 14: {
        GetStateWalkerCurrentKey(self->fC54, &r[1]);
        f32 q;
        switch (r[1]) {
        case 0x4EE:
            q = 0.083333336f;
            ((AnimationPlayer*)self->f7E0)->speed = ((AnimationPlayer*)self->f7E0)->anim->length / (self->fC88 + self->fC88);
            break;
        case 0x4F1:
        case 0x4F4:
        case 0x4F7:
            q = 0.083333336f;
            ((AnimationPlayer*)self->f7E0)->speed = ((AnimationPlayer*)self->f7E0)->anim->length / (self->fC88 * 4.0f);
            break;
        default:
            return;
        }
        ((AnimationPlayer*)self->f7E0)->time = q;
        break;
    }
    case 2:
    case 13: {
        s32 n = 4;
        GetStateWalkerCurrentKey(self->fC54, &r[2]);
        if (r[2] < 0x4EF) {
            if (r[2] >= 0x4EC) n = 2;
        }
        AddTempoAgentEntry(self, ((AnimationPlayer*)self->f7E0), n);
        if (n == 2) ((AnimationPlayer*)self->f7E0)->time = ((AnimationPlayer*)self->f7E0)->anim->length * (self->fC7C / (f32)n);
        else ((AnimationPlayer*)self->f7E0)->time = ((AnimationPlayer*)self->f7E0)->anim->length * (self->fC7C / (f32)n);
        break;
    }
    case 11:
    case 16:
        self->fC04 = 0;
        break;
    }
}

INCLUDE_ASM(func_001EC7A8);

void RemoveTempoAgentEntry(TempoAgent* self, AnimationPlayer* key);

struct TempoNoticeRec {
    void* object;           // 0x00
    u8 pad04[4];
    s32 id;                 // 0x08
};

struct TempoLineSub {
    u8 pad00[0x78];
    f32 f78;                // 0x78
};

struct TempoLine {
    u8 pad00[0x48];
    u8* rec;                // 0x48
    u8 pad4C[0x60 - 0x4C];
    TempoLineSub sub;       // 0x60
    u8 padDC[0xF0 - 0xDC];
    Vec02 vF0;              // 0xF0
};

void ChooseObjectPoolItem(void* timeline);
void GetPlacementRecordTransform(void* sub, Vec02* a, Mat02* b, s32 c);
s32 LaunchChosenPoolObject(void* timeline, s32 a);
void HandleAgentNotification(TempoAgent* self, s32 kind, void* rec);
void SetCachedVoiceParam(s32 a, s32 b);
s32 GetCachedVoiceParam(s32 a);

void HandleTempoAgentNotification(TempoAgent* self, s32 kind, TempoNoticeRec* rec)
{
    Vec02 a;
    Mat02 b;
    Mat02 rot;
    Vec02 p;
    s32 key;
    s32 voice;

    switch (kind) {
    case 0x13:
        if (rec->object == self->f7E0 && rec->id == 0x1A5) {
            TempoLine* line = (TempoLine*)self->fC24[self->fC40];
            ChooseObjectPoolItem(line);
            TempoLineSub* sub = &line->sub;
            f32 half = self->fC88 * 0.5f;
            f32 t = self->fC64 + self->fC44 - g_gameTime[0] + ((f32*)self->fC3C)[0x684 / 4] * half;
            u8* r = line->rec;
            FramePoint_001EBD10* fp = (FramePoint_001EBD10*)((BeatPressCollider*)self->fC3C)->f618[self->fC40];
            GetPlacementRecordTransform(sub, &a, &b, 0);
            ComputeObjectFrameAtTime(fp->object, 0, &p, &rot, 0, 0, t);
            Vu0::Q(line->vF0) = Vu0::Add(Vu0::Q(p), Vu0::Rotate(rot, Vu0::Q(fp->point)));
            f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(line->vF0)))) / t;
            *(f32*)(r + 0x690) = d;
            *(f32*)(r + 0x6F0) = d;
            sub->f78 = t * 1.25f;
            LaunchChosenPoolObject(line, 1);
            return;
        }
        break;
    case 6: {
        s32 i;
        for (i = 0; i < self->fC68; i++) {
            if ((void*)self->fC6C[i].player == (void*)rec) {
                break;
            }
        }
        if (i < self->fC68) {
            RemoveTempoAgentEntry(self, (AnimationPlayer*)rec);
        }
        break;
    }
    case 0x14:
        if ((void*)rec == self->fC54) {
            GetStateWalkerCurrentKey(rec, &key);
            switch (key) {
            case 0x4EC: voice = 0; break;
            case 0x4ED: voice = 1; break;
            case 0x4EE: voice = 2; break;
            case 0x4EF: voice = 3; break;
            case 0x4F0: voice = 4; break;
            case 0x4F1:
            case 0x4F2: voice = 5; break;
            case 0x4F3: voice = 6; break;
            case 0x4F4:
            case 0x4F5: voice = 7; break;
            case 0x4F6: voice = 8; break;
            case 0x4F7: voice = 9; break;
            case 0x4F8: voice = 10; break;
            }
            if (voice != GetCachedVoiceParam(0)) {
                D_00275DBC = voice;
                D_00275DB8 = 1;
                SetCachedVoiceParam(0, voice);
            }
        }
        break;
    }
done:
    HandleAgentNotification(self, kind, rec);
}

void SyncTempoAgentEntries(TempoAgent* self)
{
    f32 den = self->fC84 - (*(f32*)&g_gameTime);
    for (s32 k = 0; k < self->fC68; k++) {
        TempoPlayerEntry* e = &self->fC6C[k];
        AnimationPlayer* o = e->player;
        f32 len = o->anim->length;
        f32 start = o->time;
        f32 t = len / (f32)e->beats * (f32)((self->fC74 + 1) % e->beats);
        if (t <= start)
            t += len;
        o->speed = (t - start) / den;
    }

}

void UpdateTempoAgent(TempoAgent* self)
{
    Timeline* sub;
    s32 code;

    UpdateAgent(self);
    if (D_00275DB8 == 2) {
        if (self->fC88 != self->fC8C) {
            self->fC88 = self->fC8C;
            self->fC64 = self->fC8C * (f32)self->fC60;
        }
        sub = self->fC34;
        self->fC84 = g_gameClock.time + self->fC88;
        self->fC80 = g_gameClock.time;
        self->fC70 = 0;
        self->fC78 = 0;
        self->fC74 = 0;
        if (sub != 0) {
            self->fC34 = 0;
            self->fC38 = sub;
            RestartTimeline(sub);
        }
        D_00275DB8 = 0;
    }
    if (self->fC84 <= g_gameClock.time) {
        s32 a = self->fC74 + 1;
        s32 b = self->fC78 + 1;
        self->fC80 = self->fC84;
        self->fC74 = a;
        self->fC78 = b;
        if (b >= 4) {
            self->fC78 = 0;
            self->fC70 = self->fC70 + 1;
            if (self->fC88 != self->fC8C) {
                self->fC88 = self->fC8C;
                self->fC64 = self->fC8C * (f32)self->fC60;
            }
        }
        if (self->fC94 == 1) {
            GetStateWalkerCurrentKey(self->fC54, &code);
            if (code == 0x4F1 || (code < 0x4F2 ? code == 0x4EE : (code == 0x4F4 || code == 0x4F7))) self->fC94 = 2;
        }
        self->fC84 = self->fC84 + self->fC88;
    }
    self->fC7C = (f32)self->fC78 + (g_gameClock.time - self->fC80) / self->fC88;
    if (self->fC38 != 0) RunTimelineEntries(self->fC38);
    if (D_00275DB8 == 1) {
        RefreshCachedVoiceParam(1, 0);
        if (GetCachedVoiceParam(1) == D_00275DBC) D_00275DB8 = 2;
    }
    AppendQueuedCall(self->world, SyncTempoAgentEntries, self, 0, 0);
}

void ShowTempoAgentGauge(TempoAgent* self)
{
    s32 code;
    GetStateWalkerCurrentKey(self->fC54, &code);
    s32 obj = 0;
    if (code == 0x4F1 || (code < 0x4F2 ? code == 0x4EE : (code == 0x4F4 || code == 0x4F7))) {
        obj = AreMenusAndFadeClear();
    }
    if (obj) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

void UpdateTempoAgentGoal(TempoAgent* self)
{
    s32 loc[4];
    s32 v = self->f724;
    if (v >= 14) goto tail;
    if (v < 12) goto tail;
    {
        void* q = self->fC48;
        if (q != 0) {
            GetObjectWorldPosition(q, loc);
            SetAgentGoalPoint(self, loc);
        } else {
            SetAgentGoalPoint(self, (u8*)self + 0x140);
        }
    }
    return;
tail:
    UpdateAgentGoal(self);
}

void UpdateAgentState(TempoAgent* self);
void SetAgentFacingAngles(TempoAgent* self, f32 angle, f32 zero);

void UpdateTempoAgentState(TempoAgent* self)
{
    Vec02 diff;
    Mat3U rot;
    s32 code;
    SwitchedCollider* p;
    f32 y;
    f32 x;
    GetStateWalkerCurrentKey(self->fC54, &code);
    switch (code) {
    case 0x4ED:
    case 0x4F0:
    case 0x4F3:
    case 0x4F6:
        p = GetActiveSwitchedCollider();
        Vu0::Q(diff) = Vu0::Sub(Vu0::Q(p->v140), Vu0::Q(self->v140));
        goto fromDiff;
    case 0x4EC:
    case 0x4EF:
    case 0x4F2:
    case 0x4F5:
        if (self->f724 >= 15) goto other;
        if (self->f724 < 13) goto other;
        if (self->fC48 == 0) goto other;
        GetObjectWorldRotation(self->fC48, &rot);
        y = rot.m[0][1];
        x = rot.m[0][0];
        goto angle;
    case 0x4EE:
    case 0x4F1:
    case 0x4F4:
    case 0x4F7:
        if (self->f724 >= 15) goto other;
        if (self->f724 < 13) goto other;
        p = GetActiveSwitchedCollider();
        Vu0::Q(diff) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(p->v140));
    fromDiff:
        y = diff.y;
        x = diff.x;
    angle:
        SetAgentFacingAngles(self, ArctangentOfRatio(y, x), 0.0f);
        return;
    default:
    other:
        UpdateAgentState(self);
    }
}

void SetTempoAgentPendingTimeline(TempoAgent* self, s32 value)
{
    self->fC34 = (Timeline*)value;
}

void EndHeldTimeline(TempoAgent* self)
{
    EndTimeline(self->fC38);
    self->fC38 = 0;
}

void SetTempoAgentTempo(TempoAgent* self, s32 v)
{
    self->fC5C = v;
    self->fC8C = 60.0f / (f32)v;
}

void SetTempoAgentSpanBeats(TempoAgent* self, s32 v)
{
    self->fC60 = v;
    self->fC64 = self->fC88 * (f32)v;
}

void AddTempoAgentEntry(TempoAgent* self, AnimationPlayer* a, s32 b)
{
    TempoPlayerEntry* e = &self->fC6C[self->fC68++];
    e->beats = b;
    e->player = a;
    AddAnimationPlayerRecordCallback(a, self);
}

void RemoveTempoAgentEntry(TempoAgent* self, AnimationPlayer* key)
{
    s32 i = 0;
    if (self->fC68 > 0) {
        TempoPlayerEntry* p = self->fC6C;
        while (p->player != key) {
            i++;
            if (i >= self->fC68)
                return;
            p++;
        }
        if (i < self->fC68) {
            TempoPlayerEntry* e = self->fC6C + i;
            CopyMemory(e, e + 1, (self->fC68 - i - 1) * 8);
            self->fC68 = self->fC68 - 1;
        }
    }
}

void InitTimeline(Timeline* self)
{
    InitObject(self);
    self->buffer = AllocateFrontMemory(0xC00);
}

void FindTimelineTarget(Timeline* self)
{
    StartObject();
    self->found = FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
}

void RestartTimeline(Timeline* self)
{
    self->index = 0;
    self->f44 = ((TempoAgent*)self->found)->fC70;
    TriggerScriptEvent(self, 0x1A, 0, 0);
}

void EndTimeline(Timeline* self)
{
    s32 n;
    TriggerScriptEvent(self, 0x1C, 0, 0);
    n = 5;
    RunTimelineEntry(self, &n);
    if (((TempoAgent*)self->found)->fC3C) {
        n = 3;
        RunTimelineEntry(self, &n);
    }
}

void RunTimelineEntries(Timeline* self)
{
    Entry90* e;
    s32 v;
    while (self->index < self->f34 && (e = self->Cur(), v = e->f4 + self->f44, !(((TempoAgent*)self->found)->fC70 < v))) {
        if (v == ((TempoAgent*)self->found)->fC70 && ((TempoAgent*)self->found)->fC7C < e->f8) return;
        RunTimelineEntry(self, e);
        self->index++;
    }
}

void RunTimelineEntry(Timeline* self, Entry90* msg)
{
    switch (msg->f0) {
    case 0:
        ScheduleTempoAgentBeatPress((TempoAgent*)self->found);
        break;
    case 1: {
        s32* loc = &msg->fC;
        TriggerScriptEvent(self, 0x1B, 1, (s32*)&loc);
        break;
    }
    case 2:
        ((TempoAgent*)self->found)->fC3C->f680 = 1;
        D_00273C50.vt->m16(&D_00273C50, 2);
        ResetPadStepRepeat(&g_padRecord);
        StartSoundEffect(0, 0, 0, 0, 80000.0f, 70000.0f, 1.5f, 0.5f, 0.0f, 0, 0);
        break;
    case 3:
        ((TempoAgent*)self->found)->fC3C->f680 = 0;
        ((TempoAgent*)self->found)->fC3C->f688 = 0;
        D_00273C50.vt->m16(&D_00273C50, 0);
        break;
    case 4:
        ((TempoAgent*)self->found)->fC4C = 1;
        D_002739F0.vt->m16(&D_002739F0, 2);
        StartSoundEffect(0, 0, 0, 0, 80000.0f, 70000.0f, 1.5f, -0.25f, 0.0f, 0, 0);
        break;
    case 5:
        ((TempoAgent*)self->found)->fC4C = 0;
        D_002739F0.vt->m16(&D_002739F0, 0);
        break;
    }
}

void* AppendTimelineEntry(Timeline* self, s32 a, s32 b, f32 c)
{
    if (self->f34 >= 0xC0) return D_00625760;
    Entry90* e = (Entry90*)((u8*)self->buffer + self->f34 * 16);
    self->f34 = self->f34 + 1;
    (void)FillMemory(e, 0, 16);
    e->f0 = a;
    e->f4 = b;
    e->f8 = c;
    return e;
}

void AppendTimelineKind0Entry(void* self, s32 p, s32 val)
{
    AppendTimelineEntry(self, 0, p)->fC = val;
}

void AppendTimelineKind1Entry(void* self, s32 p, s32 val)
{
    AppendTimelineEntry(self, 1, p)->fC = val;
}

void AppendTimelineKind2Entry(void* self, s32 p)
{
    AppendTimelineEntry(self, 2, p);
}

void AppendTimelineKind3Entry(void* self, s32 p)
{
    AppendTimelineEntry(self, 3, p);
}

void AppendTimelineKind4Entry(void* self, s32 p)
{
    AppendTimelineEntry(self, 4, p);
}

void AppendTimelineKind5Entry(void* self, s32 p)
{
    AppendTimelineEntry(self, 5, p);
}

ASM_FUNC(func_001ED638);

void ComputePolarOffset(Vec3* out, f32 unused, f32 scale, f32 z)
{
    SinCos p;
    ComputeSinCos(&p.sine, &p.cosine);
    out->x = p.cosine * scale;
    out->y = p.sine * scale;
    out->z = z;
}

void ComputeDirectionFromAngles(Vec3* out, f32 first, f32 second, f32 scale)
{
    f32 t[4];
    ComputeSinCos(first, &t[0], &t[1]);
    ComputeSinCos(second, &t[2], &t[3]);
    out->x = t[3] * t[1] * scale;
    out->y = t[3] * t[0] * scale;
    out->z = t[2] * scale;
}

ASM_FUNC(func_001ED738);

ASM_FUNC(func_001ED780);

void ComputeUnitPerpendicular(Vec02* v, Vec02* out)
{
    Vec02 w;
    f32 x = v->x;
    f32 y = v->y;
    f32 ax = __builtin_fabsf(x);
    f32 z = v->z;
    f32 ay = __builtin_fabsf(y);
    f32 az = __builtin_fabsf(z);
    if (ax <= ay) {
        if (ax <= az) {
            w.y = z;
            w.x = 0.0f;
            w.z = -y;
        } else {
            w.x = y;
            w.z = 0.0f;
            w.y = -x;
        }
    } else if (ay <= az) {
        w.x = z;
        w.y = 0.0f;
        w.z = -x;
    } else {
        w.x = y;
        w.z = 0.0f;
        w.y = -x;
    }
    u128 c = Vu0::Cross(Vu0::Q(*v), Vu0::Q(w));
    Vu0::Q(*out) = Vu0::DivX(c, Vu0::Length(c));
}

LINKER_REMNANT(func_001ED900);

void ComputeUnitPerpendicular(Vec02* v, Vec02* out);
f32 Arccosine(f32 x);

f32 ComputeAngleBetweenVectors(Vec02* a, Vec02* b, Vec02* axis)
{
    u128 va = Vu0::Length(Vu0::Q(*a));
    u128 vb = Vu0::Length(Vu0::Q(*b));
    f32 la = Vu0::ToFloatMoved(va);
    f32 lb = Vu0::ToFloat(vb);
    if (la < 0.0001f || lb < 0.0001f) {
        *axis = g_unitXVector;
        return 0.0f;
    }
    if (axis != 0) {
        u128 c = Vu0::Cross(Vu0::Q(*a), Vu0::Q(*b));
        Vu0::Q(*axis) = c;
        f32 len = Vu0::ToFloat(Vu0::Length(c));
        if (1e-8f < len) {
            Vu0::Q(*axis) = Vu0::MulX(c, Vu0::Scalar(1.0f / len));
        } else {
            ComputeUnitPerpendicular(a, axis);
        }
    }
    return Arccosine(Vu0::ToFloat(Vu0::Dot(Vu0::Q(*a), Vu0::Q(*b))) / (la * lb));
}

void FindSegmentClosestParams(Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out2, f32* dist, Vec02* normal)
{
    u128 v = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    u128 w = Vu0::Sub(Vu0::Q(*d), Vu0::Q(*c));
    u128 u = Vu0::Sub(Vu0::Q(*c), Vu0::Q(*a));
    Vu0::Vec n;
    n.q = Vu0::Cross(v, w);
    f32 len2 = Vu0::ToFloat(Vu0::Dot(n.q, n.q));
    if (len2 < 0.0001f) {
        f32 z = 0.0f;
        out2[1] = z;
        out2[0] = z;
        n.q = u;
    } else {
        u128 c1 = Vu0::Cross(u, w);
        u128 c2 = Vu0::Cross(u, v);
        f32 d1 = Vu0::ToFloatMoved(Vu0::Dot(c1, n.q));
        f32 d2 = Vu0::ToFloatMoved(Vu0::Dot(c2, n.q));
        out2[0] = d1 / len2;
        out2[1] = d2 / len2;
        if (Vu0::ToFloat(Vu0::Dot(u, n.q)) < 0.0f) {
            n.q = Vu0::MulX(n.q, Vu0::Scalar(-1.0f));
        }
    }
    n = Vu0::NormalizeOr(n, Vu0::Vec::Of(g_unitZVector));
    Vu0::StoreX(*dist, Vu0::Dot(n.q, u));
    Vu0::Q(*normal) = n.q;
}

void FindSegmentClosestParams(const Vec02* p0, const Vec02* p1, const Vec02* q0, const Vec02* q1, f32* st, f32* dist, Vec02* dir);

// v clamped to [0, 1].
static inline f32 ClampUnit(f32 v)
{
    f32 c;
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    if (v < lo) {
        c = lo;
    } else if (hi < v) {
        c = hi;
    } else {
        c = v;
    }
    return c;
}

// The closest points of the segments p0-p1 and q0-q1, their fractions clamped to the segments:
// the direction from the first to the second into dir (the x axis when they meet) and the
// distance into dist.
void FindClosestPointsOnSegments(const Vec02* p0, const Vec02* p1, const Vec02* q0, const Vec02* q1, f32* st, f32* dist, Vec02* dir)
{
    FindSegmentClosestParams(p0, p1, q0, q1, st, dist, dir);
    st[0] = ClampUnit(st[0]);
    st[1] = ClampUnit(st[1]);
    Vu0::Vec w0 = Vu0::Vec::Scalar(st[0] - 1.0f);
    Vu0::Vec a0 = Vu0::Vec::Of(*p0);
    Vu0::Vec w1 = Vu0::Vec::Scalar(-st[0]);
    Vu0::Vec a1 = Vu0::Vec::Of(*p1);
    Vu0::Vec w2 = Vu0::Vec::Scalar(1.0f - st[1]);
    Vu0::Vec a2 = Vu0::Vec::Of(*q0);
    Vu0::Vec w3 = Vu0::Vec::Scalar(st[1]);
    Vu0::Vec a3 = Vu0::Vec::Of(*q1);
    u128 d = Vu0::MulXSum4(a0, w0, a1, w1, a2, w2, a3, w3).q;
    Vu0::Q(*dir) = d;
    const Vec02* fallback = &g_unitXVector;
    u128 len = Vu0::Length(d);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        *dir = *fallback;
    } else {
        Vu0::Q(*dir) = Vu0::DivX(d, len);
    }
    Vu0::StoreX(*dist, Vu0::ToBits(len));
}

void GetVectorAngles(Vec3* v, f32* a1, f32* a2)
{
    if (a1)
        *a1 = WrapAngle(ArctangentOfRatio(v->y, v->x));
    if (a2) {
        f32 r = Fpu::Sqrt(v->x * v->x + v->y * v->y);
        *a2 = WrapAngle(ArctangentOfRatio(v->z, r));
    }
}

void RotateVectorByTwoAngles(Vec3* in, Vec3* b, Vec3* out)
{
    f32 t[4];
    ComputeSinCos(in->y, &t[0], &t[1]);
    ComputeSinCos(in->z, &t[2], &t[3]);
    out->x = t[1] * t[3] * b->x - t[2] * b->y;
    out->y = t[1] * t[2] * b->x + t[3] * b->y;
    out->z = -t[0] * b->x + b->z;
}

f32 Sine(f32 x);
f32 Cosine(f32 x);
f32 Tangent(f32 x);

// The launch velocity from from to to under the gravity at 0x358 of rec (the world's when null),
// its angle above the straight line by angle's sine of the way to vertical. The speed's product
// is a variable of its own: retail moves the square root into q's register before it.
s32 ComputeBallisticLaunchVelocity(Vec02* from, Vec02* to, Vec02* out, u8* rec, f32 angle)
{
    Vec02 d;
    f32 h;
    f32 s = Sine(angle);
    u8* g;
    if (rec != 0) {
        g = rec + 0x350;
    } else {
        g = (u8*)g_currentWorld + 0x1EE0;
    }
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*to), Vu0::Q(*from));
    h = d.z;
    d.z = 0.0f;
    f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
    f32 a = ArctangentOfRatio(h, dist);
    if (a < 0.0f) {
        a = 0.0f;
    }
    f32 theta = a + (1.5707964f - a) * s;
    f32 e = h - dist * Tangent(theta);
    f32 q = *(f32*)(g + 8) / (e + e);
    if (q <= 0.0f) {
        return 0;
    }
    q = Fpu::Sqrt(q);
    f32 v = dist * q;
    q = v / Cosine(theta);
    *out = d;
    out->z = dist * Tangent(theta);
    Vu0::Q(*out) = Vu0::MulX(Vu0::DivX(Vu0::Q(*out), Vu0::Length(Vu0::Q(*out))), Vu0::Scalar(q));
    return 1;
}

// The launch velocity that throws an object from `from` to `to` at the given speed under the
// gravity of rec (the world's when null), into out: straight at the target when there is almost
// no gravity; else 0 when the speed cannot reach it.
s32 ComputeLaunchVelocityToPoint(f32 speed, Vec02* from, Vec02* to, Vec02* out, u8* rec)
{
    Vec02 d;
    u8* g;
    if (rec != 0) {
        g = rec + 0x350;
    } else {
        g = (u8*)g_currentWorld + 0x1EE0;
    }
    f32 grav = *(f32*)(g + 8);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*to), Vu0::Q(*from));
    if (__builtin_fabsf(grav) < 1.0f) {
        u128 k = Vu0::Scalar(speed);
        u128 n = Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(D_00248D30));
        Vu0::Q(*out) = Vu0::MulX(n, k);
        return 1;
    }
    f32 zero = 0.0f;
    f32 h = d.z;
    f32 sp2 = speed * speed;
    d.z = zero;
    f32 up = h >? zero;
    f32 gu = grav * up;
    u128 lv = Vu0::Length(Vu0::Q(d));
    f32 up2 = up * up;
    f32 half = grav * 0.25f;
    f32 dist = Vu0::ToFloatMoved(lv);
    f32 b = gu + sp2;
    f32 dd = dist * dist;
    {
        Vec02 flat;
        Vu0::Q(flat) = Vu0::Q(d);
        Vu0::Q(d) = Vu0::DivX(Vu0::Q(flat), lv);
    }
    f32 c = grav * half;
    f32 disc = (-b) * (-b) - c * ((dd + up2) * 4.0f);
    if (disc < zero) {
        return 0;
    }
    disc = Fpu::Sqrt(disc);
    f32 den = c + c;
    f32 n2 = b + disc;
    f32 n1 = b - disc;
    f32 t1 = n1 / den;
    f32 t2 = n2 / den;
    f32 t;
    if (zero < t1) {
        t = t1;
    } else {
        if (!(zero < t2)) {
            return 0;
        }
        t = t2;
    }
    t = Fpu::Sqrt(t);
    Vu0::Q(d) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(dist / t));
    f32 z = (up - grav * (t * 0.5f) * t) / t;
    out->x = d.x;
    out->y = d.y;
    out->z = z;
    return 1;
}

void ForwardBallisticLaunchVelocity(void* self)
{
    ComputeBallisticLaunchVelocity(self);
}

void ClampVectorLength(Vec02* v, Vec02* out, f32 max)
{
    u128 q = Vu0::Q(*v);
    f32 len = Vu0::ToFloat(Vu0::Length(q));
    if (max < len) {
        Vec02 s;
        Vu0::Q(s) = Vu0::FromFloat(max / len);
        Vu0::Q(*out) = Vu0::MulX(q, Vu0::Q(s));
    } else if (v != out) {
        Vu0::Q(*out) = q;
    }
}

PacketWriter* InitPacketWriter(PacketWriter* self)
{
    (void)InitPacketBuffer(self);
    self->f10 = 1;
    self->vt = (const PacketWriterVt*)D_0024A0E0;
    self->f1C = 0;
    self->f20 = 0;
    return self;
}

LINKER_REMNANT(func_001EE360);

void PadPacketToQuadSlot(PacketWriter* s, s32 target)
{
    u32 raw = s->curU;
    s32 idx = (s32)((raw & 0xC) >> 2);
    u32* p = (u32*)raw;
    if (idx == target) goto done;
    do {
        *p = 0;
        idx = (idx + 1) % 4;
        p++;
    } while (idx != target);
done:
    s->cur = (u8*)p;
}

void WriteVifBaseOffset(PacketWriter* s, u32 a, u32 b)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = a | 0x3000000;
    u32* q = (u32*)s->cur;
    s->cur = (u8*)(q + 1);
    *q = b | 0x2000000;
}

void WriteVifMscal(PacketWriter* s, s32 n)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = (u32)((n / 8) | 0x14000000);
}

void WriteVifMscalf(PacketWriter* s, s32 n)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = (u32)((n / 8) | 0x15000000);
}

void WriteVifFlush(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x11000000;
}

void WriteVifFlushA(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x13000000;
}

void WriteVifFlushE(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x10000000;
}

void WriteVifStcycl(PacketWriter* b, u32 x, u32 y)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = y | (x << 8) | 0x01000000;
}

void WriteVifStrow(PacketWriter* b, u32* src){
 u32 *p1,*p2,*p3,*p4,*p5;
 p1=(u32*)b->cur; b->cur = (u8*)(p1 + 1); *p1=0x30000000;
 p2=(u32*)b->cur; b->cur = (u8*)(p2 + 1); *p2=src[0];
 p3=(u32*)b->cur; b->cur = (u8*)(p3 + 1); *p3=src[1];
 p4=(u32*)b->cur; b->cur = (u8*)(p4 + 1); *p4=src[2];
 p5=(u32*)b->cur; b->cur = (u8*)(p5 + 1); *p5=src[3];
}

void WriteVifStmask(PacketWriter* self, s32 value)
{
    if (value != 0) {
        u32* p = (u32*)self->cur;
        self->cur = (u8*)(p + 1);
        *p = 0x20000000;
        u32* q = (u32*)self->cur;
        self->cur = (u8*)(q + 1);
        *q = (u32)value;
    }
    self->mask = value;
}

s32 WriteVifUnpackHeader(PacketWriter* self, s32 a, s32 b, s32 c)
{
    u32 lo = ((u32)b << 16) | 0x6000C000u;
    u32 head = ((u32)a << 24) | lo;
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 1);
    u32 tag = head | (u32)c;
    *p = tag;
    if (self->f1C != 0) {
        *p = tag | 0x10000000;
    }
    return D_00275DD0[a] * b;
}

void ReserveVifUnpack(PacketWriter* s, void* unused1, s32 size, void* unused3, s32* outSize, u8** outCursor)
{
    if (size == 0) {
        if (outCursor) *outCursor = 0;
        if (outSize) *outSize = 0;
    } else {
        size = WriteVifUnpackHeader(s);
        if (outCursor) *outCursor = s->cur;
        s->cur += ((size + 3) / 4) * 4;
        if (outSize) *outSize = size;
    }
}

void CopyWordsToWriter(void* s, void* a1, s32 size, u32* src, void* a4)
{
    s32 outSize;
    u8* outCursor;
    s32 n;
    s32 rem;
    s32 full;
    s32 i;
    u32* dst;

    ReserveVifUnpack(s, a1, size, a4, &outSize, &outCursor);
    dst = (u32*)outCursor;
    n = (outSize + 3) >> 2;
    rem = n & 3;
    full = n - rem;
    if (rem != 0) {
        i = rem;
        do {
            *dst++ = *src++;
        } while (--i != 0);
    }
    i = 0;
    if (full > 0) {
        do {
            u32 w0 = src[0];
            u32 w1 = src[1];
            u32 w2 = src[2];
            u32 w3 = src[3];
            i += 4;
            dst[0] = w0;
            dst[1] = w1;
            dst[2] = w2;
            dst[3] = w3;
            src += 4;
            dst += 4;
        } while (i < full);
    }
}

void WriteVifUnpack(PacketWriter* self, s32 a, s32 b, s32 c, s32 d, s32* out)
{
    if (b != 0) {
        PadPacketToQuadSlot(self, 3);
        s32 r = WriteVifUnpackHeader(self, a, b, d);
        s32 t = r + 0xF;
        s32 u = r + 0x1E;
        s32 n = (t >= 0) ? t : u;
        AddDmaRefTag(self, n >> 4, c);
        if (out != 0) {
            *out = (s32)self->f08 - 0xC;
        }
    }
}

void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag)
{
    PadPacketToQuadSlot(self, 3);
    u32* p = (u32*)self->cur;
    u32 w = (u32)flag << 31;
    self->cur = (u8*)(p + 1);
    w = w | 0x50000000u;
    *p = (u32)n | w;
    AppendPacketQuadwords(self, n, (s32)buf);
}

void WriteVifDirectRef(PacketWriter* self, s32 a, s32 b, s32 c)
{
    PadPacketToQuadSlot(self, 3);
    u32* p = (u32*)self->cur;
    u32 w = (u32)c << 31;
    self->cur = (u8*)(p + 1);
    w = w | 0x50000000u;
    *p = (u32)a | w;
    AddDmaRefTag(self, a, b);
}

void WriteVifDirectFromWriter(PacketWriter* a0, PacketWriter* a1) {
    u32 span = a1->curU - (u32)a1->begin;
    WriteVifDirect(a0, span >> 4, (void*)a1->begin, 0);
}

void InitValueListObject(ValueListObject* self)
{
    InitObject(self);
    self->world->f1EC4 = self;
}

void LoadValueList(ValueListObject* self, void* src)
{
    s32 i;
    s32 n;

    ReadLinkedItemArray(src, &self->count34, &self->data38);
    n = ReadBufferedU16(src);
    self->valueCount = n;
    self->values = (s32*)AllocateFrontMemory(n * 4);
    for (i = 0; i < self->valueCount; i++) {
        self->values[i] = ReadBufferedU32(src);
    }
    ReadPropertyRecords(self, src);
}

s32 ExpandMaskThroughTable(ValueListObject* self, s32 bits)
{
    s32 acc;
    bits &= 0x7FFFFFFF;
    if (bits == 0) return 0;
    acc = -1;
    for (s32 i = 0; i < self->valueCount; i++) {
        if ((bits >> i) & 1) acc &= self->values[i];
    }
    return acc | bits;
}

// One plane of the value tree (QueryValueTreeMask): a child is a node's address, or a leaf mask
// with bit 31 set.
struct PlaneNode {
    Vec02 normal;           // 0x00
    f32 dist;               // 0x10
    s32 front;              // 0x14: the child on the plane's near side
    s32 back;               // 0x18
};

// The mask of the leaves within radius of point under node: the walk follows the near side,
// descends into the far side too where the sphere straddles the plane, and ORs each leaf's mask
// (ExpandMaskThroughTable) into *out.
s32 QueryValueTreeMask(ValueListObject* self, s32 node, Bits128 point, f32 radius, s32* out)
{
    if (node < 0) {
        *out = ExpandMaskThroughTable(self, node);
    } else {
        f32 near = -radius;
        s32 next;
        do {
            PlaneNode* n = (PlaneNode*)node;
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(point), Vu0::Q(n->normal))) - n->dist;
            if (d < near) {
                next = n->front;
            } else if (radius < d) {
                next = n->back;
            } else {
                next = n->back;
                if ((u32)next & 0x80000000) {
                    *out |= ExpandMaskThroughTable(self, next);
                } else {
                    QueryValueTreeMask(self, next, point, radius, out);
                }
                next = n->front;
            }
            node = next;
        } while (!((u32)next & 0x80000000));
        *out |= ExpandMaskThroughTable(self, next);
    }
}

s32 QueryValueListMask(ValueListObject* self, f32 radius, Bits128* vec, s32* out)
{
    s32 r;
    if (self != 0 && self->data38 != 0) {
        Bits128 q = *vec;
        *out = 0;
        r = QueryValueTreeMask(self, (s32)self->data38, q, radius, out);

    } else {
        r = 0x0FFFFFFF;
        *out = r;
    }
    return r;
}

ASM_FUNC(func_001EEBB0);

void InitAttachedSet(AttachedSet* self)
{
    u64 bits;
    s32 one;

    InitCollider(self);
    bits = self->flags538;
    one = 0x8000;
    bits |= (u64)one << 28;
    self->flags538 = bits;
    self->f584 = 1;
    self->f588 = 1;
    self->f364 = 1.0f;
    self->f360 = 1.0f;
    SetColliderAnchors(self, 3, 0, 3, 0);
    InitTrackedNodes(&self->trackedNodes, self);
    self->trackedNodes.f04 = 3;
}

void StartAttachedSet(AttachedSet* self)
{
    ChildWalkFrame fr((s32*)&self->children);
    g_activeListFrames = (ListFrame*)&fr;
    StartPlacedObject(self);
    FillTrackedNodes(&self->trackedNodes);
    self->group.items = (void**)AllocateFrontMemory(0x80);
    if (self->f278 != 0) {
        self->desc03()->m32(self);
    }
}

void TransformDirectionBetweenFrames(s32 a, void* obj, void* in, void* out);
void TransformStateToAncestorFrame(void* obj, s32 a1, void* a2, s32 a3, void* a4, void* a5);
void ComputeOscillatorDisplacement(f32 f, void* a0, void* a1, void* a2, void* a3, void* a4, void* a5);

void GetAttachedSetPointMotion(AttachedSet* self, void* in, Quad16* outA, Quad16* outB)
{
    Vec02 a;
    Quad16 b;
    Quad16 c;
    Vec02 d;
    TransformDirectionBetweenFrames(0, self, in, &a);
    b = *(Quad16*)((u8*)self + 0x570);
    a.z = 0.0f;
    c = *(Quad16*)&D_00248D30;
    TransformStateToAncestorFrame(self, 0, &a, 0, &b, &c);
    if (self->f278 != 0) {
        ComputeOscillatorDisplacement(50.0f, *(void**)(self->f278 + 0xC), in, 0, 0, 0, &d);
        Vu0::Q(*(Vec02*)&b) = Vu0::Add(Vu0::Q(*(Vec02*)&b), Vu0::Q(d));
    }
    if (outA != 0) {
        *outA = b;
    }
    if (outB != 0) {
        *outB = c;
    }
}

void ReconcileColliderAttachments(void* owner, Attach03** head)
{
    Attach03** link = head;
    Attach03* node = *head;
    Attach03* removed = 0;
    while (node != 0) {
        Collider* o = node->target;
        Attach03* next = node->nextOwn;
        if (((o->flags538 >> 59) & 1) != ((o->flags538 >> 60) & 1)) {
            if (o->flags538 & (1ULL << 59)) {
                RemoveColliderAttachment(o, node);
            } else {
                AddColliderAttachment(o, node);
            }
        }
        Collider* p = node->target;
        if (p->flags538 & (1ULL << 60)) {
            link = &node->nextOwn;
        } else {
            *link = next;
            node->nextOwn = removed;
            removed = node;
        }
        Collider* q = node->target;
        q->flags538 = q->flags538 & ~(1ULL << 60);
        q->flags538 = q->flags538 & ~(1ULL << 59);
        node = next;
    }
    ReleaseAttachRecords(owner, removed);
}

void UpdateCollider(void* self);
Attach03* TakeAttachRecord(void* world);
f32 MeasureAttachedSetContactDepth(AttachedSet* self, TurningCollider* o, Vec02* nOut, Vec02* hitOut);
s32 CollectTreeNodeSpans(TreeNode03* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
void StartSoundEffect(s32 a0, s32 a1, Collider* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void BroadcastPointEvent(void* self, void* obj, f32 x);

void UpdateAttachedSet(AttachedSet* self)
{
    s32 changed = 0;
    UpdateCollider(self);
    if (self->tree.nodes == 0) {
        return;
    }
    World* world = self->world;
    Attach03* link;
    Collider* c;
    for (link = self->links; link != 0; link = link->nextOwn) {
        link->target->flags538 |= 1ULL << 59;
    }
    for (ContactRow03* r = ((Collider*)self->root)->contacts->head; r != 0; r = r->next) {
        c = r->other;
        if (c->f360 < 0.0001f) {
            continue;
        }
        if (c->flags538 & ((1ULL << 54) | (1ULL << 42))) {
            continue;
        }
        if (MeasureAttachedSetContactDepth(self, (TurningCollider*)c, 0, 0) == 0.0f) {
            continue;
        }
        c->flags538 |= 1ULL << 60;
        if (self->f278 != 0) {
            ClearRootTries((Actor6C*)(void*)c);
        }
        if (c->flags538 & (1ULL << 59)) {
            continue;
        }
        link = TakeAttachRecord(world);
        link->owner = self;
        link->target = c;
        link->nextOwn = self->links;
        self->links = link;
        if (self->f580 == 0) {
            continue;
        }
        if (!(c->v150.z < -100.0f)) {
            continue;
        }
        Vec02 from;
        Vec02 to;
        ColliderSpan spans[16];
        Vec02 off;
        if (self->f278 != 0) {
            Vec02 d;
            ComputeOscillatorDisplacement(50.0f, *(void**)(self->f278 + 0xC), &c->v140, 0, &d, 0, 0);
            Vu0::Q(off) = Vu0::Sub(Vu0::Vec::Of(d), Vu0::Vec::Of(c->v140)).q;
        } else {
            off = D_00248D30;
        }
        Vu0::Q(from) = Vu0::Sub(Vu0::Vec::Of(c->v370), Vu0::Vec::Of(off)).q;
        Vu0::Q(to) = Vu0::Sub(Vu0::Vec::Of(c->v140), Vu0::Vec::Of(off)).q;
        f32 h;
        if (c == g_player) {
            h = -75.0f;
        } else {
            h = c->boundsMin.z - c->v140.z;
        }
        from.z = from.z + h;
        to.z = to.z + h;
        if (CollectTreeNodeSpans(self->tree.nodes, &from, &to, 0, 0x10, spans) <= 0) {
            continue;
        }
        if (spans[0].face50 == 0) {
            continue;
        }
        f32 speed = c->v150.z;
        f32 six = 6.0f;
        f32 strength = (-speed <? six) * 0.16666667f;
        f32 size = ((c->boundsMax.x - c->boundsMin.x) + (c->boundsMax.y - c->boundsMin.y)) * 0.5f;
        if (speed < 0.0f) {
            StartSoundEffect(0x22, 0, c, 0, 10.0f, 1.0f, strength, 0.0f, 0.0f, 0, 0);
            Vu0::Q(spans[0].q[0]) = Vu0::Add(Vu0::Vec::Of(spans[0].q[0]), Vu0::Vec::Of(off)).q;
            BroadcastPointEvent(&spans[0], self, size * strength);
        }
    }
    for (link = self->links; link != 0; link = link->nextOwn) {
        c = link->target;
        u64 f = c->flags538;
        if (((f >> 59) & 1) != ((f >> 60) & 1)) {
            c->onSet = (f >> 60) & 1;
            DetachMsg m;
            m.self = self;
            m.obj = c;
            c->desc->m0E(c, (c->flags538 & (1ULL << 59)) ? 11 : 10, &m);
            changed = 1;
        }
    }
    ReconcileColliderAttachments(world, &self->links);
    if (changed) {
        RebuildAttachedSet(self);
    }
}

void ForwardAttachedSetLinkStep(AttachedSet* self, Attach03* link)
{
    Collider* target = link->target;
    ((AttachNotifyFn)target->desc03()->m46)(target, self);
}

void HandleAttachedSetNotification(AttachedSet* self, s32 kind, void* msg)
{
    s32 flag = 0;
    if (kind == 2) {
        if (msg == (void*)self) {
            Attach03* n = self->links;
            if (n != 0) {
                do {
                    RemoveColliderAttachment(n->target, n);
                    n = n->nextOwn;
                } while (n != 0);
            }
            flag = 1;
            ReleaseAttachRecords(self->world, self->links);
            self->links = 0;
        } else {
            Attach03** link = &self->links;
            Attach03* n = *link;
            if (n != 0) {
                if (n->target == (Collider*)msg) {
                    *link = n->nextOwn;
                } else {
                    for (;;) {
                        link = &(*link)->nextOwn;
                        n = *link;
                        if (n == 0) {
                            break;
                        }
                        if (n->target == (Collider*)msg) {
                            *link = n->nextOwn;
                            break;
                        }
                    }
                }
            }
            DetachMsg m;
            m.self = self;
            m.obj = n->target;
            if (n != 0) {
                n->nextOwn = 0;
                flag = 1;
                RemoveColliderAttachment(n->target, n);
                ReleaseAttachRecords(self->world, n);
            }
            m.obj->desc->m0E(m.obj, 11, &m);
        }
    }
    if (flag != 0) {
        RebuildAttachedSet(self);
    }
    HandlePlacedObjectNotification(self, kind, msg);
}

void RebuildAttachedSet(AttachedSet* self)
{
    if (self->root == self) {
        AttachedGroup* s = &self->group;
        UnregisterObjectGroup(self->world, s);
        s->items[0] = self;
        s->count = 1;
        Attach03* node = self->links;
        if (node) {
            do {
                s->items[s->count++] = node->target;
                node = node->nextOwn;
            } while (node);
        }
        RegisterObjectGroup(self->world, s);
    }
}

s32 CollectTreeNodeSpans(TreeNode03* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);

f32 MeasureAttachedSetContactDepth(AttachedSet* self, TurningCollider* o, Vec02* nOut, Vec02* hitOut)
{
    Vec02 from;
    Vec02 to;
    ColliderSpan spans[16];
    if (self->f278 != 0) {
        ComputeOscillatorDisplacement(50.0f, *(void**)(self->f278 + 0xC), &o->v140, 0, &from, 0, 0);
        Vu0::Q(from) = Vu0::Q(to) = Vu0::MulXSum(Vu0::Q(o->v140), Vu0::Scalar(2.0f), Vu0::Q(from), Vu0::Scalar(-1.0f));
    } else {
        from = to = o->v140;
    }
    if (o == g_player) {
        from.z = from.z + -75.0f;
        if (o->f690 != 0) {
            from.z = o->v6A0.z >? from.z;
        }
    } else {
        from.z = from.z + (*(f32*)((u8*)o + 0x428) - o->v140.z);
    }
    to.z = to.z + (*(f32*)((u8*)o + 0x438) - o->v140.z);
    s32 n = CollectTreeNodeSpans(self->tree.nodes, &from, &to, 0, 0x10, spans);
    if (n == 0) {
        if (hitOut != 0) {
            *hitOut = g_unitZVector;
        }
        return 0.0f;
    }
    if (nOut != 0) {
        *nOut = *(Vec02*)&spans[0].q[1];
    }
    if (hitOut != 0) {
        if (*(Vec02**)((u8*)&spans[0] + 0x54) != 0) {
            *hitOut = **(Vec02**)((u8*)&spans[0] + 0x54);
        } else {
            *hitOut = g_unitZVector;
        }
    }
    return spans[0].time[1] - spans[0].time[0];
}

struct SwingRecord {
    u8 pad00[0x0C];
    Oscillator* osc;        // 0x0C
};

void UpdateColliderBounds(Collider* self);
void ComputeOscillatorMaxDisplacement(Oscillator* osc, Vec02* out);

// Grows the box and both radii by the oscillator's largest swing.
void UpdateAttachedSetBounds(AttachedSet* self)
{
    UpdateColliderBounds(self);
    SwingRecord* r = (SwingRecord*)self->f278;
    if (r != 0 && r->osc != 0) {
        Vec02 d;
        ComputeOscillatorMaxDisplacement(r->osc, &d);
        u128 v = Vu0::Q(d);
        f32 len = Vu0::ToFloatMoved(Vu0::SelfLength(v));
        u128 lo = Vu0::Q(self->boundsMin);
        u128 hi = Vu0::Q(self->boundsMax);
        Vu0::Q(self->boundsMax) = Vu0::Add(hi, v);
        Vu0::Q(self->boundsMin) = Vu0::Sub(lo, v);
        self->radius3D0 += len;
        self->radius3D4 += len;
    }
}

s32 RequestAttachedSetLaunch(AttachedSet* self)
{
    OfferTrackedNodeLaunch(&self->trackedNodes);
    return 1;
}

void* GetAttachedSetTrackedNodes(AttachedSet* self)
{
    return &self->trackedNodes;
}

void ClearAttachedSetTrackedNodes(AttachedSet* o)
{
    o->trackedNodes.found = 0;
}

void InitStateResetObject(StateResetObject* self)
{
    InitPlacedObject(self);
    self->id2D0 = -1;
    self->id2E0 = -1;
}

void StartStateResetObject(StateResetObject* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, D_00275E10);
    SetStateAndNotify(self, 0);
    self->desc->m03(self);
}

s32 AddStateResetEntry(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    return UpsertKeyedEntry((u8*)self + 0x2E8, 4, (u8*)self + 0x2E4, a1, a2, a3, a4, a7);
}

void UpdateStateResetObject(void) {}

void SetStateAndNotify(StateResetObject* self, s32 state)
{
    if (self->id2D0 != state) {
        if (state != 0) {
            if (state == 2)
                SetGatheredWalkerTargets((World*)g_currentWorld, self->f2E4, self->f2E8, self, 1);
        } else {
            if (self->id2D0 == 2)
                SetGatheredWalkerTargets((World*)g_currentWorld, self->f2E4, self->f2E8, self, 0);
        }
        StateChangeMsg evt;
        evt.old = self->id2D0;
        evt.self = self;
        evt.cur = state;
        self->id2D0 = state;
        self->f2D4 = g_gameTime[0];
        self->desc->m0E(self, 0x16, &evt);
    }
}

void HandleStateResetNotification(StateResetObject* self, s32 kind, StateResetMsg* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 5) {
        if (msg->id == self->id2DC) {
            SetStateAndNotify(self, 0);
        }
    }
}

void* CreateRecord2505C0(void)
{
    StateResetGroup* p = (StateResetGroup*)AllocateZeroedFrontMemory(48);
    p->vtbl = D_002505C0;
    return p;
}

void AppendToSmallList(StateResetGroup* self, StateResetObject* value) { u32 i = self->count; if (i < 8) { self->items[i] = value; self->count = i + 1; } }

void RemoveFromSmallList(StateResetGroup* self, StateResetObject* value)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (self->items[i] == value) break;
    }
    if (i < self->count) {
        MoveItemsDown::Of(&self->items[i], &self->items[i + 1], (self->count - i) * 4 - 4);
        self->count--;
    }
}

void UpdateItemTimeouts(StateResetGroup* s)
{
    s->scheduled = 0;
    if (s->owner != 0 && s->owner->f180 != -1 && s->items[0]->id2E0 == s->owner->f180) {
        s32 i;
        for (i = 0; i < s->count; i++) {
            if (s->items[i]->id2D0 != 1) break;
        }
        if (i >= s->count) {
            for (i = 0; i < s->count; i++) {
                SetStateAndNotify(s->items[i], 2);
            }
            s->owner->f180 = -1;
        }
        return;
    }
    for (s32 i = 0; i < s->count; i++) {
        StateResetObject* it = s->items[i];
        if (it->id2D0 != 2) continue;
        if (it->id2DC != 0) continue;
        f32 d = g_gameClock.time - it->f2D4;
        if (it->f2D8 < d) {
            SetStateAndNotify(it, 0);
        }
    }
}

void ScheduleItemTimeouts(StateResetGroup* self)
{
    if (self->scheduled == 0) {
        self->scheduled = 1;
        AppendQueuedCall((s32)g_currentWorld, (void*)UpdateItemTimeouts, self, -1, 0);
    }
}

LINKER_REMNANT(func_001EFCE0);

void ResetScreenFade(ScreenFade* o)
{
    o->mode = -1;
    SetScreenFadeMode(o, 0);
}

void UpdateScreenFade(ScreenFade* self, s32 a1)
{
    s32 s = self->mode;
    f32 t = g_gameClock.elapsed - self->modeStartTime;
    f32 thr;
    f32 r;
    switch (s) {
    case 0:
        if (RestoreFadeRequest(self, a1, 1) != 0) return;
        break;
    case 1:
        if (self->style != 2) {
            thr = 0.5f;
            if (self->style == s) thr = 1.5f;
            if (thr < t) {
                s = 2;
                SetVolumeChannel6Factors(((self->active.flags >> 3) ^ 1) & 1, 0.0f);
            } else {
                r = t / thr;
                f32 hi = 1.0f;
                f32 lo = 0.0f;
                if (r < lo) r = lo;
                else if (hi < r) r = hi;
                self->opacity = r;
                SetVolumeChannel6Factors(((self->active.flags >> 3) ^ 1) & 1, 1.0f - r);
            }
        }
        break;
    case 3: {
        s32 v = self->style;
        if (v != 2) {
            thr = 0.25f;
            if (v == 1) thr = 1.0f;
            if (thr < t) {
                if (v == s) {
                    self->style = 0;
                    self->modeStartTime = g_gameClock.elapsed;
                    self->opacity = 1.0f;
                } else {
                    s = 0;
                }
            } else {
                self->opacity = 1.0f - t / thr;
            }
        }
        break;
    }
    case 2:
        if (self->active.kind == 0 && g_worldLoadRequest != 0) {
        } else {
            s = 3;
        }
        break;
    }
    SetScreenFadeMode(self, s);
}

void DrawScreenFade(ScreenFade* self)
{
    if (g_currentWorld != 0 && g_screenFade.mode != 0) {
        s32 mode = self->style;
        if (mode != 1) {
            if (mode < 2) {
                if (mode == 0) goto draw;
            }
            return;
        }
        if (g_coloredTriangleSet != 0) {
        DrawColoredTriangles(g_coloredTriangleSet, self->opacity);
            return;
        }
        draw:
    f32 v = self->opacity * 255.0f;
    WriteColoredSpritePacket(0, 0, 0, (s32)v, &g_gsPacketWriter, 0.0f, 0.0f, 640.0f, 492.80002f);
    }
}

void StartScreenFade(ScreenFade* dst, FadeRequest* args, s32 count)
{
    IdentityKey* p;
    s32 mode;

    if (dst->mode == 0) {
        if (D_0027051C != 0) {
            if (*(s32*)((u8*)D_0027051C + 0x2D0) != 2) {
                PopActiveSequenceElement(g_currentWorld);
            }
        }
        if (args->key == 0 || SameAsFixedKey::Of(args->key)) {
            args->flags |= 8;
        } else {
            args->flags &= ~8;
        }
        dst->active = *args;
        dst->style = count;
        mode = 2;
        if (g_currentWorld != 0) {
            mode = 1;
        }
        SetScreenFadeMode(dst, mode);
    }
}


void SaveFadeRequest(ScreenFade* dst, FadeRequestBlock* src, s32 last)
{
    s32 mid = src->mid;
    u64 lo = src->pair.lo;
    u64 hi = src->pair.hi;
    ((QuadP*)&dst->queued)->lo = lo;
    ((QuadP*)&dst->queued)->hi = hi;
    dst->queuedStyle = last;
    dst->queued.flags = mid;
}

s32 RestoreFadeRequest(ScreenFade* self, PadRecord* o, void* param2)
{
    if (IsPadSelectFlagHeld(g_currentWorld) != 0 && self->queued.kind != 0 && (o->flags & 0x800) != 0) {
        ClearPadPressedBits(o, 0x800);
        *(FadeRequestBlock*)&self->active = *(FadeRequestBlock*)&self->queued;
        self->style = self->queuedStyle;
        FadeRequest* rr = &self->active;
        IdentityKey* kk = rr->key;
        if (kk == 0 || SameKeys::Of(kk, &D_00275B04)) {
            rr->flags |= 8;
        } else {
            rr->flags &= ~8;
        }
        SetScreenFadeMode(self, (s32)param2);
        return 1;
    }
    return 0;
}

LINKER_REMNANT(func_001F0218);

void SetScreenFadeMode(ScreenFade* self, s32 mode)
{
    if (self->mode == mode) goto L0410;
    if (self->mode == 2) {
        if (D_0026FA68 != 0) {
            SetWarpPageMode(D_0026FA68, 0);
        }
    }
    if (mode == 1) goto L02E0;
    if (mode < 2) {
        if (mode == 0) {
            self->opacityWord = 0;
            goto L0400;
        }
        self->mode = mode;
        goto L0404;
    }
    if (mode == 2) goto L02A0;
    if (mode == 3) goto L0374;
    self->mode = mode;
    goto L0404;

L02A0:
    if (self->active.kind != 0) {
        FadeRequest* q = &self->active;
        QueueWorldLoad((u8*)&g_worldLoadRequest, (s32)q->key, q->f08, q->f0C, q->flags);
    }
    self->active.kind = 0;
    self->opacity = 1.0f;
    self->queued.kind = 0;
    goto L0400;

L02E0:
    {
        s32 v = self->style;
        if (v == 2) goto L0300;
        if (v == 3) goto L0354;
        goto L0364;
    }

L0300:
    {
        s32 v = GetEntryIdByKey((s32)self->active.key);
        s32 a3 = v >> 8;
        s32 a2 = v & 0xFF;
        if (D_0026FA68 == 0) goto L034C;
        if (v == -1) goto L034C;
        s32 a1 = 10;
        if (a3 != 0) a1 = a2;
        SetWarpCursor(D_0026FA68, a1, 3);
        ShowCountedScreenElement(g_currentWorld);
        goto L0364;
    }

L034C:
    self->style = 0;
    goto L0364;

L0354:
    mode = 2;
    goto L02A0;

L0364:
    SetElementStackState(g_elementStack, 8);
    self->mode = mode;
    goto L0404;

L0374:
    {
        s32 a = self->style;
        if (a == 2) goto L038C;
        if (a == mode) goto L03EC;
        self->mode = mode;
        goto L0404;
    }

L038C:
    {
        if (self->style == D_00275BF0[0]) {
            s32 idx = g_previousLevelIndex;
            if (idx != -1) {
                g_mapScreenList.current = g_mapScreenList.nodes[idx];
            }
        }
        if (g_mapScreenList.current != 0) {
            g_mapScreenList.current->f2E0 = 3;
            SetWarpPageMode(g_mapScreenList.current, 4);
            self->mode = mode;
            goto L0404;
        }
        self->style = 3;
        goto L0400;
    }

L03EC:
    FadeScreenToBlack(0.25f);
    self->style = 0;
    goto L0400;

L0400:
    self->mode = mode;
L0404:
    self->modeStartTime = g_elapsedTime[0];
L0410:
    return;
}

void StartObjectFade(IdentityKey* obj, s32 value, s32 count)
{
    FadeRequest m;
    m.kind = 1;
    m.key = obj;
    m.f08 = value;
    m.flags = 0;
    StartScreenFade(&g_screenFade, &m, count);
}

s32 GetCurrentWarpEntry(void)
{
    if (D_00275BF0[0] != 2) {
        return g_saveData->f19DC;
    }
    return 10;
}

s32 IsWarpEntryAvailable(WarpPage* self, s32 kind, s32* outA, s32* outB)
{
    s32 flag = 0;
    s32 sel;
    s32 idx;
    if (kind == 10) {
        sel = 0;
        idx = 4;
        flag = 1;
    } else {
        s32 mode = self->slot;
        s32 allowed = 1;
        if (mode == 5 && (kind == 1 || kind == 7)) {
            allowed = 0;
        }
        if (kind == 9) {
            if (allowed != 0) {
                s32 m = mode * 0x44C;
                if (*(s32*)((u8*)g_saveData + m + 0x88) & 1) {
                    s32 q = g_saveData->levels[mode].f448;
                    flag = (q & D_00275FC8[mode]) != 0;
                }
            }
        } else {
            s32 c = kind < 9;
            idx = -1;
            if (c) {
                idx = kind;
            }
            sel = mode;
            flag = 0;
            if (allowed != 0) {
                flag = *(s32*)((u8*)g_saveData + (sel * 0x44C + idx * 0x78) + 0x10) & 1;
            }
        }
    }
    if (outA != 0) {
        *outA = sel;
    }
    if (outB != 0) {
        *outB = idx;
    }
    return flag;
}

s32 IsWarpEntryReachable(void* self, s32 code)
{
    s32 r;
    if (code == 9) {
        return 0;
    }
    r = IsWarpEntryAvailable(self, code, 0, 0);
    if (r == 0) {
        switch (((WarpPage*)self)->slot) {
        case 1:
            if (code >= 2) {
                if (code < 6) {
                    r = IsWarpEntryAvailable(self, 1, 0, 0);
                } else if (code < 8) {
                    r = IsWarpEntryAvailable(self, 9, 0, 0);
                }
            }
            break;
        case 2:
        case 3:
        case 4:
            if (code >= 2) {
                if (code < 5) {
                    r = IsWarpEntryAvailable(self, 1, 0, 0);
                } else if (code < 8) {
                    r = IsWarpEntryAvailable(self, 9, 0, 0);
                }
            }
            break;
        }
    }
    return r;
}

void StartWarpPage(WarpPage* o) {
    StartPlacedObject(o);
    o->flags = (o->flags & ~(3UL << 40)) | (1UL << 40);
    if (g_saveData->f19D8) {
        u8* t = (u8*)&g_mapScreenList;
        ((U32P*)(t + 0x260))->v = (u32)o;
    }
    switch (o->id) {
    case 0x1C7: o->slot = 1; break;
    case 0x1C8: o->slot = 2; break;
    case 0x1C9: o->slot = 3; break;
    case 0x1C6: o->slot = 4; break;
    case 0x1CA: o->slot = 5; break;
    default: o->slot = g_saveData->f19D8; break;
    }
    g_mapScreenList.nodes[o->slot] = o;
}

void PostLoadWarpPage(WarpPage* self)
{
    ListFrame it;
    BaseObject* node;
    WarpEntry* el;
    s32 i;

    PostLoadPlacedObject(self);
    ResolveObjectLinks(self, 0x34, D_00275FE0);
    BeginPageWalk::Of(&it, &self->children);
    while ((node = NextPageNode::Of(&it)) != 0) {
        ResolveAndStartObject(node);
    }
    el = self->entries;
    for (i = 0; i < 11; i++) {
        f32 zero = 0.0f;
        el->f28 = zero;
        el->f24 = zero;
        el->phase = RandomFloatInRange(zero, 6.2831855f);
        el->speed = RandomFloatInRange(0.5f, 0.7f);
        el++;
    }
    self->selected = -1;
    g_activeListFrames = it.prev;
}

void SelectWarpPageEntry(WarpPage* self, s32 value)
{
    if (value == 10) {
        SetElementTextFromEntry(&D_0026F138, 0, 4);
    } else {
        T217D_3D0* base = &D_0026F138;
        s32 t = value < 9;
        s32 idx = t ? value : -1;
        SetElementTextFromEntry(base, self->slot, idx);
    }
    SetWarpPageSelectedEntry(self, value);
}

void SetPendingWarpEntry(s32 unused, s32 a, s32 b)
{
    D_00276250 = a;
    D_00276654 = b;
}

void AnnouncePendingWarpEntry(WarpPage* self)
{
    if (D_00276250 == -1) return;
    SetScreenElementHoldTime(&D_002721D0, ((g_saveData->f19D8 << 8) | g_saveData->f19DC) == 4 ? 0.5f : 2.0f);
    D_002721D0.vt->m16(&D_002721D0, 2);
    T217D_3D0* e = &D_0026F138;
    e->pending = 0;
    e->vt->m16(e, 0);
    SetElementTextFromEntry(e, g_saveData->f19D8, g_saveData->f19DC);
    e->announce = 1;
    SetScreenElementHoldTime(e, 0.0f);
    e->vt->m16(e, 2);
    Animation* sl = self->entries[D_00276250].f00;
    if (sl != 0) {
        f32 f = 0.0f;
        if (D_00276654 == 0) f = sl->length;
        ReplaceAnimationPlayer(sl, self, 0, &self->f2F0, f, 0.0f);
    }
    if (self->f2E8 != 0) {
        for (s32 i = 0; i < self->f2E8->startCount; i++) {
            AnimEvent* en = &self->f2E8->startList[i];
            if (en->kind == 10) {
                BaseObject* n = FindFirstObjectById(self->world, 0x104, en->a8.i, self);
                if (n != 0) n->desc->m02(n);
            }
        }
    }
    D_00276250 = -1;
}

void UpdatePlacedObject(void* self, f32 dt);
void StopAnimationPlayer(s32 player);

// Every frame: by mode, closes the page's animations (0), moves the highlight to the cursor's
// entry (2) or plays the opening of the chosen one (3); then eases every entry's values.
void UpdateWarpPage(WarpPage* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
    switch (self->mode) {
    case 0:
        if (self->f2EC != 0) {
            StopAnimationPlayer(self->f2EC);
            self->f2EC = 0;
        }
        if (self->f2F0 != 0) {
            StopAnimationPlayer((s32)self->f2F0);
            self->f2F0 = 0;
        }
        if (self->f2EC == 0 && self->f2F0 == 0) {
            self->desc->m03(self);
        }
        break;
    case 2:
        if (self->f2D8 != self->cursor) {
            SelectWarpPageEntry(self, self->cursor);
            if (IsWarpEntryAvailable(self, self->f2D8, 0, 0) != 0) {
                self->entries[self->f2D8].f10 = 0.0f;
            }
            if (IsWarpEntryAvailable(self, self->cursor, 0, 0) != 0) {
                self->entries[self->cursor].f10 = 1.0f;
            }
            self->entries[9].f10 = self->entries[1].f10;
            self->f2D8 = self->cursor;
        }
        *(u128*)&self->q540 = ApproachPointWithRamp(*(u128*)&self->q540, *(u128*)&self->q550, g_gameClock.step,
                                                     (RampProfile*)D_00276258, 0);
        break;
    case 3:
        if (self->f2D8 != self->cursor) {
            if (self->f560 == 0) {
                SelectWarpPageEntry(self, self->cursor);
                SetScreenElementHoldTime(&D_0026F138, 0.0f);
                D_0026F138.vt->m14(&D_0026F138);
            }
            // Read as a 64-bit value: GCSE then does not take this read for the later
            // `target = self->cursor`, which retail loads again (docs/TOOLCHAIN.md, "GCSE").
            s64 cursor = self->cursor;
            s32 back = 0;
            if (cursor != 1 || self->f560 != 0) {
                back = 1;
            }
            s32 target;
            if (back != 0) {
                target = self->cursor;
            } else {
                target = GetCurrentWarpEntry();
            }
            Animation* anim = self->entries[target].f00;
            if (D_00275BF0[0] != 2) {
                self->entries[GetCurrentWarpEntry()].f10 = 0.0f;
                self->entries[self->cursor].f10 = 1.0f;
                self->entries[self->cursor].f08 = 1.0f;
                self->entries[9].f10 = self->entries[1].f10;
            }
            if (anim != 0) {
                f32 start = 0.0f;
                if (back != 0) {
                    start = anim->length;
                }
                f32 rate = 1.0f;
                if (back != 0) {
                    rate = -1.0f;
                }
                ReplaceAnimationPlayer(anim, self, 1, &self->f2F0, start, rate);
                SetPendingWarpEntry((s32)self, target, back);
            }
            self->f560 = 0;
            self->f2D8 = self->cursor;
        }
        break;
    }
    if (self->mode != 0) {
        for (s32 i = 0; i < 11; i++) {
            WarpEntry* e = &self->entries[i];
            e->f24 = ApproachValueWithRamp(e->f24, e->f28, g_gameClock.step, D_00276268, 0);
            e->phase = WrapAngle(e->phase + e->speed * g_gameClock.step);
            PlacedObject* a = (PlacedObject*)e->f04;
            PlacedObject* b = (PlacedObject*)e->f0C;
            if (a != 0) {
                a->f298->level = ApproachValueWithRamp(a->f298->level, e->f08, dt,
                                                       self->f2E0 == 2 ? D_00276278 : D_00276288, 0);
            }
            if (b != 0) {
                b->f298->level = ApproachValueWithRamp(b->f298->level, e->f10, dt,
                                                       self->f2E0 == 2 ? D_00276278 : D_00276288, 0);
            }
        }
    }
}

void ApplyWarpPageTransform(WarpPage* obj, u8* s, void* c)
{
    u8 tmp[0x50];
    Camera* p = g_camera;
    f32 keep1 = p->f1C4;
    f32 keep2 = p->f1C8;
    SnapCameraZoom(p, 1.0f);
    BuildPlacedObjectTransform(obj, c, tmp);
    BuildMatrixFromRotationAndTranslation(s + 0x40, s + 0x80, tmp);
    ApplyPlacedObjectTransform(obj, s, tmp);
    SnapCameraZoom(g_camera, keep1);
    g_camera->f1C8 = keep2;
}

void HandleWarpPageNotification(WarpPage* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind != 5) return;
    s32 v = self->mode;
    if (v == 3) goto L_three;
    if (v >= 4) goto L_ge4;
    if (v == 1) goto L_one;
    return;
L_ge4:
    if (v == 4) goto L_four;
    return;
L_one:
    SetWarpPageMode(self, self->f2E0);
    return;
L_three:
    SetScreenFadeMode(&g_screenFade, 2);
    return;
L_four:
    if ((s32)msg != self->f2EC) return;
    ScreenFade* g = &g_screenFade;
    if (g->mode == 3) {
        SetScreenFadeMode(g, 0);
    }
    SetWarpPageMode(self, 0);
}

void SetWarpPageMode(WarpPage* self, u32 next)
{
    s32 i;
    Animation* t;
    s32 cur = self->mode;
    if (cur == (s32)next) {
        return;
    }
    switch (cur) {
    case 1:
    case 4:
        StopSoundRecord(self->sound, 0);
        break;
    case 2:
        if (self->f560 == 0) {
            D_0026F138.vt->m15(&D_0026F138);
        }
        for (s32 k = 0; k < 11; k++) {
            self->entries[k].f28 = 0;
        }
        break;
    case 0: {
        f32 one = 1.0f;
        self->desc->m02(self);
        for (s32 n = 0; n < 11; n++) {
            WarpEntry* s = &self->entries[n];
            if (IsWarpEntryAvailable(self, n, (s32*)0, (s32*)0)) {
                s->f08 = one;
                s32 want;
                if (self->f2E0 == 3) {
                    want = GetCurrentWarpEntry();
                } else {
                    want = self->cursor;
                }
                if (n == want) {
                    s->f10 = one;
                } else {
                    s->f10 = 0;
                }
            } else {
                s->f10 = 0;
                s->f08 = 0;
            }
        }
        *(f32*)((u8*)self + 0x4DC) = *(f32*)((u8*)self + 0x33C);
        for (s32 j = 0; j <= 10; j++) {
            WarpEntry* s = &self->entries[j];
            PlacedObject* a = (PlacedObject*)s->f04;
            PlacedObject* b = (PlacedObject*)s->f0C;
            if (a) {
                a->desc->m02(a);
                EnsureObjectWorldNode(a);
                a->f298->rate = 0;
                a->f298->level = s->f08;
            }
            if (b) {
                b->desc->m02(b);
                EnsureObjectWorldNode(b);
                b->f298->rate = 0;
                b->f298->level = s->f10;
            }
        }
        break;
    }
    }
    switch (next) {
    case 1: {
        if (self->f2E0 == 3) {
            s32 ne = self->cursor != 1;
            Animation* a;
            s32 off;
            if (ne) {
                off = self->cursor * 52;
            } else {
                off = GetCurrentWarpEntry() * 52;
            }
            a = *(Animation**)((u8*)self + off + 0x2F8);
            if (a) {
                f32 fa = 0;
                if (ne) {
                    fa = a->length;
                }
                ReplaceAnimationPlayer(a, self, 0, &self->f2F0, fa, 0.0f);
            }
        } else {
            Animation* a = self->entries[1].f00;
            if (a) {
                ReplaceAnimationPlayer(a, self, 0, &self->f2F0, 0.0f, 0.0f);
            }
            f32 z = 0.0f;
            SetWarpPageSelectedEntry(self, self->cursor);
            self->q540 = self->q550;
            SelectWarpPageEntry(self, self->cursor);
            SetScreenElementHoldTime(&D_0026F138, z);
            D_0026F138.vt->m14(&D_0026F138);
            StartSoundEffect(0x8A, &self->sound, 0, 0, 3000.0f, 300.0f, 1.0f, z, z, 0, 0);
            for (i = 0; i < 11; i++) {
                WarpEntry* s = &self->entries[i];
                s32 r = IsWarpEntryReachable(self, i);
                s->reachable = r;
                s32 v = 0;
                if (r != 0 && ((u32)(i - 2) < 6 || i == 0)) {
                    v = 1;
                }
                s->f20 = v;
                s->f24 = s->f28 = 0.0f;
            }
        }
        self->f2D8 = self->cursor;
        t = self->f2E4;
        if (t != 0) {
            goto L146C;
        }
        goto Lz;
    }
    case 4: {
        if (self->f560 == 0) {
            D_0026F138.vt->m15(&D_0026F138);
            if (self->f2E0 == 2) {
                StartSoundEffect(0x8B, &self->sound, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
        AnnouncePendingWarpEntry(self);
        t = self->f2E8;
        if (t == 0) {
            goto Lz;
        }
    L146C:
        ReplaceAnimationPlayer(t, self, 0, &self->f2EC, 0.0f, 1.0f);
        self->mode = next;
        goto L1550;
    }
    case 2:
        for (s32 m = 0; m < 11; m++) {
            if (m != self->selected) {
                self->entries[m].f28 = 1.0f;
            }
        }
        self->mode = next;
        goto L1550;
    case 3:
        self->f2D8 = -1;
        break;
    case 0:
        for (i = 0; i < 11; i++) {
            PlacedObject* a = (PlacedObject*)self->entries[i].f04;
            PlacedObject* b = (PlacedObject*)self->entries[i].f0C;
            if (a) {
                if (a->f298) {
                    RemoveObjectNodeFromWorld(a->f298);
                }
                a->desc->m03(a);
            }
            if (b) {
                if (b->f298) {
                    RemoveObjectNodeFromWorld(b->f298);
                }
                b->desc->m03(b);
            }
        }
        break;
    default:
        break;
    }
L154C:
    self->mode = next;
L1550:
    self->modeTime = g_gameClock.elapsed;
    return;
Lz:
    next = 0;
    goto L154C;
}

void SetWarpCursor(WarpPage* self, s32 a1, s32 a2)
{
    s32 v = self->mode;
    if (v == 2) goto L_two;
    if (v < 3) {
        if (v == 0) goto L_store;
    } else {
        if (v == 4) goto L_store;
    }
    return;
L_store:
    self->cursor = a1;
    self->f2E0 = a2;
    SetWarpPageMode(self, 1);
    return;
L_two:
    self->cursor = a1;
    if (a2 == 3) {
        SetWarpPageMode(self, 3);
    }
}

void BeginWarpPageClose(WarpPage* self)
{
    s32 v = self->mode;
    if (v < 3) {
        if (v > 0) {
            SetWarpPageMode(self, 4);
        }
    }
}

void MoveWarpCursor(WarpPage* self, s32 idx)
{
    s32 (*table)[4] = D_00276608[self->slot];
    if (table == 0) {
        StartSoundEffect(WARP_SOUND_REFUSE, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    s32 e = table[self->cursor][idx];
    while (e != -1 && self->entries[e].reachable == 0) {
        e = table[e][idx];
    }
    if (e != -1 && self->entries[e].reachable != 0) {
        SetWarpCursor(self, e, 2);
        StartSoundEffect(WARP_SOUND_MOVE, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    } else {
        StartSoundEffect(WARP_SOUND_REFUSE, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
}

void TransformPointBetweenFrames(void* from, void* to, void* in, void* out);
void ProjectPointToCamera(Camera* cam, void* point, f32* out);

void ProjectWarpEntryToScreen(WarpPage* self, s32 idx, s32 flag, f32* out)
{
    Vec02 v;
    BaseObject* o;
    if (flag != 0) {
        o = (BaseObject*)self->entries[idx].f18;
    } else {
        o = (BaseObject*)self->entries[idx].f14;
    }
    if (o != 0) {
        TransformPointBetweenFrames(o->parent, self, (u8*)o + 0x40, &v);
        Camera* g = g_camera;
        Vu0::Q(v) = Vu0::Rotate(g->f80, Vu0::Q(v));
        Vu0::Q(v) = Vu0::Add(Vu0::Q(g->f40), Vu0::Q(v));
        ProjectPointToCamera(g, &v, out);
        out[0] = out[0] * 320.0f + 320.0f;
        out[1] = out[1] * -246.40001f + 246.40001f;
    } else {
        out[0] = 320.0f;
        out[1] = 246.40001f;
    }
}

void SetWarpPageSelectedEntry(WarpPage* self, s32 idx) {
    u8* base = (u8*)self;
    if (*(s32*)(base + 0x534) == idx) {
        return;
    }
    BaseObject* r = *(BaseObject**)(base + idx * 0x34 + 0x30C);
    if (r != 0) {
        TransformPointBetweenFrames(r->parent, self, (u8*)r + 0x40, (Quad16*)(base + 0x550));
    } else {
        *(Quad16*)(base + 0x550) = *(Quad16*)&D_00248D30;
    }
    u8* arr = base + 0x320;
    u8* slot = arr + idx * 0x34;
    *(s32*)slot = 0;
    s32 old = *(s32*)(base + 0x534);
    if (old != -1) {
        *(f32*)(arr + old * 0x34) = 1.0f;
    }
    *(s32*)(base + 0x534) = idx;
}

extern const char D_0024E808[40] = "&2T&. : Back\n&2(&. : Move\n&2X&. : Warp";
void InitWarpMenu(T217D_0F0* self) {
    SetupScreenElementText(self);
    if (IsFontLoaded(2) != 0) {
        self->frame = (Font**)&D_00276620;
        *self->frame = GetFontById(2);
    }
    SetScreenElementHoldTime(self, 0.0f);
    SetScreenElementScale(self, 0.6f);
    self->color = 0xDF7F7F7F;
    self->vt->m08(self, D_0024E808);
    self->current = 0;
    FillMemory(self->nodes, 0, 0x18);
}

void HandleWarpMenuInput(T217D_0F0* self, PadRecord* t)
{
    s32 loc[2];
    s32 s3;
    s32 s2;
    s32 v1;

    if (self->current == 0) return;
    if (self->current->mode != 2) return;
    if (self->current->f560 != 0) return;
    if ((t->flags & 0x910) != 0 || t->f14 == 1) {
        PopStackElement((ElementStack*)g_elementStack);
        ClearPadPressedBits(&g_padRecord, 0x910);
        return;
    }
    if (self->mode != self->current->mode) return;

    s3 = IsWarpEntryAvailable(self->current, self->current->cursor, &loc[0], &loc[1]);
    s2 = GetPadHorizontalStep(t);
    v1 = GetPadVerticalStep(t);
    t->f30 = g_gameClock.elapsed + t->f34;
    t->f38 = g_gameClock.elapsed + t->f3C;

    if (v1 < 0) {
        MoveWarpCursor(self->current, 0);
    } else if (v1 > 0) {
        MoveWarpCursor(self->current, 1);
    } else if (s2 < 0) {
        MoveWarpCursor(self->current, 2);
    } else if (s2 > 0) {
        MoveWarpCursor(self->current, 3);
    } else if ((t->flags & 0x40) != 0) {
        ClearPadPressedBits(&g_padRecord, 0x40);
        if (self->current->cursor != GetCurrentWarpEntry()) {
            if (s3 != 0) {
                IdentityKey* v = LookupEntryById((loc[0] << 8) | loc[1]);
                self->current->f560 = 1;
                PopStackElement((ElementStack*)g_elementStack);
                StartObjectFade(v, -1, 2);
            } else {
                StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        } else {
            PopStackElement((ElementStack*)g_elementStack);
        }
    }

    if (s3 != 0) {
        self->scaleTarget = 1.0f;
    } else {
        self->scaleTarget = D_00275FC0;
    }
    self->scale = ApproachValueWithRamp((RampProfile*)D_00276278, 0, self->scale, self->scaleTarget, g_gameClock.step);
}

void SetWarpMenuOpen(T217D_0F0* self, s32 a1)
{
    if ((a1 != 0) != (self->open == 0)) return;
    if (a1 != 0) {
        HideScreenElements(self);
        s32 r = GetCurrentWarpEntry();
        if (r == 10) {
            r = (IsWarpEntryAvailable(self->current, 1, 0, 0) != 0);
        }
        SetWarpCursor(self->current, r, 2);
        self->scaleTarget = 1.0f;
        self->scale = 1.0f;
        Animation* an = self->current->f2E4;
        if (an != 0) {
            SetScreenElementSlideInTime(self, an->length);
        }
        GameProgress* g = g_saveData;
        if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
            PauseStagedBankVoice();
        }
        self->vt->m14(self);
        SetPadSelectFlags(1);
        ResetPadStepRepeat(&g_padRecord);
        SetElementStackState(g_elementStack, 7);
    } else {
        self->vt->m15(self);
        if (self->current->f560 == 0) {
            BeginWarpPageClose(self->current);
            Animation* an = self->current->f2E8;
            if (an != 0) {
                SetScreenElementSlideOutTime(self, an->length);
            }
            ClearPadSelectFlags(1);
            SetElementStackState(g_elementStack, 3);
            GameProgress* g = g_saveData;
            if (((g->f19D8 << 8) | g->f19DC) == 0x308) {
                ResumeStagedBankVoice();
            }
        }
    }
    self->open = a1;
}

void DrawColoredCircle(f32 cx, f32 cy, f32 radius, f32 angle, s32 n, s32* c1, s32* c2, s32 flags)
{
    FanPoint loc;
    s32 i;
    f32 step = 6.2831855f / (f32)n;
    BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x31001);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x42, (flags & 1) ? 0x48 : 0x44);
    BeginGifTag(&g_gsPacketWriter, 0x4D, 2, 0x41);
    AddGifRgbaEntry(&g_gsPacketWriter, *c1);
    AddGifXyzfEntry(&g_gsPacketWriter, (u32)(s32)((cx + 1728.0f) * 16.0f),
                  (u32)(s32)((cy * 0.454545468f + 1936.0f) * 16.0f), 0, 0);
    loc.k = 0;
    for (i = 0; i < n + 1; i++) {
        ComputeSinCos(WrapAngle(angle), &loc.x, &loc.y);
        loc.x = loc.x * radius + cx;
        loc.y = loc.y * radius + cy;
        if ((i & 1) && (flags & 2)) {
            AddGifRgbaEntry(&g_gsPacketWriter, loc.k);
        } else {
            AddGifRgbaEntry(&g_gsPacketWriter, *c2);
        }
        angle += step;
        AddGifXyzfEntry(&g_gsPacketWriter, (u32)(s32)((loc.x + 1728.0f) * 16.0f),
                      (u32)(s32)((loc.y * 0.454545468f + 1936.0f) * 16.0f), 0, 0);
    }
}

void DrawTriangleGroups(void* self, f32 a, f32 b, f32 c, f32 d);
f32 Sine(f32 x);
u32 GetEntryFlags(u32 packed);
void PushFontScale(Font* font, f32 x, f32 y);
void DrawFontString(Font* font, const void* text, void* out, s32 zero, void* d);
void PopFontScale(Font* font);
extern f32 D_00276648;
// Three floats; the first sizes the warp map's level labels.

// A colour of the warp map, one byte per channel, passed to DrawColoredCircle.
struct WarpColor {
    u8 r, g, b, a;
    WarpColor() {}
    void SetAlpha(s32 a_) { a = a_; }
    WarpColor(u8 r_, u8 g_, u8 b_, u8 a_)
    {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }
};

// The text layout DrawFontString reads (Layout_137228's fields), filled through its setters.
struct WarpLabelLayout;
void SetTextLayoutPosition(WarpLabelLayout* self, f32 x, f32 y);
void SetTextLayoutSize(WarpLabelLayout* self, f32 x, f32 y);
void SetTextLayoutColor(WarpLabelLayout* self, s32* c);
void SetTextLayoutHorizontalAlign(WarpLabelLayout* self, s32 f);
void SetTextLayoutVerticalAlign(WarpLabelLayout* self, s32 f);
#ifdef VERSION_EU
void func_eu_001374E0(WarpLabelLayout* self, s32 f);  // only PAL has this setter
#endif
struct WarpLabelLayout {
    f32 x, y;
    f32 w, h;
    s32 color;
    s32 f14;
    void* f18;
    void Pos(f32 x_, f32 y_) { SetTextLayoutPosition(this, x_, y_); }
    void Size(f32 x_, f32 y_) { SetTextLayoutSize(this, x_, y_); }
    void Color(s32* c) { SetTextLayoutColor(this, c); }
    void FlagA(s32 f) { SetTextLayoutHorizontalAlign(this, f); }
    void FlagB(s32 f) { SetTextLayoutVerticalAlign(this, f); }
#ifdef VERSION_EU
    void FlagC(s32 f) { func_eu_001374E0(this, f); }
#endif
};


void DrawWarpMenu(T217D_0F0* self)
{
    if (self->current == 0) {
        return;
    }
    f32 one = 1.0f;
    Camera* cam = g_camera;
    f32 keep1 = cam->f1C4;
    f32 keep2 = cam->f1C8;
    SnapCameraZoom(cam, one);
    if (g_coloredTriangleSet != 0) {
        Vec02 v;
        f32 out[2];
        WarpColor inner;
        WarpColor outer;
        f32 b2 = self->blend * self->blend;
        Vu0::Q(v) = Vu0::Q(self->current->q540);
        Camera* g = g_camera;
        Vu0::Q(v) = Vu0::Rotate(g->f80, Vu0::Q(v));
        Vu0::Q(v) = Vu0::Add(Vu0::Q(g->f40), Vu0::Q(v));
        ProjectPointToCamera(g, &v, out);
        out[0] = out[0] * 320.0f + 320.0f;
        out[1] = out[1] * -246.40001f + 246.40001f;
        inner.r = 0;
        inner.g = 0;
        inner.b = 0;
        inner.a = (u8)(s32)(b2 * 145.0f);
        outer.r = 0;
        outer.g = 0;
        outer.b = 0;
        outer.a = 0;
        DrawColoredCircle(out[0], out[1], 40.0f, WrapAngle(g_gameClock.elapsed), 12, (s32*)&inner, (s32*)&outer, 2);
        f32 s = Sine(g_gameClock.elapsed * 10.0f);
        DrawTriangleGroups((void*)g_coloredTriangleSet, out[0], out[1], s * 0.2f + one, b2);
    }
    for (s32 i = 0; i < 11; i++) {
        WarpEntry* e = &self->current->entries[i];
        if (e->reachable == 0) {
            continue;
        }
        WarpColor c0, c1, c2;
        if (e->f20 != 0) {
            c0 = WarpColor(0x9F, 0xFF, 0xE8, 0x4B);
            c1 = WarpColor(0x5C, 0xFF, 0xB6, 0);
            c2 = WarpColor(0x19, 0xFF, 0x64, 0);
        } else {
            c0 = WarpColor(0xE8, 0xE8, 0xE8, 0x4B);
            c1 = WarpColor(0xB6, 0xB6, 0xB6, 0);
            c2 = WarpColor(0x4B, 0x4B, 0x4B, 0);
        }
        f32 pos[2];
        ProjectWarpEntryToScreen(self->current, i, 0, pos);
        f32 size = e->f24 * self->blend;
        if (AreFloatsNearlyEqual(size, 1.0f, 0.0001f) && i < 9) {
            s32 slot = self->current->slot;
            if ((GetEntryFlags((slot << 8) | i) & 2)
                && !(*(s32*)((u8*)g_saveData + (slot * 0x44C + i * 0x78) + 0x10) & 2)) {
                size = Sine(g_gameClock.elapsed * 20.0f) * 0.2f + 0.8f;
            }
        }
        WarpColor a = c0;
        WarpColor b = c1;
        DrawColoredCircle(pos[0], pos[1], size * D_00276648, e->phase, 14, (s32*)&a, (s32*)&b, 3);
        b = c0;
        a = c1;
        DrawColoredCircle(pos[0], pos[1], size * D_00276650, -e->phase, 10, (s32*)&b, (s32*)&a, 3);
        if (i < 9) {
            s32 slot = self->current->slot;
            if (GetEntryFlags((slot << 8) | i) & 2) {
                f32 scale = e->f24;
                s32 flags = *(s32*)((u8*)g_saveData + (slot * 0x44C + i * 0x78) + 0x10);
                Font* font = GetFontById(3);
                f32 k = D_0027663C[0] * scale;
                PushFontScale(font, k, k);
                WarpLabelLayout L;
                f32 x = pos[0];
                f32 y = pos[1];
                b = *(WarpColor*)&self->rgba;
                b.SetAlpha(0xFF);
                s32 held = *(s32*)&b;
                L.Pos(x, y);
                L.Size(0.0f, 0.0f);
                T217D_Word tmp;
                tmp.v = held;
                L.Color(&tmp.v);
                L.FlagA(1);
                L.FlagB(1);
                DrawFontString(font, (flags & 2) ? "k" : "l", &L, 0, &g_gsPacketWriter);
                PopFontScale(font);
            }
        }
    }
    SnapCameraZoom(g_camera, keep1);
    g_camera->f1C8 = keep2;
}

// The style above (D_00276620) and D_00276650 are built by the static initialiser GCC writes
// here (func_001F2688), and its _GLOBAL_$I$ (func_001F2738) follows the 12 bytes the linker left
// of a function this file wrote out after it (tools/compile.py moves the block there).
LINKER_REMNANT_AFTER_INIT(func_001F2728);
