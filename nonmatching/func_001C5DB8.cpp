// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 156/152, checked 2026-11-07
// NEAR: right instructions; differs in the load of the angle for FromFloat (retail lw v0,16(sp), a GPR load; ours lwc1+mfc1) and in the order of the move of a1 before the call. FromFloat takes an f32, which GCC loads through an FPR; retail's helper took the word in a GPR.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "vu0.h"
#include "globals.h"
#include "object_link.h"
#include "attachment.h"
#include "pad_record.h"

f32 ArctangentOfRatio(f32 a, f32 b);
f32 ApproachAngleWithRamp(void* p, void* out, f32 a, f32 b, f32 c);
void BuildAxisAngleMatrix(const Vec02* t, f32 x, void* p);

void func_001C5DB8(TurningCollider* self, void* matrix, Vec02* out, f32 limit)
{
    f32 turn;
    f32 r = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 angle = ApproachAngleWithRamp((u8*)self + 0x6E0, &turn, r, self->f638, limit);
    BuildAxisAngleMatrix(&g_unitZVector, angle, matrix);
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloat(turn);
    Vu0::Q(*out) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Q(k));
}
