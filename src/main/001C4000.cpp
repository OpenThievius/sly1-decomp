// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1C4180 { u8 pad[0x698]; s32 count; s32 items[1]; };

void func_001C4180(Obj_1C4180* self, s32 value)
{
    s32 n = self->count;
    self->items[n] = value;
    self->count = n + 1;
}

void func_00192B58(void* self);
void func_001C4C20(void* self);

void func_001C4ED0(void* self)
{
    func_00192B58(self);
    func_001C4C20(self);
}

typedef s32 (*VFn_C5338)(void* self);
struct Obj_C5338 { VFn_C5338* vtbl; };
struct Out_C5338 { u8 pad[0x94]; f32 f94; s32 f98; };
extern f32 D_00274B74;

void func_001C5338(Obj_C5338* self, Out_C5338* out)
{
    if (self->vtbl[0x168 / 4](self)) {
        f32 d = D_00274B74;
        out->f98 = 0;
        out->f94 = d;
    } else {
        out->f94 = 0.0f;
        out->f98 = 0;
    }
}

struct __attribute__((aligned(16))) Quad_C5D58 { s32 a, b, c, d; };
typedef void (*VFn_C5D58)(void* self, void* arg);
struct Obj_C5D58 {
    VFn_C5D58* vtbl;
    u8 pad0[0xD0 - 4];
    f32 fD0;
    f32 fD4;
    u8 pad1[0x160 - 0xD8];
    Quad_C5D58 q160;
    u8 pad2[0x638 - 0x170];
    f32 f638;
};
f32 func_00205778(f32 a, f32 b);
void func_001EA728(void* p, void* out, f32 a, f32 b, f32 c);

void func_001C5D58(Obj_C5D58* self)
{
    Quad_C5D58 q = self->q160;
    f32 r = func_00205778(self->fD4, self->fD0);
    func_001EA728((u8*)self + 0x6E0, &q.c, r, self->f638, 0.0f);
    self->vtbl[0x94 / 4](self, &q);
}

typedef s32 (*VFn_C7B60)(void* self);
struct Obj_C7B60 {
    VFn_C7B60* vtbl;
    u8 pad0[0x724 - 4];
    s32 f724;
    u8 pad1[0xB84 - 0x728];
    s32 fB84;
    s32 fB88;
};
struct Glob_C7B60 { u8 pad[0x275C]; s32 f275C; };
extern Glob_C7B60* D_00262E10;
void func_001C8F20(Obj_C7B60* self, s32 a1, s32 a2);

void func_001C7B60(Obj_C7B60* self)
{
    if (self->fB84 != 0) return;
    if (self->fB88 != 0) return;
    if (D_00262E10 != 0 && D_00262E10->f275C != 0) return;
    for (;;) {
        s32 v = self->vtbl[0x174 / 4](self);
        if (v == self->f724) break;
        func_001C8F20(self, v, 0);
    }
}

void func_001B9338(void* self);
void func_001C5148(void* self);

void func_001C5118(void* self)
{
    func_001B9338(self);
    func_001C5148(self);
}

void func_001C53A8(void);

void func_001C5388(void)
{
    func_001C53A8();
}

void func_001C53A8(void)
{
}

struct Obj_1C53E0;
typedef s32 (*VFn_1C53E0)(void* self);
struct Obj_1C53E0 { VFn_1C53E0* vtbl; };
void func_001C54D0(Obj_1C53E0* self, void* b, s32 c);

void func_001C53E0(Obj_1C53E0* self, void* b, s32 c)
{
    if (self->vtbl[90](self)) {
        func_001C54D0(self, b, c);
    }
}

void func_001C5C10(void* a, s32 b, s32 c, s32 d);

void func_001C5BF0(void* a0, s32 a1, s32 unused2, s32 unused3, s32 a4, s32 a5)
{
    func_001C5C10(a0, a1, a4, a5);
}

struct Vec2_1C4FA0 { f32 x; f32 y; };
typedef void (*VFn_1C4FA0)(void* self);
struct Obj_1C4FA0 { VFn_1C4FA0* vtbl; u8 pad0[0x630 - 4]; f32 f630; u8 pad1[0x638 - 0x634]; f32 f638; };

void func_001B97E0(void* self, void* src);
f32 func_00205778(f32 a, f32 b);

void func_001C4FA0(Obj_1C4FA0* self, Vec2_1C4FA0* v)
{
    func_001B97E0(self, v);
    f32 r = func_00205778(v->y, v->x);
    self->f638 = r;
    self->f630 = r;
    self->vtbl[88](self);
}

