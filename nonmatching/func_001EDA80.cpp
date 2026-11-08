// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 384/392 (98.0%), checked 2026-11-08
// NEAR: night-size4: n as a Vu0::Vec (n = NormalizeOr(n, ...) gives retail's vmove into n's register and its size) and ToFloatMoved for the two dots divided (retail's zero and divide order). night-sizex2: the differences computed v, w, then u (retail loads b into vf1 and d into vf2). Still differs, 5 words: the last Dot's product takes vf2 and its 1.0 vf1 (retail the reverse); the Dot of Vecs, its operands swapped, StoreX, ToBits or ToFloat, the normal stored first, a new variable for the unit normal and NormalizeOrElse change nothing.
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
    u128 v = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    u128 w = Vu0::Sub(Vu0::Q(*d), Vu0::Q(*c));
    u128 u = Vu0::Sub(Vu0::Q(*c), Vu0::Q(*a));
    Vu0::Vec n;
    n.q = Vu0::Cross(v, w);
    f32 len2 = Vu0::ToFloat(Vu0::Dot(n.q, n.q));
    if (len2 < 0.0001f) {
        f32 z = 0.0f;
        out2[1] = z;
        out2[0] = z;
        n.q = u;
    } else {
        u128 c1 = Vu0::Cross(u, w);
        u128 c2 = Vu0::Cross(u, v);
        f32 d1 = Vu0::ToFloatMoved(Vu0::Dot(c1, n.q));
        f32 d2 = Vu0::ToFloatMoved(Vu0::Dot(c2, n.q));
        out2[0] = d1 / len2;
        out2[1] = d2 / len2;
        if (Vu0::ToFloat(Vu0::Dot(u, n.q)) < 0.0f) {
            n.q = Vu0::MulX(n.q, Vu0::Scalar(-1.0f));
        }
    }
    n = Vu0::NormalizeOr(n, Vu0::Vec::Of(g_unitZVector));
    Vu0::StoreX(*dist, Vu0::Dot(n.q, u));
    Vu0::Q(*normal) = n.q;
}
