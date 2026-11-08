// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 548/544, checked 2026-11-07
// NEAR: wave 4 e3. 544 bytes; ours 548, frame 112 against retail's 96. The shape is retail's (both vectors normalised with the unit Z as fallback, the cross and its two fallbacks on X and Y,
//       the cosine, the axis divided by its length, Arccosine, BuildAxisAngleMatrix). It needs a helper the header lacks: retail keeps the length that the last Length left in v0 (qmfc2.ni v0, vf2)
//       and uses that same GPR twice: mtc1 v0, f1 for the compare and qmtc2.ni v0, vf4 for the DivX (0x189EFC: qmtc2.ni v0,vf4; lqc2 vf1,0x10(sp); lqc2 vf3,0x20(sp); ... vdiv Q,vf0w,vf4x;
//       vmulq.xyzw vf3,vf3,Q; qmfc2.ni v0,vf2; mtc1 v0,f12; sqc2 vf3,0x20(sp); jal Arccosine; sqc2 vf4,0x30(sp)). Ours goes through an FPR (mtc1, then mfc1 and qmtc2) and a second slot.
//       The helper: a vector from a GPR holding a float's bits (qmtc2 of an "r" u128/u32 operand, stored to the Scalar slot) beside ToFloatMoved. ~8 compiles.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "shapes.h"
#include "vu0.h"

extern u8 g_unitXVector[];
extern u8 g_unitYVector[];
extern u8 g_unitZVector[];
f32 Arccosine(f32 x);
void BuildAxisAngleMatrix(f32* axis, Mat4* mat, f32 angle);
void func_00189D38(Vec02* from, Vec02* to, Mat4* out)
{
    Vec02 a = *from;
    Vec02 b = *to;
    Vec02 axis;
    Vec02& z = *(Vec02*)g_unitZVector;
    Vu0::Q(a) = Vu0::NormalizeOr(Vu0::Q(a), Vu0::Q(z));
    u128 bn = Vu0::NormalizeOr(Vu0::Q(b), Vu0::Q(z));
    Vu0::Set(b, bn);
    Vu0::Set(axis, Vu0::Cross(Vu0::Q(a), bn));
    u128 len = Vu0::Length(Vu0::Q(axis));
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        Vu0::Set(axis, Vu0::Cross(Vu0::Q(*(Vec02*)g_unitXVector), Vu0::Q(a)));
        len = Vu0::Length(Vu0::Q(axis));
        if (Vu0::ToFloatMoved(len) < 0.0001f) {
            Vu0::Set(axis, Vu0::Cross(Vu0::Q(*(Vec02*)g_unitYVector), Vu0::Q(a)));
            len = Vu0::Length(Vu0::Q(axis));
        }
    }
    u128 cosine = Vu0::Dot(Vu0::Q(a), Vu0::Q(b));
    Vu0::Set(axis, Vu0::DivX(Vu0::Q(axis), Vu0::Scalar(Vu0::ToFloatMoved(len))));
    BuildAxisAngleMatrix(&axis.x, out, Arccosine(Vu0::ToFloat(cosine)));
}
