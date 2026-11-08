// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 596/592, checked 2026-11-07
#include "transform_object.h"
#include "warp_page.h"
#include "oscillator.h"
#include "camera.h"
#include "list_iter.h"
#include "screen_element.h"
#include "shapes.h"
#include "globals.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "pad_record.h"
#include "object_link.h"
#include "contact_tracker.h"
#include "lookup_object.h"
#include "object_sub_group.h"
#include "switched_collider.h"
#include "animation.h"
#include "object_gatherer.h"
#include "asm_func.h"
#include "vu0.h"
#include "common.h"
#include "common.h"
// NEAR (2026-11-08, wave 4): Dot, ScalarAt/Scalar and MulAddX2 per entry as retail's sequences; the loop is compiled with loop optimisation (constants 0, 1, 2pi hoisted into f21-f23, the entry pointer strength-reduced) where retail multiplies i by 0xD0 each time and loads each constant inside; the sin/cos pair sits below the Scalar slot (0x00/0x04, slot 0x10) where retail has the slot at 0 and the pair at 0x10. Declaring the second loop's vector first fixes the pair but moves the slot to 0x20.
struct OscillatorSweepEntry {
    s32 kind;               // 0x00: 0 for an axis entry
    u8 pad04[0x10 - 0x04];
    Vec02 v10;              // 0x10: the axis
    Vec02 v20;              // 0x20
    u8 pad30[0x40 - 0x30];
    Vec02 v40;              // 0x40
    u8 pad50[0x64 - 0x50];
    f32 scale;              // 0x64
    f32 f68;                // 0x68
    f32 f6C;                // 0x6C
    u8 pad70[0xD0 - 0x70];
};

extern f32 g_gameClock[];
extern const Vec02 D_00248D30;
void ComputeSinCos(f32 x, f32* sinOut, f32* cosOut);

void ComputeOscillatorDisplacement(Oscillator* self, Vec02* in, Vec02* deltas, Vec02* outA, Vec02* outDeltas, Vec02* outB, f32 time)
{
    u128 pos = Vu0::Q(*in);
    u128 other = Vu0::Q(D_00248D30);
    u128 base = pos;
    for (s32 i = 0; i < self->entryCount; i++) {
        OscillatorSweepEntry* e = (OscillatorSweepEntry*)((u8*)self + 0x50) + i;
        if (e->kind != 0) {
            continue;
        }
        f32 scale = e->scale;
        f32 period = scale == 0.0f ? 0.0f : 1.0f / scale;
        if (period < time) {
            continue;
        }
        f32 phase = Vu0::ToFloat(Vu0::Dot(base, Vu0::Q(e->v10))) * scale + g_gameClock[1] * e->f68 + e->f6C;
        f32 sc[2];
        ComputeSinCos(phase * 6.2831855f, &sc[0], &sc[1]);
        u128 c = Vu0::ScalarAt(sc[1]);
        f32 s = sc[0];
        pos = Vu0::MulAddX2(pos, Vu0::Q(e->v20), c, Vu0::Q(e->v40), Vu0::Scalar(s));
        if (outB != 0) {
            other = Vu0::MulAddX2(other, Vu0::Q(e->v20), Vu0::Scalar(-s), Vu0::Q(e->v40), c);
        }
    }
    if (outA != 0) {
        Vu0::Q(*outA) = pos;
    }
    if (outB != 0) {
        Vu0::Q(*outB) = other;
    }
    if (deltas != 0 && outDeltas != 0) {
        for (s32 k = 0; k < 3; k++) {
            Vec02 t;
            Vu0::Set(t, Vu0::Add(Vu0::Q(*in), Vu0::Q(deltas[k])));
            ComputeOscillatorDisplacement(self, in, 0, &t, 0, 0, time);
            Vu0::Q(outDeltas[k]) = Vu0::Sub(Vu0::Q(t), pos);
        }
    }
}

