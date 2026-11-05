// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x1F (descriptor D_00218770, 0x6B0 bytes): a collision object that keeps a list of the
// objects it is attached to (+0x550; each link is also in the target's list at Collider::attached)
// and a record of its own at +0x590 (func_001F5590 sets it up, func_001F55A8 and func_001F57E0
// work on it). Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef C1F_H
#define C1F_H

#include "collider.h"

// The set of objects func_001EF520 hands to the world (func_0015F9A0, func_0015F8B0): the
// object itself, then the targets of its links.
struct Set1F {
    u8 pad0[8];
    s32 count;              // 0x08
    void** items;           // 0x0C: a block of 0x80 bytes (slot 16)
};

// The record at +0x590, read by function in another file; only its second word is read here.
struct Rec1F {
    u8 pad0[4];
    s32 f4;                 // 0x04: 3 at set-up
    u8 pad8[0x120 - 8];
};

struct C1F : Collider {
    Attach03* links;        // 0x550: the objects it is attached to (linked at Attach03::nextOwn)
    Set1F set554;           // 0x554
    u8 pad564[0x584 - 0x564];
    s32 f584;               // 0x584: 1 at set-up
    s32 f588;               // 0x588: 1 at set-up
    u8 pad58C[0x590 - 0x58C];
    Rec1F rec590;           // 0x590
};

typedef char check_C1F[sizeof(C1F) == 0x6B0 ? 1 : -1];

#endif
