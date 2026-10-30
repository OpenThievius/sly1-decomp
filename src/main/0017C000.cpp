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

struct Obj_17CDA8 {
    u8 pad0[0x34];
    s32 f34;
    u8 pad1[0x3C - 0x38];
    void* f3C;
    s32 f40;
};

void func_0017C660(Obj_17CDA8* self);

s32 func_0017CDA8(Obj_17CDA8* self)
{
    func_0017C660(self);
    if (self->f34 > 0) {
        return self->f40 < self->f34;
    }
    return 0;
}

struct Obj_17CDE0 {
    u8 pad0[0x34];
    s32 f34;
    u8 pad1[0x3C - 0x38];
    void* f3C;
    s32 f40;
};

void func_0017CE80(Obj_17CDE0* self);

void func_0017CDE0(Obj_17CDE0* self)
{
    if (self->f3C != 0) {
        func_0017CE80(self);
        self->f34 = 0;
    } else {
        self->f34 = 0;
    }
    self->f40 = 0;
}

struct Slot_17FE48 {
    u8 pad0[0x14];
    void* ref;
    u8 pad1[0x44];
    s32 key;
    s32 result;
};

void func_00182C58(void* self);
s32 func_0015A418(void* ref, s32 mode, s32 key, Slot_17FE48* self);

void func_0017FE48(Slot_17FE48* self)
{
    func_00182C58(self);
    if (self->key != -1) {
        self->result = func_0015A418(self->ref, 0x104, self->key, self);
    }
}

void func_001837E0(void* self, s32 kind, s32 a, s32 b);
void func_0016E0F0(s32 a);
void func_001DDA20(void* a);

struct Self_17CE20 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x3C - 0x18];
    void* f3C;
    s32 f40;
    u8 pad2[0x68 - 0x44];
    s32 f68;
};

struct Other_17CE20 {
    u8 pad[0x2740];
    void* f2740;
};

void func_0017CE20(void* a0, void* a1)
{
    Self_17CE20* self = (Self_17CE20*)a0;
    ((Other_17CE20*)a1)->f2740 = self;
    self->f3C = a1;
    self->f40 = -1;
    func_001837E0(self, 0x17, 0, 0);
    if (self->f68 != 0) {
        func_0016E0F0(4);
        func_001DDA20(self->f14);
    }
}


void* func_0017CFC8(void* self, s32 b)
{
    return func_0017CF38(self, 0, b, 1);
}


void* func_0017CFF0(void* self, s32 b)
{
    return func_0017CF38(self, 1, b, 1);
}


void* func_0017D018(void* self, s32 b)
{
    return func_0017CF38(self, 10, b, 1);
}


void* func_0017D078(void* self, s32 value)
{
    return func_0017CF38(self, 3, value, 1);
}


void* func_0017D0D8(void* self, s32 value, s32 c)
{
    return func_0017CF38(self, 9, value, c);
}


struct Obj_17D100 {
    u8 pad0[0xC];
    s32 fC;
    s32 f10;
};

void func_0017D100(void* self, s32 b, s32 c, s32 d, s32 e)
{
    Obj_17D100* o = (Obj_17D100*)func_0017CF38(self, 5, b, e);
    o->fC = c;
    o->f10 = d;
}


struct Obj_17D1B8 {
    u8 pad0[0xC];
    s32 fC;
};

void func_0017D1B8(void* self, s32 b, s32 c, s32 d)
{
    Obj_17D1B8* o = (Obj_17D1B8*)func_0017CF38(self, 8, b, d);
    o->fC = c;
}

struct Obj_17D0A0 { u8 pad0[0xC]; f32 f0C; };

void func_0017D0A0(void* self, s32 a, f32 value)
{
    Obj_17D0A0* o = (Obj_17D0A0*)func_0017CF38(self, 4, a, 0);
    o->f0C = value;
}

struct Obj_17D180 { u8 pad0[0xC]; f32 f0C; };

void func_0017D180(void* self, s32 b, s32 c, f32 value)
{
    Obj_17D180* o = (Obj_17D180*)func_0017CF38(self, 7, b, c);
    o->f0C = value;
}

struct Obj_17D1E8 { u8 pad0[0xC]; f32 f0C; };

void func_0017D1E8(void* self, f32 value)
{
    Obj_17D1E8* o = (Obj_17D1E8*)func_0017CF38(self, 11, -1, 1);
    o->f0C = value;
}

struct Pool_17CF38 { u8 pad[0x34]; s32 count; u8* base; };

extern u8 D_002BE478[];
void func_001F5C0C(void* p, s32 zero, s32 size);

void* func_0017CF38(Pool_17CF38* pool, s32 a, s32 b, s32 c)
{
    if (pool->count >= 0x80) {
        return D_002BE478;
    }
    s32 n = pool->count;
    u8* e = pool->base + n * 0x14;
    pool->count = n + 1;
    func_001F5C0C(e, 0, 0x14);
    s32* f = (s32*)e;
    f[0] = a;
    f[1] = b;
    f[2] = c;
    return e;
}
