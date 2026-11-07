// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x3A (descriptor D_0021A660, 0x570 bytes), a part with collision that is kept in a list
// of its own (the one at D_00262708, linked at +0x558). Written for this project from what
// retail's code does (config/us/classes.tsv; src/main/file_167D68.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef LISTED_COLLISION_PART_H
#define LISTED_COLLISION_PART_H

#include "collider.h"

// 0x3A: slot 6 appends it to the list (func_00152470), slot 7 removes it (func_00152600),
// slot 9 keeps the link across the copy.
struct ListedCollisionPart : Collider {
    s32 f550;               // 0x550: 0 means func_0016A580 (slot 28) lets the parts follow it
    u8 pad554[0x558 - 0x554];
    Link02 listLink;         // 0x558: the link in the list (func_00152438 gets the offset)
    u8 pad560[0x568 - 0x560];
    f32 f568;               // 0x568: 300.0 at set-up
    u8 pad56C[0x570 - 0x56C];
};

typedef char check_ListedCollisionPart[sizeof(ListedCollisionPart) == 0x570 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_0016A3A8(ListedCollisionPart* self);                       // 0x3A slot 0
void func_0016A490(ListedCollisionPart* self);                       // 0x3A slot 6
void func_0016A4C8(ListedCollisionPart* self);                       // 0x3A slot 7
void func_0016A500(ListedCollisionPart* self);                       // 0x3A slot 9
void func_0016A420(ListedCollisionPart* self);                       // 0x3A slot 10
void func_0016A580(ListedCollisionPart* self, f32 t);                // 0x3A slot 28
s32 func_0016A548(Collider* self, Collider* other);            // 0x3A slot 56

#endif
