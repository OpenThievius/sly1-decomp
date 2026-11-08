// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "sound_record.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"
#include "buffered_stream.h"
#include "object_event.h"
#include "key_record.h"
#include "key_id.h"
#include "base_object.h"
#include "fpu.h"
#include "asm_func.h"
#include "point_object.h"
#include "id_linked_object.h"
#include "game_progress.h"
#include "shapes.h"
#include "property_descriptor.h"
#include "vu0.h"
#define VA_ARG_WORD(ap, T) (*(T*)((ap += 8) - 8))

f32 RandomFloatInRange(f32 a, f32 b);
f32 Cosine(f32 a);
f32 Sine(f32 a);
f32 ArctangentOfRatio(f32 a, f32 b);
extern f32 g_gameTime[];
s32 IsObjectDescendantOf(Collider* e, void* b);
void ReleaseSoundLevel(void* p);
void TriggerScriptEvent(StateGraph* host, s32 a, s32 b, void** args);
s32 ReadBufferedU16(void* a);
void* AllocateZeroedFrontMemory(s32 size);
void FillMemory(void* p, int zero, s32 count);
void AddColliderToSweepAxes(void* owner, void* self);
Contacts03* TakeContactTable(void* owner, void* self);
void InitContactPairFlags(void* owner, void* self);
void AppendToList(void* p, void* self);
void RegisterPlacedObject(void* self);
void SetColliderPartListed(Collider* self, s32 flag);
void UpdateAnchorModeFlags(void* p);
void ResolveContactHandler(void* self);
void UnregisterPlacedObject(void* self);
void RemoveColliderFromSweepAxes(void* owner, void* self);
void ReleaseContactTable(void* owner, Contacts03* contacts);
void RemoveFromList(void* p, void* self);
void FreeTouchNodes(void* owner, Touch03* list);
void ClearRootObjectStateBits(void* owner, void* self, s32 n);
void RemoveFromList(void* a, void* b);
void PushFreeSlot(void* a, void* b);
void TriggerScriptEvent(void* a, s32 b, s32 c, s32 d);
void SetListLinkOffset(void* self, s32 value);
void InitPlacedObject(void* self);
void ClearRecordBody(Mesh03* mesh);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
s32 LookupScriptVariable(void* a, s32 b, s32 c, ScriptValue* d);
void StartPlacedObject(void* self);
void* AllocateFrontMemory(s32 size);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void UpdatePlacedObject(void* self);
void* CreateStateWalker(void* bank, s32 r, s32 minus_one, s32 zero);
void AppendToList(List01* list, StateWalker* item);
void TriggerScriptEvent(StateGraph* self, s32 a, s32 b, void* c);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(u32 bytes);
struct RandomRangeLow { s32 v; };
s32 RandomIntInRange(RandomRangeLow lo, s32 hi);
void* AllocateBackMemory(s32 size);
void RecomputePlacedObjectFrame(Collider* self);
void ClearRootObjectStateBits(void* a, void* b, s32 c);
void SetPlacedObjectVelocity(PlacedObject* self, Vec02* v);
void SetPlacedObjectSpin(PlacedObject* self, Vec02* v);
void UpdateWorldContacts(World* w, s32 arg);
void MarkSweepAxesUnsorted(void* a);
void DropColliderContacts(Collider* self, s32 value);
void InitContactPairFlags(void* a, void* b);
s32 ScriptListContainsValue(s32 value, void* out);
s32 AppendPropertyToScriptList(s32 value, void* out);
void ConstrainColliderVector(void* a, void* b, void* c, void* d, s32 e);
void AddColliderForce(void* a, void* b);
void DrawPlacedObject(Collider* self, void* a, void* m);
// What a vector is constrained by: an axis, and how (0 none, 1 the part along the axis removed,
// 2 only the part along it kept, 3 zero).
struct VectorConstraint {
    Vec02 axis;             // 0x00
    s32 kind;               // 0x10
};
void ConstrainVectorByAnchor(VectorConstraint* c, Vec02* in, Vec02* out, Vec02* rem);
void ClearRootTries(void* self);
// A quadword passed by value in one register (func_001B8820's position).
typedef u64 Qword128 __attribute__((mode(TI)));
void ComputePlacedObjectWorldFrame(void* self);
void TransformMeshToWorld(Mesh03* a, Mesh03* b, Qword128 q, Mat02* c);
void TransformDirectionBetweenFrames(void* a, void* b, void* c, void* d);
void ReparentPlacedObject(void* self, void* p);
s32 IsObjectDescendantOf(void* e, void* b);
void SendObjectNotification(void* self, s32 kind, void* arg);
// An anchor preset (func_001BB028): a direction and a mode.
struct AnchorPreset { const Vec02* quad; s32 value; };
extern AnchorPreset D_002746E0[8];
void* AllocateBackMemory(s32 n);
s32 GetContactRowHead(void* self, void* other);
// Matched by indexing the end as (u32)e + (i << 6).

void TriggerScriptEvent(void* self, s32 a, s32 b, void* c);
void FreeTouchNodes(void* pool, Touch03* m);
Touch03* AllocateTouchNode(void* pool);
void CopyPlacedObject(Collider* self, Collider* other);
void CopyMeshTransformed(Mesh03* a, s32 b, Mesh03* c);
void CloneTreeNodes(Mesh03* a, Tree03* b, Mesh03* c, Tree03* d);
// NEAR: 14 lines: retail preloads f400/f40C into s0 (lw s0 before loop and in the bnel delay slot), we load into v1; f408 loop test reload; last loop pointer s2 vs index


