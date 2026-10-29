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
