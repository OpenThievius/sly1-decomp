// SPDX-License-Identifier: AGPL-3.0-or-later
// The three records func_001694F8(mesh, strip, a, b, n, node) takes (00168000.cpp; func_00169608
// takes the node too), which func_00163ED8 and func_00164868 (file_15F678.cpp) pass it: a mesh,
// one of its strips and a node its hook gives. They are filled by their callers' data, so they
// are named by the function that takes them, with the parameter. Written for this project from
// what retail's code does (build/swarm/st3/groups.tsv, g1864, g1865, g1868).
#ifndef S1694F8_H
#define S1694F8_H

#include "common.h"

struct S1694F8_P1;
struct S1694F8_P5;

// The node, parameter 5: func_001694F8 tests flag 1, func_00169608 walks its links.
struct S1694F8_P5 {
    s32 flags;              // 0x00: func_001694F8, func_00163ED8, func_00164868
    u8 pad04[0x08 - 0x04];
    s32 idx;                // 0x08: func_001694F8
    u8 pad0C[0x14 - 0x0C];
    void* links;            // 0x14: func_001694F8, func_00169608 (Link_1694F8: src, dst, next)
};

// A strip, parameter 1: the elements of the mesh's array at 0x1C.
struct S1694F8_P1 {
    s32 count;              // 0x00: func_00163ED8, func_00164868; func_001694F8 (scale)
    s32 f4;                 // 0x04: func_001694F8 (base)
};

// The mesh, parameter 0.
struct S1694F8_P0 {
    u8 kind;                // 0x00: func_00163ED8, func_00164868
    u8 mode;                // 0x01
    u8 pad02[0x04 - 0x02];
    u8 color[4];            // 0x04
    u8 pad08[0x0C - 0x08];
    s32 f0C;                // 0x0C: func_001694F8
    u8 pad10[0x18 - 0x10];
    s32 nstrips;            // 0x18: func_00163ED8, func_00164868
    S1694F8_P1* strips;     // 0x1C
    u8 pad20[0x24 - 0x20];
    void* hook;             // 0x24: an object whose first slot gives the node (Hook_163ED8)
};


#endif
