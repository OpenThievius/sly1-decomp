// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x49 (descriptor D_0021FD58, 0x570 bytes), a collider that takes no contacts: its only
// own method, slot 0 (InitContactlessCollider), sets bit 43 of Collider's flags538, the flag
// SetColliderContactsDropped sets, which span collection, part contacts and notifier targeting
// skip; class 0x37 and the player's body parts set it the same way. It adds nothing of its own
// that the matched code reads. Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef CONTACTLESS_COLLIDER_H
#define CONTACTLESS_COLLIDER_H

#include "collider.h"

struct ContactlessCollider : Collider {
    u8 pad550[0x570 - 0x550];
};

typedef char check_ContactlessCollider[sizeof(ContactlessCollider) == 0x570 ? 1 : -1];

#endif
