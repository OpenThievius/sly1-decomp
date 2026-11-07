// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x89 (descriptor D_0021BAD8, 0x190 bytes). Written for this project from what retail's
// code does (config/us/classes.tsv).
//
// The fields follow the parent's and end at the size the descriptor gives; the pads keep
// every field at its retail offset. Fields are named for what the code does with them.
#ifndef ITEM_KEEPER_H
#define ITEM_KEEPER_H

#include "base_object.h"

// An object a 0x89 finds and owns: it keeps the owner at 0x720 (func_001CB7A0).
struct FoundItem {
    u8 pad0[0x720];
    void* owner;            // 0x720
};

// A group of up to sixteen found objects: the ones found so far, then the ids still to find
// (func_001CB7A0 looks each one up with func_0015A448 and adds what it finds).
struct ItemGroup {
    s32 count;              // 0x00
    FoundItem* found[16];      // 0x04
    s32 wantedCount;        // 0x44
    FoundItem* wanted[16];     // 0x48
};

struct ItemKeeper : BaseObject {
    u8 pad34[0x50 - 0x34];
    s32 state;              // 0x50: func_001CBB88 picks the next, 3 stops the updates
    u8 pad54[0x58 - 0x54];
    ItemGroup owned;          // 0x58: the ones that become its own (their owner is set to it)
    ItemGroup listed;         // 0xE0: the ones it only keeps
    s32 triggerCount;       // 0x168: the state triggers at 0x16C (func_001CBE20 adds one once)
    s32 triggers[4];        // 0x16C
    s32 queued;             // 0x17C: an update is queued (func_001CBAA0; func_001CBB20 clears it)
    s32 f180;               // 0x180: -1 from the start
    u8 pad184[0x188 - 0x184];
    s32 anyFree;            // 0x188: func_001CBB20 sets it, func_001CBB88 reads it
    u8 pad18C[0x190 - 0x18C];
};

typedef char check_ItemGroup[sizeof(ItemGroup) == 0x88 ? 1 : -1];
typedef char check_ItemKeeper[sizeof(ItemKeeper) == 0x190 ? 1 : -1];

void func_001CB618(ItemKeeper* self);      // 0x89 slot 0
void func_001CB7A0(ItemKeeper* self);      // 0x89 slot 15

#endif
