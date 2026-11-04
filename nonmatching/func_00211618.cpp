// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 142/152 (93.4%), checked 2026-11-04
#include "common.h"
// NEAR: the byte-refill loop matches; two registers swap (t1/t2 for n and w18, a3 for the loop sum) (10 lines)

struct Str_211618 { u64 w0; u32 f8; u32 fC; u32 f10; u32 pad14; u64 w18; u32 f20; u32 f24; u32 f28; };

void func_00211618(Str_211618* self, s32 n)
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
            k = k + 8;
            self->f10 = k;
            cnt = k;
        } while (cnt < 0x39);
    }
    self->w18 = self->w18 + n;
}
