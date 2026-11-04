// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c6e.h"
#include "t21e3.h"
#include "c6c.h"
#include "v24a0.h"
#include "v24a2.h"
#include "list_iter.h"

typedef void (*VFn_1B0F70)(void* self, s32 arg);

struct Obj_1B1DA8 {
    s32 pad_0;
    f32 f4;
    f32 f8;
};

void func_001B1BF0(Obj_1B1DA8* o);

void func_001B1DA8(Obj_1B1DA8* o, f32 v)
{
    o->f8 = v;
    if (o->f4 < 0.0f) {
        o->f4 = v;
    }
    func_001B1BF0(o);
}

struct Obj_1B2118 {
    u8 pad_0[0x410];
    u32 f410;
    u8 pad_414[0x538 - 0x414];
    u64 f538;
};

s32 func_001B2118(void* unused, Obj_1B2118* o)
{
    s32 r = 0;
    if ((o->f538 & (1UL << 43)) == 0) {
        r = o->f410 != 0;
    }
    return r;
}


extern u32 D_00275718;
void func_00137A60(void* a, s32 b, void* c);

void func_001B2B50(void* a0, V24A2_ImgB* a1)
{
    func_00137A60(a0, 12, a1);
    a1->f8 = D_00275718 + a1->f8;
    a1->fC = (u32)((a1->f4 << 2) + 15) >> 4;
}

struct Bits_1B29E0 {
    u64 bits;
};

struct Obj_1B29E0 {
    u8 pad0[2];
    u16 flags;
};

u64 func_001B2988(Obj_1B29E0* obj, s32 p1, s32 p2);
void func_00161708(void* ctx, s32 kind, u64 value);
void func_001F5C0C(void* p, s32 v, s32 n);

void func_001B29E0(Obj_1B29E0* obj, s32 p1, s32 p2, s32 flag, void* ctx)
{
    Bits_1B29E0 a;
    Bits_1B29E0 b;
    Bits_1B29E0 c;
    Bits_1B29E0 d;
    Bits_1B29E0 e;
    s32 sel = flag ^ 5;
    u64 one = 1;

    func_001F5C0C(&a, 0, 8);
    func_001F5C0C(&b, 0, 8);
    func_001F5C0C(&c, 0, 8);
    func_001F5C0C(&d, 0, 8);
    func_001F5C0C(&e, 0, 8);

    a.bits = func_001B2988(obj, p1, p2);
    s32 kindA = 7;
    if (sel != 0) {
        kindA = 6;
    }
    func_00161708(ctx, kindA, a.bits);

    b.bits = ((b.bits | one | 0x20) & ~0x1C0ULL) | 0x40;
    s32 kindB = 0x15;
    if (sel != 0) {
        kindB = 0x14;
    }
    func_00161708(ctx, kindB, b.bits);

    if (obj->flags & 1) {
        e.bits = (e.bits & ~3ULL) | one;
    }
    if (obj->flags & 2) {
        e.bits = (e.bits & ~0xCULL) | 4;
    }
    s32 kindC = 9;
    if (sel != 0) {
        kindC = 8;
    }
    func_00161708(ctx, kindC, e.bits);
}

struct Rec_1B2BA8 {
    u32 flags;
    u8 pad4[0x14];
};

extern s32 D_00274508;
extern Rec_1B2BA8* D_0027450C;
extern s32 D_00274514;

u16 func_00137BE0(void* self);
void* func_0018D5C0(s32 bytes);
void func_001B2B50(void* self, Rec_1B2BA8* rec);

void func_001B2BA8(void* self)
{
    s32 i;
    s32 count = func_00137BE0(self);
    D_00274508 = count;
    D_0027450C = (Rec_1B2BA8*)func_0018D5C0(count * 0x18);
    D_00274514 = 0;
    for (i = 0; i < D_00274508; i++) {
        func_001B2B50(self, &D_0027450C[i]);
        if (D_0027450C[i].flags & 0x10000000) {
            D_00274514++;
        }
    }
    {
        s32 done = D_00274514;
        s32 left = D_00274508 - done;
        if (done < left) {
            D_00274514 = left;
        }
    }
}

void func_00137A60(void* self, s32 size, void* obj);

void func_001B2CA8(void* self, V24A2_ImgA* obj)
{
    func_00137A60(self, 0x14, obj);
    s32 base = D_00275718;
    u32 bytes = obj->bytes;
    s32 off = obj->f10;
    obj->f14 = (bytes + 0xF) >> 4;
    obj->f10 = base + off;

}

