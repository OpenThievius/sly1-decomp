// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x80-byte requests func_0019D410 (group_marker.cpp) queues in the table at D_005E4700 (.bss),
// 16-aligned; func_00159D00 fills one. Written for this project from what retail's code does
// (build/swarm/st3/groups.tsv, g1785).
#ifndef DEFERRED_REQUEST_H
#define DEFERRED_REQUEST_H

#include "shapes.h"

// The five quadwords of transform BuildPlacedObjectTransform (func_00125B70) writes for a
// drawn object; func_001533A8 copies them into the part drawer's request.
struct DrawTransform {
    Quad16 q[5];            // 0x00
};

struct __attribute__((aligned(16))) DeferredRequest {
    union {
        void* callback;          // 0x00: func_00159D00
        u32 w0;             // 0x00: func_0019D410 (Entry_19D410 copies it as words)
    };
    f32 f04;                // 0x04: func_00159D00
    s32 group;             // 0x08
    u8 pad0C[0x10 - 0x0C];
    DrawTransform block;    // 0x10: the transform func_00153328 builds for func_001533A8
    union {
        Rgba4 col;          // 0x60: func_00159D00
        void* arg;          // 0x60: the object func_00153328 queues func_001533A8 for
    };
    u8 pad64[0x80 - 0x64];
};

typedef char check_DeferredRequest[sizeof(DeferredRequest) == 0x80 ? 1 : -1];

extern DeferredRequest g_deferredRequests[];    // .bss

#endif
