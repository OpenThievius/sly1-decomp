// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1389C8 { u8 pad[0x1AEC]; s32 field; };

void func_001389C8(Obj_1389C8* a0)
{
    a0->field = 0;
}

struct Node_138BE0 { u8 pad[0x4B8]; u32 flags; };
struct Owner_138BE0 { u8 pad[0x50]; Node_138BE0* node; };

void func_00138BE0(void* a0, Owner_138BE0* owner, u32 mask)
{
    Node_138BE0* n = owner->node;
    if (n) {
        n->flags &= ~mask;
    }
}

struct Sub_139B38 { u8 pad[0x18]; s32 flag; };
struct Owner_139B38 { u8 pad[8]; Sub_139B38* sub; };

void* func_0012CCE8(void);

void func_00139B38(void)
{
    Owner_139B38* o = (Owner_139B38*)func_0012CCE8();
    if (o) {
        if (o->sub) {
            o->sub->flag = 1;
        }
    }
}

extern u8 D_00261314[];
extern u8 D_00261318[];

void func_00139B70(s32 idx, void* arg);

void func_00139C38(void)
{
    func_00139B70(1, D_00261314);
    func_00139B70(2, D_00261318);
}

struct Sub_139C70 { u8 pad[0x1088]; void* p1088; struct Obj_139C70* owner; };
struct Obj_139C70 { u8 pad0[0x14]; u8* ctx; u8 pad1[0x320 - 0x18]; s32 mode; };

void* func_001B5EA0(void* p);
void func_001B5F28(void* p, void* q);
void func_001F5C0C(void* p, s32 v, s32 n);
void func_00152470(void* list, void* item);

Sub_139C70* func_00139C70(Obj_139C70* o)
{
    Sub_139C70* s = (Sub_139C70*)func_001B5EA0(o->ctx + 0x1B40);
    if (!s) {
        return 0;
    }
    func_001F5C0C(s, 0, 0x10C0);
    if (o->mode != 2) {
        s->owner = o;
    } else {
        void* r = func_001B5EA0(o->ctx + 0x1B4C);
        s->p1088 = r;
        if (r) {
            func_001F5C0C(r, 0, 0x580);
            s->owner = o;
        } else {
            func_001B5F28(o->ctx + 0x1B40, s);
            return 0;
        }
    }
    func_00152470((u8*)o + 0x624, s);
    return s;
}

struct Sub_139D28 { u8 pad[0x108C]; struct Obj_139D28* owner; };
struct Obj_139D28 { u8 pad[0x1]; };

extern u8 D_002622F0[];
void func_00152600(void* list, void* item);
void func_00152470(void* list, void* item);

void func_00139D28(Sub_139D28* o)
{
    func_00152600((u8*)o->owner + 0x624, o);
    func_00152470(D_002622F0, o);
}

struct Rec_138278 { s32 a; Rec_138278* b; Rec_138278* c; };
struct Table_138278 { s32 count; s32 y; Rec_138278* recs; };
struct In_138278 { u8 pad0[0x10]; s32 base; };

s32 func_00137BE0(void* self);
void* func_0018D5C0(s32 size);

void func_00138278(void* self, In_138278* in, Table_138278* out)
{
    s32 x = func_00137BE0(self);
    out->count = x;
    s32 y = func_00137BE0(self);
    out->y = y;
    out->recs = (Rec_138278*)func_0018D5C0(12 * out->count);
    for (s32 i = 0; i < out->count; i++) {
        Rec_138278* e = out->recs + i;
        s32 v = func_00137BE0(self);
        e->a = in->base + (v << 5);
        s32 w = func_00137BE0(self);
        if ((w & 0xFFFF) != 0xFFFF) {
            e->b = out->recs + w;
        }
        s32 z = func_00137BE0(self);
        if ((z & 0xFFFF) != 0xFFFF) {
            e->c = out->recs + z;
        }
    }
}

struct Actor_A418 {
    u8 pad0[0x80];
    f32 level;
    u8 pad1[0x2C8 - 0x84];
    u64 bits;
    void* owner;
};

struct Src_A418 {
    u8 pad0[0x80];
    f32 level;
    u8 pad1[0x314 - 0x84];
    u8 sub[0x10];
};

void func_001832F0(Actor_A418* self, Src_A418* src);
s32 func_001300E8(Src_A418* src, s32 kind);
s32 func_00152720(void* sub);

void func_0013A418(Actor_A418* self, Src_A418* src)
{
    func_001832F0(self, src);
    if (func_001300E8(src, 0x50) != 0) {
        self->owner = src;
        self->level = src->level;
        if (func_00152720(src->sub) == 0) {
            self->bits &= 0xFFFFFFFFF3FFFFFFULL;
            self->bits &= 0xFFFFFFFFCFFFFFFFULL;
        }
    }
}

void* func_001387C0(void* self, void* other);

s32 func_001387F8(void* self, void* other)
{
    s32* p = (s32*)func_001387C0(self, other);
    s32 r = 0;
    if (p != 0) {
        r = *p;
    }
    return r;
}

