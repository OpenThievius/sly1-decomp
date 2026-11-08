// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 265/292 (90.8%), checked 2026-11-08
#include "common.h"

// NEAR: every instruction and offset matches; the allocation of the loop variables differs (retail: self in s5, key in s6, the base in s2, i+1 in s3; ours: key in s2, self in s6, base in s3)
// Tried (2026-11-08, night-close9): the entries as 12-byte struct pointers give retail's self in s5 but fold the first count to bytes; written to keep the division, the allocation returns to this one.

void* MoveMemory(void* dst, void* src, s32 bytes);

struct Ent_1388A0 {
    s32 f0;
    s32 f4;
    s32 f8;
};

struct Self_1388A0 {
    u8 pad0[0x38];
    s32 f38;
    u8 pad3C[0x1AD8 - 0x3C];
    u8* f1AD8;
};

void RemoveColliderFromSweepAxes(Self_1388A0* self, s32 key)
{
    s32 i;
    u8* base;
    u8* cur;
    u8* last;

    for (i = 0; i < 3; i++) {
        base = self->f1AD8 + i * 0x1800;
        cur = base;
        for (;;) {
            while (((Ent_1388A0*)cur)->f4 != key) {
                cur += 12;
            }
            if (((Ent_1388A0*)cur)->f0 != 0) {
                break;
            }
            last = cur;
            cur += 12;
        }
        MoveMemory(last, last + 12, ((((cur - last) * (s32)0xAAAAAAAB) >> 2) * 12) - 12);
        MoveMemory(cur - 12, cur + 12, ((self->f38 * 2 - (((cur - base) * (s32)0xAAAAAAAB) >> 2)) * 12) - 12);
    }
}
