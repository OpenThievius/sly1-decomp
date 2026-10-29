// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Comp_17CE80 {
    u8 pad0[0x2740];
    s32 f2740;
};

struct Obj_17CE80 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x34 - 0x18];
    s32 f34;
    s32 f38;
    Comp_17CE80* f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    void* f50;
    u8 pad2[0x68 - 0x54];
    s32 f68;
};

void func_0017BC20(void* self, s32 n);
void func_0017BB78(void* self, s32 n);
void func_0012E760(void* p);
void func_00142ED0(f32 x);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_0016E118(s32 n);
void func_001DDA50(void* p);

void func_0017CE80(Obj_17CE80* self)
{
    if (self->f3C != 0) {
        func_0017BC20(self, 0);
        func_0017BB78(self, 0);
        if (self->f50 != 0) {
            func_0012E760(self->f50);
            self->f50 = 0;
        }
        func_00142ED0(1.0f);
        self->f40 = self->f34;
        self->f4C = 0;
        self->f48 = 0;
        self->f3C->f2740 = 0;
        self->f3C = 0;
        func_001837E0(self, 25, 0, 0);
        if (self->f68 != 0) {
            func_0016E118(4);
            func_001DDA50(self->f14);
        }
    }
}

struct Obj_17D040 { u8 pad0[0xC]; union { s32 f0C; f32 f0Cf; }; };
Obj_17D040* func_0017CF38(void* self, s32 a, s32 b, s32 c);

void func_0017D040(void* self, s32 value)
{
    Obj_17D040* o = func_0017CF38(self, 2, -1, 1);
    o->f0C = value;
}

void func_0017D148(void* self, s32 a, s32 b, f32 value)
{
    Obj_17D040* o = func_0017CF38(self, 6, a, b);
    o->f0Cf = value;
}

extern u8 D_00264088[];
void func_00152440(void* p);

void func_0017FD70(void)
{
    func_00152440(D_00264088);
}

extern void* D_002640A4;
void func_00182C18(void* self);

void func_0017FE90(void* self)
{
    func_00182C18(self);
    D_002640A4 = self;
}

extern u8 D_00264088[];
void func_00152438(void* self, s32 value);

void func_0017FD48(void)
{
    func_00152438(D_00264088, 0x50);
}

extern u8 D_00264088[];
void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_0017FD90(void* self)
{
    func_00182D48(self);
    func_00152470(D_00264088, self);
}

s32 func_0017D220(void* self)
{
    return (s32)func_0017CF38(self, 0xC, -1, 0);
}

extern u8 D_00264088[];

void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

void func_0017FDC8(void* self)
{
    func_00182ED0(self);
    func_00152600(D_00264088, self);
}

struct __attribute__((packed)) Packed8_17FE00 { u64 bits; };

struct Obj_17FE00 {
    u8 pad[0x50];
    Packed8_17FE00 field;
};

void func_001830D8(void* self);

void func_0017FE00(Obj_17FE00* self)
{
    Packed8_17FE00 tmp = self->field;
    func_001830D8(self);
    self->field = tmp;
}
