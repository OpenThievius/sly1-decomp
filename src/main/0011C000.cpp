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
