// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x7D (descriptor D_002179C0, 0x330 bytes), a placed object that holds the objects it
// creates from the level stream (func_001F4500 loads them; func_001F4660 starts each one).
// Written for this project from what retail's code does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C7D_H
#define C7D_H

#include "c02.h"

// 0x7D: its own fields are read in two places only, the child table and what func_001F4500
// reads from the stream.
struct C7D : C02 {
    u8 pad2D0[0x2D4 - 0x2D0];
    void* f2D4;             // 0x2D4: set means the object has something to do after its children
    u8 pad2D8[0x2E4 - 0x2D8];
    s32 f2E4;               // 0x2E4: cleared by the load
    u8 pad2E8[0x2EC - 0x2E8];
    s32 f2EC;               // 0x2EC: four values func_001E4C48 reads from the stream
    s32 f2F0;               // 0x2F0
    s32 f2F4;               // 0x2F4
    s32 f2F8;               // 0x2F8
    u8 pad2FC[0x310 - 0x2FC];
    s32 count;              // 0x310: how many children
    C01** items;            // 0x314: the children, each created by func_0011E580
    u8 pad318[0x330 - 0x318];
};

typedef char check_C7D[sizeof(C7D) == 0x330 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001F4500(C7D* self, void* stream);         // 0x7D slot 10
void func_001F4660(C7D* self);                       // 0x7D slot 16

#endif
