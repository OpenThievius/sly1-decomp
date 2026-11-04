// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x34 (descriptor D_0021B2D8, 0x5B0 bytes), a collidable object that only reacts to some
// objects: two lists of ids (object ids, then class ids) say which, and whether the lists are
// what it accepts or what it leaves out (slot 56, func_0012FA88, answers for an object). At set-up
// it takes the placement of a child object (func_0012F8C8, slot 16) or finds an object by id,
// and slot 17 (func_0012F9B8) hands that placement on to an object it keeps at +0x5A0. Written
// for this project from what retail's code does (config/us/classes.tsv;
// src/main/0012C000.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. The class adds no slot to 0x03's descriptor.
#ifndef C34_H
#define C34_H

#include "c03.h"

struct C34 : C03 {
    s32 accept;             // 0x550: 1 when the lists name what it reacts to, 0 when they name what it leaves out
    Ids03 objects;          // 0x554: object ids (func_0012FCB0)
    Ids03 kinds;            // 0x568: class ids (func_0012FCD0)
    u8 pad57C[0x580 - 0x57C];
    s32 mode;               // 0x580: 1 when f590 holds a position taken from the one child, 2 when it holds the
                            // object that was found by id
    u8 pad584[0x590 - 0x584];
    union {
        s32 id;             // 0x590: -1 at set-up, then the id to find
        C02* found;         // 0x590: the object found by that id (mode 2)
        Vec02 pos;          // 0x590: the child's placement in this object's frame (mode 1)
    };
    C02* target;            // 0x5A0: the object slot 17 sets the placement of, then keeps in f5A4
    C02* done;              // 0x5A4
    u8 pad5A8[0x5B0 - 0x5A8];
};

typedef char check_C34[sizeof(C34) == 0x5B0 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_0012F840(C34* self);                      // 0x34 slot 0
void func_0012F888(C34* self);                      // 0x34 slot 9
void func_0012F8C8(C34* self);                      // 0x34 slot 16
void func_0012F9B8(C34* self);                      // 0x34 slot 17
s32 func_0012FA88(C34* self, C03* key);             // 0x34 slot 56
void func_0012FCB0(C34* self, s32 id);              // the first list's add
void func_0012FCD0(C34* self, s32 id);              // the second list's add

#endif
