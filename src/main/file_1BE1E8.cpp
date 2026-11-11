// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1BE1E8 to 0x1C1190 (its .rodata from 0x24D2A8, its .data from 0x274720): the
// sound system (the staged sound banks and stream voices, the sound levels, the sound records and
// their listener, attenuation and Doppler, the volume channels, the world's sound entries and the
// cached voice parameters, whose statics g_stagedBankState to D_002748EC only these functions
// read, apart from g_previousSoundLevel), then class 0x66 (an object linked by id) and class 0x81
// (a listed point object). Neither edge is proved by retail; both cuts follow the change of role,
// and retail's .rodata constrains them. This file's .rodata cannot hold a jump table: it starts at
// 0x24D2A8, off 16, where a file with one would be aligned to 16 (a build that put the script
// functions' jump tables here came out short), so the jump tables from 0x24D3C0 on begin another
// file and the cut after this file lies between InitListedPointObject (0x1C10A8, whose FLT_MAX at
// 0x24D3B4 is the last of this .rodata) and 0x1C15D8 (the first jump table's function); it is at
// 0x1C1190, where the script entries begin. The cut from collider.cpp at 0x1BE1E8 is the change
// from the collider to sound (collider.cpp says what range retail's data allows). The sound
// system alone cannot be a file: a cut at 0x1C0F30 would begin the next file's .rodata with that
// FLT_MAX, off 16, so classes 0x66 and 0x81 stay here unless they were a file of their own. Named
// after its first address: its families have no one name.
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
#include "mul_rotation.h"
#include "attached_set.h"
#include "active_set_solver.h"
#include "sound_level.h"
#define VA_ARG_WORD(ap, T) (*(T*)((ap += 8) - 8))

f32 RandomFloatInRange(f32 a, f32 b);
f32 Cosine(f32 a);
f32 Sine(f32 a);
extern f32 g_gameTime[];
void ReleaseSoundLevel(void* p);
void* AllocateZeroedFrontMemory(s32 size);
void* FillMemory(void* p, s32 value, s32 size);
void AppendToList(void* p, void* self);
void RemoveFromList(void* p, void* self);
void RemoveFromList(void* a, void* b);
void PushFreeSlot(void* a, void* b);
void InitPlacedObject(void* self);
void StartPlacedObject(void* self);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void* CreateStateWalker(void* bank, s32 r, s32 minus_one, s32 zero);
void AppendToList(List01* list, StateWalker* item);
struct RandomRangeLow { s32 v; };
s32 RandomIntInRange(RandomRangeLow lo, s32 hi);
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
void* FillMemory(void* p, s32 value, s32 size);
void InitIopCommandChannels(void);
s32 EnsureSoundBankLoaded(s32 a);
s32 EnableIopDiscAccess(s32 a, s32 b, s32 c, s32 d);
void SendIopSoundLevel(s32 a);
void ResetVolumeChannelFactors(void);
void QueueIopCommandD(s32 a, s32 b);
void QueueIopChannelConfig(s32 a, s32 b, s32 c);
void QueueIopCommand51(s32 a, s32 b);
void* PopFreeSlot(void* p);
void* FillMemory(void* p, s32 value, s32 size);
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
void* FillMemory(void* p, s32 value, s32 size);
void FadeOutSoundVoice(s32 voice, s32 a, s32 b, s32 c);
void ApplySoundRecordVolumePan(PlayingSound* self);
void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
void PauseIopVoice(s32 a);
void ResumeIopVoice(s32 a);
void AppendToList(u8* a, void* b);
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
s32 RandomIntInRange(s32 a, s32 b);
void ComputeSoundAttenuation(Quad16* position, f32* volume, f32* pan, f32 a, f32 b, f32 c);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
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

void* FillMemory(void* p, s32 value, s32 size);
extern f32 g_defaultVolumeChannelFactors[11][4];
extern s32 D_00274808[];
void SetIopChannelValue(s32 channel, s32 value);
void SetIopChannelValuePair(s32 channel, s32 value, s32 value2);
void* FillMemory(void* p, s32 value, s32 size); // stays void: retail returns a value, but declared so func_001C1A28 differs in registers
s32 StepBiasedRandomWalk(void);
// func_001C0CF0's random walk: six steps for each of seven rows, and the row for each position
// from -12 to 12, copied to the stack.
struct RandomWalkSteps { s32 v[42]; };
struct RandomWalkRows { s32 v[25]; };
extern const RandomWalkSteps D_0024D2A8;
extern const RandomWalkRows D_0024D350;
extern s32 D_00274830;
void SetVoiceParam(s32 voice, s32 a1, s32 a2);
void InitObject(BaseObject* self);
void StopSoundRecord(u8* obj, void* item);
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
extern const s32 g_soundEntryForcedAvailable[772];
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
void CopyMemory(void* dst, void* src, s32 count);

void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
void* FillMemory(void* p, s32 value, s32 size);
f32 RandomFloatInRange(f32 a, f32 b);

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
    QueueIopCommandD(0, 1);
    QueueIopChannelConfig(0, 0, 0x2F);
    QueueIopChannelConfig(1, 0x18, 0x2F);
    QueueIopChannelConfig(3, 0x18, 0x2F);
    QueueIopChannelConfig(2, 0x18, 0x2F);
    QueueIopCommand51(2, 4);
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

void InitIdLinkedObject(IdLinkedObject* self)
{
    InitPlacedObject(self);
    self->color = 0x80808080;
    self->f2D4 = 0.5f;
    self->f2D8 = 400.0f;
    self->f2DC = 0.5f;
    self->f2E0 = 0.5f;
    self->f320 = 0.3f;
    self->f324 = 0.5f;
    Vu0::Q(self->v2F0) = Vu0::FromFloats(0.0f, 0.0f, 50.0f);
    Vu0::Q(self->v300) = Vu0::FromFloats(100.0f, 80.0f, 50.0f);
    self->linkId = -1;
}

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