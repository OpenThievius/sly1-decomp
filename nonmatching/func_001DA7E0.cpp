// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 532/568 (93.7%), checked 2026-11-07
// NEAR: same size and the same instructions up to the VU0 register numbers: the product of the two matrices (an inline MulMat returning a Mat02; its three copies, the result and two temporaries, come out right) takes vf4/vf2/vf1 and vf5/vf6/vf3 where retail has vf3/vf5/vf1 and vf4/vf6/vf2, and stores the copies in another order.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "world.h"
#include "queued_call.h"
#include "effect.h"
#include "game_progress.h"
#include "buffered_stream.h"
#include "value_range.h"
#include "script_value.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "font.h"
#include "level_entry.h"
#include "message_body.h"
#include "path_curve_object.h"
#include "state_notifier.h"

extern f32 g_gameClock[];
extern f32 D_00275620[4];
void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);

typedef u64 Quad_1DA7E0 __attribute__((mode(TI)));
void UpdateAttachmentFrames(void* self);
Quad_1DA7E0 ApproachPointWithRamp(Quad_1DA7E0 a, Quad_1DA7E0 b, void* ramp, s32 c, f32 dt);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

inline Mat02 MulMat(const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vu0::Q(r.r[0]) = Vu0::Rotate(a, Vu0::Q(b.r[0]));
    Vu0::Q(r.r[1]) = Vu0::Rotate(a, Vu0::Q(b.r[1]));
    Vu0::Q(r.r[2]) = Vu0::Rotate(a, Vu0::Q(b.r[2]));
    return r;
}

void func_001DA7E0(PathFollower* self)
{
    u32 i = 0;
    UpdateAttachmentFrames(self);
    for (; i < 4; i++) {
        Slot19* s = &self->f6B0[i];
        Mat02 world;
        Mat02 tilt;
        Mat02 turn;
        s->f54 += s->f50 * g_gameClock[2];
        if (s->f0C == self->f6A0) {
            TransformPointBetweenFrames(0, self, &s->v20, &s->v10);
            s->v10.z = s->v10.z + (((s32)i < 2) ? self->f610 : self->f614);
        } else {
            *(Quad_1DA7E0*)&s->v10 = ApproachPointWithRamp(*(Quad_1DA7E0*)&s->v10, *(Quad_1DA7E0*)&s->obj->v190, D_00275620, 0, g_gameClock[2]);
        }
        if ((s32)i < 2) {
            BuildAxisAngleMatrix(&g_unitZVector, &tilt, self->f69C);
        } else {
            tilt = g_identityMatrix;
        }
        BuildAxisAngleMatrix(&g_unitYVector, &turn, s->f54);
        world = MulMat(tilt, turn);
        if (s->obj2 != 0) {
            Vec02 moved;
            TransformPointBetweenFrames(s->obj->parent, s->obj2->parent, &s->v10, &moved);
            s->obj2->desc02()->m1D(s->obj2, &moved);
        }
        s->obj->desc02()->m1D(s->obj, &s->v10);
        s->obj->desc02()->m1E(s->obj, &world);
    }
}
