// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

int func_001EAC68(f32 a, f32 b, f32 eps);

void func_00183F40(f32* out0, f32* out1, f32 a, f32 b, f32 c, f32 d)
{
    if (func_001EAC68(a, c, 1e-4f)) {
        *(s32*)out1 = 0;
        *out0 = b;
    } else {
        f32 t = (d - b) / (c - a);
        *out1 = t;
        *out0 = b - t * a;
    }
}

struct __attribute__((packed)) Q_180F20 { u64 v; };
struct Obj_180F20 { u8 pad0[0x38]; Q_180F20 q; };
void func_001830D8(void* self);

void func_00180F20(Obj_180F20* self)
{
    Q_180F20 saved = self->q;
    func_001830D8(self);
    self->q = saved;
}

void func_00192C58(void* self);
void func_00181DA8(void* self, s32 n);

void func_00181AF0(void* self)
{
    func_00192C58(self);
    func_00181DA8(self, 1);
}

typedef void (*VFnA_182D00)(void* self);
typedef void (*VFnB_182D00)(void* self, s32 n, void* other);
struct Obj_182D00 { void** vtbl; };

void func_00182D00(Obj_182D00* self)
{
    ((VFnA_182D00)self->vtbl[10])(self);
    ((VFnB_182D00)self->vtbl[18])(self, 1, self);
}

typedef void (*VFn0_182E88)(void* self);
typedef void (*VFn2_182E88)(void* self, s32 a, void* b);
struct Obj_182E88 { void** vtbl; };

void func_00182E88(Obj_182E88* self)
{
    ((VFn0_182E88)self->vtbl[11])(self);
    ((VFn2_182E88)self->vtbl[18])(self, 2, self);
}

struct Node_1831E8 { void* f0; s32 f4; u8 pad0[8]; void* f10; };
void* func_001DBBD8(void);

void func_001831E8(void* a0, void** head, void* item, s32 count)
{
    Node_1831E8* n = (Node_1831E8*)func_001DBBD8();
    n->f0 = item;
    n->f4 = count;
    n->f10 = *head;
    *head = n;
}

struct Sub_183458 { u8 pad0[4]; s32 f4; };
struct Obj_183458 { u8 pad0[8]; s32 f8; u8 pad1[0x24]; Sub_183458* f30; };

s32 func_00183458(Obj_183458* a)
{
    if (a->f30) return a->f30->f4;
    return a->f8;
}

struct Obj_183DC0 { u8 pad0[0x14]; u8* f14; };
void func_00152600(void* a, void* b);
void func_001841B0(void* a);

void func_00183DC0(Obj_183DC0* self)
{
    func_00152600(self->f14 + 0x1BE8, self);
    func_001841B0(self);
}

s32 func_001EAC68(f32 a, f32 b, f32 c);

void func_00183FE0(f32* out, s32* flag, f32 x, f32 y, f32 z, f32 w)
{
    const f32 eps = 0.0001f;
    if (func_001EAC68(x, z, eps) || __builtin_fabsf(x) < eps || __builtin_fabsf(z) < eps) {
        *flag = 0;
        *out = y;
        return;
    }
    f32 t = (x * z) * (w - y) / (x - z);
    *(f32*)flag = t;
    *out = y - t / x;
}
