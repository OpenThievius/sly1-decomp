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
struct Node_001DD9C0;
extern Node_001DD9C0* D_002623C8;

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

struct Obj_001DD610 { u8 pad[0x1D68]; f32 level; };


void func_001DD610(Obj_001DD610* self, f32 v)
{
    self->level = v;
    D_00264260 = D_002622CC;
}

extern void* D_00275710;

void* func_001EAA70(void* a, void* b);
void func_00148AC0(void* heap, int size, void* c, void* d, int e);

void func_001DD950(void* unused, void* a, void* b, void* c)
{
    void* r = func_001EAA70(a, b);
    if (r != 0) {
        func_00148AC0(D_00275710, 0x58, c, r, 0);
    }
}

extern u8 D_00261EF0[];

void func_00152410(void* p);

void func_001DD9A0(void)
{
    func_00152410(D_00261EF0);
}

struct Node_001DD9C0 { u8 pad[0xC]; f32 value; };


void func_001DD9C0(void* unused, f32* out)
{
    *out = D_002623C8->value;
}

struct Owner_1DDBB8 { u8 pad[0x2320]; s32 count; };
typedef void (*VFn_1DDBB8)(void* self);
struct Svc_1DDBB8 { VFn_1DDBB8* vtbl; };
extern Svc_1DDBB8 D_002721D0;

void func_001DDBB8(Owner_1DDBB8* self)
{
    if (--self->count == 0) {
        D_002721D0.vtbl[15](&D_002721D0);
    }
}

void* func_001BF0D8(void* p);

void* func_001DDC18(void* unused, void* p)
{
    return func_001BF0D8(p);
}

struct Owner_1DDC38 { u8 pad[0x2324]; void* ptr; };

void func_001DDC38(Owner_1DDC38* self, void* v)
{
    self->ptr = v;
}

typedef void (*VFn_001DDC40)(void* self);
struct Child_001DDC40 { VFn_001DDC40* vtbl; };
struct Owner_001DDC40 { u8 pad[0x2324]; Child_001DDC40* child; };

void func_001DDC40(Owner_001DDC40* self)
{
    Child_001DDC40* p = self->child;
    if (p != 0) {
        VFn_001DDC40 fn = p->vtbl[50];
        if (fn != 0) {
            fn(p);
        }
    }
}

struct Flags_001DDC78 { u8 pad[0x235C]; s32 bits; };

void func_001DDC78(Flags_001DDC78* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->bits |= m;
}

struct Flags_001DDC90 { u8 pad[0x235C]; s32 bits; };

void func_001DDC90(Flags_001DDC90* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->bits &= ~m;
}


void func_001DDCC8(void* unused, s32* out)
{
    *out = *(s32*)((u8*)D_002623C0 + 0x19E0);
}

struct Node_1DC108 { s32 pad0; Node_1DC108* next; };

void func_001B5F28(void* list, void* item);

void func_001DC108(u8* owner, Node_1DC108* node)
{
    while (node != 0) {
        Node_1DC108* next = node->next;
        func_001B5F28(owner + 0x1C0C, node);
        node = next;
    }
}

struct __attribute__((aligned(16))) Quad_1DDCE0 { s32 a, b, c, d; };

struct Obj_1DDCE0 {
    u8 pad[0x320];
    Quad_1DDCE0 q;
};

extern u8 D_00275730[];

void func_00123ED0(Obj_1DDCE0* self);

void func_001DDCE0(Obj_1DDCE0* self)
{
    func_00123ED0(self);
    self->q = *(Quad_1DDCE0*)D_00275730;
}

struct Obj_1DE768 {
    u8 pad0[0x2D0];
    Obj_1DE768* self2D0;
    u8 pad1[0x2DC - 0x2D4];
    s32 flag2DC;
};

void func_001276C0(Obj_1DE768* self);

