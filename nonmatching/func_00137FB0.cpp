// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 648/708 (91.5%), checked 2026-11-07
// NEAR: every instruction is retail's but the delay slot of the call after the face offset:
//       retail leaves it empty (`sw v0, 16(s6)` before the call, then `nop`), ours fills it with
//       that sw, which also moves the loop's alignment nop. About 35 compiles (the offset stored
//       through a temporary, as s32, after the next read; the callee declared apart from its
//       definition).
#include "common.h"
#include "buffered_stream.h"
#include "collider.h"
#include "placed_object.h"
#include "vu0.h"

s32 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedU8(void* self);
f32 ReadBufferedFloat(void* self);
void ReadBufferedVector3(void* src, void* dst);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);

struct MeshEdge03 {
    u16 a;
    u16 b;
    s16 face;
    s16 other;
    MeshEdge03* next;
    MeshEdge03* link;
};

struct MeshFace03 {
    Vec02 normal;
    u32 offset;
    MeshEdge03* first;
    MeshEdge03* edges;
    u16 pad1C;
    u16 vert;
};

s32 ReadBufferedU8(void* self);
f32 ReadBufferedFloat(void* self);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 size);

void func_00137FB0(BufferedStream* in, Mesh03* mesh)
{
    s32 i = 0;
    mesh->radius = ReadBufferedFloat(in);
    s32 n = ReadBufferedU16(in);
    mesh->vertCount = n;
    mesh->verts = AllocateFrontMemory(n << 4);
    while (i < mesh->vertCount) {
        ReadBufferedVector3(in, (u8*)mesh->verts + (i << 4));
        i++;
    }
    s32 face = 0;
    s32 fc = ReadBufferedU16(in);
    mesh->faceCount = fc;
    mesh->faces = AllocateZeroedFrontMemory(fc << 5);
    mesh->points = AllocateFrontMemory(mesh->faceCount << 4);
    mesh->words = AllocateFrontMemory(mesh->faceCount << 2);
    s32 ec = ReadBufferedU16(in);
    mesh->edgeCount = ec;
    void* edges = AllocateZeroedFrontMemory(ec << 4);
    mesh->edges = edges;
    MeshEdge03* nextEdge = (MeshEdge03*)edges;
    while (face < mesh->faceCount) {
        MeshFace03* f = (MeshFace03*)((u8*)mesh->faces + (face << 5));
        s32 k = 0;
        s32 idx[3];
        idx[0] = ReadBufferedU16(in);
        idx[1] = ReadBufferedU16(in);
        idx[2] = ReadBufferedU16(in);
        Vec02 e1;
        Vec02 e2;
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(((Vec02*)mesh->verts)[idx[1]]), Vu0::Q(((Vec02*)mesh->verts)[idx[0]]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(((Vec02*)mesh->verts)[idx[2]]), Vu0::Q(((Vec02*)mesh->verts)[idx[0]]));
        u128 nrm = Vu0::Cross(Vu0::Q(e1), Vu0::Q(e2));
        u128 unit = Vu0::DivX(nrm, Vu0::Length(nrm));
        Vu0::Q(f->normal) = unit;
        f->vert = idx[0];
        f->offset = Vu0::ToBits(Vu0::Dot(unit, Vu0::Q(((Vec02*)mesh->verts)[f->vert])));
        ((f32*)mesh->words)[face] = ReadBufferedFloat(in);
        ReadBufferedVector3(in, (u8*)mesh->points + (face << 4));
        s32 cnt = ReadBufferedU8(in);
        while (k < cnt) {
            MeshEdge03* e = nextEdge;
            nextEdge = e + 1;
            e->a = ReadBufferedU16(in);
            e->b = ReadBufferedU16(in);
            e->face = face;
            e->other = ReadBufferedU16(in);
            if (k == 0) {
                f->first = e;
            } else {
                e[-1].next = e;
            }
            MeshFace03* g = (MeshFace03*)((u8*)mesh->faces + (e->other << 5));
            k++;
            e->link = g->edges;
            g->edges = e;
        }
        face++;
    }
}
