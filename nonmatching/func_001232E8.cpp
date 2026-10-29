// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The field-load order and argument-register setup differ from retail.
#include "common.h"

struct Object_001232E8 { void** vtable; };
struct Table_001232E8 { u8 pad0[0x3C]; u8* base; };
struct Track_001232E8 {
    u8 pad0[8];
    Table_001232E8* table;
    u8 pad0C[8];
    f32 f14;
};
struct Owner_001232E8 {
    u8 pad0[4];
    void* value;
    u8 pad8[0x14];
    Track_001232E8* track;
    u8 pad20[8];
    s32 row;
};
typedef void (*Apply_001232E8)(void* self, void* owner, s32 zero, f32 value);
extern void func_00121580(void* self, void* value);

void func_001232E8(Owner_001232E8* self, void* value)
{
    Track_001232E8* track = self->track;
    u8* row = track->table->base + self->row * 0x1C;
    Object_001232E8* object = *(Object_001232E8**)(row + 0xC);
    if (object == 0) {
        func_00121580(self, value);
    } else {
        ((Apply_001232E8)object->vtable[0])(object, self->value, 0, track->f14);
    }
}
