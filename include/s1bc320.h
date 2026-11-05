// SPDX-License-Identifier: AGPL-3.0-or-later
// What an event carries to class 0x03's slot func_001BC320 (c03.h) and its overrides
// (func_001417F0, func_0017B7A8, func_00199C78; func_001925F0 passes one on): a type, a radius
// and two words of flags, built by the senders. Written for this project from what retail's code
// does (build/swarm/st3/groups.tsv, g1452).
#ifndef S1BC320_H
#define S1BC320_H

#include "common.h"

struct S1BC320 {
    s32 type;               // 0x00: func_001417F0
    u8 pad04[0x08 - 0x04];
    f32 radius;             // 0x08: func_001BC320
    s32 fC;                 // 0x0C: func_001BC320, func_0017B7A8, func_00199C78 (flags)
    s32 f10;                // 0x10: func_001417F0, func_0017B7A8 (flags)
};

#endif
