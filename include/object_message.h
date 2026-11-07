// SPDX-License-Identifier: AGPL-3.0-or-later
// The payload of a message sent to an object: the third parameter of class 0x02's slot 13 (func_00127378, c02.h)
// and its overrides (func_0013B708, func_0013DCA8, func_00198EF8, func_001D3678, func_001D7040).
// Its senders build it on their stacks, so it is named by the function that takes it. Its
// shape depends on the message: a kind and an object, or a key at 0x08. Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g1366).
#ifndef OBJECT_MESSAGE_H
#define OBJECT_MESSAGE_H

#include "common.h"

struct ObjectMessage {
    union {
        s32 kind;           // 0x00: func_0013B708, func_0013DCA8, func_001D3678
        void* p0;           // 0x00: func_001D7040
    };
    void* target;           // 0x04: an object (ChildGroupObject in func_0013B708, TimedStateObject in func_0013DCA8, StandIn in func_001D7040)
    s32 key;                // 0x08: func_00198EF8
};

#endif
