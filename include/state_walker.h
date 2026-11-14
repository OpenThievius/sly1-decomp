// SPDX-License-Identifier: AGPL-3.0-or-later
// The handle func_001B6290(owner, a, key, b) makes for an object: taken from the world's pool
// at World+0x1B88 (func_001B5EE0; func_001DB4C8 makes it of 0x100 entries of 0x40 bytes), its table
// D_002198E8 stored at +0, and put in the world's list at +0x1B94 and the owner's at +0x48.
// StateTrigger::walker holds one, and so do TintBlendCollider+0x75C, C17+0x614, ModeWalker+0xBBC and C24+0x6C8. func_001B6568,
// func_001B6628, func_001B66A0 and func_001B6E28 (state_walker.cpp) read it. Written for this project
// from what retail's code does (build/swarm/st3/groups.tsv, g1937).
#ifndef STATE_WALKER_H
#define STATE_WALKER_H

#include "common.h"

struct StateGraph;
struct StateEdge;
struct AnimationPlayer;
struct QueuedCall;

struct StateWalker {
    const void* vt;         // 0x00: D_002198E8
    u8 pad04[0x08 - 0x04];
    StateWalker* next;      // 0x08: in its graph's list (func_001B6388 walks it)
    u8 pad0C[0x10 - 0x0C];
    StateWalker* worldNext; // 0x10: in World::list1B94 (offset 0x10; func_00129C20 walks it)
    u8 pad14[0x18 - 0x14];
    StateGraph* owner;      // 0x18: func_001B6290's first argument; func_001B6568, func_001B6628
    void* object;           // 0x1C: the second: the object it drives, its key in the graph's list
    s32 playerFlags;        // 0x20: the fourth
    AnimationPlayer* player; // 0x24: what plays the current edge's animation (func_001B66A0); a
                             // message from it names it as its source (func_00181D28)
    s32 currentEntry;       // 0x28: func_001B6628
    s32 nextEntry;          // 0x2C: -1 at set-up; func_001B6628
    s32 index;              // 0x30: func_001B6568, func_001B6628
    StateEdge* edge;        // 0x34: the edge it is on (func_001B66A0)
    f32 speed;              // 0x38: 1 at set-up; the speed along an edge
    QueuedCall* calls;      // 0x3C: told of each change (func_001B6D78), released with it
};

typedef char check_StateWalker[sizeof(StateWalker) == 0x40 ? 1 : -1];

#endif
