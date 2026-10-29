// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: candidate frame is 0x50 versus retail 0x70; register allocation and call sequence still differ.
#include "common.h"
struct Entry_1B9FB0 { u32 key; u8 pad[0x3C]; void* zero; void* one; Entry_1B9FB0* next; };
struct List_1B9FB0 { Entry_1B9FB0* first; };
extern void* func_001387F8(void*, void*);
extern s32 func_00182F40(void*, void*);
s32 func_001B9FB0(void* a, void* b)
{
    Entry_1B9FB0* e = (Entry_1B9FB0*)func_001387F8(a,b);
    while (e) {
        u32 idx = e->key != *(u32*)((u8*)a + 0x50);
        if (func_00182F40(idx ? e->one : e->zero, a))
            return func_00182F40(idx ? e->zero : e->one, b);
        e = e->next;
    }
    return 0;
}
