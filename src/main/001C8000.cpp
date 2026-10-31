// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

s32 func_001CA460(void)
{
    return 2;
}

struct Obj_CA720 { u8 pad[0xAC4]; s32 count; };

void func_001CA720(Obj_CA720* self, s32 a1, s32 a2)
{
    s32 n = self->count;
    if ((u32)n < 4) {
        self->count = n + 1;
        u8* p = (u8*)self + (n * 12 + 0xAC8);
        *(s32*)p = a1;
        *(s32*)(p + 4) = a2;
    }
}

struct Ent_CA8E8 { s32 key; void* val; };
struct Obj_CA8E8 { u8 pad0[0x14]; void* f14; u8 pad1[0x870 - 0x18]; Ent_CA8E8 ents[17]; };
void* func_0015A418(void* a, s32 b, s32 key, void* self);
void func_00182ED8(void* p);

void func_001CA8E8(Obj_CA8E8* self)
{
    for (s32 i = 16; i >= 0; i--) {
        Ent_CA8E8* e = &self->ents[16 - i];
        if (e->key != -1) {
            void* r = func_0015A418(self->f14, 0x101, e->key, self);
            e->val = r;
            if (r != 0) func_00182ED8(r);
        }
    }
}

struct Obj_CAC28 { u8 pad[0xB50]; s32 value; };

void func_001CAC28(Obj_CAC28* self, s32 value)
{
    self->value = value;
}

struct Obj_CAD98;
typedef void* (*VFn_CAD98)(void* self);

struct Obj_CAD98 {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1[0x3CC - 0x1C];
    f32 f3CC;
    u8 pad2[0x538 - 0x3D0];
    u64 f538;
};

struct Entry_CAD98 {
    s32 f0;
    Obj_CAD98* obj;
    s32 f8;
};

struct Self_CAD98 {
    VFn_CAD98* vtbl;
    u8 pad0[0xA78 - 4];
    s32 count;
    Entry_CAD98 entries[1];
    u8 pad1[0xC04 - 0xA7C - sizeof(Entry_CAD98)];
    s32 f_C04;
};

struct Obj_CAD98_3F0 {
    u8 pad0[0x3F0];
    s32 f3F0;
    u8 pad1[0x3F8 - 0x3F4];
    s32 f3F8;
};

void func_001C5C10(Self_CAD98* a, Obj_CAD98* b, s32 c, s32 d);
s32 func_001300E8(Obj_CAD98* a, s32 b);
s32 func_00182FC8(Obj_CAD98* a);
void func_001879C0(f32 f, Obj_CAD98* a, void* b, Obj_CAD98* c, s32 d, s32 e, s32 g, void* h);
void func_00186BA8(Obj_CAD98* a, Obj_CAD98* b, s32 c, s32 d, s32 e, void* f);

void func_001CAD98(Self_CAD98* a0, Obj_CAD98* a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    if (a0->f_C04 == 0) {
        func_001C5C10(a0, a1, a4, a5);
    }
    if (a1 != a0->vtbl[102](a0)) {
        if (a1->f18 != 0) {
            return;
        }
        if (func_001300E8(a1, 0x4C) == 0) {
            return;
        }
    }
    for (s32 i = 0; i < a0->count; i++) {
        Entry_CAD98* e = &a0->entries[i];
        if (func_00182FC8(e->obj) != 0) {
            if (a1->f538 & 0x10000000000ULL) {
                func_001879C0(a1->f3CC, a1, (u8*)a1 + 0x140, e->obj,
                              ((Obj_CAD98_3F0*)e->obj)->f3F0,
                              ((Obj_CAD98_3F0*)e->obj)->f3F8, 0, (u8*)a0 + 0xAAC);
            } else if (a3 != 0) {
                func_00186BA8(e->obj, a1, a2, a3, a4, (u8*)a0 + 0xAAC);
            }
        }
    }
}

extern u32 D_00275710;

void* func_0011E580(s32 a, void* b, s32 c, s32 d, s32 e);
void* func_001DBCC8(u32 a, void* fn, void* obj, s32 c, s32 d);
void func_001CB8B8(void);

void* func_001CB5B8(void* a0)
{
    void* obj = func_0011E580(0x89, a0, 0, 0x436, -1);
    func_001DBCC8(D_00275710, func_001CB8B8, obj, 0, 0);
    return obj;
}

struct Item_CB7A0;

struct Item_CB7A0 {
    u8 pad0[0x720];
    void* owner720;
};

struct Self_CB7A0 {
    u8 pad0[0x58];
    s32 n58;
    Item_CB7A0* arr5C[16];
    s32 cnt9C;
    Item_CB7A0* list9C[16];
    s32 nE0;
    Item_CB7A0* arrE4[16];
    s32 cnt124;
    Item_CB7A0* list124[16];
};

extern u32 D_00275710;

Item_CB7A0* func_0015A448(u32 a, Item_CB7A0* b, Self_CB7A0* c);

