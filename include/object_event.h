// SPDX-License-Identifier: AGPL-3.0-or-later
// What an event carries to class 0x03's slot func_001BC320 (c03.h) and its overrides
// (func_001417F0, func_0017B7A8, func_00199C78; func_001925F0 passes one on): a type, a radius
// and two words of flags, built by the senders. Written for this project from what retail's code
// does (build/swarm/st3/groups.tsv, g1452).
#ifndef OBJECT_EVENT_H
#define OBJECT_EVENT_H

#include "common.h"

struct ObjectEvent {
    s32 type;               // 0x00: func_001417F0
    s32 id;                 // 0x04: compared with the receiver's id word (func_0017B3A8)
    f32 radius;             // 0x08: func_001BC320
    s32 eventFlags;         // 0x0C: func_001BC320, func_0017B7A8, func_00199C78 (bits tested, 0x20 cleared once handled)
    s32 extraFlags;         // 0x10: func_001417F0, func_0017B7A8 (flags)
};

#endif
