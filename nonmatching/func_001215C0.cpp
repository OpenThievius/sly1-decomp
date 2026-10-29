// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: This candidate is 148 bytes versus retail 132; register allocation
//        and branch layout differ.
#include "common.h"

struct StateData_001215C0 { u8 pad[0x450]; s32 first; u8 pad2[0x1C]; s32 second; };
struct State_001215C0 { u32* vtable; u8 pad[0x2C5]; s8 first; s8 second; };
struct Object_001215C0 { u8 pad[4]; State_001215C0* state; u8 pad2[8]; s8 first; s8 second; };

void func_001215C0(Object_001215C0* object)
{
    State_001215C0* state = object->state;
    State_001215C0* flagged = (state->vtable[2] & 2) ? state : 0;
    s8 value = state->first;
    if (value != -1) {
        object->first = value;
    } else if (flagged != 0 && ((StateData_001215C0*)flagged)->first != 3) {
        object->first = 3;
    } else {
        object->first = 2;
    }

    value = state->second;
    if (value != -1) {
        object->second = value;
    } else if (flagged != 0 && ((StateData_001215C0*)flagged)->second == 3) {
        object->second = 3;
    } else {
        object->second = 2;
    }
}
