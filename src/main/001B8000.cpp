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

struct __attribute__((aligned(16))) Quad_001B9680 { s32 a, b, c, d; };
struct Obj_001B9680 { u8 pad0[0x140]; Quad_001B9680 src; u8 pad1[0x370 - 0x150]; Quad_001B9680 dst; };

void func_001B9680(Obj_001B9680* self)
{
    self->dst = self->src;
}

void func_001BA430(void* a, void* b, void* c, s32 d);

void func_001BA500(void* self, void* a, void* b, void* c, s32 d)
{
    func_001BA430(a, b, c, d);
}

struct Node_1BA528 { u8 pad0[8]; Node_1BA528* next; };
struct Owner_1BA528 { u8 pad0[0x4B0]; Node_1BA528* head; };

void func_00129DF8(void* self);

void func_001BA528(Owner_1BA528* self, Node_1BA528* node)
{
    node->next = self->head;
    self->head = node;
    func_00129DF8(self);
}

s32 func_001BBC30(void)
{
    return 0;
}

struct __attribute__((aligned(16))) Quad_1B97E0 { s32 a, b, c, d; };
typedef void (*VFn_1B97E0)(void* self);
typedef void (*VFnB_1B97E0)(void* self, s32 a, void* b);
struct Obj_1B97E0 { VFn_1B97E0* vtbl; u8 pad0[0x50 - 4]; void* f50; u8 pad1[0xD0 - 0x54]; Quad_1B97E0 q0; Quad_1B97E0 q1; Quad_1B97E0 q2; };

void func_001B94F0(void* self, s32 value);

void func_001B97E0(Obj_1B97E0* self, Quad_1B97E0* src)
{
    self->q0 = src[0];
    self->q1 = src[1];
    self->q2 = src[2];
    if (self->f50 != 0) {
        if (self->vtbl[0x58 / 4] != 0) {
            self->vtbl[0x58 / 4](self);
        }
        func_001B94F0(self, 1);
    }
    ((VFnB_1B97E0)self->vtbl[0x48 / 4])(self, 4, self);
}

struct Obj_1BAFE0 { u8 pad0[0x3CC]; f32 f3CC; u8 pad1[0x538 - 0x3D0]; u64 bits538; };

void func_001BAFE0(Obj_1BAFE0* self, f32 v)
{
    self->bits538 |= (u64)0x8000 << 25;
    self->f3CC = v;
}

struct Obj_001BB138 { u8 pad[0x538]; u64 flags; };
void func_001BB138(Obj_001BB138* self, u32 value) { self->flags = (self->flags & ~(0xFULL << 32)) | ((u64)(value & 0xF) << 32); }

struct Obj_001BB168 { u8 pad[0x538]; u64 flags; };
void func_001BB168(Obj_001BB168* self, u32 value) { self->flags = (self->flags & ~(1ULL << 47)) | ((u64)(value & 1) << 47); }

struct Obj_001BB1D8 { u8 pad[0x2C8]; u8 value; };
void func_001BB1D8(Obj_001BB1D8* self, u8 value) { self->value = value; }

struct Obj_001BB1E0 { u8 pad[0x538]; u64 flags; };
void func_001BB1E0(Obj_001BB1E0* self, u32 value) { self->flags = (self->flags & ~(0xFULL << 36)) | ((u64)(value & 0xF) << 36); }

typedef u64 Quad_1B8960 __attribute__((mode(TI)));

struct Obj_1B8960 {
    u8 pad0[0x140];
    Quad_1B8960 f140;
};

void func_00125138(void* self);
void func_001B8820(void* a, void* b, Quad_1B8960 q, void* c);

void func_001B8960(Obj_1B8960* self)
{
    func_00125138(self);
    func_001B8820((u8*)self + 0x380, (u8*)self + 0x3A4, self->f140, (u8*)self + 0x110);
    func_001B8820((u8*)self + 0x4E8, (u8*)self + 0x50C, self->f140, (u8*)self + 0x110);
}

struct __attribute__((aligned(16))) Quad_1B9B50 { s32 a, b, c, d; };

struct Obj_1B9B50 {
    u8 pad0[0x18];
    void* f18;
    u8 pad1[0x50 - 0x1C];
    Obj_1B9B50* f50;
    u8 pad2[0x538 - 0x54];
    u64 f538;
};

void func_001280C0(void* a, void* b, void* c, void* d);
void func_001245A8(void* self, void* p);
void func_001BB580(void* p);
void func_001BB4A0(void* self);

