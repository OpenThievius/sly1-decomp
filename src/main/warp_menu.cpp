// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// arc_element.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276680, which ends
// with a build stamp no code reads; the C library's state record after it is
// src/lib/library_state.c's (that file says why). Its name is ours, after its largest family, the
// warp page and menu, whose text styles its static initialiser builds. That is about a fifth of
// its code: it also holds the keyed cone agent, the element stack, the world's update, the math
// helpers, the tempo agent with its beat presses and timelines, the VIF writer, the attached set
// and the screen fade.
#include "common.h"
#include "scaled_transform.h"
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
#include "world3_timeline.h"
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
#include "object_finder.h"
#include "layout_137228.h"
#include "plane_node.h"
#include "functions/anim_record.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/colored_triangle_set.h"
#include "functions/cone_agent.h"
#include "functions/disc_access.h"
#include "functions/display.h"
#include "functions/effect_spawner.h"
#include "functions/entry_queue.h"
#include "functions/flagged_object.h"
#include "functions/game_clock.h"
#include "functions/group_marker.h"
#include "functions/matrix.h"
#include "functions/memory_card.h"
#include "functions/object_pool.h"
#include "functions/on_off_object.h"
#include "functions/pad_input.h"
#include "functions/pair_controller.h"
#include "functions/path_follower.h"
#include "functions/player.h"
#include "functions/pose_source.h"
#include "functions/screen_element.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/turning_collider.h"
#include "functions/world_contacts.h"
#include "functions/zone_collider.h"
struct BufferedStream;
struct WorldObjectNode;

struct BaseObject;
struct ContactTracker;
struct Mat3;
struct ObjectSubGroup;
struct ContactTrackerRecord;

struct Mat3;


// Types other files define, named by the parameters of their functions declared here.
struct PadPatternPlayer;
struct ScaledTransform;

void SteerAgentAlongPath(Agent* self);
void InitElementStack(ElementStack* self);
struct StateGraph;
void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d); // stays void: retail returns a value, but declared so func_001EB598 differs in registers
void CopyPlayerAttachBlock(World3BeatPressCollider* self);
struct SwitchedCollider;
void HandleSwitchedColliderActivation(SwitchedCollider* self, void* activator);
extern s32 g_buttonCodeFlags;
s32 IsPadSelectFlagHeld(World* self);
s32 TestAgentMayContact(Agent* self, Collider* obj);
void SetElementStackState(ElementStack* self, s32 state);
extern "C" f32 FloatRemainder(f32 x, f32 y);
s32 IsInsideRange(ValueRange* span, f32 x);
extern float g_gameTime[];
f32 WrapModulo(f32 x, f32 y);
PlacedObject* FindNearestAgentKey(void* a, void* b);
void* FindObjectHandle(PlacedObject* self, s32 key);
void RestartAgentClip(Agent* self);
typedef void* (*TargetObjectFn)(void* self);
void SetAgentGoalPoint(Agent* self, Vec4* p);
void UpdateAgentGoal(Agent* self, s32 flag);
void GetObjectWorldPosition(BaseObject* self, Vec4* out);
void FaceAgentTowardGoalPoint(Agent* self);
void UpdateAgentState(Agent* self);
extern u8 g_flagTable[];
struct FlagTable;
void SetWorldActiveFollower(World* self, void* v);
s32 AreMenusAndFadeClear(void);
extern s32 g_displayMode;
extern s32 g_world3BossPendingVoice;
void InitAgent(Agent* self);
void* AllocateFrontMemory(s32 size);
void PopStackElement(ElementStack* g);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
f32 WrapAngle(f32 a);
f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, void* self, f32* out);
s32 NextRandom(void);
s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots);
void StartAgent(Agent* self);
void* CopyToFrontMemory(s32 size, void* name);
// An object the tempo agent finds by id at its start (func_001EBFB0 copies D_00275D48 to
// 0xC9C and fills each obj).
struct TempoObjectRef { s32 id; f32 f04; BaseObject* obj; };
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);
s32 ChooseAgentState(Agent* self);
extern s32 g_previousSoundLevel;
extern f32 g_elapsedTime[];
void ApplyStackTimeScale(ElementStack* a, f32 f);
void SetScreenFadeMode(u8* a, s32 v);
void ReleasePadSelectFlag(World* self);
void AcquirePadSelectFlag(World* a0);
extern u32 g_padRouting;
extern u32 g_padSelectFlags;
extern s32 D_002701B8;
extern void* FindActiveObjectSubGroup(void);
extern void StartObjectSubGroupFinish(ObjectSubGroup* self);
extern void ResetGameProgress(GameProgress* self);
extern void ResumeAtSavedLevel(void);
extern void SetPauseMenuLayerPage(PauseMenu* self, s32 idx, s32 value);
extern void PushStackElement(ElementStack* o, ScreenElement* g);
extern void ApplyStackTimeScale(ElementStack* o, f32 v);
extern void SetElementStackState(ElementStack* o, s32 mode);
typedef s32 (*World3BeatPressSlotFn)(World3BeatPressCollider* self, void* arg);
typedef void (*PlayerSlotFn)(Player* g, void* arg);
void GetObjectWorldPosition(BaseObject* self, Vec4* out);
void GetObjectWorldRotation(BaseObject* self, Mat3* out);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
s32 HasSpareCount(void);
void ActivateSwitchedCollider(void* value);
void ContinueWorld3BeatPressColliderRequest(PlacedObject* from, Player* self);
void EndHeldWorld3Timeline(World3Boss* o);
extern s32 D_00275C34;
extern u32* g_memoryChecksumCursor;
extern s32 g_memoryChecksumRemaining;
extern u32 g_memoryChecksumValue;
extern u8 g_memoryChecksumEnd[];
extern u32 g_crc32Table[];
struct Crc32 {
    static u32 Step(u32 h, u8 b) { return g_crc32Table[(h ^ b) & 0xFF] ^ (h >> 8); }
};
void InitSwitchedCollider(SwitchedCollider* self);
f32 RandomFloatInRange(f32 lo, f32 hi);
extern "C" f32 Logarithm(f32 x);
s32 IsPadSelectFlagHeld(World* p);
#include "double_bits.h"
extern "C" double AddDoubles(double a, double b);
// An object of the world's lists at 0x78, 0x1B70 and 0x1C30 as func_001E9EE8 walks them: the
// slot at 0x7C of the first list's objects is called with the frame time.
struct ListedObject;
struct ListedObjectVt {
    u8 pad0[0x7C];
    void (*update)(ListedObject*, s32, f32);
};
struct ListedObject { ListedObjectVt* vtbl; };
struct BeginNodeWalk {
    static void Of(ListFrame* it, ObjectList* list)
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
void UpdateObjectTree(void* self, f32 f);
void UpdateAnimationPlayer(AnimationPlayer* self, f32 dt);
void RunQueuedCalls(World* self);
struct BeginByteWalk {
    static void Of(ListFrame* it, ObjectList* list)
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
void UpdateObjectTree(void* self, f32 f);
void UpdateAnimationPlayer(AnimationPlayer* self, f32 dt);
struct NextActor {
    static UpdatedObject* Of(ListFrame* it)
    {
        UpdatedObject* obj = *(UpdatedObject**)it->link;
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
s32 IsObjectTreeAtRest(UpdatedObject* n);
void ClearRootTries(PlacedObject* self);
void RunDueDelayedScriptCalls(World* self, f32 t);
void NotifyWorldActiveFollower(World* self);
void ReleaseWorldListEntry(void* a0);
void StepWorldValueTowardTarget(World* self, f32 t);
void RunWorld3TimelineEntry(World3Timeline* self, TimelineEntry* msg);
TimelineEntry* AppendWorld3TimelineEntry(World3Timeline* self, s32 a, s32 b, f32 c);
// What ComputeSinCos writes for func_001ED650.
struct SinCos { f32 sine; f32 cosine; };
void ComputeSinCos(f32* sinOut, f32* cosOut, f32 angle);
void RegisterSwitchedCollider(SwitchedCollider* self);
void AddAnimationPlayerRecordCallback(AnimationPlayer* a0, PlacedObject** a1);
s32 ComputeBallisticLaunchVelocity(Vec4* from, Vec4* to, Vec4* out, u8* rec, f32 angle);
s32 WriteVifUnpackHeader(PacketWriter* self, s32 a, s32 b, s32 c);
void ReleaseAttachRecords(World* self, ColliderAttachment* node);
void SetScreenFadeMode(void* o, s32 mode);
void UnregisterObjectGroup(World* self, FoundList* s);
void RegisterObjectGroup(World* self, FoundList* group);
struct ContactTrackerRecord;
struct TrackedNodeOffer;
void OfferTrackedNodeLaunch(ContactTrackerRecord* self, void* a1, TrackedNodeOffer* out);
void InitPlacedObject(PlacedObject* self);
void SetStateAndNotify(void* self, s32 b);
struct ZoneTargetEntry;
void UnregisterSwitchedCollider(SwitchedCollider* self);
void EndWorld3Timeline(void* p);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void ComputeSinCos(f32 angle, f32* sinOut, f32* cosOut);
typedef u64 Bits128 __attribute__((mode(TI)));
s32 QueryValueTreeMask(ValueListObject* self, sptr node, Bits128 point, f32 radius, s32* out);
typedef void (*AttachNotifyFn)(void* self, void* arg);
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);
void ApplyPlacedObjectTransform(PlacedObject* self, Camera* cam, ScaledTransform* xf);
void SetAgentGoalPoint(Agent* self, Vec4* p);
void UpdateAgentGoal(Agent* self, s32 flag);
void PadPacketToQuadSlot(void* s, s32 target);
s32 WriteVifUnpackHeader(PacketWriter* self, s32 a, s32 b, s32 c);
void AddDmaRefTag(PacketWriter* self, s32 lo, s32 hi);
struct BufferedStream;
struct BufferedStream;
struct LinkedItem;
void ReadLinkedItemArray(BufferedStream* src, s32* count, LinkedItem** out);
u16 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedU32(BufferedStream* self);
// The message (kind 11) func_001EF3D8 sends the object it detaches.
struct DetachMsg { AttachedSet* self; Collider* obj; };
void RebuildAttachedSet(AttachedSet* self);
void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void InitTrackedNodes(ContactTrackerRecord* a, ContactTracker* b);
extern s32 g_worldLoadRequest;
s32 RestoreFadeRequest(ScreenFade* self, PadRecord* o, s32 mode);
void SetScreenFadeMode(ScreenFade* self, s32 state);
typedef void (*TempoCallFn)(void);
void UpdateAgent(Agent* self, f32 dt);
void RestartWorld3Timeline(World3Timeline* sub);
void RunWorld3TimelineEntries(World3Timeline* sub);
void SyncWorld3BossEntries(World3Boss* self);
void LeaveAgentState(Agent* self, s32 mode);
void AppendPacketQuadwords(PacketWriter* self, s32 n, void* src);
extern void* g_stateResetGroupMethods[6];
void* AllocateZeroedFrontMemory(s32 n);
void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor);
struct ColoredTriangleSet;
extern ColoredTriangleSet* g_coloredTriangleSet;
// retail's caller evaluates them after the integers, as this order does.
void WriteColoredSpritePacket(s32 r, s32 g, s32 b, s32 a, PacketWriter* p, f32 x0, f32 y0, f32 x1, f32 y1);
void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag);
extern u8 g_packetWriterVtable[];
s32 InitPacketBuffer(PacketWriter* self);
// The ListFrame of func_001EECE0's walk of its children, opened and closed by its lifetime.
struct ChildWalkFrame {
    s32* a; s32* b; s32 c; ChildWalkFrame* prev;
    ChildWalkFrame(s32* p) : a(p), b(p), c(p[2]), prev((ChildWalkFrame*)g_activeListFrames) {}
    ~ChildWalkFrame() { g_activeListFrames = (ListFrame*)prev; }
};
void StartPlacedObject(PlacedObject* self);
void FillTrackedNodes(ContactTrackerRecord* self);
// The message (kind 0x16) func_001EF900 sends with a state change: the old and new states.
struct StateChangeMsg {
    void* self;
    s32 old;
    s32 cur;
};
struct ZoneTargetEntry;
void ScheduleWorld3BossBeatPress(World3Boss* self, TimelineEntry* e);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
extern u8 D_00625760[];
extern "C" void* FillMemory(void* p, s32 value, s32 size);
// The dead "li v0,2" after the func_001ED090 call is the compare constant of an
// "if (n == 2)" whose two arms compile identically: jump2 cross-jumps the arms after
// reload, deletes the branch and leaves the constant load.
void EnterAgentState(Agent* self, s32 evt, Animation* arg);
void MarkLevelDone(s32 n);
struct FlaggedObject;
struct ScatterController;
void RaiseScatterLevelForObject(ScatterController* obj, FlaggedObject* node);
extern u8 g_scatterController[];
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void CopyMemory(void* dst, void* src, u32 size);
void RunWorld3TimelineEntry(World3Timeline* self, TimelineEntry* e);
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
// A FadeRequest moved as a 16-byte unaligned block and its last word.
struct FadeRequestBlock {
    QuadP pair;
    s32 mid;
};
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void SetWarpPageSelectedEntry(void* self, s32 value);
extern s32 g_pendingWarpEntryAtEnd;
void StartScreenFade(ScreenFade* dst, FadeRequest* args, s32 count);
void SetWarpPageMode(WarpPage* self, u32 next);
void* AllocateFrontMemory(int size);
// The pad (include/c73.h's neighbours): its buttons at +0xAA, its direction timers at +0x30 .. 0x3C.
s32 IsWarpEntryAvailable(WarpPage* o, s32 n, s32* a, s32* b);
void MoveWarpCursor(WarpPage* o, s32 n);
s32 GetCurrentWarpEntry(void);
void PopStackElement(ElementStack* q);
IdentityKey* LookupEntryById(s32 k);
void StartObjectFade(IdentityKey* v, s32 m, s32 n);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);
s32 IsWarpEntryAvailable(WarpPage* self, s32 kind, s32* outA, s32* outB);
void SetWarpCursor(WarpPage* self, s32 a1, s32 a2);
void BeginWarpPageClose(void* self);
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
extern void* g_currentWarpPage;
extern s32 g_previousLevelIndex;
struct WorldLoadRequest;
struct WorldKeyBlock;
struct KeyedEntry;
s32 GetEntryIdByKey(KeyedEntry* key);
void ShowCountedScreenElement(World* self);
struct WarpTextStyle;
extern "C" void* FillMemory(void* p, s32 value, s32 size);
// The text style the warp menu draws with: the static initialiser (func_001F2688) zeroes it, then
// sets its kind, two sizes given as integers, 0.3 twice and its colour.
struct WarpTextStyle {
    u8 pad0[4];
    u8 kind;
    u8 pad5[3];
    f32 paddingX;
    f32 paddingY;
    f32 scaleX;
    f32 scaleY;
    s32 color;
    WarpTextStyle(s32 a, s32 b)
    {
        FillMemory(this, 0, 0x1C);
        kind = 0x3D;
        paddingX = a;
        paddingY = b;
        scaleY = scaleX = 0.3f;
        color = (s32)0xFF7D4B00;
    }
};
extern f32 g_warpInnerCircleScale;
s32 IsFontLoaded(s32 n);
Font* GetFontById(s32 n);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern void StartPlacedObject(PlacedObject* self);
s32 IsWarpEntryReachable(void* self, s32 code);
void SelectWarpPageEntry(WarpPage* o, s32 n);
void AnnouncePendingWarpEntry(WarpPage* o);
void SetWarpPageSelectedEntry(WarpPage* o, s32 n);
void EnsureObjectWorldNode(PlacedObject* o);
void ReplaceAnimationPlayer(Animation* anim, BaseObject* owner, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void PostLoadPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
struct NextPageNode {
    static BaseObject* Of(ListFrame* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct BeginPageWalk {
    static void Of(ListFrame* it, ObjectList* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};
extern s32 (*g_warpCursorTables[6])[4];
// The sounds MoveWarpCursor plays: the cursor moved, or it could not.
enum WarpCursorSound { WARP_SOUND_MOVE = 0x79, WARP_SOUND_REFUSE = 0x7B };
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
// A point of the fan func_001F1E38 draws: its colour and, at 0x10, its position.
struct FanPoint { s32 k; s32 pad[3]; f32 x; f32 y; };
void BeginGifTag(PacketWriter* f, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* f, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* self, u32 value);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void InitElementStack(ElementStack* self);
void PushStackElement(ElementStack* self, ScreenElement* node);
void SetElementStackState(ElementStack* self, s32 state);
void ApplyStackTimeScale(ElementStack* stack, f32 x);
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);
void AddWorld3BossEntry(World3Boss* self, AnimationPlayer* a, s32 b);
void RestartWorld3Timeline(World3Timeline* self);
void EndWorld3Timeline(World3Timeline* self);
void RunWorld3TimelineEntries(World3Timeline* self);
void SetStateAndNotify(StateResetObject* self, s32 state);
s32 RestoreFadeRequest(ScreenFade* self, PadRecord* o, s32 mode);
void SetWarpPageMode(WarpPage* self, u32 next);
void SetWarpCursor(WarpPage* self, s32 a1, s32 a2);
void SetWarpPageSelectedEntry(WarpPage* self, s32 idx);

ObjectLink g_world1BossLinks[8] = {
    { 3, 0x2D5, 0xC50 }, { 3, 0x2E7, 0xC60 }, { 7, 0x2E1, 0xC64 }, { 7, 0x2E2, 0xC68 },
    { 7, 0x2E3, 0xC6C }, { 7, 0x2E4, 0xC70 }, { 7, 0x2E5, 0xC74 }, { 7, 0x2E6, 0xC78 }
};
// word read whole / address only, 4 bytes to next label
// readers pass only its address; byte buffer, size to next label
u8 g_elementStack[4] = {0};
INCLUDE_DATA(D_00275BC4);
// size: s32 read as one word (pooled_object.cpp and screen_element.cpp test bit 8)
// size: s32 compared with 1 in item_column.cpp and 2 in pause_menu.cpp
s32 D_00275BEC = 0;
// size: s32, the element stack's resumeState (+0x30): compared with 1 and 2 in pause_menu.cpp and
// screen_element.cpp, with the style in this file
s32 D_00275BF0 = 0;
// Unread and unexplained: a zero word and the table {3, 10, 6, 63, 3, 11, 5, 31} follow it up to
// D_00275C18, which nothing reads; their bytes come from the disassembly.
INCLUDE_DATA(D_00275BF4);
f32 g_worldValueFallRamp[4] = { 2.0f, 0.0f, 0.1f, 0.0f };
f32 g_worldValueRiseRamp[3] = { 1.0f, 0.0f, 0.1f };
s32 D_00275C34 = 0;
// size: func_0012A610/func_0012A6E0 copy it as a 16-byte vector
Quad16 g_zeroQuad = {0};
f32 g_unitXQuad[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
ValueRange g_unitRange = { 0.0f, 1.0f };
ValueRange D_00275C68 = { -1.0f, 1.0f };
f32 g_beatPressTimingWindowRange[4] = { 0.5f, 0.8f, 0.0f, 0.0f };
f32 g_beatPressTimingCurve[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
ObjectLink g_world3BeatPressLoadLinks[1] = { { 0, 0x4C9, 0x610 } };
ObjectLink g_world3BeatPressStartLinks[4] = {
    { 4, 0x4D0, 0x618 }, { 4, 0x4D1, 0x61C }, { 4, 0x4D2, 0x620 }, { 4, 0x4D3, 0x624 }
};
f32 g_beatPressRequestSideSpeed = 700.0f;
f32 g_beatPressRequestUpSpeed = 650.0f;
s32 g_world3BeatPressWalkerTargets[4] = { 1228, 1230, 1229, 1231 };
s32 g_world3BeatPressSoundIds[4] = { 574, 576, 575, 577 };
s32 g_world3BossClipIds[4] = { 1247, 1248, 1249, 1250 };
ObjectLink g_world3BossStartLinks[5] = {
    { 1, 0x4EB, 0xC50 }, { 0, 0x4E7, 0xC24 }, { 0, 0x4E8, 0xC28 }, { 0, 0x4E9, 0xC2C },
    { 0, 0x4EA, 0xC30 }
};
TempoObjectRef g_world3BossObjectRefs[9] = {
    { 0x35, 50.0f, 0 }, { 0x36, 50.0f, 0 }, { 0x38, 80.0f, 0 }, { 0x3B, 80.0f, 0 },
    { 0x60, 70.0f, 0 }, { 0x50, 220.0f, 0 }, { 0x52, 80.0f, 0 }, { 0x53, 80.0f, 0 },
    { 0x54, 80.0f, 0 }
};
// The data from D_00275DB8 on is defined after DrawWorld3BossRing (func_001EC190), whose static's
// guard (D_00275DB4) retail's .data has before it: the compiler writes a guard out with its
// function. Declared here for the functions above that.
extern s32 g_world3BossVoiceState;
extern s32 g_unpackBytesPerElement[16];
extern s32 g_stateResetObjectLinks[92];
extern ScreenFade g_screenFade;
extern f32 g_scaleTargetSmall;
extern s32 g_warpSlotKindMasks[6];
extern ObjectLink g_warpPageLinks[52];
extern s32 g_pendingWarpEntry;
extern f32 g_warpPointRamp[4];
extern f32 g_warpDimRamp[4];
extern f32 g_warpLevelRampKind2[4];
extern f32 g_warpLevelRamp[4];
extern s32 g_warpCursorTable1[11][4];
extern s32 g_warpCursorTable2[11][4];
extern s32 g_warpCursorTable3[11][4];
extern s32 g_warpCursorTable4[11][4];
extern s32 g_warpCursorTable5[11][4];
extern s32 (*g_warpCursorTables[6])[4];
#ifndef VERSION_EU
extern WarpTextStyle g_warpTextStyle;
#endif
#ifdef VERSION_EU
extern f32 D_eu_0027FDAC;
extern f32 D_eu_0027FDB0;
#else
extern f32 g_warpCircleScale;
extern f32 g_warpInnerCircleScale;
#endif
extern s32 g_pendingWarpEntryAtEnd;
extern f32 g_warpLabelFontScale[];
extern char D_00276658[8];
extern char D_00276660[16];
extern char D_00276670[12];


// Slot 0 of the first boss: runs InitConeAgent, sets the stage key to 0x2D8 and its leash and range
// values, and a full turn (2 pi) as the near angle.
void InitWorld1Boss(World1Boss* self)
{
    InitConeAgent(self);
    self->stageKey = 0x2D8;
    self->leashHeight = 30000.0f;
    self->leashDistance = 30000000.0f;
    self->nearRange = 3000000.0f;
    self->farRange = 3000000.0f;
    self->farAngle = 0;
    self->nearAngle = 6.2831855f;
}

// The file's first read-only data, for func_001E89F0.
extern const f32 D_0024E600[4] = {3.40282347e+38f, 0.0f, 0.0f, 0.0f};

// Slot 16 of the first boss: resolves its links, makes itself the world's active follower, creates
// its state walker, sets 4 stages left with a flag table index each, and starts the cone agent.
void StartWorld1Boss(World1Boss* self)
{
    ResolveObjectLinks(self, 8, g_world1BossLinks);
    SetWorldActiveFollower(self->world, self);
    if (self->stateGraph != 0) {
        self->stateWalker = CreateStateWalker((StateGraph*)self->stateGraph, 0, 0x2D7, 0);
    }
    self->stagesLeft = 4;
    for (u32 i = 0; i < 4; i++) {
        self->stageFlagIndices[i] = TakeFlagTableIndex((FlagTable*)g_flagTable);
    }
    StartConeAgent(self);
}

ASM_FUNC(func_001E89F0);

// Called when the first world's boss enters a state: leaving state 1 sends its state walker to the
// stage key and gives each of its six key roots 0x2DE or 0x2DF by the stage (the nearest to the
// target gets 0x2DE) and sets the visits left (8 within 300 of its home, else 5); leaving 16 steps
// the stage key along 0x2D8 to 0x2DD with its slot.
void EnterWorld1BossState(World1Boss* self, s32 a, Animation* b)
{
    PlacedObject* key;
    s32 slot;

    switch (self->state) {
    case 1:
        if (self->stateWalker != 0) {
            SetStateWalkerTarget((StateWalker*)self->stateWalker, self->stageKey);
            void* near = ((TargetObjectFn*)self->desc)[102](self);
            if (near != 0) {
                key = FindNearestAgentKey(self, (u8*)&((PlacedObject*)near)->v140);
            } else {
                key = 0;
            }
            for (u32 i = 0; i < 6; i++) {
                PlacedObject* root = self->keyRoots[i];
                s32 pick;
                switch (self->stageKey) {
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
                    if (root == key) {
                        pick = 0x2DE;
                    }
                    break;
                }
                void* h = FindObjectHandle(root, -1);
                if (h != 0) {
                    SetStateWalkerTarget((StateWalker*)h, pick);
                }
            }
        }
        if (self->stageKey != 0x2DA) {
            u128 d = Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(self->v190));
            if (Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d))) < 300.0f) {
                self->visitsLeft = 8;
            } else {
                self->visitsLeft = 5;
            }
        } else {
            self->visitsLeft = 5;
        }
        self->nearestKeyRoot = 0;
        break;
    case 16:
        switch (self->stageKey) {
        case 0x2D8:
            self->stageKey = 0x2D9;
            slot = 0;
            break;
        case 0x2D9:
            self->stageKey = 0x2DA;
            slot = 1;
            break;
        case 0x2DA:
            self->stageKey = 0x2DB;
            slot = 2;
            break;
        case 0x2DB:
            self->stageKey = 0x2DC;
            slot = 3;
            break;
        }
        if (TestFlagTableBit((FlagTable*)g_flagTable, self->stageFlagIndices[slot]) == 0) {
            RaiseScatterLevelForObject((ScatterController*)g_scatterController, 0);
        }
        SetFlagTableBit((FlagTable*)g_flagTable, self->stageFlagIndices[slot]);
        self->stagesLeft = 3 - slot;
        DecrementGaugeCount(&g_gaugeBarElement);
        break;
    case 11:
        if (self->stateWalker != 0) {
            SetStateWalkerTarget((StateWalker*)self->stateWalker, 0x2DD);
        }
        for (u32 i = 0; i < 6; i++) {
            void* h = FindObjectHandle(self->keyRoots[i], -1);
            if (h != 0) {
                SetStateWalkerTarget((StateWalker*)h, 0x2DE);
            }
        }
        self->stagesLeft = 0;
        DecrementGaugeCount(&g_gaugeBarElement);
        MarkLevelDone(1);
        StartMemoryCardSave(&g_memoryCard);
        break;
    case 10:
    case 14:
        self->visitsLeft = 0;
        break;
    }
    EnterAgentState(self, a, b);
}

// Slot 89 of the first boss: with no visits left it clears the clip-10 deadline to the largest
// float; state 10 stays 10 while its state player exists (else 8), any other state is chosen by
// ChooseAgentState.
s32 ChooseWorld1BossState(World1Boss* self)
{
    s32 a1;
    if (self->visitsLeft <= 0) {
        self->clip10Deadline = 3.4028235e+38f;
    }
    a1 = self->state;
    if (a1 == 10) {
        a1 = (self->statePlayer == 0) ? 8 : 10;
    } else {
        a1 = ChooseAgentState(self);
    }
    return a1;
}

// Slot 0x16C of the first boss: not free while disabled, otherwise free while visits are left.
s32 IsWorld1BossFree(World1Boss* a0)
{
    if (a0->disabled != 0) return 0;
    return a0->visitsLeft != 0;
}

// Slot 93 of the first boss: true only in mode 0x2DB while the visit count is neither 0 nor 5.
s32 IsWorld1BossTargetInRange(World1Boss* a0)
{
    if (a0->stageKey != 0x2DB) return 0;
    {
        s32 v = a0->visitsLeft;
        if (v == 5 || v == 0) return 0;
        return 1;
    }
}

// Slot 97 of the first boss: outside mode 0x2DA it counts a visit down (not below 0), then steers
// along the path as every agent does.
void SteerWorld1BossAlongPath(World1Boss* a0)
{
    if (a0->stageKey != 0x2DA) {
        s32 v = a0->visitsLeft - 1;
        if (!(0 < v)) v = 0;
        a0->visitsLeft = v;
    }
    SteerAgentAlongPath(a0);
}


// Slot 96 of the first boss: in mode 0x2DA and state 12 while on the floor, when the nearest key
// has changed it counts a visit down and points that key's state walker at 0x2E0; then restarts the
// agent clip.
void RestartWorld1BossClip(World1Boss* self)
{
    if (self->stageKey == 0x2DA && self->state == 0xC && FindColliderFloorContact(self, 0, 0) != 0) {
        PlacedObject* s = FindNearestAgentKey(self, (u8*)&self->v140);
        if (s != self->nearestKeyRoot) {
            s32 n = self->visitsLeft - 1;
            if (!(0 < n)) n = 0;
            self->visitsLeft = n;
            if (n > 0) {
                void* p = FindObjectHandle(s, -1);
                if (p != 0) SetStateWalkerTarget((StateWalker*)p, 0x2E0);
                self->nearestKeyRoot = s;
            }
        }
    }
    RestartAgentClip(self);
}

// Slot 94 of the first boss: in state 4 the goal is its own point or the object at +0xC60, in state
// 8 the object its slot 98 returns, otherwise the agent's usual goal.
void UpdateWorld1BossGoal(World1Boss* self, s32 flag)
{
    Vec4U loc;
    switch (self->state) {
    case 4:
        if (self->disabled != 0) {
            SetAgentGoalPoint(self, &self->v190);
        } else {
            GetObjectWorldPosition((BaseObject*)self->goalObject, (Vec4*)&loc);
            SetAgentGoalPoint(self, (Vec4*)&loc);
        }
        break;
    case 8: {
        void* r = ((TargetObjectFn*)self->desc)[102](self);
        if (r != 0) SetAgentGoalPoint(self, &((PlacedObject*)r)->v140);
        break;
    }
    default:
        UpdateAgentGoal(self, flag);
        break;
    }
}

// Slot 90 of the first boss: in state 8 it turns toward the goal point, otherwise the agent's usual
// state update.
void UpdateWorld1BossState(World1Boss* self)
{
    if (self->state == 8) {
        FaceAgentTowardGoalPoint(self);
    } else {
        UpdateAgentState(self);
    }
}

// Shows the gauge bar element (slot 14) when the menus and fade are clear, otherwise hides it (slot
// 15).
void ShowElementWhenMenusClear(void)
{
    if (AreMenusAndFadeClear()) {
        g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    } else {
        g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
    }
}

// Slot 60 of the first boss: 0 when the probe belongs to one of its six key objects, else the
// agent's usual contact test.
s32 TestAgentMayContactExceptKeys(World1Boss* self, Collider* probe)
{
    PlacedObject* key = probe->root;
    u32 i = 0;
    s32 result;
    do {
        if (key == self->keyRoots[i]) {
            result = 0;
            goto done;
        }
        i++;
    } while (i < 6);
    result = TestAgentMayContact(self, probe);
done:
    return result;
}

// Initialises the global element stack that the pause and map screens push to and pop from.
void InitGlobalElementStack(void)
{
    InitElementStack((ElementStack*)g_elementStack);
}

// Clears the saved and pending states to -1, enters state 3 and leaves the stack holding only its
// empty base slot.
void InitElementStack(ElementStack* self)
{
    self->resumeState = -1;
    self->state = -1;
    SetElementStackState(self, 3);
    self->items[0] = 0;
    self->count = 1;
}

// Enters state 3, which resumes the saved state when there is one.
void ResumeElementStackState(void* self)
{
    SetElementStackState((ElementStack*)self, 3);
}

// Per-frame input update of the screen element stack (pad by the routing flags), reacting by state:
// 0 finishes an object sub-group when the memory card dialogue shows; 1 takes 0x800 (restore the
// saved card or reset progress and resume) and 0x100 (pause page 0x17); 3 takes 0x800 (pause page
// 0) and 0x100 (push the map screen list).
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
            StartObjectSubGroupFinish((ObjectSubGroup*)FindActiveObjectSubGroup());
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
            if ((v & 0x800) || (s2->connectionMode == 1 && 5.0f <= g_gameClock.time)) {
                SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0);
                s1 = obj->state;
                ClearPadPressedBits(s2, 0x800);
            } else if ((v = s2->flags) & 0x100) {
                WarpPageList* g2 = &g_mapScreenList;
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

// Pushes a screen element onto the element stack: pauses the stream voice when a second element
// goes on top of the first, tells the old top it is no longer on top (vt slot 3, 0), the new one
// that it is (slot 3, 1), then calls its slot 6.
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

// Pops the top screen element off the stack: tells it it is no longer on top (slot 3, 0), calls its
// slot 7, tells the new top it is on top, and resumes the stream voice once only the base element
// is left.
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

// Draws the screen elements; the main loop calls it once a frame after the world draw.
void DrawAllScreenElements(ElementStack* stack)
{
    DrawScreenElements();
}

// Lets each shown screen element queue its draw (slot 10); the main loop calls it before the world
// is drawn.
void QueueScreenElementDraws(ElementStack* stack)
{
    QueueEachScreenElementDraw();
}

// Pops every element above the base one, empties the saved state, sets the pad pattern player to
// state 3 and resets the screen elements.
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
    SetPadPatternState((PadPatternPlayer*)((PadRecord*)base)->patternPlayer, 3);
    ResetScreenElements();
}

