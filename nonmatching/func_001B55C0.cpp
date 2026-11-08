// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1408/1416, checked 2026-11-08
// NEAR (2026-11-08): func_001B55C0, slot 4 of the triangle animator (g_triangleAnimatorMethods):
// where the segment between the two objects at Rec2195_224::p64 and p60 crosses the animator's
// triangle strip, the strip's coordinates there, offset, clamped and eased into the cursor.
// Retail's frame, control flow and VU0 sequences; 352 of retail's 354 instructions. What got
// there: the -1.0 weight of the second edge as a braced vector local (Scalar's constant, set
// nine notes before its qmtc2, is hoisted out of the strip loop by loop.c into a saved GPR;
// FromFloat's literal is not, and the local gives retail's store at 0xC0); the cursor's address
// as a named local read for u and v (otherwise PRE's copies of &uv[1] and &tri[2] win the
// saved registers and the cursor is spilled, 16 more bytes of frame); 1 - u and 1 - v named
// before the clamps. Still differs: GCSE's PRE keeps &uv[1] (sp+0x58) in a saved register
// across the loop where retail keeps &tri[2] (sp+0x40) and re-forms &uv[1], and hoists &uv[0]
// (sp+0x50) of the inner loop into the flags block (retail forms it in the inner loop's
// preheader): retail's form of the uv copies is still unknown; the saved registers are
// permuted (cursor s5 not s7, ramp s6 not s5) and the cursor's u and v are read through it
// where retail reads them through self; the point's flags test reuses s0; the inner loop's
// counter and next pointer have each other's registers; the 0.0 and the second dot's qmfc2
// are scheduled later; the clamp's FPRs differ.
// In the context of its file, src/main/state_walker.cpp (the ramp {1, 0.1, 0.1} is retail's
// D_0024D268, whose INCLUDE_RODATA line goes with the function).
#include "common.h"
#include "shapes.h"
#include "cursor_animator.h"
#include "attachment.h"
#include "placed_object.h"
#include "base_object.h"
#include "vu0.h"
#include "game_clock.h"

// Two floats (state_walker.cpp's CopyVec2).
struct Point2 { f32 x; f32 y; };
void CopyVec3(Vec3* dst, Vec3* src);
void CopyVec2(Point2* a0, Point2* a1);
extern s32 D_00274548[4];
extern s32 D_00274558[4];
extern s32 D_00274568[4];
extern s32 D_00274578[4];

void* MoveMemory(void* dst, void* src, s32 size);
void TransformPointBetweenFrames(void* from, void* to, void* point, void* out);
f32 ApproachValueWithRamp(Vec3* ramp, f32* rate, f32 value, f32 target, f32 dt);
void SetCursorCoords(AnimCursor* cursor, f32 u, f32 v);
void DrawModelPart();

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void func_001B55C0(TriangleAnimator* self, PlacedObject* obj, void** part)
{
    if (self->cursor.record == 0 || *part != (void*)DrawModelPart) {
        return;
    }
    AnimCursor* cursor = &self->cursor;
    Vec02 b;
    Vec02 a;
    Vec02 tri[3];
    Point2 uv[3];
    Vec02 edge[3];
    f32 u;
    f32 v;
    BaseObject* end = obj->f224->p64;
    TransformPointBetweenFrames(end->parent, obj, (u8*)end + 0x40, &b);
    end = obj->f224->p60;
    TransformPointBetweenFrames(end->parent, obj, (u8*)end + 0x40, &a);
    CopyVec3((Vec3*)&tri[1], (Vec3*)&self->points[0]);
    CopyVec3((Vec3*)&tri[2], (Vec3*)&self->points[1]);
    CopyVec2(&uv[1], (Point2*)&self->coords[0]);
    CopyVec2(&uv[2], (Point2*)&self->coords[1]);
    for (s32 i = 2; i < self->count; i++) {
        s32* order;
        s32* next;
        if (i & 1) {
            order = D_00274568;
            next = D_00274578;
        } else {
            order = D_00274548;
            next = D_00274558;
        }
        MoveMemory(tri, tri + 1, 0x20);
        MoveMemory(&uv[0], &uv[1], 0x10);
        CopyVec3((Vec3*)&tri[2], (Vec3*)&self->points[i]);
        CopyVec2(&uv[2], (Point2*)&self->coords[i]);
        if (self->points[i].flags & 0x8000) {
            continue;
        }
        Vec02 n;
        Vec02 p;
        for (s32 j = 0; j < 3; j++) {
            Vu0::Q(edge[j]) = Vu0::Sub(Vu0::Vec::Of(tri[order[(j + 1) % 3]]), Vu0::Vec::Of(tri[order[j]])).q;
        }
        Vu0::Vec e0 = Vu0::Vec::Of(edge[0]);
        Vu0::Vec e2 = Vu0::Vec::Of(edge[2]);
        Vu0::Vec c;
        {
            Vec02 neg;
            Vu0::Q(neg) = Vu0::FromFloat(-1.0f);
            c = Vu0::Cross(e0, Vu0::MulX(e2, Vu0::Vec::Of(neg)));
        }
        Vu0::Q(n) = Vu0::DivX(c, Vu0::Length(c)).q;
        f32 d0 = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(tri[0])));
        f32 da = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(a))) - d0;
        f32 db = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(b))) - d0;
        if (da >= 0.0f && db >= 0.0f) {
            continue;
        }
        if (da < 0.0f && db < 0.0f) {
            continue;
        }
        f32 t = da / (da - db);
        Vu0::Q(p) = Vu0::Add(Vu0::MulX(Vu0::Vec::Of(a), Vu0::Vec::Scalar(1.0f - t)), Vu0::MulX(Vu0::Vec::Of(b), Vu0::Vec::Scalar(t))).q;
        f32 su = 0.0f;
        f32 sv = 0.0f;
        s32 j;
        for (j = 0; j < 3; j++) {
            Vec02 m;
            Vu0::Vec e = Vu0::Cross(Vu0::Vec::Of(edge[j]), Vu0::Vec::Of(n));
            Vu0::Q(m) = Vu0::DivX(e, Vu0::Length(e)).q;
            f32 dv = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(tri[order[j]])));
            f32 dp = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(p))) - dv;
            if (0.0f < dp) {
                break;
            }
            f32 w = dp / (Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(tri[next[j]]))) - dv);
            su += w * uv[next[j]].x;
            sv += w * uv[next[j]].y;
        }
        if (j >= 3) {
            u = su;
            v = sv;
            break;
        }
    }
    Vec3 ramp = { 1.0f, 0.1f, 0.1f };
    f32 iu = 1.0f - u;
    f32 iv = 1.0f - v;
    u = ClampBetween(iu - self->u0, self->uMin, self->uMax);
    v = ClampBetween(iv - self->v0, self->vMin, self->vMax);
    ApproachValueWithRamp(&ramp, 0, cursor->u, u, g_gameClock.dt);
    ApproachValueWithRamp(&ramp, 0, cursor->v, v, g_gameClock.dt);
    SetCursorCoords(cursor, u, v);
}
