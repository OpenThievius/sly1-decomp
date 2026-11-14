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
// FLT_MAX, off 16, so classes 0x66 and 0x81 stay here unless they were a file of their own. Its
// name is ours, after the sound system, which holds most of its code.
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
#include "object_finder.h"
#include "list_walk.h"
#include "playing_sound.h"
#include "point2.h"
#include "functions/base_object.h"
#include "functions/camera_controller.h"
#include "functions/heap.h"
#include "functions/iop_commands.h"
#include "functions/placed_object.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#define VA_ARG_WORD(ap, T) (*(T*)((ap += 8) - 8))

extern "C" f32 Cosine(f32 x);
extern "C" f32 Sine(f32 x);
extern f32 g_gameTime[];
void ReleaseSoundLevel(SoundLevelEntry* self);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void AppendToList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);
void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);
#include "random_range_low.h"
extern s32 g_streamVoiceLocked;
void StopStreamVoice(void);
extern s32 g_stagedBankVoice;
void RequestStagedBank(KeyRecord* self);
extern "C" void SyncDataCache(s32 a);
void RemoveFromList(List01* list, void* item);
extern u8 g_soundBankHandles[];
extern "C" void* FillMemory(void* p, s32 value, s32 size);
s32 EnsureSoundBankLoaded(s32 a);
void ResetVolumeChannelFactors(void);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void AppendToList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);
void FreeSoundRecord(PlayingSound* self);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void ApplySoundRecordVolumePan(PlayingSound* self);
void SetVolumeChannelFactor(s32 a, s32 b, f32 x);
void AppendToList(List01* self, void* item);
extern s32 D_002748EC;
extern s32 g_currentSoundLevel;
extern s32 g_previousSoundLevel;
void RemoveSoundLevelEntry(void* self);
void RecomputeSoundLevel(SoundLevelEntry* entry);
typedef signed int s32;
typedef unsigned char u8;
extern s32 g_stagedBankState;
extern s32 g_stagedBankHandle;
void RemoveSoundLevelEntry(void* self);
void RecomputeSoundLevel(SoundLevelEntry* self);
extern s32 g_streamVoice;
// How far the listener is from a position (func_001BF2E0 or func_001BF398, as func_001BF578 chooses).
typedef f32 (*ListenerDistanceFn)(void* listener, void* position);
f32 MeasureListenerDistance(void* listener, void* position);
f32 MeasureCameraWeightedDistance(Vec02* a, Vec02* b);
extern s32 g_streamVoicePending;
s32 HasStreamVoice(void);
void ClearStreamVoicePending(s32 reply, s64 arg);
typedef void (*IopCallbackFn)(s32 reply, s64 arg);
void RequestStreamCallback(s32 a0, IopCallbackFn a1, u64 a2);
f32 ComputeSoundListenerFactor(void* self);
void ComputeSoundVolumeAndPan(f32 r, void* pos, f32* volume, f32* pan, f32 a, f32 b, f32 c);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void ClearSoundRecordHandle(PlayingSound** slot);
void StopStagedBankVoice(void);
void UnloadStagedBank(void);
void StoreStagedBankHandle(s32 h, s64 arg);
void StartSoundBankLoad(s32 a0, s32 a1, IopCallbackFn a2, s64 a3);
s32 IsListEmpty(List01* p);
void* AllocateSoundLevelEntry(void);
extern f32 g_gameClock[];
// A row of g_soundEntries (global_tables.cpp defines it): the bank a sound is in, -1 for none, and
// its index in that bank.
#include "sound_entry.h"
extern SoundEntry g_soundEntries[];
extern u8 g_soundBankLoaded[];
extern u8 g_soundEntryAvailable[];
s32 EnsureSoundEntryBankLoaded(s32 idx);
// NEAR: the lui of D_0026185C is scheduled before the sw of self->idx; retail stores idx first. Otherwise every instruction matches.

void ComputeSoundRecordDoppler(PlayingSound* self);
void SetSoundRecordPitch(PlayingSound* self, f32 x);
// NEAR: first load of the chain pointer lands in $v1 and the sum in $v0, retail has them in $v0/$v1; one instruction short so the final branch targets 0x1BF028 instead of 0x1BF02C

// NEAR: 23 diff lines, register allocation only: queue index in t1 (retail) vs v1 (ours), mask built in a0 vs a2, cleanup counter in t1 vs a0

