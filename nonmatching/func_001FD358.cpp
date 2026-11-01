// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 192/184, checked 2026-11-01
// SKIP: this function is in the documented double-precision runtime section, where the retail sd/ld saves require the unsupported Sony 2.9-ee-991111 compiler.
#include "common.h"
u64 func_001FC910(void*);
u64 func_001FD358(s32 value)
{
    struct Parts { u32 kind; u32 sign; s32 exponent; u32 pad; u64 mantissa; u32 tail[2]; } parts;
    parts.kind = 3;
    parts.sign = (u32)value >> 31;
    if (value == 0) {
        parts.kind = 2;
    } else {
        parts.exponent = 0x3C;
        if (parts.sign != 0) {
            if (value == (s32)0x80000000) return 0xC1E0000000000000ULL;
            parts.mantissa = (u32)-value;
        } else {
            parts.mantissa = value;
        }
        if (parts.mantissa <= 0x0FFFFFFFFFFFFFFFULL) {
            do {
                parts.mantissa <<= 1;
                parts.exponent--;
            } while (parts.mantissa <= 0x0FFFFFFFFFFFFFFFULL);
        }
    }
    return func_001FC910(&parts);
}
