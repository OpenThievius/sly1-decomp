// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 164/168 (97.6%), checked 2026-11-08
// NEAR: right instructions and registers; differs only in the delay slot of the branch to the join. Retail puts max.s in the delay slot of `b` (an ordinary insn the scheduler can move there); the inline-asm Fpu::Max cannot be placed in a delay slot, so ours puts the join's swc1 there and duplicates it.
// Still differs (2026-11-08, night-close6): named locals for 0.0001, the level, 1.0, the difference; zero at function scope; the max through an inline MaxF in either order: the level and 0.0001 keep f2 and f1.
// Why (2026-11-08, tools/regalloc.py): local-alloc places 0.0001 (r129) before the level (r126):
// in sched1's order the level's load is set two insns before its sub and the constant's mtc1 one
// before its add, so the constant's span is shorter. Retail's sched1 must issue the constant before
// the load. `0.0001f + (1.0f - level)`, an eps local, a level local: the same order.
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
