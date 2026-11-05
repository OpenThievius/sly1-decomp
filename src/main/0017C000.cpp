// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "point_object.h"
#include "c8f.h"
#include "c05.h"
#include "c03.h"
#include "globals.h"
#include "shapes.h"

struct Comp_17CE80 {
    u8 pad0[0x2740];
    s32 f2740;
};

void func_0017BC20(void* self, s32 n);
void func_0017BB78(void* self, s32 n);
void func_0012E760(void* p);
void func_00142ED0(f32 x);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_0016E118(s32 n);
void func_001DDA50(void* p);

void func_0017CE80(C8F* self)
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
        ((Comp_17CE80*)self->f3C)->f2740 = 0;
        self->f3C = 0;
        func_001837E0(self, 25, 0, 0);
        if (self->flag68 != 0) {
            func_0016E118(4);
            func_001DDA50(self->world);
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

void func_00152440(void* p);

void func_0017FD70(void)
{
    func_00152440(&D_00264088);
}

void func_00152438(void* self, s32 value);

void func_0017FD48(void)
{
    func_00152438(&D_00264088, 0x50);
}

void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_0017FD90(C80* self)
{
    func_00182D48(self);
    func_00152470(&D_00264088, self);
}

s32 func_0017D220(void* self)
{
    return (s32)func_0017CF38(self, 0xC, -1, 0);
}


void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

void func_0017FDC8(C80* self)
{
    func_00182ED0(self);
    func_00152600(&D_00264088, self);
}

void func_0017C660(C8F* self);

s32 func_0017CDA8(C8F* self)
{
    func_0017C660(self);
    if (self->f34 > 0) {
        return self->f40 < self->f34;
    }
    return 0;
}

void func_0017CE80(C8F* self);

void func_0017CDE0(C8F* self)
{
    if (self->f3C != 0) {
        func_0017CE80(self);
        self->f34 = 0;
    } else {
        self->f34 = 0;
    }
    self->f40 = 0;
}

void func_001837E0(void* self, s32 kind, s32 a, s32 b);
void func_0016E0F0(s32 a);
void func_001DDA20(void* a);

struct Other_17CE20 {
    u8 pad[0x2740];
    void* f2740;
};

void func_0017CE20(void* a0, void* a1)
{
    C8F* self = (C8F*)a0;
    ((Other_17CE20*)a1)->f2740 = self;
    self->f3C = a1;
    self->f40 = -1;
    func_001837E0(self, 0x17, 0, 0);
    if (self->flag68 != 0) {
        func_0016E0F0(4);
        func_001DDA20(self->world);
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

extern u8 D_002BE478[];
void func_001F5C0C(void* p, s32 zero, s32 size);

void* func_0017CF38(C8F* pool, s32 a, s32 b, s32 c)
{
    if (pool->f34 >= 0x80) {
        return D_002BE478;
    }
    s32 n = pool->f34;
    u8* e = (u8*)pool->buffer + n * 0x14;
    pool->f34 = n + 1;
    func_001F5C0C(e, 0, 0x14);
    s32* f = (s32*)e;
    f[0] = a;
    f[1] = b;
    f[2] = c;
    return e;
}

s32 func_0017E6D0(C07* self)
{
    s32 r;
    if (0.0f < self->f634) {
        if (self->f900 != 0) {
            r = 1;
        } else {
            r = self->fA10 ? 5 : 0;
        }
    } else r = 0;
    return r;
}

struct Node_17DE88 { C03* f0; Node_17DE88* f4; u8 pad[4]; C03* fC; };
struct List_17DE88 { Node_17DE88* head; };
struct Obj_17DE88 { u8 pad[0x480]; List_17DE88* f480; };
struct Ctx_17DE88 { u8 pad[1]; };
struct Mat_17DE88 { f32 m[16]; };

void func_001ED780(Quad16* q, void* out, const Vec02* a, const Vec02* b);
void func_00188B08(Ctx_17DE88* a, Quad16* b, void* out);
void func_00188700(Mat_17DE88* a, f32 w, void* b, void* c);
s32 func_00141C28(C03* self, void* a1, void* a2, s32 a3, void* a4);
struct Vec_263EC0 { f32 x, y, z, w; };
extern Vec_263EC0 D_00263EC0[22];

s32 func_0017DE88(Obj_17DE88* self, Ctx_17DE88* ctx, Quad16* src)
{
    u8 buf[0x100] __attribute__((aligned(16)));
    Quad16& q = *(Quad16*)buf;
    q = *src;
    s32 hits = 0;
    func_001ED780(&q, buf + 0x10, &D_00248D20, &D_00248D20);
    func_00188B08(ctx, &q, buf + 0x30);
    for (s32 i = 0; (u32)i < 0x16; i += 2) {
        func_00188700((Mat_17DE88*)(buf + 0x30), 1.0f, &D_00263EC0[i], buf + 0x70);
        func_00188700((Mat_17DE88*)(buf + 0x30), 1.0f, &D_00263EC0[i + 1], buf + 0x80);
        Node_17DE88* n = self->f480->head;
        while (n) {
            C03* a = n->fC;
            if (!(a->flags538 & 0x40000000000ULL)) {
                C03* c = (C03*)a->parts.head;
                while (c) {
                    if (!(c->flags538 & 0x80000000000ULL)) {
                        if (func_00141C28(c, buf + 0x70, buf + 0x80, 1, buf + 0x90) > 0) {
                            if (i < 4) return 0;
                            if (*(f32*)(buf + 0xD0) == 0.0f) return 0;
                            if (0.7f < *(f32*)(buf + 0xB8)) hits++;
                        }
                    }
                    c = (C03*)c->link2E4.next;
                }
            }
            n = n->f4;
        }
    }
    return hits >= 2;
}

struct Entry_17C660 { u8 pad[8]; s32 state; u8 tail[8]; };
void func_0017BCD0(C8F* self);
s32 func_0017C428(C8F* self, void* item);

void func_0017C660(C8F* self)
{
    if (self->f40 < 0 && self->f34 > 0)
        func_0017BCD0(self);
    while (self->f40 < self->f34) {
        Entry_17C660* entry = &((Entry_17C660*)self->buffer)[self->f40];
        if (entry->state == 0 && !func_0017C428(self, entry))
            break;
        func_0017BCD0(self);
    }
    if (self->f48 && func_0017C428(self, self->f48))
        self->f48 = 0;
}

Vec_263EC0 D_00263EC0[22] = {
    { 50.0f, 0.0f, 75.0f, 0.0f },
    { 50.0f, 0.0f, -150.0f, 0.0f },
    { 50.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, -50.0f, 0.0f },
    { -57.96f, 15.53f, 75.0f, 0.0f },
    { -57.96f, 15.53f, -50.0f, 0.0f },
    { -51.96f, 30.0f, 75.0f, 0.0f },
    { -51.96f, 30.0f, -50.0f, 0.0f },
    { -42.43f, 42.43f, 75.0f, 0.0f },
    { -42.43f, 42.43f, -50.0f, 0.0f },
    { -30.0f, 51.96f, 75.0f, 0.0f },
    { -30.0f, 51.96f, -50.0f, 0.0f },
    { -57.96f, -15.53f, 75.0f, 0.0f },
    { -57.96f, -15.53f, -50.0f, 0.0f },
    { -51.96f, -30.0f, 75.0f, 0.0f },
    { -51.96f, -30.0f, -50.0f, 0.0f },
    { -42.43f, -42.43f, 75.0f, 0.0f },
    { -42.43f, -42.43f, -50.0f, 0.0f },
    { -30.0f, -51.96f, 75.0f, 0.0f },
    { -30.0f, -51.96f, -50.0f, 0.0f },
};
