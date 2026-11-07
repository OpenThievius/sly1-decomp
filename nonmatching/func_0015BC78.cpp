// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 185/208 (88.9%), checked 2026-11-07
// NEAR: the object cycler's timed message (message 6, the point and the negated velocity). Everything matches except where the receiver (f678) is loaded: retail loads it into a2 after the 1.0 constant and before the vmulx, and calls through a2 with `move a0, a2` in the delay slot; ours loads it into a0 after the stores and calls through a0. A local for the receiver (before the vector work, at the top, before the clock test) moves the load but never into a2.
#include "common.h"
#include "object_cycler.h"
#include "globals.h"
#include "vu0.h"

struct __attribute__((aligned(16))) GroupForwardMessage {
    s32 f0;
    u8 pad0[0x10 - 0x4];
    Quad16 f10;
    Quad16 f20;
    u8 pad1[0x50 - 0x30];
};

extern f32 g_gameClock[];
f32 RandomFloatInRange(f32 a, f32 b);
void ConvertPositionToWorld(BaseObject* self, Quad16* out);

void func_0015BC78(ObjectCycler* self)
{
    GroupForwardMessage loc;
    Vec02 k;
    if (self->receiver678 && self->f680 <= g_gameClock[1]) {
        loc.f0 = 6;
        if (self->source67C)
            ConvertPositionToWorld(self->source67C, &loc.f20);
        else
            loc.f20 = *(Quad16*)&self->v140;
        Vu0::Q(k) = Vu0::FromFloat(-1.0f);
        Vu0::Q(loc.f10) = Vu0::MulX(Vu0::Q(self->v150), Vu0::Q(k));
        ((f32*)&loc.f10)[2] = 0.0f;
        self->receiver678->desc->m1B(self->receiver678, &loc);
        self->f680 = g_gameClock[1] + RandomFloatInRange(self->p670.a, self->p670.b);
    }
}
