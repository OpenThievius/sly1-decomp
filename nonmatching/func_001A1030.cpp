// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 321/396 (81.1%), checked 2026-11-08
// NEAR: every instruction and frame offset is retail's except the schedule of the head: retail loads D_0026185C into $f0, 125.0 before the start/life loads, and 20.0 and 1.0 after the divide (before the clamp's compare, b.y stored before it, b.x in the branch's delay slot); here 20.0 is loaded first and 1.0 after the first compare. Registers follow ($f4 zero in retail, $f5 here). Tried clamp as if/else, as ?:, as >? and <? (max.s, wrong), as an inline function, and the order of the a/b/t statements.
// In the context of its file, src/main/file_19E040.cpp.
#include "common.h"
#include "effect.h"
#include "vu0.h"
#include "globals.h"

extern f32 g_gameTime;

static inline f32 ClampRange(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void func_001A1030(Effect* self, f32 dt)
{
    Vec02 d1, d2, vel, pa, pb;
    Vec02 a = {};
    Vec02 b = {};
    a.x = 125.0f;
    a.y = -25.0f;
    f32 t = (g_gameTime - self->start) / self->life;
    b.y = 20.0f;
    b.x = 20.0f;
    f32 u = ClampRange(t, 0.0f, 1.0f);
    Vu0::Q(pa) = Vu0::FromFloats(a.x + u * (a.y + u * a.z), 0.0f, 0.0f);
    Vu0::Q(pb) = Vu0::FromFloats(0.0f, b.x + u * (b.y + u * b.z), 0.0f);
    Vu0::Q(d1) = Vu0::Sub(Vu0::Q(pa), Vu0::Q(self->q80));
    Vu0::Q(d2) = Vu0::Sub(Vu0::Q(pb), Vu0::Q(self->qA0));
    Vu0::Q(d2) = Vu0::MulXSum(Vu0::Q(d1), Vu0::Scalar(25.0f), Vu0::Q(d2), Vu0::Scalar(10.0f));
    Vu0::Q(vel) = Vu0::MulAddX(Vu0::Q(self->qA0), Vu0::Q(d2), Vu0::Scalar(dt));
    Vu0::Q(self->qA0) = Vu0::Q(vel);
    vel.y = 0.0f;
    Vu0::Q(self->q80) = Vu0::MulAddX(Vu0::Q(self->q80), Vu0::Q(vel), Vu0::Scalar(dt));
}
