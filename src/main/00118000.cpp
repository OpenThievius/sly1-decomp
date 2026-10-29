// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// A count followed by that many values.
struct IntList { s32 count; s32 items[1]; };

void func_0011A338(IntList* list, int value)
{
    list->items[list->count++] = value;
}

void func_0011A6C0(IntList* list, int value)
{
    for (int i = 0; i < list->count; i++)
        if (list->items[i] == value)
            return;
    list->items[list->count++] = value;
}

// A record that keeps a stack of values at 0x708.
struct StackAt708 { u8 pad[0x708]; s32 count; s32 items[1]; };

int func_0011A748(StackAt708* stack)
{
    if (stack->count > 0)
        return stack->items[--stack->count];
    return 0;
}

struct Vec_1188F0 { f32 x, y, z, w; };
struct Src_1188F0 { s32 pad0; void* p4; };

void func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_001566C8(void* obj, f32 f);
void func_0011B060(void* self, s32 n);
void func_0011B538(void* self, s32 k);
void func_0011B018(void* dst, void* src);

void* func_001188F0(void* ret, s32 unused, Src_1188F0* src)
{
    Vec_1188F0 t;
    Vec_1188F0 u;
    func_0011B008(&t);
    void* s1 = src->p4;
    func_0011B9A8(&u, (u8*)src + 8);
    func_001566C8(s1, u.y);
    func_0011B060(&u, 2);
    func_0011B538(&t, 0x22);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct __attribute__((aligned(16))) Quad_119A58 { s32 w[4]; };
struct Node_119A58 { s32 pad[2]; Node_119A58* next; };

void func_0011B008(Quad_119A58* q);
void func_0011B018(void* out, Quad_119A58* q);
void func_0011B060(Quad_119A58* q, s32 mode);
void func_0011B0A8(Quad_119A58* a, Quad_119A58* b);
void func_0011A080(Quad_119A58* t, Node_119A58* n, s32 c);

void* func_00119A58(void* out, Node_119A58* list, s32 c)
{
    Quad_119A58 q, t;
    func_0011B008(&q);
    Node_119A58* n = list;
    do {
        func_0011A080(&t, n, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        n = n->next;
    } while (n);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

void* func_0011A4D8(void* a, s32 b, s32 c, void* d);
void func_0011B0A8(void* a, void* b);

s32 func_0011A498(void* a, s32 b, s32 c, void* d)
{
    void* r = func_0011A4D8(a, b, c, d);
    if (r != 0) {
        if (d)
            func_0011B0A8(d, r);
        return 1;
    }
    return 0;
}

void func_0018D778(void);

void func_0011A680(void* p, s32 flag)
{
    if (flag & 1)
        func_0018D778();
}

struct Stack_11A790 { u8 pad[0xF0C]; s32 count; s32 items[1]; };

s32 func_0011A790(Stack_11A790* s)
{
    if (s->count > 0) {
        s32 n = s->count - 1;
        s->count = n;
        return s->items[n];
    }
    return 0;
}

void func_0011ADF8(void* p, s32 mode);

void func_0011AE58(void)
{
    func_0011ADF8(0, 0xFFFF);
}

extern u8 D_0025C2B0[];
void* func_0011C240(void* p);
void func_001F5C0C(void* p, s32 value, s32 size);

void* func_0011AFC8(void)
{
    void* p = func_0011C240(D_0025C2B0);
    func_001F5C0C(p, 0, 0x14);
    return p;
}

struct Rec_11B570 { s32 tag; s32 value; };
void func_0011B418(void* self);

void func_0011B570(Rec_11B570* r, s32 value)
{
    func_0011B418(r);
    r->value = value;
    r->tag = 0x14;
}

struct Rec_11B700 { s32 tag; s32 value; };
void func_0011B418(void* self);

void func_0011B700(Rec_11B700* r, s32 value)
{
    func_0011B418(r);
    r->value = value;
    r->tag = 0x1F;
}

struct Obj_11B8A8 { s32 tag; void* ptr; };

void func_0011B418(void* self);

void func_0011B8A8(Obj_11B8A8* self, void* arg)
{
    func_0011B418(self);
    self->ptr = arg;
    self->tag = 0x20;
}

struct Node_11BE90 { s32 key; u8 data[8]; struct Node_11BE90* next; };
struct Head_11BE90 { struct Node_11BE90* first; };

void func_0011B0A8(void* a, void* b);

s32 func_0011BE90(Head_11BE90* head, s32 key, void* arg)
{
    Node_11BE90* n = head->first;
    while (n != 0) {
        if (n->key == key) {
            if (arg != 0) {
                func_0011B0A8(arg, n->data);
            }
            return 1;
        }
        n = n->next;
    }
    return 0;
}

struct Node_11AF28 {
    s32 kind;
    s32 value;
    Node_11AF28* child;
};
typedef Node_11AF28 Node_11AEB8;

void func_0011B258(void* src, void* dst, void* arg);
Node_11AEB8* func_0011AF28(void);

void func_0011AEB8(Node_11AEB8* src, Node_11AEB8* dst, void* arg)
{
    func_0011B258(src, dst, arg);
    if (src->child != 0) {
        Node_11AEB8* copy = func_0011AF28();
        func_0011AEB8(src->child, copy, arg);
        dst->child = copy;
    }
}

extern u8 D_0025C250[];

void* func_0011C240(void* pool);
void func_001F5C0C(void* dst, s32 value, s32 size);
Node_11AF28* func_0011B008(Node_11AF28* self);

Node_11AF28* func_0011AF28(void)
{
    Node_11AF28* node = (Node_11AF28*)func_0011C240(D_0025C250);
    func_001F5C0C(node, 0, 12);
    func_0011B008(node);
    node->kind = -1;
    return node;
}

void func_0011B060(void* self, s32 flags);

void func_0011AF78(void* self)
{
    func_0011B060(self, 2);
}

struct Ext_11AF98 {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
};

void func_0011AF98(Ext_11AF98* src, Ext_11AF98* dst, s32 first)
{
    if (first == 0) {
        first = src->w0;
    }
    dst->w0 = first;
    dst->w1 = src->w1;
    dst->w2 = src->w2;
    dst->w3 = src->w3;
    dst->w4 = src->w4;
}

struct Node_11B008 {
    s32 kind;
    s32 value;
    Node_11B008* child;
};

Node_11B008* func_0011B008(Node_11B008* self)
{
    self->kind = -1;
    return self;
}

struct Node_11B018 {
    s32 kind;
    s32 value;
    Node_11B018* child;
};

void func_0011B4A8(Node_11B018* node);

Node_11B018* func_0011B018(Node_11B018* dst, Node_11B018* src)
{
    func_0011B4A8(src);
    dst->kind = src->kind;
    dst->value = src->value;
    return dst;
}

void func_0011B418(void* self);
void func_0018D778(void* self);

void func_0011B060(void* self, s32 flags)
{
    func_0011B418(self);
    if (flags & 1) {
        func_0018D778(self);
    }
}
