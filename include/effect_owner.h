// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x1E (descriptor D_00219AF0, 0x570 bytes), a part with collision
// that keeps a list of records of its own (+0x558: func_0019EA78 allocates one for an owner and
// links it in, func_0019EBE8 takes it out; slot 17, func_0019E420, updates each and finds what
// touches the bodies it is in contact with, func_0019E558). The objects are pooled: the world
// keeps the unused ones in a list at +0x1B38 (linked at +0x564) and the last one it handed out
// at +0x1B3C (func_0019E040). Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/class_descriptors.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. The class adds no slot to 0x03's descriptor.
#ifndef EFFECT_OWNER_H
#define EFFECT_OWNER_H

#include "collider.h"

struct Effect;   // the records of list558 (include/t219c.h)

struct EffectOwner : Collider {
    s32 f550;               // 0x550: 0 or 1, as the world hands the object out (func_0019E040 sets it);
                            // func_0019E558 only runs for 1
    f32 f554;               // 0x554
    List01 list558;         // 0x558: the Effect records of its owners (link offset 0x10, func_00152438)
    EffectOwner* saved564;          // 0x564: the next object in the world's unused list (+0x1B38)
    u8 pad568[0x570 - 0x568];
};

typedef char check_EffectOwner[sizeof(EffectOwner) == 0x570 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitEffectOwner(EffectOwner* self);                      // 0x1E slot 0
void ReleaseEffectOwner(EffectOwner* self);                      // 0x1E slot 7
void UpdateEffectOwner(EffectOwner* self, f32 t);               // 0x1E slot 17
void DrawEffects(EffectOwner* self, void* arg, void* arg2);           // 0x1E slot 37

#endif
