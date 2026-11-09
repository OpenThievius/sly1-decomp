// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1163/1196 (97.2%), checked 2026-11-08
// BYTES 0/0, checked 2026-11-08
// NEAR (2026-11-08, worker night-large1): the agent's step (an animation's motion, the turn toward
// its heading, a spline to a time, or the turning collider's step), all but 11 lines retail's. In
// the first branch retail loads the heading matrix's row 0 before the vdiv and stores dt's weight
// after it (the weight's register lives on, so the quotient takes the sum's): row 0 is read as a
// struct member there and rows 1 and 2 through a pointer (they wait for both stores), which
// Vu0::Rotate's three pointer reads do not give; rows read as Vec values move all three up.
// Vec values for the sum and the weight leave it. The quadword product is an inline helper:
// called directly, the compiler keeps &q in a callee-saved register across the calls.
// Still differs (2026-11-08, night-close5): row 0 read as a Vec member inside a local Rotate (the alias rule for a varying struct) leaves the same 11 lines.
// Still differs (2026-11-08, w5-1C75B0, docs/TOOLCHAIN.md "A base register's pointer flag"): row 0 is
// at self + 0x660 (a pointer parameter's base, which no frame store aliases) and rows 1 and 2 go
// through Rotate's unflagged address pseudo (no base: they wait for both frame stores), so dt's
// slot store inherits their priority and sched1 issues it before row 0; without the slot the
// branch is retail's order exactly. Only a MEM_SCALAR_P slot (with rows MEM_IN_STRUCT_P) would
// separate it from the rows while v's store still holds them; no plausible C++ gives one.
#include "common.h"
#include "shapes.h"
#include "vu0.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"
#include "item_keeper.h"
#include "flag_table.h"
#include "node_query.h"
#include "c62.h"
#include "animation.h"
#include "attachment.h"
#include "c8b.h"
#include "vu0.h"

extern f32 g_gameTime[];

// A quadratic in t (c[0] + t * (c[1] + t * c[2])) on 16 bytes, as in hit_count_collider: the file's
// .data starts on 16 (0x274C18 to 0x274C20 is padding after the previous file's), and 0x274C54
// to 0x274C5F is the quadratic's own.
f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);
void* ResolveAgentClip(Agent* self, void* arg);
void* ResolveAgentClip(Agent* self, s32 arg);

struct __attribute__((aligned(16))) PaddedQuadratic { f32 c[3]; };

// The file's .data, in retail's order; its assembly reads the quadratics.
s32 D_00274C20[4] = { 2, 0x195, 0x87C, 0 };
s32 D_00274C30[8] = { 2, 0x194, 0x750, 6, 0x50, 0x734, 0, 0 };
PaddedQuadratic D_00274C50 = { { 1.0f, -1.0f, 0.0f } };
PaddedQuadratic D_00274C60 = { { 0.0f, 0.0f, 1.0f } };
PaddedQuadratic D_00274C70 = { { 0.0f, 15.0f, 1.5f } };
PaddedQuadratic D_00274C80 = { { 0.0f, 2.5f, 0.25f } };
float D_00274C90 = 40.0f;
float D_00274C94 = 50.0f;
float D_00274C98[2] = {0.5f, 0.0f};
PaddedQuadratic D_00274CA0 = { { 1.0f, -0.00100000005f, 0.0f } };
PaddedQuadratic D_00274CB0 = { { 0.25f, 1.0f, 0.0f } };
PaddedQuadratic D_00274CC0 = { { 0.0f, 0.00499999989f, 0.0f } };
float D_00274CD0[2] = {0.0f, 1.0f};
float D_00274CD8[2] = {1.0f, 0.0f};
PaddedQuadratic D_00274CE0 = { { 0.0f, 0.00499999989f, 0.0f } };
float D_00274CF0 = 0.349999994f;
f32 D_00274CF4 = 0.85f;
f32 D_00274CF8[1] = { 0 };
float D_00274CFC = 0.25f;
float D_00274D00 = 700.0f;
float D_00274D04 = 1200.0f;
f32 D_00274D08[2] = { 0.0f, 4.0f };
f32 D_00274D10[2] = { 0.0f, 1.5f };
f32 D_00274D18[2] = { 0.0f, 0.3f };
float D_00274D20[2] = {700.0f, 0.0f};
float D_00274D28[2] = {-0.200000003f, 0.200000003f};
PaddedQuadratic D_00274D30 = { { 0.800000012f, 1.20000005f, 0.0f } };

extern u8 g_flagTable[];
void InitTurningCollider(TurningCollider* self);
s32 TakeFlagTableIndex(FlagTable* p);
void SetSwitchedColliderEnabled(Agent* self, s32 a);

#define F(T, o) (*(T*)((u8*)self + (o)))

extern f32 g_gameClock[];
extern f32 g_unitRange[];

static inline f32 Limit(f32 g, f32 lo, f32 hi)
{
    if (g < lo) return lo;
    if (hi < g) return hi;
    return g;
}

// g held to the unit range (g_unitRange), the result a value of its own.
static inline f32 LimitToUnitRange(f32 g)
{
    f32* range = g_unitRange;
    f32 lo = range[0];
    f32 hi = range[1];
    f32 r;
    if (g < lo) {
        r = lo;
    } else if (hi < g) {
        r = hi;
    } else {
        r = g;
    }
    return r;
}

