// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "c2f.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "c6c.h"
#include "t217d.h"
#include "v24a2.h"
#include "globals.h"
#include "g27c220.h"
#include "g248748.h"
#include "s192230.h"
#include "s1d7098.h"
#include "shapes.h"

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

s32 func_001DD8E8(void* self, s32 index)
{
    return D_002623C0->levels[index].f448 & 1;
}

s32 func_001DD908(void* self, s32 index)
{
    return D_002623C0->levels[index].f448 & 0x20;
}

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

void func_001DC7B0(Contacts03* node, Contacts03** head)
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

void func_001DD5F8(C6C* self, f32 v)
{
    self->f1D6C = v;
    D_00264260 = D_002622CC;
}

extern u8 D_00275C60[];

f32 func_001EB0F8(void* p);

void func_001DD9D8()
{
    f32 r = func_001EB0F8(D_00275C60);
    D_002623C8->f10 = r;
}

void func_001DDAB8(C6C* self, f32 v)
{
    self->f2350 = v;
    self->f234C = v;
}

void func_001BEEF8(void* p);

void func_001DDBF8(void* self, void* p)
{
    func_001BEEF8(p);
}

void func_001DDCB0(void* self, s32* out)
{
    *out = D_002623C0->f19E4;
}

void func_001922E8(void* self, void* p);

void func_001DF290(C14* self, void* p)
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

void func_001DD610(C6C* self, f32 v)
{
    self->f1D68 = v;
    D_00264260 = D_002622CC;
}

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

void func_001DD9C0(void* unused, f32* out)
{
    *out = D_002623C8->dt;
}

void func_001DDBB8(C6C* self)
{
    if (--self->f2320 == 0) {
        D_002721D0.vt->m15(&D_002721D0);
    }
}

void* func_001BF0D8(void* p);

void* func_001DDC18(void* unused, void* p)
{
    return func_001BF0D8(p);
}

void func_001DDC38(C6C* self, void* v)
{
    self->f2324 = v;
}

typedef void (*VFn_001DDC40)(void* self);
struct Child_001DDC40 { VFn_001DDC40* vtbl; };

void func_001DDC40(C6C* self)
{
    Child_001DDC40* p = (Child_001DDC40*)self->f2324;
    if (p != 0) {
        VFn_001DDC40 fn = p->vtbl[50];
        if (fn != 0) {
            fn(p);
        }
    }
}

void func_001DDC78(C6C* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->f235C |= m;
}

void func_001DDC90(C6C* self, s32 bit)
{
    s32 m = 1;
    m <<= bit;
    self->f235C &= ~m;
}

void func_001DDCC8(void* unused, s32* out)
{
    *out = D_002623C0->f19E0;
}

void func_001B5F28(void* list, void* item);

void func_001DC108(u8* owner, Touch03* node)
{
    while (node != 0) {
        Touch03* next = node->next;
        func_001B5F28(owner + 0x1C0C, node);
        node = next;
    }
}

extern Quad16 D_00275730;

void func_00123ED0(RedirectObject* self);

void func_001DDCE0(RedirectObject* self)
{
    func_00123ED0(self);
    self->q320 = D_00275730;
}

void func_001276C0(RedirectObject* self);

void func_001DE768(RedirectObject* self)
{
    if (self->target == self) {
        self->targetIsSelf = 1;
    }
    func_001276C0(self);
}

void func_001DC710(Contacts03* node, Contacts03** head);
void func_001DC7B0(Contacts03* node, Contacts03** head);

Contacts03* func_001DC7D0(C6C* owner, C03* self)
{
    Contacts03* n = owner->freeTables;
    func_001DC710(n, &owner->freeTables);
    func_001DC7B0(n, &owner->usedTables);
    n->owner = self;
    return n;
}

extern u8 D_00275BC0[];

void func_001E9570(void* g);

