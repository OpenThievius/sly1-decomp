// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x14-byte entries of the lists at World+0x1EC8 and World+0x1ECC: func_001DBBD8 takes one from
// the world's pool at +0x1B14 (func_001B5EC0; func_001DB4C8 makes the pool of 0x400 entries of
// 0x14 bytes) and clears its 0x14 bytes; func_001DBC60, func_001DBCC8, func_001DBD40,
// func_001DBE48 (001D8000.cpp) and func_0011AB58 (file_112698.cpp) walk them. Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g3296).
#ifndef S1DBBD8_H
#define S1DBBD8_H

#include "common.h"

struct S1DBBD8 {
    union {
        s32 k0;             // 0x00: func_001DBC60, func_001DBCC8, func_001DBD40
        void (*fn)(s32 a, s32 b, s32 c);    // 0x00: func_001DBE48 calls it with k1..k3; func_0011AB58 compares it
    };
    s32 k1;                 // 0x04
    s32 k2;                 // 0x08
    union {
        s32 k3;             // 0x0C
        void* p0C;          // 0x0C: func_0011AB58
    };
    S1DBBD8* next;          // 0x10
};

typedef char check_S1DBBD8[sizeof(S1DBBD8) == 0x14 ? 1 : -1];

#endif