s32 ReadBufferedU8(BufferedStream* in);
void func_00137FB0(BufferedStream* in, Mesh03* p);
void ReadFaceTree(BufferedStream* in, Mesh03* a, Tree03* out);
f32 ReadBufferedFloat(BufferedStream* in);
void ReadBufferedRotation3(BufferedStream* in, Mat02* p);
void ReadBufferedVector3(BufferedStream* in, Vec02* p);
void ComputeColliderInverseInertia(Collider* self, f32 x);
void CopyBytes(void* dst, void* src, s32 n);
void BuildMatrixFromRotationAndTranslation(void* a, void* b, void* out);
void func_001BBC38(Collider* self);
s32 InvertMatrix3x3(Mat02* in, Mat02* out);
s32 ReadBufferedU16(BufferedStream* in);
s32 ReadBufferedS16(BufferedStream* in);
s32 ReadBufferedU32(BufferedStream* in);
void LoadPlacedObject(Collider* self, BufferedStream* in);
void InitContactPairFlags(void* a, Collider* b);
// What class 0x03's slot 69 (func_001B9F30) writes of a collider.
struct ColliderPose {
    s32 f00;                // 0x00: 0
    u8 pad04[0x0C];
    Vec02 position;         // 0x10: v140
    Vec02 v150;             // 0x20
    f32 heading;            // 0x30: from the first row of the matrix
    f32 f34;                // 0x34: 100.0
    f32 time;               // 0x38: g_gameTime
    s32 f3C;                // 0x3C: 0
};
void RotateMatrixUpright(Mat02* m, s32 zero, Vec02* out);
void FreePooledContactChain(void* pool, Contact03* head);
extern s32 g_streamVoiceLocked;
void StopStreamVoice(void);
extern s32 g_stagedBankVoice;
void RequestStagedBank(void* self);
s32 PollIopCommands(void);
void SyncDataCache(s32 a);
s32 StartSoundVoice(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void RemoveFromList(u8* a, void* b);
void PushFreeSlot(u8* a, void* b);
extern u8 g_soundBankHandles[];
void FillMemory(u8* p, s32 a, s32 b);
void InitIopCommandChannels(void);
s32 EnsureSoundBankLoaded(s32 a);
s32 EnableIopDiscAccess(s32 a, s32 b, s32 c, s32 d);
void SendIopSoundLevel(s32 a);
void ResetVolumeChannelFactors(void);
void func_0011D520(s32 a, s32 b);
void func_0011D558(s32 a, s32 b, s32 c);
void func_0011E3A0(s32 a, s32 b);
void* PopFreeSlot(void* p);
void FillMemory(void* p, s32 zero, s32 size);
void AppendToList(void* list, void* item);
// A sound playing in the world: a 0x90-byte record of the pool at World 0x1BA0, kept on
// World::list1BAC. func_001BF6B8 takes one, func_001BF920 fills it, func_001BFAF8 starts its
// voice, func_001C0070 updates each one every frame and func_001BF728 gives it back.
struct PlayingSound {
    s32 entry;              // 0x00: its row of g_soundEntries, -2 for the stream voice
    s32 serial;             // 0x04: g_nextSoundRecordId when filled, checked by MarkSoundRecordIfIdMatches
    s32 bank;               // 0x08: the bank handle its voice starts from (StartSoundRecordVoice)
    PlayingSound** owner;   // 0x0C: the caller's pointer to it, cleared when it ends
    f32 startTime;          // 0x10: g_gameTime when its voice started
    f32 baseVolume;         // 0x14: the volume before distance; SetSoundRecordVolume rescales by it
    s32 voice;              // 0x18: the IOP voice handle, 0 while silent
    u8 pad1C[4];
    Quad16 position;        // 0x20: where it plays when it follows no object
    BaseObject* object;     // 0x30: the object it follows (its position at 0x140)
    f32 farRange;           // 0x34: beyond it the sound is silenced or ended (UpdateSoundEmitters)
    f32 nearRange;          // 0x38
    s32 keepWhenFar;        // 0x3C: silenced instead of ended out of range
    s32 silent;             // 0x40: no voice is playing
    s32 positional;         // 0x44: volume and pan follow the listener
    s32 finished;           // 0x48: its voice has ended (MarkSoundRecordIfIdMatches sets it)
    u8 pollTick;            // 0x4C: frames to the next end-of-voice query, modulo 4
    f32 volume;             // 0x50
    f32 pan;                // 0x54
    f32 pitch;              // 0x58: in octaves, 1524 units each (SetSoundRecordPitch)
    f32 f5C;                // 0x5C
    s32 pitchOffset;        // 0x60: added to the pitch (SetSoundRecordPitch)
    U64P link;              // 0x64: kept when InitSoundRecord clears the record
    s32 pitchBaseValid;     // 0x6C
    s32 pitchBase;          // 0x70: the entry's pitch from GetSoundPitchBase, cached
    f32 nextTime;           // 0x74: when an ambient repeat plays next
    union { U64P bytes; f32 value; } interval;  // 0x78: the ambient repeat interval, < 0 for none
    union { U64P bytes; f32 value; } f80;       // 0x80
    u8 pad88[8];
    s32 Clamp(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) {
            return lo;
        }
        if (hi < v) {
            return hi;
        }
        return v;
    }
};
void RemoveFromList(u8* p, PlayingSound* self);
void PushFreeSlot(u8* p, PlayingSound* self);
void FreeSoundRecord(PlayingSound* self);
void* FillMemory(PlayingSound* p, s32 v, s32 n);
void FadeOutSoundVoice(s32 voice, s32 a, s32 b, s32 c);
void ApplySoundRecordVolumePan(PlayingSound* self);
void func_001BBEB8(Collider* self, f32 dt);
void MovePlacedObject(Collider* self, f32 x, void* b);
void func_001BC0E0(void* a0, f32 x, void* a1, void* a2);
void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
void PauseIopVoice(s32 a);
void ResumeIopVoice(s32 a);
void AppendToList(u8* a, void* b);
// A request for a sound level: a 12-byte record of the pool at World::pool1BB8, kept on
// World::list1BC4 (func_001BEEF8 makes one). The highest level among them is the current one
// (func_001BEF88); the IOP is sent the level plus 20.
struct SoundLevelEntry {
    s32 level;              // 0x00: -20 to 0x6B (PushSoundLevel)
    u8 pad4[8];
};
extern s32 D_002748EC;
extern s32 g_currentSoundLevel;
extern s32 g_previousSoundLevel;
void RemoveSoundLevelEntry(void* self);
void RecomputeSoundLevel(void* self);
typedef signed int s32;
typedef unsigned char u8;
extern s32 g_stagedBankState;
extern s32 g_stagedBankHandle;
void UnloadSoundBank(s32 handle);
void StopSoundVoice(s32 handle);
void RemoveSoundLevelEntry(SoundLevelEntry* self);
void RecomputeSoundLevel(SoundLevelEntry* self);
extern s32 g_streamVoice;
// How far the listener is from a position (func_001BF2E0 or func_001BF398, as func_001BF578 chooses).
typedef f32 (*ListenerDistanceFn)(void* listener, void* position);
s32 IsTopCameraController(u8* p);
s32 PeekStackValue(u8* s);
f32 MeasureListenerDistance(void* listener, void* position);
f32 MeasureCameraWeightedDistance(void* listener, void* position);
void* AllocateZeroedFrontMemory(s32 bytes);
extern s32 g_streamVoicePending;
// The comparison func_001BE0A8's heap sort orders its records by.
typedef s32 (*SortCompareFn)(void* a, void* b);
void SwapSortRecords(u8* base, s32 stride, s32 rowB, s32 rowA);
s32 HasStreamVoice(void);
void ClearKeyId(void* p);
s32 StartStreamedVoice(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
void ClearStreamVoicePending(void);
void RequestStreamCallback(s32 a0, void (*a1)(void), u64 a2);
void NotifyIopBanksChanged(void);
void* GetActiveSwitchedCollider(void);
f32 ComputeSoundListenerFactor(void* self);
void ComputeSoundVolumeAndPan(f32 r, void* self, f32* out, s32* flag, f32 a, f32 b, f32 c);
void SetVoiceVolumePan(s32 voice, s32 volume, s32 pan);
void StartSoundEffect(s32 a0, PlayingSound** a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void ClearSoundRecordHandle(PlayingSound** slot);
void StopStagedBankVoice(void);
void UnloadStagedBank(void);
s32 SyncDiscRead(s32 a);
void StoreStagedBankHandle(s32 h);
void StartSoundBankLoad(s32 a0, s32 a1, void* a2, s32 a3);
void CopyMemory(void* dst, void* src, s32 count);
s32 IsListEmpty(void* a);
void* AllocateSoundLevelEntry(void);
s32 IsVoiceBusy(s32 handle);
extern f32 g_gameClock[];
// The counts func_001BD678 fills for func_001BDD00 (its two lists of connected colliders).
struct ConnectedCounts { s32 pad; s32 n1; s32 n2; };
// What the update pass calls through slot 27 of a collider's class (func_001BDD00).
typedef void (*ColliderStepFn)(Collider* self, s32 a, f32 dt);
// The next object of World::list6C, at Collider::link414 read as one aligned word.
struct ListedCollider {
    u8 pad0[0x414];
    ListedCollider* next;
};
void PushBackMemoryMark();
void PopBackMemoryMark();
void CollectConnectedColliders(Collider* n, s32* c1, Collider** a1, s32* c2, Collider** a2);
void ProcessColliderGroup(World* ctx, s32 n, Collider** arr, f32 f, s32 flags);
s32 IsObjectTreeAtRest(Collider* n);
void ClearRootTries(Collider* n);
void QueryIopStreamVoice(s32 a0);
// A row of g_soundEntries (global_tables.cpp defines it): the bank a sound is in, -1 for none, and
// its index in that bank.
struct SoundEntry { s32 bank; s32 index; };
extern SoundEntry g_soundEntries[];
extern u8 g_soundBankLoaded[];
extern u8 g_soundEntryAvailable[];
s32 EnsureSoundEntryBankLoaded(s32 idx);
// NEAR: the lui of D_0026185C is scheduled before the sw of self->idx; retail stores idx first. Otherwise every instruction matches.

void ComputeSoundRecordDoppler(PlayingSound* self);
void SetSoundRecordPitch(PlayingSound* self, f32 x);
// NEAR: first load of the chain pointer lands in $v1 and the sum in $v0, retail has them in $v0/$v1; one instruction short so the final branch targets 0x1BF028 instead of 0x1BF02C

// NEAR: 23 diff lines, register allocation only: queue index in t1 (retail) vs v1 (ours), mask built in a0 vs a2, cleanup counter in t1 vs a0

s32 GetSoundPitchBase(s32 a, s32 b);
void SetVoicePitch(s32 x, s32 y);
extern const KeyRecord g_soundBankKeys[7];
void UnloadSoundBank(void);
void ClearKeyId(KeyId* p);
s32 WaitDiscReady(s32 a);
s32 LoadSoundBankAtLocation(s32 a, s32 b);
s32 TestSoundInBank(s32 a, s32 b);
s32 IsSoundEntryAvailable(s32 id);
void InitSoundRecord(PlayingSound* self, PlayingSound** owner, s32 a2, s32 a3, s32 a4, f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* a5, s32 a6);
void ScheduleAmbientSoundRecord(PlayingSound* self);
void StartSoundRecordVoice(PlayingSound* self, s32 id);
// The list walk of list_iter.h over a List01: push the frame, take each element, pop the frame.
struct ListWalk {
    static void Begin(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
    static u8* Next(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
    static void End(ListFrame* it) { g_activeListFrames = it->prev; }
};
Contact03* TakePoolSlot(u8* p);
void FreePooledContactChain(u8* a, Contact03* b);
s32 RandomIntInRange(s32 a, s32 b);
void ComputeSoundAttenuation(Quad16* position, f32* volume, f32* pan, f32 a, f32 b, f32 c);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
void CreatePooledContact(Collider* self, s32 a, Vec02* origin, Vec02* dir, s32 kind, s32 b, s32 c, Contact03** out, f32 z);
void NotifyContactEnds(World* world, s32 n, Contact03** list);
void SolveColliderGroupContacts(World* ctx, s32 n, Collider** arr, s32 v, Contact03** buf, f32 f, s32 ex);
void SetColliderForcedState(u8* node, s32 flag);
// The list walk of World::list1BAC, element by element.
struct PlayingSoundFrame : ListFrame {
    PlayingSound* Next() { PlayingSound* n = *(PlayingSound**)link; link = (u8*)n + offset; return n; }
};
s32 IsSoundEmitterUpdateDisabled(void);
void* GetSoundListenerPosition(void);
s32 IsVoiceBusy(ListFrame* h);
s32 IsObjectAttached(BaseObject* o);
void StopSoundVoice(s32 h);
void RequestVoiceCallback(s32 h, void (*fn)(void), s64 arg);
void MarkSoundRecordIfIdMatches(void);
void ComputeSoundVolumeAndPan(f32 r, void* pos, f32* volume, f32* pan, f32 a, f32 b, f32 c);
void StopSoundRecord(PlayingSound* self, s32 n);
void EnsureKeyedList(void* p);
s32 SetIopSoundOptionFlag(s32 flag);
extern U64P D_00274820;
extern U64P D_00274828;
extern s32 D_006053E0[];
s32 GetVoiceParam(s32 a, s32 b);
void UnregisterObject(void* self);
void RemoveFromList(void* table, void* self);
void SetCachedVoiceParam(s32 index, s32 value);
void DestroyStateWalker(s32 p);
s32 CreateStateWalker(s32 p, void* ctx, s32 a2, s32 a3);
void RegisterObject(void* self);
void AppendToList(void* table, void* self);
void CopyObjectData(void* self);
// An entry of World::f1EF4: an expression read from the level and the scope it was evaluated in
// (0 until func_001C13E8 evaluates it).
struct WorldScriptEntry { R11B008Node* expr; s32 scope; };
extern u8 g_markStacks[];
void AddUniqueMarkRoot(void* a, void* b);
void SetIopVolumeChannel(s32 a, s32 b);
extern s32 D_00274808[6];
void SetIopChannelValue(s32 a, s32 b);
void SetIopChannelValuePair(s32 a, s32 b, s32 c);
struct Point2 { f32 x; f32 y; };
extern f32 g_volumeChannelFactors[11][4];
void SetIopVolumeChannel(s32 slot, s32 value);
void ApplyVolumeChannelFactors(s32 column);
extern u8 D_002748E8[4];
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, void* a4, void* a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void StopAllIopSounds(void);
void WaitForIopSoundStop(s32 a0);
s32 SyncDiscRead(s32 flag);
void StopWorldSoundRecords(s32 a0);
void ClearSoundLevels(void);
void ClearCachedVoiceParams(void);
// A property's getter (PropertyDescriptor::getter with flags 4, or the method at that offset of
// the object's table): fills `out` with the value of `obj`.
typedef void (*PropertyGetter)(void* obj, void* out);
void WritePropertyValue(ScriptValue* self, void* a, void* b, ScriptValue* c);
// A DMA tag of a chain (two doublewords; func_001C2430 writes the first).
struct DmaTag { u64 lo; u64 hi; };
// The tags of the two transfers' chains (8 each, read uncached).
extern DmaTag D_00605440[8];
extern DmaTag D_006054C0[8];

// One of the two scratchpad transfer buffers (D_002748F0; D_00274990 picks the current one):
// func_001C2430 sends up to 8 blocks into the scratchpad by a DMA chain, func_001C25B0 sends
// them back to memory.
struct SprTransfer {
    DmaTag* tags;           // 0x00: the chain's tags
    s32 base;               // 0x04: the scratchpad address of the first block's tag
    u32 addrs[8];           // 0x08: each block's address, after its 16-byte tag
    s32 sizes[8];           // 0x28: each block's size, rounded up to 16
    s32 count;              // 0x48: the number of blocks
    s32 state;              // 0x4C: 1 sent in, 3 sending back (StartFromSprChain), 0 done
};

void* FillMemory(SprTransfer* p, s32 v, s32 n);

// Transfer i's record, cleared, with its tags read uncached (0x20000000) and its first tag's
// scratchpad address: the static initialiser (func_001C27B0) builds the two in a temporary and
// copies each into D_002748F0.
static inline SprTransfer MakeSprTransfer(s32 i)
{
    SprTransfer t;
    FillMemory(&t, 0, 0x50);
    t.tags = (DmaTag*)((u32)(i != 0 ? D_006054C0 : D_00605440) | 0x20000000);
    t.base = 0x70000000 + i * 0x2000;
    return t;
}
// The registers of the scratchpad DMA channels (g_fromSprChannel, g_toSprChannel) the code sets.
struct SprDmaChannel {
    s32 chcr;               // 0x00: its control register (bit 6 cleared or set)
    u8 pad4[0x7C];
    s32 sadr;               // 0x80: the scratchpad address
};
extern SprDmaChannel* g_fromSprChannel;
s32 WaitDmaChannel(SprDmaChannel* d, s32 b, s32 c);
void StartDmaChainToMemory(SprDmaChannel* d);
extern f32 g_defaultVolumeChannelFactors[11][4];
extern s32 D_00274808[];
void SetIopChannelValue(s32 channel, s32 value);
void SetIopChannelValuePair(s32 channel, s32 value, s32 value2);
// A script list being built (func_001C1530 hands one to a getter; func_001C1A28 appends a value
// of `type` to it).
struct ScriptListBuilder { s32 type; R11B008Node* head; R11B008Node* tail; };
void FillMemory(void* p, s32 v, s32 n);
void ReadPropertyValue(ScriptValue* t, s32 value, PropertyDescriptor* d);
s32 StepBiasedRandomWalk(void);
extern PropertyList g_classPropertyLists[];
// func_001C0CF0's random walk: six steps for each of seven rows, and the row for each position
// from -12 to 12, copied to the stack.
struct RandomWalkSteps { s32 v[42]; };
struct RandomWalkRows { s32 v[25]; };
extern const RandomWalkSteps D_0024D2A8;
extern const RandomWalkRows D_0024D350;
extern s32 D_00274830;
// (if/else with the small path first moved $s0/$s1)
void ReadPropertyValue(ScriptValue* self, void* a, s32 r);
void SetVoiceParam(s32 voice, s32 a1, s32 a2);
void InitObject(BaseObject* self);
s32 ReadBufferedU32(void* src);
void* AllocateFrontMemory(u32 size);
void SkipBufferedBlock(void* self);
s32 NewScriptScope(void);
void AddUniqueMarkRoot(u8* a, s32 b);
void* DefineScriptVariable(ScriptValue* out, s32 a, s32 b, ScriptValue* body);
extern s32 D_00275714;
// NEAR: the entry pointer is loaded into v0 where retail uses v1 (register choice only); five lines differ.

void EvalScriptExpression(ScriptValue* t, R11B008Node* node, s32 b);
// A type and a list of script values: func_001C1AD8 tells whether a value is among them.
struct ScriptValueFilter { u32 type; R11B008Node* list; };
// The payloads of script values of kind 10 and 11 (two and three words), copied word by word.
struct ScriptPair { s32 w[2]; };
struct ScriptTriple { s32 w[3]; };
extern void* AcquireVectorAPayload(void);
extern void* AcquireMatrixPayload(void);
extern void* CopyRotationMatrix(void* d, void* s);
extern void ResetMatrixHomogeneous(void* d);
extern void* AcquireVectorBPayload(void);
extern void* AcquirePairPayload(void);
extern void* AcquireTriplePayload(void);
void StopSoundRecord(u8* obj, void* item);
extern SprDmaChannel* g_toSprChannel;
s32 WaitDmaChannel(void* p, s32 a, s32 b);
void StartDmaChain(SprDmaChannel* c, u32 addr);
void SetIopVolumeChannel8(f32 x);
void SetVolumeChannelFactor(s32 row, s32 column, f32 value);
void SilenceVolumeChannel3(s32 flag);
s32 ApplySoundOptionFlag(s32 value);
void StopAllSoundsAndWait(void);
void StopWorldSoundRecords(void* item);
void PushIopChannel2Setting(World* self, s32 a, s32 b);
void PopIopChannel2Setting(World* self);
void SetIopChannel2Setting(World* self, s32 index, s32 value);
void AddWorldSoundEntry(World* self, s32 key);
void SetLastWorldSoundEntryFromPoint(World* self, Point2* p);
void SetLastWorldSoundEntryValues(World* self, U64P* item);
void StartWorldSoundEntries(World* self);
void SetCachedVoiceParam(s32 idx, s32 val);
s32 GetCachedVoiceParam(s32 index);
void RefreshCachedVoiceParam(s32 i);
s32 StepBiasedRandomWalk();
void PlaySoundWithWanderingPitch(void);
void LoadScriptEntryTable(World* self, BufferedStream* arg);
void* GetScriptEntryScope(s32 index, World* self);
ScriptValue* EvalScriptEntry(ScriptValue* self, s32 index, World* ctx);
PropertyDescriptor* FindPropertyDescriptor(BaseObject* self, s32 key);
ScriptValue* BuildScriptListFromCallback(ScriptValue* self, void* ctx, s32 v, PropertyGetter cb);
ScriptValue* ReadPropertyValue(ScriptValue* out, void* base, PropertyDescriptor* d);
s32 AppendPropertyToScriptList(ScriptListBuilder* self, s32 value);
s32 ScriptListContainsValue(ScriptValueFilter* filter, s32* val);
ScriptValue* StoreScriptArguments(ScriptValue* out, s32 n, ScriptValue* args, const u32* kinds, void** dsts);
ScriptValue* BuildScriptListFromPairs(ScriptValue* self, s32 n, s32* keys, s32* vals);
ScriptValue* GetObjectProperty(ScriptValue* self, BaseObject* p, s32 n);
ScriptValue* UpdateObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* AddObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* SetExtraObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value);
ScriptValue* StoreScriptArgumentsVa(ScriptValue* ret, s32 count, ScriptValue* args, const void* kinds, ...);
void StartToSprChain(s32 size, ...);
void StartFromSprChain(s32 first, ...);

Collider* FindHandlerForSlot(Collider* node, s32 offset);
extern const s32 g_soundEntryForcedAvailable[772];

// The file's .data, in retail's order.
f32 D_002746C0[4] = { 0.0f, 3.0f, 0.0f, 0.0f };
f32 D_002746D0[4] = { 0.0f, 0.75f, 0.0f, 0.0f };
AnchorPreset D_002746E0[8] = {
    { &D_00248D30, 0 },
    { &D_00248D30, 3 },
    { &g_unitXVector, 2 },
    { &g_unitYVector, 2 },
    { &g_unitZVector, 2 },
    { &g_unitZVector, 1 },
    { &g_unitYVector, 1 },
    { &g_unitXVector, 1 },
};
s32 g_stagedBankState = 0;
s32 g_stagedBankRecord = 0;
s32 g_stagedBankVoice = 0;
s32 g_streamVoice = 0;
s32 g_streamVoicePending = 0;
s32 g_currentSoundLevel = 0;
s32 g_previousSoundLevel = 0;
s32 g_stagedBankHandle = 0;
s32 g_loadedSoundBank = -1;
s32 g_streamVoiceLocked = 0;
s32 D_00274748 = 0;
s32 g_nextSoundRecordId = 0;
f32 D_00274750 = -2.0f;
s32 D_00274754 = 3;
f32 g_defaultVolumeChannelFactors[11][4] = { 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
s32 D_00274808[6] = { 0, 2, 3, 4, 9, 1 };
U64P D_00274820 = { 0x40C0000040800000ULL };
U64P D_00274828 = { 0x45FA0000453B8000ULL };
s32 D_00274830 = 0;
f32 g_volumeChannelFactors[11][4] = { 0 };
u8 D_002748E8[4] = { 0 };
s32 D_002748EC = 0;
SprTransfer D_002748F0[2] = { MakeSprTransfer(0), MakeSprTransfer(1) };
s32 D_00274990 = 0;

void InitCollider(Collider* self)
{
    ScriptValue local;
    s32 s0;
    InitScriptValue(&local);
    SetListLinkOffset(&self->parts, 0x2E4);
    InitPlacedObject(self);
    ClearRecordBody(&self->mesh);
    self->meshCopy = self->mesh;
    if (self->parent != 0) {
        SetColliderAnchors(self, 3, 0, 3, 0);
    }
    self->f4BC = -1;
    self->index = -1;
    if (self->f2C != 0) {
        s0 = LookupScriptVariable(self->f2C, 6, 1, &local);
        s0 |= LookupScriptVariable(self->f2C, 7, 1, &local);
        if (s0 != 0) {
            self->flags538 |= (u64)0x8000 << 48;
        }
    }
    self->gravity = self->world->gravity;
    ResolveContactHandler(self);
    DestroyScriptValue(&local, 2);
}

void RegisterCollider(Collider* self)
{
    World* owner = self->world;
    owner->count34++;
    if (self->parent == 0) {
        AddColliderToSweepAxes(owner, self);
        self->contacts = TakeContactTable(owner, self);
        InitContactPairFlags(owner, self);
        owner->count38++;
        AppendToList(&owner->bodies, self);
    }
    RegisterPlacedObject(self);
    SetColliderPartListed(self, 1);
    self->desc03()->m44(self);
    if (!(self->flags538 & (1ULL << 54))) {
        UpdateAnchorModeFlags(self->root03());
    } else {
        UpdateAnchorModeFlags(self);
    }
    ResolveContactHandler(self);
}

void UnregisterCollider(Collider* self)
{
    Collider* old50 = self->root03();
    World* owner = self->world;
    SetColliderPartListed(self, 0);
    UnregisterPlacedObject(self);
    owner->count34--;
    if (self->parent == 0) {
        RemoveColliderFromSweepAxes(owner, self);
        ReleaseContactTable(owner, self->contacts);
        owner->count38--;
        RemoveFromList(&owner->bodies, self);
    }
    FreeTouchNodes(owner, self->touching);
    u64 flags = self->flags538;
    self->touching = 0;
    if (!(flags & (1ULL << 54)) && old50 != self) {
        UpdateAnchorModeFlags(old50);
    }
}

void SetColliderPartListed(Collider* self, s32 flag)
{
    if (flag == ((self->flags538 >> 50) & 1)) {
        return;
    }
    if (flag != 0) {
        AppendToList(&self->root03()->parts, self);
    } else {
        RemoveFromList(&self->root03()->parts, self);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 50)) | ((u64)(flag & 1) << 50);
    ClearRootObjectStateBits(self->world, self, 7);
    Collider* sub = self->root03();
    sub->desc03()->m32(sub);
}

INCLUDE_ASM(func_001B7D00);

void SettlePoseSourceModes(Attachment* a);
void ApplyColliderPendingImpulse(Collider* self, s32 moved)
{
    s32 still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v490))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vu0::Q(self->v150) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(self->v490));
        if (self->f1EC != 0) {
            SettlePoseSourceModes(self->f1EC);
        }
        Vu0::Q(self->v490) = Vu0::Zero();
        moved = 1;
    }
    still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->spin4A0))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vu0::Q(self->v160) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(self->spin4A0));
        if (self->f1F0 != 0) {
            SettlePoseSourceModes(self->f1F0);
        }
        Vu0::Q(self->spin4A0) = Vu0::Zero();
        moved = 1;
    }
    ListFrame it;
    ListWalk::Begin(&it, &self->children);
    for (PlacedObject* c = (PlacedObject*)ListWalk::Next(&it); c != 0; c = (PlacedObject*)ListWalk::Next(&it)) {
        if (c->desc->flags & 2) {
            ((Collider*)c)->desc03()->m30((Collider*)c, moved);
        }
    }
    ListWalk::End(&it);
}

INCLUDE_ASM(func_001B8148);

ASM_FUNC(func_001B8420);

ASM_FUNC(func_001B8540);

ASM_FUNC(func_001B8820);

void ComputeColliderWorldFrame(Collider* self)
{
    ComputePlacedObjectWorldFrame(self);
    TransformMeshToWorld(&self->mesh, &self->meshCopy, *(Qword128*)&self->v140, &self->m110);
    TransformMeshToWorld(&self->mesh2, &self->mesh2Copy, *(Qword128*)&self->v140, &self->m110);
}

void RecomputeColliderFrame(Collider* self)
{
    RecomputePlacedObjectFrame(self);
    self->root03()->desc03()->m32(self->root03());
    ClearRootObjectStateBits(self->world, self, 7);
    MarkSweepAxesUnsorted(self->world);
}

s32 TestCollidersMayContact(Collider* a, Collider* b)
{
    u64 m1 = 0x8080;
    s32 r = 0;
    m1 <<= 40;
    if ((a->flags538 & m1) != 0) {
        u64 bf = b->flags538;
        u64 m2 = 0x8000;
        m2 <<= 40;
        if ((bf & m2) != 0) {
            return 1;
        }
    }
    return r;
}

void NotifyContactHandlers(Collider* self)
{
    ContactRow03* node = self->contacts->head;
    while (node != 0) {
        Contact03* it = node->head;
        while (it != 0) {
            if (0.0001f < it->timer) {
                for (s32 i = 0; i < 2; i++) {
                    Collider* obj = FindHandlerForSlot(it->end[i].part, 0x114);
                    if (obj != 0) {
                        void (*fn)(Collider*, Contact03*, s32) = obj->desc03()->m41;
                        if (fn != 0) {
                            fn(obj, it, i);
                        }
                    }
                }
                *(s32*)&it->timer = 0;
            }
            if (node->head == 0) {
                break;
            }
            it = it->next;
        }
        node = node->next;
    }
}

