// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 116/112, checked 2026-11-07
#include "common.h"
#include "switched_collider.h"
#include "collider.h"
#include "fpu.h"
#include "vu0.h"
// NEAR (2026-11-07, worker inline-vu0): the VU0 tail (qmtc2, vmulx.xyzw, the scale's store to
// the stack) is retail's. Only the max.s moves: retail loads f700 and the mass before it and
// multiplies after, which include/fpu.h's volatile Fpu::Max forbids (it is a barrier). With a
// copy of Max that is not volatile the function is retail's but for max.s and one lwc1 swapped
// (build/swarm/inline-vu0/tc_nv.cpp): evidence that max.s, like the VU0 helpers, was not
// volatile. fpu.h belongs to the max.s/min.s workers.

void SetColliderMass(Collider* self, f32 v);

void SetTurningColliderGravityScale(TurningCollider* self, f32 scale)
{
    f32 s = (0.1f >? scale);
    SetColliderMass(self, self->mass * self->f700 / s);
    Vec02 k;
    f32 r = s / self->f700;
    self->f700 = s;
    Vu0::Q(k) = Vu0::FromFloat(r);
    Vu0::Q(self->gravity) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Q(k));
}
