// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 72/80, checked 2026-11-07
#include "common.h"
#include "effect.h"
#include "globals.h"
#include "placed_object.h"
#include "vu0.h"
s32 DrawEffectAt(void* self, void* a1, void* a2, void* a3);
// NEAR (2026-11-08, wave 3 retry): FromFloatAt gives retail's lw, but not its allocation:
// retail copies self into v1 (move v1,a0 first, lw a0,288(v1), move a0,v1 before the vadda) and
// loads the weight (vf2) before D_00248D20 (vf3), forming a3 last, in the delay slot of the
// call; here self stays in a0, D_00248D20 is loaded first and a3 is formed early. Seven forms
// (k before or after pos, a u128 shared by the store and the product, an f32 local, &rot50[0])
// give the same.
void DrawSpinningEffect(Effect* self, void* a1)
{
    Vec02 pos;
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloatAt(self->f120);
    Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->q80), Vu0::Q(D_00248D20), Vu0::Q(k));
    DrawEffectAt(self, a1, &pos, self->rot50);
}
