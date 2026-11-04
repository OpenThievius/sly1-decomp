// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "fpu.h"

struct Vec2_1840B8 { f32 x; f32 y; };

void func_00183F40(f32* out0, f32* out1, f32 a, f32 b, f32 c, f32 d);

void func_001840B8(Vec2_1840B8* self, f32* out0, f32* out1)
{
    func_00183F40(out0, out1, self->x, 1.0f, self->y, 0.0f);
}

struct Obj_001841B0 { u8 pad[0x304]; s32 f304; };
extern s32 D_002622CC;
extern s32 D_00264260;

void func_001841B0(Obj_001841B0* self)
{
    if (self->f304 == 0) {
        D_00264260 = D_002622CC;
    }
}

struct Obj_184768 { u8 pad0[0x2C8]; u64 bits; s32 flag; };
void func_001841D0(void* self);
void func_00184B58(void* self);

void func_00184768(Obj_184768* self, s32 flag)
{
    self->flag = flag;
    if (flag == 0) {
        self->bits = (self->bits & ~(u64)0x30000000000) | ((u64)0x8000 << 25);
    } else {
        self->bits = self->bits & ~(u64)0x30000000000;
    }
    func_001841D0(self);
    func_00184B58(self);
}

struct Obj_001847F0 { u8 pad[0x2E0]; u32 q[4]; };
struct Quad_001847F0 { u32 w[4]; } __attribute__((aligned(16)));

void func_001847F0(Obj_001847F0* self, Quad_001847F0* src)
{
    *(Quad_001847F0*)self->q = *src;
    func_001841D0(self);
}

struct Obj_00184818 { u8 pad[0x2F0]; f32 value; };

