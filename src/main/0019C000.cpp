// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c8b.h"
#include "c1e.h"
#include "c6c.h"
#include "c6d.h"
#include "object_gatherer.h"
#include "c05.h"
#include "v24a0.h"
#include "t219c.h"
#include "globals.h"
#include "group_marker.h"
#include "deferred_request.h"
#include "color_fade.h"

struct Buf_19DF48 { u8 raw[0x30]; };
typedef void (*Fn_19DF48)(void);

extern s32 D_0026AC20[];

void func_001611B8(void* self);
void func_001529C8(void* self, s32 a, void* b);
void func_001612F8(void* self, s32 a, s32 b, s32 c, s32 d, s32 e);
void func_0019DA30(void);
void func_0019DA60(void);
void func_0019DAD8(void);
void func_0019DB20(void);
void func_0019DB68(void);
void func_0019DBB0(void);

void func_0019DF48(void)
{
    Buf_19DF48 buf;
    GroupMarker* rows;
    u8* p;
    s32 i;

    func_001611B8(buf.raw);
    func_001529C8(buf.raw, 1, D_0026AC20);
    func_001612F8(buf.raw, 0x7D, 0, 3, 0x412, 0);
    rows = g_groupMarkers;

    rows[0].handler = func_0019DA30;
    rows[1].handler = func_0019DA60;
    rows[2].handler = func_0019DAD8;
    rows[3].handler = func_0019DB20;
    rows[4].handler = func_0019DB20;
    rows[5].handler = func_0019DB68;
    rows[6].handler = func_0019DB20;
    rows[7].handler = func_0019DB20;
    rows[8].handler = func_0019DB20;
    rows[9].handler = func_0019DB68;
    rows[12].handler = func_0019DB20;
    rows[11].handler = func_0019DB20;
    rows[10].handler = func_0019DB20;
    rows[13].handler = func_0019DB20;
    rows[14].handler = func_0019DB68;
    rows[15].handler = func_0019DB68;
    rows[16].handler = func_0019DB20;
    rows[17].handler = func_0019DBB0;

    p = (u8*)g_groupMarkers + 0x888;
    i = 17;
    do {
        *(s32*)p = -1;
        i--;
        p -= 0x80;
    } while (i >= 0);
}

C1E* func_0019E040(C6C* self, s32 flag)
{
    if (flag == 0 && self->f1B3C != 0) {
        return self->f1B3C;
    }
    C1E* n = self->f1B38;
    if (n != 0) {
        self->f1B38 = n->saved564;
        n->f550 = flag;
        n->desc->m02(n);
        if (flag == 0) {
            self->f1B3C = n;
        }
    }
    return n;
}

void func_001B7968(C03* self);
void func_00152438(void* p, s32 n);

void func_0019E0B8(C1E* self)
{
    func_001B7968(self);
    func_00152438(&self->list558, 0x10);
    u64 flags = self->flags;
    flags &= (u64)(s64)(s32)0xCFFFFFFF;
    flags |= 0x20000000ULL;
    u64 wide = self->flags538;
    wide |= (u64)1 << 42;
    flags &= 0xFFFFFCFFFFFFFFFFULL;
    wide |= (u64)1 << 51;
    f32 k = 1e10f;
    flags |= (u64)1 << 40;
    self->flags538 = wide;
    self->f80 = k;
    self->flags = flags;
}


void* func_001B5EA0(void* p);
void func_001F5C0C(void* p, s32 zero, s32 size);
const Vt219C* func_0019E908(u32 n);
void func_00152470(void* list, void* item);
void func_0019EC20(T219C* self);

T219C* func_0019EA78(s32 kind, C1E* sys)
{
    if (sys == 0) {
        sys = func_0019E040(D_00275710, 0);
        if (sys == 0) return 0;
    }
    T219C* o = (T219C*)func_001B5EA0(&sys->world->pool1B2C);
    if (o != 0) {
        func_001F5C0C(o, 0, sys->world->pool1B2C.size);
        const Vt219C* r = func_0019E908(kind);
        o->kind = kind;
        o->owner = sys;
        o->vt = r;
        func_00152470(&sys->list558, o);
        func_0019EC20(o);
    }
    return o;
}

void func_00152600(void* table, void* self);
void func_0019EC30(T219C* self);

void func_0019EBE8(T219C* self)
{
    func_00152600(&self->owner->list558, self);
    func_0019EC30(self);
}

void func_001DBC18(void* a, void* b);
void func_001B5F28(void* a, void* b);

void func_0019EC30(T219C* self)
{
    s32 n = self->uses - 1;
    self->uses = n;
    if (n != 0) {
        return;
    }
    void (*fn)(T219C*) = self->vt->m02;
    if (fn != 0) {
        fn(self);
    }
    T219CHook* head = self->hooks;
    if (head != 0) {
        self->hooks = 0;
        for (T219CHook* it = head; it != 0; it = it->next) {
            it->fn(it->payload, 0x10, self);
        }
        func_001DBC18(D_00275710, head);
    }
    func_001B5F28(&self->owner->world->pool1B2C, self);
}

extern f32 D_00261858[];

void func_0019ED00(T219C* self, f32 x)
{
    f32 span = D_00261858[1] - self->start;
    f32 t = self->life - span;
    if (x < t) {
        f32 r = t / self->life;
        f32 q = x / r;
        self->life = q;
        self->start = D_00261858[1] - (1.0f - r) * q;
    }
}

void func_0019EB28(T219C* self);

