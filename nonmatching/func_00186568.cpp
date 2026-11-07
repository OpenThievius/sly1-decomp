// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 439/608 (72.2%), checked 2026-11-07
#include "common.h"
#include "collider.h"
#include "placed_object.h"
#include "vu0.h"
struct MeshHit { u8 pad0[0x70]; };
s32 CollectTreeNodeSpans(void* a, u8* b, u8* c, s32 d, s32 e, MeshHit* f);
// NEAR (2026-11-07, worker vu0-e6): the code is retail's but the allocator: retail spills the
// face count n (sw a2, 0(sp)) and runs the first loop in a2 itself, reloading n for the second
// and third loop; here the value n - 1 is common to the three loops and is the spilled one, so
// the counters take t0 and the stack slots swap (62 lines differ, the instructions are the
// same). Tried: separate counters per loop, `--i >= 0`, the count copied to a local.

// A face of a collision mesh (Mesh03::faces, 0x20 bytes each): the list of edges that bound it
// at +0x14 and two flag bits at +0x1C (0x1: the face may be hit, 0x2: its edges are collected).
struct FaceEdgeLink {
    s16 v0;                 // 0x00: a vertex index
    s16 v1;                 // 0x02: the other
    s16 pad04;
    s16 face;               // 0x06: the face on the far side
    FaceEdgeLink* next;     // 0x08
};
struct MeshFace {
    u8 pad00[0x14];
    FaceEdgeLink* edges;    // 0x14
    u8 pad18[4];
    u16 flags;              // 0x1C
    u8 pad1E[2];
};
struct FaceRef {
    MeshFace* face;
    s32 pad[2];
};

s32 func_00186568(Collider* self, Collider* other, s32 n, FaceRef* list, s32 cap, MeshHit* out)
{
    s32 i;
    s32 total = 0;
    s32 filled = 0;
    u8* verts = (u8*)other->meshCopy.verts;
    MeshFace* faces = (MeshFace*)other->meshCopy.faces;
    for (i = n - 1; i >= 0; i--) {
        MeshFace* f = list[i].face;
        s32 k = f - faces;
        f32 reach = self->radius3CC + ((f32*)*(void**)((u8*)other + 0x3C4))[k];
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(((Vec02*)*(void**)((u8*)other + 0x3C0))[k]));
        if (!(reach * reach <= Vu0::ToFloat(Vu0::Dot(d, d)))) {
            f->flags |= 1;
        }
    }
    for (i = n - 1; i >= 0; i--) {
        MeshFace* f = list[i].face;
        if (!(f->flags & 1)) {
            continue;
        }
        if (f->flags & 2) {
            continue;
        }
        f->flags |= 2;
        for (FaceEdgeLink* link = f->edges; link != 0; link = link->next) {
            if (!(faces[link->face].flags & 1)) {
                continue;
            }
            total += CollectTreeNodeSpans(self->tree.nodes, verts + link->v0 * 16, verts + link->v1 * 16, 0, cap - total, &out[total]);
            if (filled < total) {
                for (; filled < total; filled++) {
                    *(FaceEdgeLink**)((u8*)&out[filled] + 0x58) = link;
                }
            }
        }
    }
    for (i = n - 1; i >= 0; i--) {
        list[i].face->flags &= 0xFFFC;
    }
    return total;
}