// Switches the stack's state (a requested 3 becomes the resume state if set): leaving 1 hides the
// title and prompt and releases the pad select flag; the new state sets the time scale (0 for 5 and
// 7, else 1) and, for 0 the memory card display and fade, for 1 the title, prompt and select flag,
// for 3 the sound level, for 8 hides the counter captions.
void SetElementStackState(ElementStack* self, s32 state)
{
    if (state == 3) {
        s32 t = self->resumeState;
        if (t != -1) state = t;
    }
    if (self->state != state) {
        if (self->state != 0) {
            if (self->state == 1) {
                g_titleElement.vt->m15(&g_titleElement);
                g_promptElement.vt->m15(&g_promptElement);
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
        g_titleElement.vt->m14(&g_titleElement);
        g_promptElement.vt->m14(&g_promptElement);
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
        g_reserveCountCaption.vt->m15(&g_reserveCountCaption);
        g_collectedItemCaption.vt->m15(&g_collectedItemCaption);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
        break;
    }
    }
}

// Scales the game clock by x and, while the game time is running, eases the volume of the two
// channels toward 1.0 (factor 0.6) so sound follows the slow-down.
void ApplyStackTimeScale(ElementStack* stack, f32 x)
{
    if (0.0f < g_gameTime[0]) {
        float t = (1.0f - x) * 0.6f + x;
        SetVolumeChannelFactor(4, 1, t);
        SetVolumeChannelFactor(4, 0, t);
    }
    SetGameClockScale(x);
}

// True when nothing is covering the game: no screen fade, no pad-select hold, the pause menu and
// map list closed and the other screen mode not 1, 2 or 4.
s32 AreMenusAndFadeClear(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (IsPadSelectFlagHeld((World*)g_currentWorld) != 0) goto fail;
    if (g_pauseMenuElement.open != 0 && g_pauseMenuElement.page != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode != 0) goto fail;
    if (g_displayMode == 2) goto fail;
    if (g_displayMode == 1) goto fail;
    if (g_displayMode != 4) goto ok;
fail:
    return 0;
ok:
    return 1;
}

// True when no screen fade is on and neither the pause menu nor the map list is open or in a mode.
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

// True when the arc may be drawn: no screen fade, pause menu and map list closed with no mode, and
// the other screen mode neither 1 nor 4.
s32 IsArcDrawAllowed(void)
{
    s32 m;
    if (g_screenFade.mode != 0) goto fail;
    if (g_pauseMenuElement.open != 0) goto fail;
    if (g_pauseMenuElement.mode != 0) goto fail;
    if (g_mapScreenList.open != 0) goto fail;
    if (g_mapScreenList.mode != 0) goto fail;
    m = g_displayMode;
    if (m == 4) goto fail;
    if (m != 1) goto ok;
fail:
    return 0;
ok:
    return 1;
}

// The same test as AreMenusClosed, a separate copy used beside the arc functions.
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

// Runs a little of a background CRC-32 check of the code in main memory each frame: it takes 32
// words at a time from the cursor (restarting from address 0x100004 when a pass is finished, unless
// the check has already failed), and when a pass ends with a non-zero result it sets D_00275C34 to
// 1.
void StepMemoryChecksum(void) {
    if (D_00275C34 == 0) {
        if (g_memoryChecksumRemaining == 0) {
            g_memoryChecksumCursor = (u32*)0x100004;
            g_memoryChecksumRemaining = (s32)g_memoryChecksumEnd;
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

// Updates the world's lists that run on the frame delta: the memory checksum step, the active
// collider's control method (method 0x49, with the pad if the routing flags allow it), the world's
// object lists, the object trees, animation players and level ramps, then the delayed messages, the
// sound emitters and the queued calls.
void UpdateWorldDeltaLists(World* self, f32 dt)
{
    StepMemoryChecksum();
    SwitchedCollider* h = GetActiveSwitchedCollider();
    if (h != 0) {
        const SwitchedColliderDescriptor* vt = h->desc05();
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
        BeginByteWalk::Of(&it, (ObjectList*)&self->list60);
        for (u8* n = NextByte::Of(&it); n != 0; n = NextByte::Of(&it)) {
            UpdateObjectTree(n, dt);
        }
        EndByteWalk::Of(&it);
    }
    {
        ListFrame it;
        BeginByteWalk::Of(&it, (ObjectList*)&self->animationPlayers);
        for (u8* n = NextByte::Of(&it); n != 0; n = NextByte::Of(&it)) {
            UpdateAnimationPlayer((AnimationPlayer*)n, dt);
        }
        EndByteWalk::Of(&it);
    }
    {
        ListFrame it;
        BeginByteWalk::Of(&it, (ObjectList*)&self->worldClockNodes);
        for (u8* n = NextByte::Of(&it); n != 0; n = NextByte::Of(&it)) {
            StepObjectLevelRamp((WorldObjectNode*)n, dt);
        }
        EndByteWalk::Of(&it);
    }
    DispatchDelayedMessages(self);
    UpdateSoundEmitters();
    RunQueuedCalls(self);
}

// For every object of the world's list and every part in its list, calls the part's update (slot
// 17) unless flag bit 53 is set, then clears that bit.
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
                        ((ColliderDescriptor*)s0->desc)->m44(s0);
                    }
                    s0->flags538 &= ~bit;
                    s0 = (Collider*)s0->link2E4.next;
                } while (s0 != 0);
            }
            s1 = (Collider*)s1->link414.next;
        } while (s1 != 0);
    }
}

