// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 76/80, checked 2026-11-07
#include "common.h"
#include "effect.h"
#include "globals.h"
#include "placed_object.h"
#include "vu0.h"
s32 DrawEffectAt(void* self, void* a1, void* a2, void* a3);
// NEAR (2026-11-07, worker inline-vu0): the sequence is retail's (qmtc2, vadda.xyzw, vmaddx.xyzw,
// both stores), but retail loads +0x120 straight into a GPR (lw a0, after move v1,a0) for the
// qmtc2, where this loads it with lwc1 and moves it with mfc1; so the scale and D_00248D20 take
// each other's VU0 register. FromFloat taking a const f32 or a const f32& changes nothing.

void DrawSpinningEffect(Effect* self, void* a1)
{
    Vec02 pos;
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloat(self->f120);
    Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->q80), Vu0::Q(D_00248D20), Vu0::Q(k));
    DrawEffectAt(self, a1, &pos, self->rot50);
}
