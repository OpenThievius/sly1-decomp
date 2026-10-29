// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1C4180 { u8 pad[0x698]; s32 count; s32 items[1]; };

void func_001C4180(Obj_1C4180* self, s32 value)
{
    s32 n = self->count;
    self->items[n] = value;
    self->count = n + 1;
}
