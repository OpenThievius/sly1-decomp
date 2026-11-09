// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1638/1712 (95.7%), checked 2026-11-08
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call 3 (source line 177); 39 differing lines before, 34 now.
// NEAR: retail's blocks: the weight switch shares its curve through a label after case 6 (one block in retail), an out-of-range mode stores the 1.0 still in $f0, the matrices are read as rows from the frame (Vu0::TransformRows), the inner loop's values are Vu0::Vec (big enough that loop.c leaves it as retail's); left: register choices only (the inverse's scalar store, the three lengths' qmfc2 GPRs, the pivot's loads, out[k] formed as k*4 + out where retail adds out first).
#include "transform_object.h"
#include "warp_page.h"
#include "oscillator.h"
#include "camera.h"
#include "game_clock.h"
#include "list_iter.h"
#include "screen_element.h"
#include "shapes.h"
#include "globals.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "pad_record.h"
#include "object_link.h"
#include "contact_tracker.h"
#include "lookup_object.h"
#include "object_sub_group.h"
#include "switched_collider.h"
#include "animation.h"
#include "object_gatherer.h"
#include "asm_func.h"
#include "vu0.h"
#include "hit_target.h"
#include "value_range.h"
#include "common.h"

// A part an oscillator moves (the list at +0x8E0, AttachNodeToOwner): the object, its mesh, how
// the vertices' weights are taken (f20: -1 all 1, 0 to 3 the distance from the part's frame with
// an axis left out, 4 to 6 one axis), the distances between which the weight goes from f30 to f28
// (f2C and f24), and the frame (m40).
struct OscPart {
    PlacedObject* obj;      // 0x00
    struct OscMesh* mesh;   // 0x04
    u8 pad08[0x20 - 0x08];
    s32 mode;               // 0x20
    f32 f24;                // 0x24
    f32 f28;                // 0x28
    f32 f2C;                // 0x2C
    f32 f30;                // 0x30
    u8 pad34[0x40 - 0x34];
    Vec02 m40[4];           // 0x40
    u8 pad80[0x84 - 0x80];
    OscPart* next;          // 0x84
};
// A block of a mesh's vertices: the range of the vertex data and its stride (u16s).
struct OscVertexRange { u16 start; u16 end; u8 pad04[0x10 - 0x04]; u16 stride; };
// The vertex data and, for each oscillator entry's output, a pointer to the four floats a vertex.
struct OscVertexData { Vec02* verts; u8 pad04[0x24 - 0x04]; f32* outs[1]; };
struct OscBlock { u8 pad00[0x1C]; OscVertexRange* range; OscVertexData* data; u8 pad24[0x50 - 0x24]; };
struct OscMesh { u8 pad00[0x58]; s32 blockCount; OscBlock* blocks; u8 pad60[0x68 - 0x60]; void* f68; };
// An oscillator entry as func_001F2840 reads it (0xD0 bytes from +0x50).
struct OscEntry { s32 mode; s32 out; u8 pad08[0x10 - 0x08]; Vec02 axis; u8 pad20[0x60 - 0x20]; s32 index; f32 rate; u8 pad68[0xD0 - 0x68]; };
struct Mat4R { Vec02 r[4]; };

static inline f32 MinA(f32 a, f32 b) { return a <? b; }
static inline f32 MinB(f32 a, f32 b) { return b <? a; }
static inline f32 MaxA(f32 a, f32 b) { return a >? b; }
static inline f32 MaxB(f32 a, f32 b) { return b >? a; }
void InitIdentityMatrix(void* self);
void* InvertMatrix4x4(void* a0, void* a1);
void MultiplyMatrices(void* out, void* b, void* in);
void CopyMemory(void* dst, void* src, s32 size);
void BuildMatrixFromRotationAndTranslation(Vec02* pos, Mat02* rot, void* out);
void ComputeSinCos(f32 angle, f32* a, f32* b);

