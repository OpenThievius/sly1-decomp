// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6A (descriptor D_00221140, 0x300 bytes), a placed object (class 0x02) with nine
// objects of its own, found through the table D_00262718 after loading. Written for this
// project from what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's 0x2D0 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef PART_HOLDER_OBJECT_H
#define PART_HOLDER_OBJECT_H

#include "placed_object.h"

typedef void (*PartFn)(void* self);

// One of its objects; only slot 6 of its table is called (func_0016AA18).
struct PartObject { PartFn* vtbl; };

// 0x6A: after loading (slot 16), for the kinds 0x515..0x519, it calls slot 6 of each of its
// objects whose flag (func_001601D8, func_00160810, or D_002623C0's for the ninth) is set.
struct PartHolderObject : PlacedObject {
    PartObject* parts[9];       // 0x2D0
    u8 pad2F4[0x300 - 0x2F4];
};

typedef char check_PartHolderObject[sizeof(PartHolderObject) == 0x300 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void CallFlaggedParts(PartHolderObject* self);                       // 0x6A slot 16

#endif
