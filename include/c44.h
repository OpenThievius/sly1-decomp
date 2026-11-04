// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x44 (descriptor D_0021D978, 0x570 bytes), a direct child of class 0x03: a state
// (0x550) with a sound (0x560). Written for this project from what retail's code does
// (config/us/classes.tsv); one struct, named by class id until the naming step. Its descriptor
// has class 0x03's slots (desc03()).
#ifndef C44_H
#define C44_H

#include "c03.h"

// Eight bytes slot 9 keeps across the copy, read as one unaligned doubleword.
struct __attribute__((packed)) Pk8_44 {
    u64 v;
};

struct C44 : C03 {
    s32 state;              // 0x550: -1 at set-up (func_001A7520)
    f32 f554;               // 0x554: the time of the last state change (func_001A76A0)
    u8 pad558[0x55C - 0x558];
    void* f55C;             // 0x55C: the sound's id (slot 16 starts it)
    void* f560;             // 0x560: the sound's handle (func_001B6290)
    C01* f564;              // 0x564: the first child of kind 0x7E (slot 16)
    Pk8_44 f568;            // 0x568: kept across slot 9 (func_001A7588)
};

typedef char check_C44[sizeof(C44) == 0x570 ? 1 : -1];

#endif
