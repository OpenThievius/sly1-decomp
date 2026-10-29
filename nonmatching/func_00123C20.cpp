// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The loop body is close, but register allocation and save order
//        differ.
#include "common.h"

struct Item_00123C20 { void** vtable; };
struct Owner_00123C20 {
    u8 pad0[0x5BC];
    s32 count;
    Item_00123C20* items[1];
};

void func_00123C20(Owner_00123C20* self)
{
    s32 i = 0;
    if (self->count <= 0) return;
    Item_00123C20** item = self->items;
    do {
        if (item[0]->vtable[0x13C / 4] != 0) {
            ((void (*)(void*))item[0]->vtable[0x13C / 4])(item[0]);
        }
        if (++i >= self->count) break;
        item++;
    } while (1);
}
