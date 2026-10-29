// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; candidate frame is 96 bytes vs retail 112, with loop/control layout differences.
#include "common.h"

typedef s32 (*Test_1CBD58)(void*);
struct Item_1CBD58 { Test_1CBD58* vtbl; };
struct Self_1CBD58 { u8 pad00[0x58]; s32 count; Item_1CBD58* items[1]; };

s32 func_001CBD58(Self_1CBD58* self)
{
    s32 result = 1;
    for (s32 i = 0; i < self->count; i++) {
        Item_1CBD58* item = self->items[i];
        s32 code = item->vtbl[92](item);
        if (code == 2) break;
        if (code == 0) result = 0;
    }
    return result;
}
