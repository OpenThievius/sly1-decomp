// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4D (descriptor 0x640 bytes, parent 0x02), an object that registers itself in its
// level's list at +0x1CC0 and keeps a list of its own at +0x624. Written for this project from
// what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. Its methods also use two of class 0x02's fields (include/c02.h):
// the float at 0x80 and the flags word at 0x2C8.
#ifndef WORLD_LISTED_OBJECT_H
#define WORLD_LISTED_OBJECT_H

#include "placed_object.h"

struct FlagRecord {
    u8 pad00[0xC];
    u32 flags;              // 0x0C
};

// The list at +0x624: first element, a pad, and the offset of the link inside an element
// (func_00139EC8 walks it).
struct OffsetList {
    s32 head;               // 0x00
    u8 pad04[4];
    s32 link;               // 0x08
};

struct WorldListedObject : PlacedObject {
    void* source;                // 0x2D0: the object a copy was taken from (func_0013A418)
    u8 pad2D4[0x380 - 0x2D4];
    FlagRecord* flagRecord;           // 0x380
    u8 pad384[0x624 - 0x384];
    OffsetList members;               // 0x624
    u8 pad630[0x640 - 0x630];
};

typedef char check_WorldListedObject[sizeof(WorldListedObject) == 0x640 ? 1 : -1];

void func_00139DE8(WorldListedObject* self);                       // slot 0
void func_00139E80(WorldListedObject* self);                       // slot 6
void func_00139EC8(WorldListedObject* self);                       // slot 7
void func_0013A3A0(WorldListedObject* self);                       // slot 17
void func_0013A418(WorldListedObject* self, BaseObject* src);             // slot 23
void func_0013AD08(WorldListedObject* owner, s32 unused, void* src); // slot 37

#endif