void func_0019FE10(T219C* self)
{
    func_0019EB28(self);
    C6C* g = D_00275710;
    s32 v = (s32)g->slot1CE8[6];
    self->life = 0.5f;
    self->i20 = v;
}

void func_0019CE38(C8B* self, f32 x, f32 y, f32 z)
{
    self->f80 = 1;
    self->f54 = x;
    self->f58 = y;
    self->f5C = z;
}

struct __attribute__((aligned(16))) Vec_19D2A8 { s32 a, b, c, d; };
struct Frame_19D2A8 { Vec_19D2A8 q0; Vec_19D2A8 q1; s32 w20; s32 w24; };

extern f32 D_00261858[];

void func_0019CEC0(void* a, void* b, void* c, f32 d);
void func_0019D0E0(void* a, void* b, void* c, void* d, void* e);
void func_0019C9C8(void* a, s32 b, void* c);

void func_0019D2A8(C07* self, void* x, void* y)
{
    Frame_19D2A8 f;
    if (y != 0) {
        f32 d = self->f2424 - D_00261858[1];
        if (d < D_00261858[2]) {
            d = D_00261858[2];
        }
        func_0019CEC0(x, y, &f.q0, d);
        func_0019D0E0(x, &f.q0, &f.q1, &f.w20, &f.w24);
        func_0019C9C8(x, f.w20, &f.q1);
    }
}

extern f32 D_0026185C;

void func_0019EBE8(T219C* self);
s32 func_00182FC8(void* p);
s32 func_0013E658(void* a, s32 b);

void func_0019F560(T219C* self)
{
    f32 t = D_0026185C - self->start;
    if (self->life < t) {
        func_0019EBE8(self);
        return;
    }
    C1E* c = self->owner;
    if (c->f550 == 1) {
        return;
    }
    C03* h = self->target;
    if (h == 0) {
        return;
    }
    if (h->tree.nodes == 0) {
        return;
    }
    s32 flag = 0;
    if (func_00182FC8(h) != 0) {
        if (func_0013E658(&self->q80, (s32)self->target->tree.nodes) != 0) {
            flag = 1;
        }
    }
    self->vt->m06(self, flag);
}

void func_001F2EF0(f32 f, void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5);
s32 func_0019F620(void* self, void* a1, void* a2, void* a3);
void func_0019EBE8(T219C* self);

void func_0019F858(T219C* self, void* a1)
{
    u8 scratch[0x40];
    void* a2;
    void* a3;
    if (self->p114 != 0) {
        func_001F2EF0(50.0f, self->p114, &self->q80, self->rot50,
                      scratch, scratch + 0x10, 0);
        a2 = scratch;
        a3 = scratch + 0x10;
    } else {
        a2 = &self->q80;
        a3 = self->rot50;
    }
    s32 r = func_0019F620(self, a1, a2, a3);
    if (r == 0) {
        func_0019EBE8(self);
    }
}


void func_0019EB28(T219C* self);

void func_0019F988(T219C* self)
{
    func_0019EB28(self);
    self->life = 5.0f;
    C6C* g = D_00275710;
    self->i20 = (s32)g->slot1CE8[1];
    self->qC0 = *(Quad219C*)&g->gravity;
}


void func_0019EB28(T219C* self);

void func_0019FD70(T219C* self)
{
    func_0019EB28(self);
    self->life = 3.0f;
    C6C* g = D_00275710;
    s32 v = (s32)g->slot1CE8[3];
    self->m30[1] = 0.6f;
    self->i20 = v;
}

extern f32 D_00261858[];

struct Frame_19E848 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

void func_0019E848(C1E* self, void* arg)
{
    Frame_19E848 fr;
    s32 e = (s32)&self->list558;
    fr.cursor = e;
    fr.list = e;
    s32 old = (s32)D_0027B314;
    s32 link = *(s32*)(e + 8);
    D_0027B314 = (ListFrame*)&fr;
    fr.prev = old;
    s32 h = *(s32*)e;
    fr.link = link;
    fr.cursor = h + link;
    s32 n = h;
    while (n != 0) {
        T219C* node = (T219C*)n;
        if (node->start >= D_00261858[1]) {
        } else {
            node->vt->m05(node, arg);
        }
        s32 nx = *(s32*)fr.cursor;
        s32 lk = fr.link;
        fr.cursor = nx + lk;
        n = nx;
    }
    D_0027B314 = (ListFrame*)fr.prev;
}


void func_0019EB28(T219C* self);

void func_0019FDC0(T219C* self)
{
    func_0019EB28(self);
    self->life = 2.0f;
    C6C* g = D_00275710;
    self->qC0 = *(Quad219C*)&g->gravity;
    self->m30[2] = -1.0f;
}

extern u8 D_0026AC10[];

struct ColorFade;
typedef void (*VFn_19D6C0)(ColorFade* self, void* arg, s32 z);

struct Frame_19D6C0 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

void func_00159D00(ColorFade* n);

