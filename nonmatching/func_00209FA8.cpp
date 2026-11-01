// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 139/200 (69.5%), checked 2026-11-01
// NEAR: resource open and cleanup are modeled, but fixed-table addressing, request-store scheduling, and saved-register opcodes differ from retail.
// NEAR: the resource open and cleanup are modeled. GCC folds the fixed table base into a load displacement, schedules request stores differently, and uses sq/lq instead of sd/ld.
#include "common.h"

struct Slot_209FA8 { u8 pad00[0x24]; s32 size; };
struct Request_209FA8 { s32 owner; s32 channel; };
extern s32 D_0027AECC;
extern s32 D_0027AEC8;
extern u8 D_0062AD40[];
extern Request_209FA8 D_0062ADC0;
extern u8 D_0062C300[];
extern s32 func_001F6B70(s32);
extern s32 func_001F6B40(s32);
extern s32 func_001F8290(s32, s32, s32, void*, s32, void*, s32, s32, s32);

s32 func_00209FA8(s32 owner, s32 channel)
{
    if (func_001F6B70(D_0027AECC) < 0)
        return -200;
    Slot_209FA8* slot = (Slot_209FA8*)D_0062AD40;
    if (slot->size == 0) {
        func_001F6B40(D_0027AECC);
        return -100;
    }
    D_0062ADC0.owner = owner;
    D_0062ADC0.channel = channel;
    s32 result = func_001F8290(D_0027AECC, 0x10, 1, &D_0062ADC0, 0x30, D_0062C300, 4, 0, 0);
    if (result == 0)
        D_0027AEC8 = 0x10;
    else
        func_001F6B40(D_0027AECC);
    return result;
}
