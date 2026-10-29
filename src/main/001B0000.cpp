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
