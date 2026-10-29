// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_177828 {
    u8 pad0[0x4B8];
    s32 f4B8;
    u8 pad1[0x2BD8 - 0x4BC];
    s32 f2BD8;
};

void func_00177828(Obj_177828* self, s32 value)
{
    self->f2BD8 = value;
    self->f4B8 = 0;
}

void func_001777F8(void)
{
}

void func_00175170(void* self, s32 mode, s32 count);

void func_00177800(void* self, s32 flag)
{
    func_00175170(self, flag ? 11 : 0, -1);
}

struct Keyed_177968 { u8 pad0[0x14]; f32 key; };

s32 func_00177968(Keyed_177968* a, Keyed_177968* b)
{
    s32 r = -1;
    if (a->key > b->key) r = 1;
    return r;
}

struct Ctx_177E20 { u8 pad0[0x2220]; s32 kind; u8 pad1[4]; s32 sub; };

extern u8* D_00261990;
s32 func_001493A0(u8* p);

s32 func_00177E20(Ctx_177E20* self)
{
    if (self->kind == 12 && self->sub == 0x22) return 0;
    return func_001493A0(D_00261990 + 0x454) == 0;
}

void func_001924C8(void* self, s32 mode);
void func_00175170(void* self, s32 a, s32 b);

void func_00177E70(void* self, s32 mode)
{
    func_001924C8(self, mode);
    switch (mode) {
    case 0:
        (void)func_00175170(self, 9, 0x1C);
        break;
    case 1:
        (void)func_00175170(self, 9, 0x1D);
        break;
    }
}

typedef void (*VFn_175078)(void* self);

struct Obj_175078 {
    VFn_175078* vtbl;
};

struct Dev_175078 {
    u8 pad_00[0x10];
    s8 f10;
};

struct Self_175078 {
    u8 pad_000[0x610];
    Obj_175078* f610;
    Obj_175078* f614;
    Obj_175078* f618;
    Obj_175078* f61C;
    u8 pad_620[0x24F8 - 0x620];
    Obj_175078* f24F8;
    u8 pad_24FC[0x2500 - 0x24FC];
    Dev_175078* f2500;
    Dev_175078* f2504;
    Dev_175078* f2508;
    Dev_175078* f250C;
    Dev_175078* f2510;
};

void func_00175078(Self_175078* self, s32 flags)
{
    if (self->f2500 != 0) {
        s32 a = flags & 1;
        self->f2500->f10 = a ? 9 : -1;
        self->f2504->f10 = a ? 9 : -1;
        self->f2508->f10 = a ? 9 : -1;
        s32 b = flags & 2;
        self->f250C->f10 = b ? 9 : -1;
        self->f2510->f10 = b ? 9 : -1;
        Obj_175078* o = self->f24F8;
        o->vtbl[47](o);
        o = self->f618;
        o->vtbl[47](o);
        o = self->f61C;
        o->vtbl[47](o);
        o = self->f610;
        o->vtbl[47](o);
        o = self->f614;
        o->vtbl[47](o);
    }
}