void func_001CB7A0(Self_CB7A0* a0)
{
    for (s32 i = 0; i < a0->cnt9C; i++) {
        Item_CB7A0* r = func_0015A448(D_00275710, a0->list9C[i], a0);
        if (r != 0) {
            s32 n = a0->n58;
            if ((u32)n < 16) {
                a0->arr5C[n] = r;
                a0->n58 = n + 1;
                r->owner720 = a0;
            }
        }
    }
    for (s32 i = 0; i < a0->cnt124; i++) {
        Item_CB7A0* r = func_0015A448(D_00275710, a0->list124[i], a0);
        if (r != 0) {
            s32 n = a0->nE0;
            if ((u32)n < 16) {
                a0->arrE4[n] = r;
                a0->nE0 = n + 1;
                            }
        }
    }
}

struct Obj_1CAEE0;
typedef void (*VFn_1CAEE0)(void* self, void* arg);

struct Obj_1CAEE0 {
    VFn_1CAEE0* vtbl;
};

s32 func_001300E8(void* obj, s32 kind);
void func_00175170(void* obj, s32 a, s32 b);

void func_001CAEE0(u8* self, Obj_1CAEE0* other)
{
    other->vtbl[0x90 / 4](other, self + 0xAB0);
    if (func_001300E8(other, 7) != 0) {
        func_00175170(other, 4, 0x2B);
    }
}

struct Obj_1CB328 {
    u8 pad0[0x72C];
    s32 f72C;
    s32 f730;
    u8 pad1[0x1C];
    void* f750;
    void* f754;
};

void func_0012E760(void* p);
s32 func_001C96B8(void* self);
void func_0012C9E8(void* a, void* b, f32 c, void* d, void* e, s32 f, s32 g);

void func_001CB328(Obj_1CB328* self, void* value)
{
    void* p;

    if (value == self->f750) {
        return;
    }
    p = self->f754;
    if (p != 0) {
        func_0012E760(p);
        self->f754 = 0;
    }
    self->f750 = value;
    if (func_001C96B8(self) == 0) {
        self->f730 = 0;
        self->f72C = self->f72C | 1;
    }
    p = self->f750;
    if (p != 0) {
        func_0012C9E8(p, self, 0.0f, (u8*)self + 0x140, (u8*)self + 0x918, 0, 0);
    }
}

s32 func_001CB3C0(void)
{
    return 1;
}

s32 func_001CB3C8(void)
{
    return 0;
}

struct Obj_1CB618 {
    u8 pad0[0x180];
    s32 f180;
};

void func_00182C18(void* self);

void func_001CB618(Obj_1CB618* self)
{
    func_00182C18(self);
    self->f180 = -1;
}

struct List_1CB648 {
    u8 pad0[0x58];
    u32 count;
    void* items[16];
};

void func_001CBEE8(void* self, s32 arg);

