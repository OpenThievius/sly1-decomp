// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 240/308 (77.9%), checked 2026-11-08
// NEAR (2026-11-08, night-sizex1): 308 bytes, retail's size and frame now: the second product reads f61C's rows by index through a pointer (MulRotationIntoIndexed, q[i]), which gives retail's `addiu v1, v0, 208` and 16(v1), 32(v1). Still differs (32 lines): the first product's rows 1 and 2 take vf6/vf5 where retail has vf5/vf6, which the second product's registers follow, and the order of the dead stores of x, y, z against the rows (retail stores the first product's y and z last). Tried the chained stores in the other order, separate statements, *(u128*)& stores, both products indexed (320 bytes).
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

// The same with b's rows read by index through a pointer to them.
static inline void MulRotationIntoIndexed(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::Q(out->r[0]) = Vu0::RotateRows(a0, a1, a2, q[0]);
    Vu0::Q(y) = Vu0::Q(out->r[1]) = Vu0::RotateRows(a0, a1, a2, q[1]);
    Vu0::Q(z) = Vu0::Q(out->r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
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
    MulRotationIntoIndexed(&a, c, ((PlacedObject*)self->f61C)->rot);
    *out = a;
}