extern u8 D_00274BF0[];

struct Obj_1C6E58 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad1[0x638 - 0x18];
    f32 f638;
    u8 pad2[0x2200 - 0x63C];
    s32 f2200;
    s32 f2204;
    s32 f2208;
};

struct Tmp_1C6E58 {
    f32 pair[4];
    s32 out;
};

void func_001C6AA8(Obj_1C6E58* self, s32 n, void* table, s32* out, f32* pair, f32 lo, f32 hi);
f32 func_00205778(f32 x, f32 y);
void func_001C5D58(Obj_1C6E58* self);

void func_001C6E58(Obj_1C6E58* self)
{
    Tmp_1C6E58 t;
    func_001C6AA8(self, 8, D_00274BF0, &t.out, t.pair, 0.25f, 1.0f);
    self->f2204 = 0;
    self->f2200 = t.out;
    self->f2208 = 0;
    if (t.out != 0) {
        self->f638 = func_00205778(t.pair[1], t.pair[0]);
        func_001C5D58(self);
    }
}

extern u8 D_00274C00[];

struct Obj_1C6ED0 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad1[0x638 - 0x18];
    f32 f638;
    u8 pad2[0x2200 - 0x63C];
    s32 f2200;
    s32 f2204;
    s32 f2208;
};

struct Tmp_1C6ED0 {
    f32 pair[4];
    s32 out;
};

void func_001C6AA8(Obj_1C6ED0* self, s32 n, void* table, s32* out, f32* pair, f32 lo, f32 hi);
f32 func_00205778(f32 x, f32 y);
void func_001C5D58(Obj_1C6ED0* self);

void func_001C6ED0(Obj_1C6ED0* self)
{
    Tmp_1C6ED0 t;
    func_001C6AA8(self, 4, D_00274C00, &t.out, t.pair, 0.25f, 3.15f);
    self->f2204 = 0;
    self->f2200 = t.out;
    self->f2208 = 0;
    if (t.out != 0) {
        self->f638 = func_00205778(t.pair[1], t.pair[0]);
        func_001C5D58(self);
    }
}

struct Obj_1C71E0 {
    u8 pad0[0x14];
    s32 f14;
    u8 pad1[0x924 - 0x18];
    s32 f924;
    s32 f928;
    u8 pad2[0xAF8 - 0x92C];
    s32 fAF8;
    s32 fAFC;
    s32 fB00;
    u8 pad3[0xB4C - 0xB04];
    s32 fB4C;
};

void func_001249A8(Obj_1C71E0* self);
s32 func_0015A448(s32 a, s32 b, Obj_1C71E0* self);
void func_001CAB10(Obj_1C71E0* self);
s32 func_0015A418(s32 a, s32 b, s32 c, Obj_1C71E0* self);
void func_00159478(s32* p, Obj_1C71E0* self);

void func_001C71E0(Obj_1C71E0* self)
{
    s32 v;
    func_001249A8(self);
    if (self->f924 != -1) {
        self->f928 = func_0015A448(self->f14, self->f924, self);
    }
    if (self->fB4C != -1) {
        func_001CAB10(self);
    }
    v = self->fAF8;
    if (v != 0) {
        if (self->fAFC != -1) {
            self->fB00 = func_0015A418(self->f14, 0x101, self->fAFC, self);
        }
    } else {
        func_00159478(&self->fB00, self);
    }
}

typedef s32 (*VFn_1C7278)(void* self);
struct Obj_1C7278 { VFn_1C7278* vtbl; };

s32 func_001C7278(Obj_1C7278* self)
{
    return self->vtbl[7](self);
}

void func_00192820(void* self);
void func_001CB648(void* list, void* value);

struct Obj_1C74E8 { u8 pad0[0x720]; void* list; };

void func_001C74E8(Obj_1C74E8* self)
{
    func_00192820(self);
    if (self->list != 0) {
        func_001CB648(self->list, self);
    }
}

struct __attribute__((aligned(16))) Quad_1C4458 { s32 a; s32 b; s32 c; s32 d; };
struct __attribute__((packed)) Pack8_1C4458 { u64 v; };
struct Blk12_1C4458 { Pack8_1C4458 a; s32 b; };
struct Obj_1C4458 { u8 p0[0x360]; f32 f360; u8 p364[0x6F0 - 0x364]; Quad_1C4458 f6F0; f32 f700; };

extern f32 D_00274B20;
extern u8 D_00274B30[];
extern u8 D_00274B40[];
extern u8 D_00274B50[];

void func_001921A8(void* self);
void func_001C5E50(void* self, f32 x);

