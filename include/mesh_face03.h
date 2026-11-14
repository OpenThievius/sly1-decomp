// SPDX-License-Identifier: AGPL-3.0-or-later
// A face of a collision mesh as the level stream's reader builds it (buffered_stream.cpp: each
// face's edges, linked by next and link) and as the mesh's plane offsets are written (game_progress.cpp).
#ifndef MESH_FACE03_H
#define MESH_FACE03_H

#include "common.h"
#include "placed_object.h"

struct MeshEdge03 {
    u16 a;
    u16 b;
    s16 face;
    s16 other;
    MeshEdge03* next;
    MeshEdge03* link;
};

struct MeshFace03 {
    Vec4 normal;
    u32 offset;
    MeshEdge03* first;
    MeshEdge03* edges;
    u16 pad1C;
    u16 vert;
};

#endif
