// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 320/316, checked 2026-11-07
// NEAR: all instructions and registers match except the address of the last vector (sp+144): the compiler keeps it in a callee-saved register from its store to the call after the first one, where retail forms it again, and the second vadd has its inputs in the other two registers. A u128 local for the sums moves the stores after the calls.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
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


void TransformPointBetweenFrames(PlacedObject* z, BaseObject* frame, void* c, u8* d);
void TransformRotationBetweenFrames(PlacedObject* z, BaseObject* frame, void* c, u8* d);
void TransformDirectionBetweenFrames(BaseObject* from, BaseObject* to, void* in, void* out);
void ComputeObjectMotionInFrame(BaseObject* from, BaseObject* to, void* pt, void* a, void* b, void* c, void* d);
typedef void (*Fn_Table)();
void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);
void TransformRotationBetweenFrames(void* a, void* b, void* c, void* d);
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);

void ReframePlacedObject(PlacedObject* self, BaseObject* frame)
{
    Vec02 pos;
    Mat02 rot;
    Vec02 vel;
    Vec02 spin;
    Vec02 velDir;
    Vec02 spinDir;
    Vec02 sums[2];
    TransformPointBetweenFrames(frame, 0, &self->pos, &pos);
    self->desc02()->m1D(self, &pos);
    TransformRotationBetweenFrames(frame, 0, &self->rot, &rot);
    self->desc02()->m1E(self, &rot);
    ComputeObjectMotionInFrame(frame->parent, 0, &pos, &vel, &spin, 0, 0);
    TransformDirectionBetweenFrames(frame, 0, &self->v150, &velDir);
    TransformDirectionBetweenFrames(frame, 0, &self->v160, &spinDir);
    Vu0::Q(sums[0]) = Vu0::Add(Vu0::Q(vel), Vu0::Q(velDir));
    Vu0::Q(sums[1]) = Vu0::Add(Vu0::Q(spin), Vu0::Q(spinDir));
    self->desc02()->m20(self, &sums[0]);
    self->desc02()->m21(self, &sums[1]);
    self->v190 = self->pos;
    self->m1A0.r[0] = self->rot.r[0];
    self->m1A0.r[1] = self->rot.r[1];
    self->m1A0.r[2] = self->rot.r[2];
}
