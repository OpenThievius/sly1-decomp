// SPDX-License-Identifier: AGPL-3.0-or-later
// The handle func_001B6290(owner, a, key, b) makes for an object: taken from the world's pool
// at World+0x1B88 (func_001B5EE0; func_001DB4C8 makes it of 0x100 entries of 0x40 bytes), its table
// D_002198E8 stored at +0, and put in the world's list at +0x1B94 and the owner's at +0x48.
// StateTrigger::f55C holds one, and so do TintBlendCollider+0x75C, C17+0x614, ModeWalker+0xBBC and C24+0x6C8. func_001B6568,
// func_001B6628, func_001B66A0 and func_001B6E28 (001B4000.cpp) read it. Written for this project
// from what retail's code does (build/swarm/st3/groups.tsv, g1937).
#ifndef STATE_WALKER_H
#define STATE_WALKER_H

#include "common.h"

struct StateWalker {
    const void* vt;         // 0x00: D_002198E8
    u8 pad04[0x18 - 0x04];
    void* owner;            // 0x18: func_001B6290's first argument; func_001B6568, func_001B6628
    s32 f1C;                // 0x1C: the second
    s32 f20;                // 0x20: the fourth
    u8 pad24[0x28 - 0x24];
    s32 f28;                // 0x28: func_001B6628
    s32 f2C;                // 0x2C: -1 at set-up; func_001B6628
    s32 index;              // 0x30: func_001B6568, func_001B6628
    f32 f34;                // 0x34
    f32 f38;                // 0x38: 1 at set-up
    u8 pad3C[0x40 - 0x3C];
};

typedef char check_StateWalker[sizeof(StateWalker) == 0x40 ? 1 : -1];

#endif
