// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "c6c.h"
#include "s1dbbd8.h"
#include "t219c.h"
#include "g27c220.h"
#include "s137290.h"
#include "s1eb050.h"
#include "t217d.h"
#include "r11b008.h"

void func_001B9F30(void);

void func_001DAE48(void)
{
    func_001B9F30();
}

void func_001C0C08(void* a, void* b);

void func_001DBAC0(void* self, void* a, void* b)
{
    func_001C0C08(a, b);
}

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 value, u32 size);

void* func_001DBBD8(u8* self)
{
    void* p = func_001B5EC0(self + 0x1B14);
    func_001F5C0C(p, 0, 0x14);
    return p;
}

void* func_001C0C68(void* a, void* b);

void* func_001DBB00(void* unused, void* a1, void* a2)
{
    return func_001C0C68(a1, a2);
}

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 a, s32 b);

void* func_001DBB50(u8* self)
{
    void* p = func_001B5EC0(self + 0x1B08);
    func_001F5C0C(p, 0, 16);
    return p;
}

void func_001B5F28(void* list, void* item);

void func_001DBB90(u8* self, Attach03* node)
{
    if (node) {
        do {
            Attach03* next = node->nextOwn;
            func_001B5F28(self + 0x1B08, node);
            node = next;
        } while (node);
    }
}

f32 func_001D86F8(f32 x, f32 lim, f32 base)
{
    f32 d = lim - base;
    if (x * 0.5f < d)
        d = d - x;
    else if (d < x * -0.5f)
        d = d + x;
    return d;
}

void func_001B5F28(void* list, void* item);

void func_001DBC18(u8* self, T219CHook* node)
{
    while (node != 0) {
        T219CHook* next = node->next;
        func_001B5F28(self + 0x1B14, node);
        node = next;
    }
}


void* func_001DBBD8(void* self);

S1DBBD8* func_001DBCC8(C6C* self, s32 a, s32 b, s32 c, s32 d)
{
    S1DBBD8* e = (S1DBBD8*)func_001DBBD8(self);
    e->k0 = a;
    e->k1 = b;
    e->k2 = c;
    e->k3 = d;
    if (self->f1ECC != 0) self->f1ECC->next = e;
    else self->f1EC8 = e;
    self->f1ECC = e;
    return e;
}

typedef void (*VFn_1D92F0)(void* self);
struct Sub_1D92F0 { VFn_1D92F0* vtbl; };
extern f32 D_0026185C;

void func_001D92F0(C19* self)
{
    self->f854 = D_0026185C;
    self->f858 = self->f858 - 1;
    Sub_1D92F0* s = (Sub_1D92F0*)self->fB14;
    if (s != 0) {
        s->vtbl[6](s);
    }
}


void func_001DBC18(void* self, void* node);

void func_001DBE48(C6C* self)
{
    while (self->f1EC8 != 0) {
        S1DBBD8* node = self->f1EC8;
        if (node == self->f1ECC) self->f1ECC = 0;
        self->f1EC8 = node->next;
        node->next = 0;
        node->fn(node->k1, node->k2, node->k3);
        func_001DBC18(self, node);
    }
}

typedef void (*VFn_1DACB0)(void* self, void* a, void* b);
struct Target_1DACB0 { VFn_1DACB0* vtbl; };
void func_001CB328(void* self, void* value);
void func_001924C8(void* self, void* a, void* b);

void func_001DACB0(C19* self, void* a, void* b)
{
    if (((Target_1DACB0*)self->fB78) != 0) {
        func_001CB328(((Target_1DACB0*)self->fB78), 0);
        Target_1DACB0* t = ((Target_1DACB0*)self->fB78);
        t->vtbl[82](t, a, b);
    } else {
        func_001924C8(self, a, b);
    }
}

void func_001B89B8(void* self);
void func_001DAD28(void* self);

void func_001DAE18(C19* self)
{
    func_001B89B8(self);
    func_001DAD28(self);
}

struct Link_1DAF08 { u8 pad[0x50]; void* owner; };
struct Rec_1DAF08 { u8 pad0[8]; s32 kind; u8 pad1[0x6CC - 0xC]; Link_1DAF08* link; };

extern s32 D_002751D4;

void func_00192230(void* self, s32 kind, Rec_1DAF08* rec);

