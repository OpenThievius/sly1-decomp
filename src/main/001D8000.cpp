// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001B9F30(void);

void func_001DAE48(void)
{
    func_001B9F30();
}

void func_001C0C08(void* a, void* b);

void func_001DBAC0(void* self, void* a, void* b)
{
    func_001C0C08(a, b);
}

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 value, u32 size);

void* func_001DBBD8(u8* self)
{
    void* p = func_001B5EC0(self + 0x1B14);
    func_001F5C0C(p, 0, 0x14);
    return p;
}

void* func_001C0C68(void* a, void* b);

void* func_001DBB00(void* unused, void* a1, void* a2)
{
    return func_001C0C68(a1, a2);
}

void* func_001B5EC0(void* p);
void func_001F5C0C(void* p, s32 a, s32 b);

void* func_001DBB50(u8* self)
{
    void* p = func_001B5EC0(self + 0x1B08);
    func_001F5C0C(p, 0, 16);
    return p;
}

struct Node_001DBB90 { u8 pad[0xC]; Node_001DBB90* next; };

void func_001B5F28(void* list, void* item);

void func_001DBB90(u8* self, Node_001DBB90* node)
{
    if (node) {
        do {
            Node_001DBB90* next = node->next;
            func_001B5F28(self + 0x1B08, node);
            node = next;
        } while (node);
    }
}

f32 func_001D86F8(f32 x, f32 lim, f32 base)
{
    f32 d = lim - base;
    if (x * 0.5f < d)
        d = d - x;
    else if (d < x * -0.5f)
        d = d + x;
    return d;
}

struct Node_1DBC18 { u8 pad[0x10]; Node_1DBC18* next; };

void func_001B5F28(void* list, void* item);

void func_001DBC18(u8* self, Node_1DBC18* node)
{
    while (node != 0) {
        Node_1DBC18* next = node->next;
        func_001B5F28(self + 0x1B14, node);
        node = next;
    }
}

struct Entry_1DBCC8 { s32 k0; s32 k1; s32 k2; s32 k3; Entry_1DBCC8* next; };
struct Owner_1DBCC8 { u8 pad[0x1EC8]; Entry_1DBCC8* head; Entry_1DBCC8* tail; };

void* func_001DBBD8(void* self);

Entry_1DBCC8* func_001DBCC8(Owner_1DBCC8* self, s32 a, s32 b, s32 c, s32 d)
{
    Entry_1DBCC8* e = (Entry_1DBCC8*)func_001DBBD8(self);
    e->k0 = a;
    e->k1 = b;
    e->k2 = c;
    e->k3 = d;
    if (self->tail != 0) self->tail->next = e;
    else self->head = e;
    self->tail = e;
    return e;
}

typedef void (*VFn_1D92F0)(void* self);
struct Sub_1D92F0 { VFn_1D92F0* vtbl; };
struct Ctrl_1D92F0 {
    u8 pad0[0x854];
    f32 f854;
    s32 n858;
    u8 pad1[0xB14 - 0x85C];
    Sub_1D92F0* sub;
};

extern f32 D_0026185C;

void func_001D92F0(Ctrl_1D92F0* self)
{
    self->f854 = D_0026185C;
    self->n858 = self->n858 - 1;
    Sub_1D92F0* s = self->sub;
    if (s != 0) {
        s->vtbl[6](s);
    }
}

typedef void (*VFn_1DBE48)(s32 a, s32 b, s32 c);
struct Node_1DBE48 { VFn_1DBE48 fn; s32 a; s32 b; s32 c; Node_1DBE48* next; };
struct Owner_1DBE48 { u8 pad[0x1EC8]; Node_1DBE48* head; Node_1DBE48* tail; };

void func_001DBC18(void* self, void* node);

void func_001DBE48(Owner_1DBE48* self)
{
    while (self->head != 0) {
        Node_1DBE48* node = self->head;
        if (node == self->tail) self->tail = 0;
        self->head = node->next;
        node->next = 0;
        node->fn(node->a, node->b, node->c);
        func_001DBC18(self, node);
    }
}
