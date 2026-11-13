// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"
#include "collider.h"
#include "cone_volume.h"
#include "debug_scope.h"
#include "placed_object.h"
#include "shapes.h"

// Contacts between colliders: the friction and bounce of a pair of surface kinds, the pooled
// contact chains, the searches over a collider's edges, and class 0x03's contact method
// (func_00187F40) with the routines it runs, most of them VU0 assembly.

// A surface kind's weight and value; a pair's number is the sum of the values over the sum of
// the weights.
struct SurfaceWeight { f32 a; f32 b; };

SurfaceWeight g_surfaceFriction[13] = {
    {1.0f, 0.5f},
    {3.0f, 2.4f},
    {1.0f, 0.4f},
    {1.0f, 0.5f},
    {1.0f, 0.4f},
    {1.0f, 1.0f},
    {5.0f, 0.5f},
    {1.0f, 1.5f},
    {3.0f, 1.5f},
    {3.0f, 2.4f},
    {1.0f, 0.5f},
    {1.0f, -10.0f},
    {1.0f, -10.0f}
};
SurfaceWeight g_surfaceBounce[13] = {
    {1.0f, 0.5f},
    {5.0f, 1.0f},
    {1.0f, 0.8f},
    {1.0f, 0.4f},
    {1.0f, 0.6f},
    {1.0f, 0.9f},
    {1.0f, 0.1f},
    {1.0f, -1.0f},
    {1.0f, -1.0f},
    {1.0f, -1.0f},
    {1.0f, -1.0f},
    {1.0f, 0.5f},
    {1.0f, 1.0f}
};
void InitPoseSource(void* self);

// Two surface kinds, indexes into the weight tables.
struct SurfacePair { s32 a; s32 b; };

extern s32 g_buttonCodeFlags;

f32 GetSurfacePairFriction(SurfacePair* p)
{
    f32 num = g_surfaceFriction[p->a].b + g_surfaceFriction[p->b].b;
    f32 den = g_surfaceFriction[p->a].a + g_surfaceFriction[p->b].a;
    f32 r = num / den;
    if (r < 0.0f) r = 0.0f;
    if (g_buttonCodeFlags & 8) r = r * 0.2f;
    return r;
}



f32 GetSurfacePairBounce(SurfacePair* p)
{
    f32 one = 1.0f;
    f32 num = g_surfaceBounce[p->a].b + g_surfaceBounce[p->b].b;
    f32 den = g_surfaceBounce[p->a].a + g_surfaceBounce[p->b].a;
    f32 r = num / den;
    if (r < 0.0f) return 0.0f;
    if (one < r) r = one;
    return r;
}

// A pooled contact as func_00185D20 fills it: two ends of 0x40 bytes (the body and the part, a
// surface number, the point and its two transforms), the normal, then the numbers.
struct PooledEnd {
    Collider* body;         // 0x00
    Collider* part;         // 0x04
    s32 surface;            // 0x08
    u8 pad0C[4];
    Vec02 v10;              // 0x10
    Vec02 v20;              // 0x20
    Vec02 v30;              // 0x30
};
struct PooledContact {
    PooledEnd end[2];       // 0x00
    Vec02 v80;              // 0x80
    f32 f90;                // 0x90
    f32 f94;                // 0x94
    f32 f98;                // 0x98
    s32 kind;               // 0x9C
    s32 fA0;                // 0xA0
    s32 fA4;                // 0xA4
    u8 padA8[0xD0 - 0xA8];
    PooledContact* next;    // 0xD0
};

void* PopZeroedFreeSlot(void* pool);
void TransformPointBetweenFrames(void* frame, void* part, void* in, void* out);
Collider* FindHandlerForSlot(Collider* node, s32 offset);
void NotifyContactEnds(void* a0, s32 n, Contact03** list);

s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7)
{
    s32 surfaces[2];
    Vec02 k;
    PooledContact* c;
    s32 e;
    Collider* part;
    c = (PooledContact*)PopZeroedFreeSlot((u8*)((BaseObject*)a0)->world + 0x1AFC);
    c->f90 = f;
    c->v80 = *(Vec02*)a3;
    PooledEnd* end = c->end;
    for (e = 0; e < 2; e++) {
        part = (e != 0) ? (Collider*)a1 : (Collider*)a0;
        end->part = part;
        if (part != 0) {
            end->body = *(Collider**)((u8*)part + 0x50);
        } else {
            Vu0::Q(end->v30) = Vu0::Zero();
            end->body = 0;
        }
        end++;
    }
    c->end[0].v10 = *(Vec02*)a2;
    Vu0::Q(k) = Vu0::FromFloat(-f);
    *(Vu0::Vec*)&c->end[1].v10 = Vu0::MulAddX(Vu0::Vec::Of(*(Vec02*)a2), Vu0::Vec::Of(*(Vec02*)a3), Vu0::Vec::Of(k));
    c->kind = a4;
    for (e = 0; e < 2; e++) {
        PooledEnd* pe = &c->end[e];
        part = pe->part;
        if (part == 0) {
            pe->v20 = pe->v10;
            surfaces[e] = 0;
            pe->surface = 0;
        } else {
            TransformPointBetweenFrames(0, part, &pe->v10, &pe->v20);
            s32 surface = *(s8*)((u8*)part + 0x2C8);
            surfaces[e] = surface;
            pe->surface = surface;
        }
    }
    c->f94 = GetSurfacePairFriction((SurfacePair*)surfaces);
    c->f98 = GetSurfacePairBounce((SurfacePair*)surfaces);
    c->fA0 = a5;
    c->fA4 = a6;
    for (e = 0; e < 2; e++) {
        Collider* obj = FindHandlerForSlot(c->end[e].part, 0x100);
        if (obj != 0) {
            void (*fn)(Collider*, PooledContact*, s32) = (void (*)(Collider*, PooledContact*, s32))((s32*)obj->desc)[0x100 / 4];
            if (fn != 0) {
                fn(obj, c, e);
            }
        }
    }
    NotifyContactEnds(((BaseObject*)a0)->world, 1, (Contact03**)&c);
    c->next = *(PooledContact**)a7;
    *(PooledContact**)a7 = c;
    return (s32)c;
}