void func_001DE768(Obj_1DE768* self)
{
    if (self->self2D0 == self) {
        self->flag2DC = 1;
    }
    func_001276C0(self);
}

struct Node_1DC7D0 { u8 pad[8]; Node_1DC7D0* next; Node_1DC7D0* prev; };
struct Owner_1DC7D0 { u8 pad[0x1AE4]; Node_1DC7D0* listA; Node_1DC7D0* listB; };

void func_001DC710(Node_1DC7D0* node, Node_1DC7D0** head);
void func_001DC7B0(Node_1DC7D0* node, Node_1DC7D0** head);

Node_1DC7D0* func_001DC7D0(Owner_1DC7D0* owner, void* self)
{
    Node_1DC7D0* n = owner->listA;
    func_001DC710(n, &owner->listA);
    func_001DC7B0(n, &owner->listB);
    *(void**)((u8*)n + 4) = self;
    return n;
}

struct Ctx_1DDAD0 { u8 pad0[0x2D0]; s32 f2D0; s32 f2D4; };

extern Ctx_1DDAD0* D_0027051C;
extern u8 D_00275BC0[];

void func_001E9570(void* g);

void func_001DDAD0(void)
{
    Ctx_1DDAD0* ctx = D_0027051C;
    if (ctx != 0 && ctx->f2D4 != 4) {
        u32 t = (u32)(ctx->f2D0 - 1);
        if (t < 2) func_001E9570(D_00275BC0);
    }
}

extern u8 D_0026FF68[];

struct __attribute__((packed)) Unaligned_1DDB20 { s32 v; };

void func_00194D30(void* self, s32 mode, s32 value);

void func_001DDB20(void* unused, s32 a1, s32 a2)
{
    s32 saved = a1;
    u8* p = D_0026FF68;
    ((Unaligned_1DDB20*)(p + 0x280))->v = a2;
    func_00194D30(D_0026FF68, 0, saved);
}

struct Self_001DFBD0 { u8 pad0[0x728]; s32 f728; };

s32 func_001DFBD0(Self_001DFBD0* self)
{
    return self->f728 != 0;
}

s32 func_00137C40(void* src);
void func_00138518(void* self);

extern s32 D_00275714;

void func_001DCCC0(void* self)
{
    s32 n = func_00137C40(self);
    if (D_00275714) {
        s32 i = 1;
        if (i < n) {
            i = n - 1;
            do {
                func_00138518(self);
                i--;
            } while (i != 0);
        }
    }
}

struct Field_002623C8 { u8 pad0[0x10]; f32 value; };

void func_001DDA08(void* unused, f32* out)
{
    *out = ((Field_002623C8*)D_002623C8)->value;
}

struct Owner_1DDB58 { u8 pad[0x2320]; s32 count; };

void func_001AA8B8(void* self, f32 v);

void func_001DDB58(Owner_1DDB58* self)
{
    if (++self->count == 1) {
        func_001AA8B8(&D_002721D0, 0.0f);
        D_002721D0.vtbl[14](&D_002721D0);
    }
}

extern u8 D_002758D0[];

void func_00152440(void* p);

void func_001DFD70()
{
    func_00152440(D_002758D0);
}

struct Obj_001DFD90 { u8 pad[0x88]; s32 count; f32 scale; };

void func_001F39F8(void* self);

void func_001DFD90(void* self)
{
    Obj_001DFD90* o = (Obj_001DFD90*)self;
    func_001F39F8(self);
    o->count = 30;
    o->scale = 25.0f;
}

struct Stack_001DC208 { s32 count; s32* values; };
struct Obj_001DC208 { u8 pad[0x1F00]; Stack_001DC208 stacks[8]; };
s32 func_001DC208(Obj_001DC208* self, s32 index) { Stack_001DC208* s = &self->stacks[index]; s->count--; return s->values[s->count]; }

struct Obj_001DDA80 { u8 pad[0x231C]; s32 value; };
s32 func_001DDA80(Obj_001DDA80* self) { return self->value > 0; }

