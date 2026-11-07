// SPDX-License-Identifier: AGPL-3.0-or-later
// The C library's pseudo-random numbers, their own object from 0x1F66F8 to 0x1F6738
// (config/us/files.tsv): the seed setter and the generator, word for word a member of the
// toolchain's libc.a built from a .c source. The seed lives at +0x58 of the record
// g_randomState points to. No data of its own.
#include "common.h"

struct RandomState_1F6708 { u8 pad[0x58]; u32 state; };
extern RandomState_1F6708* D_0027696C;

void func_001F66F8(u32 value)
{
    g_randomState->state = value;
}

u32 func_001F6708(void)
{
    u32 state = g_randomState->state * 0x41C64E6Du + 0x3039u;
    g_randomState->state = state;
    return state & 0x7FFFFFFFu;
}