void func_001B9B50(Obj_1B9B50* self, void* p)
{
    Quad_1B9B50 local0;
    Quad_1B9B50 local1;
    if (self->f18 == p) {
        return;
    }
    Obj_1B9B50* s5 = self->f50;
    func_001280C0(self->f18, 0, (u8*)self + 0x440, &local0);
    func_001280C0(self->f18, 0, (u8*)self + 0x460, &local1);
    func_001245A8(self, p);
    func_001280C0(0, p, &local0, (u8*)self + 0x440);
    func_001280C0(0, p, &local1, (u8*)self + 0x460);
    if (self->f50 != 0) {
        if ((self->f538 & (1ULL << 54)) != 0 && s5 != 0) {
            func_001BB580(s5);
        }
        Obj_1B9B50* f = self->f50;
        if ((f->f538 & (1ULL << 55)) != 0) {
            func_001BB580(f);
        } else {
            func_001BB580(self);
        }
    }
    func_001BB4A0(self);
}

struct Pair_1BA068 {
    s32 f0;
    void* f4;
    u8 pad8[0x40 - 8];
    s32 g0;
    void* g4;
    u8 pad48[0xD0 - 0x48];
    Pair_1BA068* next;
};

struct Outer_1BA068 {
    Pair_1BA068* f0;
    Outer_1BA068* f4;
};

struct Obj_1BA068 {
    u8 pad0[0x50];
    Obj_1BA068* f50;
};

s32 func_00182F40(void* e, void* b);

void* func_001BA068(Obj_1BA068* self)
{
    Obj_1BA068* s3 = self->f50;
    Outer_1BA068* s2 = *(Outer_1BA068**)(*(u8**)((u8*)s3 + 0x480));
    for (; s2 != 0; s2 = s2->f4) {
        Pair_1BA068* s0 = s2->f0;
        while (s0 != 0) {
            s32 s1 = ((u32)s3 ^ (u32)s0->f0) != 0;
            if (func_00182F40(*(void**)((u8*)(s0) + (s1 << 6) + 4), self) != 0) {
                return *(void**)((u8*)(s0) + ((1 - s1) << 6) + 4);
            }
            s0 = s0->next;
        }
    }
    return 0;
}

void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_001BB000(void* self)
{
    func_001B9AE0(self, 3, 0, 3, 0);
}

typedef void (*VFn_1BB210)(void* self, void* a, void* b);

struct Obj_1BB210;

struct Node_1BB210 {
    Obj_1BB210* f0;
    u8 pad4[4];
    Node_1BB210* f8;
};

struct Obj_1BB210 {
    VFn_1BB210* vtbl;
    u8 pad4[0x4B0 - 4];
    Node_1BB210* f4B0;
};

void func_00183350(void* self, void* a, void* b);

void func_001BB210(Obj_1BB210* self, void* a, void* b)
{
    func_00183350(self, a, b);
    Node_1BB210* n = self->f4B0;
    if (n != 0) {
        do {
            Node_1BB210* next = n->f8;
            Obj_1BB210* obj = n->f0;
            if (obj != self) {
                VFn_1BB210 fn = obj->vtbl[17];
                if (fn != 0) {
                    fn(obj, a, b);
                }
            }
            n = next;
        } while (n != 0);
    }
}

struct __attribute__((aligned(16))) Quad_1BB028 { s32 v[4]; };
struct Entry_1BB028 { Quad_1BB028* quad; s32 value; };
extern Entry_1BB028 D_002746E0[];
void func_001BB028(s32 index, s32* out, Quad_1BB028* dst)
{
    *out = D_002746E0[index].value;
    *dst = *D_002746E0[index].quad;
}

struct Item_1BB800 { void* owner; u8 pad[0xCC]; Item_1BB800* next; };
struct Node_1BB800 { Item_1BB800* item; Node_1BB800* next; };
struct List_1BB800 { Node_1BB800* head; };
struct Owner_1BB800 { u8 pad[0x480]; List_1BB800* list; };
struct Obj_1BB800 { u8 pad[0x50]; Owner_1BB800* owner; };
struct Arg_1BB800 { s32 x; };

s32 func_00182F40(void* a, Arg_1BB800* b);
void* func_0018D658(s32 n);

