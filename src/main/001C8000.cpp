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
