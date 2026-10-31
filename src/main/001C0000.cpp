// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1C2320 { u8 pad[4]; void* f4; };
void func_00130110(void* p);
void* func_0011BE90(void* a, void* b, void* c);
void func_0011BDD0(void* self, void* a, void* b, void* c);
void func_0011BD28(void* self, void* a, void* b, void* c);

void* func_001C2320(void* self, Obj_1C2320* p, void* a2, void* a3)
{
    func_00130110(p);
    if (func_0011BE90(p->f4, a2, 0)) func_0011BDD0(self, p->f4, a2, a3);
    else func_0011BD28(self, p->f4, a2, a3);
    return self;
}

void func_001C27B0(s32 a, s32 b);

void func_001C29C8()
{
    func_001C27B0(1, 0xFFFF);
}

struct Obj_1C29E8 { u8 pad[8]; s32 f8; s32 fC; };

void func_001C29E8(Obj_1C29E8* o)
{
    o->fC = 0;
    o->f8 = 0;
}

void func_001921A8(void* self);

struct Obj_1C3390 { u8 pad[0x610]; s32 f610; u8 pad2[0x694 - 0x614]; s32 f694; };

void func_001C3390(Obj_1C3390* self)
{
    func_001921A8(self);
    self->f610 = -1;
    self->f694 = 5;
}

bool func_001E9970();

typedef void (*VFn_1C3928)(void*);
struct Obj_1C3928 { VFn_1C3928* vtbl; };
extern Obj_1C3928 D_0026DD48;
extern Obj_1C3928 D_0026DFC8;

// NEAR: the two lui immediates for D_0026DD48 / D_0026DFC8 come out wrong in check.py (see results.tsv note).
void func_001C3928()
{
    if (func_001E9970()) {
        D_0026DD48.vtbl[14]((void*)&D_0026DD48);
        D_0026DFC8.vtbl[14]((void*)&D_0026DFC8);
    } else {
        D_0026DD48.vtbl[15]((void*)&D_0026DD48);
        D_0026DFC8.vtbl[15]((void*)&D_0026DFC8);
    }
}

struct Entry_1C3C00 { s32 first; u8 pad[60]; };
struct Obj_1C3C00 { u8 p0[0x67C]; s32 f67C; s32 f680; s32 f684; s32 f688; u8 p1[0x694 - 0x68C]; s32 f694; };
s32 func_001300E8(s32 a, s32 b);
s32 func_001833F0(s32 a, s32 b);

void func_001C3C00(Obj_1C3C00* self, Entry_1C3C00* table, s32 idx)
{
    Entry_1C3C00* e = (Entry_1C3C00*)((u8*)table + ((1 - idx) << 6));
    if (func_001300E8(e->first, 0x21)) {
        if (self->f694 > 0) {
            self->f680 = 1;
            return;
        }
        if (self->f67C == 0) self->f684 = e->first;
        return;
    }
    if (func_001833F0(e->first, 0x52F)) self->f688 = e->first;
}

void func_00192C58(void* self);
void func_001C3FC8(void* self, s32 flag);

void func_001C3E80(void* self)
{
    func_00192C58(self);
    func_001C3FC8(self, 1);
}

typedef void (*VFn_1C3F68)(void*, void*);
struct Obj_1C3F68 { VFn_1C3F68* vtbl; };
struct Local_1C3F68 { s32 pad[2]; s32 value; VFn_1C3F68 fn; };
void func_001D7098(void* self, s32 a, s32 b);
void func_001C3EB0(void* self, void* data);

void func_001C3F68(Obj_1C3F68* self, s32 value)
{
    Local_1C3F68 local;
    func_001D7098(&local, 0, value);
    local.value = value;
    local.fn = func_001C3EB0;
    self->vtbl[80]((void*)self, (void*)&local);
}

void func_001C06A0(s32 a, s32 b, f32 x);

void func_001C0000(s32 flag, f32 x)
{
    func_001C06A0(6, 0, x);
    func_001C06A0(6, 2, x);
    func_001C06A0(6, 3, x);
    if (flag) {
        func_001C06A0(6, 1, x);
    }
}

s32 func_0011D4E0(s32 flag);

s32 func_001C0790(s32 value)
{
    return func_0011D4E0(value != 0);
}

struct Pk8_1C0A50 { u64 v; } __attribute__((packed));
struct Ent_1C0A50 { s32 key; Pk8_1C0A50 a; Pk8_1C0A50 b; };
struct Obj_1C0A50 { u8 pad[0x1D80]; s32 count; Ent_1C0A50 ents[16]; };

extern Pk8_1C0A50 D_00274820;
extern Pk8_1C0A50 D_00274828;

void func_001C0A50(Obj_1C0A50* self, s32 key)
{
    if (self->count < 16) {
        Ent_1C0A50* e = &self->ents[self->count];
        e->key = key;
        e->a = D_00274820;
        e->b = D_00274828;
        self->count++;
    }
}

extern s32 D_00274728;
extern s32 D_006053E0[];

s32 func_0011D8F0(s32 a, s32 b);

void func_001C0C68(s32 i)
{
    D_006053E0[i] = func_0011D8F0(D_00274728, i);
}

struct Obj_1C1110 { u8 pad[0x14]; s32 f14; };

void func_00182ED0(Obj_1C1110* self);
void func_00152600(s32 p, Obj_1C1110* self);

void func_001C1110(Obj_1C1110* self)
{
    func_00182ED0(self);
    func_00152600(self->f14 + 0x1C84, self);
}

struct Loc_1C1E48 { u8 obj[0x10]; s32 tmp; s32 flag; s32 cnt; };

void func_0011B008(Loc_1C1E48* p);
void func_0011B6C0(Loc_1C1E48* p, s32 v);
void func_0011B538(Loc_1C1E48* p, s32 v);
void func_0011B018(void* self, Loc_1C1E48* p);
void func_0011B060(Loc_1C1E48* p, s32 v);
void func_001C1A28(s32* p, s32 v);

void* func_001C1E48(void* self, s32 n, s32* keys, s32* vals)
{
    Loc_1C1E48 loc;
    func_0011B008(&loc);
    loc.flag = 0;
    loc.cnt = 0;
    for (s32 i = 0; i < n; i++) {
        loc.tmp = keys[i];
        func_001C1A28(&loc.tmp, vals[i]);
    }
    if (loc.flag) {
        func_0011B6C0(&loc, loc.flag);
    } else {
        func_0011B538(&loc, 0);
    }
    func_0011B018(self, &loc);
    func_0011B060(&loc, 2);
    return self;
}

