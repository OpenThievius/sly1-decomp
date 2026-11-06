// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "on_off_object.h"
#include "game_clock.h"

// The file's .rodata, in retail's order: the constants and jump tables only its assembly reads.
extern const f32 D_0024DAA0 = -3.40282347e+38f;
INCLUDE_RODATA(jtbl_0024DAB0);
extern const f32 D_0024DAD0 = -3.40282347e+38f;
INCLUDE_RODATA(D_0024DAD4);
INCLUDE_RODATA(jtbl_0024DAE0);
INCLUDE_RODATA(jtbl_0024DB00);

struct __attribute__((aligned(16))) Blob_274E60_1D1260 { f32 f[36]; };

// The file's .data, in retail's order.
float D_00274E00 = 150.0f;
float D_00274E04 = 50.0f;
float D_00274E08 = 250.0f;
float D_00274E0C = 1000.0f;
float D_00274E10 = 1.25f;
float D_00274E14 = 2.0f;
float D_00274E18 = 250.0f;
float D_00274E1C = 0.200000003f;
float D_00274E20 = 2500.0f;
float D_00274E24 = -250.0f;
f32 D_00274E28 = 0;
f32 D_00274E2C = 0;
float D_00274E30 = 1250.0f;
float D_00274E34 = 500.0f;
float D_00274E38 = 500.0f;
f32 D_00274E3C = 1e+03f;
float D_00274E40 = 100.0f;
float D_00274E44 = 100.0f;
float D_00274E48 = 0.300000012f;
float D_00274E4C = 25.0f;
float D_00274E50 = 1.5f;
float D_00274E54 = 0.25f;
float D_00274E58 = 0.5f;
float D_00274E5C = 0.200000003f;
Blob_274E60_1D1260 D_00274E60 = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      -225.0f, 1.0f, 0.0f, 0.0f, 20.0f, 1.0f, 0.0f, 0.0f,
      -3.40282347e+38f, 3.40282347e+38f, -3.40282347e+38f, 3.40282347e+38f, -3.40282347e+38f, 3.40282347e+38f,
      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }
};
float D_00274EF0[3] = {2500.0f, 0.0f, 1.0f};

ASM_FUNC(func_001CDFB8);

ASM_FUNC(func_001CE590);

ASM_FUNC(func_001CE800);

struct Ref_001CE9E8 { u8 pad0[0x18]; void* p18; };
struct Obj_001CE9E8 { void* p0; Ref_001CE9E8* p4; u8 pad1[0x10 - 8]; };
struct Frame_001CE9E8 { u8 vecA[0x10]; u8 vecB[0x10]; f32 result; };

