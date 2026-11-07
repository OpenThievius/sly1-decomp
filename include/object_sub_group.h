// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x7D (descriptor D_002179C0, 0x330 bytes), a placed object that holds the objects it
// creates from the level stream (func_001F4500 loads them; func_001F4660 starts each one).
// Written for this project from what retail's code does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef OBJECT_SUB_GROUP_H
#define OBJECT_SUB_GROUP_H

#include "placed_object.h"

// 0x7D: its own fields are read in two places only, the child table and what func_001F4500
// reads from the stream.
struct ObjectSubGroup : PlacedObject {
    s32 f2D0;               // 0x2D0: FindActiveObjectSubGroup returns the first group with it set
    void* f2D4;             // 0x2D4: set means the object has something to do after its children
    s32 f2D8;               // 0x2D8
    u8 pad2DC[0x2E0 - 0x2DC];
    s32 f2E0;               // 0x2E0
    s32 f2E4;               // 0x2E4: cleared by the load
    f32 f2E8;               // 0x2E8
    s32 f2EC;               // 0x2EC: four values func_001E4C48 reads from the stream
    s32 f2F0;               // 0x2F0
    s32 f2F4;               // 0x2F4
    s32 f2F8;               // 0x2F8
    s32 f2FC;               // 0x2FC
    s32 f300;               // 0x300
    s32 f304;               // 0x304
    s32 f308;               // 0x308
    s32 f30C;               // 0x30C
    s32 count;              // 0x310: how many children
    BaseObject** items;            // 0x314: the children, each created by func_0011E580
    s32 f318;               // 0x318
    f32 f31C;               // 0x31C
    u8 pad320[0x324 - 0x320];
    f32 f324;               // 0x324
    u8 pad328[0x330 - 0x328];
};

typedef char check_ObjectSubGroup[sizeof(ObjectSubGroup) == 0x330 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001F4500(ObjectSubGroup* self, void* stream);         // 0x7D slot 10
void func_001F4660(ObjectSubGroup* self);                       // 0x7D slot 16

#endif