extern s32 D_006053E0[];

s32 func_001C0C50(s32 index)
{
    return D_006053E0[index];
}

void func_001C0C08(s32 index, s32 value);

void func_001C0CB0(void)
{
    for (s32 i = 0; i < 8; i++) {
        func_001C0C08(i, 0);
    }
}

typedef void (*Slot_001C0FF0)(void* self);

struct Obj_001C0FF0 {
    Slot_001C0FF0* vtbl;
    u8 pad[0x328];
    s32 f32C;
};

void func_001C1030(void* self, s32 v);
void func_00124A48(void* self);

void func_001C0FF0(Obj_001C0FF0* self)
{
    func_00124A48(self);
    func_001C1030(self, self->f32C);
    self->vtbl[7](self);
}

struct Obj_001C1030 {
    void* vtbl;
    u8 pad[0x10];
    void* host;
    u8 pad2[0x314];
    s32 f32C;
    s32 f330;
    s32 f334;
};

void func_001B6438(s32 p);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
s32 func_001B6290(s32 p, void* ctx, s32 a2, s32 a3);

void func_001C1030(Obj_001C1030* self, s32 v)
{
    if (self->f334 != 0) {
        func_001B6438(self->f334);
        self->f334 = 0;
    }
    s32 r = func_0015A418(self->host, 0x101, v, self);
    self->f330 = r;
    if (r != 0) {
        self->f334 = func_001B6290(r, self, -1, 1);
    }
    self->f32C = v;
}

struct Obj_001C10D8 {
    void* vtbl;
    u8 pad[0x10];
    u8* host;
};

void func_00182D48(void* self);
void func_00152470(u8* table, void* self);

void func_001C10D8(Obj_001C10D8* self)
{
    func_00182D48(self);
    func_00152470(self->host + 0x1C84, self);
}

struct __attribute__((packed)) Pack64_1C1148 { u64 v; };
struct Obj_1C1148 { u8 pad[0x50]; Pack64_1C1148 field; };

void func_001830D8(void* self);

void func_001C1148(Obj_1C1148* self)
{
    Pack64_1C1148 saved;
    saved = self->field;
    func_001830D8(self);
    self->field = saved;
}

struct Entry_1C1390 { s32 key; void* value; };
struct Obj_1C1390 { u8 pad[0x1EF4]; Entry_1C1390* table; };

extern u8 D_00259F38[];
void func_0011A6C0(void* a, void* b);

void* func_001C1390(s32 index, Obj_1C1390* self)
{
    if (index == -1) {
        return 0;
    } else {
        Entry_1C1390* e = (Entry_1C1390*)((index << 3) + (u32)self->table);
        void* p = e->value;
        if (p != 0) func_0011A6C0(D_00259F38, p);
        return p;
    }
}

void func_0011D480(s32 a, s32 b);

void func_001C05D0(f32 x)
{
    func_0011D480(8, (s32)(x * 1024.0f));
}

extern s32 D_00274808[];

void func_0011E328(s32 a, s32 b);
void func_0011E360(s32 a, s32 b, s32 c);

struct Obj_1C09D8 { u8 pad[0x2328]; s32 f2328; s32 f232C; u8 pad2[0x18]; s32 f2348; };

void func_001C09D8(Obj_1C09D8* self, s32 index, s32 value)
{
    func_0011E328(2, D_00274808[index]);
    func_0011E360(2, value, value);
    self->f2328 = index;
    self->f232C = value;
    self->f2348 = 1;
}

struct Pt_1C0AB8 { f32 x; f32 y; };
struct Ent_1C0AB8 { s32 key; f32 a0; f32 a1; f32 b0; f32 b1; };
struct Obj_1C0AB8 { u8 pad[0x1D80]; s32 count; };

void func_001C0AB8(Obj_1C0AB8* self, Pt_1C0AB8* p)
{
    s32 n = self->count;
    if (n != 0) {
        Ent_1C0AB8* e = (Ent_1C0AB8*)((u8*)self + 0x1D70 + n * 20);
        e->b0 = 8000.0f - p->y * 50.0f;
        e->b1 = 8000.0f - p->x * 50.0f;
    }
}

extern f32 D_00274838[][4];

void func_0011D480(s32 slot, s32 value);

void func_001C0600(s32 column)
{
    f32* p = &D_00274838[0][column];
    f32 prod = 1.0f;
    s32 n = 10;

    do {
        prod = prod * *p;
        p += 4;
        n--;
    } while (n >= 0);

    f32 one = 1.0f;

    if (prod < 0.0f) {
        prod = 0.0f;
    } else if (one < prod) {
        prod = one;
    }

    func_0011D480(column, (s32)(prod * 1024.0f));
}

extern f32 D_00274838[][4];

void func_001C0600(s32 column);

void func_001C06A0(s32 row, s32 column, f32 value)
{
    D_00274838[row][column] = value;
    func_001C0600(column);
}

struct __attribute__((packed)) Pk8_1C0B38 { u64 v; };
struct Ent_1C0B38 { s32 key; Pk8_1C0B38 a; Pk8_1C0B38 b; };
struct Obj_1C0B38 { u8 pad[0x1D80]; s32 count; Ent_1C0B38 ents[16]; };

extern u8 D_002748E8[];

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, void* a4, void* a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

void func_001C0B38(Obj_1C0B38* self)
{
    for (s32 i = 0; i < self->count; i++) {
        Ent_1C0B38* e = &self->ents[i];
        func_001BFCD8(e->key, D_002748E8, 0, 0, &e->a, &e->b, 8000.0f, 3000.0f, 1.0f, 0.0f, 0.0f);
    }
}

struct Packed_001C0B08 { u64 value; } __attribute__((packed));
struct Obj_001C0B08 { u8 pad[0x1D70]; u8 slots[16]; s32 count; };
void func_001C0B08(Obj_001C0B08* self, Packed_001C0B08* item) { if (!self->count) return; u8* dst = (u8*)self + 0x1D70 + self->count * 20; *(Packed_001C0B08*)(dst + 4) = *item; }

struct Obj_001C3E50 { u8 pad[0x610]; s32 state; u8 pad2[0x24]; s32 value; };
s32 func_001C3E50(Obj_001C3E50* self) { if (self->state < 5) { if (self->state >= 2) return 1; } return self->value != 0; }

void func_0011E010(void);
s32 func_0011CE30(void);
void func_0011E110(s32 a0);
void func_0011E1F8(s32 flag);
void func_001C0808(s32 a0);
void func_001BEE48(void);
void func_001C0CB0(void);