// Carries each contact's end points into the world: an end on a part takes the part's frame
// (TransformPointBetweenFrames), except for the kinds whose end lies on the part's sphere, where
// the point is the part's centre moved by its radius against the contact's normal (kinds 4 to 6
// at end 0, kinds 7 and 9 at end 1).
void RefreshContactEndPoints(void* unused, s32 n, Contact03** list)
{
    for (s32 i = 0; i < n; i++) {
        Contact03* c = list[i];
        for (s32 e = 0; e < 2; e++) {
            ContactEnd03* end = &c->end[e];
            Collider* part = end->part;
            if (part == 0) {
                continue;
            }
            if (e == 0) {
                switch (c->kind) {
                case 4:
                case 5:
                case 6: {
                    u128 centre = Vu0::Q(part->v140);
                    Vu0::Q(end->v10) = Vu0::MulAddX(centre, Vu0::Q(c->v80), Vu0::Scalar(-part->radius3CC));
                    break;
                }
                default:
                    TransformPointBetweenFrames(end->part, 0, &end->v20, &end->v10);
                    break;
                }
            } else if (c->kind == 7 || c->kind == 9) {
                u128 centre = Vu0::Q(part->v140);
                Vu0::Q(end->v10) = Vu0::MulAddX(centre, Vu0::Q(c->v80), Vu0::Scalar(-part->radius3CC));
            } else {
                TransformPointBetweenFrames(part, 0, &end->v20, &end->v10);
            }
        }
    }
}

void ComputeObjectMotionInFrame(void* a, s32 b, void* c, void* d, s32 e, s32 f, s32 g);
Collider* FindHandlerForSlot(Collider* node, s32 offset);

void NotifyContactEnds(void* a0, s32 n, Contact03** list)
{
    for (s32 i = 0; i < n; i++) {
        Contact03* c = list[i];
        s32 e;
        for (e = 0; e < 2; e++) {
            if (c->end[e].part != 0) {
                ComputeObjectMotionInFrame(c->end[e].part, 0, &c->end[e].v10, (u8*)&c->end[e] + 0x30, 0, 0, 0);
                ((void (*)(Collider*, Contact03*, s32))c->end[e].part->desc03()->m3B)(c->end[e].part, c, e);
            }
        }
        for (e = 0; e < 2; e++) {
            Collider* obj = FindHandlerForSlot(c->end[e].part, 0x104);
            if (obj != 0) {
                void (*fn)(Collider*, Contact03*, s32) = (void (*)(Collider*, Contact03*, s32))obj->desc03()->m3D;
                if (fn != 0) {
                    fn(obj, c, e);
                }
            }
        }
        Vu0::Q(*(Vec02*)((u8*)c + 0xB0)) = Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)&c->end[0] + 0x30)), Vu0::Q(*(Vec02*)((u8*)&c->end[1] + 0x30)));
    }
}

void PushFreeSlot(u8* a, void* b);

void FreePooledContactChain(u8* self, Contact03* head)
{
    if (head != 0) {
        Contact03* cur = head;
        do {
            Contact03* next = cur->next;
            PushFreeSlot(self + 0x1AFC, cur);
            cur = next;
        } while (cur != 0);
    }
}

void MeasurePointToLine(Vec02* p, Vec02* a, Vec02* b, f32* t, f32* dist)
{
    Vec02 e;
    Vec02 w;
    Vu0::Q(e) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    Vu0::Q(w) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a));
    f32 len2 = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(e), Vu0::Q(e)));
    u128 d;
    if (len2 < 0.0001f) {
        *t = 0.0f;
        d = Vu0::Dot(Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a)), Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a)));
    } else {
        *t = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(e), Vu0::Q(w))) / len2;
        u128 q = Vu0::MulXSum(Vu0::Q(*a), Vu0::Scalar(1.0f), Vu0::Q(e), Vu0::Scalar(len2));
        u128 r = Vu0::Sub(Vu0::Q(*p), q);
        d = Vu0::Dot(r, r);
    }
    *(u32*)dist = Vu0::ToBits(Vu0::Sqrt(d));
}

void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* t, f32* dist)
{
    Vec02 e;
    Vec02 d;
    Vu0::Q(e) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    f32 r = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(e), Vu0::Q(e)));
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a));
    u128 sum;
    if (r < 0.0001f) {
        *t = 0.0f;
        sum = Vu0::Dot(Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a)), Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a)));
    } else {
        r = Vu0::ToFloat(Vu0::Dot(Vu0::Q(e), Vu0::Q(d))) / r;
        if (r < 0.0f) {
            *t = 0.0f;
        } else if (1.0f < r) {
            *t = 1.0f;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*b));
        } else {
            *t = r;
            Vu0::Q(e) = Vu0::MulAddX(Vu0::Q(*a), Vu0::Q(e), Vu0::Scalar(r));
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(e));
        }
        sum = Vu0::Dot(Vu0::Q(d), Vu0::Q(d));
    }
    *(u32*)dist = Vu0::ToBits(Vu0::Sqrt(sum));
}

extern s32 g_vif0Channel;
extern u8 D_00211E10[];
void SyncDataCache(s32 unused);
void StartDmaChain(void* dma, void* addr);
s32 WaitDmaChannel(void* dma, s32 b, s32 c);

extern u8 g_vif1Channel[];
extern u8 D_00212110[];

