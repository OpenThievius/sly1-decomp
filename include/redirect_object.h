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

// One step of the chain func_001DDD18 builds: the object's position, the point below it, its
// length and the object.
struct RedirectStep {
    Vec02 pos;              // 0x00: the object's v140
    u8 pad10[0x10];
    Vec02 below;            // 0x20
    f32 length;             // 0x30
    PlacedObject* node;     // 0x34
    u8 pad38[8];
};

struct RedirectObject : PlacedObject {
    RedirectObject* target; // 0x2D0: the object this one stands for (itself, or another)
    s32 chainCount;         // 0x2D4: the redirect objects in the chain below it (func_001DDD18)
    RedirectStep* steps;    // 0x2D8: chainCount + 1 records, one per object of the chain
    s32 targetIsSelf;       // 0x2DC
    u8 pad2E0[0x310 - 0x2E0];
    s32 f310;               // 0x310
    u8 pad314[0x320 - 0x314];
    Quad16 q320;            // 0x320: set from D_00275730 by func_001DDCE0
    u8 pad330[0x340 - 0x330];
};

typedef char check_RedirectObject[sizeof(RedirectObject) == 0x340 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitRedirectObject(RedirectObject* self);                       // 0x5E slot 0
void MarkRedirectToSelf(RedirectObject* self);                       // 0x5E slot 31

#endif
