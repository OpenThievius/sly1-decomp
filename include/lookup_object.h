// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4E (descriptor D_00217A90, 0x320 bytes), a placed object that looks up another
// object by id (func_001F4E48 finds it in its level and keeps it in one of two fields by the
// kind of object it is). Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C4E_H
#define C4E_H

#include "c02.h"

// 0x4E: the id at 0x2D0 (-1 for none), and the objects found by it.
struct C4E : C02 {
    s32 id;                 // 0x2D0: -1 for none
    C01* found2D4;          // 0x2D4: the object found, when it is not a group (flags 0x1)
    C01* found2D8;          // 0x2D8: the object found, when it is a group (flags 0x1)
    u8 pad2DC[0x320 - 0x2DC];
};

typedef char check_C4E[sizeof(C4E) == 0x320 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001F4E18(C4E* self);                       // 0x4E slot 0
void func_001F4E48(C4E* self);                       // 0x4E slot 16

#endif
