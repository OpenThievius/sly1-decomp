// SPDX-License-Identifier: AGPL-3.0-or-later
// A collision mesh's edge, face and the hit its edges give (Mesh03::edges, Mesh03::faces), as
// the colliders, the ledge test and the range records read them.
#ifndef MESH_COLLISION_H
#define MESH_COLLISION_H

#include "common.h"
#include "placed_object.h"

// An edge of a collision mesh (Mesh03::edges): its two vertex indices first.
struct MeshEdge {
    union {
        struct {
            s16 x;          // 0x00
            s16 y;          // 0x02
        };
        s16 v[2];           // 0x00
    };
    s16 face[2];            // 0x04: the faces on either side (func_00186BA8)
    MeshEdge* next;         // 0x08: the next edge of a face's list (func_00186568)
    u8 pad0C[0x10 - 0xC];
};

// A face of a collision mesh (Mesh03::faces, 0x20 bytes): its plane, then flags (8 marks a face
// func_00186BA8 has tried).
struct MeshFace {
    Vec02 normal;           // 0x00
    f32 dist;               // 0x10
    MeshEdge* edges;        // 0x14: the edges that bound it, linked by next (func_00186568)
    u8 pad18[0x1C - 0x18];
    u16 flags;              // 0x1C: 1 the face may be hit, 2 its edges are collected (func_00186568)
    u16 ref;                // 0x1E: the point (of the mesh's points) the plane passes through
};

// A 0x70-byte hit func_0013DFD8 fills (CollectEdgeContacts, func_00187C28) and GroupEdgesByKey
// sorts: four quads, two floats, two words, the edge it came from and a link.
struct MeshHit {
    Vec02 r0;               // 0x00
    Vec02 r1;               // 0x10
    Vec02 r2;               // 0x20
    Vec02 r3;               // 0x30
    f32 entryTime;          // 0x40
    f32 exitTime;           // 0x44
    u8 pad48[0x50 - 0x48];
    union {
        s32 i50;            // 0x50
        void* p50;          // 0x50: the part hit (AddSweptPartMeshContact)
        MeshFace* face50;   // 0x50: the faces either side of the hit (func_00186BA8)
    };
    union {
        s32 i54;            // 0x54
        MeshFace* face54;
    };
    MeshEdge* edge;         // 0x58
    s32 slot5C;             // 0x5C: which end of the edge is the key (0 or 1)
    MeshHit* next;          // 0x60
};

#endif
