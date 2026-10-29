// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: entry search and callback semantics are modeled, but frame size, argument scheduling, and branch layout differ.
#include "common.h"

struct Entry_13B9D8 { u8 pad000[0x10]; void* data; u8 pad014[0x0C]; f32 value; s32 key; u8 pad028[8]; };
struct Object_13B9D8 { u8 pad000[0x684]; void* active; s32 count; Entry_13B9D8* entries; };
void func_00185D20(void*, s32, void*, void*, s32, s32, s32, void*, f32);
void func_0013B9D8(Object_13B9D8* self, s32 key, s32 a2, s32 a3, s32 a4, void* arg5)
{
    if (!self->active) return;
    s32 count = self->count;
    if (count <= 0) return;
    Entry_13B9D8* entries = self->entries;
    s32 index = 0;
    if (entries[0].key != key) {
        for (index = 1; index < count; index++)
            if (entries[index].key == key) break;
    }
    if (index < count) {
        Entry_13B9D8* entry = &entries[index];
        func_00185D20(self, key, entry, (u8*)entry + 0x10, 9, 0, 0, arg5, entry->value);
    }
}
