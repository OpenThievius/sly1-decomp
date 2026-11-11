// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 341/396 (86.1%), checked 2026-11-11
// Wave 23 (w23-vuD, 2026-11-11), tools/sched1.py on this form (its replay of block 0 matches the trace): retail's frame-store order (a's clear, b's clear, a.x, a.y, b.y, b.x; sched2 keeps it) and the 20.0 issued after the divide (sharing $f0 with the difference) both follow from one change of priorities: --prio 28=2 (the 20.0, now 4: its two stores' 2 plus its latency), or a's two constants and stores one above b's (--prio 40=5 46=5 42=3 48=3); with --prio 24=2 (b's clear, now 3) b's clear also issues after the life load. A priority of 2 for the 20.0 means its stores have no dependents but the jump; 3 for a's stores means retail's a stores have an in-block dependent (a load of a or an output or anti dependence) that b's lack. Look for that difference in the source (how a and b are filled or read), not for another statement order.
// NEAR: the tail is retail's since 2026-11-10 (the new velocity stored to self->qA0 first and copied to vel from it, so its register does not die at the member store and sched1 no longer issues that store first, by INSN_REG_WEIGHT, ahead of the dead pa/pb/d1/d2 stores), and b.x is written before b.y (the dying 20.0 store goes first, retail's b.y before b.x in the delay slot). Still differs: block 0's schedule. Retail's sched1 must issue b's clear after the life load and the 20.0 constant after the divide (20.0 shares $f0 with the difference, t is $f3, 0.0 $f4); ours issues b's clear at clock 3 (priority 3 beats the dt copy's 2) and the 20.0 at clock 5 (three dependents beat 125's and -25's two). Every order of the seven a/b/t statements (280, build/swarm/w10-1A1030/brute.py) gives one of two schedules; the clamp as an inline, if/else, ?:, a reference output or named lo/hi changes nothing; g_gameClock[1] for g_gameTime and `Vec02 a = {125, -25}` initialisers neither. Re-scored 2026-11-10 (w15): retail's order is out of sched1's reach for this RTL: after reload sp has no alias base, so sched2 keeps frame stores and a2 loads in sched1's order, and the two clears rank alike but for INSN_LUID, so whatever beats b's clear at clock 3 beats a's at clock 2 (docs/toolchain/sched1.md, "Two equal clears that retail issues apart"). Also ruled out: chained or copied b stores, `Vec02 b = a`, b after the clamp, inline setters, an inline progress or quadratic, by-reference clamp or weight parameters, the update as an inline; a reused float for the difference and the 20.0 gives retail's 20.0 placement but is not plausible (18 lines).
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
