// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 218/228 (95.6%), checked 2026-11-07
// NEAR: EvaluateAxisCurves. Only the delay slot of the call through the curve's table differs: retail puts the move of the flags (a2) there and sets f12 and f13 before it; ours sets a2 first and puts the move of the scale (f13) in the slot. Ten forms of the call (locals, the table slot first, the pointers as locals) give the same order.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "anim_curve.h"

void func_0011F6B0(WeightCurve** axis, PlacedObject* other, s32 flags, Vec02* base, f32* outValues, f32* outSlopes, f32 key, f32 scale)
{
    if (outValues)
        *(Vec02*)outValues = *base;
    if (outSlopes)
        Vu0::Q(*(Vec02*)outSlopes) = Vu0::Zero();
    for (s32 i = 0; i < 3; i++) {
        WeightCurve* curve = axis[i];
        if (curve)
            curve->vt->eval(curve, other, flags, outValues ? outValues + i : 0, outSlopes ? outSlopes + i : 0, key, scale);
    }
}