typedef int Quadword128 __attribute__((mode(TI)));
void StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(void* dst, Quadword128 v);

// k times the vector at p, into dst (the quadword helpers' product).
static inline void StoreScaledQuadword(Vec02* dst, f32 k, u8* p)
{
    Quadword128 t;
    StoreFloatAsQuadword(&t, k);
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword(&u, p);
    StoreQuadword(dst, ScaleQuadword(tv, u));
}
f32 Arccosine(f32 x);
void AddColliderForce(Agent* self, Vec02* v);
void TurnColliderTowardRotation(Agent* self, Mat02* m, void* rate, f32 dt);
void SteerColliderTowardPosition(Agent* self, s32 a, s32 b, Vec02* target, s32 c, f32 dt);
void SteerColliderTowardRotation(Agent* self, Mat02* m, void* a, const Vec02* b, void* c, f32 dt);
void StepTurningCollider(Agent* self, f32 dt);
void* CopyBytes(void* dst, void* src, s32 n);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
void func_00130540(Vec02* a, Vec02* b, Vec02* c, Vec02* d, Vec02* outA, Vec02* outB, s32 e, f32 t, f32 u, f32 w);
typedef void (*AgentMotionFn)(void* self, Agent* agent, s32 a, s32 b, Vec02* out, f32 t, f32 u);

void func_001C75B0(Agent* self, f32 dt)
{
    if (F(s32, 0xB78) != 0) {
        Vec02 motion;
        Vec02 v;
        u8* ap = (u8*)self->f7E0;
        u8* src = *(u8**)(*(u8**)(*(u8**)(ap + 8) + 0x9C) + 4);
        (**(AgentMotionFn**)src)(src, self, 0, 0, &motion, *(f32*)(ap + 0x14), *(f32*)(ap + 0x18));
        Vu0::Q(v) = Vu0::DivX(Vu0::Add(Vu0::Vec::Of(motion), Vu0::Vec::Of(self->v640)), Vu0::Vec::Scalar(dt)).q;
        Vu0::Q(v) = Vu0::Rotate(self->m660, Vu0::Q(v));
        AddColliderForce(self, &v);
        TurnColliderTowardRotation(self, &self->m660, &self->f6E0, g_gameClock[2]);
    } else if (self->fB1C != 0) {
        Vec02 v;
        Mat02 m2;
        Mat02 m;
        f32 a = __builtin_fabsf(Arccosine(Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->rot.r[0]), Vu0::Q(self->m660.r[0])))));
        f32 k = LimitToUnitRange(D_00274C50.c[0] + a * (D_00274C50.c[1] + a * D_00274C50.c[2]));
        if (self->f724 == 12) {
            f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->vA50), Vu0::Q(self->v140))));
            f32* q = &F(f32, 0xB30);
            k = k * LimitToUnitRange(q[0] + d * (q[1] + d * q[2]));
        }
        u128 s = Vu0::Scalar(-k);
        Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->m110.r[0]), s);
        Vu0::Q(m.r[1]) = Vu0::MulX(Vu0::Q(self->m110.r[1]), s);
        Vu0::Q(m.r[2]) = Vu0::MulX(Vu0::Q(self->m110.r[2]), s);
        CopyBytes(&m2, &m, 0x30);
        Vu0::Q(v) = Vu0::Rotate(m2, Vu0::Q(self->v640));
        SteerColliderTowardPosition(self, 0, 0, &v, F(s32, 0x210), dt);
        TurnColliderTowardRotation(self, &self->m660, &self->f6E0, g_gameClock[2]);
    } else if (g_gameTime[0] < F(f32, 0xBA4)) {
        Vec02 p;
        Vec02 w;
        Vec02 v;
        f32 left = F(f32, 0xBA4) - g_gameTime[0];
        func_00130540(&self->pos, &self->v150, &F(Vec02, 0xBB0), &F(Vec02, 0xBC0), &p, &w, 0, left, left <? dt, 1.0f);
        Vu0::Q(v) = Vu0::DivX(Vu0::Sub(Vu0::Q(w), Vu0::Q(self->v150)), Vu0::Scalar(dt));
        ClampVectorLength(&v, &v, 20000.0f);
        AddColliderForce(self, &v);
        TurnColliderTowardRotation(self, &self->m660, &self->f6E0, dt);
    } else if (self->f724 == 16 && self->fA6C != 0) {
        Vec02 q2;
        Vec02 q;
        f32 x;
        u8* ap = (u8*)self->f7E0;
        if (ap != 0) {
            x = *(f32*)(ap + 0x14) / *(f32*)(*(u8**)(ap + 8) + 0x34);
        } else {
            x = 1.0f;
        }
        f32 k = LimitToUnitRange(D_00274C60.c[0] + x * (D_00274C60.c[1] + x * D_00274C60.c[2]));
        StoreScaledQuadword(&q, k, (u8*)&D_00274C70);
        StoreScaledQuadword(&q2, k, (u8*)&D_00274C80);
        SteerColliderTowardRotation(self, &self->m660, &q, &D_00248D30, &q2, dt);
        AddColliderForce(self, &self->gravity);
    } else {
        StepTurningCollider(self, dt);
    }
}
