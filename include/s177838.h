// SPDX-License-Identifier: AGPL-3.0-or-later
// The query func_00177838 (00174000.cpp) takes as its first parameter: what it holds, a result
// and a kind. Its callers build it on their stacks (func_00198760 within a 0x40-byte local).
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g2011).
#ifndef S177838_H
#define S177838_H

#include "common.h"

struct S177838 {
    union {
        s32 f00;            // 0x00: func_00177838
        void* p00;          // 0x00: func_00198760
    };
    void* hold;             // 0x04: func_00177838 (Node_177838), func_00198760
    s32 f08;                // 0x08
    s32 out;                // 0x0C: func_00177838
    s32 kind;               // 0x10: func_00177838
};


#endif
