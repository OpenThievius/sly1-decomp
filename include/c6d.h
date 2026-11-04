// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6D (descriptor D_00221520, 0x590 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Only the span func_00143648
// sets up is declared; its other users (file_143140.cpp) still reach the rest by offset.
#ifndef C6D_H
#define C6D_H

#include "c01.h"
#include "t2173.h"

// func_00143648 (slot 0) fills the identity frame at 0x80 and the settings at 0x1C0..0x208,
// then five sub-objects at 0x454, 0x460, 0x4C0, 0x510 and 0x520.
//
// The controllers are the kind t2173 (include/t2173.h). The camera keeps the ones in action in
// a stack ordered by key: func_00145088 pushes, func_001451F0 removes, func_00143E40 runs the
// first. The stack's size is the span up to the first controller (no code checks a limit).
struct C6D : C01 {
    u8 pad34[0x3D0 - 0x34]; // 0x34
    s32 stackCount;         // 0x3D0: how many entries are in use
    T2173Entry stack[8];    // 0x3D4: the first is in action
    T2173 ctl454;           // 0x454: D_00217398
    T2173_3B0 ctl460;       // 0x460: D_002173B0
    T2173_3C8 ctl4C0;       // 0x4C0: D_002173C8
    T2173_3E0 ctl510;       // 0x510: D_002173E0
    T2173_3F8 ctl520;       // 0x520: D_002173F8
};

typedef char check_C6D[sizeof(C6D) == 0x590 ? 1 : -1];

void func_00143648(C6D* self);   // slot 0

#endif
