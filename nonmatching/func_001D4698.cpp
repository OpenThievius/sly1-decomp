// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 409/432 (94.7%), checked 2026-11-07
// NEAR: the VU0 work (MulXSum3 twice, its Scalars, the speed's ScalarAt) and the walk-mode tests are retail's. In the forward branch retail computes min(0, x) as min.s f2, f0 (zero), f1 (x) and gives s vf3, the second row vf2 and the result vf3; here min.s takes x first and the weight and row registers trade places. The weights inline in the Scalars give the other branch's x in f0 instead (40 lines); the order of the min, max and Scalar statements, x hoisted, and the operands of <? and >? swapped: no closer.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "game_clock.h"
#include "c8b.h"
#include "vu0.h"
void ComputePolarOffset(Vec02* out, f32 angle, f32 radius, f32 z);

// The velocity of a heading and speed, from six axes of the basis: forward (y) by the
// heading's length ahead, and right or left by its side (x), the set picked by the walk mode.
void SetPlayerVelocityFromHeading(Player* self, const Vec02* basis, f32 heading, f32 speed)
{
    Vec02 h;
    ComputePolarOffset(&h, heading - self->f638, speed, 0.0f);
    f32 m;
    if (10.0f < h.y) {
        if (self->fA14 == 0) {
            h.y = 0.0f;
            m = 0.0f;
        } else {
            m = 1.0f;
        }
    } else if (h.y < -10.0f) {
        if (self->fA14 == 1) {
            h.y = 0.0f;
            m = 1.0f;
        } else {
            m = 0.0f;
        }
    } else if (self->fA14 == -1) {
        m = 0.0f;
    } else {
        m = (f32)self->fA14;
    }
    if (m == 1.0f) {
        f32 lo = 0.0f <? h.x;
        f32 hi = 0.0f >? h.x;
        u128 s = Vu0::Scalar(h.y);
        u128 t = Vu0::Scalar(hi);
        u128 u = Vu0::Scalar(-lo);
        Vu0::Q(self->v640) = Vu0::MulXSum3(Vu0::Q(basis[3]), s, Vu0::Q(basis[7]), t, Vu0::Q(basis[11]), u);
    } else {
        u128 s = Vu0::Scalar(-h.y);
        u128 t = Vu0::Scalar(0.0f >? h.x);
        u128 u = Vu0::Scalar(-(0.0f <? h.x));
        Vu0::Q(self->v640) = Vu0::MulXSum3(Vu0::Q(basis[1]), s, Vu0::Q(basis[5]), t, Vu0::Q(basis[9]), u);
    }
    self->v640.z = 0.0f;
    Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(self->v640), Vu0::ScalarAt(*(f32*)((u8*)self->watched2230 + 0x18)));
}
