// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 176/184 (95.7%), checked 2026-11-10
// NEAR: the dot over Vu0::Vec values (Vec::Of for both operands) gives retail's size: with u128 operands cse_around_loop keeps the loop test's count for the row's index, as Vec temporaries in a loop body stop (docs/TOOLCHAIN.md, func_001C4D60); now retail's code but for local-alloc's order in the body: retail places the count chain (lw v1, 4(s0); sll; addu) before the owner pointer (lw a0, 0(t0)), so the owner gets a0 and the count v1; here the owner (r138, shorter) is placed first and takes v1. A named slot, a named axis, the dot inline in the store, a named bits word and the operands swapped: no change or worse.
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
            Vu0::Vec d = Vu0::Dot(Vu0::Vec::Of(item->axis), Vu0::Vec::Of(e->axes[*(s32*)((u8*)item->owner + 0xCC)]));
            ((u32*)row)[self->count] = Vu0::ToBits(d.q);
        }
    }
    AppendToList(&self->pending, item);
    self->count++;
}