void func_001DAF08(C19* self, s32 code, Rec_1DAF08* rec)
{
    func_00192230(self, code, rec);
    if (code == 0xE && rec->kind == 0x426) {
        T217D_E30* a = &D_00272430;
        s32 lim = D_002751D4;
        if (a->own < lim) {
            T217D_E30* b = &D_002726B0;
            if (b->own < lim) {
                if (rec->link->owner == self) {
                    a->own = a->own + 1;
                } else {
                    b->own = b->own + 1;
                }
            }
        }
    }
}

struct Obj_1DBA38 { u8 pad0[0x14]; s32 f14; };

s32 D_0027571C = 0;
extern s32 D_00275718;
s32 D_00275720 = 0;
extern s32 D_00275728;
void func_00137B60(void* self, s32 n);
void func_00137A60(void* self, s32 size, s32 obj);

void func_001DBA38(Obj_1DBA38* self)
{
    if (D_0027571C != 0) {
        D_00275728 = self->f14;
        func_00137B60(self, 0x10);
        func_00137A60(self, D_00275720, D_00275718);
    }
}

void func_001DA310(C19* self) { self->f6A0++; }

struct Entry_001DB1E8 { s32 active; s32 a; u8 pad[0x10]; f32 x; f32 y; s32 b; s32 c; };
void func_001DB1E8(C19* self, s32 a, s32 b, s32 c, f32 x, f32 y) { if (a && (u32)self->f870 < 16) { Entry_001DB1E8* e = &((Entry_001DB1E8*)self->f874)[self->f870]; self->f870++; e->a = a; e->active = 1; e->x = x; e->y = y; e->b = b; e->c = c; } }

struct Link_001DBB20 { u32 pad[2]; u32 flags; };
s32 func_001DBB20(C6C* self, Link_001DBB20** link, u32 value) { return ((*link)->flags & 2) && self->count38 >= 0xF7 && value == 0; }

typedef void (*VFn_1DB0C8)(void* self, void* a, s32 b, void* c, s32 d, void* e, s32 f);
struct Inner_1DB0C8 { VFn_1DB0C8* vtbl; };
struct Outer_1DB0C8 { u8 pad0[0x34]; Inner_1DB0C8* inner; };

void func_001DB0C8(u8* self, Outer_1DB0C8* obj)
{
    s32 loc[4];
    Inner_1DB0C8* inner;

    *(Outer_1DB0C8**)(self + 0x848) = obj;
    inner = obj->inner;
    if (inner->vtbl[10] != 0) {
        inner->vtbl[10](inner, self + 0x100, 0, loc, 0, self + 0x84C, 0);
    }
}

void func_00152438(void* self, s32 value);

void func_001DB480(u8* self)
{
    u32 i;
    for (i = 0; i < 0x200; i++) {
        func_00152438(self + 0x84 + i * 0xC, 0xC);
    }
}


void func_001DBC18(void* self, void* node);

void func_001DBD40(C6C* self, u32 mask, s32 k0, s32 k1, s32 k2, s32 k3)
{
    S1DBBD8* prev = 0;
    S1DBBD8* removed = 0;
    S1DBBD8* cur = self->f1EC8;
    S1DBBD8* next;
    s32 bit;

    if (cur != 0) {
        do {
            next = cur->next;
            bit = 1;
            while (bit < 16) {
                if (mask & bit) {
                    switch (bit) {
                    case 1:
                        if (cur->k0 != k0) goto miss;
                        break;
                    case 2:
                        if (cur->k1 != k1) goto miss;
                        break;
                    case 4:
                        if (cur->k2 != k2) goto miss;
                        break;
                    case 8:
                        if (cur->k3 != k3) goto miss;
                        break;
                    }
                }
                bit <<= 1;
            }
            if (prev != 0) {
                prev->next = next;
            } else {
                self->f1EC8 = next;
            }
            if (next == 0) {
                self->f1ECC = prev;
            }
            cur->next = removed;
            removed = cur;
            goto advance;
        miss:
            prev = cur;
        advance:
            cur = next;
        } while (cur != 0);
    }
    func_001DBC18(self, removed);
}

struct Sub_1D8740 { u8 pad0[0xC]; s32 n0C; };

f32 func_001D86F8(f32 x, f32 lim, f32 base);

s32 func_001D8740(C19* self, C19* other)
{
    s32 d = self->fB00 - other->fB00;
    if (d > 0) return 1;
    if (d < 0) return 0;
    d = ((Sub_1D8740*)self->fAF8)->n0C - ((Sub_1D8740*)other->fAF8)->n0C;
    if (d > 0) return 1;
    if (d < 0) return 0;
    f32 r = func_001D86F8(self->f834, self->f83C, other->f83C);
    return 0.0f < r;
}

