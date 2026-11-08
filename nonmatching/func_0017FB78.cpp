// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 200/204, checked 2026-11-08
// NEAR: night-size4: MaxF(0.0f, x) (an inline returning a >? b) gives case 0/2's max.s with the zero first, into its register, and sqrt.s into f0, as retail. Still: every instruction is right but the tail and the case registers. Retail reloads out->z from memory after the store (lwc1 8(a1)) and has a dead `li v1,3` in the tail; it multiplies into $f0 while sqrt.s writes $f1, ours reuses $f1 and keeps z in a register. No form of the tail found reproduces the reload. Found 2026-11-08: the dead `li v1,3` is what jump2 leaves of a compare with 3 whose two arms cross-jumping merged after reload: `if (self->f224C != 3) out->z = out->z >? v150.z; else (the same)` gives it, with an extra lw of f224C (a mem load is not deleted) and still no reload; with the mode in a local, the whole test vanishes before reload. Also tried (night-size4): the copy and z's store written in each case with the max after the switch gives retail's reload of out->z, but sched1 hoists each arm's lq/sq above its z, so cross-jumping merges only the swc1 (44 lines differ).
#include "common.h"
#include "fpu.h"
#include "switched_collider.h"

extern f32 D_00263E80;
extern f32 D_00263E84;
extern f32 D_00263E88;
extern f32 D_00263E8C;

static inline f32 MaxF(f32 a, f32 b) { return a >? b; }

s32 func_0017FB78(Player* self, Vec02* out)
{
    f32 z;
    switch (self->f224C) {
    case 1:
        z = D_00263E80 * Fpu::Sqrt(self->f700);
        break;
    case 4:
        z = D_00263E8C * Fpu::Sqrt(self->f700);
        break;
    case 3:
        z = D_00263E88 * Fpu::Sqrt(self->f700);
        break;
    case 0:
    case 2:
        z = Fpu::Sqrt(MaxF(0.0f, ((self->v140.z - (*(f32*)((u8*)self + 0x6A8) + D_00263E84)) + (self->v140.z - (*(f32*)((u8*)self + 0x6A8) + D_00263E84))) * self->gravity.z));
        break;
    }
    *out = self->v150;
    out->z = z;
    out->z = (out->z >? self->v150.z);
    return self->f2220;
}