extern const KeyRecord g_soundBankKeys[7];
extern "C" s32 WaitDiscReady(s32 mode);
s32 IsSoundEntryAvailable(s32 id);
void InitSoundRecord(PlayingSound* self, PlayingSound** owner, s32 keepWhenFar, BaseObject* object, Quad16* position, f32 farRange, f32 nearRange, f32 baseVolume, f32 pitch, f32 f16, U64P* interval, U64P* p80);
void ScheduleAmbientSoundRecord(PlayingSound* self);
void StartSoundRecordVoice(PlayingSound* self, s32 id);
// The list walk of list_iter.h over a List01: push the frame, take each element, pop the frame.
void ComputeSoundAttenuation(void* self, f32* out, s32* flag, f32 a, f32 b, f32 c);
// The list walk of World::list1BAC, element by element.
struct PlayingSoundFrame : ListFrame {
    PlayingSound* Next() { PlayingSound* n = *(PlayingSound**)link; link = (u8*)n + offset; return n; }
};
s32 IsSoundEmitterUpdateDisabled(void);
void* GetSoundListenerPosition(void);
void RequestVoiceCallback(s32 value, IopCallbackFn a1, u64 a2);
void MarkSoundRecordIfIdMatches(s32 reply, s64 key);
void ComputeSoundVolumeAndPan(f32 r, void* pos, f32* volume, f32* pan, f32 a, f32 b, f32 c);
void StopSoundRecord(PlayingSound* self, s32 n);
extern U64P g_defaultSoundRepeat;
extern U64P g_defaultSoundRange;
extern s32 g_cachedVoiceParams[];
void RemoveFromList(List01* list, void* item);
void SetCachedVoiceParam(s32 index, s32 value);
void AppendToList(List01* self, void* item);
extern s32 g_iopChannel2Values[6];
extern f32 g_volumeChannelFactors[11][4];
void ApplyVolumeChannelFactors(s32 column);
extern u8 g_worldSoundHandle[4];
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void StopWorldSoundRecords(s32 item);
void ClearSoundLevels(void);
void ClearCachedVoiceParams(void);

extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern f32 g_defaultVolumeChannelFactors[11][4];
extern s32 g_iopChannel2Values[];
extern "C" void* FillMemory(void* p, s32 value, s32 size);
s32 StepBiasedRandomWalk(void);
// func_001C0CF0's random walk: six steps for each of seven rows, and the row for each position
// from -12 to 12, copied to the stack.
struct RandomWalkSteps { s32 v[42]; };
struct RandomWalkRows { s32 v[25]; };
extern const RandomWalkSteps g_randomWalkSteps;
extern const RandomWalkRows g_randomWalkRows;
extern s32 g_randomWalkPosition;
void StopSoundRecord(PlayingSound* self, s32 n);
void SetIopVolumeChannel8(f32 x);
void SetVolumeChannelFactor(s32 row, s32 column, f32 value);
void SilenceVolumeChannel3(s32 flag);
void ApplySoundOptionFlag(s32 value);
void StopAllSoundsAndWait(void);
void StopWorldSoundRecords(s32 item);
void PushIopChannel2Setting(World* self, s32 a, s32 b);
void PopIopChannel2Setting(World* self);
void SetIopChannel2Setting(World* self, s32 index, s32 value);
void AddWorldSoundEntry(World* self, s32 key);
void SetLastWorldSoundEntryFromPoint(World* self, Point2* p);
void SetLastWorldSoundEntryValues(World* self, U64P* item);
void StartWorldSoundEntries(World* self);
void SetCachedVoiceParam(s32 idx, s32 val);
s32 GetCachedVoiceParam(s32 index);
void RefreshCachedVoiceParam(s32 i, s32 unused1);
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
s32 g_soundEmitterUpdateDisabled = 0;
s32 g_nextSoundRecordId = 0;
f32 g_lastSilentSoundTime = -2.0f;
s32 g_soundLevelStepCountdown = 3;
f32 g_defaultVolumeChannelFactors[11][4] = { 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
s32 g_iopChannel2Values[6] = { 0, 2, 3, 4, 9, 1 };
U64P g_defaultSoundRepeat = { 0x40C0000040800000ULL };
U64P g_defaultSoundRange = { 0x45FA0000453B8000ULL };
s32 g_randomWalkPosition = 0;
f32 g_volumeChannelFactors[11][4] = { 0 };
u8 g_worldSoundHandle[4] = { 0 };
s32 D_002748EC = 0;

extern "C" void* FillMemory(void* p, s32 value, s32 size);

// Stops the staged bank's voice, unloads the bank, waits for the IOP commands to drain and
// resets the staged state.
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

// Makes sound bank n the loaded one and gives its handle: bank 0 stays loaded; for another bank the
// staged bank and the previous one are unloaded first, then the bank is read from its disc location
// (named by its key record), and the first time that works the availability of every sound entry of
// the bank is recorded.
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
            UnloadSoundBank(h);
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

// Loads the bank that sound entry idx belongs to (if needed).
s32 EnsureSoundEntryBankLoaded(s32 idx)
{
    return EnsureSoundBankLoaded(g_soundEntries[idx].bank);
}

// Allocates a sound record's parameter block (0x24 bytes) with the defaults: no sound, far range
// 3000, near range 300, volume 1.
void InitSoundParams(SoundRecord** self)
{
    *self = (SoundRecord*)AllocateZeroedFrontMemory(0x24);
    (*self)->soundId = -1;
    (*self)->outerRange = 3000.0f;
    (*self)->innerRange = 300.0f;
    (*self)->baseVolume = 1.0f;
    (*self)->pitch = 0;
    (*self)->soundWord = 0;
    (*self)->f14 = -1.0f;
    (*self)->startParam = 0;
}

// Whether the sound entry idx can be played, loading its bank first if it is not loaded.
s32 IsSoundEntryAvailable(s32 idx)
{
    const SoundEntry* p = g_soundEntries + idx;

    if (((s32*)g_soundBankLoaded)[p->bank] == 0) {
        EnsureSoundEntryBankLoaded(idx);
    }
    return ((s32*)g_soundEntryAvailable)[idx];
}

// IOP reply callback: the stream voice's pending request is done.
void ClearStreamVoicePending(s32 reply, s64 arg)
{
    g_streamVoicePending = 0;
}

s32 IsStreamVoiceLocked(void) { return g_streamVoiceLocked; }

// Starts the streamed voice of a key record and locks it: stops any current stream voice, starts
// the stream, remembers it as g_streamVoice with its lock set and lowers channel 8's volume factors
// to one half. Does nothing when the voice is already locked or the key is empty.
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

// Unlocks the stream voice and stops it.
void StopLockedStreamVoice(void)
{
    g_streamVoiceLocked = 0;
    StopStreamVoice();
}

// Opens the streamed voice of a key record: unless one is locked, stops the current stream voice
// and starts the record's stream, marking it pending until the stream reports its start
// (ClearStreamVoicePending). Does nothing for an empty key.
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

// Gives 1 while an unlocked stream voice has a pending request; otherwise queries the IOP about
// the voice and gives 0.
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

// Sends a sound record's volume (x 1024) and its pan, mapped by (pan + 2) * 179.5 (less 359 for a
// positive pan), to its voice.
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

// Plays sound -2 for an object with the given ranges and applies its volume and pan at once; the
// handle is released again when the caller gave no slot for it.
void PlaySoundAndApplyVolumePan(BaseObject* a0, PlayingSound** a1, f32 f12, f32 f13)
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

// Stops the stream voice (unless it is locked), busy-waits until the IOP reports it stopped and
// forgets it.
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

// Pauses the stream voice, if there is one. ResumeStreamVoice undoes it.
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

// Stops the staged bank's voice (state 3) and goes back to state 2, loaded but not playing.
void StopStagedBankVoice(void)
{
    if (g_stagedBankState == 3) {
        StopSoundVoice(g_stagedBankVoice);
        g_stagedBankVoice = 0;
        g_stagedBankState = 2;
    }
}

// Callback of the staged bank's load: keeps the bank handle and goes to state 2 (loaded), or
// clears the record and the state when the load failed (handle 0).
void StoreStagedBankHandle(s32 h, s64 arg)
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

// Asks for the staged sound bank of a key record to be loaded in the background (nothing when it is
// already staged): waits for pending IOP commands, unloads the old staged bank and starts the load
// of the new one, with StoreStagedBankHandle taking the handle. A null record stops the staged
// bank's voice.
void RequestStagedBank(KeyRecord* self)
{
    KeyId local;
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
    ClearKeyId(&local);
    if (self == 0) {
        flag = 0;
    } else {
        s32 x = self->wordB ^ self->maskB;
        local.first = self->wordA ^ self->maskA;
        local.second = x;
        flag = x != 0;
    }
    if (flag != 0) {
        g_stagedBankState = 1;
        SyncDiscRead(0);
        StartSoundBankLoad(local.first, 0, StoreStagedBankHandle, 0);
    }
}

// Requests the staged sound bank of a key record, waits for it to finish loading (state 2) and
// starts its voice (state 3).
void PlayStagedBank(void* self)
{
    RequestStagedBank((KeyRecord*)self);
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

// Sets row 2's factor of channel 1 to 0; RestoreVolumeChannel2 sets it back to 1.
void SilenceVolumeChannel2(void)
{
    SetVolumeChannelFactor(2, 1, 0.0f);
}

void RestoreVolumeChannel2(void)
{
    SetVolumeChannelFactor(2, 1, 1.0f);
}

// Pauses the staged bank's voice; ResumeStagedBankVoice resumes it.
void PauseStagedBankVoice(void)
{
    PauseIopVoice(g_stagedBankVoice);
}

void ResumeStagedBankVoice(void)
{
    ResumeIopVoice(g_stagedBankVoice);
}

// Takes a sound level entry (12 bytes) from the world's pool and links it into the level list.
void* AllocateSoundLevelEntry(void)
{
    void* p = PopFreeSlot(&g_currentWorld->pool1BB8);
    if (p != 0) {
        FillMemory((u8*)p, 0, 12);
        AppendToList(&g_currentWorld->list1BC4, p);
    }
    return p;
}

void RemoveSoundLevelEntry(void* self)
{
    RemoveFromList(&g_currentWorld->list1BC4, self);
    PushFreeSlot(&g_currentWorld->pool1BB8, self);
}

// Removes every sound level entry of the world, sends the IOP level 0x14 (the lowest) and resets
// the current and previous levels.
void ClearSoundLevels(void)
{
    ListFrame it;
    ListWalkSteps::Begin(&it, &g_currentWorld->list1BC4);
    SoundLevelEntry* node;
    for (node = (SoundLevelEntry*)ListWalkSteps::Next(&it); node != 0; node = (SoundLevelEntry*)ListWalkSteps::Next(&it)) {
        RemoveSoundLevelEntry(node);
    }
    SendIopSoundLevel(0x14);
    D_002748EC = 0;
    g_activeListFrames = it.prev;
    g_previousSoundLevel = 0;
    g_currentSoundLevel = 0;

}

// Adds a sound level entry holding x (clamped to -20..0x6B); when it is higher than the current
// level (or the list was empty) it becomes the current level and the old one the previous level.
SoundLevelEntry* PushSoundLevel(s32 x)
{
    s32 flag = IsListEmpty(&g_currentWorld->list1BC4);
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

// Sets g_currentSoundLevel to the highest level among the world's sound level entries, or to 0
// when there are none (the floor for a non-empty list is -20).
void RecomputeSoundLevel(SoundLevelEntry* entry)
{
    ListFrame f;
    u8* P = (u8*)&g_currentWorld->list1BC4;
    SoundLevelEntry* x;
    f.list = P;
    f.link = P;
    f.offset = ((List01*)P)->offset;
    f.prev = g_activeListFrames;
    g_activeListFrames = &f;
    if (IsListEmpty((List01*)P) != 0) {
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

// Removes a sound level entry; if it was the current level, recomputes the level, sends the new
// one to the IOP (plus 0x14) and restores channel 7's factor.
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

// Removes a sound level entry and, when it was the current level, recomputes the level.
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

// Brings the sound system up at start: clears the bank handles, starts the IOP command channels,
// loads bank 0, resets the sound level and the volume factors and sends the IOP its channel set-up.
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

s32 IsSoundEmitterUpdateDisabled(void) { return g_soundEmitterUpdateDisabled; }

// The volume and pan of a positional sound at distance r: full base volume a up to the near range
// c, fading linearly to 0 at the far range b with the pan following the direction to the camera's
// side (0.7 at most), and 0 beyond b. Without a position it is the base volume with no pan.
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
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*(Vec02*)pos), Vu0::Q(*(Vec02*)cam->position));
            Vu0::Q(d) = Vu0::DivX(Vu0::Q(d), Vu0::Length(Vu0::Q(d)));
            f32 across = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(*(Vec02*)cam->f90)));
            f32 ratio = away / range;
            *pan = -across * 0.7f * (1.0f - ratio);
            *volume = a * ratio;
            return;
        }
    }
    *volume = a;
    *pan = 0.0f;
}

