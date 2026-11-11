// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1410/1416 (99.6%), checked 2026-11-10
// NEAR (2026-11-10, w11): func_001B55C0, slot 4 of the triangle animator (g_triangleAnimatorMethods):
// where the segment between the two objects at Rec2195_224::p64 and p60 crosses the animator's
// triangle strip, the strip's coordinates there, offset, clamped and eased into the cursor.
// Retail's size and 340 of its 354 words. What got the size: the window shifts as an inline
// (DropFirst), whose frame-address parameters integrate.c substitutes into the argument moves,
// so the MoveMemory arguments are hard-register sets that GCSE never hashes: PRE then neither
// hoists &uv[0] into the flags block (the extra word and the loop label's alignment nop) nor
// keeps &uv[1] in a saved register (docs/TOOLCHAIN.md, "MoveMemory's frame arguments"). Then:
// the flags read through `StripPoint* pt = &self->points[i]` (a pointer set from a sum keeps
// points first, so the sum ties to the loaded points, not to i*16); one `j` for the edge loop
// and the inner loop (its refs put it before the next pointer's giv: a3 and t0 as retail);
// ApproachValueWithRamp declared floats first as most files do (the f13 move before a0); all
// three dots through ToFloat; the cursor's u and v read through self; the clamps' results
// in variables of their own (cu, cv: w15, below). Still differs (w15, 2026-11-10), two things:
// - the cursor and &tri[2]'s PRE pseudo (s7/s8 swapped). global-alloc ranks 2 refs over 240
//   insns against 3 refs over 354 (177 doubled by update_equiv_regs for its REG_EQUIV): the
//   cursor goes first only if 4 x 177 > 3 x its life, so at most 235 insns (236 ties on the
//   allocno number). Its set is sched1's filler at t3 of the entry block (ready from t1,
//   priority 2, lowest LUID among the other fillers, the PRE'd highs of $LC0 and the clock),
//   so it is born before the first call whatever the source order (declared after the loop,
//   PRE hoists it and sched1 puts it there again); retail's life needs the set after that call
//   (5 insns later) or 13 more RTL insns in the loop. Vec values for n, p, m and the edges add
//   none (their copies are gone before flow); two `end` variables, `&self->cursor` at the call
//   and cursor->record change nothing or too much (cursor->u: 3 refs, above &uv[2]).
// - sched2 in the dots' block: retail puts the 0.0's mtc1 before b's lqc2 (ours has b's load
//   at priority 7 against 6) and the b-dot before the a-dot's qmfc2 (ours: the a-dot's chain,
//   priority 10, against 6). The first needs b's chain one shorter, the second the a-dot's
//   qmfc2 not ready at t11 (a link to the d0 qmfc2 that ours lacks); ToFloatMoved for the
//   b-dot fixes the first and renumbers its registers. Every mix of ToFloat, ToFloatMoved,
//   ToFloatNow and ToFloatViaBits for the three dots, their order, a named Vec for n and a
//   named 0.0 change nothing or more. Vec::Scalar(-1.0f) for `neg` grows the frame by 16.
// w21 (2026-11-10): with ToFloatMoved's "*r" operand (wave 20), all six dots through
// ToFloatMoved (the best of 14 mixes with ToFloat) fix the second point, sched2's order in the
// dots' block (1376 -> 1410 of 1416). Left: the first point only, the cursor and &tri[2]'s PRE
// pseudo in s7/s8, unchanged (globalalloc.py: 2 refs over 240 insns against 3 over 354).
// The clamps (w15): `u = ClampBetween(..)` stored the first result in u's own pseudo, live
// while lo is loaded, so lo conflicts with u and expand_preferences gives it none of u's
// preferences ($f12, $f13 from the calls' arguments): lo took $f2, hi $f3, and 1 - v kept its
// own $f13. In a fresh variable the result is born after u dies, lo and hi pool its $f13
// preference, lo (first in the order) takes it, hi takes $f2 and 1 - v $f3, as retail.
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
f32 ApproachValueWithRamp(f32 value, f32 target, f32 dt, Vec3* ramp, f32* rate);
void SetCursorCoords(AnimCursor* cursor, f32 u, f32 v);
void DrawModelPart();
// Drops the first entry of a three-entry window: the other two move down.
template <class T> static inline void DropFirst(T* window)
{
    MoveMemory(window, window + 1, 2 * sizeof(T));
}


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
        DropFirst(tri);
        DropFirst(uv);
        CopyVec3((Vec3*)&tri[2], (Vec3*)&self->points[i]);
        CopyVec2(&uv[2], (Point2*)&self->coords[i]);
        StripPoint* pt = &self->points[i];
        if (pt->flags & 0x8000) {
            continue;
        }
        Vec02 n;
        Vec02 p;
        s32 j;
        for (j = 0; j < 3; j++) {
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
        f32 d0 = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(tri[0])));
        f32 da = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(a))) - d0;
        f32 db = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(b))) - d0;
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
        for (j = 0; j < 3; j++) {
            Vec02 m;
            Vu0::Vec e = Vu0::Cross(Vu0::Vec::Of(edge[j]), Vu0::Vec::Of(n));
            Vu0::Q(m) = Vu0::DivX(e, Vu0::Length(e)).q;
            f32 dv = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(tri[order[j]])));
            f32 dp = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(p))) - dv;
            if (0.0f < dp) {
                break;
            }
            f32 w = dp / (Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(tri[next[j]]))) - dv);
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
    f32 cu = ClampBetween(iu - self->u0, self->uMin, self->uMax);
    f32 cv = ClampBetween(iv - self->v0, self->vMin, self->vMax);
    ApproachValueWithRamp(self->cursor.u, cu, g_gameClock.dt, &ramp, 0);
    ApproachValueWithRamp(self->cursor.v, cv, g_gameClock.dt, &ramp, 0);
    SetCursorCoords(cursor, cu, cv);
}