void func_001B8540(void* self);
void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_001B8420(void* self, void* p, f32 f);

struct __attribute__((aligned(16))) Quad_001DAC20 { s32 a, b, c, d; };
struct Slot_001DAC20 { void* ptr; u8 pad[0x5C]; };
void func_001DAC20(C19* self)
{
    u32 i;
    Quad_001DAC20 q;
    func_001B8540(self);
    for (i = 0; i < 4; i++) {
        Slot_001DAC20* slot = (Slot_001DAC20*)&self->f6B0[i];
        if (slot->ptr != 0) {
            f32 f;
            q = *(Quad_001DAC20*)((u8*)slot->ptr + 0x190);
            func_00128018(self, 0, &q, &q);
            f = ((s32)i < 2) ? self->f610 : self->f614;
            func_001B8420(self, &q, f);
        }
    }
}

extern u8 D_0026DAAC[];

void func_001922E8(void* a, void* b);
void func_001DDC38(void* sub, void* self);
void func_001DB238(void* self, s32 mode);

void func_001DAE68(C19* self, void* v)
{
    func_001922E8(self, v);
    if (v != 0) {
        T217D_E30* a = &D_0026D5C8;
        *(void**)(D_0026DAAC) = (u8*)self + 0x858;
        T217D_E30* b = &D_0026DAC8;
        a->target = (s32*)((u8*)self + 0xB00);
        a->limit = (s32*)((u8*)self + 0xB04);
        b->target = (s32*)((u8*)self + 0xB08);
        b->limit = (s32*)((u8*)self + 0xB0C);
        func_001DDC38(*(void**)((u8*)self + 0x14), self);
    } else {
        if (self->fB34 == 2) {
            func_001DB238(self, 0);
        }
    }
}

struct Obj_1DAFB8 { void** vtbl; };
struct Arg_1DAFB8 { u8 pad_00[0x34]; Obj_1DAFB8* obj; };
struct Entry_1DAFB8 { s32 flag; void* ptr; u8 pad_08[8]; u8 at10[0x18]; };
void func_001DAD28(void* self);
void func_001F3BD8(void* self, void* arg);

typedef void (*VFn7_1DAFB8)(Obj_1DAFB8* self, void* a1, s32 a2, s32 a3, s32 a4, void* a5, void* a6);
typedef f32 (*VFnF_1DAFB8)(Obj_1DAFB8* self);

void func_001DAFB8(C19* self, Arg_1DAFB8* arg)
{
    self->f830 = arg;
    Obj_1DAFB8* o = arg->obj;
    if (o->vtbl[10]) ((VFn7_1DAFB8)o->vtbl[10])(o, (u8*)self + 0x100, 0, 0, 0, (u8*)self + 0x838, 0);
    func_001DAD28(self);
    self->f844 = self->f840;
    self->f834 = ((VFnF_1DAFB8)((Arg_1DAFB8*)self->f830)->obj->vtbl[8])(((Arg_1DAFB8*)self->f830)->obj);
    for (s32 i = 0; i < self->f870; i++) {
        Entry_1DAFB8* e = &((Entry_1DAFB8*)self->f874)[i];
        if (e->flag == 0) {
            s32 loc[4];
            func_001F3BD8(e->ptr, loc);
            Obj_1DAFB8* o2 = ((Arg_1DAFB8*)self->f830)->obj;
            if (o2->vtbl[10]) ((VFn7_1DAFB8)o2->vtbl[10])(o2, loc, 0, 0, 0, 0, e->at10);
        }
    }
}

extern s32 D_00275718;
extern s32 D_0027571C;
extern s32 D_00275720;
s32 D_00275724;
extern s32 D_00275728;

s32 func_00137480(void* self, s32 n);
s32 func_00137D78(void* self);
s32 func_0018D500(s32 size);

void func_001DB928(s32 a0, S137290* self)
{
    s32 s2 = a0;
    s32 s3;
    s32 s0;
    if (self->mode == 1) {
        if (s2 == 0) {
            func_00137480(self, D_00275728);
            self->f14 -= D_00275728;
        }
        s3 = func_00137D78(self);
        s0 = func_00137D78(self);
    } else {
        s3 = func_00137D78(self);
        s0 = func_00137D78(self);
        if (s0 != D_00275724) s2 = 1;
        if (s2 == 0) {
            s32 v = self->f14 - D_00275728;
            self->f14 = (s2 < v) ? v : 0;
        }
    }
    s32 r = func_0018D500(s3);
    D_00275724 = s0;
    D_00275720 = s3;
    D_00275718 = r;
    D_0027571C = s2;
}