struct Rec_1B2CF8 {
    u8 pad0[4];
    u32 flags;
    u8 pad8[0x18];
};

extern s32 D_00274500;
extern Rec_1B2CF8* D_00274504;
extern s32 D_00274510;

u16 func_00137BE0(void* self);
void* func_0018D5C0(s32 bytes);
void func_001B2CA8(void* self, Rec_1B2CF8* rec);

void func_001B2CF8(void* self)
{
    s32 i;
    s32 count = func_00137BE0(self);
    D_00274500 = count;
    D_00274504 = (Rec_1B2CF8*)func_0018D5C0(count * 0x20);
    D_00274510 = 0;
    for (i = 0; i < D_00274500; i++) {
        func_001B2CA8(self, &D_00274504[i]);
        if (D_00274504[i].flags & 0x10000000) {
            D_00274510++;
        }
    }
    {
        s32 done = D_00274510;
        s32 left = D_00274500 - done;
        if (done < left) {
            D_00274510 = left;
        }
    }
}

extern s32 D_00274518;

void func_00168D68(void* dst, s32 size, s32 align);
void func_001692B0(s32 a, void* b);

void func_001B3450(void)
{
    s32 scratch[4];
    func_00168D68(scratch, 0x1E00, 0x4000);
    func_001692B0(0x10000000, scratch);
    D_00274518 = 0;
}

void func_00124A48(void* self);

typedef void (*VFn_1B11A0)(void* self, s32 arg);

typedef void (*VFn_1B15D0)(void* self, s32 arg);

extern f32 D_0026185C;

typedef void (*VFn_1B1608)(void* self, s32 arg);

extern s32 D_002626D0;
extern u8 D_0027DC20[];

void func_001B1CF8(void* self, s32 code);
s32 func_001B1D38(void* self);
void func_001B1D70(void* self, f32 v);
void func_001B1DA8(void* self, f32 v);
void func_001F5C0C(void* p, s32 v, s32 n);

struct Hdr_1B1B38 {
    u8 pad0[0xC];
    s32 f0C;
};

struct Obj_1B1B38 {
    Hdr_1B1B38* f0;
    u8 pad0[0x2D0 - 0x4];
    u8* f2D0;
};

void func_001B1B38(Obj_1B1B38* self)
{
    if (self->f0 == 0) {
        func_001B1CF8(self, 0x2C);
    }
    if (func_001B1D38(self) == 0) {
        func_001B1D70(self, 100.0f);
        func_001B1DA8(self, 400.0f);
    }
    if ((self->f0->f0C & 0x10000000) == 0) {
        s32 idx = D_002626D0;
        if (idx < 0x4000) {
            u8* p = D_0027DC20 + idx * 16;
            self->f2D0 = p;
            D_002626D0 = idx + 1;
            func_001F5C0C(p, 0, 16);
        }
    }
}

struct Slot_1B1BF0 { u8 pad[0xC0]; s32 value; };

void func_001B1BF0(Slot_1B1BF0* self)
{
    self->value = 0;
}

struct Holder_1B1CF8 { void* link; };

void* func_001B4688(s32 key);
void func_001B1BF0(void* self);

void func_001B1CF8(Holder_1B1CF8* self, s32 key)
{
    void* found = func_001B4688(key != -1 ? key : 0x2C);
    self->link = found;
    if (found)
        func_001B1BF0(self);
}

struct Pair_1B1D38 { u8 pad[4]; f32 a; f32 b; };

s32 func_001B1D38(Pair_1B1D38* p)
{
    s32 r = 0;
    if (0.0f <= p->a && 0.0f <= p->b)
        r = 1;
    return r;
}

struct Pair_1B1D70 { u8 pad[4]; f32 a; f32 b; };

void func_001B1BF0(void* self);

void func_001B1D70(Pair_1B1D70* p, f32 v)
{
    p->a = v;
    if (p->b < 0.0f)
        p->b = v;
    func_001B1BF0(p);
}

typedef void (*VFn_1B00E8)(void* self, s32 arg);

void func_001AECB0(void* self);

struct Entry_1B2988 { u8 pad[0x18]; u64 tail; };
struct Cell_1B2988 { u8 pad[0x10]; u64 value; };
struct Table_1B2988 { u8 pad[8]; u8* flag; Entry_1B2988** entries; Cell_1B2988** cells; };

