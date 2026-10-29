// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: This candidate is 116 bytes versus retail 112; frame size and saved-
//        register layout differ.
#include "common.h"

struct Vtable_00123BB0 { u8 pad0[0x138]; void (*invoke)(void*); };
struct Element_00123BB0 { Vtable_00123BB0* vtable; };
struct Owner_00123BB0 { u8 pad0[0x5BC]; s32 count; Element_00123BB0** elements; };

void func_00123BB0(Owner_00123BB0* self)
{
    for (s32 i = 0; i < self->count; ++i) {
        Element_00123BB0* element = self->elements[i];
        if (element->vtable->invoke) element->vtable->invoke(element);
    }
}
