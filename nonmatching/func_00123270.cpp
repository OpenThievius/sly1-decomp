// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The field loads and argument-register setup differ from retail.
#include "common.h"

struct Object_00123270 { void** vtable; };
struct Table_00123270 { u8 pad0[0x3C]; u8* base; };
struct Track_00123270 {
    u8 pad0[8];
    Table_00123270* table;
    u8 pad0C[8];
    f32 f14;
    f32 f18;
};
struct Owner_00123270 {
    u8 pad0[4];
    void* value;
    u8 pad8[0x14];
    Track_00123270* track;
    u8 pad20[8];
    s32 row;
};
typedef void (*Apply_00123270)(void* self, void* owner, s32 zero,
                               void* value, s32 mode, f32 a, f32 b);
extern void func_00121568(void* self, void* value);

void func_00123270(Owner_00123270* self, void* value, s32 mode, void* unused)
{
    Track_00123270* track = self->track;
    u8* row = track->table->base + self->row * 0x1C;
    Object_00123270* object = *(Object_00123270**)(row + 0x10);
    if (object != 0) {
        ((Apply_00123270)object->vtable[0])(object, self->value, 0, value,
                                            mode, track->f14, track->f18);
    } else {
        func_00121568(self, value);
    }
}