void func_0019D6C0(C6C* self, void* arg)
{
    Frame_19D6C0 f1;
    Frame_19D6C0 f2;
    Frame_19D6C0 f3;
    s32 e = (s32)self + 0x60;
    f1.cursor = e;
    f1.list = e;
    s32 old = (s32)D_0027B314;
    s32 link = *(s32*)(e + 8);
    *(s32*)D_0026AC10 = (s32)D_005E4700;
    D_0027B314 = (ListFrame*)&f1;
    f1.prev = old;
    f1.link = link;
    s32 h = *(s32*)e;
    f1.cursor = h + link;
    s32 n = h;
    while (n != 0) {
        ColorFade* node = (ColorFade*)n;
        ((VFn_19D6C0*)node->obj)[40](node, arg, 0);
        s32 nx = *(s32*)f1.cursor;
        f1.cursor = nx + f1.link;
        n = nx;
    }
    s32 e2 = (s32)self + 0x78;
    s32 old2 = (s32)D_0027B314;
    f2.cursor = e2;
    f2.list = e2;
    s32 link2 = *(s32*)(e2 + 8);
    D_0027B314 = (ListFrame*)&f2;
    f2.prev = old2;
    s32 h2 = *(s32*)((s32)self + 0x78);
    f2.link = link2;
    f2.cursor = h2 + link2;
    n = h2;
    while (n != 0) {
        ColorFade* node = (ColorFade*)n;
        ((VFn_19D6C0*)node->obj)[40](node, arg, 0);
        s32 nx = *(s32*)f2.cursor;
        f2.cursor = nx + f2.link;
        n = nx;
    }
    s32 e3 = (s32)self + 0x1CD8;
    s32 old3 = (s32)D_0027B314;
    s32 link3 = *(s32*)(e3 + 8);
    f3.prev = old3;
    D_0027B314 = (ListFrame*)&f3;
    f3.list = e3;
    s32 h3 = *(s32*)((s32)self + 0x1CD8);
    f3.link = link3;
    f3.cursor = h3 + link3;
    n = h3;
    while (n != 0) {
        func_00159D00((ColorFade*)n);
        s32 nx = *(s32*)f3.cursor;
        f3.cursor = nx + f3.link;
        n = nx;
    }
    D_0027B314 = (ListFrame*)f1.prev;
}

extern u8 D_0060478C[];
extern u8 D_0026ABF0[];
extern u8 D_0026AC00[];
extern s32 D_0026AC20[];

void func_00152B38(void* self);
void func_00152D70(void* self);
void func_001EE3B8(void* obj, s32 size, s32 flags);
void func_001EE668(void* obj, s32 size, s32 count, void* data, s32 flags);

void func_0019D860(void)
{
    if (*(s32*)D_0060478C == 0) {
        *(s32*)D_0060478C = 1;
        void* obj = &D_002622A8;
        func_00152B38(obj);
        func_001EE3B8(obj, 0, 0);
        func_001EE668(obj, 8, 1, D_0026ABF0, 0);
        func_001EE668(obj, 8, 1, D_0026AC00, 1);
        func_001EE668(obj, 0xC, 1, D_0026AC20, 0xC);
        func_001EE668(obj, 4, 1, &D_00275710->f1D68, 3);
        func_00152D70(obj);
    }
}

extern s32 D_00604780;
extern s32 D_00604784;
extern u8 D_002BDC20[];
extern u8 D_002BDEE0[];

void func_00152B38(void* self);
void func_001EE7D0(void* self, s32 n, void* buf, s32 flag);
void func_001EE450(void* self);
void func_00152D70(void* self);

void func_0019D968(void)
{
    if (D_00604780 == 0) {
        void* self = &D_002622A8;
        func_00152B38(self);
        func_001EE7D0(self, 0x2C, D_002BDC20, 0);
        func_00152D70(self);
        D_00604780 = 1;
        D_00604784 = 1;
    } else if (D_00604784 == 0) {
        void* self = &D_002622A8;
        func_00152B38(self);
        func_001EE450(self);
        func_001EE7D0(self, 0x2C, D_002BDEE0, 0);
        func_00152D70(self);
        D_00604784 = 1;
    }
}

struct Slot_2622D8 { u8 pad00[0x1C]; s32 r1C; };

extern s32 D_00604780;
extern u8 D_00212160[];
extern u8 D_00215C50[];
extern Slot_2622D8* D_002622D8;

void func_0019D860(void);
void func_0019D930(void);
void func_0015EAE0(void* self, void* a, void* b);
void func_00152B38(void* self);
void func_001EE468(void* self);
void func_00152D70(void* self);

void func_0019DA60(void)
{
    func_0019D860();
    func_0019D930();
    void* self = &D_002622A8;
    func_0015EAE0(self, D_00212160, D_00215C50);
    D_00604780 = 1;
    g_buildFrame->r1C = 1;
    func_00152B38(self);
    func_001EE468(self);
    func_00152D70(self);
}

struct Scratch_19F9D0 { Quad219C head; u8 rest[0x700 - 16]; };

void func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
T219C* func_0019EA78(s32 kind, C1E* sys);
void func_0019EBE8(T219C* self);

void func_0019F9D0(T219C* self, s32 flag)
{
    if (flag != 0) {
        Scratch_19F9D0 s;
        s.head = self->q80;
        if (self->target->tree.nodes != 0) {
            func_0013DFD8(self->target->tree.nodes, &self->q90, &self->q80, 0, 0x10, &s);
        }
        T219C* p = func_0019EA78(4, 0);
        if (p != 0) {
            p->vt->m00(p, &s, 40.0f, 0);
            p->life = 0.75f;
            p->m30[1] = 30.0f;
            if (self->target->f278 != 0) {
                p->p114 = (void*)((s32*)self->target->f278)[3];
            }
        }
        func_0019EBE8(self);
    }
}

struct Ctx_19DBB0 { u8 pad0[0x2F4]; s32 idx2F4; };

extern Ctx_19DBB0* D_0026FA68;
extern s32 D_00274520[];
extern C6D* D_00261990;
extern u8 D_00212160[];
extern u8 D_00215C50[];

void func_0015EAE0(void* self, void* a, void* b);
void func_0019D860(void);
void func_0019D930(void);
void func_00143940(C6D* self, f32 v);
void func_00144848(C6D* self);

