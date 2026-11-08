// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 783/844 (92.8%), checked 2026-11-08
// NEAR (2026-11-08, night-size1): the same size now, 29 words differ, all float registers of the tail. Retail's compare tree for the mode (slti 3, bgtzl, beql: the range 1..2 as its root) is a third case node: `case 3: break;`, which balance_case_nodes needs to split the list (two nodes stay lopsided with case 0 first) and whose test jump.c then drops; the pushed object's point is a local (Vec02 point, at 0(sp)), not `out`; the steer's amount reads the rate field in place (its product takes the rate's f1); the clamps are an inline ClampBetween and the reach MinF(span, 300.0f). Still differs: retail keeps len (the call's f0 less 30) in f0 and the player's +0x23A4 in f4, ours len in f4 and +0x23A4 in f3, which renumbers the tail's floats; and the second clamp's arm (the positive force) branches as bc1f/b where retail's matches the first arm's. Tried: +0x23A4 read first, len assigned in two statements, the square and the scale as two statements.
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
extern f32 D_00263900[4];
f32 ArctangentOfRatio(f32 a, f32 b);
void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);

// The object the player is pushed along (+0x23A0): a frame at +0x18, flags at +0x50 and a holder
// at +0x34 that has an array of floats, or answers a length through its descriptor.
struct PushHolderDesc;
struct PushHolder { PushHolderDesc* desc; u8 pad04[4]; s32 f08; s32 count; u8 pad10[4]; f32* values; };
struct PushHolderDesc {
    u8 pad00[8];
    void (*m2)(PushHolder* self, Vec02* out, f32 t, s32 a);
    u8 pad0C[0x20 - 0x0C];
    f32 (*length)(PushHolder* self);
};
struct PushObject { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; PushHolder* holder; u8 pad38[0x50 - 0x38]; u32 flags; };
struct PushRecord { u8 pad00[0x30]; f32 f30; s32 f34; };
f32 ApproachValueWithRamp(void* p, s32 zero, f32 a, f32 b, f32 c);

// The smaller of two floats (min.s; through an inline function the result takes b's register).
static inline f32 MinF(f32 a, f32 b) { return a <? b; }

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void func_001733B8(Player* self, PushRecord* out)
{
    out->f30 = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
    if (self->f2674 != (s32)self->f2678) {
        return;
    }
    out->f34 = 0;
    switch (self->f2684) {
    case 1 ... 2: {
        PushObject* o = (PushObject*)self->f23A0;
        if (o != 0) {
            f32 limit;
            if (self->f2684 == 1) {
                PushHolder* h = o->holder;
                limit = self->f23A4 + *(f32*)&self->f26A0 * (*(f32*)&self->f26A0 * 125.0f);
                if (h->f08 == 0) {
                    f32 top = h->values[h->count - 1];
                    if (o->flags & 2) {
                        top = top + 100.0f;
                    }
                    limit = top <? limit;
                }
            } else {
                PushHolder* h = o->holder;
                limit = self->f23A4 - *(f32*)&self->f26A0 * (*(f32*)&self->f26A0 * 125.0f);
                if (h->f08 == 0) {
                    f32 bottom = h->values[0];
                    if (o->flags & 1) {
                        bottom = bottom - 100.0f;
                    }
                    limit = bottom >? limit;
                }
            }
            Vec02 point;
            PushHolder* holder = ((PushObject*)self->f23A0)->holder;
            if (holder->desc->m2 != 0) {
                holder->desc->m2(holder, &point, limit, 0);
            }
            TransformPointBetweenFrames(((PushObject*)self->f23A0)->frame, 0, &point, &self->v2690);
            self->v2690.z = self->v2690.z + 125.0f;
        } else {
            Vec02 k;
            if (self->f2684 == 1) {
                Vu0::Q(k) = Vu0::FromFloat(*(f32*)&self->f26A0 * (*(f32*)&self->f26A0 * 125.0f));
                Vu0::Q(self->v2690) = Vu0::Add(Vu0::Q(self->v140), Vu0::MulX(Vu0::Q(self->m110.r[1]), Vu0::Q(k)));
            } else {
                Vu0::Q(k) = Vu0::FromFloat(*(f32*)&self->f26A0 * (*(f32*)&self->f26A0 * 125.0f));
                Vu0::Q(self->v2690) = Vu0::Sub(Vu0::Q(self->v140), Vu0::MulX(Vu0::Q(self->m110.r[1]), Vu0::Q(k)));
            }
            self->v2690.z = self->v2690.z + 50.0f;
        }
        break;
    }
    case 0:
        self->v2690 = self->v140;
        self->v2690.z = self->v2690.z + 50.0f;
        break;    case 3:
        break;
    }
    if (self->f23A0 == 0) {
        return;
    }
    PushHolder* h = ((PushObject*)self->f23A0)->holder;
    if (h->f08 != 0) {
        return;
    }
    f32 base = 30.0f;
    f32 len = h->desc->length(h) - base;
    f32 span = (len - base) * 0.5f;
    f32 reach = MinF(span, 300.0f);
    f32 lowEdge = reach + base;
    f32 at = self->f23A4;
    f32 force;
    if (at < lowEdge) {
        f32 t = (lowEdge - at) / reach;
        f32 w = ClampBetween(t, 0.0f, 1.0f);
        force = -w * w * 150.0f;
    } else if (len - reach < at) {
        f32 t = (at - (len - reach)) / reach;
        f32 w = ClampBetween(t, 0.0f, 1.0f);
        force = w * w * 150.0f;
    } else {
        force = 0.0f;
    }
    OnOffObject* target = self->f2678;
    f32* slot = (f32*)((u8*)target + 0x300);
    *(f32*)((u8*)self->f2678 + 0x300) = ApproachValueWithRamp(D_00263900, 0, *slot, force, g_frameDt[0]);
}
