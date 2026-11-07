// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 364/372 (97.8%), checked 2026-11-07
// NEAR: one swap: retail issues c.lt.s f21,f0 (the first length against 1e-4) before the qmfc2 of the second length; here the qmfc2 comes first. Everything else equal. Tried the lengths as vectors converted after, one declaration order, and a conditional assignment of the second.
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
#include "common.h"
#include "globals.h"
#include "vu0.h"

void ComputeUnitPerpendicular(Vec02* v, Vec02* out);
f32 Arccosine(f32 x);

f32 ComputeAngleBetweenVectors(Vec02* a, Vec02* b, Vec02* axis)
{
    u128 va = Vu0::Length(Vu0::Q(*a));
    u128 vb = Vu0::Length(Vu0::Q(*b));
    f32 la = Vu0::ToFloat(va);
    f32 lb = Vu0::ToFloat(vb);
    if (la < 0.0001f || lb < 0.0001f) {
        *axis = g_unitXVector;
        return 0.0f;
    }
    if (axis != 0) {
        u128 c = Vu0::Cross(Vu0::Q(*a), Vu0::Q(*b));
        Vu0::Q(*axis) = c;
        f32 len = Vu0::ToFloat(Vu0::Length(c));
        if (1e-8f < len) {
            Vu0::Q(*axis) = Vu0::MulX(c, Vu0::Scalar(1.0f / len));
        } else {
            ComputeUnitPerpendicular(a, axis);
        }
    }
    return Arccosine(Vu0::ToFloat(Vu0::Dot(Vu0::Q(*a), Vu0::Q(*b))) / (la * lb));
}
