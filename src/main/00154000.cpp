// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c50.h"
#include "c1e.h"
#include "t219c.h"

void func_00155F90();
void func_00155FA0(C50* self);

void func_00156108(C50* self, s32 a1)
{
    if (self->f2D4 == -1) {
        self->f2D8 = a1;
    } else if (self->f2D4 == 0) {
        if (a1 == 0) {
            func_00155F90();
        } else if (a1 == -1) {
            func_00155FA0(self);
        } else {
            self->f2D8 = a1;
        }
    }
    self->f34C = 1;
}

void func_00156178(C50* a0, s32 a1)
{
    a0->f308 = a1;
    a0->f34C = 1;
}

void* func_00155778(void* a0, s32 a1);
void func_00156188(void* self, s32 a1);

void func_00156218(void* a0, s32 a1)
{
    void* r = func_00155778(a0, 1);
    func_00156188(r, a1);
}

void* func_00158DD8(void* a0, s32 a1);
void func_00156188(void* self, s32 a1);

void func_00156250(void* a0, s32 a1)
{
    void* r = func_00158DD8(a0, 1);
    func_00156188(r, a1);
}

struct __attribute__((aligned(16))) Quad_001566C8 { s32 a, b, c, d; };
struct Msg_001566C8 {
    s32 kind;
    u8 pad0[0x20 - 4];
    Quad_001566C8 q;
    s32 zero;
    f32 f;
    u8 pad1[0x50 - 0x38];
};
struct Game_001566C8 {
    u8 pad0[0x1D0C];
    void* f1D0C;
};
typedef void (*VFn_001566C8)(void* self, void* msg);

extern Game_001566C8* D_00275710;

void func_001566C8(Quad_001566C8* a0, f32 f)
{
    void* obj = D_00275710->f1D0C;
    if (obj != 0) {
        Msg_001566C8 m;
        m.kind = 12;
        m.q = *a0;
        m.f = f;
        m.zero = 0;
        VFn_001566C8* vt = *(VFn_001566C8**)obj;
        vt[31](obj, &m);
    }
}

struct Obj_1550B8;
typedef void (*VFn_1550B8)(Obj_1550B8* self, void* arg);
struct Sub_1550B8 { u8 pad[0x7C]; void* value; };
struct Obj_1550B8 { VFn_1550B8* vtbl; u8 pad[0x2D0 - 4]; Sub_1550B8* sub; };

void func_001550B8(Obj_1550B8* self)
{
    self->vtbl[25](self, self->sub->value);
}

C50* func_001557B8(C50* self, s32 value)
{
    if (value == 1) {
        self->f34C = value;
    }
    return self;
}

extern f32 D_0026185C;

s32 func_00155FB0(C50* self)
{
    if (D_0026185C < self->f340) {
        return 1;
    }
    if (self->f2D4 < 2) {
        if (self->f2D4 >= 0) {
            if (self->f2D8 == 0) {
                return 1;
            }
        }
    }
    return 0;
}

struct Frame_157E00 {
    s32 out[4];
    s32 flag;
    s32 pad[3];
    s32 pair[2];
    u8 tail[0x18];
};

void func_0018D608(void);
void func_0018D6F0(void);
void func_001579B0(void* a, void* b, s32* out);
void func_00157320(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3);
void func_00157B88(void* a, void* b, s32* out, s32* pair);
void func_001575D8(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3, s32 p0, s32 p1);

void func_00157E00(void* a, Rec50* b, void* c)
{
    Frame_157E00 f;
    if (a == 0) {
        return;
    }
    func_0018D608();
    f.flag = 1;
    func_001579B0(a, b, f.out);
    if (b->f120 == 1) {
        func_00157320(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3]);
    } else {
        if (b->f130 == 2) {
            func_00157B88(a, b, f.out, f.pair);
        } else {
            f.pair[0] = 0;
            f.pair[1] = 0;
        }
        func_001575D8(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3], f.pair[0], f.pair[1]);
    }
    func_0018D6F0();
}

struct Word_154EE0 {
    s32 value;
};

struct __attribute__((packed)) Packed_154EE0 {
    s32 value;
};

struct Buffer_154EE0 {
    u8 pad0[0x4C];
    s32 cap;
    Packed_154EE0* items;
    void* source;
};

void* func_0018D500(s32 size);
void* func_00137B90(void* src);
Word_154EE0 func_00137C40(void* src);

