// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 492/488, checked 2026-11-08
// NEAR: night-size4: the shape read into a variable of its own for each of the three calls (one variable across them is one pseudo the allocator keeps out of a0) gives retail's lw a0,0x34(s3) for the second and third and 4 bytes. Still: the first call's shape is in v1 (retail a0; an inline SamplePathShape and node->f34 read inline: no better). Was: identical but for the loads of node->f34, which retail makes straight into a0 (lw a0,0x34(s3)) where ours makes them into a1 and moves them, the order of the two loads of the player vector for the floor point (retail 0xE90 first), and the clamp of the dot: retail merges the three outcomes in $f0 (c.lt.s $f21,$f0 ... mov.s $f0,$f21 / mov.s $f0,$f1), ours keeps the dot in $f21. A shared ClampBetween (as func_001D0B20) gives the merge but keeps &d in s4 across the calls and adds a seventh saved register.
#include "common.h"
#include "switched_collider.h"
#include "game_clock.h"
#include "globals.h"
#include "vu0.h"

extern f32 D_00274E04;
extern f32 D_00274E1C;
typedef void (*PathShapeFn)(void* self, void* out, s32 x);
struct PathShape { PathShapeFn* vtbl; };
struct PathTarget { u8 pad0[0x18]; s32 f18; u8 pad1C[0x34 - 0x1C]; PathShape* f34; };
typedef f32 (*ShapeScalarFn)(void* self, f32 t);
typedef f32 (*ShapeLimitFn)(void* self);
void TransformPointBetweenFrames(void* frame, s32 zero, void* in, void* out);
void TransformDirectionBetweenFrames(void* frame, s32 zero, void* in, void* out);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
void ApproachValueWithRamp(Vec02* v, f32 value, f32 amount, f32 dt, f32* out);

void func_001CE800(f32 t, Player* self, PathTarget* node, Vec02* outA, Vec02* outB)
{
    Vec02 a;
    Vec02 b;
    Vec02 c;
    Vec02 d;
    Vec02 e;
    Vec02 f;
    f32 lo;
    f32 hi;
    PathShape* shape = node->f34;
    if (shape->vtbl[1] != 0) {
        shape->vtbl[1](shape, &a, (s32)&b);
    }
    TransformPointBetweenFrames((void*)node->f18, 0, &a, &c);
    TransformDirectionBetweenFrames((void*)node->f18, 0, &b, &d);
    ComputePolarOffset(&e, self->f630, Vu0::ToFloat(Vu0::Length(Vu0::Q(*(Vec02*)((u8*)self + 0xE90)))) * self->f634, 0.0f);
    f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(e), Vu0::Q(d)));
    PathShape* s2 = node->f34;
    f32 value = ((ShapeScalarFn)s2->vtbl[5])(s2, t);
    f.x = -*(f32*)((u8*)self + 0xE90);
    f.y = -*(f32*)((u8*)self + 0xE40);
    f.z = D_00274E1C;
    ApproachValueWithRamp(&f, value, D_00274E04, g_gameClock.dt, &lo);
    PathShape* s3 = node->f34;
    ApproachValueWithRamp(&f, value, ((ShapeLimitFn)s3->vtbl[8])(s3) - D_00274E04, g_gameClock.dt, &hi);
    *outA = c;
    f32 clamped = along;
    if (along < lo) {
        clamped = lo;
    } else if (hi < along) {
        clamped = hi;
    }
    Vu0::Q(*outB) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(clamped));
}
