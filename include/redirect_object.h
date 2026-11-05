// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x5E (RedirectObject) (descriptor D_0021B408, 0x340 bytes), a placed object that can point at itself
// (func_001DE768 raises a flag when it does) and keeps a four-word value at 0x320. Written for
// this project from what retail's code does (config/us/classes.tsv).
//
// Its fields follow class 0x02's and end at the size its descriptor gives; the pads keep every
// field at its retail offset.
#ifndef REDIRECT_OBJECT_H
#define REDIRECT_OBJECT_H

#include "placed_object.h"

#include "shapes.h"   // Quad16

struct RedirectObject : PlacedObject {
    RedirectObject* target; // 0x2D0: the object this one stands for (itself, or another)
    u8 pad2D4[0x2DC - 0x2D4];
    s32 targetIsSelf;       // 0x2DC
    u8 pad2E0[0x320 - 0x2E0];
    Quad16 q320;            // 0x320: set from D_00275730 by func_001DDCE0
    u8 pad330[0x340 - 0x330];
};

typedef char check_RedirectObject[sizeof(RedirectObject) == 0x340 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001DDCE0(RedirectObject* self);                       // 0x5E slot 0
void func_001DE768(RedirectObject* self);                       // 0x5E slot 31

#endif
