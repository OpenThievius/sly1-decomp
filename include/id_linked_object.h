// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x66 (descriptor D_00220F50, 0x340 bytes), a placed object (class 0x02) that follows
// another object it names by id. Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// Fields follow the parent's 0x2D0 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef ID_LINKED_OBJECT_H
#define ID_LINKED_OBJECT_H

#include "placed_object.h"

// 0x66: func_001C1030 sets the id: it lets go of the old link (func_001B6438), looks the id
// up (func_0015A418 with 0x101) and links to what it finds (func_001B6290).
struct IdLinkedObject : PlacedObject {
    u32 color;              // 0x2D0: 0x80808080 at set-up (InitIdLinkedObject)
    f32 f2D4;               // 0x2D4: 0.5 at set-up
    f32 f2D8;               // 0x2D8: 400.0 at set-up
    f32 f2DC;               // 0x2DC: 0.5 at set-up
    f32 f2E0;               // 0x2E0: 0.5 at set-up
    u8 pad2E4[0x2F0 - 0x2E4];
    Vec02 v2F0;             // 0x2F0: (0, 0, 50) at set-up
    Vec02 v300;             // 0x300: (100, 80, 50) at set-up
    u8 pad310[0x320 - 0x310];
    f32 f320;               // 0x320: 0.3 at set-up
    f32 f324;               // 0x324: 0.5 at set-up
    u8 pad328[0x32C - 0x328];
    s32 linkId;             // 0x32C
    s32 linkTarget;         // 0x330: what func_0015A418 returns for linkId
    s32 link;               // 0x334: what func_001B6290 returns, 0 for none
    u8 pad338[0x340 - 0x338];
};

typedef char check_IdLinkedObject[sizeof(IdLinkedObject) == 0x340 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void InitIdLinkedObject(IdLinkedObject* self);                        // 0x66 slot 0
void StartIdLinkedObject(IdLinkedObject* self);                       // 0x66 slot 16
void SetObjectLinkId(IdLinkedObject* self, s32 id);               // sets linkId (called by slot 16)

#endif
