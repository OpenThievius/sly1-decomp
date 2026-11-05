// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "c2f.h"
#include "listed_collision_part.h"
#include "c6e.h"
#include "point_object.h"
#include "current_placed_object.h"
#include "part_holder_object.h"
#include "list_iter.h"
#include "t217d.h"
#include "v24a0.h"
#include "v24a2.h"
#include "g27c220.h"
#include "t2195.h"
#include "g262c70.h"
#include "globals.h"
#include "strip_mesh.h"
#include "bump_allocator.h"
#include "texture_header.h"
#include "shapes.h"

void func_001B7B78(void* self);
void func_00152600(void* data, void* self);

void func_0016A4C8(ListedCollisionPart* self)
{
    func_001B7B78(self);
    func_00152600(&D_00262708, self);
}

void func_001BA130(void* self);

void func_0016A500(ListedCollisionPart* self)
{
    Link02 tmp = self->listLink;
    func_001BA130(self);
    self->listLink = tmp;
}

s32 func_001B8A08(C03* a, C03* b);

s32 func_0016A548(C03* a0, C03* a1)
{
    if ((void*)a1 == D_00262E10 && (void*)a0 == ((C07*)a1)->f23B0) {
        return 1;
    }
    return func_001B8A08(a0, a1);
}

void* func_0015A448(void* obj, s32 id, s32 flags);
void func_001F4ED0(void* p);

void func_0016B520(T217D_12E0* self)
{
    if (self->open != 0) {
        void* p = func_0015A448(D_00275710, 0x4FD, 0);
        if (p != 0) {
            func_001F4ED0(p);
        }
    }
}

void func_0016B560(T217D_12E0* self)
{
    func_001AA298(self);
}

u32 func_0016BB78(u32 bit)
{
    u32 mask;
    if (bit >= 16) {
        mask = 0;
    } else {
        mask = 1 << bit;
    }
    return D_002623C0->u19F4 & mask;
}

extern s32 D_002BE470;
extern s32 D_002626C0;
s32 D_002626C4 = 0;
extern s32 D_002626C8;
extern s32 D_002626CC;
extern s32 D_00262484;
extern const f32 D_0024A794;
extern const f32 D_0024A79C;
extern const u32 D_0024A7A0[2];
extern const char D_0024A7A8[8];
extern const char D_0024A7B0[8];
extern const char D_0024A7B8[32];
extern u8 D_00262490[];
extern u8 D_002624F0[];
extern u8 D_002625E0[];

void func_00168AF8(void);
void func_001683B8(void);
void func_00201A18(s32 a0, s32 a1, s32 a2, s32 a3);
void func_00202098(void* p, s32 a1, s32 a2, s32 a3);
void func_001F6C20(s32 a0);
void func_00201FF8(void* p, s32 a1);

void func_001685B8(void)
{
    D_002BE470 = 1;
    func_00168AF8();
    func_001683B8();
    D_002BE470 = 0;
    func_00201A18(0, 1, 2, 1);
    u32 flag = (*(u32*)0x12001000 >> 13) & 1;
    s32 cnt = D_002626C0;
    D_002626CC = 0;
    D_00262484 = 0;
    D_002626C8 = flag;
    D_002626C4 = (flag == 0);
    u8* ptr;
    if (cnt & 1) {
        ptr = D_002624F0;
    } else {
        ptr = D_002625E0;
    }
    s16 half = *(s16*)&D_002626C4;
    func_00202098(ptr, 0x800, 0x800, half);
    func_001F6C20(0);
    D_002626C0 = D_002626C0 + 1;
    func_00201FF8(D_00262490, D_002626C0);
}

struct Blob_168AF8 { u8 bytes[0x20]; };

extern u8 D_002BE1A0[];
void func_00152888(Blob_168AF8* a);
void func_001529C8(Blob_168AF8* a, s32 n, Blob_168AF8* b);
void func_00152B80(Blob_168AF8* a, s32 n, void* table);
void func_00152D30(Blob_168AF8* a);
void func_001529E0(Blob_168AF8* a, s32 x, s32 y);
void func_00168A48(Blob_168AF8* b);

void func_00168AF8(void)
{
    Blob_168AF8 a;
    Blob_168AF8 b;

    func_00152888(&a);
    func_001529C8(&a, 2, &b);
    func_00152B80(&a, 0x2C, D_002BE1A0);
    func_00152D30(&a);
    func_001529E0(&a, 0, 0);
    func_00168A48(&b);
}

struct Frame_1692B0 : V24A0 { s32 value; };

extern s32 D_00274514;
extern s32 D_00274510;
extern s32 D_00261F1C;

void func_001611B8(V24A0* f);
void func_0018D608(void);
void func_00152980(V24A0* f, s32 size);
void func_00152B38(V24A0* f);
s32 func_001690C0(void* self, void* arg, Frame_1692B0* f);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161708(V24A0* f, s32 a, u64 b);
void func_00161200(V24A0* f);
void func_00152D30(V24A0* f);
void func_001529E0(V24A0* f, s32 a, s32* out);
void func_001686E8(s32 a, s32 b);
void func_0018D6F0(void);

void func_001692B0(void* self, void* arg)
{
    Frame_1692B0 f;

    if (self == 0) {
        return;
    }
    func_001611B8(&f);
    func_0018D608();
    func_00152980(&f, ((D_00274514 * 2 + D_00274514 + D_00274510) * 8) | 4);
    func_00152B38(&f);
    if (func_001690C0(self, arg, &f) != 0) {
        func_001613C0(&f, 0, 1, 0xE);
        func_00161708(&f, 0x3F, 0);
        func_00161708(&f, 0x61, 0);
        func_00161200(&f);
        func_00152D30(&f);
        func_001529E0(&f, 0, &f.value);
        func_001686E8(D_00261F1C, f.value);
    }
    func_0018D6F0();
}

struct Ent_1696B8 { s32 a; s32 b; u32 value; s32 d; };

extern s32 D_002626D0;
extern Ent_1696B8 D_0027DC20[];

void func_001696B8(s32 idx, u32 lo, u32 take, u32 give)
{
    u32 end = take + lo;

    if (idx < D_002626D0) {
        Ent_1696B8* e = &D_0027DC20[idx];
        s32 n = D_002626D0 - idx;

        do {
            if (e->value >= take && e->value < end) {
                e->value = give + (e->value - take);
            }
            e++;
            n--;
        } while (n != 0);
    }
}

void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_00169D20(C6F* self)
{
    func_00182D48(self);
    func_00152470(&D_002626E8, self);
}

void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

void func_0016A178(C7F* self)
{
    func_00182ED0(self);
    func_00152600(&D_002626F8, self);
}

struct Ent_262718 { s32 a; s32 b; s32 c; };
struct Tab_262718 { Ent_262718 e[9]; s32 end; };
extern Tab_262718 D_00262718;

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
u32 func_001601D8(s32 idx);
u32* func_00160810(s32 idx);

void func_0016AA18(PartHolderObject* self)
{
    func_00124A48(self);
    func_00124DF8(self, 9, &D_00262718);

    if ((u32)(self->id - 0x515) < 5) {
        s32 t = self->id - 0x514;
        s32 s4 = t << 8;

        for (s32 i = 0; i < 9; i++) {
            if (self->parts[i] == 0) {
                continue;
            }
            s32 flag;
            if (i == 8) {
                flag = D_002623C0->levels[t].f448 & 0x20;
            } else {
                s32 idx = s4 | i;
                u32 r = func_001601D8(idx);
                u32* p = func_00160810(idx);
                if ((r & 2) != 0) {
                    flag = *p & 2;
                } else {
                    flag = *p & 1;
                }
            }
            if (flag != 0) {
                PartObject* obj = self->parts[i];
                obj->vtbl[6](obj);
            }
        }
    }
}

struct Res_0015A448 {
    u8 pad_00[0x398];
    s32 f398;
};

void* func_0015A448(void* a, s32 b, s32 c);
void* func_0015A448(void* a, s32 b, void* c);

void func_00169D90(C6F* self)
{
    if (self->id44 != -1) {
        Res_0015A448* r = (Res_0015A448*)func_0015A448(self->world, self->id44, self->parent);
        self->found48 = r;
        r->f398 = 0;
    }
}

void func_001830D8(void* self);

void func_00169DD8(C6F* self)
{
    Keep6E saved = self->keep;
    func_001830D8(self);
    self->keep = saved;
}

void func_0016A140(C7F* self)
{
    func_00182D48(self);
    func_00152470(&D_002626F8, self);
}

void func_0016A1B0(C7F* self)
{
    if (self->targetId != -1) {
        Res_0015A448* r = (Res_0015A448*)func_0015A448(self->world, self->targetId, self->parent);
        self->target = r;
        r->f398 = 0;
    }
}

