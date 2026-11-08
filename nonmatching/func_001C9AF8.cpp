// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 489/508 (96.3%), checked 2026-11-07
// NEAR: 4 words differ in two places: retail loads the constant's address into $v1 (ours $v0) and
//       qmtc2's the weight (time) after `lq` of the target, before `lqc2 vf1, 0x350(s0)`; ours
//       qmtc2's it first. Everything else matches, including the dead stores of the weights
//       (the -1 weight is stored after the rotation, as a local assigned last). About 25 compiles
//       (order of the three stores, the weight in a nested block, Scalar or FromFloat).
#include "common.h"
#include "switched_collider.h"
#include "globals.h"
#include "vu0.h"

extern f32 g_gameTime[];
f32 ArctangentOfRatio(f32 a, f32 b);
#define F(T, o) (*(T*)((u8*)self + (o)))

f32 ClampToRange(void* range, f32 x);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);

void func_001C9AF8(Agent* self)
{
    s32 last = self->f92C - 1;
    s32 n = self->f930;
    n = (n < last) ? n : last;
    Vec02 target;
    Vu0::Q(target) = Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (n << 4)));
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140));
    f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d))));
    f32 t = ClampToRange((u8*)self + 0xB9C, dist / __builtin_fabsf(F(f32, 0xB94)));
    f32 time = t * F(f32, 0xB98);
    Vec02 vel;
    Vu0::Q(vel) = Vu0::MulXSum(Vu0::Q(d), Vu0::Scalar(1.0f / time), Vu0::Q(F(Vec02, 0x350)), Vu0::Scalar(time * -0.5f));
    self->desc02()->m20(self, &vel);
    f32 speed = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d))));
    F(f32, 0xBA4) = g_gameTime[0] + time;
    F(Vec02, 0xBB0) = target;
    u128 pos = Vu0::MulAddX(Vu0::Q(vel), Vu0::Q(F(Vec02, 0x350)), Vu0::Scalar(time));
    Vu0::Q(F(Vec02, 0xBC0)) = pos;
    if (1.0f < speed) {
        f32 ang = ArctangentOfRatio(d.y, d.x);
        if (F(f32, 0xB94) < 0.0f) ang += 3.14159265f;
        SetAgentFacingAngles(self, ang, 0.0f);
        Vec02 w;
        u128 s = Vu0::FromFloat(-1.0f);
        u128 r = Vu0::RotateTransposed(F(Mat02, 0x660), Vu0::MulX(Vu0::Q(vel), s));
        Vu0::Q(w) = s;
        Vu0::Q(F(Vec02, 0x640)) = r;
    } else {
        F(Vec02, 0x640) = D_00248D30;
    }
}