void func_001CB648(List_1CB648* self, void* value)
{
    u32 n;

    if (self->count == 0) {
        func_001CBEE8(self, 0);
    }
    n = self->count;
    if (n < 0x10) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

struct Host_001CA758 { u8 pad0[0x14]; void* source; u8 pad1[0xB74 - 0x18]; s32 mode; };
struct Item_001CA758 { u8 pad0[0x48]; s32 state; };

void* func_0015A418(void* source, s32 kind, void* arg, s32 mode);
void func_0012D398(void* item, Host_001CA758* host);
void func_00182ED8(void* item);

void* func_001CA758(Host_001CA758* self, void* arg)
{
    Item_001CA758* item = (Item_001CA758*)func_0015A418(self->source, 0x101, arg, self->mode);
    if (item != 0) {
        item->state = 0;
        func_0012D398(item, self);
        func_00182ED8(item);
    }
    return item;
}

struct Slot8_001CA7C0 { s32 key; s32 value; };
struct Slot12_001CA7C0 { s32 link; s32 key; s32 value; };
struct Owner_001CA7C0 {
    u8 pad0[0x758];
    Slot8_001CA7C0 early[17];
    u8 pad1[0xAC4 - 0x758 - 17 * 8];
    s32 lateCount;
    Slot12_001CA7C0 late[1];
};

void* func_001CA758(Owner_001CA7C0* self, s32 arg);

void func_001CA7C0(Owner_001CA7C0* self)
{
    s32 i = 16;
    Slot8_001CA7C0* slot = self->early;
    do {
        if (slot->key != -1) {
            slot->value = (s32)func_001CA758(self, slot->key);
            slot->key = -1;
        }
        i--;
        slot++;
    } while (i >= 0);

    s32 j = 0;
    if (self->lateCount > 0) {
        do {
            Slot12_001CA7C0* late = &self->late[j];
            if (late->key != -1) {
                late->value = (s32)func_001CA758(self, late->key);
                late->key = -1;
            }
            j++;
        } while (j < self->lateCount);
    }
}

struct Latch_001CA878 { u8 pad0[0xAF8]; s32 flag; s32 value; };

void func_001CA878(Latch_001CA878* self, s32 v)
{
    self->value = v;
    self->flag = 1;
}

struct Latch_001CA888 { u8 pad0[0xB04]; s32 flag; s32 value; };

void func_001CA888(Latch_001CA888* self, s32 v)
{
    self->value = v;
    self->flag = 1;
}

struct Slot_1CA898 { s32 key; s32 value; };
struct Table_1CA898 { u8 pad[0x870]; Slot_1CA898 slots[16]; };

s32 func_001CA600(s32 index);

void func_001CA898(Table_1CA898* self, s32 index, s32 value)
{
    if (func_001CA600(index))
        self->slots[index].key = value;
}

struct Entry_1CA960 { s32 first; s32 middle; s32 last; };
struct Queue_1CA960 { u8 pad[0xA78]; u32 count; Entry_1CA960 entries[4]; };

void func_001CA960(Queue_1CA960* self, s32 a, s32 b)
{
    u32 n = self->count;
    if (n < 4) {
        self->count = n + 1;
        Entry_1CA960* e = &self->entries[n];
        e->first = a;
        e->last = b;
    }
}

struct Set_1CA998 {
    u8 pad0[0x14];
    void* owner;
    u8 pad1[0x924 - 0x18];
    s32 index;
    s32 found;
    u8 pad2[0xA60 - 0x92C];
    s32 cleared;
};

s32 func_0015A448(void* owner, s32 index, Set_1CA998* self);

void func_001CA998(Set_1CA998* self, s32 index)
{
    s32 v;
    if (index == -1) {
        v = 0;
    } else {
        v = func_0015A448(self->owner, index, self);
        if (v == 0)
            return;
    }
    if (v != self->found)
        self->cleared = 0;
    self->index = index;
    self->found = v;
}

typedef s32 (*VFn_1CAAD0)(void* self);

struct Obj_1CAAD0 {
    VFn_1CAAD0* vtbl;
};

void func_001CAAD0(Obj_1CAAD0* self, s32* out)
{
    *out = self->vtbl[102](self);
}

struct Obj_1CAB00 {
    u8 pad0[0xB40];
    s32 flag_B40;
    u8 pad1[4];
    s32 value_B48;
};

void func_001CAB00(Obj_1CAB00* self, s32 value)
{
    self->value_B48 = value;
    self->flag_B40 = 1;
}

struct Obj_1C84C0 { u8 pad0[0x92C]; s32 a; s32 b; u8 pad1[0xA60 - 0x934]; s32 c; };

s32 func_001C84C0(Obj_1C84C0* self)
{
    s32 result = 0;
    if (self->c != 0) {
        result = self->b == self->a;
    }
    return result;
}

struct Inner_001C9CF8 { u8 pad0[0x8]; void* p8; };
struct Owner_001C9CF8 { u8 pad0[0x7E0]; Inner_001C9CF8* inner; u8 pad1[0xA60 - 0x7E4]; s32 f_A60; u8 pad2[0xB8C - 0xA64]; s32 f_B8C; u8 pad3[0xBA4 - 0xB90]; s32 f_BA4; };

f32 func_0012CCC0(void* obj, s32 id);
void func_0012F0A0(void* obj, s32 a1, f32 fa, f32 fb);

void func_001C9CF8(Owner_001C9CF8* self)
{
    self->f_B8C = 0;
    self->f_A60 = 0;
    f32 r = func_0012CCC0(self->inner->p8, 0x1B1);
    func_0012F0A0(self->inner, 0, r, 1.0f);
    self->f_BA4 = 0;
}

void func_001C49C8(void);

void func_001CA5E0(void)
{
    func_001C49C8();
}

struct Obj_1C8BC0 { u8 pad[0x140]; };

void func_001454E0(void* a, void* b, f32* x, f32* y, s32 flag);
void func_001C7AE0(void* self, f32 x, f32 y);

void func_001C8BC0(Obj_1C8BC0* self)
{
    f32 x;
    f32 y;
    func_001454E0((u8*)self + 0xA40, (u8*)self + 0x140, &x, &y, 0);
    func_001C7AE0(self, x, y);
}

s32 func_001CA600(s32 index)
{
    return (u32)index < 17;
}

s32 func_001CA600(s32 index);

void func_001CA608(u8* self, s32 index, s32 value)
{
    if (func_001CA600(index)) {
        *(s32*)(self + (index << 3) + 0x758) = value;
    }
}

struct Obj_001C8D40 { u8 pad[0x92C]; s32 value; s32 limit; u8 pad2[0xA60 - 0x934]; s32 enabled; };
void func_001C8D40(Obj_001C8D40* self, s32* out) { if (self->enabled && self->limit >= self->value - 2) { *out = 1; return; } *out = 0; }

struct Obj_001C96B8 { u8 pad[0x720]; u32 object; };
s32 func_001C96B8(Obj_001C96B8* self) { if (!self->object) return 3; return *(s32*)(self->object + 0x50); }

struct Obj_001C9A48 { u8 pad[0xBD8]; u32 value; };
s32 func_001C9A48(Obj_001C9A48* self) { return self->value != 0; }

struct Obj_001CAD28 { u8 pad[0x74C]; f32 value; };
void func_001CAD28(Obj_001CAD28* self, f32 value) { self->value = value * 0.017453294f; }

struct Entry_001CAD60 { s32 a, b, c, d; };
struct Obj_001CAD60 { u8 pad[0x7E4]; u32 count; Entry_001CAD60 entries[8]; };
void func_001CAD60(Obj_001CAD60* self, s32 a, s32 b, s32 c, s32 d) { if (self->count < 8) { Entry_001CAD60* e = &self->entries[self->count]; self->count++; e->a = a; e->b = b; e->c = c; e->d = d; } }

struct Obj_001CB6A8 { u8 pad[0x9C]; u32 count; s32 items[16]; };
void func_001CB6A8(Obj_001CB6A8* self, s32 value) { u32 i = self->count; if (i < 16) { self->items[i] = value; self->count = i + 1; } }

struct Obj_001CB6D0 { u8 pad[0x124]; u32 count; s32 items[16]; };
void func_001CB6D0(Obj_001CB6D0* self, s32 value) { u32 i = self->count; if (i < 16) { self->items[i] = value; self->count = i + 1; } }

struct Obj_001CBE20 { u8 pad[0x168]; s32 count; s32 items[4]; };
void func_001CBE20(Obj_001CBE20* self, s32 value) { for (s32 i = 0; i < self->count; i++) if (value == self->items[i]) return; s32 i = self->count; if ((u32)i < 4) { s32 next = i + 1; self->items[i] = value; self->count = next; } }

struct Node_1C8FD0 { u8 pad[0xB88]; s32 f_B88; };

void func_001C8F20(Node_1C8FD0* self, s32 mode, s32 value);

void func_001C8FD0(Node_1C8FD0* self, s32 mode, s32 value)
{
    if (mode == -1) {
        self->f_B88 = 0;
    } else {
        self->f_B88 = 1;
        func_001C8F20(self, mode, value);
    }
}

struct Pair_1CA658 { s32 a; s32 b; };
struct Node_1CA658 { u8 pad[0x758]; Pair_1CA658 e[1]; };

s32 func_001CA600(s32 index);
s32 func_001CA758(Node_1CA658* self, s32 id);

void func_001CA658(Node_1CA658* self, s32 index, s32 value)
{
    if (func_001CA600(index)) {
        Pair_1CA658* p = &self->e[index];
        p->a = value;
        if (value == -1) {
            p->b = 0;
        } else {
            p->b = func_001CA758(self, value);
        }
    }
}

struct Node_1CAA08 {
    u8 pad0[0xB40];
    void* fB40;
    u8 pad1[0xB48 - 0xB44];
    void* fB48;
    u8 pad2[0xB50 - 0xB4C];
    void* fB50;
    void* fB54;
};

struct Obj_1CAA08 {
    void* vtbl;
};

typedef s32 (*VFnA_1CAA08)(void* self);
typedef void (*VFnB_1CAA08)(void* self, void* arg);

void* func_001925F0(void);

void* func_001CAA08(Node_1CAA08* self)
{
    void* s0;
    if (self->fB50 != 0) {
        s0 = self->fB50;
    } else if (self->fB40 != 0) {
        s0 = self->fB48;
    } else {
        s0 = func_001925F0();
    }
    void* v = func_001925F0();
    if (v != 0 && v == s0) {
        s32 r = ((VFnA_1CAA08*)((Obj_1CAA08*)s0)->vtbl)[81](s0);
        s0 = (r == 2) ? 0 : s0;
    }
    void* a0 = self->fB54;
    if (s0 == a0) {
        return s0;
    }
    if (a0 != 0) {
        ((VFnB_1CAA08*)((Obj_1CAA08*)a0)->vtbl)[28](a0, self);
    }
    if (s0 != 0) {
        ((VFnB_1CAA08*)((Obj_1CAA08*)s0)->vtbl)[27](s0, self);
    }
    self->fB54 = s0;
    return s0;
}

void func_001CBE20(void* self, s32 value);

struct Obj_1CAD40 { u8 pad0[0x720]; void* f720; };

void func_001CAD40(Obj_1CAD40* self, s32 value)
{
    func_001CBE20(self->f720, value);
}

typedef s32 (*VFn_1CBAF8)(void* self);
struct Item_1CBAF8 { VFn_1CBAF8* vtbl; };
struct Obj_1CBAF8 { u8 pad0[0x5C]; Item_1CBAF8* f5C; };

s32 func_001CBAF8(Obj_1CBAF8* self)
{
    Item_1CBAF8* item = self->f5C;
    return item->vtbl[102](item);
}

struct Obj_1CBB20 { u8 pad0[0x50]; s32 f50; u8 pad1[0x17C - 0x54]; s32 f17C; u8 pad2[0x188 - 0x180]; s32 f188; };

s32 func_001CBCB8(void* self);
s32 func_001CBB88(void* self);
void func_001CBEE8(void* self, s32 arg);

void func_001CBB20(Obj_1CBB20* self)
{
    s32 v;

    self->f17C = 0;
    if (self->f50 != 3) {
        self->f188 = func_001CBCB8(self);
        for (;;) {
            v = func_001CBB88(self);
            if (v == self->f50) {
                break;
            }
            func_001CBEE8(self, v);
        }
    }
}

struct Self_1CBE70 { u8 pad[0x168]; s32 count; void* items[1]; };

void func_00123AB0(void* object, s32 mode);

void func_001CBE70(Self_1CBE70* self, s32 mode)
{
    for (s32 i = 0; i < self->count; i++) {
        func_00123AB0(self->items[i], mode);
    }
}

struct Sub_1C8D78 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x2D0];
    void* f2DC;
};