void func_0016A1F8(C7F* self)
{
    KeptBits saved = self->keep;
    func_001830D8(self);
    self->keep = saved;
}

void func_001B7968(void* self);
void func_00129FB0(void* self, f32 k);
void func_0012A080(void* self, f32 k);
void func_0012A150(void* self, f32 k);
void func_0012A270(void* self, f32 k);

void func_0016A3A8(ListedCollisionPart* self)
{
    f32 k = 3.0f;
    func_001B7968(self);
    func_00129FB0(self, k);
    func_0012A080(self, k);
    func_0012A150(self, k);
    func_0012A270(self, 2.0f);
    self->f568 = 300.0f;
}

void func_001B7A98(void* self);

void func_0016A490(ListedCollisionPart* self)
{
    func_001B7A98(self);
    func_00152470(&D_00262708, self);
}

void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, u64 b);
void func_00161958(void* p, s32 x);

void func_00168D98(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx)
{
    func_001613C0(ctx, 0, 1, 0xE);
    func_00161708(ctx, 0x50, ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56));
    func_00161708(ctx, 0x51, 0);
    func_00161708(ctx, 0x52, rrw | ((u64)rrh << 32));
    func_00161708(ctx, 0x53, 0);
    func_00161958(ctx, x);
}

struct Bits_168FB0 {
    u64 f0 : 14;
    u64 f14 : 6;
    u64 f20 : 6;
    u64 f26 : 4;
    u64 f30 : 4;
    u64 f34 : 1;
    u64 rest : 29;
};

u32 func_00168D30(u32 n);

void func_00168FB0(V24A2_ImgA* self, u32 a1)
{
    Bits_168FB0* bits = (Bits_168FB0*)&self->f18;
    bits->f0 = a1;
    bits->f14 = self->f9;
    bits->f20 = self->f8;
    bits->f26 = func_00168D30(self->f0) & 0xF;
    bits->f30 = func_00168D30(self->f2) & 0xF;
    bits->f34 = 1;
}

