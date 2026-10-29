// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*VFn_1B89B8)(void* self);

struct Sub_1B89B8 {
    VFn_1B89B8* vtbl;
};

struct Obj_1B89B8 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x38];
    Sub_1B89B8* f50;
};

void func_00125108(Obj_1B89B8* self);
void func_00138BE0(void* a, void* b, s32 c);
void func_001389C8(void* a);

void func_001B89B8(Obj_1B89B8* self)
{
    func_00125108(self);
    self->f50->vtbl[54](self->f50);
    func_00138BE0(self->f14, self, 7);
    func_001389C8(self->f14);
}

struct Obj_1B9418 {
    u8 pad0[0x368];
    f32 f368;
};

void func_001B9448(Obj_1B9418* self);

void func_001B9418(Obj_1B9418* self, f32 v)
{
    f32 a = self->f368;
    f32 q = v / a;
    self->f368 = a * q;
    func_001B9448(self);
}

void func_001BAC28(void)
{
}

struct Obj_1BB1A0 {
    u8 pad0[0x538];
    u64 f538;
};

void func_001BB1A0(Obj_1BB1A0* self, s32 flag)
{
    self->f538 = (self->f538 & 0xFFFEFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 48);
}

struct Obj_1BB400 { u8 pad[0x538]; u64 flags; };

void func_001B94F0(Obj_1BB400* self, s32 value);

void func_001BB400(Obj_1BB400* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 43;
    self->flags = (self->flags & ~(1ULL << 43)) | bit;
    func_001B94F0(self, value != 0 ? 2 : 0);
}

struct Node_1BB9A0 { s32 value; Node_1BB9A0* next; };

s32 func_001BB9A0(Node_1BB9A0* node, s32 value)
{
    while (node != 0) {
        if (node->value == value) return 1;
        node = node->next;
    }
    return 0;
}

struct Obj_1BB378 {
    u8 pad0[0x538];
    u64 flags;
};

void func_001BB378(Obj_1BB378* self, s32 flag)
{
    self->flags = (self->flags & ~(1ULL << 51)) | ((u64)(flag & 1) << 51);
}

struct Obj_1BB3B0 {
    u8 pad0[0x538];
    u64 flags;
};

void func_001B94F0(void* self, s32 value);

void func_001BB3B0(Obj_1BB3B0* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 42;
    self->flags = (self->flags & ~(1ULL << 42)) | bit;
    func_001B94F0(self, value != 0);
}

struct Obj_1BB450 {
    u8 pad0[0x538];
    u64 flags;
};

void func_001B94F0(void* self, s32 value);

void func_001BB450(Obj_1BB450* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 44;
    self->flags = (self->flags & ~(1ULL << 44)) | bit;
    func_001B94F0(self, value != 0 ? 3 : 0);
}

struct Info_1BB4A0 {
    u8 pad0[8];
    u32 f8;
    u8 pad1[0xF4];
    void* f100;
    void* f104;
    void* f108;
    u8 pad2[0x8];
    void* f114;
};

struct Obj_1BB4A0 {
    Info_1BB4A0* info;
    u8 pad0[0x14];
    Obj_1BB4A0* f18;
    Obj_1BB4A0* f1c;
    u8 pad1[0x34 - 0x20];
    Obj_1BB4A0* f34;
    u8 pad2[0x4E4 - 0x38];
    Obj_1BB4A0* f4e4;
};

void func_001BB4A0(Obj_1BB4A0* self)
{
    s32 scratch[4];
    (void)scratch;
    Info_1BB4A0* info = self->info;
    if (info->f114 != 0 || info->f100 != 0 || info->f104 != 0) {
        self->f4e4 = self;
    } else if (info->f108 != 0) {
        self->f4e4 = self;
    } else {
        Obj_1BB4A0* p = self->f18;
        if (p != 0) {
            self->f4e4 = p->f4e4;
        } else {
            self->f4e4 = 0;
        }
    }
    Obj_1BB4A0* c = self->f34;
    while (c != 0) {
        if (c->info->f8 & 2) func_001BB4A0(c);
        c = c->f1c;
    }
}

