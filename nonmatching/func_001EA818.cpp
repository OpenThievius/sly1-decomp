// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 248/256, checked 2026-11-07
// NEAR: u128 arguments and return (the compiler's own qmtc2 and qmfc2) match, as do the control flow and Scalar stores; retail stores the difference d at 0x30(sp) and loads it back (lqc2 vf3,0x30) for the length, then spills vf3 to 0x40 across the ApproachValueWithRamp call and reloads it (frame 0x80); here d is forwarded from the register (frame 0x70, no reload, no spill).
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
#include "common.h"
#include "globals.h"
#include "ramp_profile.h"
#include "vu0.h"

f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);

u128 func_001EA818(u128 from, u128 to, RampProfile* ramp, Vec02* vel, f32 limit)
{
    f32 step;
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(to, from);
    f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
    if (0.0001f < len) {
        f32 travel = ApproachValueWithRamp(ramp, &step, 0.0f, len, limit);
        if (vel != 0) {
            Vu0::Q(*vel) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(step / len));
        }
        return Vu0::MulAddX(from, Vu0::Q(d), Vu0::Scalar(travel / len));
    }
    if (vel != 0) {
        *vel = D_00248D30;
    }
    return to;
}
