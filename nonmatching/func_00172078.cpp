// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 301/308 (97.7%), checked 2026-11-10
// NEAR (2026-11-10, w10-172078): 5 lines, all in the second product's dead stores of its row
// values: retail stores them to three slots (0xA0, 0xB0, 0xC0, the first product's), ours to one
// (0xA0) for every row. Registers, frame and every other store are retail's. The mechanism
// (docs/TOOLCHAIN.md, "A rotation product's row slots are cast copies"): the row values' slots
// are MEM_SCALAR_P (a cast's copy, as Vu0::Scalar's) and the second product's rows of f61C's
// matrix are read as Vec members (MEM_IN_STRUCT_P), so the row loads pass the slot stores
// (fixed_scalar_and_varying_struct_p) but wait for the stores to the matrix local. That moves
// f61C's row 0 load one insn earlier in sched1, which lowers its quantity's local-alloc priority
// below the first product's rows (life 22 against 20) and gives retail's vf4/vf5/vf6. Three
// distinct slots come from three casts that are arguments of one call (SetRows, first product);
// per-row statements (second product, which needs each out row stored before the next row's
// load) free the cast's temporary at the statement's end, so the rows share one. Tried for the
// second product: SetRows (the loads then pass the out stores: 37-42 lines), per-row stores then
// one call with the three casts (38), the casts bound to references (`const u128& r =
// Q((s128)x)`, `const s128& r = (s128)x`, a pointer: 5, shared slot), a value-returning row
// helper ending `return Q((s128)r)` per statement or in one comma expression (20: an inline's
// frame is freed when it returns), references bound to the product's rvalue (44, no slot),
// volatile slots (56).
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

// Out's rows from three row values (the casts' copies, bound to the parameters).
static inline void SetRows(Mat02* out, const u128& x, const u128& y, const u128& z)
{
    Vu0::Q(out->r[0]) = x;
    Vu0::Q(out->r[1]) = y;
    Vu0::Q(out->r[2]) = z;
}

// The product a b: the three rows computed, then stored through casts (one slot each).
static inline void MulRotationCast(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    u128 x = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    u128 y = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    u128 z = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    SetRows(out, Vu0::Q((s128)x), Vu0::Q((s128)y), Vu0::Q((s128)z));
}

// The same with b's rows read as Vec members and each row stored in its own statement.
static inline void MulRotationCastRows(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const Vu0::Vec* q = (const Vu0::Vec*)&b;
    u128 x = Vu0::RotateRows(a0, a1, a2, q[0].q);
    Vu0::Q(out->r[0]) = Vu0::Q((s128)x);
    u128 y = Vu0::RotateRows(a0, a1, a2, q[1].q);
    Vu0::Q(out->r[1]) = Vu0::Q((s128)y);
    u128 z = Vu0::RotateRows(a0, a1, a2, q[2].q);
    Vu0::Q(out->r[2]) = Vu0::Q((s128)z);
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
    MulRotationCast(&c, self->rot, m);
    MulRotationCastRows(&a, c, ((PlacedObject*)self->f61C)->rot);
    *out = a;
}
