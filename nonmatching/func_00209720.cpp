// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: resource open, status checks, and cleanup are modeled, but fixed-table addressing, initial load scheduling, and saved-register opcodes differ from retail.
// NEAR: the resource open, status checks, and cleanup are modeled. GCC folds the fixed table base into a load displacement and schedules the initial global loads differently; saved-register opcodes differ.
#include "common.h"

struct Slot_209720 { u8 pad00[0x24]; s32 size; };
extern s32 D_0027AECC;
extern s32 D_0027AEC8;
extern u8 D_0062AD40[];
extern s32 D_0062ADC0;
extern u8 D_0062C300[];
extern s32 func_001F6B70(s32);
extern s32 func_001F6B40(s32);
extern s32 func_001F8290(s32, s32, s32, void*, s32, void*, s32, s32, s32);

s32 func_00209720(void* self)
{
    if (func_001F6B70(D_0027AECC) < 0)
        return -200;
    Slot_209720* slot = (Slot_209720*)D_0062AD40;
    if (slot->size == 0) {
        func_001F6B40(D_0027AECC);
        return -100;
    }
    D_0062ADC0 = (s32)self;
    s32 result = func_001F8290(D_0027AECC, 3, 1, &D_0062ADC0, 0x30, D_0062C300, 4, 0, 0);
    if (result == 0)
        D_0027AEC8 = 3;
    else
        func_001F6B40(D_0027AECC);
    return result;
}
