// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 136/132, checked 2026-11-07
// NEAR: right instructions and registers; differs only in the delay slot of the branch to the join. Retail puts min.s in the delay slot of `b`; the inline-asm Fpu::Min cannot be placed in a delay slot, so ours puts the join's swc1 there and duplicates it. With -ffast-math the plain ternary gets this layout (only the operand order of min.s differs), so retail's min.s is an ordinary insn.
#include "common.h"
#include "fpu.h"
#include "placed_object.h"
#include "collider.h"

s32 IsObjectAttached(PlacedObject* self);
void EnsureObjectWorldNode(PlacedObject* self);

void func_00126D60(Collider* self, f32 time)
{
    if (IsObjectAttached(self)) {
        EnsureObjectWorldNode(self);
        f32 rate;
        if (time == 0.0f) {
            rate = Fpu::Min(0.0f, -self->f298->level - 0.0001f);
        } else {
            rate = -1.0f / time;
        }
        self->f298->rate = rate;
    }
}
