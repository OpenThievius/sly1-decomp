// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x90 (descriptor D_0021EF08, 0x48 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Fields follow the parent's
// 0x34 bytes; pads keep each at its retail offset.
#ifndef C90_H
#define C90_H

#include "c01.h"

// A 16-byte entry of the buffer at 0x38 (func_001ED4C8 adds one).
struct Entry90 {
    s32 f0;                 // 0x00
    s32 f4;                 // 0x04: a time, against the found object's +0xC70 (func_001ED278)
    f32 f8;                 // 0x08
    s32 fC;                 // 0x0C
};

// 0x90: func_001ED168 allocates its 0xC00-byte buffer, func_001ED198 looks something up in
// the level (+0x14) and keeps the result.
struct C90 : C01 {
    s32 f34;                // 0x34
    void* buffer;           // 0x38: f34 Entry90 records (0xC00 bytes, func_001ED168)
    s32 index;              // 0x3C: the entry func_001ED278 is at
    s32 found;              // 0x40
    s32 f44;                // 0x44: added to an entry's f4 (func_001ED278)

    Entry90* Cur() { return &((Entry90*)buffer)[index]; }
};

typedef char check_C90[sizeof(C90) == 0x48 ? 1 : -1];

void func_001ED168(C90* self);   // slot 0
void func_001ED198(C90* self);   // slot 16

#endif
