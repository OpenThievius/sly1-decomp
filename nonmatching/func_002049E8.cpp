// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the input copy and callback are modeled, but loop/store scheduling, table address register order, and saved-register opcodes differ from retail.
// NEAR: the input copy and callback are modeled. The loop store/branch schedule, table address register order, and saved-register opcodes still differ from retail.
#include "common.h"

struct State_2049E8 { u8 pad00[0x72]; u8 kind; };
struct Entry_2049E8 { u8 pad00[4]; u8* object; };
struct Object_2049E8 { u8 pad00[4]; s32 active; s32 size; u8 data[6]; };
extern u8 D_0062AAD0[];
extern State_2049E8* func_002044B0(s32);
extern s32 func_00203FD0(s32, s32);

s32 func_002049E8(s32 first, s32 second, u8* bytes)
{
    State_2049E8* state = func_002044B0(first);
    if (state->kind != 1)
        return 0;
    Entry_2049E8* entry = (Entry_2049E8*)(D_0062AAD0 + first * 112 + second * 28);
    Object_2049E8* object = (Object_2049E8*)entry->object;
    for (s32 i = 0; i < 6; i++)
        object->data[i] = bytes[i];
    object->active = 1;
    object->size = 6;
    s32 result = 1;
    if (func_00203FD0(first, second) != 1)
        result = 0;
    return result;
}
