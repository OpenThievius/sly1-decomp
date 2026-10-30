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

void* func_0011A678(void* p);
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

struct Quad_118608 { s32 a, b, c, d; };
struct Frame_118608 { Quad_118608 q; };
struct In_118608 { u8 pad0[4]; s32 f4; u8 pad8[4]; s32 fC; u8 pad10[4]; s32 f14; };

void func_0011B008(Quad_118608* q);
void* func_0011C618(void);
void func_00128150(s32 a, s32 b, s32 c, void* d);
void func_001884C0(void* p);
void func_0011B788(Quad_118608* q, void* b);
void func_0011B018(void* dst, Quad_118608* src);
void func_0011B060(Quad_118608* q, int mode);

void* func_00118608(void* out, s32 unused, In_118608* in)
{
    Frame_118608 f;
    void* obj;
    func_0011B008(&f.q);
    obj = func_0011C618();
    func_00128150(in->f4, in->fC, in->f14, obj);
    func_001884C0(obj);
    func_0011B788(&f.q, obj);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

struct Quad_118720 { s32 a, b, c, d; };
struct Frame_118720 { Quad_118720 q; s32 n; s32 pad[3]; };
struct In_118720 { u8 pad0[4]; s32 f4; u8 pad8[4]; s32 fC; };

void func_0011B008(Quad_118720* q);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_0011B570(Quad_118720* q, s32 n);
void func_001BF718(void* slot);
void func_0011B018(void* dst, Quad_118720* src);
void func_0011B060(Quad_118720* q, int mode);

void* func_00118720(void* out, s32 unused, In_118720* in)
{
    Frame_118720 f;
    func_0011B008(&f.q);
    f.n = 0;
    func_001BFCD8(in->f4, in->fC ? &f.n : 0, in->fC, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
    func_0011B570(&f.q, f.n);
    if (f.n != 0) func_001BF718(&f.n);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

// A node of a keyed list: the key, a value whose address is returned, and the next node at 0xC.
struct Node_11A4D8 { s32 key; s32 value; s32 pad8; struct Node_11A4D8* next; };

// A tree node: count and child pointers at 0x0 and 0x4, a list head at 0x14, a busy flag at 0x18.
struct Tree_11A4D8 {
    s32 count;
    struct Tree_11A4D8* items[4];
    struct Node_11A4D8* head;
    s32 flag;
};

void* func_0011A4D8(struct Tree_11A4D8* self, s32 key, s32 flag)
{
    void* found = 0;
    struct Node_11A4D8* n;
    s32 i;

    self->flag = 1;
    for (n = self->head; n != 0; n = n->next) {
        if (n->key == key) {
            found = &n->value;
            goto done;
        }
    }
    if (flag != 0) {
        for (i = 0; i < self->count; i++) {
            struct Tree_11A4D8* c = self->items[i];
            if (c->flag == 0) {
                found = func_0011A4D8(c, key, flag);
                if (found != 0)
                    goto done;
            }
        }
    }
done:
    self->flag = 0;
    return found;
}

// The same tree node as func_0011A4D8: count and child pointers, a list head at 0x14, a flag at 0x18.
struct Node_11A5B0;
struct Tree_11A5B0 {
    s32 count;
    struct Tree_11A5B0* items[4];
    struct Node_11A5B0* head;
    s32 flag;
};

void func_0018D800(void* dst, void* src, s32 bytes);
s32 func_0011C498(void);
void func_0011C418(void* a, void* b, void* c);

void func_0011A5B0(struct Tree_11A5B0* src, struct Tree_11A5B0* dst)
{
    dst->count = src->count;
    func_0018D800(dst->items, src->items, src->count * 4);
    if (src->head != 0) {
        void* n = (void*)func_0011C498();
        func_0011C418(src->head, n, dst);
        dst->head = (struct Node_11A5B0*)n;
    }
}

struct Flag_11B5F0 { s32 tag; s32 flag; };
void func_0011B418(void* self);

void func_0011B5F0(Flag_11B5F0* r, void* arg)
{
    func_0011B418(r);
    if (arg != 0)
        r->flag = 1;
    else
        r->flag = 0;
    r->tag = 0x1B;
}

struct Obj_11B640 { s32 tag; void* ptr; };
void func_0011B418(void* self);

void func_0011B640(Obj_11B640* self, void* arg)
{
    func_0011B418(self);
    self->ptr = arg;
    self->tag = 0x1C;
}

struct Vec_118850 { f32 x, y, z, w; };
struct Src_118850 { s32 pad0; s32 n; };

void func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_0016EC38(void* p, s32 n, f32 f);
void func_0011B060(void* self, s32 mode);
void func_0011B018(void* dst, void* src);

extern u8 D_00262C70[];

void* func_00118850(void* ret, s32 unused, Src_118850* src)
{
    Vec_118850 t;
    Vec_118850 u;
    func_0011B008(&t);
    void* p = D_00262C70;
    s32 n = src->n;
    func_0011B9A8(&u, (u8*)src + 8);
    func_0016EC38(p, n, u.y);
    func_0011B060(&u, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

extern u8 D_0025C270[];
void* func_0011C240(void* p);

void* func_0011A630(void)
{
    void* p = func_0011C240(D_0025C270);
    func_001F5C0C(p, 0, 0x1C);
    return p;
}

void func_0011A670(void)
{
}

struct Stack_11A7B8 { u8 pad[0x1310]; s32 count; s32 items[1]; };

void func_0011A7B8(Stack_11A7B8* s, s32 value)
{
    s32 n = s->count;
    s->items[n] = value;
    s->count = n + 1;
}

struct Tag_11B680 { s32 tag; s32 value; };
void func_0011B418(void* self);

void func_0011B680(Tag_11B680* r, s32 value)
{
    func_0011B418(r);
    r->value = value;
    r->tag = 0x1D;
}

struct Tagged_11B8E8 { s32 tag; s32 value; };

void func_0011B418(void* self);

void func_0011B8E8(Tagged_11B8E8* self, s32 value)
{
    func_0011B418(self);
    self->tag = 0x21;
    self->value = value;
}

struct Quad_11B928 { s32 a, b, c, d; };
struct Scaled_11B928 { s32 tag; f32 scale; };

void func_0011B008(Quad_11B928* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(Quad_11B928* q, int mode);
void func_0011B570(Quad_11B928* q, s32 n);

void* func_0011B928(void* out, Scaled_11B928* in)
{
    if (in->tag == 0x14) {
        func_0011B018(out, in);
    } else {
        Quad_11B928 q;
        func_0011B008(&q);
        func_0011B570(&q, (s32)in->scale);
        func_0011B018(out, &q);
        func_0011B060(&q, 2);
    }
    return out;
}

// A 128-bit value, copied as one quadword.
typedef u64 Quad_118D10 __attribute__((mode(TI)));

// Copies the quadword at src into out and returns out.
Quad_118D10* func_00118D10(Quad_118D10* out, void* src)
{
    Quad_118D10 v = *(Quad_118D10*)src;
    *out = v;
    return out;
}

// A 128-bit value, stored as one quadword.
typedef u64 Quad_118D20 __attribute__((mode(TI)));

// Stores the quadword v into out and returns out.
Quad_118D20* func_00118D20(Quad_118D20* out, Quad_118D20 v)
{
    *out = v;
    return out;
}

void* func_0011A678(void* self)
{
    return self;
}

struct Counters_11A6A8 {
    s32 count;
    u8 pad[0x500];
    s32 count2;
};

void func_0011A6A8(Counters_11A6A8* self)
{
    self->count = 0;
    self->count2 = 0;
}

struct Rec_11B6C0 { s32 tag; s32 value; };
void func_0011B418(void* self);

void func_0011B6C0(Rec_11B6C0* r, s32 value)
{
    func_0011B418(r);
    r->value = value;
    r->tag = 0x1E;
}

struct Rec_11B740 { s32 tag; s32 value; };
void func_0011B418(void* self);
s32 func_0011C580(u32 addr);

void func_0011B740(Rec_11B740* r, s32 value)
{
    func_0011C580(value);
    func_0011B418(r);
    r->value = value;
    r->tag = 0x16;
}

struct Obj_0011A708 { u8 pad[0x504]; s32 count; s32 values[1]; };
void func_0011A708(Obj_0011A708* obj, s32 value) { obj->values[obj->count++] = value; }

struct Obj_0011A728 { u8 pad[0x708]; s32 count; s32 values[1]; };
void func_0011A728(Obj_0011A728* obj, s32 value) { obj->values[obj->count++] = value; }

struct Obj_0011A770 { u8 pad[0xF0C]; s32 count; s32 values[1]; };
void func_0011A770(Obj_0011A770* obj, s32 value) { obj->values[obj->count++] = value; }

void func_0011A6B8() {}

s32 func_0011C690(u32 value);
void func_0011B788(Rec_11B570* self, u32 value)
{
    (void)func_0011C690(value);
    func_0011B418(self);
    self->value = value;
    self->tag = 23;
}

s32 func_0011C7C0(u32 value);
void func_0011B7D0(Rec_11B570* self, u32 value)
{
    (void)func_0011C7C0(value);
    func_0011B418(self);
    self->value = value;
    self->tag = 24;
}

s32 func_0011C8D0(u32 value);
void func_0011B818(Rec_11B570* self, u32 value)
{
    (void)func_0011C8D0(value);
    func_0011B418(self);
    self->value = value;
    self->tag = 25;
}

s32 func_0011C9E0(u32 value);
void func_0011B860(Rec_11B570* self, u32 value)
{
    (void)func_0011C9E0(value);
    func_0011B418(self);
    self->value = value;
    self->tag = 26;
}

struct Tmp_1184F8 { u8 bytes[0x10]; };
struct Src_1184F8 { s32 pad0; void* a; s32 pad2; s32 b; s32 pad4; void* c; };

void func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_00128018(void* a, s32 b, void* c, void* d);
void func_0011B740(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_001184F8(void* ret, s32 unused, Src_1184F8* src)
{
    Tmp_1184F8 t;
    func_0011B008(&t);
    void* p = func_0011C508();
    (void)func_00128018(src->a, src->b, src->c, p);
    func_0011B740(&t, p);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_118580 { u8 bytes[0x10]; };
struct Src_118580 { s32 pad0; void* a; s32 pad2; s32 b; s32 pad4; void* c; };

void func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_001280C0(void* a, s32 b, void* c, void* d);
void func_0011B740(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00118580(void* ret, s32 unused, Src_118580* src)
{
    Tmp_118580 t;
    func_0011B008(&t);
    void* p = func_0011C508();
    (void)func_001280C0(src->a, src->b, src->c, p);
    func_0011B740(&t, p);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_1187E8 { s32 w0; s32 w1; s32 w2; s32 w3; };
struct Src_1187E8 { s32 pad0; void* a; };

void func_0011B008(void* obj);
void func_001BF788(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_001187E8(void* ret, s32 unused, Src_1187E8* src)
{
    Tmp_1187E8 t;
    func_0011B008(&t);
    func_001BF788(src->a, 0);
    t.w0 = 0x22;
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_118D48 { u8 bytes[0x10]; };
struct Src_118D48 { s32 pad0; s32 a; };

void func_0011B008(void* obj);
s32 func_0011A498(void* a, s32 b, s32 c, void* d);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00118D48(void* ret, Src_118D48* src, void* ctx)
{
    Tmp_118D48 t;
    func_0011B008(&t);
    (void)func_0011A498(ctx, src->a, 1, &t);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct __attribute__((aligned(16))) Quad_119AF8 { s32 w[4]; };
struct Node_119AF8 { s32 pad[2]; Node_119AF8* next; };
struct Wrap_119AF8 { s32 pad[2]; Node_119AF8* first; };
struct Owner_119AF8 { s32 pad; Wrap_119AF8* wrap; };

void func_0011B008(Quad_119AF8* q);
void func_0011B538(Quad_119AF8* q, s32 k);
void func_0011A080(Quad_119AF8* t, Node_119AF8* n, s32 c);
void func_0011B0A8(Quad_119AF8* a, Quad_119AF8* b);
void func_0011B060(Quad_119AF8* q, s32 mode);
void func_0011B018(void* dst, Quad_119AF8* src);

void* func_00119AF8(void* self, Owner_119AF8* owner, s32 c)
{
    Quad_119AF8 q, t;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    Node_119AF8* n = owner->wrap->first;
    while (n != 0) {
        func_0011A080(&t, n, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        n = n->next;
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// EXACT: callee 0011B008 declared s32 and called as statement.

struct __attribute__((aligned(16))) Quad_118DB8 { s32 w[4]; };
struct Node_118DB8 { s32 pad0; Node_118DB8* f4; Node_118DB8* f8; };

s32 func_0011B008(Quad_118DB8* q);
void func_0011B018(void* out, Quad_118DB8* q);
void func_0011B060(Quad_118DB8* q, s32 mode);
void func_0011B0A8(Quad_118DB8* a, Quad_118DB8* b);
void func_0011B538(Quad_118DB8* q, s32 n);
void func_0011A080(Quad_118DB8* t, Node_118DB8* n, s32 c);
void* func_0011A400(void* self, s32 table, void* key, void* item);

void* func_00118DB8(void* self, Node_118DB8* x, s32 c)
{
    Quad_118DB8 q;
    Quad_118DB8 t;
    func_0011B008(&q);
    Node_118DB8* p = x->f4;
    Node_118DB8* m = p->f8;
    func_0011A080(&t, m->f8, c);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011A400(&t, c, m->f4, &q);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_118E80 { s32 w[4]; };
struct Node_118E80 { s32 pad0; Node_118E80* f4; Node_118E80* f8; };

s32 func_0011B008(Quad_118E80* q);
void func_0011B018(void* out, Quad_118E80* q);
void func_0011B060(Quad_118E80* q, s32 mode);
void func_0011B0A8(Quad_118E80* a, Quad_118E80* b);
void func_0011B538(Quad_118E80* q, s32 n);
void func_0011A080(Quad_118E80* t, Node_118E80* n, s32 c);
void* func_0011A358(void* self, s32 owner, void* kind, void* body);

void* func_00118E80(void* self, Node_118E80* x, s32 c)
{
    Quad_118E80 q;
    Quad_118E80 t;
    func_0011B008(&q);
    Node_118E80* p = x->f4;
    Node_118E80* m = p->f8;
    func_0011A080(&t, m->f8, c);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011A358(&t, c, m->f4, &q);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_119878 { s32 w[4]; };
struct Node_119878 { s32 pad[2]; Node_119878* next; };
struct Wrap_119878 { s32 pad[2]; Node_119878* first; };
struct Owner_119878 { s32 pad; Wrap_119878* wrap; };

s32 func_0011B008(Quad_119878* q);
void func_0011A080(Quad_119878* t, Node_119878* n, s32 c);
void func_0011B0A8(Quad_119878* a, Quad_119878* b);
void func_0011B060(Quad_119878* q, s32 mode);
void func_0011B538(Quad_119878* q, s32 k);
void func_0011B018(void* dst, Quad_119878* src);

void* func_00119878(void* self, Owner_119878* owner, s32 c)
{
    Quad_119878 q, t;
    s32 a, b;
    func_0011B008(&q);
    Node_119878* first = owner->wrap->first;
    Node_119878* second = first->next;
    for (;;) {
        func_0011A080(&t, first, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        a = q.w[0];
        if (a != 0x1B)
            goto other;
        b = q.w[1];
        if (b != 0)
            goto other;
        break;
    other:
        func_0011A080(&t, second, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_119970 { s32 w[4]; };
struct Item_119970 { s32 tag; Item_119970* child; Item_119970* next; };
struct Wrap_119970 { s32 pad[2]; Item_119970* first; };
struct Owner_119970 { s32 pad; Wrap_119970* wrap; };
struct Rec_119970 { s32 c; Item_119970* head; s32 count; s32 found; Item_119970* after; };

s32 func_0011B008(Quad_119970* q);
void* func_0011AFC8(void);
void func_0011B700(Quad_119970* r, Rec_119970* value);
void func_0011B018(void* dst, Quad_119970* src);
void func_0011B060(Quad_119970* q, s32 mode);

void* func_00119970(void* self, Owner_119970* owner, s32 c)
{
    Quad_119970 q;
    func_0011B008(&q);
    Item_119970* first = owner->wrap->first;
    Item_119970* after = first->next;
    Rec_119970* p = (Rec_119970*)func_0011AFC8();
    p->c = c;
    if (first->tag == 0)
        p->head = 0;
    else
        p->head = first->child;
    p->after = after;
    s32 found = 0;
    s32 count = 0;
    Item_119970* n = p->head;
    while (n != 0) {
        if (n->tag == 0x13) {
            found = 1;
            n = 0;
        } else {
            n = n->next;
            count++;
        }
    }
    p->count = count;
    p->found = found;
    func_0011B700(&q, p);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// Fixed by merging the two flag tests into one "kind != 0x1B || p != 0".

struct __attribute__((aligned(16))) Quad_119310 { s32 kind; void* p; s32 w[2]; };
struct Node_119310 { s32 kind; Node_119310* f4; Node_119310* f8; };

s32 func_0011B008(Quad_119310* q);
void func_0011B018(void* out, Quad_119310* q);
void func_0011B060(Quad_119310* q, s32 mode);
void func_0011B0A8(Quad_119310* a, Quad_119310* b);
void func_0011B538(Quad_119310* q, s32 n);
void func_0011A080(Quad_119310* t, Node_119310* n, s32 c);

void* func_00119310(void* self, Node_119310* x, s32 c)
{
    Quad_119310 q, r, t;
    func_0011B008(&q);
    func_0011B008(&r);
    func_0011B538(&q, 0x22);
    Node_119310* n = x->f4->f8;
    while (n) {
        Node_119310* e = n->f4;
        s32 flag;
        if (e->kind == 10) {
            flag = 1;
        } else {
            func_0011A080(&t, e, c);
            flag = 0;
            func_0011B0A8(&r, &t);
            func_0011B060(&t, 2);
            if (r.kind != 0x1B || r.p != 0)
                flag = 1;
            if (flag && e->f8 == 0)
                func_0011B0A8(&q, &r);
        }
        if (flag) {
            e = e->f8;
            while (e) {
                func_0011A080(&t, e, c);
                func_0011B0A8(&q, &t);
                func_0011B060(&t, 2);
                e = e->f8;
            }
            n = 0;
        } else {
            n = n->f8;
        }
    }
    func_0011B018(self, &q);
    func_0011B060(&r, 2);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_118F48 { s32 a, b, c, d; };
struct Obj_118F48 { u8 pad[4]; Quad_118F48* f4; };
struct Frame_118F48 { Quad_118F48 q; Quad_118F48 t; };

void func_0011B008(Quad_118F48* q);
void func_0011B018(void* dst, Quad_118F48* src);
void func_0011B060(Quad_118F48* q, int mode);
void func_0011B0A8(Quad_118F48* a, Quad_118F48* b);
void func_0011B538(Quad_118F48* q, int n);
void func_0011A080(Quad_118F48* t, void* n, s32 c);
void func_001E1F10(void* x);
s32 func_00113730(Quad_118F48* t, s32 mode, void* a, s32 c);
extern u8 D_00249200[];

void* func_00118F48(void* self, void* p, s32 x)
{
    Frame_118F48 f;
    func_0011B008(&f.q);
    u8* a = *(u8**)((u8*)p + 4);
    u8* b = *(u8**)(a + 8);
    u8* c = *(u8**)(b + 8);
    func_0011A080(&f.t, b, x);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    if (f.q.b == 0) {
        u8* v = *(u8**)(c + 4);
        u8* w = *(u8**)(v + 8);
        func_001E1F10(D_00249200);
        func_00113730(&f.t, 1, w, x);
        func_0011B060(&f.t, 2);
    }
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}
