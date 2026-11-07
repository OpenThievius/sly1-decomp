// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 433/516 (83.9%), checked 2026-11-07
// NEAR: the position is retail's to the register (MulXSum4 of p0, m0, m1, p1 with four Scalars), and so is the velocity's MulXSum3. Still differs: the velocity's MulX takes the sum's register (vf1) where retail gives the product a fresh one (vf3), and the acceleration's weights and rows take other registers (retail 6 - 12u vf1, 6u - 4 vf3, 6u - 2 vf4, d vf5, m0 vf7; the constants 12, 6, 2 in f1, f0, f3). The weights as locals in either order and the constants before u: no closer.
#include "common.h"
#include "placed_object.h"
#include "vu0.h"

// The cubic Hermite segment from p0 (tangent m0) to p1 (tangent m1) over dur, at time t: the
// point into pos, the velocity (scaled by k) into vel and the acceleration (by k squared)
// into acc, each when given.
void EvaluateHermiteVectorSegment(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, f32 t, f32 k, Vec02* pos, Vec02* vel, Vec02* acc)
{
    Vec02 d;
    f32 u = t / dur;
    f32 w = 1.0f - u;
    if (pos != 0) {
        f32 uw = u * w;
        f32 uu = u * u;
        f32 ww = w * w;
        f32 uww = uw * w;
        f32 uuw = uu * w;
        f32 www = ww * w;
        Vu0::Q(*pos) = Vu0::MulXSum4(Vu0::Q(*p0), Vu0::Scalar(www + uww * 3.0f), Vu0::Q(*m0), Vu0::Scalar(uww * dur),
                                     Vu0::Q(*m1), Vu0::Scalar(-uuw * dur), Vu0::Q(*p1), Vu0::Scalar(uu * u + uuw * 3.0f));
    }
    if (vel != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*p1), Vu0::Q(*p0));
        u128 v = Vu0::MulXSum3(Vu0::Q(d), Vu0::Scalar(u * (6.0f - u * 6.0f) / dur), Vu0::Q(*m0), Vu0::Scalar(1.0f - u * (4.0f - u * 3.0f)),
                               Vu0::Q(*m1), Vu0::Scalar(u * (u * 3.0f + -2.0f)));
        Vu0::Q(*vel) = Vu0::MulX(v, Vu0::Scalar(k));
    }
    if (acc != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*p1), Vu0::Q(*p0));
        u128 a = Vu0::MulXSum3(Vu0::Q(d), Vu0::Scalar((6.0f - u * 12.0f) / dur), Vu0::Q(*m0), Vu0::Scalar(u * 6.0f - 4.0f),
                               Vu0::Q(*m1), Vu0::Scalar(u * 6.0f - 2.0f));
        Vu0::Q(*acc) = Vu0::MulX(a, Vu0::Scalar(k * k / dur));
    }
}
