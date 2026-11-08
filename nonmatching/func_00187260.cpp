// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 890/1888 (47.1%), checked 2026-11-08
// NEAR (2026-11-08, night-large5): CollectMeshHits (func_00187260, 1888 bytes): frame, saved
// registers, the spilled count (written as `for (i = count; --i >= 0;)`, so count - 1 is not one
// shared pseudo), the near-face test, the face, edge and vertex passes and the clean-up follow
// retail. Left: in the face pass retail reloads pt from its stack slot after the stores into the
// hit (ours keeps it in a VU register, one instruction short, which shifts the rest); the
// MulAddX results take the Scalar's register in retail (ours the normal's); the prologue's moves
// are scheduled in another order.
#include "common.h"
#include "fpu.h"
#include "vu0.h"
#include "collider.h"

// An edge of a face's chain: its two vertex indices, the face on its other side and the next.
struct FaceEdge {
    s16 v[2];               // 0x00
    s16 face4;              // 0x04
    s16 other;              // 0x06
    FaceEdge* next;         // 0x08
};

struct MeshFace {
    Vec02 normal;           // 0x00
    f32 dist;               // 0x10
    FaceEdge* edges;        // 0x14
    u8 pad18[0x1C - 0x18];
    u16 flags;              // 0x1C
    u8 pad1E[2];
};

// A face the tree search found (func_0013E430).
struct FaceCandidate {
    MeshFace* face;
    u8 pad4[8];
};

struct MeshHitEntry {
    Vec02 point;            // 0x00
    Vec02 normal;           // 0x10
    f32 depth;              // 0x20
    s32 kind;               // 0x24
    void* part;             // 0x28
    u8 pad2C[4];
};

// A vertex contact kept until the edges are done.
struct VertexHit {
    s32 index;              // 0x00
    u8 pad4[0xC];
    Vec02 point;            // 0x10
    Vec02 normal;           // 0x20
    f32 depth;              // 0x30
    u8 pad34[0xC];
};

struct SpanHit {
    u8 pad0[0x40];
    f32 f40;                // 0x40
    f32 f44;                // 0x44
    u8 pad48[8];
    MeshFace* face50;       // 0x50
    MeshFace* face54;       // 0x54
    u8 pad58[0x70 - 0x58];
};

void PushBackMemoryMark();
void* AllocateBackMemory(s32 size);
void PopBackMemoryMark();
s32 func_0013E430(void* tree, Vec02* center, FaceCandidate** cursor, f32 radius);
s32 CollectTreeNodeSpans(void* a, Vec02* b, Vec02* c, s32 d, s32 e, SpanHit* f);

// The squared distance between two points.
static inline f32 DistanceSquared(const Vec02& a, const Vec02& b)
{
    Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(a), Vu0::Vec::Of(b));
    return Vu0::ToFloat(Vu0::Dot(d, d));
}

