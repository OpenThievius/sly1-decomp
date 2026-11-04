// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x60-byte record func_00159CA0 and func_00159D00 (00158000.cpp) take as the first
// parameter (func_00152600 puts it in a list): an object at +0, three colours and six numbers.
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g1786). The
// views end at 0x60; no code shows the size.
#ifndef S159CA0_H
#define S159CA0_H

#include "shapes.h"

struct S159CA0 {
    void* obj;              // 0x00: an object (func_0019D6C0 calls its table)
    u8 pad04[0x3C - 0x04];
    Rgba4 c0;               // 0x3C: func_00159D00
    Rgba4 c1;               // 0x40
    Rgba4 c2;               // 0x44
    f32 f48;                // 0x48
    f32 f4C;                // 0x4C
    f32 f50;                // 0x50
    f32 f54;                // 0x54
    s32 m58;                // 0x58
    s32 m5C;                // 0x5C
};

#endif
