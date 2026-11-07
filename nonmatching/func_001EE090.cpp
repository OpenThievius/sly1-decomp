// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 508/512, checked 2026-11-07
// NEAR: structure right, scheduling and allocation off: the zero-gravity arm (NormalizeOr, Scalar(speed)), the flight-time roots (Fpu::Sqrt twice, both roots computed before the test) and the launch vector are all in place, but retail computes the Scalar(speed) weight (mfc1, qmtc2) between the fallback load and the compare with vf2 for the weight and vf1 for the direction (ours the other way), stores a copy of the horizontal vector to the slot at 0x10 in the delay slot of the discriminant test, and has the discriminant in f2 with the root moved into it; ours differs in about ninety instructions of register choices.
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
#include "common.h"
#include "fpu.h"
#include "globals.h"
#include "vu0.h"

s32 func_001EE090(Vec02* from, Vec02* to, Vec02* out, u8* rec, f32 speed)
{
    Vec02 d;
    u8* g;
    if (rec != 0) {
        g = rec + 0x350;
    } else {
        g = (u8*)g_currentWorld + 0x1EE0;
    }
    f32 grav = *(f32*)(g + 8);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*to), Vu0::Q(*from));
    if (__builtin_fabsf(grav) < 1.0f) {
        u128 n = Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(D_00248D30));
        Vu0::Q(*out) = Vu0::MulX(n, Vu0::Scalar(speed));
        return 1;
    }
    f32 zero = 0.0f;
    f32 h = d.z;
    f32 sp2 = speed * speed;
    d.z = zero;
    f32 up = h >? zero;
    f32 gu = grav * up;
    u128 lv = Vu0::Length(Vu0::Q(d));
    f32 up2 = up * up;
    f32 half = grav * 0.25f;
    f32 dist = Vu0::ToFloat(lv);
    f32 b = gu + sp2;
    f32 dd = dist * dist;
    u128 dv = Vu0::Q(d);
    Vu0::Q(d) = Vu0::DivX(dv, lv);
    f32 c = grav * half;
    f32 disc = (-b) * (-b) - c * ((dd + up2) * 4.0f);
    if (disc < zero) {
        return 0;
    }
    f32 root = Fpu::Sqrt(disc);
    f32 den = c + c;
    f32 n1 = b - root;
    f32 n2 = b + root;
    f32 t1 = n1 / den;
    f32 t2 = n2 / den;
    f32 t;
    if (zero < t1) {
        t = t1;
    } else {
        if (!(zero < t2)) {
            return 0;
        }
        t = t2;
    }
    t = Fpu::Sqrt(t);
    Vu0::Q(d) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(dist / t));
    f32 z = (up - grav * (t * 0.5f) * t) / t;
    out->x = d.x;
    out->y = d.y;
    out->z = z;
    return 1;
}
