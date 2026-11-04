// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x2C (descriptor D_0021CC78, 0x5A0 bytes), an object with collision that looks up a few
// objects of its world when it is loaded and keeps them (func_00198A88 finds them by id,
// func_00198B28 lets go of them), and its two subclasses 0x2D (0x5B0) and 0x2E (0x5C0), whose
// loaders keep one more value each. Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/00198000.cpp).
//
// Each class derives from its parent's, with every field at its retail offset and the pads
// that keep it there, up to the size the descriptor gives.
#ifndef C2C_H
#define C2C_H

#include "c03.h"

struct C2C : C03 {
    u8 pad550[0x554 - 0x550];
    s32 f554;               // 0x554: slot 0 (func_00198980) sets 1; func_00198E98 (slot 72) tests it
    s32 f558;               // 0x558: func_00198B28 (slot 16) sets 1 when a kept object answers
    s32 n55C;               // 0x55C: how many ids follow; func_00198ED8 appends at keys560[n55C++]
    void* keys560[4];       // 0x560: the ids func_00198A88 (slot 15) looks up in the world
    s32 count570;           // 0x570: how many objects were found
    void* found574[4];      // 0x574: the found objects (slots 15, 16, 73, 13: func_00198EF8 compares
                            //        a message's key with each)
    void* f584;             // 0x584: the fifth found object (slot 74 sends it a message); its
                            //        address is the record func_001989B0 loads (func_00159478)
    s32 marks588[4];        // 0x588: func_00198EF8 (slot 13) marks the found objects it was told of
    s32 done598;            // 0x598: set with it
    s32 f59C;               // 0x59C: func_00199000 (slot 60)
};

typedef char check_C2C[sizeof(C2C) == 0x5A0 ? 1 : -1];

struct C2D : C2C {
    s32 f5A0;               // 0x5A0: slot 0 (func_00199070) stores a table entry; the others pass it as an index
    u8 pad5A4[0x5B0 - 0x5A4];
};

typedef char check_C2D[sizeof(C2D) == 0x5B0 ? 1 : -1];

struct C2E : C2C {
    s32 f5A0;               // 0x5A0: an index into the world's bit table (func_00199C10, func_00199500, func_00199850)
    f32 f5A4;               // 0x5A4: func_00199500 (slot 16)
    f32 f5A8;               // 0x5A8
    s32 n5AC;               // 0x5AC: func_00199428 (slot 10) counts the objects it finds ...
    void* f5B0;             // 0x5B0: ... in this 0x80-byte array
    f32 f5B4;               // 0x5B4: func_00199500
    f32 f5B8;               // 0x5B8
    u8* f5BC;               // 0x5BC: the object func_001999D0 (slot 73) was made for
};

typedef char check_C2E[sizeof(C2E) == 0x5C0 ? 1 : -1];

#endif

