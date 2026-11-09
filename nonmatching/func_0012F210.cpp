// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1167/1180 (98.9%), checked 2026-11-08
// NEAR (src/main/placed_object.cpp, where it is INCLUDE_ASM; 2026-11-08, night-untouched): the
// code is retail's but for two things, 17 lines. (1) The eval calls at t (the first and the
// bracketing loop's) set a2 before f12, retail f12 first; the third and fourth match. (2) The
// bracketing step and the upper end's dot take f25 and f26 the other way round (the step's f26
// is the halving's 0.5 after it). The step comes out in retail's f26 when the bracketing loop
// has one clamp, at its top (then the loop's layout is not retail's: retail clamps once before
// the loop and enters it at the eval), and when the evaluation goes through an inline wrapper
// taking the two out pointers (then &dir is formed afresh for each call, where retail keeps it
// in s4, and s7 is not saved). The floats first in the prototype give retail's s5 and s6.
// Tried: the declaration order of the float locals, the floats' places in the prototype, a
// named 0.5, a do-while bracketing loop, a struct of the position and direction.
// Also tried (night-close10): t as a copy of a renamed parameter, and the first call given the
// parameter with t assigned after (both change the allocation, 278 lines). func_001C9DE0's
// 0x1AC curve call shows the same a2-before-$f13 order against retail.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "animation.h"
#include "anim_curve.h"

struct ClampRange {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

// The time on a track's position curve, from t on, at which the point is level with the curve:
// where the point's offset from the curve's position turns from ahead of its direction to
// behind it (or back), unless the point is farther than the radius at t. A step of 0.2 either
// way brackets it, halving narrows the bracket to 0.05, and a linear step between its ends
// gives the time. The time, position and direction found are given where asked.
void func_0012F210(f32 end, f32 radius, f32 t, Track83* track, PlacedObject* owner, Vec02* point, f32* outT,
                   Vec02* outPos, Vec02* outDir)
{
    Vec02 pos;
    Vec02 dir;
    Vec02 d;
    Vec02 loPos;
    Vec02 hiPos;
    Vec02 loDir;
    Vec02 hiDir;
    f32 loT;
    f32 hiT;
    f32 loDot;
    f32 step;
    f32 hiDot;
    f32 dot;
    s32 behind;
    s32 far;

    track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &pos, &dir);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*point), Vu0::Q(pos));
    far = radius * radius < Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
    if (!far) {
        dot = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(dir)));
        if (__builtin_fabsf(dot) < 0.0001f) {
            goto done;
        }
        behind = 0;
        if (0.0f < dot) {
            loDot = dot;
            Vu0::Q(loPos) = Vu0::Q(pos);
            Vu0::Q(loDir) = Vu0::Q(dir);
            step = 0.2f;
            loT = t;
        } else {
            Vu0::Q(hiPos) = Vu0::Q(pos);
            hiDot = dot;
            Vu0::Q(hiDir) = Vu0::Q(dir);
            hiT = t;
            step = -0.2f;
            behind = 1;
        }
        t = ClampRange::Of(t + step, 0.0f, end);
        for (;;) {
            track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &pos, &dir);
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*point), Vu0::Q(pos));
            dot = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(dir)));
            if (behind != 0) {
                if (0.0f < dot || t == 0.0f) {
                    Vu0::Q(loPos) = Vu0::Q(pos);
                    loT = t;
                    Vu0::Q(loDir) = Vu0::Q(dir);
                    loDot = dot;
                    break;
                }
            } else if (dot < 0.0f || end - 0.0001f < t) {
                hiT = t;
                hiDot = dot;
                Vu0::Q(hiPos) = Vu0::Q(pos);
                Vu0::Q(hiDir) = Vu0::Q(dir);
                break;
            }
            t = ClampRange::Of(t + step, 0.0f, end);
        }
        while (0.05f < hiT - loT) {
            t = (hiT + loT) * 0.5f;
            track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &pos, &dir);
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*point), Vu0::Q(pos));
            dot = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(dir)));
            if (0.0f < dot) {
                loT = t;
                loDot = dot;
                Vu0::Q(loPos) = Vu0::Q(pos);
                Vu0::Q(loDir) = Vu0::Q(dir);
            } else {
                Vu0::Q(hiPos) = Vu0::Q(pos);
                hiT = t;
                Vu0::Q(hiDir) = Vu0::Q(dir);
                hiDot = dot;
            }
        }
        f32 span = hiDot - loDot;
        if (0.0001f < __builtin_fabsf(span)) {
            f32 u = ClampRange::Of(hiDot / span, 0.0f, 1.0f);
            t = loT * u + (1.0f - u) * hiT;
            track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &pos, &dir);
        } else {
            t = loT;
            pos = loPos;
            dir = loDir;
        }
    }
done:
    if (outT != 0) {
        *outT = t;
    }
    if (outPos != 0) {
        *outPos = pos;
    }
    if (outDir != 0) {
        *outDir = dir;
    }
}