struct Obj_1C8D78 {
    u8 pad0[0x1EC];
    void* f1EC;
    void* f1F0;
    u8 pad1[0x560];
    void* f754;
    u8 pad2[0x31C];
    Sub_1C8D78* fA74;
};

struct Node_1C8D78 {
    u8 pad0[0x10];
    u8 b10;
    u8 b11;
};

void func_0012C288(void* self, void* a1, s32 a2, void* a3, s32 a4, void* a5, f32 f0, f32 f1);
void func_0012F810(void* a0, Sub_1C8D78* a1);
s32 func_00183458(Obj_1C8D78* a);
void* func_0012D570(void* a0, s32 a1);

void func_001C8D78(Obj_1C8D78* self)
{
    Sub_1C8D78* sub = self->fA74;
    if (sub->f2DC != 0) {
        s32 pair[2];
        pair[0] = sub->f8;
        pair[1] = (s32)self;
        func_0012C288(sub->f2DC, self, 1, pair, 1, &self->f754, 0.0f, 1.0f);
        func_0012F810(self->f754, self->fA74);
        Node_1C8D78* node = (Node_1C8D78*)func_0012D570(self->f754, func_00183458(self));
        if ((void*)node == self->f1EC) {
            node->b10 = 5;
        }
        if ((void*)node == self->f1F0) {
            node->b11 = 5;
        }
    }
}