struct Res_1DA170 { u8 pad[0x48]; void* f48; };

Res_1DA170* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
s32 func_001E9970(void);

void func_001DA170(C19* self)
{
    s32 a = 0;
    s32 b = 0;
    switch (self->fB30) {
    case 0: {
        Res_1DA170* r = func_0015A418(self->world, 5, 0x42C, 0);
        if (r != 0) {
            void* dev = r->f48;
            s32 code;
            func_001B6568(dev, &code);
            if (code == -1) {
                func_001B6598(dev, &code);
            }
            if (code < 0x431) {
                if (code >= 0x42F) {
                    a = func_001E9970();
                }
            }
        }
        break;
    }
    case 1:
        b = func_001E9970();
        break;
    }
    if (a != 0) {
        D_0026D848.vt->m14(&D_0026D848);
        D_0026D5C8.vt->m14(&D_0026D5C8);
        D_0026DAC8.vt->m14(&D_0026DAC8);
    } else {
        D_0026D848.vt->m15(&D_0026D848);
        D_0026D5C8.vt->m15(&D_0026D5C8);
        D_0026DAC8.vt->m15(&D_0026DAC8);
    }
    if (b != 0) {
        D_00272430.vt->m14(&D_00272430);
        D_002726B0.vt->m14(&D_002726B0);
    } else {
        D_00272430.vt->m15(&D_00272430);
        D_002726B0.vt->m15(&D_002726B0);
    }
}

void func_0011A800(void* a);
s32 func_0011A498(void* a, s32 b, s32 c, R11B008* d);
void func_0011A080(R11B008* t, R11B008Node* n, void* c);
void* func_0011A400(R11B008* self, void* table, s32 key, R11B008* item);
extern u8 D_00259F38[];

void func_001DBEC8(C6C* self, f32 limit)
{
    R11B008 a;
    R11B008 q;
    R11B008 t;
    func_0011B008(&a);
    func_0011B008(&q);
    func_0011A800(D_00259F38);
    func_0011A498(self->f2C, self->f1EF8, 0, &a);
    R11B008Node* n;
    s32 found;
    if (a.tag != 0x1E) {
        goto fin;
    }
    {
        n = a.node;
        found = 0;
        while (n) {
            R11B008Node* e = n->node;
            f32 d = e->f - limit;
            if (d <= 0.0f) {
                found = 1;
                func_0011A080(&t, e->next, self->f2C);
                func_0011B0A8(&q, &t);
                func_0011B060(&t, 2);
                func_0011B538(n, 0);
            } else {
                func_0011B5B0(e, d);
            }
            n = n->next;
        }
        if (!found) {
        fin:
            func_0011B060(&q, 2);
            func_0011B060(&a, 2);
            return;
        }
    }
    func_0011A498(self->f2C, self->f1EF8, 0, &a);
    {
        R11B008Node* head = a.node;
        R11B008Node* prev = 0;
        for (n = a.node; n; n = n->next) {
            if (n->tag == 0x1E) {
                prev = n;
            } else if (prev) {
                prev->next = n->next;
            } else {
                head = n->next;
            }
        }
        if (head != a.node) {
            if (head) {
                func_0011B6C0(&a, head);
            } else {
                func_0011B538(&a, 0);
            }
            func_0011A400(&t, self->f2C, self->f1EF8, &a);
            func_0011B060(&t, 2);
        }
    }
    func_0011B060(&q, 2);
    func_0011B060(&a, 2);
}

struct Sub_1D8578 { u8 pad0[0xC]; s32 n0C; };
struct Tri_1D8578 { f32 a; f32 b; f32 c; };

extern f32 D_00261858[];
f32 D_002754A0[4] = { 1.5f, 2.5f, 0.0f, 0.0f };
extern f32 D_00275490[4];

void* func_001925F0(void);
f32 func_001EA4B8(void* p, s32 zero, f32 a, f32 b, f32 c);
f32 func_001EAAE0(f32 a, f32 b);

