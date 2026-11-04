// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4D (descriptor 0x640 bytes, parent 0x02), an object that registers itself in its
// level's list at +0x1CC0 and keeps a list of its own at +0x624. Written for this project from
// what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. Its methods also use two of class 0x02's fields (include/c02.h):
// the float at 0x80 and the flags word at 0x2C8.
#ifndef C4D_H
#define C4D_H

#include "c02.h"

struct Sub4D {
    u8 pad00[0xC];
    u32 flags;              // 0x0C
};

// The list at +0x624: first element, a pad, and the offset of the link inside an element
// (func_00139EC8 walks it).
struct List4D {
    s32 head;               // 0x00
    u8 pad04[4];
    s32 link;               // 0x08
};

struct C4D : C02 {
    void* owner;            // 0x2D0: the object a copy was taken from (func_0013A418)
    u8 pad2D4[0x380 - 0x2D4];
    Sub4D* sub;             // 0x380
    u8 pad384[0x624 - 0x384];
    List4D list;            // 0x624
    u8 pad630[0x640 - 0x630];
};

typedef char check_C4D[sizeof(C4D) == 0x640 ? 1 : -1];

void func_00139DE8(C4D* self);                       // slot 0
void func_00139E80(C4D* self);                       // slot 6
void func_00139EC8(C4D* self);                       // slot 7
void func_0013A3A0(C4D* self);                       // slot 17
void func_0013A418(C4D* self, C01* src);             // slot 23
void func_0013AD08(C4D* owner, s32 unused, void* src); // slot 37

#endif
