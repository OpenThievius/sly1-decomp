// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 159/184 (86.4%), checked 2026-11-07
#include "common.h"
#include "fpu.h"
#include "globals.h"
#include "placed_object.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-e6): the code is retail's but for the registers: retail's first
// pointer pair is a2/a3 with the count in a2, here the count and the index take other registers
// (21 lines differ, all of them register numbers and one move). Tried: the count in a local, the
// pointer walk (*d++), a Vec02[2], a union with u128, the accumulator as a local struct.

// What func_001F3140 reads: 0xD0-byte entries from +0x50, a count at +0x38; an entry whose first
// word is 0 holds two 3-float vectors at +0x20 and +0x40.
struct SpanEntry {
    s32 used;               // 0x00
    u8 pad04[0x1C];
    f32 lo[3];              // 0x20
    u8 pad2C[0x14];
    f32 hi[3];              // 0x40
    u8 pad4C[0xD0 - 0x4C];
};
struct SpanSet {
    u8 pad0[0x38];
    s32 count;              // 0x38
    u8 pad3C[0x50 - 0x3C];
    SpanEntry entries[1];   // 0x50
};

void func_001F3140(SpanSet* self, Vec02* out)
{
    Vec02 sum;
    Vec02 span;
    sum = D_00248D30;
    for (s32 i = 0; i < self->count; i++) {
        SpanEntry* e = &self->entries[i];
        if (e->used == 0) {
            f32* d = &span.x;
            for (s32 k = 0; k < 3; k++) {
                d[k] = Fpu::Sqrt(e->lo[k] * e->lo[k] + e->hi[k] * e->hi[k]);
            }
            Vu0::Q(sum) = Vu0::Add(Vu0::Q(sum), Vu0::Q(span));
        }
    }
    *out = sum;
}
