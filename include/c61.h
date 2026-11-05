// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x61 (descriptor D_0021E588, 0x2F0 bytes), a placed object (under 0x02) that keeps one
// pointer after the common block; its slot 0 (func_00152E28) only runs the common
// constructor, slot 37 (func_00153328) draws it when the pointer is set. Written for this
// project from what retail's code does (config/us/classes.tsv).
#ifndef C61_H
#define C61_H

#include "placed_object.h"

struct C61 : PlacedObject {
    void* f2D0;             // 0x2D0: what func_00153328 tests before drawing
    u8 pad2D4[0x2F0 - 0x2D4];
};

typedef char check_C61[sizeof(C61) == 0x2F0 ? 1 : -1];

void func_00152E28(C61* self);                          // 0x61 slot 0
void func_00153328(C61* self, s32 unused, void* a2);    // 0x61 slot 37

#endif
