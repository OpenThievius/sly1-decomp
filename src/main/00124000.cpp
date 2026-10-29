// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*VFn_125108)(void* self);

struct Vtbl_125108 {
    u8 pad0[0x5C];
    VFn_125108 f5C;
};

struct Obj_125108 {
    Vtbl_125108* vt;
};

void func_00125108(Obj_125108* self)
{
    VFn_125108 fn = self->vt->f5C;
    if (fn != 0) {
        fn(self);
    }
}

void* func_00159BB0(void);
s32 func_00182FC8(void* self);

struct Sub_126C58 {
    s32 f0;
    f32 f4;
};

struct Obj_126C58 {
    u8 pad0[0x298];
    Sub_126C58* f298;
};

void func_00126C58(Obj_126C58* self)
{
    if (self->f298 == 0) {
        self->f298 = (Sub_126C58*)func_00159BB0();
        if (func_00182FC8(self) != 0) {
            self->f298->f4 = 1.0f;
        } else {
            self->f298->f4 = 0.0f;
        }
    }
}

typedef void (*VFn_1243E0)(void* self, s32 a);
struct Self_1243E0 {
    VFn_1243E0* vt;
    u8 pad0[0x14 - 4];
    u8* p14;
    s32 f18;
    u8 pad1[0x50 - 0x1C];
    s32 f50;
    void* p54;
    u8 pad2[0x284 - 0x58];
    void* p284;
    u8 pad3[0x294 - 0x288];
    s32 f294;
    u8 pad4[0x2C8 - 0x298];
    u64 flags2C8;
};

extern void* D_00261990;

void func_00182ED0(Self_1243E0* self);
void func_00152600(void* list, void* item);
void func_00152440(void* a);
void func_0015F710(u8* a, void* b);
void func_00143B20(void* a, Self_1243E0* b);
void func_00129DF8(Self_1243E0* self);
void func_001837E0(Self_1243E0* self, s32 a1, s32 a2, s32 a3);

void func_001243E0(Self_1243E0* self)
{
    func_00182ED0(self);
    u8* s1 = self->p14;
    if (self->f18 == 0) {
        if (self->f294 != 0) {
            func_00152600(s1 + 0x78, self);
        } else {
            func_00152600(s1 + 0x54, self);
            u64 fl = self->flags2C8;
            if ((fl & (1ull << 37)) != 0) {
                self->flags2C8 = fl & ~(1ull << 37);
                func_00152600(s1 + 0x60, self);
                if ((((s32*)self->vt)[2] & 2) != 0) {
                    func_00152600(s1 + 0x6C, self);
                }
            }
            func_0015F710(s1, self->p54);
            self->p54 = 0;
            func_00152440((u8*)self + 0x60);
        }
    }
    if ((self->flags2C8 & (1ull << 36)) != 0) {
        func_00143B20(D_00261990, self);
    }
    if (self->p284 != 0) {
        func_00152600(self->p14 + 0x1C00, self->p284);
    }
    if ((self->flags2C8 & (1ull << 38)) != 0) {
        VFn_1243E0 fn = self->vt[0x60 / 4];
        if (fn != 0) {
            fn(self, 0);
        }
    }
    func_00129DF8(self);
    self->f50 = 0;
    func_001837E0(self, 5, 0, 0);
}
