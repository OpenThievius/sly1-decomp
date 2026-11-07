// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 156/152, checked 2026-11-07
// NEAR: the body and registers match; the scheduling differs. Retail schedules the loads of D_00274B5C and of the pad's +0x48 above the frame setup and keeps the pad in a1 across the call (no move a1,s1). Retail's max.s is an ordinary insn (sched1 hoists around it); the volatile inline-asm Fpu::Max stops that, a non-volatile one hoists too much and breaks func_001EAC68.
#include "common.h"
#include "fpu.h"
#include "switched_collider.h"
#include "globals.h"
#include "pad_record.h"

extern f32 D_00274B5C;
void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);

void func_001C49E8(TurningCollider* self, PadRecord* pad)
{
    D_00274B5C = Fpu::Max(D_00274B5C - 0.25f, 0.0f);
    if (D_00274B5C < pad->f48) {
        ComputeCameraRelativeStickHeading(g_camera, pad, 0, &self->f630);
    } else {
        self->f630 = self->f638;
    }
    f32 level = pad->f48;
    self->f634 = level;
    D_00274B5C = level;
}