typedef s32 (*VFn_1CAC30)(void* self, void* out);

struct Obj_1CAC30 {
    VFn_1CAC30* vtbl;
    u8 pad4[0xBE4];
    f32 fBE8;
    u8 padBEC[0x18];
    s32 fC04;
};

struct Out_1CAC30 {
    u8 pad0[0x94];
    f32 f94;
    f32 f98;
};

extern f32 D_00274CF4[];
extern f32 D_00274CF8[];

void func_001CAC30(Obj_1CAC30* self, Out_1CAC30* out)
{
    if (self->fC04 != 0) {
        f32 a = D_00274CF4[0];
        f32 b = D_00274CF8[0];
        out->f94 = a;
        out->f98 = b;
    } else {
        if (self->vtbl[90](self, out) != 0) {
            f32 t = self->fBE8;
            out->f98 = 0.0f;
            out->f94 = t;
        } else {
            out->f94 = 0.0f;
            out->f98 = 0.0f;
        }
    }
}

extern u8 D_00262E10[];

struct Obj_1CB578 { u8 pad0[0xB7C]; s32 fB7C; s32 fB80; };
struct Glob_1CB578 { u8 pad0[0x275C]; s32 f275C; };

s32 func_001CB578(Obj_1CB578* self)
{
    s32 r = 0;
    Glob_1CB578* g;
    if (self->fB7C != 0) {
        goto set;
    }
    if (self->fB80 != 0) {
        r = 1;
    } else {
        g = *(Glob_1CB578**)D_00262E10;
        if (g != 0 && g->f275C != 0) {
set:
            r = 1;
        }
    }
    return r;
}

void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_001CBB20(void* self);

struct Obj_1CBAA0 { u8 pad0[0x50]; s32 f50; u8 pad1[0x17C - 0x54]; s32 f17C; };

void func_001CBAA0(Obj_1CBAA0* a0)
{
    Obj_1CBAA0* self = a0;
    if (self->f50 == 3) {
        return;
    }
    if (self->f17C != 0) {
        return;
    }
    {
        s32 one = 1;
        void* owner = *(void**)&D_00275710;
        self->f17C = one;
        func_001DBCC8(owner, (void*)(void (*)(void*))func_001CBB20, self, -1, 0);
    }
}

struct Obj_1C9990 { u8 pad00[8]; s32 flags08; };
struct __attribute__((aligned(16))) Quad_1C9990 { s32 a, b, c, d; };
typedef s32 (*VFn_1C9990)(void* self, s32 arg);
struct Self_1C9990 { VFn_1C9990* vtbl00; u8 pad04[0x13C]; Quad_1C9990 q140; };
struct Req_1C9990 { s32 kind00; Obj_1C9990** ref04; };
struct Frame_1C9990 { Obj_1C9990** ref00; Self_1C9990* self04; u8 pad08[8]; s32 code10; u8 pad14[0x0C]; Quad_1C9990 q20; s32 tail30[4]; };

void func_001F5C0C(void* p, s32 v, s32 n);
s32 func_00177838(void* p, s32 a, s32 b);

s32 func_001C9990(Self_1C9990* self, Req_1C9990* req)
{
    Frame_1C9990 f;

    if (self->vtbl00[0x4F](self, req->kind00) != 0) return 0;
    func_001F5C0C(&f, 0, 0x40);
    f.ref00 = req->ref04;
    f.self04 = self;
    if (req->kind00 == 4) {
        f.code10 = req->kind00;
    } else if (f.ref00 == 0) {
        f.code10 = 2;
    } else if ((*f.ref00)->flags08 & 0x20) {
        f.code10 = 0x10;
    } else {
        f.code10 = 2;
    }
    f.q20 = self->q140;
    return func_00177838(&f, 0, 0) != 0;
}