void SyncDataCache(s32 a);
void StartDmaChain(void* a, void* b);
s32 WaitDmaChannel(void* a, s32 b, s32 c);

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
    u8 pad1E[2];
};

// A 0x70-byte hit func_0013DFD8 fills (CollectEdgeContacts, func_00187C28) and GroupEdgesByKey
// sorts: four quads, two floats, two words, the edge it came from and a link.
struct MeshHit {
    Vec02 r0;               // 0x00
    Vec02 r1;               // 0x10
    Vec02 r2;               // 0x20
    Vec02 r3;               // 0x30
    f32 f40;                // 0x40
    f32 f44;                // 0x44
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

typedef char check_MeshHit[sizeof(MeshHit) == 0x70 ? 1 : -1];

s32 CollectTreeNodeSpans(void* a, u8* b, u8* c, s32 d, s32 e, MeshHit* f);

s32 CollectEdgeContacts(s32 unused, Collider* self, u8* ctx, s32 cap, MeshHit* out)
{
    s32 i = self->meshCopy.edgeCount;
    i--;
    s32 total = 0;
    s32 filled = 0;
    MeshEdge* table = (MeshEdge*)self->meshCopy.edges;
    u8* base = (u8*)self->meshCopy.verts;

    while (i >= 0) {
        MeshEdge* e = &table[i];
        total += CollectTreeNodeSpans(ctx, base + e->x * 16, base + e->y * 16, 0, cap - total, &out[total]);
        if (filled < total) {
            for (; filled < total; filled++)
                out[filled].edge = e;
        }
        i--;
    }
    return total;
}

// A face a sweep may hit, in the list func_00186568 is given (12 bytes each).
struct FaceRef {
    MeshFace* face;         // 0x00
    u8 pad04[0x0C - 4];
};

// Collects the hits of the collider's tree on the edges of the listed faces: marks each listed
// face whose bounding sphere (the mesh's point and radius word for the face, grown by the
// collider's radius) reaches the collider's centre, then for each marked face not done yet runs
// CollectTreeNodeSpans on each edge whose far face is marked too, recording the edge in the
// hits it adds, and clears both marks at the end. Returns the number of hits.
s32 CollectMeshEdgeHitsFromFaces(Collider* self, Collider* other, s32 n, FaceRef* list, s32 cap, MeshHit* out)
{
    s32 i;
    MeshFace* f;
    s32 total = 0;
    s32 filled = 0;
    u8* verts = (u8*)other->meshCopy.verts;
    MeshFace* faces = (MeshFace*)other->meshCopy.faces;
    for (i = n; --i >= 0; ) {
        f = list[i].face;
        s32 k = f - faces;
        f32 reach = self->radius3CC + ((f32*)other->meshCopy.words)[k];
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(((Vec02*)other->meshCopy.points)[k]));
        if (!(reach * reach <= Vu0::ToFloatMoved(Vu0::Dot(d, d)))) {
            f->flags |= 1;
        }
    }
    for (i = n; --i >= 0; ) {
        f = list[i].face;
        if (f->flags & 1) {
            if (f->flags & 2) {
                continue;
            }
            f->flags |= 2;
            for (MeshEdge* e = f->edges; e != 0; e = e->next) {
                MeshFace* far = &faces[e->face[1]];
                if (!(far->flags & 1)) {
                    continue;
                }
                total += CollectTreeNodeSpans(self->tree.nodes, verts + e->x * 16, verts + e->y * 16, 0, cap - total, &out[total]);
                if (filled < total) {
                    for (; filled < total; filled++) {
                        out[filled].edge = e;
                    }
                }
            }
        }
    }
    for (i = n; --i >= 0; ) {
        f = list[i].face;
        f->flags &= 0xFFFC;
    }
    return total;
}

void* MoveMemory(void* dst, void* src, s32 size);

void GroupEdgesByKey(s32 count, MeshHit* base, s32* outCount, s32* keys, MeshHit** groups, MeshHit** head)
{
    MeshHit* single = 0;
    s32 n = 0;
    s32 i;
    s32 j;
    MeshHit* e;
    *head = 0;
    for (i = 0; i < count; i++) {
        e = &base[i];
        if (e->i50) {
            if (e->i54) {
                e->next = *head;
                *head = e;
                continue;
            }
        } else if (!e->i54) {
            e->next = single;
            single = e;
            continue;
        }
        if (!e->i54) {
            Vec02 t;
            t = e->r0;
            e->r0 = e->r1;
            e->r1 = t;
            t = e->r2;
            e->r2 = e->r3;
            e->r3 = t;
            s32 x = e->i50;
            s32 y = e->i54;
            f32 fa = e->f40;
            f32 fb = e->f44;
            e->i50 = y;
            e->i54 = x;
            e->f40 = fb;
            e->f44 = fa;
            e->slot5C = 1;
        }
        for (j = 0; j < n; j++) {
            if (e->edge->v[e->slot5C] == keys[j]) {
                break;
            }
        }
        if (j >= n) {
            keys[j] = e->edge->v[e->slot5C];
            n++;
        } else {
            e->next = groups[j];
        }
        groups[j] = e;
    }
    for (j = 0; j < n; j++) {
        if (groups[j]->next == 0) {
            e = single;
            while (e) {
                MeshEdge* r = e->edge;
                if (r->v[0] == keys[j] || r->v[1] == keys[j]) {
                    goto next;
                }
                e = e->next;
            }
            groups[j]->next = *head;
            *head = groups[j];
            s32 bytes = (n - j) * 4 - 4;
            MoveMemory(groups + j, groups + j + 1, bytes);
            MoveMemory(keys + j, keys + j + 1, bytes);
            j--;
            n--;
        }
    next:;
    }
    *outCount = n;
}

