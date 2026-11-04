// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6C (descriptor D_002214A0, 0x2360 bytes): the world, the object every level object
// has as its level (C01::world). Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// The fields follow the parent's and end at the size the descriptor gives; the pads keep
// every field at its retail offset. Only the fields the matched methods read are named; the
// many sub-records func_001DB4C8 sets up are reached by offset (its SUB macro).
#ifndef C6C_H
#define C6C_H

#include "c01.h"

struct Actor6C;

// The methods slots 0x118 and 0x11C of an object that the world updates every frame.
struct ActorVtbl6C {
    u8 pad0[0x118];
    void (*update)(Actor6C* self, f32 dt);   // 0x118
    void (*post)(Actor6C* self);             // 0x11C
};

// An object in one of the world's lists (func_001EA118).
struct Actor6C {
    ActorVtbl6C* vtable;    // 0x00
    u8 pad4[0x224];
    s32 tries;              // 0x228: how often func_00129D70 failed it
    u8 pad22C[0x30C];
    u64 flags;              // 0x538: bit 63 asks for func_001BB9D0
};

// A list head: the first element, the one after it, and the offset of the link in an element.
struct ActorList6C { Actor6C* head; u8 pad4[4]; s32 offset; };

struct C6C : C01 {
    u8 pad34[0x60 - 0x34];
    ActorList6C list60;     // 0x60: the objects func_00129D70 tries to start
    ActorList6C list6C;     // 0x6C: the objects updated every frame
    u8 pad78[0x1AD8 - 0x78];
    void* buf1AD8;          // 0x1AD8: 0x4800 bytes
    void* buf1ADC;          // 0x1ADC: 0x10000 bytes
    u8 pad1AE0[0x1B7C - 0x1AE0];
    ActorList6C list1B7C;   // 0x1B7C
    u8 pad1B88[0x1D64 - 0x1B88];
    u8 f1D64;               // 0x1D64
    u8 f1D65;
    u8 f1D66;
    u8 pad1D67;
    f32 f1D68;              // 0x1D68
    u8 pad1D6C[4];
    s32 f1D70;              // 0x1D70: -1
    s32 f1D74;              // 0x1D74
    u8 pad1D78[0x1ED4 - 0x1D78];
    void* buf1ED4;          // 0x1ED4: 0x1000 bytes
    u8 pad1ED8[0x2308 - 0x1ED8];
    f32 f2308;              // 0x2308
    f32 f230C;              // 0x230C
    u8 pad2310[0x234C - 0x2310];
    f32 f234C;              // 0x234C
    f32 f2350;              // 0x2350
    s32 f2354;              // 0x2354
    u8 pad2358[4];
    s32 f235C;              // 0x235C
};

typedef char check_C6C[sizeof(C6C) == 0x2360 ? 1 : -1];

void func_001DB4C8(C6C* self);      // 0x6C slot 0
void func_001EA118(C6C* self);      // 0x6C slot 17 (every frame)

#endif