struct Node_1CB8B8 {
    u8 pad0[0x2C];
    void* f2C;
    u8 pad1[0x2E0 - 0x30];
    s32 f2E0;
    u8 pad2[0x328 - 0x2E4];
    void* f328;
    u8 pad3[0x750 - 0x32C];
    void* f750;
};
struct Self_1CB8B8 {
    u8 pad0[0x58];
    s32 count;
    Node_1CB8B8* list[16];
};
struct Ent_1CB8B8 {
    s32 count;
    Node_1CB8B8** items;
};

void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D6A8(s32 size);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_001CB8B8(Self_1CB8B8* self)
{
    Ent_1CB8B8* arr;
    s32 i;
    s32 j;
    s32 k;
    s32 m;

    func_0018D608();
    arr = (Ent_1CB8B8*)func_0018D6A8(self->count * 8);
    for (i = 0; i < self->count; i++) {
        Node_1CB8B8* node = self->list[i];
        if (node->f750 != 0) {
            func_0012D1B0(node->f750, node, &arr[i].count, (void**)&arr[i].items);
        }
    }
    for (i = 0; i < self->count; i++) {
        Ent_1CB8B8* e = &arr[i];
        for (j = 0; j < e->count; j++) {
            Node_1CB8B8* node = e->items[j];
            if (node->f328 == 0) {
                node->f328 = func_001EFA30();
                ((Node_1CB8B8*)node->f328)->f2C = self;
                func_001EFA60(node->f328, node);
                if (node->f2E0 != -1) {
                    for (k = i + 1; k < self->count; k++) {
                        Ent_1CB8B8* e2 = &arr[k];
                        for (m = 0; m < e2->count; m++) {
                            Node_1CB8B8* item = e2->items[m];
                            if (item->f2E0 == node->f2E0) {
                                item->f328 = node->f328;
                                func_001EFA60(node->f328, item);
                            }
                        }
                    }
                }
            }
        }
    }
    func_0018D6F0();
}

struct __attribute__((aligned(16))) Quad_CBCB8 { s32 a, b, c, d; };

typedef s32 (*VFn_CBCB8)(void* self);

struct Item_CBCB8 {
    VFn_CBCB8* vtbl;
};

struct Self_CBCB8 {
    u8 pad0[0x40];
    Quad_CBCB8 f40;
    u8 pad1[0x58 - 0x50];
    s32 count;
    Item_CBCB8* items[1];
};

void* func_001CBAF8(Self_CBCB8* self);

s32 func_001CBCB8(Self_CBCB8* self)
{
    s32 i = 0;
    Item_CBCB8** p = self->items;
    for (;;) {
        if (!(i < self->count)) {
            return 0;
        }
        Item_CBCB8* it = *p;
        if (it->vtbl[91](it) != 0) {
            break;
        }
        p++;
        i++;
    }
    if (!(i < self->count)) {
        return 0;
    }
    {
        void* r = func_001CBAF8(self);
        if (r != 0) {
            self->f40 = *(Quad_CBCB8*)((u8*)r + 0x140);
        }
    }
    return 1;
}

struct Inner_1C84E8 { u8 pad[8]; u32 flags; };
struct Obj_1C84E8 { Inner_1C84E8* inner; u8 pad0[0x50 - 4]; void* p50; u8 pad1[0x360 - 0x54]; f32 f360; u8 pad2[0x538 - 0x364]; u64 f538; };

s32 func_001300E8(void* node, s32 kind);

s32 func_001C84E8(void* unused, Obj_1C84E8* self)
{
    if ((self->f538 & (1ULL << 43)) != 0) {
        if ((self->inner->flags & 0x80) == 0)
            return 0;
        if (self->f360 == 0.0f)
            return 0;
    }
    if (func_001300E8(self->p50, 5) != 0 || func_001300E8(self->p50, 0x40) != 0 || func_001300E8(self->p50, 0x41) != 0)
        return 0;
    return 1;
}

struct List_1CB6F8 { u8 pad0[0x58]; s32 count; s32 items[16]; };

void func_001CBEE8(void* self, s32 arg);
void func_0018D800(void* dst, void* src, s32 count);

void func_001CB6F8(List_1CB6F8* self, s32 value)
{
    s32 i = 0;
    if (self->count > 0) {
        for (; i < self->count; i++) {
            if (self->items[i] == value) break;
        }
        if (i >= self->count) return;
        s32 n = self->count;
        if (i < n) {
            s32 m = n - 1;
            self->count = m;
            s32* d = &self->items[i];
            func_0018D800(d, d + 1, (m - i) * 4);
            if (self->count <= 0) {
                func_001CBEE8(self, 3);
            }
        }
    }
}

struct Obj_CBD58;
typedef s32 (*VFn_CBD58)(void* self);

struct Obj_CBD58 {
    VFn_CBD58* vtbl;
};

struct Self_CBD58 {
    u8 pad0[0x58];
    s32 count;
    Obj_CBD58* items[1];
};

s32 func_001CBD58(Self_CBD58* a0)
{
    s32 result = 1;
    for (s32 i = 0; i < a0->count; i++) {
        Obj_CBD58* o = a0->items[i];
        s32 v = o->vtbl[92](o);
        switch (v) {
        case 1: break;
        case 0: result = 0; break;
        case 2: return 1;
        }
    }
    return result;
}

