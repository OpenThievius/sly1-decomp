// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 207/252 (82.1%), checked 2026-11-07
// NEAR: the range record's middle and half-length (from its near and far distances: the cone case with two square roots, or the plain case). The instruction mix and the sqrt.s operands are retail's; two things differ: the order of the first loads and of the sub/mul pairs (retail loads f08 before f44; the scheduler order differs), and where the f60 store lands (retail stores it before the move of t into the vector, ours after the vector add). The two stack slots of the dead vector stores are retail's.
#include "common.h"
#include "range_record.h"
#include "vu0.h"
#include "fpu.h"

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);

void func_001B1BF8(RangeRecord* self)
{
    Vec02 scaled;
    Vec02 k;
    f32 half;
    f32 t;
    if (AreFloatsNearlyEqual(self->f04, self->f08, 1e-4f)) {
        half = (__builtin_fabsf(self->f44 - self->f40)) * 0.5f;
        t = self->f40 + half;
    } else {
        f32 a = self->f40;
        f32 b = self->f44;
        f32 p = self->f04;
        f32 q = self->f08;
        f32 m = (a * q - b * p) / (p - q);
        f32 d = b - a;
        f32 a2 = a + m;
        f32 b2 = b + m;
        f32 s = Fpu::Sqrt(d * d + q * q);
        f32 u = a2 * s / d;
        f32 w = u + s * 0.5f;
        f32 r = u * w / a2;
        half = Fpu::Sqrt((b2 - r) * (b2 - r) + q * q);
        t = r - m;
    }
    self->f60 = half;
    Vu0::Q(k) = Vu0::FromFloat(t);
    Vu0::Q(scaled) = Vu0::MulX(Vu0::Q(self->v20), Vu0::Q(k));
    Vu0::Q(self->v50) = Vu0::Add(Vu0::Q(self->v10), Vu0::Q(scaled));
}
