// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x67 (descriptor D_00221020, 0x570 bytes), a placed object with a mode and eleven
// animated elements. Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C67_H
#define C67_H

#include "c02.h"

// One of the eleven elements func_001F0758 sets up: two values cleared, two drawn at random
// from a range (a phase and a speed).
struct Elem67 {
    u8 pad0[0x24];
    f32 f24;                // 0x24
    f32 f28;                // 0x28
    f32 f2C;                // 0x2C
    f32 f30;                // 0x30
};

// 0x67: func_001F0F70 reacts to a message by mode (1, 3 or 4), func_001F0660 enters the object
// in the table of the objects of its kind (slot by id), func_001F0758 sets up the elements.
struct C67 : C02 {
    s32 mode;               // 0x2D0
    u8 pad2D4[0x2DC - 0x2D4];
    s32 f2DC;               // 0x2DC
    s32 f2E0;               // 0x2E0
    void* f2E4;             // 0x2E4
    void* f2E8;             // 0x2E8
    s32 f2EC;               // 0x2EC
    u8 pad2F0[0x2F4 - 0x2F0];
    s32 slot;               // 0x2F4: 1..5 by id, else the value in the global block at +0x19D8
    Elem67 elems[11];       // 0x2F8
    s32 f534;               // 0x534
    u8 pad538[0x560 - 0x538];
    s32 f560;               // 0x560
    u8 pad564[0x570 - 0x564];
};

typedef char check_C67[sizeof(C67) == 0x570 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001F0F70(C67* self, s32 kind, void* msg);  // 0x67 slot 13
void func_001F0758(C67* self);                       // 0x67 slot 15
void func_001F0660(C67* self);                       // 0x67 slot 16
void func_001F0EB8(C67* self, u8* s, void* c);       // 0x67 slot 36

#endif
