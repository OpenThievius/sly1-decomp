// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The size matches, but floating-point register allocation and
//        arithmetic/store order differ.
#include "common.h"

struct State_189F58 {
    f32 f00;
    u8 pad04[0x10];
    f32 f14;
    u8 pad18[8];
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    u8 pad30[8];
    f32 f38;
};
extern void func_001F5C0C(void* p, s32 v, s32 n);

void func_00189F58(State_189F58* self, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5)
{
    func_001F5C0C(self, 0, 0x40);
    f32 delta = f4 - f5;
    f32 value = (f4 + f5) / delta;
    self->f20 = f2;
    self->f14 = f1;
    self->f24 = f3;
    self->f00 = f0;
    self->f28 = value;
    self->f2C = 1.0f;
    self->f38 = f4 * (1.0f - value);
}
