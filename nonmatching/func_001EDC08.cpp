// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 428/424, checked 2026-11-07
// NEAR: the call, the first clamp, MulXSum4 of the four corners with their four Scalars (stored in retail's order), the length and NormalizeOr's fallback copy and the ToBits store are retail's. Still differs: the second clamp keeps its result in the zero's register (f2) where retail gives it f3 and branches with bc1t, and the VU0 registers of the weights and the first point: retail u - 1 vf4, p0 vf5, 1 - v vf6, -u vf7, here vf5, vf4, vf7, vf6. MulXSum4's operands in another order, the clamps as a loop, inline or with v kept in a local: no closer.
#include "common.h"
#include "globals.h"
#include "vu0.h"

void FindSegmentClosestParams(const Vec02* p0, const Vec02* p1, const Vec02* q0, const Vec02* q1, f32* st, f32* dist, Vec02* dir);

// v clamped to [0, 1].
static inline f32 ClampUnit(f32 v)
{
    f32 c;
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    if (v < lo) {
        c = lo;
    } else if (hi < v) {
        c = hi;
    } else {
        c = v;
    }
    return c;
}

// The closest points of the segments p0-p1 and q0-q1, their fractions clamped to the segments:
// the direction from the first to the second into dir (the x axis when they meet) and the
// distance into dist.
void FindClosestPointsOnSegments(const Vec02* p0, const Vec02* p1, const Vec02* q0, const Vec02* q1, f32* st, f32* dist, Vec02* dir)
{
    FindSegmentClosestParams(p0, p1, q0, q1, st, dist, dir);
    st[0] = ClampUnit(st[0]);
    st[1] = ClampUnit(st[1]);
    u128 d = Vu0::MulXSum4(Vu0::Q(*p0), Vu0::Scalar(st[0] - 1.0f), Vu0::Q(*p1), Vu0::Scalar(-st[0]),
                           Vu0::Q(*q0), Vu0::Scalar(1.0f - st[1]), Vu0::Q(*q1), Vu0::Scalar(st[1]));
    Vu0::Q(*dir) = d;
    u128 len = Vu0::Length(d);
    if (Vu0::ToFloat(len) < 0.0001f) {
        *dir = g_unitXVector;
    } else {
        Vu0::Q(*dir) = Vu0::DivX(d, len);
    }
    *(u32*)dist = Vu0::ToBits(len);
}
