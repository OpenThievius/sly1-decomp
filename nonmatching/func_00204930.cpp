// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 155/180 (86.1%), checked 2026-11-01
// SKIP: this library function saves its registers with 8-byte sd/ld pairs;
// the current build tooling cannot select the separate compiler needed for
// this library code on a per-file basis.
#include "common.h"

struct Record_204930 { s32 field0; void* owner; void* argument; s32 fieldC; s32 field10; s32 state; };
extern u8 D_0062ACC0[];
extern u8 D_0062AA80[];
s32 func_001F8290(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5, s32 a6, s32 a7);
s32 func_00204610(void* self, void* arg, s32 mode);

s32 func_00204930(void* self, void* arg, s32 a2, s32 a3)
{
    Record_204930* record = (Record_204930*)D_0062ACC0;
    record->field0 = 6;
    record->fieldC = a2;
    record->field10 = a3;
    record->state = 6;
    record->owner = self;
    record->argument = arg;
    s32 result = func_001F8290(D_0062AA80, 1, 0, record, 0x80, record, 0x80, 0);
    if (result < 0) {
        return 0;
    }
    s32 state = record->state;
    if (state == 1) {
        func_00204610(self, arg, 2);
        state = record->state;
    }
    return state;
}
