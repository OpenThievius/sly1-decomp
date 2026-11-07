// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"

struct Ent_274AD8 { s32 a; s32 b; s32 c; };
struct __attribute__((aligned(16))) Quad_1C4458 { s32 a; s32 b; s32 c; s32 d; };

// The file's .rodata: the constants only its assembly reads.
extern const f32 D_0024D588 = 3.40282347e+38f;
extern const f32 D_0024D58C = 3.40282347e+38f;
extern const f32 D_0024D590 = 3.40282347e+38f;
extern const f32 D_0024D594 = 3.40282347e+38f;

// The file's .data, in retail's order.
f32 D_00274AD0[2] = { 1.0f, -1.0f };
Ent_274AD8 D_00274AD8[6] = { {6, 0x36, 0x61C}, {6, 0x35, 0x618}, {6, 0x37, 0x628}, {6, 0x3A, 0x62C}, {6, 0x38, 0x620}, {6, 0x3B, 0x624} };
f32 D_00274B20 = 0.5f;
Quad_1C4458 D_00274B30 = { 0x3F800000, (s32)0xBF800000, 0, 0 };
s32 D_00274B40[3] = { 0x453B8000, 0, 0x40000000 };
s32 D_00274B50[3] = { 0x453B8000, 0, 0x3E800000 };
f32 D_00274B5C = 0;
f32 D_00274B60[1] = { 0.1f };
f32 D_00274B64 = -0.033f;
f32 D_00274B68[3] = { 300.0f, 0.0f, 0.25f };
f32 D_00274B74 = 1.5f;
f32 D_00274B78 = 2.0f;
f32 D_00274B7C = 0.0333333351f;
f32 D_00274B80[3] = { 25.0f, 0.0f, 0.25f };

struct __attribute__((packed)) Pack8_1C4458 { u64 v; };
struct Blk12_1C4458 { Pack8_1C4458 a; s32 b; };

void func_001921A8(void* self);
void func_001C5E50(void* self, f32 x);

void func_001C4458(TurningCollider* self)
{
    InitSwitchedCollider(self);
    self->f700 = 1.0f;
    self->f360 = D_00274B20;
    ScaleTurningColliderRamp(self, 1.0f);
    (*(Quad_1C4458*)&self->v6F0) = D_00274B30;
    *(Blk12_1C4458*)((u8*)self + 0x710) = *(Blk12_1C4458*)D_00274B40;
    *(Blk12_1C4458*)((u8*)self + 0x704) = *(Blk12_1C4458*)D_00274B50;
}

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* table);
void func_001C4578(void* self, s32 a1);

void func_001C44F0(TurningCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 6, g_turningColliderLinks);
    func_001C4578(self, 1);
    if (self->f628 == 0) {
        self->f610 = self->f620;
    } else {
        self->f610 = self->f628;
    }
    if (self->f62C == 0) {
        self->f614 = self->f624;
    } else {
        self->f614 = self->f62C;
    }
    Mat02* dst = &self->m660;
    *dst = g_identityMatrix;
}

struct Sub_1C4578 { u8 pad[0x98]; s32 f98; u8 pad2[0xB0 - 0x9C]; s32 fB0; };
struct Holder_1C4578 { u8 pad[0x224]; Sub_1C4578* f224; };

void func_001C4578(TurningCollider* self, s32 a1)
{
    Holder_1C4578* h = (Holder_1C4578*)self->f61C;
    if (h != 0) {
        Sub_1C4578* s = h->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else s->f98 &= ~2;
        }
    }
    Holder_1C4578* v = (Holder_1C4578*)self->f618;
    if (v != 0) {
        Sub_1C4578* s = v->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else ((Holder_1C4578*)self->f61C)->f224->f98 &= ~2;
        }
    }
}

ASM_FUNC(func_001C4618);

