// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct RandomState_1F6708 { u8 pad[0x58]; u32 state; };
extern RandomState_1F6708* D_0027696C;

u32 func_001F6708(void)
{
    u32 state = D_0027696C->state * 0x41C64E6Du + 0x3039u;
    D_0027696C->state = state;
    return state & 0x7FFFFFFFu;
}
