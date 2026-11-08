// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 0/0, checked 2026-11-08
// NEAR (2026-11-08, worker night-large2): the two kind switches (the end-1 one through
// jtbl_0024D280), the edge weight, the clamps and the blend are retail's; the face case's
// loop is not. Retail keeps &idx[i], &idx[i + 1] and &idx[(i + 2) % 3] in s1, s0, s3 and i * 4
// in s2, and moves each of the three weights in and stores its slot before the next (t vf2,
// -t vf5, 1.0 vf3; the vertices vf6, vf4, vf1); ours orders the registers s0, s3, s2, s1 and
// stores the 1.0's slot after the sum (vf4, the second vertex vf3). The spilled &end->v10 and
// &w (0x48, 0x4C) come out swapped, and the blend loop keeps the hook in a3 where retail has
// v1. Tried: u128 helpers, the weights as Vec values first (retail's spill order, the loop
// worse), Set for the sum, pointer locals for the vertices (they live across the call: worse).
// In the context of its file, src/main/file_1B7968.cpp.
#include "common.h"
#include "vu0.h"
#include "collider.h"

void TransformDirectionBetweenFrames(void* a, void* b, void* c, void* d);
void CopyMemory(void* dst, void* src, s32 count);
f32 ComputeSegmentParameter(const Vec02* a, const Vec02* b, const Vec02* p);

// What Collider::hook points at for a mesh that blends per-vertex vectors (func_001B8B90): a
// vector for each vertex, and the three vertex indices of each face.
struct VertexBlend03 {
    Vec02* vectors;         // 0x00: one per vertex of the mesh copy, none to skip
    u8 pad04[0x08 - 0x04];
    s32 (*faceVerts)[3];    // 0x08: one triple per face
};

void func_001B8B90(Collider* self, Contact03* c, s32 which)
{
    typedef Vu0::Vec Vec;
    if (self->hook == 0) {
        return;
    }
    s32 idx[3];
    f32 w[3];
    Vec02 sum;
    ContactEnd03* end = &c->end[which];
    s32 kind = 0;
    if (which == 0) {
        switch (c->kind) {
        case 1:
            kind = 1;
            idx[0] = (Vec02*)c->fA0 - (Vec02*)self->meshCopy.verts;
            break;
        case 2:
        case 3:
            kind = 2;
            idx[0] = ((s16*)c->fA0)[0];
            idx[1] = ((s16*)c->fA0)[1];
            break;
        }
    } else {
        switch (c->kind) {
        case 4:
            kind = 1;
            idx[0] = (Vec02*)c->fA4 - (Vec02*)self->meshCopy.verts;
            break;
        case 3:
        case 5:
            kind = 2;
            idx[0] = ((s16*)c->fA4)[0];
            idx[1] = ((s16*)c->fA4)[1];
            break;
        case 1:
        case 2:
        case 6:
        case 8:
            kind = 3;
            CopyMemory(idx, ((VertexBlend03*)self->hook)->faceVerts[(c->fA4 - (s32)self->meshCopy.faces) >> 5], 12);
            break;
        }
    }
    switch (kind) {
    case 0:
        return;
    case 1:
        w[0] = 1.0f;
        break;
    case 2: {
        Vec02* verts = (Vec02*)self->meshCopy.verts;
        f32 t = ComputeSegmentParameter(&verts[idx[0]], &verts[idx[1]], &end->v10);
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        f32 r;
        if (t < lo) {
            r = lo;
        } else if (hi < t) {
            r = hi;
        } else {
            r = t;
        }
        w[1] = r;
        w[0] = 1.0f - r;
        break;
    }
    case 3: {
        Vec02* verts = (Vec02*)self->meshCopy.verts;
        for (s32 i = 0; i < 2; i++) {
            f32 t = ComputeSegmentParameter(&verts[idx[i]], &verts[idx[i + 1]], &verts[idx[(i + 2) % 3]]);
            Vu0::Q(sum) = Vu0::MulXSum3(Vec::Of(verts[idx[i]]), Vec::Scalar(t), Vec::Of(verts[idx[i + 1]]),
                                        Vec::Scalar(-t), Vec::Of(verts[idx[(i + 2) % 3]]), Vec::Scalar(1.0f)).q;
            w[i] = ComputeSegmentParameter(&verts[idx[i]], &sum, &end->v10);
        }
        f32 a = w[0];
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        f32 r;
        if (a < lo) {
            r = lo;
        } else if (hi < a) {
            r = hi;
        } else {
            r = a;
        }
        w[0] = r;
        f32 b = w[1];
        f32 lo2 = 0.0f;
        f32 hi2 = 1.0f - r;
        f32 q;
        if (b < lo2) {
            q = lo2;
        } else if (hi2 < b) {
            q = hi2;
        } else {
            q = b;
        }
        w[1] = q;
        w[2] = 1.0f - w[0] - w[1];
        break;
    }
    }
    VertexBlend03* h = (VertexBlend03*)self->hook;
    if (h->vectors == 0) {
        return;
    }
    Vu0::Q(sum) = Vec::Zero().q;
    for (s32 j = 0; j < kind; j++) {
        Vu0::Q(sum) = Vu0::MulAddX(Vec::Of(sum), Vec::Of(h->vectors[idx[j]]), Vec::ScalarAt(w[j])).q;
    }
    TransformDirectionBetweenFrames(self, 0, &sum, &sum);
    Vu0::Q(end->v30) = Vu0::Add(Vec::Of(end->v30), Vec::Of(sum)).q;
}
