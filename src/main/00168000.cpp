// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_00262708[];

void func_001B7B78(void* self);
void func_00152600(void* data, void* self);

void func_0016A4C8(void* self)
{
    func_001B7B78(self);
    func_00152600(D_00262708, self);
}

struct Packed_16A500 {
    u64 value;
} __attribute__((packed));

void func_001BA130(void* self);

void func_0016A500(u8* self)
{
    Packed_16A500 tmp = *(Packed_16A500*)(self + 0x558);
    func_001BA130(self);
    *(Packed_16A500*)(self + 0x558) = tmp;
}

extern void* D_00262E10;

struct Owner_16A548 {
    u8 pad0[0x23B0];
    void* field;
};

s32 func_001B8A08(void* a, void* b);

s32 func_0016A548(void* a0, Owner_16A548* a1)
{
    if (a1 == D_00262E10 && a0 == a1->field) {
        return 1;
    }
    return func_001B8A08(a0, a1);
}

extern void* D_00275710;

struct Obj_16B520 {
    u8 pad0[0x25C];
    s32 field25C;
};

void* func_0015A448(void* obj, s32 id, s32 flags);
void func_001F4ED0(void* p);

void func_0016B520(Obj_16B520* self)
{
    if (self->field25C != 0) {
        void* p = func_0015A448(D_00275710, 0x4FD, 0);
        if (p != 0) {
            func_001F4ED0(p);
        }
    }
}

void func_001AA298(void* self);

void func_0016B560(void* self)
{
    func_001AA298(self);
}

extern u8* D_002623C0;

u32 func_0016BB78(u32 bit)
{
    u32 mask;
    if (bit >= 16) {
        mask = 0;
    } else {
        mask = 1 << bit;
    }
    return *(u32*)(D_002623C0 + 0x19F4) & mask;
}

extern s32 D_002BE470;
extern s32 D_002626C0;
extern s32 D_002626C4;
extern s32 D_002626C8;
extern s32 D_002626CC;
extern s32 D_00262484;
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

struct Frame_1692B0 { u8 buf[0x30]; s32 value; };

extern s32 D_00274514;
extern s32 D_00274510;
extern s32 D_00261F1C;

void func_001611B8(Frame_1692B0* f);
void func_0018D608(void);
void func_00152980(Frame_1692B0* f, s32 size);
void func_00152B38(Frame_1692B0* f);
s32 func_001690C0(void* self, void* arg, Frame_1692B0* f);
void func_001613C0(Frame_1692B0* f, s32 a, s32 b, s32 c);
void func_00161708(Frame_1692B0* f, s32 a, s32 b);
void func_00161200(Frame_1692B0* f);
void func_00152D30(Frame_1692B0* f);
void func_001529E0(Frame_1692B0* f, s32 a, s32* out);
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

extern u8 D_002626E8[];
void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_00169D20(void* self)
{
    func_00182D48(self);
    func_00152470(D_002626E8, self);
}

extern u8 D_002626F8[];
void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

void func_0016A178(void* self)
{
    func_00182ED0(self);
    func_00152600(D_002626F8, self);
}

typedef void (*VFn_16AA18)(void* self);
struct Dyn_16AA18 { VFn_16AA18* vtbl; };

struct Self_16AA18 {
    u8 pad0[8];
    s32 kind;
    u8 pad1[0x2D0 - 0x0C];
    Dyn_16AA18* slots[9];
};

