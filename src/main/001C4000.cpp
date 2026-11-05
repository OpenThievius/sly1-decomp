// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "fpu.h"
#include "globals.h"

void func_001C4180(C1D* self, s32 value)
{
    s32 n = self->f698;
    self->f69C[n] = value;
    self->f698 = n + 1;
}

void func_00192B58(void* self);
void func_001C4C20(void* self);

void func_001C4ED0(C06* self)
{
    func_00192B58(self);
    func_001C4C20(self);
}

typedef s32 (*VFn_C5338)(void* self);
struct Out_C5338 { u8 pad[0x94]; f32 f94; s32 f98; };
extern f32 D_00274B74;

void func_001C5338(C06* self, Out_C5338* out)
{
    if (((VFn_C5338*)self->desc)[0x168 / 4](self)) {
        f32 d = D_00274B74;
        out->f98 = 0;
        out->f94 = d;
    } else {
        out->f94 = 0.0f;
        out->f98 = 0;
    }
}

f32 func_00205778(f32 a, f32 b);
void func_001EA728(void* p, void* out, f32 a, f32 b, f32 c);

void func_001C5D58(C06* self)
{
    Vec02 q = self->v160;
    f32 r = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    func_001EA728((u8*)self + 0x6E0, &q.z, r, self->f638, 0.0f);
    self->desc02()->m21(self, &q);
}

typedef s32 (*VFn_C7B60)(void* self);
void func_001C8F20(C08* self, s32 a1, s32 a2);

void func_001C7B60(C08* self)
{
    if (self->fB84 != 0) return;
    if (self->fB88 != 0) return;
    if (D_00262E10 != 0 && D_00262E10->f275C != 0) return;
    for (;;) {
        s32 v = ((VFn_C7B60*)self->desc)[0x174 / 4](self);
        if (v == self->f724) break;
        func_001C8F20(self, v, 0);
    }
}

void func_001B9338(void* self);
void func_001C5148(void* self);

void func_001C5118(C06* self)
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

typedef s32 (*VFn_1C53E0)(void* self);
void func_001C54D0(C06* self, void* b, s32 c);

void func_001C53E0(C06* self, void* b, s32 c)
{
    if (((VFn_1C53E0*)self->desc)[90](self)) {
        func_001C54D0(self, b, c);
    }
}

void func_001C5C10(void* a, s32 b, s32 c, s32 d);

void func_001C5BF0(C06* a0, s32 a1, s32 unused2, s32 unused3, s32 a4, s32 a5)
{
    func_001C5C10(a0, a1, a4, a5);
}

struct Vec2_1C4FA0 { f32 x; f32 y; };
typedef void (*VFn_1C4FA0)(void* self);
void func_001B97E0(void* self, void* src);
f32 func_00205778(f32 a, f32 b);

void func_001C4FA0(C06* self, Vec2_1C4FA0* v)
{
    func_001B97E0(self, v);
    f32 r = func_00205778(v->y, v->x);
    self->f638 = r;
    self->f630 = r;
    ((VFn_1C4FA0*)self->desc)[88](self);
}

extern f32 D_00274BF0[4];

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

extern f32 D_00274C00[4];

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

void func_001249A8(C08* self);
s32 func_0015A448(s32 a, s32 b, C08* self);
void func_001CAB10(C08* self);
s32 func_0015A418(s32 a, s32 b, s32 c, C08* self);
void func_00159478(s32* p, C08* self);

