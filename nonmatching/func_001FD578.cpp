// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: With the configured compiler the candidate is 92 bytes versus retail
//        84; save width and argument setup differ.
#include "common.h"

extern void func_001FCA40(void*, void*);
extern s64 func_001FD838(u32, u32, s32, u32);

s64 func_001FD578(u64 bits)
{
    u32 parts[8];
    func_001FCA40(&bits, parts);
    u64 mantissa = *(u64*)((u8*)parts + 16);
    u32 type = parts[0];
    u32 sign = parts[1];
    s32 exponent = parts[2];
    u32 extra = (u32)(mantissa & 0x3FFFFFFFULL);
    u32 shifted = (u32)(mantissa >> 30) | 1;
    if (extra == 0) shifted = (u32)(mantissa >> 30);
    return func_001FD838(type, sign, exponent, shifted);
}
