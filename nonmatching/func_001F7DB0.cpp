// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; retail uses 8-byte saved-register slots, while configured compiler emits sq/lq; loop and delay-slot scheduling differ.
#include "common.h"

struct Item_1F7DB0 { u8 pad00[0x10]; u32 flags; Item_1F7DB0* next; s32 state; };
struct Owner_1F7DB0 { s32 index; Item_1F7DB0* items; s32 count; };
s32 func_001F9D60(Owner_1F7DB0*);
void func_001F9DA8(void);

Item_1F7DB0* func_001F7DB0(Owner_1F7DB0* self)
{
    func_001F9D60(self);
    s32 count = self->count;
    s32 index = 0;
    Item_1F7DB0* item = self->items;
    if (count > 0) {
        do {
            if ((item->flags & 1) == 0) {
                item->flags = (index << 16) | 5;
                s32 state = self->index + 1;
                self->index = state;
                if (state == 1) {
                    self->index++;
                }
                item->next = item;
                item->state = state;
                func_001F9DA8();
                return item;
            }
            index++;
            item = (Item_1F7DB0*)((u8*)item + 0x40);
        } while (index < count);
    }
    func_001F9DA8();
    return 0;
}