// FindGraphPath's graph: links (a pair of node ids at +4 of the record at 0x58, chained at
// 0x60), nodes of 0x20 bytes with a visited flag (4) at 0x1C, and the search's steps.
struct PathEdgeEnds { u8 pad0[4]; s16 k1; s16 k2; };
struct PathEdge { u8 pad0[0x58]; PathEdgeEnds* pair; u8 pad1[4]; PathEdge* next; };
struct PathVertex { u8 pad0[0x1C]; u16 flags; u8 pad1[2]; };
struct PathSearchStep { PathSearchStep* parent; PathEdge* node; s32 id; };

s32 FindGraphPath(PathVertex* base, s32 key, s32 target, PathEdge* head, PathEdge** out)
{
    PathSearchStep recs[64];
    s32 n;
    s32 nrec;
    s32 i;

    recs[0].parent = 0;
    recs[0].node = 0;
    recs[0].id = key;
    for (i = 0, nrec = 1; i < nrec; i++) {
        PathSearchStep* rc = &recs[i];
        PathEdge* g;
        for (g = head; g != 0; g = g->next) {
            PathEdgeEnds* p = g->pair;
            s32 id;
            if (p->k1 == rc->id) {
                id = p->k2;
            } else if (p->k2 == rc->id) {
                id = p->k1;
            } else {
                continue;
            }
            if (id == target) {
                out[0] = g;
                n = 1;
                while (rc->node != 0) {
                    out[n] = rc->node;
                    n++;
                    rc = rc->parent;
                }
                goto done;
            }
            PathVertex* it = &base[id];
            if ((it->flags & 4) == 0) {
                it->flags |= 4;
                PathSearchStep* r = &recs[nrec++];
                r->parent = rc;
                r->node = g;
                r->id = id;
            }
        }
    }
    n = 0;
done:
    for (i = 0; i < nrec; i++) {
        base[recs[i].id].flags &= ~4;
    }
    return n;
}

void FindSegmentClosestParams(Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* t, f32* depth, Vec02* normal);

// The dot product of two vectors as a float, the vectors passed as values (each a movti copy
// into the parameter, which the GCSE table's size counts: docs/TOOLCHAIN.md, "GCSE"). The
// Moved form leaves the qmfc2 to the compiler (Vu0::ToFloatMoved), as retail's last
// edge-against-face contact has it.
static inline f32 DotFloat(Vu0::Vec a, Vu0::Vec b)
{
    return Vu0::ToFloat(Vu0::Dot(a, b));
}

static inline f32 DotFloatMoved(Vu0::Vec a, Vu0::Vec b)
{
    return Vu0::ToFloatMoved(Vu0::Dot(a, b));
}

