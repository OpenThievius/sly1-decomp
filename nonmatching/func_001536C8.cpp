// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 180/184, checked 2026-11-07
// NEAR: needs ActiveSetItem to have owner at 0x00, axis (Vec02) at 0x10 and axes (Vec02*) at 0x40, which active_set_solver.h does not have yet (they are local types here). Retail stores the dot product with sw straight from qmfc2 (ToFloat gives mtc1 and swc1), takes the loop count from a reload after the store, and tests the row with a branch-likely.
#include "common.h"
#include "gauge_manager.h"
#include "asm_func.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "world.h"
#include "screen_element.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "list_iter.h"
#include "c61.h"
#include "step_sequence.h"
#include "animation.h"
#include "attachment.h"
#include "camera.h"
#include "flagged_object.h"
#include "packet_writer.h"
#include "globals.h"
#include "game_progress.h"
#include "threshold_range.h"
#include "pad_record.h"
#include "active_set_solver.h"
#include "buffered_stream.h"
#include "texture_header.h"
#include "range_record.h"
#include "effect_spawner.h"
#include "effect_owner.h"
#include "effect.h"
#include "deferred_request.h"
#include "cursor_animator.h"
#include "texture_table.h"


void AppendToList(void* list, void* item);

#include "vu0.h"
void AppendToList(void* list, void* item);
struct NmItem {
    void* owner;            // 0x00
    u8 pad04[0x10 - 0x04];
    Vec02 axis;             // 0x10
    u8 pad20[0x40 - 0x20];
    Vec02* axes;            // 0x40
    f32* row;               // 0x44
    u8 pad48[4];
    NmItem* next;           // 0x4C
    u8 pad50[0x10];
};
void AddActiveSetItem(ActiveSetSolver* self, NmItem* item)
{
    for (s32 i = 0; i < self->count; i++) {
        NmItem* e = (NmItem*)(self->items + i * 0x60);
        f32* row = e->row;
        if (row != 0) {
            union {
                f32 f;
                s32 i;
            } d;
            d.f = Vu0::ToFloat(Vu0::Dot(Vu0::Q(item->axis), Vu0::Q(e->axes[*(s32*)((u8*)item->owner + 0xCC)])));
            ((s32*)row)[self->count] = d.i;
        }
    }
    AppendToList(&self->pending, item);
    self->count++;
}
