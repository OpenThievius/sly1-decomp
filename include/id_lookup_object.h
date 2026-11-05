// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x87 (descriptor D_002191E0, 0x68 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Fields follow the parent's
// 0x34 bytes; pads keep each at its retail offset.
#ifndef ID_LOOKUP_OBJECT_H
#define ID_LOOKUP_OBJECT_H

#include "c01.h"

// A growing list of s32 (func_0015FF88 appends to it).
struct FoundList {
    u8 pad0[8];
    s32 count;              // 0x08
    s32* items;             // 0x0C
};

// 0x87: eight item ids (count at 0x34); func_0015FF88 (slot 16) looks each up in the level
// object (+0x14) and keeps the hits in its own list.
struct IdLookupObject : C01 {
    s32 idCount;            // 0x34
    s32 ids[8];             // 0x38
    FoundList found;        // 0x58..0x68
};

typedef char check_IdLookupObject[sizeof(IdLookupObject) == 0x68 ? 1 : -1];

void func_0015FF88(IdLookupObject* self);   // slot 16

#endif
