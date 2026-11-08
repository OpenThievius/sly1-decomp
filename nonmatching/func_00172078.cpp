// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 304/308, checked 2026-11-08
// NEAR (2026-11-08, night-size1): now 304 bytes for retail's 308 (was 320), the right frame. Each product is an inline writing its rows straight into a Mat02 of the caller (c, then a, declared in the order retail's frame shows) and to three vector locals both products share (0xA0), and the axis is copied in each arm of the test (cross-jumping leaves retail's shared lq/sq). Still differs: the missing instruction is retail's `addiu v1, v0, 208` (below); the first product's rows 1 and 2 take vf6/vf5 where retail has vf5/vf6 and its y and z stores come before the rows' (retail stores them last); the second product reads f61C's rows at 224/240(v0), where retail forms v1 = v0 + 208 and reads 16(v1), 32(v1) (reading b through a pointer gives that but keeps m's address in s0 for the first product). Tried: the vector stores as struct copies after or before the row's, a pointer-selected axis.
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

// The product a b of two rotations into out: b's rows each rotated by a's rows (loaded once
// as values), each result stored to a vector local and to out's row.
static inline void MulRotationInto(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::Q(out->r[0]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = Vu0::Q(out->r[1]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = Vu0::Q(out->r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
}

void func_00172078(Player* self, Mat02* out, f32 t)
{
    Vec02 axis;
    Mat02 m;
    if (self->f2228 == 8) {
        axis = g_unitZVector;
    } else {
        axis = g_unitXVector;
    }
    BuildAxisAngleMatrix(&axis, &m, self->f2434 - g_frameDt[0] * self->f2430 * t);
    Mat02 a;
    Mat02 c;
    MulRotationInto(&c, self->rot, m);
    MulRotationInto(&a, c, ((PlacedObject*)self->f61C)->rot);
    *out = a;
}
