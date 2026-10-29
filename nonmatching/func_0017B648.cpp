// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: helper semantics and frame size match, but object/global comparison operands and branch target order differ.
#include "common.h"
struct Object_17B648 { u8 pad000[0x550]; s32 state; f32 time; u8 pad558[0x10]; void* item; };
extern s32 D_00263E2C;
extern f32 D_0026185C;
extern f32 D_00263E04;
extern s32 D_00263E30;
void func_001B93F8(void*);
void func_0012E760(void);
void func_0017B8C0(void*);
void func_00160578(s32);
void func_0017B648(Object_17B648* self)
{
    func_001B93F8(self);
    if (self->item && *(f32*)((u8*)self->item + 0x18) == 0.0f) {
        func_0012E760();
        self->item = 0;
    }
    if (D_00263E2C != -1) func_0017B8C0(self);
    if (self->state == 2 && D_00263E04 < D_0026185C - self->time && !D_00263E30) {
        D_00263E30 = 1;
        func_00160578(2);
    }
}