void func_00168D98(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void func_00169088(V24A2_ImgA* d, u32 dbp, void* ctx)
{
    func_00168D98(dbp, d->f9, d->f8, d->f0, d->f2, d->f14, ctx);
}

void func_00152438(void* self, s32 value);

void func_00169C58()
{
    func_00152438(&D_002626E8, 0x38);
    func_00152438(&D_002626F8, 0x50);
    func_00152438(&D_00262708, 0x558);
}

void func_00152440(void* self);

void func_00169CA0()
{
    func_00152440(&D_002626E8);
    func_00152440(&D_002626F8);
    func_00152440(&D_00262708);
}

void func_00182ED0(void* self);
void func_00152600(void* data, void* self);

void func_00169D58(C6F* self)
{
    func_00182ED0(self);
    func_00152600(&D_002626E8, self);
}

struct Pool_1694F8 { s32 f0; s32 f4; s32 f8; s32 fC; };
struct Link_1694F8 { MeshStrip* src; Pool_1694F8* dst; Link_1694F8* next; };

void func_001694A0(void* p);
void* func_0018D5C0(u32 n);

void func_001694F8(StripMesh* a0, MeshStrip* a1, s32 a2, s32 a3, s32 a4, MeshNode* a5)
{
    Pool_1694F8 local;
    Pool_1694F8* e;
    s32 link;
    s32 idx;
    s32 count;
    s32 n;
    s32 scale;
    s32 base;
    s32 off;

    link = 0;
    if (a5 != 0) {
        link = a5->flags & 1;
    }
    count = D_002626D0;
    if (count >= 0x4000) {
        goto local_path;
    }
    if (a0 == 0) {
        goto pool_path;
    }
    if ((a0->flags & 0x10000000) == 0) {
        goto pool_path;
    }
    if (link != 0) {
        goto pool_path;
    }
local_path:
    link = (count < 0x4000) ? link : 0;
    e = &local;
    goto store;
pool_path:
    n = D_002626D0;
    e = (Pool_1694F8*)&D_0027DC20[n];
    n++;
    D_002626D0 = n;
store:
    e->f0 = a3;
    idx = 0;
    if (a5 != 0) {
        idx = a5->index;
    }
    scale = a1->count;
    base = a1->base;
    off = idx * scale;
    e->f8 = a2;
    e->fC = a4;
    e->f4 = base + (off << 4);
    func_001694A0(e);
    if (link != 0) {
        Link_1694F8* p = (Link_1694F8*)func_0018D5C0(12);
        if (p != 0) {
            p->src = a1;
            p->dst = e;
            p->next = (Link_1694F8*)a5->links;
            a5->links = p;
        }
    }
}

struct Pool_169608 { s32 f0; s32 f4; s32 f8; s32 fC; };
struct Link_169608 { s32 src; Pool_169608* dst; Link_169608* next; };

void func_001694A0(void* p);
void* func_0018D5C0(u32 n);

void func_00169608(s32 a0, s32 a1, MeshNode* a2)
{
    Pool_169608 local;
    Pool_169608* e;
    s32 count = D_002626D0;

    if (count >= 0x4000) {
        e = &local;
    } else {
        e = (Pool_169608*)&D_0027DC20[count];
        D_002626D0 = count + 1;
    }
    e->f0 = a1;
    e->f4 = (s32)a2 + 0xC;
    e->f8 = a0;
    e->fC = 0;
    func_001694A0(e);
    if (D_002626D0 < 0x4000) {
        Link_169608* p = (Link_169608*)func_0018D5C0(12);
        p->dst = e;
        p->src = 0;
        p->next = (Link_169608*)a2->links;
        a2->links = p;
    }
}

struct Quad_1688B8 { u8 b0; u8 b1; u8 b2; u8 b3; } __attribute__((packed));

extern u8 D_00262490[];
extern u8 D_002BDC20[];
extern u8 D_002BE1A0[];
extern u8 D_002BDEE0[];
extern s32 D_002BE460;
extern s32 D_002BE464;

void func_00201A18(s32 a0, s32 a1, s32 a2, s32 a3);
void func_00201D60(void* p, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_00168770(void* ctx, Quad_1688B8* v, s32 flag);
s32 func_001E2268(void* a, void* b);
void func_001F6950(s32 a0, void (*fn)(void), s32 a2);
void func_001F6DA8(s32 a0);
void func_00168D00(void);
void func_001685B8(void);
void func_001682C0(void);
void func_00168698(void);

void func_001688B8(void)
{
    Quad_1688B8 k;
    Quad_1688B8 t;

    func_00201A18(0, 1, 2, 1);
    u8* s0 = D_00262490;
    func_00201D60(s0, 0, 0x280, 0xE0, 3, 0x30, 0);
    u8* p = s0;
    s32 end = (s32)s0 + 0x50;
    do {
        *(s32*)p &= -2;
        p[1] = 0x80;
        *(s32*)p |= 0x20;
        p += 0x28;
    } while ((s32)p < end);
    k.b0 = 0;
    k.b1 = 0;
    k.b2 = 0;
    k.b3 = 0x80;
    t = k;
    func_00168770(D_002BDC20, &t, 0);
    t = k;
    func_00168770(D_002BE1A0, &t, 0);
    t = k;
    func_00168770(D_002BDEE0, &t, 1);
    D_002BE460 = func_001E2268((void*)0, (void*)1);
    D_002BE464 = func_001E2268((void*)0, (void*)1);
    func_001F6950(2, func_001682C0, 0);
    func_001F6DA8(2);
    func_001F6950(0, func_00168698, 0);
    func_001F6DA8(0);
    func_00168D00();
    func_001685B8();
}

extern s32 D_002626C0;
extern u8 D_002624E0[16];
extern u8 D_002625D0[16];
extern s32 D_00261F1C;

void func_001F6C20(s32 a0);
void func_00201C78(void* p);
void func_00202A80(s32 a, void* b);
void func_00202C38(s32 a, s32 b, s32 c);

void func_00168A48(Blob_168AF8* b)
{
    s32 i = 0;
    func_001F6C20(0);
    do {
        void* p;
        if (((i + D_002626C0) & 1) != 0) {
            p = D_002624E0;
        } else {
            p = D_002625D0;
        }
        func_00201C78(p);
        i++;
        func_00202A80(D_00261F1C, b);
    } while (i < 2);
    func_00202C38(D_00261F1C, 0, 0);
}

u32 func_00168D30(u32 n) { u32 count = 0; u32 value = 1; while (value < n && count < 31) { value <<= 1; count++; } return count; }

void func_00168D68(BumpAllocator* p, s32 value, s32 other) { p->next = value; p->start = value; p->limit = other; }

void func_00168D78(BumpAllocator* p) { p->next = p->start; }

void func_00168D68(BumpAllocator*,s32,s32);
void func_00168D00()
{
    func_00168D68(&D_002626D8,0x1E00,0x4000);
    D_002626D0=0;
}

s32 func_00168D88(s32* self,s32 size)
{
    s32 old=self[1];
    self[1]=old+size;
    return old;
}

extern s32 D_002BE470;
extern s32 D_002626C4;
extern s32 D_00262484;
extern s32 D_002626C8;
extern s32 D_002626C0;
extern s32 D_002626CC;
extern u8 D_00262490[];
extern u8 D_002624F0[];
extern u8 D_002625E0[];

void func_001683B8(void);
void func_00168130(void);
void func_00202098(void* p, s32 a1, s32 a2, s32 a3);
void func_001F6C20(s32 a0);
void func_00201FF8(void* p, s32 a1);
void func_00201988(s32 a0, s32 a1);

void func_001683E8(void)
{
    D_002BE470 = 1;
    func_001683B8();
    s32 a0 = D_002626C4;
    s32 a1 = D_00262484;
    D_002626C8 = a0;
    D_002BE470 = 0;
    if (a1 > 0) {
        D_002626C4 = 0;
        D_00262484 = a1 - 1;
    } else {
        u32 flag = (*(u32*)0x12001000 >> 13) & 1;
        D_002626C4 = (flag == 0);
    }
    u8* ptr;
    if (D_002626C0 & 1) {
        ptr = D_002624F0;
    } else {
        ptr = D_002625E0;
    }
    s16 half = *(s16*)&D_002626C4;
    func_00202098(ptr, 0x800, 0x800, half);
    func_001F6C20(0);
    D_002626C0 = D_002626C0 + 1;
    func_00201FF8(D_00262490, D_002626C0);
    if ((u32)(D_002626CC - 1) < 2) {
        func_00168130();
    }
    func_00201988(0, 0);
}

extern s32 D_002626CC;
extern s32 D_002BE474;
extern s32 D_002626C0;
extern s32 D_002626C4;
extern u8 D_002625E0[];
extern u8 D_002624F0[];
extern u8 D_002625D0[16];
extern u8 D_002624E0[16];

void func_00202098(void* p, s32 a1, s32 a2, s32 a3);
void func_001F6C20(s32 a0);
void func_00201C78(void* p);

void func_001684E8(void)
{
    if (D_002626CC == 3) {
        D_002626CC = 2;
    }
    if (D_002BE474 != 0) {
        u32 flag = (*(u32*)0x12001000 >> 13) & 1;
        s32 cnt = D_002626C0;
        D_002BE474 = 0;
        D_002626C4 = (flag == 0);
        u8* ptr;
        if (cnt & 1) {
            ptr = D_002625E0;
        } else {
            ptr = D_002624F0;
        }
        s16 half = *(s16*)&D_002626C4;
        func_00202098(ptr, 0x800, 0x800, half);
        func_001F6C20(0);
        u8* ptr2;
        if (D_002626C0 & 1) {
            ptr2 = D_002625D0;
        } else {
            ptr2 = D_002624E0;
        }
        func_00201C78(ptr2);
    }
}

struct Frame_1693A8 : V24A0 { u8 span[0x10]; s32 out; };

extern s32 D_00274514;
extern s32 D_00274510;

void func_001611B8(V24A0* f);
void func_00168D68(void* p, s32 a, s32 b);
void func_0018D608(void);
void func_00152980(V24A0* f, s32 size);
void func_00152B38(V24A0* f);
s32 func_001690C0(void* self, void* arg, Frame_1693A8* f);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161708(V24A0* f, s32 a, u64 b);
void func_00161200(V24A0* f);
void func_00152D30(V24A0* f);
void func_00152A50(V24A0* f, s32 a1, s32 a2, s32* out, s32 a4);
void func_001B3510(void* self);
void func_0018D6F0(void);

s32 func_001693A8(void* self)
{
    Frame_1693A8 f;

    func_001611B8(&f);
    f.out = 0;
    func_00168D68(f.span, 0x1400, 0x1E00);
    func_0018D608();
    func_00152980(&f, ((D_00274514 * 2 + D_00274514 + D_00274510) * 8) | 4);
    func_00152B38(&f);
    if (func_001690C0(self, f.span, &f) != 0) {
        func_001613C0(&f, 0, 1, 0xE);
        func_00161708(&f, 0x3F, 0);
        func_00161200(&f);
        func_00152D30(&f);
        func_00152A50(&f, 0, 0, &f.out, 7);
        func_001B3510(self);
    }
    func_0018D6F0();
    return f.out;
}

extern s32 D_002626D0;

void func_001694A0(void* p);

void func_00169718(void)
{
    s32 i;

    for (i = 0; i < D_002626D0; i++) {
        func_001694A0(&D_0027DC20[i]);
    }
}

struct Obj_16AED8Glob { u8 pad0[0x30]; s32 f30; };

s32 D_0026FCF0;
struct Ent_262788 { s32 a; s32 b; s32 c; };
extern Ent_262788 D_00262788[18];
extern u8 D_00275BC0[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001E96F8(void* obj, s32 mode);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_0016AB38(void* self);

void func_0016AED8(CurrentPlacedObject* self)
{
    func_00124A48(self);
    self->flags = (self->flags & ~(3ULL << 40)) | (1ULL << 40);
    D_0026FCF0 = (s32)self;
    ((Obj_16AED8Glob*)D_00275BC0)->f30 = 2;
    func_001E96F8(D_00275BC0, 2);
    func_00124DF8(self, 0x12, D_00262788);
    self->f2D0 = -1;
    func_001DBCC8(self->world, (void*)func_0016AB38, self, 0, 0);
}

struct Obj_16B0F8 { u8 pad0[0x2D0]; s32 f2D0; u8 pad1[0x28]; s32 f2FC; };

s32 func_0016EC98(void* p);
void func_0016B300(Obj_16B0F8* self, s32 idx, s32 zero);

void func_0016B0F8(Obj_16B0F8* self, void* a1)
{
    s32 n = self->f2D0;
    s32 r = func_0016EC98(a1);
    f32 f = (f32)r;
    s32 v = self->f2FC;
    s32 k = (v == 5);

    if (f < 0.0f) {
        if (n <= 0) {
            n = k ? v : n;
        } else {
            n--;
        }
    } else if (0.0f < f) {
        if (n >= v) {
            n = k ? 0 : n;
        } else {
            n++;
        }
    }
    func_0016B300(self, n, 0);
}

struct Node_16B7A8 {
    u8 pad0[0x2D0];
    s32 f2D0;
};

void func_0016B300(void* self, s32 idx, s32 flag);
void func_0016E0F0(s32 bits);
void func_0016EC88(void* p);
void func_001BE998(void);
void func_0016E118(s32 n);

void func_0016B7A8(T217D_12E0* self, s32 v)
{
    s32 flag = (v != 0);
    if (flag != (self->open == 0)) {
        return;
    }
    if (v != 0) {
        func_0016B300(self->node, ((Node_16B7A8*)self->node)->f2D0, 0);
        func_0016E0F0(1);
        func_0016EC88(&D_00262C70);
    } else {
        if (self->sound != 0) {
            func_001BE998();
            self->sound = 0;
        }
        func_0016E118(1);
        self->vt->m15(self);
        D_0026F138.vt->m15(&D_0026F138);
    }
    self->open = v;
}

struct Frame_168B68 : V24A0 { s32 value; u8 pad[0x3F0]; };

extern s32 D_002626CC;
extern s32 D_00261F1C;

void func_001611B8(V24A0* f);
void func_001683B8(void);
void func_001529C8(V24A0* f, s32 n, s32* p);
void func_00152B38(V24A0* f);
void func_0019DDA0(f32 x, f32 y, f32 z, f32 w, s32 a, s32 b, s32 c, s32 d, Frame_168B68* e);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161708(V24A0* f, s32 a, u64 b);
void func_00161200(V24A0* f);
void func_00152D30(V24A0* f);
void func_001529E0(V24A0* f, s32 a, s32 b);
void func_001686E8(s32 a, s32* b);
void func_001683E8(void);

void func_00168B68(f32 t)
{
    Frame_168B68 f;
    s32 i = 0;
    s32 n;

    func_001611B8(&f);
    n = (s32)(t * 59.999996f);
    func_001683B8();
    D_002626CC = 0;
    if (n > 0) {
        do {
            f32 x = ((f32)i + 1.0f) / (f32)n;
            f32 y = x * 255.0f;
            s32 v = (s32)(x * y);
            i++;
            func_001529C8(&f, 0x40, &f.value);
            func_00152B38(&f);
            func_0019DDA0(0.0f, 0.0f, 640.0f, 492.80002f, 0, 0, 0, v, &f);
            func_001613C0(&f, 0, 1, 0xE);
            func_00161708(&f, 0x61, 0);
            func_00161200(&f);
            func_00152D30(&f);
            func_001529E0(&f, 0, 0);
            func_001686E8(D_00261F1C, &f.value);
            func_001683E8();
        } while (i < n);
    }
}

extern s32 D_00274500;
extern s32 D_00274508;
s32 func_00168D88(void* self, s32 size);
void func_00168E78(V24A2_ImgB* e, s32 v);
void func_00168F48(V24A2_ImgB* e, s32 v, void* ctx);
void func_00152B80(void* self, s32 lo, s32 hi);
void func_00168FB0(V24A2_ImgA* e, s32 v);
void func_00169088(V24A2_ImgA* e, s32 v, void* ctx);

s32 func_001690C0(s32 mask, BumpAllocator* b, V24A0* c)
{
    s32 saved;

    if (c != 0) {
        saved = c->curS;
    } else {
        saved = 0;
    }
    for (s32 i = 0; i < D_00274508; i++) {
        V24A2_ImgB* e = &D_0027450C[i];
        if ((e->f0 & mask) == mask) {
            s32 v = func_00168D88(b, e->f6);
            func_00168E78(e, v);
            if (c != 0) {
                func_00168F48(e, v, c);
                func_00152B80(c, e->fC, e->f8);
            }
        }
    }
    if ((b->next & 0x7F) != 0) {
        func_00168D88(b, 0x80 - (b->next & 0x7F));
    }
    for (s32 i = 0; i < D_00274500; i++) {
        V24A2_ImgA* e = &D_00274504[i];
        if ((e->f4 & mask) == mask) {
            s32 v;
            if (e->f8 == 0 && (b->next & 0x1F) != 0) {
                func_00168D88(b, 0x20 - (b->next & 0x1F));
            }
            v = func_00168D88(b, e->f0A);
            func_00168FB0(e, v);
            if (c != 0) {
                func_00169088(e, v, c);
                func_00152B80(c, e->f14, e->f10);
            }
        }
    }
    if (c == 0) {
        return 0;
    }
    return (c->curS ^ saved) != 0;
}

struct Obj_16B190 {
    u8 pad0[0x2D0];
    s32 f2D0;
    u8 pad1[0x24];
    void* f2F8;
    u8 pad2[4];
    s32 f300;
    u8 pad3[0x20];
    void* table[1];
};

struct Rec_16B190 {
    s32 f0;
    s32 f4;
    u8 pad[0x14];
    s32 f1C;
};

struct Tab_16B300 { s32 a; s32 b; };
extern Tab_16B300 D_00262860[6];
extern u8 D_00275BC0[];

void* func_00160180(s32 key);
void func_00160340(s32 idx);
void func_0012C7B0(void* a, void* b, s32 c, s32 d, f32 fa, f32 fb);
s32 func_0012C9A8(void* a);
void func_001F0428(void* a, s32 b, s32 c);
void func_001E9570(void* p);
void func_001B64D8(void* a, s32 b);
void func_0016B300(void* self, s32 idx, s32 flag);

void func_0016B190(Obj_16B190* self)
{
    s32 callB = 1;
    s32 idx = self->f2D0;
    if (idx != 0) {
        if ((D_002623C0->levels[idx].f448 & 1) == 0) {
        if (idx != self->f300) {
            s32 s2 = 1;
            void* elt;
            u8* table = (u8*)self + 0x324;
            func_00160340(idx);
            elt = *(void**)(table + (self->f2D0 << 2));
            if (elt != 0) {
                func_0012C7B0(elt, self, 0, 0, 0.0f, 1.0f);
                elt = *(void**)(table + (self->f2D0 << 2));
                if (elt != 0 && func_0012C9A8(elt) != 0) {
                    goto tail;
                }
            }
            {
                Rec_16B190* a = (Rec_16B190*)func_00160180(self->f2D0 << 8);
                s32 flag = 0;
                if (a != 0) {
                    flag = (a->f4 != a->f1C);
                }
                if (flag) {
                    func_001F0428(a, -1, 1);
                } else {
                    s2 = 0;
                }
            }
        tail:
            if (s2) {
                func_001E9570(D_00275BC0);
            }
        } else {
            void* h = self->f2F8;
            callB = 0;
            if (h != 0) {
                { func_001B64D8(h, D_00262860[idx].b); }
            }
        }
        }
    }
    if (callB) {
        func_0016B300(self, self->f2D0, 1);
    }
}

void func_0016E0F0(s32 n);
void func_0016E118(s32 n);
void func_0016EC88(void* p);
s32 func_0016BB78(s32 n);

void func_0016BDD0(T217D_1330* self, s32 flag)
{
    if ((flag != 0) != (self->open == 0)) {
        return;
    }
    if (flag != 0) {
        s32 bit = 15;
        func_0016E0F0(1);
        func_0016EC88(&D_00262C70);
        self->vt->m14(self);
        s32 mask = func_0016BB78(15);
        G27C220* g = D_002623C0;
        for (; bit > 0; bit--) {
            if (g->u19F4 & mask) {
                break;
            }
            mask >>= 1;
        }
        self->cursor = bit;
    } else {
        func_0016E118(1);
        self->vt->m15(self);
    }
    self->open = flag;
}

void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, u64 b);

void func_00169B18(TextureHeader* src, void* dst)
{
    s32 w = 1 << (s32)((src->tex0 >> 26) & 0xF);
    s32 cap = 64;
    if (cap < w) cap = w;
    s32 f = (s32)(src->tex0 & 0x3FFF) >> 5;
    s32 m = 1 << (s32)((src->tex0 >> 30) & 0xF);
    func_001613C0(dst, 0x200, 1, 0xE);
    func_00161708(dst, 0x4D, (u64)(cap / 64) << 16 | (u64)f);
    func_00161708(dst, 0x4F, 0x30000000 | (u64)f | (u64)0x8000 << 17);
    func_00161708(dst, 0x19, 0);
    func_00161708(dst, 0x41, (u64)(w - 1) << 16 | (u64)(m - 1) << 48);
    func_00161708(dst, 0x48, 0x31001);
    func_00161708(dst, 0x43, 0x44);
}

struct Bits_168E78 {
    u64 lo : 20;
    u64 f20 : 6;
    u64 mid : 11;
    u64 f37 : 14;
    u64 r51 : 4;
    u64 r55 : 1;
    u64 r56 : 5;
    u64 f61 : 3;
};

void func_00168E78(V24A2_ImgB* self, u32 a1){
 Bits_168E78* bits = (Bits_168E78*)&self->f10;
 bits->f37 = a1;
 bits->f20 = (self->f4 <= 0x10) ? 0x14 : 0x13;
 bits->r51=0; bits->r55=0; bits->r56=0; bits->f61=1;}

void* func_001300E8(void* node, s32 flags);

struct Walk_16A758 {
    List01* iter;
    void* cursor;
    s32 link;
    void* prev;

    Walk_16A758(List01* i)
    {
        cursor = i;
        iter = i;
        link = i->offset;
        prev = D_0027B314;
        D_0027B314 = (ListFrame*)this;
    }
    ~Walk_16A758() { D_0027B314 = (ListFrame*)prev; }
    void* First()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
};

s32 func_0016A758(u8* self)
{
    Walk_16A758 w((List01*)(self + 0x34));
    s32 count = 0;
    void* node = w.First();
    while (node != 0) {
        if (func_001300E8(node, 70)) {
            s32 x = *(s32*)((u8*)node + 0x550);
            if (1 < (u32)(x - 3)) {
            } else {
                count++;
            }
        }
        node = w.Next();
    }
    return count;
}

void func_00182C18(void* self);

void func_00169CD8(C6F* self)
{
    func_00182C18(self);
    self->id44 = -1;
    self->f4C = 1;
    self->f50 = 3;
    self->f58 = D_0024A794;
}

struct __attribute__((aligned(16))) Quad_169FC0 { s32 v[4]; };

struct Frame_169FC0 {
    Quad_169FC0 a;
    Quad_169FC0 b;
    s32 c;
    u8 pad[0xC];
    f32 x;
};

struct Obj_169FC0 {
    void** vt;
    u8 pad4[4];
    s32 f8;
};

struct Self_169FC0 {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1[0x34 - 0x1C];
    Obj_169FC0* f34;
};

void* func_001925F0(void);
s32 func_00128018(void* a, s32 b, void* c, void* d);
void func_001280C0(void* a, s32 b, void* c, void* d);
void func_00169E20(void* a0, void* a1, void* a2, f32 f);

void func_00169FC0(Self_169FC0* self, f32* out, void* a2, void* a3)
{
    Frame_169FC0 f;
    u8* node = (u8*)func_001925F0();
    Obj_169FC0* o = self->f34;
    f.c = 1;
    func_00128018(0, self->f18, node + 0x140, &f.a);
    func_001280C0(0, self->f18, (void*)&D_00248D20, &f.b);
    if (o->vt[10] != 0) {
        ((void (*)(void*, void*, void*, s32, s32, s32, void*))o->vt[10])(o, &f.a, &f.b, 0, 0, 0, &f.x);
    }
    if (o->f8 == 0) {
        f32 k = 30.0f;
        f32 t = ((f32 (*)(void*))self->f34->vt[8])(self->f34) - k;
        f32 r = f.x;
        if (r < k) {
            r = k;
        } else if (t < r) {
            r = t;
        }
        f.x = r;
    }
    func_00169E20(self, a2, a3, f.x);
    *out = f.x;
}

typedef void (*VFn_16A5F0)(void* self, void* a);

struct Obj_16A5F0 {
    VFn_16A5F0* vtbl;
    u8 pad4[0x224 - 4];
    s32 f224;
    u8 pad228[0x550 - 0x228];
    s32 f550;
    f32 f554;
};

struct Frame_16A5F0 {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    u8 e[0x10];
};

extern f32 D_0026185C[];

void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
void func_001837E0(void* obj, s32 kind, s32 a, s32 b);
void func_00189378(void* sub, void* a, void* out);
void func_00188D28(void* a, void* b, void* c);
void func_00189150(void* a, void* b, s32 c);

void func_0016A5F0(Obj_16A5F0* self, s32 v)
{
    Frame_16A5F0 f;

    if (self->f550 == v) {
        return;
    }
    if (self->f550 == 1) {
        self->vtbl[25](self, 0);
        func_001B9AE0(self, 0, 0, 0, 0);
        func_001837E0(self, 3, 0, 0);
    }
    if (v == 1) {
        self->vtbl[25](self, D_00262E10);
        self->vtbl[36](self, (void*)&D_00248D30);
        self->vtbl[37](self, (void*)&D_00248D30);
        func_001B9AE0(self, 3, 0, 3, 0);
        func_00189378((u8*)D_00262E10 + 0x110, 0, f.a);
        func_00189378((u8*)self + 0x110, f.c, f.b);
        func_00188D28(f.c, f.e, f.d);
        func_00189150(f.a, f.b, self->f224);
        func_001837E0(self, 2, 0, 0);
    }
    self->f550 = v;
    self->f554 = D_0026185C[0];
}

void* func_001300E8(void* node, s32 flags);

struct Walk_16A820 {
    List01* iter;
    void* cursor;
    s32 link;
    void* prev;

    Walk_16A820(List01* i)
    {
        cursor = i;
        iter = i;
        link = i->offset;
        prev = D_0027B314;
        D_0027B314 = (ListFrame*)this;
    }
    ~Walk_16A820() { D_0027B314 = (ListFrame*)prev; }
    void* First()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
};

struct Node_16A820 {
    u8 pad0[0x550];
    s32 f550;
    f32 f554;
};

void* func_0016A820(u8* self)
{
    Walk_16A820 w((List01*)(self + 0x34));
    void* best = 0;
    f32 bestF = D_0024A79C;
    void* node = w.First();
    while (node != 0) {
        if (func_001300E8(node, 0x46)) {
            Node_16A820* n = (Node_16A820*)node;
            if (n->f550 == 4 && n->f554 < bestF) {
                best = node;
                bestF = n->f554;
            }
        }
        node = w.Next();
    }
    return best;
}

struct Pair_16AF80 {
    u8 pad0[0x28];
    s32 f28;
    u8 pad1[4];
    s32 f30;
};

struct Ctx_16AF80 {
    u8 pad0[0x2D0];
    s32 f2D0;
    u8 pad1[0xC];
    Pair_16AF80* f2E0;
    u8 pad2[0x1C];
    s32 f300;
};

void func_001AD1E8(T217D_3D0* self);

void func_0016AF80(Ctx_16AF80* self)
{
    s32 s1 = 0;
    Pair_16AF80* p = self->f2E0;

    if (p->f28 != p->f30) {
        D_0026F138.vt->m08(&D_0026F138, "");
    } else if (self->f2D0 == 0) {
        D_0026F138.vt->m08(&D_0026F138, D_0024A7A8);
    } else {
        s32 flags = D_002623C0->levels[self->f2D0].f448;
        if (flags & 1) {
            func_001AD1E8(&D_0026F138);
        } else if (self->f2D0 == self->f300) {
            D_0026F138.vt->m08(&D_0026F138, D_0024A7B0);
        } else {
            s1 = 1;
            D_0026F138.vt->m08(&D_0026F138, "");
        }
    }

    func_001AA8B8(&D_0026F138, 0.0f);
    D_0026F138.announce = 0;
    D_0026F138.vt->m14(&D_0026F138);

    if (s1 != 0) {
        D_0026FA90.vt->m08(&D_0026FA90, D_0024A7B8);
        D_0026FA90.vt->m14(&D_0026FA90);
    } else {
        D_0026FA90.vt->m15(&D_0026FA90);
    }
}

extern s32 D_002BE460;
extern s32 D_002BE46C;
struct Arg_001683B8;
void func_001F6B60(Arg_001683B8* a);

void func_001683B8(void) {
    D_002BE46C = 1;
    func_001F6B60((Arg_001683B8*)D_002BE460);
}

struct Dst_1694A0 {
    s32 f0;
    u8 pad0[0xC];
    s32 f10;
};

struct Rec_1694A0 {
    s32 f0;
    s32 f4;
    Dst_1694A0* f8;
    s32 fC;
};

void func_0018D800(Dst_1694A0* dst, void* src, s32 count);

void func_001694A0(Rec_1694A0* self)
{
    func_0018D800(self->f8, (void*)self->f4, self->f0);
    s32 flag = self->fC;
    if (flag != 0) {
        Dst_1694A0* d = self->f8;
        s32 a = d->f0;
        s32 b = d->f10;
        a = a | 0x8000;
        a = a | flag;
        b = b | 0x8000;
        d->f0 = a;
        d->f10 = b;
    }
}

extern s32 D_002BE468;
extern s32 D_002BE464;

struct Self_1686E8 {
    u8 pad0[4];
};

s32 func_00202120(void);
s32 func_00202058(s32 a);
void func_001F6C20(s32 a);
void func_00202A80(Self_1686E8* a, void* b);
void func_001F6B60(s32 a);

void func_001686E8(Self_1686E8* self, void* b)
{
    D_002BE468 = 1;
    *(volatile u64*)0x12001000 |= 2;
    s32 r = func_00202120();
    func_00202058(r & -0x201);
    func_001F6C20(0);
    func_00202A80(self, b);
    func_001F6B60(D_002BE464);
}

extern const f32 D_0024A798 = 3.4028235e+38f;

void func_0016A100(C7F* self)
{
    func_00182C18(self);
    f32 k = D_0024A798;
    self->targetId = -1;
    self->f68 = 1;
    self->f70 = k;
}

void func_001BAC30(C03* self);
void* func_0018D5C0(s32 bytes);

void func_0016A420(ListedCollisionPart* self)
{
    Rec2195_224* b;
    Quad16* dst;
    Quad16* src;

    func_001BAC30(self);
    if (self->f224 == 0) {
        self->f224 = (Rec2195_224*)func_0018D5C0(0xC0);

    }
    b = self->f224;
    b->fB0 |= 1;
    dst = (Quad16*)self->f224;
    src = (Quad16*)&D_002483D0;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

void func_001B9338(C03* self, f32 t);
void func_00189378(Mat02* sub, s32 zero, Mat3U* out);
void func_001B91A8(C03* self, Mat3U* out, s32 a, void* table, s32 b, f32 t);

void func_0016A580(ListedCollisionPart* self, f32 t)
{
    Mat3U buf;

    func_001B9338(self, t);
    if (self->f550 != 0) {
        return;
    }
    func_00189378((Mat02*)((u8*)self + 0xD0), 0, &buf);
    func_001B91A8(self, &buf, (s32)self->p214, (void*)&D_00248D30, (s32)self->p218, t);
}

// NEAR: only the order of `addiu v0,s5,lo(D_00261858)` vs `sw s4,0x2D4(s3)` differs (2 instrs swapped)

struct Slot_16B300 { u8 pad[0x20]; };
struct Slot_262890 { u32 w[8]; };
extern Slot_262890 D_00262890[6];
extern Slot_262890 D_00262950;
struct Self_16B300 {
    u8 pad0[0x2D0]; s32 f2D0; s32 f2D4; f32 f2D8; u8 pad1[4]; void* f2E0;
    u8 pad2[0x300 - 0x2E4]; s32 f300;
};

extern f32 D_00261858[];
extern f32 D_00262970;
extern s32 D_0026FCF4;
void func_001BE728(Slot_16B300* s);
s32 func_001BE980(void);
void func_001B6628(void* h, s32 arg);
void func_001B64D8(void* h, s32 arg);

void func_0016B300(Self_16B300* self, s32 a, s32 b)
{
    if (a == self->f2D0 && b == self->f2D4) return;
    if (a != self->f300 && a > 0) {
        Slot_16B300* slot = 0;
        if (D_002623C0->levels[a].f448 & 1) {
            s32 fl = D_002623C0->f19EC;
            if (!(fl & 2)) {
                D_002623C0->f19EC = fl | 2;
                slot = (Slot_16B300*)&D_00262950;
            }
        } else {
            f32 t = D_00261858[1];
            if (D_00262970 <= t - D_0026FA90.lastAt) {
                D_0026FA90.lastAt = t;
                slot = (Slot_16B300*)((u8*)D_00262890 + (a << 5));
            }
        }
        if (slot) {
            func_001BE728(slot);
            D_0026FCF4 = func_001BE980();
        }
    }
    void* h = self->f2E0;
    if (h) {
        if (self->f2D0 == -1) {
            if (a != 0) {
                func_001B6628(h, D_00262860[a].b);
                func_001B64D8(self->f2E0, D_00262860[a].a);
            }
        } else {
            func_001B64D8(h, *(s32*)((u8*)D_00262860 + (a * 8 + b * 4)));
        }
    }
    self->f2D0 = a;
    self->f2D4 = b;
    self->f2D8 = D_00261858[1];
}

struct Sub_16B580 { u8 pad0[0x28]; s32 f28; s32 f2C; s32 f30; };
// The object the element shows (a view of it: its mode at +0x2D0, its animation clock at +0x2D8).
struct Obj_16B580 {
    u8 pad0[0x2D0];
    s32 f2D0;
    s32 f2D4;
    f32 f2D8;
    u8 pad2DC[4];
    Sub_16B580* f2E0;
    u8 pad2E4[0x308 - 0x2E4];
    void* f308;
    u8 pad30C[0x33C - 0x30C];
    void* f33C;
};

extern s32 D_00272420;
extern f32 D_0026185C[];
extern u8 D_00264A40[];
extern u8 D_00275BC0[];

s32 func_001BE810(void);
s32 func_0011CE30(void);
s32 func_001BE980(void);
void func_0018C7F8(u8* p);
void func_001518B8(void* p);
void func_0016AF80(Obj_16B580* o);
void func_001E9498(u8* a, void* b);
void func_0016EC20(G262C70* a, s32 mask);
void func_00194D30(T217D_6D0* a, s32 b, s32 c);
void func_0016B190(Obj_16B580* o);
void func_0016B0F8(Obj_16B580* o, G262C70* a);

void func_0016B580(T217D_12E0* self, G262C70* arg)
{
    if (self->node == 0) {
        return;
    }
    if (((Obj_16B580*)self->node)->f2E0 == 0) {
        return;
    }
    if (self->sound != 0) {
        if (func_001BE810() != 0) {
            func_0011CE30();
        }
        self->sound = func_001BE980();
    }
    if (D_00272420 != 0) {
        return;
    }
    if (D_0027051C != 0) {
        return;
    }
    Obj_16B580* o = (Obj_16B580*)self->node;
    Sub_16B580* p = o->f2E0;
    if (o->f308 != 0) {
        if (o->f308 == o->f33C) {
            func_0018C7F8(D_00264A40);
        }
        func_001518B8(o->f308);
        o->f308 = 0;
    }
    func_0016AF80(o);
    f32 delay = 0.3f;
    if (o->f2D4 == 1 && (p->f28 == p->f30 || delay <= D_0026185C[0] - o->f2D8)) {
        s32 idx = o->f2D0;
        if (idx == 0) {
            if (D_0026FD00.mode != 0) {
                return;
            }
            func_001E9498(D_00275BC0, &D_0026FD00);
            return;
        }
        if (D_0026F808.mode != 0) {
            return;
        }
        D_0026F808.current = D_0026F808.nodes[idx];
        func_001E9498(D_00275BC0, &D_0026F808);
        return;
    }
    if (p->f28 != p->f30) {
        return;
    }
    if ((arg->flags & 0x800) || (arg->f14 == 1 && 5.0f <= D_0026185C[0])) {
        func_0016EC20(arg, 0x800);
        func_00194D30(&D_0026FF68, 0, 0x17);
        return;
    }
    if ((arg->flags & 0x140) != 0) {
        func_0016EC20(arg, 0x140);
        func_0016B190(o);
        return;
    }
    func_0016B0F8(o, arg);
}

extern s32 D_00262988[];
extern f32 D_00262970;
s32 func_0015C188(s32 index);
V24A2* func_0015C1C0(s32 index);

void func_0016B4A0(T217D_12E0* self)
{
    func_001AA268(self);
    if (func_0015C188(2)) {
        self->frame = (V24A2**)D_00262988;
        *self->frame = func_0015C1C0(2);
    }
    func_001AA8B8(self, 0.0f);
    self->node = 0;
    *(u32*)self->rgba.c = 0xDF7F7F7F;
    self->sound = 0;
    self->lastAt = -D_00262970;
}

struct Dbp_168F48 { s32 v; };

void func_00168D98(Dbp_168F48 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void func_00168F48(V24A2_ImgB* e, s32 v, void* ctx)
{
    s32 step = (e->f4 > 16) ? 16 : 8;
    s32 n = e->f4 - 1;
    Dbp_168F48 p;
    p.v = v;
    func_00168D98(p, 1, 0, step, ((n + step) & -step) / step, e->fC, ctx);
}

void func_001611B8(V24A0* f);
void func_001529C8(V24A0* f, s32 n, V24A0* p);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161200(V24A0* f);

void func_00168770(V24A0* self, u8* color, s32 flag)
{
    V24A0 f;
    s32 x;

    func_001611B8(&f);
    func_001529C8(&f, 0x2C, self);
    func_001613C0(&f, (s8)color[3] >= 0 ? 0x46 : 6, 1, 0xE);
    func_00161708(&f, 1, (u64)color[0] | ((u64)color[1] << 8) | ((u64)color[2] << 16) | ((u64)color[3] << 24));
    func_00161708(&f, 0x47, flag != 0 ? 0x32001 : 0x32000);
    for (x = 0; x < 0x280; x += 0x20) {
        func_00161708(&f, 5, (u64)((0x6C0 + x) << 4) | ((u64)(0x790 << 4) << 16));
        func_00161708(&f, 5, (u64)((0x6E0 + x) << 4) | ((u64)(0x870 << 4) << 16));
    }
    func_00161708(&f, 0x47, 0x70000);
    func_00161200(&f);
}

extern u8 D_002629A8[];

s32 func_0015C188(s32 k);
void func_0015C8B8(V24A2* font, f32 x, f32 y);
void func_0015C900(V24A2* font);

void func_0016BA40(T217D_1330* self)
{
    func_001AA268(self);
    if (func_0015C188(2)) {
        self->frame = (V24A2**)D_002629A8;
        *self->frame = func_0015C1C0(2);
    }
    V24A2* a1 = self->font;
    f32 f20 = 60.0f;
    f32 f21 = 90.0f;
    const V24A2_Vt* vt = a1->vt;
    V24A2* n = vt->clone((V24A2*)((u8*)a1 + vt->adj1), 1.0f, 1.0f);
    self->font = n;
    self->color = 0xDF7F7F7F;
    f20 = (f32)n->height * n->sy + f20;
    V24A2* s0 = func_0015C1C0(4);
    func_0015C8B8(s0, 1.3f, 1.3f);
    const V24A2_Vt* v = s0->vt;
    f32 r = v->width((V24A2*)((u8*)s0 + v->adj3), 0x5F);
    f21 = r * 4.0f + f21;
    f20 = f20 + (f32)s0->height * s0->sy * 4.0f;
    func_0015C900(s0);
    func_001AAB20(self, f21, f20);
}

struct Pm_168130 { u32 en1 : 1; u32 rest : 31; u32 hi : 32; };
struct Fb_168130 { u32 fbp : 9; u32 fbw : 6; u32 psm : 5; u32 pad0 : 12; u32 dbx : 11; u32 dby : 11; u32 pad1 : 10; };
struct Disp_168130 { u32 dx : 12; u32 dy : 11; u32 magh : 4; u32 magv : 2; u32 pad0 : 3; u32 dw : 12; u32 dh : 11; u32 pad1 : 9; };
struct Rec_168130 { Pm_168130 pmode; u64 pad; Fb_168130 dispfb; Disp_168130 display; u64 pad2; };
struct Gs_168130 {
    Pm_168130 pmode; u8 pad0[0x70 - 8];
    Fb_168130 dispfb2; u8 pad1[8];
    Disp_168130 display2; u8 pad2[0x1000 - 0x88];
    u32 csr;
};

extern s32 D_002626C0;
extern s32 D_002626C8;

void func_00168130(void)
{
    s32 i = D_002626C0 & 1;
    s32 field = D_002626C8;
    Pm_168130 pm = ((Rec_168130*)&D_00262490)[i].pmode;

    if (field != (s32)((((Gs_168130*)0x12000000)->csr >> 13) & 1)) {
        Disp_168130 d = ((Rec_168130*)&D_00262490)[i].display;
        Fb_168130 fb = ((Rec_168130*)&D_00262490)[i].dispfb;
        d.dh = d.dh - 1;
        if (field != 0) {
            d.dy = d.dy + 1;
        } else {
            fb.dby = fb.dby + 1;
        }
        ((Gs_168130*)0x12000000)->display2 = d;
        ((Gs_168130*)0x12000000)->dispfb2 = fb;
        pm.en1 = 1;
    }
    ((Gs_168130*)0x12000000)->pmode = pm;
}

struct Out_16B860;
void func_00137228(Out_16B860* out, f32 x, f32 y);
void func_00137238(Out_16B860* out, f32 x, f32 y);
void func_00137248(Out_16B860* out, s32* value);
void func_00137260(Out_16B860* out, s32 flag);
void func_00137268(Out_16B860* out, s32 flag);
struct Out_16B860 {
    u8 b[32];
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};
struct Hd_16B860 {
    static void Draw(V24A2** h, Out_16B860* out, void* tbl)
    {
        if (*h != 0) {
            const V24A2_Vt* vt = (*h)->vt;
            vt->drawBox((V24A2*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};

extern f32 D_00261868;
f32 func_00205400(f32 x);
void func_0015C8B8(V24A2* font, f32 a, f32 b);
void func_0015DB28(void* out, void* p, V24A2* font);
void func_0015E318(void* a, void* b, s32 c, void* d);
void func_0015C900(V24A2* font);

void func_0016B860(T217D_12E0* self)
{
    T217D_Word tmp;
    Out_16B860 out;
    T217D_Word slot;
    u8 loc[0xB0];

    if (self->node != 0 && self->text[0] != 0) {
        tmp = self->colorWord;
        ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->blend);
        f32 p = self->w;
        f32 q = self->h;
        s32 held = tmp.v;
        out.Pos(self->x, self->y);
        out.Size(p, q);
        slot.v = held;
        out.Color(&slot.v);
        out.FlagA(1);
        out.FlagB(1);

        u8* h = (u8*)self->frame;
        if (h != 0) {
            slot = *(T217D_Word*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->blend);
            Hd_16B860::Draw(self->frame, &out, &D_00262280);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
        f32 r = func_00205400(D_00261868 * 10.0f);
        f32 t = r * 0.5f + 0.5f;
        f32 k = (1.0f - t) * 0.9f + t;
        f32 v = self->scale * k;
        func_0015C8B8(self->font, v, v);
        func_0015DB28(loc, &self->text[0], self->font);
        func_0015E318(loc, &out, 0, &D_00262280);
        func_0015C900(self->font);
    }
}

extern s32 D_00274508;
extern s32 D_00274500;
extern s32 D_00274514;
extern s32 D_00274510;

void func_00168D68(BumpAllocator* p, s32 a, s32 b);
void func_001611B8(V24A0* f);
void func_001EE318(V24A0* f);
void func_0018D608(void);
void func_00152980(V24A0* f, s32 size);
void func_00152B38(V24A0* f);
void func_001EE450(V24A0* f);
void func_001528E0(V24A0* f);
void func_001529C8(V24A0* f, s32 n, u8* buf);
s32 func_00168D88(BumpAllocator* p, s32 size);
void func_00168E78(V24A2_ImgB* e, s32 v);
void func_00168F48(V24A2_ImgB* e, s32 v, V24A0* f);
void func_00168FB0(V24A2_ImgA* e, s32 v);
void func_00169088(V24A2_ImgA* e, s32 v, V24A0* f);
void func_001529E0(V24A0* f, s32* o0, s32* o1);
void func_001EE7D0(V24A0* f, s32 a, s32 b, s32 c);
void func_001EE850(V24A0* f, s32 a, s32 b, s32 c);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161708(V24A0* f, s32 a, u64 b);
void func_00161200(V24A0* f);
void func_00152D70(V24A0* f);
void func_00152A50(V24A0* f, s32 a, s32 b, s32* out, s32 c);
void func_001B3510(u32 mask);
void func_0018D6F0(void);

s32 func_00169780(u32 mask)
{
    BumpAllocator span;
    V24A0 fa;
    V24A0 fb;
    u8 buf[0xA0];
    s32 o0;
    s32 o1;
    s32 res;
    s32 i;

    func_00168D68(&span, 0x1400, 0x1E00);
    func_001611B8(&fa);
    res = 0;
    func_001EE318(&fb);
    func_0018D608();
    func_00152980(&fb, (D_00274514 * 2 + D_00274514 + D_00274510) * 10 + 4);
    func_00152B38(&fb);
    func_001EE450(&fb);
    for (i = 0; i < D_00274508; i++) {
        V24A2_ImgB* e = (V24A2_ImgB*)((*(u8**)&D_0027450C) + i * 0x18);
        if ((e->f0 & mask) == mask) {
            func_001528E0(&fa);
            func_001529C8(&fa, 0xA, buf);
            s32 n = func_00168D88(&span, e->f6);
            func_00168E78(e, n);
            func_00168F48(e, n, &fa);
            *(u64*)(fa.curS - 0x10) |= 0x8000;
            func_001529E0(&fa, &o0, &o1);
            func_001EE7D0(&fb, o0, o1, 0);
            func_001EE850(&fb, e->fC, e->f8, 0);
            if (e->f0 & 0x40000000) {
                e->f0 = 0x40000000;
            }
        }
    }
    if (D_00274500 > 0) {
        i = 0;
        do {
            V24A2_ImgA* e = (V24A2_ImgA*)((*(u8**)&D_00274504) + i * 0x20);
            if ((e->f4 & mask) == mask) {
                func_001528E0(&fa);
                func_001529C8(&fa, 0xA, buf);
                s32 n = func_00168D88(&span, e->f0A);
                func_00168FB0(e, n);
                func_00169088(e, n, &fa);
                *(u64*)(fa.curS - 0x10) |= 0x8000;
                func_001529E0(&fa, &o0, &o1);
                func_001EE7D0(&fb, o0, o1, 0);
                func_001EE850(&fb, e->f14, e->f10, 0);
                if (e->f4 & 0x40000000) {
                    e->f4 = 0x40000000;
                }
            }
            i++;
        } while (i < D_00274500);
    }
    if (span.next > span.start) {
        func_001528E0(&fa);
        func_001529C8(&fa, 0xA, buf);
        func_001613C0(&fa, 0, 1, 0xE);
        func_00161708(&fa, 0x3F, 0);
        func_00161200(&fa);
        func_001529E0(&fa, &o0, &o1);
        func_001EE7D0(&fb, o0, o1, 0);
        func_001EE450(&fb);
        func_00152D70(&fb);
        *(u64*)fb.curS = 0x60000000;
        fb.curS += 0x10;
        func_00152A50(&fb, 0, 0, &res, 7);
        func_001B3510(mask);
    }
    func_0018D6F0();
    return res;
}

struct Cand_16AB38 {
    u8 pad[0x304];
    s32* flagp;
};
struct Pair_16AB38 {
    C2F* src;
    C2F* dst;
};
struct Self_16AB38 {
    u8 pad0[0x2DC];
    Pair_16AB38 p[4];
    s32 cur;
    s32 sel;
    u8 pad1[4];
    Cand_16AB38* chosen;
    u8 pad2[4];
    C2F* objs[5];
    u8 pad3[0x18];
    Cand_16AB38* cands[4];
};
struct SelEnt_16AB38 {
    s32 id;
    s32 pad;
};

extern s32 D_002623CC;
extern u8 D_00275BC0[];

C2F* func_001B6290(C2F* o, s32 a, s32 b, s32 c);
s32 func_001602A0();
void func_0016B300(Self_16AB38* self, s32 idx, s32 z);
void func_001B6628(C2F* o, s32 id);
void func_001E9498(u8* a, u8* b);

void func_0016AB38(Self_16AB38* self)
{
    if (self->p[0].src) self->p[0].dst = func_001B6290(self->p[0].src, 0, -1, 0);
    if (self->p[1].src) self->p[1].dst = func_001B6290(self->p[1].src, 0, -1, 0);
    if (self->p[2].src) self->p[2].dst = func_001B6290(self->p[2].src, 0, -1, 0);
    if (self->p[3].src) self->p[3].dst = func_001B6290(self->p[3].src, 0, -1, 1);
    self->cur = 5;
    for (;;) {
        s32 c = self->cur;
        if (c < 3) break;
        if (D_002623C0->levels[c - 2].f448 & 0x20) break;
        s32 d = c - 1;
        if (D_002623C0->levels[d].f448 & 1) break;
        self->cur = d;
    }
    for (s32 i = 1; i <= self->cur; i++) {
        C2F* o = self->objs[i - 1];
        if (o && (D_002623C0->levels[i].f448 & 1)) o->desc->m02(o);
    }
    self->chosen = 0;
    for (s32 i = 0; i < 4; i++) {
        Cand_16AB38* c = self->cands[i];
        if (c && *c->flagp == 0) {
            s32 v = 0;
            switch (i) {
            case 0: v = 1; break;
            case 1: v = func_001602A0() >> 1; goto mask;
            case 2: v = func_001602A0() >> 2; goto mask;
            case 3: v = func_001602A0() >> 3;
            mask: v &= 1; break;
            default: break;
            }
            if (v) {
                self->chosen = c;
                break;
            }
        }
    }
    s32 idx;
    if (self->chosen) {
        idx = 0;
    } else {
        s32 a = D_002623CC;
        if (a != -1 && (D_002623C0->levels[a].f448 & 1)) {
            idx = a;
        } else {
            s32 c = self->cur;
            if ((D_002623C0->levels[c - 1].f448 & 1) == 0) {
                idx = c - 2;
            } else if ((D_002623C0->levels[c].f448 & 1) == 0) {
                idx = c - 1;
            } else {
                idx = c;
            }
        }
    }
    func_0016B300(self, idx, 0);
    if (self->p[2].dst || self->p[3].dst) {
        idx = self->cur;
        if (idx != 5) {
            self->sel = idx;
        } else {
            G27C220* t = D_002623C0;
            if (t->levels[4].f448 & 0x20) self->sel = 0;
            else if (t->levels[5].f448 & 1) self->sel = 0;
            else self->sel = idx;
        }
        if (self->p[2].dst) func_001B6628(self->p[2].dst, ((SelEnt_16AB38*)&D_00262860)[self->sel].id);
        if (self->p[3].dst) func_001B6628(self->p[3].dst, ((SelEnt_16AB38*)&D_00262860)[self->sel].id);
    }
    func_001E9498(D_00275BC0, (u8*)&D_0026FA90);
}

struct Tag_16BBA8;
struct Bits_16BBA8;
struct Group_16BBA8;

extern u8 D_00275BC0[];

void func_0016EC20(G262C70* self, s32 mask);
void func_001E9570(Group_16BBA8* g);
u32 func_0016BB78(Bits_16BBA8* bit);
void func_0018E4C0(Bits_16BBA8* bit);
void func_001BFCD8(Tag_16BBA8* a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 r2, s32 a5);
s32 func_0016EC98(G262C70* p);
s32 func_0016EED0(G262C70* p);

void func_0016BBA8(T217D_1330* ctx, G262C70* o)
{
    s32 s1;
    s32 r2;

    if ((o->flags & 0x9B0) != 0 || (o->f14 == 1 && 5.0f <= D_0026185C[0])) {
        func_0016EC20(o, 0x9B0);
        func_001E9570((Group_16BBA8*)D_00275BC0);
        return;
    }
    if ((o->flags & 0x40) != 0) {
        func_0016EC20(o, 0x40);
        if (func_0016BB78((Bits_16BBA8*)ctx->cursor) != 0) {
            func_0018E4C0((Bits_16BBA8*)ctx->cursor);
            return;
        }
        func_001BFCD8((Tag_16BBA8*)0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    s1 = func_0016EC98(o);
    r2 = func_0016EED0(o);
    if (s1 == 0 && r2 == 0) {
        return;
    }
    o->f30 = D_00261858[4] + o->f34;
    o->f38 = D_00261858[4] + o->f3C;

    {
        s32 n = ctx->cursor;
        s32 q = n / 4;
        s32 r = n % 4;
        if (s1 < 0 && r == 0)
            r2 = -1;
        if (s1 > 0 && r == 3)
            r2 = 1;
        s32 dy = r2 + 4;
        s32 dx = s1 + 4;
        q = (q + dy) % 4;
        r = (r + dx) % 4;
        ctx->cursor = q * 4 + r;
    }
    func_001BFCD8((Tag_16BBA8*)0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

s32 D_00262480 = 0xF;
u8 D_002624E0[16] = { 0 };
u8 D_002625D0[16] = { 0 };
Tab_262718 D_00262718 = {
    { { 2, 0x51A, 0x2D0 }, { 2, 0x51B, 0x2D4 }, { 2, 0x51C, 0x2D8 }, { 2, 0x51D, 0x2DC },
      { 2, 0x51E, 0x2E0 }, { 2, 0x51F, 0x2E4 }, { 2, 0x520, 0x2E8 }, { 2, 0x521, 0x2EC },
      { 2, 0x522, 0x2F0 } },
    0
};
Ent_262788 D_00262788[18] = {
    { 0, 0x4F9, 0x2DC }, { 0, 0x4FA, 0x2E4 }, { 0, 0x4FB, 0x2EC }, { 1, 0x4FC, 0x2F4 },
    { 0, 0x50B, 0x328 }, { 0, 0x50C, 0x32C }, { 0, 0x50D, 0x330 }, { 0, 0x50E, 0x334 },
    { 0, 0x50F, 0x338 }, { 1, 0x510, 0x310 }, { 1, 0x511, 0x314 }, { 1, 0x512, 0x318 },
    { 1, 0x513, 0x31C }, { 1, 0x514, 0x320 }, { 7, 0x33B, 0x33C }, { 7, 0x33C, 0x340 },
    { 7, 0x33D, 0x344 }, { 7, 0x33E, 0x348 }
};
Tab_16B300 D_00262860[6] = {
    { 0x4FF, 0x505 }, { 0x500, 0x506 }, { 0x501, 0x507 }, { 0x502, 0x508 }, { 0x503, 0x509 },
    { 0x504, 0x50A }
};
Slot_262890 D_00262890[6] = {
    { { 0, 0, 0, 0, 0, 0, 0, 0 } },
    { { 0x635DE216, 0x4EC49A4B, 0xE334472E, 0xCEF69512, 0x21FD26D6, 0x635CED13, 0xE33445A7, 0x4EC400FB } },
    { { 0x3FB4CB9D, 0xE4C59CDC, 0xB54DAA16, 0x74DAA291, 0x4E0ADF39, 0x3FB04A25, 0xB54DA89D, 0xE4C5FF1C } },
    { { 0x51EAF76B, 0xB417FD43, 0x999B48BC, 0xA609B70E, 0x7503D2C5, 0x51EAB865, 0x999B4A34, 0xB41790D3 } },
    { { 0xA46F3D2E, 0x368721CE, 0xF314B84E, 0x702E7249, 0x5011BB12, 0xA47BDDCC, 0xF314BAC4, 0x3687A2FE } },
    { { 0x4BEF3327, 0x61E51B24, 0x2E2955B0, 0xFEF61D5D, 0x4AC1B015, 0x4BE71C67, 0x2E29573C, 0x61E5EF04 } }
};
Slot_262890 D_00262950 = { { 0xAD5AA16C, 0xC4D11624, 0x183E0989, 0x9870DBBF, 0xC74A50B2, 0xAD59F526, 0x183E0BF2, 0xC4D06934 } };
extern const f32 D_0024A794 = 3.4028235e+38f;
extern const f32 D_0024A79C = 3.4028235e+38f;
extern const u32 D_0024A7A0[2] = { 0, 0 };
extern const char D_0024A7A8[8] = "Bentley";
extern const char D_0024A7B0[8] = "Murray";
extern const char D_0024A7B8[32] = "Press &2X&. to Start Mission!";