void func_001D8578(C19* self)
{
    if (self != func_001925F0()) {
        self->f85C = func_001EA4B8((u8*)D_00275490, 0, self->f85C, self->f860, D_00261858[2]);
        if (!(D_00261858[1] < self->f864)) {
            f32 one = 1.0f;  // hoisted: retail holds 1.0f in $f3 before the multiply
            s32 idx = 3 * (self->fB00 - 1) + ((Sub_1D8578*)self->fAF8)->n0C;
            f32 t = (f32)idx * 0.1f;
            f32 w;
            if (t < 0.0f) {
                w = 0.0f;
            } else if (one < t) {
                w = one;
            } else {
                w = t;
            }
            Tri_1D8578* q = (Tri_1D8578*)((u8*)self + 0x670);
            f32 val = q->a + w * (q->b + w * q->c);
            f32 lo = self->f680;
            f32 hi = self->f684;
            if (val < lo) {
                val = lo;
            } else if (hi < val) {
                val = hi;
            }
            self->f860 = val;
            f32 r = func_001EAAE0(-0.05f, 0.05f);
            self->f860 = self->f860 + r;
            f32 r2 = func_001EAAE0(D_002754A0[0], D_002754A0[1]);
            self->f864 = D_00261858[1] + r2;
        }
    }
}

struct Entry_1DB110 {
    s32 f0;
    void* f4;
    u8 pad8[4];
    s32 fC;
    void* f10;
    Entry_1DB110* f14;
    u8 pad18[0x10];
};

struct VObj_1DB110;
typedef void (*VFn_1DB110)(VObj_1DB110* self, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, void* a6);
struct VObj_1DB110 {
    VFn_1DB110* vtbl;
};

struct Node_1DB110 {
    u8 pad0[0x34];
    VObj_1DB110* f34;
};

struct __attribute__((aligned(16))) Quad_1DB110 {
    s32 a, b, c, d;
};

void func_001F3BD8(void* item, void* out);

void func_001DB110(C19* self, void* item)
{
    if (item == 0) {
        return;
    }
    s32 n = self->f870;
    if ((u32)n >= 16) {
        return;
    }
    self->f870 = n + 1;
    Entry_1DB110* e = &((Entry_1DB110*)self->f874)[n];
    e->f4 = item;
    e->f0 = 0;
    if (self->fAF4 == 0) {
        self->fAF8 = e;
        self->fAF4 = e;
        e->f14 = e;
    } else {
        e->f14 = ((Entry_1DB110*)self->fAF4)->f14;
        ((Entry_1DB110*)self->fAF4)->f14 = e;
        e->fC = e->f14->fC + 1;
    }
    if (self->f830 != 0) {
        Quad_1DB110 tmp;
        func_001F3BD8(item, &tmp);
        VObj_1DB110* o = ((Node_1DB110*)self->f830)->f34;
        VFn_1DB110 fn = o->vtbl[10];
        if (fn != 0) {
            fn(o, &tmp, 0, 0, 0, 0, &e->f10);
        }
    }
}

extern f32 D_0026185C;
void* func_001925F0(void);
void func_001929D0(void* self);

void func_001DB238(C19* self, s32 mode)
{
    if (mode != self->fB34) {
        *(s32*)((u8*)self + 0xB34) = mode;
        *(f32*)((u8*)self + 0xB38) = D_0026185C;
        if (mode == 2 && self != func_001925F0()) {
            func_001929D0(self);
        }
    }
}

void func_00192B58(C19* self, f32 t);
void func_001D8578(C19* self);
void func_001D87C8(C19* self, s32* out);
void func_001D8BD0(C19* self);
void func_001D9678(C19* self, f32 t);
void func_001D8D90(C19* self);
void func_001D8E40(C19* self);
void func_001D9488(C19* self, s32 v);
void func_001D9AC8(C19* self);
void func_00129DF8(C19* self);

extern f32 D_0026185C;

void func_001D9C98(C19* self, f32 t)
{
    s32 local = 0;
    func_00192B58(self, t);
    if (self->fB34 != 1) {
        if (self->fB34 < 2) {
            if (self->fB34 == 0) {
                self->f698 = 0;
            }
        }
    } else {
        func_001D8578(self);
        func_001D87C8(self, &local);
        func_001D8BD0(self);
    }
    func_001D9678(self, t);
    func_001D8D90(self);
    func_001D8E40(self);
    func_001D9488(self, local);
    func_001D9AC8(self);
    if (self->rot.r[2].z > 0.5f) {
        self->f850 = D_0026185C;
    }
    if (self->fB34 != 0) {
        func_00129DF8(self);
    }
}

struct Inner_1D9338 { u8 pad0[0xC]; s32 value; };
extern u8 D_00261EF0[];

void func_00151E20(void* msg, f32 value);