u64 func_001B2988(Table_1B2988* t, s32 i, s32 j)
{
    Entry_1B2988* e = t->entries[i];
    s32 stride = 1;
    if (*t->flag == 0) stride = 3;
    Cell_1B2988* c = t->cells[i * stride + j];
    u64 r = e->tail;
    if (c != 0) r |= c->value;
    return r;
}

typedef void (*VFn_1B0160)(void* self, s32 arg);

struct Obj_1B1FB0 {
    u8 pad_0[0x40];
    f32 f40;
};

void func_001B1BF8(Obj_1B1FB0* o);
void func_001B1BF0(Obj_1B1FB0* o);

void func_001B1FB0(Obj_1B1FB0* o, f32 v)
{
    o->f40 = v;
    func_001B1BF8(o);
    func_001B1BF0(o);
}

struct Obj_1B1FE0 {
    u8 pad_0[0x44];
    f32 f44;
};

void func_001B1BF8(Obj_1B1FE0* o);
void func_001B1BF0(Obj_1B1FE0* o);

void func_001B1FE0(Obj_1B1FE0* o, f32 v)
{
    o->f44 = v;
    func_001B1BF8(o);
    func_001B1BF0(o);
}

typedef void (*VFn_1B0EA8)(void* self, s32 arg);

s32 func_00137B90(void* src);
T2176* func_0014D9A8(s32 kind);
void func_0011EC40(void* self, void* obj);

void func_001B2840(C6E* self, void* obj)
{
    T2176* p = func_0014D9A8(func_00137B90(obj));
    self->curve = p;
    void (*fn)(T2176* self, void* stream) = p->vt->m00;
    if (fn != 0) {
        fn(p, obj);
    }
    func_0011EC40(self, obj);
}

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

typedef void (*VFn_1B04D0)(void* self, s32 v);

typedef void (*VFn_1B0EE0)(void* self, s32 arg);

extern f32 D_0026185C;

struct Sub_1B2640 {
    u8 pad0[0xC];
    s32 f0C;
};

struct Obj_1B2640 {
    Sub_1B2640* f0;
    u8 pad4[0xBC];
    s32 fC0;
    u8 padC4[0xC];
};

struct Ctx_1B2640 {
    u8 pad0[0x21C];
    s32 f21C;
};

extern u8 D_00261990[];
extern u8 D_002622A8[];

void func_001B2358(void* o);

void func_001B2640(Obj_1B2640* o)
{
    if (o->f0 != 0) {
        Ctx_1B2640* c = *(Ctx_1B2640**)D_00261990;
        s32 bits = o->f0->f0C;
        s32 need = c->f21C;
        s32 a2 = 0;
        if ((bits & 0x10000000) != 0) {
            goto set;
        }
        if ((need & bits) != need) {
            goto skip;
        }
    set:
        a2 = 1;
    skip:
        if (a2 != 0) {
            if (o->fC0 == 0) {
                func_001B2358(o);
                if (o->fC0 == 0) {
                    goto done;
                }
            }
            V24A0* g = (V24A0*)D_002622A8;
            u64 hi = (u64)(u32)((u8*)o + 0xD0) << 32;
            u64 v = (u64)(s64)(o->fC0 | 0x40000000) | hi;
            *(u64*)g->cur = v;
            g->cur = g->cur + 0x10;
        }
    }
done:
    ;
}

struct __attribute__((aligned(16))) Quad_1B2068 {
    s32 a, b, c, d;
};

void func_001B1BF0(void* self);

void func_001B2068(void* self, Quad_1B2068* src)
{
    *(Quad_1B2068*)((u8*)self + 0x30) = *src;
    func_001B1BF0(self);
}

struct Node_1B2790;
struct Node_1B2790 { u8 pad[0xB8]; Node_1B2790* next; };

s32 func_001B26F8(Node_1B2790* node, void* a1, f32 f);

void func_001B2790(C6C* self, void* a1, s32 max, s32* outCount, Node_1B2790** out, f32 f)
{
    ListFrame frame;
    s32 count = 0;
    Node_1B2790* node;
    for (node = (Node_1B2790*)self->list1C00.head; node != 0; node = node->next) {
        if (func_001B26F8(node, a1, f) == 0) {
            continue;
        }
        if (count < max) {
            *out = node;
            out++;
            count++;
        } else {
            break;
        }
    }
    *outCount = count;
}

typedef void (*VFn_1B0120)(void* self, s32 arg);

struct Obj_1B2090 {
    u8 kind_0;
    u8 pad_1[0xB];
    u32 flags_C;
};

