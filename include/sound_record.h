// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x24-byte record at PlacedObject::f2AC (c02.h): func_0012ABA8 has func_001BE4D8 make it when the
// field is empty, class 0x02's slot 9 (func_00127048) copies it with func_0018D568(0x24, src),
// and func_00127378 (slot 13) and func_0015FBB8 (slot 20) read it. Written for this project from
// what retail's code does (build/swarm/st3/groups.tsv, g885). func_001BE4D8 makes it with its
// defaults.
#ifndef SOUND_RECORD_H
#define SOUND_RECORD_H

#include "common.h"
#include "shapes.h"   // U64P

struct SoundRecord {
    union {
        s32 f00;            // 0x00: func_00127378
        void* p00;          // 0x00: func_0015FBB8
    };
    f32 f04;                // 0x04: func_00127378, func_0015FBB8
    f32 f08;                // 0x08
    f32 f0C;                // 0x0C
    f32 f10;                // 0x10
    union {
        U64P b14;           // 0x14: an eight-byte pair, moved with ldl/ldr (func_0012AD30, func_0012AF00)
                            // and handed on as a block (func_001BFCD8)
        struct {
            f32 f14;        // 0x14: -1.0 at set-up (func_001BE4D8)
            s32 f18;        // 0x18
        };
    };
    union {
        s32 f1C;            // 0x1C: func_00127378
        void* p1C;          // 0x1C: func_0015FBB8
    };
    f32 f20;                // 0x20
};

typedef char check_SoundRecord[sizeof(SoundRecord) == 0x24 ? 1 : -1];

#endif
