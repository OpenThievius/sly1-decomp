// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 392/388, checked 2026-11-07
// NEAR: identical but for how the dot product reaches memory. Retail stores qmfc2's GPR with one sw; Vu0::ToFloat returns an f32, so the compiler adds mtc1 and swc1 (a union read gives sw plus a move). A ToFloat that returns the word, for u32 and s32 destinations, would match; retail does the same in func_001536C8 and func_00153780.
#include "common.h"
#include "id_lookup_object.h"
#include "placed_object.h"
#include "world.h"
#include "animation.h"
#include "sound_record.h"
#include "asm_func.h"
#include "vu0.h"
#include "collider.h"
#include "list_iter.h"
#include "packet_writer.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "keyed_entry.h"
#include "identity_key.h"
#include "strip_mesh.h"
#include "vertex_batch.h"
#include "shapes.h"

// Stands in for the static objects of the file: the check names its compiler-made functions.
struct NmInit {
    NmInit();
};
NmInit::NmInit() {}
NmInit g_nmInit;



void TransformByMatrixWithW(void* m, f32 w, const void* src, void* out);
typedef void (*Fn_Table)();
typedef void (*AttachmentHandlerFn)(void* self);
typedef void (*AnimatorStepFn)(void* self, f32 f);
void* CopyToFrontMemory(s32 size, void* src);

struct NmMesh {
    f32 radius;
    s32 vertCount;
    void* verts;
    s32 faceCount;
    void* faces;
    s32 edgeCount;
    void* edges;
    void* points;           // 0x1C: faceCount 16-byte points
    void* words;            // 0x20: faceCount words
};
void* CopyToFrontMemory(s32 size, void* src);
void TransformByMatrixWithW(void* m, f32 w, const void* src, void* out);

void CopyMeshTransformed(NmMesh* src, s32 matrix, NmMesh* dst)
{
    dst->vertCount = src->vertCount;
    dst->verts = CopyToFrontMemory(src->vertCount << 4, src->verts);
    dst->faceCount = src->faceCount;
    dst->faces = CopyToFrontMemory(src->faceCount << 5, src->faces);
    dst->points = CopyToFrontMemory(src->faceCount << 4, src->points);
    dst->words = CopyToFrontMemory(src->faceCount << 2, src->words);
    dst->edgeCount = src->edgeCount;
    dst->edges = src->edges;
    if (matrix != 0) {
        for (s32 i = 0; i < dst->vertCount; i++) {
            Vec02* v = &((Vec02*)dst->verts)[i];
            TransformByMatrixWithW((void*)matrix, 1.0f, v, v);
        }
        for (s32 i = 0; i < dst->faceCount; i++) {
            u8* face = (u8*)dst->faces + (i << 5);
            TransformByMatrixWithW((void*)matrix, 0.0f, face, face);
            Vec02* vert = (Vec02*)((*(u16*)(face + 0x1E) << 4) + (s32)dst->verts);
            *(f32*)(face + 0x10) = Vu0::ToFloat(Vu0::Dot(Vu0::Q(*(Vec02*)face), Vu0::Q(*vert)));
            Vec02* p = &((Vec02*)dst->points)[i];
            TransformByMatrixWithW((void*)matrix, 1.0f, p, p);
        }
    }
}
