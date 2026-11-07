// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 321/392 (81.9%), checked 2026-11-07
// NEAR: same code with ToFloat where retail ends with qmfc2 and sw of the dot product to the distance (ToBits), plus: retail loads b into vf1 and d into vf2 (ours the reverse), stores the two zero floats in the other order, loads its zero (mtc1 zero,f0) after the cross products, and keeps the normalised vector in a register copied by the compiler's own vmove (ours writes the divide straight into the register).
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
#include "common.h"
#include "globals.h"
#include "vu0.h"

void func_001EDA80(Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out2, f32* dist, Vec02* normal)
{
    u128 u = Vu0::Sub(Vu0::Q(*c), Vu0::Q(*a));
    u128 v = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    u128 w = Vu0::Sub(Vu0::Q(*d), Vu0::Q(*c));
    u128 n = Vu0::Cross(v, w);
    f32 len2 = Vu0::ToFloat(Vu0::Dot(n, n));
    if (len2 < 0.0001f) {
        f32 z = 0.0f;
        out2[0] = z;
        out2[1] = z;
        n = u;
    } else {
        u128 c1 = Vu0::Cross(u, w);
        u128 c2 = Vu0::Cross(u, v);
        f32 d1 = Vu0::ToFloat(Vu0::Dot(c1, n));
        f32 d2 = Vu0::ToFloat(Vu0::Dot(c2, n));
        out2[0] = d1 / len2;
        out2[1] = d2 / len2;
        if (Vu0::ToFloat(Vu0::Dot(u, n)) < 0.0f) {
            n = Vu0::MulX(n, Vu0::Scalar(-1.0f));
        }
    }
    u128 nn = Vu0::NormalizeOr(n, Vu0::Q(g_unitZVector));
    *dist = Vu0::ToFloat(Vu0::Dot(nn, u));
    Vu0::Q(*normal) = nn;
}