INCLUDE_ASM(func_001B8B30);

INCLUDE_RODATA(jtbl_0024D280);
INCLUDE_ASM(func_001B8B90);

ASM_FUNC(func_001B8FE0);

ASM_FUNC(func_001B8FE8);

void AddColliderForce(Collider* self, Vec02* force);

void SteerColliderTowardPosition(Collider* self, Vec02* target, f32* pull, Vec02* aim, f32* turn, f32 limit)
{
    Vec02 acc;
    Vec02 d;
    Vec02 k;
    Vu0::Q(acc) = Vu0::Zero();
    if (pull != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*target), Vu0::Q(self->pos));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (0.0001f < len) {
            Vu0::Q(k) = Vu0::FromFloat(pull[2] * len + pull[1] + pull[0] / len);
            Vu0::Q(acc) = Vu0::MulX(Vu0::Q(d), Vu0::Q(k));
        }
    }
    if (turn != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*aim), Vu0::Q(self->v150));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (0.0001f < len) {
            f32 amount = turn[2] * len + turn[1] + turn[0] / len;
            f32 cap = 1.0f / limit;
            if (cap < amount) {
                amount = cap;
            }
            Vu0::Q(k) = Vu0::FromFloat(amount);
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(d), Vu0::Q(k));
        }
    }
    AddColliderForce(self, &acc);
}

void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void AddColliderTorque(Collider* self, Vec02* torque);

void SteerColliderTowardRotation(Collider* self, Mat02* target, f32* pull, Vec02* aim, f32* turn, f32 limit)
{
    Vec02 acc;
    Vu0::Q(acc) = Vu0::Zero();
    if (pull != 0) {
        Mat02 m;
        Vec02 axis;
        Vec02 k;
        f32 angle;
        MultiplyMatrices3x3(&self->rot, target, &m);
        MatrixToAxisAngle(&m, &angle, &axis);
        if (0.0001f < angle) {
            Vu0::Q(k) = Vu0::FromFloat(pull[2] * angle * angle + pull[1] * angle + pull[0]);
            Vu0::Q(acc) = Vu0::MulX(Vu0::Q(axis), Vu0::Q(k));
        }
    }
    if (turn != 0) {
        Vec02 d;
        Vec02 k;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*aim), Vu0::Q(self->v160));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (0.0001f < len) {
            f32 amount = turn[2] * len + turn[1] + turn[0] / len;
            f32 cap = 1.0f / limit;
            if (cap < amount) {
                amount = cap;
            }
            Vu0::Q(k) = Vu0::FromFloat(amount);
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(d), Vu0::Q(k));
        }
    }
    AddColliderTorque(self, &acc);
}

void StepCollider(Collider* self, f32 t)
{
    Vec4U local;
    Attach03* node;
    u64 m = 0x8000;
    m <<= 36;
    if (self->parent == 0) {
        if ((self->flags538 & m) == 0) {
            ConstrainColliderVector(self, &self->v440, &self->gravity, &local, 0);
            AddColliderForce(self, &local);
        }
    }
    node = self->attached;
    if (node != 0) {
        do {
            Collider* obj = node->owner;
            obj->desc03()->m33(obj, node, t);
            node = node->next;
        } while (node != 0);
    }
}

void DrawCollider(Collider* self, void* a, void* m)
{
    DrawPlacedObject(self, a, m);
}

void UpdateCollider(Collider* self)
{
    UpdatePlacedObject(self);
}

void SetColliderMass(Collider* self, f32 v)
{
    f32 a = self->mass;
    f32 q = v / a;
    self->mass = a * q;
    ComputeColliderInverseInertia(self, q);
}

void ComputeColliderInverseInertia(Collider* self, f32 scale)
{
    Mat02 m;
    Vec02 k;
    Mat02 s;
    Vu0::Q(k) = Vu0::FromFloat(scale);
    Vu0::Q(s.r[0]) = Vu0::MulX(Vu0::Q(self->inertia.r[0]), Vu0::Q(k));
    Vu0::Q(s.r[1]) = Vu0::MulX(Vu0::Q(self->inertia.r[1]), Vu0::Q(k));
    Vu0::Q(s.r[2]) = Vu0::MulX(Vu0::Q(self->inertia.r[2]), Vu0::Q(k));
    CopyBytes(&m, &s, 0x30);
    self->inertia = m;
    if (!InvertMatrix3x3(&self->inertia, &self->invInertia)) {
        FillMemory(&self->invInertia, 0, 0x30);
    }
}

void DropColliderContacts(Collider* self, s32 mode)
{
    Collider* ctx = self->root03();
    if (ctx == 0) {
        return;
    }
    if (mode != 0) {
        Contact03* freed = 0;
        for (ContactRow03* o = ctx->contacts->head; o != 0; o = o->next) {
            Contact03** pp = &o->head;
            Contact03* it;
            while ((it = *pp) != 0) {
                s32 other = it->end[0].body != ctx;
                ContactEnd03* p = &it->end[other];
                s32 hit;
                switch (mode) {
                case 1:
                    hit = IsObjectDescendantOf(p->part, self);
                    break;
                case 2:
                    hit = p->part == self;
                    break;
                case 3:
                    hit = 0;
                    if (p->part == self && other == 0) {
                        if (it->kind >= 8 && it->kind <= 9) {
                            hit = 1;
                        }
                    }
                    break;
                default:
                    hit = 0;
                    break;
                }
                if (hit != 0) {
                    *pp = it->next;
                    it->next = freed;
                    freed = it;
                } else {
                    pp = &it->next;
                }
            }
            *o->link = o->head;
        }
        FreePooledContactChain(self->world, freed);
    }
    ctx->f4B8 = 0;
}

void SaveColliderPreviousPosition(Collider* self)
{
    self->v370 = self->v140;
}

// What slot 13 of a moved collider is told (kind 3): the collider and where it was.
// The record a collider's position change hands to its event method (event 3). Its frame slot
// is 0x30 bytes where placed_object.cpp's MoveNotice, the same event's record there, is 0x20:
// SetColliderPosition writes only who and before, and leaves the third quadword as it is.
struct ColliderMoveNote {
    Collider* who;
    u8 pad04[0xC];
    Vec02 before;           // 0x10
    Vec02 q20;              // 0x20: not written by SetColliderPosition
};
void RequestCameraSnap(Camera* camera, s32 mode);

void SetColliderPosition(Collider* self, Vec02* pos)
{
    ColliderMoveNote note;
    note.who = self;
    note.before = self->v140;
    if ((self->flags538 & ((u64)1 << 45)) != 0) {
        if (10.0f < Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(*pos))))) {
            Camera* cam = g_camera;
            cam->f2E0 = 0;
            RequestCameraSnap(cam, 0);
        }
    }
    self->pos = *pos;
    if (self->root != 0) {
        if (self->desc->m12 != 0) {
            self->desc->m12(self);
        }
        DropColliderContacts(self, 1);
        Collider* root = (Collider*)self->root;
        Collider* part = (Collider*)root->parts.head;
        while (part != 0) {
            if (self == root || self == part || IsObjectDescendantOf(part, self) != 0) {
                ((Desc03*)part->desc)->m44(part);
            }
            part = (Collider*)part->link2E4.next;
        }
    }
    self->desc->m0E(self, 3, &note);
}

void SetColliderRotation(Collider* self, Mat02* src)
{
    self->rot.r[0] = src->r[0];
    self->rot.r[1] = src->r[1];
    self->rot.r[2] = src->r[2];
    if (self->root != 0) {
        if (self->desc->m12 != 0) {
            self->desc->m12(self);
        }
        DropColliderContacts(self, 1);
    }
    self->desc->m0E(self, 4, self);
}

void PlaceColliderClearOfContacts(Collider* self, Vec02* start, Vec02* step)
{
    Vec02 pos = *start;
    s32 i = 9;
    do {
        self->desc02()->m1D(self, &pos);
        UpdateWorldContacts(self->world, 0);
        for (ContactRow03* node = self->contacts->head; node != 0; node = node->next) {
            for (Contact03* c = node->head; c != 0; c = c->next) {
                if (c->f90 < -2.0f) {
                    goto moved;
                }
            }
        }
        return;
    moved:
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(*step));
    } while (--i >= 0);
}

LINKER_REMNANT(func_001B9938);

void SetColliderVelocity(Collider* self, Vec02* v)
{
    SetPlacedObjectVelocity(self, v);
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*v), Vu0::Q(self->v150));
    s32 small = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(d))) < 2.0f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(d))) < 2.0f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(d))) < 2.0f) {
        small = 1;
    }
    if (!small) {
        ClearRootObjectStateBits(self->world, self, 2);
    }
}

void SetColliderSpin(Collider* self, Vec02* v)
{
    SetPlacedObjectSpin(self, v);
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*v), Vu0::Q(self->v160));
    s32 small = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(d))) < 0.02f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(d))) < 0.02f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(d))) < 0.02f) {
        small = 1;
    }
    if (!small) {
        ClearRootObjectStateBits(self->world, self, 2);
    }
}

LINKER_REMNANT(func_001B9AA8);

ASM_FUNC(func_001B9AB0);

ASM_FUNC(func_001B9AC8);

void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4)
{
    self->mode450 = a1;
    u64 flag = (self->flags538 >> 54) & 1;
    if (a2 != 0) {
        self->v440 = *a2;
    }
    self->mode470 = a3;
    if (a4 != 0) {
        self->v460 = *a4;
    }
    Collider* sub = self->root03();
    if (sub != 0) {
        s32 f2 = 0;
        if (a1 == 3) {
            f2 = (a3 == 3);
        }
        if (flag != f2) {
            UpdateAnchorModeFlags(sub);
        }
    }
}

void ReparentCollider(Collider* self, BaseObject* p)
{
    Vec02 local0;
    Vec02 local1;
    if (self->parent == p) {
        return;
    }
    Collider* s5 = self->root03();
    TransformDirectionBetweenFrames(self->parent, 0, &self->v440, &local0);
    TransformDirectionBetweenFrames(self->parent, 0, &self->v460, &local1);
    ReparentPlacedObject(self, p);
    TransformDirectionBetweenFrames(0, p, &local0, &self->v440);
    TransformDirectionBetweenFrames(0, p, &local1, &self->v460);
    if (self->root != 0) {
        if ((self->flags538 & (1ULL << 54)) != 0 && s5 != 0) {
            UpdateAnchorModeFlags(s5);
        }
        Collider* f = self->root03();
        if ((f->flags538 & (1ULL << 55)) != 0) {
            UpdateAnchorModeFlags(f);
        } else {
            UpdateAnchorModeFlags(self);
        }
    }
    ResolveContactHandler(self);
}

void ReframePlacedObject(void* self, PlacedObject* frame);

void ReframeColliderAnchors(Collider* self, PlacedObject* frame)
{
    Vec02 a;
    Vec02 b;
    ReframePlacedObject(self, frame);
    Vu0::Q(a) = Vu0::Rotate(frame->rot, Vu0::Q(self->v440));
    Vu0::Q(b) = Vu0::Rotate(frame->rot, Vu0::Q(self->v460));
    SetColliderAnchors(self, self->mode450, &a, self->mode470, &b);
}

LINKER_REMNANT(func_001B9D08);

INCLUDE_ASM(func_001B9D10);

LINKER_REMNANT(func_001B9F28);

void CaptureColliderPose(Collider* self, ColliderPose* out)
{
    Vec02 tmp[3];
    out->position = self->v140;
    out->v150 = self->v150;
    RotateMatrixUpright(&self->m110, 0, &tmp[0]);
    out->heading = ArctangentOfRatio(-tmp[0].y, -tmp[0].x);
    out->f34 = 100.0f;
    out->f00 = 0;
    out->time = g_gameTime[0];
    out->f3C = 0;
}

