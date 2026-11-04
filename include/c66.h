// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x66 (descriptor D_00220F50, 0x340 bytes), a placed object (class 0x02) that follows
// another object it names by id. Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// Fields follow the parent's 0x2D0 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef C66_H
#define C66_H

#include "c02.h"

// 0x66: func_001C1030 sets the id: it lets go of the old link (func_001B6438), looks the id
// up (func_0015A418 with 0x101) and links to what it finds (func_001B6290).
struct C66 : C02 {
    u8 pad2D0[0x32C - 0x2D0];
    s32 id32C;              // 0x32C
    s32 found330;           // 0x330: what func_0015A418 returns for id32C
    s32 link334;            // 0x334: what func_001B6290 returns, 0 for none
    u8 pad338[0x340 - 0x338];
};

typedef char check_C66[sizeof(C66) == 0x340 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
// Slot 0, func_001C0F30, is original assembly.
void func_001C0FF0(C66* self);                       // 0x66 slot 16
void func_001C1030(C66* self, s32 id);               // sets id32C (called by slot 16)

#endif
