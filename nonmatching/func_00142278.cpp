// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1796/1816 (98.9%), checked 2026-11-11
// NEAR: the first block is retail's: the statements in the order cd, ab, ca put c's load before a's and leave ab's subtraction unraised, so sched1 issues b, c, a, ca, ab and local-alloc gives retail's VU0 registers, and nn's conversion is ToFloatNow (its dot's result a VU0 pseudo). Left (docs/toolchain/sched1.md, "The side test and the half-width"): the side test's block, whose VU0 registers are retail's but whose order is not: a model of sched2 gives retail's order only with ToFloatViaBits for side, s and u and the s dot ahead of side's qmfc2 in sched1's output, which sched1's priorities (6 against 5) never give, the quadratic's head's wall (func_00141D88); and w's dot, whose retail GPR (a0, then k v0, kk v1) is reload's as ToFloat gives it, and whose order needs the compiler's qmfc2 (Moved), so retail read a VU0-allocated dot result through an "r" operand, which no plain form found gives.
// w20 (2026-11-10): ToFloatMoved now takes its vector as "*r" (regclass skips the operand; docs/toolchain/
// vu0-helpers.md, "A GPR operand that leaves the class to the producer"), so each dot read by it is a
// VU0 pseudo with reload's qmfc2; all four conversions as ToFloatMoved (the best of the 16 mixes with
// ToFloatNow/ToFloat) leave 13 lines: in the side test's block the dot's product takes vf2 and its 1.0
// vf1 where retail has vf1/vf2 (the two-or-three-quantities order of local-alloc), which cascades to the
// cross product's register and the two qmfc2s.
// w22 (2026-11-11, replayed with tools/sched1.py and tools/globalalloc.py --local): the 13 lines are
// one local-alloc decision in the side test's block. side's dot (its quantity: 2 refs, birth 2,
// death 10, priority 5000) is placed after the second cross product (4 refs over 16, 10000), which
// takes vf1 first; `--pri <side dot>=10000` (tie, lower quantity number) gives every retail register
// of the block (side vf1, its 1.0 vf2, the cross vf2, u's dot vf1). That needs a death at 6: side's
// conversion issued first in cycle 2, ahead of both cross products (priority 5 each; at the tie the
// crosses win on dependents, 2 against 1), so the conversion needs priority 6, which only an extra
// insn in its chain gives (sched1.py --prio <mtc1>=6 gives order 309 522 320 461 365 ...). Compiled:
// ToFloatViaBits for side (its ToBits has priority 6 and goes first: side's dot vf1 / 1.0 vf2 as
// retail) moves s's and u's dots next to each other, so u's 1.0 takes vf6 and the global n moves to
// vf7 (39 lines); ViaBits for side, s and u 37; ToFloat for side 19; ToFloatNow 30. The birthing
// raise would also do it, but side is not live past the block's branch. Wall unchanged.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "collider.h"
#include "shapes.h"
#include "fpu.h"

f32 SplitVectorAlongAxis(const Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
extern Vec02 g_unitXVector;
extern Vec02 g_unitYVector;
extern Vec02 g_unitZVector;

static inline u128 NormalizeOfCopy(u128 v, u128 vc, u128 fallback)
{
    u128 len = Vu0::Length(vc);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        return fallback;
    }
    return Vu0::DivX(v, len);
}