void func_001D9338(C19* self)
{
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    s32 idx = self->fB00 - 1;
    f32 f = (f32)(idx * 3 + ((Inner_1D9338*)self->fAF8)->value) * 0.1f;
    if (f < lo) {
        f = lo;
    } else if (hi < f) {
        f = hi;
    }
    s32 s0 = self->fB0C - self->fB08;
    s32 t = 0;
    if (s0 >= 3) {
        s32 mk = 1 << (s0 & 7);
        t = D_002623C8->bits74[s0 / 8] & mk;
    }
    if (s0 < 3 || t) {
        func_00151E20(D_00261EF0, f);
    }
    if (s0 >= 0) {
        do {
            G27C230* g = D_002623C8;
            u8* bb = g->bits74;
            u8* byte = bb + s0 / 8;
            s32 mask = 1 << (s0 & 7);
            if ((*byte & mask) == 0) {
                *byte = (u8)(*byte | mask);
                g->count70++;
            }
            s0--;
        } while (s0 >= 0);
    }
}

s32 func_001EB080(s32 count, S1EB050* spans, f32 x);

f32 func_001D8470(s32 count, S1EB050* spans, f32 x)
{
    if (func_001EB080(count, spans, x) == 0) {
        return x;
    }
    f32 bestDist = 3.4028234663852886e+38f;
    f32 best = bestDist;
    if (count > 0) {
        S1EB050* s = spans;
        s32 n = count;
        do {
            f32 d = __builtin_fabsf(x - s->lo);
            if (d < bestDist) {
                if (func_001EB080(count, spans, s->lo) == 0) {
                    best = s->lo;
                    bestDist = d;
                }
            }
            d = __builtin_fabsf(x - s->hi);
            if (d < bestDist) {
                if (func_001EB080(count, spans, s->hi) == 0) {
                    best = s->hi;
                    bestDist = d;
                }
            }
            s++;
            n--;
        } while (n != 0);
    }
    return best;
}

struct Sub_1DB4C8 { u8 b; };

extern s32 D_00262C64;

void func_00182C18(C6C* self);
void func_001C09D8(C6C* self, s32 a, s32 b);
void* func_0018D5C0(s32 size);
void func_001DC740(C6C* self);
void func_001B5DD0(Sub_1DB4C8* p, s32 a, s32 b);
void func_001B5E30(Sub_1DB4C8* p, s32 a, s32 b);
void func_00152438(Sub_1DB4C8* p, s32 a);
void func_001DBA90(C6C* self, f32 x);

#define SUB(off) ((Sub_1DB4C8*)((u8*)self + (off)))

