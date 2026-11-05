// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x45 (descriptor D_0021DAA8, 0x570 bytes), a direct child of class 0x03: a state
// (0x550) with an object it creates (0x55C). Written for this project from what retail's code
// does (config/us/classes.tsv); one struct. Its
// descriptor has class 0x03's slots (desc03()).
#ifndef OBJECT_CREATOR_H
#define OBJECT_CREATOR_H

#include "c03.h"

struct ObjectCreator : C03 {
    s32 state;  // 0x550: -1 at set-up (func_001A7708)
    f32 stateTime;  // 0x554: the time of the last state change (func_001A7998)
    s32 createsObject;  // 0x558: whether slot 16 creates the object
    void* created;  // 0x55C: the object slot 16 creates (func_0015A838)
    void* f560;  // 0x560
    void* activeHandle;  // 0x564: the handle func_001A7998 starts (func_0012C7B0)
    void* notifyRecord;  // 0x568: a record set up by slot 10 (func_00159478); its first word
                            //         is the object func_001A7998 sends a message to
    u8 pad56C[0x570 - 0x56C];
};

typedef char check_ObjectCreator[sizeof(ObjectCreator) == 0x570 ? 1 : -1];

#endif
