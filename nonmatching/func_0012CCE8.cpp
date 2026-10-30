// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the 140-byte loop body matches, but the compiler initializes
// the loop offset before the count branch and allocates the saved registers
// in a different order.
#include "common.h"

struct Obj_12CCE8 { u8 pad0[0x38]; s32 count; u8* items; };
void* func_001833F0(void* arg, s32 value);

void* func_0012CCE8(Obj_12CCE8* self, void* arg)
{
    if (self->count > 0) {
        s32 i = 0;
        s32 offset = 0;
        do {
            u8* item = self->items + offset;
            if (func_001833F0(arg, *(s32*)item) != 0) {
                return item;
            }
            i++;
            offset += 0x1C;
        } while (i < self->count);
    }
    return 0;
}
