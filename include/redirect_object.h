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
    Vec02 vel;              // 0x10: its velocity (func_001278A8; func_001DDE90 integrates it)
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
    f32 bendStiffness;      // 0x2E0: func_001DDE90 turns a bent step back by it times the angle
    f32 drag;               // 0x2E4: func_001DDE90 takes -drag * h (at most 1) of the velocity off
    f32 relDrag;            // 0x2E8: the same for the velocity relative to the step before
    f32 maxBend;            // 0x2EC: the angle a step may bend from the one before
    s32 iterations;         // 0x2F0: the substeps func_001DDE90 divides the frame into
    u8 pad2F4[0x300 - 0x2F4];
    Vec02 gravity;          // 0x300: added to every free step's velocity each frame
    s32 f310;               // 0x310
    u8 pad314[0x320 - 0x314];
    Quad16 q320;            // 0x320: set from D_00275730 by func_001DDCE0
    s32 frameStamp;         // 0x330: the frame count of the last update (func_001DDE90)
    u8 pad334[0x340 - 0x334];
};

typedef char check_RedirectObject[sizeof(RedirectObject) == 0x340 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitRedirectObject(RedirectObject* self);                       // 0x5E slot 0
void MarkRedirectToSelf(RedirectObject* self);                       // 0x5E slot 31

#endif
