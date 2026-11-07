// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8D (descriptor D_0021F438, 0x8F0 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Fields follow the parent's
// 0x34 bytes; pads keep each at its retail offset.
#ifndef C8D_H
#define C8D_H

#include "base_object.h"

// 0x8D, an oscillator: a set of 0xD0-byte entries (at +0x50) that EvaluateOscillator turns by a
// sine (kind 0) or a noise blend (kind 1) of the clock. func_001F2758 (slot 0) resets three
// indices and a scale to -1.
struct C8D : BaseObject {
    f32 scale34;            // 0x34: the clock time EvaluateOscillator last ran at (-1.0 at set-up)
    s32 f38;                // 0x38: the entries
    s32 f3C;                // 0x3C
    s32 index40;            // 0x40
    u8 pad44[0x6D0 - 0x44];
    s32 index6D0;           // 0x6D0
    u8 pad6D4[0x8E4 - 0x6D4];
    s32 f8E4;               // 0x8E4: set when an entry changed (RefreshOscillatorFrames)
    u8 pad8E8[0x8F0 - 0x8E8];
};

typedef char check_C8D[sizeof(C8D) == 0x8F0 ? 1 : -1];

void func_001F2758(C8D* self);   // slot 0

#endif
