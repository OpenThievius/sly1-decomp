// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: Store scheduling and the materialization of two constants still
//        differ from retail.
#include "common.h"

struct State_00121338 {
    u8 pad0[4];
    u32 value;
    u8 pad1[8];
    volatile s8 state[4];
};

void func_00121338(State_00121338* state, u32 value)
{
    state->state[0] = -1;
    state->value = value;
    state->state[3] = -1;
    state->state[2] = -1;
    state->state[1] = -1;
}
