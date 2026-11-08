// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 602/692 (87.0%), checked 2026-11-08
// NEAR: same instructions, frame (0xE0) and branches as retail; only the schedule of three groups differs: the two dead stores of the segment vector (e0 at 0x20, the unit vector at 0x0) come before the vdiv / before the compare where retail sinks them after the dot product and into the bc1f delay slot, and the prologue's addiu s2,sp,16 comes after the callee-saved saves where retail interleaves it. The tail (outDir normalised with the vmove copy stored first) matches. Found: d in the loop body shares its slot with the Scalar of the point blend (e outside the loop); outDir's length from a Vu0::Copy, its DivX from the original. permute.py --auto: 48 bytes differ at best.
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

void func_0014D680(Vec02* pos, void* anchor, s32 n, Vec02* pts, s32 idx, s32 wrap, Vec02* outPoint, Vec02* outDir, s32* outIdx, f32* outT)
{
    s32 back = 0;
    s32 fwd = 0;
    f32 frac;
    Vec02 e;
    for (;;) {
        Vec02 d, e0;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(pts[idx]));
        Vu0::Q(e) = Vu0::Sub(Vu0::Q(pts[idx + 1]), Vu0::Q(pts[idx]));
        if (anchor != 0) {
            ConstrainVectorByAnchor(anchor, &d, &d, 0);
            ConstrainVectorByAnchor(anchor, &e, &e, 0);
        }
        u128 len = Vu0::Length(Vu0::Q(e));
        f32 lenF = Vu0::ToFloat(len);
        u128 unit = Vu0::DivX(Vu0::Q(e), len);
        f32 t = Vu0::ToFloat(Vu0::Dot(unit, Vu0::Q(d)));
        Vu0::Q(e0) = Vu0::Q(e);
        Vu0::Q(e) = unit;
        if (t < 0.0f) {
            if (fwd != 0) {
                frac = 0.0f;
                break;
            }
            if (idx > 0) {
                idx--;
            } else if (wrap != 0) {
                idx = n - 2;
            } else {
                frac = 0.0f;
                break;
            }
            back = 1;
            continue;
        }
        if (!(lenF < t)) {
            frac = t / lenF;
            break;
        }
        if (back != 0) {
            frac = 1.0f;
            break;
        }
        if (idx < n - 2) {
            idx++;
        } else if (wrap != 0) {
            idx = 0;
        } else {
            frac = 1.0f;
            break;
        }
        fwd = 1;
    }
    if (outIdx != 0) {
        *outIdx = idx;
    }
    if (outT != 0) {
        *outT = frac;
    }
    if (outPoint != 0) {
        Vu0::Q(*outPoint) = Vu0::MulXSum(Vu0::Q(pts[idx]), Vu0::Scalar(1.0f - frac), Vu0::Q(pts[idx + 1]), Vu0::Scalar(frac));
    }
    if (outDir != 0) {
        u128 dir = Vu0::Sub(Vu0::Q(pts[idx + 1]), Vu0::Q(pts[idx]));
        u128 c = Vu0::Copy(dir);
        Vu0::Q(*outDir) = c;
        Vu0::Q(*outDir) = NormalizeCopy(dir, c, Vu0::Q(g_unitXVector));
    }
}
