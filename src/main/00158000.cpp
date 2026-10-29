// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001BF788(s32 value, s32 unused);
void func_001BFCD8(s32 type, void* data, void* a2, s32 a3, f32 f12, f32 f13,
                   f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001BA130(void);
s32 func_001526D0(void* a, void* b);
void func_00152600(void* a, void* b);

void func_0015AE38(void* self, s32 initialize)
{
    if (*(s32*)((u8*)self + 0x550) != 0) return;
    if (initialize) {
        func_001BF788(*(s32*)((u8*)self + 0x5E4), 0);
    } else {
        func_001BFCD8(0x41, (u8*)self + 0x5E4, self, 0,
                      700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
}

struct __attribute__((packed)) Saved_15AD80 { u64 value; };

void func_0015AD80(void* self)
{
    Saved_15AD80 saved = *(Saved_15AD80*)((u8*)self + 0x5DC);
    func_001BA130();
    *(Saved_15AD80*)((u8*)self + 0x5DC) = saved;
    if (*(s32*)((u8*)self + 0x550) == 0) {
        func_001BFCD8(0x41, (u8*)self + 0x5E4, self, 0,
                      700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    } else {
        if (func_001526D0((u8*)*(void**)((u8*)self + 0x14) + 0x1C48, self))
            func_00152600((u8*)*(void**)((u8*)self + 0x14) + 0x1C48, self);
    }
}

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

struct Obj_158DD8 { u8 pad[0x90]; void* f90; };

void* func_001556E8(void* x);

void* func_00158DD8(void* self, s32 flag)
{
    Obj_158DD8* o = (Obj_158DD8*)self;
    if (flag == 1) {
        o->f90 = func_001556E8(o->f90);
    }
    return o->f90;
}

struct Obj_158E10 { u8 pad[0xAC]; s32 fAC; s32 fB0; s32 fB4; };

void func_00158B00(void* self);

void func_00158E10(void* self)
{
    Obj_158E10* o = (Obj_158E10*)self;
    func_00158B00(self);
    o->fAC = -1;
    o->fB0 = -1;
    o->fB4 = -1;
}

struct Obj_158E48 { u8 pad0[0x14]; void* f14; u8 pad1[0x94]; s32 fAC; s32 fB0; s32 fB4; };
struct Sub_158E48 { u8 pad[0x1D8]; void* f1D8; void* f1DC; void* f1E0; };

struct Rec_158C60;
struct Obj_158C60;
void func_00158C60(Obj_158C60* self);
void* func_00158DD8(void* self, s32 flag);
Rec_158C60* func_0015A418(void* a0, s32 a1, s32 a2, void* a3);
s32 func_001300E8(void* self, s32 kind);

void func_00158E48(Obj_158C60* self)
{
    Obj_158E48* o = (Obj_158E48*)self;
    Sub_158E48* s;
    void* p;

    func_00158C60(self);
    if (o->fAC == -1 && *(s64*)&o->fB0 == -1) {
        return;
    }
    s = (Sub_158E48*)func_00158DD8(self, 1);
    if (o->fAC != -1) {
        s->f1D8 = func_0015A418(o->f14, 0x104, o->fAC, self);
    }
    if (o->fB0 != -1) {
        s->f1DC = func_0015A418(o->f14, 0x104, o->fB0, self);
    }
    if (o->fB4 != -1) {
        p = func_0015A418(o->f14, 0x104, o->fB4, self);
        if (func_001300E8(p, 3) != 0) {
            s->f1E0 = p;
        }
    }
}

struct Obj_158F80 { u8 pad0[0x14]; void* f14; u8 pad1[0xA0]; f32 fB8; };
struct __attribute__((aligned(16))) Quad_158F80 { s32 a, b, c, d; };
struct Body_158F80 { Quad_158F80 q[5]; };
struct Rec_158F80 { void* owner; u8 pad0[0xC]; Body_158F80 body; f32 f60; };

extern f32 D_00261858[];

void* func_001B5EA0(void* p);
void func_00152450(void* p);
void func_00152470(void* list, void* item);
void func_001590A0(void* self, void* body);

void func_00158F80(void* self, void* body)
{
    Obj_158F80* o = (Obj_158F80*)self;
    Rec_158F80* r;
    f32* k;
    s32 done = 0;

    if (0.0f < o->fB8) {
        r = (Rec_158F80*)func_001B5EA0((u8*)o->f14 + 0x1BD0);
        if (r != 0) {
            r->owner = self;
            r->body = *(Body_158F80*)body;
            done = 1;
            k = (f32*)D_00261858;
            r->f60 = k[1] + o->fB8;
            func_00152450((u8*)r + 0x64);
            func_00152470((u8*)o->f14 + 0x1BDC, r);
        }
    }
    if (done == 0) {
        func_001590A0(self, body);
    }
}

struct Obj_159068 { u8 pad[0xA0]; s32 fA0; };

void func_001BE4D8(void* p);

s32 func_00159068(void* self)
{
    Obj_159068* o = (Obj_159068*)self;
    if (o->fA0 == 0) {
        func_001BE4D8((u8*)o + 0xA0);
    }
    return o->fA0;
}

typedef void (*VFn)(void* self);
struct Node_159478 { VFn* vtbl; u8 pad0[0x7C]; void* owner; u8 pad1[0xC]; s32 count; void* items[8]; };
struct Owner_159478 { u8 pad0[0x14]; void* f14; };

void* func_0011E580(s32 a0, void* a1, void* a2, s32 a3, s32 a4);
void func_0018D800(void* dst, void* src, s32 size);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

void func_00159478(void** out, void* self)
{
    Owner_159478* o = (Owner_159478*)self;
    void* arr[32];
    s32 n;
    s32 cnt;
    s32 i;
    Node_159478* s2;

    n = func_0015A4F0(o->f14, 0x202, 0x77, self, 0x20, arr);
    switch (n) {
    case 0:
        *out = 0;
        return;
    case 1:
        *out = arr[0];
        return;
    }
    s2 = (Node_159478*)func_0011E580(0x78, o->f14, self, 0x202, -1);
    cnt = 8;
    if (n < 8) {
        cnt = n;
    }
    s2->count = cnt;
    func_0018D800(s2->items, arr, cnt * 4);
    for (i = 0; i < n; i++) {
        Node_159478* p = (Node_159478*)arr[i];
        if (i < s2->count) {
            p->owner = s2;
        }
        p->vtbl[7](p);
    }
    *out = s2;
}

struct Child_158C60 {
    u8 pad0[0x10];
    s32 kind;
    u8 pad1[0x120 - 0x14];
    void* link120;
    u8 pad2[0x188 - 0x124];
    s32 link188;
};

struct Rec_158C60 {
    u8 pad0[0x18];
    void* f18;
    u8 pad1[0x20 - 0x1c];
    s32 f20;
    u8 pad2[0x34 - 0x24];
    s32 f34;
    u8 pad3[0x7c - 0x38];
    Rec_158C60* f7c;
};

struct Obj_158C60 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x90 - 0x18];
    Child_158C60* child;
    s32 f94;
    s32 f98;
};

Rec_158C60* func_0015A418(void* a0, s32 a1, s32 a2, void* a3);
void func_00158288(Child_158C60* c, Obj_158C60* self);

void func_00158C60(Obj_158C60* self)
{
    Rec_158C60* r;
    Child_158C60* c;

    if (self->f94 == -1 && self->f98 == -1) {
        c = self->child;
        if (c->kind != 3) {
            if (c->link120 != 0) goto tail_c;
            if (c->link188 == -1) goto tail;
        }
    }

    {
        s32 none = -1;

        r = (Rec_158C60*)func_00158DD8(self, 1);
        if (self->f94 != none) {
            r->f7c = func_0015A418(self->f14, 260, self->f94, self);
        }
        if (self->f98 != none) {
            Rec_158C60* q = func_0015A418(self->f14, 260, self->f98, self);
            r->f20 = q->f34;
            r->f7c = (Rec_158C60*)q->f18;
        }
    }

tail:
    c = self->child;
tail_c:
    func_00158288(c, self);
}

struct Fader_159770 {
    u8 pad0[0x2c];
    f32 scale;
    f32 lo;
    f32 hi;
    f32 limit;
    u8 pad1[0x20];
    s32 count;
    s32 mode;
    f32 value;
    f32 level;
    f32 step;
    f32 pos;
    f32 ratio;
};

extern f32 D_0026185C;
f32 func_001EAAE0(f32 a, f32 b);

void func_00159770(Fader_159770* s, s32 mode)
{
    if (s->mode == mode) return;
    if (mode == 1) goto store;
    if (mode < 2) {
        if (mode == 0) goto zero;
        s->mode = mode;
        goto tail;
    }
    if (mode == 2) goto two;
    s->mode = mode;
    goto tail;

zero:
    {
        s32 n = s->count;
        f32 span = (f32)(n << 1) * (1.0f - s->ratio) / s->scale;
        s->pos = (f32)(n - 1) * s->ratio;
        s->step = span;
        f32 r = func_001EAAE0(0.0f, 1.0f);
        if (r < s->limit) {
            s->level = 0.0f;
        } else {
            s->level = func_001EAAE0(s->lo, s->hi);
        }
    }
    goto store;

two:
    {
        s32 last = s->count - 1;
        if ((s32)s->pos == last) {
            s->mode = mode;
            goto tail;
        }
        s->pos = (f32)last;
    }

store:
    s->mode = mode;

tail:
    s->value = D_0026185C;
}

extern f32 D_0026185C;
f32 func_001EAAE0(f32 a, f32 b);
void func_00159770(Fader_159770* s, s32 mode);
void func_001B46E0(void* obj, s32 value);

void func_00159890(Fader_159770* s, f32 dt)
{
    s32 count = s->count;
    if (count < 2) return;
    s32 mode = s->mode;
    if (mode == 1) goto m1;
    if (mode < 2) {
        if (mode == 0) goto m0;
        goto call;
    }
    if (mode == 2) goto m2;
    if (mode == 3) goto m3;
    goto call;

m0:
    if (s->level <= D_0026185C - s->value) mode = 1;
    goto call;

m1:
    {
        f32 step = s->step * dt;
        f32 sum = s->pos + step;
        s->pos = sum;
        if ((f32)count <= sum) {
            f32 back = sum - step;
            s->pos = back;
            mode = ((s32)back == count - 1) ? 2 : 3;
        }
    }
    goto call;

m2:
    if (s->ratio < 1.0f) mode = 3;
    goto call;

m3:
    {
        f32 v = s->pos - s->step * dt;
        s->pos = v;
        if (v <= (f32)count * s->ratio) mode = 0;
    }

call:
    func_00159770(s, mode);
    func_001B46E0((u8*)s + 16, (s32)s->pos);
    func_001B46E0((u8*)s + 64, (s32)s->pos);
}

struct Self_158B30 { u8 pad0[0x90]; void* f90; };
struct Node_158B30 { void** vtbl; u8 pad0[0x20 - 4]; void* f20; };
struct Q_158B30 { u8 pad0[0x10]; s32 f10; };
typedef void (*VFn_158B30)(void* self, void* a);

void* func_0018D5C0(s32 size);
void func_001549C8(void* p);
void func_001F3A40(void* self, void* other);
s32 func_00137CC0(void* other);
void* func_00158DD8(void* self, s32 flag);
void* func_0014D9A8(s32 idx);
void* func_00137BE0(void* other);
void func_00154C80(void* p, void* other);
void func_00154EE0(void* a, void* b, void* c, void* d);

void func_00158B30(Self_158B30* a0, void* a1)
{
    void* p = func_0018D5C0(0x200);
    a0->f90 = p;
    func_001549C8(p);
    func_001F3A40(a0, a1);
    s32 idx = func_00137CC0(a1);
    if (idx != -1) {
        Node_158B30* n = (Node_158B30*)func_00158DD8(a0, 1);
        n->f20 = func_0014D9A8(idx);
        if (((Node_158B30*)n->f20)->vtbl[0] != 0) {
            ((VFn_158B30)((Node_158B30*)n->f20)->vtbl[0])(n->f20, a1);
        }
    }
    Q_158B30* q = (Q_158B30*)a0->f90;
    if (q->f10 == 4) {
        func_00154C80((u8*)q + 0x20, a1);
    }
    void* t = func_00137BE0(a1);
    if (t != 0) {
        void* m = func_00158DD8(a0, 1);
        func_00154EE0((u8*)m + 0x130, t, a0, a1);
    }
}

struct Counter_158C28 { s32 f0; };
struct Self_158C28 { u8 pad0[0x90]; Counter_158C28* f90; };

void func_001830D8(void* self);

void func_00158C28(Self_158C28* a0)
{
    func_001830D8(a0);
    a0->f90->f0 += 1;
}

struct Self_159A00 {
    u8 pad0[0x60];
    s32 f60;
    f32 f64;
    f32 f68;
    f32 f6C;
    f32 f70;
    f32 f74;
};

void func_00159770(void* self, s32 mode);
void func_001B46E0(void* p, s32 v);

void func_00159A00(Self_159A00* a0, f32 f12)
{
    a0->f74 = f12;
    if (1.0f <= f12) {
        func_00159770(a0, 2);
    } else {
        a0->f60 = -1;
        func_00159770(a0, 0);
    }
    func_001B46E0((u8*)a0 + 0x10, (s32)a0->f70);
    func_001B46E0((u8*)a0 + 0x40, (s32)a0->f70);
}

struct Actor_15AEB0 {
    u8 pad0[0x3CC];
    f32 f3cc;
    u8 pad1[0x550 - 0x3D0];
    s32 mode_550;
    u8 pad2[0x560 - 0x554];
    s32 x560;
    u8 pad3[0x63C - 0x564];
    f32 f63c;
    f32 f640;
    u8 pad4[0x64C - 0x644];
    f32 f64c;
    u8 pad5[0x670 - 0x650];
    f32 f670;
    f32 f674;
    u8 pad6[0x680 - 0x678];
    f32 f680;
    u8 pad7[0x688 - 0x684];
    f32 f688;
};

extern u8 D_002621E0[];

void func_00124DF8(void* self, s32 n, void* p);
f32 func_001EAAE0(f32 a, f32 b);
void func_0015B7B8(Actor_15AEB0* self, s32 x);
void func_00124A48(void* self);

void func_0015AEB0(Actor_15AEB0* self)
{
    func_00124DF8(self, 2, D_002621E0);
    if (self->mode_550 == 1) {
        f32 t = func_001EAAE0(self->f63c, self->f640);
        self->f688 = D_00261858[1] + t;
        t = func_001EAAE0(self->f670, self->f674);
        self->f680 = D_00261858[1] + t;
    }
    func_0015B7B8(self, self->x560);
    func_00124A48(self);
    self->f64c = self->f3cc + self->f3cc;
}

struct Owner_159BB0 { u8 pad[0x294]; s32 flag294; };
struct Node_159BB0 { Owner_159BB0* owner; };

extern u8* D_00275710;

void* func_001B5EE0(void* where);
void func_00152470(void* where, Node_159BB0* node);

Node_159BB0* func_00159BB0(Owner_159BB0* self)
{
    Node_159BB0* node = (Node_159BB0*)func_001B5EE0(D_00275710 + 0x1C18);
    node->owner = self;
    if (self->flag294 != 0) {
        func_00152470(D_00275710 + 0x1C30, node);
    } else {
        func_00152470(D_00275710 + 0x1C24, node);
    }
    return node;
}

struct Owner_159C28 { u8 pad[0x294]; s32 flag294; s32 flag298; };
struct Node_159C28 { Owner_159C28* owner; };

extern u8* D_00275710;

void func_00152600(void* where, Node_159C28* node);
void func_001B5F28(void* where, Node_159C28* node);

void func_00159C28(Node_159C28* node)
{
    if (node->owner->flag294 != 0) {
        func_00152600(D_00275710 + 0x1C30, node);
    } else {
        func_00152600(D_00275710 + 0x1C24, node);
    }
    node->owner->flag298 = 0;
    func_001B5F28(D_00275710 + 0x1C18, node);
}

typedef void (*VFn_158A10)(void* self);
struct Item_158A10 { VFn_158A10* vtbl; };
struct Owner_158A10 {
    u8 pad[0x90];
    s32 count;
    Item_158A10* items[1];
};

void func_00158A10(Owner_158A10* self)
{
    for (s32 i = 0; i < self->count; i++) {
        Item_158A10* it = self->items[i];
        VFn_158A10 fn = it->vtbl[19];
        if (fn != 0) {
            fn(it);
        }
    }
}

struct Obj_158B00 { u8 pad[0x94]; s32 f94; s32 f98; };

void func_001F39F8(void* self);

void func_00158B00(void* self)
{
    Obj_158B00* o = (Obj_158B00*)self;
    func_001F39F8(self);
    o->f94 = -1;
    o->f98 = -1;
}

struct Obj_15A960 { u8 pad0[0x2EC]; f32 f2EC; f32 f2F0; };

extern f32 D_00261860;
void func_00124FC0(void* self);
f32 func_001EA4B8(void* p, s32 zero, f32 a, f32 b, f32 c);

void func_0015A960(Obj_15A960* self)
{
    func_00124FC0(self);
    self->f2EC = func_001EA4B8((u8*)self + 0x2E0, 0, self->f2EC, self->f2F0, D_00261860);
}

struct __attribute__((aligned(16))) Quad_15A9A8 { s32 w[4]; };
struct Obj_15A9A8 { u8 pad0[0x2EC]; f32 f2EC; };
struct Frame_15A9A8 { Quad_15A9A8 q0; u8 pad1[0x30]; Quad_15A9A8 m40[4]; u8 pad2[0x10]; Quad_15A9A8 m90[4]; };

void func_0018A008(s32 zero, void* out, f32 v);
void func_00125B70(void* obj, void* c, void* out);
void func_00188668(Quad_15A9A8* out, void* b, Quad_15A9A8* in);
void func_001261C0(void* obj, void* b, void* m);

void func_0015A9A8(Obj_15A9A8* self, void* arg1, void* arg2)
{
    Frame_15A9A8 f;
    func_0018A008(0, &f.q0, self->f2EC);
    func_00125B70(self, arg2, f.m40);
    func_00188668(f.m90, f.m40, &f.q0);
    f.m40[0] = f.m90[0];
    f.m40[1] = f.m90[1];
    f.m40[2] = f.m90[2];
    f.m40[3] = f.m90[3];
    func_001261C0(self, arg1, f.m40);
}

extern u8 D_002622A8[];

struct Frame_159CA0 { u8 buf[0x2C0]; s32 value; };

void func_00168770(void* buf, s32* value, s32 flag);
void func_00152B38(void* self);
void func_001EE7D0(void* self, s32 n, void* buf, s32 flag);
void func_00152D70(void* self);

void func_00159CA0(u8* a0)
{
    Frame_159CA0 f;
    f.value = *(s32*)(a0 + 0x60);
    func_00168770(&f, &f.value, 0);
    u8* s = D_002622A8;
    func_00152B38(s);
    func_001EE7D0(s, 0x2C, &f, 0);
    func_00152D70(s);
}

extern u8* D_00275710;
extern f32 D_0026185C;

struct Ctx_159ED0 { u8 pad0[0x54]; f32 f54; u8 pad58[4]; s32 f5C; };

void func_00152470(void* list, void* item);

void func_00159ED0(Ctx_159ED0* a0)
{
    if (a0->f5C == 0) {
        a0->f5C = 1;
        a0->f54 = D_0026185C;
        func_00152470(D_00275710 + 0x1CD8, a0);
    }
}
