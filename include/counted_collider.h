// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4C (descriptor D_0021B9A8, 0x560 bytes), a counted collider: a part with collision
// that counts its touches down and then goes away (TakeCountedColliderTouch sends its message,
// lets go of its handle and removes it). Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/player_mode.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef COUNTED_COLLIDER_H
#define COUNTED_COLLIDER_H

#include "collider.h"

struct CountedCollider : Collider {
    s32 touchesLeft;        // 0x550: TakeCountedColliderTouch counts it down
    s32 contacts;           // 0x554: a chain of pooled contacts (FreePooledContactChain)
    void* target;           // 0x558: the object TakeCountedColliderTouch sends the empty message to
    u8 pad55C[0x560 - 0x55C];
};

typedef char check_CountedCollider[sizeof(CountedCollider) == 0x560 ? 1 : -1];

// The methods that take only types known here (config/us/classes.tsv); a slot's function takes
// its class's object. Slots 13 (func_001D3678) and 45 (func_001D3500) take records that
// player_mode.cpp declares; slots 17 and 19 (func_001D3398, func_001D35A8) are assembly.
void StartCountedCollider(CountedCollider* self);                       // 0x4C slot 16
void StepCountedCollider(CountedCollider* self, f32 t);                // 0x4C slot 28
void CollectCountedColliderContacts(CountedCollider* self);                       // 0x4C slot 63

#endif
