// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: list iteration is modeled, but loop setup, register allocation, and frame layout differ.
#include "common.h"

struct IntList_13E7C0 { s32 count; void* items[1]; };
void* func_0015A418(void*, s32, void*, void*);
void func_0013E8D8(void*, void*);
void func_00182ED8(void*);
void func_0013E7C0(void* self, IntList_13E7C0* list, void* context, void* unused)
{
    s32 left = list->count;
    if (left <= 0) return;
    void** item = list->items;
    do {
        void* object = func_0015A418(self, 0x104, *item, context);
        if (object) {
            func_0013E8D8(list, object);
            func_00182ED8(object);
        }
        --left;
        ++item;
    } while (left);
}