void func_001C4458(Obj_1C4458* self)
{
    func_001921A8(self);
    self->f700 = 1.0f;
    self->f360 = D_00274B20;
    func_001C5E50(self, 1.0f);
    self->f6F0 = *(Quad_1C4458*)D_00274B30;
    *(Blk12_1C4458*)((u8*)self + 0x710) = *(Blk12_1C4458*)D_00274B40;
    *(Blk12_1C4458*)((u8*)self + 0x704) = *(Blk12_1C4458*)D_00274B50;
}

s32 func_001C4F00(void) { return 3; }

struct Sub_1C4578 { u8 pad[0x98]; s32 f98; u8 pad2[0xB0 - 0x9C]; s32 fB0; };
struct Holder_1C4578 { u8 pad[0x224]; Sub_1C4578* f224; };
struct Obj_1C4578 { u8 pad[0x618]; Holder_1C4578* f618; Holder_1C4578* f61C; };

void func_001C4578(Obj_1C4578* self, s32 a1)
{
    Holder_1C4578* h = self->f61C;
    if (h != 0) {
        Sub_1C4578* s = h->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else s->f98 &= ~2;
        }
    }
    Holder_1C4578* v = self->f618;
    if (v != 0) {
        Sub_1C4578* s = v->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else self->f61C->f224->f98 &= ~2;
        }
    }
}