s32 IsContactBetweenParts(Collider* self, void* other)
{
    s32 key;
    Contact03* n;
    for (n = (Contact03*)GetContactRowHead(self, other), key = (s32)self->root; n != 0; n = n->next) {
        s32 s1 = (key ^ (s32)n->end[0].body) != 0;
        s32 o0 = s1 * 64;
        if (IsObjectDescendantOf(*(void**)((u8*)n + o0 + 4), self) != 0) {
            s32 o1 = (1 - s1) * 64;
            if (IsObjectDescendantOf(*(void**)((u8*)n + o1 + 4), other) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

void* FindContactingPart(Collider* self)
{
    Collider* s3 = self->root03();
    ContactRow03* s2 = s3->contacts->head;
    for (; s2 != 0; s2 = s2->next) {
        Contact03* s0 = s2->head;
        while (s0 != 0) {
            s32 s1 = ((u32)s3 ^ (u32)s0->end[0].body) != 0;
            if (IsObjectDescendantOf(*(void**)((u8*)(s0) + (s1 << 6) + 4), self) != 0) {
                return *(void**)((u8*)(s0) + ((1 - s1) << 6) + 4);
            }
            s0 = s0->next;
        }
    }
    return 0;
}

void CopyCollider(Collider* self, Collider* other)
{
    u64 bit = (self->flags538 >> 50) & 1;
    Link02 a, c, d;
    List01 b;
    a = self->link2D0;
    b = self->parts;
    c = self->link2E4;
    Contacts03* s480 = self->contacts;
    Collider* s4E4 = self->handler;
    d = self->link414;
    CopyPlacedObject(self, other);
    self->contacts = s480;
    self->link2D0 = a;
    self->parts = b;
    self->link2E4 = c;
    self->link414 = d;
    self->handler = s4E4;
    self->attached = 0;
    self->f4B8 = 0;
    self->flags538 = (self->flags538 & 0xFFFBFFFFFFFFFFFFULL) | (bit << 50);
    SetColliderPartListed(self, 1);
    if (self->meshCopy.vertCount) CopyMeshTransformed(&other->meshCopy, 0, &self->meshCopy);
    if (self->tree.nodes) CloneTreeNodes(&other->meshCopy, &other->tree, &self->meshCopy, &self->tree);
    if (self->mesh2Copy.vertCount) CopyMeshTransformed(&other->mesh2Copy, 0, &self->mesh2Copy);
    if ((s32)self->flags538) CloneTreeNodes(&other->mesh2Copy, &other->tree2, &self->mesh2Copy, &self->tree2);
    self->touching = 0;
    self->flags538 |= 0x20000000000ULL;
}

void ConstrainVectorByParentAnchor(Collider* self, VectorConstraint* c, Vec02* in, Vec02* out, Vec02* rem)
{
    Vec02 axis;
    Vec02 tmp;
    if (out == 0) {
        out = &tmp;
    }
    switch (c->kind) {
    case 0:
        if (out != in) {
            *out = *in;
        }
        break;
    case 2: {
        Vec02* a;
        PlacedObject* parent = (PlacedObject*)self->parent;
        if (parent != 0) {
            Vu0::Q(axis) = Vu0::Rotate(parent->m110, Vu0::Q(c->axis));
            a = &axis;
        } else {
            a = &c->axis;
        }
        Vu0::Q(*out) = Vu0::MulX(Vu0::Q(*a), Vu0::Dot(Vu0::Q(*in), Vu0::Q(*a)));
        break;
    }
    case 1: {
        Vec02* a;
        PlacedObject* parent = (PlacedObject*)self->parent;
        if (parent != 0) {
            Vu0::Q(axis) = Vu0::Rotate(parent->m110, Vu0::Q(c->axis));
            a = &axis;
        } else {
            a = &c->axis;
        }
        Vu0::Q(*out) = Vu0::Sub(Vu0::Q(*in), Vu0::MulX(Vu0::Q(*a), Vu0::Dot(Vu0::Q(*in), Vu0::Q(*a))));
        break;
    }
    case 3:
        Vu0::Q(*out) = Vu0::Zero();
        break;
    }
    if (rem != 0) {
        Vu0::Q(*rem) = Vu0::Sub(Vu0::Q(*in), Vu0::Q(*out));
    }
}

void ConstrainVectorByAnchor(VectorConstraint* c, Vec02* in, Vec02* out, Vec02* rem)
{
    Vec02 tmp;
    if (out == 0) {
        out = &tmp;
    }
    switch (c->kind) {
    case 0:
        if (out != in) {
            *out = *in;
        }
        break;
    case 2:
        Vu0::Q(*out) = Vu0::MulX(Vu0::Q(c->axis), Vu0::Dot(Vu0::Q(*in), Vu0::Q(c->axis)));
        break;
    case 1:
        Vu0::Q(*out) = Vu0::Sub(Vu0::Q(*in), Vu0::MulX(Vu0::Q(c->axis), Vu0::Dot(Vu0::Q(*in), Vu0::Q(c->axis))));
        break;
    case 3:
        Vu0::Q(*out) = Vu0::Zero();
        break;
    }
    if (rem != 0) {
        Vu0::Q(*rem) = Vu0::Sub(Vu0::Q(*in), Vu0::Q(*out));
    }
}

void ConstrainColliderVector(void* self, void* a, void* b, void* c, s32 d)
{
    ConstrainVectorByAnchor((VectorConstraint*)a, (Vec02*)b, (Vec02*)c, (Vec02*)(s32)d);
}

void AddColliderAttachment(Collider* self, Attach03* node)
{
    node->next = self->attached;
    self->attached = node;
    ClearRootTries(self);
}

void RemoveColliderAttachment(Collider* o, Attach03* node)
{
    Attach03** link = &o->attached;
    if (*link == 0) {
        goto tail;
    }
    if (o->attached == node) {
        o->attached = node->next;
    } else {
        Attach03* prev;
        for (;;) {
            prev = *link;
            Attach03* nx = prev->next;
            link = &prev->next;
            if (nx == 0) {
                goto tail;
            }
            if (nx == node) {
                break;
            }
        }
        prev->next = node->next;
    }
    node->next = 0;
tail:
    ClearRootTries(o);
}

INCLUDE_ASM(func_001BA5B0);

void IgnoreColliderAttachmentStep(Collider* self, Attach03* node, f32 dt)
{
}

void LoadCollider(Collider* self, BufferedStream* in)
{
    s32 i;
    s32 j;
    s32 n;
    Pair03* e;
    u8 flag = ReadBufferedU8(in) & 1;
    self->flags = (self->flags & ~(1ULL << 33)) | ((u64)flag << 33);
    func_00137FB0(in, &self->mesh);
    self->radius3D0 = self->mesh.radius;
    self->radius3CC = self->mesh.radius;
    if (self->flags & (1ULL << 33)) {
        self->meshCopy = self->mesh;
    } else {
        CopyMeshTransformed(&self->mesh, 0, &self->meshCopy);
    }
    ReadFaceTree(in, &self->meshCopy, &self->tree);
    i = 0;
    self->mass = ReadBufferedFloat(in);
    ReadBufferedRotation3(in, &self->inertia);
    ReadBufferedVector3(in, &self->offset);
    ComputeColliderInverseInertia(self, 1.0f);
    self->groupCount = ReadBufferedU16(in);
    self->groups = (Pair03*)AllocateFrontMemory(self->groupCount << 3);
    if (self->groupCount > 0) {
        do {
            e = self->groups;
            e += i++;
            e->a = ReadBufferedS16(in);
            e->b = ReadBufferedU16(in);
        } while (i < self->groupCount);
    }
    n = ReadBufferedU32(in);
    j = 0;
    self->nodeGroups = (s32*)AllocateFrontMemory(n << 2);
    if (n > 0) {
        do {
            s32 v = ReadBufferedS16(in);
            self->nodeGroups[j] = v;
            j++;
        } while (j < n);
    }
    self->refCount = ReadBufferedU32(in);
    i = 0;
    self->refs = (Pair03*)AllocateFrontMemory(self->refCount << 3);
    while (i < self->refCount) {
        e = self->refs;
        e += i++;
        e->a = ReadBufferedS16(in);
        e->b = ReadBufferedS16(in);
    }
    if (self->refCount > 0) {
        j = 0;
        self->faceStarts = (s32*)AllocateFrontMemory((self->meshCopy.faceCount + 1) << 2);
        if (self->meshCopy.faceCount >= 0) {
            do {
                s32 v = ReadBufferedS16(in);
                self->faceStarts[j] = v;
                j++;
            } while (self->meshCopy.faceCount >= j);
        }
    }
    func_00137FB0(in, &self->mesh2);
    if (self->flags & (1ULL << 33)) {
        self->mesh2Copy = self->mesh2;
    } else {
        CopyMeshTransformed(&self->mesh2, 0, &self->mesh2Copy);
    }
    ReadFaceTree(in, &self->mesh2Copy, &self->tree2);
    LoadPlacedObject(self, in);
    SetColliderPartListed(self, 1);
    self->desc03()->m44(self);
    if (self->parent == 0) {
        self->desc03()->m32(self);
        InitContactPairFlags(self->world, self);
    }
}

void SetColliderOverrideRadius(Collider* self, f32 v)
{
    self->flags538 |= (u64)0x8000 << 25;
    self->radius3CC = v;
}

void ResetColliderAnchors(void* self)
{
    SetColliderAnchors(self, 3, 0, 3, 0);
}

void GetAnchorPreset(s32 index, s32* out, Vec02* dst)
{
    *out = D_002746E0[index].value;
    *dst = *D_002746E0[index].quad;
}

void SetColliderTurnAnchorPreset(Collider* self, s32 index)
{
    Vec02 v;
    Vec02 local;
    s32 mode;
    GetAnchorPreset(index, &mode, &local);
    Vu0::Q(v) = Vu0::Rotate(self->rot, Vu0::Q(local));
    SetColliderAnchors(self, mode, &v, self->mode470, &self->v460);
}

void SetColliderMoveAnchorPreset(Collider* self, s32 index)
{
    Vec02 v;
    Vec02 local;
    s32 mode;
    GetAnchorPreset(index, &mode, &local);
    Vu0::Q(v) = Vu0::Rotate(self->rot, Vu0::Q(local));
    SetColliderAnchors(self, self->mode450, &self->v440, mode, &v);
}

void SetColliderFlagNibble32(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(0xFULL << 32)) | ((u64)(value & 0xF) << 32); }

void SetColliderFlagBit47(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(1ULL << 47)) | ((u64)(value & 1) << 47); }

void SetColliderFlagBit48(Collider* self, s32 flag)
{
    self->flags538 = (self->flags538 & 0xFFFEFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 48);
}

void func_001BB1D8(Collider* self, u8 value) { self->b2C8 = value; }

void SetColliderFlagNibble36(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(0xFULL << 36)) | ((u64)(value & 0xF) << 36); }

void SendColliderNotification(Collider* self, s32 kind, void* arg)
{
    SendObjectNotification(self, kind, arg);
    Attach03* n = self->attached;
    if (n != 0) {
        do {
            Attach03* next = n->next;
            Collider* obj = n->owner;
            if (obj != self) {
                void (*fn)(BaseObject*, s32, void*) = obj->desc->m0D;
                if (fn != 0) {
                    fn(obj, kind, arg);
                }
            }
            n = next;
        } while (n != 0);
    }
}

// The literal func_001BB290 loads.
extern const f32 D_0024D2A0 = 3.4028235e38f;

INCLUDE_ASM(func_001BB290);

void SetColliderGravityDisabled(Collider* self, s32 flag)
{
    self->flags538 = (self->flags538 & ~(1ULL << 51)) | ((u64)(flag & 1) << 51);
}

void SetColliderTreeContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 42;
    self->flags538 = (self->flags538 & ~(1ULL << 42)) | bit;
    DropColliderContacts(self, value != 0);
}

void SetColliderContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 43;
    self->flags538 = (self->flags538 & ~(1ULL << 43)) | bit;
    DropColliderContacts(self, value != 0 ? 2 : 0);
}

void SetColliderKindContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 44;
    self->flags538 = (self->flags538 & ~(1ULL << 44)) | bit;
    DropColliderContacts(self, value != 0 ? 3 : 0);
}

void ResolveContactHandler(Collider* self)
{
    ListFrame frame;
    const Desc03* info = self->desc03();
    if (info->m41 != 0 || info->m3C != 0 || info->m3D != 0) {
        self->handler = self;
    } else if (info->m3E != 0) {
        self->handler = self;
    } else {
        Collider* p = (Collider*)self->parent;
        if (p != 0) {
            self->handler = p->handler;
        } else {
            self->handler = 0;
        }
    }
    Collider* c = (Collider*)self->children.head;
    while (c != 0) {
        if (c->desc->flags & 2) ResolveContactHandler(c);
        c = (Collider*)c->next;
    }
}

Collider* FindHandlerForSlot(Collider* node, s32 offset)
{
    Collider* s;
    while (node != 0 && (s = node->handler) != 0) {
        if (*(s32*)((u8*)s->desc + offset) != 0) return s;
        node = (Collider*)s->parent;
    }
    return 0;
}

void UpdateAnchorModeFlags(Collider* self)
{
    ListFrame frame;
    s32 flag = 0;
    if (self->mode450 == 3) {
        flag = (self->mode470 == 3);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 54)) | ((u64)flag << 54);
    s32 s2 = flag & 1;
    s32 a0 = 0;
    if (self->flags538 & (1ULL << 54)) {
        if (self->parent == 0 || (((Collider*)self->parent)->flags538 & (1ULL << 56)) != 0) a0 = 1;
    }
    self->flags538 = (self->flags538 & ~(1ULL << 56)) | ((u64)a0 << 56);
    Collider* c = (Collider*)self->children.head;
    while (c != 0) {
        if (c->desc->flags & 2) {
            UpdateAnchorModeFlags(c);
            if ((c->flags538 & (1ULL << 55)) == 0) s2 = 0;
        }
        c = (Collider*)c->next;
    }
    u64 bit = (self->flags538 >> 55) & 1;
    if (bit != (u64)s2) {
        self->flags538 = (self->flags538 & ~(1ULL << 55)) | ((u64)(s2 & 1) << 55);
        if (self->parent == 0 && self->root != 0) {
            InitContactPairFlags(self->world, self);
        }
    }
}

s32 CollectContactingPartsToScriptList(Collider* self, s32 value)
{
    Collider* ctx = self->root03();
    ContactRow03* n = ctx->contacts->head;
    while (n != 0) {
        Contact03* e = n->head;
        while (e != 0) {
            s32 idx = ((u32)e->end[0].body ^ (u32)ctx) != 0;
            ContactEnd03* s = &e->end[idx];
            if (s->part == self) {
                void* tmp = e->end[1 - idx].part;
                if (ScriptListContainsValue(value, &tmp) == 0) {
                    if (AppendPropertyToScriptList(value, &tmp) == 0) return 0;
                }
            }
            e = e->next;
        }
        n = n->next;
    }
    return 1;
}

s32 CollectContactingParts(Collider* obj, s32* outCount, void*** outArr)
{
    Collider* own = obj->root03();
    ContactRow03* nd;
    Contact03* it;
    s32 n = 0;
    for (nd = own->contacts->head; nd; nd = nd->next) {
        for (it = nd->head; it; it = it->next) {
            s32 g = it->end[0].body != own;
            if (IsObjectDescendantOf(*(void**)((u8*)it + (g << 6) + 4), obj))
                n++;
        }
    }
    void** arr = (void**)AllocateBackMemory(n << 2);
    void** end = arr;
    for (nd = own->contacts->head; nd; nd = nd->next) {
        for (Contact03* it2 = nd->head; it2; it2 = it2->next) {
            s32 f = it2->end[0].body != own;
            if (IsObjectDescendantOf(*(void**)((u8*)it2 + (f << 6) + 4), obj)) {
                void* v = *(void**)((u8*)it2 + ((1 - f) << 6) + 4);
                void** p;
                for (p = arr; p < end; p++)
                    if (*p == v) break;
                if (!(p < end)) {
                    *end = v;
                    end++;
                }
            }
        }
    }
    *outArr = arr;
    s32 cnt = end - arr;
    *outCount = cnt;
    return cnt;
}

s32 IsInTouchingList(Touch03* node, Collider* value)
{
    while (node != 0) {
        if (node->obj == value) return 1;
        node = node->next;
    }
    return 0;
}

void UpdateTouchingParts(Collider* self)
{
    Collider* core = self->root03();
    ContactRow03* o;
    Contact03* e;
    Touch03* m;
    Touch03* prev;
    Collider* other;
    void* args;
    for (o = core->contacts->head; o != 0; o = o->next) {
        for (e = o->head; e != 0; e = e->next) {
            s32 i = e->end[0].body != core;
            if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                if (!IsInTouchingList(self->touching, other)) {
                    args = &other;
                    TriggerScriptEvent(self, 6, 1, &args);
                }
            }
        }
    }
    for (m = self->touching; m != 0; m = m->next) {
        s32 found = 0;
        for (o = core->contacts->head; o != 0 && !found; o = o->next) {
            for (e = o->head; e != 0 && !found; e = e->next) {
                s32 i = e->end[0].body != core;
                if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                    other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                    if (other == m->obj) found = 1;
                }
            }
        }
        if (!found) {
            args = m;
            TriggerScriptEvent(self, 7, 1, &args);
        }
    }
    FreeTouchNodes(self->world, self->touching);
    self->touching = 0;
    for (o = core->contacts->head; o != 0; o = o->next) {
        for (e = o->head; e != 0; e = e->next) {
            s32 i = e->end[0].body != core;
            if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                Touch03* n = AllocateTouchNode(self->world);
                n->obj = other;
                if (self->touching != 0) prev->next = n; else self->touching = n;
                prev = n;
            }
        }
    }
}

s32 RequestColliderLaunch(Collider* self)
{
    return 0;
}

s32 SolveQuadratic(f32* roots, f32 a, f32 b, f32 c);

INCLUDE_ASM(func_001BBC38);

struct MeshMotion {
    Vec02* velocity;
    Vec02* accel;
    struct Tri { s32 i[3]; } *tris;
};

struct MeshFace {
    Vec02 normal;
    f32 dist;
    u8 pad14[0xA];
    u16 ref;
};

void func_001BBEB8(Collider* self, f32 dt)
{
    Vec02 a, b;
    Vec02* pts = (Vec02*)self->mesh.verts;
    Vec02* vel = ((MeshMotion*)self->hook)->velocity;
    Vec02* acc = ((MeshMotion*)self->hook)->accel;
    f32 big = 0.0f;
    for (s32 i = 0; i < self->mesh.vertCount; i++) {
        u128 p = Vu0::Q(pts[i]);
        u128 s = Vu0::Scalar(dt);
        u128 v = Vu0::Q(vel[i]);
        u128 t = Vu0::Scalar(dt * (dt * 0.5f));
        u128 c = Vu0::Q(acc[i]);
        Vu0::Q(pts[i]) = Vu0::MulAddX2(p, v, s, c, t);
        u128 v2 = Vu0::Q(vel[i]);
        u128 s2 = Vu0::Scalar(dt);
        u128 c2 = Vu0::Q(acc[i]);
        Vu0::Q(vel[i]) = Vu0::MulAddX(v2, c2, s2);
        f32 len = Vu0::ToFloat(Vu0::Dot(Vu0::Q(pts[i]), Vu0::Q(pts[i])));
        if (big < len) {
            big = len;
        }
    }
    self->radius3CC = Fpu::Sqrt(big);
    MeshFace* face = (MeshFace*)self->mesh.faces;
    MeshMotion::Tri* tri = ((MeshMotion*)self->hook)->tris;
    for (s32 i = 0; i < self->mesh.faceCount; i++) {
        MeshFace* f = &face[i];
        Vu0::Q(a) = Vu0::Sub(Vu0::Q(pts[tri[i].i[1]]), Vu0::Q(pts[tri[i].i[0]]));
        Vu0::Q(b) = Vu0::Sub(Vu0::Q(pts[tri[i].i[2]]), Vu0::Q(pts[tri[i].i[0]]));
        u128 n = Vu0::Cross(Vu0::Q(a), Vu0::Q(b));
        Vu0::Q(f->normal) = n;
        n = Vu0::DivX(Vu0::Q(f->normal), Vu0::Sqrt(Vu0::Dot(Vu0::Q(f->normal), Vu0::Q(f->normal))));
        Vu0::Q(f->normal) = n;
        *(u32*)&f->dist = Vu0::ToBits(Vu0::Dot(Vu0::Q(f->normal), Vu0::Q(pts[f->ref])));
    }
}

void MoveCollider(Collider* self, void* b, f32 x)
{
    if (self->hook != 0) {
        func_001BBEB8(self, x);
    }
    MovePlacedObject(self, x, b);
}

INCLUDE_ASM(func_001BC0E0);

void func_001BC260(Collider* self, f32* p, f32* out, f32 a)
{
    f32 roots[4];
    f32 m = p[2] >? self->v140.z;
    out[2] = Fpu::Sqrt(self->gravity.z * ((m + a - self->v140.z) * -2.0f));
    SolveQuadratic(roots, self->gravity.z * 0.5f, out[2], self->v140.z - p[2]);
    f32 dx = p[0] - self->v140.x;
    f32 r0 = roots[0];
    f32 r1 = roots[1];
    f32 t = r1 >? r0;
    out[0] = dx / t;
    out[1] = (p[1] - self->v140.y) / t;
}

s32 HandleObjectEvent(Collider* self, ObjectEvent* shape)
{
    if (shape->eventFlags & 0x8) {
        func_001BC0E0(self, shape->radius, (u8*)shape + 0x20, (u8*)shape + 0x30);
    }
    return shape->eventFlags != 0;
}

void CopyColliderMeshesInFrame(Collider* self, Collider* src, s32 extra)
{
    Vec02 m[4];
    Mesh03 tmp;
    BuildMatrixFromRotationAndTranslation((u8*)src + 0x100, (u8*)src + 0xD0, m);
    f32 maxDist = 0.0f;
    for (s32 i = 0; i < src->mesh.vertCount; i++) {
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(((Vec02*)src->mesh.verts)[i]), Vu0::Q(((Vec02*)src->mesh.verts)[i])));
        if (maxDist < d) {
            maxDist = d;
        }
    }
    self->radius3CC = Fpu::Sqrt(maxDist);
    tmp = src->mesh;
    tmp.vertCount = tmp.vertCount + extra;
    CopyMeshTransformed(&tmp, (s32)m, &self->mesh);
    BuildMatrixFromRotationAndTranslation((u8*)self + 0x140, (u8*)self + 0x110, m);
    CopyMeshTransformed(&self->mesh, (s32)m, &self->meshCopy);
    self->f4B8 = 0;
    CloneTreeNodes(&src->meshCopy, &src->tree, &self->meshCopy, &self->tree);
    CloneTreeNodes(&src->mesh2Copy, &src->tree2, &self->mesh2Copy, &self->tree2);
    func_001BBC38(self);
}

