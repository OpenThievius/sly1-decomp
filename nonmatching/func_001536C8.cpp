// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 176/184, checked 2026-11-07
// NEAR: retail loads the solver's count afresh in the loop's body for the row's index (lw v1, 4(s0)) and in the delay slot of a beql on the row's test; here the count of the loop's test stays in v1 and is reused. The store is ToBits's qmfc2 + sw, as retail's. A local index, the row read twice, &items[i]: no change.
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
void AddActiveSetItem(ActiveSetSolver* self, ActiveSetItem* item)
{
    for (s32 i = 0; i < self->count; i++) {
        ActiveSetItem* e = (ActiveSetItem*)(self->items + i * 0x60);
        f32* row = e->row;
        if (row != 0) {
            u128 d = Vu0::Dot(Vu0::Q(item->axis), Vu0::Q(e->axes[*(s32*)((u8*)item->owner + 0xCC)]));
            ((u32*)row)[self->count] = Vu0::ToBits(d);
        }
    }
    AppendToList(&self->pending, item);
    self->count++;
}
