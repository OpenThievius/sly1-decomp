// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 412/416, checked 2026-11-07
// NEAR: one copy: retail's sqrt.s writes f0 and a mov.s f20,f0 moves it into the speed's register, with the multiply by the distance in the delay slot of the Cosine call; ours multiplies from f0 directly and fills the delay slot with the argument move (the float registers, the calls, the vector code and the tail all match: the speed is one variable, h declared before the Sine call). Fpu::Sqrt(q) assigned to q, to a fresh local and to a product tried.
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
#include "common.h"
#include "fpu.h"
#include "globals.h"
#include "vu0.h"

f32 ArctangentOfRatio(f32 a, f32 b);
f32 Sine(f32 x);
f32 Cosine(f32 x);
f32 Tangent(f32 x);

s32 ComputeBallisticLaunchVelocity(Vec02* from, Vec02* to, Vec02* out, u8* rec, f32 angle)
{
    Vec02 d;
    f32 h;
    f32 s = Sine(angle);
    u8* g;
    if (rec != 0) {
        g = rec + 0x350;
    } else {
        g = (u8*)g_currentWorld + 0x1EE0;
    }
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*to), Vu0::Q(*from));
    h = d.z;
    d.z = 0.0f;
    f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
    f32 a = ArctangentOfRatio(h, dist);
    if (a < 0.0f) {
        a = 0.0f;
    }
    f32 theta = a + (1.5707964f - a) * s;
    f32 e = h - dist * Tangent(theta);
    f32 q = *(f32*)(g + 8) / (e + e);
    if (q <= 0.0f) {
        return 0;
    }
    q = Fpu::Sqrt(q);
    q = dist * q;
    q = q / Cosine(theta);
    *out = d;
    out->z = dist * Tangent(theta);
    Vu0::Q(*out) = Vu0::MulX(Vu0::DivX(Vu0::Q(*out), Vu0::Length(Vu0::Q(*out))), Vu0::Scalar(q));
    return 1;
}