void ExtractContactsByPartMode(Collider* self, Contact03** out)
{
    Contact03* freed = 0;
    if (self->root == self) {
        ContactRow03* h = self->contacts->head;
        if (h) {
            do {
                Contact03** pp = (Contact03**)h;
                Contact03* n;
                while ((n = *pp) != 0) {
                    int k = (n->end[0].body != self);
                    Collider* e = n->end[1 - k].part;
                    while (e && !e->f4E0) e = (Collider*)e->parent;
                    if (e) {
                        switch (e->f4E0) {
                        case 1: {
                            Contact03* c = TakePoolSlot((u8*)self->world + 0x1AFC);
                            *c = *n;
                            c->next = *out;
                            *out = c;
                            break;
                        }
                        case 3:
                            *pp = n->next;
                            n->next = freed;
                            freed = n;
                            continue;
                        case 4:
                            *pp = n->next;
                            n->next = *out;
                            *out = n;
                            continue;
                        }
                    }
                    pp = &n->next;
                }
                *h->link = h->head;
                h = h->next;
            } while (h);
        }
        FreePooledContactChain((u8*)self->world, freed);
    }
}

s32 func_0013E658(void* a, s32 b);

s32 IsPointInsideCollider(Collider* self, Vec02* p)
{
    if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
        s32 inside = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*p), Vu0::Q(self->v140)))) < self->radius3CC;
        if (inside) {
            return 1;
        }
    }
    if (self->tree.nodes != 0 && func_0013E658(p, (s32)self->tree.nodes) != 0) {
        return 1;
    }
    return 0;
}

void SetColliderFlagBit52(Collider* self, u32 flag)
{
    self->flags538 = (self->flags538 & 0xFFEFFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 52);
}

void GetColliderFlagBit52(Collider* self, u32* out)
{
    u32 bit = (u32)(self->flags538 >> 52) & 1;
    *out = bit;
}

void NumberColliderParts(Collider* self, s32* index, Collider** list)
{
    ListFrame frame;
    self->index = *index;
    list[*index] = self;
    (*index)++;
    for (Collider* item = (Collider*)self->children.head; item; item = (Collider*)item->next)
        if (item->desc->flags & 2)
            item->desc03()->m35(item, index, list);
}

ASM_FUNC(func_001BC7F8);

// A row of what ComputeColliderImpulseResponse writes, one per part (Collider::index): the
// change of velocity and of spin.
struct ImpulseRow {
    Vec02 linear;           // 0x00
    Vec02 angular;          // 0x10
};

void ConstrainVectorByParentAnchor(Collider* self, Vec02* anchor, Vec02* in, Vec02* out, Vec02* dir);
void ApplyColliderInverseInertia(Collider* self, Vec02* in, Vec02* out);

void func_001BC828(void* self, s32 a1, Contact03* c, s32 idx, ContactEnd03* hit, ImpulseRow* rows)
{
    Vec02 dir;
    Vec02 v;
    Vec02 arm;
    Vec02 k;
    ContactEnd03* e = &c->end[idx];
    if (idx == 0) {
        dir = hit->v10;
    } else {
        Vu0::Q(v) = Vu0::FromFloat(-1.0f);
        Vu0::Q(dir) = Vu0::MulX(Vu0::Q(hit->v10), Vu0::Q(v));
    }
    for (Collider* b = c->end[idx].part; b != 0; b = (Collider*)b->parent) {
        if (b->flags538 & (1ULL << 54)) {
            if (b->flags538 & (1ULL << 56)) {
                break;
            }
            continue;
        }
        ImpulseRow* row = &rows[b->index];
        Vu0::Set(arm, Vu0::Cross(Vu0::Sub(Vu0::Q(e->v10), Vu0::Q(b->v140)), Vu0::Q(dir)));
        ConstrainVectorByParentAnchor(b, &b->v440, &dir, &v, &dir);
        Vu0::Q(k) = Vu0::FromFloat(1.0f / b->mass);
        Vu0::Q(row->linear) = Vu0::MulX(Vu0::Q(v), Vu0::Q(k));
        ApplyColliderInverseInertia(b, &arm, &row->angular);
        ConstrainVectorByParentAnchor(b, &b->v460, &row->angular, &row->angular, 0);
    }
}

INCLUDE_ASM(func_001BC978);

INCLUDE_ASM(func_001BCD00);

s32 CollectGroupItems(s32 count, Collider** roots, s32 cap, Contact03** out)
{
    s32 n = 0;
    s32 i;
    Collider* root;
    for (i = 0; i < count; i++) {
        root = roots[i];
        root->flags538 |= ((u64)1 << 58);
        for (Contact03* item = root->contacts4B4; item; item = item->next) {
            if (n >= cap) goto done;
            out[n++] = item;
        }
        Contacts03* gh = root->contacts;
        for (ContactRow03* g = gh->head; g; g = g->next) {
            if (g->other->flags538 & ((u64)1 << 58)) continue;
            for (Contact03* item = g->head; item; item = item->next) {
                if (n >= cap) goto done;
                out[n++] = item;
            }
        }
    }
done:
    {
        Collider** r = roots;
        if (count > 0) {
            i = count;
            do {
                root = *r;
                i--;
                r++;
                root->flags538 &= ~((u64)1 << 58);
            } while (i != 0);
        }
    }
    return n;
}

void CollectConnectedColliders(Collider* self, s32* outQueued, Collider** queue, s32* outFlagged, Collider** list)
{
    s32 nq = 1;
    s32 nl = 0;
    queue[0] = self;
    self->flags538 |= (u64)1 << 57;
    s32 qi;
    for (qi = 0; qi < nq; qi++) {
        Collider* x = queue[qi];
        ContactRow03* node = x->contacts->head;
        while (node != 0) {
            Collider* y = node->other;
            if ((y->flags538 & ((u64)1 << 57)) == 0 && node->head != 0) {
                if (y->flags538 & ((u64)1 << 55)) {
                    list[nl] = y;
                    nl++;
                } else {
                    queue[nq] = y;
                    nq++;
                }
                y->flags538 |= (u64)1 << 57;
            }
            node = node->next;
        }
    }
    if (nl > 0) {
        qi = nl;
        Collider** p = list;
        do {
            Collider* z = *p;
            p++;
            z->flags538 &= ~((u64)1 << 57);
        } while (--qi != 0);
    }
    *outQueued = nq;
    *outFlagged = nl;
}

void SetColliderForcedState(Collider* obj, s32 mode)
{
    if (mode) {
        u64 f = obj->flags538;
        u64 sv = obj->savedC0;
        sv &= ~(u64)1;
        sv |= (f >> 54) & 1;
        sv &= ~(u64)2;
        u64 b55 = (f >> 55) & 1;
        f |= (u64)1 << 54;
        s32 a = obj->mode450;
        s32 b = obj->mode470;
        f |= (u64)1 << 55;
        sv |= b55 << 1;
        obj->save90 = a;
        obj->save94 = b;
        obj->savedC0 = sv;
        obj->mode450 = 3;
        obj->mode470 = 3;
        obj->flags538 = f;
    } else {
        u64 bit0 = (s32)obj->savedC0 & 1;
        u64 bit1 = (u64)((s32)(obj->savedC0 >> 1) & 1);
        s32 a = obj->save90;
        s32 b = obj->save94;
        obj->mode450 = a;
        obj->mode470 = b;
        obj->flags538 = ((obj->flags538 & ~((u64)1 << 54)) | (bit0 << 54)) & ~((u64)1 << 55) | (bit1 << 55);
    }
}

void SortCollidersByContactCount(s32 n, Collider** objs)
{
    s32 local[5];
    Collider** sorted;
    s32* counts;
    s32 i;

    if (n < 2) {
        return;
    }
    PushBackMemoryMark();
    sorted = (Collider**)AllocateBackMemory(n * 4);
    counts = (s32*)AllocateBackMemory(n * 4);
    FillMemory(counts, 0, n * 4);
    FillMemory(local, 0, 20);
    for (i = 0; i < n; i++) {
        Collider* o = objs[i];
        u32 cnt = 0;
        ContactRow03* p = o->contacts->head;
        while (p != 0) {
            if (p->head != 0 && (o->flags538 & 0x0080000000000000ULL) != 0) {
                cnt++;
                if (cnt >= 4) {
                    break;
                }
            }
            p = p->next;
        }
        counts[i] = cnt;
        if (cnt < 4) {
            local[cnt + 1]++;
        }
    }
    i = 1;
    do {
        local[i] += local[i - 1];
        i++;
    } while ((u32)i < 5);
    for (i = 0; i < n; i++) {
        s32 cnt = counts[i];
        s32 idx = local[cnt];
        sorted[idx] = objs[i];
        local[cnt] = idx + 1;
    }
    CopyMemory(objs, sorted, n * 4);
    PopBackMemoryMark();
}

void ProcessColliderGroup(World* ctx, s32 n, Collider** arr, f32 f, s32 ex)
{
    Contact03* buf[0x40];
    ListFrame it;
    s32 v = CollectGroupItems(n, arr, 0x40, buf);
    if (v < 0x40 || n < 2) {
        SolveColliderGroupContacts(ctx, n, arr, v, buf, f, ex);
        return;
    }
    SortCollidersByContactCount(n, arr);
    s32 half = n / 2;
    s32 i;
    u8* p;
    for (i = 0; i < half; i++) {
        arr[i]->flags538 |= 1ULL << 58;
    }
    ProcessColliderGroup(ctx, n - half, arr + half, f, ex);
    for (i = 0; i < half; i++) {
        arr[i]->flags538 &= ~(1ULL << 58);
    }
    for (i = half; i < n; i++) {
        ListWalk::Begin(&it, &arr[i]->parts);
        for (p = ListWalk::Next(&it); p; p = ListWalk::Next(&it)) {
            SetColliderForcedState(p, 1);
        }
        ListWalk::End(&it);
    }
    ProcessColliderGroup(ctx, half, arr, f, ex);
    for (i = half; i < n; i++) {
        ListWalk::Begin(&it, &arr[i]->parts);
        for (p = ListWalk::Next(&it); p; p = ListWalk::Next(&it)) {
            SetColliderForcedState(p, 0);
        }
        ListWalk::End(&it);
    }
}

void ProcessColliderGroups(World* self, s32 flags, f32 f)
{
    ListFrame fr;
    ConnectedCounts c;
    Collider** arr1;
    Collider** arr2;
    s32 j;
    s32 i;
    Collider* s;
    PushBackMemoryMark();
    arr1 = (Collider**)AllocateBackMemory(self->count38 * 4);
    c.n1 = 0;
    arr2 = (Collider**)AllocateBackMemory(self->count38 * 4);
    c.n2 = 0;
    SyncDataCache(0);
    if (flags & 1) {
        s32 e = (s32)&self->list60;
        fr.link = (u8*)e;
        fr.list = (void*)e;
        s32 old = (s32)g_activeListFrames;
        s32 link = *(s32*)(e + 8);
        g_activeListFrames = &fr;
        fr.prev = (ListFrame*)old;
        s32 h = *(s32*)e;
        fr.offset = link;
        fr.link = (u8*)(h + link);
        s32 p = h;
        while (p != 0) {
            Collider* node = (Collider*)p;
            if (!(node->desc->flags & 2) || (node->flags538 & (1ULL << 55))) {
                if (node->tries < 2) {
                    ((ColliderStepFn)node->desc->m1B)(node, 0, g_gameClock[2]);
                }
            }
            s32 nx = *(s32*)fr.link;
            fr.link = (u8*)(nx + fr.offset);
            p = nx;
        }
        g_activeListFrames = fr.prev;
    }
    for (s = (Collider*)self->list6C.head; s != 0; s = (Collider*)((ListedCollider*)s)->next) {
        if (s->flags538 & (1ULL << 57)) continue;
        if (s->flags538 & (1ULL << 55)) continue;
        CollectConnectedColliders(s, &c.n1, arr1, &c.n2, arr2);
        if (flags & 1) {
            for (i = 0; i < c.n1; i++) {
                if (arr1[i]->tries < 2) break;
            }
            if (i >= c.n1) {
                for (j = 0; j < c.n2; j++) {
                    if (arr2[j]->tries < 2) break;
                }
                if (j >= c.n2) continue;
            }
            for (i = 0; i < c.n1; i++) {
                ((ColliderStepFn)arr1[i]->desc->m1B)(arr1[i], 0, g_gameClock[2]);
            }
        }
        ProcessColliderGroup(self, c.n1, arr1, f, flags);
        for (i = 0; i < c.n1; i++) {
            if (!IsObjectTreeAtRest(arr1[i])) {
                ClearRootTries(arr1[i]);
            }
        }
    }
    for (s = (Collider*)self->bodies.head; s != 0; s = *(Collider**)((u8*)s + 0x2D0)) {
        s->flags538 &= ~(1ULL << 57);
    }
    PopBackMemoryMark();
}

void SwapSortRecords(u8* base, s32 stride, s32 rowB, s32 rowA)
{
    s32* b = (s32*)(base + rowB * stride);
    s32* a = (s32*)(base + rowA * stride);
    for (s32 n = stride; n > 0; n -= 4) {
        s32 y = *a;
        s32 x = *b;
        *b = y;
        *a = x;
        a++;
        b++;
    }
}

void HeapSortRecords(u8* base, s32 n, s32 size, SortCompareFn cmp)
{
    if (n < 2) return;
    s32 end = n - 1;
    s32 start = n / 2;
    for (;;) {
        if (start > 0) {
            start--;
        } else {
            SwapSortRecords(base, size, end, 0);
            s32 t = end;
            end = t - 1;
            if (t < 2) return;
        }
        s32 i = start;
        s32 c = 2 * i + 1;
        if (end < c) continue;
        for (;;) {
            if (c < end) {
                s32 s0 = c + 1;
                if (cmp(base + c * size, base + s0 * size) < 0) c = s0;
            }
            if (cmp(base + i * size, base + c * size) < 0) {
                SwapSortRecords(base, size, i, c);
                i = c;
                c = c + (c + 1);
                if (end < c) break;
                continue;
            }
            break;
        }
    }
}

void UnloadStagedBank(void)
{
    if (g_stagedBankHandle != 0) {
        if (g_stagedBankVoice != 0) {
            StopSoundVoice(g_stagedBankVoice);
        }
        UnloadSoundBank(g_stagedBankHandle);
        while (PollIopCommands() != 0) {
        }
        g_stagedBankHandle = 0;
    }
    g_stagedBankState = 0;
    g_stagedBankVoice = 0;
}

s32 EnsureSoundBankLoaded(s32 n)
{
    KeyId l;
    s32 h;
    if (n == g_loadedSoundBank) {
        return ((s32*)&g_soundBankHandles)[n];
    }
    if (n == 0) {
        h = ((s32*)&g_soundBankHandles)[0];
        if (h != 0) {
            return h;
        }
    } else {
        UnloadStagedBank();
        if (g_loadedSoundBank >= 0 && (h = ((s32*)&g_soundBankHandles)[g_loadedSoundBank]) != 0) {
            UnloadSoundBank();
            while (PollIopCommands() != 0) {
            }
            ((s32*)&g_soundBankHandles)[g_loadedSoundBank] = 0;
            NotifyIopBanksChanged();
        }
        g_loadedSoundBank = n;
    }
    ClearKeyId(&l);
    const KeyRecord* e = &g_soundBankKeys[n];
    s32 ok;
    if (e == 0) {
        ok = 0;
    } else {
        l.second = e->wordB ^ e->maskB;
        l.first = e->wordA ^ e->maskA;
        ok = l.second != 0;
    }
    if (ok) {
        while (WaitDiscReady(0) != 2) {
        }
        SyncDiscRead(0);
        s32 r = LoadSoundBankAtLocation(l.first, 0);
        ((s32*)&g_soundBankHandles)[n] = r;
        if (r != 0) {
            NotifyIopBanksChanged();
            if (((s32*)&g_soundBankLoaded)[n] == 0) {
                ((s32*)&g_soundBankLoaded)[n] = 1;
                for (s32 i = 0; i < 0x303; i++) {
                    if (g_soundEntries[i].bank == n) {
                        ((s32*)&g_soundEntryAvailable)[i] = TestSoundInBank(((s32*)&g_soundBankHandles)[n], g_soundEntries[i].index) != 0 || g_soundEntryForcedAvailable[i] != 0;
                    }
                }
            }
        }
    }
    return ((s32*)&g_soundBankHandles)[n];
}

s32 EnsureSoundEntryBankLoaded(s32 idx)
{
    return EnsureSoundBankLoaded(g_soundEntries[idx].bank);
}

void InitSoundParams(SoundRecord** self)
{
    *self = (SoundRecord*)AllocateZeroedFrontMemory(0x24);
    (*self)->f00 = -1;
    (*self)->f04 = 3000.0f;
    (*self)->f08 = 300.0f;
    (*self)->f0C = 1.0f;
    (*self)->f10 = 0;
    (*self)->f1C = 0;
    (*self)->f14 = -1.0f;
    (*self)->f20 = 0;
}

s32 IsSoundEntryAvailable(s32 idx)
{
    const SoundEntry* p = g_soundEntries + idx;

    if (((s32*)g_soundBankLoaded)[p->bank] == 0) {
        EnsureSoundEntryBankLoaded(idx);
    }
    return ((s32*)g_soundEntryAvailable)[idx];
}

void ClearStreamVoicePending(void)
{
    g_streamVoicePending = 0;
}