void func_00154EE0(Buffer_154EE0* self, s32 count, void* unused, void* src)
{
    s32 limit = 31;
    s32 cap = (limit < count) ? 32 : count;
    self->cap = cap;
    self->items = (Packed_154EE0*)func_0018D500(cap * 4);
    self->source = func_00137B90(src);
    for (s32 i = 0; i < count; i++) {
        Word_154EE0 tmp = func_00137C40(src);
        if (i < self->cap) {
            self->items[i] = *(Packed_154EE0*)&tmp;
        }
    }
}

void* func_0018D500(s32 size);
void func_001549C8(void* mem);
void func_001289C0(void* self, s32 count);
s32 func_00137CC0(s32 count);
T2176* func_0014D9A8(s32 kind);
void func_00154C80(void* self, s32 count);
s32 func_00137BE0(s32 count);
void* func_00155778(void* self, s32 flag);
void func_00154EE0(void* self, s32 count, void* unused, s32 src);

void func_00154F98(C50* self, s32 count)
{
    void* mem = func_0018D500(0x200);
    self->rec = (Rec50*)mem;
    func_001549C8(mem);
    func_001289C0(self, count);
    s32 index = func_00137CC0(count);
    if (index != -1) {
        T2176* obj = func_0014D9A8(index);
        self->rec->curve20 = obj;
        void (*fn)(T2176* self, void* stream) = obj->vt->m00;
        if (fn != 0) {
            fn(obj, (void*)count);
        }
    }
    if (self->rec->kind == 4) {
        func_00154C80(&self->rec->curve20, count);
    }
    s32 n = func_00137BE0(count);
    if (n != 0) {
        void* b = func_00155778(self, 1);
        func_00154EE0((u8*)b + 0x130, n, self, count);
    }
}

void func_00127048(void* self);

void func_00155080(C50* self)
{
    func_00127048(self);
    self->rec->uses++;
}

struct Rec_001550E8 { u8 pad00[0x18]; void* f18; u8 pad1C[0x18]; s32 f34; };

void func_001249A8(C50* self);
Rec50* func_00155778(C50* self, s32 mode);
void func_00158288(Rec50* p, C50* self);
Rec_001550E8* func_0015A418(void* a0, s32 a1, s32 a2, C50* a3);
s32 func_001300E8(Rec_001550E8* p, s32 k);
void func_001DBCC8(void* a0, void (*cb)(void), C50* a2, s32 a3, s32 a4);

void func_001550E8(C50* self)
{
    Rec50* s2;

    func_001249A8(self);
    if (self->key2F8 == -1 && self->id304 == -1 && self->id30C == -1 && self->id300 == -1) {
        Rec50* p = self->rec;
        if (p->kind != 3 && (p->f120 != 0 || p->f188 == -1)) goto tail;
    }
    s2 = func_00155778(self, 1);
    if (self->id2F8[0] != -1) {
        Rec_001550E8* r = func_0015A418(self->world, 0x104, self->id2F8[0], self);
        s2->target = r;
        if (r != 0) func_001DBCC8(self->world, (void (*)(void))func_001550B8, self, 0, 0);
    }
    if (self->id2F8[1] != -1) {
        s2->found[0] = func_0015A418(self->world, 0x104, self->id2F8[1], self);
    }
    if (self->id304 != -1) {
        s2->found[1] = func_0015A418(self->world, 0x104, self->id304, self);
    }
    if (self->id300 != -1) {
        Rec_001550E8* s1 = func_0015A418(self->world, 0x104, self->id300, self);
        if (func_001300E8(s1, 3) != 0) s2->found[2] = s1;
    }
    if (self->id30C != -1) {
        Rec_001550E8* r = func_0015A418(self->world, 0x104, self->id30C, self);
        s2->value20 = r->f34;
        s2->target = r->f18;
    }
tail:
    func_00158288(self->rec, self);
}

void func_00155678(C50* self, s32 mode, C01* p)
{
    if (mode == 2) {
        if (p == self->held344) {
            p->desc->m18(p, self);
            self->held344 = 0;
        } else if (p == self->held348) {
            p->desc->m18(p, self);
            self->held348 = 0;
        }
    }
}

void* func_0018D568(s32 size, void* owner);