struct Inner_1CACB0 { u8 pad0[0x88]; f32 f88; };
struct Out_1CACB0 { Inner_1CACB0* p0; u8 pad1[0x30 - 4]; s32 f30; };
struct Self_1CACB0 { u8 pad0[0xC04]; s32 fC04; };

void func_001C5388(Self_1CACB0*, s32, Out_1CACB0*);

void func_001CACB0(Self_1CACB0* self, s32 flags, Out_1CACB0* out)
{ func_001C5388(self, flags, out);
    if (self->fC04 != 0) { if ((flags & 0x12) == 0x12) { if (0.7f < out->p0->f88) { out->f30 = 0; } } } }

struct Slot_001CA6D0 { s32 key; s32 value; };
struct Table_001CA6D0 { u8 pad[0x75C]; Slot_001CA6D0 slots[1]; };

s32 func_001CA600(s32 index);

s32 func_001CA6D0(Table_001CA6D0* self, s32 index)
{
    if (func_001CA600(index) == 0)
        return 0;
    return self->slots[index].key;
}

extern f32 D_0024D828;

struct Sub_1C9A58 {
    u8 pad00[0x34];
    f32 f34;
};
struct Child_1C9A58 {
    u8 pad00[0x8];
    Sub_1C9A58* sub8;
    u8 pad0C[0x4];
    f32 f10;
    f32 f14;
};
struct Obj_1C9A58 {
    u8 pad000[0x724];
    u32 f724;
    u8 pad728[0x4];
    u32 flags72C;
    void* f730;
    u8 pad734[0xAC];
    Child_1C9A58* f7E0;
};

void func_0012E760(Child_1C9A58* c);
void func_001C8F20(Obj_1C9A58* self, void* arg, s32 mode);

void func_001C9A58(Obj_1C9A58* self) {
    if (self->flags72C == 0) {
        return;
    }
    if (self->flags72C & 2) {
        if (self->f7E0 != 0) {
            if (self->f724 != 0xB) {
                func_0012E760(self->f7E0);
                self->f7E0 = 0;
            } else {
                self->f7E0->f14 = self->f7E0->sub8->f34;
                self->f7E0->f10 = D_0024D828;
            }
        }
        s32 m = -3;
        self->flags72C &= m;
    }
    if (self->flags72C & 1) {
        func_001C8F20(self, self->f730, 0);
    }
}

struct Vt_1CBEE8 { u8 pad0[0x16C]; s32 (*fn16C)(void* self); };
struct Item_1CBEE8 {
    Vt_1CBEE8* vt;
    u8 pad4[0xBEC];
    f32 fBF0;
    f32 fBF4;
    f32 fBF8;
    f32 fBFC;
    f32 fC00;
};
struct Obj_1CBEE8 {
    u8 pad0[0x50];
    s32 f50;
    f32 f54;
    s32 cnt58;
    Item_1CBEE8* items[1];
    u8 pad60[0x124];
    void* f184;
};

extern f32 D_00261858[];
extern f32 D_00274D18[];
extern f32 D_00274D08[];
extern f32 D_00274D10[];

f32 func_001EAAE0(f32 a, f32 b);
void func_001BF0D8(void* p);
void* func_001BEEF8(s32 kind);
void func_001CBE70(Obj_1CBEE8* self, s32 a);
void func_001CC120(Obj_1CBEE8* self);

void func_001CBEE8(Obj_1CBEE8* self, s32 ns)
{
    s32 i;
    if (self->f50 == ns)
        return;
    switch (self->f50) {
    case 2:
        func_001BF0D8(self->f184);
        i = 0;
        self->f184 = 0;
        if (self->cnt58 > 0) {
            Item_1CBEE8** p = self->items;
            do {
                Item_1CBEE8* it = *p;
                f32 t = D_00261858[1];
                i++;
                f32 r = func_001EAAE0(D_00274D18[0], D_00274D18[1]);
                it->fC00 = D_00261858[1] + r;
                p++;
            } while (i < self->cnt58);
        }
        break;
    case 1: {
        s32 j = 0;
        if (self->cnt58 > 0) {
            Item_1CBEE8** p = self->items;
            do {
                f32 t = D_00261858[1];
                j++;
                f32 r = func_001EAAE0(D_00274D08[0], D_00274D08[1]);
                (*p)->fBF4 = D_00261858[1] + r;
                p++;
            } while (j < self->cnt58);
        }
        break;
    }
    }
    switch (ns) {
    case 2:
        i = 0;
        self->f184 = func_001BEEF8(0x6B);
        func_001CBE70(self, 0);
        if (self->cnt58 > 0) {
            Item_1CBEE8** p = self->items;
            do {
                Item_1CBEE8* it = *p;
                if (it->vt->fn16C(it) != 0) {
                    it->fBF8 = D_00261858[1];
                } else {
                    f32 r = func_001EAAE0(D_00274D10[0], D_00274D10[1]);
                    it->fBF8 = D_00261858[1] + r;
                }
                i++;
                p++;
            } while (i < self->cnt58);
        }
        break;
    case 1:
        func_001CC120(self);
        break;
    case 0:
        func_001CBE70(self, 1);
        break;
    case 3:
        func_001CBE70(self, 2);
        break;
    }
    self->f50 = ns;
    self->f54 = D_00261858[1];
}

