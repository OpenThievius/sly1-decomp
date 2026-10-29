// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Item_158108 { u8 pad0[0xC]; s32 fC; };
struct Owner_158108 { u8 pad0[0x278]; Item_158108* f278; };
struct Obj_158108 {
    void** vtbl;
    u8 pad0[0x1C - 4];
    f32 f1C;
    u8 pad1[0x114 - 0x20];
    s32 f114;
};
typedef void (*VFn_158108)(Obj_158108* self, void* a, s32 z, f32 f);

void* func_0019EA78(s32 a, s32 b);

void func_00158108(void* a0, Owner_158108* a1, f32 f)
{
    Obj_158108* o = (Obj_158108*)func_0019EA78(4, 0);
    if (o != 0) {
        ((VFn_158108*)o->vtbl)[0](o, a0, 0, f);
        o->f1C = 0.75f;
        if (a1->f278 != 0) {
            o->f114 = a1->f278->fC;
        }
    }
}

typedef void (*VFn_001585F8)(void* self);
struct Obj_001585F8 { void** vtbl; };

void func_00182C58(void* a0);

void func_001585F8(Obj_001585F8* a0)
{
    func_00182C58(a0);
    ((VFn_001585F8*)a0->vtbl)[7](a0);
}

struct Blob_158730 { u8 data[0x50]; };
struct Obj_158730 { void** vtbl; };
typedef void (*VFn_158730)(void* self, void* msg);

void func_001F5C0C(void* p, s32 v, s32 n);

void func_00158730(Obj_158730* a0)
{
    Blob_158730 b;
    func_001F5C0C(&b, 0, 0x50);
    ((VFn_158730*)a0->vtbl)[31](a0, &b);
}

struct __attribute__((aligned(16))) Quad_158778 { s32 a, b, c, d; };
struct Msg_158778 {
    s32 a;
    s32 b;
    u8 pad0[8];
    Quad_158778 q1;
    Quad_158778 q2;
    f32 x;
    f32 y;
    u8 pad1[0x50 - 0x38];
};
struct Obj_158778 { void** vtbl; };
typedef void (*VFn_158778)(void* self, void* msg);

void func_00158778(Obj_158778* a0, s32 a1, s32 a2, Quad_158778* a3, Quad_158778* a4, f32 x, f32 y)
{
    Msg_158778 m;
    m.a = a1;
    m.b = a2;
    m.q1 = *a3;
    m.q2 = *a4;
    m.x = x;
    m.y = y;
    ((VFn_158778*)a0->vtbl)[31](a0, &m);
}

void func_001587C0()
{
}

struct Item_158980 {
    void** vtbl;
    u8 pad0[0x80 - 4];
    void* owner;
};
struct Mgr_158980 {
    u8 pad0[0x14];
    void* f14;
    void* f18;
    u8 pad1[0x90 - 0x1C];
    s32 count;
    Item_158980* arr[1];
};
typedef void (*VFn_158980)(void* self);

void func_001830D8(Mgr_158980* a0);
Item_158980* func_00183058(void* a, void* b, void* c);

void func_00158980(Mgr_158980* s2)
{
    func_001830D8(s2);
    for (s32 i = 0; i < s2->count; i++) {
        Item_158980* o = func_00183058(s2->arr[i], s2->f14, s2->f18);
        ((VFn_158980*)o->vtbl)[7](o);
        s2->arr[i] = o;
        o->owner = s2;
    }
}

typedef void (*VFn_158A80)(void* self, void* arg);
struct Item_158A80 { VFn_158A80* vtbl; };
struct Owner_158A80 {
    u8 pad[0x90];
    s32 count;
    Item_158A80* items[1];
};

void func_00158A80(Owner_158A80* self, void* arg)
{
    for (s32 i = 0; i < self->count; i++) {
        Item_158A80* it = self->items[i];
        it->vtbl[31](it, arg);
    }
}

void func_00158D38(void)
{
}

typedef void (*VFn_158F10)(void* self, void* other);
struct Node_158F10 { VFn_158F10* vtbl; };
struct Owner_158F10 {
    u8 pad[0xC0];
    Node_158F10* slotC0;
    Node_158F10* slotC4;
};

void func_00158F10(Owner_158F10* self, s32 kind, Node_158F10* p)
{
    if (kind == 2) {
        if (p == self->slotC0) {
            p->vtbl[28](p, self);
            self->slotC0 = 0;
        } else if (p == self->slotC4) {
            p->vtbl[28](p, self);
            self->slotC4 = 0;
        }
    }
}

