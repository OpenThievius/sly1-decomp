// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8E (descriptor D_00218650, 0xA0 bytes), a direct child of 0x01: a single object
// (setup stores it in D_002640A4) that loads a list of points, two ranges and five lists of
// index triples with a colour each (func_0017FEC0). Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's 0x34 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef C8E_H
#define C8E_H

#include "c01.h"

struct Stream8E;  // the level stream (func_00137BE0, func_00137DF8)

// A point: x and the negated y from the stream, w 1.
struct Pt8E { f32 x; f32 y; f32 z; f32 w; };

// Three indices.
struct Ent8E { s32 a; s32 b; s32 c; };

struct Col8E { u8 c[4]; };

// One list: its colour (from func_001B4688, halved, or grey), the count and the triples.
struct Rec8E {
    Col8E col;              // 0x00
    s32 n;                  // 0x04
    Ent8E* ents;            // 0x08
};

struct C8E : C01 {
    s32 f34;                // 0x34: the number of points
    Pt8E* f38;              // 0x38: the points
    u8 pad3C[0x40 - 0x3C];
    f32 f40;                // 0x40
    f32 f44;                // 0x44
    u8 pad48[0x4C - 0x48];
    f32 f4C;                // 0x4C: 1.0
    f32 f50;                // 0x50
    f32 f54;                // 0x54
    u8 pad58[0x5C - 0x58];
    f32 f5C;                // 0x5C: 1.0
    f32 f60;                // 0x60: f50 - f40
    Rec8E recs[5];          // 0x64
};

typedef char check_C8E[sizeof(C8E) == 0xA0 ? 1 : -1];
typedef char check_Rec8E[sizeof(Rec8E) == 0x0C ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_0017FE90(C8E* self);                       // 0x8E slot 0
void func_0017FEC0(C8E* self, Stream8E* stream);     // 0x8E slot 10

#endif
