// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the list traversal and bounded item insertion match in behavior.
// The compiler uses a2 for the loop counter and a0 for the item pointer, while
// retail uses a3 and a2 respectively, so the body differs by register order.
#include "common.h"

struct Item_0015F8B0 { u8 pad0[0x6C]; u32 count; void* links[4]; };
struct List_0015F8B0 { u8 pad0[8]; s32 count; Item_0015F8B0** items; };
void func_0015F7D8(void);

void func_0015F8B0(void* unused, List_0015F8B0* list, void* unused2)
{
    if (list->count >= 2) {
        for (s32 i = 0; i < list->count; i++) {
            Item_0015F8B0* item = list->items[i];
            u32 index = item->count;
            if (index < 4) {
                item->links[index] = list;
                item->count = index + 1;
            }
        }
        func_0015F7D8();
    }
}