void func_001DDAD0(void)
{
    C65* ctx = D_0027051C;
    if (ctx != 0 && ctx->state2D4 != 4) {
        u32 t = (u32)(ctx->mode2D0 - 1);
        if (t < 2) func_001E9570(D_00275BC0);
    }
}

struct __attribute__((packed)) Unaligned_1DDB20 { s32 v; };

void func_00194D30(T217D_6D0* self, s32 mode, s32 value);

void func_001DDB20(void* unused, s32 a1, s32 a2)
{
    s32 saved = a1;
    u8* p = (u8*)&D_0026FF68;
    ((Unaligned_1DDB20*)(p + 0x280))->v = a2;
    func_00194D30(&D_0026FF68, 0, saved);
}

s32 func_001DFBD0(C14* self)
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

void func_001DDA08(void* unused, f32* out)
{
    *out = D_002623C8->f10;
}

void func_001DDB58(C6C* self)
{
    if (++self->f2320 == 1) {
        func_001AA8B8(&D_002721D0, 0.0f);
        D_002721D0.vt->m14(&D_002721D0);
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
s32 func_001DC208(C6C* self, s32 index) { Stack_001DC208* s = &((Stack_001DC208*)self->f1F00)[index]; s->count--; return s->values[s->count]; }

s32 func_001DDA80(C6C* self) { return self->f231C > 0; }

void func_001DDAC8(C6C* self, f32 value) { self->f2350 = value; }

struct __attribute__((packed)) Pair_1DC150 { s32 n; void* buf; };

void* func_0018D500(s32 size);
void* func_00183058(void* a, void* b, void* c);

void func_001DC150(C6C* self, void* src, s32 n)
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
    idx = self->f1EFC;
    ((Pair_1DC150*)self->f1F00)[idx] = tmp;
    self->f1EFC = idx + 1;
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

void func_001DEBB8(C14* self)
{
    func_00192C58(self);
    func_001DFBE0(self, 1);
}

void func_001BC4D8(void* self, void* sub);
void func_001C57C8(void* self);

void func_001DFA10(C14* self)
{
    func_001BC4D8(self, (u8*)self + 0x740);
    func_001C57C8(self);
}

struct Dev_001DFB08 {
    u8 pad0[0x24];
    s32 f24;
};

void func_001B6598(void* dev, s32* out);
void func_001B6568(void* dev, s32* out);
void func_00192230(void* self, s32 kind, S192230* rec);

void func_001DFB08(C14* self, s32 code, S192230* rec)
{
    s32 loc[2];

    if (code != 0x13) {
        if (code == 0x14) {
            if (rec == (S192230*)((Dev_001DFB08*)self->f75C)) {
                func_001B6598(rec, &loc[0]);
                func_001B6568(((Dev_001DFB08*)self->f75C), &loc[1]);
            }
        }
    } else {
        Dev_001DFB08* dev = ((Dev_001DFB08*)self->f75C);
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

extern u8 D_00274738[];

void func_001C06A0(s32 a, s32 b, f32 x);
void func_0011D928(s32 a);

void func_001DD628(void* self, f32 x)
{
    C6C* s = (C6C*)self;

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

void* func_0018D5C0(u32 n);

void func_001DC740(C6C* self)
{
    void* mem = func_0018D5C0(0x1000);
    self->tables = (Contacts03*)mem;
    self->freeTables = (Contacts03*)mem;
    for (s32 i = 0; i < 0x100; i++) {
        Node_DC740* n = (Node_DC740*)((u8*)self->tables + (i << 4));
        n->prev = (i < 1) ? 0 : n - 1;
        n->next = (i > 0xFE) ? 0 : n + 1;
    }
}

s32 func_001DDA80(void* p);

s32 func_001DF5A0(C14* self, s32 mode)
{
    if (mode == 5 || self->f720 == 2 || self->f720 == 0 || self->f720 == 3 || self->f728 != 0 || func_001DDA80(self->world) != 0) return 1;
    return 0;
}

struct Obj_1DC9A0;
struct Alloc_1DC9A0;

extern s32 D_00275630[4];
extern u8 D_00275640[];
extern f32 D_00275650;
extern f32 D_00275654;
extern f32 D_00275658;
extern f32 D_0027565C;
extern f32 D_00275660;
extern f32 D_00275670[4];
extern f32 D_00275680[4];
extern f32 D_00275690[2];
extern f32 D_00275698[2];
extern f32 D_002756A0[4];

ConeVolume* func_0011E580(Alloc_1DC9A0* a0, Obj_1DC9A0* a1, void* a2, s32 a3, s32 a4);
void func_00184768(ConeVolume* p, s32 v);
void func_001847F0(ConeVolume* p, void* q);
void func_00184858(ConeVolume* p, f32 v);
void func_00184818(ConeVolume* p, f32 v);
void func_00184878(ConeVolume* p, f32 v);
void func_00184838(ConeVolume* p, f32 v);
void func_00184898(ConeVolume* p, f32 v);
void func_001848B8(ConeVolume* p, void* q);
void func_00184990(ConeVolume* p, void* q);

void func_001DC9A0(Obj_1DC9A0* self)
{
    ConeVolume* p;

    if (D_00275630[0] & 1) {
        p = func_0011E580((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        func_001847F0(p, D_00275640);
        func_00184858(p, D_00275650);
        func_00184818(p, D_00275654);
        func_00184878(p, D_00275658);
        func_00184838(p, D_0027565C);
        func_00184898(p, D_00275660);
        func_001848B8(p, D_00275670);
    }
    if (D_00275630[0] & 2) {
        p = func_0011E580((Alloc_1DC9A0*)0x51, self, 0, 0x201, -1);
        func_00184768(p, 1);
        func_001847F0(p, D_00275640);
        func_00184858(p, D_00275650);
        func_00184818(p, D_00275654);
        func_00184878(p, D_00275658);
        func_00184838(p, D_0027565C);
        func_00184898(p, D_00275660);
        func_00184990(p, D_00275690);
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
    if (D_00275630[0] & 4) {
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
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
    if (D_00275630[0] & 8) {
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
        p->desc02()->m1D(p, (Vec02*)D_00275680);
    }
}

struct Out_1DFA40 { u8 pad0[0x94]; f32 f94; s32 f98; };

typedef s32 (*Pred_1DFA40)(void* self, void* out);

extern f32 D_0026185C;
struct F4_2758B0 { f32 a, b, c, d; };
extern F4_2758B0 D_002758B0;
f32 D_002758C0[4] = { 0.0f, 2.0f, 0.0f, 0.0f };

void func_001DFA40(C14* self, void* out)
{
    C14* obj = self;
    Out_1DFA40* o = (Out_1DFA40*)out;

    if (((Pred_1DFA40)obj->desc06()->m56)(self, out)) {
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
        f32 k = D_002758B0.a;
        o->f98 = 0;
        o->f94 = r * k;
    } else {
        o->f94 = 0.0f;
        o->f98 = 0;
    }
}

void func_001DC710(Contacts03* node, Contacts03** head);
void func_001DC7B0(Contacts03* node, Contacts03** head);
ContactRow03* func_00138788(void* owner, Contacts03* h, Contacts03* handle);
void func_001861E8(void* a, Contact03* b);
void func_00129DF8(void* self);
void func_001B5F28(void* list, void* item);

void func_001DC828(C6C* owner, Contacts03* handle)
{
    ContactRow03* e = handle->head;
    if (e != 0) {
        void* freeList = &owner->pool1AF0;
        do {
            ContactRow03* next = e->next;
            ContactRow03* s1 = func_00138788(owner, e->other->contacts, handle);
            if (e->head != 0) {
                func_001861E8(owner, e->head);
                if (!(e->other->flags538 & (1ULL << 55))) {
                    func_00129DF8(e->other);
                }
                if (!(s1->other->flags538 & (1ULL << 55))) {
                    func_00129DF8(s1->other);
                }
            }
            s1->head = 0;
            e->head = 0;
            func_001B5F28(freeList, e);
            func_001B5F28(freeList, s1);
            e = next;
        } while (e != 0);
    }
    handle->head = 0;
    Contacts03** hb = &owner->usedTables;
    s32 a3 = handle - owner->tables;
    Contacts03* p = *hb;
    if (p != 0) {
        do {
            s32 b = p - owner->tables;
            u8* tab = (u8*)owner->buf1ADC;
            u8* r1 = tab + (a3 << 8);
            u8* r2 = tab + (b << 8);
            r2[a3] = 0;
            r1[b] = 0;
            p = p->next;
        } while (p != 0);
    }
    handle->owner = 0;
    func_001DC710(handle, hb);
    func_001DC7B0(handle, &owner->freeTables);
}

typedef u64 Q_1DD3E0 __attribute__((mode(TI)));
struct __attribute__((aligned(16))) Quad_001DD3E0 { f32 x, y, z, w; };
struct __attribute__((packed)) Word_001DD3E0 { s32 v; };
struct Vec3_001DD3E0 { f32 x, y, z; };
struct Locals_001DD3E0 { Quad_001DD3E0 buf[4]; Word_001DD3E0 tmp; };

extern Vec3_001DD3E0 D_0026ABF0;
extern Vec3_001DD3E0 D_0026AC00;

Q_1DD3E0 func_00188740(u8* self, Q_1DD3E0 q);
s32 func_001DD218(Quad_001DD3E0* out);
void func_001AE3B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, void* tmp, s32 k);

void func_001DD3E0(Quad_001DD3E0* a, Quad_001DD3E0* b, Word_001DD3E0* c, u8* obj, s32 k)
{
    Locals_001DD3E0 L;
    Quad_001DD3E0* base;
    Quad_001DD3E0* p;
    s32 n;

    base = &L.buf[2];

    L.buf[0] = *a;
    L.buf[0].w = 1.0f;
    L.buf[1] = *b;
    L.buf[1].w = 1.0f;

    p = base;
    n = 1;
    do {
        *(Q_1DD3E0*)p = func_00188740(obj + 0x100, *(Q_1DD3E0*)(p - 2));
        n--;
        p++;
    } while (n >= 0);

    if (func_001DD218(base) != 0) {
        void* tp = &L.tmp;
        Quad_001DD3E0* q = base;
        n = 1;
        do {
            f32 r = 1.0f / q->w;
            q->x = q->x * r * D_0026ABF0.x + D_0026AC00.x;
            q->y = q->y * r * D_0026ABF0.y + D_0026AC00.y;
            q->z = q->z * r * D_0026ABF0.z + D_0026AC00.z;
            n--;
            q++;
        } while (n >= 0);
        L.tmp = *c;
        func_001AE3B8(*(s32*)&L.buf[2].x, *(s32*)&L.buf[2].y, *(s32*)&L.buf[2].z,
                      *(s32*)&L.buf[3].x, *(s32*)&L.buf[3].y, *(s32*)&L.buf[3].z,
                      tp, k);
    }
}

struct Ent_11A338 { u32 pad0; f32 f4; u8 pad1[0x1C - 8]; s32 w1c; u8 pad2[0x28 - 0x20]; void* w28; };
struct Cur_11A338 { u8 pad0[4]; s32 a; u8 pad1[0x1C - 8]; s32 b; s32 differs() { if (this == 0) return 0; return a != b; } };

extern u8 D_002758E0[];

void* func_001DFE80(s32 k);
s32 func_001E2100(void* p);
s32 func_0015C188(s32 k);
V24A2* func_0015C1C0(s32 k);
s32 func_001DD7A0(C6C* g, s32 k);
void func_001E02C8(T217D_1380* self, s32 n);

void func_001DFEB8(T217D_1380* self)
{
    Ent_11A338* e;

    func_001AA268(self);
    e = (Ent_11A338*)func_001DFE80((D_002623C0->f19D8 << 8) | D_002623C0->f19DC);
    if (e) {
        if (e->f4 != 0.0f) {
            D_00275710->f230C = e->f4;
        }
        if (!(((Cur_11A338*)D_00275710->f2310)->differs())) {
            D_00275710->f2310 = (Cur_11A338*)((u8*)e + 8);
        }
        if (D_00275710->f2314 == 0 || !func_001E2100(D_00275710->f2314)) {
            D_00275710->f2314 = e->w28;
        }
    }
    if (func_0015C188(2)) {
        self->frame = (V24A2**)D_002758E0;
        *self->frame = func_0015C1C0(2);
    }
    func_001AA788(self, 0.6f);
    *(s32*)((u8*)self + 0x208) = (s32)0xDF7F7F7Fu;
    if (func_001DD7A0(D_00275710, (D_002623C0->f19D8 << 8) | D_002623C0->f19DC)) {
        func_001E02C8(self, 1);
    } else {
        func_001E02C8(self, 0);
    }
    if (D_002623C8->bits & 8) {
        if (((Cur_11A338*)D_00275710->f2310)->differs()) {
            self->vt->m08(self, "Press &2L&. for Bonus Commentary");
            func_001AA8B8(self, 5.0f);
            self->vt->m14(self);
            self->pressed = 1;
        } else {
            self->pressed = 0;
        }
    } else {
        self->pressed = 0;
    }
    self->f270 = 0;
}

void func_001DC710(Contacts03* a0, Contacts03** a1) {
    Contacts03* next;
    if (a0->next == 0) {
        next = a0->prev;
    } else {
        a0->next->prev = a0->prev;
        next = a0->prev;
    }
    if (next != 0) {
        next->next = a0->next;
    } else {
        *a1 = a0->next;
    }
}

struct Obj_1DD758 { s32 f0; };

u32 func_001601D8(Obj_1DD758* a0);

s32 func_001DD758(void* self, void* obj)
{
    u32 flags = func_001601D8((Obj_1DD758*)obj);
    u32 bits = flags & 3;
    s32 r = 0;
    if (flags & 4) {
        G27C230* g = D_002623C8;
        u32 m = (u32)g->flags;
        r = ((bits & m) ^ bits) < 1;
    }
    return r;
}

struct Obj_1DD7A0 { s32 f0; };

u32 func_001601D8(Obj_1DD7A0* a0);

s32 func_001DD7A0(void* self, void* obj)
{
    u32 flags = func_001601D8((Obj_1DD7A0*)obj);
    u32 bits = flags & 7;
    s32 r = 0;
    if (flags & 8) {
        G27C230* g = D_002623C8;
        u32 m = (u32)g->flags;
        r = ((bits & m) ^ bits) < 1;
    }
    return r;
}

void func_0016E0F0(s32 bits);

void func_001DDA20(C6C* a0) {
    s32 n = a0->f231C + 1;
    a0->f231C = n;
    if (n == 1) {
        func_0016E0F0(2);
    }
}

void func_0016E118(s32 n);

void func_001DDA50(C6C* self)
{
    s32 v = self->f231C - 1;
    self->f231C = v;
    if (v == 0) {
        func_0016E118(2);
    }
}

struct __attribute__((aligned(16))) Quad_1DE798 { s32 w[4]; };

extern Quad_1DE798 D_00275740;
void func_001C4458(C14* self);
f32 func_00205778(f32 a, f32 b);
void func_00188850(const Vec02* t, void* out, f32 x);

void func_001DE798(C14* self)
{
    f32 f;

    func_001C4458(self);
    f = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    self->f638 = f;
    func_00188850(&D_00248D20, (u8*)self + 0x660, f);
    self->f720 = -1;
    self->f72C = -10.0f;
    (*(Quad_1DE798*)&self->v6F0) = D_00275740;
}

void* func_001DFE80(s32 key)
{
    const G248748* p = D_00248748;
    const G248748* end = D_00248748 + 33;
    do {
        if (key != p->level) {
            p++;
        } else {
            return (void*)p;
        }
    } while (p < end);
    return 0;
}

// EXACT: literal 1 stores (no `one` local), `||` condition, D_00262E10 compared as a pointer

struct Base_1DE808 { void** vtbl; };
typedef void (*Fn3_1DE808)(void* self, void* a1, s32 a2);
typedef void (*Fn0_1DE808)(void* self);

struct Ent_275750 { s32 a, b, c; };
struct Tab_275750 { Ent_275750 e[9]; s32 end; };
extern Tab_275750 D_00275750;

void func_001C44F0(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_00129D00(void* a, s32 b, void* c);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001DFBE0(void* self, s32 flag);

void func_001DE808(C14* self)
{
    C14* s = self;
    s32 flag;

    func_001C44F0(self);
    func_00124DF8(self, 9, &D_00275750);
    ((Fn3_1DE808)s->desc03()->m34)(self, s->f6DC, 1);
    func_00129D00(s->f748, 5, &s->f74C);
    ((u8*)s->f74C)[0x10] = 1;
    ((u8*)s->f74C)[0x11] = 1;
    ((Fn0_1DE808)((Base_1DE808*)s->f748)->vtbl[47])(s->f748);
    func_00129D00(s->f750, 5, &s->f754);
    ((u8*)s->f754)[0x11] = 1;
    ((Fn0_1DE808)((Base_1DE808*)s->f750)->vtbl[47])(s->f750);
    s->f75C = (S1B6290*)func_001B6290(s->f758, self, -1, 1);
    if (s->f73C == 0 || D_00262E10 == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    func_001DFBE0(self, flag);
    s->f598 = self;
    s->f594 = 150.0f;
}

// NEAR: the call sequence, the list walk and the frame (0xC0) match; the scale constant D_002757D0 is held in s8 in retail but the C here addresses it through a pointer, so the register numbering of the constants 1 and 4 and the float tail differ (40 differing lines).

struct Pa_1DE910;
struct Pb_1DE910;
typedef s32 (*VFnChild_1DE910)(void* self, void* a1, void* a2);
typedef void (*VFnObj_1DE910)(void* self, void* a1);
extern f32 D_00261858[];
f32 D_002757C0[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_002757D0[1] = { 6.0f };
extern f32 D_002757D4;

void func_001C4ED0(void);
s32 func_00128230(C14* self);
void func_001DEB30(C14* self);
void func_001D7098(S1D7098* l, s32 zero, C03* c);
void func_001861E8(Pa_1DE910* a0, Contact03* a1);
void func_00129E10(Pb_1DE910* a, f32 v);
void func_00129FB0(Pb_1DE910* a, f32 v);

void func_001DE910(C14* self)
{
    S1D7098 loc;
    f32 f20;
    Contact03* s1;
    C03* s0;
    s32 v;
    s32 idx;

    func_001C4ED0();
    if (func_00128230(self) != 0) {
        func_001DEB30(self);
    }
    Contact03* head = ((Contact03*)self->f740);
    if (head != 0) {
        s1 = head;
        do {
            idx = (s1->end[0].body != self);
            s0 = s1->end[1 - idx].part;
            while (s0 != 0 && s0->f4E0 == 0) {
                s0 = (C03*)s0->parent;
            }
            if (s0 != 0) {
                v = s0->f4E0;
                if (v == 1 || v == 4) {
                    func_001D7098(&loc, 0, s0);
                    while (s0 != 0) {
                        if (((VFnChild_1DE910)s0->desc03()->m47)(s0, s1, &loc)) {
                            break;
                        }
                        s0 = (C03*)s0->parent;
                    }
                    ((VFnObj_1DE910*)self->desc)[80](self, &loc);
                }
            }
            s1 = s1->next;
        } while (s1 != 0);
        func_001861E8((Pa_1DE910*)self->world, ((Contact03*)self->f740));
        self->f740 = 0;
    }
    {
        f32 d = D_00261858[1] - self->f72C;
        f32 x = D_002757C0[0] + d * (D_002757C0[1] + d * D_002757C0[2]);
        f32 c0 = ((f32*)D_00275C60)[0];
        f32 c1 = ((f32*)D_00275C60)[1];
        if (x < c0) {
            f20 = c0;
        } else if (c1 < x) {
            f20 = c1;
        } else {
            f20 = x;
        }
    }
    func_00129E10(((Pb_1DE910*)self->f748), f20 * D_002757D0[0]);
    func_00129FB0(((Pb_1DE910*)self->f748), f20 * D_002757D4);
    if (self->f728 != 0 && self->f720 != 2) {
        f32 e = D_00261858[1] - self->f730;
        if (2.0f < e) {
            self->f728 = 0;
        }
    }
}

struct __attribute__((packed)) Pk16_001DCD28 { u64 a; u64 b; };
struct Pair_001DCD28 { s32 key; s32 count; };

struct Desc_001DCD28 { s32 pad0; s32 key; };

struct Obj_001DCD28;
typedef void (*VFn_001DCD28)(Obj_001DCD28* self);
struct Obj_001DCD28 { VFn_001DCD28* vtbl; u8 pad[0x2D8 - 4]; s32 f2D8; };

struct Node_001DCD28 {
    Desc_001DCD28* desc;
    u8 pad0[0x334 - 4];
    s32 flag334;
    u8 pad1[0x374 - 0x338];
    Node_001DCD28* next;
};

extern const s32 D_0024DC98[4];

Obj_001DCD28* func_00183058(Node_001DCD28* node, C6C* self, void* z);

void func_001DCD28(C6C* self)
{
    Pair_001DCD28 pairs[2];
    *(Pk16_001DCD28*)&pairs[0] = *(const Pk16_001DCD28*)D_0024DC98;
    u32 i;
    for (i = 0; i < 2; i++) {
        Node_001DCD28* n;
        for (n = (Node_001DCD28*)self->list1C54.head; n != 0; n = n->next) {
            if (n->flag334 == 0 && n->desc->key == pairs[i].key) {
                break;
            }
        }
        if (n == 0) {
            continue;
        }
        for (s32 k = 0; k < pairs[i].count; k++) {
            Obj_001DCD28* o = func_00183058(n, self, 0);
            o->f2D8 = 2;
            if (o->vtbl[19] != 0) {
                o->vtbl[19](o);
            }
            o->vtbl[20](o);
        }
    }
}

extern f32 D_00261858[];
struct F2_24DCA8 { f32 a, b; };
extern const F2_24DCA8 D_0024DCA8;



void func_001B64D8(C2F* h, s32 b);
void func_001B6628(C2F* h, s32 b);
void func_00188850(const Vec02* tab, void* out, f32 v);

void func_001DFBE0(C14* self, s32 mode)
{
    s32 old = self->f720;
    if (mode != old) {
        switch (old) {
        case 2:
            self->f730 = D_00261858[1];
            break;
        case 3:
            self->f4E0 = 0;
            self->f730 = D_00261858[1];
            break;
        }
        switch (mode) {
        case 0:
            func_001B64D8((C2F*)self->f75C, 0x351);
            break;
        case 1:
            func_001B64D8((C2F*)self->f75C, 0x352);
            break;
        case 2:
            func_001B6628((C2F*)self->f75C, 0x354);
            self->f730 = D_0024DCA8.a;
            break;
        case 3:
            func_001B6628((C2F*)self->f75C, 0x355);
            self->f4E0 = mode;
            self->f730 = D_0024DCA8.a;
            break;
        }
        switch (mode) {
        case 0:
        case 2:
        case 3:
            self->v640 = D_00248D30;
            func_00188850(&D_00248D20, &self->m660, self->f638);

            self->f580 = 0;
            break;
        default:
            self->f580 = 1;
            break;
        }
        self->f720 = mode;
        self->f724 = D_00261858[1];
    }
}

struct Arg_001DD710 { s32 pad; };
u32 func_001601D8(Arg_001DD710* a);
s32 func_001DD710(C6C* a0, Arg_001DD710* a1)
{
    s32 one = 1;
    u32 m = func_001601D8(a1);
    s32 r = 0;
    if (m & 2) r = (D_002623C8->flags & 1) ? one : 0;
    return r;
}

extern f32 D_00261858[];
f32 D_00275870[4] = { 1.0f, 0.0f, -0.75f, 0.0f };
f32 D_00275880[4] = { 0.699999988f, 0.300000012f, 0.0f, 0.0f };
extern Rgba4 D_002623E0;

struct Clamp_1DF2C8 {
    static f32 Of(f32 v, f32 lo, f32 hi)
    {
        return v < lo ? lo : (hi < v ? hi : v);
    }
};

f32 func_00205210(f32 x);
void func_00126A48(C14* s, u32 c);
void func_00125C90(C14* s, void* a, void* b);

void func_001DF2C8(C14* self, void* a1, void* a2)
{
    Rgba4 out;
    Rgba4 col;
    f32 t;
    if (!(self->flags & 0x100000000UL)) {
        *(u32*)&col = 0x800000A0;
        if (self->f728 != 0) {
            if (self->f720 != 2) {
                t = (D_00261858[1] - self->f730) * 0.5f;
            } else {
                t = 0.0f;
            }
            f32 r = func_00205210((D_00261858[1] - self->f72C) * 10.0f);
            f32 a = D_00275870[0] + t * (D_00275870[1] + t * D_00275870[2]);
            a = Clamp_1DF2C8::Of(a, ((f32*)&D_00275C60)[0], ((f32*)&D_00275C60)[1]);
            f32 b = D_00275880[0] + r * (D_00275880[1] + r * D_00275880[2]);
            b = Clamp_1DF2C8::Of(b, ((f32*)&D_00275C60)[0], ((f32*)&D_00275C60)[1]);
            f32 k = a * b;
            f32 inv = 1.0f - k;
            out.r = (s32)(inv * D_002623E0.r + k * col.r);
            out.g = (s32)(inv * D_002623E0.g + k * col.g);
            out.b = (s32)(inv * D_002623E0.b + k * col.b);
            out.a = D_002623E0.a;
        } else {
            out = D_002623E0;
        }
        func_00126A48(self, *(u32*)&out);
        func_00125C90(self, a1, a2);
    }
}

s32 D_00275630[4] = { 1, 0, 0, 0 };
f32 D_00275670[4] = { -0.2f, 0.3f, -1.0f, 0.0f };
f32 D_00275680[4] = { 100.0f, -150.0f, 500.0f, 0.0f };
f32 D_00275690[2] = { 500.0f, 2500.0f };
f32 D_00275698[2] = { 500.0f, 2500.0f };
f32 D_002756A0[4] = { 500.0f, 2500.0f, 0.0f, 0.0f };
Quad16 D_00275730 = { 0x42C80000, 0, 0, 0 };

Quad_1DE798 D_00275740 = { { 0x3F800000, 0, 0, 0 } };
Tab_275750 D_00275750 = { {
    { 0x0, 0x34D, 0x6DC }, { 0x0, 0x350, 0x758 }, { 0x4, 0x60, 0x748 },
    { 0x4, 0x50, 0x750 }, { 0x4, 0x34E, 0x744 }, { 0x2, 0x161, 0x588 },
    { 0x2, 0x162, 0x58C }, { 0x2, 0x163, 0x590 }, { 0x4, 0x160, 0x584 }
    }, 0 };
F4_2758B0 D_002758B0 = { 1.5f, 0.0f, 0.0f, 0.0f };
extern const s32 D_0024DC98[4] = { 0x58, 0x23, 0x56, 0x5 };
extern const F2_24DCA8 D_0024DCA8 = { 3.402823466e+38f, 0.0f };
