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
void* func_001F5C0C(void* p, s32 value, s32 size);

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
void* func_001F5C0C(void* dst, s32 value, s32 size);
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

extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011C2A0(void* p);

void func_0011A800(void)
{
    func_0011C2A0(D_0025C250);
    func_0011C2A0(D_0025C270);
    func_0011C2A0(D_0025C290);
    func_0011C2A0(D_0025C2B0);
    func_0011C2A0(D_0025C2D0);
}

extern u8 D_00259F38[];

void func_0011A678(void* p);
void func_0011A680(void* p, s32 n);

void func_0011ADF8(s32 a, s32 b)
{
    if (b == 0xFFFF) {
        if (a != 0) {
            func_0011A678(D_00259F38);
        } else {
            func_0011A680(D_00259F38, 2);
        }
    }
}

void func_0011ADF8(s32 a, s32 b);

void func_0011AE38(void)
{
    func_0011ADF8(1, 0xFFFF);
}

extern u8 D_0025C2D0[];

void* func_0011C240(void* p);
void* func_001F5C0C(void* p, s32 v, s32 n);

void* func_0011AE78(void)
{
    void* p = func_0011C240(D_0025C2D0);
    func_001F5C0C(p, 0, 12);
    return p;
}

s32 func_0011C498(void);
void func_0011C418(void* obj, s32 value, s32 zero);

void func_0011BEE0(void** self, s32* out)
{
    s32 v = func_0011C498();
    func_0011C418(*self, v, 0);
    *out = v;
}

void* func_0018D5C0(s32 size);
void* func_001F5C0C(void* p, s32 value, s32 size);

void* func_0011BF30(void)
{
    void* p = func_0018D5C0(4);
    func_001F5C0C(p, 0, 4);
    return p;
}

extern u8 D_00259F38[];
extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011A6A8(void* p);
void func_0011A670(void);
void func_0011AF78(void* self);
void func_0011C4E8(void);
void func_0011C128(void* obj, s32 count, s32 size);
void func_0011CA90(void);

void func_0011BF70(void)
{
    func_0011A6A8(D_00259F38);
    func_0011C128(D_0025C250, 0xC, 0x2000);
    *(void**)(D_0025C250 + 0x18) = (void*)func_0011AF78;
    func_0011C128(D_0025C270, 0x1C, 0x190);
    *(void**)(D_0025C270 + 0x18) = (void*)func_0011A670;
    func_0011C128(D_0025C290, 0x10, 0x800);
    *(void**)(D_0025C290 + 0x18) = (void*)func_0011C4E8;
    func_0011C128(D_0025C2B0, 0x14, 0x800);
    func_0011CA90();
    func_0011C128(D_0025C2D0, 0xC, 0x80);
}

struct Quad_1180C0 { s32 a, b, c, d; };
struct Frame_1180C0 { Quad_1180C0 q; Quad_1180C0 t; s32 a; s32 b; };
union Raw_1180C0 { s32 i; f32 f; };
struct In_1180C0 { u8 pad0[4]; s32 w4; s32 kind; Raw_1180C0 raw; };

extern void* D_00275710;

void func_0011B008(Quad_1180C0* q);
void func_0018D608(void);
void func_0018D6F0(void);
void func_001DC4D0(void* self, f32 scale, s32 p1, s32 p2, s32 p3, s32 p4, s32* o1, s32* o2);
void func_00117AF0(Quad_1180C0* t, s32 a, s32 b);
void func_0011B0A8(Quad_1180C0* a, Quad_1180C0* b);
void func_0011B060(Quad_1180C0* q, int mode);
void func_0011B018(void* dst, Quad_1180C0* src);

