// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 74/128 (57.8%), checked 2026-11-08
// NEAR (2026-11-08, night-size2): the same size as retail now: its dead `li v0,1` is the compare of an `if (dir == 1)` whose arms (the state and clip stores, the clip read before) compile alike, which jump2 cross-jumps and deletes, as the file's other dead compare (5 compiles). Still differs: registers and the order of the loads (retail: e in t1, self in a3, dir in t0, the clip in v1, the clock's high half in a2 at the top); arms over more or fewer of the statements were further off.
// In the context of its file, src/main/file_1E88D0.cpp: its declarations before the function, bodies cut.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
// Tried (order-class pass 2): the fC60 float read first, the empty if kept, entry stores first, entry stores after the load of the clock: 21 to 31 words, baseline 19.
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
#include "c62.h"
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
#include "vu0.h"
#include "asm_func.h"
#include "vu0.h"

void SteerAgentAlongPath(void);
void InitElementStack(void* p);
void QueueEachScreenElementDraw(void);
void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a, void* p);
void* CreateStateWalker(void* a, void* self, s32 b, s32 c);
void AppendQueuedCall(void* a, void* cb, void* ctx, s32 b, s32 c);
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
void func_001C8418(KeyedConeAgent* self, void* p);
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
s32 SolveQuadratic(f32* roots, f32 a, f32 b, f32 c);
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
void ContinueBeatPressColliderRequest(void);
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
double func_001FCD20(double a, double b);
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
void func_0012EBD8(ListedObject* n, f32 dt);
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
void func_0012EBD8(u8* n, f32 dt);
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
s32 QueryValueTreeMask(void* self, void* node, Bits128 q, s32* out);
typedef void (*AttachNotifyFn)(void* self, void* arg);
void BuildPlacedObjectTransform(void* obj, void* c, void* out);
void func_00125C90(void* obj, void* s, void* out);
void func_001C8418(void* self, void* p);
void UpdateAgentGoal(void* self);
void InitObject(void* self);
void PadPacketToQuadSlot(void* s, s32 target);
s32 WriteVifUnpackHeader(void* self, s32 a, s32 b, s32 c);
void AddDmaRefTag(void* obj, s32 a, s32 b);
void ReadLinkedItemArray(void* src, s32* count, void** out);
s32 ReadBufferedU16(void* src);
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
s32 SetGatheredWalkerTargets(World* mgr, s32 a, void* b, C62* self, s32 c);
void GetStateWalkerCurrentKey(s32 sub, s32* out);
void ScheduleTempoAgentBeatPress(TempoAgent* p);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32* c);
void ResetPadStepRepeat(void* p);
void StartSoundEffect(s32 a0, Timeline* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern u8 D_00625760[];
s32 FillMemory(Entry90* dst, s32 value, s32 size);
// The dead "li v0,2" after the func_001ED090 call is the compare constant of an
// "if (n == 2)" whose two arms compile identically: jump2 cross-jumps the arms after
// reload, deletes the branch and leaves the constant load.
void EnterAgentState(TempoAgent* self, s32 a, s32 b);
void MarkLevelDone(s32 n);
void StartMemoryCardSave(void* p);
f32 ArctangentOfRatio(f32 a, f32 b);
void CopyMemory(TempoPlayerEntry* dst, TempoPlayerEntry* src, s32 bytes);
void RunTimelineEntry(Timeline* self, Entry90* e);
void* MoveMemory(void* dst, void* src, s32 size);
// An array-move helper: its parameter copies give retail its (i * 4 + self) base shared by both pointers.
// Moves n bytes of the item list down over a removed item.
struct MoveItemsDown {
    static void Of(C62** dst, C62** src, s32 n)
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
s32 TransformPointBetweenFrames(void* a, s32 b, void* c, s32 d);
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
s32 FillMemory(WarpTextStyle* p, s32 zero, s32 size);
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
void* FillMemory(void* p, s32 v, s32 size);
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
void SetStateAndNotify(C62* self, s32 state);
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
// size: s32 read as one word (file_14EE40.cpp and screen_element.cpp test bit 8)
// size: s32 compared with 1 in file_149398.cpp and 2 in pause_menu.cpp
s32 D_00275BEC = 0;
s32 D_00275BF0[10] = { 0, 0, 3, 10, 6, 63, 3, 11, 5, 31 };
f32 D_00275C18[4] = { 2.0f, 0.0f, 0.1f, 0.0f };
f32 D_00275C28[3] = { 1.0f, 0.0f, 0.1f };
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
// word read whole / address only, 4 bytes to next label
s32 D_00275DB4 = 0;
// size: s32 state compared/assigned in 001EC000
s32 D_00275DB8 = 0;
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
#ifdef VERSION_EU
// PAL's own addresses for these two, which the tools do not pair with US's (VERSION_NAME).
f32 D_eu_0027FDAC = 24.0f;
f32 D_eu_0027FDB0 = D_eu_0027FDAC * 0.75f;
#else
f32 D_00276648 = 24.0f;
f32 D_00276650 = D_00276648 * 0.75f;
#endif
s32 D_00276654;

void InitKeyedConeAgent(KeyedConeAgent* self);

// The file's first read-only data, for func_001E89F0.
extern const f32 D_0024E600[4] = {3.40282347e+38f, 0.0f, 0.0f, 0.0f};

void StartKeyedConeAgent(KeyedConeAgent* self);

s32 ChooseKeyedConeAgentState(KeyedConeAgent* self);

s32 IsKeyedConeAgentFree(KeyedConeAgent* a0);

s32 IsKeyedConeAgentTargetInRange(KeyedConeAgent* a0);

void SteerKeyedConeAgentAlongPath(KeyedConeAgent* a0);

void RestartKeyedConeAgentClip(KeyedConeAgent* self);

void UpdateKeyedConeAgentGoal(KeyedConeAgent* self);

void UpdateKeyedConeAgentState(KeyedConeAgent* self);

void ShowElementWhenMenusClear(void);

s32 TestAgentMayContactExceptKeys(KeyedConeAgent* self, Collider* probe);

void InitGlobalElementStack(void);

void InitElementStack(ElementStack* self);

void ResumeElementStackState(void* self);

void UpdateElementStack(ElementStack* obj);

void PushStackElement(ElementStack* self, ScreenElement* node);

void PopStackElement(ElementStack* g);

void DrawAllScreenElements(void);

void QueueScreenElementDraws(void);

void ResetElementStack(ElementStack* self);

void SetElementStackState(ElementStack* self, s32 state);

void ApplyStackTimeScale(float x);

s32 AreMenusAndFadeClear(void);

s32 AreMenusClosed(void);

s32 IsArcDrawAllowed(void);

s32 AreArcMenusClosed(void);

void StepMemoryChecksum(void);

void UpdateWorldDeltaLists(World* self, f32 dt);

void UpdateUnflaggedParts(World* self);

void UpdateWorldStepLists(World* self, f32 dt);

void StepWorldValueTowardTarget(World* self, f32 x);

void UpdateWorld(World* self);

f32 WrapAngle(f32 a);

f32 ClampToMagnitude(f32 a, f32 b);

f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);

f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, void* self, f32* out);

