// SPDX-License-Identifier: AGPL-3.0-or-later
// The clamped quadratic record.
#ifndef CLAMPED_QUADRATIC_H
#define CLAMPED_QUADRATIC_H

#include "common.h"
#include "pair_controller.h"
#include "value_range.h"

// The coefficients of a quadratic in t (a + bt + ct^2), as the pose holds them.
typedef BlendQuad QuadraticCoeffs;

struct ClampedQuadratic {
    static f32 Eval(const QuadraticCoeffs* p, f32 t)
    {
        return p->a + t * (p->b + t * p->c);
    }
    static void Clamp(f32& c, f32 v, const ValueRange* r)
    {
        f32 lo = r->lo;
        f32 hi = r->hi;
        if (v < lo) {
            c = lo;
        } else if (hi < v) {
            c = hi;
        } else {
            c = v;
        }
    }
    static void Get(f32& c, const QuadraticCoeffs* p, f32 t)
    {
        Clamp(c, Eval(p, t), &g_unitRange);
    }
};

#endif
