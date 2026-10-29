// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: frame and helper sequence mostly match; retail uses FPU zero stores and has different saved-register allocation.
#include "common.h"

struct EntryList_153608 { u32 a, b, c; };
struct Object_153608 {
    s32 unused;
    s32 count;
    u8* entries;
    EntryList_153608 first;
    EntryList_153608 second;
    EntryList_153608 third;
    EntryList_153608 fourth;
    s32 state;
};
struct __attribute__((aligned(16))) Entry_153608 {
    u8 pad000[0x34];
    f32 first;
    f32 second;
    u8 pad03C[0x10];
    u8 data[8];
};
void func_00152440(void*);
void func_001F5C0C(void*, s32, s32);
void func_00152470(void*, void*);
void func_00153608(Object_153608* self)
{
    func_00152440(&self->first);
    self->state = 0;
    func_00152440(&self->second);
    func_00152440(&self->third);
    func_00152440(&self->fourth);
    if (self->count > 0) {
        f32 zero = 0.0f;
        s32 offset = 0;
        s32 i = 0;
        do {
            Entry_153608* entry = (Entry_153608*)(self->entries + offset);
            ++i;
            entry->second = zero;
            entry->first = zero;
            func_001F5C0C(entry->data, 0, 8);
            func_00152470((u8*)self + 0x30, entry);
            offset += 0x60;
        } while (i < self->count);
    }
}
