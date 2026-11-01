// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 236/196, checked 2026-11-01
// Near miss: the array-search behavior is modeled, but the result is 40 bytes too large and both float-search loops compile differently.
#include "common.h"

struct Obj_12D4A8 { u8 pad0[8]; void* owner; u8 pad0C[8]; f32 threshold; f32 direction; u32 pad1C; u32 index; };
struct Value_12D4A8 { f32 value; u8 pad[12]; };
struct Owner_12D4A8 { u8 pad[0x5C]; s32 count; Value_12D4A8* values; };

void func_0012D4A8(Obj_12D4A8* self)
{
    Owner_12D4A8* owner = (Owner_12D4A8*)self->owner;
    s32 count = owner->count;
    if (count == 0) {
        return;
    }
    s32 index = count - 1;
    if (self->direction >= 0.0f) {
        if (count <= 0) {
            index = 0;
        } else {
            Value_12D4A8* item = owner->values;
            f32 value = self->threshold;
            if (value <= item->value) {
                index = 0;
            } else {
                index = 1;
                item++;
                while (index < count && item->value < value) {
                    item++;
                    index++;
                }
            }
        }
    } else {
        if (index >= 0) {
            Value_12D4A8* item = owner->values + index;
            f32 value = self->threshold;
            while (index >= 0 && item->value > value) {
                item--;
                index--;
            }
        }
        index++;
    }
    self->index = index;
}