struct Obj_1BB540 {
    u8* info;
    u8 pad0[0x14];
    Obj_1BB540* f18;
    u8 pad1[0x4E4 - 0x1C];
    Obj_1BB540* f4e4;
};

Obj_1BB540* func_001BB540(Obj_1BB540* node, s32 offset)
{
    Obj_1BB540* s;
    while (node != 0 && (s = node->f4e4) != 0) {
        if (*(s32*)(s->info + offset) != 0) return s;
        node = s->f18;
    }
    return 0;
}

struct Info_1BB580 {
    u8 pad0[8];
    u32 f8;
};

struct Obj_1BB580 {
    Info_1BB580* info;
    u8 pad0[0x10];
    void* f14;
    Obj_1BB580* f18;
    Obj_1BB580* f1c;
    u8 pad1[0x34 - 0x20];
    Obj_1BB580* f34;
    u8 pad2[0x50 - 0x38];
    void* f50;
    u8 pad3[0x450 - 0x54];
    s32 f450;
    u8 pad4[0x470 - 0x454];
    s32 f470;
    u8 pad5[0x538 - 0x474];
    u64 flags;
};

void func_00138F28(void* a, void* b);

void func_001BB580(Obj_1BB580* self)
{
    s32 scratch[4];
    (void)scratch;
    s32 flag = 0;
    if (self->f450 == 3) {
        flag = (self->f470 == 3);
    }
    self->flags = (self->flags & ~(1ULL << 54)) | ((u64)flag << 54);
    s32 s2 = flag & 1;
    s32 a0 = 0;
    if (self->flags & (1ULL << 54)) {
        if (self->f18 == 0 || (self->f18->flags & (1ULL << 56)) != 0) a0 = 1;
    }
    self->flags = (self->flags & ~(1ULL << 56)) | ((u64)a0 << 56);
    Obj_1BB580* c = self->f34;
    while (c != 0) {
        if (c->info->f8 & 2) {
            func_001BB580(c);
            if ((c->flags & (1ULL << 55)) == 0) s2 = 0;
        }
        c = c->f1c;
    }
    u64 bit = (self->flags >> 55) & 1;
    if (bit != (u64)s2) {
        self->flags = (self->flags & ~(1ULL << 55)) | ((u64)(s2 & 1) << 55);
        if (self->f18 == 0 && self->f50 != 0) {
            func_00138F28(self->f14, self);
        }
    }
}

struct Slot_1BB710 {
    u32 f0;
    void* f4;
    u8 pad0[0x38];
};

struct Entry_1BB710 {
    Slot_1BB710 slot[2];
    u8 pad1[0xD0 - 0x80];
    Entry_1BB710* next;
};

struct Node_1BB710 {
    Entry_1BB710* items;
    Node_1BB710* next;
};

struct Table_1BB710 {
    Node_1BB710* head;
};

struct Ctx_1BB710 {
    u8 pad0[0x480];
    Table_1BB710* f480;
};

struct Obj_1BB710 {
    u8 pad0[0x50];
    Ctx_1BB710* f50;
};

s32 func_001C1AD8(s32 value, void* out);
s32 func_001C1A28(s32 value, void* out);

s32 func_001BB710(Obj_1BB710* self, s32 value)
{
    Ctx_1BB710* ctx = self->f50;
    Node_1BB710* n = ctx->f480->head;
    while (n != 0) {
        Entry_1BB710* e = n->items;
        while (e != 0) {
            s32 idx = (e->slot[0].f0 ^ (u32)ctx) != 0;
            Slot_1BB710* s = &e->slot[idx];
            if (s->f4 == self) {
                void* tmp = e->slot[1 - idx].f4;
                if (func_001C1AD8(value, &tmp) == 0) {
                    if (func_001C1A28(value, &tmp) == 0) return 0;
                }
            }
            e = e->next;
        }
        n = n->next;
    }
    return 1;
}