typedef s32 (*VFn_1C4F08)(void* self);
struct Obj_1C4F08 { VFn_1C4F08* vtbl; u8 pad[0x470 - 4]; s32 f470; };
void func_001BC828(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_001C4F08(Obj_1C4F08* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 old = self->f470;
    self->f470 = self->vtbl[0x164 / 4](self);
    func_001BC828(self, a1, a2, a3, a4, a5);
    self->f470 = old;
}

struct __attribute__((aligned(16))) Ent_1C4790 { u8 pad0[0x40]; f32 f40; u8 pad1[0x70 - 0x44]; };
struct Obj_1C4790 { u8 pad0[0x50]; s32 f50; u8 pad1[0xD0 - 0x54]; f32 fD0; };
s32 func_00141C90(void* self, void* a1, void* a2, void* a3, s32 a4, void* a5);

void func_001C4790(void* unused, void* a1, void* a2, Obj_1C4790* self)
{
    Ent_1C4790 ents[2];
    s32 n;
    s32 idx;
    if (self->f50 == 0) return;
    n = func_00141C90(a1, a2, (u8*)self + 0x70, (u8*)self + 0x60, 2, ents);
    idx = 0;
    if (n > 0) {
        if (ents[0].f40 == 0.0f) idx = 1;
    }
    if (!(idx < n)) return;
    if (ents[idx].f40 < self->fD0) {
        *(Ent_1C4790*)((u8*)self + 0x90) = ents[idx];
    }
}

struct Obj_1C4A80 {
    u8 pad0[0x140];
    u8 f140[0x6C4 - 0x140];
    f32 f6C4;
    f32 f6C8;
};

extern f32 D_0026185C[];
extern f32 D_00274B60[];
extern s32 D_00605548;
f32 func_001EAFE0(f32 x, f32 y);
s32 func_001EAA70(s32 a, s32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, u8* a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_001C0EC0();

void func_001C4A80(Obj_1C4A80* self, f32* p, f32 f) {
    f32 old = self->f6C4;
    f32 ang;
    self->f6C4 = f;
    if (D_0026185C[0] - self->f6C8 < D_00274B60[0]) return;
    if (func_001EAFE0(f - p[0], 1.0f) < 0.5f && 0.5f < func_001EAFE0(old - p[0], 1.0f)) {
        ang = p[2];
    } else if (func_001EAFE0(self->f6C4 - p[1], 1.0f) < 0.5f && 0.5f < func_001EAFE0(old - p[1], 1.0f)) {
        ang = p[3];
    } else {
        return;
    }
    s32 idx = func_001EAA70(0x47, 0x4A);
    if (idx == D_00605548) {
        s32 x = idx - 0x46;
        idx = x % 4 + 0x47;
    }
    D_00605548 = idx;
    func_001BFCD8(idx, 0, 0, self->f140, 0, 0, 1000.0f, 200.0f, ang, 0.0f, 0.0f);
    func_001C0EC0();
}

struct Obj_1C72A0;
typedef void (*VFnSelf_1C72A0)(void* self, void* item, s32 flag);
typedef void (*VFnObj_1C72A0)(void* self);
struct Obj_1C72A0 { VFnObj_1C72A0* vtbl00; u8 pad04[0x534]; u64 flags538; };
struct Slot_1C72A0 { void* ptr00; void* aux04; };
struct Elem_1C72A0 { s32 key00; Obj_1C72A0* obj04; s32 c08; };
struct Self_1C72A0 {
    VFnSelf_1C72A0* vtbl00;
    u8 pad04[0x10];
    void* host14;
    u8 pad18[0x6DC - 0x18];
    void* f6DC;
    u8 pad6E0[0x700 - 0x6E0];
    f32 f700;
    u8 pad704[0x720 - 0x704];
    void* f720;
    u8 pad724[0x874 - 0x724];
    Slot_1C72A0 slots874[17];
    u8 pad8FC[0xA78 - 0x8FC];
    s32 count_A78;
    Elem_1C72A0 elems_A7C[1];
    u8 padA88[0xB04 - 0xA88];
    void* f_B04;
    s32 f_B08;
    void* f_B0C;
    s32 f_B10;
};

void func_001C44F0(void* self);
void func_00124DF8(void* self, s32 a1, u8* table);
void* func_001CB5B8(void* host);
void func_001CB648(void* a, void* b);
void func_001CA7C0(void* self);
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void* func_0015A838(void* host, s32 a1, s32 a2, void* ctx);
void func_001C5EA8(void* self, f32 v);
void func_001C8F20(void* node, s32 kind, s32 flag);
s32 func_00141008(u8* table, s32 v);
void func_001DBCC8(void* host, void* fn, void* ctx, s32 a3, s32 a4);
extern u8 D_00274C30[];
extern u8 D_00261420[];

void func_001C72A0(Self_1C72A0* self)
{
    func_001C44F0(self);
    func_00124DF8(self, 2, D_00274C30);
    if (self->f720 == 0) {
        void* t = func_001CB5B8(self->host14);
        self->f720 = t;
        func_001CB648(t, self);
    }
    func_001CA7C0(self);
    for (s32 i = 0; i < 17; i++) {
        void* item = self->slots874[i].ptr00;
        if (item != 0) {
            self->f6DC = item;
            self->slots874[16].aux04 = item;
            self->vtbl00[0x38](self, item, 1);
            break;
        }
    }
    s32 j = 0;
    if (self->count_A78 > 0) {
        u64 bit = 0x8000;
        bit <<= 28;
        Elem_1C72A0* e = self->elems_A7C;
        do {
            Obj_1C72A0* o = (Obj_1C72A0*)func_0015A418(self->host14, 0x101, e->key00, self);
            e->obj04 = o;
            if (o != 0) {
                o->flags538 |= bit;
                e->obj04->vtbl00[7](e->obj04);
            }
            e++;
            j++;
        } while (j < self->count_A78);
    }
    if (self->f_B04 != 0) {
        if (self->f_B08 != -1) {
            self->f_B0C = func_0015A418(self->host14, 0x101, self->f_B08, self);
        }
    } else {
        self->f_B0C = func_0015A838(self->host14, 0x101, 0x8C, self);
    }
    func_001C5EA8(self, self->f700);
    func_001C8F20(self, 0, 0);
    if (func_00141008(D_00261420, self->f_B10)) {
        func_001DBCC8(self->host14, (void*)func_001C7278, self, 0, 0);
    }
}

struct Obj_1C6890 {
    u8 pad0[0x21C4];
    s32 f21C4;
    u8 pad1[0x2200 - 0x21C8];
    void* p2200;
    s32 f2204;
    s32 f2208;
    u8 blk220C[0x14];
    u8 pad2[0x223C - 0x2220];
    s32 f223C;
};

s32 func_00182FC8(void* p);
void func_001C61E0(Obj_1C6890* self, s32 mode);
void func_0019D2A8(Obj_1C6890* self, s32 v, void* p);
void func_0019D338(Obj_1C6890* self, s32 v, s32 w, void* blk);

void func_001C6890(Obj_1C6890* s)
{
    if (s->p2200 != 0 && func_00182FC8(s->p2200) == 0) {
        s32 v = s->f223C;
        s->p2200 = 0;
        s->f2204 = 0;
        if (v != 0) {
            return;
        }
        func_001C61E0(s, -1);
    }
    if (s->f223C != 0) {
        return;
    }
    void* p = s->p2200;
    if (p != 0) {
        func_0019D2A8(s, s->f21C4, p);
        return;
    }
    if (s->f2208 != 0) {
        func_0019D338(s, s->f21C4, s->f2208, s->blk220C);
    }
}

struct Frame_1C6D00 { f32 x; f32 y; f32 z; u8 pad[4]; s32 n; };
struct Out_1C6D00 { f32 a; u8 pad[0xC - 4]; f32 b; };
struct Obj_1C6D00 {
    u8 pad0[0x638];
    f32 f638;
    u8 pad1[0x2200 - 0x63C];
    s32 f2200;
    s32 f2204;
    s32 f2208;
    u8 pad2[0x2220 - 0x220C];
    s32 f2220;
};

extern u8 D_00274BE0[];
extern f32 D_00274BD8;

void func_001C6AA8(Obj_1C6D00* self, s32 mode, void* tbl, s32* nOut, Frame_1C6D00* f, f32 a, f32 b);
void func_001399F8(void* ctx, s32 n, s32 m, Out_1C6D00* out);
f32 func_00205778(f32 a, f32 b);
void func_001C5D58(Obj_1C6D00* self);

void func_001C6D00(Obj_1C6D00* s, Out_1C6D00* out, void* ctx)
{
    Frame_1C6D00 fr;
    f32 k = 1.60000002f;
    if (s->f2220 == 0) {
        k = 3.1500001f;
    }
    func_001C6AA8(s, 2, D_00274BE0, &fr.n, &fr, 0.150000006f, k);
    f32 t;
    if (fr.n != 0) {
        f32 v = (fr.z - -50.0f) * 0.0090909088f;
        f32 hi = 1.0f;
        f32 lo = 0.0f;
        if (v < lo) {
            t = lo;
        } else if (hi < v) {
            t = 1.0f;
        } else {
            t = v;
        }
    } else {
        t = 1.0f;
    }
    if (D_00274BD8 >= 0.0f) {
        t = D_00274BD8;
    }
    out->a = 1.0f - t;
    out->b = t;
    func_001399F8(ctx, 0xC, 2, out);
    s->f2204 = 0;
    s->f2200 = fr.n;
    s->f2208 = 0;
    if (fr.n != 0 && s->f2220 == 0) {
        s->f638 = func_00205778(fr.y, fr.x);
        func_001C5D58(s);
    }
}

struct Obj_1C7188 {
    u8 pad0[0x720];
    s32 f720;
    u8 pad1[0xB10 - 0x724];
    s32 fB10;
    u8 pad2[0xB74 - 0xB14];
    s32 fB74;
};

void func_001921E8(Obj_1C7188* self, s32 v);

void func_001C7188(Obj_1C7188* self, s32 v)
{
    s32 b = self->fB10;
    s32 a = self->f720;
    func_001921E8(self, v);
    self->fB10 = b;
    self->f720 = a;
    self->fB74 = v;
}

struct __attribute__((aligned(16))) Blk48_1C44F0 { s32 a, b, c, d, e, f, g, h, i, j, k, l; };
struct Obj_1C44F0 { u8 p0[0x610]; s32 f610; s32 f614; u8 p618[0x620 - 0x618]; s32 f620; s32 f624; s32 f628; s32 f62C; u8 p630[0x660 - 0x630]; Blk48_1C44F0 f660; };

extern u8 D_00274AD8[];
extern u8 D_002483D0[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* table);
void func_001C4578(void* self, s32 a1);

void func_001C44F0(Obj_1C44F0* self)
{
    func_00124A48(self);
    func_00124DF8(self, 6, D_00274AD8);
    func_001C4578(self, 1);
    if (self->f628 == 0) {
        self->f610 = self->f620;
    } else {
        self->f610 = self->f628;
    }
    if (self->f62C == 0) {
        self->f614 = self->f624;
    } else {
        self->f614 = self->f62C;
    }
    Blk48_1C44F0* dst = &self->f660;
    *dst = *(Blk48_1C44F0*)D_002483D0;
}

struct Obj_1C7AE0 { u8 p0[0x638]; f32 f638; u8 p63C[0xB1C - 0x63C]; s32 fB1C; u8 pB20[4]; f32 fB24; };

extern u8 D_00248D20[];

s32 func_001CB578(void* self);
void func_001892A0(f32 a, f32 b, void* out);
void func_00188850(void* table, f32 x, void* out);

void func_001C7AE0(Obj_1C7AE0* self, f32 x, f32 y)
{
    if (func_001CB578(self) != 0) return;
    s32 t = self->fB1C;
    self->f638 = x;
    self->fB24 = y;
    if (t != 0) {
        func_001892A0(x, y, (u8*)self + 0x660);
    } else {
        func_00188850(D_00248D20, x, (u8*)self + 0x660);
    }
}
