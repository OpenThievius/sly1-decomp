// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x88 (descriptor D_00219868, 0x54 bytes), a direct child of the root class 0x01 and
// no class under it: a graph of states (docs/DISC.md). Written for this project from what
// retail's code does (config/us/classes.tsv). Its own methods are func_001B5F50 (slot 10, not
// defined in C yet) and func_001B61A8 (slot 16).
#ifndef STATE_GRAPH_H
#define STATE_GRAPH_H

#include "base_object.h"

// An entry of the graph's state table: its key (func_001B63C0 looks one up) and a second word.
struct StateEntry {
    s32 key;                // 0x00
    s32 extra;              // 0x04: the state a walker goes on to once it arrives (func_001B66A0)
};

struct Animation;

// An edge of the graph (0x14 bytes): the animation that plays along it (0 for a jump), its two
// states, flag 1 for both ways, and its weight in the random choice (func_001B66A0).
struct StateEdge {
    Animation* anim;        // 0x00: its id picks the object the first walker drives (func_001B61F0)
    s32 a;                  // 0x04
    s32 b;                  // 0x08
    u32 flags;              // 0x0C
    f32 weight;             // 0x10
};

struct StateGraph : BaseObject {
    s32 f34;                // 0x34: the entries at 0x38
    StateEntry* f38;        // 0x38: the state table
    s32 edgeCount;          // 0x3C
    StateEdge* edges;       // 0x40
    s32 armed;              // 0x44: nonzero once the graph has something to run
    List01 walkers;         // 0x48: its walkers (StateWalker::next, func_001B6290)
};

typedef char check_StateGraph[sizeof(StateGraph) == 0x54 ? 1 : -1];

void StartStateGraph(StateGraph* self);                  // slot 16

#endif
