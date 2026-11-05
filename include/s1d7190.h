// SPDX-License-Identifier: AGPL-3.0-or-later
// A buffered writer: func_001D7190(w, text, n) writes into it, func_001D72C8 flushes the
// 0x80-byte buffer at 0x18, and func_001D7148(w, flags) is its destructor (it flushes, and with
// flags & 1 frees it with func_0018D778). func_001E0CD0, func_001E1028, func_001E17A8,
// func_001E1A08 and func_001E1DB8 (file_1E08F8.cpp) write through it. Written for this project
// from what retail's code does (build/swarm/st3/groups.tsv, g3275).
#ifndef S1D7190_H
#define S1D7190_H

#include "common.h"

struct S1D7190 {
    union {
        u8* f0;             // 0x00: func_001D7190
        s32 i0;             // 0x00: func_001D72C8 tests it
    };
    s32 f4;                 // 0x04
    s32 f8;                 // 0x08
    s32 fC;                 // 0x0C: func_001D72C8 (negative: no output)
    s32 count;              // 0x10: func_001E1A08, func_001E1DB8
    s32 f14;                // 0x14: func_001D72C8 (what is buffered)
    u8 buf[0x80];           // 0x18: func_001D72C8
};

typedef char check_S1D7190[sizeof(S1D7190) == 0x98 ? 1 : -1];

#endif
