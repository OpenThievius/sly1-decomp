// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 296/300, checked 2026-11-07
// NEAR: the code and the jump table are retail's; differs in the registers (retail keeps self in s0 and the state in s1; ours the reverse) and the vector (-speed, 0, 0, 0) at 0x640: retail builds it in GPRs with pextlw/pcpyld and stores it twice (0x640 and a stack local), ours builds it piecewise on the stack. No C form tried (initialiser, four field stores) gives the pextlw.
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "font.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "scatter_controller.h"
#include "render_frame.h"
#include "background_job.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "path_curve_object.h"
#include "asm_func.h"
#include "vu0.h"

extern f32 g_frameDt[];
void SetPlayerState(void* self, s32 mode, s32 count);
void func_001C61E0(void* self, s32 arg);

void func_00128598(void* self, s32 a, s32 b, f32* heading, s32 c, f32* speed, f32 dt, f32 h);

void func_00174E20(Player* self)
{
    switch (self->f2220) {
    case 3:
        SetPlayerState(self, 2, 2);
        break;
    case 0xD:
        SetPlayerState(self, 0xD, 0x38);
        break;
    }
    s32 state = self->f2220;
    func_001C61E0(self, -1);
    switch (state) {
    case 2:
    case 3:
    case 13:
    case 14:
    case 15:
    case 16:
        break;
    case 4:
    case 12:
        Vu0::Q(self->v640) = Vu0::Zero();
        break;
    default: {
        f32 heading;
        f32 speed;
        s32 moving = 0;
        func_00128598(self, 0, 0, &heading, 0, &speed, g_frameDt[0], self->f638);
        if (speed > 0.0f) {
            moving = 1;
        }
        Vec02 v;
        v.x = -speed;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 0.0f;
        self->f638 = heading;
        self->v640 = v;
        SetPlayerState(self, moving, -1);
    }
    }
}
