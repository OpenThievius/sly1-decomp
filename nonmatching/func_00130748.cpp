// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 967/1024 (94.4%), checked 2026-11-08
// BYTES 0/0, checked 2026-11-07
// NEAR (2026-11-07, worker night-large1): the rotation's Hermite step (two rotations and their
// spins, at t of dur, into a rotation and a spin), all its code in retail's order, 31 instructions
// off in registers: wa, wb and outW take s5, s6, s7 where retail has s6, s7, s5; v (1 - u) takes
// f4 where retail has f12, so the angle's product and the length swap f0/f12 for f12/f2; and in
// the spin the axis and the third weight swap vf3/vf4, the last scaling keeping vf1 where retail
// takes vf3. Floats first in the prototype and Vec values for the spin leave all of it.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "timed_object.h"
#include "transform_object.h"
#include "state_walker.h"
#include "screen_element.h"
#include "masked_collider.h"
#include "world.h"
#include "animation.h"
#include "attachment.h"
#include "anim_curve.h"
#include "range_record.h"
#include "cursor_animator.h"
#include "sound_record.h"
#include "object_link.h"
#include "target_binding.h"
#include "globals.h"
#include "object_cycler.h"
#include "paired_object.h"
#include "code_checksum.h"
#include "switched_collider.h"
#include "shapes.h"
#include "id_filter_object.h"
#include "c8b.h"
#include "object_message.h"
#include "queued_call.h"
#include "stream_reader.h"
#include "key_id.h"
#include "game_progress.h"
#include "base_object.h"
#include "stream_reader_window.h"
extern void MultiplyMatrices3x3(void*, void*, void*);
extern void MatrixToAxisAngle(void*, void*, void*);

void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

// v made unit length where it is, or fallback when shorter than 0.0001: its length.
static inline u128 NormalizeAxis(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Q(v) = Vu0::DivX(Vu0::Q(v), len);
    }
    return len;
}

void func_00130748(Mat02* a, Vec02* wa, Mat02* b, Vec02* wb, Mat02* out, Vec02* outW, f32 dur, f32 t, f32 e)
{
    f32 u = t / dur;
    f32 v = 1.0f - u;
    if (out != 0) {
        Vec02 axis;
        Mat02 m1;
        Mat02 m2;
        Mat02 rot;
        f32 uu = u * u;
        f32 uv = u * v;
        f32 uuv = uu * v;
        f32 uuu = uu * u;
        f32 uvv = uv * v;
        u128 len;
        Vu0::Q(axis) = Vu0::Q(*wa);
        len = NormalizeAxis(axis, g_unitZVector);
        BuildAxisAngleMatrix(&axis, &rot, uvv * dur * Vu0::ToFloat(len));
        MulRotationRowsX(&m1, rot, *a);
        Vu0::Q(axis) = Vu0::Q(*wb);
        len = NormalizeAxis(axis, g_unitZVector);
        BuildAxisAngleMatrix(&axis, &rot, -uuv * dur * Vu0::ToFloat(len));
        MulRotationRowsX(&m2, rot, *b);
        MultiplyMatrices3x3(&m1, &m2, &rot);
        f32 angle;
        MatrixToAxisAngle(&rot, &angle, &axis);
        BuildAxisAngleMatrix(&axis, &rot, angle * (uuv * (3.0f - dur) + uuu));
        MulRotationRowsX(out, rot, m1);
    }
    if (outW != 0) {
        Mat02 d;
        Vec02 axis;
        f32 angle;
        MultiplyMatrices3x3(a, b, &d);
        MatrixToAxisAngle(&d, &angle, &axis);
        f32 w1 = angle * u * (6.0f - u * 6.0f) / dur;
        f32 w2 = 1.0f - u * (4.0f - u * 3.0f);
        f32 w3 = u * (u * 3.0f + -2.0f);
        Vu0::Vec r = Vu0::MulXSum3(Vu0::Vec::Of(axis), Vu0::Vec::Scalar(w1), Vu0::Vec::Of(*wa), Vu0::Vec::Scalar(w2),
                                   Vu0::Vec::Of(*wb), Vu0::Vec::Scalar(w3));
        Vu0::Q(*outW) = Vu0::MulX(r, Vu0::Vec::Scalar(e)).q;
    }
}
