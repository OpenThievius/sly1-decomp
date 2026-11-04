// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x45 (descriptor D_0021DAA8, 0x570 bytes), a direct child of class 0x03: a state
// (0x550) with an object it creates (0x55C). Written for this project from what retail's code
// does (config/us/classes.tsv); one struct, named by class id until the naming step. Its
// descriptor has class 0x03's slots (desc03()).
#ifndef C45_H
#define C45_H

#include "c03.h"

struct C45 : C03 {
    s32 state;              // 0x550: -1 at set-up (func_001A7708)
    f32 f554;               // 0x554: the time of the last state change (func_001A7998)
    s32 f558;               // 0x558: whether slot 16 creates the object
    void* f55C;             // 0x55C: the object slot 16 creates (func_0015A838)
    void* f560;             // 0x560
    void* f564;             // 0x564: the handle func_001A7998 starts (func_0012C7B0)
    void* f568;             // 0x568: a record set up by slot 10 (func_00159478); its first word
                            //         is the object func_001A7998 sends a message to
    u8 pad56C[0x570 - 0x56C];
};

typedef char check_C45[sizeof(C45) == 0x570 ? 1 : -1];

#endif