// Updates the world's lists that run on the step clock (it does nothing when dt is 0): the object
// trees, the animation players and the level ramps of their lists, then the first list's objects'
// update method (with dt), and then the queued calls.
void UpdateWorldStepLists(World* self, f32 dt)
{
    if (dt == 0.0f) return;
    ListFrame it;
    BeginNodeWalk::Of(&it, &self->list78);
    for (ListedObject* obj = NextNode::Of(&it); obj; obj = NextNode::Of(&it)) UpdateObjectTree(obj, dt);
    EndNodeWalk::Of(&it);
    BeginNodeWalk::Of(&it, (ObjectList*)&self->listedAnimationPlayers);
    for (ListedObject* obj = NextNode::Of(&it); obj; obj = NextNode::Of(&it)) UpdateAnimationPlayer((AnimationPlayer*)obj, dt);
    EndNodeWalk::Of(&it);
    BeginNodeWalk::Of(&it, (ObjectList*)&self->stepClockNodes);
    for (ListedObject* obj = NextNode::Of(&it); obj; obj = NextNode::Of(&it)) StepObjectLevelRamp((WorldObjectNode*)obj, dt);
    EndNodeWalk::Of(&it);
    BeginNodeWalk::Of(&it, &self->list78);
    for (ListedObject* obj = NextNode::Of(&it); obj; obj = NextNode::Of(&it)) obj->vtbl->update(obj, 0, dt);
    EndNodeWalk::Of(&it);
    RunQueuedCalls(self);
}

// Eases the world's value toward its target over x, with one ramp profile when moving down and
// another when moving up.
void StepWorldValueTowardTarget(World* self, f32 x)
{
    World* o = self;
    f32 a = o->value;
    f32 b = o->valueTarget;
    if (b < a) {
        o->value = ApproachValueWithRamp((RampProfile*)g_worldValueFallRamp, 0, a, b, x);
    } else if (a < b) {
        o->value = ApproachValueWithRamp((RampProfile*)g_worldValueRiseRamp, 0, a, b, x);
    }
}

// Per-frame update of the world: step-clock lists first, then, if dt is not 0, the delta lists,
// parts, contacts, collider groups, each actor's update, the second contact pass, at-rest counting,
// each actor's post method, delayed script calls, queued calls and animators. Always: notifies the
// active follower, updates the camera and moves the world value.
void UpdateWorld(World* self, f32 unused1)
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
        for (UpdatedObject* obj; (obj = NextActor::Of(&it)) != 0;) {
            if (obj->vtable->update != 0) {
                obj->vtable->update(obj, clock->dt);
            }
        }
        g_activeListFrames = it.prev;
        UpdateWorldContacts(self, 1);
        ProcessColliderGroups(self, 6, g_gameClock.dt);
        BeginActorWalk::Of(&it, &self->list60);
        for (UpdatedObject* obj; (obj = NextActor::Of(&it)) != 0;) {
            if (obj->tries < 2) {
                if (IsObjectTreeAtRest(obj) != 0) {
                    obj->tries++;
                } else {
                    ClearRootTries((PlacedObject*)obj);
                }
            }
        }
        g_activeListFrames = it.prev;
        BeginActorWalk::Of(&it, &self->list6C);
        for (UpdatedObject* obj; (obj = NextActor::Of(&it)) != 0;) {
            obj->vtable->post(obj);
            if (obj->flags & 0x8000000000000000ULL) {
                UpdateTouchingParts((Collider*)obj);
            }
        }
        g_activeListFrames = it.prev;
        RunDueDelayedScriptCalls(self, g_gameClock.dt);
        RunQueuedCalls(self);
        StepAnimators(g_gameClock.dt);
    }
    NotifyWorldActiveFollower(self);
    BeginActorWalk::Of(&it, &self->list1B7C);
    for (UpdatedObject* obj; (obj = NextActor::Of(&it)) != 0;) {
        ReleaseWorldListEntry(obj);
    }
    g_activeListFrames = it.prev;
    UpdateCamera(g_camera, 1, g_gameClock.dt);
    StepWorldValueTowardTarget(self, g_gameClock.step);
}

// Brings an angle into -pi..pi (unchanged when already inside).
f32 WrapAngle(f32 a)
{
    f32 r = a;
    if (a < -3.1415927f || a > 3.1415927f) {
        r = WrapModulo(a + 3.1415927f, 6.2831855f) - 3.1415927f;
    }
    return r;
}

// Limits a to -b..b.
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

// Moves a value x toward the target y for z seconds under a ramp profile: it runs at maxSpeed and
// slows to endSpeed over rampTime near the target. Gives the new value, and the speed it ends with
// (signed toward the target) in out if given.
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

// The same as ApproachValueWithRamp but with the rate of change of the velocity also limited by the
// profile's maxAccel (when positive): if the new velocity would differ from the old velocity b by
// more than maxAccel times d, it is clamped and the value is moved with the constant acceleration
// instead. The new velocity goes to out.
f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, void* self, f32* out)
{
    RampProfile* o = (RampProfile*)self;
    f32 tmp;
    f32 res = ApproachValueWithRamp(a, c, d, (RampProfile*)self, &tmp);
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

// ApproachValueWithRamp for an angle: steps along the wrapped difference to the target and wraps
// the result to -pi..pi.
f32 ApproachAngleWithRamp(f32 a, f32 b, f32 c, void* self, f32* out)
{
    f32 t = WrapAngle(b - a);
    f32 r = ApproachValueWithRamp(0.0f, t, c, (RampProfile*)self, out);
    return WrapAngle(a + r);
}

// ApproachValueClampingVelocity for an angle: the step is taken along the wrapped difference to the
// target and the result is wrapped to -pi..pi.
f32 ApproachAngleClampingVelocity(f32 f12, f32 f13, f32 f14, f32 f15, void* self, f32* a1)
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
u128 ApproachPointWithRamp(u128 from, u128 to, f32 limit, RampProfile* ramp, Vec4* vel)
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
        *vel = g_zeroVector;
    }
    return to;
}


// Turns the rotation from toward to under a ramp profile for limit seconds: the remaining rotation
// is taken as an axis and angle, ApproachValueWithRamp gives how far it turns this step, and the
// new rotation (or the target itself when it arrives) goes to outRot and the angular velocity along
// the axis to outSpin; either may be null.
void ApproachRotationWithRamp(Mat3* from, Mat3* to, RampProfile* ramp, Mat3* outRot, Vec4* outSpin, f32 limit)
{
    Mat3 rel;
    Mat3 built;
    Vec4 axis;
    f32 angle;
    f32 step;
    MultiplyMatrices3x3(from, to, &rel);
    MatrixToAxisAngle(&rel, &angle, (Vec4*)&axis);
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

// A random integer from a to b inclusive (a when they are equal).
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

// A random float between a and b (a when they are equal).
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

// A random number with a normal distribution around mean with the given deviation (the polar method
// of Box and Muller: a random point in the unit circle turned into a Gaussian), clamped to mean
// plus or minus limit when limit is not 0.
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

// True when |a - b| is below tolerance relative to the larger of 1 and |a|.
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 tolerance)
{
    f32 scale = 1.0f;
    scale = scale >? __builtin_fabsf(a);
    return __builtin_fabsf(a - b) / scale < tolerance;
}

// Real roots of a x^2 + b x + c written to roots; returns 0 for a negative discriminant, 1 when it
// is nearly zero (< 0.0001) and 2 otherwise.
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

// Rewrites quadratic coefficients (x, y, z) for the parameter change t -> s t + u, giving the
// coefficients of the same curve in the new parameter.
void RemapQuadraticParameter(Vec3* in, f32 s, f32 t, Vec3* out)
{
    out->z = in->z * s * s;
    out->y = (in->z + in->z) * s * t + in->y * s;
    out->x = (in->z * t * t + in->y * t) + in->x;
}

// Computes sine and cosine of an angle in radians: the angle is reduced to a half turn around zero
// (flipping its sign for odd half turns), the sine comes from a degree-9 polynomial and the cosine
// from the square root of 1 - sine squared, with the sign of the half turn.
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

// The double version of TruncateFloat: rounds toward zero by clearing the fraction bits, adding 1.0
// when they were all ones.
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

// Rounds a float toward zero by clearing the fraction bits below the binary point (0 for |x| < 1);
// when the discarded bits were all ones it adds 1.0 to the result, as the original's runtime did.
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

// x modulo y with the result always in 0..y (a negative remainder gets y added).
f32 WrapModulo(f32 x, f32 y)
{
    f32 r = FloatRemainder(x, y);
    if (r < 0.0f) {
        r += y;
    }
    return r;
}

// Fits c0 + c1 t + c2 t^2 through the value x at t = 0, y at t = 1 and w at t = z and stores the
// three coefficients.
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

// True when x is strictly between the range's lo and hi.
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

// True when x lies inside any of the count ranges in spans.
s32 IsInsideAnyRange(s32 count, ValueRange* spans, f32 x)
{
    for (s32 i = 0; i < count; i++) {
        if (IsInsideRange(&spans[i], x)) {
            return 1;
        }
    }
    return 0;
}

// x limited to the range's lo..hi.
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

// qsort-style comparison of the floats two pointers refer to: 1, -1 or 0.
s32 CompareFloats(f32* a, f32* b)
{
    f32 x = *a;
    f32 y = *b;
    if (y < x) return 1;
    if (x < y) return -1;
    return 0;
}

// Does nothing; its one caller passes it the address of a 16-byte local of its frame.
void IgnoreStackLocal(Vec4* unused0)
{
}

// A sample FindLocalMinimum keeps: an argument and the function's value there.
struct MinimumSample {
    f32 x;
    f32 y;
};

typedef f32 (*MinimumFn)(void* ctx, f32 x);

// Finds a local minimum of fn(ctx, x) near x (outputs the position and the value in outX and outY):
// it brackets a minimum between lo and hi starting with step by shifting five samples toward the
// lower side, then narrows the bracket by ten bisection steps.
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

// Start-up of the beat-press collider: runs InitSwitchedCollider, then sets its timing window by
// blending between two constants with a polynomial of the current entry's dt, clamped to the unit
// range.
void InitWorld3BeatPressCollider(World3BeatPressCollider* self)
{
    InitSwitchedCollider(self);
    f32 t = g_currentEntry->dt;
    f32 x = g_beatPressTimingCurve[0] + t * (g_beatPressTimingCurve[1] + t * g_beatPressTimingCurve[2]);
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
    self->timingWindow = (1.0f - c) * g_beatPressTimingWindowRange[0] + c * g_beatPressTimingWindowRange[1];
}

// Slot 10 of the beat-press collider: loads the collider and resolves its link.
void LoadWorld3BeatPressCollider(World3BeatPressCollider* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 1, g_world3BeatPressLoadLinks);
}

// Copies the player's 0x580 block and the word at +0x604 into the beat-press collider.
void CopyPlayerAttachBlock(World3BeatPressCollider* a0)
{
    a0->blk580 = g_player->blk580;
    a0->f604 = g_player->f604;
}

// Slot 16 of the beat-press collider: starts the placed object, resolves its links, creates its
// state walker at 0x4CA and queues CopyPlayerAttachBlock for itself.
void StartWorld3BeatPressCollider(World3BeatPressCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 4, g_world3BeatPressStartLinks);
    self->walker = CreateStateWalker((StateGraph*)self->walkerGraph, self, 0x4CA, 1);
    AppendQueuedCall(self->world, (void*)CopyPlayerAttachBlock, self, 0, 0);
}

// Slot 72 of the beat-press collider: on activation sends its walker to 0x4CB and links it with the
// tempo agent of the world; on deactivation back to 0x4CA and sets the player's pulse fade duration
// to 2.0.
void HandleWorld3BeatPressColliderActivation(World3BeatPressCollider* self, void* p)
{
    HandleSwitchedColliderActivation(self, p);
    World3Boss* r = (World3Boss*)FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
    if (p != 0) {
        SetStateWalkerTarget((StateWalker*)self->walker, 0x4CB);
        r->beatPressCollider = self;
        self->tempoAgent = r;
    } else {
        SetStateWalkerTarget((StateWalker*)self->walker, 0x4CA);
        g_player->pulseFadeDuration = 2.0f;
    }
}


// Callback of a beat-press request: turns the player to face the collider (heading is the atan2 of
// the direction to it plus pi) and sets the player to state 4 with 0x2B.
void ContinueWorld3BeatPressColliderRequest(PlacedObject* from, Player* self)
{
    Vec4 dir;
    Vu0::Q(dir) = Vu0::MulXSum(Vu0::Q(from->m110.r[0]), Vu0::Scalar(-g_beatPressRequestSideSpeed), Vu0::Q(from->m110.r[2]), Vu0::ScalarAt(g_beatPressRequestUpSpeed));
    self->desc02()->m20(self, &dir);
    self->heading = WrapAngle(ArctangentOfRatio(dir.y, dir.x) + 3.1415927f);
    TurnColliderTowardHeading(self);
    SetPlayerState(self, 4, 0x2B);
}

// Judges the pad against the beat-press timeline each frame. While judging, a face or d-pad press
// (flags 0xF0, direction 0 to 3) is a hit when the next entry has that direction and its beat is
// within half the timing window of the boss's bar position (4 beats a bar), else sound 0x7B plays.
// Also places player and collider at the frame anchor and handles missed entries.
void JudgeWorld3BeatPressInput(World3BeatPressCollider* self, PadRecord* in, f32 dt)
{
    if (self->frameAnchor != 0 && g_player != 0) {
        Vec4U pos;
        Mat3U mat;
        GetObjectWorldPosition((BaseObject*)self->frameAnchor, (Vec4*)&pos);
        GetObjectWorldRotation((BaseObject*)self->frameAnchor, (Mat3*)&mat);
        g_player->desc02()->m1D(g_player, (Vec4*)&pos);
        g_player->desc02()->m1E(g_player, (Mat3*)&mat);
        self->desc02()->m1D(self, (Vec4*)&pos);
        self->desc02()->m1E(self, (Mat3*)&mat);
    }
    if (self->judging != 0) {
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
            if (self->nextEntry < self->entryCount) {
                BeatPressEntry* e = &self->entries[self->nextEntry];
                if (e->dir == dir) {
                    World3Boss* g = ((World3Boss*)self->tempoAgent);
                    at = (f32)g->bar * 4.0f + g->barPosition;
                    if (__builtin_fabsf(e->t - at) < self->timingWindow * 0.5f) {
                        ok = 1;
                    }
                }
            }
            if (ok) {
                self->pressDirection = dir;
                self->pressBeat = at;
            } else {
                StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
    }
    if (self->nextEntry < self->entryCount) {
        BeatPressEntry* e = &self->entries[self->nextEntry];
        World3Boss* g = ((World3Boss*)self->tempoAgent);
        f32 at = (f32)g->bar * 4.0f + g->barPosition;
        f32 win = self->timingWindow;
        if (self->pressDirection == e->dir && __builtin_fabsf(e->t - self->pressBeat) < win * 0.5f) {
            SetStateWalkerTarget((StateWalker*)self->walker, g_world3BeatPressWalkerTargets[self->pressDirection]);
            StartSoundEffect(g_world3BeatPressSoundIds[self->pressDirection], 0, 0, 0, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0, 0);
        } else {
            if (!(at - e->t > win * 0.5f)) {
                return;
            }
            StartSoundEffect(0x51, 0, 0, 0, 30000.0f, 20000.0f, 1.5f, 0.3f, 0.0f, 0, 0);
            if (HasSpareCount() == 0 && self->desc05()->m4B(self, 0) == 0) {
                OwnerMessage msg;
                World3Boss* o;
                ActivateSwitchedCollider(g_player);
                InitOwnerMessage(&msg, 0, self);
                msg.fn = (void (*)(void))ContinueWorld3BeatPressColliderRequest;
                g_player->desc05()->m4C(g_player, &msg);
                o = (World3Boss*)FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
                EndHeldWorld3Timeline(o);
                o->clip10Deadline = g_gameTime[0];
                SetCachedVoiceParam(2, 1);
                goto next;
            }
            if (self->desc05()->m4B(self, 0) == 0) {
                World3Timeline* l;
                self->desc05()->m50(self);
                Player* gl = g_player;
                self->runEnded = 1;
                gl->pulseActive = 1;
                f32 v = g_gameTime[0];
                gl->pulseFadeStart = v;
                gl->pulseStartTime = v;
                l = ((World3Boss*)self->tempoAgent)->heldTimeline;
                gl->pulseFadeDuration = 2.0f;
                if (l != 0) {
                    s32 j = l->index;
                    while (j < l->entryCount) {
                        TimelineEntry* p = &((TimelineEntry*)l->buffer)[j];
                        if (p->kind == 3) break;
                        j++;
                    }
                    if (j < l->entryCount) {
                        TimelineEntry* it = &((TimelineEntry*)l->buffer)[j];
                        World3Boss* gg = ((World3Boss*)self->tempoAgent);
                        g_player->pulseFadeDuration = ((f32)it->step * 4.0f + it->substep - ((f32)gg->bar * 4.0f + gg->barPosition)) * gg->beatLength;
                    }
                }
            }
        }
        if (e->dir == 3) {
            ActivateSwitchedCollider(g_player);
            BindEntryQueueToObject(self->entryQueue, g_player);
            self->entryQueue = 0;
        }
    next:
        self->nextEntry++;
        if (self->nextEntry == self->entryCount) {
            self->nextEntry = 0;
            self->entryCount = 0;
        }
    }
}

// Slot 75 of the beat-press collider: a request is blocked while a button code flag or the pad-
// select hold is set, or after its run has ended.
s32 IsWorld3BeatPressColliderRequestBlocked(World3BeatPressCollider* self)
{
    if (g_buttonCodeFlags & 1) return 1;
    if (IsPadSelectFlagHeld(self->world) == 0) return self->runEnded != 0;
    return 1;
}

// Appends an eight-byte (time, direction) entry to the collider's list of beats that
// JudgeWorld3BeatPressInput works through.
void AppendWorld3BeatPressEntry(World3BeatPressCollider* list, const U64P* src)
{
    s32 n = list->entryCount;
    list->entryCount = n + 1;
    U64P* dst = (U64P*)&list->entries[n];
    *dst = *src;
}

// Slot 0x140 of the beat-press collider: takes no request (returns 0).
s32 AcceptWorld3BeatPressColliderRequest(void)
{
    return 0;
}

// What GetWorld3BeatPressColliderPositionAt reads of its f67C: an object to place at a time (+0x18), a
// point in its frame (+0x40) and the rotation func_001EBDD0 turns the object's by (+0x50).
struct FramePoint_001EBD10 {
    u8 pad0[0x18];
    void* object;           // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec4 point;            // 0x40
    Mat3 m50;              // 0x50
};

void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin, f32 t);

