// SPDX-License-Identifier: AGPL-3.0-or-later
// Three words and a function, the first parameter of func_001D7098 (001D4000.cpp): its callers
// (func_001DE910, func_001EB748, func_001F5C0C's users) build it on their stacks. Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g3274).
#ifndef S1D7098_H
#define S1D7098_H

#include "common.h"

struct S1D7098 {
    s32 a;                  // 0x00
    s32 b;                  // 0x04
    s32 c;                  // 0x08
    union {
        void (*fn)(void);   // 0x0C: func_001EB748
        s32 d;              // 0x0C: func_001DE910
    };
};

#endif
