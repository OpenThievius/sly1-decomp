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

void func_00128018(void* a0, s32 zero, void* table, void* out);
void func_001BC260(f32 t, void* obj, void* a, void* b);
f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);
void func_001C5D58(void* obj);
void func_00175170(void* obj, s32 a, s32 b);

extern u8 D_00264180[];
extern f32 D_00264190;

struct Vec_181B20 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

struct Obj_181B20 {
    void** vtbl;
    u8 pad0[0x638 - 4];
    f32 x638;
};

void func_00181B20(void* unused, void* obj_)
{
    Obj_181B20* obj = (Obj_181B20*)obj_;
    Vec_181B20 first;
    Vec_181B20 second;

    func_00128018(unused, 0, D_00264180, &first);
    func_001BC260(D_00264190, obj, &first, &second);
    ((void (*)(void*, void*))obj->vtbl[0x90 / 4])(obj, &second);
    f32 r = func_00205778(second.y, second.x);
    obj->x638 = func_001EA408(r + 3.1415927f);
    func_001C5D58(obj);
    func_00175170(obj, 4, 0x2B);
}

void func_001BC4D8(void* self, void* sub);

void func_00181D88(void* self)
{
    func_001BC4D8(self, (u8*)self + 0xC04);
}

void func_0013CE40(void* self);
void func_00124DF8(void* self, s32 a, void* table);
s32 func_001B6290(void* a0, void* self, s32 b, s32 c);
s32 func_00121160(s32 a);
void* func_0018D500(s32 size);

extern u8 D_00264230[];

struct Alloc_1824D8 {
    u8 pad[8];
    s32 field8;
    void* field_c;
};

struct Obj_1824D8 {
    u8 pad0[0x6C4];
    void* x6C4;
    void* x6C8;
    u8 pad1[0x6E8 - 0x6CC];
    Alloc_1824D8* x6E8;
};

void func_001824D8(void* self_)
{
    Obj_1824D8* self = (Obj_1824D8*)self_;
    func_0013CE40(self);
    func_00124DF8(self, 2, D_00264230);
    self->x6C8 = (void*)func_001B6290(self->x6C4, self, 0x36E, 0);
    Alloc_1824D8* n = (Alloc_1824D8*)func_00121160(0);
    self->x6E8 = n;
    n->field8 = 0;
    self->x6E8->field_c = func_0018D500(0xC00);
}

typedef void (*VFn_182C18)(void* self);

struct Obj_182C18 {
    VFn_182C18* vtbl;
};

void func_00182C18(void* self_)
{
    Obj_182C18* self = (Obj_182C18*)self_;
    self->vtbl[5](self);
    self->vtbl[6](self);
}

void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00182C58(void* self)
{
    func_001837E0(self, 0, 0, 0);
}

typedef void (*VFn_182F78)(void* self, s32 arg);
typedef void (*VFnNone_182F78)(void* self);
struct Obj_182F78 { void* vtbl; u8 pad[0x18 - 4]; s32 f18; };

void func_00182F78(void* a0, s32 a1)
{
    Obj_182F78* self = (Obj_182F78*)a0;
    ((VFn_182F78*)self->vtbl)[7](self, a1);
    self->f18 = a1;
    ((VFnNone_182F78*)self->vtbl)[6](self);
}

s32 func_00182FC8(void* p);

void func_00183028(void* a0, s32* out)
{
    *out = func_00182FC8(a0);
}

void* func_0011E580(s32 a, void* b, s32 c, s32 d, s32 e);

typedef void (*VFn_183058)(void* self, void* arg);
struct Ref_183058 { s32 pad0; s32 f4; };
struct Self_183058 { Ref_183058* ref; s32 pad4; s32 f8; };
struct Obj_183058 { void* vtbl; };

void* func_00183058(Self_183058* self, void* a1, s32 a2)
{
    Obj_183058* r = (Obj_183058*)func_0011E580(self->ref->f4, a1, a2, self->f8, -1);
    ((VFn_183058*)r->vtbl)[12](r, self);
    return r;
}

void func_001243E0(void* self);
void func_00183DC0(void* self);

void func_00183E70(void* self)
{
    func_001243E0(self);
    func_00183DC0(self);
}

struct Tuning_182E40 { u8 pad[0xC]; f32 scale; };

extern Tuning_182E40* D_002623C8;

s32 func_001EB050(void* target, f32 scale);
void func_00182DD8(void* self);

void func_00182E40(void* self, void* target)
{
    if (func_001EB050(target, D_002623C8->scale)) {
        func_00182DD8(self);
    }
}

void func_00182ED0(void* self)
{
    (void)self;
}

typedef void (*VFn_182ED8)(void* self);
struct Obj_182ED8 { VFn_182ED8* vtbl; };

s32 func_00182FC8(void* self);

void func_00182ED8(void* self)
{
    Obj_182ED8* obj = (Obj_182ED8*)self;
    if (func_00182FC8(self)) {
        VFn_182ED8 f = obj->vtbl[19];
        if (f) {
            f(self);
        }
        obj->vtbl[20](self);
        obj->vtbl[7](self);
    }
}

struct Link_182F40 { u8 pad[0x18]; Link_182F40* next; };

s32 func_00182F40(Link_182F40* node, Link_182F40* target)
{
    if (node == 0) {
        return 0;
    }
    while (node != 0) {
        if (node == target) {
            return 1;
        }
        node = node->next;
    }
    return target == 0;
}

struct __attribute__((aligned(16))) Quad_183B20 { s32 w[4]; };
struct __attribute__((packed)) Pack_183B20 { u64 v; };

void func_0011B008(void* self);
void* func_0011C858(void);
void func_0011B818(void* self, void* ptr);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183B20(void* a0, void* a1, void* a2)
{
    Quad_183B20 a;
    Quad_183B20 b;
    void* p;
    func_0011B008(&a);
    p = func_0011C858();
    *(Pack_183B20*)p = *(Pack_183B20*)a2;
    func_0011B818(&a, p);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

struct __attribute__((aligned(16))) Quad_183BB8 { s32 w[4]; };

void func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183BB8(void* a0, void* a1, s32 n)
{
    Quad_183BB8 a;
    Quad_183BB8 b;
    func_0011B008(&a);
    func_0011B570(&a, n);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

struct __attribute__((aligned(16))) Quad_183C38 { s32 w[4]; };

void func_0011B008(void* self);
void* func_0011C508(void);
void func_0011B740(void* a, void* b);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183C38(void* a0, void* a1, void* a2)
{
    Quad_183C38 a;
    Quad_183C38 b;
    void* p;
    func_0011B008(&a);
    p = func_0011C508();
    *(Quad_183C38*)p = *(Quad_183C38*)a2;
    func_0011B740(&a, p);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

void func_00125138(void* self);
void func_001841D0(void* self);
void func_00184B58(void* self);

void func_00183D88(void* self)
{
    func_00125138(self);
    func_001841D0(self);
    func_00184B58(self);
}