void* func_001180C0(void* out, s32 unused, In_1180C0* in)
{
    Frame_1180C0 f;
    f32 scale;
    func_0011B008(&f.q);
    if (in->kind == 0x14) scale = (f32)in->raw.i; else scale = in->raw.f;
    func_0018D608();
    func_001DC4D0(D_00275710, scale, 0, in->w4, 0, 0, &f.a, &f.b);
    func_00117AF0(&f.t, f.a, f.b);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0018D6F0();
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

struct Quad_1183B8 { s32 a, b, c, d; };
struct Frame_1183B8 { Quad_1183B8 q; Quad_1183B8 t; };

void func_0011B008(Quad_1183B8* q);
void func_00118198(Quad_1183B8* dst, s32 code, s32 x, s32 y, s32 z);
void func_0011B0A8(Quad_1183B8* a, Quad_1183B8* b);
void func_0011B060(Quad_1183B8* q, int mode);
void func_0011B018(void* dst, Quad_1183B8* src);

void* func_001183B8(void* out, s32 x, s32 y, s32 z)
{
    Frame_1183B8 f;
    func_0011B008(&f.q);
    func_00118198(&f.t, 0x71, x, y, z);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

struct Quad_118458 { s32 a, b, c, d; };
struct Frame_118458 { Quad_118458 q; Quad_118458 t; };

void func_0011B008(Quad_118458* q);
void func_00118198(Quad_118458* dst, s32 code, s32 x, s32 y, s32 z);
void func_0011B0A8(Quad_118458* a, Quad_118458* b);
void func_0011B060(Quad_118458* q, int mode);
void func_0011B018(void* dst, Quad_118458* src);

void* func_00118458(void* out, s32 x, s32 y, s32 z)
{
    Frame_118458 f;
    func_0011B008(&f.q);
    func_00118198(&f.t, 0x72, x, y, z);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

struct Blob_119FA0 { s32 w[4]; };
struct Inner_119FA0 { u8 pad0[4]; s32 id; };
struct Mid_119FA0 { u8 pad0[8]; Inner_119FA0* inner; };
struct Outer_119FA0 { u8 pad0[4]; Mid_119FA0* mid; };


void func_0011B008(Blob_119FA0* b);
void func_0011B018(void* dst, Blob_119FA0* src);
void func_0011B060(Blob_119FA0* b, s32 mode);
void func_0011B0A8(Blob_119FA0* a, void* b);
void func_0011B538(Blob_119FA0* b, s32 n);
void func_001C13E8(void* dst, s32 id, u8* ctx);
void* func_001C1390(s32 id, u8* ctx);
void func_0011A338(void* list, void* value);

void* func_00119FA0(void* self, Outer_119FA0* src, void* item)
{
    Blob_119FA0 a;
    Blob_119FA0 b;
    void* found;
    s32 id;

    func_0011B008(&a);
    id = src->mid->inner->id;
    found = func_001C1390(id, (u8*)D_00275710);
    if (found == 0) {
        func_001C13E8(&b, id, (u8*)D_00275710);
        func_0011B0A8(&a, &b);
        func_0011B060(&b, 2);
        found = func_001C1390(id, (u8*)D_00275710);
    }
    func_0011A338(item, found);
    func_0011B538(&a, 0x22);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

struct Slot_11A328 { s32 flag; s32 value; };

void func_0011A328(Slot_11A328* slot, s32 value)
{
    slot->value = value;
    slot->flag = 1;
}

struct Blob_11A358 { s32 w[4]; };
struct Node_11A358 { s32 kind; u8 body[8]; Node_11A358* next; };
struct Owner_11A358 { u8 pad0[0x14]; Node_11A358* head; };

void func_0011B008(Blob_11A358* b);
void func_0011B018(void* dst, Blob_11A358* src);
void func_0011B060(Blob_11A358* b, s32 mode);
s32 func_0011B0A8(u8* a, void* b);
void func_0011B538(Blob_11A358* b, s32 n);
s32 func_0011C498(void);

void* func_0011A358(void* self, Owner_11A358* owner, s32 kind, void* body)
{
    Blob_11A358 a;
    Node_11A358* node;

    func_0011B008(&a);
    node = (Node_11A358*)func_0011C498();
    node->kind = kind;
    (void)func_0011B0A8(node->body, body);
    node->next = owner->head;
    owner->head = node;
    func_0011B538(&a, 0x22);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

struct Blob_11A400 { s32 w[4]; };

void func_0011B008(Blob_11A400* b);
void func_0011B018(void* dst, Blob_11A400* src);
void func_0011B060(Blob_11A400* b, s32 mode);
void func_0011B0A8(void* a, void* b);
void func_0011B538(Blob_11A400* b, s32 n);
void* func_0011A4D8(void* table, void* key, s32 mode);

void* func_0011A400(void* self, void* table, void* key, void* item)
{
    Blob_11A400 a;
    void* found;

    func_0011B008(&a);
    found = func_0011A4D8(table, key, 1);
    if (found != 0) {
        (void)func_0011B0A8(found, item);
    }
    func_0011B538(&a, 0x22);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

struct Stack_11A7D8 { u8 pad[0x1310]; s32 count; s32 items[1]; };

s32 func_0011A7D8(Stack_11A7D8* s)
{
    s32 n = s->count;
    if (n > 0) {
        n = n - 1;
        s->count = n;
        return s->items[n];
    }
    return 0;
}

struct Pair_11B0A8 { s32 a; s32 b; };

void func_0011B418(void* self);
void func_0011B4A8(void* self);

Pair_11B0A8* func_0011B0A8(Pair_11B0A8* dst, Pair_11B0A8* src)
{
    func_0011B4A8(src);
    func_0011B418(dst);
    dst->a = src->a;
    dst->b = src->b;
    return dst;
}

struct Cell_11B538 { s32 value; };

void func_0011B418(void* self);

void func_0011B538(Cell_11B538* self, s32 v)
{
    func_0011B418(self);
    self->value = v;
}

struct Tagged_11B5B0 { s32 tag; f32 value; };

void func_0011B418(void* self);

void func_0011B5B0(Tagged_11B5B0* self, f32 v)
{
    func_0011B418(self);
    self->value = v;
    self->tag = 0x15;
}

struct Value_11B008 { s32 tag; s32 payload; };

void func_0011B008(Value_11B008* v);
void func_0011B018(Value_11B008* dst, Value_11B008* src);
void func_0011B060(Value_11B008* v, int mode);
void func_0011B5B0(Value_11B008* v, f32 f);

Value_11B008* func_0011B9A8(Value_11B008* out, Value_11B008* in)
{
    if (in->tag == 0x15) {
        func_0011B018(out, in);
    } else {
        Value_11B008 tmp;
        func_0011B008(&tmp);
        func_0011B5B0(&tmp, (f32)in->payload);
        func_0011B018(out, &tmp);
        func_0011B060(&tmp, 2);
    }
    return out;
}