void CreateMeshPairContacts(Collider* self, Collider* other, void* a2, void* a3, u8* ctx, PooledContact** list)
{
    s32 counts[2];
    MeshHit hits[2][0x80];
    s32 groupCounts[2];
    s32 keys[2][64];
    MeshHit* groups[2][64];
    MeshHit* heads[2];
    Collider* objs[2];
    MeshHit* path[32];
    f32 params[2];
    Vec02 normal;
    Vec02 pts[2];
    Vec02* seg[4];
    f32 depth;
    s32 i;
    s32 j;
    MeshHit* e;

    counts[0] = CollectEdgeContacts((s32)other, self, ctx, 0x80, hits[0]);
    counts[1] = CollectMeshEdgeHitsFromFaces(self, other, (s32)a2, (FaceRef*)a3, 0x80, hits[1]);
    if (counts[0] == 0 && counts[1] == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        GroupEdgesByKey(counts[i], hits[i], &groupCounts[i], keys[i], groups[i], &heads[i]);
    }
    objs[0] = self;
    objs[1] = other;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < groupCounts[i]; j++) {
            MeshHit* g = groups[i][j];
            s32 key = keys[i][j];
            Vec02* verts = (Vec02*)objs[0]->meshCopy.verts;
            Vec02* kp = &verts[key];
            f32 best = -3.40282347e+38f;
            MeshFace* bestFace = 0;
            f32 bestDot;
            MeshHit* h;
            MeshHit* c;
            for (c = g; c != 0; c = c->next) {
                MeshFace* f = c->face54;
                if (f->flags & 8) {
                    continue;
                }
                f->flags |= 8;
                f32 d = DotFloat(Vu0::Vec::Of(*kp), Vu0::Vec::Of(f->normal));
                f32 m = d;
                for (h = g; h != 0; h = h->next) {
                    if (h->face54 == f) {
                        continue;
                    }
                    f32 d2 = DotFloat(Vu0::Vec::Of(verts[h->edge->v[1 - h->slot5C]]), Vu0::Vec::Of(f->normal));
                    if (d2 < m) {
                        m = d2;
                    }
                }
                m -= f->dist;
                if (best < m) {
                    bestFace = f;
                    best = m;
                    bestDot = d;
                }
            }
            for (c = g; c != 0; c = c->next) {
                c->face54->flags &= ~8;
            }
            CreatePooledContact(bestDot - bestFace->dist, objs[0], objs[1], kp, bestFace, 1,
                                (s32)&((Vec02*)objs[0]->meshCopy.verts)[key], (s32)bestFace, list);
            for (h = g; h != 0; h = h->next) {
                if (h->face54 == bestFace) {
                    continue;
                }
                f32 d = DotFloat(Vu0::Vec::Of(h->r1), Vu0::Vec::Of(bestFace->normal));
                if (d < bestDot) {
                    CreatePooledContact(d - bestFace->dist, objs[0], objs[1], &h->r1, bestFace, 2, (s32)h->edge,
                                        (s32)bestFace, list);
                }
            }
        }
        Collider* t = objs[0];
        objs[0] = objs[1];
        objs[1] = t;
    }
    for (e = heads[0]; e != 0; e = e->next) {
        if (e->face50 == 0) {
            continue;
        }
        if (e->face54 == 0) {
            continue;
        }
        MeshFace* faces = (MeshFace*)other->meshCopy.faces;
        s32 n = FindGraphPath((PathVertex*)faces, e->face50 - faces, e->face54 - faces, (PathEdge*)heads[1],
                              (PathEdge**)path);
        if (n > 0) {
            for (s32 k = 0; k < n; k++) {
                MeshHit* h = path[k];
                Vec02* va = (Vec02*)self->meshCopy.verts;
                Vec02* vb = (Vec02*)other->meshCopy.verts;
                seg[0] = &va[e->edge->v[0]];
                seg[1] = &va[e->edge->v[1]];
                seg[2] = &vb[h->edge->v[0]];
                seg[3] = &vb[h->edge->v[1]];
                FindSegmentClosestParams(seg[0], seg[1], seg[2], seg[3], params, &depth, &normal);
                // Each weight beside its end, in the order retail stores and loads them (s, a,
                // t, b: docs/TOOLCHAIN.md, "A weighted sum's operands in insn order").
                Vu0::Vec s0 = Vu0::Vec::Scalar(1.0f - params[0]);
                Vu0::Vec a0 = Vu0::Vec::Of(*seg[0]);
                Vu0::Vec t0 = Vu0::Vec::Scalar(params[0]);
                Vu0::Vec b0 = Vu0::Vec::Of(*seg[1]);
                *(Vu0::Vec*)&pts[0] = Vu0::MulXSum(a0, s0, b0, t0);
                Vu0::Vec s1 = Vu0::Vec::Scalar(1.0f - params[1]);
                Vu0::Vec a1 = Vu0::Vec::Of(*seg[2]);
                Vu0::Vec t1 = Vu0::Vec::Scalar(params[1]);
                Vu0::Vec b1 = Vu0::Vec::Of(*seg[3]);
                *(Vu0::Vec*)&pts[1] = Vu0::MulXSum(a1, s1, b1, t1);
                CreatePooledContact(-depth, self, other, pts, &normal, 3, (s32)e->edge, (s32)h->edge, list);
            }
        } else {
            MeshEdge* edge = e->edge;
            for (s32 k = 0; k < counts[1]; k++) {
                MeshHit* h = &hits[1][k];
                MeshFace* faces = (MeshFace*)self->meshCopy.faces;
                if (h->face50 == &faces[edge->face[0]] || h->face50 == &faces[edge->face[1]] ||
                    h->face54 == &faces[edge->face[0]] || h->face54 == &faces[edge->face[1]]) {
                    goto next;
                }
            }
            Vu0::Vec pos = Vu0::Vec::Of(self->v140);
            Vu0::Vec v0 = Vu0::Sub(pos, Vu0::Vec::Of(e->r0));
            Vu0::Vec v1 = Vu0::Sub(pos, Vu0::Vec::Of(e->r1));
            f32 d0 = DotFloat(v0, Vu0::Vec::Of(e->r2));
            f32 d1 = DotFloat(v1, Vu0::Vec::Of(e->r3));
            MeshFace* face;
            s32 end = e->slot5C;
            if (d1 < d0) {
                face = e->face50;
                end = 1 - end;
            } else {
                face = e->face54;
            }
            Vec02* p = &((Vec02*)self->meshCopy.verts)[edge->v[end]];
            PooledContact* c;
            for (c = *list; c != 0; c = c->next) {
                if (c->kind == 1 && c->fA0 == (s32)p && c->fA4 == (s32)face) {
                    break;
                }
            }
            if (c != 0) {
                continue;
            }
            CreatePooledContact(DotFloatMoved(Vu0::Vec::Of(*p), Vu0::Vec::Of(face->normal)) - face->dist, self, other,
                                p, face, 1, (s32)p, (s32)face, list);
        }
    next:;
    }
}

// A 0x30-byte hit CollectMeshHits gives: the contact point, the normal, the depth, a kind (6 a
// face, 5 an edge, 4 a vertex) and the part hit.
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

void PushBackMemoryMark();
void* AllocateBackMemory(s32 size);
void PopBackMemoryMark();
s32 QueryPlaneTreePoint(void* tree, Vec02* center, f32 radius, FaceRef** cursor);
s32 CollectTreeNodeSpans(void* a, Vec02* b, Vec02* c, s32 d, s32 e, MeshHit* f);

// The squared distance between two points.
static inline f32 DistanceSquared(const Vec02& a, const Vec02& b)
{
    Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(a), Vu0::Vec::Of(b));
    return Vu0::ToFloat(Vu0::Dot(d, d));
}

