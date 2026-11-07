// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 153/224 (68.3%), checked 2026-11-07
#include "common.h"
#include "effect.h"
#include "world.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-a): the streak from the place along the velocity's direction,
// 100 long, drawn with the world's template slot 11, or DrawEffectAt in the velocity's frame.
// Retail keeps the velocity in vf1 (the Dot's result vf3, its 1.0 vf2), loads the world pointer
// between the Dot and the square root, and stores the unnormalised velocity to dir late; here
// the velocity takes vf3 and the loads and stores come after the VU work.

void func_001268B8(BaseObject* tmpl, void* a1, Vec02* from, Quad219C* to, f32 width, f32 alpha);
void BuildBasisFromXAndYHint(Quad219C* x, void* hint, Mat02* out);
s32 DrawEffectAt(void* self, void* a1, void* a2, void* a3);

void DrawStreakedEffect(Effect* self, void* a1)
{
    if (self->i20 == 0) {
        Vec02 dir;
        Vec02 tail;
        Vec02 k;
        u128 v = Vu0::Q(self->qA0);
        Vu0::Q(dir) = v;
        Vu0::Q(dir) = Vu0::DivX(v, Vu0::Length(v));
        Vu0::Q(k) = Vu0::FromFloat(100.0f);
        Vu0::Q(tail) = Vu0::MulAddX(Vu0::Q(self->q80), Vu0::Q(dir), Vu0::Q(k));
        func_001268B8(g_currentWorld->slot1CE8[11], a1, &tail, &self->q80, 10.0f, 1.0f);
    } else {
        Mat02 rot;
        BuildBasisFromXAndYHint(&self->qA0, (u8*)a1 + 0x80, &rot);
        DrawEffectAt(self, a1, &self->q80, &rot);
    }
}
