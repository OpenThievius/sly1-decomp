// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 484/500 (96.8%), checked 2026-11-07
// NEAR: The follower's position (GetFrameFollowerPosition). Five instructions differ: in the first call of ComputeObjectFrameAtTime retail moves the time f20 into f12 before `move a2,sp` and fills the delay slot with `move t1,zero`; ours puts the f12 move in the delay slot. The second call, the clamp (hi loaded in the slot of the first branch), the switch on the mode (bltz and slti) and the polynomial through a pointer are retail's.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "world.h"
#include "shapes.h"
#include "globals.h"
#include "asm_func.h"
#include "vu0.h"
#include "placed_object.h"

void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);

// A point that follows an object's frame, or a frame of its own: the spring that eases the follow
// is a quadratic of the distance (func_001A95D0).
struct FrameFollower {
    PlacedObject* frameObject;      // 0x00
    u8* anchor;                     // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 pos;                      // 0x10
    s32 mode;                       // 0x20
    u8 pad24[0x50 - 0x24];
    f32 poly[3];                    // 0x50
    u8 pad5C[0x60 - 0x5C];
    f32 lo;                         // 0x60
    f32 hi;                         // 0x64
};

s32 ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);

void func_001A95D0(FrameFollower* self, Vec02* target, Vec02* out, void* to)
{
    Vec02 here;
    Mat02 rot;
    Vec02 pos2;
    Mat02 rot2;
    void* frame;
    Vec02* local;
    if (self->frameObject != 0 || self->anchor == 0) {
        frame = self->frameObject;
        local = &self->pos;
    } else {
        frame = *(void**)(self->anchor + 0x18);
        local = (Vec02*)(self->anchor + 0x40);
    }
    switch (self->mode) {
    case 0:
        TransformPointBetweenFrames(frame, to, local, out);
        return;
    case 1:
    case 2: {
        TransformPointBetweenFrames(frame, 0, local, &here);
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(here), Vu0::Q(*target))));
        f32* p = self->poly;
        f32 v = self->poly[0] + len * (p[1] + len * p[2]);
        f32 lo = self->lo;
        f32 hi = self->hi;
        f32 t;
        if (v < lo) {
            t = lo;
        } else if (hi < v) {
            t = hi;
        } else {
            t = v;
        }
        ComputeObjectFrameAtTime(frame, 0, &here, &rot, 0, 0, t);
        Vu0::Q(*out) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(*local)), Vu0::Q(here));
        if (to != 0) {
            ComputeObjectFrameAtTime(to, 0, &pos2, &rot2, 0, 0, t);
            Vu0::Q(*out) = Vu0::RotateTransposed(rot2, Vu0::Sub(Vu0::Q(*out), Vu0::Q(pos2)));
        }
        break;
    }
    }
}
