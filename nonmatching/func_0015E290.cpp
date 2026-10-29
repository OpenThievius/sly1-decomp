// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: integer and float helper behavior is modeled, but saved-register order and frame temporaries differ.
#include "common.h"

struct Data_15E290 { u8 pad000[8]; s32 count; u8 pad00C[0x3C]; f32 scale; };
struct Object_15E290 { u8 pad000[0xC]; Data_15E290* data; };
s32 func_0015E068(void*, void*);
f32 func_0015E1F0(void*);
void func_0015E290(void* self, f32* amount, f32* product)
{
    s32 count = func_0015E068(self, amount);
    f32 max = func_0015E1F0(self);
    Data_15E290* data = ((Object_15E290*)self)->data;
    f32 value = (f32)data->count * data->scale;
    f32 result = (f32)count * value;
    if (amount) *amount = max;
    if (product) *product = result;
}
