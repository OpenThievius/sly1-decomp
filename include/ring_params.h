// SPDX-License-Identifier: AGPL-3.0-or-later
// The parameter block of a ring drawn around a set of anchors by DrawAngleSortedRing
// (func_001D5678, player_request.cpp), and the anchors it is given. Written for this project
// from what retail's code does: the reader's offsets give the layout, and the functions that
// build a block (func_001D5FA8, func_001D60B0, func_001D61C8, func_0018A510) give the form of
// its members, since each builds it once as a function-local static with a brace initialiser
// (docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER"):
//  - the compiler clears the block with its own memset call and stores the non-zero members in
//    declaration order, which is the order retail's stores have before the scheduler;
//  - a colour is stored as one word even when it is zero, so it is a member with a constructor
//    (a constructor call is never skipped as a zero, and it makes the initialiser run at run
//    time behind a guard); the reader copies it as four unaligned bytes;
//  - the first float of a row is a union's member: its non-zero initialiser (row 2 only) puts a
//    CLOBBER of the member before its store, which every earlier store must precede and every
//    later one follow. That is retail's order: the stores up to row 1's colour, then row 2's.
#ifndef RING_PARAMS_H
#define RING_PARAMS_H

#include "common.h"

struct AnimRecord;
struct PlacedObject;

// A point the ring goes around: an object's position (+0x140) and how far its offsets reach.
struct RingAnchor {
    s32 f0;                 // 0x00
    f32 scale;              // 0x04
    PlacedObject* obj;      // 0x08
};

// A row's radius terms, read as one 16-byte vector: x over the depth, plus y and z times the
// length.
struct __attribute__((aligned(16))) RingShape {
    union {
        f32 x;              // 0x00
        u32 xBits;
    };
    f32 y;                  // 0x04
    f32 z;                  // 0x08
    f32 w;                  // 0x0C
};

// A row's colour: four bytes, set as one word.
struct RingColor {
    u8 r, g, b, a;
    RingColor(u32 rgba) { *(u32*)this = rgba; }
};

// A row of the ring's strip.
struct RingRow {
    RingShape shape;        // 0x00
    f32 v;                  // 0x10: the texture's v
    f32 lift;               // 0x14: along +z
    RingColor color;        // 0x18
};

struct RingParams {
    s32 mode;               // 0x00: 1, u from the angle's distance to pi/2; otherwise from the angle
    f32 uScale;             // 0x04
    f32 rate;               // 0x08: u's scroll per second
    RingRow rows[3];        // 0x10
    AnimRecord* textures[2]; // 0x70: one strip drawn for each that is set
};

typedef char check_RingRow[sizeof(RingRow) == 0x20 ? 1 : -1];
typedef char check_RingParams[sizeof(RingParams) == 0x80 ? 1 : -1];

#endif
