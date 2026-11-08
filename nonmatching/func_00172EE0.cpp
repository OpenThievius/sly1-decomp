// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1207/1240 (97.3%), checked 2026-11-08
// BYTES 0/0, checked 2026-11-08
// NEAR (2026-11-08, worker night-large1): CapturePlayerPose, the player's camera pose (the path's
// point and direction in state 7, the eased height otherwise, the eased offset, then the pose's
// flags, stamp and weight), all retail's but one block's order: in state 7 retail loads the
// speed's word before the 125.0, does the vmulx before the sub.s and stores the pose's direction,
// the direction and the weight before the camera height (in the jump's delay slot); here sched1
// takes the 125.0's chain first and the weight's store goes in the delay slot (9 lines). The
// orders of the three statements (tools/permute.py), the stores as members or by offset and a
// Vec store of the direction leave it. Findings on the way: the normalised direction as a u128
// variable assigned in place (d = NormalizeOr(d, ...)) gives retail's GPR fallback and keeps the
// input's register; the pose as a struct and f650, f2414, v2530, f2680 as Player members order
// the loads around their stores as retail does.
// Still differs (2026-11-08, night-close6): the weight as a u128 before the MulX, the height or 125.0 in a local, Set for both stores, NormalizeOr through ToFloatNow: the same nine lines.
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

extern f32 g_frameDt[];
extern f32 g_gameTime[];
struct PoseHolder47;
struct PoseHolderDesc { u8 pad00[8]; void (*m2)(PoseHolder47* self, Vec02* out, f32 t, s32 a); };
struct PoseHolder47 { PoseHolderDesc* desc; };
struct PoseTarget { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; PoseHolder47* holder; };
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
extern f32 D_002638B8;
extern f32 D_002638BC;
extern f32 D_002638C0;
extern f32 D_002638C4;
extern f32 D_002638C8[2];
extern f32 D_002638D0[4];
extern f32 D_002638E0[4];
extern f32 D_002638F0[4];

void CaptureSwitchedColliderPose(Player* self, u8* out, f32 dt);
void TransformDirectionBetweenFrames(void* a, s32 b, void* c, void* d);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, f32* p, s32 zero);
u128 ApproachPointWithRamp(u128 a, u128 b, f32 dt, f32* ramp, s32 zero);
void func_001733B8(Player* self, u8* out);
void GetObjectWorldPosition(s32 obj, Vec02* out);
extern f32 g_gameClock[];
extern f32 g_unitRange[];
typedef void (*PoseAtFn)(PoseHolder47* self, Vec02* pos, Vec02* dir, f32 t);

// The pose a collider's slot captures each frame (CaptureSwitchedColliderPose fills pos).
struct ColliderPose {
    s32 flags;              // 0x00: bit 0 set in the player's grounded states
    u8 pad04[0x10 - 0x04];
    Vec02 pos;              // 0x10: where the camera looks
    Vec02 dir;              // 0x20: the path's direction times the speed along it
    u8 pad30[0x34 - 0x30];
    f32 f34;                // 0x34: a weight, scaled down by the spin or cleared
    f32 f38;                // 0x38: the time it was last stamped
    s32 f3C;                // 0x3C
};
#define PL(T, o) (*(T*)((u8*)self + (o)))

