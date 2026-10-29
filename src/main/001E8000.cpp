// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_E8E08 { u8 pad[0xC58]; s32 f58; s32 f5C; };
void func_001C9AF8(void);

void func_001E8E08(Obj_E8E08* a0)
{
    if (a0->f58 != 0x2DA) {
        s32 v = a0->f5C - 1;
        if (!(0 < v)) v = 0;
        a0->f5C = v;
    }
    func_001C9AF8();
}

extern u8 D_00275BC0[];
void func_001E90A8(void* p);

void func_001E9088(void)
{
    func_001E90A8(D_00275BC0);
}

void func_001AA110(void);

void func_001E9668(void)
{
    func_001AA110();
}

void func_001EB018(f32* a0, f32 x, f32 y, f32 z, f32 w)
{
    f32 p = w - x;
    f32 q = y - x;
    a0[0] = x;
    f32 r = p / z - q;
    r = r / (z - 1.0f);
    a0[2] = r;
    a0[1] = q - r;
}

struct __attribute__((packed)) Entry8_1EBCD8 { u8 b[8]; };
struct List_1EBCD8 { u8 pad[0x630]; s32 count; Entry8_1EBCD8 items[1]; };

void func_001EBCD8(List_1EBCD8* list, const Entry8_1EBCD8* src)
{
    s32 n = list->count;
    list->count = n + 1;
    Entry8_1EBCD8* dst = (Entry8_1EBCD8*)((u8*)list + (n * 8 + 0x634));
    *dst = *src;
}
