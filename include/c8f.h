// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8F (descriptor D_0021B608, 0x6C bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Fields follow the parent's
// 0x34 bytes; pads keep each at its retail offset.
#ifndef C8F_H
#define C8F_H

#include "c01.h"

// 0x8F: func_0017B998 (slot 0) allocates a 0xA00-byte buffer and sets a flag.
struct C8F : C01 {
    s32 f34;                // 0x34
    void* buffer;           // 0x38
    void* f3C;              // 0x3C
    s32 f40;                // 0x40
    s32 f44;                // 0x44
    s32 f48;                // 0x48
    s32 f4C;                // 0x4C
    void* f50;              // 0x50
    u8 pad54[0x68 - 0x54];
    s32 flag68;             // 0x68
};

typedef char check_C8F[sizeof(C8F) == 0x6C ? 1 : -1];

void func_0017B998(C8F* self);   // slot 0

#endif
