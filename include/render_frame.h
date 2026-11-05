// SPDX-License-Identifier: AGPL-3.0-or-later
// The two 0x48-byte records at D_00262320 (001E4000.cpp defines both as zeros) and the
// pointer D_002622D8 to the one in use: three lists and the words func_0015E810,
// func_0015E9F0, func_0015ED50, func_0015EE80 and func_0015EFE8 (0015C000.cpp) keep. Written
// for this project from what retail's code does (build/swarm/st3/groups.tsv, g1808).
//
// The size: D_00262320 runs 0x90 bytes to the next label, two records.
#ifndef G262320_H
#define G262320_H

#include "c01.h"

struct G262320 {
    u8 pad00[0x04];
    union {
        u8* f04;            // 0x04: 001E4000.cpp (Slot12_262320), func_0015E810
        s32 i04;            // 0x04: func_0015EE80
    };
    u8 pad08[0x0C - 0x08];
    union {
        u8* f0C;            // 0x0C: 001E4000.cpp, func_0015E810
        s32 i0C;            // 0x0C: func_0015EE80
    };
    union {
        u8* f10;            // 0x10: 001E4000.cpp, func_0015E810
        s32 i10;            // 0x10: func_0015ED50
    };
    u8 pad14[0x18 - 0x14];
    u32 flags;              // 0x18: func_0015E9F0
    s32 f1C;                // 0x1C: func_0015ED50
    List01 l20;             // 0x20: func_0015E810, func_0015EFE8
    List01 l2C;             // 0x2C
    List01 l38;             // 0x38
    s32 f44;                // 0x44: func_0015E9F0, func_0015ED50
};

typedef char check_G262320[sizeof(G262320) == 0x48 ? 1 : -1];

extern G262320 D_00262320[2];   // 001E4000.cpp
extern G262320* D_002622D8;     // 001E4000.cpp

#endif
