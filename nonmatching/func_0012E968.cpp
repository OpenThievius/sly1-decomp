// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 28/120 (23.3%), checked 2026-11-01
// Near miss: the clamped linear interpolation is modeled, but the compiler
// reverses the boundary branch and assigns the float temporaries differently.
#include "common.h"

struct Range_12E968 { u32 field0; f32 minimum; f32 maximum; };
struct Obj_12E968 { u8 pad0[8]; Range_12E968* range; };

f32 func_0012E968(Obj_12E968* self, f32 value)
{
    Range_12E968* range = self->range;
    f32 minimum = range->minimum;
    if (minimum > value) {
        return 1.0f;
    }
    f32 maximum = range->maximum;
    if (maximum <= value) {
        return 0.15f;
    }
    f32 denominator = minimum - maximum;
    f32 numerator = value - maximum;
    f32 ratio = numerator / denominator;
    f32 scaled = ratio * 0.85f;
    return scaled + 0.15f;
}
