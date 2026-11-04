// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8A (descriptor D_0021C448, 0x58 bytes), a direct child of 0x01: a graph of points,
// links and faces read from the level stream (func_001916D0). Written for this project from
// what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's 0x34 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef C8A_H
#define C8A_H

#include "c01.h"

struct Stream8A;  // the level stream the graph is read from (func_00137BE0 and friends)

struct Edge8A { f32 pad[2]; };

// A point (32 bytes): its position (func_00137E70) and the links that meet there.
struct Vert8A { u8 pad[0x10]; s32 n; Edge8A** list; u8 pad2[8]; };

// A face (32 bytes): a plane (func_00137E70, then a float) and two neighbours, each a face,
// a tagged link (bit 0 set) or none.
struct Face8A { u8 pad[0x10]; f32 f10; void* a; void* b; u8 pad2[8]; };

// The graph: the points, the links (12-byte records, two kinds), and the faces.
struct Mesh8A {
    s32 nVerts;             // 0x00
    Vert8A* verts;          // 0x04
    s32 nEdges;             // 0x08
    s32 nA;                 // 0x0C
    u8* edges;              // 0x10
    s32 nB;                 // 0x14
    u8* bs;                 // 0x18
    s32 nFaces;             // 0x1C
    Face8A* faces;          // 0x20
};

// 0x8A: the graph, right after the root's fields.
struct C8A : C01 {
    Mesh8A m;               // 0x34
};

typedef char check_C8A[sizeof(C8A) == 0x58 ? 1 : -1];
typedef char check_Mesh8A[sizeof(Mesh8A) == 0x24 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001916D0(C8A* self, Stream8A* stream);     // 0x8A slot 10

#endif