struct Obj_001DDAC8 { u8 pad[0x2350]; f32 value; };
void func_001DDAC8(Obj_001DDAC8* self, f32 value) { self->value = value; }

struct __attribute__((packed)) Pair_1DC150 { s32 n; void* buf; };
struct Self_1DC150 { u8 pad0[0x1EFC]; s32 count; struct Pair_1DC150 entries[1]; };

void* func_0018D500(s32 size);
void* func_00183058(void* a, void* b, void* c);

void func_001DC150(struct Self_1DC150* self, void* src, s32 n)
{
    struct Pair_1DC150 tmp;
    s32 i;
    s32 idx;

    tmp.n = n - 1;
    if (tmp.n > 0) {
        tmp.buf = func_0018D500(tmp.n * 4);
        for (i = 0; i < tmp.n; i++) {
            ((void**)tmp.buf)[i] = func_00183058(src, self, 0);
        }
    }
    idx = self->count;
    self->entries[idx] = tmp;
    self->count = idx + 1;
}

struct Slot_DD888 { s32 key; s32 value; };
struct Slots_DD888 { u8 pad[0x44]; Slot_DD888 slots[4]; };

void* func_00160810(void* obj);

s32 func_001DD888(void* self, void* obj, s32 key)
{
    Slots_DD888* t = (Slots_DD888*)func_00160810(obj);
    if (t != 0) {
        Slot_DD888* p = t->slots;
        for (u32 i = 0; i < 4; i++) {
            if (p->key == key) {
                return p->value;
            }
            p++;
        }
    }
    return 0;
}

s32 func_001BE980(void);

void func_001DDA90(void* self, s32* out)
{
    *out = func_001BE980();
}

void func_00192C58(void* self);
void func_001DFBE0(void* self, s32 flag);

void func_001DEBB8(void* self)
{
    func_00192C58(self);
    func_001DFBE0(self, 1);
}

void func_001BC4D8(void* self, void* sub);
void func_001C57C8(void* self);

void func_001DFA10(void* self)
{
    func_001BC4D8(self, (u8*)self + 0x740);
    func_001C57C8(self);
}

struct Rec_001DFB08 {
    s32 f0;
    s32 f4;
    s32 f8;
};

struct Dev_001DFB08 {
    u8 pad0[0x24];
    s32 f24;
};

struct Obj_001DFB08 {
    u8 pad0[0x738];
    s32 f738;
    u8 pad1[0x75C - 0x73C];
    Dev_001DFB08* f75C;
};

void func_001B6598(void* dev, s32* out);
void func_001B6568(void* dev, s32* out);
void func_00192230(void* self, s32 kind, Rec_001DFB08* rec);

void func_001DFB08(Obj_001DFB08* self, s32 code, Rec_001DFB08* rec)
{
    s32 loc[2];

    if (code != 0x13) {
        if (code == 0x14) {
            if (rec == (Rec_001DFB08*)self->f75C) {
                func_001B6598(rec, &loc[0]);
                func_001B6568(self->f75C, &loc[1]);
            }
        }
    } else {
        Dev_001DFB08* dev = self->f75C;
        s32 key = rec->f0;
        if (dev != 0 && key == dev->f24) {
            s32 kind = rec->f8;
            if (kind != 0x15E) {
                if (kind == 0x15F) {
                    self->f738 = 0;
                }
            } else {
                self->f738 = 1;
            }
        }
    }
    func_00192230(self, code, rec);
}

struct __attribute__((packed)) Pk8_001DFE38 {
    s64 v;
};

struct Obj_001DFE38 {
    u8 pad0[0x80];
    Pk8_001DFE38 f80;
};

void func_001830D8(void* self);

void func_001DFE38(Obj_001DFE38* self)
{
    Pk8_001DFE38 tmp;
    tmp = self->f80;
    func_001830D8(self);
    self->f80 = tmp;
}

