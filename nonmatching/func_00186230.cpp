// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 244/240, checked 2026-11-07
// NEAR: StoreX stores the result as retail does (night-lever2). Still differs, scheduling only: retail puts the sqc2 of the edge vector after the c.lt.s (before the bc1f; ours before the mtc1) and the mfc1 of 1.0 after the div.s. Writing the store of the edge before the dot product or after it changes nothing.
// In the context of its file, src/main/collider_contact.cpp.
#include "common.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"
#include "collider.h"
#include "cone_volume.h"
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

INCLUDE_ASM(func_00185D20);

INCLUDE_ASM(func_00185F48);

void ComputeObjectMotionInFrame(void* a, s32 b, void* c, void* d, s32 e, s32 f, s32 g);
Collider* FindHandlerForSlot(Collider* node, s32 offset);

void func_001860A8(void* a0, s32 n, Contact03** list)
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
    u128 ev = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    f32 len2 = Vu0::ToFloat(Vu0::Dot(ev, ev));
    Vu0::Q(w) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a));
    Vu0::Q(e) = ev;
    u128 d;
    if (len2 < 0.0001f) {
        *t = 0.0f;
        d = Vu0::Dot(Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a)), Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a)));
    } else {
        *t = Vu0::ToFloat(Vu0::Dot(Vu0::Q(e), Vu0::Q(w))) / len2;
        u128 q = Vu0::MulXSum(Vu0::Q(*a), Vu0::Scalar(1.0f), Vu0::Q(e), Vu0::Scalar(len2));
        u128 r = Vu0::Sub(Vu0::Q(*p), q);
        d = Vu0::Dot(r, r);
    }
    Vu0::StoreX(*dist, Vu0::Sqrt(d));
}

INCLUDE_ASM(func_00186320);

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
    u8 pad04[0x10 - 4];
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
    };
    s32 i54;                // 0x54
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

INCLUDE_ASM(func_00186568);

void MoveMemory(void* dst, void* src, s32 size);

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

// The lowest float, read by func_00186BA8.
extern const f32 D_0024B258 = -3.40282347e+38f;
INCLUDE_ASM(func_00186BA8);

INCLUDE_ASM(func_00187260);

// A 0x30-byte hit CollectMeshHits gives: its point at 0x10, a float, a kind and a part.
struct MeshHitEntry { u8 pad0[0x20]; f32 f; s32 b; s32 c; u8 pad1[4]; };

s32 CollectMeshHits(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, MeshHitEntry* a6);
s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

void AddMeshContacts(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6)
{
    MeshHitEntry ents[64];
    s32 n = CollectMeshHits(a1, a3, a4, a5, (u8*)a2 + 0x3A4, 0x40, ents);
    for (s32 i = n - 1; i >= 0; i--) {
        MeshHitEntry* e = &ents[i];
        CreatePooledContact(e->f, a0, a2, e, (u8*)e + 0x10, e->b, 0, e->c, a6);
    }
}

INCLUDE_ASM(func_00187A88);

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

INCLUDE_ASM(func_00187D08);

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

INCLUDE_ASM(func_00187F40);

INCLUDE_ASM(func_00188270);