struct Self_1C8C08;
struct __attribute__((aligned(16))) Quad_1C8C08 { s32 a, b, c, d; };
struct Tgt_1C8C08;
typedef void (*TFn_1C8C08)(Tgt_1C8C08* t, Self_1C8C08* s, f32 x, f32 y, s32 z, void* out, s32 w);
struct Tgt_1C8C08 { TFn_1C8C08* vtbl; };
struct Res_1C8C08 { s32 pad0; Tgt_1C8C08* t; };
typedef s32 (*VFn_1C8C08)(Self_1C8C08* s);
struct Self_1C8C08 {
    VFn_1C8C08* vtbl;
    u8 pad004[0x18C];
    Quad_1C8C08 f190;
    u8 pad1A0[0x584];
    s32 f724;
    u8 pad728[0x28];
    void* f750;
    u8 pad754[0x1C0];
    f32 f914;
    f32 f918;
    f32 f91C;
    s32 f920;
};

void func_001C8418(Self_1C8C08* self, void* p);
void func_0012C9E8(f32 c, void* a, Self_1C8C08* b, void* d, void* e, void* f, s32 g);
Res_1C8C08* func_0012CCE8(void* a, Self_1C8C08* b);

void func_001C8C08(Self_1C8C08* self, s32 flag)
{
    Quad_1C8C08 q;
    switch (self->f724) {
    case 7:
    case 10:
    case 12:
    case 13:
    case 14: {
        s32 v = self->vtbl[0x198 / 4](self);
        if (v != 0) func_001C8418(self, (u8*)v + 0x140);
        break;
    }
    case 4:
        if (flag != 0) {
            if (self->f750 != 0) {
                switch (self->f920) {
                case 0:
                    func_0012C9E8(self->f918, self->f750, self, (u8*)self + 0x140, (u8*)self + 0x914, &q, 0);
                    break;
                case 1: {
                    self->f914 = self->f918;
                    Tgt_1C8C08* t = func_0012CCE8(self->f750, self)->t;
                    t->vtbl[0](t, self, self->f914, 1.0f, 0, &q, 0);
                    break;
                }
                }
                self->f91C = 1.0f;
            } else {
                q = self->f190;
            }
            func_001C8418(self, &q);
        }
        break;
    case 5:
        if (flag != 0) func_001C8418(self, (u8*)self + 0x900);
        break;
    }
}

struct Obj_1C8E28;
typedef s32 (*VFn_1C8E28)(Obj_1C8E28*);
struct Obj_1C8E28 {
    VFn_1C8E28* vtbl;
    u8 pad4[0x638 - 4];
    f32 f638;
    u8 pad63C[0x724 - 0x63C];
    s32 mode;
    u8 pad728[0x754 - 0x728];
    s32 i754;
    u8 pad758[0xA74 - 0x758];
    u8* p74;
    u8 padA78[0xB1C - 0xA78];
    s32 iB1C;
};

extern f32 D_00261860;
s32 func_00128230(Obj_1C8E28* self);
void func_001C7BE8(Obj_1C8E28* self);
void func_00128598(f32 a, f32 b, Obj_1C8E28* self, s32 c, s32 d, f32* e, f32* f, f32* g);
void func_001C7AE0(Obj_1C8E28* self, f32 x, f32 y);
void func_001EFC98(void* n);
void func_001C8920(Obj_1C8E28* self);
void func_001C8BC0(Obj_1C8E28* self);

void func_001C8E28(Obj_1C8E28* self)
{
    self->vtbl[102](self);
    switch (self->mode) {
    case 0:
    case 16:
        break;
    case 1:
    case 2:
        if (func_00128230(self) != 0)
            func_001C7BE8(self);
        break;
    case 3:
        if (self->i754 != 0) {
            f32 out[3];
            f32 zero = 0.0f;
            out[1] = zero;
            func_00128598(D_00261860, self->f638, self, 0, 0, &out[0], self->iB1C ? &out[1] : 0, &out[2]);
            f32 y = out[1];
            func_001C7AE0(self, out[0], y);
        }
        func_001EFC98(*(void**)(self->p74 + 0x328));
        break;
    case 4:
    case 5:
    case 12:
        func_001C8920(self);
        break;
    case 7:
    case 10:
    case 13:
    case 14:
        func_001C8BC0(self);
        break;
    }
}

struct Other_1C9D50 { u8 pad0[0x50]; s32 f50; };
struct Self_1C9D50 {
    u8 pad0[0x50];
    s32 f50;
    u8 pad54[0x724 - 0x54];
    s32 mode;
    u8 pad728[0xB0C - 0x728];
    void* fB0C;
    u8 padB10[0xB54 - 0xB10];
    s32 fB54;
};
s32 func_001A8820(void* p, Other_1C9D50* v);

s32 func_001C9D50(Self_1C9D50* self, s32 key, Other_1C9D50* other)
{
    if (key != self->fB54)
        return 0;
    switch (self->mode) {
    case 10:
    case 11:
    case 16:
        goto ret0;
    case 12:
    case 13:
    case 14:
        goto ret1;
    }
    if (!other)
        goto ret0;
    if (other->f50 == self->f50)
        goto ret1;
    if (!self->fB0C)
        goto ret0;
    if (!func_001A8820(self->fB0C, other))
        goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}
