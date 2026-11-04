// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x54 (descriptor D_0021C4C8, 0x2E0 bytes), a placed object with one field of its own at
// 0x2D0 (func_001B5D28 reads it to decide whether to override a value of the camera block).
// Written for this project from what retail's code does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C54_H
#define C54_H

#include "c02.h"

struct C54 : C02 {
    s32 f2D0;               // 0x2D0
    u8 pad2D4[0x2E0 - 0x2D4];
};

typedef char check_C54[sizeof(C54) == 0x2E0 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001B5CD8(C54* self);                       // 0x54 slot 16
void func_001B5D28(C54* self);                       // 0x54 slot 17

#endif
