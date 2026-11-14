// SPDX-License-Identifier: AGPL-3.0-or-later
// A sound playing in the world (PlayingSound), as the sound system, the colliders and the
// surface-contact effects share it.
#ifndef PLAYING_SOUND_H
#define PLAYING_SOUND_H

#include "common.h"
#include "shapes.h"
#include "base_object.h"

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
    f32 dopplerScale;       // 0x5C: how strongly the object's motion shifts the sound's pitch
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

#endif
