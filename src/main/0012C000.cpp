// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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
    s32 scratch[4];
    Node_12D570* n = a0->head;
    while (n) {
        if (func_001833F0(n->item, a1)) return n;
        n = n->next;
    }
    (void)scratch;
    return 0;
}

struct Node_12F190 { u8 pad[0x20]; Node_12F190* next; };
struct Obj_12F190 { u8 pad[0x44]; Node_12F190* head; };

void func_00121648(void* n, void* b);

void func_0012F190(Obj_12F190* a0, void* a1)
{
    s32 scratch[4];
    Node_12F190* n = a0->head;
    while (n) {
        func_00121648(n, a1);
        n = n->next;
    }
    (void)scratch;
}

struct Mid_12F7E0 { u8 pad[0x14]; void* p14; };
struct Obj_12F7E0 { u8 pad[8]; Mid_12F7E0* mid; };

void func_001831E8(void* a, void* b, void* c, s32 d);

void func_0012F7E0(Obj_12F7E0* a0, void* a1, s32 a2)
{
    func_001831E8(a0->mid->p14, (u8*)a0 + 0xE4, a1, a2);
}

struct Obj_12FCB0 { u8 pad[0x554]; s32 count; void* items[1]; };

void func_0012FCB0(Obj_12FCB0* a0, void* a1)
{
    a0->items[a0->count++] = a1;
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

struct Kin_0012C160 {
    f32 pos;
    f32 vel;
    f32 acc;
};

struct Track_0012C160 {
    u8 pad0[0x14];
    void* host;
    u8 pad1[0x30];
    s32 enabled;
    u8 pad2[0x34];
    Kin_0012C160 kin;
    u8 pad3[4];
    f32 lo;
    f32 hi;
    f32 out;
};

struct Step_002623C8 {
    u8 pad0[0xC];
    f32 dt;
};

extern Step_002623C8* D_002623C8;

void func_00182C58(void* self);
void func_0012C208(void* self);
void func_001DBC60(void* host, void* cb, void* ctx, s32 a3, s32 a4);

void func_0012C160(Track_0012C160* self)
{
    func_00182C58(self);
    Kin_0012C160* k = &self->kin;
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
        func_001DBC60(self->host, (void*)func_0012C208, self, 0, 0);
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
    s32 scratch[4];
    (void)scratch;
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

struct Sub_0012F0A0 { u8 pad[0x34]; f32 f34; };
struct Obj_0012F0A0 { u8 pad0[0x8]; Sub_0012F0A0* sub; u8 pad1[0x8]; f32 value; };

void func_0012F6B0(Obj_0012F0A0* self, f32 x);
void func_0012F190(Obj_0012F0A0* self, s32 zero);
void func_0012F1D8(Obj_0012F0A0* self);
void func_0012E4E0(Obj_0012F0A0* self, Sub_0012F0A0* sub, s32* out);
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
        base = self->sub->f34;
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
    s32 scratch[4];
    (void)scratch;
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
struct Entry_12F810 { u8 pad[0x44]; void* p44; };

void func_001831E8(void* a, void* b, void* c, void* d);

void func_0012F810(Obj_12F810* a0, Entry_12F810** a1)
{
    func_001831E8(a0->mid->p14, (u8*)a0 + 0xE4, (*a1)->p44, a1);
}

struct Obj_12F840 { u8 pad[0x590]; s32 f590; };

void func_001B7968(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_0012F840(Obj_12F840* self)
{
    func_001B7968(self);
    func_001B9AE0(self, 3, 0, 3, 0);
    self->f590 = -1;
}

struct Self_12F888 {
    u8 pad0[0x14];
    void* f14;
    s32 f18;
};

void func_001BA130(void* self);
void func_00138F28(void* a, void* b);

void func_0012F888(Self_12F888* self)
{
    func_001BA130(self);
    if (self->f18 == 0) {
        func_00138F28(self->f14, self);
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

struct Obj_0012FCD0 { u8 pad[0x568]; s32 count; s32 values[1]; };
void func_0012FCD0(Obj_0012FCD0* obj, s32 value) { obj->values[obj->count++] = value; }

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

struct State_0012FCF0 { s32 w[11]; };

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
struct Table_12CCE8 { u8 pad[0x38]; s32 count; u8* items; };
void* func_0012CCE8(Table_12CCE8* self, void* key)
{
    for (s32 i = 0; i < self->count; i++) {
        Entry_12CCE8* e = (Entry_12CCE8*)(self->items + i * 0x1C);
        if (func_001833F0(key, e->key) != 0) {
            return e;
        }
    }
    return 0;
}

struct Set_12FA88 {
    u8 pad0[0x550];
    s32 flag550;
    s32 count554;
    s32 items558[4];
    s32 count568;
    s32 items56C[1];
};

s32 func_001B8A08(void* self, void* key);
s32 func_001833F0(void* key, s32 item);
s32 func_001300E8(void* key, s32 kind);

s32 func_0012FA88(Set_12FA88* self, void* key)
{
    s32 hit;
    s32 i;
    s32 j;

    if (func_001B8A08(self, key) != 0) {
        return 1;
    }
    for (i = 0; i < self->count554; i++) {
        if (func_001833F0(key, self->items558[i]) != 0) {
            break;
        }
    }
    if (i < self->count554) {
        hit = 1;
        goto tail;
    }
    for (j = 0; j < self->count568; j++) {
        if (func_001300E8(key, self->items56C[j]) != 0) {
            break;
        }
    }
    hit = j < self->count568;
tail:
    if (self->flag550 != 0) {
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

struct Pool_12D3F8 { u8 pad[4]; };
struct Obj_12D3F8 { void* vt; u8 pad[0x5C]; };
struct Buf_12D3F8 { u8 pad[4]; };
extern u8 D_002197B8[];
void* func_001B5EE0(Pool_12D3F8* pool);
void func_00152438(Buf_12D3F8* self, s32 value);

Obj_12D3F8* func_0012D3F8(Pool_12D3F8* pool)
{
    Obj_12D3F8* o = (Obj_12D3F8*)func_001B5EE0((Pool_12D3F8*)((u8*)pool + 0x1B58));
    o->vt = D_002197B8;
    func_00152438((Buf_12D3F8*)((u8*)o + 0x44), 0x20);
    *(void**)((u8*)o + 0x60) = (u8*)o + 0x64;
    return o;
}

struct Quad_12F9B8 { s32 a, b, c, d; };
struct Mobj_12F9B8;
struct Vt_12F9B8 {
    u8 p0[0x84];
    void (*m84)(Mobj_12F9B8* self, void* a);
    u8 p1[0x90 - 0x88];
    void (*m90)(Mobj_12F9B8* self, void* a);
    void (*m94)(Mobj_12F9B8* self, void* a);
};
struct Mobj_12F9B8 { Vt_12F9B8* vt; };
struct Node_12F9B8 { u8 p0[0x18]; Mobj_12F9B8* f18; };
struct Obj_12F9B8 {
    u8 p0[0x580];
    s32 f580;
    u8 p1[0x590 - 0x584];
    Node_12F9B8* f590;
    u8 p2[0x5A0 - 0x594];
    Mobj_12F9B8* f5A0;
    Mobj_12F9B8* f5A4;
};

void func_001B93F8(Obj_12F9B8* self);
void func_00128018(Mobj_12F9B8* a, s32 b, void* c, Quad_12F9B8* d);

extern u8 D_00248D30[];

void func_0012F9B8(Obj_12F9B8* self)
{
    Quad_12F9B8 loc;
    Mobj_12F9B8* cur;
    func_001B93F8(self);
    if (self->f5A0 != 0) {
        self->f5A0->vt->m90(self->f5A0, D_00248D30);
        self->f5A0->vt->m94(self->f5A0, D_00248D30);
        switch (self->f580) {
        case 1:
            self->f5A0->vt->m84(self->f5A0, &self->f590);
            break;
        case 2: {
            Node_12F9B8* node = self->f590;
            func_00128018(node->f18, 0, (u8*)node + 0x40, &loc);
            self->f5A0->vt->m84(self->f5A0, &loc);
            break;
        }
        }
        cur = self->f5A0;
        self->f5A0 = 0;
        self->f5A4 = cur;
    }
}

struct Item_12E760 { s32 w[4]; };
struct Sub_12E760 {
    u8 pad0[0x14];
    u8* f14;
    u8 pad1[0x38];
    s32 f50;
    u8 pad54[0x10];
    s32 cnt64;
    Item_12E760* f68;
    u8 f6C[1];
};
struct Vt_12E760 { void* pad[2]; void (*fn8)(void* self, s32 a); };
struct Elem_12E760 { Vt_12E760* vt; };
struct Obj_12E760 {
    u8 pad0[8];
    Sub_12E760* f8;
    u8 padC[0x38];
    s32 f44;
    u8 pad48[8];
    s32 f50;
    u8 pad54[0x90];
    s32 fE4;
};
struct Frame_12E760 { s32 f00; s32 f04; s32 f08; s32 f0C; };
struct Tmp_12E760 { s32 a; s32 b; };

extern u8 D_0027B314[];
void func_0012D5D0(Obj_12E760* self, Item_12E760* item, Tmp_12E760* out);
void func_0012F760(Obj_12E760* self, s32 a, Obj_12E760* b);
void func_001DBC18(u8* self, s32 node);
void func_0015F9A0(u8* a, Obj_12E760* s);
void func_0012D448(Obj_12E760* self, s32 v);
void func_001DBD40(u8* a, s32 b, s32 c, Obj_12E760* d, s32 e, s32 f);
void func_00152600(u8* a, Obj_12E760* b);
void func_00152470(u8* a, Obj_12E760* b);
void func_001BF718(s32* slot);
void func_001837E0(Sub_12E760* self, s32 a, s32 b, s32* c);

void func_0012E760(Obj_12E760* self)
{
    Frame_12E760 fr;
    Tmp_12E760 tmp;
    s32 i = 0;
    Sub_12E760* sub = self->f8;
    u8* base = sub->f14;
    for (i = 0; i < sub->cnt64; i++) {
        Item_12E760* it = (Item_12E760*)((u8*)sub->f68 + i * 16);
        tmp.a = 0;
        func_0012D5D0(self, it, &tmp);
    }
    func_0012F760(self, 6, self);
    func_001DBC18(base, self->fE4);
    self->fE4 = 0;
    func_0015F9A0(base, (Obj_12E760*)((u8*)self + 0x54));
    func_0012D448(self, 0);
    func_001DBD40(base, 2, 0, self, -1, 0);
    func_00152600(sub->f6C, self);
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
    fr.f0C = *(s32*)D_0027B314;
    *(s32*)D_0027B314 = (s32)&fr;
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
    *(s32*)D_0027B314 = fr.f0C;
}

struct Lim_12E9E0 {
    u8 pad0[0x34];
    f32 lim;
    u8 pad1[0xC];
    s32 mode;
};
struct Obj_12E9E0 {
    u8 pad0[8];
    Lim_12E9E0* l;
};

f32 func_002058A0(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);

s32 func_0012E9E0(Obj_12E9E0* o, f32* pos, f32* vel)
{
    s32 r = 0;
    Lim_12E9E0* l = o->l;
    f32 x = *pos;
    f32 lim = l->lim;
    if (lim <= x) {
        switch (l->mode) {
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
                if (*pos < l->lim) flag = 0;
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
        switch (l->mode) {
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
                if (l->lim <= q) {
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

struct Elem_12D2A8 { u64 q0 __attribute__((packed)); u64 q1 __attribute__((packed)); u64 q2 __attribute__((packed)); s32 w3; };
struct Self_12D2A8 { u8 pad0[0x38]; s32 f38; Elem_12D2A8* f3C; u8 pad1[0x9C - 0x40]; Elem_12D2A8* f9C; };

void func_001F5B08(Elem_12D2A8* dst, Elem_12D2A8* src, s32 bytes);

void func_0012D2A8(Self_12D2A8* self, Elem_12D2A8* p)
{
    Elem_12D2A8 tmp = *p;
    s32 idx = p - self->f3C;
    self->f38 = self->f38 - 1;
    if (idx < self->f38) {
        func_001F5B08(p, p + 1, (self->f38 - idx) * 0x1C);
    }
    p = self->f3C + self->f38;
    *p = tmp;
    self->f9C = p;
}
