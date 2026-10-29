// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: The global field load folds the address offset; retail materializes
// the base first. The shared epilogue layout also differs.
#include "common.h"
extern s32 D_0025C34C;
struct State_0011E2E8 { s32 pad[4]; s32 value; };
extern State_0011E2E8 D_00260DC0[];
s32 func_00203D90();
s32 func_0011E2E8()
{
    if (!D_0025C34C) return func_00203D90();
    return D_00260DC0[0].value;
}
