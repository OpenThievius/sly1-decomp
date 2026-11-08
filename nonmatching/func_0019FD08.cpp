// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 92/100 (92.0%), checked 2026-11-07
// Tried night-close8: MinF(200.0f, limit) and MinF(c, limit), the float parameter first: the same two prologue words.
// NEAR: 2 lines differ: retail saves $f20 (swc1) before `move s0, a0`, ours after. ~20 compiles (order of the stores, locals for the world,
//       the slot and the product).
#include "common.h"
#include "effect.h"
#include "world.h"
#include "globals.h"

void InitEffect(Effect* self);

void func_0019FD08(Effect* self, f32 limit)
{
    InitEffect(self);
    f32 c = 200.0f;
    f32 v = c <? limit;
    self->i20 = (s32)g_currentWorld->slot1CE8[2];
    self->m30[0] = v;
    self->m30[1] = v * 0.6f;
}
