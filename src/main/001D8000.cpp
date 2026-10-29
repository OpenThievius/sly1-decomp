// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

struct Node_001DBB90 { u8 pad[0xC]; Node_001DBB90* next; };

void func_001B5F28(void* list, void* item);

void func_001DBB90(u8* self, Node_001DBB90* node)
{
    if (node) {
        do {
            Node_001DBB90* next = node->next;
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

struct Node_1DBC18 { u8 pad[0x10]; Node_1DBC18* next; };

void func_001B5F28(void* list, void* item);

void func_001DBC18(u8* self, Node_1DBC18* node)
{
    while (node != 0) {
        Node_1DBC18* next = node->next;
        func_001B5F28(self + 0x1B14, node);
        node = next;
    }
}

struct Entry_1DBCC8 { s32 k0; s32 k1; s32 k2; s32 k3; Entry_1DBCC8* next; };
struct Owner_1DBCC8 { u8 pad[0x1EC8]; Entry_1DBCC8* head; Entry_1DBCC8* tail; };

void* func_001DBBD8(void* self);

Entry_1DBCC8* func_001DBCC8(Owner_1DBCC8* self, s32 a, s32 b, s32 c, s32 d)
{
    Entry_1DBCC8* e = (Entry_1DBCC8*)func_001DBBD8(self);
    e->k0 = a;
    e->k1 = b;
    e->k2 = c;
    e->k3 = d;
    if (self->tail != 0) self->tail->next = e;
    else self->head = e;
    self->tail = e;
    return e;
}

typedef void (*VFn_1D92F0)(void* self);
struct Sub_1D92F0 { VFn_1D92F0* vtbl; };
struct Ctrl_1D92F0 {
    u8 pad0[0x854];
    f32 f854;
    s32 n858;
    u8 pad1[0xB14 - 0x85C];
    Sub_1D92F0* sub;
};

extern f32 D_0026185C;

void func_001D92F0(Ctrl_1D92F0* self)
{
    self->f854 = D_0026185C;
    self->n858 = self->n858 - 1;
    Sub_1D92F0* s = self->sub;
    if (s != 0) {
        s->vtbl[6](s);
    }
}

typedef void (*VFn_1DBE48)(s32 a, s32 b, s32 c);
struct Node_1DBE48 { VFn_1DBE48 fn; s32 a; s32 b; s32 c; Node_1DBE48* next; };
struct Owner_1DBE48 { u8 pad[0x1EC8]; Node_1DBE48* head; Node_1DBE48* tail; };

void func_001DBC18(void* self, void* node);

void func_001DBE48(Owner_1DBE48* self)
{
    while (self->head != 0) {
        Node_1DBE48* node = self->head;
        if (node == self->tail) self->tail = 0;
        self->head = node->next;
        node->next = 0;
        node->fn(node->a, node->b, node->c);
        func_001DBC18(self, node);
    }
}

typedef void (*VFn_1DACB0)(void* self, void* a, void* b);
struct Target_1DACB0 { VFn_1DACB0* vtbl; };
struct Owner_1DACB0 { u8 pad[0xB78]; Target_1DACB0* target; };

void func_001CB328(void* self, void* value);
void func_001924C8(void* self, void* a, void* b);

void func_001DACB0(Owner_1DACB0* self, void* a, void* b)
{
    if (self->target != 0) {
        func_001CB328(self->target, 0);
        Target_1DACB0* t = self->target;
        t->vtbl[82](t, a, b);
    } else {
        func_001924C8(self, a, b);
    }
}

void func_001B89B8(void* self);
void func_001DAD28(void* self);

void func_001DAE18(void* self)
{
    func_001B89B8(self);
    func_001DAD28(self);
}

struct Counter_1DAF08 { u8 pad[0x27C]; s32 count; };
struct Link_1DAF08 { u8 pad[0x50]; void* owner; };
struct Rec_1DAF08 { u8 pad0[8]; s32 kind; u8 pad1[0x6CC - 0xC]; Link_1DAF08* link; };

extern u8 D_00272430[];
extern u8 D_002726B0[];
extern s32 D_002751D4;

void func_00192230(void* self, s32 kind, Rec_1DAF08* rec);

void func_001DAF08(void* self, s32 code, Rec_1DAF08* rec)
{
    func_00192230(self, code, rec);
    if (code == 0xE && rec->kind == 0x426) {
        Counter_1DAF08* a = (Counter_1DAF08*)D_00272430;
        s32 lim = D_002751D4;
        if (a->count < lim) {
            Counter_1DAF08* b = (Counter_1DAF08*)D_002726B0;
            if (b->count < lim) {
                if (rec->link->owner == self) {
                    a->count = a->count + 1;
                } else {
                    b->count = b->count + 1;
                }
            }
        }
    }
}

struct Obj_1DBA38 { u8 pad0[0x14]; s32 f14; };

extern s32 D_0027571C;
extern s32 D_00275718;
extern s32 D_00275720;
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

struct Obj_001DA310 { u8 pad[0x6A0]; s32 value; };
void func_001DA310(Obj_001DA310* self) { self->value++; }

struct Entry_001DB1E8 { s32 active; s32 a; u8 pad[0x10]; f32 x; f32 y; s32 b; s32 c; };
struct Obj_001DB1E8 { u8 pad[0x870]; u32 count; Entry_001DB1E8 entries[16]; };
void func_001DB1E8(Obj_001DB1E8* self, s32 a, s32 b, s32 c, f32 x, f32 y) { if (a && self->count < 16) { Entry_001DB1E8* e = &self->entries[self->count]; self->count++; e->a = a; e->active = 1; e->x = x; e->y = y; e->b = b; e->c = c; } }

struct Obj_001DBB20 { u8 pad[0x38]; s32 count; };
struct Link_001DBB20 { u32 pad[2]; u32 flags; };
s32 func_001DBB20(Obj_001DBB20* self, Link_001DBB20** link, u32 value) { return ((*link)->flags & 2) && self->count >= 0xF7 && value == 0; }

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

struct Node_1DBD40 { s32 f0; s32 f4; s32 f8; s32 fC; struct Node_1DBD40* next; };
struct Self_1DBD40 { u8 pad0[0x1EC8]; struct Node_1DBD40* head; struct Node_1DBD40* tail; };

void func_001DBC18(void* self, void* node);

void func_001DBD40(struct Self_1DBD40* self, u32 mask, s32 k0, s32 k1, s32 k2, s32 k3)
{
    struct Node_1DBD40* prev = 0;
    struct Node_1DBD40* removed = 0;
    struct Node_1DBD40* cur = self->head;
    struct Node_1DBD40* next;
    s32 bit;

    if (cur != 0) {
        do {
            next = cur->next;
            bit = 1;
            while (bit < 16) {
                if (mask & bit) {
                    switch (bit) {
                    case 1:
                        if (cur->f0 != k0) goto miss;
                        break;
                    case 2:
                        if (cur->f4 != k1) goto miss;
                        break;
                    case 4:
                        if (cur->f8 != k2) goto miss;
                        break;
                    case 8:
                        if (cur->fC != k3) goto miss;
                        break;
                    }
                }
                bit <<= 1;
            }
            if (prev != 0) {
                prev->next = next;
            } else {
                self->head = next;
            }
            if (next == 0) {
                self->tail = prev;
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

struct Obj_1D8740 {
    u8 pad0[0x834];
    f32 f834;
    u8 pad1[0x83C - 0x838];
    f32 f83C;
    u8 pad2[0xAF8 - 0x840];
    Sub_1D8740* sub;
    u8 pad3[0xB00 - 0xAFC];
    s32 nB00;
};

f32 func_001D86F8(f32 x, f32 lim, f32 base);

s32 func_001D8740(Obj_1D8740* self, Obj_1D8740* other)
{
    s32 d = self->nB00 - other->nB00;
    if (d > 0) return 1;
    if (d < 0) return 0;
    d = self->sub->n0C - other->sub->n0C;
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
struct Self_001DAC20 { u8 pad0[0x610]; f32 f610; f32 f614; u8 pad1[0x98]; Slot_001DAC20 slots[4]; };

void func_001DAC20(Self_001DAC20* self)
{
    u32 i;
    Quad_001DAC20 q;
    func_001B8540(self);
    for (i = 0; i < 4; i++) {
        Slot_001DAC20* slot = &self->slots[i];
        if (slot->ptr != 0) {
            f32 f;
            q = *(Quad_001DAC20*)((u8*)slot->ptr + 0x190);
            func_00128018(self, 0, &q, &q);
            f = ((s32)i < 2) ? self->f610 : self->f614;
            func_001B8420(self, &q, f);
        }
    }
}

extern u8 D_0026D5C8[];
extern u8 D_0026DAAC[];
extern u8 D_0026DAC8[];

void func_001922E8(void* a, void* b);
void func_001DDC38(void* sub, void* self);
void func_001DB238(void* self, s32 mode);

void func_001DAE68(u8* self, void* v)
{
    func_001922E8(self, v);
    if (v != 0) {
        u8* a = D_0026D5C8;
        *(void**)(D_0026DAAC) = self + 0x858;
        u8* b = D_0026DAC8;
        *(void**)(a + 0x264) = self + 0xB00;
        *(void**)(a + 0x268) = self + 0xB04;
        *(void**)(b + 0x264) = self + 0xB08;
        *(void**)(b + 0x268) = self + 0xB0C;
        func_001DDC38(*(void**)(self + 0x14), self);
    } else {
        if (*(s32*)(self + 0xB34) == 2) {
            func_001DB238(self, 0);
        }
    }
}

struct Obj_1DAFB8 { void** vtbl; };
struct Arg_1DAFB8 { u8 pad_00[0x34]; Obj_1DAFB8* obj; };
struct Entry_1DAFB8 { s32 flag; void* ptr; u8 pad_08[8]; u8 at10[0x18]; };
struct Self_1DAFB8 {
    u8 pad_000[0x830];
    Arg_1DAFB8* f830;
    f32 f834;
    u8 pad_838[8];
    f32 f840;
    f32 f844;
    u8 pad_848[0x28];
    s32 f870;
    Entry_1DAFB8 f874[1];
};

void func_001DAD28(void* self);
void func_001F3BD8(void* self, void* arg);

typedef void (*VFn7_1DAFB8)(Obj_1DAFB8* self, void* a1, s32 a2, s32 a3, s32 a4, void* a5, void* a6);
typedef f32 (*VFnF_1DAFB8)(Obj_1DAFB8* self);

void func_001DAFB8(Self_1DAFB8* self, Arg_1DAFB8* arg)
{
    self->f830 = arg;
    Obj_1DAFB8* o = arg->obj;
    if (o->vtbl[10]) ((VFn7_1DAFB8)o->vtbl[10])(o, self->pad_000 + 0x100, 0, 0, 0, self->pad_838, 0);
    func_001DAD28(self);
    self->f844 = self->f840;
    self->f834 = ((VFnF_1DAFB8)self->f830->obj->vtbl[8])(self->f830->obj);
    for (s32 i = 0; i < self->f870; i++) {
        Entry_1DAFB8* e = &self->f874[i];
        if (e->flag == 0) {
            s32 loc[4];
            func_001F3BD8(e->ptr, loc);
            Obj_1DAFB8* o2 = self->f830->obj;
            if (o2->vtbl[10]) ((VFn7_1DAFB8)o2->vtbl[10])(o2, loc, 0, 0, 0, 0, e->at10);
        }
    }
}

struct Self_1DB928 { s32 f0; s32 f4; u8 pad_08[0xC]; s32 f14; };

extern s32 D_00275718;
extern s32 D_0027571C;
extern s32 D_00275720;
extern s32 D_00275724;
extern s32 D_00275728;

s32 func_00137480(void* self, s32 n);
s32 func_00137D78(void* self);
s32 func_0018D500(s32 size);

void func_001DB928(s32 a0, Self_1DB928* self)
{
    s32 s2 = a0;
    s32 s3;
    s32 s0;
    if (self->f4 == 1) {
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
