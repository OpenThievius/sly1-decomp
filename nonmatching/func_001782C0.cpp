// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 718/728 (98.6%), checked 2026-11-08
// NEAR: wave 4 e3. 728 bytes, same size; 11 words differ: the two weights of the tail (dt and -0.5 dt) take vf4 and vf5
//       in the other order (retail dt in vf5), the scheduling of their stores (retail leaves dt's second store for the delay
//       slot of the first null test) and the temporary of the hi of D_002639E0 (v1, retail v0). The branches, the frame
//       (the path frame is a Mat02 at 0x40, which the tail's weights reuse) and the registers of the pointers are retail's.
//       ~15 compiles.
// Night-close2 (2026-11-08): one expression for v, a named Scalar(dt), -0.5f * dt and FromFloat for the last weight leave the same 11 words (FromFloat 31).
// Still differs (2026-11-08, night-close5): the tail's stores in retail's order (p, v1, then a's sum written last, permute.py), which puts dt's second store in the null test's delay slot; left: dt takes vf4 and -0.5 dt vf5 (retail the other way), and D_002639E0's hi in v1 (retail v0). A Vec tail, a named half weight and one expression for v change nothing or worse.
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

struct TargetArcSource {
    BaseObject* target;
    f32 t;
    u8 pad08[8];
    Vec02 v10;
};
typedef void (*ShapeAtFn)(void* self, f32 t, Vec02* out, s32 x);
struct ShapeOwner {
    ShapeAtFn* vtbl;
};
struct TargetShaped {
    u8 pad00[0x34];
    ShapeOwner* shape;
};
s32 IsObjectOfKind(void* obj, s32 kind);
void PlaceOnPathAt(void* self, void* obj, f32 t, Mat02* out);
void PlaceOnTargetCurve(void* obj, Vec02* out, f32 t, s32 x);
void PlaceOnTargetPoint(void* obj, Vec02* out, f32 t, s32 x);
void TransformPointBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);
void TransformPointAtTime(void* obj, s32 a, f32 t, Vec02* in, s32 b, Vec02* out, s32 c);
extern f32 D_002639C0[4];
extern f32 D_002639D0[4];
extern f32 D_002639E0[2];
extern const Vec02 D_00248D30;
void func_001782C0(Player* self, TargetArcSource* src, f32 dt, Vec02* vel, Vec02* pos, Vec02* acc)
{
    Vec02 p;
    Vec02 v1;
    Vec02 a;
    Vec02 off = *(Vec02*)D_002639C0;
    BaseObject* parent;
    if (src->target != 0) {
        parent = src->target->parent;
        if (IsObjectOfKind(src->target, 0x76)) {
            p = *(Vec02*)((u8*)src->target + 0x40);
            off = *(Vec02*)D_002639D0;
        } else if (IsObjectOfKind(src->target, 0x70)) {
            BaseObject* obj = src->target;
            ShapeOwner* shape = ((TargetShaped*)obj)->shape;
            if (shape->vtbl[2] != 0) {
                shape->vtbl[2](shape, src->t, &p, 0);
            }
            Mat02 frame;
            PlaceOnPathAt(self, obj, src->t, &frame);
            Vu0::Q(off) = Vu0::MulX(Vu0::Q(frame.r[0]), Vu0::ScalarAt(D_002639E0[0]));
        } else if (IsObjectOfKind(src->target, 0x6F)) {
            PlaceOnTargetCurve(src->target, &p, src->t, 0);
            TransformPointBetweenFrames(0, parent, &p, &p);
        } else if (IsObjectOfKind(src->target, 0x7F)) {
            PlaceOnTargetPoint(src->target, &p, src->t, 0);
            TransformPointBetweenFrames(0, parent, &p, &p);
        } else if (IsObjectOfKind(src->target, 0x6E)) {
            ShapeOwner* shape = ((TargetShaped*)src->target)->shape;
            if (shape->vtbl[2] != 0) {
                shape->vtbl[2](shape, src->t, &p, 0);
            }
        } else if (IsObjectOfKind(src->target, 0x7E)) {
            p = *(Vec02*)((u8*)src->target + 0x40);
        } else {
            p = D_00248D30;
        }
    } else {
        parent = 0;
        p = src->v10;
    }
    a = D_00248D30;
    TransformPointAtTime(parent, 0, dt, &p, 0, &a, 0);
    u128 end = Vu0::Add(Vu0::Q(p), Vu0::Q(off));
    u128 g = Vu0::Q(self->gravity);
    u128 v = Vu0::DivX(Vu0::Sub(end, Vu0::Q(self->v140)), Vu0::Scalar(dt));
    v = Vu0::MulAddX(v, g, Vu0::Scalar(dt * -0.5f));
    Vu0::Q(p) = end;
    Vu0::Q(v1) = v;
    Vu0::Q(a) = Vu0::MulAddX(v, g, Vu0::Scalar(dt));
    if (vel != 0) {
        Vu0::Q(*vel) = v;
    }
    if (pos != 0) {
        *pos = p;
    }
    if (acc != 0) {
        *acc = a;
    }
}
