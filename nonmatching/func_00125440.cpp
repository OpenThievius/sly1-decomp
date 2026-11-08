// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 776/780, checked 2026-11-07
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "game_clock.h"
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
// NEAR (2026-11-08, wave 4): MovePlacedObject: every instruction is retail's in kind and order of use except the rotation product and two register choices. Retail loads the clock through a base register formed in the block (v0, the converted float in v1; here v1 and v0), and for the product loads row 0 of the matrix first, the three rows of the rotation (vf3, vf6, vf5) next and rows 1 and 2 only when their products come (through v0 = s0 + 0xD0), storing the three result rows to s0 after all three are computed; here all three rows are loaded first and the result rows are stored to s0 between the products (a Mat02* m to the matrix, MulRotationRows(m, rot, *m)). MulRotationRows with &self->rot gives the same loads and the stores after. The clock as a function-level pointer costs a callee-saved register; a pointer declared in each block gives the base register.
extern f32 g_frameDt;
s32 IsVelocityNegligible(void* a);
s32 IsSpinNegligible(void* a);
struct ListWalkNext {
    static BaseObject* Of(ListFrame* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct ListWalkBegin {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = (ListFrame*)it;
    }
};
void ApplyPoseSourcePosition(Attachment* a);
void ApplyPoseSourceRotation(Attachment* a);
s32 IsAccelerationNegligible(void* a);
s32 IsSpinAccelerationNegligible(void* a);
void BuildRotationFromVector(Vec02* in, Mat02* out);
void OrthonormalizeMatrix(Mat02* m);

void MovePlacedObject(PlacedObject* self, s32 flag, f32 dt)
{
    Attachment* pa = self->f1EC;
    Attachment* ra = self->f1F0;
    s32 moved = flag;
    if (pa == 0 || pa->mode0 == 5 || ra == 0 || ra->mode1 == 5) {
        Vu0::Q(self->v180) = Vu0::Q(self->v170) = Vu0::Zero();
        ((void (*)(PlacedObject*, f32))self->desc02()->m1C)(self, g_frameDt);
    }
    if (pa != 0 && pa->mode0 != 5) {
        ApplyPoseSourcePosition(pa);
        moved = 1;
    } else if (IsVelocityNegligible(&self->v150) == 0 || IsAccelerationNegligible(&self->v170) == 0) {
        moved = 1;
        GameClock* clk = &g_gameClock;
        Vu0::Q(self->pos) = Vu0::MulAddX2(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Scalar(clk->dt), Vu0::Q(self->v170), Vu0::Scalar(clk->dt * (clk->dt * 0.5f)));
        Vu0::Q(self->v150) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(self->v170), Vu0::ScalarAt(clk->dt));
    }
    if (ra != 0 && ra->mode1 != 5) {
        ApplyPoseSourceRotation(ra);
        moved = 1;
    } else if (IsSpinNegligible(&self->v160) == 0 || IsSpinAccelerationNegligible(&self->v180) == 0) {
        GameClock* clk = &g_gameClock;
        Vec02 prev;
        Vec02 w;
        Mat02 rot;
        Vu0::Q(prev) = Vu0::Q(self->v160);
        Vu0::Q(self->v160) = Vu0::MulAddX(Vu0::Q(self->v160), Vu0::Q(self->v180), Vu0::ScalarAt(clk->dt));
        moved = 1;
        Vu0::Q(w) = Vu0::MulXSum(Vu0::Q(prev), Vu0::Scalar(clk->dt * 0.5f), Vu0::Q(self->v160), Vu0::Scalar(clk->dt * 0.5f));
        BuildRotationFromVector(&w, &rot);
        Mat02* m = &self->rot;
        MulRotationRows(m, rot, *m);
        OrthonormalizeMatrix(m);
    }
    ListFrame it;
    ListWalkBegin::Of(&it, &self->children);
    BaseObject* obj;
    while ((obj = ListWalkNext::Of(&it)) != 0) {
        if ((obj->desc->flags & 1) != 0) {
            ((void (*)(BaseObject*, s32, f32))obj->desc->m1B)(obj, moved, dt);
        }
    }
    g_activeListFrames = (ListFrame*)it.prev;
    if (moved != 0) {
        if (flag == 0) {
            if (self->desc->m12 != 0) {
                self->desc->m12(self);
            }
        }
    }
}

