// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 539/640 (84.2%), checked 2026-11-07
#include "common.h"
#include "sound_record.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"
#include "buffered_stream.h"
#include "object_event.h"
#include "key_record.h"
#include "key_id.h"
#include "base_object.h"
#include "fpu.h"
#include "asm_func.h"
#include "point_object.h"
#include "id_linked_object.h"
#include "game_progress.h"
#include "shapes.h"
#include "property_descriptor.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-c): the VU0 part (the face's two edges, their cross product and
// its dot with the face normal) is retail's; the edge-to-triangle loops differ in registers
// (retail keeps the edge index in a0 and the edge in a6, here a3 and t3), one bnez that is a
// bnezl here, and the operand order of tri + count. Tried: counts[f] read in place of a pointer
// to it (closer), the triangle as pointer arithmetic.

// The triangles a collider's hook keeps (Collider::hook, 0xC bytes): two vectors per vertex and
// three vertex indices per face, wound to face along the face's normal (func_001BBC38).
struct MeshHook {
    Vec02* f0;              // 0x00
    Vec02* f4;              // 0x04
    s32* tris;              // 0x08
};

// An edge of a collision mesh (0x10 bytes): its two vertices and the two faces it joins.
struct MeshEdge {
    s16 verts[2];           // 0x00
    s16 faces[2];           // 0x04
    u8 pad08[0x10 - 0x08];
};

// A face of a collision mesh as func_001BBC38 reads it: its normal first (0x20 bytes).
struct MeshFacePlane {
    Vec02 normal;           // 0x00
    u8 pad10[0x20 - 0x10];
};

void* AllocateZeroedBackMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);
void* AllocateFrontMemory(s32 size);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

void func_001BBC38(Collider* self)
{
    Vec02 e1;
    Vec02 e2;
    Vec02 n;
    if (self->hook != 0) {
        return;
    }
    PushBackMemoryMark();
    MeshHook* h = (MeshHook*)AllocateFrontMemory(0xC);
    self->hook = h;
    h->f0 = (Vec02*)AllocateZeroedFrontMemory(self->meshCopy.vertCount * 16);
    h->f4 = (Vec02*)AllocateZeroedFrontMemory(self->meshCopy.vertCount * 16);
    h->tris = (s32*)AllocateZeroedFrontMemory(self->meshCopy.faceCount * 12);
    s32* counts = (s32*)AllocateZeroedBackMemory(self->meshCopy.faceCount * 4);
    s32 i;
    for (i = 0; i < self->meshCopy.edgeCount; i++) {
        MeshEdge* e = &((MeshEdge*)self->meshCopy.edges)[i];
        for (s32 j = 0; j < 2; j++) {
            s32 f = e->faces[j];
            s32* tri = &h->tris[f * 3];
            for (s32 k = 0; k < 2; k++) {
                s32 v = e->verts[k];
                s32 m;
                for (m = 0; m < counts[f]; m++) {
                    if (v == tri[m]) {
                        break;
                    }
                }
                if (m >= counts[f] && m < 3) {
                    tri[counts[f]] = v;
                    counts[f]++;
                }
            }
        }
    }
    Vec02* verts = (Vec02*)self->mesh.verts;
    for (i = 0; i < self->meshCopy.faceCount; i++) {
        s32* t = &h->tris[i * 3];
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(verts[t[1]]), Vu0::Q(verts[t[0]]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(verts[t[2]]), Vu0::Q(verts[t[0]]));
        Vu0::Q(n) = Vu0::Cross(Vu0::Q(e1), Vu0::Q(e2));
        if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(n), Vu0::Q(((MeshFacePlane*)self->mesh.faces)[i].normal))) < 0.0f) {
            s32 b = t[1];
            t[1] = t[2];
            t[2] = b;
        }
    }
    PopBackMemoryMark();
}
