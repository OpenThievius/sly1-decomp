// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x8A (descriptor D_0021C448, 0x58 bytes), a direct child of 0x01: a graph of points,
// links and faces read from the level stream (func_001916D0). Written for this project from
// what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's 0x34 bytes and end at the descriptor's size; they are named for
// what the code does with them; step 6 of the roadmap may rename them.
#ifndef POINT_GRAPH_OBJECT_H
#define POINT_GRAPH_OBJECT_H

#include "base_object.h"
struct PointGraphObject;
struct Stream8A;


struct Stream8A;  // the level stream the graph is read from (func_00137BE0 and friends)

struct GraphLink { f32 pad[2]; };

// A point (32 bytes): its position (func_00137E70) and the links that meet there.
struct GraphPoint { u8 pad[0x10]; s32 linkCount; GraphLink** links; u8 pad2[8]; };

// A face (32 bytes): a plane (func_00137E70, then a float) and two neighbours, each a face,
// a tagged link (bit 0 set) or none.
struct GraphFace { u8 pad[0x10]; f32 f10; void* neighbourA; void* neighbourB; u8 pad2[8]; };

// A triangle (12 bytes, PointGraph::tris): its three corners (func_00191C78).
struct GraphTri { GraphPoint* corner[3]; };

// The graph: the points, the links (12-byte records, two kinds), and the faces.
struct PointGraph {
    s32 pointCount;         // 0x00
    GraphPoint* points;     // 0x04
    s32 linkCount;          // 0x08
    s32 nA;                 // 0x0C
    u8* links;              // 0x10
    s32 triCount;           // 0x14
    u8* tris;               // 0x18
    s32 faceCount;          // 0x1C
    GraphFace* faces;       // 0x20
};

// 0x8A: the graph, right after the root's fields.
struct PointGraphObject : BaseObject {
    PointGraph graph;       // 0x34
};

typedef char check_PointGraphObject[sizeof(PointGraphObject) == 0x58 ? 1 : -1];
typedef char check_PointGraph[sizeof(PointGraph) == 0x24 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void LoadPointGraph(PointGraphObject* o, Stream8A* in);     // 0x8A slot 10

#endif