s32 func_001B2090(Obj_1B2090** self, u32 bits)
{
    s32 r = 0;
    if (*self != 0) {
        u32 flags = (*self)->flags_C;
        u8* g = *(u8**)D_00261990;
        u32 mask = *(u32*)(g + 0x21C);
        s32 ok = 0;
        if ((flags & 0x10000000) != 0 || (mask & flags) == mask) {
            ok = 1;
        }
        if (ok != 0) {
            if (((bits & 1) != 0 && (*self)->kind_0 == 2) || ((bits & 2) != 0 && (*self)->kind_0 == 3)) {
                r = 1;
            }
        }
    }
    return r;
}

struct Obj_1B2F00 {
    u8 pad0[4];
    u8 countA;
    u8 countB;
    u8 pad6[6];
    u32* ptrC;
    u32* ptr10;
};

void func_00137A60(void* self, s32 size, void* obj);
u32* func_0018D500(s32 bytes);

void func_001B2F00(void* self, Obj_1B2F00* o)
{
    func_00137A60(self, 6, o);
    if (o->countA != 0) {
        o->ptrC = func_0018D500(o->countA * 4);
        for (s32 i = 0; i < o->countA; i++) {
            u16 idx = func_00137BE0(self);
            o->ptrC[i] = (u32)D_00274504 + (idx << 5);
        }
    }
    if (o->countB != 0) {
        o->ptr10 = func_0018D500(o->countB * 4);
        for (s32 i = 0; i < o->countB; i++) {
            u16 idx = func_00137BE0(self);
            if (idx == 0xFFFF) {
                o->ptr10[i] = 0;
            } else {
                o->ptr10[i] = (u32)D_0027450C + idx * 0x18;
            }
        }
    }
}

s32 func_001925F0(void);
s32 func_001AEE50(void* self, void* other);

// Matched by a switch on f558 (cases 1 and 5).

typedef void (*VFn_1B1698)(void* self, s32 arg);

struct Obj_001B2010 {
    u8 pad0[4];
    f32 f4;
    f32 f8;
    u8 pad1[0x40 - 0xC];
    f32 f40;
    f32 f44;
};

f32 func_002054F0(struct Obj_001B2010* o, f32 s);
void func_001B1BF0(struct Obj_001B2010* o);

void func_001B2010(struct Obj_001B2010* o, f32 s) {
    f32 t = func_002054F0(o, s * 0.00872664712f);
    o->f4 = t * o->f40;
    o->f8 = t * o->f44;
    func_001B1BF0(o);
}

struct Obj_1B3488;

extern s32 D_00274518;
extern u8 D_002626D8[];
extern s32 D_002626CC;

void func_001B47C0(void);
void func_00168D78(Obj_1B3488* p);
void func_001692B0(Obj_1B3488* self, u8* arg);
void func_001B3510(Obj_1B3488* self);
void func_00169718(void);
void func_0013B430(Obj_1B3488* mask);

void func_001B3488(Obj_1B3488* self)
{
    func_001B47C0();
    if ((s32)self != D_00274518) {
        func_00168D78((Obj_1B3488*)D_002626D8);
        func_001692B0(self, D_002626D8);
        func_001B3510(self);
        func_00169718();
        func_0013B430(self);
        D_002626CC = 2;
        D_00274518 = (s32)self;
    }
}

struct __attribute__((aligned(16))) Quad_1B28A8 { s32 w[4]; };
struct Dst_1B28A8 { Quad_1B28A8 q0, q1, q2, q3; };

extern u8 D_00248400[];

void func_00188B08(void* a, void* b, Dst_1B28A8* dst);
void func_00182F78(C01* self, void* other);

void func_001B28A8(C6E* self, C01* other)
{
    Dst_1B28A8 a;
    Dst_1B28A8 b;
    T2176* h;
    if (self->parent) {
        func_00188B08((u8*)self->parent + 0x140, (u8*)self->parent + 0x110, &a);
    } else {
        a = *(Dst_1B28A8*)D_00248400;
    }
    if (other) {
        func_00188B08((u8*)other + 0x140, (u8*)other + 0x110, &b);
    } else {
        b = *(Dst_1B28A8*)D_00248400;
    }
    h = self->curve;
    if (h->vt->m04) {
        h->vt->m04(h, &a, &b);
    }
    func_00182F78(self, other);
}

extern s32 D_002744D0;
void func_001BF788(s32 a, s32 n);
void func_00155F90(s32 p);

struct Tgt_1B1710;
void func_001BF788(Tgt_1B1710* t, s32 n);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

extern f32 D_0026185C;

