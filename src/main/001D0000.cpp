// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_D27C0 {
    u8 pad0[0x14];
    void* owner;
    u8 pad1[0x2718 - 0x18];
    s32 state;
};

void func_001DDA20(void* a);
void func_001DDB58(void* a);
void func_001DDA50(void* a);
void func_001DDBB8(void* a);

void func_001D27C0(Obj_D27C0* a0, s32 a1)
{
    if (a0->state != a1) {
        if (a0->state == -1) {
            func_001DDA20(a0->owner);
            func_001DDB58(a0->owner);
        }
        a0->state = a1;
        if (a1 == -1) {
            func_001DDA50(a0->owner);
            func_001DDBB8(a0->owner);
        }
    }
}

struct Ref_D3500;

struct Node_D3500 {
    Ref_D3500* ref;
    u8 pad0[0xC - 4];
    s32 flags;
};

struct Ref_D3500 {
    s32* vtbl;
    u8 pad0[0x18 - 4];
    Ref_D3500* f18;
    u8 pad1[0x50 - 0x1C];
    s32 f50;
};

struct Self_D3500 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x554 - 0x18];
    s32 f554;
};

extern s32 D_00262E10;

void* func_001BC320(Self_D3500* a);
void func_001D32D8(Self_D3500* a, Ref_D3500* b, s32 c);
void func_001861E8(void* a, s32 b);

void* func_001D3500(Self_D3500* a0, Node_D3500* a1)
{
    void* r = func_001BC320(a0);
    if (r != 0 && (a1->flags & 0x20)) {
        Ref_D3500* a2 = a1->ref;
        s32 v1;
        if (a2->vtbl[2] & 1) {
            v1 = a2->f50;
        } else {
            v1 = a2->f18->f50;
        }
        func_001D32D8(a0, a1->ref, (v1 ^ D_00262E10) == 0);
        func_001861E8(a0->f14, a0->f554);
        a0->f554 = 0;
    }
    return r;
}

struct Thing_1D1200 {
    u8 pad0[0x2674];
    s32 f2674;
    s32 f2678;
    u8 pad1[0x2684 - 0x267C];
    s32 f2684;
    f32 f2688;
    s32 f268C;
    u8 pad2[0x26A0 - 0x2690];
    s32 f26A0;
};

extern f32 D_0026185C;

void func_001D1200(Thing_1D1200* self, s32 n)
{
    if (n == self->f2684) {
        return;
    }
    self->f2684 = n;
    self->f2688 = D_0026185C;
    self->f26A0 = 0;
    if (n <= 0) {
        return;
    }
    if (n >= 3) {
        if (n == 3) {
            self->f268C = 1;
        }
        return;
    }
    {
        s32 v = self->f2674;
        if (v == self->f2678) {
            self->f268C = 2;
        } else {
            self->f268C = 0;
        }
    }
}

struct __attribute__((aligned(16))) Blob_274E60_1D1260 { u8 bytes[0x90]; };

struct __attribute__((aligned(16))) Obj_1D1260 {
    u8 p0[0x2D4];
    s32 f2D4;
    u8 p1[4];
    s32 f2DC;
    u8 p2[4];
    s32 f2E4;
    u8 p3[0x2F0 - 0x2E8];
    Blob_274E60_1D1260 blob;
    s32 f380;
    s32 f384;
    s32 f388;
    u8 p4[0x390 - 0x38C];
    s32 f390;
    u8 p5[0x3A0 - 0x394];
    s32 f3A0;
    u8 p6[0x414 - 0x3A4];
    s32 f414;
    s32 f418;
    s32 f41C;
};

struct Thing_1D1260 {
    u8 pad0[0x2678];
    Obj_1D1260* f2678;
};

extern Blob_274E60_1D1260 D_00274E60;

void func_001E2840(Obj_1D1260* o, s32 v);

void func_001D1260(Thing_1D1260* self)
{
    Obj_1D1260* o = self->f2678;
    o->f414 = 5;
    o->f2D4 = 0;
    o->f2DC = 0;
    o->f2E4 = 0;
    o->blob = D_00274E60;
    o->f418 = 1;
    o->f388 = 3;
    o->f380 = 0;
    o->f384 = 0;
    o->f41C = 0;
    o->f390 = 0;
    o->f3A0 = 0;
    func_001E2840(o, 0);
}