s32 IsStreamVoiceLocked(void) { return g_streamVoiceLocked; }

void StartLockedStreamVoice(KeyRecord* self)
{
    if (g_streamVoiceLocked != 0) {
        return;
    }
    if (self == 0) {
        return;
    }
    KeyId l;
    KeyId* p;
    if (HasStreamVoice() != 0) {
        StopStreamVoice();
    }
    p = &l;
    ClearKeyId(p);
    s32 b = self->wordB ^ self->maskB;
    p->second = b;
    p->first = self->wordA ^ self->maskA;
    if (b == 0) {
        return;
    }
    s32 h = StartStreamedVoice(p->first, 0, 0, 0, 0x400, 0, 2, 0, 0);
    if (h == 0) {
        return;
    }
    g_streamVoice = h;
    g_streamVoiceLocked = 1;
    g_streamVoicePending = 0;
    SetVolumeChannelFactor(8, 1, 0.5f);
    SetVolumeChannelFactor(8, 0, 0.5f);
    SetVolumeChannelFactor(8, 3, 0.5f);
}

void StopLockedStreamVoice(void)
{
    g_streamVoiceLocked = 0;
    StopStreamVoice();
}

void OpenKeyRecord(KeyRecord* self)
{
    if (g_streamVoiceLocked != 0) {
        return;
    }
    KeyId l;
    KeyId* p;
    if (HasStreamVoice() != 0) {
        StopStreamVoice();
    }
    p = &l;
    ClearKeyId(p);
    s32 r = 0;
    if (self != 0) {
        s32 b = self->wordB ^ self->maskB;
        p->second = b;
        l.first = self->wordA ^ self->maskA;
        r = b != 0;
    }
    if (r == 0) {
        return;
    }
    s32 h = StartStreamedVoice(l.first, 0, 0, 0, 0x400, 0, 2, 0, 1);
    if (h == 0) {
        return;
    }
    g_streamVoice = h;
    g_streamVoicePending = 1;
    RequestStreamCallback(h, ClearStreamVoicePending, (u32)h);
}

s32 CheckStreamVoicePending(void)
{
    if (g_streamVoiceLocked != 0)
        return 0;
    if (g_streamVoice != 0) {
        if (g_streamVoicePending != 0)
            return 1;
        QueryIopStreamVoice(g_streamVoice);
    }
    return 0;
}

void ApplySoundRecordVolumePan(PlayingSound* self)
{
    s32 a1 = (s32)(self->volume * 1024.0f);
    s32 a2;
    if (0.0f < self->pan) {
        a2 = (s32)((self->pan + 2.0f) * 179.5f) - 359;
    } else {
        a2 = (s32)((self->pan + 2.0f) * 179.5f);
    }
    SetVoiceVolumePan(self->voice, a1, a2);
}

void PlaySoundAndApplyVolumePan(s32 a0, PlayingSound** a1, f32 f12, f32 f13)
{
    s32 flag = 0;
    PlayingSound* local;
    PlayingSound** p = a1;
    if (p == 0) {
        flag = 1;
        p = &local;
    }
    StartSoundEffect(-2, p, a0, 0, f12, f13, 1.0f, 0.0f, 0.0f, 0, 0);
    if (*p != 0) {
        ApplySoundRecordVolumePan(*p);
        if (flag != 0) {
            ClearSoundRecordHandle(p);
        }
    }
}

s32 HasStreamVoice(void)
{
    return g_streamVoice != 0;
}

LINKER_REMNANT(func_001BE990);

void StopStreamVoice(void)
{
    s32 r;
    if (g_streamVoiceLocked != 0) return;
    if (g_streamVoice == 0) return;
    StopSoundVoice(g_streamVoice);
    while ((r = IsVoiceBusy(g_streamVoice)) != 0) {
        r = 0x4E20;
        while (--r >= 0) {
        }
    }
    g_streamVoice = 0;
    g_streamVoicePending = 0;
}

void PauseStreamVoice(void)
{
    if (g_streamVoice != 0) {
        PauseIopVoice(g_streamVoice);
    }
}

void ResumeStreamVoice(void)
{
    if (g_streamVoice != 0) {
        ResumeIopVoice(g_streamVoice);
    }
}

void StopStagedBankVoice(void)
{
    if (g_stagedBankState == 3) {
        StopSoundVoice(g_stagedBankVoice);
        g_stagedBankVoice = 0;
        g_stagedBankState = 2;
    }
}

void StoreStagedBankHandle(s32 h)
{
    g_stagedBankHandle = h;
    if (h != 0) {
        NotifyIopBanksChanged();
        g_stagedBankState = 2;
    } else {
        g_stagedBankRecord = 0;
        g_stagedBankState = 0;
    }
}

void RequestStagedBank(KeyRecord* self)
{
    s32 local[2];
    s32 same;
    s32 flag;

    if (self == 0) {
        StopStagedBankVoice();
        return;
    }
    KeyRecord* old = (KeyRecord*)g_stagedBankRecord;
    if (self == old) {
        same = 1;
    } else if (self == 0) {
        same = 0;
    } else if (old == 0) {
        same = 0;
    } else {
        same = ((self->idA ^ self->idB) ^ (old->idA ^ old->idB)) == 0;
    }
    if (same != 0 && g_stagedBankState != 0) {
        return;
    }
    while (PollIopCommands() != 0 && g_stagedBankState == 1) {
        SyncDataCache(0);
    }
    UnloadStagedBank();
    g_stagedBankRecord = (s32)self;
    ClearKeyId(local);
    if (self == 0) {
        flag = 0;
    } else {
        s32 x = self->wordB ^ self->maskB;
        local[0] = self->wordA ^ self->maskA;
        local[1] = x;
        flag = x != 0;
    }
    if (flag != 0) {
        g_stagedBankState = 1;
        SyncDiscRead(0);
        StartSoundBankLoad(local[0], 0, (void*)StoreStagedBankHandle, 0);
    }
}

void PlayStagedBank(void* self)
{
    RequestStagedBank(self);
    if (self == 0) return;
    while (PollIopCommands() != 0 && g_stagedBankState == 1) {
        SyncDataCache(0);
    }
    if (g_stagedBankState == 2) {
        s32 h = StartSoundVoice(g_stagedBankHandle, 0, 0x400, -1, 0, 0);
        g_stagedBankVoice = h;
        if (h == 0) return;
        g_stagedBankState = 3;
    }
}

void SilenceVolumeChannel2(void)
{
    SetVolumeChannelFactor(2, 1, 0.0f);
}

void RestoreVolumeChannel2(void)
{
    SetVolumeChannelFactor(2, 1, 1.0f);
}

void PauseStagedBankVoice(void)
{
    PauseIopVoice(g_stagedBankVoice);
}

void ResumeStagedBankVoice(void)
{
    ResumeIopVoice(g_stagedBankVoice);
}

void* AllocateSoundLevelEntry(void)
{
    void* p = PopFreeSlot((u8*)g_currentWorld + 0x1BB8);
    if (p != 0) {
        FillMemory((u8*)p, 0, 12);
        AppendToList((u8*)g_currentWorld + 0x1BC4, p);
    }
    return p;
}

void RemoveSoundLevelEntry(void* self)
{
    RemoveFromList((u8*)g_currentWorld + 0x1BC4, self);
    PushFreeSlot((u8*)g_currentWorld + 0x1BB8, self);
}

void ClearSoundLevels(void)
{
    ListFrame it;
    ListWalk::Begin(&it, &g_currentWorld->list1BC4);
    SoundLevelEntry* node;
    for (node = (SoundLevelEntry*)ListWalk::Next(&it); node != 0; node = (SoundLevelEntry*)ListWalk::Next(&it)) {
        RemoveSoundLevelEntry(node);
    }
    SendIopSoundLevel(0x14);
    D_002748EC = 0;
    g_activeListFrames = it.prev;
    g_previousSoundLevel = 0;
    g_currentSoundLevel = 0;

}

void* PushSoundLevel(s32 x)
{
    s32 flag = IsListEmpty((u8*)g_currentWorld + 0x1BC4);
    SoundLevelEntry* p = (SoundLevelEntry*)AllocateSoundLevelEntry();
    s32 hi = 0x6B;
    s32 v = -20;
    if (x >= -20) {
        if (hi < x) v = hi; else v = x;
    }
    if (p != 0) {
        p->level = v;
        s32 cur = g_currentSoundLevel;
        if (cur < v || flag != 0) {
            g_currentSoundLevel = v;
            g_previousSoundLevel = cur;
        }
    }
    return p;
}

void RecomputeSoundLevel(void)
{
    ListFrame f;
    u8* P = (u8*)g_currentWorld + 0x1BC4;
    SoundLevelEntry* x;
    f.list = P;
    f.link = P;
    f.offset = *(s32*)(P + 8);
    f.prev = g_activeListFrames;
    g_activeListFrames = &f;
    if (IsListEmpty(P) != 0) {
        g_currentSoundLevel = 0;
    } else {
        g_currentSoundLevel = -20;
        SoundLevelEntry* x0 = *(SoundLevelEntry**)f.link;
        f.link = (u8*)x0 + f.offset;
        x = x0;
        if (x != 0) {
            do {
                s32 v = x->level;
                if (g_currentSoundLevel < v) {
                    g_currentSoundLevel = v;
                }
                SoundLevelEntry* y = *(SoundLevelEntry**)f.link;
                f.link = (u8*)y + f.offset;
                x = y;
            } while (x != 0);
        }
    }
    g_activeListFrames = f.prev;
}

void ReleaseSoundLevel(SoundLevelEntry* self)
{
    if (self != 0) {
        s32 key = self->level;
        RemoveSoundLevelEntry(self);
        if (key == g_currentSoundLevel) {
            RecomputeSoundLevel(self);
            s32 cur = g_currentSoundLevel;
            if (cur >= 0) {
                D_002748EC = 0;
            }
            g_previousSoundLevel = cur;
            SendIopSoundLevel(cur + 0x14);
            SetVolumeChannelFactor(7, 1, 1.0f);
            g_previousSoundLevel = -0x64;
        }
    }
}

void RemoveSoundLevelAndRecompute(SoundLevelEntry* self)
{
    if (self == 0) {
        return;
    }
    s32 k = self->level;
    RemoveSoundLevelEntry(self);
    if (k == g_currentSoundLevel) {
        g_previousSoundLevel = k;
        RecomputeSoundLevel(self);
    }
}

void InitSoundSystem(void)
{
    FillMemory(g_soundBankHandles, 0, 0x1C);
    InitIopCommandChannels();
    EnsureSoundBankLoaded(0);
    EnableIopDiscAccess(1, 0x2000, 1, 1);
    SendIopSoundLevel(0x14);
    ResetVolumeChannelFactors();
    func_0011D520(0, 1);
    func_0011D558(0, 0, 0x2F);
    func_0011D558(1, 0x18, 0x2F);
    func_0011D558(3, 0x18, 0x2F);
    func_0011D558(2, 0x18, 0x2F);
    func_0011E3A0(2, 4);
}

LINKER_REMNANT(func_001BF1E8);

s32 IsSoundEmitterUpdateDisabled(void) { return D_00274748; }

void ComputeSoundVolumeAndPan(f32 r, void* pos, f32* volume, f32* pan, f32 a, f32 b, f32 c)
{
    if (pos != 0) {
        if (b < r) {
            *volume = *pan = 0.0f;
            return;
        }
        if (c < r) {
            Camera* cam = g_camera;
            Vec02 d;
            f32 range = b - c;
            f32 away = b - r;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*(Vec02*)pos), Vu0::Q(*(Vec02*)((u8*)cam + 0x40)));
            Vu0::Q(d) = Vu0::DivX(Vu0::Q(d), Vu0::Length(Vu0::Q(d)));
            f32 across = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(*(Vec02*)((u8*)cam + 0x90))));
            f32 ratio = away / range;
            *pan = -across * 0.7f * (1.0f - ratio);
            *volume = a * ratio;
            return;
        }
    }
    *volume = a;
    *pan = 0.0f;
}

f32 MeasureCameraWeightedDistance(Vec02* a, Vec02* b)
{
    Vec02 d;
    Vec02 r;
    Vec02 k;
    Camera* cam = g_camera;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    f32 w = cam->ctl460.g18;
    u128 side = Vu0::Sub(Vu0::Q(d), Vu0::MulX(Vu0::Q(cam->g80), Vu0::Dot(Vu0::Q(d), Vu0::Q(cam->g80))));
    Vu0::Q(k) = Vu0::FromFloat(1.0f / ((1.0f - w) + w * 10.0f));
    u128 along = Vu0::MulX(Vu0::Q(cam->g80), Vu0::Dot(Vu0::Q(d), Vu0::Q(cam->g80)));
    Vu0::Q(r) = Vu0::Add(side, Vu0::MulX(along, Vu0::Q(k)));
    return Vu0::ToFloat(Vu0::Length(Vu0::Q(r)));
}

ASM_FUNC(func_001BF398);

void* GetSoundListenerPosition(void)
{
    SwitchedCollider* p = (SwitchedCollider*)GetActiveSwitchedCollider();
    u8* r;
    if (p != 0 && p->desc05()->m4A(p) != 0) {
        r = (u8*)p + 0x140;
    } else {
        r = (u8*)g_camera + 0x40;
    }
    return r;
}

s32 ConvertSpeedToPitchOffset(s32 speed);

void ComputeSoundRecordDoppler(PlayingSound* self)
{
    PlacedObject* source = (PlacedObject*)self->object;
    if (source == 0 || self->f5C <= 0.0001f) {
        self->pitchOffset = 0;
        return;
    }
    PlacedObject* listener = (PlacedObject*)GetActiveSwitchedCollider();
    if (listener != 0) {
        Vec02 rel;
        Vec02 away;
        Vec02 sourceVel;
        Vec02 listenerVel;
        ComputeObjectMotionInFrame(source, 0, &source->v140, &sourceVel, 0, 0, 0);
        ComputeObjectMotionInFrame(listener, 0, &listener->v140, &listenerVel, 0, 0, 0);
        Vu0::Q(rel) = Vu0::Sub(Vu0::Q(sourceVel), Vu0::Q(listenerVel));
        f32 scale = self->f5C * 3600.0f;
        Vu0::Q(away) = Vu0::Sub(Vu0::Q(listener->v140), Vu0::Q(source->v140));
        u128 unit = Vu0::DivX(Vu0::Q(away), Vu0::Length(Vu0::Q(away)));
        self->pitchOffset = ConvertSpeedToPitchOffset((s32)(Vu0::ToFloat(Vu0::Dot(unit, Vu0::Q(rel))) * scale * 6.24999984e-06f));
    } else {
        self->pitchOffset = 0;
    }
}

ListenerDistanceFn ChooseSoundListenerFunction(void)
{
    s32 n;
    if (IsTopCameraController((u8*)g_camera + 0x460) == 0) return MeasureListenerDistance;
    n = PeekStackValue((u8*)g_camera + 0x460);
    if (n >= 3) return MeasureListenerDistance;
    if (n <= 0) return MeasureListenerDistance;
    return MeasureCameraWeightedDistance;
}

f32 ComputeSoundListenerFactor(void* position)
{
    void* listener = GetSoundListenerPosition();
    return ChooseSoundListenerFunction()(listener, position);
}

void ComputeSoundAttenuation(void* self, f32* out, s32* flag, f32 a, f32 b, f32 c)
{
    if (self != 0) {
        f32 r = ComputeSoundListenerFactor(self);
        ComputeSoundVolumeAndPan(r, self, out, flag, a, b, c);
    } else {
        *out = a;
        *flag = 0;
    }
}

void* AllocateSoundRecord(void)
{
    void* s = PopFreeSlot((u8*)g_currentWorld + 0x1BA0);
    if (s) {
        FillMemory(s, 0, 0x90);
        AppendToList((u8*)g_currentWorld + 0x1BAC, s);
    }
    return s;
}

void ClearSoundRecordHandle(PlayingSound** slot)
{
    PlayingSound* e = *slot;
    e->owner = 0;
    *slot = 0;
}

void FreeSoundRecord(PlayingSound* self)
{
    if (self->owner != 0) {
        *self->owner = 0;
    }
    self->serial = -1;
    RemoveFromList((u8*)g_currentWorld + 0x1BAC, self);
    PushFreeSlot((u8*)g_currentWorld + 0x1BA0, self);
}

void StopSoundRecord(PlayingSound* self, s32 n)
{
    if (self != 0) {
        if (n == 0) {
            StopSoundVoice(self->voice);
        } else {
            f32 t = (f32)n * 0.24000001f;
            s32 q = (s32)t;
            FadeOutSoundVoice(self->voice, -4, q, 2);
        }
        FreeSoundRecord(self);
    }
}

void SetSoundRecordPitch(PlayingSound* p, f32 a)
{
    if (p == 0) {
        return;
    }
    if (a == p->pitch) {
        if (p->object == 0) {
            return;
        }
        if (!(0.0001f < p->f5C)) {
            return;
        }
    }
    s32 v0 = p->pitchBaseValid;
    p->pitch = a;
    if (v0 == 0) {
        p->pitchBase = GetSoundPitchBase(p->bank, g_soundEntries[p->entry].index);
        p->pitchBaseValid = 1;
    }
    s32 v = p->pitchBase + (s32)(p->pitch * 1524.0f) + p->pitchOffset;
    SetVoicePitch(p->voice, p->Clamp(v, -0x8000, 0x7FFF));
}