void func_0019DBB0(void)
{
    V24A0* self = &D_002622A8;
    func_0015EAE0(self, D_00212160, D_00215C50);
    func_0019D860();
    func_0019D930();

    if (D_0026FA68 != 0) {
        s32 v = D_00274520[D_0026FA68->idx2F4];
        if (v != 0) {
            *(u64*)self->cur = ((u64)v << 32) | 0x50000000;
            self->cur = self->cur + 0x10;
        }
    }

    {
        C6D* o = D_00261990;
        f32 keep20 = o->f1C4;
        f32 keep21 = o->f1C8;
        func_00143940(o, 1.0f);
        func_00144848(D_00261990);
        func_00143940(D_00261990, keep20);
        D_00261990->f1C8 = keep21;
    }
}

struct __attribute__((aligned(16))) Vec_19D338 { s32 a, b, c, d; };
struct Frame_19D338 {
    Vec_19D338 q0;
    Vec_19D338 q1;
    Vec_19D338 q2;
    Vec_19D338 q3;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
};

typedef s32 (*Slot_19D338)(void* self, void* a1, s32 a2, void* a3, s32 a4, s32 a5, f32 f, void* a6);
struct Obj_19D338 { Slot_19D338* vtbl; };
struct Src_19D338 {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1[0x34 - 0x1C];
    Obj_19D338* f34;
};

s32 func_00128018(void* a, s32 b, void* c, void* d);
void func_0019D0E0(void* a, void* b, void* c, void* d, void* e);
void func_0019C9C8(void* a, s32 b, void* c);

void func_0019D338(void* self, void* dst, Src_19D338* src, f32* k)
{
    Frame_19D338 f;
    func_00128018(0, src->f18, (u8*)self + 0x140, &f.q0);
    Obj_19D338* o = src->f34;
    if (o->vtbl[12] != 0) {
        o->vtbl[12](o, &f.q0, 0, &f.q1, 0, 0, *k, k);
    }
    func_00128018((void*)src->f18, (s32)self, &f.q1, &f.q2);
    func_0019D0E0(dst, &f.q2, &f.q3, &f.w40, &f.w44);
    func_0019C9C8(dst, f.w40, &f.q3);
}

struct Cursor_19E168;
struct Cursor_19E168 {
    void* link;
    u8* at;
    s32 stride;
    Cursor_19E168* prev;
    Cursor_19E168(void* l) {
        link = l;
        at = (u8*)l;
        stride = ((s32*)l)[2];
        prev = ((Cursor_19E168*)D_0027B314);
        D_0027B314 = (ListFrame*)this;
    }
    T219C* first() {
        T219C* n = *(T219C**)link;
        at = (u8*)n + stride;
        return n;
    }
    T219C* next() {
        T219C* n = *(T219C**)at;
        at = (u8*)n + stride;
        return n;
    }
    ~Cursor_19E168() { D_0027B314 = (ListFrame*)prev; }
};


void func_0019EBE8(T219C* node);
void func_001B7B78(C03* self);

void func_0019E168(C1E* self)
{
    Cursor_19E168 cur(&self->list558);
    T219C* node = cur.first();
    while (node != 0) {
        func_0019EBE8(node);
        node = cur.next();
    }
    self->saved564 = self->world->f1B38;
    self->world->f1B38 = self;
    if (self == self->world->f1B3C) {
        self->world->f1B3C = 0;
    }
    func_001B7B78(self);
}

struct Stream_19C470;
s32 func_00137D10(Stream_19C470* in);
void func_00137FB0(Stream_19C470* in, void* p);
void* func_0018D5C0(s32 n);
s32 func_00137CC0(Stream_19C470* in);
void func_0019CD90(C8B* o, s32 i, f32* x, f32* y, f32* z);
void func_0019CC10(f32 x, f32 y, f32 z, C8B* o, void* p);
f32 func_00137DF8(Stream_19C470* in);
void func_0011EC40(C8B* o, Stream_19C470* in);

void func_0019C470(C8B* o, Stream_19C470* in)
{
    {
        s32 i = 0x17;
        s32* p = (s32*)((u8*)o + 0xF0);
        do {
            i--;
            *p = func_00137D10(in);
            p += 8;
        } while (i >= 0);
    }
    s32 i = 0;
    o->f48 = func_00137D10(in);
    func_00137FB0(in, o->fA0);
    o->fC4 = (Rec8B*)func_0018D5C0(o->fA4 * 100);
    for (i = 0; i < o->fA4; i++) {
        f32 x;
        f32 y;
        f32 z;
        Rec8B* r = &o->fC4[i];
        o->fC4[i].id = func_00137CC0(in);
        func_0019CD90(o, i, &x, &y, &z);
        func_0019CC10(x, y, z, o, r->pos);
    }
    o->fC8 = func_00137D10(in);
    o->fCC = (u8*)func_0018D5C0(o->fC8 << 4);
    for (s32 e = 0; e < o->fC8; e++) {
        s32* r = (s32*)(o->fCC + (e << 4));
        s32 j = 3;
        do {
            j--;
            *r = func_00137D10(in);
            r++;
        } while (j >= 0);
    }
    o->fD0 = o->fD4 = func_00137D10(in);
    o->fD8 = (Tri8B*)func_0018D5C0(o->fD0 * 12);
    o->fDC = (Edge8B*)func_0018D5C0(o->fD0 << 3);
    for (s32 n = 0; n < o->fD0; n++) {
        Tri8B* t = &o->fD8[n];
        Edge8B* e = &o->fDC[n];
        s32 a = func_00137D10(in);
        s32 b = func_00137D10(in);
        s32 c = func_00137D10(in);
        t->a = o->fB0 + (a << 5);
        if (b > 0) {
            b--;
            t->b = (u8*)&o->fD8[b];
        } else if (b < 0) {
            b = ~b;
            e->a = o->fCC + (b << 4);
        }
        if (c > 0) {
            c--;
            t->c = (u8*)&o->fD8[c];
        } else if (c < 0) {
            c = ~c;
            e->b = o->fCC + (c << 4);
        }
    }
    o->fE0 = func_00137DF8(in);
    func_0011EC40(o, in);
}

