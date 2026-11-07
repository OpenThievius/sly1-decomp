// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 200/204, checked 2026-11-07
// NEAR: every instruction is right but the tail and the case registers. Retail reloads out->z from memory after the store (lwc1 8(a1)) and has a dead `li v1,3` in the tail; it multiplies into $f0 while sqrt.s writes $f1, ours reuses $f1 and keeps z in a register. No form of the tail found reproduces the reload.
#include "common.h"
#include "fpu.h"
#include "switched_collider.h"

extern f32 D_00263E80;
extern f32 D_00263E84;
extern f32 D_00263E88;
extern f32 D_00263E8C;

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
        z = Fpu::Sqrt(Fpu::Max(0.0f, ((self->v140.z - (*(f32*)((u8*)self + 0x6A8) + D_00263E84)) + (self->v140.z - (*(f32*)((u8*)self + 0x6A8) + D_00263E84))) * self->gravity.z));
        break;
    }
    *out = self->v150;
    out->z = z;
    out->z = Fpu::Max(out->z, self->v150.z);
    return self->f2220;
}
