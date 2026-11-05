// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4C (descriptor D_0021B9A8, 0x560 bytes), a part with collision that counts down and
// then goes away (func_001D32D8 sends its message, lets go of its handle and removes it).
// Written for this project from what retail's code does (config/us/classes.tsv;
// src/main/file_1D29C8.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C4C_H
#define C4C_H

#include "collider.h"

struct C4C : Collider {
    s32 count;              // 0x550: the touches left (func_001D32D8 counts it down)
    s32 f554;               // 0x554: a chain of the world's records, given back with func_001861E8
    void* f558;             // 0x558: the object func_001D32D8 hands to func_00158730
    u8 pad55C[0x560 - 0x55C];
};

typedef char check_C4C[sizeof(C4C) == 0x560 ? 1 : -1];

// The methods that take only types known here (config/us/classes.tsv); a slot's function takes
// its class's object. Slots 13 (func_001D3678) and 45 (func_001D3500) take records that
// file_1D29C8.cpp declares; slots 17 and 19 (func_001D3398, func_001D35A8) are assembly.
void func_001D3290(C4C* self);                       // 0x4C slot 16
void func_001D3470(C4C* self, f32 t);                // 0x4C slot 28
void func_001D34E0(C4C* self);                       // 0x4C slot 63

#endif
