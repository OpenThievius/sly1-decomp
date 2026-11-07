// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4B (descriptor D_00220828, 0x570 bytes), an object with collision that keeps up to
// three handles (0x55C, 0x560, 0x564) and counts a number down from 0x10 (func_0017B7A8, slot
// 45). Written for this project from what retail's code does (config/us/classes.tsv;
// src/main/file_1793C0.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef COUNTDOWN_COLLIDER_H
#define COUNTDOWN_COLLIDER_H

#include "collider.h"

// The record at CountdownCollider::record, which func_0017B648 (slot 17) lets go of when its field at 0x18
// has run to zero.
struct CountdownRecord {
    u8 pad00[0x18];
    f32 remaining;
};

struct CountdownCollider : Collider {
    s32 mode;               // 0x550: func_0017B648 tests it for 2; func_0017B710 (slot 46) for 1
    f32 startTime;          // 0x554: the clock func_0017B648 compares against
    s32 countdown;          // 0x558: 0x10 at set-up (slot 0, func_0017B5D0); func_0017B7A8 counts it down
    void* f55C;             // 0x55C
    void* f560;             // 0x560
    void* f564;             // 0x564
    CountdownRecord* record;      // 0x568: func_0017B7A8 passes its address
    u8 pad56C[0x570 - 0x56C];
};

typedef char check_CountdownCollider[sizeof(CountdownCollider) == 0x570 ? 1 : -1];

#endif