void func_00172EE0(Player* self, ColliderPose* pose, f32 dt)
{
    u8* out = (u8*)pose;
    Vec02 last = self->v560;
    CaptureSwitchedColliderPose(self, out, dt);
    if (self->f554 == 0) {
        if (self->f2220 == 7) {
            Vec02 pos;
            Vec02 dir;
            PoseHolder47* h = ((PoseTarget*)self->f2208)->holder;
            PoseAtFn fn = (PoseAtFn)h->desc->m2;
            if (fn != 0) {
                fn(h, &pos, &dir, self->f2410);
            }
            TransformPointBetweenFrames(((PoseTarget*)self->f2208)->frame, 0, &pos, &pos);
            Vu0::Q(pose->pos) = Vu0::Q(pos);
            TransformDirectionBetweenFrames(((PoseTarget*)self->f2208)->frame, 0, &dir, &dir);
            u128 d = Vu0::Q(dir);
            d = Vu0::NormalizeOr(d, Vu0::Q(D_00248D30));
            Vu0::Q(pose->dir) = Vu0::MulX(d, Vu0::ScalarAt(self->f2414));
            Vu0::Q(dir) = d;
            self->f650 = pose->pos.z - 125.0f;
        } else {
            if (self->f2220 == 3) {
                Vec02 pos;
                GetObjectWorldPosition(self->f2204, &pos);
                self->f650 = pos.z + D_002638C8[0];
            } else if (self->f690 != 0) {
                self->f650 = self->v6A0.z;
            } else if (g_camera->f224 != 0) {
                self->f650 = self->v140.z - 75.0f;
            }
            f32 h = self->f650;
            f32 lo = self->pos.z + D_002638C4;
            f32 hi = self->pos.z + D_002638C0;
            f32 r;
            if (h < lo) {
                r = lo;
            } else if (hi < h) {
                r = hi;
            } else {
                r = h;
            }
            self->f650 = r;
            f32 z = r + 125.0f;
            if (g_camera->f224 != 0) {
                pose->pos.z = z;
            } else {
                f32 v = ApproachValueWithRamp(last.z, z, g_gameClock[2], D_002638F0, 0);
                pose->pos.z = v;
                f32 zlo = self->pos.z + D_002638BC;
                f32 zhi = self->pos.z + D_002638B8;
                f32 w;
                if (v < zlo) {
                    w = zlo;
                } else if (zhi < v) {
                    w = zhi;
                } else {
                    w = v;
                }
                pose->pos.z = w;
            }
        }
        if (self->f2220 == 6 && self->f239C == 0) {
            func_001733B8(self, out);
        }
        u128 d = ApproachPointWithRamp(Vu0::Q(self->v2530), Vu0::Q(D_00248D30), dt, D_002638E0, 0);
        Vu0::Q(self->v2530) = d;
        Vu0::Q(pose->pos) = Vu0::Add(Vu0::Q(pose->pos), d);
    }
    switch (self->f2220) {
    case 2:
        if (self->f2498 != 0) {
            pose->flags |= 1;
        }
        break;
    case 3:
    case 4:
    case 5:
        pose->flags |= 1;
        break;
    case 6:
        switch (self->f239C) {
        case 0:
        case 1:
            pose->f3C = 1;
            break;
        case 2:
        case 4:
        case 5:
            break;
        default:
            pose->flags |= 1;
            break;
        }
        break;
    }
    s32 stamp = 1;
    switch (self->f2220) {
    case 0:
        stamp = 0;
        break;
    case 6:
        if (self->f2228 == 16) {
            stamp = 0;
        }
        break;
    case 7:
        if (self->f2228 == 24) {
            stamp = 0;
        }
        break;
    }
    if (stamp != 0) {
        self->f2680 = g_gameTime[0];
    }
    pose->f38 = self->f2680;
    switch (self->f2220) {
    case 0: {
        f32 a = __builtin_fabsf(self->v160.z);
        f32 k = D_002638D0[0] + a * (D_002638D0[1] + a * D_002638D0[2]);
        f32* range = g_unitRange;
        f32 lo = range[0];
        f32 hi = range[1];
        f32 r;
        if (k < lo) {
            r = lo;
        } else if (hi < k) {
            r = hi;
        } else {
            r = k;
        }
        k = r;
        pose->f34 = pose->f34 * k;
        break;
    }
    case 4:
        switch (self->f2228) {
        case 41:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            pose->f34 = 0.0f;
        }
        break;
    case 7:
    case 13:
        pose->f34 = 0.0f;
        break;
    }
    self->v560 = pose->pos;
}

#undef POSE
#undef PL
