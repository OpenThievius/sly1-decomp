// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

s32 func_00160850(void* obj);

s32 func_001DD690(void* self, void* obj)
{
    return func_00160850(obj) & 0x1;
}

s32 func_00160850(void* obj);

s32 func_001DD6B0(void* self, void* obj)
{
    return func_00160850(obj) & 0x2;
}

s32 func_00160850(void* obj);

s32 func_001DD6D0(void* self, void* obj)
{
    return func_00160850(obj) & 0x4;
}

s32 func_00160850(void* obj);

s32 func_001DD6F0(void* self, void* obj)
{
    return func_00160850(obj) & 0x8;
}

struct Slot_1DD7E8 { s32 key; s32 value; };
struct Slots_1DD7E8 { u8 pad[0x44]; Slot_1DD7E8 slots[4]; };

void* func_00160810(void* obj);

void func_001DD7E8(void* self, void* obj, s32 key, s32 value)
{
    Slots_1DD7E8* t = (Slots_1DD7E8*)func_00160810(obj);
    if (t) {
        Slot_1DD7E8* found = 0;
        for (u32 i = 0; i < 4; i++) {
            Slot_1DD7E8* p = &t->slots[i];
            if (found == 0 && p->key == 0) {
                found = p;
                continue;
            }
            if (p->key == key) {
                found = p;
                break;
            }
        }
        if (found) {
            found->key = key;
            found->value = value;
        }
    }
}

extern void* D_002623C0;

s32 func_001DD8E8(void* self, s32 index)
{
    s32 off = index * 0x44C;
    u8* base = (u8*)D_002623C0;
    return *(s32*)(base + off + 0x458) & 1;
}

extern void* D_002623C0;

s32 func_001DD908(void* self, s32 index)
{
    s32 off = index * 0x44C;
    u8* base = (u8*)D_002623C0;
    return *(s32*)(base + off + 0x458) & 0x20;
}

extern void* D_002623C0;
void func_00160B28(void* p);

void func_001DD928(void* self)
{
    func_00160B28(D_002623C0);
}

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 value, u32 size);

void* func_001DC0C8(u8* self)
{
    void* p = func_001B5EC0(self + 0x1C0C);
    func_001F5C0C(p, 0, 0x8);
    return p;
}

struct Node_DC7B0 {
    u8 pad[8];
    Node_DC7B0* next;
    Node_DC7B0* prev;
};

void func_001DC7B0(Node_DC7B0* node, Node_DC7B0** head)
{
    node->next = *head;
    node->prev = 0;
    if (*head != 0) {
        (*head)->prev = node;
    }
    *head = node;
}

extern void* D_002622CC;
extern void* D_00264260;

struct Obj_DD5F8 {
    u8 pad[0x1D6C];
    f32 f1D6C;
};

void func_001DD5F8(Obj_DD5F8* self, f32 v)
{
    self->f1D6C = v;
    D_00264260 = D_002622CC;
}

extern u8 D_00275C60[];
extern void* D_002623C8;

struct Obj_DD9D8 {
    u8 pad[0x10];
    f32 f10;
};

f32 func_001EB0F8(void* p);

void func_001DD9D8()
{
    f32 r = func_001EB0F8(D_00275C60);
    ((Obj_DD9D8*)D_002623C8)->f10 = r;
}

struct Obj_DDAB8 {
    u8 pad[0x234C];
    f32 f234C;
    f32 f2350;
};

void func_001DDAB8(Obj_DDAB8* self, f32 v)
{
    self->f2350 = v;
    self->f234C = v;
}

void func_001BEEF8(void* p);

void func_001DDBF8(void* self, void* p)
{
    func_001BEEF8(p);
}

extern void* D_002623C0;

struct Obj_DDCB0 {
    u8 pad[0x19E4];
    s32 f19E4;
};

void func_001DDCB0(void* self, s32* out)
{
    *out = ((Obj_DDCB0*)D_002623C0)->f19E4;
}

struct Obj_DF290 {
    u8 pad[0x728];
    s32 f728;
};

void func_001922E8(void* self, void* p);

void func_001DF290(Obj_DF290* self, void* p)
{
    func_001922E8(self, p);
    if (p == 0) {
        self->f728 = 0;
    }
}

extern u8 D_002758D0[];

void func_00152438(void* p, s32 n);

void func_001DFD48()
{
    func_00152438(D_002758D0, 0x80);
}