void func_001F2840(Oscillator* self)
{
    for (OscPart* part = *(OscPart**)((u8*)self + 0x8E0); part != 0; part = part->next) {
        PlacedObject* obj = part->obj;
        OscMesh* mesh = part->mesh;
        Mat4R m;
        TimePolynomial poly;
        ValueRange range;
        u128 dir;
        if (part->mode == -1) {
            InitIdentityMatrix(&m);
            dir = Vu0::Q(D_00248D30);
        } else {
            m = *(Mat4R*)part->m40;
            range.lo = MinB(part->f28, part->f30);
            range.hi = MaxB(part->f28, part->f30);
            poly.y = (part->f28 - part->f30) / (part->f24 - part->f2C);
            poly.x = part->f28 - poly.y * part->f24;
            poly.z = 0.0f;
            switch (part->mode) {
            case 4:
                dir = Vu0::MulX(Vu0::Q(g_unitXVector), Vu0::Scalar((part->f24 + part->f2C) * 0.5f));
                break;
            case 5:
                dir = Vu0::MulX(Vu0::Q(g_unitYVector), Vu0::Scalar((part->f24 + part->f2C) * 0.5f));
                break;
            case 6:
                dir = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar((part->f24 + part->f2C) * 0.5f));
                break;
            default:
                dir = Vu0::Q(D_00248D30);
                break;
            }
            Mat4R inv;
            InvertMatrix4x4(&m, &inv);
            dir = Vu0::TransformRows(Vu0::Q(inv.r[0]), Vu0::Q(inv.r[1]), Vu0::Q(inv.r[2]), Vu0::Q(inv.r[3]), dir, 1.0f);
            if (mesh->f68 != 0) {
                Mat4R t;
                MultiplyMatrices(&t, part->m40, mesh->f68);
                m = t;
            }
        }
        for (s32 i = 0; i < mesh->blockCount; i++) {
            OscBlock* block = &mesh->blocks[i];
            OscVertexData* data = block->data;
            OscVertexRange* r = block->range;
            Vec02 verts[0x100];
            f32 weights[0x100];
            s32 n = (r->end - r->start) / r->stride;
            Vec02* end = verts + n;
            CopyMemory(verts, data->verts, n * sizeof(Vec02));
            Vec02* v;
            f32* w = weights;
            for (v = verts; v < end; v++, w++) {
                Vec02 p;
                f32 weight;
                f32 d;
                Vu0::Q(p) = Vu0::Transform(m, Vu0::Q(*v), 1.0f);
                switch (part->mode) {
                case -1:
                default:
                    *w = 1.0f;
                    break;
                case 1:
                    p.z = 0.0f;
                    d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(p)));
                    goto curve;
                case 2:
                    p.y = 0.0f;
                    d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(p)));
                    goto curve;
                case 3:
                    p.x = 0.0f;
                case 0:
                    d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(p)));
                    goto curve;
                case 4:
                    d = p.x;
                    goto curve;
                case 5:
                    d = p.y;
                    goto curve;
                case 6:
                    d = p.z;
                curve:
                    *w = range.Clamp(poly.Eval(d));
                    break;
                }
            }
            Mat4R mat;
            BuildMatrixFromRotationAndTranslation(&obj->v140, &obj->m110, &mat);
            if (mesh->f68 != 0) {
                Mat4R t;
                MultiplyMatrices(&t, &mat, mesh->f68);
                mat = t;
            }
            u128 pivot = Vu0::Add(Vu0::Q(obj->v140), Vu0::Rotate(obj->m110, dir));
            for (s32 j = 0; j < self->entryCount; j++) {
                OscEntry* ent = &((OscEntry*)((u8*)self + 0x50))[j];
                f32* out = data->outs[ent->out];
                w = weights;
                for (v = verts; v < end; v++, out += 4, w++) {
                    u128 q = Vu0::TransformRows(Vu0::Q(mat.r[0]), Vu0::Q(mat.r[1]), Vu0::Q(mat.r[2]), Vu0::Q(mat.r[3]), Vu0::Q(*v), 1.0f);
                    u128 qc = Vu0::Copy(q);
                    switch (ent->mode) {
                    case 0: {
                        f32 sn, cs;
                        s32 k;
                        Vu0::Vec qv; qv.q = qc;
                        f32 a = Vu0::ToFloatMoved(Vu0::Dot(qv, Vu0::Vec::Of(ent->axis))) * (ent->rate * 6.2831855f);
                        k = ent->index;
                        ComputeSinCos(a, &sn, &cs);
                        out[k++] = cs * *w;
                        out[k] = sn * *w;
                        break;
                    }
                    case 1: {
                        Vec02 d;
                        Vu0::Vec qv, pv; qv.q = q; pv.q = pivot;
                        Vu0::Q(d) = Vu0::Sub(qv, pv).q;
                        out[0] = *w * d.x;
                        out[1] = *w * d.y;
                        out[2] = *w * d.z;
                        out[3] = 1.0f;
                        break;
                    }
                    }
                }
            }
        }
    }
    *(s32*)((u8*)self + 0x8E4) = 0;
}
