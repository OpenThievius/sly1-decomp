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
#include "shapes.h"

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
    sptr head;              // 0x00
    u8 pad04[4];
    s32 link;               // 0x08
};

struct WorldListedObject : PlacedObject {
    void* source;                // 0x2D0: the object a copy was taken from (func_0013A418)
    u8 pad2D4[0x2E0 - 0x2D4];
    u8 curve2E0[0x10];      // 0x2E0: remapped from the source's +0x140 (func_0013A128)
    u8 curve2F0[0x10];      // 0x2F0: remapped from the source's +0x110
    union {
        Quad16 q300;        // 0x300: zeroed, then the source's +0x150 or a rate in f304 (func_0013A128)
        struct {
            f32 f300;
            f32 f304;
        };
    };
    u8 curve310[0x10];      // 0x310: remapped from the source's +0x160
    s32 mode;               // 0x320: 2 gives each owned record an extra record (func_00139C70); 1 when the source is still
    u8 pad324[0x330 - 0x324];
    u8 block330[0x50];      // 0x330: zeroed, then filled from the source by func_001583E8 unless mode is set
    AnimRecord* flagRecord;           // 0x380: its anim record (func_00139F80); func_0013A3A0 and func_0013B430 test its mask
    s32 regCount;           // 0x384: a power of two up to 16 (func_0013A008)
    u8 pad388[0x390 - 0x388];
    TextureRegWrite regs[32]; // 0x390: one for each texture entry, the first ones doubled to fill regCount
    s32 colorCount;         // 0x590: the colours in color: the source's (func_0013A128), or 1 taken from the record (func_00139F80)
    u8 color[32][4];        // 0x594: halved bytes: the source's colours last first, or the record's bytes 4..7
    s32 f614;               // 0x614: copied from the source's +0x184 (func_0013A128)
    s32 particleMode;       // 0x618: from the source's +0x190
    f32 f61C;               // 0x61C: from the source's +0x194
    s32 particleCount;      // 0x620: cleared by func_00139D68
    OffsetList members;               // 0x624
    WorldListedObject* next;          // 0x630: in World::list1CB4 (func_0013B430)
    u8 pad634[0x640 - 0x634];
};

typedef char check_WorldListedObject[sizeof(WorldListedObject) == 0x640 ? 1 : -1];

void InitWorldListedObject(WorldListedObject* self);                       // slot 0
void LeaveWorldLists(WorldListedObject* self);                       // slot 6
void ReleaseWorldListedObject(WorldListedObject* self);                       // slot 7
void UpdateWorldListedObject(WorldListedObject* self, f32 dt);                       // slot 17
void CopyWorldListedObject(WorldListedObject* self, BaseObject* src);             // slot 23
struct Src_13AD08;
void SubmitWorldListedObjectBlock(WorldListedObject* owner, s32 unused, Src_13AD08* src); // slot 37

#endif
