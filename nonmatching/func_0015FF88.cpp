// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: retail uses a 0x60-byte frame versus this 0x40-byte frame; setup, loop registers, and store scheduling differ.
#include "common.h"
struct Object_15FF88 { u8 pad00[0x14]; void* resource; u8 pad18[0x1C]; s32 count; u8 pad38[0x20]; u8 pad58[0x0C]; void** results; s32 result_count; };
void func_00182C58(void*);
void* func_0018D500(s32);
void* func_0015A480(void*, void*, s32);
void func_0015F8B0(void*, void*);
void func_0015FF88(Object_15FF88* self)
{
    func_00182C58(self);
    self->results = (void**)func_0018D500(self->count * 4);
    self->result_count = 0;
    for (s32 i = 0; i < self->count; ++i) {
        void* result = func_0015A480(self->resource, *(void**)((u8*)self + 0x38 + i * 4), *(s32*)((u8*)self + 0x18));
        if (result) self->results[self->result_count++] = result;
    }
    func_0015F8B0(self->resource, (u8*)self + 0x58);
}