extern f32 D_0026185C;

// NEAR: float regs: case 0 wants t=$f4 zero=$f2 m=$f3; ours t=$f3 zero=$f4 m=$f2 (8 lines differ); delay-slot load of m fixed via local m

extern f32 D_0026185C;

// EXACT (us)

struct Ent_1B3040 {
    s32 type;
    s32 data;
};
struct Elem_1B3040 {
    u8 pad0[4];
    u8 f4;
    u8 pad5[3];
    T21E3_Rec* f8;
    u8 pad0C[8];
};
struct Frame_1B3040 {
    s32 w[4];
};

extern s32 D_002744F8;
extern T21E3_Rec* D_002744FC;
extern s32 D_0027453C;
extern T21E3** D_00274540;
extern s32 D_00274520[];
extern s32 D_00274538;
extern u8 D_002626D8[];

void func_001B2BA8(void* self);
void func_001B2CF8(void* self);
void* func_0018D5C0(s32 bytes);
void func_00137A60(void* self, s32 key, T21E3_Rec* out);
T21E3* func_001B4A10(void* self);
void func_001B2F00(void* self, Elem_1B3040* e);
void func_001B2DF8(void* self);
void func_00168D68(Frame_1B3040* p, s32 a, s32 b);
s32 func_001690C0(s32 mask, Frame_1B3040* arg, s32 f);
void func_001B3510(s32 mask);
void func_0015E5F0(void);
void func_001A9F78(void);
s32 func_00169780(s32 mask);
s32 func_001693A8(s32 mask);

void func_001B3040(void* self)
{
    s32 i;
    s32 j;
    T21E3_Rec* rec;
    T21E3** out;
    Frame_1B3040 f;

    func_001B2BA8(self);
    func_001B2CF8(self);
    D_002744F8 = func_00137BE0(self);
    D_002744FC = (T21E3_Rec*)func_0018D5C0(D_002744F8 * 0x28);
    D_0027453C = func_00137BE0(self);
    D_00274540 = (T21E3**)func_0018D5C0(D_0027453C * 4);
    out = D_00274540;
    for (i = 0; i < D_002744F8; i++) {
        rec = &D_002744FC[i];
        func_00137A60(self, 0x14, rec);
        rec->owner = func_001B4A10(self);
        if (rec->owner) {
            rec->owner->cur.rec = rec;
            *out++ = rec->owner;
        }
        rec->elems = func_0018D5C0(rec->nelem * 0x14);
        for (j = 0; j < rec->nelem; j++) {
            Elem_1B3040* e = (Elem_1B3040*)((u8*)rec->elems + j * 0x14);
            func_001B2F00(self, e);
            e->f8 = rec;
        }
        rec->count = ((Elem_1B3040*)rec->elems)->f4;
        switch (rec->kind) {
        case 0:
            rec->f18 = 3;
            break;
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            rec->f18 = 1;
            break;
        case 4:
            rec->f18 = 4;
            break;
        }
        rec->ents = func_0018D5C0(rec->f18 * 8);
        Ent_1B3040* arr = (Ent_1B3040*)rec->ents;
        Ent_1B3040* e;
        switch (rec->kind) {
        case 1:
        case 6:
        case 7:
        case 8:
        case 10:
            arr[0].type = 8;
            arr[0].data = (s32)func_0018D5C0(rec->count << 7);
            break;
        case 4: {
            s32 n = (rec->flags & 2) ? 3 : 0;
            n += 5;
            e = arr + 1;
            arr[0].type = n;
            arr[0].data = (s32)func_0018D5C0((rec->count * arr[0].type) << 4);
            e->type = 5;
            e->data = (s32)func_0018D5C0((rec->count * e->type) << 4);
            e = arr + 2;
            e->type = 7;
            e->data = (s32)func_0018D5C0((rec->count * e->type) << 4);
            e = arr + 3;
            e->type = 4;
            e->data = (s32)func_0018D5C0(rec->count << 6);
            break;
        }
        case 2:
        case 3:
            arr[0].type = 6;
            arr[0].data = (s32)func_0018D5C0((rec->count * arr[0].type) << 4);
            break;
        case 0:
            e = arr + 1;
            arr[0].type = 8;
            arr[0].data = (s32)func_0018D5C0(rec->count << 7);
            e->type = 8;
            e->data = (s32)func_0018D5C0(rec->count << 7);
            e = arr + 2;
            e->type = 8;
            e->data = (s32)func_0018D5C0(rec->count << 7);
            break;
        case 5:
            arr[0].type = 7;
            arr[0].data = (s32)func_0018D5C0((rec->count * arr[0].type) << 4);
            break;
        case 9:
            arr[0].type = 4;
            arr[0].data = (s32)func_0018D5C0(0x40);
            break;
        }
    }
    func_001B2DF8(self);
    for (s32 k = 0; k < D_0027453C; k++) {
        D_00274540[k]->vt->m01(D_00274540[k]);
    }
    func_00168D68(&f, 0x1E00, 0x4000);
    func_001690C0(0x10000000, &f, 0);
    func_001B3510(0x10000000);
    func_00168D68((Frame_1B3040*)D_002626D8, f.w[1], 0x4000);
    func_0015E5F0();
    func_001A9F78();
    for (s32 m = 0; m < 6; m++) {
        D_00274520[m] = func_00169780((1 << m) | 0x40000000);
    }
    D_00274538 = func_001693A8(0x20000000);
}