void SetSoundRecordVolume(PlayingSound* self, f32 a)
{
    if (self != 0) {
        f32 scale = a / self->baseVolume;
        f32 base = self->volume;
        self->baseVolume = a;
        self->volume = base * scale;
        ApplySoundRecordVolumePan(self);
    }
}

void InitSoundRecord(PlayingSound* self, PlayingSound** owner, s32 keepWhenFar, BaseObject* object, Quad16* position, f32 farRange, f32 nearRange, f32 baseVolume, f32 pitch, f32 f16, U64P* interval, U64P* p80)
{
    U64P keep = self->link;
    FillMemory(self, 0, 0x90);
    self->link = keep;
    if (object) position = (Quad16*)((u8*)object + 0x140);
    self->owner = owner;
    if (owner) *owner = self;
    self->pitch = pitch;
    self->f5C = f16;
    s32 id = g_nextSoundRecordId;
    self->serial = id++;
    self->keepWhenFar = keepWhenFar;
    self->object = object;
    self->farRange = farRange;
    self->nearRange = nearRange;
    self->baseVolume = baseVolume;
    self->finished = 0;
    g_nextSoundRecordId = id;
    self->pollTick = RandomIntInRange(0, 3);
    if (interval) self->interval.bytes = *interval; else self->interval.value = -1.0f;
    if (p80) self->f80.bytes = *p80; else self->f80.value = -1.0f;
    if (position) self->position = *position;
    s32 fl = 0;
    if (position || self->interval.value >= 0.0f) fl = 1;
    self->positional = fl;
    ComputeSoundAttenuation(position, &self->volume, &self->pan, baseVolume, farRange, nearRange);
    ComputeSoundRecordDoppler(self);
}

void StartSoundRecordVoice(PlayingSound* self, s32 idx)
{
    s32 link;
    s32 v3;
    if (idx != -2) {
        link = EnsureSoundEntryBankLoaded(idx);
        v3 = g_soundEntries[idx].index;
        self->bank = link;
    }
    self->entry = idx;
    self->startTime = g_gameTime[0];
    if (idx == -2) {
        v3 = g_streamVoice;
        self->silent = 0;
        self->voice = v3;
        return;
    }
    if (self->volume != 0.0f && self->interval.value < 0.0f) {
        s32 r = StartSoundVoice(link, v3, 0, 0, 0, 0);
        self->silent = 0;
        self->voice = r;
        ComputeSoundRecordDoppler(self);
        SetSoundRecordPitch(self, self->pitch);
        ApplySoundRecordVolumePan(self);
    } else {
        self->voice = 0;
        self->silent = 1;
    }
}

void ScheduleAmbientSoundRecord(PlayingSound* self)
{
    self->nextTime = g_gameTime[0] + RandomFloatInRange(self->interval.value, (&self->interval.value)[1]);
    if (self->object == 0) {
        f32 angle = RandomFloatInRange(0.0f, 6.2831855f);
        f32 r = RandomFloatInRange(self->f80.value, (&self->f80.value)[1]);
        u128 off = Vu0::FromFloats(Cosine(angle) * r, Sine(angle) * r, 0.0f);
        Vu0::Q(self->position) = off;
        Vu0::Q(self->position) = Vu0::Add(off, Vu0::Q(*(Vec02*)GetSoundListenerPosition()));
    }
}

void StartSoundEffect(s32 id, PlayingSound** out, s32 p2, s32 p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, s32 p5) {
    PlayingSound* s1;
    s32 s0;
    if (id == -1) return;
    if (id != -2) {
        s32 a1 = g_soundEntries[id].bank;
        if (a1 > 0 && a1 != g_currentWorld->f1D70) return;
        s0 = IsSoundEntryAvailable(id);
    } else {
        s0 = 0;
    }
    s1 = 0;
    if (p3 || p2 || out) {
        if (s0 == 0 && (p4 == 0 || *p4 < 0.0f)) {
            PlayingSound tmp;
            InitSoundRecord(&tmp, out, 0, p2, p3, fa, fb, fc, fd, fe, 0, 0);
            if (tmp.volume != 0.0f) {
                s1 = (PlayingSound*)AllocateSoundRecord();
                if (s1) {
                    tmp.link = s1->link;
                    *s1 = tmp;
                }
            } else if (id == -2) {
                SetVoiceVolumePan(g_streamVoice, 0, 0);
            }
            if (out) *out = s1;
        } else {
            s1 = (PlayingSound*)AllocateSoundRecord();
            if (!s1) return;
            InitSoundRecord(s1, out, s0, p2, p3, fa, fb, fc, fd, fe, p4, p5);
        }
        if (s1) {
            if (0.0f <= s1->interval.value) {
                ScheduleAmbientSoundRecord(s1);
                s1->nextTime = (*(f32*)&g_gameTime) + RandomFloatInRange(0.0f, s1->interval.value);
            }
            StartSoundRecordVoice(s1, id);
        }
    } else {
        s32 v = EnsureSoundEntryBankLoaded(id);
        StartSoundVoice(v, g_soundEntries[id].index, (s32)(fc * 1024.0f), 0, (s32)(fd * 1524.0f), 0);
    }
}

void MarkSoundRecordIfIdMatches(void* guard, s64 key)
{
    if (guard == 0) {
        s32 tag = (s32)(key >> 32);
        PlayingSound* r = (PlayingSound*)(s32)(key & 0xFFFFFFFFu);
        if (r->serial == tag) {
            r->finished = 1;
        }
    }
}

void SetVolumeChannel6Factors(s32 flag, f32 x)
{
    SetVolumeChannelFactor(6, 0, x);
    SetVolumeChannelFactor(6, 2, x);
    SetVolumeChannelFactor(6, 3, x);
    if (flag) {
        SetVolumeChannelFactor(6, 1, x);
    }
}

void UpdateSoundEmitters(void)
{
    PlayingSoundFrame f;
    if (IsSoundEmitterUpdateDisabled() != 0) return;
    void* v4 = GetSoundListenerPosition();
    ListenerDistanceFn v5 = ChooseSoundListenerFunction();
    u8* P = (u8*)g_currentWorld + 0x1BAC;
    ListFrame* saved = g_activeListFrames;
    f.list = P;
    f.link = P;
    f.offset = *(s32*)(P + 8);
    f.prev = saved;
    g_activeListFrames = &f;
    if (g_streamVoice != 0 && IsVoiceBusy(g_streamVoice) == 0) {
        if (g_streamVoiceLocked != 0) {
            SetVolumeChannelFactor(8, 1, 1.0f);
            SetVolumeChannelFactor(8, 0, 1.0f);
            SetVolumeChannelFactor(8, 3, 1.0f);
        }
        g_streamVoice = 0;
        g_streamVoiceLocked = 0;
        g_streamVoicePending = 0;
    }
    if (g_previousSoundLevel != -100) {
        s32 up = g_previousSoundLevel < g_currentSoundLevel;
        if (g_currentSoundLevel > 0 && up) {
            SendIopSoundLevel(g_currentSoundLevel + 0x14);
            g_previousSoundLevel = g_currentSoundLevel;
            SetVolumeChannelFactor(7, 1, 1.0f);
            D_002748EC = 0;
        } else {
            D_00274754 = D_00274754 - 1;
            if (D_00274754 < 0) {
                s32 a = g_previousSoundLevel;
                s32 v = (g_currentSoundLevel < a) ? a - 1 : a + 1;
                D_002748EC = (u32)v >> 31;
                g_previousSoundLevel = v;
                SendIopSoundLevel(v + 0x14);
                if (g_previousSoundLevel < 0) {
                    f32 cnv = (f32)g_previousSoundLevel;
                    f32 k = -0.05f;
                    f32 zero = 0.0f;
                    f32 one = 1.0f;
                    f32 x = cnv * k;
                    f32 y;
                    if (x < zero) y = zero;
                    else if (one < x) y = one;
                    else y = x;
                    f32 m = y * 0.6666667f;
                    SetVolumeChannelFactor(7, 1, (1.0f - y) + m);
                }
                D_00274754 = D_00274754 + 3;
            }
        }
        if (up ? !(g_previousSoundLevel < g_currentSoundLevel) : !(g_previousSoundLevel > g_currentSoundLevel)) {
            D_002748EC = (u32)g_previousSoundLevel >> 31;
            SendIopSoundLevel(g_currentSoundLevel + 0x14);
            g_previousSoundLevel = -100;
        }
    }
    PlayingSound* e;
    {
        while ((e = f.Next()) != 0) {
            u8* s1;
            f32 r;
            if (e->object != 0 && IsObjectAttached(e->object) == 0) {
                StopSoundRecord(e, 0);
                goto next;
            }
            if (e->silent == 0) {
                if (e->finished != 0) {
                    if (0.0f <= e->interval.value) {
                        e->voice = 0;
                    } else {
                        if (e->object != 0) e->object->desc->m0E(e->object, 9, e);
                        if (e->keepWhenFar == 0) goto kill;
                        StopSoundVoice(e->voice);
                        e->voice = 0;
                    }
                    e->finished = 0;
                    e->silent = 1;
                    goto next;
                }
                e->pollTick = (e->pollTick + 1) % 4;
                if (e->pollTick == 0) {
                    RequestVoiceCallback(e->voice, MarkSoundRecordIfIdMatches, ((s64)e->serial << 32) | (s64)(s32)e);
                }
            }
            if (0.0f <= e->interval.value) {
                f32* s1 = g_gameClock;
                if (s1[1] < e->nextTime) {
                    if (e->silent != 0) goto next;
                } else {
                    ScheduleAmbientSoundRecord(e);
                    if (e->silent != 0) {
                        if (s1[1] - D_00274750 < 1.0f) goto next;
                        D_00274750 = s1[1];
                    }
                }
            }
            if (e->positional == 0) goto next;
            {
                s1 = (u8*)&e->position;
                if (e->object != 0) s1 = (u8*)e->object + 0x140;
                r = v5(v4, s1);
                if (e->farRange < r) {
                    if (0.0f <= e->interval.value) goto next;
                    if (e->silent != 0) goto next;
                    if (e->keepWhenFar != 0 || 0.0f < e->nextTime) {
                        StopSoundVoice(e->voice);
                        e->voice = 0;
                        e->silent = 1;
                        goto next;
                    }
                kill:
                    StopSoundRecord(e, 0);
                    goto next;
                }
                ComputeSoundVolumeAndPan(r, s1, &e->volume, &e->pan, e->baseVolume, e->farRange, e->nearRange);
            }
            if (e->silent != 0 && e->entry != -2) {
                e->voice = StartSoundVoice(e->bank, g_soundEntries[e->entry].index, 0, 0, 0, 0);
                e->silent = 0;
            }
            ComputeSoundRecordDoppler(e);
            SetSoundRecordPitch(e, e->pitch);
            ApplySoundRecordVolumePan(e);
        next:;
        }
    }
    PollIopCommands();
    g_activeListFrames = f.prev;
}

void SetIopVolumeChannel8(f32 x)
{
    SetIopVolumeChannel(8, (s32)(x * 1024.0f));
}

void ApplyVolumeChannelFactors(s32 column)
{
    f32* p = &g_volumeChannelFactors[0][column];
    f32 prod = 1.0f;
    s32 n = 10;

    do {
        prod = prod * *p;
        p += 4;
        n--;
    } while (n >= 0);

    f32 one = 1.0f;

    if (prod < 0.0f) {
        prod = 0.0f;
    } else if (one < prod) {
        prod = one;
    }

    SetIopVolumeChannel(column, (s32)(prod * 1024.0f));
}

void SetVolumeChannelFactor(s32 row, s32 column, f32 value)
{
    g_volumeChannelFactors[row][column] = value;
    ApplyVolumeChannelFactors(column);
}

void ResetVolumeChannelFactors(void)
{
    CopyMemory(g_volumeChannelFactors, g_defaultVolumeChannelFactors, 0xB0);
    SetIopVolumeChannel8(1.0f);
    for (s32 i = 0; i < 4; i++) {
        ApplyVolumeChannelFactors(i);
    }
    SilenceVolumeChannel3(g_saveData->f19EC & 0x80);
    ApplySoundOptionFlag(g_saveData->f19EC & 0x40);
}

void SilenceVolumeChannel3(s32 flag)
{
    SetVolumeChannelFactor(3, 1, flag ? 0.0f : 1.0f);
}

s32 ApplySoundOptionFlag(s32 value)
{
    return SetIopSoundOptionFlag(value != 0);
}

void StopAllSoundsAndWait(void)
{
    StopAllIopSounds();
    StopWorldSoundRecords(0);
    ClearSoundLevels();
    ClearCachedVoiceParams();
    while (PollIopCommands() != 0) {
    }
    WaitForIopSoundStop(1);
    SyncDiscRead(0);
}

void StopWorldSoundRecords(void* item)
{
    if (g_currentWorld) {
        ListFrame it;
        u8* obj;
        ListWalk::Begin(&it, &g_currentWorld->list1BAC);
        for (obj = ListWalk::Next(&it); obj; obj = ListWalk::Next(&it)) {
            StopSoundRecord(obj, item);
        }
        ListWalk::End(&it);
    }
    PollIopCommands();
}

void PushIopChannel2Setting(World* self, s32 a, s32 b)
{
    if ((u32)self->channel2Count < 4) {
        SetIopChannelValue(2, D_00274808[a]);
        SetIopChannelValuePair(2, b, b);
        self->channel2[self->channel2Count].index = a;
        self->channel2[self->channel2Count].value = b;
        self->channel2Count++;
    }
}

void PopIopChannel2Setting(World* self)
{
    s32 n = self->channel2Count;
    if (n >= 2) {
        self->channel2Count = n - 1;
        SetIopChannelValue(2, D_00274808[self->channel2[n - 2].index]);
        SetIopChannelValuePair(2, self->channel2[self->channel2Count - 1].value, self->channel2[self->channel2Count - 1].value);
    }
}

void SetIopChannel2Setting(World* self, s32 index, s32 value)
{
    SetIopChannelValue(2, D_00274808[index]);
    SetIopChannelValuePair(2, value, value);
    self->channel2[0].index = index;
    self->channel2[0].value = value;
    self->channel2Count = 1;
}

void AddWorldSoundEntry(World* self, s32 key)
{
    if (self->soundCount < 16) {
        WorldSoundEntry* e = &self->soundEntries[self->soundCount];
        e->sound = key;
        e->repeat = D_00274820;
        e->range = D_00274828;
        self->soundCount++;
    }
}

void SetLastWorldSoundEntryFromPoint(World* self, Point2* p)
{
    s32 n = self->soundCount;
    if (n != 0) {
        WorldSoundEntry* e = &self->soundEntries[n - 1];
        e->range0 = 8000.0f - p->y * 50.0f;
        e->range1 = 8000.0f - p->x * 50.0f;
    }
}

void SetLastWorldSoundEntryValues(World* self, U64P* item)
{
    if (!self->soundCount) return;
    // &soundEntries[soundCount - 1], written from 0x1D70 as retail computes it
    WorldSoundEntry* e = (WorldSoundEntry*)((u8*)self + 0x1D70 + self->soundCount * 20);
    e->repeat = *item;
}

void StartWorldSoundEntries(World* self)
{
    for (s32 i = 0; i < self->soundCount; i++) {
        WorldSoundEntry* e = &self->soundEntries[i];
        StartSoundEffect(e->sound, D_002748E8, 0, 0, &e->repeat, &e->range, 8000.0f, 3000.0f, 1.0f, 0.0f, 0.0f);
    }
}

void SetCachedVoiceParam(s32 idx, s32 val)
{
    if (val != D_006053E0[idx]) {
        D_006053E0[idx] = val;
        SetVoiceParam(g_stagedBankVoice, idx, val);
    }
}

s32 GetCachedVoiceParam(s32 index)
{
    return D_006053E0[index];
}

void RefreshCachedVoiceParam(s32 i)
{
    D_006053E0[i] = GetVoiceParam(g_stagedBankVoice, i);
}

void ClearCachedVoiceParams(void)
{
    for (s32 i = 0; i < 8; i++) {
        SetCachedVoiceParam(i, 0);
    }
}

