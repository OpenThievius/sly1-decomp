// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c83.h"
#include "c34.h"
#include "c6c.h"
#include "c8b.h"
#include "t2195.h"

s32 func_0012C288(void* a, void* b, s32 c, s32 d, s32 e, s32 f);

s32 func_0012C7B0(void* a, void* b, s32 c, s32 d)
{
    return func_0012C288(a, b, 0, 0, c, d);
}

struct Obj_12C9A8 { u8 pad[0x5C]; s32 count; u8* table; };

s32 func_0012C9A8(Obj_12C9A8* a0)
{
    s32 n = a0->count;
    if (n > 0) {
        s32 i = 0;
        u8* p = a0->table + 4;
        do {
            i++;
            if (*(s32*)p == 0x19) return 1;
            p += 0x10;
        } while (i < n);
    }
    return 0;
}

struct Obj_12D398 { u8 pad[0x9C]; s32 f9C; };

void* func_0012CCE8(void);
void func_0012D2A8(Obj_12D398* a, void* b);

void func_0012D398(Obj_12D398* a0)
{
    if (a0->f9C == 0) {
        void* r = func_0012CCE8();
        if (r) func_0012D2A8(a0, r);
    }
}

struct Node_12D570 { u8 pad0[4]; void* item; u8 pad1[0x18]; Node_12D570* next; };
struct Obj_12D570 { u8 pad[0x44]; Node_12D570* head; };

s32 func_001833F0(void* a, void* b);

Node_12D570* func_0012D570(Obj_12D570* a0, void* a1)
{
    ListFrame frame;
    Node_12D570* n = a0->head;
    while (n) {
        if (func_001833F0(n->item, a1)) return n;
        n = n->next;
    }
    return 0;
}

struct Node_12F190 { u8 pad[0x20]; Node_12F190* next; };
struct Obj_12F190 { u8 pad[0x44]; Node_12F190* head; };

void func_00121648(void* n, void* b);

void func_0012F190(Obj_12F190* a0, void* a1)
{
    ListFrame frame;
    Node_12F190* n = a0->head;
    while (n) {
        func_00121648(n, a1);
        n = n->next;
    }
}

struct Mid_12F7E0 { u8 pad[0x14]; void* p14; };
struct Obj_12F7E0 { u8 pad[8]; Mid_12F7E0* mid; };

void func_001831E8(void* a, void* b, void* c, s32 d);

void func_0012F7E0(Obj_12F7E0* a0, void* a1, s32 a2)
{
    func_001831E8(a0->mid->p14, (u8*)a0 + 0xE4, a1, a2);
}

void func_0012FCB0(C34* a0, s32 a1)
{
    a0->objects.items[a0->objects.count++] = a1;
}

struct Obj_12FDE8 { s32 state; s32 f4; s32 f8; };

s32 func_0012FF10(Obj_12FDE8* self);
void func_001F8C38(s32 h);
s32 func_002032C8(s32 x);
void func_0012FFE8(Obj_12FDE8* self);

void func_0012FDE8(Obj_12FDE8* a0)
{
    switch (a0->state) {
    case 0:
        if (a0->f4 >= 0) func_001F8C38(a0->f4);
        a0->f4 = -1;
        break;
    case 1:
        if (func_0012FF10(a0)) {
            func_002032C8(0);
            func_0012FFE8(a0);
        }
        a0->f8 = 0;
        break;
    }
    a0->state = -1;
}

void func_001830D8(void);

void func_0012C140(void)
{
    func_001830D8();
}

struct Step_002623C8 {
    u8 pad0[0xC];
    f32 dt;
};

extern Step_002623C8* D_002623C8;

void func_00182C58(void* self);
void func_0012C208(void* self);
void func_001DBC60(void* host, void* cb, void* ctx, s32 a3, s32 a4);

void func_0012C160(C83* self)
{
    func_00182C58(self);
    Kin83* k = &self->kin;
    f32 t = D_002623C8->dt;
    f32 v = k->pos + t * (k->vel + t * k->acc);
    f32 lo = self->lo;
    f32 hi = self->hi;
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    self->out = v;
    if (self->enabled) {
        func_001DBC60(self->world, (void*)func_0012C208, self, 0, 0);
    }
}

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_0012C7B0(void* self, s32 a1, s32 a2, s32* out, f32 fa, f32 fb);

struct Obj_0012C208 {
    u8 pad0[0x14];
    void* host;
    u8 pad1[0x28];
    s32 id;
};

void func_0012C208(Obj_0012C208* self)
{
    s32 scratch[4];
    s32 v;
    if (self->id != -1) {
        v = func_0015A418(self->host, 4, self->id, self);
        if (v == 0) {
            v = func_0015A418(self->host, 0x104, self->id, self);
        }
    } else {
        v = 0;
    }
    func_0012C7B0(self, v, 0, scratch, 0.0f, 1.0f);
}

void func_0012C288(void* self, s32 a1, s32 a2, s32 a3, s32 a4, void** out);

void* func_0012C7D8(void* self, s32 key, s32 a2)
{
    void* out;
    func_0012C288(self, key, 0, 0, a2, &out);
    return out;
}

struct Node_0012C808 {
    u8 pad0[0xC];
    s32 key;
    u8 pad1[0x2C];
    Node_0012C808* next;
};

struct Owner_0012C808 {
    u8 pad0[0x6C];
    Node_0012C808* head;
};