// The distance from a to b as heard through the camera: the part along the camera's axis is
// scaled down by 1 / ((1 - z) + z * 10), z being the camera controller's zoom fraction, so a
// zoomed-in view hears things along the view axis as nearer.
f32 MeasureCameraWeightedDistance(Vec02* a, Vec02* b)
{
    Vec02 d;
    Vec02 r;
    Vec02 k;
    Camera* cam = g_camera;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    f32 w = cam->ctl460.zoomFraction;
    u128 side = Vu0::Sub(Vu0::Q(d), Vu0::MulX(Vu0::Q(cam->g80), Vu0::Dot(Vu0::Q(d), Vu0::Q(cam->g80))));
    Vu0::Q(k) = Vu0::FromFloat(1.0f / ((1.0f - w) + w * 10.0f));
    u128 along = Vu0::MulX(Vu0::Q(cam->g80), Vu0::Dot(Vu0::Q(d), Vu0::Q(cam->g80)));
    Vu0::Q(r) = Vu0::Add(side, Vu0::MulX(along, Vu0::Q(k)));
    return Vu0::ToFloat(Vu0::Length(Vu0::Q(r)));
}

ASM_FUNC(func_001BF398);

// Where sounds are heard from: the active switched collider's position (+0x140) when it has
// one, otherwise the camera's position.
void* GetSoundListenerPosition(void)
{
    SwitchedCollider* p = (SwitchedCollider*)GetActiveSwitchedCollider();
    u8* r;
    if (p != 0 && p->desc05()->m4A(p) != 0) {
        r = (u8*)&p->v140;
    } else {
        r = (u8*)g_camera->position;
    }
    return r;
}


