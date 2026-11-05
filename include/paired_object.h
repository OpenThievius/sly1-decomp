// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x42 (descriptor D_0021D718, 0x5C0 bytes), a direct child of class 0x03 with one state
// (0x550) and the objects of that state. Written for this project from what retail's code does
// (config/us/classes.tsv); one struct. Its descriptor
// has class 0x03's slots, so desc03() is the accessor.
#ifndef PAIRED_OBJECT_H
#define PAIRED_OBJECT_H

#include "c03.h"

struct PairedObject : C03 {
    s32 state;  // 0x550: -1 at set-up (func_001A6498); func_001A6BE0 sets it
    f32 stateTime;  // 0x554: the time of the last state change (func_001A6BE0)
    void* controller;  // 0x558: the object func_001A6BE0 hands to the state's functions
    void* partner;  // 0x55C: an object (func_001A6DE0 tells its slot 31 when it is hit)
    void* attachment;  // 0x560
    u8 pad564[0x574 - 0x564];
    f32 f574;  // 0x574
    u8 pad578[0x584 - 0x578];
    f32 f584;  // 0x584: 1.0 at set-up
    f32 f588;  // 0x588: 2.5 at set-up
    void* f58C;  // 0x58C: handles func_001A6BE0 starts by state (f58C..f5A4)
    void* f590;  // 0x590
    void* f594;  // 0x594
    void* f598;  // 0x598
    void* activeHandle;  // 0x59C: the one started last (stopped on the next change)
    void* f5A0;  // 0x5A0
    void* f5A4;  // 0x5A4
    void* soundHandle;  // 0x5A8: the sound (func_001B6290) started by states 7 and 8
    void* notifyRecord;  // 0x5AC: a record set up by slot 10 (func_00159478); its first word
                            //        is the object func_001A6DE0 sends a message to
    u8 blob5B0[8];  // 0x5B0: kept across slot 9 (func_001A6540)
    u8 pad5B8[0x5C0 - 0x5B8];
};

typedef char check_PairedObject[sizeof(PairedObject) == 0x5C0 ? 1 : -1];

#endif