Node_0012C808* func_0012C808(Owner_0012C808* self, s32 key)
{
    ListFrame frame;
    Node_0012C808* node = self->head;
    if (node != 0) {
        do {
            if (node->key == key) {
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

void* func_0012C808(void* self, s32 key);
void func_0012C7B0(void* self, s32 a1, s32 a2, void** out, f32 fa, f32 fb);
void func_0012F0A0(void* obj, s32 a1, f32 fa, f32 fb);

void func_0012C840(void* self, s32 key, s32 a2, s32 a3, void** out, f32 fa, f32 fb)
{
    void* hit;
    void** dst = out ? out : &hit;
    hit = func_0012C808(self, key);
    if (hit) {
        *dst = hit;
    } else {
        func_0012C7B0(self, key, a3, dst, 0.0f, 1.0f);
    }
    func_0012F0A0(*dst, a2, fa, fb);
}

void func_0012C840(void* self, s32 key, s32 a2, s32 a3, void** out, f32 fa, f32 fb);

void* func_0012C8F8(void* self, s32 key, s32 a2, s32 a3, f32 fa, f32 fb)
{
    void* out;
    func_0012C840(self, key, a2, a3, &out, fa, fb);
    return out;
}

struct Obj_0012F0A0 { u8 pad0[0x8]; C83* sub; u8 pad1[0x8]; f32 value; };

void func_0012F6B0(Obj_0012F0A0* self, f32 x);
void func_0012F190(Obj_0012F0A0* self, s32 zero);
void func_0012F1D8(Obj_0012F0A0* self);
void func_0012E4E0(Obj_0012F0A0* self, C83* sub, s32* out);
void func_0012E760(Obj_0012F0A0* self);
void func_0012D4A8(Obj_0012F0A0* self);

void func_0012F0A0(Obj_0012F0A0* self, s32 mode, f32 a, f32 b)
{
    s32 flag = 0;
    f32 t;
    f32 base;
    switch (mode) {
    case 0:
        t = a;
        goto call;
    case 1:
        base = self->value;
        break;
    case 2:
    case 3:
        base = self->sub->length;
        break;
    default:
        goto call;
    }
    t = base + a;
call:
    func_0012F6B0(self, b);
    if (t == self->value) {
        return;
    }
    self->value = t;
    if (mode == 3) {
        func_0012E4E0(self, self->sub, &flag);
    } else {
        func_0012D4A8(self);
    }
    func_0012F190(self, 0);
    func_0012F1D8(self);
    if (flag != 0) {
        func_0012E760(self);
    }
}

struct Item_0012F1D8 { u8 pad[0x20]; Item_0012F1D8* next; };
struct Owner_0012F1D8 { u8 pad[0x44]; Item_0012F1D8* items; };

void func_001226D8(Item_0012F1D8* item);

void func_0012F1D8(Owner_0012F1D8* self)
{
    ListFrame frame;
    for (Item_0012F1D8* p = self->items; p != 0; p = p->next) {
        func_001226D8(p);
    }
}

struct Sub_0012F6B0 { u8 pad[0x98]; f32 k98; };
struct Rec_0012F6B0 { u8 pad0[0x8]; Sub_0012F6B0* sub; u8 pad1[0xC]; f32 out; f32 scale; };

void func_0012F6B0(Rec_0012F6B0* self, f32 x)
{
    self->out = x * self->scale * self->sub->k98;
}

struct Sub_0012F6D0 { u8 pad[0x98]; f32 k98; };
struct Rec_0012F6D0 { u8 pad0[0x8]; Sub_0012F6D0* sub; u8 pad1[0xC]; f32 out; f32 scale; };

void func_0012F6B0(Rec_0012F6D0* self, f32 x);

void func_0012F6D0(Rec_0012F6D0* self, f32 x)
{
    f32 denom = self->scale * self->sub->k98;
    f32 r = self->out;
    if (denom != 0.0f) {
        r = r / denom;
    }
    self->scale = x;
    func_0012F6B0(self, r);
}

extern u8* D_00275710;

void func_00152600(u8* a, void* b);
void func_001B5F28(u8* a, void* b);

void func_0012E710(void* a0)
{
    func_00152600(D_00275710 + 0x1B7C, a0);
    func_001B5F28(D_00275710 + 0x1B58, a0);
}

struct Obj_12E928 { void** vtbl; };

void* func_0012D570(void* a0, void* a1);

void func_0012E928(void* a0, void* a1, void* a2)
{
    Obj_12E928* n = (Obj_12E928*)func_0012D570(a0, a1);
    if (n) ((void (*)(void*, void*))n->vtbl[2])(n, a2);
}

struct Node_12F718 {
    u8 pad0[4];
    void* data4;
    u8 pad8[0xC];
    s32 value14;
    u8 pad18[8];
    Node_12F718* next;
};

struct Owner_12F718 {
    u8 pad0[0x44];
    Node_12F718* head;
};

void func_00129A58(void* p);

void func_0012F718(Owner_12F718* owner, s32 value)
{
    s32 frame[4];
    (void)frame;
    Node_12F718* node = owner->head;
    while (node != 0) {
        node->value14 = value;
        func_00129A58(node->data4);
        node = node->next;
    }
}

struct Obj_12F760 {
    void (**vtbl)(void* self);
};

struct Node_12F760 {
    void (*fn)(void* data, s32 a, s32 b);
    void* data4;
    u8 pad8[8];
    Node_12F760* next;
};

struct Owner_12F760 {
    u8 pad0[0xC];
    Obj_12F760* obj;
    u8 pad1[0xD4];
    Node_12F760* list;
};

void func_0012F760(Owner_12F760* self, s32 a1, s32 a2)
{
    Obj_12F760* obj = self->obj;
    if (obj != 0) {
        obj->vtbl[18](obj);
    }
    Node_12F760* node = self->list;
    while (node != 0) {
        Node_12F760* next = node->next;
        node->fn(node->data4, a1, a2);
        node = next;
    }
}

void* func_0012CBE8(void);

f32 func_0012CCC0(void)
{
    f32* p = (f32*)func_0012CBE8();
    f32 r = 0.0f;
    if (p != 0) {
        r = *p;
    }
    return r;
}

struct Mid_12F810 { u8 pad[0x14]; void* p14; };
struct Obj_12F810 { u8 pad[8]; Mid_12F810* mid; };

void func_001831E8(void* a, void* b, void* c, void* d);

void func_0012F810(Obj_12F810* a0, C02** a1)
{
    func_001831E8(a0->mid->p14, (u8*)a0 + 0xE4, (void*)(*a1)->link40.prev, a1);
}

void func_001B7968(C03* self);
void func_001B9AE0(C03* self, s32 a, Vec02* b, s32 c, Vec02* d);

void func_0012F840(C34* self)
{
    func_001B7968(self);
    func_001B9AE0(self, 3, 0, 3, 0);
    self->id = -1;
}

void func_001BA130(C03* self);
void func_00138F28(void* a, void* b);

void func_0012F888(C34* self)
{
    func_001BA130(self);
    if (self->parent == 0) {
        func_00138F28(self->world, self);
    }
}

struct Obj_12FF10 { u8 pad[0xC]; s32 f0C; };

s32 func_0012FF10(Obj_12FF10* a0)
{
    return a0->f0C != 0;
}

struct Obj_12FF20 { s32 f00; s32 f04; u8 pad08[4]; s32 f0C; s32 f10; u8 pad14[4]; s32 f18; u8 pad1C[4]; s32 f20; };

s32 func_0012FF10(Obj_12FF20* a0);
s32 func_001F92E8(s32 a, s32 b, s32* c);
s32 func_00203D90(void);

s32 func_0012FF20(Obj_12FF20* a0)
{
    s32 r = 0;
    s32 done = 0;
    if (a0->f18 == a0->f20 && func_0012FF10(a0)) {
        switch (a0->f00) {
        case 0: {
            s32 tmp;
            done = func_001F92E8(a0->f04, 1, &tmp);
            r = tmp == 0;
            break;
        }
        case 1:
            r = func_002032C8(1) == 0;
            if (r) done = func_00203D90();
            break;
        }
    }
    if (done) {
        a0->f0C = 0;
        a0->f10 = 0;
        r = 0;
    }
    return r;
}

void func_0012D3E0() {}

void func_0012D3E8() {}

void func_0012D3F0() {}

void func_0012FCD0(C34* obj, s32 value) { obj->kinds.items[obj->kinds.count++] = value; }

struct Obj_12FCF0 { u8 pad0[4]; s32 f4; s32 f8; s32 fc; s32 f10; s32 f14; s32 f18; s32 f1c; s32 f20; s32 f24; s32 f28; };
Obj_12FCF0* func_0012FCF0(Obj_12FCF0* obj, s32 value)
{
    obj->f8 = 0;
    obj->f14 = (value + 0x3F) & -64;
    obj->f4 = -1;
    obj->f10 = 0;
    obj->f1c = 0;
    obj->f28 = 0;
    obj->f24 = 0;
    obj->fc = 0;
    obj->f20 = 0;
    obj->f18 = 0;
    return obj;
}

void func_0018D778(void* self);
void func_0012FD30(void* self, s32 flags)
{
    func_0012FDE8((Obj_12FDE8*)self);
    if (flags & 1) func_0018D778(self);
}

struct Pair_0012FD78 { s32 a; s32 b; };
s32 func_0012FDA0(void* self, s32 a, s32 b);
s32 func_0012FD78(void* self, Pair_0012FD78* pair)
{
    return func_0012FDA0(self, pair->a, pair->b);
}

struct Obj_12D448 {
    u8 pad0[0x24];
    s8 state;
};

void func_001DDA20(void* a);
void func_001DDA50(void* a);

void func_0012D448(Obj_12D448* self, s32 v)
{
    if (v == self->state) {
        return;
    }
    if (v != 0) {
        func_001DDA20(*(void**)&D_00275710);
    } else {
        func_001DDA50(*(void**)&D_00275710);
    }
    self->state = (s8)v;
}

void func_0012E760(void* obj);
void func_0012C7B0(void* self, void* a1, f32 fa, f32 fb, void* a2, void** out);

void func_0012C918(void* self, void* a1, void* a2, void** out, f32 fa, f32 fb)
{
    if (*out != 0) {
        func_0012E760(*out);
        *out = 0;
    }
    if (self != 0) {
        func_0012C7B0(self, a1, fa, fb, a2, out);
    }
}

s32 func_001833F0(void* a, s32 b);

struct Entry_12CCE8 { s32 key; u8 pad[0x18]; };
void* func_0012CCE8(Gr8B* self, void* key)
{
    for (s32 i = 0; i < self->f38; i++) {
        Entry_12CCE8* e = (Entry_12CCE8*)(self->f3C + i * 0x1C);
        if (func_001833F0(key, e->key) != 0) {
            return e;
        }
    }
    return 0;
}

s32 func_001B8A08(C03* self, C03* key);
s32 func_001833F0(void* key, s32 item);
s32 func_001300E8(void* key, s32 kind);

s32 func_0012FA88(C34* self, C03* key)
{
    s32 hit;
    s32 i;
    s32 j;

    if (func_001B8A08(self, key) != 0) {
        return 1;
    }
    for (i = 0; i < self->objects.count; i++) {
        if (func_001833F0(key, self->objects.items[i]) != 0) {
            break;
        }
    }
    if (i < self->objects.count) {
        hit = 1;
        goto tail;
    }
    for (j = 0; j < self->kinds.count; j++) {
        if (func_001300E8(key, self->kinds.items[j]) != 0) {
            break;
        }
    }
    hit = j < self->kinds.count;
tail:
    if (self->accept != 0) {
        return hit;
    }
    return hit ^ 1;
}

struct Ref_0012FDA0;

struct Obj_0012FDA0 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
};

void func_0012FE70(Ref_0012FDA0 *self);

s32 func_0012FDA0(Obj_0012FDA0 *self, s32 a1, s32 a2) {
    self->f8 = a1;
    s32 t = self->f14;
    self->f28 = a2;
    self->f24 = a2;
    self->f0 = 1;
    self->f1C = t;
    self->f18 = 0;
    self->f20 = 0;
    func_0012FE70((Ref_0012FDA0 *)self);
    return 1;
}

struct Obj_12FFE8 {
    s32 f0;
    u8 pad4[4];
    s32 f8;
    s32 fC;
    s32 f10;
    u8 pad14[4];
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
};

s32 func_0012FF20(Obj_12FFE8* a0);

void func_0012FFE8(Obj_12FFE8* self)
{
    if (func_0012FF20(self) == 0) {
        return;
    }
    if (self->f0 == 1) {
        self->f8 += self->fC / 2048;
    }
    s32 v = self->fC;
    self->f24 -= v;
    self->f18 = v;
    self->f1C = self->f10;
    self->fC = 0;
    self->f10 = 0;
    self->f20 = 0;
}

struct Obj_12D3F8 { void* vt; u8 pad[0x5C]; };
struct Buf_12D3F8 { u8 pad[4]; };
struct Head_2197B8 { const void* tinfo; s32 f4; };
extern const Head_2197B8 D_002197B8;
void* func_001B5EE0(Pool6C* pool);
void func_00152438(Buf_12D3F8* self, s32 value);

Obj_12D3F8* func_0012D3F8(C6C* pool)
{
    Obj_12D3F8* o = (Obj_12D3F8*)func_001B5EE0((Pool6C*)((u8*)pool + 0x1B58));
    o->vt = (void*)&D_002197B8;
    func_00152438((Buf_12D3F8*)((u8*)o + 0x44), 0x20);
    *(void**)((u8*)o + 0x60) = (u8*)o + 0x64;
    return o;
}

struct Quad_12F9B8 { s32 a, b, c, d; };

void func_001B93F8(C03* self);
void func_00128018(void* a, s32 b, void* c, void* d);

extern u8 D_00248D30[];

void func_0012F9B8(C34* self)
{
    Quad_12F9B8 loc;
    C02* cur;
    func_001B93F8(self);
    if (self->target != 0) {
        self->target->desc02()->m20(self->target, (Vec02*)D_00248D30);
        self->target->desc02()->m21(self->target, (Vec02*)D_00248D30);
        switch (self->mode) {
        case 1:
            self->target->desc02()->m1D(self->target, &self->pos);
            break;
        case 2: {
            C02* node = self->found;
            func_00128018(node->parent, 0, &node->link40, &loc);
            self->target->desc02()->m1D(self->target, (Vec02*)&loc);
            break;
        }
        }
        cur = self->target;
        self->target = 0;
        self->done = cur;
    }
}

struct Item_12E760 { s32 w[4]; };
struct Vt_12E760 { void* pad[2]; void (*fn8)(void* self, s32 a); };
struct Elem_12E760 { Vt_12E760* vt; };
struct Obj_12E760 {
    u8 pad0[8];
    C83* f8;
    u8 padC[0x38];
    s32 f44;
    u8 pad48[8];
    s32 f50;
    u8 pad54[0x90];
    s32 fE4;
};
struct Frame_12E760 { s32 f00; s32 f04; s32 f08; s32 f0C; };
struct Tmp_12E760 { s32 a; s32 b; };

void func_0012D5D0(Obj_12E760* self, Item_12E760* item, Tmp_12E760* out);
void func_0012F760(Obj_12E760* self, s32 a, Obj_12E760* b);
void func_001DBC18(u8* self, s32 node);
void func_0015F9A0(u8* a, Obj_12E760* s);
void func_0012D448(Obj_12E760* self, s32 v);
void func_001DBD40(u8* a, s32 b, s32 c, Obj_12E760* d, s32 e, s32 f);
void func_00152600(u8* a, Obj_12E760* b);
void func_00152470(u8* a, Obj_12E760* b);
void func_001BF718(s32* slot);
void func_001837E0(C83* self, s32 a, s32 b, s32* c);

void func_0012E760(Obj_12E760* self)
{
    Frame_12E760 fr;
    Tmp_12E760 tmp;
    s32 i = 0;
    C83* sub = self->f8;
    u8* base = (u8*)sub->world;
    for (i = 0; i < sub->endCount; i++) {
        Item_12E760* it = (Item_12E760*)((u8*)sub->endList + i * 16);
        tmp.a = 0;
        func_0012D5D0(self, it, &tmp);
    }
    func_0012F760(self, 6, self);
    func_001DBC18(base, self->fE4);
    self->fE4 = 0;
    func_0015F9A0(base, (Obj_12E760*)((u8*)self + 0x54));
    func_0012D448(self, 0);
    func_001DBD40(base, 2, 0, self, -1, 0);
    func_00152600(sub->props6C, self);
    if (sub->f50 != 0) {
        func_00152600(base + 0x1B70, self);
    } else {
        func_00152600(base + 0x1B64, self);
    }
    func_00152470(base + 0x1B7C, self);
    s32 s0 = (s32)self + 0xC;
    s32 e = (s32)self + 0x44;
    fr.f04 = e;
    fr.f00 = e;
    s32 link = *(s32*)(e + 8);
    fr.f0C = (s32)D_0027B314;
    D_0027B314 = (ListFrame*)&fr;
    fr.f08 = link;
    s32 head = *(s32*)e;
    fr.f04 = head + fr.f08;
    s32 a = head;
    if (a != 0) {
        do {
            Elem_12E760* el = (Elem_12E760*)a;
            el->vt->fn8(el, 7);
            s32 nx = *(s32*)fr.f04;
            fr.f04 = nx + fr.f08;
            a = nx;
        } while (a != 0);
    }
    if (self->f50 != 0)
        func_001BF718(&self->f50);
    tmp.b = s0;
    func_001837E0(sub, 0xB, 1, &tmp.b);
    D_0027B314 = (ListFrame*)fr.f0C;
}


f32 func_002058A0(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);

s32 func_0012E9E0(Player2195* o, f32* pos, f32* vel)
{
    s32 r = 0;
    C83* l = o->anim;
    f32 x = *pos;
    f32 lim = l->length;
    if (lim <= x) {
        switch (l->f44) {
        case 0:
            if (lim < x) {
                *pos = lim;
                *vel = 0.0f;
            }
            break;
        case 1:
            *pos = func_002058A0(x, lim);
            break;
        case 2: {
            f32 d = lim + lim;
            s32 flag = 1;
            if (d <= x) {
                *pos = func_002058A0(x, d);
                if (*pos < l->length) flag = 0;
                *vel = __builtin_fabsf(*vel);
            }
            if (flag) {
                *pos = d - *pos;
                *vel = -*vel;
            }
            break;
        }
        }
        r = 1;
    } else if (x < 0.0f) {
        switch (l->f44) {
        case 0:
            *pos = 0.0f;
            *vel = 0.0f;
            break;
        case 1:
            *pos = func_001EAFE0(x, lim);
            break;
        case 2: {
            x = -x;
            if (x <= lim) {
                *pos = x;
                *vel = -*vel;
            } else {
                f32 d = lim + lim;
                *vel = __builtin_fabsf(*vel);
                f32 q = func_001EAFE0(*pos, d);
                *pos = q;
                if (l->length <= q) {
                    *pos = d - q;
                    *vel = -*vel;
                }
            }
            break;
        }
        }
        r = 1;
    }
    return r;
}

struct Self_12D2A8 { u8 pad0[0x38]; s32 f38; Track83* f3C; u8 pad1[0x9C - 0x40]; Track83* f9C; };

void func_001F5B08(Track83* dst, Track83* src, s32 bytes);

void func_0012D2A8(Self_12D2A8* self, Track83* p)
{
    Track83 tmp = *p;
    s32 idx = p - self->f3C;
    self->f38 = self->f38 - 1;
    if (idx < self->f38) {
        func_001F5B08(p, p + 1, (self->f38 - idx) * 0x1C);
    }
    p = self->f3C + self->f38;
    *p = tmp;
    self->f9C = p;
}

struct Item_12E4E0 { f32 t; s32 type; s32 w2; s32 w3; };
struct Self_12E4E0 { u8 pad0[0x14]; f32 time; s32 f18; s32 f1C; s32 idx; };
void func_0012D5D0(Self_12E4E0* self, Item_12E4E0* item, s32* out);

void func_0012E4E0(Self_12E4E0* self, C83* sub, s32* out)
{
    f32 limit = self->time + 0.0001f;
    if (sub->timedCount != 0) {
    while (self->idx < sub->timedCount && ((Item_12E4E0*)sub->timedList)[self->idx].t < limit) {
        Item_12E4E0* it = &((Item_12E4E0*)sub->timedList)[self->idx++];
        switch (it->type) {
        case 8:
            self->time = it->t;
            self->f18 = 0;
            *out = 1;
            return;
        case 9:
        case 10:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 28:
        case 39:
            func_0012D5D0(self, it, out);
            break;
        }
    }
    }
}

// was NEAR: call result is stored directly (retail copies v0 to v1 first, then s1=v1 for the out pointer); 5 lines differ

struct Entry_12D1B0 { s32 f0; s32 type; s32 f8; s32 fC; };
struct Obj_12D1B0 {
    u8 pad0[0x14];
    void* host;
    u8 pad1[0x5C - 0x18];
    s32 count;
    Entry_12D1B0* items;
};

void* func_0018D658(s32 size);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_0012D1B0(Obj_12D1B0* self, void* ctx, s32* outCount, s32** outArr)
{
    s32 n = 0;
    s32 i;
    u8* p;
    if (self->count > 0) {
        i = self->count;
        p = (u8*)self->items + 4;
        do {
            if (*(s32*)p == 0x29) n++;
            p += 16;
        } while (--i != 0);
    }
    if (outCount != 0) {
        *outCount = n;
    }
    if (outArr != 0) {
        s32* res = (s32*)func_0018D658(n * 4);
        *outArr = res;
        i = 0;
        if (i < self->count) {
            s32* out = res;
            do {
                Entry_12D1B0* e = (Entry_12D1B0*)(i * 16 + (u8*)self->items);
                if (e->type == 0x29) {
                    *out = func_0015A418(self->host, 0x104, e->f8, ctx);
                    out++;
                }
                i++;
            } while (i < self->count);
        }
    }
}

struct World_12D5D0;
struct VObj_12D5D0 {
    void** vt;
};
struct Msg_12D5D0 {
    union {
        f32 f;
        s32 i;
    } a0;
    s32 kind;
    union {
        s32 i;
        f32 f;
        void* p;
        struct {
            s16 lo;
            s16 hi;
        } h;
    } a8;
    union {
        s32 i;
        f32 f;
        struct {
            s16 lo;
            s16 hi;
        } h;
    } aC;
};
struct Seq_12D5D0 {
    s16 count;
    s16 ids[6];
    s16 cur;
    s16 target;
    u8 pad12[2];
    s32 f14;
    s32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
};
struct Ent_12D5D0 {
    u8 pad0[4];
    VObj_12D5D0* f4;
    VObj_12D5D0* f8;
    s32 fC;
    u8 pad10[0x18 - 0x10];
    s32 f18;
};
struct Owner_12D5D0 {
    u8 pad0[0x14];
    World_12D5D0* world;
    void* f18;
    u8 pad1C[0x34 - 0x1C];
    f32 f34;
    u8 pad38[0x3C - 0x38];
    Ent_12D5D0* ents;
    u8 pad40[0x5C - 0x40];
    s32 nmsgs;
    Msg_12D5D0* msgs;
};
struct Self_12D5D0 {
    u8 pad0[0x8];
    Owner_12D5D0* owner;
    void* fC;
    u8 pad10[0x14 - 0x10];
    f32 f14;
    f32 f18;
    u8 pad1C[0x20 - 0x1C];
    s32 f20;
    u8 pad24[0x28 - 0x24];
    void* f28;
    Msg_12D5D0* f2C;
    Msg_12D5D0* f30;
    u8 pad34[0x50 - 0x34];
    VObj_12D5D0* f50;
};
struct Node_12D5D0 {
    u8 pad0[4];
    VObj_12D5D0* f4;
    u8 pad8[0x10 - 0x8];
    u8 f10;
    u8 f11;
    s8 f12;
    s8 f13;
    u8 pad14[0x28 - 0x14];
    s32 f28;
    void SetMode(s32 mode) { f11 = mode; }
};
struct Thing_12D5D0 {
    void** vt;
    u8 pad4[0x18 - 0x4];
    void* f18;
    u8 pad1C[0x450 - 0x1C];
    s32 f450;
    u8 pad454[0x470 - 0x454];
    s32 f470;
};
struct Info_12D5D0 {
    s32 f0;
    s32 f4;
    s32 f8;
    f32 fC;
};
struct Glob_12D5D0 {
    u8 pad0[0x2220];
    s32 f2220;
    u8 pad2224[4];
    s32 f2228;
};
struct Vec_12D5D0 {
    f32 x, y, z, w;
};
struct Req_12D5D0 {
    s32 flags;
    void* f4;
    u8 pad8[0x20 - 0x8];
    Vec_12D5D0 buf;
    f32 f30;
    u8 pad34[4];
    void* f38;
    u8 pad3C[0x50 - 0x3C];
};
union Scratch_12D5D0 {
    Req_12D5D0 req;
    Vec_12D5D0 v[3];
    void* p[3];
    s32 w[3];
};
struct __attribute__((packed)) Word_12D5D0 { s32 v; };

typedef void (*VFn_12D5D0)(void* self);
typedef void (*VFnI_12D5D0)(void* self, s32 a);
typedef void (*VFnP_12D5D0)(void* self, void* a);
typedef void (*VFnIP_12D5D0)(void* self, s32 a, void* b);
typedef void (*VFnAim_12D5D0)(void* self, void* obj, s32 a, Vec_12D5D0* b, Vec_12D5D0* c, f32 x, f32 y);

extern Glob_12D5D0* D_00262E10;
extern s32 D_002623C4;
extern u8 D_00275F80[];
extern u8 D_0026E760[];
extern u8 D_00262C70[];
extern u8 D_00269A00[];
extern VObj_12D5D0 D_00272E08;
extern u8 D_00275BC0[];

s32 func_001BE810(void);
void func_001BE728(void* p);
void func_001BE998(void);
s32 func_001EAA70(s32 lo, s32 hi);
s32 func_001BE568(s32 id);
Thing_12D5D0* func_0015A418(World_12D5D0* w, s32 kind, s32 id, void* scope);
Thing_12D5D0* func_0015A448(World_12D5D0* w, s32 id, void* scope);
void func_001BFCD8(s32 id, VObj_12D5D0** handle, Thing_12D5D0* target, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001BF788(VObj_12D5D0* h, s32 n);
void func_001BED20(void);
void func_001BECF8(void);
void func_0012F6B0(Self_12D5D0* self, f32 x);
void func_0012D4A8(Self_12D5D0* self);
void func_0012F1D8(Self_12D5D0* self);
void func_001518B8(Thing_12D5D0* t);
void func_0012E760(Self_12D5D0* self);
s32 func_00126CB8(Thing_12D5D0* t, f32 v);
s32 func_00126D60(Thing_12D5D0* t, f32 v);
void func_001B9AE0(Thing_12D5D0* t, s32 a, s32 b, s32 c, s32 d);
void func_001F4ED0(Thing_12D5D0* t);
void func_001F4F20(Thing_12D5D0* t);
void func_0012D448(Self_12D5D0* self, s32 v);
void func_00177800(Glob_12D5D0* g, s32 flag);
void func_0012F190(Self_12D5D0* self, s32 v);
Node_12D5D0* func_0012D570(Self_12D5D0* self, s32 key);
void func_001215C0(Node_12D5D0* n);
void func_001EFFA0(u8* dst, s32 a, s32 b);
void func_001F00C0(u8* dst, s32 a, s32 b);
void func_001F4408(s32 a, s32 b);
void func_001AB890(u8* p, f32 x);
void func_001AB938(u8* p);
void func_001AB958(u8* p);
s32 func_0012C7B0(Thing_12D5D0* a, Thing_12D5D0* b, s32 c, s32 d, f32 x, f32 y);
void func_0016EC38(u8* p, s32 n, f32 f);
void func_001837E0(void* self, s32 a, s32 b, void* c);
void func_0012F760(Self_12D5D0* self, s32 a, void* b);
void func_0012B2F8(Thing_12D5D0* t, s32 key);
void* func_001B6388(Thing_12D5D0* a, Thing_12D5D0* b);
void* func_001B6290(Thing_12D5D0* a, Thing_12D5D0* b, s32 c, s32 d);
void func_001B64D8(void* a, s32 b);
void func_001B6438(void* o);
s32 func_001300E8(Thing_12D5D0* n, s32 kind);
void func_001920B0(Thing_12D5D0* n, Vec_12D5D0* out);
void func_001F3BD8(Thing_12D5D0* n, Vec_12D5D0* out);
s32 func_00182FC8(void* p);
void func_001DDB58(World_12D5D0* w);
void func_001DDBB8(World_12D5D0* w);
void func_0018F0E8(u8* a, s32 b);
void func_0014AEA0(VObj_12D5D0* self, s32 n, f32 x, f32 y);
void func_0014AF10(VObj_12D5D0* self);
void func_0014AF38(VObj_12D5D0* self, s32 a, s32 b, f32 x);
void func_001E96F8(u8* obj, s32 mode);
void func_001DDAB8(World_12D5D0* w, f32 v);
void func_001DDAC8(World_12D5D0* w, f32 v);
void func_0017CE20(Thing_12D5D0* t, Glob_12D5D0* g);

struct Clamp_12D5D0 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

void func_0012D5D0(Self_12D5D0* self, Msg_12D5D0* msg, s32* out)
{
    Scratch_12D5D0 u;
    s32 rev = 0;
    Owner_12D5D0* owner = self->owner;
    World_12D5D0* world = owner->world;

    if (self->f18 < 0.0f && msg >= owner->msgs) {
        rev = msg < &owner->msgs[owner->nmsgs];
    }
    switch (msg->kind) {
    case 42:
        if (func_001BE810() != 0) {
            self->f14 = Clamp_12D5D0::Of(msg->a0.f, 0.0f, owner->f34);
            self->f20--;
            *out = 1;
        }
        break;
    case 44:
        func_001BE728(msg->a8.p);
        break;
    case 43:
        func_001BE998();
        break;
    case 0: {
#define Q_12D5D0 ((Seq_12D5D0*)msg->a8.p)
        s32 idx;
        s32 busy;
        s32 id;
        Thing_12D5D0* tgt;
        if (Q_12D5D0->count < 2) {
            idx = 0;
        } else {
            s32 r = func_001EAA70(0, Q_12D5D0->count - 2);
            idx = (Q_12D5D0->cur + r + 1) % Q_12D5D0->count;
            Q_12D5D0->cur = idx;
        }
        id = Q_12D5D0->ids[idx];
        if (id == -1) {
            return;
        }
        busy = func_001BE568(id);
        if (self->f50 != 0 && busy != 0) {
            return;
        }
        if (Q_12D5D0->target != -1) {
            tgt = func_0015A418(world, 0x104, Q_12D5D0->target, self->fC ? self->fC : (void*)self->owner);
        } else {
            tgt = (Thing_12D5D0*)self->fC;
        }
        if (tgt != 0) {
            func_001BFCD8(id, busy ? &self->f50 : 0, tgt, 0, (f32)Q_12D5D0->f18, (f32)Q_12D5D0->f14, Q_12D5D0->f24,
                          Q_12D5D0->f1C, Q_12D5D0->f20, 0, 0);
            if (busy && self->f50 != 0) {
                ((VFnIP_12D5D0)tgt->vt[18])(tgt, 8, self->f50);
            }
        } else {
            func_001BFCD8(id, busy ? &self->f50 : 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
#undef Q_12D5D0
        break;
    }
    case 1:
        if (self->f50 != 0) {
            func_001BF788(self->f50, 0);
        }
        break;
    case 2:
        func_001BED20();
        break;
    case 3:
        func_001BECF8();
        break;
    case 11:
        self->f14 = Clamp_12D5D0::Of(msg->a0.f, 0.0f, owner->f34);
        self->f18 = 0.0f;
        break;
    case 4:
    case 7:
        self->f14 = msg->a8.f;
        func_0012F6B0(self, msg->aC.f);
        func_0012D4A8(self);
        func_0012F1D8(self);
        break;
    case 5:
        func_0012F6B0(self, msg->a8.f);
        break;
    case 6: {
        Thing_12D5D0* t = func_0015A418(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t != 0) {
            func_001518B8(t);
        }
        break;
    }
    case 8:
        func_0012E760(self);
        *out = 1;
        break;
    case 9:
    case 10: {
        s32 on = msg->kind == 9;
        if (rev) {
            on = !on;
        }
        Thing_12D5D0* t = func_0015A418(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t == 0) {
            return;
        }
        if (msg->aC.f != 0.0f) {
            if (on) {
                func_00126CB8(t, msg->aC.f);
            } else {
                func_00126D60(t, msg->aC.f);
            }
        } else {
            if (on) {
                ((VFn_12D5D0)t->vt[6])(t);
            } else {
                ((VFn_12D5D0)t->vt[7])(t);
            }
        }
        break;
    }
    case 16: {
        Thing_12D5D0* t = func_0015A418(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)self->owner);
        if (t != 0) {
            func_001B9AE0(t, msg->aC.h.lo < 0 ? t->f450 : msg->aC.h.lo, 0, msg->aC.h.hi < 0 ? t->f470 : msg->aC.h.hi, 0);
        }
        break;
    }
    case 12:
    case 13: {
        s32 on = msg->kind == 12;
        Thing_12D5D0* t;
        if (rev) {
            on = !on;
        }
        t = func_0015A418(world, 4, msg->a8.i, self->owner);
        if (t != 0) {
            if (on) {
                func_001F4ED0(t);
            } else {
                func_001F4F20(t);
            }
        }
        break;
    }
    case 14:
    case 15:
    {
        s32 on = msg->kind == 14;
        if (rev) {
            on = !on;
        }
        func_0012D448(self, on);
    }
        break;
    case 19:
    case 20: {
        s32 on = msg->kind == 19;
        if (rev) {
            on = !on;
        }
        func_00177800(D_00262E10, on);
        if (on && msg->aC.i != 0) {
            func_0012F190(self, 1);
        }
        break;
    }
    case 17:
    case 18: {
        Node_12D5D0* n = func_0012D570(self, msg->a8.i);
        if (n != 0) {
            if ((msg->kind != 17) != !rev) {
                n->SetMode(5);
                n->f10 = 5;
            } else {
                func_001215C0(n);
            }
        }
        break;
    }
    case 21:
    case 22:
    case 23:
    case 24: {
        Node_12D5D0* n;
        s32 key;
        if (msg->kind == 21 || msg->kind == 23) {
            key = *(s32*)msg->a8.p;
        } else {
            key = msg->a8.i;
        }
        n = func_0012D570(self, key);
        if (n == 0) {
            break;
        }
        switch (msg->kind) {
        case 21:
            self->f28 = n;
            self->f2C = msg;
            break;
        case 22:
            self->f2C = 0;
            if (self->f30 == 0) {
                self->f28 = 0;
            }
            break;
        case 23:
            self->f28 = n;
            self->f30 = msg;
            break;
        case 24:
            self->f30 = 0;
            if (self->f2C == 0) {
                self->f28 = 0;
            }
            break;
        }
        break;
    }
    case 25:
        func_001EFFA0(D_00275F80, msg->aC.i, msg->a8.h.lo);
        break;
    case 26:
        func_001F00C0(D_00275F80, msg->aC.i, msg->a8.h.lo);
        break;
    case 27: {
        Glob_12D5D0* g = D_00262E10;
        if (g != 0 && g->f2220 == 9 && g->f2228 == 0x1C && (s32)D_002623C8 == D_002623C4) {
            return;
        }
        func_001F4408(msg->a8.i, msg->aC.i);
        break;
    }
    case 33:
        func_001AB890(D_0026E760, msg->a8.f);
        func_001AB938(D_0026E760);
        break;
    case 34:
        func_001AB958(D_0026E760);
        break;
    case 28: {
        Thing_12D5D0* a = func_0015A448(world, ((Info_12D5D0*)msg->a8.p)->f0, owner->f18);
        Thing_12D5D0* b;
        if (((Info_12D5D0*)msg->a8.p)->f4 != -1) {
            b = func_0015A448(owner->world, ((Info_12D5D0*)msg->a8.p)->f4, owner->f18);
        } else {
            b = 0;
        }
        if (a != 0) {
            func_0012C7B0(a, b, 0, 0, *(f32*)&((Info_12D5D0*)msg->a8.p)->f8, ((Info_12D5D0*)msg->a8.p)->fC);
        }
        break;
    }
    case 29:
    case 30:
    case 31:
    case 32: {
        Node_12D5D0* n = func_0012D570(self, msg->a8.i);
        u8 go = 0;
        if (n != 0) {
            Ent_12D5D0* e = &owner->ents[n->f28];
            switch (msg->kind) {
            case 29:
                if (e->fC != 0) {
                    u8 v = n->f12;
                    n->f12 = 2;
                    go = (u8)(v + 1) < 2;
                }
                break;
            case 30:
                if (e->fC != 0) {
                    s8 v = n->f12;
                    n->f12 = -1;
                    go = v != -1;
                }
                break;
            case 31:
                if (e->f18 != 0) {
                    u8 v = n->f13;
                    n->f13 = 2;
                    go = (u8)(v + 1) < 2;
                }
                break;
            case 32:
                if (e->f18 != 0) {
                    s8 v = n->f13;
                    n->f13 = -1;
                    go = v != -1;
                }
                break;
            }
        }
        if (go) {
            ((VFn_12D5D0)n->f4->vt[47])(n->f4);
        }
        break;
    }
    case 35:
    case 36: {
        Node_12D5D0* n = func_0012D570(self, msg->a8.i);
        if (n == 0) {
            break;
        }
        Ent_12D5D0* e = &owner->ents[n->f28];
        VObj_12D5D0* o = n->f4;
        if (msg->kind == 35) {
            ((VFnAim_12D5D0)e->f4->vt[0])(e->f4, o, 0, &u.v[0], &u.v[1], msg->a0.f, self->f18);
            ((VFnP_12D5D0)o->vt[33])(o, &u.v[0]);
            ((VFnP_12D5D0)o->vt[36])(o, &u.v[1]);
        } else {
            ((VFnAim_12D5D0)e->f8->vt[0])(e->f8, o, 0, &u.v[2], &u.v[0], msg->a0.f, self->f18);
            ((VFnP_12D5D0)o->vt[34])(o, &u.v[2]);
            ((VFnP_12D5D0)o->vt[37])(o, &u.v[0]);
        }
        break;
    }
    case 37:
        func_0016EC38(D_00262C70, msg->a8.h.hi, (f32)msg->a8.h.lo * 0.016666668f);
        break;
    case 38: {
        Thing_12D5D0* t;
        if (msg->a8.i == -1) {
            t = (Thing_12D5D0*)self->fC;
        } else {
            t = func_0015A448(world, msg->a8.i, self->fC);
        }
        if (t == 0) {
            break;
        }
        u.p[1] = (void*)msg->aC.i;
        u.p[0] = self;
        ((VFnIP_12D5D0)t->vt[18])(t, 0x12, u.p);
        break;
    }
    case 39: {
        *(f32*)&u.w[1] = msg->a0.f;
        u.w[2] = msg->a8.i;
        u.p[0] = self;
        func_0012F760(self, 0x13, u.w);
        break;
    }
    case 40: {
        u.p[1] = &msg->a8;
        u.p[0] = &self;
        func_001837E0(self->owner, 0xA, 2, u.p);
        break;
    }
    case 41: {
        Thing_12D5D0* t;
        if (self->fC == 0) {
            break;
        }
        t = func_0015A418(world, 0x104, msg->a8.i, self->fC);
        if (t == 0) {
            break;
        }
        u.p[1] = t;
        *(f32*)&u.w[2] = msg->a0.f;
        u.p[0] = self;
        func_0012F760(self, 0x15, u.w);
        break;
    }
    case 45: {
        Thing_12D5D0* t = func_0015A418(world, 0x104, msg->a8.i, self->fC);
        if (t != 0) {
            func_0012B2F8(t, msg->aC.i);
        }
        break;
    }
    case 46: {
        void* scope = self->fC ? self->fC : (void*)self->owner;
        Thing_12D5D0* a = func_0015A418(world, 0x104, msg->a8.h.lo, scope);
        Thing_12D5D0* b;
        void* link;
        if (a == 0) {
            break;
        }
        b = func_0015A418(world, 0x104, msg->a8.h.hi, scope);
        link = func_001B6388(a, b);
        if (link == 0) {
            link = func_001B6290(a, b, msg->aC.h.lo, 1);
        }
        func_001B64D8(link, msg->aC.h.lo);
        break;
    }
    case 47: {
        void* link = 0;
        void* scope = self->fC;
        if (scope == 0) {
            scope = self->owner;
        }
        Thing_12D5D0* a = func_0015A448(world, msg->a8.i, scope);
        if (a != 0) {
            link = func_001B6388(a, func_0015A448(world, msg->aC.i, scope));
        }
        if (link != 0) {
            func_001B6438(link);
        }
        break;
    }
    case 48: {
        Info_12D5D0* in = (Info_12D5D0*)msg->a8.p;
        void* scope = self->fC ? self->fC : (void*)owner;
        Thing_12D5D0* t = func_0015A418(world, 0x104, in->f0, scope);
        if (t == 0) {
            break;
        }
        u.req.flags = 0;
        if (in->f4 != -1) {
            Thing_12D5D0* s = func_0015A418(world, 4, in->f4, scope);
            if (s != 0) {
                if (func_001300E8(s, 2) != 0) {
                    u.req.f4 = s;
                    u.req.flags |= 1;
                } else if (func_001300E8(s, 0x7E) != 0) {
                    u.req.flags |= 4;
                    func_001920B0(s, &u.req.buf);
                } else if (func_001300E8(s, 0x73) != 0) {
                    u.req.flags |= 4;
                    func_001F3BD8(s, &u.req.buf);
                }
            }
        }
        if (u.req.flags == 0) {
            if (t->f18 != 0 && func_00182FC8(t->f18) != 0) {
                u.req.flags |= 1;
                u.req.f4 = t->f18;
            } else {
                u.req.flags |= 4;
                func_001F3BD8(t, &u.req.buf);
            }
        }
        if (in->f8 != -1) {
            Thing_12D5D0* s = func_0015A418(world, 4, in->f8, scope);
            if (s != 0) {
                u.req.f38 = s;
                u.req.flags |= 0x20;
            }
        }
        if (in->fC != 1.0f) {
            u.req.flags |= 0x18;
            u.req.f30 = in->fC;
        }
        ((VFnP_12D5D0)t->vt[31])(t, &u.req);
        break;
    }
    case 49:
        func_001DDB58(world);
        break;
    case 50:
        func_001DDBB8(world);
        break;
    case 51:
        func_0018F0E8(D_00269A00, msg->a8.i);
        break;
    case 52:
        ((VFnP_12D5D0)D_00272E08.vt[17])(&D_00272E08, &self->f14);
        func_0014AEA0(&D_00272E08, msg->aC.h.lo, (f32)msg->a8.h.lo, (f32)msg->a8.h.hi);
        break;
    case 53:
        ((VFnP_12D5D0)D_00272E08.vt[17])(&D_00272E08, 0);
        func_0014AF10(&D_00272E08);
        break;
    case 54:
        func_0014AF38(&D_00272E08, msg->a8.h.lo, msg->aC.i, (f32)msg->a8.h.hi * 0.00390625f);
        break;
    case 55:
    {
        u8* sys = D_00275BC0;
        ((Word_12D5D0*)(sys + 0x30))->v = 0;
        func_001E96F8(sys, 0);
    }
        break;
    case 56:
    {
        u8* sys = D_00275BC0;
        *(s32*)(sys + 0x30) = 1;
        func_001E96F8(sys, 1);
    }
        break;
    case 57:
        func_001DDAB8(world, msg->a8.f);
        break;
    case 58:
        func_001DDAC8(world, msg->a8.f);
        break;
    case 59: {
        Thing_12D5D0* t = func_0015A418(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t != 0) {
            func_0017CE20(t, D_00262E10);
        }
        break;
    }
    }
}

struct Range_12E968 { u32 field0; f32 minimum; f32 maximum; };
struct Obj_12E968 { u8 pad0[8]; Range_12E968* range; };

f32 func_0012E968(Obj_12E968* self, f32 value)
{
    Range_12E968* range = self->range;
    f32 r;
    if (value < range->minimum) {
        r = 1.0f;
    } else if (range->maximum <= value) {
        r = 0.15f;
    } else {
        r = (value - range->maximum) / (range->minimum - range->maximum);
        r = r * 0.85f + 0.15f;
    }
    return r;
}

struct Ptr_12FE70 { u8 pad[0x4]; };
struct Obj_12FE70 {
    s32 f0;
    Ptr_12FE70* f4;
    Ptr_12FE70* f8;
    s32 fC;
    s32 f10;
    s32 f14;
    u8 pad1[4];
    s32 f1C;
    u8 pad2[4];
    s32 f24;
};

s32 func_0012FF10(Obj_12FE70* self);
void func_001F8DB8(Ptr_12FE70* p, s32 a, s32 b);
void func_00140CC8(Ptr_12FE70* p, s32 n, s32 base);

void func_0012FE70(Obj_12FE70* self)
{
    if (func_0012FF10(self) != 0) {
        return;
    }
    s32 size = self->f24;
    if (size == 0) {
        return;
    }
    s32 clamp = 0x4000;
    if (!(size > 0x3FFF)) {
        clamp = size;
    }
    s32 base = self->f14;
    if (self->f1C == base) {
        base += 0x4000;
    }
    self->fC = clamp;
    self->f10 = base;
    switch (self->f0) {
    case 0:
        func_001F8DB8(self->f4, base, clamp);
        break;
    case 1:
        func_00140CC8(self->f8, (s32)((u32)(clamp + 0x7FF) >> 11), base);
        break;
    }
}

struct Key_12D4A8 {
    f32 time;
    u8 pad[12];
};

struct Track_12D4A8 {
    u8 pad[0x5C];
    s32 count;
    Key_12D4A8* keys;
};

struct Cursor_12D4A8 {
    u8 pad0[8];
    Track_12D4A8* track;
    u8 pad0C[8];
    f32 time;
    f32 rate;
    u32 pad1C;
    s32 index;
};

void func_0012D4A8(Cursor_12D4A8* self)
{
    Track_12D4A8* track = self->track;
    s32 n = track->count;
    s32 i;
    if (n == 0) {
        return;
    }
    if (self->rate >= 0.0f) {
        i = 0;
        if (n > 0) {
            Key_12D4A8* keys = track->keys;
            for (i = 0; i < track->count; i++) {
                if (keys[i].time >= self->time) {
                    break;
                }
            }
        }
        self->index = i;
    } else {
        for (i = n - 1; i >= 0; i--) {
            Key_12D4A8* k = &track->keys[i];
            if (k->time <= self->time) {
                break;
            }
        }
        self->index = i + 1;
    }
}

struct Rec_12CBE8 {
    u32 f0;
    s32 f4;
    s32 f8;
    u32 fC;
};

struct Obj_12CBE8 {
    u8 pad0[0x54];
    s32 f54;
    Rec_12CBE8* f58;
    s32 f5C;
    Rec_12CBE8* f60;
    s32 f64;
    Rec_12CBE8* f68;
};

Rec_12CBE8* func_0012CBE8(Obj_12CBE8* self, s32 key) {
    s32 i;
    Rec_12CBE8* p;
    for (i = 0; i < self->f54; i++) {
        p = &self->f58[i];
        if (p->f4 == 0x27 && p->f8 == key) {
            return p;
        }
    }
    for (i = 0; i < self->f5C; i++) {
        p = &self->f60[i];
        if (p->f4 == 0x27 && p->f8 == key) {
            return p;
        }
    }
    for (i = 0; i < self->f64; i++) {
        p = &self->f68[i];
        if (p->f4 == 0x27 && p->f8 == key) {
            return p;
        }
    }
    return 0;
}

struct Iter_12F8C8 { List01* list; u8* link; s32 offset; Iter_12F8C8* saved; };

struct Next_12F8C8 {
    static C02* Of(Iter_12F8C8* it)
    {
        C02* obj = *(C02**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_12F8C8 {
    static void Of(Iter_12F8C8* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_12F8C8*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00124A48(C02* self);
s32 func_0015A448(void* world, s32 b, C02* c);
s32 func_001300E8(void* n, s32 kind);

void func_0012F8C8(C34* self)
{
    func_00124A48(self);
    if (self->id != -1) {
        self->id = func_0015A448(self->world, self->id, self);
        self->mode = 2;
        return;
    }
    Iter_12F8C8 it;
    Begin_12F8C8::Of(&it, &self->children);
    C02* n = Next_12F8C8::Of(&it);
    if (n == 0 || func_001300E8(n, 0x7E) == 0) {
        D_0027B314 = (ListFrame*)it.saved;
        return;
    }
    if (Next_12F8C8::Of(&it) != 0) {
        D_0027B314 = (ListFrame*)it.saved;
        return;
    }
    func_00128018(self, 0, (u8*)n + 0x40, &self->pos);
    self->mode = 1;
    n->desc->m03(n);
    D_0027B314 = (ListFrame*)it.saved;
}

struct Entry_12E5D0 {
    f32 key;
    s32 a4;
    s32 a8;
    s32 aC;
};

struct List_12E5D0 {
    u8 pad0[0x5C];
    s32 count;
    Entry_12E5D0* entries;
};

struct Self_12E5D0 {
    u8 pad0[0x14];
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    s32 idx;
};

void func_0012D5D0(Self_12E5D0* self, Entry_12E5D0* entry, s32* out);

void func_0012E5D0(Self_12E5D0* self, List_12E5D0* list, s32* out)
{
    if (list->count == 0) return;
    for (;;) {
        if (self->idx < list->count) {
            if (list->entries[self->idx].key < self->f14 || (self->f14 == list->entries[self->idx].key && 0.0f < self->f18)) {
                Entry_12E5D0* e = &list->entries[self->idx];
                self->idx = self->idx + 1;
                func_0012D5D0(self, e, out);
                if (*out != 0) return;
                continue;
            }
        }
        if (self->idx <= 0) return;
        if (self->f14 < list->entries[self->idx - 1].key || (self->f14 == list->entries[self->idx - 1].key && self->f18 < 0.0f)) {
            self->idx = self->idx - 1;
            func_0012D5D0(self, &list->entries[self->idx], out);
            if (*out != 0) return;
            continue;
        }
        return;
    }
}

struct Pair_12C288 { s32 key; struct Host_12C288* val; };
struct Host_12C288 {
    u8 pad0[0x18]; Host_12C288* parent;
    u8 pad1[0x50 - 0x1C]; Host_12C288* root;
    u8 pad2[0x2C8 - 0x54]; u64 flags;
};
struct Node_12C288 {
    u8 pad0[0x10]; s32 f10 : 8; s32 f11 : 8; s32 f12 : 8; s32 f13 : 8; s32 f14;
    u8 pad1[0x1C - 0x18]; struct Obj_12C288* f1C;
    u8 pad2[0x28 - 0x20]; s32 f28;
};
struct Obj_12C288 {
    u8 pad0[8]; struct Self_12C288* f8; struct Self_12C288* fC;
    u8 pad1[0x14 - 0x10]; f32 f14;
    u8 pad2[0x1C - 0x18]; f32 f1C;
    u8 pad3[0x44 - 0x20]; u8 f44[0x10];
    u8 f54[8]; s32 f5C; Host_12C288** f60;
};
struct Item_12C288 { u8 pad[0x10]; };
struct Self_12C288 {
    u8 pad0[0x14]; C6C* world;
    u8 pad1[0x38 - 0x18]; s32 nelems; Track83* elems;
    u8 pad2[0x4C - 0x40]; s32 f4C; s32 f50; s32 nitems; Item_12C288* items;
    u8 pad3[0x6C - 0x5C]; u8 f6C[0xC]; s32 f78; f32 f7C;
    u8 pad4[0x9C - 0x80]; s32 f9C; s32 nkeys; s32* keys;
};

void func_0012F6B0(Obj_12C288* o, f32 x);
void func_00152470(u8* list, Obj_12C288* o);
void func_00152470(u8* list, Node_12C288* n);
void func_0018D608(void);
void* func_0018D658(s32 size);
Host_12C288* func_0015A418(C6C* w, s32 kind, s32 key, void* ctx);
Node_12C288* func_00128998(Host_12C288* h);
void func_001B5F28(u8* list, Node_12C288* n);
void func_001215C0(Node_12C288* n);
void func_001299E0(Host_12C288* h, Node_12C288* n);
void func_0018D6F0(void);
void func_0015F8B0(C6C* w, u8* p);
void func_0012D448(Obj_12C288* o, s32 v);
void func_0012D5D0(Obj_12C288* o, Item_12C288* item, s32* out);
void func_0012F190(Obj_12C288* o, s32 flag);
void func_0012E4E0(Obj_12C288* o, Self_12C288* self, s32* out);
void func_0012D4A8(Obj_12C288* o);
void func_001837E0(Self_12C288* self, s32 a, s32 b, Obj_12C288*** c);

void func_0012C288(Self_12C288* self, Self_12C288* alt, s32 npairs, Pair_12C288* pairs, s32 flags, Obj_12C288** out, f32 fa, f32 fb)
{
    s32 tmp;
    Obj_12C288* obj;
    Obj_12C288** pobj;
    C6C* world = self->world;
    obj = (Obj_12C288*)func_0012D3F8(world);
    if (out != 0) *out = obj;
    obj->f14 = fa;
    obj->f8 = self;
    obj->fC = alt;
    obj->f1C = self->f7C;
    func_0012F6B0(obj, fb);
    func_00152470(self->f6C, obj);
    if (self->f50 != 0) {
        func_00152470((u8*)&world->f1B70, obj);
    } else {
        func_00152470((u8*)&world->f1B64, obj);
    }
    func_0018D608();
    Self_12C288* ctx;
    if (alt == 0) ctx = self; else ctx = alt;
    Host_12C288** hosts = (Host_12C288**)func_0018D658(self->nkeys * 4);
    s32 i;
    for (i = 0; i < self->nkeys; i++) {
        hosts[i] = func_0015A418(world, 4, self->keys[i], ctx);
    }
    s32 count = self->nelems + (self->f9C != 0);
    for (s32 k = 0; k < count; k++) {
        Track83* e = &self->elems[k];
        s32 key = e->target;
        Host_12C288* h;
        s32 j;
        for (j = 0; j < npairs; j++) {
            if (key == pairs[j].key) {
                h = pairs[j].val;
                goto found;
            }
        }
        h = func_0015A418(world, 4, key, ctx);
        if (h == 0) {
            for (i = 0; i < self->nkeys; i++) {
                h = func_0015A418(world, 1, key, hosts[i]);
                if (h != 0) break;
            }
            if (h == 0) {
                h = func_0015A418(world, 0x104, key, ctx);
                if (h == 0) continue;
            }
        }
    found:
        Node_12C288* n = func_00128998(h);
        n->f28 = k;
        n->f1C = obj;
        n->f14 = self->f78;
        if (k >= self->nelems) {
            if (e->scale == 0 && e->morph == 0) {
                func_001B5F28((u8*)&self->world->pool1B20, n);
                continue;
            }
        } else {
            if (flags & 1) {
                n->f10 = n->f11 = 3;
            } else {
                func_001215C0(n);
            }
            if (e->pos == 0) n->f10 = -1;
            if (e->rot == 0 && e->weight == 0) n->f11 = -1;
        }
        if (e->scale != 0) n->f12 = 2;
        if (e->morph != 0) n->f13 = 2;
        func_00152470(obj->f44, n);
        func_001299E0(h, n);
        Host_12C288* r = h->root;
        if (r == 0) {
            r = h;
            while (r->parent != 0) r = r->parent;
        }
        if (!(r->flags & 0x400000000000)) {
            if ((u32)obj->f5C < 0x20) {
                r->flags |= 0x400000000000;
                obj->f60[obj->f5C++] = r;
            }
        }
    }
    func_0018D6F0();
    for (s32 j = 0; j < obj->f5C; j++) {
        obj->f60[j]->flags &= ~0x400000000000;
    }
    func_0015F8B0(world, obj->f54);
    if (self->f4C != 0) func_0012D448(obj, 1);
    tmp = 0;
    for (s32 m = 0; m < self->nitems; m++) {
        func_0012D5D0(obj, &self->items[m], &tmp);
    }
    func_0012F190(obj, flags & 4);
    if (flags & 2) {
        func_0012E4E0(obj, self, &tmp);
    } else {
        func_0012D4A8(obj);
    }
    pobj = &obj;
    func_001837E0(self, 9, 1, &pobj);
}

extern const u8 D_00217410[];
extern const Head_2197B8 D_002197B8 = { D_00217410, 0x92 };