// Position and velocity of the collider at time t: the plain placed-object answer, or, when it is
// anchored to a point on another object, that point's position and velocity in the other object's
// frame at t.
void GetWorld3BeatPressColliderPositionAt(World3BeatPressCollider* self, f32 t, Vec4* pos, Vec4* vel)
{
    if (self->frameAnchor == 0) {
        GetPlacedObjectPositionAt(self, t, pos, vel);
        return;
    }
    Vec4 p;
    Mat3 rot;
    Vec4 v;
    Vec4 w;
    ComputeObjectFrameAtTime((PlacedObject*)(((FramePoint_001EBD10*)self->frameAnchor)->object), 0, &p, &rot, &v, &w, t);
    Vu0::Q(*pos) = Vu0::Add(Vu0::Q(p), Vu0::Rotate(rot, Vu0::Q(((FramePoint_001EBD10*)self->frameAnchor)->point)));
    Vu0::Q(*vel) = Vu0::Add(Vu0::Q(v), Vu0::Cross(Vu0::Q(w), Vu0::Q(((FramePoint_001EBD10*)self->frameAnchor)->point)));
}


// Gives the press collider's rotation and spin at t seconds from now: those of a placed object when
// it has no frame anchor, otherwise the anchor object's frame at that time composed with the
// anchor's own rotation, and the object's spin.
void GetWorld3BeatPressColliderRotationAt(World3BeatPressCollider* self, f32 t, Mat3* rot, Vec4* spin)
{
    if (self->frameAnchor == 0) {
        GetPlacedObjectRotationAt(self, t, rot, spin);
        return;
    }
    Mat3 m;
    Vec4 w;
    ComputeObjectFrameAtTime((PlacedObject*)(((FramePoint_001EBD10*)self->frameAnchor)->object), 0, 0, &m, 0, &w, t);
    FramePoint_001EBD10* f = (FramePoint_001EBD10*)self->frameAnchor;
    MulRotationRowsIndexed(rot, m, f->m50);
    *spin = w;
}

// Slot 0 of the third boss: runs InitAgent, starts at 60 beats a minute with 8 beats per span,
// allocates the 0x400-byte tempo entry array and stops the staged bank voice.
void InitWorld3Boss(World3Boss* self)
{
    InitAgent(self);
    self->tempo = 0x3C;
    self->newBeatLength = 1.0f;
    self->spanSeconds = 8.0f;
    self->bar = 0;
    self->beatInBar = -1;
    self->beat = -1;
    self->spanBeats = 8;
    self->players = (TempoPlayerEntry*)AllocateFrontMemory(0x400);
    self->world->f2358 = 1;
    StopStagedBankVoice();
    g_world3BossVoiceState = 2;
    g_world3BossPendingVoice = 0;
}

s32 ResolveAgentClip(Agent* self, s32 id);
void LoadAgent(Agent* self, void* reader);
// Slot 10 of the third boss: loads the agent, then resolves its four clips from the table of clip
// ids.
void LoadWorld3Boss(World3Boss* self, void* reader)
{
    LoadAgent(self, reader);
    for (s32 i = 0; i < 4; i++) {
        self->clips[i] = ResolveAgentClip(self, g_world3BossClipIds[i]);
    }
}

// Starts the third world's boss agent: becomes the world's active follower, resolves its links,
// creates its state walker (with itself as listener) and copies the table of nine keyed object
// references, finding each object by its id in the world.
void StartWorld3Boss(World3Boss* self)
{
    StartAgent(self);
    SetWorldActiveFollower(self->world, self);
    ResolveObjectLinks(self, 5, g_world3BossStartLinks);
    void* r = CreateStateWalker((StateGraph*)self->walkerGraph, 0, -1, 0);
    self->walker = r;
    AddStateWalkerListener((StateWalker*)r, (PlacedObject**)self);
    self->keyedCount = 9;
    self->keyedObjects = CopyToFrontMemory(0x6C, g_world3BossObjectRefs);
    s32 i = 0;
    if (self->keyedCount > 0) {
        s32 off = 0;
        do {
            // address arithmetic over a variable index
            TempoObjectRef* e = (TempoObjectRef*)((u8*)self->keyedObjects + off);
            e->obj = FindFirstObjectById(self->world, 1, e->id, self);
            i++;
            off += 12;
        } while (i < self->keyedCount);
    }
}


void UnregisterWorld3Boss(World3Boss* self)
{
    UnregisterSwitchedCollider(self);
}

void RegisterWorld3Boss(World3Boss* self)
{
    RegisterSwitchedCollider(self);
}

// Slot 93 of the third boss: decided by the state its walker is in: the first group needs the
// pending clip, the second group is true on phase 2 of the beat gate (phase 0 moves it to 1).
s32 IsWorld3BossTargetInRange(World3Boss* self)
{
    s32 r[4];
    GetStateWalkerCurrentKey((StateWalker*)self->walker, r);
    switch (r[0]) {
    case 0x4ED:
    case 0x4F0:
    case 0x4F3:
    case 0x4F6:
        if (self->pendingClip == 0) goto zero;
    yes:
        return 1;
    case 0x4EE:
    case 0x4F1:
    case 0x4F4:
    case 0x4F7:
        if (self->beatGate == 1) goto zero;
        if (self->beatGate < 2) {
            if (self->beatGate == 0) goto set;
            return 0;
        }
        if (self->beatGate == 2) goto yes;
        return 0;
    set:
        self->beatGate = 1;
    }
zero:
    return 0;
}

// Slot 0x16C of the third boss: always 1.
s32 IsWorld3BossFree(void)
{
    return 1;
}

typedef int Quadword128 __attribute__((mode(TI)));
void* StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(u128* out, u128 v);
extern f32 g_ringSevenPoints[14];

// k times the quadword at p, into dst (the quadword helpers' product).
static inline void StoreScaledQuadword(void* dst, f32 k, void* p)
{
    Quadword128 t;
    StoreFloatAsQuadword((u128*)&t, k);
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword((u128*)&u, p);
    StoreQuadword((u128*)dst, ScaleQuadword(tv, u));
}

// The tempo agent's ring: the block's defaults are built once, as a function-local static with
// a brace initialiser (include/ring_params.h), and copied for each draw, where rows 1 and 2 are
// scaled by the agent's level. DrawWorld3Boss queues it as a deferred request's callback, the
// agent the request's argument.
void DrawWorld3BossRing(DeferredRequest* request)
{
    World3Boss* agent = (World3Boss*)request->arg;
    static RingParams defaults = {
        1, 10.0f, 0.25f,
        {
            { { 0.0f, 0.0f, 0.0f }, 0.0f, 100.0f, RingColor(0x80FFFFFF) },
            { { 0.0f, 0.5f, 0.0f }, 0.0f, 50.0f, RingColor(0x80FFFFFF) },
            { { 500.0f, 1.0f, 0.0f }, 1.0f, -100.0f, RingColor(0x80FFFFFF) },
        },
    };
    if (agent->rampNode != 0) {
        RingParams params = defaults;
        params.textures[0] = 0;
        params.textures[1] = FindAnimRecord(0x15D);
        f32 level = agent->rampNode->level;
        StoreScaledQuadword(&params.rows[1].shape, level * level, &params.rows[1].shape);
        StoreScaledQuadword(&params.rows[2].shape, agent->rampNode->level, &params.rows[2].shape);
        DrawAngleSortedRing((Vec4*)&agent->v140, 7, (Point2*)g_ringSevenPoints, agent->keyedCount, (RingAnchor*)agent->keyedObjects, &params, request);
    }
}

// The file's data from here on follows the static's guard (D_00275DB4) in retail's .data.
// size: s32 state compared/assigned in 001EC000
s32 g_world3BossVoiceState = 0;
INCLUDE_DATA(D_00275DBC);
s32 g_unpackBytesPerElement[16] = { 4, 2, 1, -1, 8, 4, 2, -1, 12, 6, 3, -1, 16, 8, 4, 2 };
s32 g_stateResetObjectLinks[92] = { 2, 0x2EB, 0x2DC };
// word read whole / address only, 4 bytes to next label
ScreenFade g_screenFade = { 0 };
f32 g_scaleTargetSmall = 0.5f;
// Globals defined from C.
s32 g_warpSlotKindMasks[6] = { 0, 2, 4, 4, 4, 0 };
ObjectLink g_warpPageLinks[52] = {
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
s32 g_pendingWarpEntry = -1;
f32 g_warpPointRamp[4] = { 600.0f, 0.0f, 0.25f, 0.0f };
f32 g_warpDimRamp[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 g_warpLevelRampKind2[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 g_warpLevelRamp[4] = { 1.0f, 0.0f, 0.200000003f, 0.0f };
s32 g_warpCursorTable1[11][4] = {
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
s32 g_warpCursorTable2[11][4] = {
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
s32 g_warpCursorTable3[11][4] = {
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
s32 g_warpCursorTable4[11][4] = {
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
s32 g_warpCursorTable5[11][4] = {
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
s32 (*g_warpCursorTables[6])[4] = { 0, (s32(*)[4])g_warpCursorTable1, (s32(*)[4])g_warpCursorTable2, (s32(*)[4])g_warpCursorTable3, (s32(*)[4])g_warpCursorTable4, (s32(*)[4])g_warpCursorTable5 };
#ifndef VERSION_EU
// PAL has no style here (its func_001F1960 draws without one): its static initialiser only
// sets D_00276650.
WarpTextStyle g_warpTextStyle(2, 1);
#endif
INCLUDE_DATA(D_0027663C);
#ifdef VERSION_EU
// PAL's own addresses for these two, which the tools do not pair with US's (VERSION_NAME).
f32 D_eu_0027FDAC = 24.0f;
f32 D_eu_0027FDB0 = D_eu_0027FDAC * 0.75f;
#else
f32 g_warpCircleScale = 24.0f;
f32 g_warpInnerCircleScale = g_warpCircleScale * 0.75f;
#endif
s32 g_pendingWarpEntryAtEnd = 0;
extern f32 g_warpLabelFontScale[];
char D_00276658[8] = "jojo";
char D_00276660[16] = "08/24/02 22:06";
char D_00276670[12] = "0824.2206";

// Slot 0xA0 of the third boss: in state 16 it builds its own placed-object transform with +0x44
// cleared and applies that, otherwise it applies the one given.
void ApplyWorld3BossTransform(World3Boss* self, void* s, void* c)
{
    ScaledTransform tmp;
    void* out = c;
    if (self->state == 16) {
        BuildPlacedObjectTransform(self, (Quad16*)c, &tmp);
        *(s32*)&tmp.innerFade = 0;
        out = &tmp;
    }
    ApplyPlacedObjectTransform(self, (Camera*)s, (ScaledTransform*)out);
}

#include "deferred_request.h"
void DrawAgent(Agent* self, void* unused1, void* unused2);
void DrawWorld3BossRing(DeferredRequest* self);

// Slot 37 of the third boss: draws the agent, and in state 16 also queues a deferred request (group
// 0xD, sorted by its distance along the camera's view) that draws the boss's ring.
void DrawWorld3Boss(World3Boss* self, Camera* cam, void* arg2)
{
    DrawAgent(self, cam, arg2);
    if (self->state == 16) {
        DeferredRequest r;
        FillMemory(&r, 0, 0x80);
        f32 d = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->position)), Vu0::Q(cam->rotation)));
        r.group = 0xD;
        r.f04 = d;
        r.arg = self;
        r.callback = (void*)DrawWorld3BossRing;
        QueueDeferredRequest(&r);
    }
}

// Slot 91 of the third boss: runs LeaveAgentState; leaving state 14 or 16 clears the beat gate, and
// leaving 16 also moves the walker from 0x4EE, 0x4F1 or 0x4F4 on to the next state.
void LeaveWorld3BossState(World3Boss* self, s32 arg)
{
    s32 out;
    s32 sel;
    LeaveAgentState(self, arg);
    s32 st = self->state;
    if (st != 0xE) {
        if (st != 0x10) {
            return;
        }
        self->beatGate = 0;
        GetStateWalkerCurrentKey((StateWalker*)(self->walker), &out);
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
        SetStateWalkerTarget((StateWalker*)(self->walker), sel);
    } else {
        self->beatGate = 0;
    }
}

// Called by a script built-in: lowers the gauge bar's count, sets the boss's hits left to 2 and
// snaps the bar's fill to its target.
void DecrementWorld3BossGauge(World3Boss* self)
{
    GaugeBar* g = &g_gaugeBarElement;
    DecrementGaugeCount((GaugeBar*)&g_gaugeBarElement);
    self->hitsLeft = 2;
    g->fill = g->fillTarget;
}

// Called when the third world's boss enters a state: on leaving state 0xE it hands the pending clip
// on for some walker keys, on leaving 0x10 or 0xB it decrements the gauge count (0xB also marks
// level 3 done and saves the memory card); then the base agent state is entered and, for state 14
// and states 2 and 13, the state player's start time and speed are set from the walker key.
void EnterWorld3BossState(World3Boss* self, s32 a, s32 b)
{
    s32 r[3];
    switch (self->state) {
    case 0xE:
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &r[0]);
        switch (r[0]) {
        case 0x4ED:
        case 0x4F0:
        case 0x4F3:
        case 0x4F6:
            b = self->pendingClip;
            self->pendingClip = 0;
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
    EnterAgentState(self, a, (Animation*)b);
    switch (self->state) {
    case 14: {
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &r[1]);
        f32 q;
        switch (r[1]) {
        case 0x4EE:
            q = 0.083333336f;
            ((AnimationPlayer*)self->statePlayer)->speed = ((AnimationPlayer*)self->statePlayer)->anim->length / (self->beatLength + self->beatLength);
            break;
        case 0x4F1:
        case 0x4F4:
        case 0x4F7:
            q = 0.083333336f;
            ((AnimationPlayer*)self->statePlayer)->speed = ((AnimationPlayer*)self->statePlayer)->anim->length / (self->beatLength * 4.0f);
            break;
        default:
            return;
        }
        ((AnimationPlayer*)self->statePlayer)->time = q;
        break;
    }
    case 2:
    case 13: {
        s32 n = 4;
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &r[2]);
        if (r[2] < 0x4EF) {
            if (r[2] >= 0x4EC) n = 2;
        }
        AddWorld3BossEntry(self, ((AnimationPlayer*)self->statePlayer), n);
        if (n == 2) ((AnimationPlayer*)self->statePlayer)->time = ((AnimationPlayer*)self->statePlayer)->anim->length * (self->barPosition / (f32)n);
        else ((AnimationPlayer*)self->statePlayer)->time = ((AnimationPlayer*)self->statePlayer)->anim->length * (self->barPosition / (f32)n);
        break;
    }
    case 11:
    case 16:
        self->contactsDisabled = 0;
        break;
    }
}

// A timeline entry of kind 0: the entry's direction and the clip for it become the agent's, the
// time is noted, and the beat (four per bar, after the agent's offset) is queued with its
// direction on the beat-press collider.
// The dead "li v0,1" is the compare constant of the if/else below. Both arms set clip, which the
// next statement sets again (the same choice, by index): flow deletes the two loads as dead,
// but the branch keeps its two empty arms through reload and sched2, and jump2, which deletes
// it, leaves the constant (docs/toolchain/alias-classes.md, "A merged arm keeps its place").
void ScheduleWorld3BossBeatPress(World3Boss* self, TimelineEntry* e)
{
    s32 dir = e->value;
    BeatPressEntry entry;
    s32 clip;
    if (dir == 1) {
        clip = self->clips[1];
    } else {
        clip = self->clips[0];
    }
    clip = self->clips[dir];
    self->direction = dir;
    self->pendingClip = clip;
    self->pressScheduledTime = g_gameTime[0];
    entry.dir = dir;
    entry.t = (f32)e->step * 4.0f + e->substep + (f32)self->spanBeats;
    AppendWorld3BeatPressEntry(self->beatPressCollider, (const U64P*)&entry);
}

void RemoveWorld3BossEntry(World3Boss* self, AnimationPlayer* key);

struct TempoNoticeRec {
    void* object;           // 0x00
    u8 pad04[4];
    s32 id;                 // 0x08
};

struct TempoLineSub {
    u8 pad00[0x78];
    f32 life;               // 0x78: how long the launched line object lives
};

struct TempoLine {
    u8 pad00[0x48];
    u8* rec;                // 0x48
    u8 pad4C[0x60 - 0x4C];
    TempoLineSub sub;       // 0x60
    u8 padDC[0xF0 - 0xDC];
    Vec4 vF0;              // 0xF0
};

struct PlacementRecord;
struct AgentNotification;
struct Agent;
void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg);

// Handles the third world's boss notifications: 0x13 with id 0x1A5 from its state player launches
// the next note of the current direction's line from the frame point toward the player's press
// collider, with a speed that arrives on the beat; 6 removes a finished player's entry; 0x14 from
// its walker maps its key (0x4EC to 0x4F8) to a voice number for the cached voice parameter.
void HandleWorld3BossNotification(World3Boss* self, s32 kind, TempoNoticeRec* rec)
{
    Vec4 a;
    Mat3 b;
    Mat3 rot;
    Vec4 p;
    s32 key;
    s32 voice;

    switch (kind) {
    case 0x13:
        if (rec->object == self->statePlayer && rec->id == 0x1A5) {
            TempoLine* line = (TempoLine*)self->lines[self->direction];
            ChooseObjectPoolItem((ObjectPool*)line);
            TempoLineSub* sub = &line->sub;
            f32 half = self->beatLength * 0.5f;
            f32 t = self->spanSeconds + self->pressScheduledTime - g_gameTime[0] + ((World3BeatPressCollider*)self->beatPressCollider)->timingWindow * half;
            u8* r = line->rec;
            FramePoint_001EBD10* fp = (FramePoint_001EBD10*)((World3BeatPressCollider*)self->beatPressCollider)->lineAnchors[self->direction];
            GetPlacementRecordTransform((PlacementRecord*)sub, &a, b.r, 0);
            ComputeObjectFrameAtTime((PlacedObject*)fp->object, 0, &p, &rot, 0, 0, t);
            Vu0::Q(line->vF0) = Vu0::Add(Vu0::Q(p), Vu0::Rotate(rot, Vu0::Q(fp->point)));
            f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(line->vF0)))) / t;
            // the object's class is not known
            *(f32*)(r + 0x690) = d;
            *(f32*)(r + 0x6F0) = d;
            sub->life = t * 1.25f;
            LaunchChosenPoolObject((ObjectPool*)line, 1);
            return;
        }
        break;
    case 6: {
        s32 i;
        for (i = 0; i < self->playerCount; i++) {
            if ((void*)self->players[i].player == (void*)rec) {
                break;
            }
        }
        if (i < self->playerCount) {
            RemoveWorld3BossEntry(self, (AnimationPlayer*)rec);
        }
        break;
    }
    case 0x14:
        if ((void*)rec == self->walker) {
            GetStateWalkerCurrentKey((StateWalker*)rec, &key);
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
                g_world3BossPendingVoice = voice;
                g_world3BossVoiceState = 1;
                SetCachedVoiceParam(0, voice);
            }
        }
        break;
    }