// Sets the pitch offset of a playing sound for the Doppler shift: from the speed of the source
// relative to the listener (the active switched collider) along the line between them, scaled by
// the sound's Doppler scale; 0 without a source object or listener, or with a scale near 0.
void ComputeSoundRecordDoppler(PlayingSound* self)
{
    PlacedObject* source = (PlacedObject*)self->object;
    if (source == 0 || self->dopplerScale <= 0.0001f) {
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
        f32 scale = self->dopplerScale * 3600.0f;
        Vu0::Q(away) = Vu0::Sub(Vu0::Q(listener->v140), Vu0::Q(source->v140));
        u128 unit = Vu0::DivX(Vu0::Q(away), Vu0::Length(Vu0::Q(away)));
        self->pitchOffset = ConvertSpeedToPitchOffset((s32)(Vu0::ToFloat(Vu0::Dot(unit, Vu0::Q(rel))) * scale * 6.24999984e-06f));
    } else {
        self->pitchOffset = 0;
    }
}

// The distance function used for sounds: the camera-weighted one while the top camera controller
// is one of the first two kinds, otherwise the plain distance.
ListenerDistanceFn ChooseSoundListenerFunction(void)
{
    s32 n;
    if (IsTopCameraController(&g_camera->ctl460) == 0) return MeasureListenerDistance;
    n = PeekStackValue(&g_camera->ctl460);
    if (n >= 3) return MeasureListenerDistance;
    if (n <= 0) return MeasureListenerDistance;
    return MeasureCameraWeightedDistance;
}

// The distance from the listener to position, by the function ChooseSoundListenerFunction picks.
f32 ComputeSoundListenerFactor(void* position)
{
    void* listener = GetSoundListenerPosition();
    return ChooseSoundListenerFunction()(listener, position);
}

// The volume and pan of a sound at a position for the listener of the moment: the base volume
// and no pan when there is no position, otherwise ComputeSoundVolumeAndPan on the distance.
void ComputeSoundAttenuation(void* self, f32* out, s32* flag, f32 a, f32 b, f32 c)
{
    if (self != 0) {
        f32 r = ComputeSoundListenerFactor(self);
        ComputeSoundVolumeAndPan(r, self, out, (f32*)flag, a, b, c);
    } else {
        *out = a;
        *flag = 0;
    }
}

// Takes a sound record (0x90 bytes) from the world's pool, clears it and links it into the
// record list.
void* AllocateSoundRecord(void)
{
    void* s = PopFreeSlot(&g_currentWorld->pool1BA0);
    if (s) {
        FillMemory(s, 0, 0x90);
        AppendToList(&g_currentWorld->list1BAC, s);
    }
    return s;
}

// Detaches a record from the caller's handle slot: the record's owner is cleared and the slot
// set to null (the sound goes on playing).
void ClearSoundRecordHandle(PlayingSound** slot)
{
    PlayingSound* e = *slot;
    e->owner = 0;
    *slot = 0;
}

// Clears the owner's handle, invalidates the record's serial and returns it to the pool.
void FreeSoundRecord(PlayingSound* self)
{
    if (self->owner != 0) {
        *self->owner = 0;
    }
    self->serial = -1;
    RemoveFromList(&g_currentWorld->list1BAC, self);
    PushFreeSlot(&g_currentWorld->pool1BA0, self);
}

// Stops a sound record's voice, at once for n = 0 or with a fade of n * 0.24 units, and frees
// the record.
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

