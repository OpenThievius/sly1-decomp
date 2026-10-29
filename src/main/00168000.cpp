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