Rec50* func_001556E8(Rec50* self)
{
    Rec50* n;
    if (self->uses < 2) return self;
    n = (Rec50*)func_0018D568(0x200, self);
    if (self->kind == 3 && self->f24 != 0) {
        n->f24 = func_0018D568(0x28 * self->value20, self->f24);
    }
    n->uses = 1;
    self->uses -= 1;
    return n;
}

Rec50* func_00155778(C50* self, s32 mode)
{
    if (mode == 1) {
        self->f34C = mode;
        self->rec = func_001556E8(self->rec);
    }
    return self->rec;
}

void func_00155F28(C50* self)
{
    if ((self->flags & 0x0C000000) == 0x08000000) {
        return;
    }
    C02* p = (C02*)self->parent;
    while (p != 0) {
        if ((p->flags & 0x0C000000) == 0x08000000) {
            break;
        }
        p = (C02*)p->parent;
    }
    if (p != 0) {
        self->f88 = p->f88;
    }
}

extern f32 D_0026185C;

void func_00155F78(C50* self, f32 f)
{
    self->f340 = D_0026185C + f;
}

void func_00155FA0(C50* self)
{
    self->f340 = -1.0f;
}

struct Obj_156000;

void func_00155F90();
void func_00155FA0(Obj_156000* self);

void func_00156000(Obj_156000* self, s32 a1)
{
    if (a1 != 0) {
        func_00155FA0(self);
    } else {
        func_00155F90();
    }
}

struct Obj_156030;

s32 func_00155FB0(Obj_156030* self);

void func_00156030(Obj_156030* self, s32* out)
{
    *out = func_00155FB0(self) == 0;
}

void func_00123ED0(void*);
void func_00152438(void*,s32);
void func_00154C10(C50* self)
{
    func_00123ED0(self);
    self->f2D8=-1;
    self->f2E0=10.0f;
    self->id2F8[0]=-1;
    self->id2F8[1]=-1;
    self->id304=-1;
    self->id300=-1;
    self->id30C=-1;
    self->f2D4=-1;
    self->f2DC=10.0f;
    self->f340=-1.0f;
    self->f310=-1;
    func_00152438(self->list314,0x320);
}

void func_00158198(void*,void*,void*,f32,f32,f32,f32,void*);
void func_001557D0(void* self,void* a,void* b,f32 x,f32 y,f32 z,f32 w)
{
    u8* p=(u8*)func_00155778(self,1);
    func_00158198(p+16,a,b,x,y,z,w,self);
}

void func_00156060(void* self,s32* out)
{
    *out=func_00155FB0((C50*)self);
}

void func_0013A128(void*,void*);
void func_0019E158(void*,void*);
f32 func_001EAAE0(f32,f32);
void func_00156088(u8* self)
{
    *(s32*)(self+0x34C)=0;
    if (*(void**)(self+0x348)) func_0013A128(*(void**)(self+0x348),*(void**)(self+0x2D0));
    if (*(void**)(self+0x344)) func_0019E158(*(void**)(self+0x344),*(void**)(self+0x2D0));
    f32 value;
    if (*(s32*)(self+0x2D4)==3) value=func_001EAAE0(*(f32*)(self+0x2DC),*(f32*)(self+0x2E0))*60.0f;
    else value=func_001EAAE0(*(f32*)(self+0x2DC),*(f32*)(self+0x2E0));
    *(f32*)(self+0x328)=value;
}

void* func_001F5C0C(void*,s32,s32);
void func_00156188(u8* self,s32 kind)
{
    *(s32*)(self+0x1B0)=kind;
    func_001F5C0C(self+0x1F0,0,12);
    if (kind!=24) {
        if (kind==27) {
            *(s32*)(self+0x1F0)=-1;
            *(f32*)(self+0x1F4)=10.0f;
        }
    } else {
        *(f32*)(self+0x1F0)=25.0f;
        *(f32*)(self+0x1F4)=0.8f;
        *(f32*)(self+0x1F8)=0.8f;
    }
}

struct Item_154880 {
    u8 pad0[0x34];
    f32 f34;
    f32 f38;
    u8 pad1[0x44 - 0x3C];
    void* p44;
    u8 pad2[0x60 - 0x48];
};

struct Loc_154880 {
    u32 hdr;
    s32 count;
    u8* items;
    u8 pad[0x30 - 0xC];
    u8 tmp[0x10];
    u8 tail[0x10];
};

