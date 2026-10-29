// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// A count followed by that many values.
struct IntList { s32 count; s32 items[1]; };

void func_0011A338(IntList* list, int value)
{
    list->items[list->count++] = value;
}

void func_0011A6C0(IntList* list, int value)
{
    for (int i = 0; i < list->count; i++)
        if (list->items[i] == value)
            return;
    list->items[list->count++] = value;
}

// A record that keeps a stack of values at 0x708.
struct StackAt708 { u8 pad[0x708]; s32 count; s32 items[1]; };

int func_0011A748(StackAt708* stack)
{
    if (stack->count > 0)
        return stack->items[--stack->count];
    return 0;
}
