// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: return-address save and branch/shift sequence differ from retail.
#include "common.h"

struct Result_FD4A8 { s32 type; s32 pad; s32 bit; s64 value; };
void func_001FCA40(u64* input, Result_FD4A8* result);

s32 func_001FD4A8(u64 input)
{
    Result_FD4A8 result;
    func_001FCA40(&input, &result);
    if (result.type == 2) return 0;
    if (result.type < 2) return 0;
    if (result.type != 4) {
        s32 bit = result.bit;
        if (bit < 0) return 0;
        if (bit >= 32 && bit < 61)
            return (s32)(result.value << (bit - 60));
        if (bit >= 61) return -1;
        return (s32)(result.value >> (60 - bit));
    }
    return -1;
}
