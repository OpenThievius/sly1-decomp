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

struct Arg_1C06D8;

extern u8 D_00274758[];
extern void* D_002623C0;

void func_0018D800(Arg_1C06D8* dst, u8* src, s32 count);
void func_001C05D0(f32 x);
void func_001C0600(Arg_1C06D8* column);
void func_001C0760(Arg_1C06D8* flag);
s32 func_001C0790(Arg_1C06D8* value);

void func_001C06D8(void)
{
    func_0018D800((Arg_1C06D8*)&D_00274838[0][0], D_00274758, 0xB0);
    func_001C05D0(1.0f);
    for (s32 i = 0; i < 4; i++) {
        func_001C0600((Arg_1C06D8*)i);
    }
    func_001C0760((Arg_1C06D8*)(*(s32*)((u8*)D_002623C0 + 0x19EC) & 0x80));
    func_001C0790((Arg_1C06D8*)(*(s32*)((u8*)D_002623C0 + 0x19EC) & 0x40));
}

struct Obj_1C0950 { u8 pad[0x2328]; };
struct Arg_1C0950;

extern s32 D_00274808[];

void func_0011E328(Arg_1C0950* a, s32 b);
void func_0011E360(Arg_1C0950* a, s32 b, s32 c);

void func_001C0950(Obj_1C0950* self)
{
    s32 n = *(s32*)((u8*)self + 0x2348);
    if (n >= 2) {
        s32 m = n - 1;
        *(s32*)((u8*)self + 0x2348) = m;
        s32 i = n - 2;
        func_0011E328((Arg_1C0950*)2, D_00274808[*(s32*)((u8*)self + (i << 3) + 0x2328)]);
        s32 j = *(s32*)((u8*)self + 0x2348) - 1;
        s32 v = *(s32*)((u8*)self + (j << 3) + 0x232C);
        func_0011E360((Arg_1C0950*)2, v, v);
    }
}

extern s32 D_00274808[];

void func_0011E328(s32 a, s32 b);
void func_0011E360(s32 a, s32 b, s32 c);

struct Pair_1C08B0 { s32 first; s32 second; };
struct Obj_1C08B0 { u8 pad[0x2328]; Pair_1C08B0 pairs[4]; s32 count; };

void func_001C08B0(Obj_1C08B0* self, s32 index, s32 value)
{
    if ((u32)self->count < 4) {
        func_0011E328(2, D_00274808[index]);
        func_0011E360(2, value, value);
        self->pairs[self->count].first = index;
        self->pairs[self->count].second = value;
        self->count++;
    }
}

struct Tmp_1C1A28 { s32 w0; s32 w1; s32 w2; s32 w3; s32 w4; s32 w5; s32 w6; s32 w7; };
struct Obj_1C1A28 { s32 w0; s32 w1; s32 w2; s32 w3; };
struct Node_1C1A28 { s32 w0; s32 w1; Node_1C1A28* next; };
struct List_1C1A28 { s32 value; Node_1C1A28* first; Node_1C1A28* last; };

void func_001F5C0C(void* dst, s32 value, s32 size);
Node_1C1A28* func_0011AF28(void);
void func_001C15D8(void* self, void* a, Tmp_1C1A28* r);
void func_0011B0A8(Node_1C1A28* a, void* b);
void func_0011B060(void* p, s32 mode);

s32 func_001C1A28(List_1C1A28* self, void* a1)
{
    Tmp_1C1A28 tmp;
    Obj_1C1A28 o;
    Node_1C1A28* n;
    func_001F5C0C(&tmp, 0, 0x20);
    tmp.w0 = self->value;
    tmp.w1 = 2;
    tmp.w3 = 0;
    n = func_0011AF28();
    func_001C15D8(&o, a1, &tmp);
    func_0011B0A8(n, &o);
    func_0011B060(&o, 2);
    if (self->first != 0) {
        self->last->next = n;
    } else {
        self->first = n;
    }
    self->last = n;
    return 1;
}
