// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 259/292 (88.7%), checked 2026-11-05
#include "common.h"

// NEAR: every instruction and offset matches; the allocation of the loop variables differs (retail: self in s5, key in s6, the base in s2, i+1 in s3; ours: key in s2, self in s6, base in s3)

void func_001F5B08(void* dst, void* src, s32 bytes);

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

void func_001388A0(Self_1388A0* self, s32 key)
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
        func_001F5B08(last, last + 12, ((((cur - last) * (s32)0xAAAAAAAB) >> 2) * 12) - 12);
        func_001F5B08(cur - 12, cur + 12, ((self->f38 * 2 - (((cur - base) * (s32)0xAAAAAAAB) >> 2)) * 12) - 12);
    }
}
