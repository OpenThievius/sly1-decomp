// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: mode cases and store order now match; the first compare uses v0 where retail uses v1.
#include "common.h"

struct Object_156188 {
    u8 pad000[0x1B0];
    s32 mode;
    u8 pad1B4[0x3C];
    union { f32 real; s32 bits; } first;
    f32 second;
    f32 third;
};
void func_001F5C0C(void*, s32, s32);
void func_00156188(Object_156188* self, s32 mode)
{
    self->mode = mode;
    func_001F5C0C(&self->first, 0, 0xC);
    switch (mode) {
    case 0x1B:
        self->first.bits = -1;
        self->second = 10.0f;
        break;
    case 0x18:
        self->second = 0.8f;
        self->first.real = 25.0f;
        self->third = 0.8f;
        break;
    default:
        return;
    }
}