done:
    HandleAgentNotification(self, kind, (AgentNotification*)rec);
}

// Sets each tempo entry's animation speed so its animation reaches its next beat division exactly
// at the next beat time (one more full length when that point has already passed).
void SyncWorld3BossEntries(World3Boss* self)
{
    f32 den = self->nextBeatTime - (*(f32*)&g_gameTime);
    for (s32 k = 0; k < self->playerCount; k++) {
        TempoPlayerEntry* e = &self->players[k];
        AnimationPlayer* o = e->player;
        f32 len = o->anim->length;
        f32 start = o->time;
        f32 t = len / (f32)e->beats * (f32)((self->beat + 1) % e->beats);
        if (t <= start)
            t += len;
        o->speed = (t - start) / den;
    }

}

// Per-frame tempo of the third world's boss after the agent update: keeps the beat clock (beats,
// bars of four, new beat length at the bar end, held in some states), restarts the pending timeline
// once the voice parameter is taken (flag 2), runs the held timeline's entries, follows the cached
// voice parameter, and queues SyncWorld3BossEntries.
void UpdateWorld3Boss(World3Boss* self, f32 dt)
{
    World3Timeline* sub;
    s32 code;

    UpdateAgent(self, dt);
    if (g_world3BossVoiceState == 2) {
        if (self->beatLength != self->newBeatLength) {
            self->beatLength = self->newBeatLength;
            self->spanSeconds = self->newBeatLength * (f32)self->spanBeats;
        }
        sub = self->pendingTimeline;
        self->nextBeatTime = g_gameClock.time + self->beatLength;
        self->lastBeatTime = g_gameClock.time;
        self->bar = 0;
        self->beatInBar = 0;
        self->beat = 0;
        if (sub != 0) {
            self->pendingTimeline = 0;
            self->heldTimeline = sub;
            RestartWorld3Timeline(sub);
        }
        g_world3BossVoiceState = 0;
    }
    if (self->nextBeatTime <= g_gameClock.time) {
        s32 a = self->beat + 1;
        s32 b = self->beatInBar + 1;
        self->lastBeatTime = self->nextBeatTime;
        self->beat = a;
        self->beatInBar = b;
        if (b >= 4) {
            self->beatInBar = 0;
            self->bar = self->bar + 1;
            if (self->beatLength != self->newBeatLength) {
                self->beatLength = self->newBeatLength;
                self->spanSeconds = self->newBeatLength * (f32)self->spanBeats;
            }
        }
        if (self->beatGate == 1) {
            GetStateWalkerCurrentKey((StateWalker*)self->walker, &code);
            if (code == 0x4F1 || (code < 0x4F2 ? code == 0x4EE : (code == 0x4F4 || code == 0x4F7))) self->beatGate = 2;
        }
        self->nextBeatTime = self->nextBeatTime + self->beatLength;
    }
    self->barPosition = (f32)self->beatInBar + (g_gameClock.time - self->lastBeatTime) / self->beatLength;
    if (self->heldTimeline != 0) RunWorld3TimelineEntries(self->heldTimeline);
    if (g_world3BossVoiceState == 1) {
        RefreshCachedVoiceParam(1, 0);
        if (GetCachedVoiceParam(1) == g_world3BossPendingVoice) g_world3BossVoiceState = 2;
    }
    AppendQueuedCall(self->world, (void*)(void (*)(World3Boss*))SyncWorld3BossEntries, self, 0, 0);
}

// Shows the gauge bar element while the boss's walker is in one of the gauge states (0x4EE, 0x4F1,
// 0x4F4, 0x4F7) and the menus and fade are clear, else hides it.
void ShowWorld3BossGauge(World3Boss* self)
{
    s32 code;
    GetStateWalkerCurrentKey((StateWalker*)self->walker, &code);
    s32 obj = 0;
    if (code == 0x4F1 || (code < 0x4F2 ? code == 0x4EE : (code == 0x4F4 || code == 0x4F7))) {
        obj = AreMenusAndFadeClear();
    }
    if (obj) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

// Slot 94 of the third boss: in states 12 and 13 it heads for the object at +0xC48 (or stays on its
// own position), otherwise the agent's usual goal.
void UpdateWorld3BossGoal(World3Boss* self, s32 flag)
{
    s32 loc[4];
    s32 v = self->state;
    if (v >= 14) goto tail;
    if (v < 12) goto tail;
    {
        void* q = self->faceObject;
        if (q != 0) {
            GetObjectWorldPosition((BaseObject*)q, (Vec4*)loc);
            SetAgentGoalPoint(self, (Vec4*)loc);
        } else {
            SetAgentGoalPoint(self, &self->v140);
        }
    }
    return;
tail:
    UpdateAgentGoal(self, flag);
}

void UpdateAgentState(Agent* self);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);

// Per-frame facing of the third world's boss by its walker key: for 0x4ED, 0x4F0, 0x4F3 and 0x4F6
// it faces the active collider; for 0x4EC, 0x4EF, 0x4F2 and 0x4F5 (states 13 and 14) the way a face
// object points; for 0x4EE, 0x4F1, 0x4F4 and 0x4F7 (states 13 and 14) away from the collider.
// Otherwise it runs the generic agent state update.
void UpdateWorld3BossState(World3Boss* self)
{
    Vec4 diff;
    Mat3U rot;
    s32 code;
    SwitchedCollider* p;
    f32 y;
    f32 x;
    GetStateWalkerCurrentKey((StateWalker*)self->walker, &code);
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
        if (self->state >= 15) goto other;
        if (self->state < 13) goto other;
        if (self->faceObject == 0) goto other;
        GetObjectWorldRotation((BaseObject*)self->faceObject, (Mat3*)&rot);
        y = rot.m[0][1];
        x = rot.m[0][0];
        goto angle;
    case 0x4EE:
    case 0x4F1:
    case 0x4F4:
    case 0x4F7:
        if (self->state >= 15) goto other;
        if (self->state < 13) goto other;
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

void SetWorld3BossPendingTimeline(World3Boss* self, World3Timeline* value)
{
    self->pendingTimeline = value;
}

// Ends the timeline the boss holds and forgets it (a script built-in calls it).
void EndHeldWorld3Timeline(World3Boss* self)
{
    EndWorld3Timeline(self->heldTimeline);
    self->heldTimeline = 0;
}

// Sets the tempo in beats a minute and the beat length in seconds (60 / tempo); a script built-in
// calls it.
void SetWorld3BossTempo(World3Boss* self, s32 v)
{
    self->tempo = v;
    self->newBeatLength = 60.0f / (f32)v;
}

// Sets the span in beats and, from the beat length, in seconds (a script built-in calls it).
void SetWorld3BossSpanBeats(World3Boss* self, s32 v)
{
    self->spanBeats = v;
    self->spanSeconds = self->beatLength * (f32)v;
}

// Appends a tempo entry (animation player, beats per cycle) to the boss's array and registers the
// player's record callback; slot 92 and a script built-in call it.
void AddWorld3BossEntry(World3Boss* self, AnimationPlayer* a, s32 b)
{
    TempoPlayerEntry* e = &self->players[self->playerCount++];
    e->beats = b;
    e->player = a;
    AddAnimationPlayerRecordCallback(a, (PlacedObject**)self);
}

// Removes the tempo entry whose animation player is key from the boss's array, shifting the rest
// down.
void RemoveWorld3BossEntry(World3Boss* self, AnimationPlayer* key)
{
    s32 i = 0;
    if (self->playerCount > 0) {
        TempoPlayerEntry* p = self->players;
        while (p->player != key) {
            i++;
            if (i >= self->playerCount)
                return;
            p++;
        }
        if (i < self->playerCount) {
            TempoPlayerEntry* e = self->players + i;
            CopyMemory(e, e + 1, (self->playerCount - i - 1) * 8);
            self->playerCount = self->playerCount - 1;
        }
    }
}

// Slot 4 of the timeline: base init, then allocates room for 0xC0 sixteen-byte entries.
void InitWorld3Timeline(World3Timeline* self)
{
    InitObject(self);
    self->buffer = AllocateFrontMemory(0xC00);
}

// Slot 20 of the timeline: starts the object and remembers the third boss of the world as its
// target.
void FindWorld3TimelineTarget(World3Timeline* self)
{
    StartObject(self);
    self->found = FindFirstObjectByIdGathered(self->world, 5, 0x13, 0);
}

// Rewinds the timeline: entry index 0, time offset the target's current bar, and raises script
// event 0x1A.
void RestartWorld3Timeline(World3Timeline* self)
{
    self->index = 0;
    self->timeOffset = ((World3Boss*)self->found)->bar;
    TriggerScriptEvent(self, 0x1A, 0, 0);
}

// Ends the timeline: raises script event 0x1C, runs its kind-5 entry and, when a beat-press
// collider is linked, its kind-3 entry.
void EndWorld3Timeline(World3Timeline* self)
{
    s32 n;
    TriggerScriptEvent(self, 0x1C, 0, 0);
    n = 5;
    RunWorld3TimelineEntry(self, (TimelineEntry*)&n);
    if (((World3Boss*)self->found)->beatPressCollider) {
        n = 3;
        RunWorld3TimelineEntry(self, (TimelineEntry*)&n);
    }
}

// Runs every timeline entry that is due, in order: one is due once the target's bar (and, on the
// same bar, its position within it) has reached the entry's step plus the offset.
void RunWorld3TimelineEntries(World3Timeline* self)
{
    TimelineEntry* e;
    s32 v;
    while (self->index < self->entryCount && (e = self->Cur(), v = e->step + self->timeOffset, !(((World3Boss*)self->found)->bar < v))) {
        if (v == ((World3Boss*)self->found)->bar && ((World3Boss*)self->found)->barPosition < e->substep) return;
        RunWorld3TimelineEntry(self, e);
        self->index++;
    }
}

// Runs one entry of a third-world boss timeline by its kind: 0 schedules a beat press, 1 triggers
// script event 0x1B with the entry's value, 2 and 3 start and end the judging of the press collider
// (with its caption and a sound for 2), 4 and 5 turn the boss's flag on and off (with a caption and
// a lower-pitched sound for 4).
void RunWorld3TimelineEntry(World3Timeline* self, TimelineEntry* msg)
{
    switch (msg->kind) {
    case 0:
        ScheduleWorld3BossBeatPress((World3Boss*)self->found, msg);
        break;
    case 1: {
        s32* loc = &msg->value;
        TriggerScriptEvent(self, 0x1B, 1, &loc);
        break;
    }
    case 2:
        ((World3Boss*)self->found)->beatPressCollider->judging = 1;
        g_beatPressGlyphElement.vt->m16(&g_beatPressGlyphElement, 2);
        ResetPadStepRepeat(&g_padRecord);
        StartSoundEffect(0, 0, 0, 0, 80000.0f, 70000.0f, 1.5f, 0.5f, 0.0f, 0, 0);
        break;
    case 3:
        ((World3Boss*)self->found)->beatPressCollider->judging = 0;
        ((World3Boss*)self->found)->beatPressCollider->runEnded = 0;
        g_beatPressGlyphElement.vt->m16(&g_beatPressGlyphElement, 0);
        break;
    case 4:
        ((World3Boss*)self->found)->fC4C = 1;
        g_bossBeatGlyphElement.vt->m16(&g_bossBeatGlyphElement, 2);
        StartSoundEffect(0, 0, 0, 0, 80000.0f, 70000.0f, 1.5f, -0.25f, 0.0f, 0, 0);
        break;
    case 5:
        ((World3Boss*)self->found)->fC4C = 0;
        g_bossBeatGlyphElement.vt->m16(&g_bossBeatGlyphElement, 0);
        break;
    }
}

// Adds a 16-byte entry (kind, step, substep) to the timeline buffer and returns it; at the limit of
// 0xC0 entries it returns a dummy entry.
TimelineEntry* AppendWorld3TimelineEntry(World3Timeline* self, s32 a, s32 b, f32 c)
{
    if (self->entryCount >= 0xC0) return (TimelineEntry*)D_00625760;
    // address arithmetic over a variable index
    TimelineEntry* e = (TimelineEntry*)((u8*)self->buffer + self->entryCount * 16);
    self->entryCount = self->entryCount + 1;
    (void)FillMemory(e, 0, 16);
    e->kind = a;
    e->step = b;
    e->substep = c;
    return e;
}

// Adds a kind-0 timeline entry at the given step and substep with a value (a script built-in calls
// it).
void AppendWorld3TimelineKind0Entry(World3Timeline* self, s32 p, f32 time, s32 val)
{
    AppendWorld3TimelineEntry(self, 0, p, time)->value = val;
}

// Adds a kind-1 timeline entry at the given step and substep with a value.
void AppendWorld3TimelineKind1Entry(World3Timeline* self, s32 p, f32 time, s32 val)
{
    AppendWorld3TimelineEntry(self, 1, p, time)->value = val;
}

// Adds a kind-2 timeline entry at the given step and substep.
void AppendWorld3TimelineKind2Entry(World3Timeline* self, s32 p, f32 time)
{
    AppendWorld3TimelineEntry(self, 2, p, time);
}

// Adds a kind-3 timeline entry at the given step and substep.
void AppendWorld3TimelineKind3Entry(World3Timeline* self, s32 p, f32 time)
{
    AppendWorld3TimelineEntry(self, 3, p, time);
}

// Adds a kind-4 timeline entry at the given step and substep.
void AppendWorld3TimelineKind4Entry(World3Timeline* self, s32 p, f32 time)
{
    AppendWorld3TimelineEntry(self, 4, p, time);
}

// Adds a kind-5 timeline entry at the given step and substep.
void AppendWorld3TimelineKind5Entry(World3Timeline* self, s32 p, f32 time)
{
    AppendWorld3TimelineEntry(self, 5, p, time);
}

LINKER_REMNANT(func_001ED638);

// Writes the vector (cos angle * scale, sin angle * scale, z).
void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z)
{
    SinCos p;
    ComputeSinCos(&p.sine, &p.cosine, angle);
    out->x = p.cosine * scale;
    out->y = p.sine * scale;
    out->z = z;
}

// Writes the vector of length scale for a heading (first) and an elevation (second) angle.
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

// Writes a unit vector perpendicular to v: crosses v with a copy whose two smaller-magnitude
// components are swapped (one negated), then normalises the result.
void ComputeUnitPerpendicular(Vec4* v, Vec4* out)
{
    Vec4 w;
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

void ComputeUnitPerpendicular(Vec4* v, Vec4* out);
extern "C" f32 Arccosine(f32 x);

// Gives the angle between a and b in radians (0 and the x axis in axis if either is almost zero),
// and the unit axis of the turn from a to b in axis (a perpendicular if they are parallel); axis
// may be null.
f32 ComputeAngleBetweenVectors(Vec4* a, Vec4* b, Vec4* axis)
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

// Finds the closest approach of the two lines a to b and c to d: writes to out2 the parameters of
// the closest point on each line (both 0 where they are almost parallel), to dist the signed
// distance between the lines along their common normal, and to normal that unit normal (the z axis
// if it has no length), oriented to point from the first line toward the second.
void FindSegmentClosestParams(Vec4* a, Vec4* b, Vec4* c, Vec4* d, f32* out2, f32* dist, Vec4* normal)
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

void FindSegmentClosestParams(Vec4* a, Vec4* b, Vec4* c, Vec4* d, f32* out2, f32* dist, Vec4* normal);

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
void FindClosestPointsOnSegments(const Vec4* p0, const Vec4* p1, const Vec4* q0, const Vec4* q1, f32* st, f32* dist, Vec4* dir)
{
    FindSegmentClosestParams((Vec4*)p0, (Vec4*)p1, (Vec4*)q0, (Vec4*)q1, st, dist, dir);
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
    const Vec4* fallback = &g_unitXVector;
    u128 len = Vu0::Length(d);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        *dir = *fallback;
    } else {
        Vu0::Q(*dir) = Vu0::DivX(d, len);
    }
    Vu0::StoreX(*dist, Vu0::ToBits(len));
}

// The angle of a vector in the xy plane and its elevation, both wrapped, written to a1 and a2 (each
// only when not null).
void GetVectorAngles(Vec3* v, f32* a1, f32* a2)
{
    if (a1)
        *a1 = WrapAngle(ArctangentOfRatio(v->y, v->x));
    if (a2) {
        f32 r = Fpu::Sqrt(v->x * v->x + v->y * v->y);
        *a2 = WrapAngle(ArctangentOfRatio(v->z, r));
    }
}