void func_001DB4C8(C6C* self)
{
    f32 x;
    func_00182C18(self);
    func_001C09D8(self, 0, 0);
    self->buf1AD8 = (void*)func_0018D500(0x4800);
    self->buf1ADC = func_0018D5C0(0x10000);
    func_001DC740(self);
    func_001B5DD0(SUB(0x1AF0), 0x10, 0x400);
    func_001B5DD0(SUB(0x1AFC), 0xE0, 0x100);
    func_001B5DD0(SUB(0x1B08), 0x10, 0x80);
    func_001B5DD0(SUB(0x1B14), 0x14, 0x400);
    func_001B5DD0(SUB(0x1B2C), 0x140, 0x180);
    func_001B5E30(SUB(0x1B40), 0x10C0, 0x80);
    func_001B5DD0(SUB(0x1B4C), 0x580, 0x20);
    func_001B5DD0(SUB(0x1B58), 0xEC, 0x100);
    func_001B5DD0(SUB(0x1B20), 0xD0, 0x400);
    func_001B5DD0(SUB(0x1BA0), 0x90, 0x80);
    func_001B5DD0(SUB(0x1BB8), 0xC, 0x20);
    func_001B5DD0(SUB(0x1B88), 0x40, 0x100);
    func_001B5DD0(SUB(0x1BF4), 0x2E0, 0x20);
    func_001B5DD0(SUB(0x1BD0), 0x70, 0x20);
    func_001B5DD0(SUB(0x1C0C), 0x8, 0x80);
    func_001B5DD0(SUB(0x1C18), 0x14, 0x100);
    self->buf1ED4 = (void*)func_0018D500(0x1000);
    func_00152438(SUB(0x48), 0x1C);
    func_00152438(SUB(0x54), 0x48);
    func_00152438(SUB(0x78), 0x48);
    func_00152438(SUB(0x60), 0x40);
    func_00152438(SUB(0x6C), 0x414);
    func_00152438(SUB(0x3C), 0x2D0);
    func_00152438(SUB(0x1B64), 0x34);
    func_00152438(SUB(0x1B70), 0x34);
    func_00152438(SUB(0x1B7C), 0x34);
    func_00152438(SUB(0x1B94), 0x10);
    func_00152438(SUB(0x1BAC), 0x64);
    func_00152438(SUB(0x1BC4), 0x4);
    func_00152438(SUB(0x1BE8), 0x410);
    func_00152438(SUB(0x1C00), 0xB8);
    func_00152438(SUB(0x1BDC), 0x64);
    func_00152438(SUB(0x1C3C), 0x2DC);
    func_00152438(SUB(0x1C48), 0x5DC);
    func_00152438(SUB(0x1C54), 0x374);
    func_00152438(SUB(0x1C60), 0x600);
    func_00152438(SUB(0x1C6C), 0x90);
    func_00152438(SUB(0x1C78), 0x56C);
    func_00152438(SUB(0x1C84), 0x50);
    func_00152438(SUB(0x1C90), 0x38);
    func_00152438(SUB(0x1C9C), 0x38);
    func_00152438(SUB(0x1CA8), 0xAF0);
    func_00152438(SUB(0x1CB4), 0x630);
    func_00152438(SUB(0x1CC0), 0x630);
    func_00152438(SUB(0x1C24), 0xC);
    func_00152438(SUB(0x1C30), 0xC);
    func_00152438(SUB(0x1CCC), 0xC10);
    func_00152438(SUB(0x1CD8), 0x34);
    x = -1500.0f;
    if (D_00262C64 & 4) {
        x = -900.0f;
    }
    func_001DBA90(self, x);
    self->f1D64 = 0x10;
    self->f1D65 = 0x10;
    self->f1D66 = 0x40;
    self->f1D68 = 50.0f;
    self->f1D70 = -1;
    self->f1D74 = 0;
    self->f2308 = 15.0f;
    self->f230C = 180.0f;
    self->f234C = 1.0f;
    self->f2350 = 1.0f;
    self->f2354 = 1;
    self->f235C = 0xF03FFFFF;
}

typedef s32 Id_1DBAE0;

s32 func_001C0C50(Id_1DBAE0 index);

s32 func_001DBAE0(s32 unused, Id_1DBAE0 index)
{
    return func_001C0C50(index);
}


void func_001DBC60(C6C* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    S1DBBD8* n = self->f1EC8;
    if (n != 0) {
        do {
            if (n->k0 == a1 && n->k1 == a2 && n->k2 == a3 && n->k3 == a4) {
                return;
            }
            n = n->next;
        } while (n != 0);
    }
    func_001DBCC8(self, a1, a2, a3, a4);
}


extern f32 D_002754F8; extern f32 D_002754F4; extern f32 D_00261860; extern f32 D_002754E8[3];
f32 func_00205778(f32 a, f32 b); f32 func_001EA408(f32 a); f32 func_001EA480(f32 a, f32 b); f32 func_001EA728(void* p, void* out, f32 a, f32 b, f32 c);
void func_001D8D90(C19* self)
{
    f32 a = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    f32 b = func_001EA408(self->f694 - a);
    f32 c = func_001EA480(D_002754F8 * b, D_002754F4);
    self->f69C = func_001EA728((u8*)D_002754E8, 0, self->f69C, c, D_00261860);
    for (u32 i = 0; i < 4; i++) {
        Slot19* s = &self->f6B0[i];
        if ((s32)i < 2) {
            s->f50 = self->f698 / self->f610;
        } else {
            s->f50 = self->f698 / self->f614;
        }

    }
}

extern s32 D_00269C90;
extern s32 D_00262E10;
extern s32 D_00262C6C;
extern void* D_00261990;
extern u8 D_00275BC0[];
extern s32 D_002640A4;
extern f32 D_00261854;
extern s32 D_00261D38;

void func_00192880(s32 index);
void func_0016E148(void);
void func_00143AF0(void* obj);
void func_001DFD70(void);
void func_0017FD70(void);
void func_00191EE8(void);
void func_00169CA0(void);
void func_001C07B0(void);
void func_001B40C8(void);
void func_0011C040(void);
void func_001E9688(void* a);
void func_0018D550(void);

struct __attribute__((packed)) Word_1DB838 { s32 v; };

