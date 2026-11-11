// SPDX-License-Identifier: AGPL-3.0-or-later
// The payload of a message sent to an object: the third parameter of class 0x02's slot 13 (func_00127378, c02.h)
// and its overrides (func_0013B708, func_0013DCA8, func_00198EF8, func_001D3678, func_001D7040).
// Its senders build it on their stacks, so it is named by the function that takes it. Its
// shape depends on the message: a kind and an object, or a key at 0x08. Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g1366).
#ifndef OBJECT_MESSAGE_H
#define OBJECT_MESSAGE_H

#include "common.h"
#include "shapes.h"
#include "placed_object.h"

struct ObjectMessage {
    union {
        s32 kind;           // 0x00: func_0013B708, func_0013DCA8, func_001D3678
        void* p0;           // 0x00: func_001D7040
    };
    void* target;           // 0x04: an object (ChildGroupObject in func_0013B708, TimedStateObject in func_0013DCA8, StandIn in func_001D7040)
    s32 key;                // 0x08: func_00198EF8
};

// A message an object receives through its slot 27 (Desc01::m1B), built in a 0x50-byte local:
// its kind, and the sender (kind 1) or quadwords (kinds 4 and 6; file_198980.cpp, effect.cpp,
// file_1A3AE0.cpp).
struct SlotMessage {
    union {
        s32 kind;           // 0x00
        s32 flags;          // 0x00: what func_0012D5D0 fills (1 owner, 4 qb, 8|0x10 f30, 0x20 f38)
    };
    void* owner;            // 0x04
    u8 pad08[0x10 - 0x08];
    union {
        Quad16 qa;          // 0x10
        Vec02 va;           // 0x10: as floats (kind 6: func_001A6DE0, func_001A72B0)
    };
    union {
        Quad16 qb;          // 0x20
        Vec02 vb;           // 0x20
    };
    f32 f30;                // 0x30: func_0012D5D0 (event 48, with flags 0x18); a zone's f620 (kind 9, func_0013D278)
    f32 f34;                // 0x34: the zone's radius (kind 9, func_0013D278)
    void* f38;              // 0x38: func_0012D5D0 (event 48, flag 0x20)
    u8 pad3C[0x50 - 0x3C];
};

#endif
