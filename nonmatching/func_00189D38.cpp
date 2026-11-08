// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 548/544, checked 2026-11-07
// NEAR: night-lever2. ScalarOfGpr below (a GPR holding the length's bits qmtc2'd into the Scalar slot, beside ToFloatMoved) gives retail's qmfc2.ni v0 used for both the mtc1 and the qmtc2.ni v0,vf4; it would be a helper for vu0.h. Still differs: the frame, 112 against retail's 96: ours keeps &axis (addiu s0,sp,32) in a callee-saved register and out in s1, where retail keeps out in s0 and forms addiu a0,sp,32 after Arccosine's call; the scheduling of the head follows (lq of the fallback and the order of the mtc1/c.lt). Computing Arccosine first, or casting the address, changes nothing.
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
static inline u128 ScalarOfGpr(u128 g)
{
    Vu0::Slot t;
    u128 r;
    __asm__("qmtc2 %1, %0" : "=j"(r) : "r"(g));
    Vu0::Q(t) = r;
    return Vu0::Q(t);
}
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
    Vu0::Set(axis, Vu0::DivX(Vu0::Q(axis), ScalarOfGpr(len)));
    BuildAxisAngleMatrix(&axis.x, out, Arccosine(Vu0::ToFloat(cosine)));
}