void func_001DB838(s32 a0)
{
    if (a0 != 0) {
        func_00192880(-1);
        D_00269C90 = 0;
        D_00262E10 = 0;
        D_00262C6C = 0;
        func_0016E148();
        func_00143AF0(D_00261990);
        func_001DFD70();
        func_0017FD70();
        func_00191EE8();
        func_00169CA0();
        func_001C07B0();
        func_001B40C8();
        func_0011C040();
        func_001E9688(D_00275BC0);
        func_0018D550();
        u8* c = (u8*)&D_0026CE48;
        u8* e = (u8*)&D_0026E760;
        D_00261990 = 0;
        D_002640A4 = 0;
        D_00261854 = 1.0f;
        ((Word_1DB838*)(c + 0x274))->v = 0;
        ((Word_1DB838*)(e + 0x280))->v = 0;
        D_00261D38 = 0;
        *(s32*)(c + 0x278) = 0;
        *(s32*)(e + 0x28C) = 0;
    }
}

f32 D_00275490[4] = { 0.05f, 0.0f, 0.25f, 0.0f };
f32 D_002754E8[3] = { 8.0f, 0.0f, 0.25f };
f32 D_002754F4 = 0.7f;
f32 D_002754F8 = 0.5f;
s32 D_00275728;

typedef int V128_1DB290 __attribute__((mode(TI)));

struct Poly_1DB290 {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

struct Obj_1DB290 {
    u8 pad0[0x620];
    f32 f620;
    f32 f624;
    f32 f628;
    u8 pad62C[4];
    u8 v630[0x10];
    f32 f640;
    f32 f644;
    u8 pad648[8];
    u8 v650[0x10];
    f32 f660;
    f32 f664;
    u8 pad668[8];
    u8 v670[0x10];
    f32 f680;
    f32 f684;
    u8 pad688[0x854 - 0x688];
    f32 f854;
    s32 f858;
    f32 f85C;
    f32 f860;
    f32 f864;
    u8 pad868[4];
    f32 f86C;
    u8 pad870[0xAF4 - 0x870];
    s32 fAF4;
    s32 fAF8;
    u8 padAFC[4];
    s32 fB00;
    u8 padB04[0xB10 - 0xB04];
    f32 fB10;
};

void func_00118CF0(void* out, f32 f);
void func_00118D10(void* out, void* in);
void func_00118D20(void* dst, V128_1DB290 v);
V128_1DB290 func_001DB460(V128_1DB290 a, V128_1DB290 b, V128_1DB290 c, V128_1DB290 d);

struct Bounds_1DB290 {
    f32 lo;
    f32 hi;
    void Blend(f32 y, const Bounds_1DB290& a, f32 x, const Bounds_1DB290& b)
    {
        lo = y * a.lo + x * b.lo;
        hi = y * a.hi + x * b.hi;
    }
};
struct Clamp2_1DB290 {
    f32 lo;
    f32 hi;
    f32 Clamp(f32 v)
    {
        if (v < lo)
            return lo;
        if (hi < v)
            return hi;
        return v;
    }
};
void func_001DB290(Obj_1DB290* self)
{
    self->fB00 = 1;
    self->fAF8 = self->fAF4;
    self->f858 = 0;
    self->f854 = -10.0f;
    self->f864 = -10.0f;
    self->f86C = -10.0f;
    self->fB10 = -10.0f;
    G27C230* rec = D_002623C8;
    f32 t = ((Poly_1DB290*)&self->f620)->Eval(rec->dt);
    f32 l = D_00275C60.lo;
    f32 h = D_00275C60.hi;
    f32 x;
    if (t < l)
        x = l;
    else if (h < t)
        x = h;
    else
        x = t;
    f32 y = 1.0f - x;
    u8* p630 = self->v630;
    u8* p650 = self->v650;
    u8* p670 = self->v670;
    V128_1DB290 a, b, c, d;
    V128_1DB290 a2, b2, c2, d2;
    func_00118CF0(&a, y);
    a2 = a;
    func_00118D10(&b, p630);
    b2 = b;
    func_00118CF0(&c, x);
    c2 = c;
    func_00118D10(&d, p650);
    d2 = d;
    func_00118D20(p670, func_001DB460(a2, b2, c2, d2));
    ((Bounds_1DB290*)&self->f680)->Blend(y, *(Bounds_1DB290*)&self->f640, x, *(Bounds_1DB290*)&self->f660);
    f32 r = ((Clamp2_1DB290*)&self->f680)->Clamp(*(f32*)p670);
    self->f860 = r;
    self->f85C = r;
}
