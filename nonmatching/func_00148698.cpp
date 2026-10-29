// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: initialization values and conditional behavior are modeled, but float store order and register scheduling differ.
#include "common.h"

struct Object_148698 {
    u8 pad000[0x2D8];
    s32 f2D8;
    u8 pad2DC[0x44];
    f32 f320;
    u8 pad324[0x20];
    f32 f344;
    f32 f348;
    f32 f34C;
    f32 f350;
    f32 f354;
    f32 f358;
};
extern s32 D_0026EC60;
void func_00146340(void* self);
void func_00148698(Object_148698* self)
{
    func_00146340(self);
    self->f358 = 0.6f;
    self->f34C = 60.0f;
    self->f320 = 0.75f;
    self->f354 = 0.6f;
    self->f348 = 250.0f;
    self->f344 = 500.0f;
    self->f350 = 60.0f;
    if (D_0026EC60 != 0) return;
    self->f2D8 = 2;
}
