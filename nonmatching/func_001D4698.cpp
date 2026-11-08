// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 430/432 (99.5%), checked 2026-11-08
// NEAR (2026-11-08, night-close7): all but two instructions: retail loads watched2230 into v0 and its float's bits with lw v0,0x18(v0) (the open `lw X,0(X)` before a qmtc2 of docs/TOOLCHAIN.md); ours loads the pointer into v1. MinF/MaxF inline (b <? a, b >? a, called with x first) give retail's min.s/max.s operand order and FPRs in both arms, with arm 1's weights inline in the Scalars as arm 2's. Tried for the lw: the weight named first, the pointer named, the vector named, Set, a float index.
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
static inline f32 MinF(f32 a, f32 b) { return b <? a; }
static inline f32 MaxF(f32 a, f32 b) { return b >? a; }
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
        u128 s = Vu0::Scalar(h.y);
        u128 t = Vu0::Scalar(MaxF(h.x, 0.0f));
        u128 u = Vu0::Scalar(-MinF(h.x, 0.0f));
        Vu0::Q(self->v640) = Vu0::MulXSum3(Vu0::Q(basis[3]), s, Vu0::Q(basis[7]), t, Vu0::Q(basis[11]), u);
    } else {
        u128 s = Vu0::Scalar(-h.y);
        u128 t = Vu0::Scalar(MaxF(h.x, 0.0f));
        u128 u = Vu0::Scalar(-MinF(h.x, 0.0f));
        Vu0::Q(self->v640) = Vu0::MulXSum3(Vu0::Q(basis[1]), s, Vu0::Q(basis[5]), t, Vu0::Q(basis[9]), u);
    }
    self->v640.z = 0.0f;
    Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(self->v640), Vu0::ScalarAt(*(f32*)((u8*)self->watched2230 + 0x18)));
}
