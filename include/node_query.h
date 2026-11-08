// SPDX-License-Identifier: AGPL-3.0-or-later
// The query func_00177838 (player.cpp) takes as its first parameter: what it holds, a result
// and a kind. Its callers build it on their stacks (func_00198760 within a 0x40-byte local).
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g2011).
#ifndef NODE_QUERY_H
#define NODE_QUERY_H

#include "common.h"
#include "placed_object.h"

struct NodeQuery {
    union {
        s32 f00;            // 0x00: func_00177838
        void* p00;          // 0x00: func_00198760
    };
    void* hold;             // 0x04: func_00177838 (a PlacedObject), func_00198760
    f32 weight;             // 0x08: the player's mass times 1000 (func_00177990)
    s32 out;                // 0x0C: func_00177838
    s32 kind;               // 0x10: func_00177838
    f32 key;                // 0x14: the order func_00177990 sorts them in (CompareKeysAscending)
    u8 pad18[0x20 - 0x18];
    Vec02 pos;              // 0x20: where (func_001C9990: the agent's position)
    Vec02 dir;              // 0x30
};


#endif
