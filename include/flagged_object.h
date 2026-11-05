// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x38 (descriptor D_0021C318, 0x5C0 bytes): a collision object that keeps two small lists
// of the objects it works on, the children of kind 0x83 (A) and 0x7B (B), found by id from its
// level data or from its children (slot 10, func_00141210), and one more object (kind 0x74).
// Written for this project from what retail's code does (config/us/classes.tsv).
#ifndef FLAGGED_OBJECT_H
#define FLAGGED_OBJECT_H

#include "collider.h"

struct StateWalker;     // a handle func_001B6290 makes (s1b6290.h)

struct FlaggedObject : Collider {
    s32 nIdsA;              // 0x550: the ids at idsA (func_00141338 looks each up)
    s32 idsA[4];            // 0x554
    s32 countA;             // 0x564: the objects found (kind 0x83)
    void* objsA[4];         // 0x568
    s32 nIdsB;              // 0x578
    s32 idsB[4];            // 0x57C
    s32 countB;             // 0x58C: the objects found (kind 0x7B)
    void* objsB[4];         // 0x590
    s32 childId;            // 0x5A0: the id of the first child of kind 0x74 (-1 until found)
    void* child;            // 0x5A4: that object
    void* f5A8;             // 0x5A8: the object of id 0x545 (the loader's table D_00261410)
    StateWalker* handle;        // 0x5AC: a handle func_001B6290 makes for f5A8
    s32 flagIndex;          // 0x5B0: an index of the table at D_00261420 (func_00140FF8)
    s32 ordinal;            // 0x5B4: the world's count at +0x2304 when it was made
    u8 pad5B8[0x5C0 - 0x5B8];
};

typedef char check_FlaggedObject[sizeof(FlaggedObject) == 0x5C0 ? 1 : -1];

void func_001411A8(FlaggedObject* self);                  // slot 0
void func_001415D0(FlaggedObject* self);                  // slot 9
void func_00141210(FlaggedObject* self);                  // slot 10
void func_00141338(FlaggedObject* self);                  // slot 15
void func_00141438(FlaggedObject* self);                  // slot 16

#endif