// Collects up to cap hits of a sphere (center, radius) on a mesh's faces, edges and vertices:
// marks each listed face whose bounding sphere and plane the sphere reaches (0x10), records a
// face hit where the tree's spans through the sphere along the normal find the face (0x80), then
// the edge hits of the marked faces not hit whole (0x20), keeping the vertex hits found on the
// way, and last the vertex hits no edge hit ends at. The list comes from func_0013E430 when no
// cursor is given. The marks are cleared on the way out.
s32 CollectMeshHits(Vec02* center, s32 count, FaceRef* list, FaceRef* cursor, Mesh03* mesh, s32 cap, MeshHitEntry* out,
                    f32 radius)
{
    VertexHit verts[64];
    s32 n;
    s32 nv;
    s32 i;
    s32 firstEdge;
    s32 lastEdge;
    MeshFace* face;
    MeshHitEntry* o;

    PushBackMemoryMark();
    nv = 0;
    n = 0;
    if (cap <= 0) {
        goto done;
    }
    if (cursor == 0) {
        FaceRef* buf = (FaceRef*)AllocateBackMemory(count * sizeof(FaceRef));
        cursor = buf;
        if (QueryPlaneTreePoint(list, center, radius, &cursor) != 2) {
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
        f32 r = radius + w[k];
        f32 dsq = DistanceSquared(*center, ((Vec02*)mesh->points)[k]);
        if (r * r <= dsq) {
            continue;
        }
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(*center), Vu0::Vec::Of(face->normal))) - face->dist;
        Vu0::Vec s = Vu0::Vec::Scalar(-d);
        Vu0::Vec p = Vu0::MulAddX(Vu0::Vec::Of(*center), Vu0::Vec::Of(face->normal), s);
        f32 e = Vu0::ToFloat(Vu0::Length(Vu0::Sub(p, Vu0::Vec::Of(((Vec02*)mesh->points)[k])))) - w[k];
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
        MeshHit spans[16];
        Vec02 pt;
        Vu0::Set(top, Vu0::MulAddX(Vu0::Q(*center), Vu0::Q(face->normal), Vu0::Scalar(radius)));
        Vu0::Set(bottom, Vu0::MulAddX(Vu0::Q(*center), Vu0::Q(face->normal), Vu0::Scalar(-radius)));
        s32 m = CollectTreeNodeSpans(cursor, &top, &bottom, 0, 0x10, spans);
        s32 k;
        for (k = 0; k < m; k++) {
            MeshHit* h = &spans[k];
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
        Vu0::Set(pt, Vu0::MulAddX(Vu0::Q(*center), Vu0::Q(face->normal), Vu0::Scalar(-radius)));
        if (n < cap) {
            o = &out[n++];
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
        for (MeshEdge* ed = face->edges; ed != 0; ed = ed->next) {
            MeshFace* of = &faces[ed->face[1]];
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
                vi = ed->v[1];
                Vu0::Set(rel, Vu0::Sub(Vu0::Vec::Of(*center), Vu0::Vec::Of(*b)).q);
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
                f32 depth = Fpu::Sqrt(dsq);
                Vu0::Vec s = Vu0::Vec::Scalar(1.0f / depth);
                Vu0::Set(nrm, Vu0::MulX(Vu0::Vec::Of(rel), s).q);
                Vu0::Set(p, Vu0::MulAddX(Vu0::Vec::Of(*center), Vu0::Vec::Of(nrm), Vu0::Vec::Scalar(-radius)).q);
                depth -= radius;
                if (vi >= 0) {
                    if ((u32)nv < 64) {
                        VertexHit* v = &verts[nv++];
                        v->index = vi;
                        v->point = p;
                        v->normal = nrm;
                        v->depth = depth;
                    }
                } else if (n < cap) {
                    o = &out[n++];
                    o->point = p;
                    o->normal = nrm;
                    o->depth = depth;
                    o->kind = 5;
                    o->part = ed;
                    if (n >= cap) {
                        goto clear;
                    }
                }
            }
        next:;
        }
    }
    lastEdge = n;
    for (s32 j = nv - 1; j >= 0; j--) {
        VertexHit* v = &verts[j];
        s32 vi = v->index;
        s32 q;
        for (q = firstEdge; q < lastEdge; q++) {
            o = &out[q];
            MeshEdge* ed = (MeshEdge*)o->part;
            if (ed->v[0] == vi || ed->v[1] == vi) {
                goto nextv;
            }
        }
        if (n < cap) {
            o = &out[n++];
            o->point = v->point;
            o->normal = v->normal;
            o->depth = v->depth;
            o->kind = 4;
            o->part = &((Vec02*)mesh->verts)[vi];
            if (n >= cap) {
                goto clear;
            }
        }
    nextv:;
    }
clear:
    for (i = count; --i >= 0;) {
        face = list[i].face;
        face->flags &= ~0xF0;
    }
done:
    PopBackMemoryMark();
    return n;
}

s32 CollectMeshHits(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, MeshHitEntry* a6);
s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

void AddMeshContacts(void* a0, f32 radius, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6)
{
    MeshHitEntry ents[64];
    s32 n = CollectMeshHits(a1, a3, a4, a5, (u8*)a2 + 0x3A4, 0x40, ents);
    for (s32 i = n - 1; i >= 0; i--) {
        MeshHitEntry* e = &ents[i];
        CreatePooledContact(e->depth, a0, a2, e, &e->normal, e->kind, 0, (s32)e->part, a6);
    }
}

void AddSphereSphereContact(Collider* self, Collider* other, void* a2)
{
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(other->v140));
    f32 rs = self->radius3CC;
    f32 dist2 = Vu0::ToFloatNow(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
    f32 sum = rs + other->radius3CC;
    if (dist2 < 0.0001f) {
        return;
    }
    if (sum * sum < dist2) {
        return;
    }
    f32 dist = Fpu::Sqrt(dist2);
    Vec02 point;
    Vec02 n;
    {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(1.0f / dist);
        Vu0::Q(n) = Vu0::MulX(Vu0::Q(d), Vu0::Q(k));
    }
    {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(-rs);
        Vu0::Q(point) = Vu0::MulAddX(Vu0::Q(self->v140), Vu0::Q(n), Vu0::Q(k));
    }
    CreatePooledContact(dist - sum, self, other, &point, &n, 7, 0, 0, a2);
}

