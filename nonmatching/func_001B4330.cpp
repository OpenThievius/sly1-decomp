// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 600/592, checked 2026-11-08
#include "common.h"
#include "vu0.h"
// NEAR (2026-11-08, worker night-mmi): the six sectors, the jump table (0 and 6 one case) and
// FromFloats in each match; the clamps differ: retail loads the hue into $f12 and clamps it
// straight into $f21 with its 0 shared with the sign test, and gives the value's clamp a
// branch-likely form ending in mtc1 zero, $f1 (the 0 the saturation test reads); here the hue
// takes $f0, its clamp $f12, and the frame saves $f20 before $f21. regdiff: code, 128/148.

struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };

f32 RoundDown(f32 x);

// A value clamped to [lo, hi], as an inline function of its own: each clamp of ConvertHsvToRgb
// sets its 0 and 1 again.
static inline f32 ClampTo(f32 v, f32 lo, f32 hi)
{
    f32 r;
    if (v < lo) r = lo;
    else if (hi < v) r = hi;
    else r = v;
    return r;
}

void ConvertHsvToRgb(Quad_001B4580* hsv, Quad_001B4580* rgb)
{
    f32 h;
    if (0.0f <= hsv->v[0]) {
        h = ClampTo(hsv->v[0], 0.0f, 360.0f);
    } else {
        h = -1.0f;
    }
    f32 s = ClampTo(hsv->v[1], 0.0f, 1.0f);
    f32 v = ClampTo(hsv->v[2], 0.0f, 1.0f);
    if (s == 0.0f) {
        Vu0::Q(*rgb) = Vu0::FromFloats(v, v, v);
        return;
    }
    if (h == 360.0f) h = 0.0f;
    h *= 0.016666668f;
    s32 i = (s32)RoundDown(h);
    f32 f = h - (f32)i;
    f32 p = v * (1.0f - s);
    f32 q = v * (1.0f - s * f);
    f32 t = v * (1.0f - s * (1.0f - f));
    switch (i) {
    case 0:
    case 6:
        Vu0::Q(*rgb) = Vu0::FromFloats(v, t, p);
        break;
    case 1:
        Vu0::Q(*rgb) = Vu0::FromFloats(q, v, p);
        break;
    case 2:
        Vu0::Q(*rgb) = Vu0::FromFloats(p, v, t);
        break;
    case 3:
        Vu0::Q(*rgb) = Vu0::FromFloats(p, q, v);
        break;
    case 4:
        Vu0::Q(*rgb) = Vu0::FromFloats(t, p, v);
        break;
    case 5:
        Vu0::Q(*rgb) = Vu0::FromFloats(v, p, q);
        break;
    }
}
