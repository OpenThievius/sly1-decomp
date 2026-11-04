// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x1E (descriptor D_00219AF0, 0x570 bytes), a part with collision
// that keeps a list of records of its own (+0x558: func_0019EA78 allocates one for an owner and
// links it in, func_0019EBE8 takes it out; slot 17, func_0019E420, updates each and finds what
// touches the bodies it is in contact with, func_0019E558). The objects are pooled: the world
// keeps the unused ones in a list at +0x1B38 (linked at +0x564) and the last one it handed out
// at +0x1B3C (func_0019E040). Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/0019C000.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. The class adds no slot to 0x03's descriptor.
#ifndef C1E_H
#define C1E_H

#include "c03.h"

struct T219C;   // the records of list558 (include/t219c.h)

struct C1E : C03 {
    s32 f550;               // 0x550: 0 or 1, as the world hands the object out (func_0019E040 sets it);
                            // func_0019E558 only runs for 1
    u8 pad554[0x558 - 0x554];
    List01 list558;         // 0x558: the T219C records of its owners (link offset 0x10, func_00152438)
    C1E* saved564;          // 0x564: the next object in the world's unused list (+0x1B38)
    u8 pad568[0x570 - 0x568];
};

typedef char check_C1E[sizeof(C1E) == 0x570 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_0019E0B8(C1E* self);                      // 0x1E slot 0
void func_0019E168(C1E* self);                      // 0x1E slot 7
void func_0019E420(C1E* self, f32 t);               // 0x1E slot 17
void func_0019E848(C1E* self, void* arg);           // 0x1E slot 37

#endif