void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D658(s32 size);
void func_0018D800(void* dst, void* src, s32 size);
void func_00153528(Loc_154880* loc, s32 count);
void func_00152470(void* tmp, Item_154880* item);
void func_00153EC0(Loc_154880* loc, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_00154880(s32 count, u8* data, f32* values, f32* out)
{
    Loc_154880 loc;
    s32 i;

    func_0018D608();
    func_00153528(&loc, count);
    for (i = 0; i < count; i++) {
        Item_154880* item = (Item_154880*)(loc.items + i * 0x60);
        item->p44 = func_0018D658(count * 4);
        func_0018D800(item->p44, data + i * count * 4, count * 4);
        item->f38 = values[i];
        func_00152470(loc.tmp, item);
    }
    loc.count = count;
    func_00153EC0(&loc, 0, 0, 0, 0, 0);
    for (i = 0; i < count; i++)
        out[i] = *(f32*)(loc.items + i * 0x60 + 0x34);
    func_0018D6F0();
}

void func_00155F90(C50* self)
{
    self->f340 = 3.4028234663852886e+38f;
}

struct __attribute__((aligned(16))) Q_157320 { s32 a, b, c, d; };
struct Hdr_157320 { u8 pad[4]; s32* f4; s32 f8; };
C1E* func_0019E040(u8* ctx, s32 flag);
void func_0019E158(C1E* a, Rec50* b);
T219C* func_0019EA78(s32 a, C1E* b);
void func_001A0338(C1E* self, s32 kind, T219C* extra);
void func_001583E8(T219C* a, Rec50* b);
f32 func_001EAAE0(f32 a, f32 b);
s32 func_00152720(void* p);

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))
typedef void (*VFn)();

void func_00157320(Rec50* self, Hdr_157320* h, s32 n, Q_157320* pos, Q_157320* q2, f32* v5, f32* v6)
{
    u8* s7 = AT(u8*, self, 0x7C);
    C1E* node = 0;
    u8* c = (u8*)self + 0x120;
    s32 i;
    if (h) {
        if (h->f4) node = (C1E*)*h->f4;
    }
    if (!node) {
        node = func_0019E040((u8*)D_00275710, AT(s32, c, 0xC4));
        if (!node) return;
        if (h) {
            if (h->f4) *h->f4 = (s32)node;
        }
        func_0019E158(node, self);
        if (h) {
            if (h->f8) {
                typedef void (*F)(C1E*, s32);
                (*(F*)(AT(u8*, node, 0) + 0x6C))(node, h->f8);
            }
        }
    }
    if (node) {
    for (i = 0; i < n; i++) {
        T219C* it = func_0019EA78(AT(s32, c, 0x90), node);
        if (!it) break;
        Q_157320* s1 = pos + i;
        u8* cls = AT(u8*, it, 0);
        f32 f = func_001EAAE0(AT(f32, c, 0xB0), AT(f32, c, 0xB4));
        typedef void (*F0)(T219C*, Q_157320*, s32, f32);
        (*(F0*)cls)(it, s1, AT(s32, c, 0xC0), f);
        f32 f1 = AT(f32, c, 0xA4);
        if (f1 != 0.0f || AT(f32, c, 0xA8) != 0.0f) {
            AT(f32, it, 0x34) = f1;
            AT(f32, it, 0x38) = AT(f32, c, 0xA8);
        }
        AT(Q_157320, it, 0xA0) = q2[i];
        AT(f32, it, 0x18) = v5[i];
        AT(f32, it, 0x1C) = v6[i] - v5[i];
        AT(Q_157320, it, 0x40) = AT(Q_157320, self, 0x110);
        func_001583E8((T219C*)((u8*)it + 0xB0), self);
        if (AT(s32, c, 0xB8)) AT(s32, it, 0x20) = AT(s32, c, 0xB8);
        if (s7) {
            AT(Q_157320, it, 0x50) = AT(Q_157320, s7, 0x110);
            AT(Q_157320, it, 0x60) = AT(Q_157320, s7, 0x120);
            AT(Q_157320, it, 0x70) = AT(Q_157320, s7, 0x130);
        }
        if (AT(s32, c, 0x94) != -1) {
            C1E* o = (C1E*)func_0019EA78(AT(s32, c, 0x94), 0);
            if (!o) break;
            typedef void (*F1)(f32, C1E*, void*, s32);
            F1 fn = *(F1*)(*(u8**)o);
            fn(AT(f32, it, 0x30) * 0.5f, o, (u8*)it + 0x80, 0);
            func_001A0338(o, 1, it);
        }
        {
            u8* cl = AT(u8*, it, 0);
            VFn* p = (VFn*)(cl + 4);
            if (*p) ((void (*)(T219C*, Rec50*))*p)(it, self);
        }
    }
    if (func_00152720((u8*)node + 0x558)) {
        typedef void (*F2)(C1E*);
        (*(F2*)(AT(u8*, node, 0) + 0x1C))(node);
    }
    }
}