struct Actor_1B8A08 { u8 pad[0x538]; u64 flags; };

s32 func_001B8A08(Actor_1B8A08* a, Actor_1B8A08* b)
{
    u64 m1 = 0x8080;
    s32 r = 0;
    m1 <<= 40;
    if ((a->flags & m1) != 0) {
        u64 bf = b->flags;
        u64 m2 = 0x8000;
        m2 <<= 40;
        if ((bf & m2) != 0) {
            return 1;
        }
    }
    return r;
}

typedef void (*Fn_1B8A48)(void* obj, void* item, s32 index);

struct Obj_1B8A48 { Fn_1B8A48* vtbl; };

struct Slot_1B8A48 { Obj_1B8A48* obj; u8 rest[0x3C]; };

struct Item_1B8A48 {
    u8 pad0[4];
    Slot_1B8A48 slots[2];
    u8 pad1[0xC4 - 0x84];
    f32 timer;
    u8 pad2[0xD0 - 0xC8];
    Item_1B8A48* next;
};

struct Node_1B8A48 { Item_1B8A48* item; Node_1B8A48* next; };

struct List_1B8A48 { Node_1B8A48* head; };

struct Self_1B8A48 {
    u8 pad[0x480];
    List_1B8A48* list;
};

extern void* func_001BB540(void* obj, s32 type);

void func_001B8A48(Self_1B8A48* self)
{
    Node_1B8A48* node = self->list->head;
    while (node != 0) {
        Item_1B8A48* it = node->item;
        while (it != 0) {
            if (0.0001f < it->timer) {
                for (s32 i = 0; i < 2; i++) {
                    Obj_1B8A48* obj = (Obj_1B8A48*)func_001BB540(it->slots[i].obj, 0x114);
                    if (obj != 0) {
                        Fn_1B8A48 fn = obj->vtbl[0x114 / 4];
                        if (fn != 0) {
                            fn(obj, it, i);
                        }
                    }
                }
                *(s32*)&it->timer = 0;
            }
            if (node->item == 0) {
                break;
            }
            it = it->next;
        }
        node = node->next;
    }
}

typedef void (*Fn_1B9338)(void* obj, void* node, f32 t);

struct Obj_1B9338 { Fn_1B9338* vtbl; };

struct Node_1B9338 { Obj_1B9338* obj; u8 pad[4]; Node_1B9338* next; };

struct Actor_1B9338 {
    u8 pad0[0x18];
    s32 field18;
    u8 pad1[0x4B0 - 0x1C];
    Node_1B9338* chain;
    u8 pad2[0x538 - 0x4B4];
    u64 flags;
};

struct Vec_1B9338 { s32 v[4]; };

void func_001BA500(void* a, void* b, void* c, void* d, s32 e);
void func_001B9AB0(void* a, void* b);

void func_001B9338(Actor_1B9338* self, f32 t)
{
    Vec_1B9338 local;
    Node_1B9338* node;
    u64 m = 0x8000;
    m <<= 36;
    if (self->field18 == 0) {
        if ((self->flags & m) == 0) {
            func_001BA500(self, (u8*)self + 0x440, (u8*)self + 0x350, &local, 0);
            func_001B9AB0(self, &local);
        }
    }
    node = self->chain;
    if (node != 0) {
        do {
            Obj_1B9338* obj = node->obj;
            obj->vtbl[0xDC / 4](obj, node, t);
            node = node->next;
        } while (node != 0);
    }
}

void func_001261C0(void);

void func_001B93D8(void)
{
    func_001261C0();
}

void func_00124FC0(void* self);

void func_001B93F8(void* self)
{
    func_00124FC0(self);
}
