// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8E (descriptor D_00218650, 0xA0 bytes), a direct child of 0x01: a single object
// (setup stores it in D_002640A4) that loads a list of points, two ranges and five lists of
// index triples with a colour each (func_0017FEC0). Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's 0x34 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef COLORED_TRIANGLE_SET_H
#define COLORED_TRIANGLE_SET_H

#include "base_object.h"

struct Stream8E;  // the level stream (func_00137BE0, func_00137DF8)

// A point: x and the negated y from the stream, w 1.
struct TrianglePoint { f32 x; f32 y; f32 z; f32 w; };

// Three indices.
struct TriangleIndices { s32 a; s32 b; s32 c; };

struct TriangleColor { u8 c[4]; };

// One list: its colour (from func_001B4688, halved, or grey), the count and the triples.
struct TriangleList {
    TriangleColor col;      // 0x00
    s32 count;              // 0x04
    TriangleIndices* triangles;     // 0x08
};

struct ColoredTriangleSet : BaseObject {
    s32 pointCount;         // 0x34: the number of points
    TrianglePoint* points;  // 0x38: the points
    u8 pad3C[0x40 - 0x3C];
    f32 minX;               // 0x40
    f32 minY;               // 0x44
    u8 pad48[0x4C - 0x48];
    f32 f4C;                // 0x4C: 1.0
    f32 maxX;               // 0x50
    f32 maxY;               // 0x54
    u8 pad58[0x5C - 0x58];
    f32 f5C;                // 0x5C: 1.0
    f32 width;              // 0x60: maxX - minX
    TriangleList lists[5];  // 0x64
};

typedef char check_ColoredTriangleSet[sizeof(ColoredTriangleSet) == 0xA0 ? 1 : -1];
typedef char check_TriangleList[sizeof(TriangleList) == 0x0C ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitColoredTriangles(ColoredTriangleSet* self);                       // 0x8E slot 0
void LoadColoredTriangles(ColoredTriangleSet* self, Stream8E* stream);     // 0x8E slot 10

#endif