void FindPartSupportPoint(void* a0, void* a1, void* a2, void* a3, f32 f)
{
    Collider* part = (Collider*)a0;
    Vec02* dir = (Vec02*)a1;
    Vec02* out = (Vec02*)a2;
    f32 best = Vu0::ToFloat(Vu0::Dot(Vu0::Q(part->v140), Vu0::Q(*dir)));
    if (part->meshCopy.vertCount > 0) {
        Vec02* verts = (Vec02*)part->meshCopy.verts;
        Vu0::Q(*out) = Vu0::Q(part->v140);
        s32 i = part->meshCopy.vertCount; i--; for (; i >= 0; i--) {
            u128 p = Vu0::Q(verts[i]);
            f32 d = Vu0::ToFloat(Vu0::Dot(p, Vu0::Q(*dir)));
            if (d < best) {
                Vu0::Q(*out) = p;
                best = d;
            }
        }
    } else {
        f32 r = part->radius3CC;
        Vec02 k;
        best -= r;
        Vu0::Q(k) = Vu0::FromFloat(-r);
        Vu0::Q(*out) = Vu0::MulAddX(Vu0::Q(part->v140), Vu0::Q(*dir), Vu0::Q(k));
    }
    best -= f;
    *(f32*)a3 = best;
}


s32 CollectTreeNodeSpans(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
void FindPartSupportPoint(void* a0, void* a1, void* a2, void* a3, f32 f);
s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, void* a6, void* a7);

s32 AddSweptPartMeshContact(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5)
{
    MeshHit recs[2];
    Vec4U v1;
    Vec4U v2;
    s32 count = CollectTreeNodeSpans(a4, (u8*)a0 + 0x370, (u8*)a0 + 0x140, 0, 2, recs);
    s32 idx = 0;
    if (count > 0) {
        idx = (recs[0].p50 == 0);
    }
    if (idx >= count) {
        return 0;
    }
    void* p = recs[idx].p50;
    FindPartSupportPoint(a0, p, &v1, &v2, *(f32*)((u8*)p + 0x10));
    CreatePooledContact(v2.x, a0, a1, &v1, p, 8, 0, p, a5);
    return 1;
}

// Where the segment from b to c first meets the sphere of radius r around a: the quadratic in t
// of |b + t(c - b) - a|^2 = r^2 (aa = e.e, b2 = 2 e.d, cc = d.d - r^2). The two differences are
// stored as locals before the products are taken, and the squared length of e before the cross
// term: local-alloc then ranks d's register ahead of the products' (docs/TOOLCHAIN.md,
// "Local allocation's ranking"). Its outputs are optional.
s32 IntersectSegmentWithSphere(Vec02* a, Vec02* b, Vec02* c, f32* tOut, Vec02* hitOut, Vec02* nOut, f32* dOut, f32 r)
{
    Vec02 e;
    Vec02 d;
    Vec02 p;
    Vec02 w;
    Vec02 n;
    u128 dv = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    u128 ev = Vu0::Sub(Vu0::Q(*c), Vu0::Q(*b));
    Vu0::Q(e) = ev;
    Vu0::Q(d) = dv;
    f32 dd = Vu0::ToFloatMoved(Vu0::Dot(dv, dv));
    f32 aa = Vu0::ToFloatMoved(Vu0::Dot(ev, ev));
    f32 bb = Vu0::ToFloatMoved(Vu0::Dot(ev, dv));
    f32 cc = dd - r * r;
    f32 b2 = 2.0f * bb;
    f32 disc = b2 * b2 - aa * (cc * 4.0f);
    if (disc < 0.0f) {
        return 0;
    }
    f32 t = (-b2 - Fpu::Sqrt(disc)) / (2.0f * aa);
    if (t < 0.0f || 1.0f < t) {
        return 0;
    }
    Vu0::Q(p) = Vu0::MulXSum(Vu0::Q(*c), Vu0::Scalar(t), Vu0::Q(*b), Vu0::Scalar(1.0f - t));
    Vu0::Q(w) = Vu0::Sub(Vu0::Q(p), Vu0::Q(*a));
    Vu0::Q(n) = Vu0::MulX(Vu0::Q(w), Vu0::Scalar(1.0f / r));
    if (tOut != 0) {
        *tOut = t;
    }
    if (hitOut != 0) {
        *hitOut = p;
    }
    if (nOut != 0) {
        *nOut = n;
    }
    if (dOut != 0) {
        *dOut = Vu0::ToFloat(Vu0::Dot(Vu0::Q(n), Vu0::Q(*a))) + r;
    }
    return 1;
}

// func_00187E88's locals: the support point, the sphere hit, its distance and the contact's.
struct SphereHitFrame { s32 a[4]; s32 b[4]; f32 fa; f32 fb; s32 pad[2]; };

s32 IntersectSegmentWithSphere(void* a0, void* a1, void* a2, s32 a3, void* a4, void* a5, void* a6, f32 f);
void FindPartSupportPoint(void* a0, void* a1, void* a2, void* a3, f32 f);
s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

s32 AddSweptPartSphereContact(void* a0, void* a1, void* a2)
{
    SphereHitFrame loc;
    if (IntersectSegmentWithSphere((u8*)a1 + 0x140, (u8*)a0 + 0x370, (u8*)a0 + 0x140, 0, &loc, loc.b, &loc.fa, *(f32*)((u8*)a1 + 0x3CC)) == 0) {
        return 0;
    }
    FindPartSupportPoint(a0, loc.b, loc.a, &loc.fb, loc.fa);
    CreatePooledContact(loc.fb, a0, a1, loc.a, loc.b, 9, 0, 0, a2);
    return 1;
}

