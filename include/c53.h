// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x53 (descriptor D_0021A320, 0x2F0 bytes, flags 0x101), a group of placed objects: it
// holds the cells of the objects it loaded (their class ids and their own data come from the
// level stream, func_00196410). Written for this project from what retail's code does
// (config/us/classes.tsv, docs/DISC.md "Objects").
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset. The group creates class 0x65 objects (func_0011E580 with their id);
// those are another family's and stay untyped here.
#ifndef C53_H
#define C53_H

#include "c02.h"

struct Stream53;  // the level stream an object is loaded from

// An intrusive list head (func_00152438 sets its element size, func_00152440 empties it):
// the first cell, the last, the offset of the link inside a cell.
struct List53 {
    u32 first;              // 0x00
    u32 second;             // 0x04
    u32 third;              // 0x08
};

// Two words func_00196810 keeps across the copy of the common fields.
struct Pair53 {
    u32 first;
    u32 second;
};

// 0x53: a list of cells that point at the loaded objects (func_00196410 fills it; copying
// (func_00196810) makes new cells that point at the copy's objects).
struct C53 : C02 {
    List53 cells;           // 0x2D0
    Pair53 kept;            // 0x2DC: restored after the common copy
    u8 pad2E4[0x2F0 - 0x2E4];
};

typedef char check_C53[sizeof(C53) == 0x2F0 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001963D8(C53* self);                       // 0x53 slot 0
void func_00196410(C53* self, Stream53* stream);       // 0x53 slot 10
void func_00196810(C53* self, C53* src);             // 0x53 slot 9
void func_00196900(C53* self);                       // 0x53 slot 16

#endif
