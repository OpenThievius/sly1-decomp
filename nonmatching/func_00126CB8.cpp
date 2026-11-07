// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 164/168 (97.6%), checked 2026-11-07
// NEAR: right instructions and registers; differs only in the delay slot of the branch to the join. Retail puts max.s in the delay slot of `b` (an ordinary insn the scheduler can move there); the inline-asm Fpu::Max cannot be placed in a delay slot, so ours puts the join's swc1 there and duplicates it.
#include "common.h"
#include "fpu.h"
#include "placed_object.h"
#include "collider.h"

s32 IsObjectAttached(PlacedObject* self);
void EnsureObjectWorldNode(PlacedObject* self);

void func_00126CB8(Collider* self, f32 time)
{
    if (!IsObjectAttached(self) || self->f298 != 0) {
        EnsureObjectWorldNode(self);
        self->desc->m02(self);
        f32 rate;
        if (time == 0.0f) {
            f32 zero = 0.0f;
            rate = zero >? 1.0f - self->f298->level + 0.0001f;
        } else {
            rate = 1.0f / time;
        }
        self->f298->rate = rate;
    }
}