// NEAR: 3 lines: prologue schedules "li t0,17" before the two addiu sp addresses (retail after them)



void func_001BE0A8(void** base, s32 count, s32 size, void* cmp);
void func_0019D468(void);

s32 func_0019D4B0(s32 n, DeferredRequest* items, void** out)
{
    s32 start[18];
    s32 pos[18];
    s32 cnt[18];
    s32 j;
    s32 i;
    for (i = 0; i < 18; i++) cnt[i] = 0;
    for (j = 0; j < n; j++) cnt[items[j].group]++;
    pos[0] = 0;
    if (cnt[0] > 0 && g_groupMarkers[0].handlerWord != 0) {
        out[0] = &g_groupMarkers[0];
        pos[0] = 1;
        cnt[0]++;
    }
    start[0] = pos[0];
    for (i = 1; i < 18; i++) {
        pos[i] = cnt[i - 1];
        if (cnt[i] > 0 && g_groupMarkers[i].handlerWord != 0) {
            out[pos[i]] = &g_groupMarkers[i];
            pos[i]++;
        }
        cnt[i] += pos[i];
        start[i] = pos[i];
    }
    for (j = 0; j < n; j++, items++) {
        s32 b = items->group;
        out[start[b]++] = items;
    }
    {
        s32 c = cnt[4] - pos[4];
        func_001BE0A8(&out[pos[4]], c, 4, (void*)func_0019D468);
    }
    {
        s32 c = cnt[8] - pos[8];
        func_001BE0A8(&out[pos[8]], c, 4, (void*)func_0019D468);
    }
    {
        s32 c = cnt[13] - pos[13];
        func_001BE0A8(&out[pos[13]], c, 4, (void*)func_0019D468);
    }
    {
        s32 c = cnt[1] - pos[1];
        func_001BE0A8(&out[pos[1]], c, 4, (void*)func_0019D468);
    }
    return cnt[17];
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_00219C20[];
extern const Fn_Table D_00219C40[];
extern const Fn_Table D_00219C60[];
extern const Fn_Table D_00219C80[];
extern const Fn_Table D_00219CA0[];
extern const Fn_Table D_00219CC0[];
extern const Fn_Table D_00219CE0[];
extern const Fn_Table D_00219D00[];
extern const Fn_Table D_00219D20[];
extern const Fn_Table D_00219D40[];
extern const Fn_Table D_00219D60[];
extern const Fn_Table D_00219D80[];
extern const Fn_Table D_00219DA0[];
extern const Fn_Table D_00219DC0[];
extern u8 D_00219DE0[];
extern const Fn_Table D_00219E00[];
extern const Fn_Table D_00219E20[];
extern const Fn_Table D_00219E40[];
extern const Fn_Table D_00219E60[];
extern const Fn_Table D_00219E80[];
extern const Fn_Table D_00219EA0[];
extern const Fn_Table D_00219EC0[];
extern const Fn_Table D_00219EE0[];
extern const Fn_Table D_00219F00[];
extern const Fn_Table D_00219F20[];
extern const Fn_Table D_00219F40[];
extern const Fn_Table D_00219F60[];

const Vt219C* func_0019E908(u32 n)
{
    switch (n) {
    case 0: return (const Vt219C*)(D_00219C20);
    case 2: return (const Vt219C*)(D_00219C40);
    case 3: return (const Vt219C*)(D_00219C60);
    case 4: return (const Vt219C*)(D_00219C80);
    case 5: return (const Vt219C*)(D_00219CA0);
    case 6: return (const Vt219C*)(D_00219CC0);
    case 7: return (const Vt219C*)(D_00219CE0);
    case 8: return (const Vt219C*)(D_00219D00);
    case 9: return (const Vt219C*)(D_00219D20);
    case 10: return (const Vt219C*)(D_00219D40);
    case 11: return (const Vt219C*)(D_00219D60);
    case 12: return (const Vt219C*)(D_00219D80);
    case 13: return (const Vt219C*)(D_00219DA0);
    case 14: return (const Vt219C*)(D_00219DC0);
    case 15: return (const Vt219C*)D_00219DE0;
    case 16: return (const Vt219C*)(D_00219E00);
    case 17: return (const Vt219C*)(D_00219E20);
    case 18: return (const Vt219C*)(D_00219E40);
    case 19: return (const Vt219C*)(D_00219E60);
    case 20: return (const Vt219C*)(D_00219E80);
    case 21: return (const Vt219C*)(D_00219EA0);
    case 22: return (const Vt219C*)(D_00219EC0);
    case 23: return (const Vt219C*)(D_00219EE0);
    case 24: return (const Vt219C*)(D_00219F00);
    case 25: return (const Vt219C*)(D_00219F20);
    case 26: return (const Vt219C*)(D_00219F40);
    case 27: return (const Vt219C*)(D_00219F60);
    default: return 0;
    }
}

// The loop walks an intrusive list with an iterator that registers itself on a global stack
// (D_0027B314) for its lifetime and unregisters in its destructor.


typedef void (*VFn_19C068)(void *self);
typedef void (*VFn2_19C068)(void *self, void *x);

struct Frame_19C068;
struct Frame_19C068 {
    List01 *list;
    s32 *cur;
    s32 step;
    Frame_19C068 *prev;
    Frame_19C068(List01 *l)
    {
        list = l;
        cur = (s32 *)&l->head;
        step = l->offset;
        prev = ((Frame_19C068*)D_0027B314);
        D_0027B314 = (ListFrame*)this;
    }
    ~Frame_19C068() { D_0027B314 = (ListFrame*)prev; }
    s32 Next()
    {
        s32 n = *cur;
        cur = (s32 *)(n + step);
        return n;
    }
};

struct Ob_19C068 {
    VFn_19C068 *vtbl;
};

void func_00152600(List01 *a, ObjectGatherer *b);
void func_00152470(List01 *a, ObjectGatherer *b);
struct Buf_19C068 { s32 w[4]; };
void func_00128018(void *a, s32 b, void *c, struct Buf_19C068 *d);
void func_001B9860(ObjectGatherer *a, struct Buf_19C068 *b, void *c);
void func_001B7C40(ObjectGatherer *self, s32 flag);

void func_0019C068(ObjectGatherer *self, s32 a1) {
    if (a1 != 0) {
        func_00152600(&self->world->list1C60, self);
        ((struct Ob_19C068 *)self->f5FC)->vtbl[7](self->f5FC);
    } else {
        struct Buf_19C068 buf;
        func_00152470(&self->world->list1C60, self);
        ((struct Ob_19C068 *)self->f5FC)->vtbl[6](self->f5FC);
        func_00128018(*(void **)((u8 *)self->f660 + 0x18), 0,
                      (u8 *)self->f660 + 0x40, &buf);
        func_001B9860(self, &buf, (void*)&D_00248D20);
    }
    func_001B7C40(self, a1 == 0);
    Frame_19C068 it(&self->parts);
    s32 node = it.Next();
    while (node != 0) {
        func_001B7C40((ObjectGatherer *)node, a1 == 0);
        node = it.Next();
    }
    self->desc02()->m20(self, (Vec02 *)&D_00248D30);
    self->desc02()->m21(self, (Vec02 *)&D_00248D30);
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_0019ECE0();
void func_0019ED58();
void func_0019F390();
void func_0019FA98();
void func_0019FB08();
void func_0019FCE8();
void func_0019FD08();
void func_0019FE50();
void func_0019FF20();
void func_001A0020();
void func_001A0040();
void func_001A00A0();
void func_001A01B8();
void func_001A0258();
void func_001A0318();
void func_001A05D8();
void func_001A0758();
void func_001A09C0();
void func_001A0A78();
void func_001A0B20();
void func_001A0BA0();
void func_001A0C50();
void func_001A0C98();
void func_001A0D60();
void func_001A0DF0();
void func_001A0F88();
void func_001A1410();
void func_001A1458();
void func_001A1498();
void func_001A14A0();
void func_001A15D8();
void func_001A22C8();
void func_001A22E0();
void func_001A25F0();
void func_001A26B0();
void func_001A26F8();
void func_001A2770();
void func_001A2830();
void func_001A2A68();
void func_001A2B48();
void func_001A2D30();
void func_001A2D88();
void func_001A2E68();
void func_001A3008();
void func_001A3128();
void func_001A31A0();
void func_001A31F0();
void func_001A3250();
void func_001A3598();
void func_001A3730();
void func_001A38F0();
void func_001A3990();
void func_001A39C8();
void func_001A3A18();
extern const Fn_Table D_00219C20[8] = { (Fn_Table)(void (*)(T219C* self))func_0019EB28, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219C40[8] = { (Fn_Table)func_0019F988, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019F9D0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219C60[8] = { (Fn_Table)func_0019FA98, 0, 0, (Fn_Table)func_0019FB08, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019FCE8, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219C80[8] = { (Fn_Table)func_0019FD08, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219CA0[8] = { (Fn_Table)func_0019FD70, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219CC0[8] = { (Fn_Table)func_0019FDC0, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219CE0[8] = { (Fn_Table)func_0019FE10, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019FE50, (Fn_Table)func_0019FF20, (Fn_Table)func_001A0020, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D00[8] = { (Fn_Table)func_001A0040, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A00A0, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D20[8] = { (Fn_Table)func_001A01B8, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D40[8] = { (Fn_Table)func_001A0258, 0, (Fn_Table)func_001A0318, (Fn_Table)func_001A05D8, (Fn_Table)func_0019F560, (Fn_Table)func_001A0758, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D60[8] = { (Fn_Table)func_001A09C0, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_001A0A78, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D80[8] = { (Fn_Table)func_001A0B20, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219DA0[8] = { (Fn_Table)func_001A0BA0, 0, (Fn_Table)func_001A0318, (Fn_Table)func_001A05D8, (Fn_Table)func_0019F560, (Fn_Table)func_001A0758, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219DC0[8] = { (Fn_Table)func_001A0C50, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219E00[8] = { (Fn_Table)func_001A0C98, 0, 0, (Fn_Table)func_001A0D60, (Fn_Table)func_001A0F88, (Fn_Table)func_001A0DF0, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219E20[8] = { (Fn_Table)func_001A1410, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A00A0, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219E40[8] = { (Fn_Table)func_001A1458, 0, 0, (Fn_Table)func_001A1498, (Fn_Table)func_001A14A0, (Fn_Table)func_001A15D8, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219E60[8] = { (Fn_Table)(void (*)(T219C* self))func_0019EB28, (Fn_Table)func_001A22C8, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A22E0, (Fn_Table)func_0019ECE0, (Fn_Table)func_001A25F0 };
extern const Fn_Table D_00219E80[8] = { (Fn_Table)(void (*)(T219C* self))func_0019EB28, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_001A26B0, (Fn_Table)func_001A26F8, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219EA0[8] = { (Fn_Table)(void (*)(T219C* self))func_0019EB28, (Fn_Table)func_001A2770, 0, (Fn_Table)func_001A2830, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_001A2A68 };
extern const Fn_Table D_00219EC0[8] = { (Fn_Table)(void (*)(T219C* self))func_0019EB28, (Fn_Table)func_001A2B48, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219EE0[8] = { (Fn_Table)(void (*)(T219C* self))func_0019EB28, (Fn_Table)func_001A2D30, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A2D88, (Fn_Table)func_0019ECE0, (Fn_Table)func_001A2E68 };
extern const Fn_Table D_00219F00[8] = { (Fn_Table)(void (*)(T219C* self))func_0019EB28, (Fn_Table)func_001A3008, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A31A0, (Fn_Table)func_0019ECE0, (Fn_Table)func_001A3128 };
extern const Fn_Table D_00219F20[8] = { (Fn_Table)func_001A31F0, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A3250, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219F40[8] = { (Fn_Table)func_001A3598, 0, 0, (Fn_Table)func_001A3730, (Fn_Table)func_001A38F0, (Fn_Table)func_001A3990, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219F60[8] = { (Fn_Table)(void (*)(T219C* self))func_0019EB28, (Fn_Table)func_001A39C8, 0, (Fn_Table)func_0019F390, (Fn_Table)func_001A3A18, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };


// D_0026AC10 points at the next free 128-byte entry of D_005E4700 (1024 of them).
void func_0019D410(DeferredRequest* src)
{
    DeferredRequest* cur = *(DeferredRequest**)D_0026AC10;
    if ((u32)(cur - D_005E4700) < 0x400) {
        *(DeferredRequest**)D_0026AC10 = cur + 1;
        *(DeferredRequest*)((u32)cur | 0x20000000) = *src;
    }
}

void func_0019CD90(C8B* self, s32 p, f32* out0, f32* out1, f32* out2)
{
    s32 n = self->f48;
    s32 q = p / ((n + 1) * (3 * n + 1));
    s32 r = p - q * (n + 1) * (3 * n + 1);
    s32 m = r / (3 * n + 1);
    s32 s = r - m * (3 * n + 1);
    *out0 = (f32)(q - n) / (f32)self->f48;
    *out1 = (f32)m / (f32)self->f48;
    *out2 = (f32)s / (f32)self->f48;
}

extern f32 D_00261858[];

void func_0019EC20(T219C* node);
void func_0019EC30(T219C* node);
u32 func_00152720(List01* list);
void func_0019E558(C1E* self);
void func_00129DF8(C02* self);

struct Iter_19E420 { List01* list; u8* link; s32 offset; Iter_19E420* saved; };

struct Next_19E420 {
    static T219C* Of(Iter_19E420* it)
    {
        T219C* obj = *(T219C**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_19E420 {
    static void Of(Iter_19E420* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_19E420*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_0019E420(C1E* self, f32 t)
{
    Iter_19E420 it;
    Begin_19E420::Of(&it, &self->list558);
    T219C* node;
    while ((node = Next_19E420::Of(&it)) != 0) {
        if (node->start >= D_00261858[1]) {
            continue;
        }
        func_0019EC20(node);
        node->vt->m04(node, t);
        func_0019EC30(node);
    }
    s64 m = 0x8000;
    m <<= 23;
    if ((self->flags & m) != 0 || func_00152720(&self->list558) != 0) {
        self->desc->m03(self);
    } else {
        func_0019E558(self);
    }
    func_00129DF8(self);
    D_0027B314 = (ListFrame*)it.saved;
}

void func_00182C58(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void* func_0015A480(void* a, s32 b, void* c);
void func_00139600(s32 a, s32 b, void* c, s32 d, s32 e, void* f);
void func_00139038(void* self, s32 a, s32 b, void* c, s32 d, void* e, void* f, void* g);
void func_00139B38(void* g, void* n);
void func_0019CC10(C8B* self, f32* out, f32 a, f32 b, f32 c);
void func_001399F8(void* g, s32 a, s32 b, void* c);
void func_0012CD78(f32 a, f32 b, Gr8B* g, void* r1, void* r2, s32 r3, void* r4, s32 r5, s32 r6, s32 r7);

extern s32 D_0026ABD0[];
extern s32 D_0026ABE0[];
extern s32 D_0026ABD8[];

void func_0019C728(C8B* self)
{
    Slot8B* s;
    s32 i;
    func_00182C58(self);
    self->f3C = func_0015A448(self->world, self->first34, self);
    if (self->f3C == 0) return;
    self->f40 = func_0015A480(self->world, self->second38, self->f3C);
    if (self->f40 == 0) return;
    for (i = 0; i < 24; i++) {
        s = &self->slots[i];
        Node8B* n = (Node8B*)func_0015A480(self->world, s->fC, self->f3C);
        s->n4 = n;
        if (n != 0) n->vtbl[7](n);
    }
    func_00139600(0x20, 0x18, self->slots, 0x10, 2, D_0026ABD0);
    func_00139038(self->f3C, 0x20, 0x18, self->slots, 1, D_0026ABE0, D_0026ABD8, &self->f3E4);
    if (self->f3E4->f78 == 0) self->f3E4->f78 = 1;
    void* nd = func_0015A480(self->world, 0x36, self->f3C);
    if (nd != 0) func_00139B38(self->f3E4, nd);
    f32 buf[24];
    func_0019CC10(self, buf, self->f54, self->f58, self->f5C);
    Slot8B* d = self->slots;
    f32* src = buf;
    for (i = 0; i < 24; i++, d++) *(f32*)d = *src++;
    func_001399F8(self->f3E4, 0x20, 0x18, self->slots);
    func_0012CD78(self->f3E4->pC0->p8->f8, 0.0f, self->f3E4, self->f40, self->f3C, 1, &self->q70, 0, 0, 0);
    self->f60 = self->f3E4->pC0->p8->f8;
    if (self->f80 != 0) {
        func_0019CC10(self, buf, self->f84, self->f88, self->f8C);
        d = self->slots;
        src = buf;
        for (i = 0; i < 24; i++, d++) *(f32*)d = *src++;
        func_001399F8(self->f3E4, 0x20, 0x18, self->slots);
        func_0012CD78(self->f3E4->pC0->p8->f8, 0.0f, self->f3E4, self->f40, self->f3C, 1, &self->q90, 0, 0, 0);
    } else {
        self->q90 = self->q70;
    }
    self->f50 = 1;
}

struct Iter_19E558 { List01* list; u8* link; s32 offset; Iter_19E558* prev; };


struct Begin_19E558 {
    static void Of(Iter_19E558* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (Iter_19E558*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_19E558 {
    static u8* Of(Iter_19E558* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct End_19E558 {
    static void Of(Iter_19E558* it)
    {
        D_0027B314 = (ListFrame*)it->prev;
    }
};

struct Hit_19E558 { u8 pad0[0x40]; f32 weight; u8 pad44[0x2C]; };

extern f32 D_00261858[];

void func_0018D608(void);
void* func_0018D658(s32 size);
void func_0018D6F0(void);
s32 func_0013E430(u8* a0, u8* a1, void** a2, f32 scale);
s32 func_00141C90(C03* self, void* a1, void* a2, void* a3, s32 a4, Hit_19E558* a5);
u32 func_00152720(List01* p);

void func_0019E558(C1E* self)
{
    if (self->f550 != 1) return;
    ContactRow03* l;
    for (l = self->contacts->head; l != 0; l = l->next) {
        Iter_19E558 it0;
        Begin_19E558::Of(&it0, &l->other->parts);
        if (l->other->flags538 & ((u64)0x8000 << 27)) {
            End_19E558::Of(&it0);
            continue;
        }
        C03* s2;
        for (s2 = (C03*)Next_19E558::Of(&it0); s2 != 0; s2 = (C03*)Next_19E558::Of(&it0)) {
            Iter_19E558 it1;
            void* buf;
            Hit_19E558 hits[4];
            Begin_19E558::Of(&it1, &self->list558);
            if ((s2->flags538 & ((u64)0x8000 << 28)) && (s2->desc->flags & 0x80) == 0) {
                End_19E558::Of(&it1);
                continue;
            }
            func_0018D608();
            if (s2->tree.count > 0) {
                buf = func_0018D658(s2->tree.count2 * 12);
                if (func_0013E430((u8*)s2->tree.nodes, (u8*)&self->v140, &buf, self->radius3D0) != 2) goto skip;
                buf = (u8*)buf - 12;
            } else {
                buf = 0;
            }
            {
                T219C* n;
                for (n = (T219C*)Next_19E558::Of(&it1); n != 0; n = (T219C*)Next_19E558::Of(&it1)) {
                    if (n->start >= D_00261858[1]) continue;
                    s32 cnt = func_00141C90(s2, buf, &n->q90, &n->q80, 4, hits);
                    s32 i;
                    for (i = 0; i < cnt; i++) {
                        Hit_19E558* h = &hits[i];
                        if (h->weight == 0.0f) continue;
                        if (n->vt->m07(n, s2, h, (u8*)h + 0x20) != 0) break;
                    }
                }
            }
        skip:
            func_0018D6F0();
            End_19E558::Of(&it1);
        }
        End_19E558::Of(&it0);
    }
    if (func_00152720(&self->list558) != 0) {
        self->desc->m03(self);
    }
}

s32 D_0026ABD0[2] = { 0x130, 0x132 };
s32 D_0026ABD8[2] = { 2, 0 };
s32 D_0026ABE0[4] = { 0x10, 0, 0, 0 };
s32 D_0026AC20[4] = { 0, 0, 0, 0 };

struct Pkt_19DDA0;
void func_001613C0(Pkt_19DDA0* p, s32 a, s32 b, u64 c);
void func_00161708(Pkt_19DDA0* p, s32 reg, u64 value);
void func_00161458(Pkt_19DDA0* p, u32 c);
void func_001615F0(Pkt_19DDA0* p, s32 a, s32 b, s32 c, s32 d);

void func_0019DDA0(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, Pkt_19DDA0* p)
{
    u32 col;
    func_001613C0(p, a <= 0xFE ? 0x46 : 6, 5, 0x441EE);
    col = (((a + 1) & 0x1FE) << 23) | (b << 16) | (g << 8) | r;
    func_00161708(p, 0x47, 0x31001);
    func_00161708(p, 0x42, 0x44);
    func_00161458(p, col);
    func_001615F0(p, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    func_001615F0(p, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
}
