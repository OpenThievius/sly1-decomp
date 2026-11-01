// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 156/176, checked 2026-11-01
// NEAR: aligned 16-byte and 8-byte copies are expressed, but bulk/tail loop control, pointer updates, and return scheduling differ.
#include "common.h"
struct __attribute__((aligned(16))) Quad_1F5A58 { u64 lo, hi; };
struct __attribute__((aligned(8))) Double_1F5A58 { u64 value; };
void* func_001F5A58(void* dst, const void* src, u32 size)
{
    u8* d = (u8*)dst;
    const u8* s = (const u8*)src;
    u32 n = size;
    if (n >= 32 && ((((u32)d | (u32)s) & 15) == 0)) {
        do { *(Quad_1F5A58*)d = *(const Quad_1F5A58*)s; s += 16; d += 16; n -= 16; }
        while (n >= 32);
        if (n >= 8) { *(Double_1F5A58*)d = *(const Double_1F5A58*)s; s += 8; d += 8; n -= 8; }
    }
    while (n--) *d++ = *s++;
    return dst;
}
