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
