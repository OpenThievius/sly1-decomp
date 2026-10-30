// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: callback loop and maxima are modeled, but loop shape and max operation lowering differ.
#include "common.h"

struct Callback_15E1F0 {
    u8 pad000[0x18];
    s16 offset;
    u16 pad01A;
    f32 (*function)(void*, s32);
};
struct Item_15E1F0 { u8 pad000[0x4C]; Callback_15E1F0* callback; };
struct Object_15E1F0 { u8 pad000[8]; Item_15E1F0* item; };
void func_0015DB80(void*);
s32 func_0015DBE0(void*);
f32 func_0015E1F0(Object_15E1F0* self)
{
    f32 maximum = 0.0f;
    f32 total = 0.0f;
    func_0015DB80(self);
    s32 type;
    while ((type = func_0015DBE0(self)) != 0) {
        if (type == 10) {
            if (total > maximum) maximum = total;
            total = 0.0f;
        } else {
            Item_15E1F0* item = self->item;
            Callback_15E1F0* cb = item->callback;
            total += cb->function((u8*)item + cb->offset, type);
        }
    }
    if (total > maximum) maximum = total;
    return maximum;
}
