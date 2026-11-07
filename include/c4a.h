// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x4A (descriptor D_002206F8, 0x620 bytes), an object with collision that switches
// between two modes (func_0017B410 sets the mode, takes the camera system's state, and starts
// the object it keeps for each) and hands out three sound handles it makes when it is loaded.
// Written for this project from what retail's code does (config/us/classes.tsv;
// src/main/file_1793C0.cpp).
//
// Its fields follow class 0x03's and end at the size the descriptor gives; the pads keep every
// field at its retail offset.
#ifndef C4A_H
#define C4A_H

#include "collider.h"

struct C4A : Collider {
    s32 mode;               // 0x550: -1 at set-up (slot 0, func_0017ADD0); func_0017B410 sets it
    f32 f554;               // 0x554: the clock when the mode was set
    u8 f558[4];             // 0x558: passed with the object to func_0012C918
    u8 grpA[0x24];          // 0x55C: the first group of func_00139038 (slot 10)
    f32 fA;                 // 0x580: 1.0
    u8 pad584[0x58C - 0x584];
    void* ptrA;             // 0x58C: the handle it gives
    f32 fB;                 // 0x590: 1.0, the second group
    u8 padB[0x5C0 - 0x594];
    void* ptrB;             // 0x5C0
    f32 fC;                 // 0x5C4: 1.0, the third group
    u8 padC[0x600 - 0x5C8];
    void* ptrC;             // 0x600
    u8 f604[4];             // 0x604: passed with the object to func_0012C918 by func_0017B510
    s32 f608;               // 0x608: compared with a message's id by slot 45 (func_0017B3A8)
    void* f60C;             // 0x60C: the object func_0017B550 finds; func_0017B598 starts it
    u8 f610[0x620 - 0x610]; // 0x610: passed with the object to func_0012C918 by func_0017B598
};

typedef char check_C4A[sizeof(C4A) == 0x620 ? 1 : -1];

#endif
