// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x64 (descriptor D_0021EF88, 0x340 bytes), a placed object with a table of up to
// sixteen entries and seven tuning values. Written for this project from what retail's code
// does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef ENTRY_TABLE_OBJECT_H
#define ENTRY_TABLE_OBJECT_H

#include "placed_object.h"

// 0x64: func_0016DD10 sets the tuning values; func_0016DD90 loads the table (the entries
// func_0015A4F0 finds for the object, at most 0x10 of them) after the common load.
struct EntryTableObject : PlacedObject {
    u8 entries[0x310 - 0x2D0];  // 0x2D0: sixteen 32-bit entries
    s32 entryCount;         // 0x310: how many were found (at most 0x10)
    s32 mode314;            // 0x314: 0 picks the entry nearest to the active collider, 1 a random one (func_0016DE20)
    s32 mode318;            // 0x318: 0, 1 or other: which state the follower goes to (func_0016DAC0)
    f32 tune31C;            // 0x31C
    f32 tune320;            // 0x320
    f32 tune324;            // 0x324
    f32 tune328;            // 0x328
    f32 tune32C;            // 0x32C
    f32 tune330;            // 0x330
    f32 tune334;            // 0x334
    u8 pad338[0x340 - 0x338];
};

typedef char check_EntryTableObject[sizeof(EntryTableObject) == 0x340 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitEntryTableObject(EntryTableObject* self);                       // 0x64 slot 0
void LoadEntryTable(EntryTableObject* self);                       // 0x64 slot 10
void StartEntryTableObject(EntryTableObject* self);                       // 0x64 slot 16

#endif
