// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_0062C568[];
void func_001B5F28(void* list, void* item);

void func_0011C720(void* item)
{
    func_001B5F28(D_0062C568, item);
}

// The array D_0025C360 is addressed as one symbol; indexing its address keeps retail's lui/addu form.
extern s32 D_0025C380;
extern s32 D_0025C360;
s32 func_0011CE30(void);

void func_0011DDD8()
{
    s32* p = (s32*)((&D_0025C360)[D_0025C380]);
    p[0]++;
    func_0011CE30();
}

extern s32 D_0025C34C;
extern s32 D_0025C388;
s32 func_0011CE30(void);
s32 func_0011E1F8(s32 flag);
s32 func_0011D968(s32 id, s32 size, void* data);

s32 func_0011DF58(s32 a, s32 b, s32 c, s32 d)
{
    s32 buf[4];
    s32 r;
    if (D_0025C34C == 1)
        return 0;
    if (D_0025C388) {
        do {
        } while (func_0011CE30());
    }
    func_0011E1F8(0);
    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    buf[3] = d;
    r = func_0011D968(0x2A, 0x10, buf);
    D_0025C34C = r;
    return r;
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011E010()
{
    func_0011DB00(0x34, 0, 0, 0, 0);
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011E0B0(s32 a0)
{
    s32 buf = a0;
    func_0011DB00(0x2E, 4, &buf, 0, 0);
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011E0E0(s32 a0, s32 a1, s32 a2)
{
    s32 buf = a0;
    func_0011DB00(0x4F, 4, &buf, a1, a2);
}

s32 func_0011D968(s32 id, s32 size, void* data);

void func_0011E110(s32 a0)
{
    s32 buf = a0;
    func_0011D968(0x36, 4, &buf);
}

extern s32 D_0025C34C;
s32 func_00203E28(void);
s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

s32 func_0011E2A0()
{
    if (D_0025C34C == 0)
        return func_00203E28();
    func_0011DB00(0x37, 0, 0, 0, 0);
    return 1;
}

s32 func_0011C0A8(s32 a, s32 b);

s32 func_0011C0E8(void)
{
    return func_0011C0A8(1, 0xFFFF);
}

struct Stride_11C288 { s32 stride; s32 pad4; s32 base; };

s32 func_0011C288(Stride_11C288* self, s32 index)
{
    return self->base + index * self->stride;
}

struct Cell_11C3C8 { s32 pad0; s32 value; };

Cell_11C3C8* func_0011C3C0(void);

s32 func_0011C3C8(void)
{
    return func_0011C3C0()->value == 0;
}

extern u32 D_0062C55C;
extern u8* D_0027B300[];

s32 func_0011C580(u32 addr)
{
    u8* p = D_0027B300[0] + ((addr - D_0062C55C) >> 4);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

extern u32 D_0062C57C;
extern u8* D_0027B300[];

s32 func_0011C7C0(u32 addr)
{
    u8* p = D_0027B300[2] + ((addr - D_0062C57C) >> 4);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

s32 func_0011DB00(s32 a, s32 b, void* c, s32 d, s32 e);

void func_0011D450(s32 arg)
{
    s32 local = arg;
    func_0011DB00(6, 4, &local, 0, 0);
}

s32 func_0011DB00(s32 kind, s32 id, void* args, s32 a3, s32 a4);

struct Args_11D558
{
    void* a0;
    s32 a1;
    s32 a2;
};

void func_0011D558(void* a0, s32 a1, s32 a2)
{
    Args_11D558 args;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    func_0011DB00(0x4E, 0xC, &args, 0, 0);
}

s32 func_0011DB00(s32 kind, s32 id, void* args, s32 a3, s32 a4);

struct Args_11D670
{
    void* a0;
};

void func_0011D670(void* a0)
{
    Args_11D670 args;
    args.a0 = a0;
    func_0011DB00(0x14, 4, &args, 0, 0);
}

s32 func_0011DB00(s32 kind, s32 id, void* args, s32 a3, s32 a4);

struct Args_11D798
{
    void* a0;
    s32 a1;
    s32 a2;
};

void func_0011D798(void* a0, s32 a1, s32 a2)
{
    Args_11D798 args;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    func_0011DB00(0x1B, 0xC, &args, 0, 0);
}

s32 func_0011DB00(s32 kind, s32 id, void* args, s32 a3, s32 a4);

struct Args_11D8B0
{
    void* a0;
    s32 a1;
    s32 a2;
};

void func_0011D8B0(void* a0, s32 a1, s32 a2)
{
    Args_11D8B0 args;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    func_0011DB00(0x29, 0xC, &args, 0, 0);
}

void func_0011D968(s32 kind, s32 a1, s32 a2);

void func_0011E4F8()
{
    func_0011D968(0x40, 0, 0);
}

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr)
{
    s32 hi = n;
    s32 lo = 1;

    if (n != 1)
    {
        do
        {
            s32 mid = (hi + lo) / 2;
            f32 v = *(f32*)(base + stride * mid);
            if (key < v)
            {
                hi = mid;
            }
            else
            {
                lo = mid + 1;
            }
        } while (lo != hi);
    }

    if (lo >= n)
    {
        lo = n - 1;
    }
    s32 exact = flags & 1;
    lo = lo - 1;
    u8* p = base + stride * lo;

    if (exact)
    {
        if (*(f32*)p == key)
        {
            p = p - stride;
            if (p < base)
            {
                p = p + (n - 1) * stride;
                key = *(f32*)(p + stride);
            }
        }
    }

    if (outDiff != 0)
    {
        *outDiff = key - *(f32*)p;
    }
    if (outDelta != 0)
    {
        *outDelta = *(f32*)(p + stride) - *(f32*)p;
    }
    *outPtr = p;
}

void func_0011EF88()
{
}

void* func_0018D658(s32 size);

struct Elem_11F180
{
    f32 value;
    u8 pad[0x14];
};

struct Source_11F180
{
    u8 pad[8];
    s32 count;
    Elem_11F180* elems;
};

void func_0011F180(Source_11F180* src, s32* outCount, f32** outValues)
{
    *outCount = src->count;
    if (outValues != 0)
    {
        *outValues = (f32*)func_0018D658(*outCount << 2);
        for (s32 i = 0; i < *outCount; i++)
        {
            (*outValues)[i] = src->elems[i].value;
        }
    }
}

struct Item_11F620 { f32 x; f32 y; };
struct Set_11F620 { u8 pad0[8]; s32 count; Item_11F620* items; };

void* func_0018D658(s32 size);

void func_0011F620(Set_11F620* self, s32* count, f32** out)
{
    s32 n = self->count;
    *count = n;
    if (out != 0) {
        *out = (f32*)func_0018D658(n * 4);
        for (s32 i = 0; i < *count; i++) {
            (*out)[i] = self->items[i].x;
        }
    }
}

void func_0011F850(void* a, void* b);

void func_0011FDB8(u8* self, void* p)
{
    func_0011F850(self + 0x20, p);
}

void func_00109488(void);

void func_0011E560(void)
{
    func_00109488();
}

extern u8 D_002505D8[];

void func_0011E680(void* self, void* slot, void* obj);
s32 func_00137D10(void* p);

void func_0011EC40(void* self, void* obj)
{
    s32 r;
    while ((r = func_00137D10(obj)) >= 0) {
        func_0011E680(self, D_002505D8 + (r << 5), obj);
    }
}

s32 func_0011ECA0(s32 value)
{
    s32 r = value - 12;
    return ((u32)30 < (u32)r) ? -1 : r;
}

void func_0011EF40(void)
{
}

void func_0011EF48(void* unused, s32* a, s32* b)
{
    *a = 0;
    if (b != 0) {
        *b = 0;
    }
}

void func_0011EF60(void)
{
}

extern u8 D_00259F38[];
extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011A6B8(void* p);
void func_0011C1D0(void* p);
void func_0011CBB0(void);

void func_0011C040(void)
{
    func_0011C1D0(D_0025C250);
    func_0011C1D0(D_0025C270);
    func_0011C1D0(D_0025C290);
    func_0011C1D0(D_0025C2B0);
    func_0011CBB0();
    func_0011C1D0(D_0025C2D0);
    func_0011A6B8(D_00259F38);
}

extern u8 D_0062C568[];
extern u8 D_00259F38[];

void* func_001B5EA0(void* pool);
void* func_001B5EE0(void* pool);
void func_001F5C0C(void* p, s32 zero, u32 count);
void func_0011AB58(void* p);

void* func_0011C618(void)
{
    void* s0 = func_001B5EA0(D_0062C568);
    if (s0 != 0) {
        func_001F5C0C(s0, 0, *(u32*)D_0062C568);
    } else {
        func_0011AB58(D_00259F38);
        s0 = func_001B5EE0(D_0062C568);
    }
    return s0;
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011D6A8(s32 a0)
{
    s32 buf = a0;
    func_0011DB00(0x16, 4, &buf, 0, 0);
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011D6D8(s32 a0)
{
    s32 buf = a0;
    func_0011DB00(0x17, 4, &buf, 0, 0);
}

s32 func_0011D968(s32 id, s32 size, void* data);

void func_0011D708(s32 a0)
{
    s32 buf = a0;
    func_0011D968(0x19, 4, &buf);
}

s32 func_0011D968(s32 id, s32 flags, void* args);

void func_0011E428(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    s32 args[5];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    func_0011D968(0x3B, 0x14, args);
}

s32 func_0011D968(s32 id, s32 flags, void* args);

void func_0011E460(void)
{
    func_0011D968(0x3D, 0, 0);
}

s32 func_0011D968(s32 id, s32 flags, void* args);

void func_0011E498(void)
{
    func_0011D968(0x3C, 0, 0);
}

struct Entry_11FB98 { f32 value; u8 rest[0x3C]; };

void* func_0018D658(s32 size);

void func_0011FB98(s32 count, Entry_11FB98* src, s32* outCount, f32** outArr)
{
    *outCount = count;
    if (outArr) {
        *outArr = (f32*)func_0018D658(count * 4);
        s32 i = 0;
        if (*outCount > 0) {
            Entry_11FB98* p = src;
            do {
                (*outArr)[i] = p->value;
                p++;
                i++;
            } while (i < *outCount);
        }
    }
}

typedef void (*Hook_11FC20)(void* self, s32 a, s32 b);
struct Owner_11FC20 { Hook_11FC20* vtbl; };

void func_0011F6B0(u8* a, Owner_11FC20* b, s32 c, u8* d, s32 e, s32 f, f32 g, f32 h);

void func_0011FC20(u8* self, Owner_11FC20* other, s32 c, s32 e, s32 f, f32 p12, f32 p13)
{
    func_0011F6B0(self + 0x20, other, c, self + 0x10, e, f, p12, p13);
    if (other && other->vtbl[44])
        other->vtbl[44](other, e, f);
}

typedef void (*Hook_11FDD8)(void* self, s32 a, s32 b);
struct Owner_11FDD8 { Hook_11FDD8* vtbl; };
struct Self_11FDD8 { u8 pad0[0xC]; s32 f0c; s32 f10; };

void func_0011F9F8(s32 a, s32 b, s32 c, s32 d, s32 e, f32 g, f32 h);

void func_0011FDD8(Self_11FDD8* self, Owner_11FDD8* other, s32 a2, s32 a3, s32 a4, f32 p12, f32 p13)
{
    func_0011F9F8(self->f0c, self->f10, a2, a3, a4, p12, p13);
    if (other && other->vtbl[44])
        other->vtbl[44](other, a3, a4);
}

struct Self_11FED8 { u8 pad0[0xC]; s32 count; u8* records; };

void func_0011FB98(s32 count, u8* src, s32* outCount, f32** outArr);

void func_0011FED8(Self_11FED8* self, s32* outCount, f32** outArr)
{
    func_0011FB98(self->count, self->records, outCount, outArr);
}

extern s32 D_0025C268;
extern s32 D_0025C288;
extern s32 D_0025C2A8;
extern s32 D_0025C2C8;
extern s32 D_0025C2E8;

void func_0011C0A8(s32 a, u32 b)
{
    if (b == 0xFFFF && a != 0) {
        D_0025C268 = 0;
        D_0025C288 = 0;
        D_0025C2A8 = 0;
        D_0025C2C8 = 0;
        D_0025C2E8 = 0;
    }
}

struct Node_11C418 { s32 f0; s32 f4; s32 f8; s32 fC; };

void func_0011B258(void* dst, void* src);
Node_11C418* func_0011C498(void);
void func_0011C418(Node_11C418* a, Node_11C418* b, s32 c);

void func_0011C418(Node_11C418* a, Node_11C418* b, s32 c)
{
    b->f0 = a->f0;
    func_0011B258(&a->f4, &b->f4);
    if (a->fC != 0) {
        Node_11C418* n = func_0011C498();
        func_0011C418((Node_11C418*)a->fC, n, c);
        b->fC = (s32)n;
    }
}

extern u8 D_0025C290[];
Node_11C418* func_0011C240(void* pool);
void func_001F5C0C(void* dst, s32 value, u32 size);
void func_0011B008(void* p);

Node_11C418* func_0011C498(void)
{
    Node_11C418* n = func_0011C240(D_0025C290);
    func_001F5C0C(n, 0, 16);
    func_0011B008(&n->f4);
    n->f4 = -1;
    return n;
}

void func_0011B060(void* p, s32 mode);

void func_0011C4E8(void* a)
{
    func_0011B060((u8*)a + 4, 2);
}

extern s32 D_0062C558;
extern u8 D_00259F38[];
void* func_001B5EA0(void* pool);
void* func_001B5EE0(void* pool);
void func_0011AB58(void* arg);
void func_001F5C0C(void* dst, s32 value, u32 size);

void* func_0011C508(void)
{
    void* p = func_001B5EA0(&D_0062C558);
    if (p != 0) {
        func_001F5C0C(p, 0, D_0062C558);
    } else {
        func_0011AB58(D_00259F38);
        p = func_001B5EE0(&D_0062C558);
    }
    return p;
}

void func_0011DB00(s32 a, s32 b, void* args, void* c, void* d);

void func_0011D520(s32 x, s32 y)
{
    s32 args[2];
    args[0] = x;
    args[1] = y;
    func_0011DB00(0xD, 8, args, 0, 0);
}

s32 func_0011D968(s32 a, s32 b, void* args);

void func_0011D598(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 args[6];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    args[5] = a5;
    func_0011D968(0x11, 0x18, args);
}

struct Words_11D8F0 { s32 a; s32 b; };

s32 func_0011D968(s32 kind, s32 count, void* words);

void func_0011D8F0(s32 a, s32 b)
{
    Words_11D8F0 w;
    w.a = a;
    w.b = b;
    func_0011D968(0x28, 8, &w);
}

struct Word_11D928 { s32 a; };

s32 func_0011DB00(s32 kind, s32 count, void* words, s32 x, s32 y);

void func_0011D928(s32 a)
{
    Word_11D928 w;
    w.a = a;
    func_0011DB00(0x27, 4, &w, 0, 0);
}

void func_0011EFB0(s32 unused, s32* a, s32* b)
{
    *a = 0;
    if (b != 0)
        *b = 0;
}

struct Sample_11EFC8 { f32 a; f32 b; s32 c; f32 d; s32 e; f32 f; };
struct Table_11EFC8 { s32 pad[2]; s32 count; Sample_11EFC8* items; };

s32 func_00137BE0(void* src);
s32 func_00137D10(void* src);
f32 func_00137DF8(void* src);
s32 func_00137CC0(void* src);
void* func_0018D500(s32 size);

void func_0011EFC8(Table_11EFC8* self, void* src)
{
    self->count = func_00137BE0(src);
    self->items = (Sample_11EFC8*)func_0018D500(0x18 * self->count);
    for (s32 i = 0; i < self->count; i++) {
        Sample_11EFC8* e = self->items + i;
        e->a = (f32)func_00137D10(src) * 0.016666668f;
        e->b = func_00137DF8(src);
        e->c = func_00137CC0(src);
        e->e = func_00137CC0(src);
        e->d = func_00137DF8(src);
        e->f = func_00137DF8(src);
    }
}

struct Elem_11F210 { f32 a; f32 b; s32 c; f32 d; f32 e; s32 f; f32 g; f32 h; };
struct Table_11F210 { s32 pad[2]; s32 count; Elem_11F210* items; };

s32 func_00137BE0(void* src);
s32 func_00137D10(void* src);
f32 func_00137DF8(void* src);
s32 func_00137CC0(void* src);
void* func_0018D500(s32 size);

void func_0011F210(Table_11F210* self, void* src)
{
    self->count = func_00137BE0(src);
    self->items = (Elem_11F210*)func_0018D500(0x20 * self->count);
    for (s32 i = 0; i < self->count; i++) {
        Elem_11F210* e = self->items + i;
        e->a = (f32)func_00137D10(src) * 0.016666668f;
        e->b = func_00137DF8(src);
        e->c = func_00137CC0(src);
        e->f = func_00137CC0(src);
        e->d = func_00137DF8(src);
        f32 t = func_00137DF8(src);
        e->e = e->b - t;
        e->g = func_00137DF8(src);
        f32 u = func_00137DF8(src);
        e->h = e->b + u;
    }
}

s32 func_0011C0A8(void* p, s32 mask);

void func_0011C108(void)
{
    (void)func_0011C0A8(0, 0xFFFF);
}

struct Pool_11C128 {
    s32 slots;
    s32 size;
    void* mem;
    void* head;
    s32 live;
    s32 high;
};

void* func_0018D500(s32 bytes);
void* func_0011C288(Pool_11C128* p, s32 index);

void func_0011C128(Pool_11C128* p, s32 count, s32 size)
{
    p->slots = count + 8;
    p->size = size;
    p->mem = func_0018D500((count + 8) * size);
    void* node = func_0011C288(p, 0);
    p->head = node;
    s32 i = 1;
    if (i < size) {
        void* prev;
        do {
            prev = node;
            node = func_0011C288(p, i);
            i++;
            *(void**)prev = node;
        } while (i < size);
    }
    *(void**)node = 0;
    p->live = 0;
    p->high = 0;
}

extern u8* D_0027B300[];
void func_001B5F28(void* list, void* item);

void func_0011C5B0(u32 addr)
{
    u8* pool = (u8*)&D_0062C558;
    u8* p = D_0027B300[0] + ((addr - *(u32*)(pool + 4)) >> 4);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        func_001B5F28(pool, (void*)addr);
    }
}

extern u8 D_0062C578[];
extern u8 D_00259F38[];
void* func_001B5EA0(void* pool);
void* func_001B5EE0(void* pool);
void func_001F5C0C(void* p, s32 zero, u32 count);
void func_0011AB58(void* p);

void* func_0011C748(void)
{
    void* s0 = func_001B5EA0(D_0062C578);
    if (s0 != 0) {
        func_001F5C0C(s0, 0, *(u32*)D_0062C578);
    } else {
        func_0011AB58(D_00259F38);
        s0 = func_001B5EE0(D_0062C578);
    }
    return s0;
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011D600(s32 value)
{
    s32 buf = value;
    func_0011DB00(0x15, 4, &buf, 0, 0);
}

struct Self_11F3E8 { u8 pad0[8]; s32 count; u8* items; };
struct Item_11F3E8 { f32 v; u8 pad4[0x1C]; };
void* func_0018D658(s32 size);

void func_0011F3E8(Self_11F3E8* self, s32* outCount, f32** outArr)
{
    s32 n = self->count;
    *outCount = n;
    if (outArr) {
        s32 i;
        *outArr = (f32*)func_0018D658(n * 4);
        i = 0;
        if (*outCount > 0) {
            do {
                (*outArr)[i] = ((Item_11F3E8*)self->items)[i].v;
                i++;
            } while (i < *outCount);
        }
    }
}

struct Entry_11C3B8 { u8 pad[8]; };

Entry_11C3B8* func_0011C3B8(u8* base)
{
    return (Entry_11C3B8*)(base + 8);
}

struct Entry_11C3C0 { u8 pad[8]; };

Entry_11C3C0* func_0011C3C0(u8* base)
{
    return (Entry_11C3C0*)(base - 8);
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011D420(void)
{
    func_0011DB00(0x8, 0, 0, 0, 0);
}

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011D480(s32 a0, s32 a1)
{
    s32 buf[2];
    buf[0] = a0;
    buf[1] = a1;
    func_0011DB00(0x9, 0x8, buf, 0, 0);
}

s32 func_0011D968(s32 kind, s32 count, void* words);

struct Words_11D7D8 { s32 a; s32 b; };

s32 func_0011D7D8(s32 a, s32 b)
{
    Words_11D7D8 w;
    w.a = a;
    w.b = b;
    return func_0011D968(0x1C, 8, &w);
}

s32 func_0011D968(s32 id, s32 flags, void* args);

void func_0011E4C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    s32 args[5];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    func_0011D968(0x3E, 0x14, args);
}

struct Object_11F798 { void** vtbl; };
typedef void (*Method_11F798)(Object_11F798* self, void* src);

s32 func_00137B90(void* src);
void func_00137E70(void* src, void* dst);
void* func_00121160(s32 index);

void func_0011F798(Object_11F798** out, void* dst, void* src)
{
    s32 mask = func_00137B90(src);
    Object_11F798** slot = out;
    func_00137E70(src, dst);
    s32 i = 2;
    do {
        s32 bit = mask & 1;
        mask >>= 1;
        if (bit) {
            Object_11F798* o = (Object_11F798*)func_00121160(func_00137B90(src));
            Method_11F798 fn = (Method_11F798)o->vtbl[1];
            if (fn)
                fn(o, src);
            *slot = o;
        }
        slot++;
        i--;
    } while (i >= 0);
}

struct Scratch_11F9F8 { f32 diff; f32 delta; u8* ptr; };

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);
void func_00130540(u8* a, u8* b, u8* c, u8* d, f32 f12, f32 f13, f32 f14, s32 a4, s32 a5, s32 a6);

void func_0011F9F8(s32 count, s32 base, s32 flags, s32 d, s32 e, f32 key, f32 scale)
{
    Scratch_11F9F8 s;
    func_0011EE70(key, flags, 0x40, count, (u8*)base, &s.diff, &s.delta, &s.ptr);
    u8* p = s.ptr;
    func_00130540(p + 0x10, p + 0x30, p + 0x50, p + 0x60, s.delta, s.diff, scale, d, e, 0);
}

void func_0011C1D0(void* p)
{
}

struct Link_11C1D8 { struct Link_11C1D8* next; };
struct Pool_11C1D8 { u8 pad0[0xC]; Link_11C1D8* free; Link_11C1D8* used; };

extern u8 D_00259F38[];
void func_0011AB58(void* p);
void* func_0011C3B8(void* base);

void* func_0011C1D8(Pool_11C1D8* self)
{
    if (self->free == 0) {
        func_0011AB58(D_00259F38);
    }
    Link_11C1D8* n = self->free;
    if (n != 0) {
        self->free = n->next;
        n->next = self->used;
        self->used = n;
        return func_0011C3B8(n);
    }
    return 0;
}

struct Link_11C3C0 { s32 pad0; s32 value; };

void func_0011C3F0(u8* base)
{
    ((Link_11C3C0*)func_0011C3C0(base))->value = 1;
}

void func_0011CBB0(void)
{
}

s32 func_0011D968(s32 id, s32 size, void* data);

void func_0011D4B8(s32 arg)
{
    s32 local = arg;
    func_0011D968(10, 4, &local);
}

s32 func_0011DB00(s32 kind, s32 id, void* args, s32 a3, s32 a4);

s32 func_0011D4E0(s32 arg)
{
    s32 local = arg;
    return func_0011DB00(11, 4, &local, 0, 0);
}

void func_0011DB00(s32 a, s32 b, void* args, void* c, void* d);

void func_0011D810(s32 x, s32 y)
{
    s32 args[2];
    args[0] = x;
    args[1] = y;
    func_0011DB00(0x1E, 8, args, 0, 0);
}

void func_0011EF68(void)
{
}

struct Word_11EF70 { s32 value; };

void func_0011EF70(void* context, Word_11EF70* first, Word_11EF70* second)
{
    first->value = 0;
    if (second != 0) {
        second->value = 0;
    }
}

struct Item_11FA88 { f32 k; u8 pad0[0xC]; u8 v0[0x10]; u8 v1[0x10]; u8 v2[0x10]; };

s32 func_00137BE0(void* src);
s32 func_00137D10(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);

void func_0011FA88(s32* outCount, void** outItems, void* src)
{
    s32 count = func_00137BE0(src);
    Item_11FA88* items = (Item_11FA88*)func_0018D500(count << 6);
    if (count > 0) {
        u8* p2 = items->v2;
        u8* p1 = items->v1;
        u8* p0 = items->v0;
        Item_11FA88* it = items;
        s32 left = count;
        do {
            left--;
            it->k = (f32)func_00137D10(src) * 0.016666668f;
            func_00137E70(src, p0);
            p0 += 0x40;
            func_00137E70(src, p1);
            p1 += 0x40;
            func_00137E70(src, p2);
            p2 += 0x40;
            it++;
        } while (left != 0);
    }
    *outCount = count;
    *outItems = items;
}

struct Obj_11FF08;
typedef void (*Method_11FF08)(Obj_11FF08* self, void* a, void* b);
struct Obj_11FF08 { Method_11FF08* vtbl; };
struct Scratch_11FF08 { s32 a[4]; s32 b[4]; };

void func_0011F6B0(u8* a, void* b, s32 c, u8* d, void* e, void* f);
void func_00188A20(void* a, void* b);
void func_001EDE38(void* a, void* b, void* c);

void func_0011FF08(u8* self, Obj_11FF08* other, s32 c, void* p3, void* p4)
{
    Scratch_11FF08 tmp;
    func_0011F6B0(self + 0x20, other, c, self + 0x10, p3 ? (void*)&tmp : 0, p4 ? (void*)tmp.b : 0);
    if (p3)
        func_00188A20(&tmp, p3);
    if (p4)
        func_001EDE38(&tmp, tmp.b, p4);
    if (other)
        other->vtbl[45](other, p3, p4);
}

// Newly matched US functions from the small-function wave.
extern void* func_0011C1D8(void*);
extern void* func_0011F6B0(void*, u32, u32, void*, u32, u32);
struct Node_0011C2A0 {
    Node_0011C2A0* next;
    s32 state;
};
struct State_0011C2B0 {
    u8 pad0[0x10];
    Node_0011C2A0* current;
};

Node_11C418* func_0011C240(void* self)
{
    Node_11C418* result = (Node_11C418*)func_0011C1D8(self);
    func_001F5C0C(result, 0, *(s32*)self - 8);
    return result;
}

void func_0011C2A0(State_0011C2B0* self)
{
    *(Node_0011C2A0**)((u8*)self + 0x14) = self->current;
}

void func_0011C2B0(State_0011C2B0* self)
{
    Node_0011C2A0* node = self->current;
    if (node == 0) return;
    do {
        node->state = 0;
        node = node->next;
    } while (node != 0);
}

void func_0011D640(s32 value)
{
    s32 local = value;
    func_0011DB00(0x13, 4, &local, 0, 0);
}

void func_0011D730(s32 value, s32 a1, s32 a2)
{
    s32 local = value;
    func_0011DB00(0x19, 4, &local, a1, a2);
}

void func_0011D760(s32 a0, s32 a1)
{
    s32 local[2];
    local[0] = a0;
    local[1] = a1;
    func_0011D968(0x1A, 8, local);
}

void func_0011D860(s32 a0, s32 a1, s32 a2, s32 a3)
{
    s32 local[4];
    local[0] = a0;
    local[1] = a1;
    local[2] = a2;
    local[3] = a3;
    func_0011DB00(0x22, 16, local, 0, 0);
}

void func_0011E328(s32 a0, s32 a1)
{
    s32 local[2];
    local[0] = a0;
    local[1] = a1;
    func_0011DB00(0xE, 8, local, 0, 0);
}

void func_0011E360(s32 a0, s32 a1, s32 a2)
{
    s32 local[3];
    local[0] = a0;
    local[1] = a1;
    local[2] = a2;
    func_0011DB00(0xF, 12, local, 0, 0);
}

void func_0011E3A0(s32 a0, s32 a1)
{
    s32 local[2];
    local[0] = a0;
    local[1] = a1;
    func_0011DB00(0x51, 8, local, 0, 0);
}

void func_0011EFA8()
{
}

void* func_0011FFA8(void* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    return func_0011F6B0((u8*)self + 0x20, a1, a2, (u8*)self + 0x10, a3, a4);
}

extern u32 D_0062C56C;
s32 func_0011C690(u32 addr)
{
    u8* p = D_0027B300[1] + ((addr - D_0062C56C) >> 6);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

extern u32 D_0062C58C;
s32 func_0011C8D0(u32 addr)
{
    u8* p = D_0027B300[3] + ((addr - D_0062C58C) >> 3);
    s32 v = *p;
    v++;
    *p = v;
    return v;
}

extern s32* D_0025C340;
extern s32 D_0025C344;
void func_0011D110(s32* ptr, s32 count)
{
    D_0025C344 = count;
    D_0025C340 = ptr;
    ptr[count + 1] = 0;
    ptr[0] = 0;
}

void* func_0011C3B8(void* base);

struct Node_11C2E8;
typedef void (*Cb_11C2E8)(void* p);

struct Node_11C2E8 {
    Node_11C2E8* next;
    s32 f4;
};

struct Pool_11C2E8 {
    s32 f00;
    s32 f04;
    s32 f08;
    Node_11C2E8* freeHead;
    Node_11C2E8* head;
    Node_11C2E8* tail;
    Cb_11C2E8 onRemove;
};

void func_0011C2E8(Pool_11C2E8* self)
{
    Node_11C2E8* prev = (Node_11C2E8*)&self->head;
    Node_11C2E8* cur = self->head;
    if (cur != 0 && cur != self->tail) {
        prev = cur;
        for (;;) {
            cur = cur->next;
            if (cur == 0 || cur == self->tail) {
                break;
            }
            prev = cur;
        }
    }
    Node_11C2E8* s2 = prev;
    cur = s2->next;
    while (cur != 0) {
        if (cur->f4 != 0) {
            prev = cur;
        } else {
            prev->next = cur->next;
            cur->next = self->freeHead;
            self->freeHead = cur;
            if (self->onRemove != 0) {
                self->onRemove(func_0011C3B8(cur));
            }
        }
        cur = prev->next;
    }
    self->tail = s2->next;
}

void func_0011EF90(void* a0, s32* a1, s32* a2)
{
    *a1 = 0;
    if (a2 != 0) {
        *a2 = 0;
    }
}

extern u8 D_0062C568[];

void func_001B5F28(void* list, void* item);

void func_0011C6C0(s32 a)
{
    u8* base = D_0062C568;
    s32 idx = (s32)((u32)(a - *(s32*)(base + 4)) >> 6);
    u8* p = (u8*)(*(s32*)((u8*)D_0027B300 + 4) + idx);
    *p = *p - 1;
    if (*p == 0) {
        func_001B5F28(base, (void*)a);
    }
}

extern u8 D_0062C578[];
extern u8* D_0027B300[];
void func_001B5F28(void* list, void* item);

void func_0011C7F0(u32 addr)
{
    u8* pool = D_0062C578;
    u8* p = D_0027B300[2] + ((addr - *(u32*)(pool + 4)) >> 4);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        func_001B5F28(pool, (void*)addr);
    }
}

extern u8 D_0062C588[];
extern u8* D_0027B300[];
void func_001B5F28(void* list, void* item);

void func_0011C900(u32 addr)
{
    u8* pool = D_0062C588;
    u8* p = D_0027B300[3] + ((addr - *(u32*)(pool + 4)) >> 3);
    s32 v = *p - 1;
    *p = v;
    if ((u8)v == 0) {
        func_001B5F28(pool, (void*)addr);
    }
}

struct Table_11F478 { s32 pad[2]; s32 count; u8* items; };
struct Entry_11F478 { u8 pad0[4]; f32 f04; u8 pad1[4]; f32 f0C; };

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);

void func_0011F478(Table_11F478* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    func_0011EE70(key, flags, 8, self->count, self->items, &diff, &delta, &p);
    if (delta < 0.0001f) {
        if (outF != 0) {
            *outF = ((Entry_11F478*)p)->f04;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    if (outF != 0) {
        f32 t = diff / delta;
        *outF = (1.0f - t) * ((Entry_11F478*)p)->f04 + t * ((Entry_11F478*)p)->f0C;
    }
    if (outI != 0) {
        *outI = scale * (((Entry_11F478*)p)->f0C - ((Entry_11F478*)p)->f04) / delta;
    }
}

struct Elem_11F568 { f32 a; f32 b; };
struct Table_11F568 { s32 pad[2]; s32 count; Elem_11F568* items; };

s32 func_00137BE0(void* src);
s32 func_00137D10(void* src);
f32 func_00137DF8(void* src);
void* func_0018D500(s32 size);

void func_0011F568(Table_11F568* self, void* src)
{
    self->count = func_00137BE0(src);
    self->items = (Elem_11F568*)func_0018D500(self->count << 3);
    for (s32 i = 0; i < self->count; i++) {
        Elem_11F568* e = self->items + i;
        e->a = (f32)func_00137D10(src) * 0.016666668f;
        e->b = func_00137DF8(src);
    }
}

struct Self_11FFD8 { void** vt; u8 pad0[4]; s32 flag; };
struct Locals_11FFD8 {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    s32 count;
    f32* values;
    f32 first;
};
typedef void (*Fn3_11FFD8)(void*, void*, void*);
typedef void (*Fn0_11FFD8)(void*, void*, void*, void*, void*, f32, f32);

extern void func_0011F798(void*, void*, void*);
extern void func_00189150(void*, void*, void*);
extern void func_00188D28(void*, void*, void*);
extern void func_0018D608(void);
extern void func_0018D6F0(void);

void func_0011FFD8(Self_11FFD8* self, void* arg)
{
    Locals_11FFD8 loc;
    s32 result;

    func_0011F798((u8*)self + 0x20, (u8*)self + 0x10, arg);
    func_0018D608();
    ((Fn3_11FFD8)self->vt[3])(self, &loc.count, &loc.values);
    if (loc.count > 0) {
        ((Fn0_11FFD8)self->vt[0])(self, 0, 0, loc.a, 0, loc.values[0], 1.0f);
        ((Fn0_11FFD8)self->vt[0])(self, 0, 0, loc.b, 0, loc.values[loc.count - 1], 1.0f);
        func_00189150(loc.a, loc.b, loc.c);
        func_00188D28(loc.c, &loc.first, loc.d);
        result = (loc.first < 0.01f) ? 1 : 0;
    } else {
        result = 1;
    }
    self->flag = result;
    func_0018D6F0();
}

// NEAR: same bytes except the order of the float move `mov.s $f14,$f20` (retail issues it first, before the `lwc1 $f18` and the `move $a0`); the argument setup is scheduled differently.

struct Table_11F0C8 { s32 pad[2]; s32 count; u8* items; };
struct Entry_11F0C8 { u8 pad0[4]; f32 f04; u8 pad1[8]; s32 kind; f32 f14; u8 pad2[4]; f32 f1C; u8 pad3[4]; f32 f24; };

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);
void func_001303F0(f32 delta, f32 diff, f32 scale, f32 p4, f32 p14, f32 p1C, f32 p24, f32* outF, f32* outI, s32 zero);

void func_0011F0C8(Table_11F0C8* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    func_0011EE70(key, flags, 0x18, self->count, self->items, &diff, &delta, &p);
    if (((Entry_11F0C8*)p)->kind == 5) {
        if (outF != 0) {
            *outF = ((Entry_11F0C8*)p)->f04;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    func_001303F0(delta, diff, scale, ((Entry_11F0C8*)p)->f04, ((Entry_11F0C8*)p)->f14, ((Entry_11F0C8*)p)->f1C, ((Entry_11F0C8*)p)->f24, outF, outI, 0);
}

// NEAR: same bytes except the order of the float move `mov.s $f14,$f20` (retail issues it first, before the `lwc1 $f12` and the `move $a0`); the argument setup is scheduled differently.

struct Table_11F320 { s32 pad[2]; s32 count; u8* items; };
struct Entry_11F320 { u8 pad0[4]; f32 f04; u8 pad1[0xC]; s32 kind; f32 f18; f32 f1C; u8 pad2[4]; f32 f24; u8 pad3[4]; f32 f2C; f32 f30; };

void func_0011EE70(f32 key, s32 flags, s32 stride, s32 n, u8* base, f32* outDiff, f32* outDelta, u8** outPtr);
void func_00130168(f32 delta, f32 diff, f32 scale, f32 p4, f32 p18, f32 p1C, f32 p24, f32 p2C, f32 p30, f32* outF, f32* outI, s32 zero);

void func_0011F320(Table_11F320* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale)
{
    f32 diff;
    f32 delta;
    u8* p;
    func_0011EE70(key, flags, 0x20, self->count, self->items, &diff, &delta, &p);
    if (((Entry_11F320*)p)->kind == 5) {
        if (outF != 0) {
            *outF = ((Entry_11F320*)p)->f04;
        }
        if (outI != 0) {
            *outI = 0.0f;
        }
        return;
    }
    func_00130168(delta, diff, scale, ((Entry_11F320*)p)->f04, ((Entry_11F320*)p)->f18, ((Entry_11F320*)p)->f1C, ((Entry_11F320*)p)->f24, ((Entry_11F320*)p)->f2C, ((Entry_11F320*)p)->f30, outF, outI, 0);
}

struct Pack7_11E048 { void* w0; s32 w1; s32 w2; s32 w3; s32 w4; s32 w5; s32 w6; };

s32 func_0011D968(s32 id, s32 size, void* data);

s32 func_0011E048(void* a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8)
{
    Pack7_11E048 buf;
    buf.w0 = a0;
    buf.w1 = a1;
    buf.w2 = (a4 << 16) | (a2 & 0xFFFF);
    buf.w3 = (a5 << 16) | (a3 & 0xFFFF);
    buf.w4 = a6;
    buf.w5 = a7;
    buf.w6 = a8;
    return func_0011D968(0x2C, 0x1C, &buf);
}

typedef void (*Slot_11ECB8)(void* self, void* arg);

struct Obj_11ECB8 {
    Slot_11ECB8* vtbl;
};

struct Ctx_11ECB8 {
    u8 pad[0x1CE8];
    void* table[31];
};

s32 func_00137D10(void* p);
void* func_0011E580(s32 slot, void* self, void* a1, s32 key, s32 flag);
s32 func_0011ECA0(s32 value);
void func_00182ED8(void* obj);

void func_0011ECB8(Ctx_11ECB8* self, void* a1, void* a2)
{
    s32 n = func_00137D10(a2);
    if (n > 0) {
        s32 i = n;
        do {
            s32 slot = func_00137D10(a2);
            s32 key = func_00137D10(a2);
            s32 flag = func_00137D10(a2);
            Obj_11ECB8* obj = (Obj_11ECB8*)func_0011E580(slot, self, a1, key, flag);
            obj->vtbl[14](obj, a2);
            s32 r = func_0011ECA0(key);
            if (r >= 0) {
                self->table[r] = obj;
                func_00182ED8(obj);
            }
        } while (--i != 0);
    }
}

struct Entry_11CE30 { s32 fn; s32 pad; u64 arg; };
struct Pend_11CE30 { s32 fn; s32 pad; u64 arg; };
typedef s32 (*Cb_11CE30)(s32 ctx, u64 arg);
typedef void (*Cb1_11CE30)(s32 a0);

extern s32 D_0025C35C;
extern s32 D_0025C380;
extern s32 D_0025C384;
extern s32 D_0025C388;
extern s32 D_0025C354;
extern s32 D_0025C358;
extern s32 D_0025C350;
extern s32 D_0025C3A0;
extern s32 D_0025C3C4;
extern u64 D_0025C3A8;
extern s32 D_0025C360;
extern s32 D_0025C370;
extern s32 D_0025C378;
extern s32 D_00260E00;
extern Pend_11CE30 D_0025C390;

s32 func_0011D078(void);
void func_0011DE18(void);
s32 func_0011E1F8(s32 flag);
void func_001F6C20(s32 a0);

s32 func_0011CE30(void)
{
    s32 i;
    s32 idx;
    s32 k;
    Cb_11CE30 f;
    if (D_0025C340 != 0 && func_0011D078() != 0) {
        if (D_0025C35C != 0) {
            if (D_0025C3A0 != 0)
                ((Cb_11CE30)D_0025C3A0)(D_0025C3C4, D_0025C3A8);
            D_0025C3A0 = 0;
            D_0025C35C = 0;
        } else {
            idx = D_0025C380 != 1;
            i = 0;
            if (((s32*)(&D_0025C360)[idx])[0] > 0) {
                do {
                    Entry_11CE30* e = (Entry_11CE30*)(i * 16 + (s32)(s32*)(&D_0025C370)[idx]);
                    if (e->fn != 0)
                        ((Cb_11CE30)e->fn)(((s32*)(&D_0025C378)[idx])[i + 1], e->arg);
                    i++;
                } while (i < ((s32*)(&D_0025C360)[idx])[0]);
            }
        }
    }
    if (D_0025C388 != 0) {
        func_001F6C20(0);
        k = D_00260E00;
        if ((u32)k != 0xFFFFFFFFu) {
            if (D_0025C390.fn != 0) {
                u64 a = D_0025C390.arg;
                Cb_11CE30 g = (Cb_11CE30)D_0025C390.fn;
                D_0025C390.fn = 0;
                D_0025C390.arg = 0;
                g(k, a);
            }
            D_00260E00 = 0;
            D_0025C388 = 0;
        }
    }
    if (D_0025C340 == 0) {
        s32* p = (s32*)(&D_0025C360)[D_0025C380];
        if (p[0] != 0 && D_0025C384 == 0)
            func_0011DE18();
    }
    if (D_0025C354 != 0) {
        func_0011E1F8(1);
        if (D_0025C358 != 0) {
            D_0025C354 = 0;
            f = (Cb_11CE30)D_0025C350;
            D_0025C358 = 0;
            if (f != 0)
                ((Cb1_11CE30)f)(1);
        }
    }
    if (D_0025C340 != 0 || D_0025C388 != 0)
        return 1;
    return 0;
}
