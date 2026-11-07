// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x49 (descriptor D_0021FD58, 0x570 bytes), a box collider: a collision object whose only
// own method, slot 0 (InitBoxCollider), sets the bit of Collider's flags538 that makes
// CollectColliderSpans test its box at +0x140 instead of a tree. It adds nothing of its own that
// the matched code reads. Written for this project from what retail's code does
// (config/us/classes.tsv).
#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "collider.h"

struct BoxCollider : Collider {
    u8 pad550[0x570 - 0x550];
};

typedef char check_BoxCollider[sizeof(BoxCollider) == 0x570 ? 1 : -1];

#endif