struct Quad_1B3510 {
    u32 w[4];
};
struct Ent_1B3510 {
    s32 type;
    Quad_1B3510* data;
};
struct Elem_1B3510;
struct Rec_1B3510 {
    u8 kind;
    u8 f1;
    u8 pad2[6];
    u8 col[4];
    u32 mask;
    s16 f10;
    u8 pad12[2];
    Elem_1B3510* f14;
    s32 f18;
    Ent_1B3510* f1C;
    s32 f20;
    void* f24;
};
struct Glob_1B3510 {
    u8 pad0[0x204];
    u32 f204;
};

#define TEST_1B3510(ate, atst, aref, afail, date, datm, zte, ztst) \
    ((u64)(ate) | ((u64)(atst) << 1) | ((u64)(aref) << 4) | ((u64)(afail) << 12) | ((u64)(date) << 14) | \
     ((u64)(datm) << 15) | ((u64)(zte) << 16) | ((u64)(ztst) << 17))
#define ALPHA_1B3510(a, b, c, d, fix) \
    ((u64)(a) | ((u64)(b) << 2) | ((u64)(c) << 4) | ((u64)(d) << 6) | ((u64)(fix) << 32))

extern s32 D_002744F8;

void func_001611B8(V24A0* b);
void func_001529C8(V24A0* b, s32 n, Quad_1B3510* q);
void func_001612F8(V24A0* b, s32 a, s32 c, s32 d, s32 e, s32 f);
void func_001613C0(V24A0* b, s32 a, s32 c, u64 d);
void func_00161708(V24A0* b, s32 reg, u64 v);
void func_001B29E0(Elem_1B3510* e, s32 j, s32 pass, s32 kind, V24A0* b);
void func_00152D70(V24A0* b);
void func_001528C8(V24A0* b);
void func_00161278(V24A0* b, s32 n);
void func_00161520(V24A0* b, f32 x, f32 y, f32 z);
void func_00161458(V24A0* b, u32 c);
void* func_001B4688(s32 key);

