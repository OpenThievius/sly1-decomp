// SPDX-License-Identifier: AGPL-3.0-or-later
// The quadratic curve record.
#ifndef QUADRATIC_CURVE_H
#define QUADRATIC_CURVE_H

#include "common.h"

struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

#endif
