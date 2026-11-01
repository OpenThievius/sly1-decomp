// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 164/180, checked 2026-11-01
// NEAR: state checks and value assembly are modeled, but table-multiply order, branch sequence, and saved-register opcodes differ from retail.
// NEAR: the state checks and 32-bit value assembly are modeled. GCC keeps the table multiplies in the opposite order, emits a different branch sequence, and saves registers with sq/lq instead of sd/ld.
#include "common.h"

struct Entry_204B80 { u8 pad00[0x10]; u32 active; };
struct State_204B80 {
    u8 pad00[0x64];
    u8 low;
    u8 pad65;
    u8 high;
    u8 pad67[0x0B];
    u8 b72;
    u8 pad73[0x06];
    u8 b79;
    u8 b7A;
    u8 b7B;
    u8 b7C;
};
extern u8 D_0062AAD0[];
extern State_204B80* func_002044B0(s32);

s32 func_00204B80(s32 first, s32 second)
{
    s32 first_offset = first * 112;
    s32 second_offset = second * 28;
    Entry_204B80* entry = (Entry_204B80*)(D_0062AAD0 + first_offset + second_offset);
    if (entry->active == 0)
        return 0;
    State_204B80* state = func_002044B0(first);
    if (state->b72 == 1) {
        if (state->low >= 2 && state->high >= 2) {
            u8 b7a = state->b7A;
            u8 b7c = state->b7C;
            u8 b7b = state->b7B;
            u8 b79 = state->b79;
            s64 value = b79;
            value += (s64)b7a << 8;
            value += (s64)b7b << 16;
            value += (s64)b7c << 24;
            return (s32)((value << 32) >> 32);
        }
    }
    return 0;
}