struct Link_1596E0 {
    u8 pad0[0x20];
    s32 f20;
    void* f24;
};
struct Obj_1596E0 {
    u8 pad0[0x14];
    Link_1596E0* f14;
    u8 pad1[0x3C - 0x18];
    void* f3C;
    u8 pad2a[0x44 - 0x40];
    Link_1596E0* f44;
    u8 pad2[0x5C - 0x48];
    s32 f5C;
    s32 f60;
};

void func_001B4AD0(Obj_1596E0* self);
Link_1596E0* func_001B4688(void* x);
void func_00159770(Obj_1596E0* self, s32 n);

void func_001596E0(Obj_1596E0* self)
{
    func_001B4AD0(self);
    Link_1596E0* a = func_001B4688(self->f3C);
    self->f44 = a;
    if (a != 0) {
        if (a->f24 == 0) {
            if (self->f14->f24 == self) {
                a->f24 = self;
            }
        }
    }
    s32 lo = 0;
    if (self->f14 != 0) {
        lo = self->f14->f20;
    }
    s32 hi = 0;
    if (self->f44 != 0) {
        hi = self->f44->f20;
    }
    self->f60 = -1;
    self->f5C = (hi < lo) ? lo : hi;
    func_00159770(self, 0);
}

typedef void (*VFn_159AD0)(void* self);
struct Sub_159AD0 { VFn_159AD0* vtbl; };
struct Obj_159AD0 {
    Sub_159AD0* f0;
    f32 f4;
    f32 f8;
};

s32 func_00182FC8(void* obj);
void func_00159C28(Obj_159AD0* self);

void func_00159AD0(Obj_159AD0* self, f32 dt)
{
    if (self->f8 != 0.0f) {
        if (func_00182FC8(self->f0) == 0) {
            func_00159C28(self);
            return;
        }
    }
    f32 old = self->f4;
    self->f4 = old + self->f8 * dt;
    if (self->f4 <= 0.0f && old > 0.0f) {
        Sub_159AD0* s = self->f0;
        s->vtbl[7](s);
        func_00159C28(self);
        return;
    }
    if (self->f4 >= 1.0f && old < 1.0f) {
        func_00159C28(self);
    }
}

u8* func_00159F20(u8* base, s32 n)
{
    return base + (((n * 0x95675) & 0x1FF) * 12 + 0x84);
}

struct Node_15A868 {
    u8 pad[0x18];
    Node_15A868* next;
};

Node_15A868* func_0015A868(Node_15A868* list, Node_15A868* other)
{
    for (Node_15A868* p = list; p != 0; p = p->next) {
        for (Node_15A868* q = other; q != 0; q = q->next) {
            if (p == q) {
                return p;
            }
        }
    }
    return 0;
}

struct __attribute__((packed)) Pk_15AAE0 { u64 v; };

extern Pk_15AAE0 D_00262180;
extern Pk_15AAE0 D_00262188;
extern Pk_15AAE0 D_00262190;
extern Pk_15AAE0 D_00262198;
extern Pk_15AAE0 D_002621A0;
extern Pk_15AAE0 D_002621A8;
extern Pk_15AAE0 D_002621B0;
extern Pk_15AAE0 D_002621B8;
extern Pk_15AAE0 D_002621C0;

struct Obj_15AAE0 {
    u8 pad0[0x14];
    u8* f14;
    u8 pad1[0x554 - 0x18];
    s32 f554;
    u8 pad2[0x610 - 0x558];
    Pk_15AAE0 f610;
    Pk_15AAE0 f618;
    Pk_15AAE0 f620;
    Pk_15AAE0 f628;
    s32 f630;
    u8 pad3[0x63C - 0x634];
    Pk_15AAE0 f63C;
    u8 pad4[0x650 - 0x644];
    Pk_15AAE0 f650;
    Pk_15AAE0 f658;
    Pk_15AAE0 f660;
    u8 pad5[0x670 - 0x668];
    Pk_15AAE0 f670;
    u8 pad6[0x68C - 0x678];
    s32 f68C;
    s32 f690;
};

void func_001B7968(Obj_15AAE0* self);
void func_00152470(u8* a, Obj_15AAE0* b);

void func_0015AAE0(Obj_15AAE0* self)
{
    func_001B7968(self);
    self->f554 = -1;
    self->f610 = D_00262180;
    self->f618 = D_00262188;
    self->f620 = D_00262190;
    self->f628 = D_00262198;
    self->f630 = -1;
    self->f63C = D_002621A0;
    self->f650 = D_002621A8;
    self->f658 = D_002621B0;
    self->f660 = D_002621B8;
    self->f670 = D_002621C0;
    self->f68C = 1;
    self->f690 = -1;
    func_00152470(self->f14 + 0x1C48, self);
}
