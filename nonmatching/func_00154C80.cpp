// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 561/604 (92.9%), checked 2026-11-08
// Tried night-close3, 2 compiles: the third loop with its own counter, all three counters declared in their loops: the same 22 differing words.
// NEAR: registers only: the same instructions, with the vertex counter in s0 where retail has s1 and the triangle record in s1 where retail has s2.
#include "common.h"
#include "globals.h"
#include "vu0.h"

void* ReadBufferedU16(void* other);
void* AllocateZeroedFrontMemory(s32 bytes);
void* AllocateFrontMemory(s32 n);
f32 ReadBufferedFloat(void* stream);
void ReadBufferedVector3(void* stream, Vec02* out);
struct MeshTriangle {
    s32 corner[3];          // 0x00
    f32 area;               // 0x0C
};
struct MeshData {
    s32 vertexCount;        // 0x00
    Vec02* vertices;        // 0x04
    s32 triangleCount;      // 0x08
    MeshTriangle* triangles;    // 0x0C
    Vec02* normals;         // 0x10
    f32 totalArea;          // 0x14
    u8 pad18[0x20 - 0x18];
    Vec02 extent;           // 0x20
};

void func_00154C80(void* p, void* other)
{
    MeshData* m = (MeshData*)p;
    s32 i;
    m->vertexCount = (s32)ReadBufferedU16(other);
    m->vertices = (Vec02*)AllocateFrontMemory(m->vertexCount << 4);
    m->normals = (Vec02*)AllocateZeroedFrontMemory(m->vertexCount << 4);
    for (i = 0; i < m->vertexCount; i++) {
        ReadBufferedVector3(other, &m->vertices[i]);
    }
    m->triangleCount = (s32)ReadBufferedU16(other);
    m->triangles = (MeshTriangle*)AllocateFrontMemory(m->triangleCount << 4);
    m->totalArea = 0.0f;
    for (s32 i = 0; i < m->triangleCount; i++) {
        MeshTriangle* t = &m->triangles[i];
        for (s32 j = 0; j < 3; j++) {
            t->corner[j] = (s32)ReadBufferedU16(other);
        }
        t->area = ReadBufferedFloat(other);
        m->totalArea = m->totalArea + t->area;
        u128 first = Vu0::Q(m->vertices[t->corner[0]]);
        u128 e1 = Vu0::Sub(Vu0::Q(m->vertices[t->corner[1]]), first);
        u128 e2 = Vu0::Sub(Vu0::Q(m->vertices[t->corner[2]]), first);
        u128 n = Vu0::Cross(e1, e2);
        for (s32 j = 0; j < 3; j++) {
            Vec02* v = &m->normals[t->corner[j]];
            Vu0::Q(*v) = Vu0::Add(Vu0::Q(*v), n);
        }
    }
    ReadBufferedVector3(other, &m->extent);
    for (i = 0; i < m->vertexCount; i++) {
        Vu0::Q(m->normals[i]) = Vu0::NormalizeOr(Vu0::Q(m->normals[i]), Vu0::Q(g_unitZVector));
    }
}
