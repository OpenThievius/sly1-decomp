// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c73.h"
#include "t219c.h"
#include "t21e3.h"
#include "c40.h"
#include "c60.h"
#include "c6c.h"

struct Item_158108 { u8 pad0[0xC]; s32 fC; };
struct Owner_158108 { u8 pad0[0x278]; Item_158108* f278; };
typedef void (*VFn_158108)(T219C* self, void* a, s32 z, f32 f);

void* func_0019EA78(s32 a, s32 b);

void func_00158108(void* a0, Owner_158108* a1, f32 f)
{
    T219C* o = (T219C*)func_0019EA78(4, 0);
    if (o != 0) {
        ((VFn_158108)o->vt->m00)(o, a0, 0, f);
        o->life = 0.75f;
        if (a1->f278 != 0) {
            o->p114 = (void*)a1->f278->fC;
        }
    }
}

void func_00182C58(void* a0);

void func_001585F8(C77* self)
{
    func_00182C58(self);
    self->desc->m03(self);
}

struct Blob_158730 { u8 data[0x50]; };

void func_001F5C0C(void* p, s32 v, s32 n);

void func_00158730(C77* a0)
{
    Blob_158730 b;
    func_001F5C0C(&b, 0, 0x50);
    a0->desc->m1B(a0, &b);
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

void func_00158778(C77* a0, s32 a1, s32 a2, Quad_158778* a3, Quad_158778* a4, f32 x, f32 y)
{
    Msg_158778 m;
    m.a = a1;
    m.b = a2;
    m.q1 = *a3;
    m.q2 = *a4;
    m.x = x;
    m.y = y;
    a0->desc->m1B(a0, &m);
}

void func_001587C0()
{
}

void func_001830D8(void* self);
C77* func_00183058(void* a, void* b, void* c);

void func_00158980(C78* self)
{
    func_001830D8(self);
    for (s32 i = 0; i < self->count; i++) {
        C77* o = func_00183058(self->members[i], self->world, self->parent);
        o->desc->m03(o);
        self->members[i] = o;
        o->group = self;
    }
}

void func_00158A80(C78* self, void* message)
{
    for (s32 i = 0; i < self->count; i++) {
        C77* it = self->members[i];
        it->desc->m1B(it, message);
    }
}

void func_00158D38(void)
{
}

void func_00158F10(C7A* self, s32 kind, C01* other)
{
    if (kind == 2) {
        if (other == self->heldC0) {
            other->desc->m18(other, self);
            self->heldC0 = 0;
        } else if (other == self->heldC4) {
            other->desc->m18(other, self);
            self->heldC4 = 0;
        }
    }
}

void func_001B4AD0(T21E3* self);
T21E3_Rec* func_001B4688(s32 key);
void func_00159770(T21E3_438* self, s32 mode);

void func_001596E0(T21E3_438* self)
{
    func_001B4AD0(self);
    T21E3_Rec* a = func_001B4688(self->id2);
    self->cur2.rec = a;
    if (a != 0) {
        if (a->owner == 0) {
            if (self->cur.rec->owner == self) {
                a->owner = self;
            }
        }
    }
    s32 lo = 0;
    if (self->cur.rec != 0) {
        lo = self->cur.rec->count;
    }
    s32 hi = 0;
    if (self->cur2.rec != 0) {
        hi = self->cur2.rec->count;
    }
    self->mode = -1;
    self->count = (hi < lo) ? lo : hi;
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

C01* func_0015A868(C01* list, C01* other)
{
    for (C01* p = list; p != 0; p = p->parent) {
        for (C01* q = other; q != 0; q = q->parent) {
            if (p == q) {
                return p;
            }
        }
    }
    return 0;
}

Pk40 D_00262180 = { 0x4348000043480000ULL };
Pk40 D_00262188 = { 0x42C8000042C80000ULL };
Pk40 D_00262190 = { 0x4448000043FA0000ULL };
Pk40 D_00262198 = { 0x43960000C3960000ULL };
Pk40 D_002621A0 = { 0x4270000041700000ULL };
Pk40 D_002621A8 = { 0x42F0000041F00000ULL };
Pk40 D_002621B0 = { 0x3E4CCCCD3D4CCCCDULL };
Pk40 D_002621B8 = { 0x3F4CCCCD3DCCCCCDULL };
Pk40 D_002621C0 = { 0x4170000040A00000ULL };

void func_001B7968(C03* self);
void func_00152470(List01* a, C40* b);

void func_0015AAE0(C40* self)
{
    func_001B7968(self);
    self->state = -1;
    self->p610.pk = D_00262180;
    self->p618.pk = D_00262188;
    self->p620.pk = D_00262190;
    self->p628.pk = D_00262198;
    self->f630 = -1;
    self->p63C.pk = D_002621A0;
    self->p650.pk = D_002621A8;
    self->p658.pk = D_002621B0;
    self->p660.pk = D_002621B8;
    self->p670.pk = D_002621C0;
    self->f68C = 1;
    self->f690 = -1;
    func_00152470(&self->world->list1C48, self);
}

void* func_001556E8(void* x);

Rec79* func_00158DD8(C79* self, s32 own)
{
    if (own == 1) {
        self->rec = (Rec79*)func_001556E8(self->rec);
    }
    return self->rec;
}

void func_00158E10(C7A* self)
{
    func_00158B00(self);
    self->idAC = -1;
    self->idB0 = -1;
    self->idB4 = -1;
}

struct Rec_158C60;
Rec_158C60* func_0015A418(void* a0, s32 a1, s32 a2, void* a3);
s32 func_001300E8(void* self, s32 kind);

void func_00158E48(C7A* self)
{
    Rec79* s;
    void* p;

    func_00158C60(self);
    if (self->idAC == -1 && *(s64*)&self->idB0 == -1) {
        return;
    }
    s = func_00158DD8(self, 1);
    if (self->idAC != -1) {
        s->found[0] = func_0015A418(self->world, 0x104, self->idAC, self);
    }
    if (self->idB0 != -1) {
        s->found[1] = func_0015A418(self->world, 0x104, self->idB0, self);
    }
    if (self->idB4 != -1) {
        p = func_0015A418(self->world, 0x104, self->idB4, self);
        if (func_001300E8(p, 3) != 0) {
            s->found[2] = p;
        }
    }
}

struct __attribute__((aligned(16))) Quad_158F80 { s32 a, b, c, d; };
struct Body_158F80 { Quad_158F80 q[5]; };
struct Rec_158F80 { void* owner; u8 pad0[0xC]; Body_158F80 body; f32 f60; };

extern f32 D_00261858[];

void* func_001B5EA0(void* p);
void func_00152450(void* p);
void func_00152470(void* list, void* item);
void func_001590A0(void* self, void* body);

void func_00158F80(C7A* self, void* message)
{
    Rec_158F80* r;
    f32* k;
    s32 done = 0;

    if (0.0f < self->delay) {
        r = (Rec_158F80*)func_001B5EA0(&self->world->pool1BD0);
        if (r != 0) {
            r->owner = self;
            r->body = *(Body_158F80*)message;
            done = 1;
            k = (f32*)D_00261858;
            r->f60 = k[1] + self->delay;
            func_00152450((u8*)r + 0x64);
            func_00152470(&self->world->list1BDC, r);
        }
    }
    if (done == 0) {
        func_001590A0(self, message);
    }
}

void func_001BE4D8(void* p);

s32 func_00159068(void* self)
{
    C7A* o = (C7A*)self;
    if (o->fA0 == 0) {
        func_001BE4D8(&o->fA0);
    }
    return o->fA0;
}

typedef void (*VFn)(void* self);
struct Node_159478 { VFn* vtbl; u8 pad0[0x7C]; void* owner; u8 pad1[0xC]; s32 count; void* items[8]; };

void* func_0011E580(s32 a0, void* a1, void* a2, s32 a3, s32 a4);
void func_0018D800(void* dst, void* src, s32 size);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

void func_00159478(void** out, void* self)
{
    C01* o = (C01*)self;
    void* arr[32];
    s32 n;
    s32 cnt;
    s32 i;
    Node_159478* s2;

    n = func_0015A4F0(o->world, 0x202, 0x77, self, 0x20, arr);
    switch (n) {
    case 0:
        *out = 0;
        return;
    case 1:
        *out = arr[0];
        return;
    }
    s2 = (Node_159478*)func_0011E580(0x78, o->world, self, 0x202, -1);
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

Rec_158C60* func_0015A418(void* a0, s32 a1, s32 a2, void* a3);
void func_00158288(Rec79* rec, C79* self);

void func_00158C60(C79* self)
{
    Rec79* r;
    Rec79* c;

    if (self->id94 == -1 && self->id98 == -1) {
        c = self->rec;
        if (c->kind != 3) {
            if (c->link120 != 0) goto tail_c;
            if (c->link188 == -1) goto tail;
        }
    }

    {
        s32 none = -1;

        r = func_00158DD8(self, 1);
        if (self->id94 != none) {
            r->target = func_0015A418(self->world, 260, self->id94, self);
        }
        if (self->id98 != none) {
            Rec_158C60* q = func_0015A418(self->world, 260, self->id98, self);
            r->value20 = q->f34;
            r->target = q->f18;
        }
    }

tail:
    c = self->rec;
tail_c:
    func_00158288(c, self);
}

extern f32 D_0026185C;
f32 func_001EAAE0(f32 a, f32 b);

void func_00159770(T21E3_438* s, s32 mode)
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
    s->stamp2 = D_0026185C;
}

extern f32 D_0026185C;
f32 func_001EAAE0(f32 a, f32 b);
void func_001B46E0(T21E3_Cursor* cur, s32 idx);

void func_00159890(T21E3_438* s, f32 dt)
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
    if (s->level <= D_0026185C - s->stamp2) mode = 1;
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
    func_001B46E0(&s->cur, (s32)s->pos);
    func_001B46E0(&s->cur2, (s32)s->pos);
}


void* func_0018D5C0(s32 size);
void func_001549C8(void* p);
s32 func_00137CC0(void* other);
T2176* func_0014D9A8(s32 kind);
void* func_00137BE0(void* other);
void func_00154C80(void* p, void* other);
void func_00154EE0(void* a, void* b, void* c, void* d);

void func_00158B30(C79* self, void* stream)
{
    Rec79* p = (Rec79*)func_0018D5C0(0x200);
    self->rec = p;
    func_001549C8(p);
    func_001F3A40(self, stream);
    s32 idx = func_00137CC0(stream);
    if (idx != -1) {
        Rec79* n = func_00158DD8(self, 1);
        n->curve20 = func_0014D9A8(idx);
        if (n->curve20->vt->m00 != 0) {
            n->curve20->vt->m00(n->curve20, stream);
        }
    }
    Rec79* q = self->rec;
    if (q->kind == 4) {
        func_00154C80(&q->curve20, stream);
    }
    void* t = func_00137BE0(stream);
    if (t != 0) {
        Rec79* m = func_00158DD8(self, 1);
        func_00154EE0((u8*)m + 0x130, t, self, stream);
    }
}

void func_00158C28(C79* self)
{
    func_001830D8(self);
    self->rec->uses += 1;
}


void func_00159A00(T21E3_438* a0, f32 f12)
{
    a0->ratio = f12;
    if (1.0f <= f12) {
        func_00159770(a0, 2);
    } else {
        a0->mode = -1;
        func_00159770(a0, 0);
    }
    func_001B46E0(&a0->cur, (s32)a0->pos);
    func_001B46E0(&a0->cur2, (s32)a0->pos);
}



s32 D_002621E0[6] = { 4, 0x258, 0x5D8, 2, 0x25A, 0x67C };

void func_00124DF8(void* self, s32 n, void* p);
f32 func_001EAAE0(f32 a, f32 b);
void func_0015B7B8(C40* self, s32 x);
void func_00124A48(void* self);

void func_0015AEB0(C40* self)
{
    func_00124DF8(self, 2, D_002621E0);
    if (self->mode == 1) {
        f32 t = func_001EAAE0(self->p63C.a, self->p63C.b);
        self->f688 = D_00261858[1] + t;
        t = func_001EAAE0(self->p670.a, self->p670.b);
        self->f680 = D_00261858[1] + t;
    }
    func_0015B7B8(self, self->f560);
    func_00124A48(self);
    self->f64C = self->radius3CC + self->radius3CC;
}

struct Node_159BB0 { C02* owner; };

extern u8* D_00275710;

void* func_001B5EE0(void* where);
void func_00152470(void* where, Node_159BB0* node);

Node_159BB0* func_00159BB0(C02* self)
{
    Node_159BB0* node = (Node_159BB0*)func_001B5EE0(D_00275710 + 0x1C18);
    node->owner = self;
    if (self->f294 != 0) {
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

void func_00158A10(C78* self)
{
    for (s32 i = 0; i < self->count; i++) {
        C77* it = self->members[i];
        void (*fn)(C01*) = it->desc->m0F;
        if (fn != 0) {
            fn(it);
        }
    }
}

void func_00158B00(C79* self)
{
    func_001F39F8(self);
    self->id94 = -1;
    self->id98 = -1;
}

extern f32 D_00261860;
void func_00124FC0(void* self);
f32 func_001EA4B8(void* p, s32 zero, f32 a, f32 b, f32 c);

void func_0015A960(C60* self)
{
    func_00124FC0(self);
    self->f2EC = func_001EA4B8(self->v, 0, self->f2EC, self->f2F0, D_00261860);
}

struct __attribute__((aligned(16))) Quad_15A9A8 { s32 w[4]; };
struct Frame_15A9A8 { Quad_15A9A8 q0; u8 pad1[0x30]; Quad_15A9A8 m40[4]; u8 pad2[0x10]; Quad_15A9A8 m90[4]; };

void func_0018A008(s32 zero, void* out, f32 v);
void func_00125B70(void* obj, void* c, void* out);
void func_00188668(Quad_15A9A8* out, void* b, Quad_15A9A8* in);
void func_001261C0(void* obj, void* b, void* m);

void func_0015A9A8(C60* self, void* arg1, void* arg2)
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

s32 func_0015A198(void*,s32,s32,void*,s32,void*);
Rec_158C60* func_0015A418(void* self,s32 flags,s32 kind,void* arg)
{
    s32 out=0;
    func_0015A198(self,flags|0x200,kind,arg,1,&out);
    return (Rec_158C60*)out;
}

s32 func_0015A448(void* self,s32 kind,void* arg)
{
    s32 out=0;
    func_0015A198(self,0x204,kind,arg,1,&out);
    return out;
}

s32 func_0015A480(void* self,s32 kind,void* arg)
{
    s32 out=0;
    func_0015A198(self,0x201,kind,arg,1,&out);
    return out;
}

s32 func_0015A838(void* self,s32 flags,s32 kind,void* arg)
{
    s32 out=0;
    func_0015A4F0(self,flags|0x200,kind,arg,1,&out);
    return out;
}

void func_001289C0(void*,void*);
s32 func_001E4C48(void*,void*,void*,void*,void*);
void func_0015A918(C60* self,void* other)
{
    func_001289C0(self,other);
    func_001E4C48(other,&self->out2D0,&self->out2D4,&self->out2D8,&self->out2DC);
}

T21E3_Cursor* func_001B4B48(T21E3* self, const T21E3_Rec* key);

T21E3_Cursor* func_00159A80(T21E3_438* self, const T21E3_Rec* key)
{
    T21E3_Cursor* p = func_001B4B48(self, key);
    if (p == 0) {
        p = &self->cur2;
        if ((key->key ^ self->id2) != 0) {
            p = 0;
        }
    }
    return p;
}

void func_00158198(void*,void*,void*,f32,f32,f32,f32,void*);

void func_00158D40(C79* self, void* a, void* b, f32 x, f32 y, f32 z, f32 w)
{
    u8* p = (u8*)func_00158DD8(self, 1);
    func_00158198(p+16,a,b,x,y,z,w,self);
}

struct __attribute__((aligned(16))) Quad_15B720 { s32 a, b, c, d; };
struct Rec_15B720 {
    u8 pad0[0x8];
    f32 f8;
    s32 fC;
    u8 pad1[0x20 - 0x10];
    Quad_15B720 f20;
    Quad_15B720 f30;
};
struct __attribute__((aligned(16))) Local_15B720 {
    s32 f0;
    u8 pad0[0x10 - 0x4];
    Quad_15B720 f10;
    Quad_15B720 f20;
    u8 pad1[0x50 - 0x30];
};

void func_0015B7B8(void* self, s32 x);
void func_001BC0E0(void* a0, f32 x, void* a1, void* a2);

s32 func_0015B720(C40* self, Rec_15B720* r)
{
    if (self->state != 1) {
        func_0015B7B8(self, 1);
        if ((r->fC & 8) != 0) {
            func_001BC0E0(self, r->f8, &r->f20, &r->f30);
        }
        if (self->group != 0) {
            Local_15B720 loc;
            loc.f0 = 6;
            loc.f20 = r->f20;
            loc.f10 = r->f30;
            self->group->desc->m1B(self->group, &loc);
        }
    }
    return 1;
}

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void func_001BA130();
s32 func_001526D0(void* sub, C40* self);
void func_00152600(void* data, C40* self);
void func_001BFCD8(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);

void func_0015AD80(C40* self)
{
    Pk40 tmp;
    tmp = self->f5DC;
    func_001BA130();
    self->f5DC = tmp;
    if (self->mode == 0) {
        func_001BFCD8(700.0f, 10.0f, 1.0f, 0.0f, 0x41, &self->handle, self, 0, 0.0f, 0, 0);
    } else {
        if (func_001526D0(&self->world->list1C48, self) != 0) {
            func_00152600(&self->world->list1C48, self);
        }
    }
}

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void func_001BF788(void* self, s32 n);
void func_001BFCD8(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);

void func_0015AE38(C40* self, s32 flag)
{
    if (self->mode == 0) {
        if (flag != 0) {
            func_001BF788(self->handle, 0);
        } else {
            func_001BFCD8(700.0f, 10.0f, 1.0f, 0.0f, 0x41, &self->handle, self, 0, 0.0f, 0, 0);
        }
    }
}

struct Col_159D00 { u8 c[4]; };
struct __attribute__((aligned(4))) Out_159D00 { u8 c[4]; };
struct Req_159D00 { void* fn; f32 f; s32 mode; u8 pad[0x54]; Out_159D00 col; u8 pad2[0x1C]; };
struct Obj_159D00 {
    u8 pad0[0x3C];
    Col_159D00 c0, c1, c2;
    f32 f48, f4C, f50, f54;
    s32 m58, m5C;
};
extern s32 D_00275BC4;
extern s32 D_00270458;
extern f32 D_0026185C;
void func_00152600(u8* a, Obj_159D00* b);
void func_00159CA0(Obj_159D00* o);
void func_0019D410(Req_159D00* r);

void func_00159D00(Obj_159D00* self)
{
    if (D_00275BC4 != 3) return;
    s32 g = D_00270458;
    if (g == 1) return;
    if (g == 2) return;
    Out_159D00 out; Col_159D00 a, b;
    f32 t = D_0026185C - self->f54;
    f32 d;
    if (t < self->f48) {
        a = self->c0; b = self->c1;
        d = self->f48;
    } else {
        t -= self->f48;
        if (t < self->f4C) {
            a = self->c1; b = self->c1;
            d = self->f4C;
        } else {
            t -= self->f4C;
            if (!(t < self->f50)) {
                u8* p = *(u8**)&D_00275710 + 0x1CD8;
                self->m5C = 0;
                func_00152600(p, self);
                return;
            }
            a = self->c1; b = self->c2;
            d = self->f50;
        }
    }
    f32 r = t / d;
    for (s32 i = 0; i < 4; i++)
        out.c[i] = (s32)((1.0f - r) * a.c[i] + r * b.c[i]);
    Req_159D00 q;
    q.f = -1.0f;
    q.fn = (void*)(void (*)(Obj_159D00*))func_00159CA0;
    q.col = out;
    switch (self->m58) {
    case 0: q.mode = 1; break;
    case 1: q.mode = 0x10; break;
    }
    func_0019D410(&q);
}

struct Entry_158198 {
    s32 a;
    s32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 f;
    u8 pad0[0x10];
};

struct Emitter_158198 {
    s32 kind;
    u8 pad0[0xC];
    s32 count;
    Entry_158198* entries;
};

void* func_0018D5C0(s32 bytes);

void func_00158198(Emitter_158198* self, s32 a1, s32 a2, f32 f12, f32 f13, f32 f14, f32 f15)
{
    self->kind = 3;
    if (self->entries == 0) {
        self->entries = (Entry_158198*)func_0018D5C0(0x500);
    }
    if (self->count < 0x20) {
        s32 n = self->count;
        Entry_158198* e = self->entries + n;
        self->count = n + 1;
        e->a = a1;
        e->b = a2;
        e->c = f13;
        if (0.0f <= f15) {
            e->d = f15;
        } else {
            e->d = f13;
        }
        e->e = f12;
        if (0.0f <= f14) {
            e->f = f14;
        } else {
            e->f = f12;
        }
    }
}

typedef void (*Fn1_1587C8)(void* self, void* arg);

struct Link_1587C8 { void* item; u8 pad0[4]; Link_1587C8* next; };
struct Node_1587C8 { void** vtbl; u8 pad0[0x2CC]; Link_1587C8* list; };

s32 func_00137D10(void* src);
s32 func_001300E8(void* node, s32 kind);
void* func_0011E580(s32 a0, void* a1, void* a2, s32 a3, s32 a4);

void func_001587C8(C78* self, void* src)
{
    void* arr[8];
    s32 total;
    s32 i;
    func_001F3A40(self, src);
    total = func_00137D10(src);
    for (i = 0; i < total; i++) {
        s32 r1 = func_00137D10(src);
        s32 r2 = func_00137D10(src);
        s32 r3 = func_00137D10(src);
        Node_1587C8* obj = (Node_1587C8*)func_0011E580(r1, self->world, self->parent, r2, r3);
        s32 n;
        ((Fn1_1587C8)obj->vtbl[14])(obj, src);
        if (((u32*)obj->vtbl)[2] & 0x100) {
            Link_1587C8* p = obj->list;
            n = 0;
            while (p != 0) {
                if ((u32)n < 8) {
                    arr[n] = p->item;
                    n++;
                }
                p = p->next;
            }
        } else {
            arr[0] = obj;
            n = 1;
        }
        if (n > 0) {
            void** dst = (void**)self->members;
            void** s = arr;
            s32 j;
            for (j = n; j != 0; j--, s++) {
                C77* o = (C77*)*s;
                if (func_001300E8(o, 0x78) != 0 || func_001300E8(o, 0x7A) != 0) {
                    o->desc->m03(o);
                    u32 c = self->count;
                    if (c < 8) {
                        *(void**)((u8*)dst + (c << 2)) = o;
                        self->count = c + 1;
                        o->group = self;
                    }
                }
            }
        }
    }
}

struct Node_15A4B8 { Node_15A4B8* next; s32 value; };

extern u8 D_00247448[];

s32 func_0015A4B8(s32 index, s32 value)
{
    Node_15A4B8* p = ((Node_15A4B8**)D_00247448)[index];
    while (p != 0) {
        if (p->value != value) {
            p = p->next;
        } else {
            return 1;
        }
    }
    return 0;
}

s32 func_00182FC8(C02* o);

void func_00159F48(C02* self, s32 mode, s32 a2, s32 a3, C02* a4, s32 cap,
                   s32* count, C02** arr, s32* lvlp)
{
    C02* a0;
    C02* prev;
    switch (mode) {
    case 2:
        if (self->alias != 0 && a3 == 0) return;
        if (self->parent == a4) goto add;
        return;
    case 1:
        if (self->alias != 0 && a3 == 0) return;
        a0 = (C02*)self->parent;
        if (a0 == 0) return;
        do {
            u64 lvl = a0->mark;
            if (lvl != 0) {
                if (lvl == 1) goto add;
                return;
            }
            if (a0->alias != 0) return;
            a0 = (C02*)a0->parent;
        } while (a0 != 0);
        return;
    case 3:
        if (self->desc->flags & 1) {
            if (self->flags & ((u64)0xF000 << 30)) goto add;
        }
        return;
    case 4:
        prev = 0;
        a0 = self;
        if ((self->desc->flags & 1) == 0) a0 = (C02*)self->parent;
        while (a0 != 0) {
            u64 f = a0->flags;
            if (f & ((u64)0xF000 << 30)) {
                s32 lvl = (s32)(a0->flags >> 42) & 0xF;
                u32 cur = *lvlp;
                if (!(cur < lvl)) {
                    if (!(lvl < cur)) goto add;
                    *lvlp = lvl;
                    *count = 0;
                    *arr = 0;
                    goto add;
                }
            }
            if (a0 == prev) return;
            if (a0->alias != 0 && (a0 != self || a3 == 0)) {
                s32 want = -1;
                if (a4 != 0) {
                    for (C02* v = a4; v; v = (C02*)v->parent) {
                        if (v->alias != 0) { want = v->alias->id; break; }
                    }
                }
                if (a0->alias->id != want) return;
                prev = (C02*)a0->parent;
            }
            a0 = (C02*)a0->parent;
        }
        if (*lvlp != 0x7FFFFFFF) return;
        goto add;
    case 5:
    add:
        if (a2 == 0 && func_00182FC8(self) == 0) return;
        if (*count < cap) arr[*count] = self;
        (*count)++;
        return;
    default:
        return;
    }
}

typedef int V128_15B128 __attribute__((mode(TI)));

extern f32 D_00261858[];

void func_001B93F8(C40* self);
void func_0015B7B8(C40* self, s32 mode);
s32 func_0015BEF0(C40* self);
s32 func_0015BD48(C40* self, V128_15B128* out);
void func_0015BC78(C40* self);
s32 func_0015C0A0(C40* self);
s32 func_0015BFC0(C40* self);
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_0015B128(C40* self)
{
    func_001B93F8(self);
    if (self->f55C <= D_00261858[1]) {
        s32 a1 = self->state;
        switch (a1) {
        case 0:
        case 3:
            func_0015B7B8(self, -1);
            a1 = 0;
            break;
        case 1:
            a1 = 2;
            break;
        case 5:
            a1 = func_0015BEF0(self);
            break;
        case 6:
            a1 = 0;
            break;
        default:
            break;
        }
        func_0015B7B8(self, a1);
    }
    s32 st = self->state;
    switch (st) {
    case 0:
    case 3:
    case 5: {
        s32 sub = self->mode;
        switch (sub) {
        case 0:
            if (self->handle == 0) {
                func_001BFCD8(0x41, &self->handle, (s32)self, 0, 700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            self->index = (self->index + 1) % self->count;
            break;
        case 1:
            if (st == 0) {
                if (self->f688 <= D_00261858[1]) {
                    V128_15B128 tmp;
                    if (func_0015BD48(self, &tmp)) {
                        *(V128_15B128*)&self->v5F0 = tmp;
                        func_0015B7B8(self, 5);
                    } else {
                        self->f688 = D_00261858[1] + func_001EAAE0(self->p63C.a, self->p63C.b);
                    }
                }
            }
            if (self->f648 <= D_00261858[1]) {
                s32 n = self->count;
                if (n >= 2) {
                    s32 v = self->index + self->f68C;
                    self->index = v;
                    if (v >= n) {
                        self->index = n - 2;
                        self->f68C = -1;
                    } else if (v < 0) {
                        self->index = 1;
                        self->f68C = 1;
                    }
                    self->f648 = D_00261858[1] + self->f644;
                }
            }
            break;
        }
        if (0.15f < D_00261858[1] - self->f558) {
            ContactRow03* n = self->contacts->head;
            if (n != 0) {
                for (; n != 0; n = n->next) {
                    if (n->head != 0) {
                        self->f55C = D_00261858[1];
                        break;
                    }
                }
            }
        }
        break;
    }
    case 6:
        if (func_0015C0A0(self) || func_0015BFC0(self)) {
            func_0015B7B8(self, 0);
        } else if (self->f668 <= D_00261858[1]) {
            s32 idx = (self->index + 1) % self->count5AC;
            self->index = idx;
            self->f668 = D_00261858[1];
            f32 x, y;
            if (idx == 0) {
                x = self->p660.a;
                y = self->p660.b;
            } else {
                x = self->p658.a;
                y = self->p658.b;
            }
            self->f668 += func_001EAAE0(x, y);
        }
        break;
    }
    if (self->mode == 1) {
        s32 s = self->state;
        if (s == 0 || s == 5) {
            func_0015BC78(self);
        }
    }
}

void func_00123ED0(void* self);

void func_0015A8B8(C60* self)
{
    func_00123ED0(self);
    f32* v = self->v;
    self->f2F0 = 1.0f;
    self->f2EC = 1.0f;
    self->v[0] = 1.0f;
    v[1] = 0.2f;
    v[2] = 0.1f;
}

struct Iter_00159588;
extern f32 D_00261858[];

struct Node_00159588 { void* f0; u8 pad4[0xC]; u8 body[0x50]; f32 f60; };
struct Iter_00159588 { List01* list; u8* link; s32 offset; Iter_00159588* saved; };

void func_001590A0(void* a, void* b);
void func_00152600(List01* list, Node_00159588* node);
void func_001B5F28(Pool6C* set, Node_00159588* node);

struct Next_00159588 {
    static Node_00159588* Of(Iter_00159588* it)
    {
        Node_00159588* obj = *(Node_00159588**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_00159588 {
    static void Of(Iter_00159588* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_00159588*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00159588(C6C* self)
{
    Iter_00159588 it;
    Begin_00159588::Of(&it, &self->list1BDC);
    Node_00159588* node;
    while ((node = Next_00159588::Of(&it)) != 0) {
        if (!(D_00261858[1] < node->f60)) {
            func_001590A0(node->f0, node->body);
            func_00152600(&self->list1BDC, node);
            func_001B5F28(&self->pool1BD0, node);
        }
    }
    D_0027B314 = (ListFrame*)it.saved;
}


s32 D_002621C8[6] = { 0, 0x256, 0x5D0, 2, 0x259, 0x678 };

void func_001BAC30(C40* self, void* arg);
void func_00124DF8(C40* self, s32 n, void* table);
void func_00159478(void** out, C40* self);
s32 func_0015A480(u8* self, s32 kind, C40* arg);
void func_00182ED8(s32 a);
s32 func_001526D0(List01* sub, C40* self);
void func_00152600(List01* data, C40* self);

void func_0015AC08(C40* self, void* arg)
{
    u32 i;
    func_001BAC30(self, arg);
    func_00124DF8(self, 2, D_002621C8);
    func_00159478((void**)&self->group, self);
    for (i = 0; i < 16; i++) {
        s32 kind = i + 0x23C;
        s32 p = func_0015A480((u8*)self->world, kind, self);
        if (!p)
            continue;
        func_00182ED8(p);
        if (self->mode == 1) {
            if (self->f630 == kind)
                self->f634 = self->count;
        }
        self->objs[self->count++] = (C02*)p;
    }
    if (self->mode == 1) {
        for (i = 0; i < 8; i++) {
            s32 p = func_0015A480((u8*)self->world, i + 0x24D, self);
            if (p) {
                func_00182ED8(p);
                self->objs5B0[self->count5AC++] = (C02*)p;
            }
        }
    }
    if (self->mode) {
        if (func_001526D0(&self->world->list1C48, self))
            func_00152600(&self->world->list1C48, self);
    }
}

struct Out_15B4D0 { u8 pad[0x40]; f32 scale; u8 pad2[0x10 - 4]; };
extern f32 D_0026185C;
f32 D_00262230[4] = { 1.0f, 1.5f, -2.5f, 0.0f };
f32 D_00262240[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
extern f32 D_00275C60[];
void func_00125B70(C40* self, void* c, void* out);

void func_0015B4D0(C40* self, void* a1, void* a2)
{
    Out_15B4D0 out;
    func_00125B70(self, a2, &out);
    switch (self->state) {
    case 1: {
        f32 base = self->f558;
        f32 num = D_0026185C - base;
        f32 den = self->f55C - base;
        f32 t = num / den;
        f32 v = D_00262230[0] + t * (D_00262230[1] + t * D_00262230[2]);
        f32 lo = D_00275C60[0];
        f32 hi = D_00275C60[1];
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        out.scale = out.scale * v;
        self->obj5D0->desc02()->m24(self->obj5D0, a1, &out);
        break;
    }
    case 3: {
        f32 base = self->f558;
        f32 num = D_0026185C - base;
        f32 den = self->f55C - base;
        f32 t = num / den;
        f32 v = D_00262240[0] + t * (D_00262240[1] + t * D_00262240[2]);
        f32 lo = D_00275C60[0];
        f32 hi = D_00275C60[1];
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        out.scale = out.scale * v;
        self->objs[self->index]->desc02()->m24(self->objs[self->index], a1, &out);
        break;
    }
    case 6: {
        self->objs5B0[self->index]->desc02()->m24(self->objs5B0[self->index], a1, &out);
        break;
    }
    default: {
        s32 idx = self->index;
        if (self->mode == 1 && self->f630 != -1) {
            f32 t = (D_0026185C - self->f558) / (self->f55C - self->f558);
            if (1.0f - self->f638 < t) idx = self->f634;
        }
        self->objs[idx]->desc02()->m24(self->objs[idx], a1, &out);
        break;
    }
    }
}

s32 func_001300E8(C02* plo, s32 id);
s32 func_00182FC8(C02* plo);
s32 func_0015A4B8(u32 i, s32 id);
void func_00159F48(C02* plo, s32 kind, s32 fAll, s32 zero, C02* ploRoot, s32 cmax,
                   s32* pc, C02** aplo, s32* pmin);

s32 func_0015A4F0(C6C* psw, u32 grf, s32 id, C02* ploRoot, s32 cmax, C02** aplo)
{
    s32 c;
    s32 min;
    s32 kind;
    C02* plo;
    C02* ploMark;
    C02* p;
    s32 n;
    u32 i;

    if (id == -1) {
        return 0;
    }
    if (ploRoot == 0 && (grf & 5) == 0) {
        return 0;
    }
    kind = grf & 0xFF;
    c = 0;
    if (kind == 3) {
        // Retail reads plo here before anything sets it (lw 0($s0) with $s0 unset).
        if (!(plo->desc->flags & 1)) {
            plo = (C02*)plo->parent;
        }
        for (; plo != 0; plo = (C02*)plo->parent) {
            if (func_001300E8(plo, id) != 0 && ((grf & 0x100) || func_00182FC8(plo) != 0)) {
                if (c < cmax) {
                    aplo[c] = plo;
                }
                c++;
            }
        }
    } else if (kind == 2 && !(grf & 0x100)) {
        if (!(ploRoot->desc->flags & 1)) {
            return 0;
        }
        for (plo = (C02*)ploRoot->children.head; plo != 0; plo = (C02*)plo->next) {
            if (func_001300E8(plo, id) == 0) {
                continue;
            }
            if (c < cmax) {
                aplo[c] = plo;
            }
            c++;
        }
    } else {
        switch (kind) {
        case 1:
        case 3:
        case 4:
            ploMark = ploRoot;
            if (ploMark != 0 && !(ploMark->desc->flags & 1)) {
                ploMark = (C02*)ploMark->parent;
            }
            p = ploMark;
            n = 0;
            while (p != 0) {
                n++;
                p->mark = n;
                p = (C02*)p->parent;
            }
            min = 0x7FFFFFFF;
            break;
        default:
            ploMark = 0;
            break;
        }
        for (i = id; i < 0x95 && func_0015A4B8(i, id); i++) {
            for (plo = (C02*)psw->f1884[i]; plo != 0; plo = (C02*)plo->nextById) {
                func_00159F48(plo, kind, grf & 0x100, 0, ploRoot, cmax, &c, aplo, &min);
            }
        }
        for (p = ploMark; p != 0; p = (C02*)p->parent) {
            p->mark = 0;
        }
    }
    if (!(grf & 0x200) && cmax < c) {
        c = cmax;
    }
    return c;
}

void func_001B4AA0(T21E3* self, const T21E3_Src* src);

void func_00159680(T21E3_438* self, T21E3_Src* src)
{
    func_001B4AA0(self, src);
    self->cur2.flags = self->cur.flags;
    self->id2 = src->s14;
    self->scale = src->f4;
    self->lo = src->f8;
    self->hi = src->fC;
    self->limit = src->f10;
}
