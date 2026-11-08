// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 888/892, checked 2026-11-08
// NEAR (night-low1, 2026-11-08): two of the three open points fixed, one instruction short now
//       (888 of 892 bytes): the spin part's rows read as m90.r[i] (no pointer to m90, so &m90 is
//       formed afresh for the call, addiu a1, sp, 144, and the rows load from the frame, as
//       retail's), and the trail flag a switch (case 3, 4, 7: flag = 1; default: 0), which
//       gives retail's compare tree with li v0, 7 and bne. Still differs: retail forms t1 =
//       obj + 0xD0 (addiu t1, v1, 208) and loads the product's base rows 1 and 2 through it
//       (row 0 at 208(v1)); ours folds every row into v1 offsets (the base passed inline or
//       through a later local: the same); and the 0.0 for the two compares is f12 in retail
//       (f2 here).
// Before: wave 4 e3. 892 bytes, same size and frame (0x190); regdiff 'code' 93.7% (209 of 223 words). The player's ramp-up of the cling and spin weights
//       (blend by the time since f2224, then the ramp of both toward their targets), the transform with the two weights written into it, the trail point (position through the
//       spin part's frame, the product of the two rotations, the flag set on the parent) and the plain trail point by state, then the two early exits and the placement.
//       The scalar part is retail's to the byte. Open: (1) retail keeps the constant 0.0 for the two compares in f12 (shared with the else arm's 0.0 argument; a shared local
//       made it worse: 132 lines); (2) retail does not keep &m90 in a callee-saved register (ours does: s0) and loads the base rows of the product through t1 = obj + 0xD0 for
//       rows 1 and 2 only; ours folds every row into v1 offsets. ~14 compiles.
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
#include "vu0.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "path_curve_object.h"
#include "asm_func.h"
#include "vu0.h"

#include "mul_rotation.h"
extern void* D_0026FA68;
extern f32 g_gameClock[];
extern f32 D_00263894;
extern f32 D_00263898;
extern f32 D_00263888[3];
s32 HasNoActiveObject89(void);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, Quad16* p, s32 zero);
void BuildPlacedObjectTransform(void* a, void* b, void* out);
void OrientPlayerSpinPart(void* self, void* out);
void AddTrailPoint(void* record, Vec02* pos, Mat02* m, s32 flag, f32 a, f32 dt);
void func_00125C90(void* self, void* a, void* b);
void func_001721B0(Player* self, void* a, void* b)
{
    u8 out[0x50] __attribute__((aligned(16)));
    Vec02 pos;
    Mat02 turned;
    Mat02 m90;
    if (self->flags & (0x8000ULL << 17)) {
        return;
    }
    f32 target;
    if (self->f2220 == 6 && self->f239C == 3 && HasNoActiveObject89() != 0) {
        f32 since = g_gameClock[1] - self->f2224;
        f32 k;
        if (0.5f <= since) {
            k = 1.0f;
        } else {
            k = g_gameClock[2] / (0.5f - since);
        }
        f32 ramp = *(f32*)((u8*)self + 0x2724);
        target = D_00263898;
        *(f32*)((u8*)self + 0x2724) = k * D_00263894 + (1.0f - k) * ramp;
    } else {
        f32 one = 1.0f;
        *(f32*)((u8*)self + 0x2724) = ApproachValueWithRamp(*(f32*)((u8*)self + 0x2724), one, g_gameClock[2], (Quad16*)D_00263888, 0);
        target = one;
    }
    f32 spin = ApproachValueWithRamp(*(f32*)((u8*)self + 0x2728), target, g_gameClock[2], (Quad16*)D_00263888, 0);
    *(f32*)((u8*)self + 0x2728) = spin;
    if (*(f32*)((u8*)self + 0x2724) < 1.0f || spin < 1.0f) {
        BuildPlacedObjectTransform(self, b, out);
        b = out;
        *(f32*)(out + 0x44) = *(f32*)((u8*)self + 0x2728);
        *(f32*)(out + 0x40) = *(f32*)(out + 0x40) * *(f32*)((u8*)self + 0x2724);
    }
    *(f32*)((u8*)self + 0x2A8) = 500.0f;
    if (self->f2434 != 0.0f || self->f2430 != 0.0f) {
        OrientPlayerSpinPart(self, &m90);
        u8* obj = *(u8**)((u8*)self + 0x23D0);
        Mat02* b3 = (Mat02*)(obj + 0xD0);
        u128 r0 = Vu0::Q(m90.r[0]);
        u128 r1 = Vu0::Q(m90.r[1]);
        u128 r2 = Vu0::Q(m90.r[2]);
        Vu0::Q(pos) = Vu0::RotateRows(r0, r1, r2, Vu0::Q(*(Vec02*)(obj + 0x100)));
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(((Collider*)self->f61C)->v140), Vu0::Q(pos));
        MulRotationRows(&turned, m90, *b3);
        AddTrailPoint((u8*)self + 0x1520, &pos, &turned, 0, self->f2430, g_gameClock[2]);
        ((Collider*)self->f61C)->flags |= (0x8000ULL << 17);
    } else {
        s32 flag;
        switch (self->f2220) {
        case 3:
        case 4:
        case 7:
            flag = 1;
            break;
        default:
            flag = 0;
            break;
        }
        AddTrailPoint((u8*)self + 0x1520, 0, 0, flag, 0.0f, g_gameClock[2]);
    }
    if (self->f2220 == 12 && self->f2228 == 0x22) {
        return;
    }
    if (D_0026FA68 != 0 && (u32)(*(s32*)((u8*)D_0026FA68 + 0x2D0) - 2) < 2) {
        return;
    }
    func_00125C90(self, a, b);
    ((Collider*)self->f61C)->flags &= ~(0x8000ULL << 17);
}
