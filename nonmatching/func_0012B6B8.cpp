// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 160/164 (97.6%), checked 2026-11-04
#include "common.h"

// NEAR: only register allocation differs: retail keeps i*4 in a3 and i+1 in a2, ours the other way round (q-variants with an index variable, a slot pointer and a goto-free next did not change it)

extern u8 D_00148D64[];
void func_00123ED0(void* self);

struct Crc_12B6B8 {
    u8 pad[0x2D0];
    u32 f2D0;
    s32 f2D4;
    void* f2D8;
    u32 table[256];
};

void func_0012B6B8(Crc_12B6B8* self)
{
    s32 i;

    func_00123ED0(self);
    self->f2D4 = 0x100018;
    self->f2D8 = D_00148D64;
    self->f2D0 = 0xFFFFFFFF;
    for (i = 0; i < 256; i++) {
        u32 c = (u32)i;
        s32 k = 7;
        do {
            if (c & 1) {
                c = (c >> 1) ^ 0xEDB88320;
            } else {
                c >>= 1;
            }
        } while (--k >= 0);
        self->table[i] = c;
    }
}
