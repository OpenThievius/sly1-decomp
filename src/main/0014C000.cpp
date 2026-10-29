// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Item_14C838 { s32 value; s32 pad[4]; };
struct List_14C838 { u8 pad0[0x2DC]; s32 count; Item_14C838 items[1]; };

void func_0014C838(List_14C838* self, s32 value)
{
    s32 i = self->count;
    self->count = i + 1;
    self->items[i].value = value;
}

struct Obj_14DA68 { u8 pad0[0x8]; void* p8; s32 cnt; u8 pad1[4]; f32* p14; };

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

s32 func_0014DA68(Obj_14DA68* self, f32* a1, f32* a2)
{
    return func_0014D1A0(self->cnt, self->p14, self->p8, a1, a2);
}

struct Obj_14DD28 { void** vtbl; u8 pad0[4]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; };
typedef void (*Fn_14DD28)(void* self);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);

void func_0014DD28(Obj_14DD28* self, void* src)
{
    self->a8 = func_00137B90(src);
    s32 n = func_00137B90(src);
    self->cnt = n;
    self->p10 = (f32*)func_0018D500(n * 4);
    self->p14 = (f32*)func_0018D500(self->cnt * 4);
    self->p18 = func_0018D500(self->cnt * 16);
    for (s32 i = 0; i < self->cnt; i++) {
        self->p10[i] = func_00137DF8(src);
        func_00137E70(src, (u8*)self->p18 + i * 16);
    }
    Fn_14DD28 fn = (Fn_14DD28)self->vtbl[9];
    if (fn) fn(self);
}

struct Obj_14DF98 { u8 pad0[0x14]; f32* p14; };

s32 func_0014DA38(void* self, f32* a, f32* b);

f32 func_0014DF98(Obj_14DF98* self)
{
    f32 a, b;
    s32 i = func_0014DA38(self, &a, &b);
    f32 t = a / b;
    return (1.0f - t) * self->p14[i] + t * self->p14[i + 1];
}

struct Obj_14E2A0 { u8 pad0[0x8]; s32 a8; s32 cnt; f32* p10; f32* p14; void* p18; };

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);
void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

void func_0014E2A0(Obj_14E2A0* self, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = func_0014D1A0(self->cnt, self->p14, (void*)self->a8, 0, 0);
    s32 ia;
    f32 fb;
    func_0014D680(a1, a2, self->cnt, self->p18, idx, self->a8, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->p14[ia] + fb * self->p14[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->p10[ia] + fb * self->p10[ia + 1];
}

struct Obj_14E910 { u8 pad0[0x14]; f32* p14; void* p18; void* p1C; void* p20; };
s32 func_0014DA38(void* self, f32* a, f32* b);
f32 func_00130C20(void* p0, void* p1, void* p2, void* p3, f32 x, f32 y);
f32 func_0014E910(Obj_14E910* self)
{
    f32 a, b;
    s32 i = func_0014DA38(self, &a, &b);
    u32 off = i * 16;
    f32 r = func_00130C20((u8*)self->p18 + off, (u8*)self->p20 + off,
                          (u8*)self->p18 + (off + 16), (u8*)self->p1C + (off + 16), b, a);
    return r + self->p14[i];
}

struct Obj_14EE70 { u8 pad0[0x14]; u8* p14; void* p18; u8 pad1[0x538 - 0x1C]; u64 bits538; };

void func_001B7A98(void* self);
s32 func_001526D0(void* a, void* b);
void func_00152600(void* a, void* b);
s32 func_001300E8(void* a, s32 b);

void func_0014EE70(Obj_14EE70* self)
{
    func_001B7A98(self);
    if (func_001526D0(self->p14 + 0x1C78, self)) func_00152600(self->p14 + 0x1C78, self);
    if (self->p18 != 0 && func_001300E8(self->p18, 0x3A) != 0) {
        self->bits538 |= (u64)0x8000 << 28;
    } else {
        self->bits538 &= ~((u64)1 << 43);
    }
}

extern u8 D_00261CC8[];
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 idx, void* table);

void func_0014F020(void* self)
{
    func_00124A48(self);
    func_00124DF8(self, 1, D_00261CC8);
}

extern u8* D_00262E10;

void func_0014F900(u8* self)
{
    if (D_00262E10 != 0) {
        *(s32*)(self + 0x6DC) = *(s32*)(D_00262E10 + 0x24F8);
    }
}
