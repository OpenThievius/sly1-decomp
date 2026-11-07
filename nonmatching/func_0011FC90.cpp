// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 281/292 (96.2%), checked 2026-11-07
// NEAR: ReadAxisPositionCurve. Everything is retail's except the order of the argument moves of the second call through the curve's table: retail sets f13 (the scale 1.0 kept in f20) and f12 before a3 (&b) and puts `move t0,zero` in the delay slot; ours sets a3 first and puts the f13 move in the slot. The first call is identical. Tried: the scale as a local, a Vec02[2], a local for the last time, the locals in the other order (moves the frame).
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "attachment.h"
#include "anim_curve.h"
#include "globals.h"
#include "buffered_stream.h"
#include "script_value.h"

extern void ReadAxisCurves(WeightCurve**, Vec02*, Stream83*);
extern void PushBackMemoryMark(void);
extern void PopBackMemoryMark(void);

void ReadAxisPositionCurve(AxisPositionCurve* self, Stream83* arg)
{
    Vec02 v[2];
    s32 count;
    f32* values;
    s32 result;

    ReadAxisCurves(self->axis, &self->base, arg);
    PushBackMemoryMark();
    self->vt->times(self, &count, &values);
    if (count != 0) {
        self->vt->eval(self, 0, 0, &v[0], 0, values[0], 1.0f);
        self->vt->eval(self, 0, 0, &v[1], 0, values[count - 1], 1.0f);
        result = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(v[0]), Vu0::Q(v[1])))) < 1.0f;
    } else {
        result = 1;
    }
    *(s32*)((u8*)self + 8) = result;
    PopBackMemoryMark();
}
