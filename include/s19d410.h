// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x80-byte requests func_0019D410 (0019C000.cpp) queues in the table at D_005E4700 (.bss),
// 16-aligned; func_00159D00 fills one. Written for this project from what retail's code does
// (build/swarm/st3/groups.tsv, g1785).
#ifndef S19D410_H
#define S19D410_H

#include "shapes.h"

struct __attribute__((aligned(16))) S19D410 {
    union {
        void* fn;           // 0x00: func_00159D00
        u32 w0;             // 0x00: func_0019D410 (Entry_19D410 copies it as words)
    };
    f32 f04;                // 0x04: func_00159D00
    s32 mode;               // 0x08
    u8 pad0C[0x60 - 0x0C];
    Rgba4 col;              // 0x60: func_00159D00
    u8 pad64[0x80 - 0x64];
};

typedef char check_S19D410[sizeof(S19D410) == 0x80 ? 1 : -1];

extern S19D410 D_005E4700[];    // .bss

#endif