// Sets the pitch of a sound record's voice: the sound's own base pitch plus the pitch (1524 units
// per octave step) and the Doppler offset, clamped to the 16-bit range. It does nothing when the
// pitch is unchanged and no Doppler effect applies.
void SetSoundRecordPitch(PlayingSound* p, f32 a)
{
    if (p == 0) {
        return;
    }
    if (a == p->pitch) {
        if (p->object == 0) {
            return;
        }
        if (!(0.0001f < p->dopplerScale)) {
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

// Changes a sound record's base volume to a, scaling its current volume by the same ratio, and
// sends it.
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

// Fills a playing-sound record (the link kept): its owner slot, the object it follows or position,
// far and near range, base volume, pitch and Doppler scale, a serial number, a random poll tick,
// the optional repeat interval and range (-1 when none), and whether it is positional; then its
// first volume, pan and Doppler offset.
void InitSoundRecord(PlayingSound* self, PlayingSound** owner, s32 keepWhenFar, BaseObject* object, Quad16* position, f32 farRange, f32 nearRange, f32 baseVolume, f32 pitch, f32 f16, U64P* interval, U64P* p80)
{
    U64P keep = self->link;
    FillMemory(self, 0, 0x90);
    self->link = keep;
    if (object) position = (Quad16*)&((PlacedObject*)object)->v140;
    self->owner = owner;
    if (owner) *owner = self;
    self->pitch = pitch;
    self->dopplerScale = f16;
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
    ComputeSoundAttenuation(position, &self->volume, (int*)&self->pan, baseVolume, farRange, nearRange);
    ComputeSoundRecordDoppler(self);
}

// Starts the voice of a playing-sound record for sound entry idx (-2 being the stream voice): loads
// the entry's bank and starts its voice when the record is audible and not a repeating one, with
// its Doppler, pitch and volume set; otherwise the record starts silent.
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

// Sets when a repeating sound plays next (a random time in its interval from now) and, for one
// without an object, picks a random place around the listener at a random distance within its
// range, on the ground plane.
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

// Plays sound entry id (-1 none, -2 the stream voice). With an object, a position or an out slot
// it makes a playing-sound record (far range fa, near range fb, base volume fc, pitch fd, Doppler
// scale fe, a repeat interval p4 and range p5 for an ambient sound), with *out set to it;
// otherwise it is a one-shot voice at volume fc and pitch fd.
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5) {
    PlayingSound* s1;
    s32 s0;
    if (id == -1) return;
    if (id != -2) {
        s32 a1 = g_soundEntries[id].bank;
        if (a1 > 0 && a1 != g_currentWorld->soundBank) return;
        s0 = IsSoundEntryAvailable(id);
    } else {
        s0 = 0;
    }
    s1 = 0;
    if (p3 || p2 || out) {
        if (s0 == 0 && (p4 == 0 || *p4 < 0.0f)) {
            PlayingSound tmp;
            InitSoundRecord(&tmp, out, 0, p2, (Quad16*)p3, fa, fb, fc, fd, fe, 0, 0);
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
            InitSoundRecord(s1, out, s0, p2, (Quad16*)p3, fa, fb, fc, fd, fe, (U64P*)p4, p5);
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

// IOP reply callback: on success (reply 0) marks the record finished if its serial still equals
// the one in the key's high word.
void MarkSoundRecordIfIdMatches(s32 reply, s64 key)
{
    if (reply == 0) {
        s32 tag = (s32)(key >> 32);
        PlayingSound* r = (PlayingSound*)(s32)(key & 0xFFFFFFFFu);
        if (r->serial == tag) {
            r->finished = 1;
        }
    }
}

// Sets row 6 of the volume factors to x for channels 0, 2 and 3, and for channel 1 when flag is
// set.
void SetVolumeChannel6Factors(s32 flag, f32 x)
{
    SetVolumeChannelFactor(6, 0, x);
    SetVolumeChannelFactor(6, 2, x);
    SetVolumeChannelFactor(6, 3, x);
    if (flag) {
        SetVolumeChannelFactor(6, 1, x);
    }
}

// The sound system's per-frame update: lets go of a finished stream voice, steps the IOP sound
// level one notch toward the wanted level, and walks the world's playing sounds: stops those whose
// object is gone, schedules repeating ones, silences or stops those past their far range, and
// updates volume, pan and Doppler pitch for the rest.
void UpdateSoundEmitters(void)
{
    PlayingSoundFrame f;
    if (IsSoundEmitterUpdateDisabled() != 0) return;
    void* v4 = GetSoundListenerPosition();
    ListenerDistanceFn v5 = ChooseSoundListenerFunction();
    u8* P = (u8*)&g_currentWorld->list1BAC;
    ListFrame* saved = g_activeListFrames;
    f.list = P;
    f.link = P;
    f.offset = ((List01*)P)->offset;
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
            g_soundLevelStepCountdown = g_soundLevelStepCountdown - 1;
            if (g_soundLevelStepCountdown < 0) {
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
                g_soundLevelStepCountdown = g_soundLevelStepCountdown + 3;
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
                        if (s1[1] - g_lastSilentSoundTime < 1.0f) goto next;
                        g_lastSilentSoundTime = s1[1];
                    }
                }
            }
            if (e->positional == 0) goto next;
            {
                s1 = (u8*)&e->position;
                if (e->object != 0) s1 = (u8*)&((PlacedObject*)e->object)->v140;
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

// Sets IOP volume channel 8 to x (x 1024).
void SetIopVolumeChannel8(f32 x)
{
    SetIopVolumeChannel(8, (s32)(x * 1024.0f));
}

// Sets the IOP volume of channel column to the product of that column of every row of
// g_volumeChannelFactors, clamped to 0..1 and scaled by 1024.
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

// Sets one factor and re-applies the channel it belongs to.
void SetVolumeChannelFactor(s32 row, s32 column, f32 value)
{
    g_volumeChannelFactors[row][column] = value;
    ApplyVolumeChannelFactors(column);
}

// Restores the default volume channel factors and re-applies the four channels, then applies two
// option flags (0x80 silences channel 3's factor, 0x40 goes to ApplySoundOptionFlag) from the
// save data.
void ResetVolumeChannelFactors(void)
{
    CopyMemory(g_volumeChannelFactors, g_defaultVolumeChannelFactors, 0xB0);
    SetIopVolumeChannel8(1.0f);
    for (s32 i = 0; i < 4; i++) {
        ApplyVolumeChannelFactors(i);
    }
    SilenceVolumeChannel3(g_saveData->optionFlags & 0x80);
    ApplySoundOptionFlag(g_saveData->optionFlags & 0x40);
}

// Channel 3's factor in row 3: 0 when flag is set, else 1.
void SilenceVolumeChannel3(s32 flag)
{
    SetVolumeChannelFactor(3, 1, flag ? 0.0f : 1.0f);
}

// Passes the sound option (a boolean) on to the IOP.
void ApplySoundOptionFlag(s32 value)
{
    SetIopSoundOptionFlag(value != 0);
}

// Stops every sound (IOP and world records), clears levels and cached parameters and waits
// until the IOP has finished.
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

// Stops every sound record of the current world (a fade of item frames when item is not 0) and
// then polls the IOP commands.
void StopWorldSoundRecords(s32 item)
{
    if (g_currentWorld) {
        ListFrame it;
        u8* obj;
        ListWalkSteps::Begin(&it, &g_currentWorld->list1BAC);
        for (obj = ListWalkSteps::Next(&it); obj; obj = ListWalkSteps::Next(&it)) {
            StopSoundRecord((PlayingSound*)obj, item);
        }
        ListWalkSteps::End(&it);
    }
    PollIopCommands();
}

// Pushes a setting (a value index and a pair value) for IOP channel 2 onto the world's stack of
// four and sends it; does nothing when the stack is full.
void PushIopChannel2Setting(World* self, s32 a, s32 b)
{
    if ((u32)self->channel2Count < 4) {
        SetIopChannelValue(2, g_iopChannel2Values[a]);
        SetIopChannelValuePair(2, b, b);
        self->channel2[self->channel2Count].index = a;
        self->channel2[self->channel2Count].value = b;
        self->channel2Count++;
    }
}

// Drops the top setting of the world's IOP channel 2 stack and re-sends the one below it (the
// last one is never dropped).
void PopIopChannel2Setting(World* self)
{
    s32 n = self->channel2Count;
    if (n >= 2) {
        self->channel2Count = n - 1;
        SetIopChannelValue(2, g_iopChannel2Values[self->channel2[n - 2].index]);
        SetIopChannelValuePair(2, self->channel2[self->channel2Count - 1].value, self->channel2[self->channel2Count - 1].value);
    }
}

// Replaces the whole IOP channel 2 stack with a single setting and sends it.
void SetIopChannel2Setting(World* self, s32 index, s32 value)
{
    SetIopChannelValue(2, g_iopChannel2Values[index]);
    SetIopChannelValuePair(2, value, value);
    self->channel2[0].index = index;
    self->channel2[0].value = value;
    self->channel2Count = 1;
}

// Appends a sound entry (up to 16) with the default repeat and range to the world.
void AddWorldSoundEntry(World* self, s32 key)
{
    if (self->soundCount < 16) {
        WorldSoundEntry* e = &self->soundEntries[self->soundCount];
        e->sound = key;
        e->repeat = g_defaultSoundRepeat;
        e->range = g_defaultSoundRange;
        self->soundCount++;
    }
}

// Sets the ranges of the world's last sound entry from a 2D point: 8000 minus 50 times its y
// and x.
void SetLastWorldSoundEntryFromPoint(World* self, Point2* p)
{
    s32 n = self->soundCount;
    if (n != 0) {
        WorldSoundEntry* e = &self->soundEntries[n - 1];
        e->range0 = 8000.0f - p->y * 50.0f;
        e->range1 = 8000.0f - p->x * 50.0f;
    }
}

// Sets the repeat value of the world's last sound entry.
void SetLastWorldSoundEntryValues(World* self, U64P* item)
{
    if (!self->soundCount) return;
    WorldSoundEntry* e = &self->soundEntries[self->soundCount - 1];
    e->repeat = *item;
}

// Starts the sound of each of the world's sound entries (the looping ambience placed in the
// level), with the entry's own repeat and range values and the default 8000/3000 ranges.
void StartWorldSoundEntries(World* self)
{
    for (s32 i = 0; i < self->soundCount; i++) {
        WorldSoundEntry* e = &self->soundEntries[i];
        StartSoundEffect(e->sound, (PlayingSound**)g_worldSoundHandle, 0, 0, 8000.0f, 3000.0f, 1.0f, 0.0f, 0.0f, (f32*)&e->repeat, &e->range);
    }
}

// Sets voice parameter idx of the staged bank's voice, only when it differs from the cached
// value.
void SetCachedVoiceParam(s32 idx, s32 val)
{
    if (val != g_cachedVoiceParams[idx]) {
        g_cachedVoiceParams[idx] = val;
        SetVoiceParam(g_stagedBankVoice, idx, val);
    }
}

s32 GetCachedVoiceParam(s32 index)
{
    return g_cachedVoiceParams[index];
}

// Reads parameter i back from the staged bank's voice into the cache.
void RefreshCachedVoiceParam(s32 i, s32 unused1)
{
    g_cachedVoiceParams[i] = GetVoiceParam(g_stagedBankVoice, i);
}

// Sets the eight cached voice parameters to 0 (sending those that differ).
void ClearCachedVoiceParams(void)
{
    for (s32 i = 0; i < 8; i++) {
        SetCachedVoiceParam(i, 0);
    }
}

extern const RandomWalkSteps g_randomWalkSteps = { { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, 1, -5, -5, -5, -5, 1, 1, -5, -5, -5, 1, 1, 1, -5, -5, 1, 1, 1, 1, -5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
extern const RandomWalkRows g_randomWalkRows = { { 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 } };

// One step of a random walk with a bias: from the current position (-12 to 12) it adds one of six
// steps chosen at random from the row of that position (seven rows of six steps), and gives the new
// position. A sound's wandering pitch follows it.
// One step of a biased random walk: from the current position (-12 to 12) it adds one of six steps
// chosen at random from the row of that position (seven rows of six), and gives the new position.
// PlaySoundWithWanderingPitch uses it as the pitch of a sound.
s32 StepBiasedRandomWalk() {
    RandomWalkSteps a = g_randomWalkSteps;
    RandomWalkRows b = g_randomWalkRows;
    s32 r = RandomIntInRange(0, 5);
    g_randomWalkPosition += *(s32*)((u8*)&a + (b.v[g_randomWalkPosition + 12] * 24 + r * 4));
    return g_randomWalkPosition;
}

// While D_002748EC is set, plays sound 0x77 at half volume with a pitch that wanders by a
// biased random walk step in twelfths.
void PlaySoundWithWanderingPitch(void)
{
    if (D_002748EC != 0) {
        f32 scale = (f32)StepBiasedRandomWalk();
        StartSoundEffect(0x77, 0, 0, 0, 0.0f, 0.0f, 0.5f, scale * 0.083333336f, 0.0f, 0, 0);
    }
}

// Initialiser of class 0x66, an object linked to another by id: sets the placed-object defaults,
// a grey colour (0x80808080), a few tuning floats and two vectors, and no link yet (id -1).
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

// Start of class 0x66: the placed object's start, then the link by id, then the descriptor's
// slot 3 method.
void StartIdLinkedObject(IdLinkedObject* self)
{
    StartPlacedObject(self);
    SetObjectLinkId(self, self->linkId);
    self->desc->m03(self);
}

// Links the object to the object found by id v: drops the old link (a state walker), looks the
// target up in the world and creates a new walker for it.
void SetObjectLinkId(IdLinkedObject* self, s32 v)
{
    if (self->link != 0) {
        DestroyStateWalker(self->link);
        self->link = 0;
    }
    BaseObject* r = FindFirstObjectById(self->world, 0x101, v, self);
    self->linkTarget = r;
    if (r != 0) {
        self->link = CreateStateWalker((StateGraph*)r, self, -1, 1);
    }
    self->linkId = v;
}

// Initialiser of class 0x81: the object's defaults, with a distance field set to the largest
// float.
void InitListedPointObject(ListedPointObject* self)
{
    InitObject(self);
    self->f58 = 3.4028235e38f;
}

// Registers a class 0x81 object and also adds it to the world's list at 0x1C84.
void RegisterListedPointObject(ListedPointObject* self)
{
    RegisterObject(self);
    AppendToList(&self->world->list1C84, self);
}

// Undoes RegisterListedPointObject.
void UnregisterListedPointObject(ListedPointObject* self)
{
    UnregisterObject(self);
    RemoveFromList(&self->world->list1C84, self);
}

// Copy for class 0x81: copies the object's data but keeps the object's own list bits.
void CopyListedPointObject(ListedPointObject* self, ListedPointObject* src)
{
    KeptBits saved;
    saved = self->keep;
    CopyObjectData(self, src);
    self->keep = saved;
}