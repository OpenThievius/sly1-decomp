// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: helper calls and the frame match, but the early-return paths, argument register ordering, and range-selection code still differ.
#include "common.h"

struct Obj_12FE70 { s32 mode; void* first; void* second; u32 chunk; u32 begin; u32 start; u32 field18; u32 end; u32 field20; u32 limit; };
s32 func_0012FF10(void* self);
void func_001F8DB8(void* out, u32 start, u32 size);
void func_00140CC8(void* out, u32 blocks);

void func_0012FE70(Obj_12FE70* self)
{
    if (func_0012FF10(self) != 0) {
        return;
    }
    u32 limit = self->limit;
    if (limit == 0) {
        return;
    }
    u32 size = limit <= 0x3FFF ? limit : 0x4000;
    u32 start = self->start;
    u32 end = self->end;
    u32 begin = (start == end) ? start + 0x4000 : start;
    self->chunk = size;
    self->begin = begin;
    if (self->mode == 0) {
        func_001F8DB8(self->first, begin, size);
    } else if (self->mode == 1) {
        func_00140CC8(self->second, (size + 0x7FF) >> 11);
    }
}
