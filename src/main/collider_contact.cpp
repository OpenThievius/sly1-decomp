// SPDX-License-Identifier: AGPL-3.0-or-later
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
void func_001860A8(void* a0, s32 n, Contact03** list);

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
    func_001860A8(((BaseObject*)a0)->world, 1, (Contact03**)&c);
    c->next = *(PooledContact**)a7;
    *(PooledContact**)a7 = c;
    return (s32)c;
}

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

INCLUDE_ASM(func_00186230);

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

void func_00187A88(Collider* self, Collider* other, void* a2)
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

struct Item_188270 {
    s32 a, b, c;
};

struct Obj_188270;

struct Node_188270 {
    u8 pad0[0x3F0];
    s32 f3F0;
    s32 f3F4;
    Item_188270* f3F8;
    u8 pad3FC[0x13C];
    u64 flags;
};

struct Vt_188270 {
    u8 pad[0xF4];
    s32 (*f0)(Obj_188270*, Node_188270*, s32, s32, Item_188270*, Item_188270*, s32*);
    s32 (*f1)(Obj_188270*, Node_188270*, s32, Item_188270*, Item_188270*, s32*);
};

struct Obj_188270 {
    Vt_188270* vt;
    u8 pad4[0x3D0 - 4];
    f32 f3D0;
    f32 f3D4;
    u8 pad3D8[8];
    u8 blob[1];
};

struct Pair_188270 {
    Obj_188270* a;
    Obj_188270* b;
};

void PushBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);
s32 func_0013E430(Item_188270* node, void* p, f32 f, Item_188270** out);

// A mark on the back memory for as long as it is in scope. Retail's frame has its one-byte
// slot at 0x10, between the ordered pair and the two address-taken locals, and reads the result
// after PopBackMemoryMark (docs/TOOLCHAIN.md, "A scalar local's store and a call's argument
// registers").
struct BackMemoryScope {
    BackMemoryScope() { PushBackMemoryMark(); }
    ~BackMemoryScope() { PopBackMemoryMark(); }
};

s32 BuildObjectPairContacts(s32 unused, Pair_188270* pair, s32 arg)
{
    Pair_188270 ord;
    Item_188270* cur;
    s32 res;
    Obj_188270* pa = pair->a;
    Obj_188270* pb = pair->b;
    f32 da = pa->f3D0;
    f32 db = pb->f3D0;
    res = 0;
    if (da > db) {
        ord.a = pb;
        ord.b = pa;
    } else {
        ord.a = pa;
        ord.b = pb;
    }
    s32 most = 0;
    Node_188270* n;
    for (n = *(Node_188270**)((u8*)ord.b + 0x2D8); n; n = *(Node_188270**)((u8*)n + 0x2E4)) {
        if (n->f3F4 > most) {
            most = n->f3F4;
        }
    }
    {
        BackMemoryScope mark;
        Item_188270* buf = (Item_188270*)AllocateBackMemory(most * 12);
        s32 idx;
        for (n = *(Node_188270**)((u8*)ord.b + 0x2D8); n; n = *(Node_188270**)((u8*)n + 0x2E4)) {
            if (n->flags & 0x80000000000ULL) {
                continue;
            }
            if (n->flags & 0x10000000000ULL) {
                cur = 0;
            } else {
                Item_188270* h = n->f3F8;
                if (h == 0) {
                    continue;
                }
                cur = buf;
                if (func_0013E430(h, ord.a->blob, ord.a->f3D4, &cur) != 2) {
                    continue;
                }
                idx = cur - buf;
                cur = cur - 1;
            }
            ord.a->vt->f0(ord.a, n, arg, idx, buf, cur, &res);
            if (ord.a->vt->f1) {
                ord.a->vt->f1(ord.a, n, idx, buf, cur, &res);
            }
        }
        for (n = *(Node_188270**)((u8*)ord.a + 0x2D8); n; n = *(Node_188270**)((u8*)n + 0x2E4)) {
            if (n->flags & 0x80000000000ULL) {
                continue;
            }
            if (!(n->flags & 0x10000000000ULL) && n->f3F8 == 0) {
                continue;
            }
            if (ord.b->vt->f1) {
                ord.b->vt->f1(ord.b, n, n->f3F0, n->f3F8, n->f3F8, &res);
            }
        }
    }
    return res;
}
