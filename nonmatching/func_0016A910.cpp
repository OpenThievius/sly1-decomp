// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 209/260 (80.4%), checked 2026-11-07
// NEAR: scheduling only: every instruction is right, but retail loads the 0x560 float and the 70.0 constant (lwc1, lui, mtc1) before the first vmul.xyz of the normalisation and the add.s after the square root; here they come after the vaddq.x, and the qmfc2 and the 0.0001 constant move with them. Five orderings of the weight (inside the arguments, a local before the call, a Scalar before it) tried.
// In the context of its file, src/main/file_167D68.cpp.
#include "common.h"
#include "globals.h"
#include "vu0.h"

void* GetActiveSwitchedCollider(void);
f32 WrapAngle(f32 a);
f32 ArctangentOfRatio(f32 y, f32 x);

void func_0016A910(PlacedObject* self, Vec02* out, f32* angleOut)
{
    Vec02 d;
    PlacedObject* active = (PlacedObject*)GetActiveSwitchedCollider();
    u128 p = Vu0::Q(self->v140);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(active->v140), p);
    d.z = 0.0f;
    if (out) {
        u128 k = Vu0::Scalar(*(f32*)((u8*)self + 0x560) + 70.0f);
        Vu0::Q(*out) = Vu0::MulAddX(p, Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector)), k);
    }
    if (angleOut) {
        *angleOut = WrapAngle(ArctangentOfRatio(d.y, d.x) + 3.14159274f);
    }
}
