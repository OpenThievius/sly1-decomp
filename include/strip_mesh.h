// SPDX-License-Identifier: AGPL-3.0-or-later
// The three records func_001694F8(mesh, strip, a, b, n, node) takes (00168000.cpp; func_00169608
// takes the node too), which func_00163ED8 and func_00164868 (file_15F678.cpp) pass it: a mesh,
// one of its strips and a node its hook gives. They are filled by their callers' data, so they
// are named by what they hold and where the code reads them. Written for this project from
// what retail's code does (build/swarm/st3/groups.tsv, g1864, g1865, g1868).
#ifndef STRIP_MESH_H
#define STRIP_MESH_H

#include "common.h"

struct MeshStrip;
struct MeshNode;

// The node, parameter 5: func_001694F8 tests flag 1, func_00169608 walks its links.
struct MeshNode {
    s32 flags;              // 0x00: func_001694F8, func_00163ED8, func_00164868
    u8 pad04[0x08 - 0x04];
    s32 index;              // 0x08: func_001694F8 (multiplies the strip's count)
    u8 pad0C[0x14 - 0x0C];
    void* links;            // 0x14: func_001694F8, func_00169608 (Link_1694F8: src, dst, next)
};

// A strip, parameter 1: the elements of the mesh's array at 0x1C.
struct MeshStrip {
    s32 count;              // 0x00: func_00163ED8, func_00164868; func_001694F8 (scale)
    s32 base;               // 0x04: func_001694F8
};

// The mesh, parameter 0.
struct StripMesh {
    u8 kind;                // 0x00: func_00163ED8, func_00164868
    u8 mode;                // 0x01
    u8 pad02[0x04 - 0x02];
    u8 color[4];            // 0x04
    u8 pad08[0x0C - 0x08];
    s32 flags;              // 0x0C: func_001694F8 tests 0x10000000
    u8 pad10[0x18 - 0x10];
    s32 nstrips;            // 0x18: func_00163ED8, func_00164868
    MeshStrip* strips;      // 0x1C
    u8 pad20[0x24 - 0x20];
    void* hook;             // 0x24: an object whose first slot gives the node (Hook_163ED8)
};


#endif