void func_001C07B0(void)
{
    func_0011E010();
    func_001C0808(0);
    func_001BEE48();
    func_001C0CB0();
    while (func_0011CE30() != 0) {
    }
    func_0011E110(1);
    func_0011E1F8(0);
}

struct Quad_1C1530 { s32 a, b, c, d; };
struct Rec_1C1530 { s32 a; s32 flag; s32 cnt; };
struct Frame_1C1530 { Quad_1C1530 q; Rec_1C1530 r; };
typedef void (*Cb_1C1530)(void* a, void* b);

void func_0011B008(void* q);
void func_0011B6C0(void* q, s32 v);
void func_0011B538(void* q, s32 n);
void func_0011B018(void* self, void* q);
void func_0011B060(void* q, s32 mode);

void* func_001C1530(void* self, void* ctx, s32 v, Cb_1C1530 cb)
{
    Frame_1C1530 f;
    func_0011B008(&f.q);
    f.r.a = v;
    f.r.flag = 0;
    f.r.cnt = 0;
    cb(ctx, &f.r);
    if (f.r.flag != 0) {
        func_0011B6C0(&f.q, f.r.flag);
    } else {
        func_0011B538(&f.q, 0);
    }
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Obj_1C2238 { u8 pad[4]; void* f4; };
void* func_001C14C0(void* a, s32 b);
void func_001C1F20(void* self, void* a, void* b, void* c);
void func_0011BDD0(void* self, void* a, void* b, void* c);

void* func_001C2238(void* self, Obj_1C2238* p, s32 a2, void* a3)
{
    if (a2 < 0x495) {
        void* v = func_001C14C0(p, a2);
        func_001C1F20(self, p, v, a3);
    } else {
        func_0011BDD0(self, p->f4, (void*)a2, a3);
    }
    return self;
}

struct Obj_1C22B8 { u8 pad[4]; void* f4; };
void func_00130110(void* p);
void func_0011BD28(void* self, void* a, void* b, void* c);

void* func_001C22B8(void* self, Obj_1C22B8* p, void* a2, void* a3)
{
    func_00130110(p);
    func_0011BD28(self, p->f4, a2, a3);
    return self;
}

void func_001C06A0(s32 a, s32 b, f32 x);

void func_001C0760(s32 flag)
{
    func_001C06A0(3, 1, flag ? 0.0f : 1.0f);
}

struct __attribute__((packed)) Pk8_1C33C8 { u64 v; };
struct __attribute__((packed)) Pp_1C33C8 { void* p; };

struct Obj_1C33C8 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0xD0 - 0x18];
    f32 fD0;
    f32 fD4;
    u8 pad2[0x3CC - 0xD8];
    f32 f3CC;
    u8 pad3[0x62C - 0x3D0];
    void* f62C;
    Pk8_1C33C8 f630;
    u8 pad4[0x644 - 0x638];
    f32 f644;
    f32 f648;
    u8 pad5[0x660 - 0x64C];
    void* f660;
    void* f664;
    void* f668;
    u8 pad6[0x68C - 0x66C];
    f32 f68C;
    u8 pad7[0x71C - 0x690];
    s32 count;
    void* f720[16];
};

