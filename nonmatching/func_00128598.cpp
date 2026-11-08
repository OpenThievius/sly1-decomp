// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 832/852, checked 2026-11-07
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
#include "world.h"
#include "object_cycler.h"
#include "paired_object.h"
// NEAR (2026-11-08, wave 4): func_00128598 (a follow step: the object's offset from its attachment's position, damped by a polynomial of the distance, handed to ConvertOffsetToSpherical): the first 60 instructions are retail's and the rest has the same operations. Retail reads the flags doubleword between the two Lengths and keeps their qmfc2 results in v0 (here the ld comes first and v1 holds them); the field at bit 30 is read as (flags << 2) >> 32 & 3, which a 2-bit field does not give (it gives dsrl 30), so the read is written out; the stores are a 2-bit field's (bits30). Tried by hand and with tools/permute.py --auto.
extern f32 D_00260EE0[4];
extern f32 D_00260EF0[4];
extern const Vec02 D_00248D30;
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
void ConvertOffsetToSpherical(Vec02* v, s32 zero, f32* a, f32* b, f32* c);

void func_00128598(f32 a, f32 b, PlacedObject* self, f32* p1, f32* p3, f32* out0, f32* out1, f32* out2)
{
    Vec02 d;
    Vec02 g;
    Vec02 tgt;
    Vec02 pos;
    Vec02 vel;
    Vec02 w;
    Mat02 R;
    if (p1 == 0) {
        p1 = D_00260EE0;
    }
    if (p3 == 0) {
        p3 = D_00260EF0;
    }
    Attachment* pa = self->f1EC;
    Attachment* ra = self->f1F0;
    if (pa != 0) {
        pa->vt->getPos(pa, 0.0f, &pos, &vel);
    } else {
        pos = self->pos;
        vel = D_00248D30;
    }
    if (ra != 0) {
        ra->vt->getRot(ra, 0.0f, &R, &w);
    } else {
        R = self->rot;
        w = D_00248D30;
    }
    Vu0::Set(d, Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos)));
    if (out1 == 0) {
        d.z = 0.0f;
    }
    f32 len1 = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
    f32 len2 = Vu0::ToFloat(Vu0::Length(Vu0::Q(vel)));
    s32 f = ((s32)((s64)self->flags << 2 >> 32)) & 3;
    if (f == 0) {
        if (len1 < 25.0f) {
            if (len2 < 10.0f) {
                self->bits30 = 1;
            }
        }
    } else if (f == 1) {
        if (50.0f < len1 || 10.0f < len2) {
            self->bits30 = 0;
        }
    }
    f = ((s32)((s64)self->flags << 2 >> 32)) & 3;
    if (f == 0) {
        u128 push;
        if (0.0001f < len1) {
            f32 v = ClampRange::Of(p1[0] + len1 * (p1[1] + len1 * p1[2]), p3[0], p3[1]);
            push = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(v / len1));
        } else {
            push = Vu0::Zero();
        }
        Vu0::Q(g) = push;
        Vu0::Q(tgt) = Vu0::Add(Vu0::Q(g), Vu0::Q(vel));
        ConvertOffsetToSpherical(&tgt, 0, out0, out1, out2);
    } else if (f == 1) {
        if (ra != 0) {
            ConvertOffsetToSpherical((Vec02*)&R, 0, out0, out1, 0);
            *out2 = 0.0f;
        } else {
            *out0 = b;
            if (out1 != 0) {
                *out1 = 0.0f;
            }
            *out2 = 0.0f;
        }
    }
}

