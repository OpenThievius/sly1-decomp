// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 531/592 (89.7%), checked 2026-11-07
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
// NEAR (2026-11-07, night-loop): the loop now as retail's: its vectors as Vu0::Vec values (one u128 in a struct, passed and returned by value), whose register copies make the loop big enough (94 real insns at the loop pass, the limit with a call is 80) that loop.c leaves 0, 1.0, 2pi and the index multiplication (li 0xD0; mult) inside it, as retail does (docs/TOOLCHAIN.md, "Loops"); the frame (weight slot 0, sin and cos at 0x10/0x14 as two locals), the c, s, c weight stores and the recursion's arguments match. Still differs: the scheduling around the call, 19 lines: retail loads e->f68 before the dot's qmfc2 and multiplies dot*scale before clock*f68 (ours the other way, and a1's addiu earlier), and after the call loads cos (lw) before sin (lwc1), mfc1 into v0 where ours uses v1.
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

void ComputeOscillatorDisplacement(Oscillator* self, f32 time, Vec02* in, Vec02* deltas, Vec02* outA, Vec02* outDeltas, Vec02* outB)
{
    Vu0::Vec pos = Vu0::Vec::Of(*in);
    Vu0::Vec other = Vu0::Vec::Of(D_00248D30);
    Vu0::Vec base = pos;
    for (s32 i = 0; i < self->entryCount; i++) {
        OscillatorSweepEntry* e = (OscillatorSweepEntry*)((u8*)self + 0x50) + i;
        if (e->kind != 0) {
            continue;
        }
        f32 period = e->scale == 0.0f ? 0.0f : 1.0f / e->scale;
        f32 scale = e->scale;
        if (period < time) {
            continue;
        }
        f32 phase = Vu0::ToFloat(Vu0::Dot(base, Vu0::Vec::Of(e->v10))) * scale + g_gameClock[1] * e->f68 + e->f6C;
        f32 sn, cs;
        ComputeSinCos(phase * 6.2831855f, &sn, &cs);
        pos = Vu0::MulAddX2(pos, Vu0::Vec::Of(e->v20), Vu0::Vec::ScalarAt(cs), Vu0::Vec::Of(e->v40), Vu0::Vec::Scalar(sn));
        if (outB != 0) {
            other = Vu0::MulAddX2(other, Vu0::Vec::Of(e->v20), Vu0::Vec::FromFloat(-sn), Vu0::Vec::Of(e->v40), Vu0::Vec::ScalarAt(cs));
        }
    }
    if (outA != 0) {
        Vu0::Q(*outA) = pos.q;
    }
    if (outB != 0) {
        Vu0::Q(*outB) = other.q;
    }
    if (deltas != 0 && outDeltas != 0) {
        for (s32 k = 0; k < 3; k++) {
            Vec02 t;
            Vu0::Set(t, Vu0::Add(Vu0::Q(*in), Vu0::Q(deltas[k])));
            ComputeOscillatorDisplacement(self, time, &t, 0, &t, 0, 0);
            Vu0::Q(outDeltas[k]) = Vu0::Sub(Vu0::Q(t), pos.q);
        }
    }
}

