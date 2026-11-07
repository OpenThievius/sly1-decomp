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

struct AnimRecord;      // cursor_animator.h

// A register write of the object's texture setting (func_0013A008): the value and the GS
// register it goes to (6), as a 16-byte record.
struct __attribute__((aligned(16))) TextureRegWrite {
    u64 value;              // 0x00
    s32 reg;                // 0x08
    s32 pad0C;              // 0x0C
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
    u8 pad2D4[0x320 - 0x2D4];
    s32 mode;               // 0x320: 2 gives each owned record an extra record (func_00139C70)
    u8 pad324[0x380 - 0x324];
    AnimRecord* flagRecord;           // 0x380: its anim record (func_00139F80); func_0013A3A0 and func_0013B430 test its mask
    s32 regCount;           // 0x384: a power of two up to 16 (func_0013A008)
    u8 pad388[0x390 - 0x388];
    TextureRegWrite regs[32]; // 0x390: one for each texture entry, the first ones doubled to fill regCount
    s32 colorTaken;         // 0x590: set once the colour is taken from the record (func_00139F80)
    u8 color[4];            // 0x594: the record's bytes 4..7 halved
    u8 pad598[0x620 - 0x598];
    s32 f620;               // 0x620: cleared by func_00139D68
    OffsetList members;               // 0x624
    WorldListedObject* next;          // 0x630: in World::list1CB4 (func_0013B430)
    u8 pad634[0x640 - 0x634];
};

typedef char check_WorldListedObject[sizeof(WorldListedObject) == 0x640 ? 1 : -1];

void func_00139DE8(WorldListedObject* self);                       // slot 0
void func_00139E80(WorldListedObject* self);                       // slot 6
void func_00139EC8(WorldListedObject* self);                       // slot 7
void func_0013A3A0(WorldListedObject* self);                       // slot 17
void func_0013A418(WorldListedObject* self, BaseObject* src);             // slot 23
void func_0013AD08(WorldListedObject* owner, s32 unused, void* src); // slot 37

#endif