// Rotates vector b by the angles in in->y and in->z (sine/cosine of each) and writes the result to
// out.
void RotateVectorByTwoAngles(Vec3* in, Vec3* b, Vec3* out)
{
    f32 t[4];
    ComputeSinCos(in->y, &t[0], &t[1]);
    ComputeSinCos(in->z, &t[2], &t[3]);
    out->x = t[1] * t[3] * b->x - t[2] * b->y;
    out->y = t[1] * t[2] * b->x + t[3] * b->y;
    out->z = -t[0] * b->x + b->z;
}

extern "C" f32 Sine(f32 x);
extern "C" f32 Cosine(f32 x);
extern "C" f32 Tangent(f32 x);

// The launch velocity from from to to under the gravity at 0x358 of rec (the world's when null),
// its angle above the straight line by angle's sine of the way to vertical. The speed's product
// is a variable of its own: retail moves the square root into q's register before it.
s32 ComputeBallisticLaunchVelocity(Vec4* from, Vec4* to, Vec4* out, u8* rec, f32 angle)
{
    Vec4 d;
    f32 h;
    f32 s = Sine(angle);
    u8* g;
    if (rec != 0) {
        g = (u8*)&((Collider*)rec)->gravity;
    } else {
        g = (u8*)&g_currentWorld->gravity;
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
    f32 q = ((Vec4*)g)->z / (e + e);
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
s32 ComputeLaunchVelocityToPoint(f32 speed, Vec4* from, Vec4* to, Vec4* out, u8* rec)
{
    Vec4 d;
    u8* g;
    if (rec != 0) {
        g = (u8*)&((Collider*)rec)->gravity;
    } else {
        g = (u8*)&g_currentWorld->gravity;
    }
    f32 grav = ((Vec4*)g)->z;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*to), Vu0::Q(*from));
    if (__builtin_fabsf(grav) < 1.0f) {
        u128 k = Vu0::Scalar(speed);
        u128 n = Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_zeroVector));
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
        Vec4 flat;
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

void ForwardBallisticLaunchVelocity(Vec4* from, Vec4* to, Vec4* out, u8* rec, f32 angle)
{
    ComputeBallisticLaunchVelocity(from, to, out, rec, angle);
}

// Writes v to out, scaled down to length max when it is longer.
void ClampVectorLength(Vec4* v, Vec4* out, f32 max)
{
    u128 q = Vu0::Q(*v);
    f32 len = Vu0::ToFloat(Vu0::Length(q));
    if (max < len) {
        Vec4 s;
        Vu0::Q(s) = Vu0::FromFloat(max / len);
        Vu0::Q(*out) = Vu0::MulX(q, Vu0::Q(s));
    } else if (v != out) {
        Vu0::Q(*out) = q;
    }
}

// Sets up a packet writer: base init, closing pad on, its vtable installed and the open tag and
// register count cleared.
PacketWriter* InitPacketWriter(PacketWriter* self)
{
    (void)InitPacketBuffer(self);
    self->padsOnClose = 1;
    self->vt = (const PacketWriterVt*)g_packetWriterVtable;
    self->openTag = 0;
    self->registerCount = 0;
    return self;
}

LINKER_REMNANT(func_001EE360);

// Zero-fills words from the packet cursor until it sits at word target (0 to 3) of a quadword.
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

// Appends the VIF BASE (0x03000000) and OFFSET (0x02000000) words with the given values.
void WriteVifBaseOffset(PacketWriter* s, u32 a, u32 b)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = a | 0x3000000;
    u32* q = (u32*)s->cur;
    s->cur = (u8*)(q + 1);
    *q = b | 0x2000000;
}

// Appends a VIF MSCAL code starting the microprogram at byte address n (stored in units of 8
// bytes).
void WriteVifMscal(PacketWriter* s, s32 n)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = (u32)((n / 8) | 0x14000000);
}

// Appends a VIF MSCALF code, as WriteVifMscal.
void WriteVifMscalf(PacketWriter* s, s32 n)
{
    u32* p = (u32*)s->cur;
    s->cur = (u8*)(p + 1);
    *p = (u32)((n / 8) | 0x15000000);
}

// Appends a VIF FLUSH code (0x11000000).
void WriteVifFlush(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x11000000;
}

// Appends a VIF FLUSHA code (0x13000000).
void WriteVifFlushA(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x13000000;
}

// Appends a VIF FLUSHE code (0x10000000).
void WriteVifFlushE(PacketWriter* b)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = 0x10000000;
}

// Appends a VIF STCYCL code with write cycle y and cycle length x.
void WriteVifStcycl(PacketWriter* b, u32 x, u32 y)
{
    u32* p = (u32*)b->cur;
    b->cur = (u8*)(p + 1);
    *p = y | (x << 8) | 0x01000000;
}

// Appends a VIF STROW code (0x30000000) with the four words of src, the row register.
void WriteVifStrow(PacketWriter* b, u32* src){
 u32 *p1,*p2,*p3,*p4,*p5;
 p1=(u32*)b->cur; b->cur = (u8*)(p1 + 1); *p1=0x30000000;
 p2=(u32*)b->cur; b->cur = (u8*)(p2 + 1); *p2=src[0];
 p3=(u32*)b->cur; b->cur = (u8*)(p3 + 1); *p3=src[1];
 p4=(u32*)b->cur; b->cur = (u8*)(p4 + 1); *p4=src[2];
 p5=(u32*)b->cur; b->cur = (u8*)(p5 + 1); *p5=src[3];
}

// Appends a VIF STMASK code (0x20000000) with the mask when it is nonzero, and remembers the mask
// in the writer.
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

// Appends a VIF UNPACK word for format a, count b at address c (the interrupt bit when the writer's
// tag is open) and returns the data size in bytes (per-format size times count).
s32 WriteVifUnpackHeader(PacketWriter* self, s32 a, s32 b, s32 c)
{
    u32 lo = ((u32)b << 16) | 0x6000C000u;
    u32 head = ((u32)a << 24) | lo;
    u32* p = (u32*)self->cur;
    self->cur = (u8*)(p + 1);
    u32 tag = head | (u32)c;
    *p = tag;
    if (self->openTag != 0) {
        *p = tag | 0x10000000;
    }
    return g_unpackBytesPerElement[a] * b;
}

// Writes a VIF unpack header and reserves its data in the packet; gives back the start of the data
// and its size (both 0 for an empty unpack).
void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor)
{
    if (size == 0) {
        if (outCursor) *outCursor = 0;
        if (outSize) *outSize = 0;
    } else {
        size = WriteVifUnpackHeader(s, a, size, d);
        if (outCursor) *outCursor = s->cur;
        s->cur += ((size + 3) / 4) * 4;
        if (outSize) *outSize = size;
    }
}

// Reserves a VIF unpack in the packet writer and copies size bytes of words from src into it, the
// leftover words (count mod 4) first and then four at a time.
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4)
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

// Writes a VIF unpack header for b items, pads to quad slot 3, adds the data as a DMA reference tag
// of its length in quadwords and optionally returns the offset of the header; nothing is written
// for a count of zero.
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
            *out = (s32)self->openHeader - 0xC;
        }
    }
}

// Writes a VIF DIRECT code (0x50) for n quadwords, with the interrupt bit when flag is set, and
// copies the n quadwords from buf behind it.
void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag)
{
    PadPacketToQuadSlot(self, 3);
    u32* p = (u32*)self->cur;
    u32 w = (u32)flag << 31;
    self->cur = (u8*)(p + 1);
    w = w | 0x50000000u;
    *p = (u32)n | w;
    AppendPacketQuadwords(self, n, buf);
}

// As WriteVifDirect, but the data is not copied: a DMA reference tag to it is added to the packet.
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

// Appends a DIRECT packet holding everything the second writer has written so far (its span in
// quadwords).
void WriteVifDirectFromWriter(PacketWriter* a0, PacketWriter* a1) {
    u32 span = a1->curU - (u32)a1->begin;
    WriteVifDirect(a0, span >> 4, (void*)a1->begin, 0);
}

// Slot 4 of the value-list object: base init and registers itself as the world's value list.
void InitValueListObject(ValueListObject* self)
{
    InitObject(self);
    self->world->valueListObject = self;
}

// Slot 10 of the value-list object: reads the tree of nodes, a 16-bit count and that many 32-bit
// values, then the property records.
void LoadValueList(ValueListObject* self, void* src)
{
    s32 i;
    s32 n;

    ReadLinkedItemArray((BufferedStream*)src, &self->count34, (LinkedItem**)&self->data38);
    n = ReadBufferedU16((BufferedStream*)src);
    self->valueCount = n;
    self->values = (s32*)AllocateFrontMemory(n * 4);
    for (i = 0; i < self->valueCount; i++) {
        self->values[i] = ReadBufferedU32((BufferedStream*)src);
    }
    ReadPropertyRecords(self, src);
}

// Turns a leaf mask into the full mask: ANDs the table value of every set bit together and ORs the
// result with the mask (0 for an empty mask).
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

// The mask of the leaves within radius of point under node: the walk follows the near side,
// descends into the far side too where the sphere straddles the plane, and ORs each leaf's mask
// (ExpandMaskThroughTable) into *out.
s32 QueryValueTreeMask(ValueListObject* self, sptr node, Bits128 point, f32 radius, s32* out)
{
    if (node < 0) {
        *out = ExpandMaskThroughTable(self, node);
    } else {
        f32 near = -radius;
        sptr next;
        do {
            PlaneNode* n = (PlaneNode*)node;
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(point), Vu0::Q(n->normal))) - n->offset;
            if (d < near) {
                next = n->below;
            } else if (radius < d) {
                next = n->above;
            } else {
                next = n->above;
                if ((u32)next & 0x80000000) {
                    *out |= ExpandMaskThroughTable(self, next);
                } else {
                    QueryValueTreeMask(self, next, point, radius, out);
                }
                next = n->below;
            }
            node = next;
        } while (!((u32)next & 0x80000000));
        *out |= ExpandMaskThroughTable(self, next);
    }
}

// Looks up the mask for a point and radius in the world's value tree into *out; 0x0FFFFFFF when
// there is no list or tree.
void QueryValueListMask(ValueListObject* self, f32 radius, Bits128* vec, s32* out)
{
    if (self != 0 && self->data38 != 0) {
        Bits128 q = *vec;
        *out = 0;
        QueryValueTreeMask(self, (sptr)self->data38, q, radius, out);
    } else {
        *out = 0x0FFFFFFF;
    }
}

ASM_FUNC(func_001EEBB0);

// Slot 0 of the attached set: runs InitCollider, sets a flag bit, unit drag and push factors and
// anchors 3, 0, 3, 0, and sets up the tracked nodes.
void InitAttachedSet(AttachedSet* self)
{
    u64 bits;
    s32 one;

    InitCollider(self);
    bits = self->flags538;
    one = 0x8000;
    bits |= (u64)one << 28;
    self->flags538 = bits;
    self->splashSoundEnabled = 1;
    self->splashBurstEnabled = 1;
    self->dragFactor = 1.0f;
    self->pushFactor = 1.0f;
    SetColliderAnchors(self, 3, 0, 3, 0);
    InitTrackedNodes(&self->trackedNodes, (ContactTracker*)self);
    self->trackedNodes.f04 = 3;
}

// Slot 16 of the attached set: starts the placed object, fills the tracked nodes, allocates the
// 0x80-byte item block of its group and calls slot 50 when +0x278 is set.
void StartAttachedSet(AttachedSet* self)
{
    ChildWalkFrame fr((s32*)&self->children);
    g_activeListFrames = (ListFrame*)&fr;
    StartPlacedObject(self);
    FillTrackedNodes(&self->trackedNodes);
    self->group.items = (void**)AllocateFrontMemory(0x80);
    if (self->oscillatorBlock != 0) {
        self->desc03()->m32(self);
    }
}

struct Oscillator;
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void TransformStateToAncestorFrame(PlacedObject* self, PlacedObject* top, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin);
void ComputeOscillatorDisplacement(Oscillator* self, f32 time, Vec4* in, Vec4* deltas, Vec4* outA, Vec4* outDeltas, Vec4* outB);

// Gives the position (outA) and velocity (outB) that a point in (given in world space) of the
// attached set has, by taking it into the set's frame and moving it with the set's state up the
// frames to the ancestor (and, if the set has an oscillator, adding the oscillator's displacement
// at the point).
void GetAttachedSetPointMotion(AttachedSet* self, void* in, Quad16* outA, Quad16* outB)
{
    Vec4 a;
    Quad16 b;
    Quad16 c;
    Vec4 d;
    TransformDirectionBetweenFrames(0, self, (Vec4*)in, &a);
    b = *(Quad16*)&self->baseVelocity;
    a.z = 0.0f;
    c = *(Quad16*)&g_zeroVector;
    TransformStateToAncestorFrame(self, 0, &a, 0, (Vec4*)&b, (Vec4*)&c);
    if (self->oscillatorBlock != 0) {
        ComputeOscillatorDisplacement((Oscillator*)(*(void**)(self->oscillatorBlock + 0xC)), 50.0f, (Vec4*)in, 0, 0, 0, &d);
        Vu0::Q(*(Vec4*)&b) = Vu0::Add(Vu0::Q(*(Vec4*)&b), Vu0::Q(d));
    }
    if (outA != 0) {
        *outA = b;
    }
    if (outB != 0) {
        *outB = c;
    }
}

