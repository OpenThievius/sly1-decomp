// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 210/216 (97.2%), checked 2026-11-08
#include "common.h"
#include "collider.h"
#include "fpu.h"
#include "placed_object.h"
#include "vu0.h"
s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);
// NEAR (2026-11-07, worker vu0-e6): one swap: retail stores the difference vector (sqc2 vf3, 0(sp))
// after the mtc1 of the squared distance, here before it. The frame, the registers and every
// other instruction are retail's. Tried: the difference in a u128 local stored after the dot,
// the radii loaded first, the store after the sum.
// Night-close2 (2026-11-08): ToFloatMoved for the squared distance gives retail's order (mtc1 before the sqc2) but then the difference takes vf2 and the dot vf3 (retail vf3, vf1): 8 words; the Vec forms and the difference as a u128 local do not change it.

void func_00187A88(Collider* self, Collider* other, void* a2)
{
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(other->v140));
    f32 rs = self->radius3CC;
    f32 dist2 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
    f32 sum = rs + other->radius3CC;
    if (dist2 < 0.0001f) {
        return;
    }
    if (sum * sum < dist2) {
        return;
    }
    f32 dist = Fpu::Sqrt(dist2);
    Vec02 point;
    Vec02 n;
    {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(1.0f / dist);
        Vu0::Q(n) = Vu0::MulX(Vu0::Q(d), Vu0::Q(k));
    }
    {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(-rs);
        Vu0::Q(point) = Vu0::MulAddX(Vu0::Q(self->v140), Vu0::Q(n), Vu0::Q(k));
    }
    CreatePooledContact(dist - sum, self, other, &point, &n, 7, 0, 0, a2);
}
