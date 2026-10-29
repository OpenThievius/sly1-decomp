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

struct __attribute__((aligned(16))) Quad_121648 {
    s32 w[4];
};

struct Obj_121648 {
    void** vt;
    Obj_121648* parent;
    u8 pad0[8];
    s8 b10;
    s8 b11;
    u8 pad1[0x1EC - 0x12];
    Obj_121648* p1EC;
    Obj_121648* p1F0;
};

struct Locals_121648 {
    Quad_121648 l0;
    Quad_121648 l1;
    Quad_121648 l2;
    Quad_121648 spare[2];
};

void func_00121648(Obj_121648* self, s32 flag)
{
    Locals_121648 loc;
    Obj_121648* s2 = self->parent;

    if (self == s2->p1EC) {
        if (flag != 0 || self->b10 == 2) {
            ((void (*)(Obj_121648*, void*, void*, f32))self->vt[4])(self, &loc.l0, &loc.l1, 0.0f);
            ((void (*)(Obj_121648*, void*))s2->vt[0x84 / 4])(s2, &loc.l0);
            ((void (*)(Obj_121648*, void*))s2->vt[0x90 / 4])(s2, &loc.l1);
        }
    }
    if (self == s2->p1F0) {
        if (flag != 0 || self->b11 == 2) {
            ((void (*)(Obj_121648*, void*, void*, f32))self->vt[5])(self, &loc.l2, &loc.l0, 0.0f);
            ((void (*)(Obj_121648*, void*))s2->vt[0x88 / 4])(s2, &loc.l2);
            ((void (*)(Obj_121648*, void*))s2->vt[0x94 / 4])(s2, &loc.l0);
        }
    }
}

struct Flags_1226D8 {
    u8 pad[0x10];
    s8 a;
    s8 b;
};

void func_001226D8(Flags_1226D8* self)
{
    if (self->a == 7) {
        self->a = 3;
    }
    if (self->b == 7) {
        self->b = 3;
    }
}

struct __attribute__((aligned(16))) Quad_1227B0 {
    s32 w[4];
};

struct Vtbl_1227B0 {
    u8 pad[0xB0];
    void (*fn)(void*, Quad_1227B0*, Quad_1227B0*);
};

struct Obj_1227B0 {
    Vtbl_1227B0* vt;
};

struct Src_1227B0 {
    u8 pad0[4];
    Obj_1227B0* obj;
    u8 pad1[0x18];
    Quad_1227B0 lo;
    Quad_1227B0 hi;
};

void func_001227B0(Src_1227B0* src, Quad_1227B0* d0, Quad_1227B0* d1)
{
    *d0 = src->lo;
    *d1 = src->hi;
    Obj_1227B0* obj = src->obj;
    void (*fn)(void*, Quad_1227B0*, Quad_1227B0*) = obj->vt->fn;
    if (fn != 0) {
        fn(obj, d0, d1);
    }
}

struct __attribute__((aligned(16))) Quad_1227F0 {
    s32 w[4];
};

struct Block_1227F0 {
    Quad_1227F0 q[3];
};

struct Vtbl_1227F0 {
    u8 pad[0xB4];
    void (*fn)(void* self, Block_1227F0* b, Quad_1227F0* q);
};

struct Obj_1227F0 {
    Vtbl_1227F0* vt;
};

struct Src_1227F0 {
    u8 pad0[4];
    Obj_1227F0* obj;
    u8 pad1[0x38];
    Quad_1227F0 q40;
    Quad_1227F0 q50;
    Quad_1227F0 q60;
    Quad_1227F0 q70;
};

void func_001227F0(Src_1227F0* src, Block_1227F0* d0, Quad_1227F0* d1)
{
    d0->q[0] = src->q40;
    d0->q[1] = src->q50;
    d0->q[2] = src->q60;
    *d1 = src->q70;
    Obj_1227F0* obj = src->obj;
    void (*fn)(void*, Block_1227F0*, Quad_1227F0*) = obj->vt->fn;
    fn(obj, d0, d1);
}

struct SlotList4_00123C90 { u8 pad0[0x564]; u32 count; s32 items[4]; };

void func_00123C90(SlotList4_00123C90* self, s32 value)
{
    u32 n = self->count;
    if (n < 4) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

struct SlotList16_00123CB8 { u8 pad0[0x578]; u32 count; s32 items[16]; };

void func_00123CB8(SlotList16_00123CB8* self, s32 value)
{
    u32 n = self->count;
    if (n < 16) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

struct SlotList6_00123CE0 { u8 pad0[0x600]; u32 count; s32 items[6]; };

void func_00123CE0(SlotList6_00123CE0* self, s32 value)
{
    u32 n = self->count;
    if (n < 6) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

struct TestList_00123D40 { u8 pad0[0x5BC]; s32 count; void* items[1]; };

s32 func_001C1A28(void* a, void* b);

s32 func_00123D40(TestList_00123D40* self, void* arg)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (func_001C1A28(arg, &self->items[i]) == 0) {
            return 0;
        }
    }
    return 1;
}
