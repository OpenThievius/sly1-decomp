// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x51 (descriptor 0x620 bytes, parent 0x02), an object with two camera-style tuning
// vectors (+0x320, +0x340) and a state value at +0x304 that slot 9 compares and keeps through
// a copy. Written for this project from what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. A 64-bit flag word at 0x2C8 (class 0x02's range) is still read
// by offset (see build/swarm/ty8/NOTES.md).
#ifndef C51_H
#define C51_H

#include "c02.h"

struct __attribute__((aligned(16))) Quad51 { s32 a, b, c, d; };

// Eight bytes that slot 9 keeps through the parent's copy; retail moves them unaligned.
struct __attribute__((packed)) Pair51 { s32 a; s32 b; };

struct C51 : C02 {
    s32 w2d0;               // 0x2D0: 0 at setup
    u8 pad2D4[0x2F8 - 0x2D4];
    f32 f2f8;               // 0x2F8: 180.0 at setup
    f32 f2fc;               // 0x2FC: 240.0 at setup
    f32 f300;               // 0x300: 180.0 at setup
    s32 value;              // 0x304: compared by slot 9
    u8 pad308[0x320 - 0x308];
    Quad51 q320;            // 0x320: D_00248D20 at setup
    f32 f330;               // 0x330: 200.0 at setup
    f32 f334;               // 0x334: 2000.0 at setup
    f32 f338;               // 0x338: 60.0 at setup
    u8 pad33C[0x340 - 0x33C];
    Quad51 q340;            // 0x340: D_00248D10 at setup
    u8 pad350[0x410 - 0x350];
    Pair51 saved;           // 0x410: kept through a copy
    u8 pad418[0x620 - 0x418];
};

typedef char check_C51[sizeof(C51) == 0x620 ? 1 : -1];

void func_00183CC8(C51* self);                       // slot 0
void func_00183E40(C51* self);                       // slot 6
void func_00183E70(C51* self);                       // slot 7
void func_00183EA0(C51* self, C51* other);           // slot 9
void func_00183D88(C51* self);                       // slot 19

#endif
