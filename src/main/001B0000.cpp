// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1B04A0 {
    u8 pad_0[0x5D8];
    s32 f5D8;
};

void func_001AECB0(Obj_1B04A0* o);

void func_001B04A0(Obj_1B04A0* o)
{
    func_001AECB0(o);
    o->f5D8 = -1;
}

typedef void (*VFn_1B0F70)(void* self, s32 arg);

struct Obj_1B0F70 {
    VFn_1B0F70* vtbl;
    u8 pad_4[0x554 - 4];
    s32 f554;
    s32 f558;
};

void func_001B0F70(Obj_1B0F70* o)
{
    if (o->f554 == 0) {
        o->f554 = 1;
        if (o->f558 != 8) {
            o->vtbl[0x144 / 4](o, 3);
        }
    }
}

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

struct Hdr_1B2B50 { u8 pad0[4]; u16 count; u8 pad6[2]; u32 off8; u32 size; };
extern u32 D_00275718;
void func_00137A60(void* a, s32 b, void* c);

void func_001B2B50(void* a0, Hdr_1B2B50* a1)
{
    func_00137A60(a0, 12, a1);
    a1->off8 = D_00275718 + a1->off8;
    a1->size = (u32)((a1->count << 2) + 15) >> 4;
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

s32 func_00137BE0(void* self);
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

struct Blk_1B2CA8 {
    u8 pad0[0xC];
    u32 bytes;
    s32 offset;
    s32 blocks;
};

void func_001B2CA8(void* self, Blk_1B2CA8* obj)
{
    func_00137A60(self, 0x14, obj);
    s32 base = D_00275718;
    u32 bytes = obj->bytes;
    s32 off = obj->offset;
    obj->blocks = (bytes + 0xF) >> 4;
    obj->offset = base + off;
}

struct Rec_1B2CF8 {
    u8 pad0[4];
    u32 flags;
    u8 pad8[0x18];
};

extern s32 D_00274500;
extern Rec_1B2CF8* D_00274504;
extern s32 D_00274510;

s32 func_00137BE0(void* self);
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

struct Vtbl_1B11A0 {
    u8 pad0[0x144];
    VFn_1B11A0 fn144;
};

struct Item_1B11A0 {
    u8 pad0[0x8];
    s32 f08;
    u8 pad1[0x14 - 0xC];
    s32 f14;
};

struct Obj_1B11A0 {
    Vtbl_1B11A0* vt;
    u8 pad0[0x278];
    s32 f27C;
    Item_1B11A0** f280;
    u8 pad1[0x560 - 0x284];
    s32 f560;
    u8 pad2[0x610 - 0x564];
    Item_1B11A0* f610;
};

void func_001B11A0(Obj_1B11A0* self)
{
    func_00124A48(self);
    for (s32 i = 0; i < self->f27C; i++) {
        Item_1B11A0* it = self->f280[i];
        if (it->f08 == 1 && it->f14 != 0) {
            self->f610 = it;
            break;
        }
    }
    self->vt->fn144(self, self->f560);
}

typedef void (*VFn_1B15D0)(void* self, s32 arg);

struct Vtbl_1B15D0 {
    u8 pad0[0x144];
    VFn_1B15D0 fn144;
};

struct Obj_1B15D0 {
    Vtbl_1B15D0* vt;
    u8 pad0[0x554 - 0x4];
    s32 f554;
};

void func_001B15D0(Obj_1B15D0* self, s32 mode)
{
    self->f554 = mode;
    self->vt->fn144(self, mode == 0 ? 1 : 5);
}

extern f32 D_0026185C;

typedef void (*VFn_1B1608)(void* self, s32 arg);

struct Vtbl_1B1608 {
    u8 pad0[0x144];
    VFn_1B1608 fn144;
};

struct Rec_1B1608 {
    u8 pad0[0x550];
    s32 f550;
    f32 f554;
};

struct Obj_1B1608 {
    Vtbl_1B1608* vt;
    u8 pad0[0x550 - 0x4];
    Rec_1B1608* f550;
    s32 f554;
    s32 f558;
    u8 pad1[0x5C0 - 0x55C];
    s32 f5C0;
};

void func_001B1608(Obj_1B1608* self)
{
    if (self->f558 != 8) {
        self->vt->fn144(self, self->f554 == 0 ? 3 : 7);
    }
    Rec_1B1608* r = self->f550;
    if (r != 0) {
        if (r->f550 == 1) {
            if (__builtin_fabsf(D_0026185C - r->f554) < 0.2f) {
                self->f5C0 = r->f550;
            }
        }
    }
}

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

struct Obj_1B00E8 { VFn_1B00E8* vtbl; u8 pad_4[0x554 - 4]; s32 f554; s32 f558; };

void func_001B00E8(Obj_1B00E8* self, s32 flag)
{
    s32 m = 5;
    self->f554 = flag;
    if (!flag) {
        m = 1;
    }
    self->vtbl[0x144 / 4](self, m);
}

struct Obj_1B1158 {
    u8 pad_0[0x5D0];
    s32 f5D0;
    s32 f5D4;
    u8 pad_5D8[0x5E0 - 0x5D8];
    s32 f5E0;
    s32 f5E4;
    u8 pad_5E8[0x5F0 - 0x5E8];
    s32 f5F0;
    s32 f5F4;
    u8 pad_5F8[0x600 - 0x5F8];
    s32 f600;
};

void func_001AECB0(void* self);

void func_001B1158(Obj_1B1158* self)
{
    func_001AECB0(self);
    self->f5D0 = -1;
    self->f5D4 = -1;
    self->f5E0 = -1;
    self->f5E4 = -1;
    self->f5F0 = -1;
    self->f5F4 = -1;
    self->f600 = -1;
}

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
