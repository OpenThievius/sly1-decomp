// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 320/308, checked 2026-11-07
// NEAR: right frame (256) and the same VU0 arithmetic, 12 bytes long: retail stores each product's rows twice (the product and a temporary slot at 0xA0 shared by both products) and keeps rot's rows in different registers; ours (an inline MulMat returning a Mat02) stores them once and loads the third row of the first product later.
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
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

inline Mat02 MulMat(const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vu0::Q(r.r[0]) = Vu0::Rotate(a, Vu0::Q(b.r[0]));
    Vu0::Q(r.r[1]) = Vu0::Rotate(a, Vu0::Q(b.r[1]));
    Vu0::Q(r.r[2]) = Vu0::Rotate(a, Vu0::Q(b.r[2]));
    return r;
}

void func_00172078(Player* self, Mat02* out, f32 t)
{
    Vec02 axis;
    Mat02 m;
    axis = self->f2228 == 8 ? g_unitZVector : g_unitXVector;
    BuildAxisAngleMatrix(&axis, &m, self->f2434 - g_frameDt[0] * self->f2430 * t);
    Mat02 a = MulMat(self->rot, m);
    Mat02 c = MulMat(a, *(Mat02*)((u8*)self->f61C + 0xD0));
    *out = c;
}