void func_001CE800(void* a0, void* a1, void* a2, void* a3);
void func_001CE590(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 func_001CE9E8(Obj_001CE9E8* self)
{
    Frame_001CE9E8 f;
    func_001CE800(self->p0, self->p4, f.vecA, f.vecB);
    func_001CE590(self->p0, (u8*)self + 0x10, self->p4->p18, f.vecA, f.vecB, 0, &f.result, 0, 0);
    return f.result;
}

struct Ref_001CEA58 { u8 pad0[0x18]; void* p18; };
struct Obj_001CEA58 { void* p0; Ref_001CEA58* p4; u8 pad1[0x10 - 8]; };
struct Frame_001CEA58 { u8 vecA[0x10]; f32 result; };

void func_0016A240(void* a0, void* a1, s32 a2);
void func_001CE590(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 func_001CEA58(Obj_001CEA58* self)
{
    Frame_001CEA58 f;
    func_0016A240(self->p4, f.vecA, 0);
    func_001CE590(self->p0, (u8*)self + 0x10, self->p4->p18, f.vecA, 0, 0, &f.result, 0, 0);
    return f.result;
}

void func_00169E20(void* a0, void* a1, s32 a2);
void func_001CE590(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 func_001CEAB8(Obj_001CEA58* self)
{
    Frame_001CEA58 f;
    func_00169E20(self->p4, f.vecA, 0);
    func_001CE590(self->p0, (u8*)self + 0x10, self->p4->p18, f.vecA, 0, 0, &f.result, 0, 0);
    return f.result;
}

ASM_FUNC(func_001CEB18);

// func_001CEB18 also takes a float in $f12 (it reads $f12 at entry); this
// function passes its own float parameter straight through.
struct Obj_1CEDF8 { s32 a; s32 b; s32 pad[2]; s32 c[4]; };
void func_001CEB18(f32 t, s32 a, s32 b, s32* c, f32* out, s32 d, s32 e);

f32 func_001CEDF8(Obj_1CEDF8* o, f32 t)
{
    f32 out;
    func_001CEB18(t, o->a, o->b, o->c, &out, 0, 0);
    return out;
}

typedef void (*VFn_1CEE30)(void* self, void* out, s32 x);

struct Obj_1CEE30 {
    VFn_1CEE30* vtbl;
};

struct Node_1CEE30 {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1C[0x34 - 0x1C];
    Obj_1CEE30* f34;
};

struct Self_1CEE30 {
    s32 f0;
    Node_1CEE30* node;
};

struct __attribute__((aligned(16))) Quad_1CEE30 {
    s32 a, b, c, d;
};

struct Locals_1CEE30 {
    Quad_1CEE30 a;
    s32 b[2];
    u8 pad18[8];
    Quad_1CEE30 c;
    f32 out;
};

void func_001EB168(f32 f12, f32 f13, f32 f14, f32 f15, void* fn, void* b, s32 c, void* out);

f32 func_001CEE30(Self_1CEE30* self)
{
    Locals_1CEE30 l;
    Node_1CEE30* n = self->node;
    Obj_1CEE30* o = n->f34;
    if (o->vtbl[2] != 0) {
        o->vtbl[2](o, &l.a, 0);
    }
    f32 q = 0.25f;
    l.b[0] = self->f0;
    l.b[1] = n->f18;
    l.c = l.a;
    
    func_001EB168(0.5f, q, q, 3.0f, (void*)func_001CEDF8, l.b, 0, &l.out);
    return l.out;
}

ASM_FUNC(func_001CEEC8);

struct Obj_001CF138 { u8 pad0[0x2BDC]; s32 key; };

f32 func_001CF138(Obj_001CF138* self, s32 id, f32 a, f32 b)
{
    f32 r = a + b;
    if (id == self->key) {
        r = r + D_00274E3C;
    }
    return r;
}

ASM_FUNC(func_001CF158);

ASM_FUNC(func_001CFFD0);

ASM_FUNC(func_001D0B20);

ASM_FUNC(func_001D0C78);

ASM_FUNC(func_001D0F20);

void func_001861E8(void* a, s32 b);

void func_001D1200(Player* self, s32 n)
{
    if (n == self->f2684) {
        return;
    }
    self->f2684 = n;
    self->f2688 = g_gameClock.time;
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
        if (v == (s32)self->f2678) {
            self->f268C = 2;
        } else {
            self->f268C = 0;
        }
    }
}

void func_001E2840(OnOffObject* o, s32 v);

void func_001D1260(Player* self)
{
    OnOffObject* o = self->f2678;
    o->i414 = 5;
    o->f2D4 = 0;
    o->f2DC = 0;
    o->obj = 0;
    o->block2F0 = *(Block63*)&D_00274E60;
    o->f418 = 1;
    o->f388 = 3;
    o->f380 = 0;
    o->f384 = 0;
    o->f41C = 0;
    o->f390 = 0;
    o->f3A0 = 0;
    SetOnOffObjectForcedState(o, 0);
}

ASM_FUNC(func_001D12F0);

struct Obj_1D1478 { u8 pad[0x50]; s32 f50; };
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
s32 func_001D1478(Player* self)
{
    void* arr[64];
    s32 n = GatherObjectsById(self->world, 5, 0x89, 0, 0x40, arr);
    for (s32 i = 0; i < n; i++) {
        Obj_1D1478* o = (Obj_1D1478*)arr[i];
        s32 v = o->f50;
        if (v < 3) {
            if (v > 0) {
                return 0;
            }
        }
    }
    return 1;
}
