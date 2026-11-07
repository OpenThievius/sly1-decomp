// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8D (descriptor D_0021F438, 0x8F0 bytes), a direct child of 0x01: an oscillator.
// Written for this project from what retail's code does (config/us/classes.tsv). Fields follow
// the parent's 0x34 bytes; pads keep each at its retail offset.
#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "base_object.h"

// 0x8D: a set of 0xD0-byte entries (at +0x50) that EvaluateOscillator turns by a sine (kind 0)
// or a noise blend (kind 1) of the clock, once per clock time. Scripts add entries
// (AddOscillatorXEntry, AddOscillatorYZEntry) and set the current one's period;
// InitOscillator (slot 0) sets the pending id, the current entry and the last time to -1.
struct Oscillator : BaseObject {
    f32 lastTime;           // 0x34: the clock time EvaluateOscillator last ran at (-1.0 at set-up)
    s32 entryCount;         // 0x38: the entries
    s32 nextId;             // 0x3C: the next entry id (an X entry takes it, a YZ entry uses one up)
    s32 pendingId;          // 0x40: the id the next X entry takes as its pair (-1 for none)
    u8 pad44[0x6D0 - 0x44];
    s32 currentEntry;       // 0x6D0: the index of the current entry (-1 for none)
    u8 pad6D4[0x8E4 - 0x6D4];
    s32 framesDirty;        // 0x8E4: set when an entry changed (RefreshOscillatorFrames)
    u8 pad8E8[0x8F0 - 0x8E8];
};

typedef char check_Oscillator[sizeof(Oscillator) == 0x8F0 ? 1 : -1];

void func_001F2758(Oscillator* self);   // slot 0

#endif