extern u8 D_00274A40[];
extern u8 D_002749B0[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
f32 func_00205778(f32 a, f32 b);
void func_001DDC38(void* sub, void* self);
void func_001C3FC8(void* self, s32 flag);

void func_001C33C8(Obj_1C33C8* self)
{
    func_00124A48(self);
    self->f68C = self->f3CC;
    func_00124DF8(self, 0xC, D_002749B0);
    self->f668 = func_001B6290(self->f664, self, -1, 0);
    self->f644 = func_00205778(self->fD4, self->fD0);
    Obj_1C33C8* v = (Obj_1C33C8*)self->f660;
    self->f648 = func_00205778(v->fD4, v->fD0);
    self->f630 = *(Pk8_1C33C8*)((u8*)self->f62C + 0x2DC);
    u8* g1 = (u8*)&D_0026DD48;
    ((Pp_1C33C8*)(g1 + 0x264))->p = (u8*)self + 0x690;
    u8* g2 = (u8*)&D_0026DFC8;
    ((Pp_1C33C8*)(g2 + 0x264))->p = (u8*)self + 0x694;
    *(void**)(g1 + 0x268) = D_00274A40;
    *(f32*)(g2 + 0x26C) = 4.0f;
    func_001DDC38(self->f14, self);
    s32 c = self->count;
    self->f720[c] = self;
    self->count = c + 1;
    func_001C3FC8(self, 1);
}

// NEAR: retail ends the zero path with beqz + move $v0,$zero and falls into li $v0,1; ours folds the call result into sltu $v0,$zero,$v0 (2 lines differ).

struct Obj_1C3D28 { u8 pad[0x14]; void* f14; };
extern s32 D_00262C64;
s32 func_001DDA80(void* p);

s32 func_001C3D28(Obj_1C3D28* self)
{ if ((D_00262C64 & 1) || func_001DDA80(self->f14)) return 1; return 0; }

// EXACT: declare D_0026185C as extern f32 D_0026185C[] and read [0]

typedef s32 (*VFnA_1C3D60)(void* self, s32 v);
typedef void (*VFnB_1C3D60)(void* self, s32 v, void* data);
typedef void (*VFnC_1C3D60)(void* a0, void* self);
struct Obj_1C3D60 {
    void** vtbl;
    u8 pad0[0x610 - 4];
    s32 f610;
    u8 pad1[0x638 - 0x614];
    s32 f638;
    f32 f63C;
};

struct Arg_1C3D60 {
    s32 f0;
    s32 f4;
    void* f8;
    VFnC_1C3D60 fC;
};
struct Local_1C3D60 { void* self; s32 v; };
extern f32 D_0026185C[];
s32 func_00160C58();
void func_001C3FC8(void* self, s32 flag);

s32 func_001C3D60(Obj_1C3D60* self, Arg_1C3D60* arg)
{
    Local_1C3D60 local;
    s32 m;
    if (((VFnA_1C3D60)self->vtbl[79])(self, arg->f0)) return 0;
    if (arg->f0 == 0) {
        if (arg->fC != 0) arg->fC(arg->f8, self);
    }
    m = self->f610;
    if (m < 5) {
        if (!(m < 2)) return 1;
    }
    if (self->f638 != 0) return 1;
    if (func_00160C58()) {
        func_001C3FC8(self, 2);
        self->f638 = 1;
        self->f63C = D_0026185C[0];
    } else {
        func_001C3FC8(self, 3);
    }
    local.self = self;
    local.v = arg->f4;
    ((VFnB_1C3D60)self->vtbl[18])(self, 0x17, &local);
    return 1;
}

struct Ring_1C25B0 {
    s32 f0;
    s32 f4;
    s32 f8[8];
    s32 f28[0x20 / 4];
    s32 f48;
    s32 f4C;
};

struct Dma_1C25B0 {
    s32 f0;
    u8 pad4[0x7C];
    s32 f80;
};

extern Ring_1C25B0 D_002748F0[];
extern s32 D_00274990;
extern Dma_1C25B0* D_00261F20;
void func_00202C38(Dma_1C25B0* d, s32 b, s32 c);
void func_00202B68(Dma_1C25B0* d);

void func_001C25B0(s32 first, ...) {
    s32 buf[8];
    Ring_1C25B0* r = &D_002748F0[D_00274990];
    s32 n = 0;
    s32 x = first;
    r->f4C = 3;
    func_00202C38(D_00261F20, 0, 0);
    void* ap = (char*)__builtin_next_arg(first) - 56;
    while (x) {
        buf[n] = x;
        ap = (char*)ap + 8;
        x = *(s32*)((char*)ap - 8);
        n++;
    }
    s32 i = 0;
    n = r->f48 - n;
    while (n < r->f48 - 1) {
        *(u64*)(r->f8[n] - 0x10) = ((r->f28[n] >> 4) | 0x10000000) | ((u64)buf[i] << 32);
        n++;
        i++;
    }
    Dma_1C25B0* d = D_00261F20;
    *(u64*)(r->f8[n] - 0x10) = ((r->f28[n] >> 4) | 0x70000000) | ((u64)buf[i] << 32);
    d->f0 &= ~0x40;
    d->f80 = (r->f4 & 0xFFFFFFF) + 0x80000000;
    func_00202B68(d);
    r = &D_002748F0[1 - D_00274990];
    if (r->f4C == 3) r->f4C = 0;
}

extern u8 D_00274758[];
extern u8* D_002623C0;

void func_0018D800(void* dst, void* src, s32 count);

void func_001C06D8(void)
{
    func_0018D800(D_00274838, D_00274758, 0xB0);
    func_001C05D0(1.0f);
    for (s32 i = 0; i < 4; i++) {
        func_001C0600(i);
    }
    func_001C0760(*(s32*)(D_002623C0 + 0x19EC) & 0x80);
    func_001C0790(*(s32*)(D_002623C0 + 0x19EC) & 0x40);
}

struct Pair_1C08B0 { s32 a; s32 b; };
struct Stack_1C08B0 { u8 pad0[0x2328]; Pair_1C08B0 pairs[4]; s32 count; };

extern s32 D_00274808[];

void func_0011E328(s32 channel, s32 value);
void func_0011E360(s32 channel, s32 value, s32 value2);

void func_001C08B0(Stack_1C08B0* self, s32 a, s32 b)
{
    if ((u32)self->count < 4) {
        func_0011E328(2, D_00274808[a]);
        func_0011E360(2, b, b);
        self->pairs[self->count].a = a;
        self->pairs[self->count].b = b;
        self->count++;
    }
}

struct Pair_1C0950 { s32 a; s32 b; };
struct Stack_1C0950 { u8 pad0[0x2328]; Pair_1C0950 pairs[4]; s32 count; };

extern s32 D_00274808[];

void func_0011E328(s32 channel, s32 value);
void func_0011E360(s32 channel, s32 value, s32 value2);

void func_001C0950(Stack_1C0950* self)
{
    s32 n = self->count;
    if (n >= 2) {
        self->count = n - 1;
        func_0011E328(2, D_00274808[self->pairs[n - 2].a]);
        func_0011E360(2, self->pairs[self->count - 1].b, self->pairs[self->count - 1].b);
    }
}

struct Node_1C1A28 { s32 f0; s32 f4; Node_1C1A28* f8; };
struct List_1C1A28 { s32 type; Node_1C1A28* head; Node_1C1A28* tail; };
struct Frame_1C1A28 { s32 type; s32 kind; s32 w2; s32 w3; s32 pad[4]; s32 t[4]; };

void func_001F5C0C(void* p, s32 v, s32 n);
void* func_0011AF28(void);
void func_001C15D8(void* t, s32 value, void* q);
void func_0011B0A8(void* a, void* b);
void func_0011B060(void* q, s32 mode);

s32 func_001C1A28(List_1C1A28* self, s32 value)
{
    Frame_1C1A28 f;
    func_001F5C0C(&f, 0, 0x20);
    f.kind = 2;
    f.type = self->type;
    f.w3 = 0;
    Node_1C1A28* n = (Node_1C1A28*)func_0011AF28();
    func_001C15D8(f.t, value, &f);
    func_0011B0A8(n, f.t);
    func_0011B060(f.t, 2);
    if (self->head != 0) {
        self->tail->f8 = n;
    } else {
        self->head = n;
    }
    self->tail = n;
    return 1;
}

extern s32 D_002748EC;
s32 func_001C0CF0(void);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001C0EC0(void)
{
    if (D_002748EC != 0) {
        f32 scale = (f32)func_001C0CF0();
        func_001BFCD8(0x77, 0, 0, 0, 0.0f, 0.0f, 0.5f, scale * 0.083333336f, 0.0f, 0, 0);
    }
}

struct Quad_1C23B0 { s32 f0; s32 f4; s32 f8; s32 fC; };

void func_001C1BF8(Quad_1C23B0* t, s32 n, s32 c, void* z, s32* arr);

Quad_1C23B0* func_001C23B0(Quad_1C23B0* t, s32 n, s32 c, void* z, ...)
{
    s32 arr[32];
    void* ap = (char*)__builtin_next_arg(z) - 32;
    if (n > 0) {
        s32* d = arr;
        s32 i = n;
        do {
            ap = (char*)ap + 8;
            *d = *(s32*)((char*)ap - 8);
            d++;
            i--;
        } while (i != 0);
    }
    func_001C1BF8(t, n, c, z, arr);
    return t;
}

struct KeyPair_1C14C0 { s32 key; s32 value; };
struct KeyTable_1C14C0 { s32 count; KeyPair_1C14C0* items; };
struct KeyRef_1C14C0 { s32 pad0; s32 index; };
struct KeyHolder_1C14C0 { KeyRef_1C14C0* ref; };

extern KeyTable_1C14C0 D_00244950[];

s32 func_001C14C0(KeyHolder_1C14C0* self, s32 key)
{
    KeyTable_1C14C0* entry = &D_00244950[self->ref->index];
    s32 lo = 0;
    s32 hi = entry->count - 1;
    KeyPair_1C14C0* items = entry->items;

    while (lo <= hi) {
        s32 mid = (lo + hi) >> 1;
        s32 k = items[mid].key;
        if (k == key) {
            return items[mid].value;
        }
        if (key < k) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

struct TabA_24D2A8 { s32 v[42]; };
struct TabB_24D350 { s32 v[25]; };
extern TabA_24D2A8 D_0024D2A8;
extern TabB_24D350 D_0024D350;
extern s32 D_00274830;
s32 func_001EAA70(s32 a, s32 b);

s32 func_001C0CF0() {
    TabA_24D2A8 a = D_0024D2A8;
    TabB_24D350 b = D_0024D350;
    s32 r = func_001EAA70(0, 5);
    D_00274830 += *(s32*)((u8*)&a + (b.v[D_00274830 + 12] * 24 + r * 4));
    return D_00274830;
}

struct Vt_1C34C8 { void* pad[7]; void (*f1C)(void*); void* pad2[0x1A]; void (*f88)(void*, void*); };
struct Obj_1C34C8_Vt { Vt_1C34C8* vt; };
struct Sub_1C34C8 { u8 pad[8]; struct Sub2_1C34C8* p8; u8 padC[8]; f32 f14; f32 f18; };
struct Sub2_1C34C8 { u8 pad[0x34]; f32 f34; };
struct Obj_1C34C8 {
    u8 pad0[0x14]; void* host;
    u8 pad1[0xD0 - 0x18]; f32 fD0; f32 fD4;
    u8 pad2[0x3CC - 0xD8]; f32 f3CC; f32 f3D0;
    u8 pad3[0x610 - 0x3D4]; s32 s610; f32 f614;
    u8 pad4[0x62C - 0x618]; u8* p62C; f32 f630; f32 f634; s32 s638; f32 f63C; f32 f640;
    u8 pad5[4]; f32 f648;
    u8 pad6[0x660 - 0x64C]; Obj_1C34C8_Vt* p660;
    u8 pad7[0x670 - 0x664]; f32 f670;
    u8 pad8[4]; void* p678; Sub_1C34C8* p67C; s32 s680; s32 s684; Obj_1C34C8_Vt* p688;
    f32 f68C; s32 s690; s32 s694;
};

extern f32 D_00274A50[];
extern f32 D_00274A70[];
extern f32 D_00274A80[];
extern f32 D_00275C60[];
extern f32 D_00261854;
extern f32 D_00261858[];
extern f32 D_00274A44;
extern f32 D_00274A60[];
extern u8 D_00248D20[];
extern s32 D_0026E228;

void func_00192B58(void* self, f32 t);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_00158730(void* x);
void func_001C3F68(void* self, s32 v);
void func_0012E760(void* p);
void func_0012C7B0(void* a, void* b, s32 c, void* d, f32 fa, f32 fb);
f32 func_00205778(f32 a, f32 b);
void func_00188850(void* a, void* b, f32 f);
void func_001EA918(void* a, void* b, void* c, void* d, s32 e, f32 f);
f32 func_00205210(f32 a);
void func_00126A48(void* o, u32 v);

void func_001C34C8(Obj_1C34C8* self, f32 t)
{
    f32 buf[12];
    f32 buf2[12];
    u32 ca[4];
    u32 cb[4];
    func_00192B58(self, t);
    if (self->p688) {
        void* h = func_0015A838(self->host, 0x101, 0x77, (s32)self->p688);
        if (h) func_00158730(h);
        self->s690 = self->s690 + 1;
        self->p688->vt->f1C(self->p688);
        self->p688 = 0;
    }
    if (self->s684) {
        func_001C3F68(self, self->s684);
        self->s684 = 0;
    }
    if (self->p67C) {
        if (self->p67C->f18 == 0.0f) {
            func_0012E760(self->p67C);
            self->p67C = 0;
        }
    } else if (self->s680) {
        func_0012C7B0(self->p678, self, 0, &self->p67C, 0.0f, 1.0f);
        self->s694 = self->s694 - 1;
        D_0026E228 = -1;
    }
    self->s680 = 0;
    f32 u;
    if (self->p67C) {
        f32* lim = D_00275C60;
        f32 r = self->p67C->f14 / self->p67C->p8->f34;
        f32* pp = D_00274A50;
        f32 lo = lim[0];
        f32 hi = lim[1];
        f32 v = pp[0] + r * (pp[1] + r * pp[2]);
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        D_00261854 = v;
        u = r;
    } else {
        D_00261854 = 1.0f;
        u = 0.0f;
    }
    f32 w = u * D_00274A44 + (1.0f - u) * self->f68C;
    self->f3D0 = w;
    self->f3CC = w;
    if (self->s638) {
        if (D_0026185C[0] - self->f640 > 2.0f) self->s638 = 0;
    }
    f32 ang = func_00205778(self->fD4, self->fD0);
    func_00188850(D_00248D20, buf, self->f648 - ang);
    func_001EA918((u8*)self->p660 + 0xD0, buf, D_00274A60, buf2, 0, t);
    self->p660->vt->f88(self->p660, buf2);
    ca[0] = 0x8010FF00;
    cb[0] = 0x800000FF;
    if (self->s638) {
        f32 q;
        if (self->s610 != 2) q = (D_00261858[1] - self->f614) * 0.5f;
        else q = 0.0f;
        f32 z = func_00205210((D_00261858[1] - self->f63C) * 10.0f);
        f32 x0 = D_00274A70[0] + q * (D_00274A70[1] + q * D_00274A70[2]);
        f32 lo = D_00275C60[0];
        f32 hi = D_00275C60[1];
        f32 x = x0 < lo ? lo : (hi < x0 ? hi : x0);
        f32 y = D_00274A80[0] + z * (D_00274A80[1] + z * D_00274A80[2]);
        f32 lo2 = D_00275C60[0];
        f32 hi2 = D_00275C60[1];
        if (y < lo2) y = lo2;
        else if (hi2 < y) y = hi2;
        f32 m = x * y;
        f32 n = 1.0f - m;
        f32 r0 = n * ((u8*)ca)[0] + m * ((u8*)cb)[0];
        f32 r1 = n * ((u8*)ca)[1] + m * ((u8*)cb)[1];
        f32 r2 = n * ((u8*)ca)[2] + m * ((u8*)cb)[2];
        ((u8*)ca)[0] = (s32)r0;
        ((u8*)ca)[2] = (s32)r2;
        ((u8*)ca)[1] = (s32)r1;
    }
    func_00126A48(self, ca[0]);
    *(f32*)(self->p62C + 0x2DC) = self->f670 * self->f630;
    *(f32*)(self->p62C + 0x2E0) = self->f670 * self->f634;
    *(s32*)(self->p62C + 0x32C) = 0;
}

// (if/else with the small path first moved $s0/$s1)
struct Quad_1C21A0 { s32 a, b, c, d; };
struct Obj_1C21A0 { u8 pad[4]; void* f4; };
void func_001C15D8(void* self, void* a, s32 r);
s32 func_0011BE90(void* head, s32 key, void* arg);
void func_0011B008(Quad_1C21A0* q);
void func_0011B018(void* self, Quad_1C21A0* q);
void func_0011B060(Quad_1C21A0* q, s32 mode);
void* func_001C21A0(void* self, Obj_1C21A0* p, s32 n)
{
    if (n < 0x495) {
        s32 r = (s32)func_001C14C0(p, n);
        func_001C15D8(self, p, r);
    } else {
        Quad_1C21A0 q;
        func_0011B008(&q);
        func_0011BE90(p->f4, n, &q);
        func_0011B018(self, &q);
        func_0011B060(&q, 2);
    }
    return self;
}

struct Owner_1C0C08 { u8 pad0[1]; };

void func_0011D8B0(Owner_1C0C08* a0, s32 a1, s32 a2);

extern s32 D_006053E0[];

void func_001C0C08(s32 idx, s32 val)
{
    if (val != D_006053E0[idx]) {
        D_006053E0[idx] = val;
        func_0011D8B0((Owner_1C0C08*)D_00274728, idx, val);
    }
}

struct Self_1C10A8 { u8 pad[0x58]; f32 f58; };

extern f32 D_0024D3B4;
void func_00182C18(Self_1C10A8* self);

void func_001C10A8(Self_1C10A8* self)
{
    func_00182C18(self);
    self->f58 = D_0024D3B4;
}

struct Q_1C1190 { u8 b[16]; };
struct E_1C1190 { s32 a; s32 b; };
struct Obj_1C1190 {
    u8 p0[0x2C]; s32 f2C;
    u8 p30[0x1EF0 - 0x30]; s32 f1EF0; E_1C1190* f1EF4; s32 f1EF8;
};

void func_0011B008(Q_1C1190* q);
s32 func_00137C40(void* src);
void* func_0018D500(u32 size);
s32 func_0011BA28(void* src);
void func_00138518(void* self);
s32 func_0011A630(void);
void func_0011A6C0(u8* a, s32 b);
void func_0011B538(Q_1C1190* q, s32 n);
void func_0011A358(Q_1C1190* out, s32 a, s32 b, Q_1C1190* body);
void func_0011B060(Q_1C1190* q, s32 mode);
void func_001C13E8(Q_1C1190* dst, s32 id, Obj_1C1190* ctx);
void func_0011B0A8(Q_1C1190* a, Q_1C1190* b);
extern s32 D_00275714;
extern u8 D_00259F38[];

void func_001C1190(Obj_1C1190* self, void* arg) {
    Q_1C1190 q0;
    Q_1C1190 q1;
    Q_1C1190 q2;
    s32 i = 0;
    func_0011B008(&q0);
    self->f1EF0 = func_00137C40(arg);
    self->f1EF4 = (E_1C1190*)func_0018D500(self->f1EF0 << 3);
    s32 n1 = func_00137C40(arg);
    s32 n2 = func_00137C40(arg);
    for (i = 0; i < self->f1EF0; i++) {
        {
            E_1C1190* e = self->f1EF4 + i;
            e->a = func_0011BA28(arg);
            e->b = 0;
            if (D_00275714) {
                func_00138518(arg);
                func_00138518(arg);
                func_00138518(arg);
            }
        }
    }
    if (D_00275714) {
        if (n1 > 0) { s32 k = n1; do func_00138518(arg); while (--k); }
        if (n2 > 0) { s32 k = n2; do func_00138518(arg); while (--k); }
    }
    s32 r = func_0011A630();
    i = 0;
    self->f2C = r;
    func_0011A6C0(D_00259F38, r);
    self->f1EF8 = n1;
    func_0011B538(&q0, 0);
    func_0011A358(&q1, self->f2C, self->f1EF8, &q0);
    func_0011B060(&q1, 2);
    if (self->f1EF0 > 0) {
        do {
            func_0011B008(&q1);
            func_001C13E8(&q2, i, self);
            i++;
            func_0011B0A8(&q1, &q2);
            func_0011B060(&q2, 2);
            func_0011B060(&q1, 2);
        } while (i < self->f1EF0);
    }
    func_0011B060(&q0, 2);
}

// NEAR: the entry pointer is loaded into v0 where retail uses v1 (register choice only); five lines differ.

struct Quad_1C13E8 { u8 pad0[16]; };
struct Ent_1C13E8 { s32 a; s32 b; };
struct Ctx_1C13E8 { u8 pad0[0x1EF4]; s32 ents; };

s32 func_0011B008(Quad_1C13E8* q);
s32 func_0011A630(void);
void func_0011A080(Quad_1C13E8* t, s32 a, s32 b);
void func_0011B0A8(Quad_1C13E8* a, Quad_1C13E8* b);
void func_0011B538(Quad_1C13E8* q, s32 n);
void func_0011B018(void* dst, Quad_1C13E8* src);
void func_0011B060(Quad_1C13E8* q, s32 mode);

void* func_001C13E8(void* self, s32 index, Ctx_1C13E8* ctx)
{
    s32 off = index << 3;
    Quad_1C13E8 q;
    Ent_1C13E8* e;
    (void)func_0011B008(&q);
    e = (Ent_1C13E8*)(off + ctx->ents);
    if (e->a != 0 && e->b == 0) {
        Quad_1C13E8 t;
        ((Ent_1C13E8*)(off + ctx->ents))->b = func_0011A630();
        func_0011A080(&t, ((Ent_1C13E8*)(off + ctx->ents))->a, ((Ent_1C13E8*)(off + ctx->ents))->b);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_1C1AD8 { s32 a, b, c, d; };
struct Link_1C1AD8 { u32 pad0; u32 pad4; Link_1C1AD8* next; };
struct Cmd_1C1AD8 { u32 kind; Link_1C1AD8* list; };

extern void func_0011B008(Quad_1C1AD8* q);
extern void func_0011B060(Quad_1C1AD8* q, s32 mode);
extern s32 func_0011B0F8(Link_1C1AD8* l, Quad_1C1AD8* q);
extern void func_0011B570(Quad_1C1AD8* q, s32 v);
extern void func_0011B5B0(Quad_1C1AD8* q, f32 v);
extern void func_0011B5F0(Quad_1C1AD8* q, s32 v);
extern void func_0011B8A8(Quad_1C1AD8* q, s32 v);

s32 func_001C1AD8(Cmd_1C1AD8* cmd, s32* val) {
    Quad_1C1AD8 q;
    Link_1C1AD8* l;
    func_0011B008(&q);
    l = cmd->list;
    if (l) {
        switch (cmd->kind) {
        case 1:
            func_0011B5B0(&q, *(f32*)val);
            break;
        case 0:
            func_0011B5F0(&q, *val);
            break;
        case 2: case 4: case 9: case 10: case 11: case 13:
            break;
        default:
            if (cmd->kind & 0x1000) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
                func_0011B570(&q, *val);
            } else if (cmd->kind & 0x2000) {
                func_0011B8A8(&q, *val);
            }
            break;
        }
        while (l) {
            if (func_0011B0F8(l, &q)) {
                func_0011B060(&q, 2);
                return 1;
            }
            l = l->next;
        }
    }
    func_0011B060(&q, 2);
    return 0;
}

struct __attribute__((aligned(16))) Quad_1C1BF8 {
    s32 type;
    union { s32 i; f32 f; void* p; } u;
    s32 c, d;
};
struct __attribute__((aligned(16))) Blob_1C1BF8 { Quad_1C1BF8 q[3]; };
struct W8_1C1BF8 { s32 a, b; };
struct W12_1C1BF8 { s32 a, b, c; };

void func_0011B008(Quad_1C1BF8* q);
void func_0011B018(Quad_1C1BF8* out, Quad_1C1BF8* q);
void func_0011B060(Quad_1C1BF8* q, s32 mode);
void func_0011B0A8(Quad_1C1BF8* a, void* b);
void func_0011B538(Quad_1C1BF8* q, s32 n);
void func_0011B928(Quad_1C1BF8* a, Quad_1C1BF8* b);
void func_0011B9A8(Quad_1C1BF8* a, Quad_1C1BF8* b);

Quad_1C1BF8* func_001C1BF8(Quad_1C1BF8* out, s32 n, u8* src, u32* types, void** dsts)
{
    Quad_1C1BF8 q;
    Quad_1C1BF8 a;
    Quad_1C1BF8 b;
    Quad_1C1BF8 c;
    s32 i;
    func_0011B008(&q);
    for (i = 0; i < n; i++) {
        func_0011B0A8(&q, src + i * 8);
        u32 t = types[i];
        void* d = dsts[i];
        switch (t) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
        case 20:
            if (q.type == 0x14) {
                goto store;
            }
            func_0011B008(&a);
            func_0011B928(&b, &q);
            func_0011B0A8(&a, &b);
            func_0011B060(&b, 2);
            *(s32*)d = a.u.i;
            func_0011B060(&a, 2);
            break;
        case 1:
            if (q.type == 0x15) {
                *(f32*)d = q.u.f;
            } else {
                func_0011B008(&a);
                func_0011B9A8(&c, &q);
                func_0011B0A8(&a, &c);
                func_0011B060(&c, 2);
                *(f32*)d = a.u.f;
                func_0011B060(&a, 2);
            }
            break;
        case 4:
            *(Blob_1C1BF8*)d = *(Blob_1C1BF8*)q.u.p;
            break;
        case 2:
        case 9:
            *(Quad_1C1BF8*)d = *(Quad_1C1BF8*)q.u.p;
            break;
        case 10:
            *(W8_1C1BF8*)d = *(W8_1C1BF8*)q.u.p;
            break;
        case 11:
            *(W12_1C1BF8*)d = *(W12_1C1BF8*)q.u.p;
            break;
        default:
            if (t & 0x1000) {
                goto store;
            }
            if (t & 0x2000) {
                goto store;
            }
            break;
        case 0:
        store:
            *(s32*)d = q.u.i;
            break;
        case 13:
            break;
        }
    }
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct __attribute__((aligned(16))) Quad_1C15D8 { s32 a, b, c, d; };
struct Desc_1C15D8;
typedef void (*Get_1C15D8)(void* obj, void* out);
typedef void* (*Base_1C15D8)(void* obj, s32 z);
struct Desc_1C15D8 {
    s32 kind;
    u32 flags;
    s32 pad8;
    s32 off;
    s32 imm;
    s32 imm2;
    s32 pad18;
    Base_1C15D8 base;
};
struct Rec3_1C15D8 { s32 a, b, c; };
struct __attribute__((aligned(16))) Q16_1C15D8 { s32 a, b, c, d; };
struct D8_1C15D8 { s32 a, b; };

extern void func_0011B008(Quad_1C15D8* q);
extern void* func_0011AE78(void);
extern void func_0011B8E8(Quad_1C15D8* q, void* v);
extern void func_0011B570(Quad_1C15D8* q, s32 v);
extern void func_0011B5B0(Quad_1C15D8* q, f32 v);
extern void func_0011B5F0(Quad_1C15D8* q, s32 v);
extern void* func_0011C508(void);
extern void func_0011B740(Quad_1C15D8* q, void* v);
extern void* func_0011C618(void);
extern void func_001884E0(void* d, void* s);
extern void func_001884C0(void* d);
extern void func_0011B788(Quad_1C15D8* q, void* v);
extern void* func_0011C748(void);
extern void func_0011B7D0(Quad_1C15D8* q, void* v);
extern void* func_0011C858(void);
extern void func_0011B818(Quad_1C15D8* q, void* v);
extern void* func_0011C968(void);
extern void func_0011B860(Quad_1C15D8* q, void* v);
extern void func_0011B8A8(Quad_1C15D8* q, s32 v);
extern void func_001C1530(Quad_1C15D8* out, void* base, s32 v, Get_1C15D8 cb);
extern void func_0011B0A8(Quad_1C15D8* a, Quad_1C15D8* b);
extern void func_0011B018(void* out, Quad_1C15D8* q);
extern void func_0011B060(Quad_1C15D8* q, s32 mode);

void* func_001C15D8(void* out, void* base, Desc_1C15D8* d)
{
    Quad_1C15D8 q;
    Quad_1C15D8 q2;
    s32 t20, t28, t2c, t30;
    f32 t24;
    char* p;
    Get_1C15D8 fn;
    func_0011B008(&q);
    if (d->flags & 1) {
        s32* r = (s32*)func_0011AE78();
        r[0] = (s32)base;
        r[1] = d->imm;
        r[2] = d->imm2;
        func_0011B8E8(&q, r);
    } else if (d->flags & 2) {
        if (d->flags & 0x1000) {
            p = (char*)d->base(base, 0) + d->off;
        } else {
            p = (char*)base + d->off;
        }
        switch (d->kind) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            func_0011B570(&q, *(s32*)p);
            break;
        case 1:
            func_0011B5B0(&q, *(f32*)p);
            break;
        case 0:
            func_0011B5F0(&q, *(s32*)p);
            break;
        case 2: {
            Q16_1C15D8* r = (Q16_1C15D8*)func_0011C508();
            *r = *(Q16_1C15D8*)p;
            func_0011B740(&q, r);
            break;
        }
        case 4: {
            void* r = func_0011C618();
            func_001884E0(r, p);
            func_0011B788(&q, r);
            break;
        }
        case 9: {
            Q16_1C15D8* r = (Q16_1C15D8*)func_0011C748();
            *r = *(Q16_1C15D8*)p;
            func_0011B7D0(&q, r);
            break;
        }
        case 10: {
            D8_1C15D8* r = (D8_1C15D8*)func_0011C858();
            *r = *(D8_1C15D8*)p;
            func_0011B818(&q, r);
            break;
        }
        case 11: {
            Rec3_1C15D8* r = (Rec3_1C15D8*)func_0011C968();
            *r = *(Rec3_1C15D8*)p;
            func_0011B860(&q, r);
            break;
        }
        case 13:
            break;
        default:
            if (d->kind & 0x1000) {
                func_0011B570(&q, *(s32*)p);
            } else if (d->kind & 0x2000) {
                func_0011B8A8(&q, *(s32*)p);
            }
            break;
        }
    } else {
        if (d->flags & 0x1000) {
            p = (char*)d->base(base, 0);
        } else {
            p = (char*)base;
        }
        if (d->flags & 4) {
            fn = (Get_1C15D8)d->off;
        } else {
            fn = *(Get_1C15D8*)(*(char**)base + d->off);
        }
        switch (d->kind) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            fn(p, &t20);
            func_0011B570(&q, t20);
            break;
        case 1:
            fn(p, &t24);
            func_0011B5B0(&q, t24);
            break;
        case 0:
            fn(p, &t28);
            func_0011B5F0(&q, t28);
            break;
        case 2: {
            void* r = func_0011C508();
            fn(p, r);
            func_0011B740(&q, r);
            break;
        }
        case 4: {
            void* r = func_0011C618();
            fn(p, r);
            func_001884C0(r);
            func_0011B788(&q, r);
            break;
        }
        case 9: {
            void* r = func_0011C748();
            fn(p, r);
            func_0011B7D0(&q, r);
            break;
        }
        case 10: {
            void* r = func_0011C858();
            fn(p, r);
            func_0011B818(&q, r);
            break;
        }
        case 11: {
            void* r = func_0011C968();
            fn(p, r);
            func_0011B860(&q, r);
            break;
        }
        case 13:
            break;
        default:
            if (d->kind < 0) {
                func_001C1530(&q2, base, d->kind & 0x7fffffff, fn);
                func_0011B0A8(&q, &q2);
                func_0011B060(&q2, 2);
            } else if (d->kind & 0x1000) {
                fn(p, &t2c);
                func_0011B570(&q, t2c);
            } else if (d->kind & 0x2000) {
                fn(p, &t30);
                func_0011B8A8(&q, t30);
            }
            break;
        }
    }
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

// EXACT: callee func_001EA728 declared with float params first

struct Obj_1C3FC8;
struct Vt_1C3FC8 {
    u8 pad[0x94];
    void (*f94)(Obj_1C3FC8* self, void* q);
};
struct __attribute__((aligned(16))) Quad_1C3FC8 { f32 v[4]; };
struct Obj_1C3FC8 {
    Vt_1C3FC8* vt;
};

extern f32 D_00261858[];
extern Quad_1C3FC8 D_00248D30;
extern u8 D_00274AA8[];
extern s32 D_0026E228;
extern u8 D_00261EF0[];
extern u8 D_0026FF68[];
extern f32 D_0024D560;

f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);
void func_001EA728(f32 x, f32 y, f32 z, u8* a, void* out);
void func_00151E20(u8* a, f32 b);
void func_00194D30(u8* a, s32 b, s32 c);
void func_0012C918(void* a, Obj_1C3FC8* b, s32 c, void* d, f32 e, f32 f);

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))

