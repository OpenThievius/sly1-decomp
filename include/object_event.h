// SPDX-License-Identifier: AGPL-3.0-or-later
// What an event carries to class 0x03's slot func_001BC320 (c03.h) and its overrides
// (func_001417F0, func_0017B7A8, func_00199C78, func_001A6DE0, func_001A72B0; func_001925F0 passes
// one on): a type, a radius, two words of flags and two vectors, built by the senders. Written for this project from what retail's code
// does (build/swarm/st3/groups.tsv, g1452).
#ifndef OBJECT_EVENT_H
#define OBJECT_EVENT_H

#include "common.h"
#include "placed_object.h"

struct ObjectEvent {
    void* source;           // 0x00: the object it came from; func_001417F0 compares it with the active switched collider
    s32 id;                 // 0x04: compared with the receiver's id word (func_0017B3A8)
    f32 radius;             // 0x08: func_001BC320
    s32 eventFlags;         // 0x0C: func_001BC320, func_0017B7A8, func_00199C78 (bits tested, 0x20 cleared once handled)
    s32 extraFlags;         // 0x10: func_001417F0, func_0017B7A8 (flags)
    u8 pad14[0x20 - 0x14];
    Vec02 pos;              // 0x20: where it happened: classes 0x42 and 0x43 play their hit sound there (func_001A6DE0, func_001A72B0)
    Vec02 v30;              // 0x30: passed on, raised, in their kind-6 message
};

#endif