s32 func_00142278(Vec02* a, Vec02* b, Vec02* c, Vec02* d, s32 count, ColliderSpan* out, f32 radius)
{
    Vec02 cd;
    Vec02 ab;
    Vec02 ca;
    Vec02 n;
    Vec02 x;
    Vec02 m;
    Vec02 dir;
    f32 s;
    f32 u;
    if (count == 0)
        return 0;
    Vu0::Q(cd) = Vu0::Sub(Vu0::Q(*d), Vu0::Q(*c));
    Vu0::Q(ab) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    Vu0::Q(ca) = Vu0::Sub(Vu0::Q(*a), Vu0::Q(*c));
    Vu0::Q(n) = Vu0::Cross(Vu0::Q(cd), Vu0::Q(ab));
    f32 nn = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(n), Vu0::Q(n)));
    if (!(nn < 0.0001f)) {
        f32 side = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ca), Vu0::Q(n)));
        Vu0::Q(x) = Vu0::Cross(Vu0::Q(ca), Vu0::Q(ab));
        s = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(x), Vu0::Q(n))) / nn;
        Vu0::Q(x) = Vu0::Cross(Vu0::Q(ca), Vu0::Q(cd));
        u = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(x), Vu0::Q(n))) / nn;
        if (side < 0.0f)
            Vu0::Q(n) = Vu0::MulX(Vu0::Q(n), Vu0::Scalar(-1.0f));
    }
    Vu0::Set(n, Vu0::NormalizeOr(Vu0::Q(n), Vu0::Q(g_unitZVector)));
    f32 h = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ca), Vu0::Q(n)));
    if (radius < h)
        return 0;
    {
        u128 p = Vu0::Cross(Vu0::Q(n), Vu0::Q(ab));
        u128 pc = Vu0::Copy(p);
        Vu0::Q(m) = pc;
        Vu0::Set(m, NormalizeOfCopy(p, pc, Vu0::Q(g_unitYVector)));
    }
    f32 w = Fpu::Sqrt(radius * radius - h * h) / Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(cd), Vu0::Q(m)));
    f32 k = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(cd), Vu0::Q(ab)));
    f32 kk = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
    out->time[0] = s - w;
    out->time[1] = s + w;
    w = w * k;
    w = w / kk;
    out->param[0] = u - w;
    out->param[1] = u + w;
    if (out->param[1] < out->param[0]) {
        f32 tmp = out->time[0];
        out->time[0] = out->time[1];
        out->time[1] = tmp;
        tmp = out->param[0];
        out->param[0] = out->param[1];
        out->param[1] = tmp;
    }
    if (out->param[1] < 0.0f)
        return 0;
    if (1.0f < out->param[0])
        return 0;
    if (0.0001f < out->param[1] - out->param[0]) {
        f32 f = out->param[0] / (out->param[0] - out->param[1]);
        if (0.0f < f && f < 1.0f) {
            out->param[0] = (1.0f - f) * out->param[0] + f * out->param[1];
            out->time[0] = (1.0f - f) * out->time[0] + f * out->time[1];
        }
        f = (out->param[0] - 1.0f) / (out->param[0] - out->param[1]);
        if (0.0f < f && f < 1.0f) {
            out->param[1] = (1.0f - f) * out->param[0] + f * out->param[1];
            out->time[1] = (1.0f - f) * out->time[0] + f * out->time[1];
        }
    }
    if (out->time[0] > out->time[1]) {
        f32 a1 = out->time[1];
        f32 a0 = out->time[0];
        f32 b0 = out->param[0];
        f32 b1 = out->param[1];
        out->time[0] = a1;
        out->time[1] = a0;
        out->param[0] = b1;
        out->param[1] = b0;
    }
    if (out->time[1] < 0.0f)
        return 0;
    if (1.0f < out->time[0])
        return 0;
    if (0.0001f < out->time[1] - out->time[0]) {
        f32 f = out->time[0] / (out->time[0] - out->time[1]);
        if (0.0f < f && f < 1.0f) {
            out->time[0] = (1.0f - f) * out->time[0] + f * out->time[1];
            out->param[0] = (1.0f - f) * out->param[0] + f * out->param[1];
        }
        f = (out->time[0] - 1.0f) / (out->time[0] - out->time[1]);
        if (0.0f < f && f < 1.0f) {
            out->time[1] = (1.0f - f) * out->time[0] + f * out->time[1];
            out->param[1] = (1.0f - f) * out->param[0] + f * out->param[1];
        }
    }
    Vu0::Q(dir) = Vu0::Q(ab);
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Q(dir), Vu0::Q(g_unitXVector)));
    for (s32 i = 0; i < 2; i++) {
        f32 ti = out->time[i];
        Vu0::Q(out->q[i]) = Vu0::MulXSum(Vu0::Vec::Of(*c), Vu0::Vec::Scalar(1.0f - ti), Vu0::Vec::Of(*d), Vu0::Vec::Scalar(ti)).q;
        if (out->param[0] == 0.0f) {
            Vu0::Q(out->q[i + 2]) = Vu0::MulX(Vu0::Vec::Of(dir), Vu0::Vec::Scalar(-1.0f)).q;
        } else if (out->param[0] == 1.0f) {
            *(Vec02*)&out->q[i + 2] = dir;
        } else {
            Vu0::Q(ca) = Vu0::Sub(Vu0::Vec::Of(out->q[i]), Vu0::Vec::Of(*a)).q;
            SplitVectorAlongAxis(&ca, &dir, 0, (Vec02*)&out->q[i + 2]);
            Vu0::Q(out->q[i + 2]) = Vu0::NormalizeOr(Vu0::Vec::Of(out->q[i + 2]), Vu0::Vec::Of(g_unitZVector)).q;
        }
    }
    out->f48 = 2;
    return 1;
}