s32 func_00187260(Vec02* center, s32 count, FaceCandidate* list, FaceCandidate* cursor, Mesh03* mesh, s32 cap,
                  MeshHitEntry* out, f32 radius)
{
    VertexHit verts[64];
    s32 n = 0;
    s32 nv = 0;
    s32 i;
    s32 firstEdge;
    s32 lastEdge;
    MeshFace* face;

    PushBackMemoryMark();
    if (cap <= 0) {
        goto done;
    }
    if (cursor == 0) {
        FaceCandidate* buf = (FaceCandidate*)AllocateBackMemory(count * sizeof(FaceCandidate));
        cursor = buf;
        if (func_0013E430(list, center, &cursor, radius) != 2) {
            goto done;
        }
        list = buf;
        count = cursor - list;
        cursor--;
    }
    for (i = count; --i >= 0;) {
        face = list[i].face;
        s32 k = face - (MeshFace*)mesh->faces;
        f32* w = (f32*)mesh->words;
        Vec02* c = &((Vec02*)mesh->points)[k];
        f32 r = radius + w[k];
        f32 dsq = DistanceSquared(*center, *c);
        if (r * r <= dsq) {
            continue;
        }
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(*center), Vu0::Vec::Of(face->normal))) - face->dist;
        Vu0::Vec s = Vu0::Vec::Scalar(-d);
        Vu0::Vec p = Vu0::MulAddX(Vu0::Vec::Of(*center), Vu0::Vec::Of(face->normal), s);
        f32 e = Vu0::ToFloat(Vu0::Length(Vu0::Sub(p, Vu0::Vec::Of(*c)))) - w[k];
        e = e >? 0.0f;
        if (radius * radius < e * e + d * d) {
            continue;
        }
        face->flags |= 0x10;
    }
    for (i = count; --i >= 0;) {
        face = list[i].face;
        if (!(face->flags & 0x10)) {
            continue;
        }
        if (face->flags & 0x40) {
            continue;
        }
        face->flags |= 0x40;
        Vec02 top;
        Vec02 bottom;
        SpanHit spans[16];
        Vec02 pt;
        Vu0::Set(top, Vu0::MulAddX(Vu0::Vec::Of(*center), Vu0::Vec::Of(face->normal), Vu0::Vec::Scalar(radius)).q);
        Vu0::Set(bottom, Vu0::MulAddX(Vu0::Vec::Of(*center), Vu0::Vec::Of(face->normal), Vu0::Vec::Scalar(-radius)).q);
        s32 m = CollectTreeNodeSpans(cursor, &top, &bottom, 0, 0x10, spans);
        s32 k;
        for (k = 0; k < m; k++) {
            SpanHit* h = &spans[k];
            MeshFace* f;
            if (1.0f < h->f40 + h->f44) {
                f = h->face50;
            } else {
                f = h->face54;
            }
            if (f == face) {
                break;
            }
        }
        if (k >= m) {
            continue;
        }
        Vu0::Set(pt, Vu0::MulAddX(Vu0::Vec::Of(*center), Vu0::Vec::Of(face->normal), Vu0::Vec::Scalar(-radius)).q);
        if (n < cap) {
            MeshHitEntry* o = &out[n++];
            o->point = pt;
            o->normal = face->normal;
            o->depth = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(pt), Vu0::Vec::Of(face->normal))) - face->dist;
            o->kind = 6;
            o->part = face;
            if (n >= cap) {
                goto clear;
            }
        }
        face->flags |= 0x80;
    }
    firstEdge = n;
    for (i = count; --i >= 0;) {
        Vec02* vtx = (Vec02*)mesh->verts;
        MeshFace* faces = (MeshFace*)mesh->faces;
        face = list[i].face;
        if (!(face->flags & 0x10)) {
            continue;
        }
        if (face->flags & 0xA0) {
            continue;
        }
        face->flags |= 0x20;
        for (FaceEdge* ed = face->edges; ed != 0; ed = ed->next) {
            MeshFace* of = &faces[ed->other];
            if (!(of->flags & 0x10)) {
                continue;
            }
            if (of->flags & 0x80) {
                continue;
            }
            Vec02* a = &vtx[ed->v[0]];
            Vec02* b = &vtx[ed->v[1]];
            Vec02 dir;
            Vec02 rel;
            Vec02 nrm;
            Vec02 p;
            s32 vi;
            Vu0::Set(dir, Vu0::Sub(Vu0::Vec::Of(*b), Vu0::Vec::Of(*a)).q);
            f32 lsq = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(dir), Vu0::Vec::Of(dir)));
            Vu0::Set(rel, Vu0::Sub(Vu0::Vec::Of(*center), Vu0::Vec::Of(*a)).q);
            f32 t = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(rel), Vu0::Vec::Of(dir))) / lsq;
            if (t < 0.0001f) {
                vi = ed->v[0];
            } else if (0.9999f < t) {
                Vu0::Set(rel, Vu0::Sub(Vu0::Vec::Of(*center), Vu0::Vec::Of(*b)).q);
                vi = ed->v[1];
            } else {
                vi = -1;
                Vu0::Set(p, Vu0::MulAddX(Vu0::Vec::Of(*a), Vu0::Vec::Of(dir), Vu0::Vec::Scalar(t)).q);
                Vu0::Set(rel, Vu0::Sub(Vu0::Vec::Of(*center), Vu0::Vec::Of(p)).q);
            }
            f32 dsq = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(rel), Vu0::Vec::Of(rel)));
            if (radius * radius < dsq) {
                continue;
            }
            if (vi >= 0) {
                s32 j;
                for (j = nv - 1; j >= 0; j--) {
                    if (verts[j].index == vi) {
                        goto next;
                    }
                }
            }
            {
                f32 len = Fpu::Sqrt(dsq);
                f32 depth = len - radius;
                Vu0::Set(nrm, Vu0::MulX(Vu0::Vec::Of(rel), Vu0::Vec::Scalar(1.0f / len)).q);
                Vu0::Set(p, Vu0::MulAddX(Vu0::Vec::Of(*center), Vu0::Vec::Of(nrm), Vu0::Vec::Scalar(-radius)).q);
                if (vi < 0) {
                    if (n < cap) {
                        MeshHitEntry* o = &out[n++];
                        o->point = p;
                        o->normal = nrm;
                        o->depth = depth;
                        o->kind = 5;
                        o->part = ed;
                        if (n >= cap) {
                            goto clear;
                        }
                    }
                } else if ((u32)nv < 64) {
                    VertexHit* v = &verts[nv++];
                    v->index = vi;
                    v->point = p;
                    v->normal = nrm;
                    v->depth = depth;
                }
            }
        next:;
        }
    }
    lastEdge = n;
    for (i = nv - 1; i >= 0; i--) {
        VertexHit* v = &verts[i];
        s32 q;
        for (q = firstEdge; q < lastEdge; q++) {
            FaceEdge* ed = (FaceEdge*)out[q].part;
            if (ed->v[0] == v->index || ed->v[1] == v->index) {
                goto nextv;
            }
        }
        if (n < cap) {
            MeshHitEntry* o = &out[n++];
            o->point = v->point;
            o->normal = v->normal;
            o->depth = v->depth;
            o->kind = 4;
            o->part = &((Vec02*)mesh->verts)[v->index];
            if (n >= cap) {
                goto clear;
            }
        }
    nextv:;
    }
clear:
    for (i = count; --i >= 0;) {
        list[i].face->flags &= ~0xF0;
    }
done:
    PopBackMemoryMark();
    return n;
}
