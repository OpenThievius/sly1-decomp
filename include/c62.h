// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x62 (descriptor D_0021E658, 0x330 bytes), a placed object that watches for one object
// id. Written for this project from what retail's code does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C62_H
#define C62_H

#include "c02.h"

// What func_001EF9C8 reads of the message it is told about (kind 5): the id at 0x08.
struct Msg62 {
    s32 f0;
    s32 f4;
    s32 id;                 // 0x08
};

// 0x62: func_001EF838 sets both ids to -1 (none); func_001EF9C8 resets the object when the
// message names the id at 0x2DC.
struct C62 : C02 {
    s32 id2D0;              // 0x2D0: -1 for none
    f32 f2D4;               // 0x2D4
    u8 pad2D8[0x2DC - 0x2D8];
    s32 id2DC;              // 0x2DC
    s32 id2E0;              // 0x2E0: -1 for none
    s32 f2E4;               // 0x2E4
    u8 f2E8[1];             // 0x2E8
    u8 pad2E9[0x330 - 0x2E9];
};

typedef char check_C62[sizeof(C62) == 0x330 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001EF838(C62* self);                       // 0x62 slot 0
void func_001EF9C8(C62* self, s32 kind, Msg62* msg); // 0x62 slot 13
void func_001EF868(C62* self);                       // 0x62 slot 16
void func_001EF8F8(void);                            // 0x62 slot 17 (empty)

#endif