void func_001C3FC8(Obj_1C3FC8* self, s32 state)
{
    void* s2;
    f32 f12;
    if (state == W(self, 0x610)) return;
    if (W(self, 0x610) == 2) {
        f32 t = D_00261858[1];
        W(self, 0x694) = 3;
        F(self, 0x640) = t;
    }
    W(self, 0x670) = 0;
    if (state < 4) if (state >= 2) {
        Quad_1C3FC8 q;
        f32 a = func_00205778(F(self, 0x154), F(self, 0x150));
        f32 b = func_001EA408(a + 3.14159274f);
        F(self, 0x644) = b;
        F(self, 0x648) = b;
        q = D_00248D30;
        f32 r = func_00205778(F(self, 0xD4), F(self, 0xD0));
        func_001EA728(r, F(self, 0x644), 0.0f, D_00274AA8, (u8*)&q + 8);
        self->vt->f94(self, &q);
        W(self, 0x694) = 0;
        D_0026E228 = -1;
        if (state == 3) func_00151E20(D_00261EF0, 1.0f);
    }
    f12 = 0.0f;
    switch (state) {
    case 0: s2 = P(self, 0x618); break;
    case 1: s2 = P(self, 0x61C); break;
    case 2: s2 = P(self, 0x620); F(self, 0x640) = D_0024D560; break;
    case 3: s2 = P(self, 0x624); break;
    case 4:
        func_00194D30(D_0026FF68, 0, 0x1A);
        s2 = P(self, 0x624);
        f12 = F(s2, 0x34);
        break;
    }
    func_0012C918(s2, self, 1, (u8*)self + 0x628, f12, 1.0f);
    W(self, 0x610) = state;
    F(self, 0x614) = D_00261858[1];
}
