// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 341/396 (86.1%), checked 2026-11-10
// NEAR: the tail is retail's since 2026-11-10 (the new velocity stored to self->qA0 first and copied to vel from it, so its register does not die at the member store and sched1 no longer issues that store first, by INSN_REG_WEIGHT, ahead of the dead pa/pb/d1/d2 stores), and b.x is written before b.y (the dying 20.0 store goes first, retail's b.y before b.x in the delay slot). Still differs: block 0's schedule. Retail's sched1 must issue b's clear after the life load and the 20.0 constant after the divide (20.0 shares $f0 with the difference, t is $f3, 0.0 $f4); ours issues b's clear at clock 3 (priority 3 beats the dt copy's 2) and the 20.0 at clock 5 (three dependents beat 125's and -25's two). Every order of the seven a/b/t statements (280, build/swarm/w10-1A1030/brute.py) gives one of two schedules; the clamp as an inline, if/else, ?:, a reference output or named lo/hi changes nothing; g_gameClock[1] for g_gameTime and `Vec02 a = {125, -25}` initialisers neither.
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
    b.x = 20.0f;
    b.y = 20.0f;
    a.x = 125.0f;
    a.y = -25.0f;
    f32 t = (g_gameTime - self->start) / self->life;
    f32 u = ClampRange(t, 0.0f, 1.0f);
    Vu0::Q(pa) = Vu0::FromFloats(a.x + u * (a.y + u * a.z), 0.0f, 0.0f);
    Vu0::Q(pb) = Vu0::FromFloats(0.0f, b.x + u * (b.y + u * b.z), 0.0f);
    Vu0::Q(d1) = Vu0::Sub(Vu0::Q(pa), Vu0::Q(self->q80));
    Vu0::Q(d2) = Vu0::Sub(Vu0::Q(pb), Vu0::Q(self->qA0));
    Vu0::Q(d2) = Vu0::MulXSum(Vu0::Q(d1), Vu0::Scalar(25.0f), Vu0::Q(d2), Vu0::Scalar(10.0f));
    Vu0::Q(self->qA0) = Vu0::MulAddX(Vu0::Q(self->qA0), Vu0::Q(d2), Vu0::Scalar(dt));
    Vu0::Q(vel) = Vu0::Q(self->qA0);
    vel.y = 0.0f;
    Vu0::Q(self->q80) = Vu0::MulAddX(Vu0::Q(self->q80), Vu0::Q(vel), Vu0::Scalar(dt));
}