struct __attribute__((aligned(16))) Ent_1C4790 { u8 pad0[0x40]; f32 f40; u8 pad1[0x70 - 0x44]; };
struct Obj_1C4790 { u8 pad0[0x50]; s32 f50; u8 pad1[0xD0 - 0x54]; f32 fD0; };
s32 func_00141C90(void* self, void* a1, void* a2, void* a3, s32 a4, void* a5);

void func_001C4790(void* unused, void* a1, void* a2, Obj_1C4790* self)
{
    Ent_1C4790 ents[2];
    s32 n;
    s32 idx;
    if (self->f50 == 0) return;
    n = CollectColliderSpansInTree(a1, a2, (u8*)self + 0x70, (u8*)self + 0x60, 2, ents);
    idx = 0;
    if (n > 0) {
        if (ents[0].f40 == 0.0f) idx = 1;
    }
    if (!(idx < n)) return;
    if (ents[idx].f40 < self->fD0) {
        *(Ent_1C4790*)((u8*)self + 0x90) = ents[idx];
    }
}

ASM_FUNC(func_001C4848);

void func_001B93D8(void);

void func_001C49C8(void)
{
    DrawCollider();
}

ASM_FUNC(func_001C49E8);

extern f32 D_0026185C[];
extern s32 D_00605548;
f32 func_001EAFE0(f32 x, f32 y);
s32 func_001EAA70(s32 a, s32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, u8* a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_001C0EC0();

void func_001C4A80(Player* self, f32* p, f32 f) {
    f32 old = self->f6C4;
    f32 ang;
    self->f6C4 = f;
    if (g_gameTime[0] - self->f6C8 < D_00274B60[0]) return;
    if (WrapModulo(f - p[0], 1.0f) < 0.5f && 0.5f < WrapModulo(old - p[0], 1.0f)) {
        ang = p[2];
    } else if (WrapModulo(self->f6C4 - p[1], 1.0f) < 0.5f && 0.5f < WrapModulo(old - p[1], 1.0f)) {
        ang = p[3];
    } else {
        return;
    }
    s32 idx = RandomIntInRange(0x47, 0x4A);
    if (idx == D_00605548) {
        s32 x = idx - 0x46;
        idx = x % 4 + 0x47;
    }
    D_00605548 = idx;
    StartSoundEffect(idx, 0, 0, (u8*)&self->v140, 0, 0, 1000.0f, 200.0f, ang, 0.0f, 0.0f);
    PlaySoundWithWanderingPitch();
}

ASM_FUNC(func_001C4C20);

ASM_FUNC(func_001C4D60);


void func_00192B58(void* self);
void func_001C4C20(void* self);

void func_001C4ED0(TurningCollider* self)
{
    UpdateSwitchedCollider(self);
    func_001C4C20(self);
}

s32 func_001C4F00(void) { return 3; }

void func_001BC828(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_001C4F08(TurningCollider* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 old = self->mode470;
    self->mode470 = self->desc06()->m55(self);
    ComputeColliderImpulseResponse(self, a1, a2, a3, a4, a5);
    self->mode470 = old;
}

struct Vec2_1C4FA0 { f32 x; f32 y; };
typedef void (*VFn_1C4FA0)(void* self);
void func_001B97E0(void* self, void* src);
f32 func_00205778(f32 a, f32 b);

void func_001C4FA0(TurningCollider* self, Vec2_1C4FA0* v)
{
    SetColliderRotation(self, v);
    f32 r = ArctangentOfRatio(v->y, v->x);
    self->f638 = r;
    self->f630 = r;
    ((VFn_1C4FA0*)self->desc)[88](self);
}

ASM_FUNC(func_001C4FF8);

void func_001B9338(void* self);
void func_001C5148(void* self);

void func_001C5118(TurningCollider* self)
{
    StepCollider(self);
    func_001C5148(self);
}

ASM_FUNC(func_001C5148);

struct Arg_1C5248 { u8 pad0[0x88]; f32 f88; u8 pad1[0x9C - 0x8C]; s32 f9C; s32 fA0; s32 fA4; };

s32 func_001C5248(TurningCollider* self, Arg_1C5248* a, s32 idx)
{
    if (self->f6DC == 0) {
        return 0;
    }
    if (a->f88 * D_00274AD0[idx] < 0.7f) {
        return 0;
    }
    s32 kind = a->f9C;
    switch (kind) {
    case 1: {
        s32 r = 0;
        if (idx == 0 && a->fA0 == self->f6D4) {
            r = 1;
        }
        return r;
    }
    case 4: {
        s32 r = 0;
        if (idx == 1 && a->fA4 == self->f6D4) {
            r = 1;
        }
        return r;
    }
    case 10: {
        s32 r = 0;
        if (idx == 0) {
            r = a->fA0 == self->f6D4;
        }
        return r;
    }
    }
    return 0;
}

typedef s32 (*VFn_C5338)(void* self);
struct Out_C5338 { u8 pad[0x94]; f32 f94; s32 f98; };

void func_001C5338(TurningCollider* self, Out_C5338* out)
{
    if (((VFn_C5338*)self->desc)[0x168 / 4](self)) {
        f32 d = D_00274B74;
        out->f98 = 0;
        out->f94 = d;
    } else {
        out->f94 = 0.0f;
        out->f98 = 0;
    }
}

void func_001C53A8(void);

void func_001C5388(void)
{
    func_001C53A8();
}

void func_001C53A8(void)
{
}

void func_00188850(const Vec02* t, f32 x, void* p);

void func_001C53B0(TurningCollider* self)
{
    BuildAxisAngleMatrix(&g_unitZVector, self->f638, (u8*)self + 0x660);
}

typedef s32 (*VFn_1C53E0)(void* self);
void func_001C54D0(TurningCollider* self, void* b, s32 c);

void func_001C53E0(TurningCollider* self, void* b, s32 c)
{
    if (((VFn_1C53E0*)self->desc)[90](self)) {
        func_001C54D0(self, b, c);
    }
}

extern f32 D_00275C60[];

void func_001B89B8(TurningCollider* self);
f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);

void func_001C5438(TurningCollider* self)
{
    RecomputeColliderFrame(self);
    f32 t = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 ay = __builtin_fabsf(WrapAngle(self->f638 - t));
    f32* lim = g_unitRange;
    Vec02* p = &self->v6F0;
    f32 v = self->v6F0.x + ay * (p->y + ay * p->z);
    f32 lo = lim[0];
    f32 hi = lim[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    self->f63C = v;
}

ASM_FUNC(func_001C54D0);

ASM_FUNC(func_001C57C8);

void func_001C5C10(void* a, s32 b, s32 c, s32 d);

void func_001C5BF0(TurningCollider* a0, s32 a1, s32 unused2, s32 unused3, s32 a4, s32 a5)
{
    func_001C5C10(a0, a1, a4, a5);
}

ASM_FUNC(func_001C5C10);

f32 func_00205778(f32 a, f32 b);
f32 func_001EA728(void* p, void* out, f32 a, f32 b, f32 c);

void func_001C5D58(TurningCollider* self)
{
    Vec02 q = self->v160;
    f32 r = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    ApproachAngleWithRamp((u8*)self + 0x6E0, &q.z, r, self->f638, 0.0f);
    self->desc02()->m21(self, &q);
}

ASM_FUNC(func_001C5DB8);

struct __attribute__((packed)) Pk8_1C5E50 { u32 a; u32 b; };
struct Vec_1C5E50 { Pk8_1C5E50 xy; u32 z; };


void func_001C5E50(TurningCollider* self, f32 s)
{
    *(Vec_1C5E50*)&self->f6E0 = *(Vec_1C5E50*)D_00274B80;
    self->f6E0 *= s;
    self->f6E4 *= s;
    self->f6E8 *= 1.0f / Fpu::Sqrt(s);
}

ASM_FUNC(func_001C5EA8);