f32 ApproachAngleWithRamp(f32 a, f32 b, f32 c, void* self, f32* out);

f32 ApproachAngleClampingVelocity(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1);

s32 RandomIntInRange(s32 a, s32 b);

f32 RandomFloatInRange(f32 a, f32 b);

f32 RandomGaussian(f32 mean, f32 deviation, f32 limit);

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 tolerance);

s32 SolveQuadratic(f32* roots, f32 a, f32 b, f32 c);

void RemapQuadraticParameter(Vec3* in, Vec3* out, f32 s, f32 t);

void ComputeSinCos(f32* sinOut, f32* cosOut, f32 angle);

double TruncateDouble(double x);

f32 TruncateFloat(f32 x);

f32 WrapModulo(f32 x, f32 y);

void FitQuadraticCurve(f32* a0, f32 x, f32 y, f32 z, f32 w);

s32 IsInsideRange(ValueRange* span, f32 x);

s32 IsInsideAnyRange(s32 count, ValueRange* spans, f32 x);

f32 ClampToRange(ValueRange* span, f32 x);

s32 CompareFloats(f32* a, f32* b);

void IgnoreStackLocal(void);

// A sample FindLocalMinimum keeps: an argument and the function's value there.
struct MinimumSample {
    f32 x;
    f32 y;
};

typedef f32 (*MinimumFn)(void* ctx, f32 x);

void FindLocalMinimum(f32 x, f32 step, f32 lo, f32 hi, MinimumFn fn, void* ctx, f32* outX, f32* outY);

void InitBeatPressCollider(BeatPressCollider* self);

void LoadBeatPressCollider(BeatPressCollider* self);

void CopyPlayerAttachBlock(BeatPressCollider* a0);

void StartBeatPressCollider(BeatPressCollider* self);

void HandleBeatPressColliderActivation(BeatPressCollider* self, void* p);

void JudgeBeatPressInput(BeatPressCollider* self, PadRecord* in);

s32 IsBeatPressColliderRequestBlocked(BeatPressCollider* self);

void AppendBeatPressEntry(BeatPressCollider* list, const U64P* src);

s32 AcceptBeatPressColliderRequest(void);

// What GetBeatPressColliderPositionAt reads of its f67C: an object to place at a time (+0x18) and
// a point in its frame (+0x40).
struct FramePoint_001EBD10 {
    u8 pad0[0x18];
    void* object;           // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 point;            // 0x40
};

void GetPlacedObjectPositionAt(void* self, f32 t, Vec02* pos, Vec02* vel);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, Vec02* e, Vec02* f, f32 t);

void func_001EBD10(BeatPressCollider* self, f32 t, Vec02* pos, Vec02* vel);

void InitTempoAgent(TempoAgent* self);

void StartTempoAgent(TempoAgent* self);

void UnregisterTempoAgent(void);

void RegisterTempoAgent(void);

s32 IsTempoAgentTargetInRange(TempoAgent* self);

s32 IsTempoAgentFree(void);

void ApplyTempoAgentTransform(TempoAgent* self, void* s, void* c);

void LeaveTempoAgentState(TempoAgent* self, void* arg);

void DecrementTempoAgentGauge(TempoAgent* self);

void EnterTempoAgentState(TempoAgent* self, s32 a, s32 b);

void ScheduleTempoAgentBeatPress(TempoAgent* self, Entry90* e);

void ScheduleTempoAgentBeatPress(TempoAgent* self, Entry90* e)
{
    s32 dir = e->fC;
    Ent1C entry;
    s32 clip = self->fC10[dir];
    self->fC40 = dir;
    if (dir == 1) {
        self->fC20 = clip;
    } else {
        self->fC20 = clip;
    }
    self->fC44 = g_gameTime[0];
    entry.dir = dir;
    entry.t = (f32)e->f4 * 4.0f + e->f8 + (f32)self->fC60;
    AppendBeatPressEntry(self->fC3C, (const U64P*)&entry);
}
