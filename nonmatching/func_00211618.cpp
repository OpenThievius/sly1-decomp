// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 148/152 (97.4%), checked 2026-11-08
// Still differs (2026-11-08, night-close5): `w18 + n` (6 lines), (s64) casts, a while loop, an early return (31) and permute.py --auto leave n in t2.
#include "common.h"
// Why (2026-11-08, tools/regalloc.py): n's extension (r141) and the w18 load (r139) are both set
// on each exit path and have the same global priority (4 refs over 24 insns); global-alloc breaks the
// tie to the lower pseudo, w18's. s64/u64 locals for n or w18 at the end, w18 read at the top, a s64
// parameter, `+ (u32)n` keep the order or change the code.
// Mechanism (2026-11-08, w4-211618, -dG dumps; docs/TOOLCHAIN.md "GCSE", "Sony's compiler"):
// the two values are PRE's reaching registers for the w18 load and (s64)n, copied into both
// arms of the join; their global-alloc tie falls to the pseudo number, which is GCSE's bucket
// order. With 34-35 insns at gcse the table has T = 17 buckets: the load is in bucket 2, the
// extension in 15. Retail needs the extension first: T = 21, 23, 25 (40 to 51 insns) or n held
// in a pseudo numbered 119-121 (`s32 count = n;` as the third pseudo gives EXACT, but only
// behind unused locals). The plain form `self->window <<= n; self->loaded -= n; while
// (self->loaded < 57) { ... } self->consumed += n;` has the same registers (6 lines, retail's
// operand order); a u32 byte (+2), `loaded += 8` (+1) and returning the count (+2) reach 39
// insns, still T = 19. Not found: a plausible form with 40+ insns at gcse.
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