struct Span_00156FC8 {
    f32 lo;
    f32 hi;
};

struct Slot_00156FC8 {
    s32 count;
    f32 step;
    f32 rate;
    f32 phase;
    f32 out10;
};

f32 func_001EA408(f32 x);
f32 func_001EAAE0(f32 a, f32 b);
void func_00156FC8(s32 n, Span_00156FC8* span, s32 k, Slot_00156FC8* out) { if (n > 0) { out->count = n < k ? n : k; } else { out->count = k; } s32 steps = k - 1; steps += out->count; steps = steps / out->count; f32 w = func_001EA408(span->hi - span->lo); f32 rate = 6.2831855f / (f32)out->count; f32 step = w / (f32)steps; out->rate = rate; out->step = step; out->phase = span->lo + step * 0.5f; out->out10 = func_001EAAE0(0.0f, 6.2831855f); }


typedef void (*VFn_157FF8)(void* self, void* frame);

struct __attribute__((aligned(16))) Quad_157FF8 { s32 a, b, c, d; };

struct Frame_157FF8 {
    s32 kind;
    u8 pad0[0x1C];
    Quad_157FF8 pos;
    f32 f30;
    s32 f34;
    void* f38;
    u8 pad1[0xC];
};

struct Sub_157FF8 { u8 pad0[0x120]; s32 f120; u8 pad1[0x8C]; s32 f1B0; };

struct Elem_157FF8 { VFn_157FF8* vtbl; u8 pad0[0x8C]; Sub_157FF8* f90; };

struct List_157FF8 { u8 pad0[0x90]; s32 count; Elem_157FF8* items[1]; };

struct Owner_157FF8 { u8 pad0[0x1CE8]; List_157FF8* list; };

void func_00157FF8(void* self, void* obj, f32 x)
{
    Frame_157FF8 frame;
    List_157FF8* list = (*(Owner_157FF8**)((u8*)&D_00275710))->list;

    if (list == 0) return;
    for (s32 i = 0; i < list->count; i++) {
        Elem_157FF8* e = list->items[i];
        frame.kind = 4;
        frame.pos = *(Quad_157FF8*)self;
        if (e->f90->f120 == 1) {
            switch (e->f90->f1B0) {
            case 4:
                frame.kind = 0x14;
                frame.f30 = x;
                break;
            case 2:
                frame.kind = 0x24;
                frame.f38 = obj;
                break;
            }
        }
        e->vtbl[31](e, &frame);
    }
}

struct __attribute__((aligned(16))) Quad_157EF8 { s32 a, b, c, d; };
struct __attribute__((aligned(16))) Blk_157EF8 { Quad_157EF8 q[8]; };
struct __attribute__((aligned(16))) Tail_157EF8 { Quad_157EF8 q[4]; };
void* func_001F5C0C(void* p, s32 v, u32 n);
struct Pair_157EF8 { s32 z; s32 b; s32 c; Pair_157EF8() { func_001F5C0C(this, 0, sizeof(*this)); } };
struct __attribute__((aligned(16))) Frame_157EF8 { u8 pad0[0x20]; Quad_157EF8 self_copy; u8 pad1[0x30]; Quad_157EF8 a1_copy; u8 pad2[0x30]; Blk_157EF8 blk; s32 f120; u8 pad3[0x8C]; Tail_157EF8 tail; u8 pad4[0x10]; };

void func_001549C8(void* mem);
void func_00157E00(void* a, void* b, void* c);

void func_00157EF8(Quad_157EF8* self, Quad_157EF8* a1, void* a2, Tail_157EF8* a3, Blk_157EF8* a4, s32 a5, s32 a6)
{
    Frame_157EF8 f;
    func_001549C8(&f);
    Pair_157EF8 p;
    f.self_copy = *self;
    f.a1_copy = *a1;
    f.blk = *a4;
    p.b = a5;
    p.c = a6;
    f.f120 = 1;
    f.tail = *a3;
    func_00157E00(a2, &f, &p);
}