struct Slot_138828 {
    s32 flag;
    void* owner;
    void* link;
};

struct Table_138828 {
    u8 pad0[0x38];
    s32 count;
    u8 pad1[0x1AD8 - 0x3C];
    u8* items;
};

void func_001389C8(void* self);

void func_00138828(void* self, void* arg)
{
    Table_138828* t = (Table_138828*)self;
    s32 stride = 24;
    s32 one = 1;
    u8* a3 = (u8*)arg + 0x430;
    u8* a2 = (u8*)arg + 0x420;
    s32 off = 0;
    s32 n = 2;
    do {
        n--;
        Slot_138828* e = (Slot_138828*)(t->items + off + t->count * stride);
        off += 0x1800;
        e->link = a2;
        e->flag = 0;
        e->owner = arg;
        a2 += 4;
        e++;
        e->link = a3;
        e->owner = arg;
        e->flag = one;
        a3 += 4;
    } while (n >= 0);
    func_001389C8(self);
}

struct Owner_139E80 {
    u8 pad0[0x14];
    u8* sub;
};

void func_00152600(void* sub, void* self);
void func_00152470(void* sub, void* self);
void func_001240F8(void* self);

void func_00139E80(void* self)
{
    Owner_139E80* o = (Owner_139E80*)self;
    func_00152600(o->sub + 0x1CC0, self);
    func_00152470(o->sub + 0x1CB4, self);
    func_001240F8(self);
}

struct Offset_13BE00 { u8 pad[0x554]; f32 value; };

extern f32 D_0026185C;

void func_0013BE00(Offset_13BE00* self, f32 delta)
{
    self->value = D_0026185C + delta;
}

void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);

void func_0013B598(void* self)
{
    func_001BAC30(self);
    func_00159478((u8*)self + 0x5BC, self);
}

s32 func_00137BE0(void* src);
void func_00137A60(void* self, s32 size, void* obj);

void func_00138518(void* self)
{
    s32 n = func_00137BE0(self);
    func_00137A60(self, n, 0);
}

struct Range_138550 {
    s32 w[8];
};

void func_00137A60(void* self, s32 size, void* obj);
u32 func_0018D568(s32 size, void* src);

void func_00138550(void* self, u32* out)
{
    Range_138550 r;
    func_00137A60(self, 0x20, &r);
    if (r.w[1] != r.w[7]) {
        *out = func_0018D568(0x20, &r);
    } else {
        *out = 0;
    }
}

struct Node_138738 { s32 a0; Node_138738* next; void* a8; s32 value; };
struct List_138738 { Node_138738* head; };
struct Src_138738 { u8 pad0[4]; s32 value4; };
struct Self_138738 { u8 pad0[0x1AF0]; };

void* func_001B5EC0(void* pool);

Node_138738* func_00138738(Self_138738* self, List_138738* list, Src_138738* src)
{
    Node_138738* n = (Node_138738*)func_001B5EC0((u8*)self + 0x1AF0);
    n->a0 = 0;
    n->value = src->value4;
    n->next = list->head;
    list->head = n;
    return n;
}

struct Node_1387C0 { s32 a0; Node_1387C0* next; s32 a8; s32 key; };
struct Chain_1387C0 { Node_1387C0* first; };
struct Owner_1387C0 { u8 pad0[0x480]; Chain_1387C0* chain; };
struct Self_1387C0 { u8 pad0[0x50]; Owner_1387C0* owner; };
struct Other_1387C0 { u8 pad0[0x50]; s32 key; };

void* func_001387C0(Self_1387C0* self, Other_1387C0* other)
{
    Node_1387C0* cur = self->owner->chain->first;
    s32 key = other->key;
    if (cur != 0) {
        do {
            if (cur->key != key) {
                cur = cur->next;
            } else {
                return cur;
            }
        } while (cur != 0);
    }
    return 0;
}

void* func_0018D500(s32 size);
void func_001384A0(void* self, u8** out)
{
    s32 size = func_00137BE0(self);
    u8* buffer = (u8*)func_0018D500(size + 1);
    func_00137A60(self, size, buffer);
    buffer[size] = 0;
    *out = buffer;
}

struct Key_00138788 { s32 unused; s32 key; };
Node_1387C0* func_00138788(void* unused, Node_1387C0** head, Key_00138788* key)
{
    Node_1387C0* node = *head;
    s32 wanted = key->key;
    while (node) {
        if (node->key == wanted) {
            *head = node->next;
            break;
        }
        head = &node->next;
        node = node->next;
    }
    return node;
}

struct State_0013B5C8 { u8 pad[0x680]; void* slot; };
void func_001BA130(void* self, void* other);
void func_0013B5C8(State_0013B5C8* self, State_0013B5C8* other)
{
    func_001BA130(self, other);
    if (other->slot) self->slot = (void*)func_0018D568(0x24, other->slot);
}