s32 func_001BB800(Obj_1BB800* obj, s32* outCount, void*** outArr)
{
    Owner_1BB800* own = obj->owner;
    Node_1BB800* nd;
    Item_1BB800* it;
    s32 n = 0;
    for (nd = own->list->head; nd; nd = nd->next) {
        for (it = nd->item; it; it = it->next) {
            s32 g = it->owner != own;
            if (func_00182F40(*(void**)((u8*)it + (g << 6) + 4), (Arg_1BB800*)obj))
                n++;
        }
    }
    void** arr = (void**)func_0018D658(n << 2);
    void** end = arr;
    for (nd = own->list->head; nd; nd = nd->next) {
        for (Item_1BB800* it2 = nd->item; it2; it2 = it2->next) {
            s32 f = it2->owner != own;
            if (func_00182F40(*(void**)((u8*)it2 + (f << 6) + 4), (Arg_1BB800*)obj)) {
                void* v = *(void**)((u8*)it2 + ((1 - f) << 6) + 4);
                void** p;
                for (p = arr; p < end; p++)
                    if (*p == v) break;
                if (!(p < end)) {
                    *end = v;
                    end++;
                }
            }
        }
    }
    *outArr = arr;
    s32 cnt = end - arr;
    *outCount = cnt;
    return cnt;
}

struct Node_1BA550 { u8 pad0[8]; Node_1BA550* next; };

struct Obj_1BA550 { u8 pad0[0x4B0]; Node_1BA550* chain; };

void func_00129DF8(void* self);

void func_001BA550(Obj_1BA550* o, Node_1BA550* node)
{
    Node_1BA550** link = &o->chain;
    if (*link == 0) {
        goto tail;
    }
    if (o->chain == node) {
        o->chain = node->next;
    } else {
        Node_1BA550* prev;
        for (;;) {
            prev = *link;
            Node_1BA550* nx = prev->next;
            link = &prev->next;
            if (nx == 0) {
                goto tail;
            }
            if (nx == node) {
                break;
            }
        }
        prev->next = node->next;
    }
    node->next = 0;
tail:
    func_00129DF8(o);
}

struct Slot_1B9FB0 { s32 f0; void* f4; u8 pad0[0x38]; };
struct Node_1B9FB0 { Slot_1B9FB0 slot[2]; u8 pad0[0xD0 - 0x80]; Node_1B9FB0* next; };
struct Self_1B9FB0 { u8 pad0[0x50]; s32 key; };

