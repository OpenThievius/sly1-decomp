// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_178008 {
    u8 pad0[0x1520];
    u8 f1520[0x2768 - 0x1520];
    s32 f2768;
};

void func_001B9690(void* self);
void func_001C29E8(void* sub);

void func_00178008(Obj_178008* self)
{
    func_001B9690(self);
    func_001C29E8(self->f1520);
    self->f2768 = 0;
}

struct Obj_17ADD0 {
    u8 pad0[0x550];
    s32 f550;
};

void func_001B7968(void* self);

void func_0017ADD0(Obj_17ADD0* self)
{
    func_001B7968(self);
    self->f550 = -1;
}

struct Obj_17B510 {
    u8 pad0[0x600];
    void* f600;
    u8 f604[4];
};

s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);

s32 func_0017B510(Obj_17B510* self, s32 flag)
{
    void* p = 0;
    if (flag != 0) {
        p = self->f600;
    }
    return func_0012C918(p, self, 1, self->f604, 0.0f, 1.0f);
}

typedef void (*VFn_17BC20)(void* self);

struct Comp_17BC20 {
    VFn_17BC20* vtbl;
    u8 pad0[0x2D0 - 4];
    s32 f2D0;
};

struct Obj_17BC20 {
    u8 pad0[0x3C];
    s32 f3C;
    u8 pad1[0x58 - 0x40];
    Comp_17BC20* f58;
    s32 f5C;
};

void func_001E2840(void* p, s32 n);
s32 func_00182FC8(void* p);

void func_0017BC20(Obj_17BC20* self, Comp_17BC20* next)
{
    if (self->f58 != 0) {
        func_001E2840(self->f58, -1);
        self->f58->f2D0 = 0;
        if (self->f5C != 0) {
            self->f58->vtbl[7](self->f58);
        }
        self->f58 = 0;
    }
    if (next != 0) {
        self->f58 = next;
        s32 isNull = func_00182FC8(next) == 0;
        self->f5C = isNull;
        if (isNull != 0) {
            next->vtbl[6](next);
        }
        next->f2D0 = self->f3C;
        func_001E2840(next, 1);
    }
}

void func_0017B598(void* self)
{
    func_0012C918(*(void**)((u8*)self + 0x60C), self, 1, (u8*)self + 0x610, 0.0f, 1.0f);
}

extern s32 D_00263E2C;
extern s32 D_00263E30;

struct Obj_17B5D0 { u8 pad0[0x558]; s32 f558; };

void func_0017B5D0(void* self)
{
    Obj_17B5D0* o = (Obj_17B5D0*)self;
    func_001B7968(self);
    o->f558 = 0x10;
    D_00263E2C = -1;
    D_00263E30 = 0;
}

extern u8 D_00263E08[];

void func_00124A48(void* self);
void func_00124DF8(void* self, int n, void* table);

void func_0017B610(void* self)
{
    func_00124A48(self);
    func_00124DF8(self, 3, D_00263E08);
}

void func_00182C18(void* self);
void* func_0018D500(int size);

struct Obj_17B998 {
    u8 pad0[0x38];
    void* f38;
    u8 pad1[0x68 - 0x3C];
    s32 f68;
};

void func_0017B998(void* self)
{
    Obj_17B998* o = (Obj_17B998*)self;
    func_00182C18(self);
    o->f38 = func_0018D500(0xA00);
    o->f68 = 1;
}
