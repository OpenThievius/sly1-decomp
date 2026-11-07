// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x36 (descriptor D_0021C038, 0x860 bytes), a part with collision that keeps a list of
// the objects it touches in a record of its own (+0x550), and class 0x37 (D_0021C168, the same
// size) under it. Written for this project from what retail's code does
// (config/us/classes.tsv; src/main/file_1F2758.cpp).
//
// Their fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef CONTACT_TRACKER_H
#define CONTACT_TRACKER_H

#include "collider.h"

struct ContactTracker;

// The record at +0x550 (func_001F5590 sets it up, func_001F55A8 fills its two lists from the
// owner's children and from the ids it keeps, func_001F5840 adds an id, func_001F5868 adds an
// object, func_001F5930 removes one).
struct Rec36 {
    ContactTracker* owner;             // 0x00: the object it is in
    u32 f04;                // 0x04: 0 at set-up
    f32 f08;                // 0x08: 150.0 at set-up
    u8 pad0C[0x10 - 0x0C];
    s32 count;              // 0x10: the ids in keys
    void* keys[32];         // 0x14: object ids (func_001F5840)
    u32 found;              // 0x94: the objects in nodes
    void* nodes[32];        // 0x98
    u8 pad118[0x120 - 0x118];
};

// A held contact: the object it touches and two vectors of the contact (func_001F5008).
struct Slot36 {
    Collider* obj;               // 0x00
    u8 pad04[0x10 - 0x04];
    Vec02 q10;              // 0x10
    Vec02 q20;              // 0x20
};

// 0x36: set up by func_001F4F70, which marks the part (f4E0 = 1, flag bits 36 to 39 = 2) and
// sets up the record; slot 17 (func_001F5008) collects up to ten of the other bodies' objects it
// touches in `slots`.
struct ContactTracker : Collider {
    Rec36 rec;              // 0x550
    Slot36 slots[10];       // 0x670
    s32 count;              // 0x850
    u8 pad854[0x860 - 0x854];
};

// 0x37: the same layout; it also sets bit 43 of the flags and puts v440 and v460 in mode 3.
struct C37 : ContactTracker {
};

typedef char check_Rec36[sizeof(Rec36) == 0x120 ? 1 : -1];
typedef char check_ContactTracker[sizeof(ContactTracker) == 0x860 ? 1 : -1];
typedef char check_C37[sizeof(C37) == 0x860 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitContactTracker(ContactTracker* self);                       // 0x36 slot 0
void CopyContactTracker(ContactTracker* self);                       // 0x36 slot 9
void StartContactTracker(ContactTracker* self);                       // 0x36 slot 16
void CollectTouchingObjects(ContactTracker* self);                       // 0x36 slot 17
void ApplyContactTrackerTransform();                                // 0x36 slot 36 (empty)
int RequestContactTrackerLaunch(ContactTracker* self);                        // 0x36 slot 71
void InitC37(C37* self);                       // 0x37 slot 0

#endif