struct __attribute__((aligned(16))) Quad_1DD548 { s32 v[4]; };
struct __attribute__((packed)) Pack4_1DD548 { s32 v; };
struct Locals_1DD548 { Quad_1DD548 pts[10]; Pack4_1DD548 c; };

void func_00130B48(void* a0, void* a1, void* a2, void* a3, s32 n, void* out, f32 w0, f32 w1, f32 w2);
void func_001DD3E0(void* a, void* b, void* c, s32 d, s32 e);

void func_001DD548(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, f32 x)
{
    Locals_1DD548 L;
    Quad_1DD548* p;
    Quad_1DD548* q;
    u32 i;

    func_00130B48(a0, a1, a2, a3, 10, L.pts, x, 0.0f, x);
    i = 1;
    q = &L.pts[1];
    p = &L.pts[0];
    do {
        L.c = *(Pack4_1DD548*)a4;
        func_001DD3E0(p, q, &L.c, a5, 1);
        i++;
        q++;
        p++;
    } while (i < 10);
}

struct Obj_1DD628 { u8 pad0[0x2318]; f32 f2318; };

extern u8 D_00274738[];

void func_001C06A0(s32 a, s32 b, f32 x);
void func_0011D928(s32 a);

void func_001DD628(void* self, f32 x)
{
    Obj_1DD628* s = (Obj_1DD628*)self;

    s->f2318 = x;
    *(s32*)D_00274738 = -100;
    func_001C06A0(7, 1, 1.0f);
    func_0011D928((s32)(s->f2318 + 0.5f));
}

extern u8 D_002758D0[];
void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_001DFDC8(void* self)
{
    func_00182D48(self);
    func_00152470(D_002758D0, self);
}

extern u8 D_002758D0[];
void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

void func_001DFE00(void* self)
{
    func_00182ED0(self);
    func_00152600(D_002758D0, self);
}

// NEAR: the loop, the calls and the frame match; retail stores the new block to 0x1AE4 before 0x1AE0 (the compiler emits 0x1AE0 first, and so does a store through a separate struct type).

struct Node_DC740 { u8 pad[8]; Node_DC740* next; Node_DC740* prev; };
struct Pool_DC740 { u8 pad0[0x1AE0]; void* f1AE0; void* f1AE4; };

void* func_0018D5C0(u32 n);

void func_001DC740(Pool_DC740* self)
{
    void* mem = func_0018D5C0(0x1000);
    self->f1AE0 = mem;
    self->f1AE4 = mem;
    for (s32 i = 0; i < 0x100; i++) {
        Node_DC740* n = (Node_DC740*)((u8*)self->f1AE0 + (i << 4));
        n->prev = (i < 1) ? 0 : n - 1;
        n->next = (i > 0xFE) ? 0 : n + 1;
    }
}

struct Obj_001DF5A0 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x720 - 0x18];
    s32 f720;
    s32 f724;
    s32 f728;
};

s32 func_001DDA80(void* p);

s32 func_001DF5A0(Obj_001DF5A0* self, s32 mode)
{
    if (mode == 5 || self->f720 == 2 || self->f720 == 0 || self->f720 == 3 || self->f728 != 0 || func_001DDA80(self->f14) != 0) return 1;
    return 0;
}

struct Obj_1DC9A0;
struct Alloc_1DC9A0;
typedef void (*VFn_1DC9A0)(void* self, void* p);
struct Inst_1DC9A0 { VFn_1DC9A0* vtbl; };

extern s32 D_00275630;
extern u8 D_00275640[];
extern f32 D_00275650;
extern f32 D_00275654;
extern f32 D_00275658;
extern f32 D_0027565C;
extern f32 D_00275660;
extern u8 D_00275670[];
extern u8 D_00275680[];
extern u8 D_00275690[];
extern u8 D_00275698[];
extern u8 D_002756A0[];

