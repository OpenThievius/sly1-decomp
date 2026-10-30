// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Data_1B4BC8 { u8 pad0[0x20]; s32 count; };
struct Node_1B4BC8 {
    u8 pad0[0x10]; s32 flags; Data_1B4BC8* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B4AD0(void* p);
f32 func_001EAAE0(f32 a, f32 b);

void func_001B4BC8(Node_1B4BC8* p)
{
    func_001B4AD0(p);
    if (p->data != 0) {
        f32 a = func_001EAAE0(p->f2C, p->f30);
        p->f3C = (f32)p->data->count / a;
        f32 b = func_001EAAE0(p->f34, p->f38);
        p->f44 = b;
        p->f48 = b;
    }
}

struct Data_1B4D18 { u8 pad0[0x20]; s32 count; };
struct Node_1B4D18 {
    u8 pad0[0x10]; s32 flags; Data_1B4D18* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

f32 func_001B4D18(Node_1B4D18* p)
{
    return (p->f40 / p->f3C) / ((f32)p->data->count / p->f3C + p->f44);
}

struct Data_1B4D48 { u8 pad0[0x20]; s32 count; };
struct Node_1B4D48 {
    u8 pad0[0x10]; s32 flags; Data_1B4D48* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};
struct Src_1B4D48 { u8 pad0[4]; f32 f4; f32 f8; f32 fC; f32 f10; u16 u14; };

void func_001B4AA0(void* a, void* b);

void func_001B4D48(Node_1B4D48* p, Src_1B4D48* s)
{
    func_001B4AA0(p, s);
    p->f2C = s->f4;
    p->f30 = s->f8;
    p->f34 = s->fC;
    p->f38 = s->f10;
    p->f40 = (f32)s->u14;
}

struct Data_1B4F18 { u8 pad0[0x20]; s32 count; };
struct Node_1B4F18 {
    u8 pad0[0x10]; s32 flags; Data_1B4F18* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

f32 func_001B4F18(Node_1B4F18* p)
{
    f32 x = p->f3C;
    f32 a;
    if (x < 0.0f) {
        x = -x;
        a = (f32)(p->data->count << 1) - p->f40;
    } else {
        a = p->f40;
    }
    return (a / x) / ((f32)(p->data->count << 1) / x + p->f44);
}

struct Data_1B4F80 { u8 pad0[0x20]; s32 count; };
struct Node_1B4F80 {
    u8 pad0[0x10]; s32 flags; Data_1B4F80* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};
struct Src_1B4F80 { u8 pad0[4]; f32 f4; f32 f8; f32 fC; f32 f10; u16 u14; };

void func_001B4AA0(void* a, void* b);

void func_001B4F80(Node_1B4F80* p, Src_1B4F80* s)
{
    func_001B4AA0(p, s);
    p->f2C = s->f4;
    p->f30 = s->f8;
}

struct Data_1B5108 { u8 pad0[0x20]; s32 count; };
struct Node_1B5108 {
    u8 pad0[0x10]; s32 flags; Data_1B5108* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B4AD0(void* p);

void func_001B5108(Node_1B5108* p)
{
    func_001B4AD0(p);
    if (p->data != 0) {
        s32 n = p->data->count;
        if (n >= 2) {
            p->f34 = p->f30 / (f32)n;
        }
    }
}

struct Data_1B5160 { u8 pad0[0x20]; s32 count; };
struct Node_1B5160 {
    u8 pad0[0x10]; s32 flags; Data_1B5160* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};
struct Vec2_1B5160 { f32 x; f32 y; };
struct Inner_1B5160 { u8 pad0[0x34]; s32 i34; };
struct Other_1B5160 {
    void* vt; u8 pad0[0xC]; Vec2_1B5160 vec; u8 pad1[0x60]; Inner_1B5160* p78;
};

extern u8 func_00166690[];
extern u8* D_00261990;
void func_001B4AD0(void* p);
f32 func_00205778(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);
void func_001B46E0(void* p, s32 k);

void func_001B5160(Node_1B5160* p, void* unused, Other_1B5160* q)
{
    if (p->data == 0) {
        return;
    }
    if (p->data->count < 2) {
        return;
    }
    if (*(void**)q != (void*)func_00166690) {
        return;
    }
    Vec2_1B5160* vv;
    if (q->p78->i34 != 0) {
        vv = &q->vec;
    } else {
        vv = (Vec2_1B5160*)(D_00261990 + 0x80);
    }
    f32 t = func_00205778(vv->y, vv->x);
    f32 r = func_001EAFE0(p->f2C - t, p->f30);
    s32 k = (s32)(r / p->f34);
    func_001B46E0((u8*)p + 0x10, k);
}

struct Data_1B5278 { u8 pad0[0x20]; s32 count; };
struct Node_1B5278 {
    u8 pad0[0x10]; s32 flags; Data_1B5278* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B4750(void* p, f32 a, f32 b);
f32 func_002058A0(f32 a, f32 b);

void func_001B5278(Node_1B5278* p, f32 t)
{
    if (p->data != 0) {
        f32 r1 = func_002058A0(p->f1C + p->f2C * p->f3C * t, p->f34);
        f32 r2 = func_002058A0(p->f20 + p->f30 * p->f40 * t, p->f38);
        func_001B4750((u8*)p + 0x10, r1, r2);
    }
}

struct Data_1B5388 { u8 pad0[0x20]; s32 count; };
struct Node_1B5388 {
    u8 pad0[0x10]; s32 flags; Data_1B5388* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B5388(Node_1B5388* p, f32 a, f32 b)
{
    p->f3C = a;
    p->f40 = b;
}

struct Node_1B4750 { u8 pad0[4]; s32 count; u8 pad8[4]; f32 x; f32 y; u8 pad14[4]; Node_1B4750* next; };
extern Node_1B4750* D_00274544;
extern Node_1B4750* D_0027451C;

void func_001B4750(Node_1B4750* a0, f32 a, f32 b)
{
    if (a0->count == 0) return;
    if (a0->x == a && a0->y == b) return;
    a0->x = a;
    Node_1B4750* v = a0->next;
    a0->y = b;
    if (v != 0) return;
    if (a0 == D_00274544) return;
    if (D_00274544 == 0) D_00274544 = a0;
    a0->next = D_0027451C;
    D_0027451C = a0;
}

struct Node_1B4B08 { u8 pad0[4]; f32 f; };
extern f32 D_0026185C;

s32 func_001B4B08(Node_1B4B08* a0)
{
    if (a0->f != D_0026185C) {
        a0->f = D_0026185C;
        return 1;
    }
    return 0;
}

struct Vec2_1B55A8 { f32 x; f32 y; };

void func_001B55A8(Vec2_1B55A8* a0, Vec2_1B55A8* a1)
{
    a0->x = a1->x;
    a0->y = a1->y;
}

struct Walk_1B5D80 { s32 a; u32 b; u32 c; };

void func_001B5D80(Walk_1B5D80* s, s32 v, s32 n)
{
    u32 cur = s->b;
    s->a = v;
    s->c = cur;
    for (s32 i = 1; i < n; i++) {
        u32 prev = cur;
        s32 a = s->a;
        cur = s->b + i * a;
        *(u32*)prev = cur;
    }
    *(u32*)cur = 0;
}

struct Node_1B5F28 { Node_1B5F28* link; u8 pad4[4]; Node_1B5F28* next; };

void func_001B5F28(Node_1B5F28* list, Node_1B5F28* item)
{
    if (item) {
        item->link = list->next;
        list->next = item;
    }
}

struct Table_1B6420 { u8 pad0[0x38]; u32 base; };

u32 func_001B6420(Table_1B6420* a0, s32 a1)
{
    a1 = (a1 << 3) + a0->base;
    return *(u32*)a1;
}

struct Obj_1B65F8 {
    u8 pad0[0x24];
    void* f24;
    u8 pad1[0x10];
    f32 f38;
};

void func_0012F6B0(void* p);

void func_001B65F8(Obj_1B65F8* self, f32 v)
{
    self->f38 = v;
    if (self->f24 != 0) {
        func_0012F6B0(self->f24);
    }
}

struct Slot_1B71C8 {
    void* first;
    s32 second;
};

struct Self_1B71C8 {
    u8 pad0[0xCD4];
    s32 count;
    u8 pad1[4];
    Slot_1B71C8 slots[1];
};

struct Ent_1B71C8 {
    u8 pad0[0x50];
    void* f50;
    u8 pad1[0x4E4];
    u64 f538;
};

s32 func_001300E8(void* a, s32 b);
s32 func_00182F40(Ent_1B71C8* e, void* b);

s32 func_001B71C8(Self_1B71C8* self, Ent_1B71C8* ent)
{
    if (ent->f538 & (1ULL << 43)) {
        return 0;
    }
    if (func_001300E8(ent->f50, 5) != 0) {
        return 0;
    }
    if (func_001300E8(ent->f50, 0x4C) != 0) {
        return 0;
    }
    for (s32 i = 0; i < self->count; i++) {
        if (func_00182F40(ent, self->slots[i].first) != 0) {
            return 0;
        }
    }
    return 1;
}

struct Obj_1B7920 {
    u8 pad0[0xCC0];
    void* fCC0;
};

void func_0015FCD8(Obj_1B7920* self, void* p);
void func_001BF048(void* p);

void func_001B7920(Obj_1B7920* self, void* p)
{
    func_0015FCD8(self, p);
    if (p != 0) {
        func_001BF048(self->fCC0);
        self->fCC0 = 0;
    }
}

struct Entry_1B65C8 { s32 value; s32 extra; };
struct Host_1B65C8 { u8 pad[0x38]; Entry_1B65C8* entries; };
struct Node_1B65C8 { u8 pad[0x18]; Host_1B65C8* host; u8 pad2[0x2C - 0x1C]; s32 index; };

void func_001B65C8(Node_1B65C8* self, s32* out)
{
    s32 value;
    if (self->index >= 0) {
        value = self->host->entries[self->index].value;
    } else {
        value = -1;
    }
    *out = value;
}

struct Node_1B6C68 {
    u8 pad[0x28];
    s32 f28;
    s32 index;
};

void func_001B6E28(Node_1B6C68* self, s32 a, s32 b);

void func_001B6C68(Node_1B6C68* self)
{
    func_001B6E28(self, self->f28, self->index);
    s32 v = self->index;
    self->index = -1;
    self->f28 = v;
}

struct Node_1B6CA8 {
    u8 pad[0x24];
    s32 f24;
};

void func_001B6C68(Node_1B6CA8* self);
void func_001B66A0(Node_1B6CA8* self);

void func_001B6CA8(Node_1B6CA8* self, s32 a, s32 b)
{
    if (a == 5 && b == self->f24) {
        func_001B6C68(self);
        func_001B66A0(self);
    }
}

typedef void (*VFn_1B6D78)(void* self);
struct Obj_1B6D78 { VFn_1B6D78* vtbl; };
typedef void (*Cb_1B6D78)(void* obj, s32 a, s32 b);
struct Link_1B6D78 {
    Cb_1B6D78 fn;
    void* obj;
    u8 pad[0x8];
    Link_1B6D78* next;
};
struct Node_1B6D78 {
    u8 pad[0x1C];
    Obj_1B6D78* f1C;
    u8 pad2[0x3C - 0x20];
    Link_1B6D78* f3C;
};

void func_001B6D78(Node_1B6D78* self, s32 a, s32 b)
{
    Obj_1B6D78* o = self->f1C;
    if (o != 0) {
        o->vtbl[18](o);
    }
    Link_1B6D78* link = self->f3C;
    if (link != 0) {
        do {
            void* obj = link->obj;
            Cb_1B6D78 fn = link->fn;
            link = link->next;
            fn(obj, a, b);
        } while (link != 0);
    }
}

struct Entry_1B6E28 { s32 value; s32 extra; };
struct Host_1B6E28 { u8 pad[0x38]; Entry_1B6E28* entries; };
struct Node_1B6E28 { u8 pad[0x18]; Host_1B6E28* host; };

void func_001837E0(Host_1B6E28* host, s32 a, s32 b, void** args);

void func_001B6E28(Node_1B6E28* self, s32 idx1, s32 idx2)
{
    void* args[3];
    s32 v1;
    s32 v2;
    if (idx1 >= 0) {
        v1 = self->host->entries[idx1].value;
    } else {
        v1 = -1;
    }
    if (idx2 >= 0) {
        v2 = self->host->entries[idx2].value;
    } else {
        v2 = -1;
    }
    args[0] = &self;
    args[1] = &v1;
    args[2] = &v2;
    func_001837E0(self->host, 0xE, 3, args);
}

struct Data_1B46E0 { u8 pad0[0x20]; s32 count; };
struct Node_1B46E0 {
    u8 pad0[4];
    Data_1B46E0* data;
    s32 idx;
    u8 pad1[0xC];
    Node_1B46E0* next;
};


void func_001B46E0(Node_1B46E0* a0, s32 a1)
{
    if (a0->data != 0) {
        s32 hi = a0->data->count - 1;
        if (a1 < 0) {
            a1 = 0;
        } else {
            a1 = (hi < a1) ? hi : a1;
        }
        if (a0->idx != a1) {
            Node_1B46E0* n = a0->next;
            a0->idx = a1;
            if (n == 0) {
                if ((void*)a0 != (void*)D_00274544) {
                    if (D_00274544 == 0) {
                        D_00274544 = (Node_1B4750*)a0;
                    }
                    a0->next = (Node_1B46E0*)D_0027451C;
                    D_0027451C = (Node_1B4750*)a0;
                }
            }
        }
    }
}

struct Src_1B47C0 { s32 scale; s32 base; };
struct Dst_1B47C0 { u8 pad0[4]; s32 value; };
struct Entry_1B47C0 {
    Src_1B47C0* src;
    Dst_1B47C0* dst;
    Entry_1B47C0* next;
};
struct Node_1B47C0 {
    s32 flags;
    u8 pad4[4];
    s32 idx;
    u8 pad0C[8];
    Entry_1B47C0* entries;
    Node_1B47C0* next;
};


void func_001694A0(void* p);

void func_001B47C0(void)
{
    Node_1B47C0* n = (Node_1B47C0*)D_0027451C;
    while (n != 0) {
        for (Entry_1B47C0* e = n->entries; e != 0; e = e->next) {
            if (n->flags & 1) {
                e->dst->value = e->src->base + ((n->idx * e->src->scale) << 4);
            }
            func_001694A0(e->dst);
        }
        Node_1B47C0* nx = n->next;
        n->next = 0;
        n = nx;
    }
    D_0027451C = 0;
    D_00274544 = 0;
}

typedef void (*Hook_1B4878)(void* self, f32 t);
struct Obj_1B4878 { Hook_1B4878* vt; };

extern s32 D_0027453C;
extern Obj_1B4878** D_00274540;

s32 func_001B4B08(void* p);

void func_001B4878(f32 t)
{
    for (s32 i = 0; i < D_0027453C; i++) {
        Obj_1B4878* o = D_00274540[i];
        if (func_001B4B08(o) != 0) {
            Hook_1B4878 fn = o->vt[2];
            if (fn != 0) {
                fn(o, t);
            }
        }
    }
}

typedef void (*Fn_1B4A10)(void* self, void* buf);
struct Obj_1B4A10 { void* vt; u8 pad4[4]; s32 type; };

s32 func_00137BE0(void* a);
s32 func_001B4920(s32 type);
void* func_0018D5C0(s32 size);
void* func_001B4980(s32 type);
void func_00137A60(void* owner, s32 key, void* out);

Obj_1B4A10* func_001B4A10(void* a0)
{
    s32 type = func_00137BE0(a0);
    Obj_1B4A10* result = 0;
    if (type != 0) {
        Obj_1B4A10* o = (Obj_1B4A10*)func_0018D5C0(func_001B4920(type));
        void* vt = func_001B4980(type);
        o->type = type;
        o->vt = vt;
        u32 buf[8];
        func_00137A60(a0, 0x1C, buf);
        ((Fn_1B4A10*)o->vt)[0](o, buf);
        result = o;
    }
    return result;
}

struct Node_1B5EA0 { Node_1B5EA0* next; };
struct Pool_1B5EA0 { u8 pad[8]; Node_1B5EA0* head; };

void* func_001B5EA0(Pool_1B5EA0* pool)
{
    Node_1B5EA0* n = pool->head;
    if (n != 0) {
        pool->head = n->next;
    }
    return n;
}

struct Node_1B5EC0 { Node_1B5EC0* next; };
struct Pool_1B5EC0 { u8 pad[8]; Node_1B5EC0* head; };

void* func_001B5EA0(Pool_1B5EC0* pool);

void* func_001B5EC0(Pool_1B5EC0* pool)
{
    return func_001B5EA0(pool);
}

struct Node_1B5EE0 { Node_1B5EE0* next; };
struct Pool_1B5EE0 { s32 count; u8 pad[4]; Node_1B5EE0* head; };

void* func_001B5EA0(Pool_1B5EE0* pool);
void func_001F5C0C(void* p, int zero, s32 count);

void* func_001B5EE0(Pool_1B5EE0* pool)
{
    void* p = func_001B5EA0(pool);
    func_001F5C0C(p, 0, pool->count);
    return p;
}

typedef void (*VFn_1B7A98)(void* self);
struct Sub_1B7A98 { VFn_1B7A98* vtbl; };
struct Owner_1B7A98 {
    u8 pad0[0x34];
    s32 count34;
    s32 count38;
};
struct Node_1B7A98 {
    VFn_1B7A98* vtbl;
    u8 pad0[0x14 - 4];
    Owner_1B7A98* owner;
    s32 flag18;
    u8 pad1[0x50 - 0x1C];
    Sub_1B7A98* sub50;
    u8 pad2[0x480 - 0x54];
    s32 handle480;
    u8 pad3[0x538 - 0x484];
    u64 flags538;
    s32 field540;
};

void func_00138828(void* owner, void* self);
s32 func_001DC7D0(void* owner, void* self);
void func_00138F28(void* owner, void* self);
void func_00152470(void* p, void* self);
void func_001240F8(void* self);
void func_001B7C40(void* self, s32 flag);
void func_001BB580(void* p);
void func_001BB4A0(void* self);

void func_001B7A98(Node_1B7A98* self)
{
    Owner_1B7A98* owner = self->owner;
    owner->count34++;
    if (self->flag18 == 0) {
        func_00138828(owner, self);
        self->handle480 = func_001DC7D0(owner, self);
        func_00138F28(owner, self);
        owner->count38++;
        func_00152470((u8*)owner + 0x3C, self);
    }
    func_001240F8(self);
    func_001B7C40(self, 1);
    self->vtbl[72](self);
    if (!(self->flags538 & (1ULL << 54))) {
        func_001BB580(self->sub50);
    } else {
        func_001BB580(self);
    }
    func_001BB4A0(self);
}

typedef void (*VFn_1B7B78)(void* self);
struct Sub_1B7B78 { VFn_1B7B78* vtbl; };
struct Owner_1B7B78 {
    u8 pad0[0x34];
    s32 count34;
    s32 count38;
};
struct Node_1B7B78 {
    VFn_1B7B78* vtbl;
    u8 pad0[0x14 - 4];
    Owner_1B7B78* owner;
    s32 flag18;
    u8 pad1[0x50 - 0x1C];
    Sub_1B7B78* sub50;
    u8 pad2[0x480 - 0x54];
    s32 handle480;
    u8 pad3[0x538 - 0x484];
    u64 flags538;
    s32 field540;
};

void func_001B7C40(void* self, s32 flag);
void func_001243E0(void* self);
void func_001388A0(void* owner, void* self);
void func_001DC828(void* owner, s32 handle);
void func_00152600(void* p, void* self);
void func_001DC108(void* owner, s32 value);
void func_001BB580(void* p);

void func_001B7B78(Node_1B7B78* self)
{
    Sub_1B7B78* old50 = self->sub50;
    Owner_1B7B78* owner = self->owner;
    func_001B7C40(self, 0);
    func_001243E0(self);
    owner->count34--;
    if (self->flag18 == 0) {
        func_001388A0(owner, self);
        func_001DC828(owner, self->handle480);
        owner->count38--;
        func_00152600((u8*)owner + 0x3C, self);
    }
    func_001DC108(owner, self->field540);
    u64 flags = self->flags538;
    self->field540 = 0;
    if (!(flags & (1ULL << 54)) && old50 != (Sub_1B7B78*)self) {
        func_001BB580(old50);
    }
}

typedef void (*VFn_1B7C40)(void* self);
struct Sub_1B7C40 { VFn_1B7C40* vtbl; };
struct Owner_1B7C40 { u8 pad0[1]; };
struct Node_1B7C40 {
    VFn_1B7C40* vtbl;
    u8 pad0[0x14 - 4];
    Owner_1B7C40* owner;
    u8 pad1[0x50 - 0x18];
    Sub_1B7C40* sub50;
    u8 pad2[0x538 - 0x54];
    u64 flags538;
};

void func_00138BE0(void* owner, void* self, s32 n);
void func_00152470(void* p, void* self);
void func_00152600(void* p, void* self);

void func_001B7C40(Node_1B7C40* self, s32 flag)
{
    if (flag == ((self->flags538 >> 50) & 1)) {
        return;
    }
    if (flag != 0) {
        func_00152470((u8*)self->sub50 + 0x2D8, self);
    } else {
        func_00152600((u8*)self->sub50 + 0x2D8, self);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 50)) | ((u64)(flag & 1) << 50);
    func_00138BE0(self->owner, self, 7);
    Sub_1B7C40* sub = self->sub50;
    sub->vtbl[54](sub);
}

struct Rec_1B4AA0 { u8 pad[0xC]; s32 value; s32 flags; };
struct Src_1B4AA0 { s16 first; u16 second; };

void func_001B4AA0(Rec_1B4AA0* rec, Src_1B4AA0* src)
{
    s32 old = rec->flags;
    rec->value = src->first;
    rec->flags = old | 1;
    if (src->second != 0) {
        rec->flags = old | 5;
    }
}

s32 func_001B4688(void* key);

struct Node_1B4AD0 { u8 pad[0xC]; void* key; s32 unk10; s32 result; };

void func_001B4AD0(Node_1B4AD0* node)
{
    if (node->result == 0) {
        node->result = func_001B4688(node->key);
    }
}

f32 func_001B4B38(void)
{
    return 0.0f;
}

struct Owner_1B4B48 { u8 pad[0xC]; s32 id; };
struct Key_1B4B48 { u8 pad[0x2]; s16 id; };

u8* func_001B4B48(Owner_1B4B48* owner, Key_1B4B48* key)
{
    if (key->id == owner->id) {
        return (u8*)owner + 0x10;
    }
    return 0;
}

struct Actor_1B61A8 {
    u8 pad_00[0x14];
    void* owner_14;
    u8 pad_18[0x2C];
    s32 armed_44;
};

void func_00182C58(void* self);
void func_001B61F0(void* self);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);

void func_001B61A8(Actor_1B61A8* self)
{
    func_00182C58(self);
    if (self->armed_44 != 0) {
        func_001DBCC8(self->owner_14, (void*)func_001B61F0, self, 0, 0);
    }
}

struct Pair_1B63C0 {
    s32 key_00;
    s32 value_04;
};

struct Table_1B63C0 {
    u8 pad_00[0x34];
    s32 count_34;
    Pair_1B63C0* entries_38;
};

s32 func_001B63C0(Table_1B63C0* self, s32 key)
{
    s32 count = self->count_34;
    if (count > 0) {
        Pair_1B63C0* p = self->entries_38;
        s32 i = 0;
        do {
            if (p->key_00 == key) {
                return i;
            }
            i++;
            p++;
        } while (i < count);
    }
    return -1;
}

struct Node_1B4B68 {
    u8 pad0[0x2C]; f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40;
};
struct Src_1B4B68 { u8 pad0[4]; f32 f4; f32 f8; f32 fC; f32 f10; u16 u14; };

void func_001B4AA0(void* a, void* b);

void func_001B4B68(Node_1B4B68* p, Src_1B4B68* s)
{
    func_001B4AA0(p, s);
    p->f2C = s->f4;
    p->f30 = s->f8;
    p->f34 = s->fC;
    p->f38 = s->f10;
    p->f40 = (f32)s->u14;
}

struct Data_1B4C30 { u8 pad0[0x20]; s32 count; };
struct Node_1B4C30 {
    u8 pad0[0x10]; s32 flags; Data_1B4C30* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

f32 func_001EAAE0(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);
void func_001B46E0(void* obj, s32 value);

void func_001B4C30(Node_1B4C30* p, f32 dt)
{
    if (p->data == 0) {
        return;
    }
    if (p->data->count < 2) {
        return;
    }
    if (p->f48 > 0.0f) {
        p->f48 = p->f48 - dt;
        return;
    }
    p->f40 = p->f40 + p->f3C * dt;
    if ((f32)p->data->count <= p->f40) {
        f32 a = func_001EAAE0(p->f2C, p->f30);
        p->f3C = (f32)p->data->count / a;
        f32 b = func_001EAAE0(p->f34, p->f38);
        p->f44 = b;
        p->f48 = b;
    }
    f32 t = func_001EAFE0(p->f40, (f32)p->data->count);
    p->f40 = t;
    func_001B46E0(&p->flags, (s32)t);
}

s32 func_001B63C0(void* self, s32 key);

s32 func_001B63F8(void* self, s32 key)
{
    s32 r = func_001B63C0(self, key);
    return r < 0 ? 0 : r;
}

struct Reg_001B6438 { u8 pad0[0x1B88]; };
struct Owner_001B6438 { u8 pad0[0x14]; Reg_001B6438* reg_14; };
struct Obj_001B6438 {
    u8 pad0[0x18];
    Owner_001B6438* owner_18;
    u8 pad1[0x24 - 0x1C];
    void* handle_24;
    u8 pad2[0x3C - 0x28];
    void* ptr_3C;
};

void func_0012E760(void* p);
void func_001DBC18(void* a, void* b);
void func_00152600(void* a, void* b);
void func_001B5F28(void* a, void* b);
void func_001837E0(void* a, s32 b, s32 c, s32 d);

void func_001B6438(Obj_001B6438* self)
{
    Owner_001B6438* owner = self->owner_18;
    if (self->handle_24 != 0) {
        func_0012E760(self->handle_24);
        self->handle_24 = 0;
    }
    func_001DBC18(self->owner_18->reg_14, self->ptr_3C);
    self->ptr_3C = 0;
    func_00152600((u8*)self->owner_18 + 0x48, self);
    func_00152600((u8*)self->owner_18->reg_14 + 0x1B94, self);
    func_001B5F28((u8*)self->owner_18->reg_14 + 0x1B88, self);
    func_001837E0(owner, 0x12, 0, 0);
}

struct Vec3_1B5588 { f32 x; f32 y; f32 z; };

void func_001B5588(Vec3_1B5588* dst, Vec3_1B5588* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

struct __attribute__((aligned(16))) Quad_001B7968 { s32 a, b, c, d; };
struct __attribute__((packed)) Blk_001B7968 { s64 a, b, c, d; };
struct Blk36_001B7968 { Blk_001B7968 body; s32 e; };
struct Obj_001B7968 { u8 pad0[0x14]; void* p14; s32 f18; u8 pad1[0x2C - 0x1C]; void* p2C; u8 pad2[0x350 - 0x30]; Quad_001B7968 q350; u8 pad3[0x380 - 0x360]; Blk36_001B7968 src380; Blk36_001B7968 dst3A4; u8 pad4[0x4BC - 0x3C8]; s32 f4BC; s32 f4C0; u8 pad5[0x538 - 0x4C4]; u64 f538; };

void func_0011B008(Quad_001B7968* q);
void func_0011B060(Quad_001B7968* q, s32 mode);
void func_00152438(void* self, s32 value);
void func_00123ED0(void* self);
void func_00160E80(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
s32 func_0011A498(void* a, s32 b, s32 c, void* d);
void func_001BB4A0(void* self);

void func_001B7968(Obj_001B7968* self)
{
    Quad_001B7968 local;
    s32 s0;
    func_0011B008(&local);
    func_00152438((u8*)self + 0x2D8, 0x2E4);
    func_00123ED0(self);
    func_00160E80((u8*)self + 0x380);
    self->dst3A4 = self->src380;
    if (self->f18 != 0) {
        func_001B9AE0(self, 3, 0, 3, 0);
    }
    self->f4BC = -1;
    self->f4C0 = -1;
    if (self->p2C != 0) {
        s0 = func_0011A498(self->p2C, 6, 1, &local);
        s0 |= func_0011A498(self->p2C, 7, 1, &local);
        if (s0 != 0) {
            self->f538 |= (u64)0x8000 << 48;
        }
    }
    self->q350 = *(Quad_001B7968*)((u8*)self->p14 + 0x1EE0);
    func_001BB4A0(self);
    func_0011B060(&local, 2);
}

struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };

void func_001B4330(Quad_001B4580* p);

void func_001B4580(Quad_001B4580* src, f32* dst)
{
    Quad_001B4580 tmp = *src;
    tmp.v[1] = tmp.v[1] * 0.003921569f;
    tmp.v[2] = tmp.v[2] * 0.003921569f;
    func_001B4330(&tmp);
    dst[0] = dst[0] * 255.0f;
    dst[1] = dst[1] * 255.0f;
    dst[2] = dst[2] * 255.0f;
}

struct Slot_1B70B0 { s32 value; s32 pad4; };
struct Self_1B70B0 { u8 pad0[0xC38]; Slot_1B70B0 slots[1]; };

s32 func_001CA600(s32 index);

void func_001B70B0(Self_1B70B0* self, s32 index, s32 value)
{
    (void)func_001CA600(index);
    self->slots[index].value = value;
}

struct Entry_1B7100 { s32 value; s32 pad4; };
struct Self_1B7100 { u8 pad0[0xCD4]; s32 count; Entry_1B7100 entries[1]; };

void func_001B7100(Self_1B7100* self, s32 value)
{
    s32 n = self->count;
    if ((u32)n < 4) {
        self->entries[n].value = value;
        n++;
        self->count = n;
    }
}

struct S_1B5308 { u8 pad0[0x1C]; f32 a; f32 b; u8 pad1[8]; f32 testA; f32 testB; f32 denomA; f32 denomB; };
f32 func_001B5308(S_1B5308* p) { f32 result=0.0f; if (p->testA != 0.0f) result=(p->a/p->denomA)*0.5f; else result=0.5f; if (p->testB != 0.0f) result += (p->b/p->denomB)*0.5f; else result += 0.5f; return result; }

void func_001B5568(void* base, void** out) { out[0] = (u8*)base + 0x44; out[1] = (u8*)base + 0x4C; out[2] = (u8*)base + 0x48; }

struct Actor_1B5CD8 { u8 pad0[0x2C8]; u64 flags; };

void func_00124A48(void* self);

void func_001B5CD8(Actor_1B5CD8* self)
{
    func_00124A48(self);
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
}

struct Walk_1B5DD0 { s32 a; void* b; s32 c; };

void* func_0018D500(s32 size);
void func_001B5D80(void* s, s32 v, s32 n);

void func_001B5DD0(Walk_1B5DD0* s, s32 size, s32 count)
{
    s32 stride = (size + 7) & ~7;
    s->b = func_0018D500(stride * count);
    func_001B5D80(s, stride, count);
}

struct Walk_1B5E30 { s32 a; void* b; s32 c; };

void* func_0018D500(s32 size);
void func_001B5D80(void* s, s32 v, s32 n);

void func_001B5E30(Walk_1B5E30* s, s32 size, s32 count)
{
    s32 addr = (s32)func_0018D500(size * count + 0x30);
    s->b = (void*)((addr + 0x3F) & -0x40);
    func_001B5D80(s, size, count);
}

struct Node_1B6388 {
    u8 pad0[0x8];
    Node_1B6388* next;
    u8 pad1[0x10];
    s32 key;
};

struct Owner_1B6388 {
    u8 pad0[0x48];
    Node_1B6388* head;
};

void* func_001B6388(Owner_1B6388* self, s32 key)
{
    s32 scratch[4];
    (void)scratch;
    Node_1B6388* node = self->head;
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

struct Entry_1B6DF8 {
    u8 pad0[0x44];
    s32 value;
};

struct Holder_1B6DF8 {
    u8 pad0[0x14];
    void* ptr;
};

struct Self_1B6DF8 {
    u8 pad0[0x18];
    Holder_1B6DF8* holder;
};

void func_001831E8(void* a, void* b, s32 c, void* d);

void func_001B6DF8(Self_1B6DF8* self, Entry_1B6DF8** p)
{
    func_001831E8(self->holder->ptr, (u8*)self + 0x3C, (*p)->value, p);
}

struct Pair_1B7128 {
    s32 key;
    s32 value;
};

struct Self_1B7128 {
    u8 pad0[0x14];
    void* host;
    u8 pad1[0xC28 - 0x18];
    s32 sel;
    s32 result;
    u8 pad2[0xCD4 - 0xC30];
    s32 count;
    Pair_1B7128 pairs[1];
};

void func_001C72A0(void* self);
void func_001B6F50(void* self);
s32 func_0015A448(void* host, s32 id, void* ctx);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_001B7128(Self_1B7128* self)
{
    func_001C72A0(self);
    func_001B6F50(self);
    if (self->sel != -1) {
        self->result = func_0015A448(self->host, self->sel, self);
    }
    if (self->count > 0) {
        s32 i = 0;
        Pair_1B7128* p = self->pairs;
        do {
            p->value = func_0015A418(self->host, 0x104, p->key, self);
            p++;
            i++;
        } while (i < self->count);
    }
}

void func_001C7CB8(void* self);
void func_001B7638(void* self);

void func_001B7608(void* self)
{
    func_001C7CB8(self);
    func_001B7638(self);
}

typedef void (*VFn_1B7790)(void* self);
struct Sub_1B7790 { VFn_1B7790* vtbl; };
struct Obj_1B7790 {
    u8 pad0[0x724];
    s32 f724;
    u8 pad1[0xC14 - 0x728];
    Sub_1B7790* fC14;
    u8 pad2[0xC30 - 0xC18];
    s32 fC30;
    u8 pad3[0xCC0 - 0xC34];
    void* fCC0;
    s32 fCC4;
};
void func_001C91C8(void* self);
void func_001BF048(void* p);

void func_001B7790(Obj_1B7790* self)
{
    func_001C91C8(self);
    switch (self->f724) {
    case 6:
        self->fCC4 = 0;
        break;
    case 0xB: {
        Sub_1B7790* p = self->fC14;
        if (p != 0) {
            p->vtbl[7](p);
        }
        func_001BF048(self->fCC0);
        self->fCC0 = 0;
        break;
    }
    }
    self->fC30 = *(s32*)((u8*)self + (self->f724 << 3) + 0xC3C);
}

typedef s32 (*VFn_1B7818)(void* self);

struct Sub_1B7818 {
    VFn_1B7818* vtbl;
};

s32 func_001CA468(void* self);

s32 func_001B7818(Sub_1B7818* self)
{
    if (func_001CA468(self) == 0) {
        return 0;
    }
    return self->vtbl[91](self);
}

struct Obj_1B78C0 {
    u8 pad0[0x7E0];
    void* f7E0;
    u8 pad1[0xCC4 - 0x7E4];
    s32 fCC4;
};

void func_001C9DE0(void* self, s32 code, void* req);

void func_001B78C0(Obj_1B78C0* self, s32 code, void* req)
{
    func_001C9DE0(self, code, req);
    if (code == 7) {
        if (req == self->f7E0) {
            self->fCC4++;
        }
    }
}

struct Data_1B4DA8 { u8 pad0[0x20]; s32 count; };
struct Node_1B4DA8 {
    u8 pad0[0x10]; s32 flags; Data_1B4DA8* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B4AD0(void* p);
f32 func_001EAAE0(f32 a, f32 b);

void func_001B4DA8(Node_1B4DA8* p)
{
    func_001B4AD0(p);
    if (p->data != 0) {
        f32 a = func_001EAAE0(p->f2C, p->f30);
        p->f3C = (f32)(p->data->count * 2) / a;
        f32 b = func_001EAAE0(p->f34, p->f38);
        p->f44 = b;
        p->f48 = b;
    }
}

struct Data_1B4E18 { u8 pad0[0x20]; s32 count; };
struct Node_1B4E18 {
    u8 pad0[0x10]; s32 flags; Data_1B4E18* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};

void func_001B46E0(void* p, s32 v);
f32 func_001EAAE0(f32 a, f32 b);

void func_001B4E18(Node_1B4E18* p, f32 dt)
{
    Data_1B4E18* d = p->data;
    if (d == 0) return;
    if (d->count < 2) return;
    if (0.0f < p->f48) {
        p->f48 = p->f48 - dt;
        return;
    }
    f32 prod = p->f3C * dt;
    f32 sum = p->f40 + prod;
    p->f40 = sum;
    if ((f32)d->count <= sum) {
        p->f40 = sum - prod;
        p->f3C = -p->f3C;
    }
    if (p->f40 < 0.0f) {
        p->f40 = 0.0f;
        f32 a = func_001EAAE0(p->f2C, p->f30);
        p->f3C = (f32)(p->data->count * 2) / a;
        f32 b = func_001EAAE0(p->f34, p->f38);
        p->f44 = b;
        p->f48 = b;
    }
    func_001B46E0((u8*)p + 0x10, (s32)p->f40);
}

struct Node_1B5400 { u8 pad0[0x14]; s32 f14; u8 pad1[0x14]; f32 f2C; f32 f30; f32 f34; f32 f38; };

extern f32 D_0026185C;
f32 func_001EA408(f32 a);
void func_001EAD88(f32 angle, f32* a, f32* b);
void func_001B4750(void* p, f32 a, f32 b);

void func_001B5400(Node_1B5400* self)
{
    if (self->f14 != 0) {
        f32 t[2];
        f32 ang = func_001EA408(D_0026185C * self->f2C);
        func_001EAD88(ang, &t[0], &t[1]);
        t[0] = t[0] * self->f30 + self->f34;
        t[1] = t[1] * self->f30 + self->f38;
        func_001B4750((u8*)self + 0x10, t[0], t[1]);
    }
}

struct Node_1B5488 { u8 pad0[0x2C]; f32 f2C; };

extern f32 D_0026185C;
f32 func_001EAFE0(f32 x, f32 y);

f32 func_001B5488(Node_1B5488* p)
{
    f32 a = func_001EAFE0(D_0026185C * p->f2C, 6.2831855f);
    return a * 0.15915494f;
}

struct Src_1B54D0 { u8 pad0[4]; f32 f4; f32 f8; f32 fC; f32 f10; f32 f14; f32 f18; };
struct Node_1B54D0 { u8 pad0[0x10]; s32 flags; u8 pad1[0x18]; f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; };

void func_001B4AA0(void* a, void* b);

void func_001B54D0(Node_1B54D0* self, Src_1B54D0* src)
{
    func_001B4AA0(self, src);
    s32 fl = self->flags;
    self->f2C = src->f4;
    self->f30 = src->f8;
    self->f34 = src->fC - src->f4;
    self->f38 = src->f10 - src->f4;
    self->f3C = src->f14 - src->f8;
    f32 d = src->f18 - src->f8;
    self->flags = (fl & -2) | 2;
    self->f40 = d;
}


void func_00124FC0(void* self);

struct __attribute__((aligned(16))) Quad_1B5D28 { s32 a, b; f32 c; s32 d; };

typedef void (*VFn_1B5D28)(void* self, void* p);
struct Node_1B5D28 {
    VFn_1B5D28* vtbl;
    u8 pad[0x148 - 4];
    f32 f148;
    u8 pad2[0x2D0 - 0x14C];
    s32 f2D0;
};

void func_001B5D28(Node_1B5D28* self)
{
    func_00124FC0(self);
    Quad_1B5D28* src = (Quad_1B5D28*)((u8*)D_00261990 + 0x40);
    Quad_1B5D28 q = *src;
    if (self->f2D0 == 0) {
        q.c = self->f148;
    }
    self->vtbl[33](self, &q);
}

void func_001C6F48(void* self);

struct Ent_1B6EC8 { s32 v; s32 pad; };
struct Node_1B6EC8 {
    u8 pad[0xC10];
    s32 fC10;
    u8 pad2[0xC18 - 0xC14];
    f32 fC18;
    f32 fC1C;
    f32 fC20;
    f32 fC24;
    s32 fC28;
    s32 fC2C;
};

void func_001B6EC8(Node_1B6EC8* self)
{
    func_001C6F48(self);
    self->fC20 = 2000.0f;
    self->fC18 = 300.0f;
    self->fC1C = 300.0f;
    self->fC24 = 300.0f;
    self->fC28 = -1;
    self->fC2C = 0;
    s32 i = 16;
    Ent_1B6EC8* e = (Ent_1B6EC8*)((u8*)self + 0xCB8);
    do {
        e->v = -1;
        i--;
        e--;
    } while (i >= 0);
    self->fC10 = -1;
}

struct Node_1B5398 {
    u8 pad0[0x10]; s32 flags; void* data; u8 pad1[4];
    f32 f1C; f32 f20; u8 pad2[8];
    f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48;
};
struct Src_1B5398 { u8 pad0[4]; f32 f4; f32 f8; f32 fC; f32 f10; };

void func_001B4AA0(void* a, void* b);

void func_001B5398(Node_1B5398* p, Src_1B5398* s)
{
    func_001B4AA0(p, s);
    p->f2C = s->f4; p->f30 = s->f8; p->f34 = s->fC; p->f38 = s->f10; p->flags = (p->flags & ~1) | 2;
}

extern f32 D_0026185C;

struct Obj_1B7860 {
    u8 pad0[0x724];
    s32 f724;
    f32 f728;
    u8 pad1[0xCC4 - 0x72C];
    s32 fCC4;
};

s32 func_001B7860(Obj_1B7860* self)
{
    s32 r;
    if (self->f724 == 11) {
        goto ret1;
    }
    if (self->f724 != 6) {
        goto ret0;
    }
    if (self->fCC4 <= 0) {
        goto ret0;
    }
    if (5.0f < D_0026185C - self->f728) {
        r = 2;
        return r;
    }
ret1:
    return 1;
ret0:
    r = 0;
    return r;
}
