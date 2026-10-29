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
void func_002032C8(s32 x);
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
