// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x88 (descriptor D_00219868, 0x54 bytes), a direct child of the root class 0x01 and
// no class under it: a graph of states (docs/DISC.md). Written for this project from what
// retail's code does (config/us/classes.tsv). Its own methods are func_001B5F50 (slot 10, not
// defined in C yet) and func_001B61A8 (slot 16).
#ifndef C88_H
#define C88_H

#include "c01.h"

struct C88 : C01 {
    s32 f34;                // 0x34
    void* f38;              // 0x38
    u8 pad3C[0x44 - 0x3C];
    s32 armed;              // 0x44: nonzero once the graph has something to run
    u8 pad48[0x54 - 0x48];
};

typedef char check_C88[sizeof(C88) == 0x54 ? 1 : -1];

void func_001B61A8(C88* self);                  // slot 16

#endif