void func_001C71E0(C08* self)
{
    s32 v;
    func_001249A8(self);
    if (self->f924 != -1) {
        self->f928 = func_0015A448((s32)self->world, self->f924, self);
    }
    if (self->fB4C != -1) {
        func_001CAB10(self);
    }
    v = self->fAF8;
    if (v != 0) {
        if (self->fAFC != -1) {
            self->fB00 = func_0015A418((s32)self->world, 0x101, self->fAFC, self);
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

void func_001C74E8(C08* self)
{
    func_00192820(self);
    if (self->f720 != 0) {
        func_001CB648(self->f720, self);
    }
}

struct __attribute__((aligned(16))) Quad_1C4458 { s32 a; s32 b; s32 c; s32 d; };
struct __attribute__((packed)) Pack8_1C4458 { u64 v; };
struct Blk12_1C4458 { Pack8_1C4458 a; s32 b; };
extern f32 D_00274B20;
extern Quad_1C4458 D_00274B30;
extern s32 D_00274B40[4];
extern s32 D_00274B50[3];

void func_001921A8(void* self);
void func_001C5E50(void* self, f32 x);

void func_001C4458(C06* self)
{
    func_001921A8(self);
    self->f700 = 1.0f;
    self->f360 = D_00274B20;
    func_001C5E50(self, 1.0f);
    (*(Quad_1C4458*)&self->v6F0) = D_00274B30;
    *(Blk12_1C4458*)((u8*)self + 0x710) = *(Blk12_1C4458*)D_00274B40;
    *(Blk12_1C4458*)((u8*)self + 0x704) = *(Blk12_1C4458*)D_00274B50;
}

s32 func_001C4F00(void) { return 3; }

struct Sub_1C4578 { u8 pad[0x98]; s32 f98; u8 pad2[0xB0 - 0x9C]; s32 fB0; };
struct Holder_1C4578 { u8 pad[0x224]; Sub_1C4578* f224; };

void func_001C4578(C06* self, s32 a1)
{
    Holder_1C4578* h = (Holder_1C4578*)self->f61C;
    if (h != 0) {
        Sub_1C4578* s = h->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else s->f98 &= ~2;
        }
    }
    Holder_1C4578* v = (Holder_1C4578*)self->f618;
    if (v != 0) {
        Sub_1C4578* s = v->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else ((Holder_1C4578*)self->f61C)->f224->f98 &= ~2;
        }
    }
}

void func_001BC828(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_001C4F08(C06* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 old = self->mode470;
    self->mode470 = self->desc06()->m55(self);
    func_001BC828(self, a1, a2, a3, a4, a5);
    self->mode470 = old;
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

extern f32 D_0026185C[];
f32 D_00274B60[1] = { 0.1f };
extern s32 D_00605548;
f32 func_001EAFE0(f32 x, f32 y);
s32 func_001EAA70(s32 a, s32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, u8* a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_001C0EC0();

void func_001C4A80(C07* self, f32* p, f32 f) {
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
    func_001BFCD8(idx, 0, 0, (u8*)&self->v140, 0, 0, 1000.0f, 200.0f, ang, 0.0f, 0.0f);
    func_001C0EC0();
}

typedef void (*VFnSelf_1C72A0)(void* self, void* item, s32 flag);
void func_001C44F0(C06* self);
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
extern s32 D_00274C30[8];
struct Ent_274AD8 { s32 a; s32 b; s32 c; };
extern Ent_274AD8 D_00274AD8[6];

extern u8 D_00261420[];

void func_001C72A0(C08* self)
{
    func_001C44F0(self);
    func_00124DF8(self, 2, (u8*)D_00274C30);
    if (self->f720 == 0) {
        void* t = func_001CB5B8(self->world);
        self->f720 = t;
        func_001CB648(t, self);
    }
    func_001CA7C0(self);
    for (s32 i = 0; i < 17; i++) {
        void* item = self->f870[i].obj;
        if (item != 0) {
            self->f6DC = item;
            self->f8F8 = item;
            ((VFnSelf_1C72A0*)self->desc)[0x38](self, item, 1);
            break;
        }
    }
    s32 j = 0;
    if (self->fA78 > 0) {
        u64 bit = 0x8000;
        bit <<= 28;
        Elem08* e = self->fA7C;
        do {
            C03* o = (C03*)func_0015A418(self->world, 0x101, e->key, self);
            e->obj = o;
            if (o != 0) {
                o->flags538 |= bit;
                ((C03*)e->obj)->desc->m03((C03*)e->obj);
            }
            e++;
            j++;
        } while (j < self->fA78);
    }
    if (self->fB04 != 0) {
        if (self->fB08 != -1) {
            self->fB0C = func_0015A418(self->world, 0x101, self->fB08, self);
        }
    } else {
        self->fB0C = func_0015A838(self->world, 0x101, 0x8C, self);
    }
    func_001C5EA8(self, self->f700);
    func_001C8F20(self, 0, 0);
    if (func_00141008(D_00261420, self->fB10)) {
        func_001DBCC8(self->world, (void*)func_001C7278, self, 0, 0);
    }
}

s32 func_00182FC8(void* p);
void func_001C61E0(C07* self, s32 mode);
void func_0019D2A8(C07* self, s32 v, void* p);
void func_0019D338(C07* self, s32 v, s32 w, void* blk);

void func_001C6890(C07* s)
{
    if (s->f2200 != 0 && func_00182FC8(s->f2200) == 0) {
        s32 v = s->f223C;
        s->f2200 = 0;
        s->f2204 = 0;
        if (v != 0) {
            return;
        }
        func_001C61E0(s, -1);
    }
    if (s->f223C != 0) {
        return;
    }
    void* p = s->f2200;
    if (p != 0) {
        func_0019D2A8(s, s->f21C4, p);
        return;
    }
    if (s->f2208 != 0) {
        func_0019D338(s, s->f21C4, s->f2208, s->pad220C);
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

extern f32 D_00274BE0[4];
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

void func_001921E8(C08* self, s32 v);

void func_001C7188(C08* self, s32 v)
{
    s32 b = self->fB10;
    s32 a = (s32)self->f720;
    func_001921E8(self, v);
    self->fB10 = b;
    self->f720 = (void*)a;
    self->fB74 = v;
}


void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* table);
void func_001C4578(void* self, s32 a1);

void func_001C44F0(C06* self)
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
    Mat02* dst = &self->m660;
    *dst = D_002483D0;
}


s32 func_001CB578(void* self);
void func_001892A0(f32 a, f32 b, void* out);
void func_00188850(void* table, f32 x, void* out);

void func_001C7AE0(C08* self, f32 x, f32 y)
{
    if (func_001CB578(self) != 0) return;
    s32 t = self->fB1C;
    self->f638 = x;
    self->fB24 = y;
    if (t != 0) {
        func_001892A0(x, y, (u8*)self + 0x660);
    } else {
        func_00188850((u8*)&D_00248D20, x, (u8*)self + 0x660);
    }
}

void func_001B93D8(void);

void func_001C49C8(void)
{
    func_001B93D8();
}

s32 func_001B8A08(C08* self, C03* obj);
s32 func_001A8820(void* p, C03* obj);

s32 func_001C7468(C08* self, C03* obj)
{
    if (func_001B8A08(self, obj) != 0) {
        return 1;
    }
    if (self->fB0C != 0) {
        if (func_001A8820(self->fB0C, obj) != 0) {
            return 1;
        }
    }
    if (self->f724 == 0xB) {
        if ((obj->flags538 & ((u64)1 << 55)) == 0) {
            return 1;
        }
    }
    return 0;
}

void func_00188850(const Vec02* t, f32 x, void* p);

void func_001C53B0(C06* self)
{
    func_00188850(&D_00248D20, self->f638, (u8*)self + 0x660);
}

extern f32 D_0024D654;

void func_00192850(C08* self);
void func_0012E760(void* obj);
void func_001CB6F8(void* a, C08* b);

void func_001C7520(C08* self)
{
    func_00192850(self);
    if (self->f7E0 != 0) {
        func_0012E760(self->f7E0);
        self->f7E0 = 0;
    }
    if (self->f754 != 0) {
        func_0012E760(self->f754);
        self->f754 = 0;
    }
    if (self->f720 != 0) {
        func_001CB6F8(self->f720, self);
    }
    self->f72C = 0;
    self->fA60 = 0;
    self->f748 = 0;
    self->fBA4 = 0;
    self->fBF4 = D_0024D654;
    self->fBF8 = D_0024D654;
    self->fBFC = D_0024D654;
    self->fC00 = D_0024D654;
}

extern f32 D_00275C60[];

void func_001B89B8(C06* self);
f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);

void func_001C5438(C06* self)
{
    func_001B89B8(self);
    f32 t = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    f32 ay = __builtin_fabsf(func_001EA408(self->f638 - t));
    f32* lim = D_00275C60;
    Vec02* p = &self->v6F0;
    f32 v = self->v6F0.x + ay * (p->y + ay * p->z);
    f32 lo = lim[0];
    f32 hi = lim[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    self->f63C = v;
}

struct Other_1C6928 { u8 pad[0xAA]; u16 flags; };
void func_00175170(C07* self, s32 a, s32 b);
void func_001C61E0(C07* self, s32 state);

void func_001C6928(C07* self, Other_1C6928* other)
{
    s32 flag = 1;
    s32 held = other->flags & 0x80;
    switch (self->f2220) {
    case 3:
        if (held == 0) goto tail;
        flag = 0;
        func_00175170(self, 2, 2);
        break;
    case 6:
        if (self->f239C < 6) {
            if (self->f239C >= 4) break;
        }
        flag = 0;
        break;
    case 2:
    case 4:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        flag = 0;
        break;
    case 0:
        if (self->f2590 != 0 && self->f25AC != 0) {
            switch (self->f223C) {
            case 4:
                func_001C61E0(self, 6);
                break;
            case 5:
                func_001C61E0(self, 7);
                break;
            }
        }
        break;
    }
    if (held != 0)
        self->f21C8 = D_0026185C[0];
tail:
    s32 st = self->f223C;
    if (st == -1) {
        if (flag != 0) {
            if (D_0026185C[0] - self->f21C8 < 0.35f) st = 3;
        }
    } else if (st >= -1) {
        if (st < 8) {
            if (st >= 4) {
                if (flag != 0 && self->f2248 != 0) {
                    if (D_0026185C[0] - self->f21C8 < 0.35f) st = 3;
                }
            }
        }
    }
    func_001C61E0(self, st);
}

extern u8 D_00261420[];
extern const f32 D_0024D650 = 3.4028235e+38f;
void func_001C4458(C06* self);
struct Tbl_1C6F48;
s32 func_00140FF8(Tbl_1C6F48* p);
void func_00192990(C08* self, s32 a);

#define F(T, o) (*(T*)((u8*)self + (o)))

void func_001C6F48(C08* self)
{
    func_001C4458(self);
    f32 c300 = 300.0f;
    F(s32, 0x724) = -1;
    F(s32, 0x924) = -1;
    F(u64, 0x538) = (F(u64, 0x538) & ~((u64)0xF0 << 32)) | ((u64)1 << 37);
    F(f32, 0x73C) = c300;
    F(f32, 0x740) = 0.2f;
    F(f32, 0x744) = 0.5f;
    F(f32, 0x74C) = 0.17453294f;
    F(s32, 0x738) = 0;
    s32 i;
    for (i = 16; i >= 0; i--) F(s32, 0x758 + i * 8) = -1;
    f32* s3 = (f32*)((u8*)self + 0xB9C);
    f32* s4 = (f32*)((u8*)self + 0xBE0);
    s32 m = -1;
    for (i = 16; i >= 0; i--) F(s32, 0x870 + i * 8) = m;
    f32 one = 1.0f;
    s32 r = func_00140FF8((Tbl_1C6F48*)D_00261420);
    s32 s1 = 1;
    s32 s0 = -1;
    F(s32, 0xB10) = r;
    F(u64, 0x538) = (F(u64, 0x538) & ~((u64)0xF0 << 32)) | ((u64)1 << 37);
    F(s32, 0xB14) = s1;
    F(s32, 0xB4C) = s0;
    F(f32, 0xB30) = one;
    F(s32, 0xB58) = s0;
    func_00192990(self, 0);
    f32 d = D_0024D650;
    F(f32, 0x700) = 1.5f;
    F(f32, 0xB18) = -1.0f;
    F(f32, 0xB9C) = one;
    F(void*, 0xB74) = self;
    F(f32, 0xBFC) = d;
    F(f32, 0xC00) = d;
    F(u8, 0x2B3) = 0x20;
    s3[1] = 2.5f;
    F(s32, 0xBE0) = 0;
    s4[1] = 0.8f;
    F(s32, 0xBEC) = s0;
    F(f32, 0xBD0) = one;
    F(s32, 0xBD4) = s1;
    F(f32, 0xBE8) = 1.25f;
    F(s32, 0xBDC) = s1;
}

struct __attribute__((packed)) Pk8_1C5E50 { u32 a; u32 b; };
struct Vec_1C5E50 { Pk8_1C5E50 xy; u32 z; };

extern f32 D_00274B80[4];

void func_001C5E50(C06* self, f32 s)
{
    *(Vec_1C5E50*)&self->f6E0 = *(Vec_1C5E50*)D_00274B80;
    self->f6E0 *= s;
    self->f6E4 *= s;
    self->f6E8 *= 1.0f / Fpu::Sqrt(s);
}

void func_001BAC30(C08* self, void* a1);
void func_00124DF8(C08* self, s32 a1, void* a2);
void func_001CA7C0(C08* self);
void func_001CA8E8(C08* self);
extern s32 D_00274C20[4];

void func_001C7140(C08* self, void* a1)
{
    func_001BAC30(self, a1);
    func_00124DF8(self, 1, D_00274C20);
    func_001CA7C0(self);
    func_001CA8E8(self);
}

struct Arg_1C5248 { u8 pad0[0x88]; f32 f88; u8 pad1[0x9C - 0x8C]; s32 f9C; s32 fA0; s32 fA4; };
extern f32 D_00274AD0[];

s32 func_001C5248(C06* self, Arg_1C5248* a, s32 idx)
{
    if (self->f6DC == 0) {
        return 0;
    }
    if (a->f88 * D_00274AD0[idx] < 0.7f) {
        return 0;
    }
    s32 kind = a->f9C;
    switch (kind) {
    case 1: {
        s32 r = 0;
        if (idx == 0 && a->fA0 == self->f6D4) {
            r = 1;
        }
        return r;
    }
    case 4: {
        s32 r = 0;
        if (idx == 1 && a->fA4 == self->f6D4) {
            r = 1;
        }
        return r;
    }
    case 10: {
        s32 r = 0;
        if (idx == 0) {
            r = a->fA0 == self->f6D4;
        }
        return r;
    }
    }
    return 0;
}

Ent_274AD8 D_00274AD8[6] = { {6, 0x36, 0x61C}, {6, 0x35, 0x618}, {6, 0x37, 0x628}, {6, 0x3A, 0x62C}, {6, 0x38, 0x620}, {6, 0x3B, 0x624} };
Quad_1C4458 D_00274B30 = { 0x3F800000, (s32)0xBF800000, 0, 0 };
s32 D_00274B40[4] = { 0x453B8000, 0, 0x40000000, 0 };
s32 D_00274B50[3] = { 0x453B8000, 0, 0x3E800000 };
f32 D_00274B80[4] = { 25.0f, 0.0f, 0.25f, 0.0f };
f32 D_00274BD8 = -1.0f;
f32 D_00274BE0[4] = { 175.0f, 0.0f, 0.0f, 0.0f };
f32 D_00274BF0[4] = { 250.0f, 0.0f, 125.0f, 0.0f };
f32 D_00274C00[4] = { 125.0f, 0.0f, 0.0f, 0.0f };
s32 D_00274C20[4] = { 2, 0x195, 0x87C, 0 };
s32 D_00274C30[8] = { 2, 0x194, 0x750, 6, 0x50, 0x734, 0, 0 };
