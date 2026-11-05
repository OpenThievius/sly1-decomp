// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x27 (descriptor D_00218AA8, 0x570 bytes): a collision object with three states that
// moves on to the next after a time or when it is hit (func_0013DD78 sets the state, slot 17,
// func_0013DC38, runs it). Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef TIMED_STATE_OBJECT_H
#define TIMED_STATE_OBJECT_H

#include "collider.h"

// The object at +0x560: a part of another class whose +0x694 func_0013DD08 tests.
struct Child27 {
    u8 pad0[0x694];
    s32 f694;
};

struct TimedStateObject : Collider {
    s32 state;              // 0x550: func_0013DD78 sets it
    f32 stamp;              // 0x554: the clock when the state changed (D_0026185C)
    f32 limit;              // 0x558: how long state 1 lasts
    f32 param;              // 0x55C: handed to func_00126D60 when the state becomes 2
    Child27* child;             // 0x560
    s32 acceptAll;              // 0x564
    u8 pad568[0x570 - 0x568];
};

typedef char check_TimedStateObject[sizeof(TimedStateObject) == 0x570 ? 1 : -1];

void func_0013DCA8(TimedStateObject* self, s32 kind, void* msg);     // slot 13
void func_0013DC38(TimedStateObject* self);                          // slot 17
s32 func_0013DD08(TimedStateObject* self, Collider* other);               // slot 57
void func_0013DD78(TimedStateObject* self, s32 state);               // sets the state

#endif
