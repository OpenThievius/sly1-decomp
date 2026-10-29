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
