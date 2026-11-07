// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x61 (descriptor D_0021E588, 0x2F0 bytes), a placed object (under 0x02) that keeps one
// pointer after the common block; its slot 0 (func_00152E28) only runs the common
// constructor, slot 37 (func_00153328) draws it when the pointer is set. Written for this
// project from what retail's code does (config/us/classes.tsv).
#ifndef C61_H
#define C61_H

#include "placed_object.h"

struct C61 : PlacedObject {
    void* f2D0;             // 0x2D0: the range record func_00152E48 builds for; func_00153328 tests it before drawing
    s32 f2D4;               // 0x2D4: the first DMA packet func_00152E48 builds (func_001533A8 sends it)
    s32 f2D8;               // 0x2D8: its size
    s32 f2DC;               // 0x2DC: the second packet
    s32 f2E0;               // 0x2E0: its size
    u8 pad2E4[0x2F0 - 0x2E4];
};

typedef char check_C61[sizeof(C61) == 0x2F0 ? 1 : -1];

void InitC61Object(C61* self);                          // 0x61 slot 0
void QueuePlacedObjectDraw(C61* self, s32 unused, void* a2);    // 0x61 slot 37

#endif
