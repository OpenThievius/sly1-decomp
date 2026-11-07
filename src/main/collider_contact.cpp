// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "fpu.h"
#include "collider.h"
#include "cone_volume.h"

// Contacts between colliders: the friction and bounce of a pair of surface kinds, the pooled
// contact chains, the searches over a collider's edges, and class 0x03's contact method
// (func_00187F40) with the routines it runs, most of them VU0 assembly.

// A surface kind's weight and value; a pair's number is the sum of the values over the sum of
// the weights.
struct SurfaceWeight { f32 a; f32 b; };

SurfaceWeight D_00264840[13] = {
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
SurfaceWeight D_002648A8[13] = {
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
void func_00121338(void* self);

// Two surface kinds, indexes into the weight tables.
struct SurfacePair { s32 a; s32 b; };

extern s32 D_00262C64;

f32 func_00185C18(SurfacePair* p)
{
    f32 num = g_surfaceFriction[p->a].b + g_surfaceFriction[p->b].b;
    f32 den = g_surfaceFriction[p->a].a + g_surfaceFriction[p->b].a;
    f32 r = num / den;
    if (r < 0.0f) r = 0.0f;
    if (g_buttonCodeFlags & 8) r = r * 0.2f;
    return r;
}



f32 func_00185CA0(SurfacePair* p)
{
    f32 one = 1.0f;
    f32 num = g_surfaceBounce[p->a].b + g_surfaceBounce[p->b].b;
    f32 den = g_surfaceBounce[p->a].a + g_surfaceBounce[p->b].a;
    f32 r = num / den;
    if (r < 0.0f) return 0.0f;
    if (one < r) r = one;
    return r;
}

ASM_FUNC(func_00185D20);

ASM_FUNC(func_00185F48);

ASM_FUNC(func_001860A8);

void func_001B5F28(u8* a, void* b);

void func_001861E8(u8* self, Contact03* head)
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

ASM_FUNC(func_00186230);

ASM_FUNC(func_00186320);

extern s32 D_00261F14;
extern u8 D_00211E10[];
void func_001F6C20(s32 unused);
void func_00202A80(void* dma, void* addr);
s32 func_00202C38(void* dma, s32 b, s32 c);

extern u8 D_00261F18[];
extern u8 D_00212110[];

void func_001F6C20(s32 a);
void func_00202A80(void* a, void* b);
s32 func_00202C38(void* a, s32 b, s32 c);

struct Self_186450 {
    u8 pad0[0x3AC];
    u8* base;
    u8 pad1[0x3B8 - 0x3B0];
    s32 count;
    u8* table;
};

struct Entry_186450 {
    s16 x;
    s16 y;
    u8 pad0[0x10 - 4];
};

struct Out_186450 {
    u8 pad0[0x58];
    Entry_186450* link;
    u8 pad1[0x70 - 0x5C];
};

s32 func_0013DFD8(void* a, u8* b, u8* c, s32 d, s32 e, Out_186450* f);

s32 func_00186450(s32 unused, Self_186450* self, u8* ctx, s32 cap, Out_186450* out)
{
    s32 i = self->count;
    i--;
    s32 total = 0;
    s32 filled = 0;
    Entry_186450* table = (Entry_186450*)self->table;
    u8* base = self->base;

    while (i >= 0) {
        Entry_186450* e = &table[i];
        total += func_0013DFD8(ctx, base + e->x * 16, base + e->y * 16, 0, cap - total, &out[total]);
        if (filled < total) {
            for (; filled < total; filled++)
                out[filled].link = e;
        }
        i--;
    }
    return total;
}

ASM_FUNC(func_00186568);

struct __attribute__((aligned(16))) Row_1867C8 {
    f32 v[4];
};

struct Pair_1867C8 {
    s16 v[2];
};

struct Edge_1867C8 {
    Row_1867C8 r0;
    Row_1867C8 r1;
    Row_1867C8 r2;
    Row_1867C8 r3;
    f32 f40;
    f32 f44;
    u8 pad48[0x50 - 0x48];
    s32 i50;
    s32 i54;
    Pair_1867C8* idx58;
    s32 slot5C;
    Edge_1867C8* next;
};

void func_001F5B08(void* dst, void* src, s32 size);

void func_001867C8(s32 count, Edge_1867C8* base, s32* outCount, s32* keys, Edge_1867C8** groups, Edge_1867C8** head)
{
    Edge_1867C8* single = 0;
    s32 n = 0;
    s32 i;
    s32 j;
    Edge_1867C8* e;
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
            Row_1867C8 t;
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
            if (e->idx58->v[e->slot5C] == keys[j]) {
                break;
            }
        }
        if (j >= n) {
            keys[j] = e->idx58->v[e->slot5C];
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
                Pair_1867C8* r = e->idx58;
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

struct Pair_00186A70 { u8 pad0[4]; s16 k1; s16 k2; };
struct Grp_00186A70 { u8 pad0[0x58]; Pair_00186A70* pair; u8 pad1[4]; Grp_00186A70* next; };
struct Item_00186A70 { u8 pad0[0x1C]; u16 flags; u8 pad1[2]; };
struct Rec_00186A70 { Rec_00186A70* parent; Grp_00186A70* node; s32 id; };

s32 func_00186A70(Item_00186A70* base, s32 key, s32 target, Grp_00186A70* head, Grp_00186A70** out)
{
    Rec_00186A70 recs[64];
    s32 n;
    s32 nrec;
    s32 i;

    recs[0].parent = 0;
    recs[0].node = 0;
    recs[0].id = key;
    for (i = 0, nrec = 1; i < nrec; i++) {
        Rec_00186A70* rc = &recs[i];
        Grp_00186A70* g;
        for (g = head; g != 0; g = g->next) {
            Pair_00186A70* p = g->pair;
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
            Item_00186A70* it = &base[id];
            if ((it->flags & 4) == 0) {
                it->flags |= 4;
                Rec_00186A70* r = &recs[nrec++];
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
ASM_FUNC(func_00186BA8);

ASM_FUNC(func_00187260);

struct Ent_001879C0 { u8 pad0[0x20]; f32 f; s32 b; s32 c; u8 pad1[4]; };

s32 func_00187260(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, Ent_001879C0* a6);
s32 func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

void func_001879C0(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6)
{
    Ent_001879C0 ents[64];
    s32 n = CollectMeshHits(a1, a3, a4, a5, (u8*)a2 + 0x3A4, 0x40, ents);
    for (s32 i = n - 1; i >= 0; i--) {
        Ent_001879C0* e = &ents[i];
        CreatePooledContact(e->f, a0, a2, e, (u8*)e + 0x10, e->b, 0, e->c, a6);
    }
}

ASM_FUNC(func_00187A88);

ASM_FUNC(func_00187B60);

struct Rec_00187C28 { u8 pad0[0x50]; void* p; u8 pad1[0x1C]; };
struct Vec_00187C28 { f32 x; f32 y; f32 z; f32 w; };

s32 func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
void func_00187B60(void* a0, void* a1, void* a2, void* a3, f32 f);
s32 func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, void* a6, void* a7);

s32 func_00187C28(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5)
{
    Rec_00187C28 recs[2];
    Vec_00187C28 v1;
    Vec_00187C28 v2;
    s32 count = func_0013DFD8(a4, (u8*)a0 + 0x370, (u8*)a0 + 0x140, 0, 2, recs);
    s32 idx = 0;
    if (count > 0) {
        idx = (recs[0].p == 0);
    }
    if (idx >= count) {
        return 0;
    }
    void* p = recs[idx].p;
    FindPartSupportPoint(a0, p, &v1, &v2, *(f32*)((u8*)p + 0x10));
    CreatePooledContact(v2.x, a0, a1, &v1, p, 8, 0, p, a5);
    return 1;
}

ASM_FUNC(func_00187D08);

struct Loc_00187E88 { s32 a[4]; s32 b[4]; f32 fa; f32 fb; s32 pad[2]; };

s32 func_00187D08(void* a0, void* a1, void* a2, s32 a3, void* a4, void* a5, void* a6, f32 f);
void func_00187B60(void* a0, void* a1, void* a2, void* a3, f32 f);
s32 func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

s32 func_00187E88(void* a0, void* a1, void* a2)
{
    Loc_00187E88 loc;
    if (IntersectSegmentWithSphere((u8*)a1 + 0x140, (u8*)a0 + 0x370, (u8*)a0 + 0x140, 0, &loc, loc.b, &loc.fa, *(f32*)((u8*)a1 + 0x3CC)) == 0) {
        return 0;
    }
    FindPartSupportPoint(a0, loc.b, loc.a, &loc.fb, loc.fa);
    CreatePooledContact(loc.fb, a0, a1, loc.a, loc.b, 9, 0, 0, a2);
    return 1;
}

ASM_FUNC(func_00187F40);

INCLUDE_ASM(func_00188270);