// Class 0x03's contact method: each part of this collider against another body. The hit test is
// written in each arm of both sweeps: the two tails are separate blocks until jump2 merges them
// after sched2, so PRE shares no load of the flags across them and the bit-53 constant has four
// uses (docs/toolchain/gcse.md, "A test written in each arm").
void CollideColliderParts(Collider* self, Collider* other, s32 sweep, void* a3, void* a4, void* a5, void* a6)
{
    // Retail's frame has a slot at 0(sp) that nothing touches, under the sweep flag's spill at
    // 4(sp): a scope object of the debug build (include/debug_scope.h;
    // docs/toolchain/stack-slots.md, "A 4-byte slot nothing touches").
    DebugScope scope;
    for (Collider* p = (Collider*)self->parts.head; p != 0; p = (Collider*)p->link2E4.next) {
        u64 f = p->flags538;
        if (f & (1ULL << 43)) {
            continue;
        }
        if (!(f & (1ULL << 40)) && p->tree.nodes == 0) {
            continue;
        }
        u64 g = other->flags538;
        if (f & ((1ULL << 47) | (1ULL << 56))) {
            if (g & ((1ULL << 47) | (1ULL << 56))) {
                if (f & (1ULL << 56)) {
                    continue;
                }
                if (g & (1ULL << 56)) {
                    continue;
                }
            }
        }
        if (sweep != 0) {
            if (!(p->flags538 & (1ULL << 44))) {
                u128 d = Vu0::Sub(Vu0::Q(p->v370), Vu0::Q(p->v140));
                if (1.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
                    if (g & (1ULL << 40)) {
                        if (AddSweptPartSphereContact(p, other, a6) != 0) {
                            p->flags538 |= (1ULL << 53);
                            continue;
                        }
                    } else {
                        if (AddSweptPartMeshContact(p, other, a3, a4, a5, a6) != 0) {
                            p->flags538 |= (1ULL << 53);
                            continue;
                        }
                    }
                }
            }
            if (!(other->flags538 & (1ULL << 44))) {
                u128 d = Vu0::Sub(Vu0::Q(other->v370), Vu0::Q(other->v140));
                if (1.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
                    if (p->flags538 & (1ULL << 40)) {
                        if (AddSweptPartSphereContact(other, p, a6) != 0) {
                            other->flags538 |= (1ULL << 53);
                            continue;
                        }
                    } else {
                        if (AddSweptPartMeshContact(other, p, (void*)p->tree.count, (void*)p->tree.nodes, (void*)p->tree.nodes, a6) != 0) {
                            other->flags538 |= (1ULL << 53);
                            continue;
                        }
                    }
                }
            }
        }
        if (other->flags538 & (1ULL << 40)) {
            if (p->flags538 & (1ULL << 40)) {
                AddSphereSphereContact(p, other, a6);
            } else {
                AddMeshContacts(other, other->radius3CC, &other->v140, p, (void*)p->tree.count2, (void*)p->tree.nodes, 0, a6);
            }
        } else if (p->flags538 & (1ULL << 40)) {
            s32 v = p != self || p->radius3CC != p->radius3D4;
            AddMeshContacts(p, p->radius3CC, &p->v140, other, a3, v ? a5 : a4, v ? (void*)0 : a5, a6);
        } else {
            CreateMeshPairContacts(p, other, a3, a4, (u8*)a5, (PooledContact**)a6);
        }
    }
}

struct ColliderPair {
    Collider* a;
    Collider* b;
};

s32 QueryPlaneTreePoint(TreeNode03* node, void* p, f32 f, TreeNode03** out);
void PushBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);

// A mark on the back memory for as long as it is in scope. Retail's frame has its one-byte
// slot at 0x10, between the ordered pair and the two address-taken locals, and reads the result
// after PopBackMemoryMark (docs/TOOLCHAIN.md, "A scalar local's store and a call's argument
// registers").
struct BackMemoryScope {
    BackMemoryScope() { PushBackMemoryMark(); }
    ~BackMemoryScope() { PopBackMemoryMark(); }
};

s32 BuildObjectPairContacts(s32 unused, ColliderPair* pair, s32 arg)
{
    ColliderPair ord;
    TreeNode03* cur;
    s32 res;
    Collider* pa = pair->a;
    Collider* pb = pair->b;
    f32 da = pa->radius3D0;
    f32 db = pb->radius3D0;
    res = 0;
    if (da > db) {
        ord.a = pb;
        ord.b = pa;
    } else {
        ord.a = pa;
        ord.b = pb;
    }
    s32 most = 0;
    Collider* n;
    for (n = (Collider*)ord.b->parts.head; n; n = (Collider*)n->link2E4.next) {
        if (n->tree.count2 > most) {
            most = n->tree.count2;
        }
    }
    {
        BackMemoryScope mark;
        TreeNode03* buf = (TreeNode03*)AllocateBackMemory(most * 12);
        s32 idx;
        for (n = (Collider*)ord.b->parts.head; n; n = (Collider*)n->link2E4.next) {
            if (n->flags538 & 0x80000000000ULL) {
                continue;
            }
            if (n->flags538 & 0x10000000000ULL) {
                cur = 0;
            } else {
                TreeNode03* h = n->tree.nodes;
                if (h == 0) {
                    continue;
                }
                cur = buf;
                if (QueryPlaneTreePoint(h, &ord.a->v3E0, ord.a->radius3D4, &cur) != 2) {
                    continue;
                }
                idx = cur - buf;
                cur = cur - 1;
            }
            ord.a->desc03()->m39(ord.a, n, arg, idx, buf, cur, &res);
            if (ord.a->desc03()->m3A) {
                ord.a->desc03()->m3A(ord.a, n, idx, buf, cur, &res);
            }
        }
        for (n = (Collider*)ord.a->parts.head; n; n = (Collider*)n->link2E4.next) {
            if (n->flags538 & 0x80000000000ULL) {
                continue;
            }
            if (!(n->flags538 & 0x10000000000ULL) && n->tree.nodes == 0) {
                continue;
            }
            if (ord.b->desc03()->m3A) {
                ord.b->desc03()->m3A(ord.b, n, n->tree.count, n->tree.nodes, n->tree.nodes, &res);
            }
        }
    }
    return res;
}