extern const RandomWalkSteps D_0024D2A8 = { { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, 1, -5, -5, -5, -5, 1, 1, -5, -5, -5, 1, 1, 1, -5, -5, 1, 1, 1, 1, -5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
extern const RandomWalkRows D_0024D350 = { { 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 } };

s32 StepBiasedRandomWalk() {
    RandomWalkSteps a = D_0024D2A8;
    RandomWalkRows b = D_0024D350;
    s32 r = RandomIntInRange(0, 5);
    D_00274830 += *(s32*)((u8*)&a + (b.v[D_00274830 + 12] * 24 + r * 4));
    return D_00274830;
}

void PlaySoundWithWanderingPitch(void)
{
    if (D_002748EC != 0) {
        f32 scale = (f32)StepBiasedRandomWalk();
        StartSoundEffect(0x77, 0, 0, 0, 0.0f, 0.0f, 0.5f, scale * 0.083333336f, 0.0f, 0, 0);
    }
}

INCLUDE_ASM(func_001C0F30);

void StartIdLinkedObject(IdLinkedObject* self)
{
    StartPlacedObject(self);
    SetObjectLinkId(self, self->linkId);
    self->desc->m03(self);
}

void SetObjectLinkId(IdLinkedObject* self, s32 v)
{
    if (self->link != 0) {
        DestroyStateWalker(self->link);
        self->link = 0;
    }
    s32 r = FindFirstObjectById(self->world, 0x101, v, self);
    self->linkTarget = r;
    if (r != 0) {
        self->link = CreateStateWalker(r, self, -1, 1);
    }
    self->linkId = v;
}

void InitListedPointObject(ListedPointObject* self)
{
    InitObject(self);
    self->f58 = 3.4028235e38f;
}

void RegisterListedPointObject(ListedPointObject* self)
{
    RegisterObject(self);
    AppendToList(&self->world->list1C84, self);
}

void UnregisterListedPointObject(ListedPointObject* self)
{
    UnregisterObject(self);
    RemoveFromList(&self->world->list1C84, self);
}

void CopyListedPointObject(ListedPointObject* self)
{
    KeptBits saved;
    saved = self->keep;
    CopyObjectData(self);
    self->keep = saved;
}

void LoadScriptEntryTable(World* self, BufferedStream* arg) {
    ScriptValue q0;
    ScriptValue q1;
    ScriptValue q2;
    s32 i = 0;
    InitScriptValue(&q0);
    self->f1EF0 = ReadBufferedU32(arg);
    self->f1EF4 = AllocateFrontMemory(self->f1EF0 << 3);
    s32 n1 = ReadBufferedU32(arg);
    s32 n2 = ReadBufferedU32(arg);
    for (i = 0; i < self->f1EF0; i++) {
        {
            WorldScriptEntry* e = (WorldScriptEntry*)self->f1EF4 + i;
            e->expr = ReadScriptValueChain(arg);
            e->scope = 0;
            if (D_00275714) {
                SkipBufferedBlock(arg);
                SkipBufferedBlock(arg);
                SkipBufferedBlock(arg);
            }
        }
    }
    if (D_00275714) {
        if (n1 > 0) { s32 k = n1; do SkipBufferedBlock(arg); while (--k); }
        if (n2 > 0) { s32 k = n2; do SkipBufferedBlock(arg); while (--k); }
    }
    s32 r = NewScriptScope();
    i = 0;
    self->f2C = (void*)r;
    AddUniqueMarkRoot(g_markStacks, r);
    self->f1EF8 = n1;
    SetScriptValueTag(&q0, 0);
    DefineScriptVariable(&q1, (s32)self->f2C, self->f1EF8, &q0);
    DestroyScriptValue(&q1, 2);
    if (self->f1EF0 > 0) {
        do {
            InitScriptValue(&q1);
            EvalScriptEntry(&q2, i, self);
            i++;
            AssignScriptValue(&q1, &q2);
            DestroyScriptValue(&q2, 2);
            DestroyScriptValue(&q1, 2);
        } while (i < self->f1EF0);
    }
    DestroyScriptValue(&q0, 2);
}

void* GetScriptEntryScope(s32 index, World* self)
{
    if (index == -1) {
        return 0;
    } else {
        WorldScriptEntry* e = (WorldScriptEntry*)((index << 3) + (u32)self->f1EF4);
        void* p = (void*)e->scope;
        if (p != 0) AddUniqueMarkRoot(g_markStacks, p);
        return p;
    }
}

ScriptValue* EvalScriptEntry(ScriptValue* self, s32 index, World* ctx)
{
    s32 off = index << 3;
    ScriptValue q;
    WorldScriptEntry* e;
    InitScriptValue(&q);
    e = (WorldScriptEntry*)(off + (s32)ctx->f1EF4);
    if (e->expr != 0 && e->scope == 0) {
        ScriptValue t;
        ((WorldScriptEntry*)(off + (s32)ctx->f1EF4))->scope = NewScriptScope();
        EvalScriptExpression(&t, ((WorldScriptEntry*)(off + (s32)ctx->f1EF4))->expr, ((WorldScriptEntry*)(off + (s32)ctx->f1EF4))->scope);
        AssignScriptValue(&q, &t);
        DestroyScriptValue(&t, 2);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

PropertyDescriptor* FindPropertyDescriptor(BaseObject* self, s32 key)
{
    PropertyList* entry = &g_classPropertyLists[self->desc->id];
    s32 lo = 0;
    s32 hi = entry->count - 1;
    const PropertyEntry* items = entry->entries;

    while (lo <= hi) {
        s32 mid = (lo + hi) >> 1;
        s32 k = items[mid].id;
        if (k == key) {
            return items[mid].prop;
        }
        if (key < k) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

ScriptValue* BuildScriptListFromCallback(ScriptValue* self, void* ctx, s32 v, PropertyGetter cb)
{
    ScriptValue q;
    ScriptListBuilder r;
    InitScriptValue(&q);
    r.type = v;
    r.head = 0;
    r.tail = 0;
    cb(ctx, &r);
    if (r.head != 0) {
        SetScriptValueChain(&q, r.head);
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

ScriptValue* ReadPropertyValue(ScriptValue* out, void* base, PropertyDescriptor* d)
{
    ScriptValue q;
    ScriptValue q2;
    s32 t20, t28, t2c, t30;
    f32 t24;
    char* p;
    PropertyGetter fn;
    InitScriptValue(&q);
    if (d->flags & 1) {
        s32* r = (s32*)TakeZeroedPoolEntry();
        r[0] = (s32)base;
        r[1] = d->f10;
        r[2] = d->argCount;
        SetScriptValueIntC(&q, (s32)r);
    } else if (d->flags & 2) {
        if (d->flags & 0x1000) {
            p = (char*)d->target(base, 0) + d->getter;
        } else {
            p = (char*)base + d->getter;
        }
        switch (d->type) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            SetScriptValueInt(&q, *(s32*)p);
            break;
        case 1:
            SetScriptValueFloat(&q, *(f32*)p);
            break;
        case 0:
            SetScriptValueBool(&q, *(s32*)p);
            break;
        case 2: {
            Quad16* r = (Quad16*)AcquireVectorAPayload();
            *r = *(Quad16*)p;
            SetScriptValueVectorA(&q, (f32*)r);
            break;
        }
        case 4: {
            void* r = AcquireMatrixPayload();
            CopyRotationMatrix(r, p);
            SetScriptValueMatrix(&q, (f32*)r);
            break;
        }
        case 9: {
            Quad16* r = (Quad16*)AcquireVectorBPayload();
            *r = *(Quad16*)p;
            SetScriptValueVectorB(&q, (f32*)r);
            break;
        }
        case 10: {
            ScriptPair* r = (ScriptPair*)AcquirePairPayload();
            *r = *(ScriptPair*)p;
            SetScriptValuePair(&q, (f32*)r);
            break;
        }
        case 11: {
            ScriptTriple* r = (ScriptTriple*)AcquireTriplePayload();
            *r = *(ScriptTriple*)p;
            SetScriptValueTriple(&q, (f32*)r);
            break;
        }
        case 13:
            break;
        default:
            if (d->type & 0x1000) {
                SetScriptValueInt(&q, *(s32*)p);
            } else if (d->type & 0x2000) {
                SetScriptValuePointerB(&q, (void*)*(s32*)p);
            }
            break;
        }
    } else {
        if (d->flags & 0x1000) {
            p = (char*)d->target(base, 0);
        } else {
            p = (char*)base;
        }
        if (d->flags & 4) {
            fn = (PropertyGetter)d->getter;
        } else {
            fn = *(PropertyGetter*)(*(char**)base + d->getter);
        }
        switch (d->type) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            fn(p, &t20);
            SetScriptValueInt(&q, t20);
            break;
        case 1:
            fn(p, &t24);
            SetScriptValueFloat(&q, t24);
            break;
        case 0:
            fn(p, &t28);
            SetScriptValueBool(&q, t28);
            break;
        case 2: {
            void* r = AcquireVectorAPayload();
            fn(p, r);
            SetScriptValueVectorA(&q, (f32*)r);
            break;
        }
        case 4: {
            void* r = AcquireMatrixPayload();
            fn(p, r);
            ResetMatrixHomogeneous(r);
            SetScriptValueMatrix(&q, (f32*)r);
            break;
        }
        case 9: {
            void* r = AcquireVectorBPayload();
            fn(p, r);
            SetScriptValueVectorB(&q, (f32*)r);
            break;
        }
        case 10: {
            void* r = AcquirePairPayload();
            fn(p, r);
            SetScriptValuePair(&q, (f32*)r);
            break;
        }
        case 11: {
            void* r = AcquireTriplePayload();
            fn(p, r);
            SetScriptValueTriple(&q, (f32*)r);
            break;
        }
        case 13:
            break;
        default:
            if (d->type < 0) {
                BuildScriptListFromCallback(&q2, base, d->type & 0x7fffffff, fn);
                AssignScriptValue(&q, &q2);
                DestroyScriptValue(&q2, 2);
            } else if (d->type & 0x1000) {
                fn(p, &t2c);
                SetScriptValueInt(&q, t2c);
            } else if (d->type & 0x2000) {
                fn(p, &t30);
                SetScriptValuePointerB(&q, (void*)t30);
            }
            break;
        }
    }
    CopyConstructScriptValue(out, &q);
    DestroyScriptValue(&q, 2);
    return out;
}

s32 AppendPropertyToScriptList(ScriptListBuilder* self, s32 value)
{
    PropertyDescriptor d;
    ScriptValue t;
    FillMemory(&d, 0, 0x20);
    d.flags = 2;
    d.type = self->type;
    d.getter = 0;
    R11B008Node* n = NewScriptValueNode();
    ReadPropertyValue(&t, value, &d);
    AssignScriptValue(n, &t);
    DestroyScriptValue(&t, 2);
    if (self->head != 0) {
        self->tail->next = n;
    } else {
        self->head = n;
    }
    self->tail = n;
    return 1;
}

s32 ScriptListContainsValue(ScriptValueFilter* filter, s32* val) {
    ScriptValue q;
    R11B008Node* l;
    InitScriptValue(&q);
    l = filter->list;
    if (l) {
        switch (filter->type) {
        case 1:
            SetScriptValueFloat(&q, *(f32*)val);
            break;
        case 0:
            SetScriptValueBool(&q, *val);
            break;
        case 2: case 4: case 9: case 10: case 11: case 13:
            break;
        default:
            if (filter->type & 0x1000) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
                SetScriptValueInt(&q, *val);
            } else if (filter->type & 0x2000) {
                SetScriptValuePointerB(&q, (void*)*val);
            }
            break;
        }
        while (l) {
            if (AreScriptValuesEqual(l, &q)) {
                DestroyScriptValue(&q, 2);
                return 1;
            }
            l = l->next;
        }
    }
    DestroyScriptValue(&q, 2);
    return 0;
}

ScriptValue* StoreScriptArguments(ScriptValue* out, s32 n, ScriptValue* args, const u32* kinds, void** dsts)
{
    ScriptValue q;
    ScriptValue a;
    ScriptValue b;
    ScriptValue c;
    s32 i;
    InitScriptValue(&q);
    for (i = 0; i < n; i++) {
        AssignScriptValue(&q, args + i);
        u32 t = kinds[i];
        void* d = dsts[i];
        switch (t) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
        case 20:
            if (q.tag == 0x14) {
                goto store;
            }
            InitScriptValue(&a);
            ConvertScriptValueToInt(&b, &q);
            AssignScriptValue(&a, &b);
            DestroyScriptValue(&b, 2);
            *(s32*)d = a.i;
            DestroyScriptValue(&a, 2);
            break;
        case 1:
            if (q.tag == 0x15) {
                *(f32*)d = q.f;
            } else {
                InitScriptValue(&a);
                ConvertScriptValueToFloat(&c, &q);
                AssignScriptValue(&a, &c);
                DestroyScriptValue(&c, 2);
                *(f32*)d = a.f;
                DestroyScriptValue(&a, 2);
            }
            break;
        case 4:
            *(Mat02*)d = *(Mat02*)q.p;
            break;
        case 2:
        case 9:
            *(Quad16*)d = *(Quad16*)q.p;
            break;
        case 10:
            *(ScriptPair*)d = *(ScriptPair*)q.p;
            break;
        case 11:
            *(ScriptTriple*)d = *(ScriptTriple*)q.p;
            break;
        default:
            if (t & 0x1000) {
                goto store;
            }
            if (t & 0x2000) {
                goto store;
            }
            break;
        case 0:
        store:
            *(s32*)d = q.i;
            break;
        case 13:
            break;
        }
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(out, &q);
    DestroyScriptValue(&q, 2);
    return out;
}

ScriptValue* BuildScriptListFromPairs(ScriptValue* self, s32 n, s32* keys, s32* vals)
{
    ScriptValue q;
    ScriptListBuilder list;
    InitScriptValue(&q);
    list.head = 0;
    list.tail = 0;
    for (s32 i = 0; i < n; i++) {
        list.type = keys[i];
        AppendPropertyToScriptList(&list, vals[i]);
    }
    if (list.head) {
        SetScriptValueChain(&q, list.head);
    } else {
        SetScriptValueTag(&q, 0);
    }
    CopyConstructScriptValue(self, &q);
    DestroyScriptValue(&q, 2);
    return self;
}

INCLUDE_RODATA(jtbl_0024D510);
INCLUDE_ASM(func_001C1F20);

ScriptValue* GetObjectProperty(ScriptValue* self, BaseObject* p, s32 n)
{
    if (n < 0x495) {
        s32 r = (s32)FindPropertyDescriptor(p, n);
        ReadPropertyValue(self, p, r);
    } else {
        ScriptValue q;
        InitScriptValue(&q);
        FindKeyedValue((R11B008List*)p->f04, n, &q);
        CopyConstructScriptValue(self, &q);
        DestroyScriptValue(&q, 2);
    }
    return self;
}

ScriptValue* UpdateObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value)
{
    if (key < 0x495) {
        void* v = FindPropertyDescriptor(p, key);
        WritePropertyValue(self, p, v, value);
    } else {
        UpdateKeyedValue(self, (R11B008List*)p->f04, key, value);
    }
    return self;
}

ScriptValue* AddObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value)
{
    EnsureKeyedList(p);
    AddKeyedValue(self, (R11B008List*)p->f04, key, value);
    return self;
}

ScriptValue* SetExtraObjectProperty(ScriptValue* self, BaseObject* p, s32 key, ScriptValue* value)
{
    EnsureKeyedList(p);
    if (FindKeyedValue((R11B008List*)p->f04, key, 0)) UpdateKeyedValue(self, (R11B008List*)p->f04, key, value);
    else AddKeyedValue(self, (R11B008List*)p->f04, key, value);
    return self;
}

ScriptValue* StoreScriptArgumentsVa(ScriptValue* ret, s32 count, ScriptValue* args, const void* kinds, ...)
{
    void* arr[32];
    void* ap = (char*)__builtin_next_arg(kinds) - 32;
    if (count > 0) {
        void** d = arr;
        s32 i = count;
        do {
            ap = (char*)ap + 8;
            *d = *(void**)((char*)ap - 8);
            d++;
            i--;
        } while (i != 0);
    }
    StoreScriptArguments(ret, count, args, (const u32*)kinds, arr);
    return ret;
}

void StartToSprChain(s32 size, ...)
{
    char* ap;
    SprTransfer* e = &D_002748F0[1 - D_00274990];
    s32 n = 0;
    ap = (char*)__builtin_next_arg(size) - (8 - __builtin_args_info(0)) * 8;
    u32 addr = e->base;
    if (e->state == 3) {
        WaitDmaChannel((*(void**)&g_fromSprChannel), 0, 0);
    }
    e->state = 1;
    s32 data = VA_ARG_WORD(ap, s32);
    if (size != 0) {
        do {
            s32 nsize = VA_ARG_WORD(ap, s32);
            size = (size + 15) & ~15;
            addr += 16;
            e->sizes[n] = size;
            e->addrs[n] = addr;
            addr += size;
            s32 ndata = VA_ARG_WORD(ap, s32);
            if (data != 0) {
                e->tags[n].lo = (u64)(size >> 4) | ((u64)(ndata != 0 ? 3 : 0) << 28) | ((u64)data << 32);
            }
            data = ndata;
            size = nsize;
            n++;
        } while (size != 0);
    }
    e->count = n;
    SprDmaChannel* c = g_toSprChannel;
    c->chcr |= 0x40;
    c->sadr = (e->base & 0x0FFFFFFF) | 0x80000000;
    StartDmaChain(c, (u32)e->tags & 0x0FFFFFFF);
}

void StartFromSprChain(s32 first, ...) {
    s32 buf[8];
    SprTransfer* r = &D_002748F0[D_00274990];
    s32 n = 0;
    s32 x = first;
    r->state = 3;
    WaitDmaChannel(g_fromSprChannel, 0, 0);
    void* ap = (char*)__builtin_next_arg(first) - 56;
    while (x) {
        buf[n] = x;
        ap = (char*)ap + 8;
        x = *(s32*)((char*)ap - 8);
        n++;
    }
    s32 i = 0;
    n = r->count - n;
    while (n < r->count - 1) {
        *(u64*)(r->addrs[n] - 0x10) = ((r->sizes[n] >> 4) | 0x10000000) | ((u64)buf[i] << 32);
        n++;
        i++;
    }
    SprDmaChannel* d = g_fromSprChannel;
    *(u64*)(r->addrs[n] - 0x10) = ((r->sizes[n] >> 4) | 0x70000000) | ((u64)buf[i] << 32);
    d->chcr &= ~0x40;
    d->sadr = (r->base & 0xFFFFFFF) + 0x80000000;
    StartDmaChainToMemory(d);
    r = &D_002748F0[1 - D_00274990];
    if (r->state == 3) r->state = 0;
}

LINKER_REMNANT(func_001C27A8);

