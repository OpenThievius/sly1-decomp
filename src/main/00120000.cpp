// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_0011F850(void* a, void* b);

void func_00120110(u8* self, void* p)
{
    func_0011F850(self + 0x20, p);
}

void func_0011F798(void* a, void* b, void* c);

void func_00120360(u8* self, void* p)
{
    func_0011F798(self + 0x20, self + 0x10, p);
}

struct __attribute__((packed)) Pair_1212D8 { s32 lo; s32 hi; };
struct Obj_1212D8 { u8 pad0[4]; s32 w4; Pair_1212D8 p8; };
struct Ctx_1212D8 { u8 pad[0x1B20]; s32 x; };
extern Ctx_1212D8* D_00275710;

void func_0018D800(Obj_1212D8* self, s32 a, s32 b);

void func_001212D8(Obj_1212D8* self, s32 a1)
{
    Pair_1212D8 tmp = self->p8;
    s32 saved = self->w4;
    func_0018D800(self, a1, D_00275710->x);
    self->p8 = tmp;
    self->w4 = saved;
}

struct Obj_122878 { u8 pad[0xC4]; f32* data; };

f32 func_00122878(Obj_122878* self, s32 i)
{
    return self->data[i];
}

typedef s32 (*VFn_123120)(void* self, void* a, s32 b, s32 c, s32 d, f32 e, f32 f);
struct Obj_123120 { VFn_123120* vtbl; };
struct Table_123120 { u8 pad[0x3C]; u8* base; };
struct Track_123120 { u8 pad0[8]; Table_123120* table; u8 pad1[4]; f32 c10; f32 c14; f32 c18; };
struct Entry_123120 { u8 pad0[8]; Obj_123120* obj; u8 pad1[16]; };
struct Self_123120 { u8 pad0[4]; void* p4; u8 pad1[9]; s8 kind; u8 pad2[6]; f32 f18; Track_123120* track; u8 pad3[8]; s32 index; };

extern f32 D_0026185C[];
s32 func_00121508(Self_123120* self, s32 a, s32 b);
s32 func_0012E9E0(Track_123120* t, f32* a, f32* b);

s32 func_00123120(Self_123120* self, s32 a1, s32 a2, f32 f)
{
    void* p4 = self->p4;
    Track_123120* track = self->track;
    Entry_123120* e = (Entry_123120*)(track->table->base + self->index * 0x1C);
    if (e->obj != 0) {
        f32 tmp[2];
        if (f != 0.0f) {
            f32 c14 = track->c14;
            f32 c18 = track->c18;
            tmp[1] = c18;
            tmp[0] = c14 + f * c18;
            func_0012E9E0(track, &tmp[0], &tmp[1]);
        } else {
            tmp[0] = track->c14;
        }
        if (self->kind == 4) {
            f32 d = self->f18 - D_0026185C[0] - track->c10;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->c18;
            }
        }
        return e->obj->vtbl[0](e->obj, p4, 0, a1, a2, tmp[0], track->c18);
    }
    return func_00121508(self, a1, a2);
}

extern u8 D_00261420[];
void func_001B7968(void* self);
s32 func_00140FF8(void* p);

struct Obj_123408 {
    u8 pad0[0x550];
    s32 f550;
    u8 pad1[0x6B0 - 0x554];
    s32 f6B0;
};

void func_00123408(Obj_123408* self)
{
    func_001B7968(self);
    self->f550 = -1;
    self->f6B0 = func_00140FF8(D_00261420);
}

typedef void (*VFn_123B28)(void* self, s32 arg);

struct Vtbl_123B28 {
    u8 pad0[0x134];
    VFn_123B28 f134;
};

struct Elem_123B28 {
    Vtbl_123B28* vt;
    u8 pad1[0x560 - 4];
    s32 f560;
};

struct Obj_123B28 {
    u8 pad0[0x5BC];
    s32 count5BC;
    Elem_123B28* items[1];
};

void func_00123B28(Obj_123B28* self)
{
    for (s32 i = 0; i < self->count5BC; i++) {
        Elem_123B28* e = self->items[i];
        if (e->f560 == -1 && e->vt->f134 != 0) {
            e->vt->f134(e, 0);
        }
    }
}

struct __attribute__((aligned(16))) Quad_122968 { s32 a, b, c, d; };
typedef void (*VFn_122968)(void* self, void* a, void* b);
struct Obj_122968 { VFn_122968* vtbl; };
struct Self_122968 {
    u8 pad0[4];
    Obj_122968* obj;
    u8 pad1[0x1C];
    Quad_122968* src24;
    Quad_122968* src28;
};

void func_00122968(Self_122968* self, Quad_122968* d1, Quad_122968* d2)
{
    Quad_122968* s = self->src24;
    d1[0] = s[0];
    d1[1] = s[1];
    d1[2] = s[2];
    *d2 = *self->src28;
    self->obj->vtbl[45](self->obj, d1, d2);
}

struct Self_1229C0 {
    u8 pad[0x2C];
    f32* p2c;
    f32* p30;
};

void func_001229C0(Self_1229C0* self, f32* a, f32* b)
{
    *a = *self->p2c;
    *b = *self->p30;
}

struct __attribute__((aligned(16))) Quad_1229E0 { s32 a, b, c, d; };
struct Self_1229E0 {
    u8 pad[0x34];
    Quad_1229E0* src;
};

void func_001229E0(Self_1229E0* self, Quad_1229E0* dst)
{
    Quad_1229E0* s = self->src;
    dst[0] = s[0];
    dst[1] = s[1];
    dst[2] = s[2];
}

struct Self_122A00 {
    u8 pad[0x3C];
    f32* data;
};

f32 func_00122A00(Self_122A00* self, s32 i)
{
    return self->data[i];
}

f32 func_00122D90(void)
{
    return 0.0f;
}

struct Self_122DA0 {
    u8 pad0[0x1C];
    f32 f1c;
    f32 f20;
};

void func_00121338(void* self, s32 a1);

void func_00122DA0(Self_122DA0* self, s32 a1)
{
    func_00121338(self, a1);
    self->f1c = 1.0f;
    self->f20 = 0.25f;
}

struct Owner_122F28 {
    u8 pad0[0x28];
    void* p28;
};
struct Self_122F28 {
    u8 pad0[0x1C];
    Owner_122F28* owner;
};

void func_00152600(void* list, void* item);
void func_00121358(void* self, void* a1);

void func_00122F28(Self_122F28* self, void* a1)
{
    Owner_122F28* o = self->owner;
    func_00152600((u8*)o + 0x44, self);
    if (o->p28 == self) {
        o->p28 = 0;
    }
    func_00121358(self, a1);
}