s32 func_001387F8(void* self, void* other);
s32 func_00182F40(void* e, void* b);
s32 func_001B9FB0(Self_1B9FB0* self, void* other)
{
    s32 key;
    Node_1B9FB0* n;
    for (n = (Node_1B9FB0*)func_001387F8(self, other), key = self->key; n != 0; n = n->next) {
        s32 s1 = (key ^ n->slot[0].f0) != 0;
        s32 o0 = s1 * 64;
        if (func_00182F40(*(void**)((u8*)n + o0 + 4), self) != 0) {
            s32 o1 = (1 - s1) * 64;
            if (func_00182F40(*(void**)((u8*)n + o1 + 4), other) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Matched by indexing the end as (u32)e + (i << 6).

struct Obj_1BB9D0;
struct Edge_1BB9D0 {
    struct End { Obj_1BB9D0* o; Obj_1BB9D0* other; u8 pad[0x38]; } e[2];
    u8 pad80[0x50];
    Edge_1BB9D0* next;
};
struct Out_1BB9D0 { Edge_1BB9D0* first; Out_1BB9D0* next; };
struct OutHead_1BB9D0 { Out_1BB9D0* head; };
struct Mem_1BB9D0 { Obj_1BB9D0* value; Mem_1BB9D0* next; };
struct Core_1BB9D0 { u8 pad[0x480]; OutHead_1BB9D0* outs; };
struct Obj_1BB9D0 {
    u8 pad0[0x14]; void* pool;
    u8 pad18[0x38]; Core_1BB9D0* core;
    u8 pad54[0x4EC]; Mem_1BB9D0* mem;
};

s32 func_001BB9A0(Mem_1BB9D0* m, Obj_1BB9D0* v);
void func_001837E0(Obj_1BB9D0* self, s32 a, s32 b, void* c);
void func_001DC108(void* pool, Mem_1BB9D0* m);
Mem_1BB9D0* func_001DC0C8(void* pool);

void func_001BB9D0(Obj_1BB9D0* self)
{
    Core_1BB9D0* core = self->core;
    Out_1BB9D0* o;
    Edge_1BB9D0* e;
    Mem_1BB9D0* m;
    Mem_1BB9D0* prev;
    Obj_1BB9D0* other;
    void* args;
    for (o = core->outs->head; o != 0; o = o->next) {
        for (e = o->first; e != 0; e = e->next) {
            s32 i = e->e[0].o != (Obj_1BB9D0*)core;
            if (((Edge_1BB9D0::End*)((u32)e + (i << 6)))->other == self) {
                other = ((Edge_1BB9D0::End*)((u32)e + ((1 - i) << 6)))->other;
                if (!func_001BB9A0(self->mem, other)) {
                    args = &other;
                    func_001837E0(self, 6, 1, &args);
                }
            }
        }
    }
    for (m = self->mem; m != 0; m = m->next) {
        s32 found = 0;
        for (o = core->outs->head; o != 0 && !found; o = o->next) {
            for (e = o->first; e != 0 && !found; e = e->next) {
                s32 i = e->e[0].o != (Obj_1BB9D0*)core;
                if (((Edge_1BB9D0::End*)((u32)e + (i << 6)))->other == self) {
                    other = ((Edge_1BB9D0::End*)((u32)e + ((1 - i) << 6)))->other;
                    if (other == m->value) found = 1;
                }
            }
        }
        if (!found) {
            args = m;
            func_001837E0(self, 7, 1, &args);
        }
    }
    func_001DC108(self->pool, self->mem);
    self->mem = 0;
    for (o = core->outs->head; o != 0; o = o->next) {
        for (e = o->first; e != 0; e = e->next) {
            s32 i = e->e[0].o != (Obj_1BB9D0*)core;
            if (((Edge_1BB9D0::End*)((u32)e + (i << 6)))->other == self) {
                other = ((Edge_1BB9D0::End*)((u32)e + ((1 - i) << 6)))->other;
                Mem_1BB9D0* n = func_001DC0C8(self->pool);
                n->value = other;
                if (self->mem != 0) prev->next = n; else self->mem = n;
                prev = n;
            }
        }
    }
}

struct B8_1BA130 { u8 b[8]; };
struct B12_1BA130 { u8 b[8]; s32 w; };
struct Obj_1BA130 {
    u8 pad0[0x2D0];
    B8_1BA130 f2D0;
    B12_1BA130 f2D8;
    B8_1BA130 f2E4;
    u8 pad2EC[0x3A4 - 0x2EC];
    u8 f3A4[0x4C];
    s32 f3F0[2];
    u8 pad3F8[0x414 - 0x3F8];
    B8_1BA130 f414;
    u8 pad41C[0x480 - 0x41C];
    s32 f480;
    u8 pad484[0x4B0 - 0x484];
    s32 f4B0;
    u8 pad4B4[4];
    s32 f4B8;
    u8 pad4BC[0x4E4 - 0x4BC];
    s32 f4E4;
    u8 pad4E8[0x510 - 0x4E8];
    s32 f510;
    u8 pad514[0x538 - 0x514];
    u64 f538;
    s32 f540;
};

void func_00127048(Obj_1BA130* self, Obj_1BA130* other);
void func_001B7C40(Obj_1BA130* self, s32 flag);
void func_00160EA0(u8* a, s32 b, u8* c);
void func_0013E6C8(u8* a, u8* b, u8* c, u8* d);

void func_001BA130(Obj_1BA130* self, Obj_1BA130* other)
{
    u64 bit = (self->f538 >> 50) & 1;
    B8_1BA130 a, c, d;
    B12_1BA130 b;
    a = self->f2D0;
    b = self->f2D8;
    c = self->f2E4;
    s32 s480 = self->f480;
    s32 s4E4 = self->f4E4;
    d = self->f414;
    func_00127048(self, other);
    self->f480 = s480;
    self->f2D0 = a;
    self->f2D8 = b;
    self->f2E4 = c;
    self->f414 = d;
    self->f4E4 = s4E4;
    self->f4B0 = 0;
    self->f4B8 = 0;
    self->f538 = (self->f538 & 0xFFFBFFFFFFFFFFFFULL) | (bit << 50);
    func_001B7C40(self, 1);
    if (*(s32*)(self->f3A4 + 4)) func_00160EA0((u8*)other + 0x3A4, 0, self->f3A4);
    if (*(s32*)((u8*)self + 0x3F8)) func_0013E6C8((u8*)other + 0x3A4, (u8*)other + 0x3F0, self->f3A4, (u8*)self + 0x3F0);
    if (self->f510) func_00160EA0((u8*)other + 0x50C, 0, (u8*)self + 0x50C);
    if ((s32)self->f538) func_0013E6C8((u8*)other + 0x50C, (u8*)other + 0x530, (u8*)self + 0x50C, (u8*)self + 0x530);
    self->f540 = 0;
    self->f538 |= 0x20000000000ULL;
}
