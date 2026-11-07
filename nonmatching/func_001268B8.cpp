// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 381/396 (96.2%), checked 2026-11-07
// NEAR: one swap: retail loads the 0.01 constant (lui, ori, mtc1 f1) before the qmfc2 of the cross product's length; ours after it (the constant as a named local, on either side of the compare, and the rows' statements in every order tried: the stores, the ScaledTransform's scales and the fallback address then match). The unnormalised length stays in vf4 as retail has it only when the fallback address is formed first (a pointer local).
// In the context of its file, src/main/placed_object.cpp.
// 0x1233C0 to 0x130F48: the state triggers (classes 0x22 and 0x2F), the placed object's set-up,
// update and loading (func_00123ED0 to func_001289C0), its range, sound and colour records, the
// code checksum, the animation players and their events, the id filter object, the sector stream
// reader and the curve segment helpers. One file between two edges; it could be several.
#include "common.h"
#include "mul_rotation.h"
#include "globals.h"

struct ScaledTransform {
    Quad16 q[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4c;
};
void BuildMatrixFromRotationAndTranslation(void* a, void* b, void* out);

void func_001268B8(PlacedObject* self, PlacedObject* b, Vec02* p, Vec02* q, f32 sx, f32 sy)
{
    Mat02 m;
    Vec02 e;
    ScaledTransform out;
    const Vec02* fallback = &D_00248D30;
    Vu0::Q(m.r[2]) = Vu0::Sub(Vu0::Q(*q), Vu0::Q(*p));
    Vu0::Q(e) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*(Vec02*)((u8*)b + 0x40)));
    u128 c = Vu0::Cross(Vu0::Q(e), Vu0::Q(m.r[2]));
    Vu0::Q(m.r[1]) = c;
    u128 len = Vu0::Length(c);
    if (Vu0::ToFloat(len) < 0.0001f) {
        m.r[1] = *fallback;
    } else {
        Vu0::Q(m.r[1]) = Vu0::DivX(c, len);
    }
    f32 minLen = 0.01f;
    if (minLen < Vu0::ToFloat(len)) {
        u128 c2 = Vu0::Cross(Vu0::Q(m.r[1]), Vu0::Q(m.r[2]));
        Vu0::Q(m.r[0]) = c2;
        Vu0::Q(m.r[0]) = Vu0::DivX(c2, Vu0::Length(c2));
        Vu0::Q(m.r[1]) = Vu0::MulX(Vu0::Q(m.r[1]), Vu0::Scalar(sx));
        Vu0::Q(m.r[2]) = Vu0::MulX(Vu0::Q(m.r[2]), Vu0::Scalar(minLen));
        BuildMatrixFromRotationAndTranslation(p, &m, &out);
        out.f44 = sy;
        out.f40 = sy;
        self->desc02()->m26(self, b, &out);
    }
}