extern u8 D_00262718[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
u32 func_001601D8(s32 idx);
u32* func_00160810(s32 idx);

void func_0016AA18(Self_16AA18* self)
{
    func_00124A48(self);
    func_00124DF8(self, 9, D_00262718);

    if ((u32)(self->kind - 0x515) < 5) {
        s32 t = self->kind - 0x514;
        s32 s4 = t << 8;
        s32 s5 = t * 0x44C;

        for (s32 i = 0; i < 9; i++) {
            if (self->slots[i] == 0) {
                continue;
            }
            s32 flag;
            if (i == 8) {
                flag = *(s32*)((u8*)D_002623C0 + s5 + 0x458) & 0x20;
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
                Dyn_16AA18* obj = self->slots[i];
                obj->vtbl[6](obj);
            }
        }
    }
}

struct Actor_169D90 {
    u8 pad_00[0x14];
    void* ptr_14;
    s32 arg_18;
    u8 pad_1C[0x44 - 0x1C];
    s32 key_44;
    void* res_48;
};

struct Res_0015A448 {
    u8 pad_00[0x398];
    s32 f398;
};

void* func_0015A448(void* a, s32 b, s32 c);

void func_00169D90(Actor_169D90* self)
{
    if (self->key_44 != -1) {
        Res_0015A448* r = (Res_0015A448*)func_0015A448(self->ptr_14, self->key_44, self->arg_18);
        self->res_48 = r;
        r->f398 = 0;
    }
}

struct Blob_169DD8 {
    u64 bits;
} __attribute__((packed));

struct Actor_169DD8 {
    u8 pad_00[0x38];
    Blob_169DD8 blob_38;
};

void func_001830D8(void* self);

void func_00169DD8(Actor_169DD8* self)
{
    Blob_169DD8 saved = self->blob_38;
    func_001830D8(self);
    self->blob_38 = saved;
}

void func_0016A140(void* self)
{
    func_00182D48(self);
    func_00152470(D_002626F8, self);
}

struct Actor_16A1B0 {
    u8 pad_00[0x14];
    void* ptr_14;
    s32 arg_18;
    u8 pad_1C[0x60 - 0x1C];
    s32 key_60;
    void* res_64;
};

void func_0016A1B0(Actor_16A1B0* self)
{
    if (self->key_60 != -1) {
        Res_0015A448* r = (Res_0015A448*)func_0015A448(self->ptr_14, self->key_60, self->arg_18);
        self->res_64 = r;
        r->f398 = 0;
    }
}

struct Blob_16A1F8 {
    u64 bits;
} __attribute__((packed));

struct Actor_16A1F8 {
    u8 pad_00[0x50];
    Blob_16A1F8 blob_50;
};

void func_0016A1F8(Actor_16A1F8* self)
{
    Blob_16A1F8 saved = self->blob_50;
    func_001830D8(self);
    self->blob_50 = saved;
}

struct Actor_16A3A8 {
    u8 pad_000[0x568];
    f32 f568;
};

void func_001B7968(void* self);
void func_00129FB0(void* self, f32 k);
void func_0012A080(void* self, f32 k);
void func_0012A150(void* self, f32 k);
void func_0012A270(void* self, f32 k);

void func_0016A3A8(Actor_16A3A8* self)
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

void func_0016A490(void* self)
{
    func_001B7A98(self);
    func_00152470(D_00262708, self);
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

struct Ctx_168FB0 {
    u16 u0;
    u16 u2;
    u8 pad4[4];
    u8 b8;
    u8 b9;
    u8 pad10[0x0E];
    Bits_168FB0 bits;
};

u32 func_00168D30(u32 n);

void func_00168FB0(Ctx_168FB0* self, u32 a1)
{
    self->bits.f0 = a1;
    self->bits.f14 = self->b9;
    self->bits.f20 = self->b8;
    self->bits.f26 = func_00168D30(self->u0) & 0xF;
    self->bits.f30 = func_00168D30(self->u2) & 0xF;
    self->bits.f34 = 1;
}

struct Desc_169088 {
    u16 u0;
    u16 u2;
    u8 pad4[4];
    u8 b8;
    u8 b9;
    u8 pad10[0x0A];
    s32 x14;
};

void func_00168D98(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void func_00169088(Desc_169088* d, u32 dbp, void* ctx)
{
    func_00168D98(dbp, d->b9, d->b8, d->u0, d->u2, d->x14, ctx);
}

extern u8 D_002626E8[];
extern u8 D_002626F8[];
extern u8 D_00262708[];

void func_00152438(void* self, s32 value);

void func_00169C58()
{
    func_00152438(D_002626E8, 0x38);
    func_00152438(D_002626F8, 0x50);
    func_00152438(D_00262708, 0x558);
}

extern u8 D_002626E8[];
extern u8 D_002626F8[];
extern u8 D_00262708[];

void func_00152440(void* self);

void func_00169CA0()
{
    func_00152440(D_002626E8);
    func_00152440(D_002626F8);
    func_00152440(D_00262708);
}

extern u8 D_002626E8[];

void func_00182ED0(void* self);
void func_00152600(void* data, void* self);

void func_00169D58(void* self)
{
    func_00182ED0(self);
    func_00152600(D_002626E8, self);
}

struct Hdr_1694F8 { u8 pad0[0xC]; s32 f0C; };
struct Src_1694F8 { s32 scale; s32 base; };
struct Pool_1694F8 { s32 f0; s32 f4; s32 f8; s32 fC; };
struct Link_1694F8 { Src_1694F8* src; Pool_1694F8* dst; Link_1694F8* next; };
struct Node_1694F8 { s32 flags; u8 pad4[4]; s32 idx; u8 pad0C[8]; Link_1694F8* links; };


void func_001694A0(void* p);
void* func_0018D5C0(u32 n);

void func_001694F8(Hdr_1694F8* a0, Src_1694F8* a1, s32 a2, s32 a3, s32 a4, Node_1694F8* a5)
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
    if ((a0->f0C & 0x10000000) == 0) {
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
        idx = a5->idx;
    }
    scale = a1->scale;
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
            p->next = a5->links;
            a5->links = p;
        }
    }
}