Inst_1DC9A0* func_0011E580(Alloc_1DC9A0* a0, Obj_1DC9A0* a1, void* a2, s32 a3, s32 a4);
void func_00184768(Inst_1DC9A0* p, s32 v);
void func_001847F0(Inst_1DC9A0* p, void* q);
void func_00184858(Inst_1DC9A0* p, f32 v);
void func_00184818(Inst_1DC9A0* p, f32 v);
void func_00184878(Inst_1DC9A0* p, f32 v);
void func_00184838(Inst_1DC9A0* p, f32 v);
void func_00184898(Inst_1DC9A0* p, f32 v);
void func_001848B8(Inst_1DC9A0* p, void* q);
void func_00184990(Inst_1DC9A0* p, void* q);

void func_001DC9A0(Obj_1DC9A0* self)
{
    Inst_1DC9A0* p;

    if (D_00275630 & 1) {
        p = func_0011E580((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        func_001847F0(p, D_00275640);
        func_00184858(p, D_00275650);
        func_00184818(p, D_00275654);
        func_00184878(p, D_00275658);
        func_00184838(p, D_0027565C);
        func_00184898(p, D_00275660);
        func_001848B8(p, D_00275670);
    }
    if (D_00275630 & 2) {
        p = func_0011E580((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        func_00184768(p, 1);
        func_001847F0(p, D_00275640);
        func_00184858(p, D_00275650);
        func_00184818(p, D_00275654);
        func_00184878(p, D_00275658);
        func_00184838(p, D_0027565C);
        func_00184898(p, D_00275660);
        func_00184990(p, D_00275690);
        p->vtbl[33](p, D_00275680);
    }
    if (D_00275630 & 4) {
        p = func_0011E580((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        func_00184768(p, 2);
        func_001847F0(p, D_00275640);
        func_00184858(p, D_00275650);
        func_00184818(p, D_00275654);
        func_00184878(p, D_00275658);
        func_00184838(p, D_0027565C);
        func_00184898(p, D_00275660);
        func_001848B8(p, D_00275670);
        func_00184990(p, D_00275698);
        p->vtbl[33](p, D_00275680);
    }
    if (D_00275630 & 8) {
        p = func_0011E580((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        func_00184768(p, 3);
        func_001847F0(p, D_00275640);
        func_00184858(p, D_00275650);
        func_00184818(p, D_00275654);
        func_00184878(p, D_00275658);
        func_00184838(p, D_0027565C);
        func_00184898(p, D_00275660);
        func_001848B8(p, D_00275670);
        func_00184990(p, D_002756A0);
        p->vtbl[33](p, D_00275680);
    }
}

struct Obj_1DFA40 { void** vtbl; u8 pad0[0x72C - 4]; f32 f72C; };
struct Out_1DFA40 { u8 pad0[0x94]; f32 f94; s32 f98; };

typedef s32 (*Pred_1DFA40)(void* self, void* out);

extern f32 D_0026185C;
extern f32 D_002758B0;
extern f32 D_002758C0[];

void func_001DFA40(void* self, void* out)
{
    Obj_1DFA40* obj = (Obj_1DFA40*)self;
    Out_1DFA40* o = (Out_1DFA40*)out;

    if (((Pred_1DFA40)obj->vtbl[0x168 / 4])(self, out)) {
        f32 d = D_0026185C - obj->f72C;
        f32 lo = ((f32*)D_00275C60)[0];
        f32 hi = ((f32*)D_00275C60)[1];
        f32 v = D_002758C0[0] + d * (D_002758C0[1] + d * D_002758C0[2]);
        f32 r;
        if (v < lo) {
            r = lo;
        } else if (hi < v) {
            r = hi;
        } else {
            r = v;
        }
        f32 k = D_002758B0;
        o->f98 = 0;
        o->f94 = r * k;
    } else {
        o->f94 = 0.0f;
        o->f98 = 0;
    }
}
