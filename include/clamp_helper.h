// SPDX-License-Identifier: AGPL-3.0-or-later
// A float clamped between a minimum and a maximum, as the game's files write it.
#ifndef CLAMP_HELPER_H
#define CLAMP_HELPER_H

#include "common.h"

struct ClampHelper {
    static f32 Of(f32 v, f32 lo, f32 hi)
    {
        if (v < lo)
            return lo;
        if (hi < v)
            return hi;
        return v;
    }
};

#endif
