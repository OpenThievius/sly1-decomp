// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 148/152 (97.4%), checked 2026-11-06
#include "common.h"
// NEAR: only the t1/t2 registers of n and w18 swap (4 lines differ); dead-end tries: s64/u64 temp, += n

struct Str_211618 { u64 w0; u32 f8; u32 fC; u32 f10; u32 pad14; u64 w18; u32 f20; u32 f24; u32 f28; };

void AdvanceBits(Str_211618* self, s32 n)
{
    u64 w = self->w0 << n;
    u32 cnt = self->f10 - n;
    self->w0 = w;
    self->f10 = cnt;
    if (cnt < 0x39) {
        do {
            u8* p = (u8*)self->fC;
            u32 k = self->f10;
            u64 bits = (u64)*p << (0x38 - k);
            self->w0 = self->w0 | bits;
            p++;
            self->fC = (u32)p;
            if ((u32)p >= self->f24) {
                self->fC = self->f20;
            }
            u32 k2 = k + 8;
            self->f10 = k2;
            cnt = k2;
        } while (cnt < 0x39);
    }
    self->w18 = n + self->w18;
}
