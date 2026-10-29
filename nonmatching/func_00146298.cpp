// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the item scan is modeled, but retail preloads the first item and
// uses branch-likely iteration; this source compiles to a different loop and
// assigns the two float products to different registers.
#include "common.h"

struct Item_00146298 { u8 pad0[8]; s32 type; u8 pad0C[0x20]; f32 x; f32 y; };
struct Self_00146298 { u8 pad0[0x27C]; s32 count; Item_00146298** items; u8 pad284[0x2CC]; f32 scaleX; f32 scaleY; f32 scaleZ; };

void func_00146298(Self_00146298* self)
{
    s32 count = self->count;
    if (count > 0) {
        Item_00146298* item = self->items[0];
        s32 i = 0;
        do {
            if (item->type == 6) {
                item->x = -(self->scaleX * self->scaleY);
                item->y = -(self->scaleX * self->scaleZ);
            }
            i++;
            if (i >= count) {
                break;
            }
            item = self->items[i];
        } while (1);
    }
}
