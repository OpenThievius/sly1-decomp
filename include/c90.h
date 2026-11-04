// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x90 (descriptor D_0021EF08, 0x48 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Fields follow the parent's
// 0x34 bytes; pads keep each at its retail offset.
#ifndef C90_H
#define C90_H

#include "c01.h"

// 0x90: func_001ED168 allocates its 0xC00-byte buffer, func_001ED198 looks something up in
// the level (+0x14) and keeps the result.
struct C90 : C01 {
    s32 f34;                // 0x34
    void* buffer;           // 0x38
    u8 pad3C[0x40 - 0x3C];
    s32 found;              // 0x40
    u8 pad44[0x48 - 0x44];
};

typedef char check_C90[sizeof(C90) == 0x48 ? 1 : -1];

void func_001ED168(C90* self);   // slot 0
void func_001ED198(C90* self);   // slot 16

#endif
