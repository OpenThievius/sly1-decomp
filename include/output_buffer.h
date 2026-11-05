// SPDX-License-Identifier: AGPL-3.0-or-later
// A buffered writer: func_001D7190(w, text, n) writes into it, func_001D72C8 flushes the
// 0x80-byte buffer at 0x18, and func_001D7148(w, flags) is its destructor (it flushes, and with
// flags & 1 frees it with func_0018D778). func_001E0CD0, func_001E1028, func_001E17A8,
// func_001E1A08 and func_001E1DB8 (file_1E08F8.cpp) write through it. Written for this project
// from what retail's code does (build/swarm/st3/groups.tsv, g3275).
#ifndef OUTPUT_BUFFER_H
#define OUTPUT_BUFFER_H

#include "common.h"

struct OutputBuffer {
    union {
        u8* target;         // 0x00: func_001D7190 (memory written to directly when set)
        s32 targetWord;     // 0x00: func_001D72C8 tests it
    };
    s32 capacity;           // 0x04: func_001D7190 (limit of target)
    s32 used;               // 0x08: func_001D7190 (bytes written into target)
    s32 handle;             // 0x0C: func_001D72C8 (negative: no output)
    s32 count;              // 0x10: func_001E1A08, func_001E1DB8
    s32 pending;            // 0x14: func_001D72C8, func_001D7190 (bytes buffered)
    u8 buf[0x80];           // 0x18: func_001D72C8
};

typedef char check_OutputBuffer[sizeof(OutputBuffer) == 0x98 ? 1 : -1];

#endif