void func_001B3510(s32 mask)
{
    V24A0 buf;
    u8 col[4];
    s32 i;
    s32 j;
    Rec_1B3510* rec;
    Ent_1B3510* ents;
    u64 test;
    u64 sel;

    if (mask == 0) {
        return;
    }
    for (i = 0; i < D_002744F8; i++) {
        rec = &((Rec_1B3510*)D_002744FC)[i];
        if ((rec->mask & mask) != (u32)mask) {
            continue;
        }
        for (j = 0; j < rec->f20; j++) {
            ents = rec->f1C;
            switch (rec->kind) {
            case 1:
            case 6:
            case 7:
            case 8:
            case 10:
                func_001611B8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                func_001612F8(&buf, 0x7C, 0, 3, 0x412, 0);
                func_001613C0(&buf, 0, 1, 0xE);
                if (rec->kind == 10) {
                    func_00161708(&buf, 0x47, 0x53001);
                    func_00161708(&buf, 0x42, 0x11);
                } else if (rec->f1 & 8) {
                    func_00161708(&buf, 0x47, 0x7001B);
                    func_00161708(&buf, 0x42, 0);
                } else if (rec->f1 & 0x20) {
                    test = (rec->f1 & 4) ? 0x13001 : 0x11001;
                    test |= (rec->kind != 1) ? 0x20000 : 0x60000;
                    func_00161708(&buf, 0x47, test);
                    func_00161708(&buf, 0x42, 0);
                } else if (rec->f1 & 0x10) {
                    test = TEST_1B3510(1, (rec->kind == 1) ? 5 : 0, 0x7E, (rec->f1 & 4) ? 3 : 1, 0, 0, 1, (rec->kind == 1) ? 3 : 1);
                    func_00161708(&buf, 0x47, test);
                    sel = (rec->f1 & 1) ? 2 : 0;
                    func_00161708(&buf, 0x42, ALPHA_1B3510(1, sel, 0, 0, 0));
                } else {
                    test = TEST_1B3510(1, (rec->kind == 1) ? 5 : 0, 0x7E, (rec->f1 & 4) ? 3 : 1, 0, 0, 1, (rec->kind == 1) ? 3 : 1);
                    func_00161708(&buf, 0x47, test);
                    sel = (rec->f1 & 1) ? 2 : 1;
                    func_00161708(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                }
                func_00161708(&buf, 0x3D, (*(Glob_1B3510**)D_00261990)->f204);
                func_001B29E0(rec->f14, j, 0, rec->kind, &buf);
                func_00152D70(&buf);
                break;
            case 4:
                func_001611B8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                if (rec->f1 & 2) {
                    func_001612F8(&buf, 0x7C, 0, 3, 0x412, 0);
                    func_001613C0(&buf, 0, 1, 0xE);
                    func_00161708(&buf, 0x47, 0x71001);
                    sel = (rec->f1 & 1) ? 2 : 1;
                    func_00161708(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                    func_00161708(&buf, 0x3D, (*(Glob_1B3510**)D_00261990)->f204);
                    func_001B29E0(rec->f14, j, 0, rec->kind, &buf);
                } else {
                    func_001612F8(&buf, 0x4C, 0, 3, 0x4FF, 0);
                    func_001613C0(&buf, 0, 1, 0xE);
                    func_00161708(&buf, 0x47, 0x71001);
                    func_00161708(&buf, 0x42, 0x6A);
                    func_00161708(&buf, 1, 0x100000020);
                }
                ents++;
                func_00152D70(&buf);
                func_001528C8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                ents++;
                func_001612F8(&buf, 0x4C, 0, 3, 0x4FF, 0);
                func_001613C0(&buf, 0, 1, 0xE);
                func_00161708(&buf, 0x47, 0x71001);
                func_00161708(&buf, 0x42, 0x6A);
                func_00161708(&buf, 1, 0x180002000);
                func_00152D70(&buf);
                func_001528C8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                ents++;
                func_001612F8(&buf, 0x6C, 0, 3, 0x4FF, 0);
                func_001613C0(&buf, 0, 5, 0x12EEE);
                func_00161708(&buf, 0x47, 0x75001);
                sel = (rec->f1 & 1) ? 2 : 1;
                func_00161708(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                func_00161708(&buf, 0x3D, (*(Glob_1B3510**)D_00261990)->f204);
                func_00161520(&buf, 0.0f, 0.0f, 1.0f);
                col[0] = (rec->col[0] + 1) >> 1;
                col[1] = (rec->col[1] + 1) >> 1;
                col[2] = (rec->col[2] + 1) >> 1;
                col[3] = (rec->col[3] + 1) >> 1;
                func_00161458(&buf, *(u32*)col);
                func_00152D70(&buf);
                func_001528C8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                if (rec->f1 & 2) {
                    func_001612F8(&buf, 0x7D, 0, 3, 0x412, 0);
                } else {
                    func_001612F8(&buf, 0x4D, 0, 3, 0x4FF, 0);
                }
                func_001612F8(&buf, 0x6D, 0, 3, 0x4FF, 0);
                if (rec->f1 & 2) {
                    func_001612F8(&buf, 0x5D, 0, 1, 4, 0);
                } else {
                    func_001612F8(&buf, 0x4D, 0, 1, 4, 0);
                }
                func_001612F8(&buf, 0x4D, 0, 1, 4, 0);
                func_00152D70(&buf);
                break;
            case 2:
            case 3:
                func_001611B8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                func_001613C0(&buf, 0, 1, 0xE);
                func_00161708(&buf, 0x47, 0x5F001);
                if (rec->kind == 2) {
                    func_00161708(&buf, 0x42, 0x44);
                } else {
                    func_00161708(&buf, 0x42, 0x49);
                }
                func_001B29E0(rec->f14, j, 0, rec->kind, &buf);
                func_00161278(&buf, 1);
                break;
            case 0: {
                func_001611B8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                func_001612F8(&buf, 0x7C, 0, 4, 0x4F12, 0);
                func_001613C0(&buf, 0, 1, 0xE);
                if (rec->f1 & 8) {
                    func_00161708(&buf, 0x47, 0x70000);
                    func_00161708(&buf, 0x42, 0);
                } else {
                    func_00161708(&buf, 0x47, (rec->f1 & 4) ? 0x737EB : 0x717EB);
                    sel = (rec->f1 & 1) ? 2 : 1;
                    func_00161708(&buf, 0x42, ALPHA_1B3510(0, sel, 0, 1, 0));
                }
                ents++;
                func_00161708(&buf, 0x3D, (*(Glob_1B3510**)D_00261990)->f204);
                func_001B29E0(rec->f14, j, 0, rec->kind, &buf);
                func_00152D70(&buf);
                func_001528C8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                func_001612F8(&buf, 0x7C, 0, 4, 0x41F2, 0);
                func_001613C0(&buf, 0, 1, 0xE);
                func_00161708(&buf, 0x47, 0x53001);
                if (rec->f1 & 8) {
                    func_00161708(&buf, 0x42, 0x8000000068);
                } else {
                    func_00161708(&buf, 0x42, 0x48);
                }
                ents++;
                func_00161708(&buf, 0x3D, 0);
                func_001B29E0(rec->f14, j, 1, rec->kind, &buf);
                func_00152D70(&buf);
                func_001528C8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                func_001612F8(&buf, 0x7C, 0, 4, 0x4F12, 0);
                func_001613C0(&buf, 0, 1, 0xE);
                func_00161708(&buf, 0x47, 0x53001);
                if (rec->f1 & 8) {
                    func_00161708(&buf, 0x42, 0x8000000068);
                } else {
                    func_00161708(&buf, 0x42, 0x48);
                }
                func_00161708(&buf, 0x3D, 0);
                T21E3_Rec* found = (T21E3_Rec*)func_001B4688(rec->f10);
                if (found) {
                    func_001B29E0((Elem_1B3510*)found->elems, j, 0, rec->kind, &buf);
                } else {
                    func_001B29E0(rec->f14, j, 2, rec->kind, &buf);
                }
                func_00152D70(&buf);
                break;
            }
            case 5:
                func_001611B8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                func_001612F8(&buf, 0x24C, 0, 3, 0x412, 0);
                func_001613C0(&buf, 0, 1, 0xE);
                func_00161708(&buf, 0x48, 0x31001);
                func_00161708(&buf, 0x43, 0x44);
                func_001B29E0(rec->f14, j, 0, rec->kind, &buf);
                func_00152D70(&buf);
                break;
            case 9:
                func_001611B8(&buf);
                func_001529C8(&buf, ents->type, ents->data + j * ents->type);
                func_001612F8(&buf, 0x4C, 0, 3, 0x41F, 0);
                func_001613C0(&buf, 0, 1, 0xE);
                func_00161708(&buf, 0x47, 0x51001);
                func_00161708(&buf, 0x42, 0x6A);
                func_00152D70(&buf);
                break;
            }
        }
    }
}

struct Ctx_1B2DF8;

extern u8 D_0024A220[];
void* func_001FD8A8(s32 size);

struct Ent_1B2DF8 {
    u8 pad00[0x4C];
    void* p4c;
    u8 pad50[0x30];
    s32 v80;
    u8 pad84[0x04];

    Ent_1B2DF8() { p4c = D_0024A220; }
    void* operator new[](__SIZE_TYPE__ size) { return func_001FD8A8(size); }
};

extern s32 D_00262260;
extern Ent_1B2DF8* D_00262264;
extern s32 D_0026227C;

s32 func_00137BE0(Ctx_1B2DF8* src);
void func_0015D8A8(Ent_1B2DF8* e, Ctx_1B2DF8* self);
s32 func_0015C1C0(s32 n);

void func_001B2DF8(Ctx_1B2DF8* self)
{
    D_00262260 = func_00137BE0(self);
    D_00262264 = new Ent_1B2DF8[D_00262260];
    for (s32 i = 0; i < D_00262260; i++) {
        func_0015D8A8(&D_00262264[i], self);
        D_00262264[i].v80 = 1 << i;
    }
    D_0026227C = func_0015C1C0(0);
}

extern f32 D_0026185C;
void func_001B46E0(s32 a, s32 frame);

struct Snd_1B1070;
enum Kind_1B1070 { KIND_1B1070_1B = 0x1B };

void func_001BF788(Snd_1B1070* p, s32 n);
void func_001BFCD8(Kind_1B1070 a0, Snd_1B1070** a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

