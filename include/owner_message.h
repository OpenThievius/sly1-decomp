// SPDX-License-Identifier: AGPL-3.0-or-later
// Three words and a function, the first parameter of func_001D7098 (001D4000.cpp): its callers
// (func_001DE910, func_001EB748, func_001F5C0C's users) build it on their stacks. Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g3274).
#ifndef OWNER_MESSAGE_H
#define OWNER_MESSAGE_H

#include "common.h"

struct OwnerMessage {
    s32 mode;               // 0x00: func_001D7098 (0 or 2 from its callers)
    s32 owner;              // 0x04: func_001D7098 (the object it is built for)
    s32 c;                  // 0x08: func_001D7098 (the same object again)
    union {
        void (*fn)(void);   // 0x0C: func_001EB748
        s32 d;              // 0x0C: func_001DE910
    };
};

#endif
