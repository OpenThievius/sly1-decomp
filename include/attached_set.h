// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x1F (descriptor D_00218770, 0x6B0 bytes), an attached set: a collision object that keeps
// a list of the objects attached to it (+0x550; each link is also in the target's list at
// Collider::attached), registers itself and their targets with the world as one group
// (RebuildAttachedSet) and keeps the tracked-node record a contact tracker keeps
// (include/contact_tracker.h) at +0x590 (InitTrackedNodes sets it up, FillTrackedNodes and
// OfferTrackedNodeLaunch work on it). Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef ATTACHED_SET_H
#define ATTACHED_SET_H

#include "collider.h"
#include "contact_tracker.h"

// The group RebuildAttachedSet hands to the world (UnregisterObjectGroup, RegisterObjectGroup):
// the object itself, then the targets of its links.
struct AttachedGroup {
    u8 pad0[8];
    s32 count;              // 0x08
    void** items;           // 0x0C: a block of 0x80 bytes (StartAttachedSet)
};

struct AttachedSet : Collider {
    Attach03* links;        // 0x550: the objects attached to it (linked at Attach03::nextOwn)
    AttachedGroup group;    // 0x554
    u8 pad564[0x580 - 0x564];
    s32 f580;               // 0x580: nonzero, a body landing on it is told of the point (func_001EEF90)
    s32 f584;               // 0x584: 1 at set-up
    s32 f588;               // 0x588: 1 at set-up
    u8 pad58C[0x590 - 0x58C];
    Rec36 trackedNodes;     // 0x590: tracked nodes, as a contact tracker keeps (InitAttachedSet)
};

typedef char check_AttachedSet[sizeof(AttachedSet) == 0x6B0 ? 1 : -1];

#endif