// After the attach records of an owner have been rebuilt, compares each one's two marker bits in
// its target's flags (59 for the old records, 60 for the new) to remove or add the attachment on
// the target, drops the records without bit 60 from the list (freeing them in a chain) and clears
// both bits.
void ReconcileColliderAttachments(void* owner, ColliderAttachment** head)
{
    ColliderAttachment** link = head;
    ColliderAttachment* node = *head;
    ColliderAttachment* removed = 0;
    while (node != 0) {
        Collider* o = node->target;
        ColliderAttachment* next = node->nextOwn;
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
    ReleaseAttachRecords((World*)owner, removed);
}

ColliderAttachment* TakeAttachRecord(World* self);
f32 MeasureAttachedSetContactDepth(AttachedSet* self, TurningCollider* o, Vec4* nOut, Vec4* hitOut);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// Per-frame update of an attached set (a collider others ride on): after the base update it clears
// the old attach records and takes a new one for each collider in contact with its root that pushes
// and sinks into it (MeasureAttachedSetContactDepth not 0). When the set tells landings and the
// collider fell faster than 100, it checks by a segment test where it landed and notifies it.
void UpdateAttachedSet(AttachedSet* self, f32 dt)
{
    s32 changed = 0;
    UpdateCollider(self, dt);
    if (self->tree.nodes == 0) {
        return;
    }
    World* world = self->world;
    ColliderAttachment* link;
    Collider* c;
    for (link = self->links; link != 0; link = link->nextOwn) {
        link->target->flags538 |= 1ULL << 59;
    }
    for (ContactRow03* r = ((Collider*)self->root)->contacts->head; r != 0; r = r->next) {
        c = r->other;
        if (c->pushFactor < 0.0001f) {
            continue;
        }
        if (c->flags538 & ((1ULL << 54) | (1ULL << 42))) {
            continue;
        }
        if (MeasureAttachedSetContactDepth(self, (TurningCollider*)c, 0, 0) == 0.0f) {
            continue;
        }
        c->flags538 |= 1ULL << 60;
        if (self->oscillatorBlock != 0) {
            ClearRootTries((PlacedObject*)(c));
        }
        if (c->flags538 & (1ULL << 59)) {
            continue;
        }
        link = TakeAttachRecord(world);
        link->owner = self;
        link->target = c;
        link->nextOwn = self->links;
        self->links = link;
        if (self->tellsLanding == 0) {
            continue;
        }
        if (!(c->v150.z < -100.0f)) {
            continue;
        }
        Vec4 from;
        Vec4 to;
        ColliderSpan spans[16];
        Vec4 off;
        if (self->oscillatorBlock != 0) {
            Vec4 d;
            ComputeOscillatorDisplacement((Oscillator*)(*(void**)(self->oscillatorBlock + 0xC)), 50.0f, &c->v140, 0, &d, 0, 0);
            Vu0::Q(off) = Vu0::Sub(Vu0::Vec::Of(d), Vu0::Vec::Of(c->v140)).q;
        } else {
            off = g_zeroVector;
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

// Slot 0xDC of the attached set: passes the step on to its link's target (that object's slot 46,
// with this set).
void ForwardAttachedSetLinkStep(AttachedSet* self, ColliderAttachment* link)
{
    Collider* target = link->target;
    ((AttachNotifyFn)target->desc03()->m46)(target, self);
}

// Handles the destruction message (kind 2) of an attached set: when it is the set itself, it
// detaches all its attached colliders and frees the records; when it is a collider it was carrying,
// that attach record is removed and the collider is told (message 11). Rebuilds the set afterwards
// if anything changed.
void HandleAttachedSetNotification(AttachedSet* self, s32 kind, void* msg)
{
    s32 flag = 0;
    if (kind == 2) {
        if (msg == (void*)self) {
            ColliderAttachment* n = self->links;
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
            ColliderAttachment** link = &self->links;
            ColliderAttachment* n = *link;
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

// On the root of an attached set, rebuilds the registered group of the object plus the target of
// each attached link and registers it with the world.
void RebuildAttachedSet(AttachedSet* self)
{
    if (self->root == self) {
        AttachedGroup* s = &self->group;
        UnregisterObjectGroup(self->world, (FoundList*)s);
        s->items[0] = self;
        s->count = 1;
        ColliderAttachment* node = self->links;
        if (node) {
            do {
                s->items[s->count++] = node->target;
                node = node->nextOwn;
            } while (node);
        }
        RegisterObjectGroup(self->world, (FoundList*)s);
    }
}


// Measures how far collider o sinks into the set: a segment from below the collider (the player's
// feet 75 below, else its lower bound) to its upper bound is tested against the set's tree
// (displaced by its oscillator). Gives the first span's length as a fraction of the segment (0 for
// none); nOut gets its normal, hitOut the surface normal or the z axis.
f32 MeasureAttachedSetContactDepth(AttachedSet* self, TurningCollider* o, Vec4* nOut, Vec4* hitOut)
{
    Vec4 from;
    Vec4 to;
    ColliderSpan spans[16];
    if (self->oscillatorBlock != 0) {
        ComputeOscillatorDisplacement((Oscillator*)(*(void**)(self->oscillatorBlock + 0xC)), 50.0f, &o->v140, 0, &from, 0, 0);
        Vu0::Q(from) = Vu0::Q(to) = Vu0::MulXSum(Vu0::Q(o->v140), Vu0::Scalar(2.0f), Vu0::Q(from), Vu0::Scalar(-1.0f));
    } else {
        from = to = o->v140;
    }
    if (o == g_player) {
        from.z = from.z + -75.0f;
        if (o->groundContact != 0) {
            from.z = o->groundContactPoint.z >? from.z;
        }
    } else {
        from.z = from.z + (((Collider*)o)->boundsMin.z - o->v140.z);
    }
    to.z = to.z + (((Collider*)o)->boundsMax.z - o->v140.z);
    s32 n = CollectTreeNodeSpans(self->tree.nodes, &from, &to, 0, 0x10, spans);
    if (n == 0) {
        if (hitOut != 0) {
            *hitOut = g_unitZVector;
        }
        return 0.0f;
    }
    if (nOut != 0) {
        *nOut = *(Vec4*)&spans[0].q[1];
    }
    if (hitOut != 0) {
        if (spans[0].face54 != 0) {
            *hitOut = *(Vec4*)spans[0].face54;
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
void ComputeOscillatorMaxDisplacement(Oscillator* osc, Vec4* out);

// Grows the box and both radii by the oscillator's largest swing.
void UpdateAttachedSetBounds(AttachedSet* self)
{
    UpdateColliderBounds(self);
    SwingRecord* r = (SwingRecord*)self->oscillatorBlock;
    if (r != 0 && r->osc != 0) {
        Vec4 d;
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

// Slot 71 of the attached set: passes the launch offer to its tracked nodes and accepts it (returns
// 1).
s32 RequestAttachedSetLaunch(AttachedSet* self, void* source, TrackedNodeOffer* offer)
{
    OfferTrackedNodeLaunch(&self->trackedNodes, source, offer);
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

// Slot 0 of the state-reset object: base init and both its ids set to -1.
void InitStateResetObject(StateResetObject* self)
{
    InitPlacedObject(self);
    self->id2D0 = -1;
    self->id2E0 = -1;
}

// Slot 16 of the state-reset object: starts the placed object, resolves its link, sets state 0 and
// takes itself out of its parent's list.
void StartStateResetObject(StateResetObject* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, (ObjectLink*)g_stateResetObjectLinks);
    SetStateAndNotify(self, 0);
    self->desc->m03(self);
}

// Adds or updates a keyed entry in the object's table of 4 (a script built-in calls it).
s32 AddStateResetEntry(StateResetObject* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    return UpsertKeyedEntry((ZoneTargetEntry*)self->targets, 4, &self->targetCount, a1, a2, a3, a4);
}

// Update slot of the state-reset object: does nothing.
void UpdateStateResetObject(StateResetObject* self, f32 dt) {}

// Sets the state of a state-reset object when it changes: entering or leaving state 2 turns its
// walker targets on or off, and the change is stamped with the game time and sent to the object as
// message 0x16 with the old and new state.
void SetStateAndNotify(StateResetObject* self, s32 state)
{
    if (self->id2D0 != state) {
        if (state != 0) {
            if (state == 2)
                SetGatheredWalkerTargets((World*)g_currentWorld, self->targetCount, (ZoneTargetEntry*)self->targets, self, 1);
        } else {
            if (self->id2D0 == 2)
                SetGatheredWalkerTargets((World*)g_currentWorld, self->targetCount, (ZoneTargetEntry*)self->targets, self, 0);
        }
        StateChangeMsg evt;
        evt.old = self->id2D0;
        evt.self = self;
        evt.cur = state;
        self->id2D0 = state;
        self->stateTime = g_gameTime[0];
        self->desc->m0E(self, 0x16, &evt);
    }
}

// Slot 13 of the state-reset object: base handling, and for notification kind 5 whose id matches
// its own it resets the state to 0.
void HandleStateResetNotification(StateResetObject* self, s32 kind, StateResetMsg* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 5) {
        if (msg->id == self->id2DC) {
            SetStateAndNotify(self, 0);
        }
    }
}

// Allocates a zeroed 48-byte state-reset group and installs its method table.
void* CreateRecord2505C0(void)
{
    StateResetGroup* p = (StateResetGroup*)AllocateZeroedFrontMemory(48);
    p->vtbl = g_stateResetGroupMethods;
    return p;
}

// Appends a value to the group's list while it holds fewer than 8.
void AppendToSmallList(StateResetGroup* self, StateResetObject* value) { u32 i = self->count; if (i < 8) { self->items[i] = value; self->count = i + 1; } }

// Removes value from the list by moving the following items down one place and lowering the count;
// does nothing when it is not in the list.
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

// Checks a state reset group's items: when its owner has a selected id equal to the first item's
// and all items are in state 1 it moves every item to state 2 and clears the selection; otherwise
// each item in state 2 with no hold whose time has run longer than its limit is reset to state 0.
void UpdateItemTimeouts(StateResetGroup* s)
{
    s->scheduled = 0;
    if (s->owner != 0 && s->owner->selectedId != -1 && s->items[0]->id2E0 == s->owner->selectedId) {
        s32 i;
        for (i = 0; i < s->count; i++) {
            if (s->items[i]->id2D0 != 1) break;
        }
        if (i >= s->count) {
            for (i = 0; i < s->count; i++) {
                SetStateAndNotify(s->items[i], 2);
            }
            s->owner->selectedId = -1;
        }
        return;
    }
    for (s32 i = 0; i < s->count; i++) {
        StateResetObject* it = s->items[i];
        if (it->id2D0 != 2) continue;
        if (it->id2DC != 0) continue;
        f32 d = g_gameClock.time - it->stateTime;
        if (it->stateDuration < d) {
            SetStateAndNotify(it, 0);
        }
    }
}

// Once per group, queues UpdateItemTimeouts on the current world.
void ScheduleItemTimeouts(StateResetGroup* self)
{
    if (self->scheduled == 0) {
        self->scheduled = 1;
        AppendQueuedCall(g_currentWorld, (void*)UpdateItemTimeouts, self, -1, 0);
    }
}

LINKER_REMNANT(func_001EFCE0);

// Puts the fade's mode to -1 and back to 0 so that it switches off.
void ResetScreenFade(ScreenFade* o)
{
    o->mode = -1;
    SetScreenFadeMode(o, 0);
}

// Per-frame update of the screen fade by its mode: 0 checks for a restore request, 1 fades out (0.5
// s, or 1.5 s for style 1) raising the opacity and lowering the volume on channel 6 and then goes
// to mode 2, 2 waits for the world load to finish and goes to 3, 3 fades back in (0.25 s, or 1 s
// for style 1) and ends at mode 0.
void UpdateScreenFade(ScreenFade* self, PadRecord* a1)
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

// Draws the screen fade when one is active: style 0 is a black full-screen sprite with alpha
// opacity * 255, style 1 draws the coloured triangle set at that opacity (or the sprite when there
// is none).
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

// Starts a screen fade to the request args (a world to load) with the style count, only if no fade
// is running: pops an active step sequence element unless it is in its state 2, flags whether the
// request's key is the fixed one, and begins mode 1 (fade out) when a world exists, or mode 2
// straight away.
void StartScreenFade(ScreenFade* dst, FadeRequest* args, s32 count)
{
    IdentityKey* p;
    s32 mode;

    if (dst->mode == 0) {
        if (g_activeStepSequence != 0) {
            if (g_activeStepSequence->mode2D0 != 2) {
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


// Stores a fade request and its style as the screen fade's queued one.
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

// When the pad select flag is held, a fade request is queued and button 0x800 is pressed, copies
// the queued request into the active one (flagging whether its key is the fixed one), switches the
// fade to mode and gives 1; otherwise gives 0.
s32 RestoreFadeRequest(ScreenFade* self, PadRecord* o, s32 mode)
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
        SetScreenFadeMode(self, mode);
        return 1;
    }
    return 0;
}

LINKER_REMNANT(func_001F0218);

// Switches the screen fade to a mode (nothing if unchanged): leaving 2 closes the warp page, mode 0
// clears the opacity, mode 1 sets up the fade out (for style 2 the warp cursor of the destination
// entry), mode 2 starts the queued world load (and sets the opacity to 1), mode 3 starts fading
// back in.
void SetScreenFadeMode(ScreenFade* self, s32 mode)
{
    if (self->mode == mode) goto L0410;
    if (self->mode == 2) {
        if (g_currentWarpPage != 0) {
            SetWarpPageMode((WarpPage*)g_currentWarpPage, 0);
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
        QueueWorldLoad((WorldLoadRequest*)&g_worldLoadRequest, (WorldKeyBlock*)q->key, q->f08, q->f0C, q->flags);
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
        s32 v = GetEntryIdByKey((KeyedEntry*)self->active.key);
        s32 a3 = v >> 8;
        s32 a2 = v & 0xFF;
        if (g_currentWarpPage == 0) goto L034C;
        if (v == -1) goto L034C;
        s32 a1 = 10;
        if (a3 != 0) a1 = a2;
        SetWarpCursor((WarpPage*)g_currentWarpPage, a1, 3);
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
    SetElementStackState((ElementStack*)g_elementStack, 8);
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
        if (self->style == D_00275BF0) {
            s32 idx = g_previousLevelIndex;
            if (idx != -1) {
                g_mapScreenList.current = g_mapScreenList.nodes[idx];
            }
        }
        if (g_mapScreenList.current != 0) {
            g_mapScreenList.current->openKind = 3;
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

// Starts the screen fade with a request of kind 1 for the given object and value (count passed on).
void StartObjectFade(IdentityKey* obj, s32 value, s32 count)
{
    FadeRequest m;
    m.kind = 1;
    m.key = obj;
    m.f08 = value;
    m.flags = 0;
    StartScreenFade(&g_screenFade, &m, count);
}

// The warp entry the player is at: the saved location's entry, or 10 when the warp mode flag is 2;
// the page compares its cursor with it before confirming.
s32 GetCurrentWarpEntry(void)
{
    if (D_00275BF0 != 2) {
        return g_saveData->entryIndex;
    }
    return 10;
}

// True when warp entry kind (0 to 8 are the page's entries, 9 and 10 special ones) is available on
// this page: the save's entry flag (bit 0) for the page's slot and entry, with kind 9 using the
// slot's mask in D_00275FC8 and kind 10 always counting. Slot 5 excludes kinds 1 and 7. The slot
// and entry index it looked at go to outA and outB when given.
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
                // address arithmetic over a variable index
                if (*(s32*)((u8*)g_saveData + m + 0x88) & 1) {
                    s32 q = g_saveData->levels[mode].f448;
                    flag = (q & g_warpSlotKindMasks[mode]) != 0;
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

// True when the entry can be reached by the cursor on this page: never for kind 9; the entry's own
// availability, or, for entries from 2 up, the availability of entry 1 (below a limit that depends
// on the slot) or of the special entry 9 (above it).
s32 IsWarpEntryReachable(void* self, s32 code)
{
    s32 r;
    if (code == 9) {
        return 0;
    }
    r = IsWarpEntryAvailable((WarpPage*)self, code, 0, 0);
    if (r == 0) {
        switch (((WarpPage*)self)->slot) {
        case 1:
            if (code >= 2) {
                if (code < 6) {
                    r = IsWarpEntryAvailable((WarpPage*)self, 1, 0, 0);
                } else if (code < 8) {
                    r = IsWarpEntryAvailable((WarpPage*)self, 9, 0, 0);
                }
            }
            break;
        case 2:
        case 3:
        case 4:
            if (code >= 2) {
                if (code < 5) {
                    r = IsWarpEntryAvailable((WarpPage*)self, 1, 0, 0);
                } else if (code < 8) {
                    r = IsWarpEntryAvailable((WarpPage*)self, 9, 0, 0);
                }
            }
            break;
        }
    }
    return r;
}

// Starts the warp page object: sets its flag bits, links itself into the map screen list, and picks
// its slot from its id (0x1C7 to 1, 0x1C8 to 2, 0x1C9 to 3, 0x1C6 to 4, 0x1CA to 5, else the
// current level index), registering itself there.
void StartWarpPage(WarpPage* o) {
    StartPlacedObject(o);
    o->flags = (o->flags & ~(3UL << 40)) | (1UL << 40);
    if (g_saveData->levelIndex) {
        u8* t = (u8*)&g_mapScreenList;
        ((PtrP*)&((WarpPageList*)t)->current)->v = o;
    }
    switch (o->id) {
    case 0x1C7: o->slot = 1; break;
    case 0x1C8: o->slot = 2; break;
    case 0x1C9: o->slot = 3; break;
    case 0x1C6: o->slot = 4; break;
    case 0x1CA: o->slot = 5; break;
    default: o->slot = g_saveData->levelIndex; break;
    }
    g_mapScreenList.nodes[o->slot] = o;
}

// After loading a warp page: resolves its links, starts its child objects, gives each of its 11
// entries a random phase (0 to 2 pi) and speed (0.5 to 0.7) for its idle motion and clears its dim
// values, and sets selected to -1.
void PostLoadWarpPage(WarpPage* self)
{
    ListFrame it;
    BaseObject* node;
    WarpEntry* el;
    s32 i;

    PostLoadPlacedObject(self);
    ResolveObjectLinks(self, 0x34, g_warpPageLinks);
    BeginPageWalk::Of(&it, &self->children);
    while ((node = NextPageNode::Of(&it)) != 0) {
        ResolveAndStartObject(node);
    }
    el = self->entries;
    for (i = 0; i < 11; i++) {
        f32 zero = 0.0f;
        el->dimTarget = zero;
        el->dim = zero;
        el->phase = RandomFloatInRange(zero, 6.2831855f);
        el->speed = RandomFloatInRange(0.5f, 0.7f);
        el++;
    }
    self->selected = -1;
    g_activeListFrames = it.prev;
}

// Shows the caption text for entry value (the fourth entry for 10, none for 9 and up) and makes
// value the selected entry.
void SelectWarpPageEntry(WarpPage* self, s32 value)
{
    if (value == 10) {
        SetElementTextFromEntry(&g_copiedTextCaption, 0, 4);
    } else {
        CopiedTextCaption* base = &g_copiedTextCaption;
        s32 t = value < 9;
        s32 idx = t ? value : -1;
        SetElementTextFromEntry(base, self->slot, idx);
    }
    SetWarpPageSelectedEntry(self, value);
}

// Stores the warp entry and its at-end flag that the warp page's confirm step reads and clears; the
// first argument is unused.
void SetPendingWarpEntry(s32 unused, s32 a, s32 b)
{
    g_pendingWarpEntry = a;
    g_pendingWarpEntryAtEnd = b;
}

// If a warp entry is pending, shows the letterbox and the entry's caption text, starts the entry's
// animation (at its start or its end) on the page, wakes the objects its close animation starts,
// and clears the pending entry.
void AnnouncePendingWarpEntry(WarpPage* self)
{
    if (g_pendingWarpEntry == -1) return;
    SetScreenElementHoldTime(&g_letterboxElement, ((g_saveData->levelIndex << 8) | g_saveData->entryIndex) == 4 ? 0.5f : 2.0f);
    g_letterboxElement.vt->m16(&g_letterboxElement, 2);
    CopiedTextCaption* e = &g_copiedTextCaption;
    e->pending = 0;
    e->vt->m16(e, 0);
    SetElementTextFromEntry(e, g_saveData->levelIndex, g_saveData->entryIndex);
    e->announce = 1;
    SetScreenElementHoldTime(e, 0.0f);
    e->vt->m16(e, 2);
    Animation* sl = self->entries[g_pendingWarpEntry].animation;
    if (sl != 0) {
        f32 f = 0.0f;
        if (g_pendingWarpEntryAtEnd == 0) f = sl->length;
        ReplaceAnimationPlayer(sl, self, 0, (AnimationPlayer**)&self->entryPlayer, f, 0.0f);
    }
    if (self->closeAnimation != 0) {
        for (s32 i = 0; i < self->closeAnimation->startCount; i++) {
            AnimEvent* en = &self->closeAnimation->startList[i];
            if (en->kind == 10) {
                BaseObject* n = FindFirstObjectById(self->world, 0x104, en->a8.i, self);
                if (n != 0) n->desc->m02(n);
            }
        }
    }
    g_pendingWarpEntry = -1;
}

void UpdatePlacedObject(PlacedObject* self, f32 f);
void StopAnimationPlayer(AnimationPlayer* self);

// Every frame: by mode, closes the page's animations (0), moves the highlight to the cursor's
// entry (2) or plays the opening of the chosen one (3); then eases every entry's values.

void UpdateWarpPage(WarpPage* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
    switch (self->mode) {
    case 0:
        if (self->closePlayer != 0) {
            StopAnimationPlayer(self->closePlayer);
            self->closePlayer = 0;
        }
        if (self->entryPlayer != 0) {
            StopAnimationPlayer((AnimationPlayer*)self->entryPlayer);
            self->entryPlayer = 0;
        }
        if (self->closePlayer == 0 && self->entryPlayer == 0) {
            self->desc->m03(self);
        }
        break;
    case 2:
        if (self->lastCursor != self->cursor) {
            SelectWarpPageEntry(self, self->cursor);
            if (IsWarpEntryAvailable(self, self->lastCursor, 0, 0) != 0) {
                self->entries[self->lastCursor].cursorLevel = 0.0f;
            }
            if (IsWarpEntryAvailable(self, self->cursor, 0, 0) != 0) {
                self->entries[self->cursor].cursorLevel = 1.0f;
            }
            self->entries[9].cursorLevel = self->entries[1].cursorLevel;
            self->lastCursor = self->cursor;
        }
        *(u128*)&self->smoothPoint = ApproachPointWithRamp(*(u128*)&self->smoothPoint, *(u128*)&self->targetPoint, g_gameClock.step,
                                                     (RampProfile*)g_warpPointRamp, 0);
        break;
    case 3:
        if (self->lastCursor != self->cursor) {
            if (self->warpChosen == 0) {
                SelectWarpPageEntry(self, self->cursor);
                SetScreenElementHoldTime(&g_copiedTextCaption, 0.0f);
                g_copiedTextCaption.vt->m14(&g_copiedTextCaption);
            }
            // Read as a 64-bit value: GCSE then does not take this read for the later
            // `target = self->cursor`, which retail loads again (docs/TOOLCHAIN.md, "GCSE").
            s64 cursor = self->cursor;
            s32 back = 0;
            if (cursor != 1 || self->warpChosen != 0) {
                back = 1;
            }
            s32 target;
            if (back != 0) {
                target = self->cursor;
            } else {
                target = GetCurrentWarpEntry();
            }
            Animation* anim = self->entries[target].animation;
            if (D_00275BF0 != 2) {
                self->entries[GetCurrentWarpEntry()].cursorLevel = 0.0f;
                self->entries[self->cursor].cursorLevel = 1.0f;
                self->entries[self->cursor].availableLevel = 1.0f;
                self->entries[9].cursorLevel = self->entries[1].cursorLevel;
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
                ReplaceAnimationPlayer(anim, self, 1, (AnimationPlayer**)&self->entryPlayer, start, rate);
                SetPendingWarpEntry((s32)self, target, back);
            }
            self->warpChosen = 0;
            self->lastCursor = self->cursor;
        }
        break;
    }
    if (self->mode != 0) {
        for (s32 i = 0; i < 11; i++) {
            WarpEntry* e = &self->entries[i];
            e->dim = ApproachValueWithRamp(e->dim, e->dimTarget, g_gameClock.step, (RampProfile*)g_warpDimRamp, 0);
            e->phase = WrapAngle(e->phase + e->speed * g_gameClock.step);
            PlacedObject* a = (PlacedObject*)e->availableObject;
            PlacedObject* b = (PlacedObject*)e->cursorObject;
            if (a != 0) {
                a->rampNode->level = ApproachValueWithRamp(a->rampNode->level, e->availableLevel, dt,
                                                       (RampProfile*)(self->openKind == 2 ? g_warpLevelRampKind2 : g_warpLevelRamp), 0);
            }
            if (b != 0) {
                b->rampNode->level = ApproachValueWithRamp(b->rampNode->level, e->cursorLevel, dt,
                                                       (RampProfile*)(self->openKind == 2 ? g_warpLevelRampKind2 : g_warpLevelRamp), 0);
            }
        }
    }
}

// Slot 0xA0 of the warp page: builds the page's transform with the camera zoom forced to 1.0 so the
// page ignores the zoom, applies it, then restores the camera's zoom and zoom goal.
void ApplyWarpPageTransform(WarpPage* obj, u8* s, void* c)
{
    // a stack buffer used as two record types
    u8 tmp[0x50];
    Camera* p = g_camera;
    f32 keep1 = p->zoom;
    f32 keep2 = p->zoomGoal;
    SnapCameraZoom(p, 1.0f);
    BuildPlacedObjectTransform(obj, (Quad16*)c, (ScaledTransform*)tmp);
    BuildMatrixFromRotationAndTranslation((const Vec4*)((Camera*)s)->position, (const Mat3*)&((Camera*)s)->rot80, (Mat4A*)tmp);
    ApplyPlacedObjectTransform(obj, (Camera*)s, (ScaledTransform*)tmp);
    SnapCameraZoom(g_camera, keep1);
    g_camera->zoomGoal = keep2;
}

// Handles notifications after the base handler: for message 5 (an animation finished) it moves on
// by the page's mode: from 1 to the mode it was opened with, from 3 to screen fade mode 2, and from
// 4, when the close player is the one that finished, ends the fade (if it was in mode 3) and sets
// the page to mode 0.
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
    SetWarpPageMode(self, self->openKind);
    return;
L_three:
    SetScreenFadeMode(&g_screenFade, 2);
    return;
L_four:
    if ((AnimationPlayer*)msg != self->closePlayer) return;
    ScreenFade* g = &g_screenFade;
    if (g->mode == 3) {
        SetScreenFadeMode(g, 0);
    }
    SetWarpPageMode(self, 0);
}

// Switches the warp page's mode (nothing if unchanged): leaving 1 or 4 stops its sound, leaving 2
// hides the caption and clears dim targets, leaving 0 turns the page on and sets each entry's
// available and cursor levels (and ramp nodes) for the reachable entries and the one under the
// cursor. Then it sets up the new mode.
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
        StopSoundRecord((PlayingSound*)self->sound, 0);
        break;
    case 2:
        if (self->warpChosen == 0) {
            g_copiedTextCaption.vt->m15(&g_copiedTextCaption);
        }
        for (s32 k = 0; k < 11; k++) {
            self->entries[k].dimTarget = 0;
        }
        break;
    case 0: {
        f32 one = 1.0f;
        self->desc->m02(self);
        for (s32 n = 0; n < 11; n++) {
            WarpEntry* s = &self->entries[n];
            if (IsWarpEntryAvailable(self, n, (s32*)0, (s32*)0)) {
                s->availableLevel = one;
                s32 want;
                if (self->openKind == 3) {
                    want = GetCurrentWarpEntry();
                } else {
                    want = self->cursor;
                }
                if (n == want) {
                    s->cursorLevel = one;
                } else {
                    s->cursorLevel = 0;
                }
            } else {
                s->cursorLevel = 0;
                s->availableLevel = 0;
            }
        }
        self->entries[9].cursorLevel = self->entries[1].cursorLevel;
        for (s32 j = 0; j <= 10; j++) {
            WarpEntry* s = &self->entries[j];
            PlacedObject* a = (PlacedObject*)s->availableObject;
            PlacedObject* b = (PlacedObject*)s->cursorObject;
            if (a) {
                a->desc->m02(a);
                EnsureObjectWorldNode(a);
                a->rampNode->rate = 0;
                a->rampNode->level = s->availableLevel;
            }
            if (b) {
                b->desc->m02(b);
                EnsureObjectWorldNode(b);
                b->rampNode->rate = 0;
                b->rampNode->level = s->cursorLevel;
            }
        }
        break;
    }
    }
    switch (next) {
    case 1: {
        if (self->openKind == 3) {
            s32 ne = self->cursor != 1;
            Animation* a;
            s32 off;
            if (ne) {
                off = self->cursor * 52;
            } else {
                off = GetCurrentWarpEntry() * 52;
            }
            // address arithmetic over a variable index
            a = *(Animation**)((u8*)self + off + 0x2F8);
            if (a) {
                f32 fa = 0;
                if (ne) {
                    fa = a->length;
                }
                ReplaceAnimationPlayer(a, self, 0, (AnimationPlayer**)&self->entryPlayer, fa, 0.0f);
            }
        } else {
            Animation* a = self->entries[1].animation;
            if (a) {
                ReplaceAnimationPlayer(a, self, 0, (AnimationPlayer**)&self->entryPlayer, 0.0f, 0.0f);
            }
            f32 z = 0.0f;
            SetWarpPageSelectedEntry(self, self->cursor);
            self->smoothPoint = self->targetPoint;
            SelectWarpPageEntry(self, self->cursor);
            SetScreenElementHoldTime(&g_copiedTextCaption, z);
            g_copiedTextCaption.vt->m14(&g_copiedTextCaption);
            StartSoundEffect(0x8A, (PlayingSound**)&self->sound, 0, 0, 3000.0f, 300.0f, 1.0f, z, z, 0, 0);
            for (i = 0; i < 11; i++) {
                WarpEntry* s = &self->entries[i];
                s32 r = IsWarpEntryReachable(self, i);
                s->reachable = r;
                s32 v = 0;
                if (r != 0 && ((u32)(i - 2) < 6 || i == 0)) {
                    v = 1;
                }
                s->brightColors = v;
                s->dim = s->dimTarget = 0.0f;
            }
        }
        self->lastCursor = self->cursor;
        t = self->openAnimation;
        if (t != 0) {
            goto L146C;
        }
        goto Lz;
    }
    case 4: {
        if (self->warpChosen == 0) {
            g_copiedTextCaption.vt->m15(&g_copiedTextCaption);
            if (self->openKind == 2) {
                StartSoundEffect(0x8B, (PlayingSound**)&self->sound, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
        AnnouncePendingWarpEntry(self);
        t = self->closeAnimation;
        if (t == 0) {
            goto Lz;
        }
    L146C:
        ReplaceAnimationPlayer(t, self, 0, &self->closePlayer, 0.0f, 1.0f);
        self->mode = next;
        goto L1550;
    }
    case 2:
        for (s32 m = 0; m < 11; m++) {
            if (m != self->selected) {
                self->entries[m].dimTarget = 1.0f;
            }
        }
        self->mode = next;
        goto L1550;
    case 3:
        self->lastCursor = -1;
        break;
    case 0:
        for (i = 0; i < 11; i++) {
            PlacedObject* a = (PlacedObject*)self->entries[i].availableObject;
            PlacedObject* b = (PlacedObject*)self->entries[i].cursorObject;
            if (a) {
                if (a->rampNode) {
                    RemoveObjectNodeFromWorld(a->rampNode);
                }
                a->desc->m03(a);
            }
            if (b) {
                if (b->rampNode) {
                    RemoveObjectNodeFromWorld(b->rampNode);
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

// Moves the warp page's cursor: in modes 0 and 4 it stores the cursor and the open kind and enters
// mode 1; in mode 2 it stores the cursor and enters mode 3 when the kind is 3.
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
    self->openKind = a2;
    SetWarpPageMode(self, 1);
    return;
L_two:
    self->cursor = a1;
    if (a2 == 3) {
        SetWarpPageMode(self, 3);
    }
}

// Starts closing the warp page (mode 4) when it is in mode 1 or 2.
void BeginWarpPageClose(WarpPage* self)
{
    s32 v = self->mode;
    if (v < 3) {
        if (v > 0) {
            SetWarpPageMode(self, 4);
        }
    }
}

// Moves the warp page's cursor in direction idx (an index of the page's neighbour table) to the
// next reachable entry (skipping the unreachable ones) and plays the move sound, or the refuse
// sound if there is none or no table.
void MoveWarpCursor(WarpPage* self, s32 idx)
{
    s32 (*table)[4] = g_warpCursorTables[self->slot];
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

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);

// Gives in out the screen position (in 640x492.8 pixel units) of one of an entry's two anchor
// objects (picked by flag): its point is taken into the camera's view and projected; the screen
// centre if the entry has no such object.
void ProjectWarpEntryToScreen(WarpPage* self, s32 idx, s32 flag, f32* out)
{
    Vec4 v;
    BaseObject* o;
    if (flag != 0) {
        o = (BaseObject*)self->entries[idx].secondAnchor;
    } else {
        o = (BaseObject*)self->entries[idx].firstAnchor;
    }
    if (o != 0) {
        TransformPointBetweenFrames((PlacedObject*)o->parent, self, (Vec4*)&((TransformObject*)o)->pos, &v);
        Camera* g = g_camera;
        Vu0::Q(v) = Vu0::Rotate(g->rotation, Vu0::Q(v));
        Vu0::Q(v) = Vu0::Add(Vu0::Q(g->position), Vu0::Q(v));
        ProjectPointToCamera(g, &v, out);
        out[0] = out[0] * 320.0f + 320.0f;
        out[1] = out[1] * -246.40001f + 246.40001f;
    } else {
        out[0] = 320.0f;
        out[1] = 246.40001f;
    }
}

// Makes idx the selected warp page entry: stores the entry's placement relative to the page (or the
// identity) at +0x550, zeroes its float and sets the previous selection's float to 1.0.
void SetWarpPageSelectedEntry(WarpPage* self, s32 idx) {
    // a field access here changes retail's code (it works on selected, entries[].f14 and dimTarget, targetPoint)
    u8* base = (u8*)self;
    if (*(s32*)(base + 0x534) == idx) {
        return;
    }
    BaseObject* r = *(BaseObject**)(base + idx * 0x34 + 0x30C);
    if (r != 0) {
        TransformPointBetweenFrames((PlacedObject*)r->parent, self, (Vec4*)&((TransformObject*)r)->pos, (Vec4*)((base + 0x550)));
    } else {
        *(Quad16*)(base + 0x550) = *(Quad16*)&g_zeroVector;
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

extern const char g_warpMenuHint[40] = "&2T&. : Back\n&2(&. : Move\n&2X&. : Warp";
void InitWarpMenu(WarpPageList* self) {
    SetupScreenElementText(self);
    if (IsFontLoaded(2) != 0) {
        self->frame = (Font**)&g_warpTextStyle;
        *self->frame = GetFontById(2);
    }
    SetScreenElementHoldTime(self, 0.0f);
    SetScreenElementScale(self, 0.6f);
    self->color = 0xDF7F7F7F;
    self->vt->m08(self, g_warpMenuHint);
    self->current = 0;
    FillMemory(self->nodes, 0, 0x18);
}

void HandleWarpMenuInput(WarpPageList* self, PadRecord* t)
{
    s32 loc[2];
    s32 s3;
    s32 s2;
    s32 v1;

    if (self->current == 0) return;
    if (self->current->mode != 2) return;
    if (self->current->warpChosen != 0) return;
    if ((t->flags & 0x910) != 0 || t->connectionMode == 1) {
        PopStackElement((ElementStack*)g_elementStack);
        ClearPadPressedBits(&g_padRecord, 0x910);
        return;
    }
    if (self->mode != self->current->mode) return;

    s3 = IsWarpEntryAvailable(self->current, self->current->cursor, &loc[0], &loc[1]);
    s2 = GetPadHorizontalStep(t);
    v1 = GetPadVerticalStep(t);
    t->nextStepTimeX = g_gameClock.elapsed + t->stepDelayX;
    t->nextStepTimeY = g_gameClock.elapsed + t->stepDelayY;

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
                self->current->warpChosen = 1;
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
        self->scaleTarget = g_scaleTargetSmall;
    }
    self->scale = ApproachValueWithRamp((RampProfile*)g_warpLevelRampKind2, 0, self->scale, self->scaleTarget, g_gameClock.step);
}

void SetWarpMenuOpen(WarpPageList* self, s32 a1)
{
    if ((a1 != 0) != (self->open == 0)) return;
    if (a1 != 0) {
        HideScreenElements();
        s32 r = GetCurrentWarpEntry();
        if (r == 10) {
            r = (IsWarpEntryAvailable(self->current, 1, 0, 0) != 0);
        }
        SetWarpCursor(self->current, r, 2);
        self->scaleTarget = 1.0f;
        self->scale = 1.0f;
        Animation* an = self->current->openAnimation;
        if (an != 0) {
            SetScreenElementSlideInTime(self, an->length);
        }
        GameProgress* g = g_saveData;
        if (((g->levelIndex << 8) | g->entryIndex) == 0x308) {
            PauseStagedBankVoice();
        }
        self->vt->m14(self);
        SetPadSelectFlags(1);
        ResetPadStepRepeat(&g_padRecord);
        SetElementStackState((ElementStack*)g_elementStack, 7);
    } else {
        self->vt->m15(self);
        if (self->current->warpChosen == 0) {
            BeginWarpPageClose(self->current);
            Animation* an = self->current->closeAnimation;
            if (an != 0) {
                SetScreenElementSlideOutTime(self, an->length);
            }
            ClearPadSelectFlags(1);
            SetElementStackState((ElementStack*)g_elementStack, 3);
            GameProgress* g = g_saveData;
            if (((g->levelIndex << 8) | g->entryIndex) == 0x308) {
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

void DrawTriangleGroups(ColoredTriangleSet* self, f32 a, f32 b, f32 c, f32 d);
extern "C" f32 Sine(f32 x);
u32 GetEntryFlags(s32 id);
void PushFontScale(Font* font, f32 x, f32 y);
struct Font;
struct PacketWriter;
struct StringLayout;
struct Vec4U;
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);
void PopFontScale(Font* font);
extern f32 g_warpCircleScale;
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

// The text layout DrawFontString reads (TextBoxLayout's fields), filled through its setters.
struct WarpLabelLayout;
#ifdef VERSION_EU
void SetTextLayoutVerticalPlacement(WarpLabelLayout* self, s32 f);  // only PAL has this setter
#endif
struct WarpLabelLayout {
    f32 x, y;
    f32 w, h;
    s32 color;
    s32 f14;
    void* f18;
    void Pos(f32 x_, f32 y_) { ((TextBoxLayout*)this)->Pos(x_, y_); }
    void Size(f32 x_, f32 y_) { ((TextBoxLayout*)this)->Size(x_, y_); }
    void Color(s32* c) { ((TextBoxLayout*)this)->Color(c); }
    void FlagA(s32 f) { ((TextBoxLayout*)this)->SetF14(f); }
    void FlagB(s32 f) { ((TextBoxLayout*)this)->SetF18(f); }
#ifdef VERSION_EU
    void FlagC(s32 f) { SetTextLayoutVerticalPlacement(this, f); }
#endif
};


void DrawWarpMenu(WarpPageList* self)
{
    if (self->current == 0) {
        return;
    }
    f32 one = 1.0f;
    Camera* cam = g_camera;
    f32 keep1 = cam->zoom;
    f32 keep2 = cam->zoomGoal;
    SnapCameraZoom(cam, one);
    if (g_coloredTriangleSet != 0) {
        Vec4 v;
        f32 out[2];
        WarpColor inner;
        WarpColor outer;
        f32 b2 = self->blend * self->blend;
        Vu0::Q(v) = Vu0::Q(self->current->smoothPoint);
        Camera* g = g_camera;
        Vu0::Q(v) = Vu0::Rotate(g->rotation, Vu0::Q(v));
        Vu0::Q(v) = Vu0::Add(Vu0::Q(g->position), Vu0::Q(v));
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
        DrawTriangleGroups(g_coloredTriangleSet, out[0], out[1], s * 0.2f + one, b2);
    }
    for (s32 i = 0; i < 11; i++) {
        WarpEntry* e = &self->current->entries[i];
        if (e->reachable == 0) {
            continue;
        }
        WarpColor c0, c1, c2;
        if (e->brightColors != 0) {
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
        f32 size = e->dim * self->blend;
        if (AreFloatsNearlyEqual(size, 1.0f, 0.0001f) && i < 9) {
            s32 slot = self->current->slot;
            if ((GetEntryFlags((slot << 8) | i) & 2)
                && !(*(s32*)((u8*)g_saveData + (slot * 0x44C + i * 0x78) + 0x10) & 2)) {
                size = Sine(g_gameClock.elapsed * 20.0f) * 0.2f + 0.8f;
            }
        }
        WarpColor a = c0;
        WarpColor b = c1;
        DrawColoredCircle(pos[0], pos[1], size * g_warpCircleScale, e->phase, 14, (s32*)&a, (s32*)&b, 3);
        b = c0;
        a = c1;
        DrawColoredCircle(pos[0], pos[1], size * g_warpInnerCircleScale, -e->phase, 10, (s32*)&b, (s32*)&a, 3);
        if (i < 9) {
            s32 slot = self->current->slot;
            if (GetEntryFlags((slot << 8) | i) & 2) {
                f32 scale = e->dim;
                s32 flags = *(s32*)((u8*)g_saveData + (slot * 0x44C + i * 0x78) + 0x10);
                Font* font = GetFontById(3);
                f32 k = g_warpLabelFontScale[0] * scale;
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
                DrawFontString(font, (flags & 2) ? "k" : "l", (StringLayout*)&L, 0, &g_gsPacketWriter);
                PopFontScale(font);
            }
        }
    }
    SnapCameraZoom(g_camera, keep1);
    g_camera->zoomGoal = keep2;
}

// The style above (D_00276620) and D_00276650 are built by the static initialiser GCC writes
// here (func_001F2688), and its _GLOBAL_$I$ (func_001F2738) follows the 12 bytes the linker left
// of a function this file wrote out after it (tools/compile.py moves the block there).
LINKER_REMNANT_AFTER_INIT(func_001F2728);