void func_00184818(Obj_00184818* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_00184838 { u8 pad[0x2F4]; f32 value; };

void func_00184838(Obj_00184838* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_00184858 { u8 pad[0x2F8]; f32 value; };

void func_00184858(Obj_00184858* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_00184878 { u8 pad[0x2FC]; f32 value; };

void func_00184878(Obj_00184878* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_00184898 { u8 pad[0x300]; f32 value; };

void func_00184898(Obj_00184898* self, f32 v)
{
    self->value = v;
    func_001841D0(self);
}

struct Obj_184968 { u8 pad[0x304]; s32 f304; };

void func_00184968(Obj_184968* self, s32 v)
{
    if (v != self->f304) {
        self->f304 = v;
        func_001841D0(self);
    }
}

struct __attribute__((packed)) Packed8_184990 { u64 v; };

struct Obj_184990 {
    u8 pad0[0x330];
    Packed8_184990 p330;
};

void func_00184990(Obj_184990* self, Packed8_184990* src)
{
    self->p330 = *src;
    func_001841D0(self);
    func_00184B58(self);
}

struct Obj_1849D0 {
    u8 pad0[0x338];
    f32 f338;
};

void func_00184A70(void* self);

void func_001849D0(Obj_1849D0* self, f32 v)
{
    self->f338 = v;
    func_00184A70(self);
    func_001841D0(self);
    func_00184B58(self);
}

struct Obj_184A08 {
    u8 pad0[0x33C];
    f32 f33C;
};

void func_00184A08(Obj_184A08* self, f32 v)
{
    self->f33C = v;
    func_00184A70(self);
    func_001841D0(self);
}

struct __attribute__((aligned(16))) Quad_184A38 { s32 a, b, c, d; };

struct Obj_184A38 {
    u8 pad0[0x340];
    Quad_184A38 q340;
};

void func_00184A38(Obj_184A38* self, Quad_184A38* src)
{
    self->q340 = *src;
    func_001841D0(self);
    func_00184B58(self);
}

void func_00184818(void* self, f32 v);
void func_00184838(void* self, f32 v);

void func_00184CD0(void* self, f32 v)
{
    func_00184818(self, v);
    func_00184838(self, v);
}

struct Obj_184D10 {
    u8 pad0[0x2F0];
    f32 f2F0;
};

void func_00184D10(Obj_184D10* self, f32* out)
{
    *out = self->f2F0;
}

struct __attribute__((aligned(16))) Quad_00184D20 { s32 a, b, c, d; };

void func_001B4600(void* a0, void* a1);
void func_001847F0(void* self, void* a1);

void func_00184D20(void* self, void* a1)
{
    Quad_00184D20 q;
    func_001B4600(a1, &q);
    func_001847F0(self, &q);
}

void func_001B4580(void* self);

void func_00184D58(u8* self)
{
    func_001B4580(self + 736);
}

void func_00121338(void* self);

struct IndexPair_185C18 { s32 a; s32 b; };
struct Weight_264840 { f32 a; f32 b; };

extern Weight_264840 D_00264840[13];
extern s32 D_00262C64;

f32 func_00185C18(IndexPair_185C18* p)
{
    f32 num = D_00264840[p->a].b + D_00264840[p->b].b;
    f32 den = D_00264840[p->a].a + D_00264840[p->b].a;
    f32 r = num / den;
    if (r < 0.0f) r = 0.0f;
    if (D_00262C64 & 8) r = r * 0.2f;
    return r;
}

struct IndexPair_185CA0 { s32 a; s32 b; };
struct Weight_2648A8 { f32 a; f32 b; };

extern Weight_2648A8 D_002648A8[13];

f32 func_00185CA0(IndexPair_185CA0* p)
{
    f32 one = 1.0f;
    f32 num = D_002648A8[p->a].b + D_002648A8[p->b].b;
    f32 den = D_002648A8[p->a].a + D_002648A8[p->b].a;
    f32 r = num / den;
    if (r < 0.0f) return 0.0f;
    if (one < r) r = one;
    return r;
}

struct Node_1861E8 {
    u8 pad0[0xD0];
    Node_1861E8* next;
};

void func_001B5F28(u8* a, void* b);

void func_001861E8(u8* self, Node_1861E8* head)
{
    if (head != 0) {
        Node_1861E8* cur = head;
        do {
            Node_1861E8* next = cur->next;
            func_001B5F28(self + 0x1AFC, cur);
            cur = next;
        } while (cur != 0);
    }
}

struct Ent_001879C0 { u8 pad0[0x20]; f32 f; s32 b; s32 c; u8 pad1[4]; };

s32 func_00187260(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, Ent_001879C0* a6);
void func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

void func_001879C0(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6)
{
    Ent_001879C0 ents[64];
    s32 n = func_00187260(a1, a3, a4, a5, (u8*)a2 + 0x3A4, 0x40, ents);
    for (s32 i = n - 1; i >= 0; i--) {
        Ent_001879C0* e = &ents[i];
        func_00185D20(e->f, a0, a2, e, (u8*)e + 0x10, e->b, 0, e->c, a6);
    }
}

struct Rec_00187C28 { u8 pad0[0x50]; void* p; u8 pad1[0x1C]; };
struct Vec_00187C28 { f32 x; f32 y; f32 z; f32 w; };

s32 func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
void func_00187B60(void* a0, void* a1, void* a2, void* a3, f32 f);
void func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, void* a6, void* a7);

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
    func_00187B60(a0, p, &v1, &v2, *(f32*)((u8*)p + 0x10));
    func_00185D20(v2.x, a0, a1, &v1, p, 8, 0, p, a5);
    return 1;
}

struct Loc_00187E88 { s32 a[4]; s32 b[4]; f32 fa; f32 fb; s32 pad[2]; };

s32 func_00187D08(void* a0, void* a1, void* a2, s32 a3, void* a4, void* a5, void* a6, f32 f);
void func_00187B60(void* a0, void* a1, void* a2, void* a3, f32 f);
void func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

s32 func_00187E88(void* a0, void* a1, void* a2)
{
    Loc_00187E88 loc;
    if (func_00187D08((u8*)a1 + 0x140, (u8*)a0 + 0x370, (u8*)a0 + 0x140, 0, &loc, loc.b, &loc.fa, *(f32*)((u8*)a1 + 0x3CC)) == 0) {
        return 0;
    }
    func_00187B60(a0, loc.b, loc.a, &loc.fb, loc.fa);
    func_00185D20(loc.fb, a0, a1, loc.a, loc.b, 9, 0, 0, a2);
    return 1;
}

extern s32 D_00261F14;
extern u8 D_00211E10[];
void func_001F6C20(s32 unused);
void func_00202A80(void* dma, void* addr);
void func_00202C38(void* dma, s32 b, s32 c);

extern u8 D_00261F18[];
extern u8 D_00212110[];

void func_001F6C20(s32 a);
void func_00202A80(void* a, void* b);
void func_00202C38(void* a, s32 b, s32 c);

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

extern s32 D_00264838;
extern s32 D_00275AF0;
extern u8 D_00262C70[];
extern u8 D_00275BC0[];
extern u8 D_00264A40[];
extern void* D_00261990;
extern s32 D_002622CC;

void func_001FAE18(void);
void func_00185B38(void);
void func_0015F210(s32 flag);
void func_0018F148(void* p);
void func_001E4EA8(void* p);
void func_0016E238(void* p);
void func_0016F2E0(void);
void func_0018BDC8(void* p);
void func_001E9108(void* p);
void func_001607D0(f32 dt);
void func_00144270(void* p);
void func_0015E9F0(void);
void func_00142F10(void* p);
void func_001E9668(void* p);
void func_001E9648(void* p);
void func_0015EC68(void);

typedef void (*Fn_185B38)(void);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern Fn_Table D_002647C0[];

s32 func_00193210(void* a, void* b, void* c, void* d, void* e);
void func_00191E70(s32 value);
void func_00193270(void* p);
void func_00193288(void* self, s32 value);
void func_00193300(void* p);
void func_00191EB0(s32 value);

s32 func_001925F0(void);

extern const char D_0024B248[16];
extern const u8* D_002647A8[6];
void func_00140B60(void* buf, const u8* name, s32 n);
void func_001F7BE8(s32 a);
s32 func_00203548(s32 a);
s32 func_00140968();
void func_001409A8();
s32 func_001F8BF8();
s32 func_001F9C50(void* buf);
s32 func_001F9C18();
s32 func_001F9820();
s32 func_00203828(s32 a);
s32 func_00140D68(s32 a);
s32 func_001F9A90(void* buf, s32 a, s32 b);

struct Obj_184A70 {
    u8 pad0[0x338];
    f32 in0;
    f32 in1;
    u8 pad1[0x350 - 0x340];
    f32 s0;
    f32 s1;
    f32 f358;
    f32 f35C;
    f32 f360;
    f32 f364;
    f32 f368;
    f32 f36C;
};

f32 func_002054F0(f32 a);

struct Clamp_184A70 {
    static f32 Of(f32 v, f32 lo, f32 hi)
    {
        if (v < lo)
            return lo;
        if (hi < v)
            return hi;
        return v;
    }
};

void func_00184A70(Obj_184A70* self)
{
    f32 a = Clamp_184A70::Of(self->in0, 0.0f, 175.0f);
    f32 b = Clamp_184A70::Of(self->in1, 0.0f, a);
    f32 r = func_002054F0(a * 0.00872664712f);
    self->s1 = r;
    self->s0 = r;
    f32 q = func_002054F0(b * 0.00872664712f);
    self->f360 = q / self->s0;
    self->f368 = q / self->s1;
    self->f36C = self->f364 = 1.0f;
    self->f358 = Fpu::Sqrt(self->f360);
    self->f35C = 1.0f;
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_0011E560();
void func_0012B868();
void func_00139C38();
void func_00140790();
void func_001409D8();
void func_001430C8();
void func_00143140();
void func_00152810();
void func_0015C178();
void func_0015E810();
void func_00160070();
void func_001688B8();
void func_00169C58();
void func_0016E0B8();
void func_0016F588();
void func_0017FD48();
void func_0018B580();
void func_0018D430();
void func_0018E5E8();
void func_00191EC0();
void func_0019DF48();
void func_001A9C68();
void func_001BF130();
void func_001DFD48();
void func_001E2398();
void func_001E9088();

struct Out_1840F0;
f32 func_00205210(f32 value);
void func_00183F40(f32 a, f32 b, f32 c, f32 d, Out_1840F0* out0, void* out1);

void func_001840F0(f32 a, f32 b, f32 c, f32 d, Out_1840F0* out0, void* out1)
{
    f32 x = func_00205210(a * 0.0087266471f);
    x = x + x * x * x;
    f32 y = func_00205210(c * 0.0087266471f);
    y = y + y * y * y;
    func_00183F40(x, b * 0.003921569f, y, d * 0.003921569f, out0, out1);
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
            func_001F5B08(groups + j, groups + j + 1, bytes);
            func_001F5B08(keys + j, keys + j + 1, bytes);
            j--;
            n--;
        }
    next:;
    }
    *outCount = n;
}

extern const char D_0024B1E8[];

Weight_264840 D_00264840[13] = {
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
Weight_2648A8 D_002648A8[13] = {
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
