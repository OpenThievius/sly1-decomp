// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 708/724 (97.8%), checked 2026-11-08
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call 1 (source line 39); 19 differing lines before, 5 now.
// NEAR: every register, the frame (0x110) and the branches are retail's; only the two dead stores of the segment vector differ in place, as in func_0014D680: the copy at 0x30 comes before the vdiv where retail's follows the vmulq, and the unit vector at 0x20 before the compare where retail's is in the bc1f delay slot. Found: the copy's block scope makes the Scalar of the point blend share its slot (0x30); the loop on an index (pts[i]) gives retail's s0 pointer / s1 index; the literal 3.4028234663852886e+38f is retail's bound (the checker's rodata message is only the instruction offset); the tail is NormalizeCopy (length of the vmove copy, DivX of the original). Written with Vu0::Vec for the segment (Vec::Of, Length, DivX on .q) the copy's store is dropped altogether.
// Tried (2026-11-08, night-close9): the copy and the unit vector's stores moved after the dot in the C: the scheduler puts them back.
// In the context of its file, src/main/path_curve.cpp.
#include "common.h"
#include "vu0.h"
#include "globals.h"
#include "path_curve.h"
#include "placed_object.h"

void ConstrainVectorByAnchor(void* self, void* a, void* b, s32 c);

static inline u128 NormalizeCopy(u128 v, u128 c, u128 fallback)
{
    u128 len = Vu0::Length(c);
    if (Vu0::ToFloat(len) < 0.0001f) {
        return fallback;
    }
    return Vu0::DivX(v, len);
}

void func_0014D3A8(Vec02* pos, void* anchor, s32 n, Vec02* pts, Vec02* outPoint, Vec02* outDir, s32* outIdx, f32* outT)
{
    s32 best = -1;
    f32 frac = -1.0f;
    f32 bestDist = 3.4028234663852886e+38f;
    s32 count = n - 1;
    for (s32 i = 0; i < count; i++) {
        Vec02 d, pt, e;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(pts[i]));
        Vu0::Q(e) = Vu0::Sub(Vu0::Q(pts[i + 1]), Vu0::Q(pts[i]));
        if (anchor != 0) {
            ConstrainVectorByAnchor(anchor, &d, &d, 0);
            ConstrainVectorByAnchor(anchor, &e, &e, 0);
        }
        Vu0::Vec ev = Vu0::Vec::Of(e);
        Vu0::Vec len = Vu0::Length(ev);
        f32 lenF = Vu0::ToFloatMoved(len);
        Vu0::Vec unit;
        unit.q = Vu0::DivX(ev.q, len.q);
        {
            Vec02 e0;
            Vu0::Q(e0) = ev.q;
        }
        f32 t = Vu0::ToFloat(Vu0::Dot(unit, Vu0::Vec::Of(d)));
        Vu0::Q(e) = unit.q;
        f32 c = t;
        if (t < 0.0f) {
            c = 0.0f;
        } else if (lenF < t) {
            c = lenF;
        }
        Vu0::Q(pt) = Vu0::MulAddX(Vu0::Q(d), Vu0::Q(e), Vu0::Scalar(-c));
        f32 dist = Vu0::ToFloat(Vu0::Dot(Vu0::Q(pt), Vu0::Q(pt)));
        if (dist < bestDist) {
            frac = c / lenF;
            bestDist = dist;
            best = i;
        }
    }
    if (outIdx != 0) {
        *outIdx = best;
    }
    if (outT != 0) {
        *outT = frac;
    }
    if (outPoint != 0) {
        Vu0::Q(*outPoint) = Vu0::MulXSum(Vu0::Q(pts[best]), Vu0::Scalar(1.0f - frac), Vu0::Q(pts[best + 1]), Vu0::Scalar(frac));
    }
    if (outDir != 0) {
        u128 dir = Vu0::Sub(Vu0::Q(pts[best + 1]), Vu0::Q(pts[best]));
        u128 cp = Vu0::Copy(dir);
        Vu0::Q(*outDir) = cp;
        Vu0::Q(*outDir) = NormalizeCopy(dir, cp, Vu0::Q(g_unitXVector));
    }
}