struct Pool_169608 { s32 f0; s32 f4; s32 f8; s32 fC; };
struct Link_169608 { s32 src; Pool_169608* dst; Link_169608* next; };
struct Node_169608 { u8 pad0[0x14]; Link_169608* links; };


void func_001694A0(void* p);
void* func_0018D5C0(u32 n);

void func_00169608(s32 a0, s32 a1, Node_169608* a2)
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
        p->next = a2->links;
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
extern u8 D_002624E0[];
extern u8 D_002625D0[];
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

struct S_168D68 { s32 a; s32 b; s32 c; };
void func_00168D68(S_168D68* p, s32 value, s32 other) { p->b = value; p->a = value; p->c = other; }

struct S_168D78 { s32 a; s32 b; };
void func_00168D78(S_168D78* p) { p->b = p->a; }

extern s32 D_002626D8[];
void func_00168D68(s32*,s32,s32);
void func_00168D00()
{
    func_00168D68(D_002626D8,0x1E00,0x4000);
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
extern u8 D_002625D0[];
extern u8 D_002624E0[];

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

struct Frame_1693A8 { u8 buf[0x30]; u8 span[0x10]; s32 out; };

extern s32 D_00274514;
extern s32 D_00274510;

void func_001611B8(Frame_1693A8* f);
void func_00168D68(void* p, s32 a, s32 b);
void func_0018D608(void);
void func_00152980(Frame_1693A8* f, s32 size);
void func_00152B38(Frame_1693A8* f);
s32 func_001690C0(void* self, void* arg, Frame_1693A8* f);
void func_001613C0(Frame_1693A8* f, s32 a, s32 b, s32 c);
void func_00161708(Frame_1693A8* f, s32 a, s32 b);
void func_00161200(Frame_1693A8* f);
void func_00152D30(Frame_1693A8* f);
void func_00152A50(Frame_1693A8* f, s32 a1, s32 a2, s32* out, s32 a4);
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

struct Ent_169718 { s32 a; s32 b; s32 c; s32 d; };

extern s32 D_002626D0;

void func_001694A0(void* p);

void func_00169718(void)
{
    s32 i;

    for (i = 0; i < D_002626D0; i++) {
        func_001694A0(&D_0027DC20[i]);
    }
}

struct Obj_16AED8 { u8 pad0[0x14]; void* f14; u8 pad1[0x2B0]; u64 f2C8; s32 f2D0; };

struct Obj_16AED8Glob { u8 pad0[0x30]; s32 f30; };

extern s32 D_0026FCF0;
extern u8 D_00262788[];
extern u8 D_00275BC0[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001E96F8(void* obj, s32 mode);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_0016AB38(void* self);

void func_0016AED8(Obj_16AED8* self)
{
    func_00124A48(self);
    self->f2C8 = (self->f2C8 & ~(3ULL << 40)) | (1ULL << 40);
    D_0026FCF0 = (s32)self;
    ((Obj_16AED8Glob*)D_00275BC0)->f30 = 2;
    func_001E96F8(D_00275BC0, 2);
    func_00124DF8(self, 0x12, D_00262788);
    self->f2D0 = -1;
    func_001DBCC8(self->f14, (void*)func_0016AB38, self, 0, 0);
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

typedef void (*VFn_16B7A8)(void* self);

struct Obj_16B7A8 {
    VFn_16B7A8* vtbl;
    u8 pad0[0x258];
    s32 f25C;
    void* f260;
    s32 f264;
};

struct Node_16B7A8 {
    u8 pad0[0x2D0];
    s32 f2D0;
};

extern u8 D_0026F138[];
extern u8 D_00262C70[];

void func_0016B300(void* self, s32 idx, s32 flag);
void func_0016E0F0(s32 bits);
void func_0016EC88(void* p);
void func_001BE998(void);
void func_0016E118(s32 n);

void func_0016B7A8(Obj_16B7A8* self, s32 v)
{
    s32 flag = (v != 0);
    if (flag != (self->f25C == 0)) {
        return;
    }
    if (v != 0) {
        func_0016B300(self->f260, ((Node_16B7A8*)self->f260)->f2D0, 0);
        func_0016E0F0(1);
        func_0016EC88(D_00262C70);
    } else {
        if (self->f264 != 0) {
            func_001BE998();
            self->f264 = 0;
        }
        func_0016E118(1);
        self->vtbl[15](self);
        Obj_16B7A8* g = (Obj_16B7A8*)D_0026F138;
        g->vtbl[15](g);
    }
    self->f25C = v;
}

struct Frame_168B68 { u8 buf[0x30]; s32 value; u8 pad[0x3F0]; };

extern s32 D_002626CC;
extern s32 D_00261F1C;

void func_001611B8(Frame_168B68* f);
void func_001683B8(void);
void func_001529C8(Frame_168B68* f, s32 n, s32* p);
void func_00152B38(Frame_168B68* f);
void func_0019DDA0(f32 x, f32 y, f32 z, f32 w, s32 a, s32 b, s32 c, s32 d, Frame_168B68* e);
void func_001613C0(Frame_168B68* f, s32 a, s32 b, s32 c);
void func_00161708(Frame_168B68* f, s32 a, s32 b);
void func_00161200(Frame_168B68* f);
void func_00152D30(Frame_168B68* f);
void func_001529E0(Frame_168B68* f, s32 a, s32 b);
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

struct Ent1_1690C0 { s32 flags; u8 pad0[2]; u16 f6; s32 f8; s32 fC; u8 pad1[8]; };
struct Ent2_1690C0 { u8 pad0[4]; s32 flags4; u8 f8; u8 pad1; u16 fA; u8 pad2[4]; s32 f10; s32 f14; u8 pad3[8]; };
struct Ctl_1690C0 { u8 pad0[4]; s32 f4; };
struct Ctx_1690C0 { u8 pad0[0xC]; s32 fC; };

extern s32 D_00274500;
extern Ent2_1690C0* D_00274504;
extern s32 D_00274508;
extern Ent1_1690C0* D_0027450C;

s32 func_00168D88(void* self, s32 size);
void func_00168E78(void* e, s32 v);
void func_00168F48(void* e, s32 v, void* ctx);
void func_00152B80(void* self, s32 lo, s32 hi);
void func_00168FB0(void* e, s32 v);
void func_00169088(void* e, s32 v, void* ctx);

s32 func_001690C0(s32 mask, Ctl_1690C0* b, Ctx_1690C0* c)
{
    s32 saved;

    if (c != 0) {
        saved = c->fC;
    } else {
        saved = 0;
    }
    for (s32 i = 0; i < D_00274508; i++) {
        Ent1_1690C0* e = &D_0027450C[i];
        if ((e->flags & mask) == mask) {
            s32 v = func_00168D88(b, e->f6);
            func_00168E78(e, v);
            if (c != 0) {
                func_00168F48(e, v, c);
                func_00152B80(c, e->fC, e->f8);
            }
        }
    }
    if ((b->f4 & 0x7F) != 0) {
        func_00168D88(b, 0x80 - (b->f4 & 0x7F));
    }
    for (s32 i = 0; i < D_00274500; i++) {
        Ent2_1690C0* e = &D_00274504[i];
        if ((e->flags4 & mask) == mask) {
            s32 v;
            if (e->f8 == 0 && (b->f4 & 0x1F) != 0) {
                func_00168D88(b, 0x20 - (b->f4 & 0x1F));
            }
            v = func_00168D88(b, e->fA);
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
    return (c->fC ^ saved) != 0;
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

extern u8* D_002623C0;
struct Tab_16B300 { s32 a; s32 b; };
extern Tab_16B300 D_00262860[];
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
        s32 off = idx * 0x44C;
        if ((*(s32*)(D_002623C0 + off + 0x458) & 1) == 0) {
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

typedef void (*VFn_16BDD0)(void* self);
struct Mgr_16BDD0 { VFn_16BDD0* vtbl; u8 pad0[0x25C - 4]; s32 x25C; s32 x260; };
struct Glob_16BDD0 { u8 pad0[0x19F4]; u32 w19F4; };

extern u8 D_00262C70[];

void func_0016E0F0(s32 n);
void func_0016E118(s32 n);
void func_0016EC88(void* p);
s32 func_0016BB78(s32 n);

void func_0016BDD0(Mgr_16BDD0* self, s32 flag)
{
    if ((flag != 0) != (self->x25C == 0)) {
        return;
    }
    if (flag != 0) {
        s32 bit = 15;
        func_0016E0F0(1);
        func_0016EC88(D_00262C70);
        self->vtbl[14](self);
        s32 mask = func_0016BB78(15);
        Glob_16BDD0* g = (Glob_16BDD0*)D_002623C0;
        for (; bit > 0; bit--) {
            if (g->w19F4 & mask) {
                break;
            }
            mask >>= 1;
        }
        self->x260 = bit;
    } else {
        func_0016E118(1);
        self->vtbl[15](self);
    }
    self->x25C = flag;
}

struct Bits_169B18 { u8 pad[0x18]; u64 bits; };
void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, u64 b);

void func_00169B18(Bits_169B18* src, void* dst)
{
    s32 w = 1 << (s32)((src->bits >> 26) & 0xF);
    s32 cap = 64;
    if (cap < w) cap = w;
    s32 f = (s32)(src->bits & 0x3FFF) >> 5;
    s32 m = 1 << (s32)((src->bits >> 30) & 0xF);
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

struct Ctx_168E78 {
    u8 pad0[4];
    u16 n4;
    u8 pad1[0x0A];
    Bits_168E78 bits;
};

void func_00168E78(Ctx_168E78* self, u32 a1){
 self->bits.f37 = a1;
 self->bits.f20 = (self->n4 <= 0x10) ? 0x14 : 0x13;
 self->bits.r51=0; self->bits.r55=0; self->bits.r56=0; self->bits.f61=1;}

extern void* D_0027B314;

void* func_001300E8(void* node, s32 flags);

struct Iter_16A758 {
    void* head;
    u8 pad4[4];
    s32 link;
};

struct Walk_16A758 {
    Iter_16A758* iter;
    void* cursor;
    s32 link;
    void* prev;

    Walk_16A758(Iter_16A758* i)
    {
        cursor = i;
        iter = i;
        link = i->link;
        prev = D_0027B314;
        D_0027B314 = this;
    }
    ~Walk_16A758() { D_0027B314 = prev; }
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
    Walk_16A758 w((Iter_16A758*)(self + 0x34));
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

struct Obj_169CD8 {
    u8 pad0[0x44];
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    u8 pad54[0x58 - 0x54];
    f32 f58;
};

void func_00169CD8(void* self)
{
    Obj_169CD8* o = (Obj_169CD8*)self;
    func_00182C18(self);
    o->f44 = -1;
    o->f4C = 1;
    o->f50 = 3;
    o->f58 = 3.4028234663852886e+38f;
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

extern u8 D_00248D20[];

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
    func_001280C0(0, self->f18, D_00248D20, &f.b);
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

extern void* D_00262E10;
extern u8 D_00248D30[];
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
        self->vtbl[36](self, D_00248D30);
        self->vtbl[37](self, D_00248D30);
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

extern void* D_0027B314;
void* func_001300E8(void* node, s32 flags);

struct Iter_16A820 {
    void* head;
    u8 pad4[4];
    s32 link;
};

struct Walk_16A820 {
    Iter_16A820* iter;
    void* cursor;
    s32 link;
    void* prev;

    Walk_16A820(Iter_16A820* i)
    {
        cursor = i;
        iter = i;
        link = i->link;
        prev = D_0027B314;
        D_0027B314 = this;
    }
    ~Walk_16A820() { D_0027B314 = prev; }
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
    Walk_16A820 w((Iter_16A820*)(self + 0x34));
    void* best = 0;
    f32 bestF = 3.4028234663852886e+38f;
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

typedef void (*VFnV_16AF80)(void* self);
typedef void (*VFnS_16AF80)(void* self, const char* s);

struct Obj_16AF80 {
    void** vtbl;
    u8 pad4[0x460];
    s32 f464;
};

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

extern u8 D_0026F138[];
extern u8 D_0026FA90[];
extern u8* D_002623C0;

void func_001AA8B8(void* self, f32 v);
void func_001AD1E8(void* self);

void func_0016AF80(Ctx_16AF80* self)
{
    s32 s1 = 0;
    s32 stride = 0x44C;
    Pair_16AF80* p = self->f2E0;

    if (p->f28 != p->f30) {
        void** vt = *(void***)D_0026F138;
        ((VFnS_16AF80)vt[8])(D_0026F138, "");
    } else if (self->f2D0 == 0) {
        void** vt = *(void***)D_0026F138;
        ((VFnS_16AF80)vt[8])(D_0026F138, "Bentley");
    } else {
        s32 flags = *(s32*)(D_002623C0 + self->f2D0 * stride + 0x458);
        if (flags & 1) {
            func_001AD1E8(D_0026F138);
        } else if (self->f2D0 == self->f300) {
            void** vt = *(void***)D_0026F138;
            ((VFnS_16AF80)vt[8])(D_0026F138, "Murray");
        } else {
            s1 = 1;
            void** vt = *(void***)D_0026F138;
            ((VFnS_16AF80)vt[8])(D_0026F138, "");
        }
    }

    func_001AA8B8(D_0026F138, 0.0f);
    ((Obj_16AF80*)D_0026F138)->f464 = 0;
    {
        void** vt = *(void***)D_0026F138;
        ((VFnV_16AF80)vt[14])(D_0026F138);
    }

    if (s1 != 0) {
        ((VFnS_16AF80)(*(void***)D_0026FA90)[8])(D_0026FA90, "Press &2X&. to Start Mission!");
        ((VFnV_16AF80)(*(void***)D_0026FA90)[14])(D_0026FA90);
    } else {
        void** vt = *(void***)D_0026FA90;
        ((VFnV_16AF80)vt[15])(D_0026FA90);
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

struct Self_16A100 { u8 pad0[0x60]; s32 f60; u8 pad1[0x68 - 0x64]; s32 f68; u8 pad2[0x70 - 0x6C]; f32 f70; };

extern f32 D_0024A798;
void func_00182C18(Self_16A100* self);

void func_0016A100(Self_16A100* self)
{
    func_00182C18(self);
    f32 k = D_0024A798;
    self->f60 = -1;
    self->f68 = 1;
    self->f70 = k;
}

struct Self_16A420;
struct Blk_16A420 { u8 pad0[0xB0]; u32 flags; };
struct __attribute__((aligned(16))) Quad_16A420 { s32 w[4]; };
struct Self_16A420 { u8 pad0[0x224]; Blk_16A420* blk; };

extern u8 D_002483D0[];
void func_001BAC30(Self_16A420* self);
void* func_0018D5C0(s32 bytes);

void func_0016A420(Self_16A420* self)
{
    Blk_16A420* b;
    Quad_16A420* dst;
    Quad_16A420* src;

    func_001BAC30(self);
    if (self->blk == 0) {
        self->blk = (Blk_16A420*)func_0018D5C0(0xC0);
    }
    b = self->blk;
    b->flags |= 1;
    dst = (Quad_16A420*)self->blk;
    src = (Quad_16A420*)D_002483D0;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

struct Obj_16A580 { u8 pad0[0x214]; s32 w214; s32 w218; u8 pad1[0x550 - 0x21C]; s32 w550; };
struct Sub_16A580 { u8 pad0[4]; };
struct Buf_16A580 { f32 v[12]; };

extern u8 D_00248D30[];

void func_001B9338(Obj_16A580* self, f32 t);
void func_00189378(Sub_16A580* sub, s32 zero, Buf_16A580* out);
void func_001B91A8(Obj_16A580* self, Buf_16A580* out, s32 a, void* table, s32 b, f32 t);

void func_0016A580(Obj_16A580* self, f32 t)
{
    Buf_16A580 buf;

    func_001B9338(self, t);
    if (self->w550 != 0) {
        return;
    }
    func_00189378((Sub_16A580*)((u8*)self + 0xD0), 0, &buf);
    func_001B91A8(self, &buf, self->w214, D_00248D30, self->w218, t);
}

// NEAR: only the order of `addiu v0,s5,lo(D_00261858)` vs `sw s4,0x2D4(s3)` differs (2 instrs swapped)

struct Glob_16B300 { u8 pad[0x19EC]; s32 f19EC; };
struct Self_16B300 {
    u8 pad0[0x2D0]; s32 f2D0; s32 f2D4; f32 f2D8; u8 pad1[4]; void* f2E0;
    u8 pad2[0x300 - 0x2E4]; s32 f300;
};
struct Slot_16B300 { u8 pad[0x20]; };

struct Tm_16B300 { f32 f0; f32 f4; };
extern Tm_16B300 D_00261858;
extern f32 D_00262970;
struct Gl_16B300 { u8 pad[0x268]; f32 f268; };
extern u8 D_00262890[];
extern u8 D_00262950[];
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
        u8* ent = (u8*)D_002623C0 + a * 0x44C;
        if (*(s32*)(ent + 0x458) & 1) {
            s32 fl = ((Glob_16B300*)D_002623C0)->f19EC;
            if (!(fl & 2)) {
                ((Glob_16B300*)D_002623C0)->f19EC = fl | 2;
                slot = (Slot_16B300*)D_00262950;
            }
        } else {
            Gl_16B300* gp = (Gl_16B300*)D_0026FA90;
            f32 t = D_00261858.f4;
            if (D_00262970 <= t - gp->f268) {
                gp->f268 = t;
                slot = (Slot_16B300*)(D_00262890 + (a << 5));
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
    self->f2D8 = D_00261858.f4;
}
