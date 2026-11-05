// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x1850-byte builder func_001C30E8 (file_1C29E8.cpp) keeps on its stack and hands to
// func_001619C0, func_00161A88, func_00161AB0, func_00161B10, func_00161BB0, func_00162508,
// func_00162680, func_001626A8, func_001626C0 and func_001626D8 (file_15F678.cpp). Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g4664). Only a few of its
// words are known; the frame gives the size, no code checks it.
#ifndef VERTEX_BATCH_H
#define VERTEX_BATCH_H

#include "shapes.h"

struct VertexBatch {
    u8 pad000[0x98];
    s32 f98;                // 0x98: func_001C30E8
    u8 pad09C[0xFC - 0x9C];
    f32 x;                  // 0xFC: func_00162680
    f32 y;                  // 0x100
    f32 z;                  // 0x104
    u8 pad108[0x118 - 0x108];
    U64P texCoord;          // 0x118: func_001626C0 (ldl/ldr; the pair of floats the caller copies in)
    u8 pad120[0x1850 - 0x120];
};

#endif
